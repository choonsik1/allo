# EVA v3.0-channel — `Stream` → `Channel[.., valid_ready]`

`eva_v3_channel.py` — copy of `chip/eva_sb_syscredit_rtprime.py` with all **32** link
declarations swapped from `Stream[T, STREAM_DEPTH]` to `Channel[T, valid_ready]`.
Zero buffering, handshake preserved. `put`/`get` call sites unchanged (240 of them).

Credit planes are still present and unchanged — that is the *next* version.

## Validated (csim, 1×1, 2026-08-03)
| workload | PRIME=0 | PRIME=1 | PRIME=2 | PRIME=6 |
|---|---|---|---|---|
| passthrough ramp | ✅ PASS | ✅ PASS | ✅ PASS | ❌ all zeros |
| **MMM (real 4-instr program)** | ✅ **PASS** | ✅ **PASS** | — | ❌ all zeros |

A v2 control (`CHIP=eva_sb_syscredit_rtprime`) was run through the same refactored
driver and passes, so the driver changes are not confounding the result.

## ⚠️ PRIME must be ≤ 2 (was 6)
The node primes every link before its main loop:

```python
for _pt in range(pcfg[i, j] - 1):      # pcfg = PRIME_TOKENS (runtime input)
    rtr_e[...].put(zpkt);  sys_e[...].put(zsys);  cr_e[...].put(zcr);  ...
# then one UNCONDITIONAL "NECESSARY PRIME" put per link
```

With `Stream[.., 8]` those tokens sit in the FIFO. A zero-buffer `Channel` `put`
cannot retire without a matching `get`, and during priming nobody is getting yet —
so the extra tokens never land and every output reads back zero.

`PRIME=0` and `PRIME=1` are equivalent (`range(pcfg-1)` is empty for both): the
**unconditional** prime block still supplies exactly one token per feedback edge,
which is all a handshake link needs to break the read-before-write cycle.

**Side result worth keeping:** the Vitis `golden_testbenches` README reports MMM needs
PRIME=6 and fft/cordic need PRIME=1, calling priming "drain-direction-dependent". On
the Channel chip **MMM passes at PRIME=1** — the handshake supplies the ordering that
deeper priming was compensating for.

## Not yet done
- csyn / cosim (no RTL yet). Prior art (`allo_sup/agents/noc/FINDINGS_wire_channel.md`
  §5) measured **1325 → 1188 register bits, ~10% fewer** for Channel vs Stream on a
  small controlled design; worth confirming here against the `1x1_unscheduled` baseline.
- Credit-plane removal → see the `v3.1_*` folder.

## Why `Channel` and not `Wire`
`Wire` (combinational, no handshake) **fails csim** — a controlled 4-variant experiment
(`agents/noc/pe_split.py`) shows `mono`/`stream`/`channel` PASS and `wire` FAIL (all
zeros), because nothing aligns two SC_THREADs without a handshake. `Wire` still
*synthesises* to RTL, so it yields a design that is synthesisable but un-simulatable —
i.e. unverifiable. The buffer was never what made `Stream` correct; the handshake was.

## Reproduce
```bash
CHIP=eva_v3_channel PRIME=1 PRJ=/tmp/v3ch MODE=csim python scripts/run_systemc.py
CHIP=eva_v3_channel PRIME=1 PRJ=/tmp/v3mmm MODE=csim python scripts/run_mmm_systemc.py
```
