#!/usr/bin/env python3
# Replay ANOTHER golden workload against an ALREADY-SYNTHESIZED cosim solution.
#
# EVA is programmable: the RTL is fixed, only the router-delivered program and the
# input vectors change (the `one_bitstream` property). So there is no need to re-run
# the ~7 h Catapult synthesis per workload -- regenerate input*.data, re-run the
# SCVerify ncsim makefile, read output*.data back. Minutes instead of hours.
#
# HARD CONSTRAINT: the lane length L is baked into the RTL's memory ports, so every
# replayed workload MUST use the same L as the synthesized run (LFORCE).
#
#   WL=mmm PRJ=/scratch/.../8x8_v30ts_cosim_fft LFORCE=928 python scripts/replay_cosim.py
import os, sys, re, glob, subprocess
import numpy as np

MGC = os.environ.setdefault("MGC_HOME", "/opt/siemens/catapult/2024.2/Mgc_home")
os.environ["PATH"] = f"{MGC}/bin:" + os.environ.get("PATH", "")
NC_ROOT = os.environ.get("NC_ROOT", "/opt/cadence/XCELIUM2403")
HERE = os.path.dirname(os.path.abspath(__file__)); ROOT = os.path.dirname(HERE)
sys.path.insert(0, "/home/zsm9/allo_sup"); sys.path.insert(0, os.path.join(ROOT, "chip"))
for _p in sorted(sum([glob.glob(os.path.join(ROOT, _d, "v[0-9]*"))
                      for _d in ("designs", "tools", "deadends")], [])):
    if os.path.isdir(_p):
        sys.path.append(_p)

GB = "/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array"
LOG = "/home/zsm9/eva_tb_logs"
CFG = {
 "mmm":       ("mmm",                         "lft", 2, "btm", "sys_tx_btm_data", "pe_array_mmm.out"),
 "fft":       ("fft",                         "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_fft.out"),
 "cordic_cr": ("cordic_circular_rotation",    "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_cr.out"),
 "cordic_cv": ("cordic_circular_vectoring",   "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_cv.out"),
 "cordic_hr": ("cordic_hyperbolic_rotation",  "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_hr.out"),
 "cordic_hv": ("cordic_hyperbolic_vectoring", "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_hv.out"),
}
# arg discovery order -> file index. inputs: prime_cfg, (in,iv)x4, rin x4 = 13
# outputs: (out,out_cyc) x4 then rout x4 = 12.  out_X data is at 2*edge, stamps 2*edge+1
OUT_IDX = {"lft": 0, "rgt": 1, "top": 2, "btm": 3}
# iter_size = KERNEL ITERATIONS, not stream reps. mmm's 4-instr MAC kernel consumes one
# WORD per iteration (cf. load_mmm_router's cfg=(KLEN, B, 0), B = batch count), so it
# needs REPS*2; fft/cordic consume a whole rep per iteration. Getting this wrong makes
# the PC stop early and produce exactly half the outputs -- all correct, just too few.
ACT_PER_REP = {"mmm": 2}

WL = os.environ.get("WL", "mmm")
CHIP = os.environ.get("CHIP", "eva_v3_channel_ts")
PRJ = os.environ["PRJ"]
REPS = int(os.environ.get("REPS", "8"))
L = int(os.environ["LFORCE"])          # MUST equal the synthesized lane length
_PRIME = int(os.environ.get("PRIME", "1"))
subdir, in_edge, per_row, out_edge, out_sig, goldfile = CFG[WL]
GOLD, GOUT = f"{GB}/{subdir}", f"{LOG}/{goldfile}"
TBSV = f"{GOLD}/tb_pe_array_{subdir}.sv"

import importlib
chip = importlib.import_module(CHIP); sys.modules["eva"] = chip
import eva_workloads as wl
f16 = lambda h: np.uint16(h).view(np.float16)
zi = lambda *s: np.zeros(s, np.int32); zf = lambda *s: np.zeros(s, np.float16)


