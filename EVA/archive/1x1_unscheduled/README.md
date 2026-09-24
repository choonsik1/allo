# 1×1 UNSCHEDULED — EVA rtprime on the Allo SystemC backend (2026-08-03)

Baseline: emitted **without** any Allo schedule, so there are **no `#pragma hls_*`** in
`allo/kernel.cpp`. Catapult does all the scheduling itself.

Config: `M=N=1`, `NSTEP=215`, `float16`, `PRIME_TOKENS=6`, nangate-45nm, clock 2.0 ns.
Driver: `allo/driver_used.py` (standalone cosim driver; predates the `SCHED` knob in
`scripts/run_systemc.py`).

## Result — full flow GREEN
| step | result |
|---|---|
| codegen | ✅ 4,767 lines, 22 `SC_MODULE`, 274 `Connections` |
| csim | ✅ `out_e == [1..6]` bit-exact |
| csyn | ✅ 0 errors, 6m16s |
| SCVerify RTL cosim | ✅ **8/8 output arrays bit-exact vs golden** (Xcelium 24.03) |

## Numbers (`reports/rtl.rpt`)
| metric | value |
|---|---|
| clock target / critical path | 2.000 ns / 2.0978 ns |
| **slack** | **−0.0978 ns** (does NOT close; 2.1 ns would) |
| total area score (post-assign) | 150,109 (REG 64%, FUNC 15%, MUX 14%) |
| `node_0_0` | 1,960 real ops, throughput **1**, reset length 7,317 |
| design total | 2,606 real ops |

Note: Catapult reaches **throughput 1 with no pragmas at all** — see `../1x1_scheduled/`
for what adding `pipeline_ii=1` actually buys (short answer: area, not throughput).

## Workload
1×1 systolic passthrough: one PE runs `MOV west-rx -> east-tx`, delivered as a router
program packet; a 6-long ramp `[1..6]` enters WEST at cycles 15–20 and must exit EAST
unchanged. Verified twice — RTL vs software golden (`hls.py`), and `out_e` vs a numpy
ramp. NOTE: the emitted testbench has **no self-check**; a clean exit is not a pass.

## Layout
```
rtl/       rtl.v, concat_rtl.v (+ .dc/.sdc, order files)
reports/   rtl.rpt (area/timing/throughput), synth.log, cosim.log, catapult.log
allo/      chip source + workloads + driver + the exact emitted kernel.cpp/run.tcl
generated/ full untouched project (inputs, goldens, RTL outputs, build dirs)
```

> `rtl/` (regenerable netlists) removed 2026-08-15; `reports/` kept — they back the 1x1 area ladder in the top-level README.
