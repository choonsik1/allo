# final_chip_1x1 — corrected findings (2026-07-23)

## Reading-error correction
Each Vitis cosim prints **two** tb verdicts: (1) the C-simulation phase and (2) the
`Starting C post checking` = **RTL** phase (authoritative). For these dataflow+feedback
chips the C-sim is always the all-zero artifact → always FAIL. Only the RTL verdict counts.
Earlier notes (`RESULT_FP1_hazard.txt`) mis-read the C-sim FAIL as the result — DISREGARD
the "hazard confirmed" claim there.

## Authoritative RTL cosim verdicts (1×1 rtprime, mmm X@W=1.0, prime=6)
| build | scheduling | FP_LAT | RTL cosim |
|---|---|---|---|
| NOSCHED | pipeline_node=False | 1 | **PASS** ✅ (out_s=0x3c00) |
| scheduled II=1 | pipeline_node=True + depfalse + bind_op | 1 | **FAIL** ❌ (out_s=0x0000) |
| scheduled II=1 | same | 3 | **FAIL** ❌ (out_s=0x0000) |

NOSCHED also passes at prime=1 and prime=2 (serial sweep) → tb/prime/1×1 setup all fine.

## Conclusion
- **NOSCHED rtprime 1×1 is correct.** (matches the 8×8 capstone: NOSCHED = 8/8 bit-exact.)
- **Scheduled II=1 rtprime is broken at RTL, independent of FP_LAT** (fails at both 1 and 3).
  So the failure is NOT the FP_LAT>=L stale-forward hazard.
- The proven scheduled II=1 PE `variant_ii1/allo_prj_fwd` (4 cyc/MAC) uses `eva_sb_fwd`
  which has **no systolic-credit plane**; rtprime has one. The breakage is the
  **II=1 pipelining × credit-plane interaction** — suspect: the blanket `dependence=false`
  pragmas (resq/cmpq/res/wb) are unsafe once the credit handshake is loop-carried, and/or
  pipelining collapses the credit round-trip timing.

## Still-valid QoR data points (scheduled build; correctness void)
- node loop achieves II=1 (l_S_t_1_t, II achieved=1).
- csynth Est Fmax ~80 MHz; node-only P&R CP ~4.76 ns post-synth (timing not met @3.33).
  → forcing II=1 on this datapath is expensive AND currently incorrect.

## Open question / next
Why does II=1 break the credit-plane chip? Options: (a) apply dependence=false more
selectively (not on credit-coupled vars), (b) test scheduled rtprime at 4×4 (the validated
size) to see if it's size-independent, (c) accept NOSCHED as the shipped rtprime (correct,
already 8/8) and treat II=1 as an eva_sb_fwd-only (no-credit) result.

## ROOT CAUSE CONFIRMED (dep-false scoping experiments, all @prime=6, RTL cosim)
| build | dep-false | node II | RTL cosim |
|---|---|---|---|
| NOSCHED | none | high | PASS |
| scheduled | resq,cmpq,res,wb | 1 | FAIL |
| scheduled | resq,cmpq only | 1 | FAIL |
| scheduled | none (honored) | **2** | **PASS** |

=> The **resq/cmpq ring dependence=false is the culprit.** Honoring it (II=2) is correct;
asserting it false (II=1) is wrong. res/wb dep-false was a no-op (II stayed 1, still failed).
Root cause: rtprime's retire is **credit-gated** (retire_ok stalls on tx backpressure), so the
resq read distance is NOT a fixed SB_DEPTH-1 -> the dep-false's fixed-cadence promise is violated.
eva_sb_fwd (no credit plane, fixed retire cadence) survives the identical pragma; rtprime doesn't.

## We now HAVE a correct scheduled build: exp1 = prj_prime_1x1_sched_nodep (no dep-false, II=2, RTL PASS).
Fixes for II=1 (make the promise honest): (1) FIFO-buffer pending tx so retire never stalls
[recommended], (2) explicit per-slot committed bit, (3) rotating single-writer result reg.
Open decision: P&R exp1 (II=2) to get real Fmax, THEN decide if II=1+FIFO is worth it (II=1 P&R'd 80MHz).

## FINAL QoR — scheduled II=2 correct rtprime (1x1), post-route Vivado impl
- node_0_0 (PE core): CP 4.462 ns (~224 MHz), 3371 LUT / 2681 FF / 2 DSP, timing not met @3.33
- full-top 1x1:       CP 4.287 ns (~233 MHz), 6037 LUT / 6244 FF / 2 DSP, timing not met @3.33
- II=2, RTL cosim PASS (bit-exact vs X@W). Fmax is II-INDEPENDENT (fp+sub->hold_cnt path ~4.3-4.5ns caps it).
CONCLUSION: II=2 no-dep-false is the honest shippable scheduled point (~233MHz, correct).
FIFO-fix for II=1 would ~2x throughput at same clock/area (retire decoupled from credit => ring
dep-false becomes honest). 300MHz needs re-pipelining the fp/control critical path (separate effort).

## FIFO FIX RESULT (2026-07-24): FAILED — and the retire-cadence root-cause was WRONG
- NOSCHED 1x1 FIFO chip: RTL cosim PASS (0 mismatches) => FIFO edits are functionally CORRECT (not buggy).
- Scheduled II=1 FIFO chip: II=1 achieved, RTL cosim FAIL (out_s=0x0000) => FIFO did NOT fix the dep-false hazard.
=> "credit-gated retire breaks the fixed retire cadence" hypothesis is REFUTED. Removing the retire
   stall (FIFO) changed nothing at II=1. The real cause is NOT the retire stall.
Revised hypothesis: the credit plane's heavier per-iteration logic shifts the II=1 pipeline schedule
so the resq read lands BEFORE the fp write commits (stage-alignment/timing), which dep-false then lies about.
eva_sb_fwd's lighter loop schedules the read after commit; rtprime doesn't.
Remaining II=1 options: (2) explicit per-slot COMMITTED bit on resq (gate forward/retire on it -> timing-
INDEPENDENT, robust) — the one principled attempt left; else accept II=2 (correct, ~233MHz, already P&R'd).
Chip files: eva_sb_syscredit_rtprime_fifo.py (correct NOSCHED), prj_prime_1x1_L120_fifo (NOSCHED, PASS).
