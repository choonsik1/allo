# EVA v3.1 — Channel links + **systolic credit plane DELETED**

`eva_v3_nosyscred.py` — built on `../v3.0_channel/eva_v3_channel.py` (all links already
`Channel[.., valid_ready]`). This version **removes the systolic credit plane entirely**.
The router credit plane (`cr_*`) is deliberately **untouched** — that is the next step.

## Validated (csim, 1×1, 2026-08-03)
| workload | result |
|---|---|
| passthrough ramp | ✅ PASS bit-exact |
| **MMM (real 4-instr program)** | ✅ PASS bit-exact |

Run at `PRIME=1` (see `../v3.0_channel/README.md` — a zero-buffer `Channel` cannot
absorb the deeper priming, and one token per feedback edge is all a handshake needs).

## What changed vs v3.0

| | v2 (`chip/`) | v3.0-channel | **v3.1** |
|---|---|---|---|
| `Stream[` decls | 32 | 0 | 0 |
| `Channel[` decls | 0 | 32 | **24** |
| `scr_*` refs (systolic credit) | 72 | 72 | **0** |
| `cr_*` refs (router credit) | 72 | 72 | 72 (untouched) |
| `sys_*` refs (systolic data) | 64 | 64 | 64 (intact) |
| source lines | — | 1785 | **1659** |

**8 link arrays removed** (4 `scr_*` × base + extended regions).

Deleted: the `scr_e/w/s/n` `Channel` declarations; the `scred` / `sc_r` counters; the
prime puts; the per-iteration `get`s; the end-of-iteration credit returns; the `col_*`
credit-return puts; and the `scred`/`sc_r` entries in `get_scheduled_eva`'s partition
list (those buffers no longer exist).

## The core result — why this works
The systolic credit scheme existed to give the systolic plane a stall-not-drop
handshake ("a registered equivalent of golden EVA's rq/gt handshake"). With
`Channel[.., valid_ready]` the link **already has** a real handshake, so the emulation
is redundant. Established in two checkpointed stages, each regression-tested:

1. **Guards removed** — `if txp_v[k] == 1 and scred[k] > 0:` → `if txp_v[k] == 1:` and
   `elif dcred[r] > 0:` → `else:`. Both workloads still passed ⇒ the credit gating was
   never load-bearing under `valid_ready`.
2. **Links removed** — declarations and all traffic deleted. Both workloads still
   passed ⇒ the plane is genuinely gone, not merely ignored.

Stage 1 alone changes no hardware (dead links still synthesise and still carry a token
per cycle); stage 2 is where the area/wiring win actually lands.

## Not yet done
- **csyn / cosim — no RTL yet.** The area claim is unquantified until then; compare
  `rtl.rpt` register counts against `../1x1_unscheduled/reports/rtl.rpt`.
- Router credit plane (`cr_*`) still present.
- Dead scalar locals (`cret`, `dcred`, `zc`) are intentionally left in the `col_*`/`drv_*`
  kernels: those names are **shared with the router** collectors/drivers (`rclc_*`,
  `rdrv_*`), where they are still live. Removing them globally broke the router twice
  during this work. They are unused scalars in the systolic kernels — no links, no cost
  of consequence — and can be pruned later with per-kernel scoping.

## Reproduce
```bash
CHIP=eva_v3_nosyscred PRIME=1 PRJ=/tmp/v31  MODE=csim python scripts/run_systemc.py
CHIP=eva_v3_nosyscred PRIME=1 PRJ=/tmp/v31m MODE=csim python scripts/run_mmm_systemc.py
```
