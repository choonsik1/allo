import os, sys
os.environ.setdefault("OMP_NUM_THREADS", "256")
HERE = os.path.dirname(os.path.abspath(__file__))   # this verification/ folder
FR   = os.path.dirname(HERE)                         # parent (Allo/EVA) — the chip .py files live here
sys.path.insert(0, FR); sys.path.insert(0, HERE)     # chips from parent; eva_workloads.py from HERE
import numpy as np, allo.dataflow as df
from allo.ir.types import float16
import eva_sb_syscredit as e
sys.modules["eva"] = e                      # eva_workloads/eva_tests import `eva`
import eva_workloads as wl
zi = lambda *s: np.zeros(s, dtype=np.int32)
z  = lambda *s: np.zeros(s, dtype=np.float16)
_NOP = e.OP_MOV | (6 << 4) | (6 << 8)

def _dims(M, N, margin=40):
    e.M, e.N = M, N; e.IRF_DEPTH = 8; e.DATADRIVEN = 1
    pc = M*(e.IRF_DEPTH+2) + M + 4; e.NSTEP = pc + margin; e.LANELEN = e.NSTEP
    return pc, e.LANELEN

def run_one(INSTR, a_val, b_val=None):
    M, N = 1, 1
    pc, L = _dims(M, N)
    prog = zi(M, N, e.IRF_DEPTH); prog[:] = _NOP; prog[0,0,0] = INSTR
    rin_s = wl.load_prog_packets(prog, M, N, cfg=(1, 1, 0))     # klen=1, iterate once
    mod = df.build(e.get_eva_top_extended(float16), target='simulator')
    ins  = [z(M,L), z(M,L), z(N,L), z(N,L)]     # in_w,in_e,in_n,in_s
    outs = [z(M,L), z(M,L), z(N,L), z(N,L)]
    rins = [zi(M,L), zi(M,L), zi(N,L), zi(N,L)]
    routs= [zi(M,L), zi(M,L), zi(N,L), zi(N,L)]
    ivw, ivn = zi(M,L), zi(N,L)
    ins[0][0, pc] = np.float16(a_val); ivw[0, pc] = 1           # operand a on WEST (addr 0xE)
    if b_val is not None:
        ins[2][0, pc] = np.float16(b_val); ivn[0, pc] = 1       # operand b on NORTH (addr 0xC)
    rins[3] = rin_s
    e.run_eva(mod, ins, [ivw, zi(M,L), ivn, zi(N,L)], outs, rins, routs)
    return float(outs[1][0, 0])                                 # east collector, first token

# DIV: dst=east-tx(0xF), s1=west-rx(0xE)=a, s2=north-rx(0xC)=b  ->  a/b
DIV  = e.OP_DIV  | (0xF<<4) | (0xE<<8) | (0xC<<12)
# SQRT: dst=east-tx(0xF), s1=west-rx(0xE)=a  ->  sqrt(a)
SQRT = e.OP_SQRT | (0xF<<4) | (0xE<<8)

r_div  = run_one(DIV,  6.0, 2.0)
r_sqrt = run_one(SQRT, 9.0)
print(f"DIV  6.0/2.0 -> {r_div}   expect 3.0   {'PASS' if abs(r_div-3.0)<1e-2 else 'FAIL'}")
print(f"SQRT sqrt(9.0) -> {r_sqrt}   expect 3.0   {'PASS' if abs(r_sqrt-3.0)<1e-2 else 'FAIL'}")

print("--- extra vectors ---")
for (op,name,a,b) in [(DIV,"DIV",7.0,4.0),(DIV,"DIV",1.0,8.0),(SQRT,"SQRT",2.0,None),(SQRT,"SQRT",16.0,None)]:
    got = run_one(op, a, b)
    exp = float(np.float16(a)/np.float16(b)) if name=="DIV" else float(np.sqrt(np.float16(a)))
    exp = float(np.float16(exp))
    print(f"{name} a={a} b={b} -> {got:.5f}  expect ~{exp:.5f}  {'PASS' if abs(got-exp)<abs(exp)*0.02+1e-3 else 'FAIL'}")
