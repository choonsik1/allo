# final_eva_systemc — EVA on the Allo SystemC backend

EVA through Allo's **SystemC** backend (`target="systemc"`) to **Catapult HLS + SCVerify
RTL cosim**.

**Design of record: `designs/v16_VERIFIED_credfree_uniform/`** — RTL-verified at 8×8 on
all six golden workloads (640 outputs, 0 mismatches), streams to its REPS=256
architectural ceiling (a further 12,016 outputs, 0 mismatches). On the **current emitter**
(2026-08-19) it is **−12.7 % area at 8×8** vs `v3.0_VERIFIED_channel_ts` and **−9.1 %** at
1 PE, **meets timing at 2.0 ns** (+0.0013 slack), and is **RTL-cosim verified — 640 outputs,
0 mismatches**. See the new-emitter section below; older figures are superseded. `v3.0` remains the older
fallback (1,280 outputs, 0 mismatches, two bitstreams).

## ⭐ NEW-EMITTER RESULTS (2026-08-19) — these supersede everything below

The SystemC emitter changed: **memory boundaries are RAM pins instead of req/resp
Connections channels** (`req.`/`rsp.` 78/60 → **0**; `Connections::In`/`Out` 64/71 → 25/25).
Every area number was re-measured; **timing did not move at all** (max delay identical to
ten decimals in every config).

### Area — 1 PE and 8×8, 2.0 ns, same emitter throughout
| chip | 1 PE old → **new** | Δ | 8×8 old → **new** | Δ | slack |
|---|---|---|---|---|---|
| **v16** | 62,655 → **56,955** | **−9.1 %** | 1,667,031 → **1,650,541** | −1.0 % | **+0.0013** |
| v3.0 | 73,862 → **74,872** | +1.4 % | 1,892,488 → **1,889,687** | −0.1 % | −0.0978 |
| elastic | 57,958 → **54,527** | −5.9 % | 2,028,945 → **2,011,692** | −0.9 % | −0.0831 |

**The RAM-pin change is a 1 PE effect that amortises away at scale** — up to −9.1 % at one
node, but only −0.1…−1.0 % at 64, consistent with a fixed per-design interface cost.

### The numbers to quote at 8×8
| | TOTAL AREA | vs v16 |
|---|---|---|
| **v16** | **1,650,540.5** | — |
| v3.0 | 1,889,687.4 | +14.5 % |
| elastic | 2,011,691.7 | **+21.9 %** |

**v16 is −12.7 % vs v3.0 at 8×8.** ⚠️ **Elastic's area advantage INVERTS with scale** —
**−4.3 % vs v16 at 1 PE, +21.9 % at 8×8.** The reversal survived the emitter change, so it
is a property of the design, not the toolchain. Quote elastic's −7.5 %/−4.3 % as a **1 PE**
number only.

### Correctness on the new emitter
| chip | csim | **RTL cosim** |
|---|---|---|
| **v16** | 640 outputs, 0 mism (6 golden workloads, REPS=8) | ✅ **640 outputs, 0 mismatches** — `cosim MATCH`, 8 output arrays |
| v3.0 | 320 outputs, 0 mism (3 workloads) | running |
| elastic | **80 outputs, 0 mism (6 golden workloads)** + MMM ladder 1×1…8×8 | running |

⚠️ **csim proves nothing about the RAM-pin path.** A csim project contains **zero `.v`
files** — g++ runs the emitted SystemC and Catapult is never invoked. `csyn` builds RTL but
never simulates it *and emits no ncsim makefile*, so its RTL cannot be cosim'd afterwards.
Only **cosim** exercises the memory interface the emitter change actually rewrote.

### Golden-vector harness for the verification chips
`scripts/run_golden_vec_systemc.py` runs elastic/skid on the **shipped golden EVA vectors**
(`/work/shared/users/zsm9/verification/vectors/Allo/<chip>/<wl>/<wl>.h`, whose `EOUT`
equals the RTL EVA output bit-for-bit). Before this, elastic was checked only against a
**synthetic numpy MMM** while v16/v3.0 had real golden verification — not comparable.
`REPLAY=1` reuses a built bitstream (~1 min/workload instead of ~5 h).
⚠️ These vectors carry **one rep** (2 outputs/lane) vs the REPS=8 sweep — same stimulus and
reference, lower depth.

### 1 PE table for the paper (2.0 ns, Nangate 45 nm, **no P&R** — Catapult is HLS only)
| configuration | TOTAL AREA | Area Score (Post-Assign) | max delay | 1/delay |
|---|---|---|---|---|
| fp16, FIFO (elastic) | **54,526.7** | 55,030.7 | 2.0831 ns | 480 MHz |
| fp16, FIFO (skid) | 111,964.9 | 112,785.9 | 2.1217 ns | 471 MHz |
| fp16, valid-ready (**v16**) | **56,954.8** | 57,819.8 | 1.9987 ns | 500 MHz |
| fp16, valid-ready (v3.0) | 74,871.9 | 75,850.0 | 2.0978 ns | 477 MHz |
| int16, FIFO (skid) | 108,968.4 | 109,789.4 | 1.9969 ns | 501 MHz |
| int16, FIFO (elastic) | **emitter bug** — `emitBitcast` hardcodes `half` for 16-bit bitcasts (CRD-312/413) | | | |
| int16, valid-ready | **no such design** — v16/v3.0 have no int/float branching | | | |

