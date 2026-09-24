# EVA v3.2 — Channel links, **BOTH credit planes deleted**

`eva_v3_nocred.py` — built on `../v3.1_channel_nosyscred/` (systolic credits already
gone). This version also removes the **router** credit plane (`cr_*`, `rcred`).
Both data planes (`sys_*`, `rtr_*`) are intact.

## Validated (csim, 1×1, `PRIME=1`, 2026-08-03)
| workload | result |
|---|---|
| passthrough ramp | ✅ PASS bit-exact |
| **MMM (real 4-instr program)** | ✅ PASS bit-exact |

## The measured effect — emitted SystemC
| version | lines | `SC_MODULE` | **`Connections`** |
|---|---|---|---|
| v2 `eva_sb_syscredit_rtprime` (Stream) | 4767 | 22 | **274** |
| v3.0 `eva_v3_channel` (Channel) | 4447 | 22 | 242 |
| v3.1 `eva_v3_nosyscred` | 4103 | 22 | 202 |
| **v3.2 `eva_v3_nocred`** | **3804** | 22 | **162** |

**274 → 162 MatchLib `Connections`: −41%.** Source is −20% (4767 → 3804 lines).
Module count is unchanged (22) — the *structure* is the same chip; what disappeared is
link plumbing, not kernels.

Note v2 → v3.0 alone drops 32 `Connections` (274 → 242) purely from `Stream` →
`Channel`: a `Stream` emits FIFO plumbing that a zero-buffer handshake does not need.

| | v2 | v3.0 | v3.1 | **v3.2** |
|---|---|---|---|---|
| `Stream[` / `Channel[` decls | 32 / 0 | 0 / 32 | 0 / 24 | **0 / 16** |
| `scr_*` systolic credit | 72 | 72 | 0 | 0 |
| `cr_*` router credit | 72 | 72 | 72 | **0** |
| `sys_*`, `rtr_*` data | 64, 64 | 64, 64 | 64, 64 | 64, 64 |

## Why it works
Both credit planes existed to emulate a stall-not-drop handshake over buffered
`Stream`s. `Channel[.., valid_ready]` *is* that handshake, so the emulation is
redundant. Removed in two checkpointed stages, each regression-tested on both
workloads — guards first (proves the gating is not load-bearing), then the links
(proves the plane is gone rather than merely ignored):

```python
# node router arbitration -- the `if rcred[o] > 0:` wrapper dropped, body dedented
for o in range(4):
    if idir == o:                                  # was nested under the credit guard
        o_out[o] = csd_pkt; inj_done = 1
    elif hvld[o] == 1 and hit[o] == 0:
        o_out[o] = hd[o]; pop[o] = 1
```

## ⚠️ Caveats
- **csim only — still no RTL for any v3 variant.** `Connections` count is a good proxy
  but the real number is registers/area from `rtl.rpt`. Until a csyn run, the area win
  is inferred, not measured.
- **Only validated at 1×1 on two workloads.** Credits matter most under contention
  (multiple nodes competing for a link); a 1×1 mesh barely exercises that. **An 8×8 run
  with the fft/cordic golden replays is the real test** and may well expose a case where
  the handshake alone deadlocks where credits did not.
- `PRIME=1` required (see `../v3.0_channel/README.md`).
- Dead scalar locals (`cret`, `dcred`, `zc`) remain in `col_*`/`drv_*`/`rclc_*`/`rdrv_*`.
  Harmless (scalars, no links). They were left deliberately — those names are shared
  across systolic and router kernels and removing them globally broke the router twice.
- The always-fire/bubble model is **unchanged**: the node still does 4 unconditional
  blocking `get()`s per iteration and `for t in range(NSTEP)` is still a cycle counter.
  Removing that is the non-blocking rework (`v4`), and it would end cycle-level
  correspondence with golden EVA.

## Reproduce
```bash
CHIP=eva_v3_nocred PRIME=1 PRJ=/tmp/v32  MODE=csim python scripts/run_systemc.py
CHIP=eva_v3_nocred PRIME=1 PRJ=/tmp/v32m MODE=csim python scripts/run_mmm_systemc.py
```
