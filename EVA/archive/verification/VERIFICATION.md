# final_runs — verification (sim tests + bit-exact RTL cosim)

Two levels. **QoR/routing uses NSTEP=10/depth-2** (the chip files here);
**verification overrides the config** per its needs (below). The chip .py in
`../` are the single source; harnesses set `e.M/e.N/e.NSTEP/e.PRIME_TOKENS/
e.STREAM_DEPTH` before building.

## Level 1 — sim functional (fast, this folder)
```
LLVM_BUILD_DIR=/home/zsm9/miniconda3/envs/allo \
python run_sim.py {eva|eva_sb|eva_sb_syscredit}
```
Runs the canonical `Allo/EVA/tests/eva_tests.py` (7 tests) against the chip.
`_dims` sets each test's NSTEP. Verified path (passthrough PASS vs eva).

## Level 2 — bit-exact RTL cosim (dump golden vectors → replay vs RTL)
The VALIDATED replay suites (which produced the COMPARISON.md results) live at:
| chip | suite | cosim config | workloads |
|---|---|---|---|
| eva | `../../scoreboard_allo_eva_final/eva_prime_baseline/cosim_suite/` | PRIME=1/D=2 | normal dump; fft8r needs MARGIN=600 |
| eva_sb | `../../scoreboard_allo_eva_final/cosim_suite/` | PRIME=1/D=2 | **dilated** (F≥2; drop-model needs rate-match) |
| eva_sb_syscredit | `../../scoreboard_allo_eva_final/cosim_suite_sc/` | **PRIME=2/D=4** (scr edges) | **padded** (lossless; run longer) |

Each suite: `dump_vectors.py` (7 tests → `vec_*.npz`), `dump_workloads*.py`
(mmmr/fft2r/fft8r), `run_suite.py` (npz → header → kernel → csynth+cosim →
PASS/FAIL), `tb_replay.cpp` (one generic bitwise-compare TB). Run recipe:
```
cd <suite>; export LLVM_BUILD_DIR=/home/zsm9/miniconda3/envs/allo
python dump_vectors.py && python dump_workloads.py && python run_suite.py
```
NOTE these suites import `eva`/`eva_sb`/`eva_sb_syscredit` from their own
locations — they predate final_runs. To point them at THESE chip files, prepend
`sys.path.insert(0, "<final_runs>")`. (Behaviour is identical: same source.)

## Verified status (from COMPARISON.md; bit-exact RTL unless noted)
| chip | sim tests | RTL cosim | workloads (RTL) |
|---|---|---|---|
| eva | 7/7 | 9 test-vectors ✅ | MMM ✅ FFT2 ✅ FFT8 ✅ |
| eva_sb | 7/7 | 9 ✅ | MMM ✅ FFT2 ✅ (FFT8 = overnight run) |
| eva_sb_syscredit | 11/11 | 11 ✅ | MMM ✅ FFT2 ✅ (FFT8 = blocked on 8×5 codegen) |

## Not included: eva_sb_nb (event-driven)
Parked — router NB logic proven but sim non-deterministic; needs free-running
termination + vhls printer extension for RTL. See `../../scoreboard_allo_eva_
final/eva_sb_nb.py` banner.