⚠️ Catapult reports **no LUT/FF/DSP** (ASIC target) and does **no place & route**. Nearest
analogues: `REG` ≈ FF, `FUNC` ≈ DSP, `MUX`+`LOGIC` ≈ LUT. `II = 0` everywhere — these loops
are not pipelined in the Vitis sense, and pipeline pragmas are measured no-ops (see below).

---

## ⭐ SCOREBOARD (2026-08-15, OLD emitter — superseded by the section above)

| axis | winner | numbers |
|---|---|---|
| **area 8×8** @2.0 ns (same emitter) | **v16** | v3.0 1,892,488 → **v16 1,667,031 = −11.9 %** (Area Score −13.1 %) |
| area 1×1 @2.0 ns (same emitter) | **elastic** | elastic 57,958 · v16 62,655 · v3.0 73,862 |
| — v16 vs v3.0 | **v16** | −11.9 % @8×8 · −15.2 % @1×1 (shrinks with mesh) |
| — elastic vs v16 / v3.0 | **elastic** | **−7.5 % / −21.5 %** (1×1 only — no 8×8 elastic csyn) |
| source size | **elastic** | 626 vs 1,727 lines; **zero** credit planes |
| correctness | tie | both RTL-verified at 8×8; elastic bit-exact 1×1…8×8 csim **and** cosim 2×2/4×4/8×8 |
| throughput **per iteration** | **elastic** | 1.66× (2×2), 1.89× (4×4), ~1.0× (8×8 — edge fades) |
| **throughput TOTAL, ≥4×4** | **v16** | 4×4: v16 **5,054** vs elastic **7,498** (+48 %) |

**Read it as: v16 is the throughput design of record at mesh ≥4×4; `from_verification/`
elastic is the better base for area and simplicity.** Elastic's architecture is genuinely
faster per step — it loses on total cycles only because `BUDGET = max(RUN_BUDGET,
6*LANELEN)` has **no early exit** and burns 792 iterations where v16 needs 282. That 6×
floor is measured **load-bearing** (4×/3×/2× all FAIL). And the deficit is **structural**:
elastic's minimum correct trip count (~660 at 4×4) already exceeds the 533 needed to match
v16, so even a perfect early exit leaves it ~24 % behind. See "How to improve" §1.

⚠️ **Two measurement traps that nearly produced false results — both real, both recorded:**
1. A `cycles=[…]` reading is void unless the same run says **PASS**. The first elastic 4×4
   attempt read 4,778 vs v16's 5,054 and looked like a win; it **FAILED** correctness.
2. Compare each design at **its own minimum correct lane**. v16 needs ≥160 cycles of drain
   margin for its credit plane; padding elastic to match measured *v16's* constraint and
   made elastic look 3.1× worse at 2×2 (7,814 cycles at BUDGET=1500).

---

## ⭐ THE VERIFIED RESULT — v3.0, 8×8, all six workloads bit-exact
| workload | outputs | mismatches | cyc/val (RTL == csim) |
|---|---|---|---|
| fft | 128/128 | **0** | 7.53 |
| mmm | 128/128 | **0** | **4.00** (the 4-instr MAC floor; matches Vitis 4.0) |
| cordic_cr/cv/hr/hv | 96/96 each | **0** | 18.13 |

Archives: `/work/shared/users/zsm9/eva_8x8_v30ts_cosim_fft_rtl` (unscheduled) and
`…_v30ts_SCHED_cosim_rtl` (scheduled) — each with `rtl/`, `reports/rtl.rpt`, `src/`,
`workload_logs/`.

`v3.0_channel_ts` = `chip/eva_sb_syscredit_rtprime.py` with **one change** — all 32
`Stream[T, STREAM_DEPTH]` links swapped to `Channel[T, valid_ready]` — plus `out_cyc_*`
timestamp ports. Credits KEPT, always-fire KEPT. De-buffering alone is **−51 % area** at
1×1 and is the safe win.

## ⭐ THE CREDIT-FREE LINE — v16, −15.2 % area (same emitter)
Removing the **systolic** credit plane (router credits kept) needs **three** mechanisms.
Any one missing and it breaks; that took v10–v16 to establish.

| | mechanism | why |
|---|---|---|
| v13 | RX gate on `hold_cnt < 2`, TX retain-until-grant, receive-after-drain | sound **between nodes** |
| v15 | `rq/gt` on the four systolic **edge drivers** | the injection link the gate does not govern |
| v16 | **one write primitive per channel** (all systolic primes → `try_put`) | else Catapult will not compile it |

✅ **DE-CONFOUNDED 2026-08-15.** v3.0 was rebuilt at 8×8 on the **current** emitter, config
matched to v16 (NSTEP=928, 2.0 ns, unscheduled). Every area figure below is now same-emitter:

