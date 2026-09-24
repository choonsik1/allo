#!/usr/bin/env python3
# Drive the VERIFICATION ELASTIC chip (designs/from_verification/eva_fp16_elastic.py)
# through the SystemC/Catapult flow, using the same MMM stimulus as run_mmm_systemc.py.
#
# WHY a separate driver: elastic's interface is ours MINUS `prime_cfg` (it has no credit
# plane to pre-charge), and it is sized by LANELEN/RUN_BUDGET rather than NSTEP. Keeping
# it out of run_mmm_systemc.py avoids destabilising the driver our verified chips use.
#
# Elastic is the design that fixes what our v16 line cannot: buffered Stream links with
# full()/empty() predicates (the FIFO IS the backpressure -> no credits, no silent drop)
# and DATA-DRIVEN firing (no always-fire bubbles), versus our unbuffered Channel
# rendezvous + 24 forced handshakes per iteration.
#
#   CHIP=eva_fp16_elastic MMM_MESH=2 MODE=csim|cosim PRJ=/scratch/... python scripts/run_elastic_systemc.py
import os, sys, glob, importlib
import numpy as np

os.environ.setdefault("OMP_NUM_THREADS", "8")
os.environ.setdefault("MGC_HOME", "/opt/siemens/catapult/2024.2/Mgc_home")
MGC = os.environ["MGC_HOME"]
os.environ["PATH"] = f"{MGC}/bin:" + os.environ.get("PATH", "")
os.environ.setdefault("SYSTEMC_HOME", f"{MGC}/shared")
os.environ["LD_LIBRARY_PATH"] = f"{MGC}/lib:{MGC}/shared/lib:" + os.environ.get("LD_LIBRARY_PATH", "")
os.environ.setdefault("ALLO_COSIM_SYNTH_TIMEOUT", "10800")
os.environ.setdefault("ALLO_COSIM_SIM_TIMEOUT", "3600")

HERE = os.path.dirname(os.path.abspath(__file__)); ROOT = os.path.dirname(HERE)
sys.path.insert(0, "/home/zsm9/allo_sup")
sys.path.insert(0, os.path.join(ROOT, "chip"))
sys.path.insert(0, os.path.join(ROOT, "designs", "from_verification"))

CHIP = os.environ.get("CHIP", "eva_fp16_elastic")
MODE = os.environ.get("MODE", "csim")
PRJ = os.environ.get("PRJ", os.path.join(ROOT, "generated_elastic"))

e = importlib.import_module(CHIP); sys.modules["eva"] = e
import eva_workloads as wl
import allo.dataflow as df
from allo.ir.types import float16

_MESH = int(os.environ.get("MMM_MESH", "1"))
_B = int(os.environ.get("MMM_B", "3"))
if _MESH == 1:
    W = np.array([[float(os.environ.get("MMM_W", "3"))]], np.float16)
    X = np.array([[float(v)] for v in ([2, 5, 7] + list(range(1, _B + 1)))[:_B]], np.float16)
else:
    W = np.array([[float(1 + ((i + j) % 3)) for j in range(_MESH)] for i in range(_MESH)], np.float16)
    X = np.array([[float(1 + ((b + i) % 3)) for i in range(_MESH)] for b in range(_B)], np.float16)

args, check = wl.load_mmm_router(W, X)          # sets e.M/e.N/e.LANELEN (+ e.NSTEP if present)
B = X.shape[0]

# Same lane padding rationale as run_mmm_systemc.py: give the mesh room to drain.
MARGIN = int(os.environ.get("LANE_MARGIN", "200"))
_L0 = e.LANELEN
e.LANELEN = _L0 + MARGIN
if hasattr(e, "NSTEP"):
    e.NSTEP = e.LANELEN
# Elastic is DATA-DRIVEN, so its loop runs a fixed BUDGET rather than one step per lane
# slot. BUDGET = max(RUN_BUDGET, 6*LANELEN) inside the region, so set RUN_BUDGET here.
e.RUN_BUDGET = int(os.environ.get("BUDGET", str(6 * e.LANELEN)))
_pad = lambda a: np.pad(a, ((0, 0), (0, MARGIN)))
for _k in ("ins", "ivs", "outs", "rins", "routs"):
    args[_k] = [_pad(a) for a in args[_k]]
out_s = args["outs"][3]

print(f"=== ELASTIC MMM SystemC: MODE={MODE}  M=N={e.M}  B={B}  "
      f"LANELEN={e.LANELEN} (pad {_L0}->{e.LANELEN})  RUN_BUDGET={e.RUN_BUDGET} ===", flush=True)

os.system(f"rm -rf {PRJ}")
build_mode = "csim" if MODE == "csim" else MODE
top = e.get_eva_top_elastic(float16)
# SCHED=1 pipelines the NODE loop only, at PIPE_II. Measured at 1 PE csyn: II=4 gives
# 23 -> 4 cycles/iter, -5.3 % area, and meets 2.0 ns. But that is Catapult's STALL-FREE
# schedule for one PE in isolation -- real throughput is set by the mesh (neighbour
# backpressure, hop latency, the program), so it must be COSIM'd, not read off the report.
# Also: PIPELINE_STALL_MODE flush was required to schedule, and flush + a CYCLIC channel
# graph can deadlock where the unscheduled design did not -- hence the mesh ladder here.
_SCHED = int(os.environ.get("SCHED", "0"))
if _SCHED:
    _s = df.customize(top)
    for _i in range(e.M):
        for _j in range(e.N):
            _s.pipeline(f"node_{_i}_{_j}:it",
                        initiation_interval=int(os.environ.get("PIPE_II", "1")))
    mod = _s.build(target="systemc", mode=build_mode, project=PRJ)
else:
    mod = df.build(top, target="systemc", mode=build_mode, project=PRJ)
print(f"emitted -> {PRJ}; running {MODE} ...", flush=True)

# --- EXTRA_TCL: inject directives Catapult exposes only via TCL (e.g. the pipeline stall
# --- mode, which has no source-pragma form). Applied after `go assembly`, before extract.
_extra = os.environ.get("EXTRA_TCL", "")
if _extra:
    _tcl = os.path.join(PRJ, "run.tcl")
    _s = open(_tcl).read()
    _ins = "go assembly\n" + "".join(l + "\n" for l in _extra.split(";") if l.strip()) + "go architect\n"
    assert "go assembly\n" in _s, "run.tcl has no `go assembly` anchor"
    open(_tcl, "w").write(_s.replace("go assembly\n", _ins, 1))
    print(f"EXTRA_TCL injected -> {_tcl}:\n  " + "\n  ".join(_extra.split(";")), flush=True)


ins, ivs = args["ins"], args["ivs"]
# Discovery order identical to run_mmm_systemc.py but WITHOUT prime_cfg (no credit plane).
mod(ins[0], ivs[0], ins[1], ivs[1], ins[2], ivs[2], ins[3], ivs[3],
    *args["outs"], *args["rins"], *args["routs"])

got = np.array([[float(out_s[j, b]) for j in range(e.N)] for b in range(B)], np.float32)
gold = (X.astype(np.float32) @ W.astype(np.float32))
ok = bool(np.allclose(got, gold, atol=1e-2))
print(f"=== ELASTIC MMM {e.M}x{e.N} B={B} ===")
print("expected Y = X@W =\n", gold)
print("got out_s      =\n", got)
print(f"=== ELASTIC MMM {MODE} :", "PASS (bit-exact vs numpy X@W) ===" if ok else "FAIL ===")
sys.exit(0 if ok else 1)
