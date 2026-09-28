# EVA-in-Allo — current state (2026-07-23)

## The chips that matter (sources of truth)
| chip | file | what it is | II | correctness |
|---|---|---|---|---|
| **rtprime** (FINAL / capstone) | `scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime.py` | one-bitstream, runtime `prime_cfg` | **NOT II=1** (built NOSCHED) | 8/8 bit-exact all workloads |
| **syscredit_fwd** | `final_runs/eva_sb_syscredit_fwd.py` | forwarding + credit plane, per-workload | II=1 *when scheduled* | golden 8/8 |
| **syscredit_1x1** (the real II=1 QoR) | `scoreboard_allo_eva_final/final_final/syscredit_1x1/` | scheduled 1×1 forwarding | **II=1, ~229 MHz** (csynth+P&R) | MAC bit-exact |

The **forwarding gate is byte-identical** between `fwd` and `rtprime` (verified) — only the runtime `prime_cfg` port differs.

## Two facts to stop the confusion
1. **The FINAL rtprime chip is NOSCHED → not II=1.** Its P&R (2.924 ns / ~342 MHz) is the NOSCHED "Fmax mirage" (short per-cycle path, but node loops report `Pipelined: no`, II = latency). Correctness (8/8, streaming lossless) is real; the II=1 timing is *not* on this build.
2. **The only real II=1 builds are the SCHEDULED forwarding chip** (`syscredit_1x1` = II=1 ~229 MHz; `allo_prj_fwd_4x4` = 4×4 II=1). A scheduled **II=1 rtprime at 8×8 has never been built** (full-schedule codegen is the intractable >3.5 h job).

## The FP_LAT correctness invariant (open thesis point)
For any **II=1 (dep-false) build**, the operand-forwarding read `a = resq[fwd_a_ix]` is gated only by `inflight >= FP_LAT` (gate at `eva_sb_syscredit_fwd.py:350-354`). The `resq` slot isn't committed until the fp-op latency `L` cycles after issue. So the safety condition is **`FP_LAT >= L`** (minus a ~1-stage scan offset). The shipped `FP_LAT=1` with `L=3` (bind_op, clamped — see `syscredit_1x1/reports/node_csynth.rpt`: `hmul/hadd/hsub_..._3`) lives on that offset margin. Default binding (`L=4-5`) widens the gap. The dep-false pragma's own justification comment only covers the *retire* read (distance `SB_DEPTH-1=4`), NOT the *forward* read (distance `FP_LAT`) — that's the gap.
- NOSCHED builds dodge it entirely (no pipeline overlap → world-1 holds in RTL).

## OPEN / next
- Build the **scheduled II=1 rtprime** (`CHIP=eva_sb_syscredit_rtprime`, `TB=tb_replay_golden_prime.cpp`, `SCHED=1` in `build_golden_cosim.py`) to answer "does the FINAL chip pipeline at II=1, and does FP_LAT=1 stay bit-exact or forward stale?" — start at 4×4 (tractable), then 8×8.
- Variant C (`inject_depfalse.py`) + variant D (FP_LAT=3) = the hazard vs safe A/B.

## Archive
`_archive_20260723/` — 50 regenerable `prj_*` build dirs, 7 `variant_ii1` kernels (incl. `allo_prj_fp1/2/3`, `allo_prj_fwd`, `allo_prj_fwd_4x4`), and killed/botched session logs. See its `MANIFEST.txt`. All regenerable; nothing there is a source of truth.