def nrev(g):
    op = (g >> 12) & 0xF; dst = (g >> 8) & 0xF; r1 = (g >> 4) & 0xF; r2 = g & 0xF
    if op in (0x3, 0xB):                 return op | (dst << 4) | (r2 << 8)
    if 0x4 <= op <= 0x7 or 0xC <= op <= 0xF: return op | (dst << 4) | (r2 << 8) | (r1 << 12)
    return op | (dst << 4) | (r1 << 8) | (r2 << 12)


M = N = 8; IRFD = 8
prog = zi(M, N, IRFD); prog[:] = chip.OP_MOV | (6 << 4) | (6 << 8)
drf, cfg0 = {}, {}
for f in sorted(glob.glob(f"{GOLD}/file_col_upp_*.mem")):
    j = int(re.search(r"_(\d+)\.mem", f).group(1))
    for line in open(f):
        m = re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)", line.strip())
        if not m: continue
        i, mode, addr, data = int(m[1],16), int(m[2],2), int(m[3],16), int(m[4],16)
        if   mode == 1 and 8 <= addr <= 15: prog[i, j, addr-8] = nrev(data)
        elif mode == 0:                     drf.setdefault(addr, zf(M,N))[i,j] = f16(data)
        elif mode == 1 and addr == 0:       cfg0[(i,j)] = (((data>>8)&7)+1, data & 0xFF)

chip.M, chip.N = M, N
chip.IRF_DEPTH, chip.DATADRIVEN = IRFD, 1
chip.NSTEP = chip.LANELEN = L
per_node = IRFD + len(drf) + 2
pc = M * per_node + M + 8
rin_s_pkts = wl.load_prog_packets(prog, M, N, data=[(a, drf[a]) for a in sorted(drf)],
                                  cfg=lambda i, j: (cfg0.get((i,j),(8,0))[0], int(os.environ.get('ITER', REPS * ACT_PER_REP.get(WL, 1))) & 0xFF,
                                                    cfg0.get((i,j),(8,0))[1]))
vals = [int(x,16) for x in re.findall(r"16'h([0-9A-Fa-f]+)",
        re.search(r"_inputs\s*=\s*\{(.*?)\};", open(TBSV).read(), re.S).group(1))]

ins = [zf(M,L), zf(M,L), zf(N,L), zf(N,L)]; ivs = [zi(M,L), zi(M,L), zi(N,L), zi(N,L)]
rins = [zi(M,L), zi(M,L), zi(N,L), zi(N,L)]
ie = OUT_IDX[in_edge]
words_of = (lambda k: 1 if k % 2 == 0 else 2) if WL.startswith("cordic") else (lambda k: per_row)
for b in range(REPS):
    for k in range(N):
        w = words_of(k)
        for t in range(w):
            c = pc + b * w + t
            if c < L:
                ins[ie][k, c] = f16(vals[per_row * k + t]); ivs[ie][k, c] = 1
rins[3] = rin_s_pkts
prime_cfg = np.full((M, N), _PRIME, np.int32)
print(f"=== REPLAY {WL} on existing RTL: L={L} pc={pc} REPS={REPS} PRIME={_PRIME} "
      f"drf={sorted(drf)} ===", flush=True)

# ---- write the 13 input files in discovery order ----
SYN = os.path.join(PRJ, "cosb")
order = [prime_cfg, ins[0], ivs[0], ins[1], ivs[1], ins[2], ivs[2], ins[3], ivs[3],
         rins[0], rins[1], rins[2], rins[3]]
for i, a in enumerate(order):
    with open(f"{SYN}/input{i}.data", "w") as fh:
        for v in np.asarray(a).reshape(-1):
            fh.write(f"{float(v):.9g}\n" if a.dtype == np.float16 else f"{int(v)}\n")
print(f"wrote {len(order)} input files -> {SYN}", flush=True)

