# EVA — the EVA accelerator (A-tile), rebuilt in Allo

The EVA accelerator (A-tile) — a tiled fp16/int16 spatial array — rebuilt in Allo and
verified bit-exact against the original EVA RTL by 8×8 RTL cosim. The measured throughput
and place-and-route numbers live in `results/final_chips/`.

## Layout
| dir | what |
|---|---|
| `results/` | evaluation + **the deliverable**. Start at `results/final_chips/` — 4 verified chips (fp16/int16 × blocking/non-blocking) with throughput + P&R tables. Also `EVALUATION.md`, `COMPARISON.md`, `DESIGN_RATIONALE.md`, `CHIP_MAP.md`. |
| `final/` | canonical chip sources (`syscredit_1x1/` = blocking, `non_syscredit_1x1/` = non-blocking) + the golden-replay harness (`sim/`). |
| `generators/` | program generators (`build_fft.py`, `build_golden_cosim.py`, …) that emit per-workload kernels/vectors. |
| `golden/` | golden-RTL testbench stimuli + capture scripts (the cosim oracle). |
| `archive/` | superseded experiments + earlier chip variants (`archive/chips/`), kept for provenance. |

## Docs
- `results/EVALUATION.md` — throughput (outputs/cycle) + P&R tables, methodology.
- `BUBBLE_MODEL_PLAN.md` — status + the always-fire/bubble architecture plan + findings log.

## Reproduce
Each config in `results/final_chips/<config>/` has `chip/` (source), `pnr/` (P&R reports),
and `cosim/` (`rcmon.txt` throughput stamps + `RESULT.txt` verdicts).
