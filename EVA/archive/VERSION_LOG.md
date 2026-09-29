# EVA — full version log & deadlock catalog (archive)

The detailed provenance behind the two shipped models — see [`../results/DESIGN_RATIONALE.md`](../results/DESIGN_RATIONALE.md)
for the current rationale. Verdicts are **RTL cosim** unless marked (Allo/OMP simulator = functional-only;
Vitis C-sim = sequential single-pass, all-zero for EVA). The dead ends here are why v2.0 is always-fire +
credit, and why v3.0 had to be a full elastic redesign rather than a strip of v2.0.

## Version log — every alternative and what it broke on

| version | change | verdict | root cause |
|---|---|---|---|
| **v2.0 credit (rtprime line)** | always-fire + credit, runtime prime | mmm+cordic 8/8, fft 8/8 (Option B) | the shipped blocking model |
| NOSCHED | no pipeline pragmas | all 6 = 8/8 | correct but unpipelined (II≈5) |
| II=1 dep-false (naive) | dep-false on resq/cmpq | **wrong results** | read-before-FP-commit hazard |
| II=1 honest (`wbfwd`, FWD=0) | deeper SB/RESQ, FWD=0 | mmm 8/8 | honest II=1, no worthwhile Fmax gain |
| **no_cred** | strip `scr_`, unconditional send | K1 pass, **K2+ all-zero** | credit protected the lossy `hold_v` (drops, not blocks) |
| guarded / elastic / elastic2 | demand read / full-empty guards | **deadlock / all-zero** | always-fire sender floods a demand reader |
| demand / demand2 / demand3 | real-only send + n_in/n_out bounds | **deadlock / computes 0** | credit also = demand-matched supply + operand timing |
| **buf4** | `BUF_DEPTH 2→4` (shift-register) | **cosim DEADLOCK (200-742)** | deep shift-register relaxes II → desync |
| **nocred_deep** | strip `scr_` + deep buffers | **RTL HANG** | always-fire get/put closes a combinational ring credit was breaking |
| int16 | IS_FLOAT dual-type | honest 1-cyc II=1 | the int16 datatype track |

## Deadlock catalog (Allo-sim, mmm K=2)

`deadlock_catalog.py` runs every variant through the circular-wait detector. Three clean clusters:

| variant | verdict | detail |
|---|---|---|
| **v2.0 credit** | **PASS** | always-fire + credit |
| wbfwd (honest II=1) | **PASS** | — |
| no_cred / elastic / elastic2 | ALL-ZERO | buffers *drop* when full (credit was the backpressure) |
| guarded / demand / demand2 / demand3 | **DEADLOCK** | on every plane (systolic / router / credit) |
| non-blocking `try_get`/`empty` | **PASS** | the credit-free design that works — the basis of v3.0 |

Pattern: **credit-removed-but-blocking → drops (all-zero); demand/predict-blocking reads → deadlock.**
Only always-fire+credit (blocking, lossless) or full non-blocking (`try_get`/`empty`) works.

## 4×4 RTL cosim confirmation (cycle-accurate)

The two failure modes are cycle-accurately **distinct**: credit-removed-but-blocking (`no_cred`/`elastic`)
*completes lossy* (drops data, no hang); demand/predict-blocking (`guarded`) *deadlocks* (200-742). So
neither a lossy strip nor a demand-blocking strip is viable — which is why v3.0 is a proper elastic redesign.

### Why instruction-gated blocking reads deadlock
The instruction says *which* dir to read, not *when* it arrives; when actual timing drifts from the
program's assumed schedule, a producer's real `put` has no consumer `get` (the consumer isn't at a reading
instruction) → the FIFO fills → the put blocks → every PE in the producer↔consumer ring blocks → circular
wait. Bubbles (always-fire) were the escape hatch — advance past a not-yet-arrived input; demand-blocking
removes it. This is the specific reason v3.0 uses non-blocking `try_get`/`empty` (check FIFO state) rather
than blocking demand reads.

## Through-line

v2.0 EVA is **latency-sensitive** — pipelining overlap, dep-false, deep shift-buffers, and credit removal
all break the choreographed lockstep. Credit and fixed buffer depths are *tuned* to that lockstep, not free
parameters. v3.0 removes that sensitivity by construction (addressed routing + operand tagging).
