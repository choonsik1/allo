#!/usr/bin/env python3
# Deadlock instrumentation for the credit-free systolic variants.
#
# v12 exposes two extra outputs per node:
#   dbg_t[i,j] = last loop iteration that node reached
#   dbg_s[i,j] = packed flow-control snapshot at that iteration
#                bits0-7 hold_cnt[0..3] (2b each), bits8-11 txp_v[0..3]
# On deadlock the node loop stops advancing, so these hold the STALL CYCLE and the
# state AT the stall -- which is enough to read off the wait-for graph.
#
# The emitted testbench spins `for (_c=0; _c<630000 && !done; ++_c) sc_start(...)`,
# which never terminates under deadlock, so the arrays would never be written back.
# We patch that cap down between build and run.
import os, sys, re, glob
import numpy as np

os.environ.setdefault("OMP_NUM_THREADS", "8")
os.environ.setdefault("MGC_HOME", "/opt/siemens/catapult/2024.2/Mgc_home")
MGC = os.environ["MGC_HOME"]
os.environ["PATH"] = f"{MGC}/bin:" + os.environ.get("PATH", "")
os.environ.setdefault("SYSTEMC_HOME", f"{MGC}/shared")
os.environ["LD_LIBRARY_PATH"] = f"{MGC}/lib:{MGC}/shared/lib:" + os.environ.get("LD_LIBRARY_PATH", "")

HERE = os.path.dirname(os.path.abspath(__file__)); ROOT = os.path.dirname(HERE)
sys.path.insert(0, "/home/zsm9/allo_sup"); sys.path.insert(0, os.path.join(ROOT, "chip"))
for _p in sorted(sum([glob.glob(os.path.join(ROOT, _d, "v[0-9]*"))
                      for _d in ("designs", "tools", "deadends")], [])):
    if os.path.isdir(_p):
        sys.path.append(_p)

CHIP = os.environ.get("CHIP", "eva_v12")
MESH = int(os.environ.get("MESH", "8"))
REPS = int(os.environ.get("REPS", "2"))
CAP  = int(os.environ.get("CAP", "4000"))       # tb cycle cap after patching
PRJ  = os.environ["PRJ"]

import importlib
chip = importlib.import_module(CHIP); sys.modules["eva"] = chip
import eva_workloads as wl
import allo.dataflow as df
from allo.ir.types import float16
f16 = lambda h: np.uint16(h).view(np.float16)
zi = lambda *s: np.zeros(s, np.int32); zf = lambda *s: np.zeros(s, np.float16)

GB = "/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array/fft"
def nrev(g):
    op=(g>>12)&0xF; dst=(g>>8)&0xF; r1=(g>>4)&0xF; r2=g&0xF
    if op in (0x3,0xB): return op|(dst<<4)|(r2<<8)
    if 0x4<=op<=0x7 or 0xC<=op<=0xF: return op|(dst<<4)|(r2<<8)|(r1<<12)
    return op|(dst<<4)|(r1<<8)|(r2<<12)

M = N = MESH; IRFD = 8
prog = zi(M,N,IRFD); prog[:] = chip.OP_MOV|(6<<4)|(6<<8)
drf, cfg0 = {}, {}
for f in sorted(glob.glob(f"{GB}/file_col_upp_*.mem")):
    j = int(re.search(r"_(\d+)\.mem", f).group(1))
    for line in open(f):
        m = re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)", line.strip())
        if not m: continue
        i,mode,addr,data = int(m[1],16),int(m[2],2),int(m[3],16),int(m[4],16)
        if   mode==1 and 8<=addr<=15: prog[i,j,addr-8] = nrev(data)
        elif mode==0:                 drf.setdefault(addr, zf(M,N))[i,j] = f16(data)
        elif mode==1 and addr==0:     cfg0[(i,j)] = (((data>>8)&7)+1, data&0xFF)

chip.M, chip.N = M, N
chip.IRF_DEPTH, chip.DATADRIVEN = IRFD, 1
per_node = IRFD + len(drf) + 2
pc = M*per_node + M + 8
L = pc + REPS*2 + 300
chip.NSTEP = chip.LANELEN = L
rin_s = wl.load_prog_packets(prog, M, N, data=[(a, drf[a]) for a in sorted(drf)],
        cfg=lambda i,j: (cfg0.get((i,j),(8,0))[0], REPS & 0xFF, cfg0.get((i,j),(8,0))[1]))
vals = [int(x,16) for x in re.findall(r"16'h([0-9A-Fa-f]+)",
        re.search(r"_inputs\s*=\s*\{(.*?)\};", open(f"{GB}/tb_pe_array_fft.sv").read(), re.S).group(1))]

ins=[zf(M,L),zf(M,L),zf(N,L),zf(N,L)]; ivs=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
outs=[zf(M,L),zf(M,L),zf(N,L),zf(N,L)]
rins=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]; routs=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
for b in range(REPS):
    for k in range(N):
        for t in range(2):
            ins[0][k, pc+b*2+t] = f16(vals[2*k+t]); ivs[0][k, pc+b*2+t] = 1
rins[3] = rin_s
prime_cfg = np.full((M,N), int(os.environ.get("PRIME","1")), np.int32)
dbg_t = zi(M,N); dbg_s = zi(M,N)

print(f"=== DEADLOCK PROBE  CHIP={CHIP} {M}x{N} REPS={REPS} L={L} CAP={CAP} ===", flush=True)
os.system(f"rm -rf {PRJ}")
mod = df.build(chip.get_eva_top(float16), target="systemc", mode="csim", project=PRJ)

# shrink the tb spin cap so a DEADLOCKED run still terminates and writes outputs back
kp = os.path.join(PRJ, "kernel.cpp"); src = open(kp).read()
src2, n = re.subn(r'_c < \d+LL', f'_c < {CAP}LL', src)
open(kp, "w").write(src2)
print(f"patched tb cycle cap -> {CAP} ({n} site)", flush=True)

mod(prime_cfg, dbg_t, dbg_s,
    ins[0], ivs[0], ins[1], ivs[1], ins[2], ivs[2], ins[3], ivs[3],
    *outs, *rins, *routs)

print(f"\n=== per-node LAST ITERATION reached (NSTEP={L}) ===")
for i in range(M):
    print("  " + " ".join(f"{int(dbg_t[i,j]):4d}" for j in range(N)))
stalled = dbg_t < (L - 1)
print(f"\n  nodes that did NOT finish: {int(stalled.sum())}/{M*N}"
      f"   min={int(dbg_t.min())} max={int(dbg_t.max())}")

print("\n=== state at stall: hold_cnt[N,S,W,E] | txp_v[N,S,W,E] ===")
for i in range(M):
    row = []
    for j in range(N):
        v = int(dbg_s[i,j])
        h = [(v >> (2*d)) & 3 for d in range(4)]
        p = [(v >> (8+d)) & 1 for d in range(4)]
        row.append("".join(map(str,h)) + "/" + "".join(map(str,p)))
    print("  " + " ".join(row))
print("\n  hold_cnt==2 means that direction's hold is FULL (refusing input);")
print("  txp_v==1 means a word is stuck pending on that TX direction.")
