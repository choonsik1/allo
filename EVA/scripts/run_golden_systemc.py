#!/usr/bin/env python3
# Replay a SHIPPED GOLDEN EVA pe_array workload on the Allo SystemC backend and diff
# bit-exact against the captured golden RTL outputs.
#
# Ported from final_eva_performance/scripts/ii2_cosim/build_golden_cosim.py (which
# emitted a C++ vector header for the Vitis harness). Here the vectors go straight
# into numpy and through mod(...), because the SystemC backend emits its own
# self-contained sc_main testbench.
#
#   program : EVA_untouched/.../<wl>/file_col_upp_*.mem   (per-column program+weights)
#   inputs  : the golden .sv testbench's `_inputs = {...}` block
#   golden  : /home/zsm9/eva_tb_logs/pe_array_<wl>.out    (captured golden RTL values)
#
# NOTE the golden .out files carry NO timestamps -- only values and their order. So
# correctness is diffed against golden EVA; THROUGHPUT is measured from our own
# out_cyc_* ports (TS chips) and compared to the Vitis cyc/val numbers instead.
#
#   WL=fft|mmm|cordic_cr|cordic_cv|cordic_hr|cordic_hv   MODE=csim|cosim
#   CHIP=<chip module>  MESH=8  LFORCE=800  PRIME=<n>  PRJ=<dir>
import os, sys, re, glob
import numpy as np

os.environ.setdefault("OMP_NUM_THREADS", "8")
os.environ.setdefault("MGC_HOME", "/opt/siemens/catapult/2024.2/Mgc_home")
MGC = os.environ["MGC_HOME"]
os.environ["PATH"] = f"{MGC}/bin:" + os.environ.get("PATH", "")
os.environ.setdefault("SYSTEMC_HOME", f"{MGC}/shared")
os.environ["LD_LIBRARY_PATH"] = (
    f"{MGC}/lib:{MGC}/shared/lib:" + os.environ.get("LD_LIBRARY_PATH", "")
)
os.environ.setdefault("ALLO_COSIM_SYNTH_TIMEOUT", "36000")   # 8x8 csyn ~6 h
os.environ.setdefault("ALLO_COSIM_SIM_TIMEOUT", "7200")

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, "/home/zsm9/allo_sup")
sys.path.insert(0, os.path.join(ROOT, "chip"))
import glob as _glob
for _p in sorted(sum([_glob.glob(os.path.join(ROOT, _d, "v[0-9]*"))
                      for _d in ("designs", "tools", "deadends")], [])):
    if os.path.isdir(_p):
        sys.path.append(_p)

GB = "/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array"   # golden programs + tb .sv
LOG = "/home/zsm9/eva_tb_logs"                             # captured golden RTL outputs

# (gold_subdir, in_edge, per_row, out_edge, out_sig, goldfile)
# edges: lft->in_w(0)/west, rgt->out_e(1)/east, top->out_n(2), btm->out_s(3)/south
CFG = {
 "mmm":       ("mmm",                         "lft", 2, "btm", "sys_tx_btm_data", "pe_array_mmm.out"),
 "fft":       ("fft",                         "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_fft.out"),
 "cordic_cr": ("cordic_circular_rotation",    "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_cr.out"),
 "cordic_cv": ("cordic_circular_vectoring",   "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_cv.out"),
 "cordic_hr": ("cordic_hyperbolic_rotation",  "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_hr.out"),
 "cordic_hv": ("cordic_hyperbolic_vectoring", "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_hv.out"),
}
IDX = {"lft": 0, "rgt": 1, "top": 2, "btm": 3}
# iter_size = KERNEL ITERATIONS, not stream reps. mmm's 4-instr MAC kernel consumes one
# WORD per iteration (cf. load_mmm_router's cfg=(KLEN, B, 0), B = batch count), so it
# needs REPS*2; fft/cordic consume a whole rep per iteration. Getting this wrong makes
# the PC stop early and produce exactly half the outputs -- all correct, just too few.
ACT_PER_REP = {"mmm": 2}

