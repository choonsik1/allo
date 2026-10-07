# EVA — the EVA accelerator (A-tile), rebuilt in Allo

The EVA accelerator (A-tile) — a tiled fp16/int16 spatial array — rebuilt in Allo and
verified bit-exact against the original EVA RTL by 8×8 RTL cosim. The measured throughput
and place-and-route numbers live in `results/final_chips/`.

## Layout
| dir | what |
|---|---|
| `results/` | evaluation + **the deliverable**. Start at `results/final_chips/` — 4 verified chips (fp16/int16 × blocking/non-blocking) with throughput + P&R tables. Also `EVALUATION.md`, `COMPARISON.md`, `DESIGN_RATIONALE.md`. |
| `sim/` | golden-replay harness (`replay_golden_*.py`) — runs a golden EVA program through an Allo chip and diffs bit-exact vs the golden RTL (the functional cross-check). |
| `generators/` | program generators (`build_fft.py`, `build_golden_cosim.py`, …) that emit per-workload kernels/vectors. |
| `golden/` | golden-RTL testbench stimuli + capture scripts (the cosim oracle); `programs_decoded.txt` = the fft/cordic programs in human-readable EVA-ISA. |
| `archive/` | superseded experiments, earlier chip variants (`archive/chips/`), old results (`archive/old_results/`), and the full version log (`archive/VERSION_LOG.md`), kept for provenance. |

The verified chip **sources** live under `results/final_chips/<config>/chip/` — see that folder.

## Docs
- `results/EVALUATION.md` — throughput (outputs/cycle) + P&R tables, methodology.
- `results/DESIGN_RATIONALE.md` — the two models (v2.0 blocking / v3.0 non-blocking), the decision matrix, and the always-fire/bubble mechanics.
- `results/COMPARISON.md` — vs the golden RTL: faithfulness, simplification audit, Allo-expressiveness gaps.

## Reproduce
Each config in `results/final_chips/<config>/` has `chip/` (source), `pnr/` (P&R reports),
and `cosim/` (`rcmon.txt` throughput stamps + `RESULT.txt` verdicts).
