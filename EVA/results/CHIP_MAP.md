# EVA chip map — which chip / folder / P&R is THE final, and what everything else is

> Written 2026-08-04 to stop the recurring confusion between `prime` / `syscredit` /
> `rtprime` chips and the many `pnr*` / `1307_prj_*` P&R dirs. **Anchor: `final_chip_1x1/`.**

---

## ⭐ THE FINAL CHIP

| | |
|---|---|
| **name** | **scheduled II=2, credit-based, runtime-prime EVA** |
| **Allo source** | `final_final/prime/eva_sb_syscredit_rtprime.py`  (`+_ts` = same + `out_cyc` timestamp ports) |
| **curated copy** | `final_eva_performance/final_eva_ii2/` |
| **schedule** | pipeline II=1 + array_partition + bind_op, **NO `dependence=false`** → HLS honors the `resq/cmpq` recurrence → **achieved II=2 (correct)**. dep-false II=1 is a silent hazard. |
| **authoritative QoR folder** | **`final_final/final_chip_1x1/`** (see `CORRECTED_FINDINGS.md`, 2026-07-23) |
| **8×8 RTL (reused for cosim)** | `/work/shared/users/zsm9/eva_ts_8x8_rtl/wd` (13 h csynth, once) |

### Definitive QoR (1×1, post-route Vivado impl) — **timing NOT met @3.33 (misses 300 MHz)**
| unit | CP | Fmax | LUT / FF / DSP | file |
|---|---|---|---|---|
| **node_0_0 (PE core)** | **4.462 ns** | **~224 MHz** | 3371 / 2681 / 2 | `final_chip_1x1/ii2/pnr_node_only/node_0_0_timing_paths_routed.rpt` |
| **full-top 1×1** | **4.287 ns** | **~233 MHz** | 6037 / 6244 / 2 | `final_chip_1x1/ii2/pnr_full/…routed.rpt` |

### Critical path (the reason for the Fmax)
The **fp16 MAC datapath**: adder-input FF → DSP48E2 mantissa **multiply** → DSP **ALU** → CARRY8 → 2nd DSP ALU → CARRY8 → dest FF. 13 logic levels, **69% logic** (2 DSPs + carries ≈ 1.6 ns). **`Fmax is II-INDEPENDENT`** — the fp op caps it at ~4.3–4.5 ns regardless of II. 300 MHz would need re-pipelining the fp/control path (separate effort).

### Suite verdicts
- RTL cosim (8×8): mmm / fft / cordic×4 all **8/8 bit-exact** (fft/cordic at prime=3, mmm at prime=6).
- Streaming throughput (per-lane, out_cyc): mmm 0.167, fft 0.045, cordic even 0.036 / odd 0.072 out/cyc.

---

## Superseded / variant P&R dirs — NOT the final number
| dir | what it is | Fmax | why not final |
|---|---|---|---|
| `eva_home_offload/final_runs/pnr25_prime/` | **`prime` variant, NO sys-credit** | 321 MHz (met 3.33) | different chip — meets 300 only *without* the credit plane |
| `eva_home_offload/final_runs/pnr25_syscredit/` | a syscredit P&R (8-bit hold_cnt) | 293 MHz | not the authoritative final run |
| `eva_home_offload/final_runs/1307_prj_eva_prime/` `_eva_sb_syscredit/` etc. | older (Jul-13) P&R sweep | 310–324 MHz | superseded by `final_chip_1x1` |
| `final_runs/pnr_1x1_syscredit_fwd/` | **fwd (FWD=1 forwarding)** 1×1 | 229 MHz | forwarding variant, not the shipped II=2 |

## Related chips (Allo `prime/`) — one-line each
| file | what |
|---|---|
| **`eva_sb_syscredit_rtprime.py`** ⭐ | THE final (II=2, credit, runtime-prime) |
| `eva_sb_syscredit_rtprime_ts.py` | ⭐ + `out_cyc` timestamp ports (throughput measurement) |
| `eva_sb_syscredit_rtprime_wbfwd.py` | FWD=0, 2-line diff → honest II=1 at 9.0 cyc/MMM (slow) |
| `eva_sb_syscredit_fwd_cosim.py` (in `final_runs/`) | FWD=1 forwarding, fast ~5.9 cyc/MMM |
| `eva_sb_syscredit_rtprime_stalldbg.py` | instrumented (stall-reason breakdown) — NOT for synth |
| `eva_sb_syscredit_rtprime_{no_cred,demand*,elastic*}.py` | credit-free exploration — PARKED |

