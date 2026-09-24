# 1×1 MMM — a REAL EVA program on the Allo SystemC backend (2026-08-03)

The first run here driving an actual shipped EVA workload rather than a plumbing test.
Unscheduled build (no `hls_*` pragmas), same chip as `../1x1_unscheduled/`.

## Workload — router-loaded + looping MMM
The shipped 4-instruction MMM MAC kernel `I0..I3 = 0xE13, 0x1022, 0x1F3, 0xC2D0`,
delivered over the **router** (program + stationary weight + config regs as packets),
with a **looping program counter**: the kernel lives once in `irf[0..3]` and loops
B times (`INSTR_SIZE=4`, `ITER_SIZE=B`), so any batch fits the 8-slot IRF with no
unrolling. Built by `eva_workloads.load_mmm_router(W, X)`.

```
W = [[3]]              (M,N) = (1,1)   stationary weight -> drf[0]
X = [[2],[5],[7]]      (B,M) = (3,1)   activations on the WEST systolic edge
Y = X @ W = [[6],[15],[21]]            golden (numpy fp32)
```

Exercises the scoreboard, DRF, operand forwarding, the credit plane and the fp16 MAC
datapath — far more of the chip than the `../1x1_unscheduled/` passthrough ramp.

## Result — PASS
| step | result |
|---|---|
| csim (software SystemC) | ✅ `[[6],[15],[21]]` bit-exact |
| **SCVerify RTL cosim** | ✅ **8/8 output arrays bit-exact vs golden** + `out_s == X@W` |

Synthesis 6m01s, RTL sim 16s (Xcelium 24.03).

> Note: the Vitis `golden_testbenches/README.md` claims *"C-simulation is always
> all-zero for these dataflow+feedback chips (known artifact); the RTL cosim verdict
> is authoritative."* That does **not** hold on the SystemC backend — csim produces
> the correct answer here. Only the RTL run is authoritative on Vitis.

## ⚠️ The drain-margin trap (why this first read back all zeros)
`load_mmm_router` sizes lanes as `PROG_CYCLES + KLEN*B + M + 3N + 2` = **34 cycles**.
That formula carries **no drain margin**, and rtprime's *runtime*-prime credit flow
needs **≥160** extra cycles or tokens never leave the mesh and every output reads back
zero — with no error, since the emitted testbench has no self-check.

Worked around in `allo/driver_used.py` by zero-padding every lane (`LANE_MARGIN`,
default 200 → NSTEP 34→234) rather than editing `eva_workloads.py`, which is shared
with the Vitis flow. A source fix would need a chip-dependent margin term.
Same trap as `run_systemc.py`'s old `NSTEP=55` default.

## Numbers (`reports/rtl.rpt`) — vs the passthrough baseline
| metric | passthrough (`../1x1_unscheduled`) | **MMM (this run)** |
|---|---|---|
| clock target / critical path | 2.000 / 2.0978 ns | 2.000 / **2.0978 ns** |
| slack | −0.0978 ns | **−0.0978 ns** (identical) |
| total area score | 150,109 | **151,217** (+0.7%) |
| `node_0_0` real ops | 1,960 | **1,960** (identical) |
| `node_0_0` throughput | 1 | **1** |
| reset length | 7,317 | **7,963** (+8.8%, longer lanes) |

The hardware is essentially **the same design** — identical critical path, identical op
count, +0.7% area. Expected: the RTL is a programmable chip, and MMM vs passthrough is
a difference in the *program and data* (router packets), not in the synthesized logic.
The small deltas come from lane length (234 vs 215), not the workload. This is the
`one_bitstream` property — one bitstream, many programs — reproduced on SystemC.

## Reproduce
```bash
MODE=csim  python scripts/run_mmm_systemc.py     # fast software check
MODE=cosim python scripts/run_mmm_systemc.py     # Catapult + SCVerify RTL
LANE_MARGIN=200                                  # rtprime drain margin (default)
```

## Layout
```
rtl/       rtl.v, concat_rtl.v (+ .dc/.sdc, order files)
reports/   rtl.rpt (area/timing/throughput), synth.log, cosim.log, catapult.log
allo/      chip source + eva_workloads.py + driver + emitted kernel.cpp/run.tcl
generated/ full untouched project (inputs, goldens, RTL outputs, build dirs)
```

> `rtl/` (regenerable netlists) removed 2026-08-15; `reports/` kept — they back the 1x1 area ladder in the top-level README.
