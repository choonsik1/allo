# EVA accelerator — Allo rebuild

A parameterized rebuild of the EVA accelerator in [Allo](https://github.com/cornell-zhang/allo):
an `M×N` mesh of fused router+PE nodes with perimeter drivers/collectors, real fp16, one-arg
datatype swap (`Ty`). The chip is **router-load only** — programs, weights and config all arrive as
router packets.

## Files

- **`eva.py`** — the hardware. `get_eva_top(Ty=float16)` builds the mesh; drive it with
  `run_eva(mod, ins, ivs, outs, rins, routs)`. Compile-time dims are module globals (`M, N, NSTEP, …`).
  This is the **END-PUT primed** variant (every process emits its t=0 outputs before the loop, puts
  moved to iteration end): the generated RTL is deadlock-free and replay-verified **bit-exact vs the
  Python simulator** (9/9 configs incl. the 4×4 mesh, plus router-loaded MMM).
- **`eva_comments.py`** — fully-commented walkthrough of eva.py (same code, AST-verified).
- **`tests/eva_workloads.py`** — router-loaded programs, verified vs numpy:
  - `mmmr` — weight-stationary `Y = X @ W`
  - `fft2r` — 2-point butterfly
  - `fft8r` — 8-point DIT FFT (bit-exact vs `numpy.fft`)
- **`tests/eva_tests.py`** — 7 bring-up tests (`passthrough`, `row`, `router`, `core_send`,
  `turn`, `shuffle`, `mesh`), easiest→hardest.
- **`tests/cosim/`** — RTL replay suite: `dump_vectors.py` / `dump_workloads.py` snapshot every
  simulator run into `vec_*.npz` golden vectors (tracked); `run_suite.py` replays each vector
  set against the generated RTL via `tb_replay.cpp` (Vitis HLS 2023.2 cosim) and prints a
  PASS/FAIL/DEADLOCK table. Status: **9/9 bit-exact, 0 deadlocks** (+ `mmmr` workload PASS).

## Run

```bash
export LLVM_BUILD_DIR=$CONDA_PREFIX
export OMP_NUM_THREADS=256          # >= #kernel instances or the sim deadlocks

cd tests
python eva_workloads.py mmmr        # or fft2r / fft8r
python eva_tests.py                 # all bring-up tests

cd cosim                            # RTL replay (needs vitis_hls 2023.2 on PATH)
python dump_vectors.py              # refresh golden vectors from the simulator (allo env)
python run_suite.py                 # cosim every vec_*.npz; optional name filter arg
```

The Python simulator is the source of truth for correctness.

## HLS

`python eva.py` generates an HLS project (Vitis HLS 2023.2, part `xcu280`); it does not run the tool.
csynth + P&R route ~301–306 MHz at 4×4. RTL cosim runs through `tests/cosim/run_suite.py`
(golden vectors dumped from the simulator, replayed against the generated RTL):
9/9 bit-exact, 0 deadlocks.
