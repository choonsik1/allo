"""
cycle_calibration.py -- how close is the simulator's cost model to real HLS?

Runs the EXACT design that was pushed through Vitis csynth and compares
`sim.get_cycles()` against the cycles Vitis reported.  This is the only
ground-truth anchor the cost model has.

Result: 7 modelled vs 6 reported per PE (1.2x), down from ~2.7x before the
per-op latency table landed.

READ THE CAVEAT BEFORE QUOTING THAT NUMBER.  It is ONE data point on two
trivial integer PEs.  Float, BRAM and pipelined-loop latencies are entirely
uncalibrated.  Say "cycle-approximate, 1.2x at one point", never a flat
"cycle-accurate".

The makespan ratio (0.4x) is expected to be off: Vitis charges the top-level
wrapper for load_buf/store_res, which the simulator does not clock at all.
That shifts every design by roughly a constant, so it does not change DSE
*rankings* -- which is why it was deliberately not chased.

Related finding (see ../claude_simulator.md): non-blocking designs csynth to
`undef` latency, so there is no static schedule to ingest for exactly the
designs this work targets.  Blocking designs report fine.

Usage:
    python simulator_profiling/cycle_calibration.py

Needs LLVM_BUILD_DIR set (the `allo` conda env sets it; do not override).
"""
import sys
sys.path.insert(0, "/home/zsm9/allo_sup")
import numpy as np
import allo
from allo.ir.types import int32, Stream
import allo.dataflow as df


@df.region()
def top(out: int32[4]):
    S: Stream[int32, 4][1]

    @df.kernel(mapping=[1])
    def producer():
        for i in range(4):
            x: int32 = i * 10
            S[0].put(x)

    @df.kernel(mapping=[1], args=[out])
    def consumer(o: int32[4]):
        for i in range(4):
            v: int32 = S[0].get()
            o[i] = v


sim = df.build(top, target="simulator")
o = np.zeros(4, dtype=np.int32)
sim(o)
c = sim.get_cycles()
print("functional result:", o.tolist(), "(expect [0, 10, 20, 30])")
print("simulator per-PE :", c.per_pe)
print("simulator makespan:", c.makespan)
print()
print("Vitis csynth ground truth for the same design:")
print("  producer_0 = 6      consumer_0 = 6      top = 19..20")
print(f"  => sim/HLS ratio: producer {c.per_pe.get('producer_0',0)/6:.1f}x, "
      f"consumer {c.per_pe.get('consumer_0',0)/6:.1f}x, makespan {c.makespan/19.5:.1f}x")
