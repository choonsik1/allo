#!/usr/bin/env python3
# Minimal csyn probe: does a chip variant SYNTHESIZE at all?
#
# Purpose is the error list, not the area. v13/v15 mix blocking put() and try_put() on
# the same systolic channel (node prime loop + pre-loop emission + in-loop try_put),
# which has previously produced CIN-150 "Multiple writers". 1x1 answers that in minutes;
# the mesh size does not change whether the error fires.
#
# NOTE: csyn takes mod() with NO arguments (allo/backend/hls.py asserts this) -- the
# run_*_systemc.py drivers pass arrays and trip the assert before Catapult ever runs.
#
#   CHIP=eva_v15 MESH=1 PRJ=/scratch/... python scripts/csyn_probe.py
import os, sys, glob, importlib
import numpy as np

os.environ.setdefault("OMP_NUM_THREADS", "8")
os.environ.setdefault("MGC_HOME", "/opt/siemens/catapult/2024.2/Mgc_home")
MGC = os.environ["MGC_HOME"]
os.environ["PATH"] = f"{MGC}/bin:" + os.environ.get("PATH", "")
os.environ.setdefault("SYSTEMC_HOME", f"{MGC}/shared")
os.environ["LD_LIBRARY_PATH"] = f"{MGC}/lib:{MGC}/shared/lib:" + os.environ.get("LD_LIBRARY_PATH", "")
os.environ.setdefault("ALLO_COSIM_SYNTH_TIMEOUT", "36000")

HERE = os.path.dirname(os.path.abspath(__file__)); ROOT = os.path.dirname(HERE)
sys.path.insert(0, "/home/zsm9/allo_sup"); sys.path.insert(0, os.path.join(ROOT, "chip"))
for p in sorted(sum([glob.glob(os.path.join(ROOT, _d, "v[0-9]*"))
                      for _d in ("designs", "tools", "deadends")], [])):
    if os.path.isdir(p):
        sys.path.append(p)
sys.path.append(os.path.join(ROOT, "designs", "from_verification"))

CHIP = os.environ.get("CHIP", "eva_v15")
MESH = int(os.environ.get("MESH", "1"))
NSTEP = int(os.environ.get("NSTEP", "215"))
PRJ = os.environ["PRJ"]
# CLK: clock period in ns. Catapult BAKES THE PERIOD INTO THE SCHEDULE (how many ops it
# packs per cycle), so this is not a pure constraint -- it is the timing/area knob.
# Use it to sweep the frequency FLOOR: v16 closes 2.0 ns at 8x8 with only +0.0013 ns of
# slack, so 500 MHz is a lower bound, not the answer.
CLK = float(os.environ.get("CLK", "2.0"))

e = importlib.import_module(CHIP); sys.modules["eva"] = e
import allo.dataflow as df
from allo.ir.types import float16, int16
# DTYPE selects the datatype-generic chips' element type (int16 variants exist
# in designs/from_verification but were never synthesized).
_TY = {'fp16': float16, 'int16': int16}[os.environ.get('DTYPE', 'fp16')]

e.M = e.N = MESH
e.NSTEP = e.LANELEN = NSTEP
if hasattr(e, "RUN_BUDGET"):          # elastic: fixed trip count = max(RUN_BUDGET, 6*LANELEN)
    e.RUN_BUDGET = int(os.environ.get("BUDGET", str(6 * NSTEP)))
print(f"=== CSYN PROBE  CHIP={CHIP}  {MESH}x{MESH}  NSTEP={NSTEP}  CLK={CLK} ns  DTYPE={os.environ.get('DTYPE','fp16')} ===", flush=True)
os.system(f"rm -rf {PRJ}")
# The verification chips expose get_eva_top_elastic(); ours expose get_eva_top().
_top = (e.get_eva_top_elastic(_TY) if hasattr(e, "get_eva_top_elastic")
        else e.get_eva_top(_TY))