## II=1 / datatype experiments (2026-08, all confirm II is NOT the wall)
| what | where | result |
|---|---|---|
| honest II=1 8×8 (lat 2→1) | `final_final/sched8x8_ii1ts/` + `/work/shared/…/eva_sched8x8_ii1ts_rtl/wd` | 6/6 bit-exact, throughput **byte-identical to II=2**, 1×1 P&R 154 MHz → net loss |
| custom fp16 (combinational) | `final_final/custom_fp16/` + `/work/shared/…/custom_fp16_1x1_wd` | II=1 achievable but **70 MHz routed** → net loss |
| Exp A/B (lat=1 / dep-false) | `final_eva_performance/results/allo_stream/ii1_exp/` | II≈fp_lat−1; dep-false didn't corrupt mmm (mixed II) |

**Takeaway:** every route (II=1 clamp, custom fp16) is capped by the **fp16 op latency/path**, which is II-independent → **II=2 (`final_chip_1x1`, 224/233 MHz) is the shippable best.** Only **int16** (true 1-cycle) would let II=1 win.

## Clock-uncertainty experiment (2026-08-04) — banks 239 MHz, confirms recurrence wall
`final_final/fpsplit_1x1/` — re-ran the final-chip node with `syn.clock_uncertainty=0.9 ns` (forces HLS to schedule to ~2.43 ns and try to break the 2-DSP combinational fp chain). Result:
- **II held at 2** (node loop Final II=2 Depth=5 — no regression), routed **Fmax 233 → 239 MHz** (data-path 4.445 → 4.159 ns). **Free +6 MHz — worth baking into the final config.**
- BUT the chain did **NOT** split: critical path structurally identical (13 levels, 2× DSP48E2 combinational); the gain came from **route** (1.360 → 1.058 ns), **logic flat** (3.085 → 3.101). Better placement, not a register insertion.
- **Why:** csynth `200-887` names the residual chain **`hadd`(res, kernel:1445) → `hsub`(kernel:1454), 10.21 ns**, and `res` is the **loop-carried** var (`200-880`). The fp chain that's left is **inside the `res→resq` recurrence** — can't register without II=3. (II=3 @ 300 = 100 Mop/s **loses** to II=2 @ 239 = 120.)
- **Conclusion:** scheduling knobs can't reach 300 MHz. Only structural fixes do: **(a) fixed-accumulator / restructure the `res→hsub` dependency**, or **(b) int16** (collapses the chain).

## MUL rebalance (2026-08-04) — 251 MHz banked, and the wall MOVES off fp-mul
`final_final/mulbal_{fabric,fulldsp}/` — swap the fp16 MUL's HLS `impl` at constant latency-3 (keeps II=2). Guarded (csynth-complete + real routed report required; earlier parallel run gave a FALSE 300 = missing-report defaulting to WNS 0). All II=2 verified:
| mul impl | routed WNS | Fmax | critical path |
|---|---|---|---|
| `max_dsp` (was banked) | −0.849 | 239 | fp16 **multiply** (2 DSP, 69% logic) |
| `no_dsp` (fabric) | −0.830 | 240 | ~same |
| **`full_dsp`** ⭐ | **−0.657** | **251** | **fabric add/sub + mux** (20 lvl, 8×CARRY8, 51% route) — **mul off-path** |
- **`fulldsp` = new best: 251 MHz, II=2** (+18 over 233 final chip), one `bind_op` change. **Adopt as banked point.**
- **Wall MOVED:** fulldsp puts the mantissa mul in DSP → fp-mul leaves the critical path; new wall = **fabric fp `hadd`/`hsub`** (`no_dsp`) + `sparsemux` operand mux (csynth 200-887: `sparsemux(k:1010)→hsub`, `hadd→hsub`). → the custom-multiplier lever is now **moot**; remaining lever = the fabric add/sub (recurrence-bound) or mux, with placement headroom (51% route).
- **Standing: 233 → 251 MHz at II=2, honestly, via 2 free knobs.** Still <300; closing it means attacking the recurrence-bound fabric add/sub — diminishing returns. Per the RTL-baseline finding (no faithful FPGA fp Fmax for golden EVA — DesignWare ASIC IP black-boxes), 251 is a strong **FPGA-native absolute**, not a gap-vs-RTL.

