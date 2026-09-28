# EVA — final chips, results & reports

Four configurations, one folder each. Everything here is a **copy**; originals are untouched.

```
final/<config>/
  chip/     the Allo chip source (.py)
  pnr/      1-PE node-level Place-and-Route (Vitis 2025.1, xczu7ev-ffvc1156-2-e):
            utilization_routed.rpt, timing_routed.rpt, csynth.rpt, kernel_1x1*.cpp, RESULT.txt
  cosim/    8x8 RTL cosim per workload (mmm, fft, cordic_{cr,cv,hr,hv}):
            rcmon.txt (throughput stamps), RESULT.txt (PASS + stamp count), cosim.log
```

## Folder → configuration

| Folder | Config | Source chip | Notes |
|---|---|---|---|
| `fp16_v2p0_blocking`     | fp16 / Allo v2.0 (blocking)     | fp16_skid  | rbuf-full-partition; node II=2 (FPU recurrence). fft/cordic use strong `_ap` vectors. |
| `int16_v2p0_blocking`    | int16 / Allo v2.0 (blocking)    | int16_skid | rbuf-full-partition; node II=1. |
| `fp16_v3p0_nonblocking`  | fp16 / Allo v3.0 (non-blocking) | fp16_elastic  | Option-B fft fix. |
| `int16_v3p0_nonblocking` | int16 / Allo v3.0 (non-blocking)| int16_elastic | Option-B, int16 vectors + `fft_rev2`. |

## Throughput (elements/cycle, aggregate = 8 / per-lane avg gap from `cosim/*/rcmon.txt`)

| Workload | Original RTL | fp16 v2.0 | int16 v2.0 | fp16 v3.0 | int16 v3.0 |
|---|---|---|---|---|---|
| MMM        | 2    | 0.67 | 1.34 | 1.6  | 2    |
| FFT (8-pt) | 1.23 | 0.16 | 0.32 | 0.37 | 0.39 |
| CORDIC     | 0.55 | 0.12 | 0.24 | 0.28 | 0.33 |

CORDIC throughput is the average over the 4-variant family (cr/cv/hr/hv).

## Place-and-Route, 1 PE, node-level (from `pnr/utilization_routed.rpt` + `timing_routed.rpt`)

| Config | Clock (ns) | Freq (MHz) | LUT | FF | DSP | SRL | CLB |
|---|---|---|---|---|---|---|---|
| fp16 v2.0 (blocking)      | 4.431 | 225.68 | 3,120 | 2,564 | 2 | 6 | 585 |
| int16 v2.0 (blocking)     | 4.444 | 225.02 | 2,719 | 1,602 | 1 | 8 | 496 |
| fp16 v3.0 (non-blocking)  | 4.311 | 231.96 | 2,186 | 1,115 | 2 | 8 | 404 |
| int16 v3.0 (non-blocking) | 4.647 | 215.19 | 1,766 | 1,004 | 1 | 8 | 308 |

All four P&R rows are `syn.top=node_0_0`, non-wrapper placed utilization + routed timing — one consistent methodology.