WL = os.environ.get("WL", "fft")
CHIP = os.environ.get("CHIP", "eva_v3_nocred_ts")
MODE = os.environ.get("MODE", "csim")
MESH = int(os.environ.get("MESH", "8"))
REPS = int(os.environ.get("REPS", "8"))       # STREAM_REPS: base block repeated back-to-back
MARGIN = int(os.environ.get("MARGIN", "300"))  # rtprime drain margin (>=160)
subdir, in_edge, per_row, out_edge, out_sig, goldfile = CFG[WL]
GOLD, GOUT = f"{GB}/{subdir}", f"{LOG}/{goldfile}"
TBSV = f"{GOLD}/tb_pe_array_{subdir}.sv"

import importlib
chip = importlib.import_module(CHIP)
sys.modules["eva"] = chip
import eva_workloads as wl
import allo.dataflow as df
from allo.ir.types import float16

TS = "_ts" in CHIP or os.environ.get("TS", "0") == "1"
# SCHED=1 applies the Allo schedule -> Catapult emits #pragma hls_pipeline_init_interval
# (one per node). PARTITION=0 is MANDATORY with it: partition_rf is a no-op on this
# backend (byte-identical output) but issues M*N*25 s.partition() calls -- 1600 at 8x8,
# which pushes emit from ~64 s to >1 h20m.
SCHED = os.environ.get("SCHED", "0") == "1"
PARTITION = os.environ.get("PARTITION", "0") == "1"
PRJ = os.environ.get("PRJ", os.path.join(ROOT, "generated"))
f16 = lambda h: np.uint16(h).view(np.float16)
zi = lambda *s: np.zeros(s, np.int32)
zf = lambda *s: np.zeros(s, np.float16)


def nrev(g):
    """Golden .mem encoding -> Allo's LSB-first instruction encoding."""
    op = (g >> 12) & 0xF; dst = (g >> 8) & 0xF; r1 = (g >> 4) & 0xF; r2 = g & 0xF
    if op in (0x3, 0xB):
        return op | (dst << 4) | (r2 << 8)
    if 0x4 <= op <= 0x7 or 0xC <= op <= 0xF:
        return op | (dst << 4) | (r2 << 8) | (r1 << 12)
    return op | (dst << 4) | (r1 << 8) | (r2 << 12)


# ---- 1. program + resident weights, straight out of the golden .mem files ----
M = N = MESH
IRFD = 8
prog = zi(M, N, IRFD); prog[:] = chip.OP_MOV | (6 << 4) | (6 << 8)   # NOP
drf, cfg0 = {}, {}
for f in sorted(glob.glob(f"{GOLD}/file_col_upp_*.mem")):
    j = int(re.search(r"_(\d+)\.mem", f).group(1))
    for line in open(f):
        m = re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), "
                     r"data = ([0-9A-Fa-f]+)", line.strip())
        if not m:
            continue
        i, mode, addr, data = int(m[1], 16), int(m[2], 2), int(m[3], 16), int(m[4], 16)
        if mode == 1 and 8 <= addr <= 15:
            prog[i, j, addr - 8] = nrev(data)
        elif mode == 0:
            drf.setdefault(addr, zf(M, N))[i, j] = f16(data)
        elif mode == 1 and addr == 0:
            cfg0[(i, j)] = (((data >> 8) & 7) + 1, data & 0xFF)


def cfg(i, j):
    klen, sync = cfg0.get((i, j), (8, 0))
    # iter_size = number of kernel iterations (load_mmm_router passes the batch count).
    # 0 was inherited from build_golden_cosim.py annotated "Inf" -- it is NOT: it caps
    # the stream. ITER=REPS makes each rep one kernel iteration.
    return (klen, int(os.environ.get("ITER", REPS * ACT_PER_REP.get(WL, 1))) & 0xFF, sync)


