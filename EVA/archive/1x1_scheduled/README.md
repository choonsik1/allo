# 1×1 SCHEDULED — EVA rtprime on the Allo SystemC backend (2026-08-03)

Same chip and workload as `../1x1_unscheduled/`, but built through
`get_scheduled_eva(pipeline_node=True, partition_rf=True)`, so the emitter produces
Catapult-native loop pragmas. `allo/kernel.cpp` contains **1**
`#pragma hls_pipeline_init_interval 1` (one node at 1×1), placed in the loop
**preheader** — in-body placement makes Catapult drop it with CIN-319:

```cpp
#pragma hls_pipeline_init_interval 1
l_S_t_1_t: for (int t = 0; t < 215; t++) {
```

Config: `M=N=1`, `NSTEP=215`, `float16`, `PRIME_TOKENS=6`, nangate-45nm, clock 2.0 ns.
Reproduce: `SCHED=1 MODE=cosim python scripts/run_systemc.py` (driver snapshot in
`allo/driver_used.py`).

## Result — full flow GREEN
| step | result |
|---|---|
| codegen | ✅ 4,768 lines, 1 `hls_pipeline_init_interval` |
| SCVerify RTL cosim | ✅ **bit-exact** (Xcelium 24.03) |

## Numbers vs unscheduled (`reports/rtl.rpt`)
| metric | unscheduled | **scheduled** | Δ |
|---|---|---|---|
| slack | −0.0978 ns | **−0.0848 ns** | 13% less negative |
| critical path | 2.0978 ns | 2.0848 ns | −0.013 ns |
| **area score** | 150,109 | **158,860** | **+5.8%** |
| `node_0_0` real ops | 1,960 | 3,235 | +65% |
| `node_0_0` throughput | 1 | **1** | **no change** |
| **reset length** | 7,317 | **5,169** | **−29%** |
| design total ops | 2,606 | 3,881 | +49% |

## Takeaway
`pipeline_ii=1` bought **no throughput** here — Catapult already scheduled the
unscheduled build to throughput 1 on its own. The cost is +5.8% area and +65% ops in
the node, for a 0.013 ns timing gain. The one real win is **reset length −29%**.

Neither build closes 2.0 ns (both ~4–5% short); 2.1 ns / 476 MHz would close either.

Caveat: `partition_rf=True` emitted **no** `hls_unroll` — array partitioning does not
appear to map onto a Catapult pragma in this path, so that half of the schedule may be
a no-op here. Unverified.

## Layout
```
rtl/       rtl.v, concat_rtl.v (+ .dc/.sdc, order files)
reports/   rtl.rpt (area/timing/throughput), synth.log, cosim.log, catapult.log
allo/      chip source + workloads + driver + the exact emitted kernel.cpp/run.tcl
generated/ full untouched project (inputs, goldens, RTL outputs, build dirs)
```

> `rtl/` (regenerable netlists) removed 2026-08-15; `reports/` kept — they back the 1x1 area ladder in the top-level README.
