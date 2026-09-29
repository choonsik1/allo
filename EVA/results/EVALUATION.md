# EVA — Evaluation: Allo → Vitis HLS vs. the original EVA RTL

Apples-to-apples comparison of the Allo/HLS EVA rebuild against the original hand-written
EVA RTL, plus the correctness and productivity story. Raw data and reports:
[`final_chips/`](final_chips/). Companion: [`DESIGN_RATIONALE.md`](DESIGN_RATIONALE.md)
(why the final chips are what they are).

## 1. Designs under test

Four Allo/HLS chips — two datatypes × two execution models — plus the original RTL baseline:

| config | datatype | model | node II |
|---|---|---|---|
| **fp16 v2.0 (blocking)**      | fp16  | credit / blocking      | II=2 (FPU recurrence) |
| **int16 v2.0 (blocking)**     | int16 | credit / blocking      | II=1 |
| **fp16 v3.0 (non-blocking)**  | fp16  | elastic / non-blocking | — |
| **int16 v3.0 (non-blocking)** | int16 | elastic / non-blocking | — |
| **Original RTL**              | fp16  | hand-written EVA       | baseline |

## 2. Throughput — outputs/cycle (8×8 PE grid)

| Workload | Original RTL | fp16 v2.0 | int16 v2.0 | fp16 v3.0 | int16 v3.0 |
|---|---|---|---|---|---|
| MMM        | 2.00 | 0.67 | 1.34 | 1.60 | 2.00 |
| FFT (8-pt) | 1.23 | 0.16 | 0.32 | 0.37 | 0.39 |
| CORDIC     | 0.55 | 0.12 | 0.24 | 0.28 | 0.33 |

One "output" = one MMM result element, one FFT complex sample (re+im), one CORDIC scalar.
CORDIC is the average over the 4-variant family (cr/cv/hr/hv).

## 3. Place & route — 1 PE, node level (Vitis 2025.1, `xczu7ev-ffvc1156-2-e`)

| Config | Clock (ns) | Freq (MHz) | LUT | FF | DSP | SRL | CLB |
|---|---|---|---|---|---|---|---|
| fp16 v2.0 (blocking)      | 4.431 | 225.68 | 3,120 | 2,564 | 2 | 6 | 585 |
| int16 v2.0 (blocking)     | 4.444 | 225.02 | 2,719 | 1,602 | 1 | 8 | 496 |
| fp16 v3.0 (non-blocking)  | 4.311 | 231.96 | 2,186 | 1,115 | 2 | 8 | 404 |
| int16 v3.0 (non-blocking) | 4.647 | 215.19 | 1,766 | 1,004 | 1 | 8 | 308 |

All rows are `syn.top=node_0_0`, non-wrapper placed utilization + routed timing.

## 4. Key findings

- **Non-blocking reaches RTL parity on MMM** (int16 v3.0 = 2.0 = original). MMM is issue-bound,
  and HLS reproduces the issue rate exactly.
- **FFT is the bottleneck (~4–5× more cycles/output than MMM)** on every version — the only
  workload whose critical path runs through the **router** (butterfly operands are exchanged
  across lanes; the pipeline stalls on that round-trip). MMM and CORDIC use zero router links.
- **int16 vs fp16:** int16 wins throughput (1-cycle adder → II=1 vs fp16's II=2) and area, but
  **not frequency** — the clock is set by the DSP-multiply → scoreboard path, which is identical
  in both datatypes.
- **Allo vs RTL on FFT (~3× slower):** the HLS exchange round-trip carries a 5-deep scoreboard
  retire + registered FIFO handshakes, where the RTL uses a combinational handshake and no
  scoreboard — hidden on issue-bound MMM, exposed on FFT.

## 5. Correctness

All four chips are **8/8 bit-exact** against the golden EVA RTL by 8×8 RTL cosim, on all six
workloads (mmm, fft, cordic ×4).

## 6. Methodology & fairness

- **Metric = outputs/cycle**, frequency-independent — the microarchitectural efficiency, so the
  ASIC-native original RTL and our FPGA HLS chips are comparable at the *cycle* level (not
  confounded by clock/technology). Computed as `8 / (per-lane average inter-output gap)` from the
  cosim `rc_mon` stamps.
- **Same 8×8 grid, same golden program.** The Allo chip replays the exact original EVA program and
  is checked bit-exact against the golden RTL's captured outputs; cosim is the sole correctness
  oracle.
- **fp arithmetic differs** (original = Synopsys DesignWare fp16; ours = Vitis `hls::half`), so the
  directly-comparable part is the control / router / systolic / credit fabric — our contribution.
- Original-RTL cycles come from its SystemVerilog streaming TB (VCS, steady-state); Allo cycles from
  the `rc_mon` output-write timestamps.

## 7. Productivity

- ~3.6× less code than the hand-written RTL (PE / mesh), and datatype retarget is a single knob
  (`float16` ↔ `int16`) versus a manual DesignWare-IP swap. Design entry is Python (Allo dataflow)
  rather than SystemVerilog + DW IP.

## Reproduce

Each config in [`final_chips/<config>/`](final_chips/) has `chip/` (source), `pnr/` (P&R reports),
and `cosim/` (`rcmon.txt` throughput stamps + `RESULT.txt` verdicts). See
[`final_chips/README.md`](final_chips/README.md).
