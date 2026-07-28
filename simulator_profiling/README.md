# simulator_profiling

Profiling harness for Allo's dataflow **simulator** (`df.build(target="simulator")`).
Measures *where* the simulator spends time and *whether* non-blocking behavior is
deterministic, as a baseline for the wire / valid_only / valid_ready / non-blocking
extension work. See `../claude_simulator.md` for the full analysis and results.

## Files

| file | what it does |
|---|---|
| `profile_worker.py` | Profiles ONE systolic-GEMM config in its own process. Builds the region, checks correctness vs `numpy A@B`, runs a warm N-run loop, and emits one JSON line of metrics from `getrusage` deltas (build time is excluded). |
| `profile_driver.py` | Sweeps a list of configs (16→324 PEs), launching one `profile_worker.py` subprocess per config with `OMP_NUM_THREADS = PE count`. Prints a table + correctness verdict and writes `profile_results.json`. |
| `profile_strace.py` | Syscall breakdown (`futex`/`nanosleep`/`sched_yield`) via `strace -f -c`, per-sim = counts(NRUNS=1)−counts(NRUNS=0), merged with the clean `sys_frac`/`ivcsw` columns. Shows *what* the kernel time is made of. strace perturbs heavily, so counts are composition indicators, not magnitudes. |
| `profile_knobs.py` | libomp runtime-knob sweep (`OMP_WAIT_POLICY`, `OMP_PROC_BIND`/`OMP_PLACES`) on oversubscribed configs — how much scheduling cost is recoverable with env vars alone. **Finding: `OMP_WAIT_POLICY=passive` → 4–6.5× faster, ~1000–4000× fewer involuntary ctx switches, variance collapses.** Writes `profile_knobs_results.json` / `knobs_output.txt`. |
| `profile_worker_heavy.py` / `profile_heavy_driver.py` | Compute-intensity sweep: same systolic topology but FLOP loop-carried madds per PE step, swept 0→1M under active vs passive. Tests whether "compute negligible" holds and whether passive still wins when PEs compute. **Finding: passive wins 32×→3.3× (always ≥3.3×, never hurts); "compute negligible" only at FLOP≈0; active masks compute, passive reveals it.** Writes `profile_heavy_results.json` / `heavy_output.txt`. |
| `deadlock_worker.py` / `deadlock_driver.py` | Runs a correct control + 3 deliberately-deadlocking designs (starvation, back-pressure, circular wait) under a hard `timeout -s KILL`. **Original finding (now fixed): the sim did NOT detect deadlock — it hung forever with no error, diagnostic or localization; only the control completed.** Since `62d5e4b` all four resolve in 1–3 s — see [Deadlock detection](#deadlock-detection) below. Writes `deadlock_output.txt`. |
| `probe_guard_emission.py` | Compiler-side check for the deadlock guard: monkeypatches `_emit_blocked_delta`, then asserts the invariant `(#inc) − (#dec) == n_pes` (each spin loop emits a matched ±1 pair; each PE termination an unpaired +1). Also prints which allo checkout was imported. Exits non-zero if unbalanced. |
| `check_dce_survival.py` | Pass-pipeline-side check: counts an op before vs after lowering and fails if any were dropped. Catches `MemRefDCE` silently erasing side-effecting ops. **Use together with `probe_guard_emission.py` — see the warning below; either alone is misleading.** |
| `cycle_calibration.py` | Runs the exact design that was pushed through Vitis csynth and compares `sim.get_cycles()` against the reported cycles. **Result: 7 modelled vs 6 reported (1.2×), down from ~2.7×.** One data point on two trivial integer PEs — float/BRAM/pipelined-loop latencies are uncalibrated. |
| `feedback_worker.py` / `feedback_driver.py` | Cyclic (feedback) dataflow: primed 2- and 3-kernel loops vs the same loop unprimed, under a hard timeout. **Finding: buffered feedback works correctly & deterministically when primed; the same cycle unprimed deadlocks — priming/depth (design), not the sim, decides. Hard case for the extension is only *combinational* feedback.** Writes `feedback_output.txt`. |
| `nb_nondeterminism.py` | Standalone demo: proves the current non-blocking (`try_put`/`try_get`) ops are non-deterministic — same program + input yields many different outputs across runs (scheduler-decided, no clock). |
| `sweep_output.txt` | Baseline full timing sweep (before the `OMP_WAIT_POLICY=passive` default). |
| `sweep_output_passive.txt` | Full timing sweep AFTER the passive default was added to `build_dataflow_simulator` — 12–28× faster at scale, all PASS. |
| `strace_output.txt` / `knobs_output.txt` | Saved stdout of the syscall-breakdown and knob sweeps. |
| `profile_results.json` / `profile_results_passive.json` / `profile_strace_results.json` / `profile_knobs_results.json` | Machine-readable raw metrics from each sweep. |

## Deadlock detection

The simulator used to hang forever on a deadlocked design — no error, no output,
nothing to debug. It now raises `DeadlockError` naming the stream and the blocking
side. Implemented in `allo/backend/simulator.py` (`ed99cc2` → `3831021` → `62d5e4b`).

```bash
python simulator_profiling/deadlock_worker.py circular    # one case
python simulator_profiling/deadlock_driver.py             # all four under timeout
```

| case | before | after (1–3 s) |
|---|---|---|
| `control` | COMPLETED | COMPLETED |
| `mismatch_get` | hangs | DEADLOCK — peer-done, names stream + side |
| `overfill_put` | hangs | DEADLOCK — peer-done, names stream + side |
| `circular` | hangs | DEADLOCK — circular wait |

**Two detectors with deliberately different confidence. Keep them distinguished —
they report a `cause` and are worded differently on purpose.**

- **peer-done — a *proof*.** A PE blocked on a stream whose peer PE has already
  returned can never unblock: nobody is left to drain the full FIFO or fill the
  empty one. No threshold, no false positives, cannot misfire on a merely slow
  peer. Keys off `_CLOCK_DONE_BIT`.
- **circular — a *heuristic*.** No PE ever finishes in a cycle, so the proof never
  fires. Instead it counts consecutive polls where every PE is blocked-or-finished
  (`ALLO_SIM_DEADLOCK_POLLS`, default 16384 ≈ 1 s). An *instantaneous* all-blocked
  reading is **not** sufficient — a PE can be counted blocked while its condition
  has already been satisfied — so the consecutive-poll run is what makes it robust.
  Its message says the reporting PE is one participant, not necessarily the cause.

**Independent of the cost model.** Detection keys off *completion*, not simulated
time, so zeroing every per-op latency changes nothing. Verified by running the whole
matrix under `ALLO_SIM_CLOCK=cycle`, which bypasses the latency table entirely. It
*does* still need the clock plumbing: with no `sim.clock` PEs, `n_pes == 0`, the
guard becomes a no-op and the design hangs as before.

### ⚠ MemRefDCE silently deletes side-effecting ops

`mlir/lib/Transforms/MemRefDCE.cpp:28` erases **any** op with results and no uses,
with no side-effect check:

```cpp
if (op->getNumResults() != 0 && op->use_empty()) { op->erase(); }
```

All 10 `memref.atomic_rmw` ops for the blocked-PE counter were emitted and then
deleted before reaching LLVM, so the watchdog was dead code — no error, no warning,
no detection. Same trap as a `try_put` whose `ok` flag is never read. Fixed by
sinking the atomic's old value into a live global slot.

**Debugging lesson:** "my emission helper ran" ≠ "the op is in the final module".
`probe_guard_emission.py` reported a healthy 10 calls while `check_dce_survival.py`
showed 0 surviving. Only running **both** localised the loss to the pass pipeline.

### Not covered

- **`try_put`/`try_get` time barriers** (`_emit_read_barrier` / `_emit_write_barrier`)
  are not instrumented, so a PE parked there is not counted blocked. This
  *undercounts*, costing detection rather than causing false positives.
- **Livelock** in non-blocking retry loops is missed entirely — those keep ticking
  their clocks and re-entering, so they never look blocked. Likely the bigger gap
  for generated non-blocking designs.
- **`tests/dataflow/test_hierachical_mesh.py` still hangs** (killed at 1500 s, exit
  137) with both detectors live. It hangs identically at baseline, and it is *our*
  test (`b73b555`, 2026-04-14), not upstream — upstream's is `test_hierachical.py`.
  It uses only blocking ops, so its spin loops *are* instrumented.
  **Unverified hypothesis:** `n_blocked` never reaches `n_pes` because a PE that has
  not been scheduled is neither blocked nor finished, and that mesh has more PEs than
  OMP threads. Test by re-running with `OMP_NUM_THREADS` ≥ PE count; if it then fires,
  the fix is to count not-yet-started PEs as blocked. Best specimen we have for this gap.

## Applied change (from this profiling)

`allo/backend/simulator.py :: build_dataflow_simulator` now sets
`OMP_WAIT_POLICY=passive` by default (only if unset — user override respected),
next to the existing `OMP_MAX_ACTIVE_LEVELS`. Idle PE-threads sleep instead of
busy-spinning at OpenMP barriers/locks. Verified 12–28× faster at scale, ~7000×
fewer involuntary context switches, correctness unchanged. See
`sweep_output.txt` (before) vs `sweep_output_passive.txt` (after).

## How to run

Requires the `allo` conda env, the RHEL8 LLVM build (for the JIT runtime libs), and the
working checkout on `PYTHONPATH` (avoids the stale installed `allo`):

```bash
source /home/zsm9/miniconda3/etc/profile.d/conda.sh && conda activate allo
export LLVM_BUILD_DIR=/work/shared/common/llvm-project-main/build-rhel8   # has libomp/runner utils; build-rhel8 is GLIBC-safe (plain build/ core-dumps)
export PYTHONPATH=/home/zsm9/allo_sup

cd /home/zsm9/allo_sup/simulator_profiling
python -u profile_driver.py | tee sweep_output.txt      # full sweep
NRUNS=50 python -u profile_driver.py                     # override warm-run count
python profile_worker.py 8 8 30                          # one config: side=8, depth=8, 30 runs
python nb_nondeterminism.py                              # non-determinism demo

# deadlock detection
python deadlock_worker.py circular                       # one case: control | mismatch_get | overfill_put | circular
python deadlock_driver.py                                # all four under a hard timeout
ALLO_SIM_CLOCK=cycle python deadlock_worker.py circular  # prove detection is cost-model-independent
ALLO_SIM_DEADLOCK_POLLS=1024 python deadlock_worker.py circular   # lower the watchdog threshold

# guard diagnostics (run BOTH — either alone is misleading)
python probe_guard_emission.py                           # were the ops emitted?      (compiler side)
python check_dce_survival.py                             # did they survive to LLVM?  (pass pipeline)

# cost model vs Vitis
python cycle_calibration.py                              # 7 modelled vs 6 reported
```

**`RuntimeError: Unknown function top`** means `LLVM_BUILD_DIR` is unset — the JIT
found no runtime symbols. The `allo` conda env sets it; do not override it with a
plain `build/` (GLIBC abort). This is the most common way these scripts appear broken.

`OMP_NUM_THREADS` is set per-config by the driver and must be ≥ the PE count, because
libomp reads it once at load and each PE runs as its own OpenMP section — too few threads
and sections never start (deadlock). That's why each config runs in a fresh subprocess.

## Metric glossary (per config, warm N-run loop, build excluded)

- `pe_active` / `pe_total` — PEs after / before dead-corner elimination; `pe_total` = threads spawned.
- `oversub` = `pe_total / nproc` — the variable that flips spin-bound → scheduling-bound.
- `sim_ms_mean ± sd` — warm per-invocation latency and its run-to-run variance.
- `cpu_busy_cores` = (utime+stime)/wall — cores actually busy on average.
- `sys_frac` = stime/(utime+stime) — kernel-CPU fraction. **Low ⇒ user-mode spin; high ⇒ futex/nanosleep/scheduling-bound.**
- `nvcsw_per_sim` / `nivcsw_per_sim` — voluntary (sleep/futex wait) / involuntary (scheduler preemption) context switches per simulation.
- `peak_rss_mb` — peak resident memory.
- `max_abs_err` — correctness vs `numpy A@B` (tol 1e-3); the driver prints a PASS/CHECK verdict.

## Headline result (64-core host)

Two regimes, knee at the core count: below 1 PE/core the sim is **user-mode spin-bound**
(`sys_frac`≈0.01); above it, `sys_frac` plateaus at **~0.79** (kernel/scheduling-bound) and
involuntary context switches explode to **~7.8M per single simulation** at 324 PEs.
Parallelism saturates at ~59 cores; beyond that it's pure context-switch overhead. Memory
and compute are never the bottleneck. Full table in `../claude_simulator.md`.
