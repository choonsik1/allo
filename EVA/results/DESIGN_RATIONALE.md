# EVA 8×8 — Design Rationale, Version Log, and Credit-Free Sketch

*Why the credit-based, runtime-prime, II=2 scoreboard chip is the final design — and what every
alternative broke on.* Verdicts below are **RTL cosim** unless marked otherwise (Allo/OMP simulator
= functional only, can give false positives; Vitis C-sim = sequential single-pass, all-zero for EVA;
**RTL cosim is the only cycle-accurate oracle**).

---

## 1. The final design

**Chip:** `prime/eva_sb_syscredit_rtprime.py` — data-driven scoreboard PE in an 8×8 mesh, three
overlaid stream planes (systolic `sys_`, router `rtr_`, credit `scr_`+`cr_`), runtime `prime_cfg[M,N]`.
**Schedule:** NOSCHED kernel + `inject_pragmas_ii2.py` (pipeline II=1 request + array_partition +
bind_op, **no** dep-false ⇒ HLS honors the scoreboard recurrence ⇒ **II=2**).

**Verified results:**
| build | mmm | cordic ×4 | fft | notes |
|---|---|---|---|---|
| **NOSCHED** (`one_bitstream/`) | ✅ 8/8 (p6) | ✅ 8/8 (p1) | ✅ 8/8 (p1) | correct, unpipelined |
| **Scheduled II=2** (`sched8x8_ii2/` + prime sweep) | ✅ 8/8 (p6) | ✅ 8/8 (**p3**) | ❌ ≤4/8 any prime | fft is the lone holdout |
| **II=2 P&R** (`final_chip_1x1/ii2/`) | — | — | — | full 1×1 top **4.287 ns ≈ 233 MHz** (csynth est was ~80 MHz) |

**One-line justification:** it is the only build that (a) runs the whole shipped suite bit-exact from a
single runtime-programmable bitstream (NOSCHED), (b) has a correct *pipelined* point at ~233 MHz for the
latency-tolerant workloads (mmm + cordic), and (c) survived every alternative below.

---

## 2. Decision matrix (the axes, and why each was chosen)

| axis | chosen | rejected alternative | reason |
|---|---|---|---|
| flow control | **credit plane** | credit-free / elastic | credit does ≥4 jobs; every credit-strip broke (§4). Credit-free = a *different architecture* (§5). |
| schedule | **II=2 (no dep-false)** | II=1 dep-false | dep-false on the resq/cmpq ring = read-before-FP-commit **hazard** (wrong results). |
| schedule | **II=2** | honest II=1 (`wbfwd`, FWD=0) | II=1 needs FWD=0 + dep-false; passes mmm but same fft holdout, no worthwhile Fmax gain. |
| correctness fallback | **NOSCHED** for full suite | II=2 for everything | fft fails under any pipelining overlap (§3). NOSCHED = correct, II=2 = throughput for the workloads that tolerate it. |
| prime | **runtime `prime_cfg`** | compile-time `PRIME_TOKENS` (`fwd_cosim`) | one bitstream runs mmm(p6)+fft/cordic(p1); no re-synth per workload. |
| buffers | **BUF_DEPTH=2, HOLD depth 2** | deeper buffers | deepening (shift-register) relaxes node II → deadlock (§4). |
| datatype | float16 (int16 variant exists) | — | int16 = honest 1-cyc II=1; kept as a separate track (`eva_int16/`). |

---

## 3. The fft holdout — why II=2 breaks it (fully characterized)

**Symptom (waveform-verified on the real II=2 RTL, prime=3):** east-edge drain per row —
rows 0,1,4,5 = 2/2 words; rows **2,3,6,7 = 0–1/2**; 9/16 total. The failing rows = **bit-1-set** =
the middle FFT butterfly (shuffle keyed on bit-1). Failure is **"never," not "late"** (0 words at
L=2000).

**Root cause (schedule numbers + router waveform):**
- node loop: **iteration latency = 5 cycles, II achieved = 2 ⇒ 3 cycles of overlap.** That overlap is a
  node reading timestep *t+1* before it has committed the writes of timestep *t* — the lockstep violation.