chip.M, chip.N = M, N
chip.IRF_DEPTH, chip.DATADRIVEN = IRFD, 1
per_node = IRFD + len(drf) + 2
pc = M * per_node + M + 8
# lanes must hold: program prefix + REPS copies of the base block + drain margin
L = int(os.environ.get("LFORCE", "0")) or (pc + REPS * max(2, int(os.environ.get("STRIDE", "0")) or per_row) + MARGIN)
chip.NSTEP = chip.LANELEN = L

# ⚠️ The formula above assumes ~1 CYCLE PER VALUE. Real throughput is 4 (mmm) to ~20
# (cordic) cyc/val, so the default MARGIN silently truncates the drain: outputs stop
# early and the tail reads back as 0x0, which the comparison reports as MISMATCHES.
# That looks exactly like a broken design -- it has already cost two false alarms on
# chips that were in fact RTL-verified. Warn loudly instead of failing silently.
_CPV = {"mmm": 4.0, "fft": 8.0}.get(WL, 20.0)          # measured in RTL; cordic is ~19.7
_need = int(pc + REPS * per_row * _CPV + 400)
if not int(os.environ.get("LFORCE", "0")) and L < _need:
    print(f"!! LANE MAY BE TOO SHORT: L={L} but {WL} at {_CPV:g} cyc/val needs ~{_need}.\n"
          f"!! Expect correct values then a 0x0 tail counted as mismatches.\n"
          f"!! Fix: LFORCE={_need} (NOT a bigger MARGIN -- cosim replays must reuse L).",
          flush=True)
rin_s_pkts = wl.load_prog_packets(prog, M, N,
                                  data=[(a, drf[a]) for a in sorted(drf)], cfg=cfg)

# ---- 2. stimulus: the golden .sv testbench's own input vector ----
blk = re.search(r"_inputs\s*=\s*\{(.*?)\};", open(TBSV).read(), re.S).group(1)
vals = [int(x, 16) for x in re.findall(r"16'h([0-9A-Fa-f]+)", blk)]

_PRIME = int(os.environ.get("PRIME", "1"))   # Channel chips cannot absorb PRIME>2
print(f"=== GOLDEN REPLAY  WL={WL}  CHIP={CHIP}  {M}x{N}  L={L}  pc={pc}  "
      f"in={in_edge} out={out_edge}  PRIME={_PRIME}  REPS={REPS}  SCHED={int(SCHED)}  drf={sorted(drf)}  "
      f"#inputs={len(vals)} ===", flush=True)

ins = [zf(M, L), zf(M, L), zf(N, L), zf(N, L)]
ivs = [zi(M, L), zi(M, L), zi(N, L), zi(N, L)]
outs = [zf(M, L), zf(M, L), zf(N, L), zf(N, L)]
rins = [zi(M, L), zi(M, L), zi(N, L), zi(N, L)]
routs = [zi(M, L), zi(M, L), zi(N, L), zi(N, L)]
ie = IDX[in_edge]
# Lane asymmetry, per the _stream.sv tbs: cordic even lanes carry only the x operand
# (1 word/op), odd lanes carry z then y (2 words/op); stream_inputs[2*j+1] on an even
# lane is a DUMMY placeholder and must not be driven. fft/mmm are 2 words on every row.
words_of = (lambda k: 1 if k % 2 == 0 else 2) if WL.startswith("cordic") else (lambda k: per_row)
# STRIDE = cycles between successive reps. Default per_row = back-to-back, i.e. one
# word per row per cycle -- the LINK SATURATION rate, so measured cyc/val cannot
# exceed 1 by construction. Raise STRIDE to inject slower and see whether the
# reported throughput tracks the injection rate (it does) rather than the hardware.
# each lane streams independently, back-to-back at its own word count (the tb forks
# one driver per lane); STRIDE overrides that spacing if set.
_ST = int(os.environ.get("STRIDE", "0"))
for b in range(REPS):
    for k in range(N):
        w = words_of(k)
        step = _ST or w
        for t in range(w):
            ins[ie][k, pc + b * step + t] = f16(vals[per_row * k + t])
            ivs[ie][k, pc + b * step + t] = 1
rins[3] = rin_s_pkts
prime_cfg = np.full((M, N), _PRIME, np.int32)