| same-emitter | v3.0 | **v16** | delta |
|---|---|---|---|
| **8×8 TOTAL AREA** | 1,892,487.8 | **1,667,030.9** | **−11.9 %** |
| **8×8 Area Score** | 2,038,047.4 | **1,771,178.0** | **−13.1 %** |
| 1×1 TOTAL AREA | 73,862.0 | 62,654.8 | −15.2 % |

The old cross-emitter figure was −10.8 %; the confound was worth only ~1.1 points
(the guard cost v3.0 +1.2 % area: archived 1,869,399.9 → 1,892,487.8). v3.0's critical-path
slack is **−0.0978, identical to the archived build** — the emitter change did not move its
timing. The area advantage shrinks with mesh (−15.2 % at 1×1 → −11.9 % at 8×8) as fixed
overheads amortise.

**8×8 csyn, `NSTEP=928`, unscheduled, 2.0 ns — matched to the v3.0 build:**

| | v3.0_channel_ts | **v16** | saving |
|---|---|---|---|
| TOTAL AREA (after assignment) | 1,869,399.9 | **1,667,030.9** | **−202,369 (−10.8 %)** |
| Total Area Score | 2,060,529.2 | **1,771,178.0** | −289,351 (−14.0 %) |
| **critical-path slack @ 2.0 ns** | −0.0978 (2.0978 ns) | **+0.0013 (1.9987 ns)** | **v16 MEETS TIMING** |
| worst interface path (reg→top I/O) | −0.3388 | −0.3388 | unchanged |

**1×1 area ladder** (same NSTEP=215, 2.0 ns, nangate-45nm):
v2 150,109 → v3.0 73,603 (−51 %) → **v16 62,655 (−58 %)** → v3.2 54,890 (−63 %, **broken**).
v16 lands between v3.0 and v3.2 exactly as expected — it removes one plane, not both —
and unlike v3.2 it is correct.

⚠️ **Read the right section of `rtl.rpt`.** `Timing Report / Critical Path` is the real
internal path; `Register Input and Register-to-Output Slack` is the pin-to-reg/reg-to-pin
**interface**. Quoting the latter as "the critical path" understated v16 for a while.

- **Critical path:** v3.0 2.0978 ns (−0.0978) → **v16 1.9987 ns (+0.0013)**. v16 is the
  first variant to **close timing at 2.0 ns = 500 MHz**.
- **It is the fp16 DATAPATH, not flow control:** `reg(hold_v.d(0)(1))` →
  `leading_sign` (0.3747 ns) → `not` → `addc` (0.1880) → mux → `reg(drf(...))`.
  Normalize + add is ~40 % of it, so more frequency has to come from there.
- **Interface path −0.3388** (both designs) is `rclc_[wens]_0:run/reg(...Push()...)` →
  `l_S_t_1_t7x`, the **router credit return** v16 keeps.

csim: all six workloads at 8×8 REPS=8, **640 outputs, 0 mismatches**, plus `cordic_cr` at
`MARGIN=6000` (the case that deadlocked v13).
**8×8 RTL cosim (4 h 01 m): fft 128/0 on the built bitstream, then mmm 128/0 and
cordic_cr/cv/hr/hv 96/0 each by replay — 640 outputs, 0 mismatches.**

### ⭐ RTL-measured throughput and deep streaming (v16_ts, 8×8)
Timestamps (`out_cyc_*`) are written **by the DUT**, so read back from a cosim they are
RTL cycle counts. SCVerify compared **all 12 output arrays** — the four stamp arrays
included — and reported bit-exact, so these are measurements, not model estimates.

| workload | outputs | csim | **RTL** | **RTL clocks/val** |
|---|---|---|---|---|
| fft | 128 | 7.53 | **7.53** | 133.3 |
| mmm | 128 | 4.00 | **4.00** | 70.8 |
| cordic_cr/cv/hr/hv | 96 each | 19.67 | **19.67** | 348.2 |

⚠️ **These `cyc/val` figures are LOOP ITERATIONS, not clocks.** The `out_cyc_*` stamps
count `t`; the `wait()` that makes an iteration one clock is compiled out under
`__SYNTHESIS__`. Measured exactly (single ncsim run, 1 ns ticks): **8×8 = 17.70 RTL clocks
per iteration** (24,780 cycles / NSTEP=1400), 1×1 = 6.11. Multiply to get the last column.

**RTL reproduces csim exactly, on every workload and every depth.** The csim throughput
model is therefore *validated*, not assumed — measure in csim (seconds) from here on.
It also confirms the **cordic +8.5 % vs v3.0's 18.13 is real silicon behaviour**, so it
is a genuine optimization target rather than a modelling artifact.

**Deep streaming, in RTL, on one bitstream — 12,016 outputs, 0 mismatches:**

| REPS | 16 | 32 | 64 | 128 | 255 | 256 |
|---|---|---|---|---|---|---|
| outputs | 256 | 512 | 1,024 | 2,048 | 4,080 | 4,096 |
| cyc/val | 7.77 | 7.89 | 7.94 | 7.97 | **7.99** | **7.99** |