# SCHED replicates the chip's OWN Allo schedule (the verification chips apply this in
# their __main__ for the Vitis flow; our Catapult builds normally skip it):
#   0 = none (default)
#   1 = s.pipeline the NODE loop only, at PIPE_II (default 1)
#   2 = 1 + s.partition on the 23 per-node buffers (elastic __main__, full)
#   3 = 2 + pipeline the 16 driver/collector loops (breaks scheduling -- see below)
# PIPE_II picks the initiation interval. MEASURED on fp16_elastic 1 PE @2.0 ns:
#   unsched 23 cyc/iter, AREA 54,526.7, 2.0831 ns (MISSES 2.0)
#   II=2 -> 64,475 (+18%) and a 5.011 ns path;  II=4 -> 51,636 (-5.3%), 1.9980 ns  <-- BEST
#   II=8 -> 51,521, 1.9984;  II=16 -> 51,341, 1.9827;  II=1 UNSCHEDULABLE (SCHD-30)
# II=4 beats unscheduled on ALL THREE axes (5.75x throughput, less area, meets timing).
# SCHED>=3 also pipelines the IO loops -> a collector partition then fails SCHD-30.
_SCHED = int(os.environ.get("SCHED", "0"))
_RBUF2 = int(os.environ.get("RBUF2", "0"))
# RBUF2 must be usable WITHOUT pipelining -- the unscheduled schedule is today's
# baseline, so partition-only is the comparison that isolates the rbuf effect.
if _SCHED or _RBUF2:
    _IT = "it" if hasattr(e, "get_eva_top_elastic") else "t"   # elastic names its loop `it`
    _s = df.customize(_top)
    for _i in range(MESH):
        for _j in range(MESH):
            if not _SCHED: continue
            _s.pipeline(f"node_{_i}_{_j}:{_IT}",
                        initiation_interval=int(os.environ.get("PIPE_II", "1")))
            if _SCHED >= 2:
                for _b in ("irf drf drf_full hold_v hold_cnt ig_p ig_v oh_p oh_v txp_d txp_v "
                           "resq cmpq sb_v sb_dst sb_cmp sb_rtr sb_inj sb_dir sb_id sb_rvld "
                           "sb_ix sb_long").split():
                    _s.partition(f"node_{_i}_{_j}:{_b}")
    if _SCHED >= 3:          # node-only is the useful config; IO loops break scheduling
        for _io in ("drv_w drv_e drv_n drv_s col_w col_e col_n col_s rdrv_w rdrv_e rdrv_n "
                    "rdrv_s rclc_w rclc_e rclc_n rclc_s").split():
            _s.pipeline(f"{_io}_0:{_IT}",
                        initiation_interval=int(os.environ.get("PIPE_II", "1")))
    # RBUF2: the Allo equivalent of verification/helpers/skid_inject_full_rbuf2.py.
    # That helper adds `rbuf` to the `array_partition complete dim=2` clause -- but it
    # injects a VITIS pragma into the Vitis kernel.cpp AFTER emission, and Catapult
    # ignores HLS pragmas (our emitted kernel.cpp has zero array_partition lines).
    # So the transfer to this flow has to go through s.partition(), not the injector.
    # rbuf is `Pkt[4, BUF_DEPTH]`, so dim=2 splits the BUF_DEPTH axis, matching the helper.
    if _RBUF2:
        from allo.customize import Partition
        for _i in range(MESH):
            for _j in range(MESH):
                _s.partition(f"node_{_i}_{_j}:rbuf", Partition.Complete, dim=2)
        print(f"RBUF2: s.partition(rbuf, Complete, dim=2) on {MESH*MESH} node(s)", flush=True)
    _cfg = {"clock_period": CLK}
    # NODE_ONLY=1 -> synthesize just the PE (DESIGN_HIERARCHY = the node module) instead
    # of the whole region. The region top also contains the 16 driver/collector kernels
    # and the FIFOs, so whole-region area is NOT per-PE area (backend note: a router
    # measured 5,806 of 22,260 um2 = 26 % harness). ⚠ csyn/area ONLY -- the backend
    # states cosim does not work against a submodule top (SCVerify wraps the design top
    # and the input<k>.data stimulus path disappears).
    if int(os.environ.get("NODE_ONLY", "0")):
        _cfg["synth_top"] = os.environ.get("SYNTH_TOP", "node_0_0")
        print(f"NODE_ONLY: DESIGN_HIERARCHY -> {_cfg['synth_top']}", flush=True)
    mod = _s.build(target="systemc", mode="csyn", project=PRJ, configs=_cfg)
else:
    _cfg = {"clock_period": CLK}
    if int(os.environ.get("NODE_ONLY", "0")):
        _cfg["synth_top"] = os.environ.get("SYNTH_TOP", "node_0_0")
        print(f"NODE_ONLY: DESIGN_HIERARCHY -> {_cfg['synth_top']}", flush=True)
    mod = df.build(_top, target="systemc", mode="csyn", project=PRJ, configs=_cfg)
# --- EXTRA_TCL: directives Catapult exposes ONLY via TCL, with no source-pragma form.
# The one that matters here is PIPELINE_STALL_MODE. Without it the pipelined node loop
# schedules but Catapult inserts a full stall network: MEASURED at 1 PE elastic II=4,
#   without -> area 57,060, throughput 64      with -> area 51,636.5, throughput 4
# Applied after `go assembly`, then `go architect` re-runs scheduling with it in effect.
# NOTE: this patches THIS project's run.tcl only. cosim regenerates its own run.tcl under
# cosb/, so a cosim needs the directive in the BACKEND, not here.
_extra = os.environ.get("EXTRA_TCL", "")
if _extra:
    _tcl = os.path.join(PRJ, "run.tcl")
    _s = open(_tcl).read()
    _ins = "go assembly\n" + "".join(l + "\n" for l in _extra.split(";") if l.strip()) + "go architect\n"
    assert "go assembly\n" in _s, "run.tcl has no `go assembly` anchor"
    open(_tcl, "w").write(_s.replace("go assembly\n", _ins, 1))
    print(f"EXTRA_TCL injected -> {_tcl}:\n  " + "\n  ".join(_extra.split(";")), flush=True)

print(f"emitted -> {PRJ}; running Catapult ...", flush=True)
mod()                      # csyn: NO arguments
print("=== CSYN RETURNED (no exception) ===")
