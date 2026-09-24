# deadends/ — documented negatives

Sixteen chip variants that **do not work**, kept as evidence so the same ideas are not
retried. Each folder name states its failure mode. None of these should be used for
anything except reproducing the failure it documents.

They are still importable — all 7 drivers in `../scripts/` scan `v[0-9]*` **and**
`deadends/v[0-9]*` — so `CHIP=eva_v13 … python scripts/run_golden_systemc.py` still runs.
Module names are unchanged from when each was live.

## The credit-removal ladder (why the systolic plane was hard to remove)
| folder | module | what it proved |
|---|---|---|
| `v3.1_BROKEN_nosyscred_silentdrop` | `eva_v3_nosyscred` | systolic credits deleted → node `get()`s unconditionally then discards when the hold is full. **Silent drop.** |
| `v3.2_BROKEN_nocred_silentdrop` | `eva_v3_nocred` | both planes deleted. −63 % area at 1×1 (54,890) and **wrong** — the number that made removal look attractive |
| `v3.3_BROKEN_nocred_ts` | `eva_v3_nocred_ts` | v3.2 + timestamps; used for the 8×8 synthesis-cost probe only |
| `v3.4_BROKEN_blockingget_deadlock` | `eva_v3_bp` | gated **blocking** `get()` → deadlock |
| `v3.5_BROKEN_tryget_livelock` | `eva_v3_nb2` | gated `try_get()` → livelock |
| `v10_BROKEN_8x8_deadlock` | `eva_v10` | minimal `sync_register` rules. 4×4 green, **8×8 deadlock** |
| `v11_BROKEN_rxorder_partial` | `eva_v11` | + receive-after-drain. Necessary, **not sufficient** |
| `v13_BROKEN_halfout_deadlock` | `eva_v13` | ⚠️ **looked solved** on 4×4 MMM + 8×8 fft REPS=2. Actually emits **half** the cordic outputs and deadlocks at MARGIN=6000 — and cannot synthesize (CIN-150). See the main README |
| `v13_BROKEN_halfout_ts` | `eva_v13_ts` | v13 + timestamps; the stamps that disproved the truncation theory |

**What was missing:** backpressure at the **injection edge** — the driver→node[r,0] link
that the node's RX gate does not govern. Fixed in `../v15_OK_edgebp_nosynth/`, made
synthesizable in `../v16_VERIFIED_credfree_uniform/`.

## Always-fire / elastic attempts
| folder | module | what it proved |
|---|---|---|
| `v4_BROKEN_nofire_4xslower` | `eva_v4` | bubbles removed. 1×1 passes, **all-zero at 8×8**, costs 4× throughput |
| `v5_BROKEN_elastic` | `eva_v5` | elastic links |
| `v6_BROKEN_syselastic_allzero` | `eva_v6` | systolic-only elastic; csim **and** RTL cosim both all-zero (they agreed — csim was not the weak link) |
| `v7_BROKEN_txq2_capacity`, `v8_BROKEN_deepq_capacity` | `eva_v7`, `eva_v8` | deeper TX queues. Fail identically to depth 2 ⇒ **not a capacity problem** |

## Not failures
| folder | module | why it is here |
|---|---|---|
| `v9_ISOLATION_txretain_only` | `eva_v9` | deliberate one-variable isolation: TX retention only, always-fire and primes untouched. Reproduced v3.2 exactly ⇒ TX plumbing sound ⇒ **the fault was RX**. The method that cracked it — change one thing at a time |
| `v3.0_EMPTY_nonblocking_neverstarted` | `eva_v3_nb` | never started; empty of work |

## Two rules these cost us
1. **A variant is not verified until all six workloads pass at REPS=8 and it
   synthesizes.** fft and mmm do not discriminate; cordic exposes injection-edge faults.
   v13 passed the narrow test and was wrong in three separate ways.
2. **Keep always-fire and the primes.** Several attempts here failed only because they
   removed one of those too.
