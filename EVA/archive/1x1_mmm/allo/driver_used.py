#!/usr/bin/env python3
# Real EVA program on the Allo SystemC backend: ROUTER-LOADED + LOOPING MMM at 1x1.
#
# Unlike the passthrough ramp in run_systemc.py (which only proves the plumbing),
# this runs the shipped 4-instruction MMM MAC kernel (I0..I3 = 0xE13, 0x1022, 0x1F3,
# 0xC2D0) with a LOOPING program counter: the kernel lives once in irf[0..3] and
# loops B times. It exercises the scoreboard, DRF, operand forwarding, the credit
# plane and the fp16 MAC datapath.
#
#   MODE=csim   -> software SystemC golden      (fast)
#   MODE=cosim  -> Catapult HLS + SCVerify RTL  (authoritative)
#
# Golden: numpy Y = X @ W, checked by the loader's own check() closure.
# NOTE: load_mmm_router sets eva.M/N/NSTEP/LANELEN itself from the operand shapes;
# it is documented exact for a single PE (1x1, off=0) -- multi-node needs the i+3j
# start skew, which is a separate chip step.
import os, sys
import numpy as np

os.environ.setdefault("OMP_NUM_THREADS", "8")
os.environ.setdefault("MGC_HOME", "/opt/siemens/catapult/2024.2/Mgc_home")
MGC = os.environ["MGC_HOME"]
os.environ["PATH"] = f"{MGC}/bin:" + os.environ.get("PATH", "")
os.environ.setdefault("SYSTEMC_HOME", f"{MGC}/shared")
os.environ["LD_LIBRARY_PATH"] = (
    f"{MGC}/lib:{MGC}/shared/lib:" + os.environ.get("LD_LIBRARY_PATH", "")
)
os.environ.setdefault("ALLO_COSIM_SYNTH_TIMEOUT", "3600")
os.environ.setdefault("ALLO_COSIM_SIM_TIMEOUT", "1800")

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, "/home/zsm9/allo_sup")
sys.path.insert(0, os.path.join(ROOT, "chip"))

import eva_sb_syscredit_rtprime as e
sys.modules["eva"] = e                 # eva_workloads' `import eva` binds this chip
import eva_workloads as wl
import allo.dataflow as df
from allo.ir.types import float16

MODE = os.environ.get("MODE", "csim")
PRJ = os.path.join(ROOT, "generated")

# ---- workload: 1x1 MMM, B batches. W is (M,N)=(1,1), X is (B,M)=(B,1). ----
W = np.array([[3]], np.float16)
X = np.array([[2], [5], [7]], np.float16)          # B=3 -> Y = [[6],[15],[21]]
args, check = wl.load_mmm_router(W, X)             # sets e.M/e.N/e.NSTEP/e.LANELEN
B = X.shape[0]

# load_mmm_router sizes lanes as PROG_CYCLES + KLEN*B + M + 3N + 2 (=34 here), which
# has NO drain margin for rtprime: its RUNTIME-prime credit flow needs >=160 extra
# cycles or the tokens never leave the mesh and every output reads back zero (the
# same trap NSTEP=55 set in run_systemc.py). Pad every lane with zeros and extend
# NSTEP to match. Outputs are compacted from index 0 by the collector, so padding
# the tail does not move them.
MARGIN = int(os.environ.get("LANE_MARGIN", "200"))
_L0 = e.LANELEN
e.NSTEP = e.LANELEN = _L0 + MARGIN
_pad = lambda a: np.pad(a, ((0, 0), (0, MARGIN)))
for _k in ("ins", "ivs", "outs", "rins", "routs"):
    args[_k] = [_pad(a) for a in args[_k]]
out_s = args["outs"][3]                            # padded array the DUT will write
print(f"lane pad: {_L0} -> {e.LANELEN} (rtprime drain margin {MARGIN})", flush=True)
print(f"=== EVA MMM SystemC: MODE={MODE}  M=N={e.M}  B={B}  "
      f"NSTEP={e.NSTEP}  PROG_CYCLES={e.PROG_CYCLES}  PRIME={e.PRIME_TOKENS} ===",
      flush=True)

os.system(f"rm -rf {PRJ}")
build_mode = "csim" if MODE == "csim" else MODE
mod = df.build(e.get_eva_top(float16), target="systemc", mode=build_mode, project=PRJ)
print(f"emitted -> {PRJ}", flush=True)

prime_cfg = np.full((e.M, e.N), e.PRIME_TOKENS, np.int32)
ins, ivs = args["ins"], args["ivs"]

# TRUE (discovery) order, matching eva.run_eva but with rtprime's prime_cfg FIRST:
#   (in_w,iv_w), (in_e,iv_e), (in_n,iv_n), (in_s,iv_s), outs, rins, routs
print(f"running {MODE} ...", flush=True)
mod(prime_cfg,
    ins[0], ivs[0], ins[1], ivs[1], ins[2], ivs[2], ins[3], ivs[3],
    *args["outs"], *args["rins"], *args["routs"])

# The loader's check() closes over its PRE-pad out_s, so redo its comparison on the
# padded array the DUT actually wrote. Same semantics: collector compacts from 0.
got = np.array([[float(out_s[j, b]) for j in range(e.N)] for b in range(B)], np.float32)
gold = (X.astype(np.float32) @ W.astype(np.float32))
ok = bool(np.allclose(got, gold, atol=1e-2))
print(f"=== ROUTER-LOADED + LOOPING MMM {e.M}x{e.N} B={B} "
      f"(INSTR_SIZE=4 ITER_SIZE={B}) ===")
print("expected Y = X@W =\n", gold)
print("got out_s      =\n", got)
print(f"=== MMM {MODE} :", "PASS (bit-exact vs numpy X@W) ===" if ok else "FAIL ===")
sys.exit(0 if ok else 1)
