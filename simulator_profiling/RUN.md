# RUN — commands to run every profiling test

All tests run against the **original simulator** (`allo/backend/simulator.py` — the
`OMP_WAIT_POLICY=passive` experiment was reverted, so a plain run gives the original
baseline behavior). Results tables: see `RESULTS.md`. File/metric docs: `README.md`.

## 1. Setup (once per shell)

```bash
source /home/zsm9/miniconda3/etc/profile.d/conda.sh && conda activate allo
export LLVM_BUILD_DIR=/work/shared/common/llvm-project-main/build-rhel8   # build-rhel8 = GLIBC-safe + has libomp; plain build/ core-dumps
export PYTHONPATH=/home/zsm9/allo_sup                                     # force the working checkout
cd /home/zsm9/allo_sup/simulator_profiling
```

## 2. All tests

```bash
# Round 0 — non-blocking non-determinism demo             (~10s)
python nb_nondeterminism.py

# Round 1 — main timing sweep (original baseline)          (~2.5 min)
python -u profile_driver.py       | tee sweep_output.txt

# Round 2 — syscall breakdown (futex vs sched_yield…)      (~5 min)
python -u profile_strace.py       | tee strace_output.txt

# Round 3 — libomp knob sweep (baseline/active/passive/pin)(~3–4 min)
python -u profile_knobs.py        | tee knobs_output.txt

# Round 4 — compute-heavy (FLOP sweep, active vs passive)  (~3–4 min)
python -u profile_heavy_driver.py | tee heavy_output.txt

# Round 5 — deadlock detection                             (~70s)
python -u deadlock_driver.py      | tee deadlock_output.txt

# Round 6 — feedback / cyclic dataflow                     (~25s)
python -u feedback_driver.py      | tee feedback_output.txt
```

## 3. Baseline vs passive

- **Plain run = original slow baseline** (default, since the code was reverted).
- For the passive (fast) comparison, set it explicitly:
  ```bash
  OMP_WAIT_POLICY=passive python -u profile_driver.py | tee sweep_passive.txt
  ```
- The knob sweep already tests baseline/active/passive/pinning as separate rows.

## 4. Run everything in sequence

```bash
cd /home/zsm9/allo_sup/simulator_profiling
for e in "python nb_nondeterminism.py" \
         "python -u profile_driver.py       | tee sweep_output.txt" \
         "python -u profile_strace.py        | tee strace_output.txt" \
         "python -u profile_knobs.py         | tee knobs_output.txt" \
         "python -u profile_heavy_driver.py  | tee heavy_output.txt" \
         "python -u deadlock_driver.py       | tee deadlock_output.txt" \
         "python -u feedback_driver.py       | tee feedback_output.txt"; do
  echo "=== $e ==="; eval "$e"; done
```
Total ≈ 15–20 min (dominated by the ~35 s builds at the largest array sizes).

## 5. Useful overrides

- `NRUNS=50 … profile_driver.py` — more warm runs (tighter stats)
- `STRACE_TIMEOUT=120 … profile_strace.py`
- `DL_TIMEOUT=30 … deadlock_driver.py`
- `FB_TIMEOUT=30 N=20 … feedback_driver.py`
- single config: `OMP_NUM_THREADS=100 python profile_worker.py 8 8 30`  (side=8, depth=8, 30 runs)