- The overlap desyncs the multiple feedback loops (data / credit / cross-row shuffle), which have
  **different hop-counts**, so they drift by *different* amounts (non-uniform).
- Router drill (waveform): failing node_2_7 receives **36 valid router packets** vs passing node_4_7's
  **60** — a 40% shortfall, with equal total dequeues (3200 each). So it's **not** backpressure or an
  `rbuf` drop — the operands are **never delivered**; the loss is **upstream in the shuffle**.

**Why no global knob fixes it:** prime (uniform offset), a per-node latency pragma (nodes already
uniform; can't beat the 5-cycle datapath), and deeper buffers/credits are all *uniform* — they can't
re-align loops that drifted by *different* amounts. Confirmed: prime sweep never > 4/8; the schedule
arithmetic (latency 5 > II 2) proves you can't have II=2 *and* zero overlap.

**Streaming / batching — DOES NOT fix II=2 (clean isolation, verified 2026-07-30).**
Controlled A/B: **same chip (`fwd_cosim`), same stream tb (`tb_replay_golden_stream`), same B=20
vectors — only the pragmas differ:**
| chip | single-shot fft | streaming B=20 (stream tb) |
|---|---|---|
| NOSCHED | 8/8 | **8/8** |
| **II=2** (+inject_pragmas) | 4/8 | **DEADLOCK (200-742)** |
So II=2 breaks fft **both** ways; streaming makes it **worse** (deadlock), not better. The earlier
"8/8 streaming" was **NOSCHED being NOSCHED** (no overlap to break). Adding the II=2 overlap +
continuous multi-activation load → credit plane can't hold >1 activation in flight under shifted
timing → deadlock (same family as `buf4`/`ncdts`). The rtprime **5/8** run was a false lead: driven by
the *single-shot* prime tb, which doesn't sustain continuous load — never truly streamed. **Verdict:
NOSCHED is the only fft-correct chip; streaming is NOT a schedule fix for II=2.** Other levers:
2. **Latency-insensitive routing** (§5) — makes any schedule correct by construction.
3. **Ship NOSCHED** — correct everywhere at ~411 MHz clock, no pipeline overlap.

> **✅ RESOLVED — UPDATE 2026-08-02: the switch is PRIME, not chip, not streaming.** A 4-point
> reconciliation on the shipped rtprime_ts RTL (`out_cyc`, `tb_replay_golden_prime_ts_full`) isolated it:
>
> | B | prime | result |
> |---|---|---|
> | 20 | 1 | **DEADLOCK** (200-742) |
> | 300 | 1 | **DEADLOCK** (more batches does NOT help) |
> | 20 | 3 | **PASS 8/8** full-stream bit-exact |
> | 300 | 3 | **PASS 8/8** full-stream bit-exact (every 64–74 words/row `[ALL-OK]`) |
>
> **`prime=1` → hard deadlock at any B; `prime=3` → correct at any B.** The `fwd_cosim` deadlock test
> above used **`prime=1`** → so that "streaming deadlocks II=2" was a **prime=1 artifact**, not a
> streaming property. Corrected picture at the *correct* fft prime (3):
> - **single-pass (B=1) starves** the bit-1 butterfly rows (2,3,6,7 drain 0 → 4/8) — the §3 symptom above;
> - **streaming (B≥20) → all 8 rows drain FULL-STREAM bit-exact.** Every streamed word matches golden.
>
> So the honest verdict is **not** "II=2 fft fails structurally" — it's: **fft II=2 with prime=3 is
> streaming-CORRECT (bit-exact), just throughput-degraded** (~0.045 out/cyc, mid rows 64–66 vs 74 words).
> The "never drains" was *single-pass at prime=3*; the "deadlock" was *prime=1*. NOSCHED is still the
> simplest all-correct chip, but the II=2 chip is more capable under streaming than §3 originally claimed.
> Evidence: `final_eva_performance/results/allo_stream/{fft_full.log,reconcile/00_reconcile.txt}`.

---

## 4. Version log — every alternative and what it broke on

| version | file / how | change vs final | verdict | issue (root cause) |
|---|---|---|---|---|
| **rtprime (FINAL)** | `eva_sb_syscredit_rtprime.py` | — | mmm+cordic 8/8, fft ≤4/8 | fft = pipelining overlap (§3) |
| NOSCHED | build_golden_cosim, no inject | no pipeline pragmas | **all 6 = 8/8** | correct but unpipelined (II≈5) |
| II=1 dep-false (naive) | `add_depfalse_ii1.py` | dep-false on resq/cmpq | **wrong results** | read-before-FP-commit **hazard** |
| II=1 honest (`wbfwd`) | `..._wbfwd.py` (FWD=0) | SB/RESQ deeper, FWD=0 | mmm 8/8, east-drains fail | same fft artifact; no Fmax win |
| **no_cred** | `make_no_cred_systolic.py` | strip `scr_`, unconditional send | K1 pass, **K2+ all-zero** (sim) | credit protected lossy `hold_v` (drops, not blocks) |
| guarded / elastic / elastic2 | `make_elastic.py` | + demand read / full-empty guards | **deadlock / all-zero** (sim) | always-fire sender floods demand reader |
| demand / demand2 / demand3 | `make_demand*.py` | real-only send + n_in/n_out bounds | **deadlock / node computes 0** | credit also = demand-matched supply + operand timing |
| **buf4** (credit intact) | `BUF_DEPTH 2→4` | deeper `rbuf` only | **cosim DEADLOCK (200-742)** | deep shift-register relaxes II (128× 200-880) → desync |
| **nocred_deep (ncdts)** | `make_nocred_deep_ts.py` | strip `scr_` + deep hold_v/rbuf/FIFO | **RTL HANG** (delta-loop) | always-fire get/put closes a combinational ring credit was breaking |
| nb_fix | non-blocking try_get/put | NB ops on always-fire structure | sim-only, **doesn't help** | swaps *how* reads fail, not *when* things happen — lockstep identical |
| fwd_cosim | `final_runs/eva_sb_syscredit_fwd_cosim.py` | compile-time prime + out_cyc | compute **byte-identical** to rtprime | not a distinct design — rtprime's predecessor |
| int16 | `eva_int16/` | IS_FLOAT dual-type | honest 1-cyc II=1 | separate datatype track |

### Deadlock catalog (Allo-sim, mmm K=2, 2026-07-30) — the empirical justification
`prime/deadlock_catalog.py` runs every variant through the Allo-sim circular-wait detector.
Three clean clusters — this is *why* the final design is always-fire + credit:
| variant | verdict | stuck FIFO / detail |
|---|---|---|
| **rtprime (FINAL)** | **PASS** | 4/4 correct — always-fire + credit |
| wbfwd (honest II=1, FWD=0) | **PASS** | 4/4 correct |
| no_cred (strip credit, always-fire) | ALL-ZERO | buffers *drop* when full (credit was the backpressure) |
| elastic / elastic2 (full/empty guards) | ALL-ZERO | same drop |
| guarded (demand systolic read) | **DEADLOCK** | `sys_w_0_1` (cosim 4x4: systolic col-3 ring, `200-742`) |
| demand (demand read + real-only send) | **DEADLOCK** | `rtr_e_1_0` |
| demand2 (+ n_in bounds) | **DEADLOCK** | `cr_e_1_2` |
| demand3 (read after decode) | **DEADLOCK** | `sys_s_1_0` |
| eva_sb_nb (full non-blocking try_get/try_put) | PASS* | *only credit-free design that works — uses `empty()`/`try_get` (check state), needs emitter ext for RTL |
Pattern: **credit-removed-but-still-blocking → drops (ALL-ZERO); demand/predict blocking reads → DEADLOCK
on every plane (systolic/router/credit). Only always-fire+credit (blocking, lossless, deadlock-free) or
full non-blocking (`try_get`/`empty`) works.** The demand chips prove "instruction says WHICH not WHEN"
(§4 above). This table is the reproducible record behind choosing always-fire + credit.

### 4x4 RTL cosim confirmation (2026-07-30) — cycle-accurate, matches Allo-sim
`run_cosim4x4_sweep.sh` (NOSCHED 4x4, mmm ones, standard-signature chips; `build_var_4x4.py` +
`tb_replay_golden_prime`). Verdict = DEADLOCK(200-742) vs COMPLETED (dummy golden, so "PASS"=no-deadlock):
| chip | Allo-sim | **4x4 RTL cosim** |
|---|---|---|
| rtprime (FINAL) | PASS | **COMPLETED** (no deadlock) |
| wbfwd (II=1) | PASS | **COMPLETED** |
| no_cred | ALL-ZERO | **COMPLETED** (lossy drop, NOT hung) |
| elastic / elastic2 | ALL-ZERO | **COMPLETED** (both confirmed — lossy, no deadlock) |
| **guarded** (demand read) | DEADLOCK | **DEADLOCK 200-742** (systolic col-3 ring node_0_3<->node_1_3, all w17) |
**Key confirmation: the two failure modes are cycle-accurately DISTINCT** — credit-removed-but-blocking
(no_cred/elastic) *completes lossy* (drops data, no deadlock); demand/predict-blocking (guarded)
*deadlocks*. So neither credit-free path is viable: one silently loses data, the other hangs. Only
always-fire+credit is lossless AND deadlock-free at RTL. Logs: `eva_sb_nb/cosim4x4_logs/`. NOT cosim'd in
this sweep (signature/emitter limits): demand/demand2/3 (need n_out/n_in tbs); the *current* eva_sb_nb.py
(uses supervisor-branch `try_get`/`empty` — needs vhls-printer ext). BUT an EARLIER non-blocking EVA
using **`read_nb`/`write_nb`** (standard Vitis HLS, RTL-emittable) DID cosim and PASS at II=3 (mmm 4x4,
rows [18,21,16,15]) — preserved verbatim at `final_runs/nonblocking_final/PASSING_II3_baseline/`
(kernel_II3_PASSING.cpp). So a non-blocking EVA IS RTL-viable via `read_nb` (no emitter ext needed);
open: whether it passes fft cosim (only mmm tested) and getting below II=3.

**The through-line:** EVA is **latency-sensitive**. Anything that perturbs per-node cycle timing —
pipelining overlap (fft), dep-false (hazard), deeper shift-buffers (deadlock), credit removal
(all-zero/hang) — breaks the choreographed lockstep. Credit and fixed buffer depths are *tuned* to that
lockstep; they are not free parameters.

---

## 5. Credit-free sketch — how it *could* look (a different architecture, not a patch)

**Why not a patch:** credit does ≥4 jobs — (i) backpressure for the lossy internal `hold_v`/`rbuf`
(they drop, they don't block), (ii) demand-matched supply, (iii) operand timing, (iv) breaking a
handshake cycle. §4 shows removing it one job at a time trips over the next. A credit-free chip must
replace **all four at once** by going **elastic / latency-insensitive**. Two layers, both required:

### Layer A — transport: FIFO backpressure *is* the credit
```python
for t in range(NSTEP):
    # RECEIVE: pull an operand ONLY if the datapath has room to hold it.
    for d in range(4):
        if hold_cnt[d] < HOLD_DEPTH:              # room?
            w, ok = sys_in[d].try_get()           # non-blocking; ok=0 if empty (never block)
            if ok and w.valid:
                hold_v[d, hold_cnt[d]] = w.data; hold_cnt[d] += 1
        # else: leave it in the upstream FIFO -> upstream FIFO fills -> upstream STALLS.
        #       That stall IS the backpressure. No scr_/cr_ credit stream anywhere.

    for d in range(4):                            # router receive: same rule
        if rbcnt[d] < RBUF_DEPTH:
            p, ok = rtr_in[d].try_get()
            if ok and p.valid: rbuf[d, rbcnt[d]] = p; rbcnt[d] += 1

    ... scoreboard issue / execute / retire (unchanged) ...

    # SEND: real packets ONLY, BLOCKING put. A full downstream FIFO stalls this node.
    for o in range(4):
        if have_real_output[o]:
            rtr_out[o].put(pkt[o])                # blocks if full -> natural backpressure
        # NO bubble emission, NO credit gate, NO always-fire.
```
Key inversions vs the current chip: reads become **conditional** (room-gated, non-blocking), internal
buffers become **blocking not lossy** (never drop — just don't read), sends become **real-only +
blocking**. The `scr_`/`cr_` planes disappear entirely; the stream `full_n`/`empty_n` replace them.

### Layer B — control: addressed routing + operand tagging (mandatory)
Layer A alone **abandons always-fire lockstep**, so the *timed* shuffle choreography no longer holds —
which is exactly why `nb_fix` (Layer-A-only on the old structure) didn't help. You must also:
- **route by address:** each packet carries its dest (the `hd[d][…]==axis` match already exists);
  the router forwards by that address (XY/dimension-order), not by timestep.
- **pair by tag:** the butterfly fires when **both tagged operands of a pair are present**, whenever
  that is — not "the operand at timestep T." A small per-slot tag + a match check.

With A+B, correctness no longer depends on arrival *timestep* → **any II is correct**, fft included, and
no credit is needed.

### Why instruction-gated blocking reads deadlock (EMPIRICAL, 2026-07-30)
`eva_sb_syscredit_rtprime_demand.py` = instruction-gated **blocking** demand reads
(`if need_d[d] and hold_cnt[d]<2: rx = sys_·.get()`, `need_d` from the instr's s1/s2) + real-only
sends (`if tx[0]==1: sys_·.put(tx)`). Allo-sim mmm K=2 → **`DeadlockError` (circular wait)**: a PE
blocked putting to full FIFO `rtr_s_1_1`. ROOT: the instruction says *which* dir to read, not *when* it
arrives; when actual timing drifts from the program's assumed schedule, a producer's real `put` has no
consumer `get` (consumer isn't at a reading instruction) → FIFO fills → put blocks → every PE in the
producer↔consumer ring blocks → circular wait. Bubbles were the escape hatch (advance past a not-yet-
arrived input); demand-blocking removes it. => this is the SPECIFIC reason non-blocking (`try_get`/
`empty()`, check FIFO state instead of predicting arrival) is required, not blocking demand reads.

### Honest risk assessment
- **Deadlock is the real danger** (the elastic/demand attempts deadlocked): conditional reads + blocking
  puts can form cyclic waits. Needs one guaranteed-drainable direction per cycle or a bounded-look-ahead
  arbiter — must be proven, not assumed.
- **Circular-buffer** internal buffers (head/tail, not shift-register) to avoid the II-relaxation that
  deadlocked `buf4`.
- **Validate small first:** 2×2 Allo-sim functional pass → then 4×4 → then 8×8 cosim. Do **not** jump to
  8×8 (both `buf4` and `ncdts` burned ~7 h of csynth to reach a deadlock).
- **Payoff is area/simplicity, not fft.** (Though A+B *also* fixes fft as a side effect, via B.)

**Verdict:** feasible as a *rebuild* of the node control + router (essentially the Allo
latency-insensitive-interconnect project), **not** as a strip of the current chip. Confidence: low for a
quick win, moderate for a proper elastic redesign.

---

## 6. Open items
- fft under **streaming/batching** — **INCONCLUSIVE so far.** Reuse-RTL B=4 on rtprime
  (`ci_sii2_fft_stream4.ini`, no re-synth) → **cosim DEADLOCK (200-742)**, but likely a **harness
  artifact**: the proper stream tb (`tb_replay_golden_stream.cpp`) targets the `fwd_cosim` signature
  (`out_cyc`, no `prime_cfg`) and won't link with rtprime, so B=4 was driven by the *single-shot* prime
  tb (single-shot completes 4/8; only the 4-activation packing changed → stream imbalance → deadlock).
  Clean test = `fwd_cosim` B=20 rebuild (proper stream tb, in flight) + a stream-tb adapted to the
  rtprime signature. NOTE: prior README `fwd_cosim` "fft 20/20 lossless" had an **empty `verdict.txt`**
  (thin evidence) — reproduction pending.
- **C-sim** for 1×1: pre-charge credit ≥ total-output (or `no_cred`) + emission reorder makes Vitis C-sim
  drain (single-pass sequential can't close the credit cycle otherwise). Not yet built.
- Latency-insensitive router (§5 A+B) — scoped, not built.
