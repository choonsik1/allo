"""Smoke test for the SPLIT EVA (router + simplified single-cycle pe) on the
Allo JIT *simulator* (exercises the deterministic non-blocking try_get/try_put
local interface). Same passthrough workload as the systemc cosim:
one node loops MOV west->east K times; a K-ramp in WEST must exit EAST unchanged.
"""
import os, sys, importlib.util, numpy as np
os.environ.setdefault("OMP_NUM_THREADS", "8")

EVA_DIR = "examples/systemc/eva_example"
sys.path.insert(0, EVA_DIR)                       # eva_workloads.py

# import the split chip module by path
spec = importlib.util.spec_from_file_location(
    "eva_pe_router_split", "agents/eva_pe_router_split.py")
e = importlib.util.module_from_spec(spec)
sys.modules["eva_pe_router_split"] = e
spec.loader.exec_module(e)
sys.modules["eva"] = e                             # eva_workloads' `import eva`

e.M, e.N = 1, 1
import eva_workloads as wl
import allo.dataflow as df
from allo.ir.types import float16

zi = lambda *s: np.zeros(s, np.int32)
z  = lambda *s: np.zeros(s, np.float16)
_NOP = e.OP_MOV | (6 << 4) | (6 << 8)

M, N, K = 1, 1, 6
e.IRF_DEPTH, e.DATADRIVEN = 8, 1
pc = M * (e.IRF_DEPTH + 2) + M + 4
e.NSTEP = pc + 200
e.LANELEN = e.NSTEP
L = e.LANELEN
print(f"config: M=N=1  K={K}  pc={pc}  NSTEP={L}  PRIME_TOKENS={e.PRIME_TOKENS}")

INSTR = e.OP_MOV | (0xF << 4) | (0xE << 8)         # MOV west-rx -> east-tx
prog = zi(M, N, e.IRF_DEPTH); prog[:] = _NOP; prog[0, 0, 0] = INSTR
rin_s_pkts = wl.load_prog_packets(prog, M, N, cfg=(1, K, 0))

print("=== building split EVA on target=simulator ===")
mod = df.build(e.get_eva_top(float16), target="simulator")
print("=== built; driving workload ===")

in_w, in_e, in_n, in_s = z(M, L), z(M, L), z(N, L), z(N, L)
out_w, out_e, out_n, out_s = z(M, L), z(M, L), z(N, L), z(N, L)
iv_w, iv_e, iv_n, iv_s = zi(M, L), zi(M, L), zi(N, L), zi(N, L)
rin_w, rin_e, rin_n, rin_s = zi(M, L), zi(M, L), zi(N, L), zi(N, L)
rout_w, rout_e, rout_n, rout_s = zi(M, L), zi(M, L), zi(N, L), zi(N, L)
prime_cfg = np.full((M, N), e.PRIME_TOKENS, np.int32)

ramp = np.arange(1, K + 1, dtype=np.float16)
for t in range(K):
    in_w[0, pc + t] = ramp[t]; iv_w[0, pc + t] = 1
rin_s[:] = rin_s_pkts

mod(prime_cfg,
    in_w, iv_w, in_e, iv_e, in_n, iv_n, in_s, iv_s,
    out_w, out_e, out_n, out_s,
    rin_w, rin_e, rin_n, rin_s,
    rout_w, rout_e, rout_n, rout_s)

got = out_e[0, :K]
print("EXPECT ramp   :", ramp.astype(np.float32).tolist())
print("SIM out_e     :", got.astype(np.float32).tolist())
print("RESULT        :", "PASS (bit-exact)" if np.array_equal(got, ramp) else "MISMATCH")
