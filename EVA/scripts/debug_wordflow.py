#!/usr/bin/env python3
# Word-flow probe for v14_dbg: why does v13 emit exactly HALF the cordic outputs?
#
# Every value v13 produces is bit-exact, and it stops with the lane window and the
# iteration budget both far from exhausted. Two candidates remain:
#   (a) half the words never reach the nodes  -> n_rx will be ~half the injected count
#   (b) the words arrive and two are eaten per output -> n_rx full, n_cn ~2x n_gr
# The counters separate these directly.
#
#   WL=cordic_cr CHIP=eva_v14 MESH=8 REPS=8 PRJ=/scratch/... python scripts/debug_wordflow.py
import os, sys, re, glob, importlib
import numpy as np

os.environ.setdefault("OMP_NUM_THREADS", "8")
os.environ.setdefault("MGC_HOME", "/opt/siemens/catapult/2024.2/Mgc_home")
MGC = os.environ["MGC_HOME"]
os.environ["PATH"] = f"{MGC}/bin:" + os.environ.get("PATH", "")
os.environ.setdefault("SYSTEMC_HOME", f"{MGC}/shared")
os.environ["LD_LIBRARY_PATH"] = f"{MGC}/lib:{MGC}/shared/lib:" + os.environ.get("LD_LIBRARY_PATH", "")

HERE = os.path.dirname(os.path.abspath(__file__)); ROOT = os.path.dirname(HERE)
sys.path.insert(0, "/home/zsm9/allo_sup"); sys.path.insert(0, os.path.join(ROOT, "chip"))
for p in sorted(sum([glob.glob(os.path.join(ROOT, _d, "v[0-9]*"))
                      for _d in ("designs", "tools", "deadends")], [])):
    if os.path.isdir(p):
        sys.path.append(p)

GB = "/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array"
CFG = {
 "mmm":       ("mmm",                      "lft", 2, "btm"),
 "fft":       ("fft",                      "lft", 2, "rgt"),
 "cordic_cr": ("cordic_circular_rotation", "lft", 2, "rgt"),
}
EDGE = {"lft": 0, "rgt": 1, "top": 2, "btm": 3}
ACT_PER_REP = {"mmm": 2}

WL = os.environ.get("WL", "cordic_cr")
CHIP = os.environ.get("CHIP", "eva_v14")
MESH = int(os.environ.get("MESH", "8"))
REPS = int(os.environ.get("REPS", "8"))
MARGIN = int(os.environ.get("MARGIN", "800"))
PRJ = os.environ["PRJ"]
subdir, in_edge, per_row, out_edge = CFG[WL]
GOLD = f"{GB}/{subdir}"

chip = importlib.import_module(CHIP); sys.modules["eva"] = chip
import eva_workloads as wl
import allo.dataflow as df
from allo.ir.types import float16
f16 = lambda h: np.uint16(h).view(np.float16)
zi = lambda *s: np.zeros(s, np.int32); zf = lambda *s: np.zeros(s, np.float16)


def nrev(g):
    op = (g >> 12) & 0xF; dst = (g >> 8) & 0xF; r1 = (g >> 4) & 0xF; r2 = g & 0xF
    if op in (0x3, 0xB):                     return op | (dst << 4) | (r2 << 8)
    if 0x4 <= op <= 0x7 or 0xC <= op <= 0xF: return op | (dst << 4) | (r2 << 8) | (r1 << 12)
    return op | (dst << 4) | (r1 << 8) | (r2 << 12)


M = N = MESH; IRFD = 8
prog = zi(M, N, IRFD); prog[:] = chip.OP_MOV | (6 << 4) | (6 << 8)
drf, cfg0 = {}, {}
for f in sorted(glob.glob(f"{GOLD}/file_col_upp_*.mem")):
    j = int(re.search(r"_(\d+)\.mem", f).group(1))
    for line in open(f):
        m = re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)", line.strip())
        if not m: continue
        i, mode, addr, data = int(m[1], 16), int(m[2], 2), int(m[3], 16), int(m[4], 16)
        if   mode == 1 and 8 <= addr <= 15: prog[i, j, addr - 8] = nrev(data)
        elif mode == 0:                     drf.setdefault(addr, zf(M, N))[i, j] = f16(data)
        elif mode == 1 and addr == 0:       cfg0[(i, j)] = (((data >> 8) & 7) + 1, data & 0xFF)