### add/sub-on-DSP (2026-08-04) — LOSS, ruled out (`alldsp_fulldsp/`)
Patched `hadd`/`hsub` bind `fabric → fulldsp` (all 3 fp ops on DSP), mul already fulldsp, II=2 held. Routed **128 MHz** (WNS −4.493, 27 levels: DSP_MULTIPLIER + 2×DSP_ALU + DSP_PREADD + 10 LUT + MUXF7). **Big regression** — fp16 add/sub is naturally a FABRIC op (variable-shift align→add→normalize); DSP has no alignment path, so forcing it on creates a DSP↔fabric round-trip AND re-chains mul+add across DSPs. → **"more ops on DSP" lever CLOSED.** Sweet spot = **mul on DSP, add/sub in fabric = 251 MHz** (`mulbal_fulldsp/`), the banked best.
- ⚠️ **251/fulldsp is QoR-proven, correctness NOT yet re-cosim'd** (bind change → can't reuse 13h maxdsp 8x8 RTL; Xilinx FP cores are bit-identical across impls so values SHOULD match, but unverified). Promote to "final chip" only after a cosim re-check.
- **Remaining levers:** (1) fanout/floorplan on the 251 fulldsp path (51% route, fo≈21-29 nets) — small; (2) **int16** — 1-cyc ALU deletes fabric fp add/sub + mul DSP, enables II=1, only route that clears 300.