# ---- re-run ONLY the RTL simulation against the already-synthesized design ----
mk = glob.glob(f"{SYN}/**/Verify_concat_sim_rtl_v_ncsim.mk", recursive=True)
assert mk, "no ncsim makefile -- was this project built with mode='cosim'?"
v1 = os.path.dirname(os.path.dirname(mk[0]))
for f in glob.glob(f"{SYN}/output*.data"):
    os.remove(f)
env = dict(os.environ, NC_ROOT=NC_ROOT, NCSim_NC_ROOT=NC_ROOT)
print("running ncsim ...", flush=True)
r = subprocess.run([f"{MGC}/bin/make", "-f", "./scverify/Verify_concat_sim_rtl_v_ncsim.mk",
                    f"NC_ROOT={NC_ROOT}", f"NCSim_NC_ROOT={NC_ROOT}", "SIMTOOL=ncsim", "sim"],
                   cwd=v1, capture_output=True, text=True, timeout=14400, env=env)
open(f"{PRJ}/replay_{WL}.log", "w").write((r.stdout or "") + (r.stderr or ""))
print(f"ncsim rc={r.returncode} (log: {PRJ}/replay_{WL}.log)", flush=True)

# ---- compare, tb-style: each produced output vs cyclic golden ----
gold = {}
for line in open(GOUT):
    m = re.search(rf"{out_sig}\[(\d)\] = ([0-9a-f]+)", line)
    if m: gold.setdefault(int(m[1]), []).append(int(m[2], 16))
oi = OUT_IDX[out_edge]
# Port layout depends on whether the chip has out_cyc_* TIMESTAMP ports:
#   TS  : (out, out_cyc) x4 interleaved -> data at 2*edge, stamps at 2*edge+1
#   noTS: out x4 then rout x4           -> data at edge, NO stamps
# Reading a non-TS build with the TS layout silently yields router arrays and reports
# ZERO outputs on every row -- a harness artifact that looks exactly like a dead design.
TS = "_ts" in CHIP or os.environ.get("TS", "0") == "1"
dat = np.loadtxt(f"{SYN}/output{2*oi if TS else oi}.data").reshape(-1, L)
stp = np.loadtxt(f"{SYN}/output{2*oi+1}.data").reshape(-1, L) if TS else None
print(f"    port layout: {'TS (data@%d, stamps@%d)' % (2*oi, 2*oi+1) if TS else 'no-TS (data@%d, no stamps)' % oi}")
rows_ok = tot_out = tot_mism = 0
spans = []
for k in range(N):
    g = gold.get(k, [])
    if not g: continue
    # with stamps, count what ACTUALLY arrived; without, fall back to the expected count
    n_out = int((stp[k] > 0).sum()) if TS else min(len(g) * REPS, L)
    mine = [int(np.float16(dat[k, t]).view(np.uint16)) for t in range(n_out)]
    mism = [i for i, v in enumerate(mine) if v != g[i % len(g)]]
    ok = len(mism) == 0 and n_out > 0
    rows_ok += ok; tot_out += n_out; tot_mism += len(mism)
    if TS and n_out > 1: spans.append((stp[k, n_out-1] - stp[k, 0]) / (n_out - 1))
    print(f"  row {k}: {'OK ' if ok else ' x '} out={n_out} "
          f"golden={[hex(v) for v in g[:2]]} got={[hex(v) for v in mine[:2]]}"
          + ("" if ok else f"  [{len(mism)} mism]"))
nrows = sum(1 for k in range(N) if gold.get(k))
print(f"=== {WL} COSIM-REPLAY: {rows_ok}/{nrows} rows clean | {tot_out} outputs, "
      f"{tot_mism} mismatches ===")
if spans: print(f"    throughput: {np.mean(spans):.2f} cyc/val")
sys.exit(0 if rows_ok == nrows and nrows > 0 else 1)