Fill cost amortizes away; **7.99 is the asymptote**. REPS=256 is the architectural
ceiling — `iter_size` is 8-bit, so 512 aliases to 256; the 255/256 pair pins that in
hardware. All 8 rows carry identical stamps (238 → 351 at REPS=8): the mesh is exactly
row-symmetric in time, a cheap sanity check for any future variant.

**⭐ Lane length is free in TIME as well as area.** L=1400 vs L=4800 built in 3 h 59 m vs
3 h 56 m (ncsim 43 s vs 67 s) — a 3.4× lane costs nothing, matching the 22×-lane 1×1 probe
(+2 % area). `LANELEN` is a streaming-port dimension, not stored state. **So build one
long-lane cosim and replay everything on it:** the six workloads *and* the full 16→256
ladder took **7.5 minutes** against a 4 h bitstream.
⚠️ Replays must be **sequential** — they all write `input*.data` into the same project.

### ⚠️ v13 was recorded as "solved" and was not
It passed 4×4 MMM and 8×8 fft at REPS=2, so it looked done. The six-workload sweep at
REPS=8 then showed **all four cordic variants emitting exactly half** their outputs —
every value bit-exact, the tail all zeros — and at `MARGIN=6000` it **deadlocked**
(68 s CPU in 4 h 29 m). It also could never have been synthesized (CIN-150). Four
hypotheses were disproved before the cause was found; see
`memory/eva-v10-syscredit-removal.md` so they are not re-explored.

The lesson generalises: **a variant is not verified until all six workloads pass at
REPS=8 *and* it synthesizes.** fft and mmm alone do not discriminate — cordic is the
workload that exposes injection-edge faults.

## ⭐ THE VERIFICATION CHIPS — `designs/from_verification/` (elastic & skid)
Byte-identical copies of `/work/shared/users/zsm9/verification/{fp16,int16}_{elastic,skid}`
(Vitis-verified). **Elastic runs in THIS flow**: emits for `target="systemc"`, Catapult
`csyn rc=0`, bit-exact MMM csim at **1×1, 2×2, 3×3, 4×4, 8×8**, and cosim-PASS at 2×2/4×4.
Driver: `scripts/run_elastic_systemc.py` (our MMM stimulus minus `prime_cfg` — elastic has
no credit plane — sized by `LANELEN`/`RUN_BUDGET`, not `NSTEP`).

| | elastic | skid | our v16 |
|---|---|---|---|
| lines | **626** | 1,008 | 1,727 |
| credit planes | **none** | `cr_`+`scr_` | `cr_` |
| links | `Stream[T,8]` buffered | `Stream[T,8]` | `Channel` **unbuffered** |
| link ops | blocking only | blocking only | blocking + `try_*` |
| firing | data-driven | data-driven | **always-fire** |
| 1×1 area | **57,958** | 113,585 (**+81 %**) | 62,655 |

**Skid is not a candidate** (+81 % area).

**8×8 cosim (2026-08-15): `cosim MATCH`, bit-exact, 35,774 RTL cycles**
(`LANELEN=346, RUN_BUDGET=2076`). Elastic now meets v16's verification bar at full mesh —
its 8×8 correctness is measured, not inferred from csim.

cyc/iter by mesh — **elastic 6.05 → 9.47 → 17.23** (2×2/4×4/8×8) vs **v16 10.04 → 17.92 →
17.70**: elastic's per-iteration edge fades from 1.66× to ~1.0× as the mesh grows.
⚠️ The 8×8 pair is **not apples-to-apples** (v16's 17.70 is *fft* at NSTEP=1400, elastic's
17.23 is *MMM*) — treat the convergence as suggestive; the bit-exact result is the solid
part. It does not change the verdict: v16 already wins total throughput from 4×4.

### ⭐⭐ The mechanism our line was missing
Elastic guards **blocking** ops with FIFO status predicates on **buffered** links:
```python
if oh_v[0] == 1 and rtr_e[i,j+1].full()  == 0:  rtr_e[i,j+1].put(...); oh_v[0] = 0
if ig_v[0] == 0 and rtr_e[i,j].empty() == 0:  ig_p[0] = rtr_e[i,j].get(); ig_v[0] = 1
```
**The FIFO *is* the backpressure** ⇒ no credits, no silent drop, and **zero handshakes when
idle**. `v17` failed at 3×3 because it removed credits from *unbuffered* `Channel`s — where
nothing can be full or empty. Elastic passes 3×3.
The SystemC backend already supports this: `connections_fifo.h` (vendor FWFT
`Connections::Fifo`) plus **occupancy sidebands**, because "regular Connections In/Out ports
cannot report Empty/Full in HLS".

