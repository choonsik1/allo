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
| `deadlock_worker.py` / `deadlock_driver.py` | Runs a correct control + 3 deliberately-deadlocking designs (starvation, back-pressure, circular wait) under a hard `timeout -s KILL`. **Finding: the sim does NOT detect deadlock — it hangs forever (no error/diagnostic/localization); only the control completes.** Writes `deadlock_output.txt`. |
| `feedback_worker.py` / `feedback_driver.py` | Cyclic (feedback) dataflow: primed 2- and 3-kernel loops vs the same loop unprimed, under a hard timeout. **Finding: buffered feedback works correctly & deterministically when primed; the same cycle unprimed deadlocks — priming/depth (design), not the sim, decides. Hard case for the extension is only *combinational* feedback.** Writes `feedback_output.txt`. |
| `nb_nondeterminism.py` | Standalone demo: proves the current non-blocking (`try_put`/`try_get`) ops are non-deterministic — same program + input yields many different outputs across runs (scheduler-decided, no clock). |
| `sweep_output.txt` | Baseline full timing sweep (before the `OMP_WAIT_POLICY=passive` default). |
| `sweep_output_passive.txt` | Full timing sweep AFTER the passive default was added to `build_dataflow_simulator` — 12–28× faster at scale, all PASS. |
| `strace_output.txt` / `knobs_output.txt` | Saved stdout of the syscall-breakdown and knob sweeps. |
| `profile_results.json` / `profile_results_passive.json` / `profile_strace_results.json` / `profile_knobs_results.json` | Machine-readable raw metrics from each sweep. |

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
```

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