# ---- 3. the golden RTL values we must reproduce ----
gold = {}
for line in open(GOUT):
    m = re.search(rf"{out_sig}\[(\d)\] = ([0-9a-f]+)", line)
    if m:
        gold.setdefault(int(m[1]), []).append(int(m[2], 16))
oi = IDX[out_edge]
print(f"  golden rows: " + ", ".join(f"{k}:{len(gold.get(k,[]))}" for k in range(N)),
      flush=True)

# ---- 4. build + run ----
os.system(f"rm -rf {PRJ}")
build_mode = "csim" if MODE == "csim" else MODE
if SCHED:
    _sched = chip.get_scheduled_eva(float16, pipeline_node=True, partition_rf=PARTITION)
    mod = _sched.build(target="systemc", mode=build_mode, project=PRJ)
else:
    mod = df.build(chip.get_eva_top(float16), target="systemc",
                   mode=build_mode, project=PRJ)
print(f"emitted -> {PRJ}; running {MODE} ...", flush=True)

if TS:
    ocs = [zi(M, L), zi(M, L), zi(N, L), zi(N, L)]
    mod(prime_cfg, ins[0], ivs[0], ins[1], ivs[1], ins[2], ivs[2], ins[3], ivs[3],
        outs[0], ocs[0], outs[1], ocs[1], outs[2], ocs[2], outs[3], ocs[3],
        *rins, *routs)
else:
    mod(prime_cfg, ins[0], ivs[0], ins[1], ivs[1], ins[2], ivs[2], ins[3], ivs[3],
        *outs, *rins, *routs)

# ---- 5. bit-exact diff against golden, row by row ----
got = outs[oi]
st_all = ocs[oi] if TS else None
rows_ok, tot_out, tot_mism = 0, 0, 0
for k in range(N):
    g = gold.get(k, [])
    if not g:
        continue
    # The .sv tb checks each output THAT ARRIVES against golden[out_count % ng] and
    # reports out_count separately -- it never demands REPS*ng outputs. Count what the
    # collector actually produced: it compacts from 0 and stamps t (>0, production
    # starts long after pc). Without TS, fall back to the expected count.
    n_out = min(int((st_all[k] > 0).sum()) if TS else len(g) * REPS, L)
    mine = [int(np.asarray(got[k, t], np.float16).view(np.uint16)) for t in range(n_out)]
    mism = [i for i, v in enumerate(mine) if v != g[i % len(g)]]   # CYCLIC compare
    ok = len(mism) == 0 and n_out > 0
    rows_ok += ok; tot_out += n_out; tot_mism += len(mism)
    mark = "OK " if ok else " x "
    extra = "" if ok else (f"  [{len(mism)} mism, first #{mism[0]}: got={hex(mine[mism[0]])} "
                           f"want={hex(g[mism[0] % len(g)])}]" if mism else "  [no output]")
    print(f"  row {k}: {mark} out={n_out}/{len(g)*REPS} golden={[hex(v) for v in g[:3]]} "
          f"got={[hex(v) for v in mine[:3]]}{extra}")
nrows = sum(1 for k in range(N) if gold.get(k))
print(f"=== {WL} {MODE}: {rows_ok}/{nrows} rows clean | {tot_out} outputs, "
      f"{tot_mism} mismatches (cyclic vs golden EVA) ===")

if TS and tot_out > 0:   # only meaningful if every value was produced;
    st = ocs[oi]                            # a truncated stream leaves tail stamps at 0
    spans = []
    for k in range(N):
        n = int((st[k] > 0).sum())           # ALL values actually produced on this row
        if n > 1:
            spans.append((int(st[k, n - 1]) - int(st[k, 0])) / (n - 1))
    if spans:
        print(f"    throughput: {np.mean(spans):.2f} cyc/val "
              f"(per-row span mean over {len(spans)} rows)")

elif TS:
    print("    throughput: n/a (stream truncated -- timestamps invalid)")
sys.exit(0 if rows_ok == nrows and nrows > 0 else 1)