chip.M, chip.N = M, N
chip.IRF_DEPTH, chip.DATADRIVEN = IRFD, 1
per_node = IRFD + len(drf) + 2
pc = M * per_node + M + 8
L = pc + REPS * per_row + MARGIN
chip.NSTEP = chip.LANELEN = L

ITER = int(os.environ.get("ITER", REPS * ACT_PER_REP.get(WL, 1)))
rin_s = wl.load_prog_packets(prog, M, N, data=[(a, drf[a]) for a in sorted(drf)],
                             cfg=lambda i, j: (cfg0.get((i, j), (8, 0))[0], ITER & 0xFF,
                                               cfg0.get((i, j), (8, 0))[1]))
vals = [int(x, 16) for x in re.findall(r"16'h([0-9A-Fa-f]+)",
        re.search(r"_inputs\s*=\s*\{(.*?)\};",
                  open(f"{GOLD}/tb_pe_array_{subdir}.sv").read(), re.S).group(1))]

ins = [zf(M, L), zf(M, L), zf(N, L), zf(N, L)]; ivs = [zi(M, L), zi(M, L), zi(N, L), zi(N, L)]
outs = [zf(M, L), zf(M, L), zf(N, L), zf(N, L)]
rins = [zi(M, L), zi(M, L), zi(N, L), zi(N, L)]; routs = [zi(M, L), zi(M, L), zi(N, L), zi(N, L)]
ie = EDGE[in_edge]
# cordic lane asymmetry: even lanes carry 1 real word per rep, odd lanes 2
words_of = (lambda k: 1 if k % 2 == 0 else 2) if WL.startswith("cordic") else (lambda k: per_row)
injected = zi(M)
for b in range(REPS):
    for k in range(N):
        w = words_of(k)
        for t in range(w):
            c = pc + b * w + t
            if c < L:
                ins[ie][k, c] = f16(vals[per_row * k + t]); ivs[ie][k, c] = 1
                injected[k] += 1
rins[3] = rin_s
prime_cfg = np.full((M, N), int(os.environ.get("PRIME", "1")), np.int32)
dbg_a = zi(M, N); dbg_b = zi(M, N)

print(f"=== WORD-FLOW PROBE  WL={WL} CHIP={CHIP} {M}x{N} REPS={REPS} ITER={ITER} "
      f"L={L} pc={pc} ===", flush=True)
print(f"  words injected per row: {list(injected)}", flush=True)
os.system(f"rm -rf {PRJ}")
mod = df.build(chip.get_eva_top(float16), target="systemc", mode="csim", project=PRJ)
# node-kernel args lead the discovery order (cf. debug_deadlock.py)
mod(prime_cfg, dbg_a, dbg_b,
    ins[0], ivs[0], ins[1], ivs[1], ins[2], ivs[2], ins[3], ivs[3],
    *outs, *rins, *routs)

lo = lambda v: int(v) & 0xFFFF
hi = lambda v: (int(v) >> 16) & 0xFFFF
n_rx = np.vectorize(lo)(dbg_a); n_cn = np.vectorize(hi)(dbg_a)
n_gr = np.vectorize(lo)(dbg_b); n_tx = np.vectorize(hi)(dbg_b)

for name, arr in (("WORDS RECEIVED into hold", n_rx), ("OPERANDS CONSUMED", n_cn),
                  ("REAL WORDS TRANSMITTED", n_tx)):
    print(f"\n=== {name} ===")
    for i in range(M):
        print("  " + " ".join(f"{int(arr[i, j]):5d}" for j in range(N)))

ic = EDGE[in_edge]
print(f"\n=== INPUT-EDGE COLUMN (the nodes fed directly by drv_{in_edge}) ===")
col = 0 if in_edge == "lft" else N - 1
print(f"  row : injected -> received  consumed  transmitted")
for r in range(M):
    print(f"  {r:3d} : {int(injected[r]):8d} -> {int(n_rx[r, col]):8d}  "
          f"{int(n_cn[r, col]):8d}  {int(n_tx[r, col]):11d}")
short = [r for r in range(M) if int(n_rx[r, col]) < int(injected[r])]
print(f"\n  rows whose edge node received FEWER words than were injected: {short}")
print("  -> nonempty  => words are LOST before/at the node (flow-control gap)")
print("  -> empty     => words all arrive; look at CONSUMED vs TRANSMITTED instead")
