# v18 — non-blocking router credits (`CHIP=eva_v18`)

**Status: CORRECT but NO SPEEDUP.** Keep as a documented negative + a clean base.

v16 with the node's 8 router-credit channel ops converted from blocking `put`/`get` to
`try_put`/`try_get`. Credit **semantics are unchanged** — credits are additive, so a
missed `try_get` only defers an increment, and a refused `try_put` accumulates in `cq_*`
and retries (sending the running sum == sending each increment, since the receiver `+=`s).
Primes converted to `try_put` for one-primitive-per-channel (CIN-150).

## Correct everywhere — unlike v17
| mesh | 1×1 | 2×2 | 3×3 | 4×4 | 8×8 |
|---|---|---|---|---|---|
| v18 MMM csim | PASS | PASS | PASS | PASS | PASS |

3×3 is where `v17` (router credits *removed*) died. Changing credit **transport** while
keeping credit **semantics** is safe; removing the backpressure guarantee is not.

## ❌ Zero effect on RTL cycles — the hypothesis was WRONG
Exact single-run cycle counts, identical workload/NSTEP:

| mesh | NSTEP | v16 | **v18** |
|---|---|---|---|
| 1×1 | 234 | 1430 | **1430** |
| 2×2 | 250 | 2510 | **2510** |
| 4×4 | 282 | 5054 | **5054** |

Identical **to the cycle**. The premise — that the node loop's 16 blocking handshakes
serialize and set the ~17.7 cyc/iter — is false. Halving them changes nothing.

## What the cycle data actually says
| mesh | 1×1 | 2×2 | 4×4 | 8×8 |
|---|---|---|---|---|
| cyc/iter | 6.11 | 10.04 | 17.92 | 17.70 |

Rises with mesh, then **saturates at ~18 by 4×4**. Handshake count is identical at every
mesh, so op count is not the driver; blocking-vs-non-blocking is not either.

**Working hypothesis:** the limiter is a **dependency cycle between neighbouring nodes** —
a node's `Pop` cannot complete until its neighbour's body has run far enough to `Push`, so
the steady-state period is set by the node body's scheduled length once the mesh is large
enough to close a cycle. At 1×1 there are no neighbours (drivers/collectors are always
ready), so the body gates nothing — which is why 1×1 reads 6.11 and **cannot discriminate**.

⚠️ **Never benchmark a mesh-coupling change at 1×1.** It cost this experiment, and it is
the same blind spot that made the II=1 pragma look useless (also only tested at 1×1).
