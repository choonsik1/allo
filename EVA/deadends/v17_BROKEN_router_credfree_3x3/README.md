# v17 — router credit plane removed (`CHIP=eva_v17`)

**Status: DOES NOT WORK past 2×2 — but it synthesizes, and the failure is precisely
localized.** Derived from `v16_VERIFIED_credfree_uniform` on 2026-08-13.

| mesh | 1×1 | 2×2 | 3×3 | 4×4 | 6×6 | 8×8 |
|---|---|---|---|---|---|---|
| **v16** (control) | PASS | PASS | PASS | PASS | PASS | PASS |
| **v17** | PASS | PASS | **FAIL** | FAIL | FAIL | FAIL |

- **1×1 `csyn` rc=0** — compiles clean, no CIN-150. The transformation is structurally valid.
- 8×8, all six workloads: `0/8 rows clean`, **every output `0x0`**, run terminates (not a
  hang). The program never lands, so nothing executes.

### The discriminator is TWO FORWARDING HOPS
This router routes in **straight lines along an axis** — a packet from the west either
matches `col_id` and is delivered, or continues east; it never turns. So in a 2×2 a packet
is forwarded **at most once** (enters column 0, must land at column 1). **3×3 is the first
mesh in which a packet transits an intermediate node** — forwarded by one node, then
forwarded again by the next. That is what the 2×2→3×3 boundary isolates; it is not mesh
size, "interior nodes", or gradual capacity exhaustion.

**❌ NOT a capacity problem — disproved, do not re-run.** `BUF_DEPTH` 2 → 4 → 8 fails at
3×3 identically; v16 at `BUF_DEPTH=4` passes 2×2/3×3/4×4, so the constant is live. The
obvious suspect (the deferred pop halves effective buffering, since an ungranted packet
holds both the egress register and its `rbuf` head while the relocated RX lags egress by a
cycle) is therefore **wrong** — quadrupling the buffer changes nothing. The failure is
**structural**. Same shape as v7/v8 for the systolic plane.

**Next step:** per-direction counters comparing **2×2 (passing) vs 3×3 (failing)** under
identical instrumentation — the method that cracked v13. Does the transit node receive the
packet and fail to forward it, or never receive it?

## What it changes
v16 removed the **systolic** credit plane. v17 removes the **router** one — the last
credit plane in the design. That plane is worth attacking because it is *both*
remaining costs at once:

- the residual **~12 % area** after v16's −10.8 %
- the **actual critical path** in v3.0 *and* v16 — identical in both:
  `rclc_s_0:run/reg(...Push()...)` → `l_S_t_1_t79`, the router credit return.
  v16 did not move timing at all (−0.3388 ns in both), because the systolic plane was
  never on the path. This is the plane that is.

## How — the same three mechanisms that made v16 work
Nothing here is new; it is v13 + v15 + v16 applied to the router.

| mechanism | where | v16 precedent |
|---|---|---|
| **RX gated on room**, via `try_get` under `rbcnt[d] < BUF_DEPTH` | node | v13 RX gate on `hold_cnt < 2` |
| **receive AFTER the drain** — RX moved to the loop bottom, past the END-PUT | node | v11/v13 receive-after-drain |
| **retain until granted** — egress `try_put`; `op_v[o]` holds an ungranted packet and its source buffer pops only on grant | node | v15 TX retain |
| **rq/gt at the injection edge** — `rdrv_*` advance `sp` only on grant | 4 drivers × 2 regions | v15's edge fix |
| **one write primitive per channel** — every `rtr_*` writer is `try_put` | everywhere | v16 uniform PushNB (CIN-150) |

The decisive difference from the **v3.2 dead end**, which also deleted this plane: v3.2
`get()`-ed unconditionally and then discarded when the buffer was full — a **silent
drop**. Credits were the only thing making that path unreachable. Here the packet is
never accepted unless there is room for it.

## Deferred pop — the one genuinely new detail
With credits, `rcred[o] > 0` guaranteed the downstream had room, so a forwarded packet
could be popped from `rbuf` in the same cycle it was selected. Without them the grant is
not known until the END-PUT, so the pop is **deferred to the grant**:

```python
ge = rtr_e[i, j + 1].try_put(oe_r)
if ge == 1 and op_v[0] == 1:
    op_v[0] = 0
    if op_s[0] >= 0:            # -1 = core injection, nothing to pop
        for sfe in range(BUF_DEPTH - 1): rbuf[0, sfe] = rbuf[0, sfe + 1]
        rbcnt[0] -= 1
```
An ungranted packet therefore sits in **both** `oe_r` and `rbuf` — deliberately. It is
re-offered every cycle and cannot be lost. Local delivery (`crv_in`) still pops
immediately: a packet consumed by this node has no downstream to refuse it.

`op_s[o]` is always either `-1` or `o` (forwarding is straight-through, buffer `o` →
port `o`), so the double-pop case cannot arise: a head pending on port `o` had
`hit[o] == 0`, and local delivery only takes heads with `hit == 1`.

## Deliberately NOT changed
`col_*` and `drv_*` still carry the dead `cret` / `dcred` declarations v16 left behind.
Removing them here would make a v16↔v17 area comparison confound two variables. They are
write-only, so Catapult eliminates them regardless.

## Test ladder (in order — each is cheap and kills the next if it fails)
1. `csyn_probe.py` at 1×1 — does it compile at all (CIN-150)?
2. 4×4 MMM csim — the cheapest correctness signal
3. 8×8 **all six** workloads at REPS=8 with `LFORCE=1400` — cordic is the discriminator;
   fft and mmm alone do not distinguish a working router from a broken one
4. only then an 8×8 csyn for the area and, critically, **the critical path**