**Why our v16 is pinned at ~18 cyc/iter:** unbuffered `Channel` (Allo: "protocol … but *no
buffering*") makes every Push/Pop a **rendezvous**, and always-fire forces **24 handshakes
per iteration** regardless of data.

### ❌ Four optimizations that returned ZERO — all measured, do not retry
| attempt | folder | result |
|---|---|---|
| remove router credits | `v17_credfree_router/` | synthesizes; correct to 2×2, **all-zero from 3×3** (2nd forwarding hop). Not capacity — `BUF_DEPTH` 2/4/8 fail identically |
| credits non-blocking | `v18_nb_router_credits/` | correct at **every** mesh, **cycle-identical** to v16 (1430/2510/5054) |
| `#pragma HLS pipeline II=1` | `SCHED=1` | **identical cycles** at 1×1 *and* 2×2 (1430, 2510) |
| buffer our links | `v19_buffered_links/` | depth 2 → **+16.6 % area** (73,068), erasing the v3.0→v16 win; 4×4 cosim exceeded the 1 h synth timeout |

⚠️ **Never benchmark a mesh-coupling change at 1×1** — a node's only peers are drivers and
collectors that are always ready, so nothing can refuse a handshake and the effect is
invisible by construction. This invalidated the first v18 and II=1 measurements.

## ⚠️ USE UNSCHEDULED — the II pragmas make it strictly worse
| metric | unscheduled | scheduled (64 pragmas) |
|---|---|---|
| **RTL cycles (exact, 1x1 cosim)** | **1430** | **1430 — identical to the cycle** |
| throughput | 7.53 iter/val | **7.53 — identical** |
| area score | **1,880,994** | 2,440,732 (**+30 %**) |
| critical path | **2.0978 ns** | 2.7908 ns (**+33 %**) |
| slack @2.0 ns | **−0.0978** → closes at 2.1 ns / **476 MHz** | −0.7908 → needs 2.8 ns |
| real ops / node | **1,960** | 3,235 (+65 %) |

**The loop is HANDSHAKE-limited, not schedule-limited.** `II=1` demonstrably changed the
schedule (node throughput 33 → 24, ops +62 %) and still produced **the same 1430 RTL
cycles**: each iteration must complete its Connections handshakes with neighbours,
drivers and collectors, and that — not Catapult's C-step count — sets the rate. So the
pragma costs area (+30 %) and critical path (+33 %) and returns nothing. Measured in real
RTL cycles, not iterations; see `memory/eva-pipeline-pragma-no-effect.md`.

**Why:** the emitter sets `scfWhileWait = true` (a `wait()` per loop iteration), so the
node loop is already a clocked state machine rather than something an II pragma has to
create. ⚠️ Do **not** read `rtl.rpt`'s `Throughput` column as clocks-per-iteration — see
`memory/eva-synthesis-wait-guard.md`; adding waits *increases* it (34 → 81), and
`Latency -1 / Throughput 1` on the older builds means *not pipelined*, not "1 clock". On **Vitis** the II pragma was essential
(unscheduled II=211); on **Catapult+SystemC the clock already created the pipeline**, so
the Vitis II=1/II=2 story does **not** transfer.

## Drivers
```bash
# golden-workload replay (the main harness) — 8x8, all six shipped EVA programs
WL=fft|mmm|cordic_{cr,cv,hr,hv}  MODE=csim|cosim  CHIP=eva_v16 \
  MESH=8 REPS=8 PRIME=1 MARGIN=800 PRJ=<dir>  python scripts/run_golden_systemc.py

# is a variant SYNTHESIZABLE? 1x1, minutes — run this BEFORE any ~6 h 8x8 build
CHIP=eva_v16 MESH=1 NSTEP=215 PRJ=<dir> python scripts/csyn_probe.py

# replay ANOTHER workload on an ALREADY-BUILT cosim bitstream: ~1 min, not 7 h
WL=mmm PRJ=<built-cosim-prj> LFORCE=928 python scripts/replay_cosim.py

# per-node word-flow counters (localizes WHERE words are lost)
WL=cordic_cr CHIP=eva_v14 MESH=8 REPS=8 PRJ=<dir> python scripts/debug_wordflow.py

MODE=codegen|csim|csyn|cosim  python scripts/run_systemc.py       # passthrough ramp
MODE=csim|cosim               python scripts/run_mmm_systemc.py   # 1x1/NxN MMM (MMM_MESH=, SCHED=)
CHIP=eva_fp16_elastic MMM_MESH=4 LANE_MARGIN=50 MODE=csim|cosim \
                              python scripts/run_elastic_systemc.py  # elastic, synthetic MMM
CHIP=eva_fp16_elastic VEC=fp16_elastic WL=fft MODE=csim|cosim [REPLAY=1] \
                              python scripts/run_golden_vec_systemc.py  # elastic/skid, GOLDEN vectors
CHIP=eva_v16 DTYPE=fp16|int16 MESH=8 NSTEP=928 CLK=2.0 SCHED=0|1|2 \
                              python scripts/csyn_probe.py           # area/timing, any chip
```
Knobs: `MESH NSTEP SCHED PARTITION PRJ PRIME REPS MARGIN LFORCE ITER TS MMM_MESH MMM_B`.

**Detached runs need the interpreter spelled out** — `setsid`/`nohup` do not source the
profile, and conda `base` has **no numpy**. Use
`/home/zsm9/miniconda3/envs/allo/bin/python`.

**`csyn` takes `mod()` with NO arguments** (`allo/backend/hls.py` asserts it); the
`run_*_systemc.py` drivers pass arrays and trip that assert before Catapult ever runs.
That is what `csyn_probe.py` is for. `cosim` needs all arrays.

## Chip variants
| folder | change | status |
|---|---|---|
| `chip/` | v2 baseline, `Stream` + credits | reference |
| **`v3.0_VERIFIED_channel_ts/`** | Channel + credits + timestamps | ⭐ **RTL-VERIFIED — design of record** |
| `v3.0_OK_channel_nots/` | Channel + credits, no timestamps | ok |
| **`v16_VERIFIED_credfree_uniform/`** | + uniform `PushNB` (CIN-150 fix) | ⭐ **CURRENT — RTL-VERIFIED**, −10.8 % area |
| `v15_OK_edgebp_nosynth/` | + `rq/gt` at the injection edge | correct, but will not synthesize |
| `v14_TOOL_wordflow_counters/` | per-direction word-flow counters | 🔧 diagnostic, reusable |
| `v13_BROKEN_halfout_deadlock/`, `v13_BROKEN_halfout_ts/` | systolic credits removed, edge unfixed | ❌ half outputs on cordic + deadlock |
| `deadends/*` | 16 credit / always-fire / elastic experiments | ❌ documented negatives, named by failure |

## Known traps
**`iter_size` counts KERNEL ITERATIONS, not stream reps.**
`load_prog_packets(cfg=(klen, iter_size, sync))` → config_reg_1. It is **not** "Inf" when
0 — it **caps the stream**, and counts *activations*: mmm's 4-instruction MAC kernel
consumes one word per iteration, so mmm needs `REPS*2` while fft/cordic need `REPS`. Get
it wrong and the PC stops early, emitting **exactly half** the outputs — every one
correct, just too few. Handled by `ACT_PER_REP = {"mmm": 2}`.

**cordic lane asymmetry.** Even lanes carry 1 word/op (x only), odd lanes 2 (z then y);
`stream_inputs[2*j+1]` on an even lane is a **dummy that must not be driven**.

**The drain-margin trap.** rtprime's runtime-prime credit flow needs **≥160 cycles of
drain margin** or tokens never leave the mesh and **every output reads back zero**. The
emitted testbench has **no self-check**, so this looks like a clean pass (`rc=0`) while
computing nothing. Use `MARGIN=800`; both drivers assert against a numpy golden.

**⚠️ The lane formula assumes ~1 cyc/val — the default `MARGIN=300` truncates cordic.**
`L = pc + REPS*per_row + MARGIN` is blind to throughput, but real rates are 4 (mmm),
7.99 (fft) and **19.67 (cordic)** cyc/val. Too short ⇒ correct values then a **`0x0`
tail**, which the comparison counts as *mismatches* — so a fully RTL-verified chip
reports `0/8 rows clean | 56 mismatches`. This has caused **two** false alarms.
Tell: the mismatches are all `got=0x0` and start partway through a row; real corruption
gives wrong *values*, not zeros. Fix with **`LFORCE ≈ pc + REPS*per_row*cyc_per_val +
400`** (not a bigger `MARGIN` — cosim replays must reuse the exact `L`).
`run_golden_systemc.py` now prints a `!! LANE MAY BE TOO SHORT` warning with the
`LFORCE` value to use.

**`partition_rf` is a no-op and costs hours.** It issues M·N·25 `s.partition()` calls
(1,600 at 8×8) and produces **byte-identical** code (verified with `diff` at 2×2).
Catapult has no array-partition pragma, and this design already maps every array to flops
(`rtl.rpt`: `MEM 0.0`, `ROM 0.0`, `REG 64 %`). Always use **`PARTITION=0`**.
Emit time at 8×8: **1 m 04 s** without it, killed at **1 h 20 m** with it.

**`replay_cosim.py` port layout follows the chip.** A TS chip interleaves
`(out, out_cyc)` so data sits at `2*edge`; a non-TS chip has `out x4` then `rout x4`, data
at `edge`. Reading a non-TS build with the TS layout returns router arrays and reports
**zero outputs on every row with `ncsim rc=0`** — indistinguishable from a dead design.
The script now picks the layout from the chip name and prints which it used.

**A cycle count is void unless the same run says PASS.** The first elastic 4×4 cosim read
4,778 cycles against v16's 5,054 and looked like a 5.5 % win — it had **FAILED** the
bit-exact check. Always read the verdict and the number together.

**Compare designs at each one's own minimum correct lane.** v16 needs ≥160 cycles of drain
margin to flush its credit plane; elastic needs none at 2×2 and ≥50 at 4×4. Padding elastic
to v16's margin measures *v16's* constraint and made elastic look 3.1× worse at 2×2, because
its `BUDGET = 6*LANELEN` has no early exit and multiplies any padding by six.

**⚠️ A timed-out cosim leaves an ORPHANED Catapult.** When `ALLO_COSIM_SYNTH_TIMEOUT` fires
the Python raises but the `catapult` child survives with **PPID=1** and pins a core
indefinitely. Happened twice in one day. After any timeout:
`ps -eo pid,ppid,args | awk '$2==1 && /catapult/'` and kill by explicit PID.
(`run_mmm_systemc.py` uses 3600 s; `run_golden_systemc.py` 36000 s.)

**Diagnose hangs by CPU time, not elapsed time.** A deadlocked SystemC sim looks
identical to a slow one on the clock. Two `ps -o time=` samples showing the *same
absolute CPU* is conclusive — the v13 deadlock had 68 s of CPU across 4 h 29 m.

## Flow status
| step | 1×1 | 8×8 (64 PEs) |
|---|---|---|
| codegen | ✅ 4,767 lines, 22 `SC_MODULE` | ✅ 144,670 lines, 85 `SC_MODULE`, ~64 s |
| csim | ✅ bit-exact | ✅ six workloads, 0 mismatches (v3.0 **and** v16) |
| Catapult csyn | ✅ ~6 min | ✅ 0 errors — v3.0, v16 (3 h 54 m, 12.9 GB peak) |
| SCVerify RTL cosim | ✅ bit-exact | ✅ **v3.0: 1,280** · **v16: 640 + 12,016 deep** — 0 mismatches |

⚠️ `csyn` does **not** emit SCVerify/ncsim makefiles (`catapult.py` gates them on
`mode=="cosim"`), so a csyn'd RTL **cannot** be cosim'd — that needs its own ~7 h run.

**Run long jobs detached** (`setsid nohup`) with `PRJ=` on `/scratch` (local, no quota) —
`/home` has a 20 GB quota and a 3 h run was once lost to session teardown.

## Layout
Reorganised 2026-08-15. `designs/` = chips you would actually use; `deadends/` = documented
negatives; `archive/` = build output. 27 MB -> 16 MB.
```
chip/       eva_sb_syscredit_rtprime.py   v2 baseline
            eva_workloads.py              ⭐ THE ONLY COPY
designs/    v16_VERIFIED_credfree_uniform/  ⭐ DESIGN OF RECORD
            v16_VERIFIED_credfree_ts/       + out_cyc_* timestamps
            v3.0_VERIFIED_channel_ts/       older RTL-verified fallback
            v3.0_OK_channel_nots/           same, no timestamps
            from_verification/              ⭐ elastic & skid (+ own README)
tools/      v12_TOOL_deadlock_probe/      per-node stall snapshot
            v14_TOOL_wordflow_counters/   per-direction word counts
deadends/   20 documented negatives (+ own README), incl. this session's:
            v15_SUPERSEDED_edgebp_nosynth/       v16's base; trips CIN-150
            v17_BROKEN_router_credfree_3x3/      dies at 3x3 (2nd forwarding hop)
            v18_NULL_nb_credits_no_speedup/      correct, cycle-identical to v16
            v19_NULL_buffered_links_area_cost/   +16.6 % area, no gain
scripts/    run_golden_systemc, run_mmm_systemc, run_elastic_systemc, run_systemc,
            replay_cosim, csyn_probe, debug_wordflow, debug_deadlock, archive_rtl.sh
archive/    1x1_*/  three 1x1 builds: reports/ + allo/ (rtl/ dropped — regenerable)
            runs/ logs/ orig_example/
```
**Build output lives in `/scratch/zsm9/eva_runs`** (not here). Cleaned 24 GB -> 4.3 GB,
keeping the two replay bitstreams `v16ts_cosim8x8` (L=1400) and `v16ts_cosim4800` (L=4800)
— rebuilding either is ~4 h — plus `_kept_evidence/` (43 gzipped `rtl.rpt`, 39 `STATUS`,
38 run scripts: the backing data for every number in this README, 219 MB -> 9.4 MB).

**Folder names carry the verdict** — `VERIFIED` / `OK` / `TOOL` / `ISOLATION` / `BROKEN`,
so `ls` answers "which of these can I trust?". **Module names are unchanged**
(`designs/v16_VERIFIED_credfree_uniform/eva_v16.py` → `CHIP=eva_v16`), so every command
and every note that references a chip still works.

Every variant stays importable: all 7 drivers scan **`designs/`, `tools/` and
`deadends/`** for `v[0-9]*`, so `CHIP=eva_v13` still resolves for reproducing a
documented failure. If you add a driver, copy that two-line glob.

⚠️ **`chip/eva_workloads.py` is the only copy — do not re-add per-variant copies.**
There used to be 24. Every driver does `sys.path.insert(0, chip/)` and then *appends* the
variant dirs, so `chip/`'s copy always won and the other 23 were **never imported** —
editing one did nothing. They were deleted 2026-08-13 after verifying all were
byte-identical.

`archive/1x1_*/generated/` (383 MB) and `archive/runs/8x8_v33_ts_sched/run.log` (13 MB,
raw csyn log of a *broken* v3.3 build) were deleted; `rtl/`, `reports/`, `allo/`,
`run.sh` and `time.log` are intact. `deadends/v3.2/rtl/` was dropped too — its
`reports/rtl.rpt` (the −63 % area evidence) is kept. Folder: 42 MB → 26 MB.

## Backend notes
Backend: `/home/zsm9/allo_sup`. The SystemC target maps to the Catapult backend
(`allo/backend/catapult.py` tcl, `allo/backend/hls.py` runner).

**CIN-71 (fp16 bitcast) — fixed upstream.** `EmitSystemC.cpp::emitBitcast`
(`mlir/lib/Translation/EmitSystemC.cpp:708-758`) routes float bitcasts through the type's
own bit accessors, which synthesize *and* work in csim. Historical failure:
`logs/catapult_csyn.log`.

**Scheduling pragmas.** `SystemCModuleEmitter` inherits `emitLoopDirectivesPreheader`
from `CatapultModuleEmitter` (`EmitCatapultHLS.cpp:233`), emitting Catapult-native
pragmas (`hls_pipeline_init_interval`, `hls_unroll`, `hls_design dataflow`) in the loop
**preheader** — in-body placement makes Catapult drop them with CIN-319. `run.tcl`
carries no `PIPELINE_INIT_INTERVAL`; pipelining comes from the pragmas, so it needs
`SCHED=1`. See the table above for why you should not want it.

**Environment.** `hls.py`'s cosim path needs **`SYSTEMC_HOME`** (`$MGC_HOME/shared`) and
runs the software golden as a bare `./sim`, which needs
**`LD_LIBRARY_PATH=$MGC_HOME/lib:$MGC_HOME/shared/lib`** for `GLIBCXX_3.4.26`.

---

## 🔭 HOW TO IMPROVE THE RESULTS — ranked by (payoff ÷ risk)

Everything below is grounded in a measurement in this README, not a guess.

### 1. ❌ Early exit for elastic — MEASURED, IT CANNOT WIN (recommendation withdrawn)
An early exit means replacing every kernel's `for it in range(BUDGET)` (no `break`) with a
termination condition — stop once the mesh is quiescent instead of after a fixed trip count.
Tempting, because elastic burns 792 iterations at 4×4 where v16 needs 282.

**But the minimum correct iteration count is already above break-even.** Break-even vs
v16's 5,054 cycles at 9.47 cyc/iter is **533 iterations**. Sweeping the budget floor at
LANELEN=132 (`eva_fp16_elastic_bud.py`, `BUDMUL` env):

| iterations | 528 | 554 | 594 | **660** | 792 (current) |
|---|---|---|---|---|---|
| bit-exact | FAIL | FAIL | FAIL | **PASS** | PASS |
| est. cycles | 5,000 | 5,246 | 5,625 | **6,250** | 7,498 |

A *perfect* early exit lands at ~6,250 cycles — still **~24 % slower than v16's 5,054**.
Elastic needs ≈2.2× more iterations than v16 while being only 1.89× faster per iteration;
2.2 > 1.89, so it loses regardless of how tightly the budget is drawn.
**Elastic's throughput deficit at ≥4×4 is structural.** An early exit is still worth ~17 %
(792→660) if elastic is used for other reasons, but it does not change the verdict.

### 2. Port elastic's `full()`/`empty()` discipline onto our v16 lineage
Our ~18 cyc/iter is unbuffered-`Channel` rendezvous **+** always-fire (24 forced handshakes
per iteration). Elastic proves buffered `Stream` + status predicates removes both. Note
`v19` showed buffering **alone** costs +16.6 % area — the win needs the *data-driven firing*
too, which is precisely what always-fire prevents.
*Risk: high (v4/v5/v6 already failed removing always-fire from our chip). Payoff: large.*

### 3. ✅ DONE — v3.0 re-measured at 8×8 on the current emitter
The area delta is no longer cross-emitter. v3.0 8×8 csyn (NSTEP=928, 2.0 ns, unscheduled,
current emitter): **TOTAL AREA 1,892,487.8** vs v16's 1,667,030.9 = **−11.9 %**
(Area Score 2,038,047.4 → 1,771,178.0 = −13.1 %). The old confounded figure was −10.8 %,
so the guard was worth only ~1.1 points (+1.2 % area on v3.0). v3.0's slack came back
**−0.0978, identical to the archived build** — the emitter change did not move its timing.

### 4. Attack the fp16 datapath, not the flow control
The real critical path is `reg(hold_v)` → `leading_sign` (0.375 ns) → `addc` (0.188) →
`reg(drf)` — normalize+add is ~40 % of 2.0 ns. Flow control is **not** on it, so no credit
or handshake change buys frequency. Timing is also **non-monotonic** (v16 fails 1.9/1.8 but
passes 1.7), so never bisect for Fmax.
*Risk: low. Payoff: the only route to higher clock.*

### 5. Still never measured
**Power** (needs library + flow work), **v3.0's clocks/iteration** (required before any
absolute v3.0-vs-v16 speed claim), and an **8×8 csyn of elastic** (its area advantage is
measured at 1×1 only, and v16's advantage over v3.0 shrank with mesh — so elastic's −7.5 %
may not hold at 8×8 either).

### ✋ Do NOT spend time on
Removing credits from unbuffered channels (`v17` — 3×3), making credit ops non-blocking
(`v18` — cycle-identical), `II=1` pipeline pragmas (identical at 1×1 and 2×2; the loop is
handshake-limited), buffering our links alone (`v19` — +16.6 % area), reverting the
`__SYNTHESIS__` wait guard (reproduces SCHD-67 even under `-IO_MODE super`), or the skid
machine (+81 % area).