### LEAN #1 (2026-08-04) — delete hsub, 254 MHz, bit-exact ⭐ NEW BEST
Source-level: `a-b === a+flip_sign(b)` (IEEE-exact). Chip `..._leanalu.py` (ALU rewritten: `bbits=b.bitcast(); if SUB bbits^=0x8000; res=a+b_eff`). Deletes the fabric `hsub` (the 200-887 endpoint) + one mux arm. `lean_1x1/`: **hsub instances=0**, node II=2 held, routed **254 MHz** (WNS -0.606), crit path now a SINGLE fabric `hadd` (18 lvl, 7×CARRY8). **PROVEN bit-exact 4 ways:** (1) 32.8M fp16-pair identity 0 mismatch; (2) mmm 4/4 Allo-sim; (3) **fft2 SUB path base==lean bit-exact** (out1=in0-prod=0.5 correct); (4) hsub=0 in RTL II=2. **Journey: 233→239(clk_unc)→251(fulldsp mul)→254(#1), all II=2, honest.**
- **+3 not +30:** #1 removed the REDUNDANT subtractor+mux-arm; what remains is the ONE fabric fp adder on the res→resq recurrence = irreducible fp16-add core. → reviewer's #2(compare)/#4(bitwidth) touch control/mux (no longer the tail, diminishing); #3(resq→shift-reg) still aimed at real depth; only **int16** collapses the adder → 300+.
- ⚠️ 254/lean QoR-proven + Allo-sim-correct; 8x8 RTL streaming cosim NOT yet run (needs fresh 13h csynth on `..._ts_leanalu`). Bank 254 as fp16 floor; commit 8x8 cosim only to lock final.

### 254 is the fabric fp16-add FLOOR — physical levers exhausted (2026-08-04)
Netlist probe of the 254 lean path (`lean_1x1/probe_fanout.tcl`): all high-fanout nets (fo=24-31) are **INTERNAL to the Xilinx hadd IP** (`ADDSUB_OP.ADDSUB/{EXP/NUMB_CMP, NORM/LZE, ALIGN_BLK/FRAC_ADDSUB}`), NOT control broadcast. → **fanout/floorplan (MAX_FANOUT/pblock) is DEAD** (can't replicate/restructure inside a fixed IP, same wall as retiming null); **#4 bitwidth won't touch this path** (tail is IP align/normalize, not sb_* — still worth it for AREA + 2nd/3rd paths). Path IS align→frac-add→normalize = textbook fp-add long pole. **Only int16 (1 CARRY8, no align/norm) breaks it.**

### ✅ LOCKED (2026-08-05): 8x8 LEAN cosim COMPLETE — 254 MHz is COSIM-VERIFIED FINAL
Streaming cosim (B=300) on the lean+fulldsp 8x8 RTL: **ALL 6 workloads PASS bit-exact vs golden** — mmm(p6) 8/8, fft(p3) 8/8, cordic_cr/cv/hr/hv(p3) 8/8 each, all `*** C/RTL co-simulation finished: PASS ***`, `LEAN_LOCK_COMPLETE`. The #1 (a-b→a+flip(b)) + fulldsp-mul chip is now proven correct in REAL 8x8 RTL, not just Allo-sim. **254 MHz II=2 = the cosim-verified final fp16 chip.** RTL kept `/work/shared/users/zsm9/eva_leanfulldsp8x8_rtl/wd`; logs `final_eva_performance/results/lean_cosim/`. TB=fixed cordic gating (build_golden_cosim.py:92-101 even=1word/odd=2word, matches golden). NOTE: read 2nd-verdict (real-data) lines for throughput; 1st cosim pass is all-zero (known two-verdict behavior).

### (superseded) RUNNING (2026-08-04 21:52): 8x8 LEAN LOCK — csynth ~13h + streaming cosim
`overnight_lean_reverify.sh` (PID 2891139, monitor b2s0v0qag). Kernel `eva_leanfulldsp8x8_rtl/kernel_lean_fulldsp_sched.cpp` = NOSCHED codegen of `..._ts_leanalu` + `inject_pragmas_fulldsp.py` (64 hmul fulldsp, 64 hadd fabric, 0 hsub, 64 pipeline, 0 dep-false, clk_unc 0.9). Proves #1 bit-exact at 8x8 RTL on all 6 WL → promotes 254 to COSIM-VERIFIED. Results `final_eva_performance/results/lean_cosim/`.
- **233→254 journey = the finding** (each stage moved the wall to a NEW structure, semantics proven unchanged): 239 SCHEDULING (clk_unc), 251 OPERATOR-BINDING (fulldsp mul, wall mul→add/sub), 254 SOURCE-ALGEBRA (#1 hsub delete, wall →irreducible adder). Endpoint MHz matters less than naming+proving each limiter.
- **NEXT (parallel-ok):** int16 design-point (separate Q: datatype cost; only route to 300+). Reviewer's #2(single compare)/#3(resq→shift-reg)/#4(bitwidth) = area/2nd-path, not this 254 tail.

## ⭐ int16 DESIGN POINT (2026-08-06) — II=1 achieved, ~1.75× faster/PE, smaller, bit-exact
Chip `eva_int16/eva_int16.py` = dual-type copy of rtprime (IS_FLOAT meta_if wraps 36 bitcast sites; int16 = direct no-op, no `union{uint16;half}`). int16 ALU = **1-cycle integer** ops → the `resq` recurrence fits **II=1 honestly** (what fp16 never could). All prior-computed (`eva_int16/`, 2026-07-25):
| | fp16 final (lean) | **int16 (II=1)** |
|---|---|---|
| II | 2 | **1** ✅ |
| node Fmax | 254 MHz | **223 MHz** (WNS −1.169, 4.482ns) |
| full 1×1 Fmax | 254 MHz | 214 MHz (WNS −1.311) |
| node LUT/FF/DSP | 3460/2680/1 | **2681/1594/1** (smaller — no fp datapath) |
| correctness | bit-exact | ✅ bit-exact vs analytical int X@W (cosim PASS) |
| crit path | fabric fp16 adder | **control mux** (`sparsemux` in node_0_0_Pipeline, 4.48ns, 45% route) |

**Net throughput/PE = Fmax×(1/II): fp16 254/2=127 vs int16 223/1=223 M-issue/s → int16 ~1.75× FASTER** + smaller area. **The datatype answer: int16 wins on throughput** (breaks the II=2 recurrence), trades a little Fmax for a big II gain.

**int16 wall CORRECTED (bitwidth sweep 2026-08-06, `eva_int16/pnr_narrow_ii1/`):** narrowed sb_* flags (6 bool→UInt1, dir→UInt2, ix→UInt4) → II held 1, codegen clean, but **222 MHz = NO CHANGE** (WNS −1.169 identical, path byte-identical, LUT 2681 identical). → the int16 wall is **NOT the sparsemux/scoreboard** (my earlier guess WRONG); it's the **int16 DSP-multiply chain** (17 levels: DSP_MULTIPLIER+DSP_ALU+DSP_PREADD+DSP_M/OUTPUT + 10 LUT → control). Same structural story as fp16 (DSP-mul-dominated), integer not float. sb_* were never on the path; Vitis already packed them. **To beat 223: attack the int16 mul→control chain** (register between mul & downstream, or remap mul), NOT the control widths. #4 bitwidth = confirmed no-op here. Recorded [[eva-int16-dual-type]].
