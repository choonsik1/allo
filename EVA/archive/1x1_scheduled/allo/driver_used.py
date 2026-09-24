#!/usr/bin/env python3
# Unified driver: EVA chip (eva_sb_syscredit_rtprime) on the Allo SystemC backend.
#
#   MODE=codegen  -> emit SystemC, print stats (no tool)          [Python only]
#   MODE=csim     -> emit + compile + run functional MatchLib csim [g++/libsystemc]
#   MODE=csyn     -> emit + Catapult HLS to RTL                    [Catapult]
#   MODE=cosim    -> emit + Catapult HLS + SCVerify RTL cosim      [Catapult + ncsim]
#
# Knobs (env):
#   MODE   (default codegen)
#   MESH   (default 1)      M=N mesh dimension
#   NSTEP  (default pc+200) run length. MUST leave drain margin -- see below.
#   SCHED  (default 0)      1 = apply the Allo schedule (pipeline_node + partition_rf),
#                           which emits Catapult #pragma hls_pipeline_init_interval /
#                           hls_unroll. 0 = unscheduled; Catapult schedules it itself.
#
# Run with the allo env python:
#   MODE=csyn /home/zsm9/miniconda3/envs/allo/bin/python scripts/run_systemc.py
#
# NOTE on NSTEP: rtprime's runtime-prime credit flow needs a generous drain margin
# (>=160) or the tokens never leave the mesh and every output is all-zero. The old
# default of 55 produced a csim that "passed" (rc=0) while computing nothing -- the
# emitted testbench has NO self-check, so a clean exit is not a pass. csim/cosim
# below therefore drive a real workload and assert against a numpy golden.
import os, sys

os.environ.setdefault("OMP_NUM_THREADS", "8")
os.environ.setdefault("MGC_HOME", "/opt/siemens/catapult/2024.2/Mgc_home")
MGC = os.environ["MGC_HOME"]
os.environ["PATH"] = f"{MGC}/bin:" + os.environ.get("PATH", "")

# Catapult bundles SystemC 2.3.3 under $MGC_HOME/shared (include/ + lib/). hls.py's
# cosim path requires SYSTEMC_HOME and does not infer it from MGC_HOME.
os.environ.setdefault("SYSTEMC_HOME", f"{MGC}/shared")
# hls.py runs the software golden as a bare `./sim`; Catapult's libsystemc needs
# GLIBCXX_3.4.26 from Catapult's own libstdc++ (absent from this box's /lib64).
# csim.sh sets this itself, the cosim path does not.
os.environ["LD_LIBRARY_PATH"] = (
    f"{MGC}/lib:{MGC}/shared/lib:" + os.environ.get("LD_LIBRARY_PATH", "")
)
# Catapult synthesis of the full 1x1 chip takes ~7 min; the 900s default is tight.
os.environ.setdefault("ALLO_COSIM_SYNTH_TIMEOUT", "3600")
os.environ.setdefault("ALLO_COSIM_SIM_TIMEOUT", "1800")

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, "/home/zsm9/allo_sup")          # the allo checkout
sys.path.insert(0, os.path.join(ROOT, "chip"))     # local chip source

import numpy as np
import eva_sb_syscredit_rtprime as e

MESH = int(os.environ.get("MESH", "1"))
e.M = e.N = MESH
sys.modules["eva"] = e            # eva_workloads' `import eva` binds this chip
import eva_workloads as wl

import allo.dataflow as df
from allo.ir.types import float16

MODE = os.environ.get("MODE", "codegen")
SCHED = os.environ.get("SCHED", "0") == "1"

# ---- run length: default leaves rtprime's credit drain margin ----
e.IRF_DEPTH, e.DATADRIVEN = 8, 1
K = 6                                             # ramp length (workload below)
pc = e.M * (e.IRF_DEPTH + 2) + e.M + 4            # cycle the program is delivered
e.NSTEP = int(os.environ.get("NSTEP", str(pc + 200)))
e.LANELEN = e.NSTEP
L = e.LANELEN
if MODE in ("csim", "cosim") and e.NSTEP < pc + 160:
    print(f"WARNING: NSTEP={e.NSTEP} < {pc + 160}; tokens may not drain "
          "-> all-zero outputs (this is NOT a pass).", flush=True)

