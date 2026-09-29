# EVA 8×8 — Design Rationale & Version Log

*Why the shipped chips are what they are, and what every alternative broke on.* Verdicts are
**RTL cosim** unless marked otherwise (the Allo/OMP simulator is functional-only and can give false
positives; Vitis C-sim is sequential single-pass and drains all-zero for EVA; **RTL cosim is the only
cycle-accurate oracle**). Numbers: [`EVALUATION.md`](EVALUATION.md); reports: [`final_chips/`](final_chips/).

---

## 1. The shipped design — two models × two datatypes

The deliverable is **four chips** on two axes:

| axis | options |
|---|---|
| **flow-control model** | **v2.0 blocking** (always-fire + credit plane) · **v3.0 non-blocking** (elastic / latency-insensitive) |
| **datatype** | fp16 · int16 |

All four are **8/8 bit-exact** on all six workloads and place-and-routed on `xczu7ev-ffvc1156-2-e`.
They span a design spectrum:

- **v2.0 (blocking / credit)** — three overlaid stream planes (systolic `sys_`, router `rtr_`, credit
  `scr_`+`cr_`) in always-fire lockstep: a word on every link every cycle, bubbles when idle. The credit
  plane gives lossless backpressure for the internal 2-deep buffers. This is the faithful reproduction of
  the original EVA execution model. int16 closes the recurrence at **II=1**; fp16 at **II=2** (FPU recurrence).
- **v3.0 (non-blocking / elastic)** — the latency-insensitive redesign of §3, now built: FIFO backpressure
  replaces the credit plane, reads are room-gated non-blocking, routing is by address, and butterflies fire
  on operand tags. Correct for any II by construction.

---

## 2. Decision matrix — the axes and why

| axis | v2.0 (blocking) | v3.0 (non-blocking) | note |
|---|---|---|---|
| flow control | credit plane | FIFO backpressure (elastic) | on the always-fire structure credit does ≥4 jobs; the elastic model replaces all four at once (§3) |
| reads | always-fire, blocking, lossless | room-gated `try_get`, non-blocking | credit-removed-but-still-blocking **drops** data; instruction-gated blocking (demand) **deadlocks** |
| routing / pairing | by timestep (lockstep) | by address + operand tag | makes correctness independent of arrival *timestep* → any II |
| schedule | II=2 (fp16) / II=1 (int16) | — | dep-false on the resq/cmpq ring is a read-before-FP-commit **hazard** → not used |
| buffers | BUF_DEPTH=2, HOLD=2 | circular (head/tail) | deep shift-register buffers relax node II → deadlock (`buf4`) |
| prime | runtime `prime_cfg[M,N]` | — | one bitstream runs every workload at its prime; no re-synth |

**What the alternatives proved (the empirical justification).** Stripping the credit plane one job at a
time always tripped over the next: **credit-removed-but-still-blocking drops data** (buffers are lossy —
all-zero output), while **instruction-gated (demand) blocking reads deadlock** on every plane (a producer's
real `put` has no consumer `get` when timing drifts from the assumed schedule → circular wait). This is why
only two models work — **always-fire + credit (v2.0)**, which is lossless and deadlock-free but
latency-sensitive; and **full non-blocking (v3.0)**, which removes that sensitivity by construction (§3).
Both were confirmed cycle-accurately at 4×4 RTL cosim (lossy strips *complete* dropping data; demand strips
*deadlock*, 200-742). Full version log + deadlock catalog: [`../archive/VERSION_LOG.md`](../archive/VERSION_LOG.md).

---

## 3. The elastic redesign — realized as v3.0

Credit (in v2.0) does ≥4 jobs — (i) backpressure for the lossy internal `hold_v`/`rbuf`, (ii) demand-matched
supply, (iii) operand timing, (iv) breaking a handshake cycle. Because removing it one job at a time trips
over the next (§2), the non-blocking chip replaces **all four at once**, in two layers:

**Layer A — transport: FIFO backpressure *is* the credit.** Reads become room-gated non-blocking
(`try_get`, never block), internal buffers become blocking-not-lossy (never drop — just don't read), sends
become real-only + blocking (a full downstream FIFO stalls the node). The `scr_`/`cr_` planes disappear; the
stream `full_n`/`empty_n` replace them.

**Layer B — control: addressed routing + operand tagging.** Layer A alone abandons always-fire lockstep, so
the timed shuffle no longer holds (a Layer-A-only strip of v2.0 didn't help). So the router forwards **by
address** (XY / dimension-order, using the existing `hd==axis` match), and a butterfly fires when **both
tagged operands of a pair are present**, whenever that is — not "the operand at timestep T."

With A+B, correctness no longer depends on arrival timestep → **any II is correct, no credit needed.** This
is the shipped **v3.0 non-blocking** design. Practical notes from the bring-up: use circular-buffer
(head/tail) internal buffers to avoid the II-relaxation that deadlocked `buf4`, and validate small
(2×2 → 4×4 → 8×8) rather than jumping to 8×8 csynth.

---

## 4. Open items
- **Scheduled II=1 at 8×8** for the fp16 blocking chip (full-schedule codegen is the intractable >3.5 h job;
  int16 already closes at II=1).
- The **II=1 forwarding-safety invariant** `FP_LAT >= L` (see `BUBBLE_MODEL_PLAN.md` §Status) — the shipped
  `FP_LAT=1` sits on a ~1-stage margin.
