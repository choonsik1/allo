# RESULTS — Allo dataflow simulator profiling

Host: **64 cores** (the prior study's `mininpu` doc used 16). Workload: parametric
systolic GEMM (`side×side×depth`, PEs = `(side+2)²`). Metrics are **per warm
simulation**, build excluded, averaged over N runs; correctness checked vs `numpy A@B`.
Commands: `RUN.md`. Metric glossary + file list: `README.md`. Narrative + the 4
related papers: `../claude_simulator.md`.

---

## Round 0 — Non-blocking non-determinism (`nb_nondeterminism.py`)

Type-C test (producer 200 `try_put`, consumer 200 `try_get`, fixed count, no spin),
same compiled sim + same input, run 30×:

| metric | value |
|---|---|
| distinct `(put_ok, got)` outcomes | **23 / 30 runs** |
| `put_ok` range | 32 … 200 |
| `got` range | 32 … 200 |

**Finding:** identical program + input → 23 different answers. NB outcomes are decided by
the OS scheduler (no clock). Lowered but not semantically faithful.

---

## Round 1 — Where sim time goes: baseline vs passive (`profile_driver.py`)

Full sweep, N=30, all configs **PASS** (worst err 4.8e-7):

| config | PE | PE/core | baseline sim ms ±sd | passive sim ms ±sd | speedup | baseline ivcsw/sim | passive ivcsw/sim |
|---|--:|--:|--:|--:|--:|--:|--:|
| 2×2×2 | 12 | 0.25 | 0.59 ±0.20 | 0.72 ±0.17 | 0.82× | 0 | 0 |
| 4×4×4 | 32 | 0.56 | 0.90 ±0.38 | 1.10 ±0.18 | 0.82× | 27 | 0 |
| 6×6×6 | 60 | 1.0 | 3.70 ±6.38 | 1.28 ±0.21 | 2.9× | 1,566 | 0 |
| 8×8×8 | 96 | 1.56 | 21.8 ±26.3 | 1.79 ±0.15 | **12.1×** | 409,180 | 30 |
| 10×10×8 | 140 | 2.25 | 56.1 ±25.7 | 2.00 ±0.25 | **28.1×** | 2,000,747 | 93 |
| 12×12×8 | 192 | 3.06 | 87.3 ±41.6 | 3.45 ±1.79 | **25.3×** | 3,657,498 | 185 |
| 14×14×8 | 252 | 4.0 | 80.8 ±55.8 | 3.09 ±0.71 | **26.1×** | 3,269,518 | 323 |
| 16×16×8 | 320 | 5.06 | 101.3 ±85.9 | 4.94 ±3.54 | **20.5×** | 3,138,008 | 456 |

**Finding:** two regimes, knee at the core count (64). Below 1 PE/core = user-mode
spin-bound (`sys_frac`≈0.02); above it = ~80% kernel/scheduling-bound with millions of
involuntary context switches. `OMP_WAIT_POLICY=passive` recovers 12–28× at scale with
~7000× fewer ctx switches, same results (tiny sub-ms cost only when undersubscribed).
Baseline build time grows 0.84→35 s (∝ PE); memory 269→347 MB (never a wall).

---

## Round 2 — Syscall breakdown (`profile_strace.py`)

`sys_frac` / `ivcsw` are clean (unstraced); syscall counts are strace-perturbed
(composition, not magnitude):

| config | sys_frac | ivcsw/sim | futex/sim | yield/sim | nsleep/sim | **futex %time** |
|---|--:|--:|--:|--:|--:|--:|
| 2×2×2 | 0.026 | 0 | 0 | 0 | 16 | 87% |
| 4×4×4 | 0.023 | 27 | 236 | 0 | 87 | 92% |
| 6×6×6 | 0.044 | 1,566 | 0 | 1,147 | 438 | 95% |
| 8×8×8 | 0.794 | 409,180 | 0 | 3,087 | 858 | 89% |
| 10×10×8 | 0.792 | 2,000,747 | 0 | 3,194 | 1,345 | 89% |
| 12×12×8 | 0.792 | 3,657,498 | 48 | 5,498 | 2,575 | 81% |
| 14×14×8 | 0.793 | 3,269,518 | 174 | 7,370 | 3,512 | 82% |
| 16×16×8 | 0.793 | 3,138,008 | 1,883 | 8,883 | 5,503 | 82% |

**Finding:** kernel time is **futex-dominated (81–95%)** — OpenMP lock/barrier/park-wake,
not `usleep`. `sched_yield` (taskyield) and `nanosleep` (usleep) are high-count, low-time.

---

## Round 3 — libomp knob sweep (`profile_knobs.py`), N=20

**config 8×8×8 (100 PE, 1.56× oversub):**

| knob | sim ms ±sd | sys_frac | busy cores | ivcsw/sim | vs baseline |
|---|--:|--:|--:|--:|--:|
| baseline | 11.76 ±16.6 | 0.80 | 56.3 | 185,934 | 1.00× |
| **wait=passive** | **1.81 ±0.20** | 0.27 | 4.8 | 30 | **6.50×** |
| wait=active | 2.07 ±1.10 | 0.79 | 52.5 | 29,676 | 5.67× |
| bind=close+cores | 29.3 ±6.7 | 0.79 | 53.8 | 940,863 | 0.40× |
| bind=spread+cores | 29.7 ±9.3 | 0.79 | 48.3 | 781,791 | 0.40× |
| passive+bind=close | 2.07 ±2.28 | 0.34 | 4.2 | 95 | 5.69× |

**config 12×12×8 (196 PE, 3.06× oversub):**

| knob | sim ms ±sd | sys_frac | busy cores | ivcsw/sim | vs baseline |
|---|--:|--:|--:|--:|--:|
| baseline | 9.83 ±19.8 | 0.79 | 50.0 | 259,950 | 1.00× |
| **wait=passive** | **2.50 ±0.83** | 0.54 | 9.1 | 190 | **3.93×** |
| wait=active | 92.4 ±26.9 | 0.80 | 57.9 | 3,458,555 | 0.11× |
| bind=close+cores | 87.7 ±18.1 | 0.78 | 52.1 | 4,015,998 | 0.11× |
| bind=spread+cores | 75.2 ±12.4 | 0.79 | 50.0 | 3,258,519 | 0.13× |
| passive+bind=close | 2.46 ±0.88 | 0.52 | 5.8 | 365 | 4.00× |

**Finding:** `passive` wins; `active` is catastrophic when heavily oversubscribed (0.11×);
thread pinning (`OMP_PROC_BIND`) hurts (0.11–0.40×). All PASS correctness.

---

## Round 4 — Compute-heavy (`profile_heavy_driver.py`), 10×10×8, active vs passive

| FLOP | ~madds | active ms | passive ms | passive/active | act sys | pas sys | act busy | pas busy |
|--:|--:|--:|--:|--:|--:|--:|--:|--:|
| 0 | 0 | 66.4 | 2.05 | **32.4×** | 0.80 | 0.346 | 53.4 | 6.7 |
| 8,192 | 6.6M | 66.6 | 3.93 | **16.9×** | 0.80 | 0.182 | 54.5 | 11.8 |
| 65,536 | 52M | 82.4 | 9.12 | **9.0×** | 0.78 | 0.046 | 54.2 | 17.5 |
| 262,144 | 210M | 135.7 | 27.2 | **5.0×** | 0.74 | 0.033 | 52.7 | 22.0 |
| 1,048,576 | 839M | 327.8 | 100.2 | **3.27×** | 0.71 | 0.026 | 51.4 | 23.5 |

**Finding:** "compute negligible" holds only near FLOP=0 — as work rises `sys_frac` falls
and `busy` rises (compute dominates). Passive wins at *every* intensity (32×→3.3×, never
hurts); active masks compute while passive reveals it. Active & passive give bit-identical
results (`max_dev=0`, verified with seeded inputs).

---

## Round 5 — Deadlock detection (`deadlock_driver.py`), 20 s kill-timeout

| case | design | outcome |
|---|---|---|
| control | correct: 4 puts / 4 gets | **COMPLETED (1.6 s)** |
| mismatch_get | consumer gets 1 more than produced | **HANG → killed at 20 s** |
| overfill_put | producer overfills depth-2 FIFO | **HANG → killed at 20 s** |
| circular | two kernels each get-before-put | **HANG → killed at 20 s** |

**Finding:** the sim does **not detect** deadlock — it hangs forever (no error, no
diagnostic, no localization); only the correct control completes. (With passive, a hang is
also a *quiet* idle hang — no CPU spike.)

---

## Round 6 — Feedback / cyclic dataflow (`feedback_driver.py`), 15 s kill-timeout

| case | outcome |
|---|---|
| ring2_primed (2-kernel cycle) | **COMPLETED** — got=10=expected, deterministic (10,10,10) |
| ring3_primed (3-kernel cycle) | **COMPLETED** — got=20=expected, deterministic (20,20,20) |
| ring2_unprimed (same cycle, consume-first) | **HANG (deadlock)** — killed at 15 s |

**Finding:** buffered feedback (FIFO cycles) works correctly & deterministically **when
primed**; the same cycle unprimed deadlocks — priming/depth (the design), not the sim,
decides. The extension's genuinely hard case is only **combinational** feedback
(zero-latency wire loops that can't be primed).

---

## One-line summary

The simulator is functionally correct (incl. buffered feedback) but, at realistic array
sizes, spends ~80% of its time in OpenMP futex/scheduling due to default busy-waiting —
recoverable ~4–28× via `OMP_WAIT_POLICY=passive` (measured, then reverted). It does not
model timing, does not detect deadlock (hangs), and its non-blocking outcomes are
scheduler-non-deterministic — the gaps the wire/valid-ready/NB extension must address.
