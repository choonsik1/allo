# Scoreboard-vs-baseline failure bisection (sim only). Two minimal programs:
#   A: RAW chain, no preload:  MOV r1<-hold_w ; MOV TX_E<-r1        (klen=2)
#   B: preload + RAW:  r0:=2.0 (mode=0 pkt); MOV r1<-hold_w ;
#      MULT r2<-r0*r1 ; MOV TX_E<-r2                                 (klen=3)
# Usage:  python debug_sb.py eva_sb | eva_prime
import os, sys
import numpy as np
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(1, HERE + "/eva_prime_baseline")
sys.path.insert(2, "/home/zsm9/pe_core_implementation/Allo/EVA/tests")
sys.path.insert(3, "/home/zsm9/pe_core_implementation/Allo/EVA")
chip = sys.argv[1] if len(sys.argv) > 1 else "eva_sb"
e = __import__(chip)
sys.modules["eva"] = e
import allo.dataflow as df
from allo.ir.types import float16
import eva_tests as T
import eva_workloads as wl

def run_case(name, prog_instrs, data, expect_fn, K=4):
    M = N = 1
    pc, L = T._dims(M, N, margin=200)
    pc += 8 * len(data)                       # margin for preload packets
    prog = T.zi(M, N, e.IRF_DEPTH); prog[:] = T._NOP
    for k, ins in enumerate(prog_instrs):
        prog[0, 0, k] = ins
    rin_s = wl.load_prog_packets(prog, M, N, data=data,
                                 cfg=(len(prog_instrs), K, 0))
    mod = df.build(e.get_eva_top(float16), target="simulator")
    ins_, outs, rins, routs = T.io_bufs(M, N, L)
    ramp = np.arange(1, K + 1, dtype=np.float16)
    ivw = T.zi(M, L)
    SPACING = int(sys.argv[2]) if len(sys.argv) > 2 else 8
    for t in range(K):
        ins_[0][0, pc + t * SPACING] = ramp[t]; ivw[0, pc + t * SPACING] = 1
    rins[3] = rin_s
    e.run_eva(mod, ins_, [ivw, T.zi(M, L), T.zi(N, L), T.zi(N, L)],
              outs, rins, routs)
    got = outs[1][0, :K].astype(np.float32)
    exp = expect_fn(ramp).astype(np.float32)
    ok = np.array_equal(got, exp)
    print(f"  {name}: got={got} exp={exp}  {'PASS' if ok else 'FAIL'}")
    return ok

print(f"== chip: {chip} ==")
I_MOV_R1_W  = 0x3 | (1 << 4) | (0xE << 8)     # MOV r1 <- hold_w   (0xE13)
I_MOV_TXE_1 = 0x3 | (0xF << 4) | (1 << 8)     # MOV TX_E <- r1     (0x1F3)
I_MULT_R2   = 0x2 | (2 << 4) | (0 << 8) | (1 << 12)  # MULT r2 <- r0*r1
I_MOV_TXE_2 = 0x3 | (0xF << 4) | (2 << 8)     # MOV TX_E <- r2
run_case("A raw-chain   ", [I_MOV_R1_W, I_MOV_TXE_1], [],
         lambda r: r)
run_case("B preload+RAW ", [I_MOV_R1_W, I_MULT_R2, I_MOV_TXE_2],
         [(0, np.full((1, 1), 2.0, np.float16))],
         lambda r: r * np.float16(2.0))
