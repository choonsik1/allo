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
- **v3.0 (non-blocking / elastic)** — the latency-insensitive redesign of §5, now built: FIFO backpressure
  replaces the credit plane, reads are room-gated non-blocking, routing is by address, and butterflies fire
  on operand tags. Correct for any II by construction.

---

## 2. Decision matrix — the axes and why

| axis | v2.0 (blocking) | v3.0 (non-blocking) | note |
|---|---|---|---|
| flow control | credit plane | FIFO backpressure (elastic) | on the always-fire structure credit does ≥4 jobs; the elastic model replaces all four at once (§5) |
| reads | always-fire, blocking, lossless | room-gated `try_get`, non-blocking | credit-removed-but-still-blocking **drops** data; instruction-gated blocking (demand) **deadlocks** (§4) |
| routing / pairing | by timestep (lockstep) | by address + operand tag | makes correctness independent of arrival *timestep* → any II, fft included |
| schedule | II=2 (fp16) / II=1 (int16) | — | dep-false on the resq/cmpq ring is a read-before-FP-commit **hazard** → not used |
| buffers | BUF_DEPTH=2, HOLD=2 | circular (head/tail) | deep shift-register buffers relax node II → deadlock (§4, `buf4`) |
| prime | runtime `prime_cfg[M,N]` | — | one bitstream runs every workload at its prime; no re-synth |

---

## 3. fft correctness (resolved)

The fft symptom — east-edge rows **2,3,6,7 draining short (≤4/8)**, the "bit-1" middle-butterfly rows —
was for a long time mis-attributed to II=2 pipelining overlap and called "structural." The real cause was a
**shared-core config-before-data hazard**: a pre-config data packet was written back *without* setting
`drf_full`, so a dependent activation read one step ahead. The fix ("Option B") sets `drf_full` on the plain
router writeback — one line, applied to all four chips. **All four now drain 8/8 bit-exact** (rows 2,3,6,7 =
40/40, was 4/8). fft is no longer a holdout.

---

## 4. Version log — every alternative and what it broke on

The v2.0 (credit) chip emerged from this exploration; the dead ends here are exactly why v2.0 is
always-fire + credit, and why v3.0 had to be a full elastic redesign (§5) rather than a strip of v2.0.

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

### Deadlock catalog (Allo-sim, mmm K=2) — the empirical justification
`deadlock_catalog.py` runs every variant through the circular-wait detector. Three clean clusters:

| variant | verdict | detail |
|---|---|---|
| **v2.0 credit** | **PASS** | always-fire + credit |
| wbfwd (honest II=1) | **PASS** | — |
| no_cred / elastic / elastic2 | ALL-ZERO | buffers *drop* when full (credit was the backpressure) |
| guarded / demand / demand2 / demand3 | **DEADLOCK** | on every plane (systolic / router / credit) |
| non-blocking `try_get`/`empty` | **PASS** | the credit-free design that works — the basis of v3.0 |

Pattern: **credit-removed-but-blocking → drops (all-zero); demand/predict-blocking reads → deadlock.**
Only always-fire+credit (blocking, lossless) or full non-blocking (`try_get`/`empty`) works — the two
shipped models.

### 4×4 RTL cosim confirmation (cycle-accurate)
The two failure modes are cycle-accurately **distinct**: credit-removed-but-blocking (`no_cred`/`elastic`)
*completes lossy* (drops data, no hang); demand/predict-blocking (`guarded`) *deadlocks* (200-742). So
neither a lossy strip nor a demand-blocking strip is viable — which is why v3.0 is a proper elastic redesign.

**Through-line:** v2.0 EVA is **latency-sensitive** — pipelining overlap, dep-false, deep shift-buffers, and
credit removal all break the choreographed lockstep. Credit and fixed buffer depths are *tuned* to that
lockstep, not free parameters. v3.0 removes that sensitivity by construction (§5).

---

## 5. The elastic redesign — realized as v3.0

Credit (in v2.0) does ≥4 jobs — (i) backpressure for the lossy internal `hold_v`/`rbuf`, (ii) demand-matched
supply, (iii) operand timing, (iv) breaking a handshake cycle. §4 shows removing it one job at a time trips
over the next, so the non-blocking chip replaces **all four at once**, in two layers:

**Layer A — transport: FIFO backpressure *is* the credit.** Reads become room-gated non-blocking
(`try_get`, never block), internal buffers become blocking-not-lossy (never drop — just don't read), sends
become real-only + blocking (a full downstream FIFO stalls the node). The `scr_`/`cr_` planes disappear; the
stream `full_n`/`empty_n` replace them.

**Layer B — control: addressed routing + operand tagging.** Layer A alone abandons always-fire lockstep, so
the timed shuffle no longer holds (this is why an A-only strip of v2.0 didn't help). So the router forwards
**by address** (XY / dimension-order, using the existing `hd==axis` match), and a butterfly fires when **both
tagged operands of a pair are present**, whenever that is — not "the operand at timestep T."

With A+B, correctness no longer depends on arrival timestep → **any II is correct, fft included, no credit
needed.** This is the shipped **v3.0 non-blocking** design. Practical notes carried over from the bring-up:
use circular-buffer (head/tail) internal buffers to avoid the II-relaxation that deadlocked `buf4`, and
validate small (2×2 → 4×4 → 8×8) rather than jumping to 8×8 csynth.

---

## 6. Open items
- **Scheduled II=1 at 8×8** for the fp16 blocking chip (full-schedule codegen is the intractable >3.5 h job;
  int16 already closes at II=1).
- The **II=1 forwarding-safety invariant** `FP_LAT >= L` (see `BUBBLE_MODEL_PLAN.md` §Status) — the shipped
  `FP_LAT=1` sits on a ~1-stage margin.