PRJ = os.path.join(ROOT, "generated")
print(f"=== EVA SystemC: MODE={MODE}  M=N={e.M}  NSTEP={L}  SCHED={int(SCHED)} ===",
      flush=True)


def _top():
    """Unscheduled region, or the Allo schedule (emits Catapult loop pragmas)."""
    if SCHED:
        return e.get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)
    return e.get_eva_top(float16)


def _build(**kw):
    top = _top()
    # get_scheduled_eva returns a Schedule (build is a method); the plain region
    # goes through df.build.
    return top.build(**kw) if SCHED else df.build(top, **kw)


if MODE == "codegen":
    mod = _build(target="systemc")
    code = mod.hls_code
    outp = os.path.join(PRJ, "kernel_codegen.cpp")
    os.makedirs(PRJ, exist_ok=True)
    open(outp, "w").write(code)
    print(f"OK -> {outp}: {code.count(chr(10))+1} lines")
    for kw in ["SC_MODULE", "SC_THREAD", "Connections", "std::memcpy", "half ",
               "hls_pipeline_init_interval", "hls_unroll"]:
        print(f"    {kw:28s}: {code.count(kw)}")
    sys.exit(0)

os.system(f"rm -rf {PRJ}")
build_mode = "csim" if MODE == "csim" else MODE
mod = _build(target="systemc", mode=build_mode, project=PRJ)
print(f"emitted -> {PRJ}", flush=True)

if MODE == "csyn":
    # csyn is data-independent: no argument binding needed.
    print("running Catapult (csyn) ...", flush=True)
    mod()
    print(f"=== csyn DONE -> {PRJ} (see {PRJ}/build/catapult.log) ===")
    sys.exit(0)

# ---- csim / cosim: drive a real workload and check against a numpy golden ----
# 1x1 systolic passthrough: one PE runs MOV west-rx -> east-tx, looped K times.
# A K-long ramp enters WEST and must exit EAST unchanged; the collector compacts
# valid tokens from index 0, so out_e[0, 0:K] == ramp.
zi = lambda *s: np.zeros(s, np.int32)
z = lambda *s: np.zeros(s, np.float16)
M, N = e.M, e.N
_NOP = e.OP_MOV | (6 << 4) | (6 << 8)
INSTR = e.OP_MOV | (0xF << 4) | (0xE << 8)        # MOV west-rx -> east-tx

prog = zi(M, N, e.IRF_DEPTH)
prog[:] = _NOP
prog[0, 0, 0] = INSTR
rin_s_pkts = wl.load_prog_packets(prog, M, N, cfg=(1, K, 0))

in_w, in_e, in_n, in_s = z(M, L), z(M, L), z(N, L), z(N, L)
out_w, out_e, out_n, out_s = z(M, L), z(M, L), z(N, L), z(N, L)
iv_w, iv_e, iv_n, iv_s = zi(M, L), zi(M, L), zi(N, L), zi(N, L)
rin_w, rin_e, rin_n, rin_s = zi(M, L), zi(M, L), zi(N, L), zi(N, L)
rout_w, rout_e, rout_n, rout_s = zi(M, L), zi(M, L), zi(N, L), zi(N, L)
prime_cfg = np.full((M, N), e.PRIME_TOKENS, np.int32)   # runtime prime per tile

ramp = np.arange(1, K + 1, dtype=np.float16)
for t in range(K):
    in_w[0, pc + t] = ramp[t]
    iv_w[0, pc + t] = 1
rin_s[:] = rin_s_pkts

print(f"running {MODE} (K={K} ramp, pc={pc}) ...", flush=True)
# arg order: prime_cfg FIRST (the `node` kernel is discovered first), then the
# systolic args, then the router packet args.
mod(prime_cfg,
    in_w, iv_w, in_e, iv_e, in_n, iv_n, in_s, iv_s,
    out_w, out_e, out_n, out_s,
    rin_w, rin_e, rin_n, rin_s,
    rout_w, rout_e, rout_n, rout_s)

got = out_e[0, :K]
ok = np.array_equal(got, ramp)
print("EXPECT ramp   :", ramp.astype(np.float32).tolist())
print("EVA    out_e  :", got.astype(np.float32).tolist())
print(f"=== {MODE} RESULT :", "PASS (bit-exact) ===" if ok else "MISMATCH ===")
sys.exit(0 if ok else 1)
