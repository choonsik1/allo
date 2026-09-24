"""RTL cosim (SCVerify) of the EVA rtprime chip on the Allo SystemC backend.

Same workload + numpy golden as scripts/cosim_eva_systemc.py, but mode="cosim"
so Catapult synthesizes to RTL and SCVerify runs the RTL against the same
testbench vectors. NSTEP follows the reference script's drain margin (pc+200),
NOT run_systemc.py's NSTEP=55 (too short -> tokens never drain -> all zeros).
"""
import os, sys, numpy as np

os.environ.setdefault("OMP_NUM_THREADS", "8")
os.environ.setdefault("MGC_HOME", "/opt/siemens/catapult/2024.2/Mgc_home")
os.environ["PATH"] = f"{os.environ['MGC_HOME']}/bin:" + os.environ.get("PATH", "")
# hls.py cosim requires SYSTEMC_HOME (run_systemc.py never sets it). Point it at a
# shim mirroring what csim.sh links against: Catapult's bundled SystemC 2.3.3
# headers + the gcc-10.3.0-64 build (matches Catapult's g++ 10.3.0 on PATH).
os.environ.setdefault(
    "SYSTEMC_HOME",
    "/tmp/claude-1838657/-home-zsm9-final-eva-systemc/"
    "9cec8437-a27a-47c2-a31b-141c9605081d/scratchpad/sc_home",
)
os.environ.setdefault("ALLO_CXX_EXTRA", "-DSC_INCLUDE_DYNAMIC_PROCESSES")
# hls.py runs the golden `./sim` bare, but Catapult's libsystemc needs GLIBCXX_3.4.26
# from Catapult's own libstdc++ (absent from this box's /lib64). csim.sh sets this;
# the cosim path does not -> "version GLIBCXX_3.4.26 not found".
_MGC = os.environ["MGC_HOME"]
os.environ["LD_LIBRARY_PATH"] = (
    f"{_MGC}/lib:{os.environ['SYSTEMC_HOME']}/lib:"
    + os.environ.get("LD_LIBRARY_PATH", "")
)
os.environ.setdefault("ALLO_COSIM_SYNTH_TIMEOUT", "3600")  # NSTEP=215 >> the 900s default

ROOT = "/home/zsm9/final_eva_systemc"
sys.path.insert(0, "/home/zsm9/allo_sup")
sys.path.insert(0, os.path.join(ROOT, "chip"))

import eva_sb_syscredit_rtprime as e

e.M, e.N = 1, 1
sys.modules["eva"] = e  # eva_workloads' `import eva` binds this chip
import eva_workloads as wl
import allo.dataflow as df
from allo.ir.types import float16

zi = lambda *s: np.zeros(s, np.int32)
z = lambda *s: np.zeros(s, np.float16)
_NOP = e.OP_MOV | (6 << 4) | (6 << 8)

M, N, K = 1, 1, 6
e.IRF_DEPTH, e.DATADRIVEN = 8, 1
pc = M * (e.IRF_DEPTH + 2) + M + 4
e.NSTEP = pc + 200
e.LANELEN = e.NSTEP
L = e.LANELEN
print(f"config: M=N=1 K={K} pc={pc} NSTEP={L} PRIME_TOKENS={e.PRIME_TOKENS}", flush=True)

INSTR = e.OP_MOV | (0xF << 4) | (0xE << 8)  # MOV west-rx -> east-tx
prog = zi(M, N, e.IRF_DEPTH)
prog[:] = _NOP
prog[0, 0, 0] = INSTR
rin_s_pkts = wl.load_prog_packets(prog, M, N, cfg=(1, K, 0))

PRJ = os.path.join(ROOT, "generated")
os.system(f"rm -rf {PRJ}")
mod = df.build(e.get_eva_top(float16), target="systemc", mode="cosim", project=PRJ)
print("=== built EVA systemc (cosim mode); driving workload ===", flush=True)

in_w, in_e, in_n, in_s = z(M, L), z(M, L), z(N, L), z(N, L)
out_w, out_e, out_n, out_s = z(M, L), z(M, L), z(N, L), z(N, L)
iv_w, iv_e, iv_n, iv_s = zi(M, L), zi(M, L), zi(N, L), zi(N, L)
rin_w, rin_e, rin_n, rin_s = zi(M, L), zi(M, L), zi(N, L), zi(N, L)
rout_w, rout_e, rout_n, rout_s = zi(M, L), zi(M, L), zi(N, L), zi(N, L)
prime_cfg = np.full((M, N), e.PRIME_TOKENS, np.int32)

ramp = np.arange(1, K + 1, dtype=np.float16)
for t in range(K):
    in_w[0, pc + t] = ramp[t]
    iv_w[0, pc + t] = 1
rin_s[:] = rin_s_pkts

mod(prime_cfg,
    in_w, iv_w, in_e, iv_e, in_n, iv_n, in_s, iv_s,
    out_w, out_e, out_n, out_s,
    rin_w, rin_e, rin_n, rin_s,
    rout_w, rout_e, rout_n, rout_s)

got = out_e[0, :K]
print("EXPECT ramp   :", ramp.astype(np.float32).tolist())
print("SYSTEMC out_e :", got.astype(np.float32).tolist())
print("RESULT        :", "PASS (bit-exact)" if np.array_equal(got, ramp) else "MISMATCH")
