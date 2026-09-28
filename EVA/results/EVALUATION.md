# EVA — Evaluation: Allo→Vitis HLS chip vs. original EVA RTL

*Apples-to-apples FPGA comparison of our Allo/HLS EVA implementation against the original
hand-written EVA RTL, plus the productivity/correctness story. All FPGA numbers target the
**same device** `xczu7ev-ffvc1156-2-e` at the **same** 3.333 ns (300 MHz) clock target.*

Companion to `DESIGN_RATIONALE.md` (which explains *why* the final chip is what it is). This file
is the *quantitative* evaluation. Cells marked ⏳ are pending a run; the exact source report is named.

---

## 0. Two measurement flows (both required, complementary by design)

The original EVA repo already separates these — the perf TB even prints *"[7] Area — REQUIRES
SYNTHESIS"*, deferring area to the synth flow.

| Flow | Tool | Produces | Script |
|---|---|---|---|
| **Static** | Vivado synth+P&R | Fmax (WNS), LUT/FF/DSP/BRAM, power (W) | `/work/shared/users/zsm9/eva_orig_rtl_pnr/run_synth.sh` |
| **Dynamic** | VCS RTL sim | cycles, latency, throughput (outputs/cyc), CPI, stalls, pipeline util | `EVA_org_claude/EVA/rsim/perf` → `make sim` |

**Real-time throughput = (outputs/cycle from VCS) × (Fmax from Vivado).** Neither flow alone suffices.

### FP16 fidelity note (important for area validity)
The PE's fp16 arithmetic is **Synopsys DesignWare** IP (`DW_fp_addsub/mult/div/sqrt`, release
W-2024.09). The original functional/perf TBs use the **genuine licensed sim models**
(`/opt/synopsys/prime/W-2024.09-SP5/dw/sim_ver/DW_fp_*.v`). For FPGA synthesis we feed those **same
real DW models** to Vivado (`REAL_FP=1`, the default) — Vivado strips their `parameter_check`
`initial` block and synthesizes the real fp datapath. The repo's `vivado_stubs.v` (zero-constant
black boxes) are **NOT used** for QoR (they were elaboration-only). Caveat to state in the paper:
the RTL's fp is DesignWare arithmetic *mapped onto* FPGA fabric, whereas our HLS chip's fp is Vitis
`hls::half` (Xilinx-native) — same silicon, fair comparison, but not the identical fp implementation.
The **control/router/systolic/credit fabric** (our actual contribution) *is* directly comparable.

---

## 1. Designs under test

| id | design | description | source |
|---|---|---|---|
| **RTL-orig** | original EVA `pe_array` | hand-written 8×8 fused router+PE mesh (4×4 groups × 2×2 PE), fp16 | `EVA_org_claude/EVA/rtl` |
| **RTL-pe_core** | original EVA `pe_core` | single PE (for per-PE latency/throughput perf TB) | `EVA_org_claude/EVA/rtl/pe_core` |
| **HLS-NOSCHED** | `one_bitstream/` (rtprime) | Allo→HLS 8×8, unpipelined, **correct full suite** | `prime/eva_sb_syscredit_rtprime.py` |
| **HLS-II2** | `sched8x8_ii2/` | same chip + `inject_pragmas_ii2` → II=2 (pipelined) | `prime/` + `inject_pragmas_ii2.py` |
| **HLS-PEcore** | 1×1 PE-core P&R | single-node HLS PE (for per-PE comparison to RTL-pe_core) | `final_chip_1x1/` |

---

## 2. Static QoR — Fmax / area / power  (same part, 3.333 ns target)

### 2a. Full 8×8 mesh — FPGA static QoR
> **RTL-orig FPGA columns = N/A (off-table).** Per the framing (§0, "we reproduce/extend an ASIC
> accelerator"), FPGA P&R of the **original EVA is not a meaningful metric** — it's ASIC-native
> (Synopsys DesignWare fp16, SRAM macros, foundry scan-FFs). The DesignWare fp cells are **not
> Vivado-synthesizable** (they black-box → `opt_design` DRC-fails), so any FPGA number for it either
> excludes fp (fabric-only) or needs unfaithful Xilinx-IP substitution. **EVA's real static QoR
> belongs to an ASIC (Design Compiler) flow, not FPGA.** The FPGA static column that IS valid is
> **our own HLS chip** (FPGA-native) — an absolute number, not a vs-EVA comparison.

| metric | RTL-orig (FPGA) | HLS-NOSCHED 8×8 | HLS-II2 8×8 | source |
|---|---|---|---|---|
| Fmax (MHz) | **N/A** (ASIC-native) | ⏳ | ⏳ | 1000/(3.333−WNS) |
| LUT | N/A | ⏳ | ⏳ | util |
| FF | N/A | ⏳ | ⏳ | util |
| DSP | N/A | ⏳ | ⏳ | util |
| BRAM | N/A | ⏳ | ⏳ | util |
| Power (W) | N/A | ⏳ | ⏳ | report_power |

Recorded for the record (NOT a valid full-area number): an OOC Vivado synth of `pe_array` gave
66,470 LUT / 48,640 FF / DSP=0 — but that's **control-fabric only** (the DesignWare fp black-boxed),
so it undercounts and is not comparable. Flow files kept in `/work/shared/users/zsm9/eva_orig_rtl_pnr/`.
**TODO:** P&R our HLS 8×8 (NOSCHED + II=2) on `xczu7ev` → fills the HLS columns (our design's own QoR).

### 2b. Single PE (RTL-pe_core vs HLS-PEcore) — known HLS points
| metric | RTL-pe_core | HLS-PEcore | source |
|---|---|---|---|
| period / Fmax | ⏳ | **2.924 ns ≈ 342 MHz** | HLS P&R (memory: runtime-prime) |
| LUT | ⏳ | **2548** | HLS P&R |
| full-tile (router+PE) | — | 2.962 ns / 4627 LUT | HLS P&R |
| II=2 1×1 top P&R | — | 4.287 ns ≈ 233 MHz | `final_chip_1x1/ii2/` |

---

## 3. Dynamic performance — cycles / latency / throughput  (VCS perf TB)

From `tb/perf/tb_perf_pe_core.sv` (single `pe_core`, real DW fp). Run: `cd rsim/perf && make sim`.

| metric | RTL-pe_core | HLS-PEcore | notes |
|---|---|---|---|
| [1] config load latency (cyc) | ⏳ | ⏳ | instruction program load |
| [2] min pipeline latency — MOV (cyc) | ⏳ | ⏳ | 1-op passthrough |
| [3] MAC compute latency (cyc) | ⏳ | ⏳ | MOV→MULT→MOV, +hazard stalls |
| [3] hazard stalls (ID/EX1/EX2/WB) | ⏳ | ⏳ | breakdown |
| [4] steady-state throughput (out/cyc) | ⏳ | ⏳ | full stream |
| [4] **CPI (cycles/output)** | ⏳ | ~2 (II=2) / ~4 (NOSCHED) | headline throughput number |
| [5] back-pressure throughput + degrade | ⏳ | ⏳ | consumer 2× slower |
| [6] pipeline utilization (%) | ⏳ | ⏳ | per-stage valid |

**HLS-vs-RTL perf mode:** `make sim_hls` compares against `pe_core/gen/pe_core_hls_rtl.v` — that gen
RTL is **not present**; drop in our HLS `pe_core` RTL to enable it.

Mesh-level throughput: `rsim/pe_array/` TB (TBD whether it prints cycle counts) — else derive from
cyc/output × mesh depth.

### 3b. ⭐ HEAD-TO-HEAD steady-state throughput (both 8×8, streaming, measured the same way)
Original EVA = SV streaming TB (`+REPS=512`, VCS). Allo/HLS II=2 = ts chip `out_cyc` ports, B=300
Vitis RTL cosim (reuses the 13h-synth RTL; L=2000 truncates B=300→~240 words, rate still clean).

| workload | Original EVA (out/cyc·lane) | Allo/HLS II=2 (out/cyc·lane) | Allo cyc/output | correctness |
|---|---|---|---|---|
| **mmm** | **0.250** (4.0 cyc/out) | **0.167** (B=300) | **~6.0** | ✅ 8/8 bit-exact |
| **fft** (prime=3) | 0.154 | **0.045** (B=300) | ~22 | ✅ 8/8 full-stream bit-exact |
| **cordic ×4** | (asymmetric) | **0.036** even / **0.071** odd (B=300, ✅ VALIDATED fixed-TB 2026-08-05) | 28/14 | ✅ 8/8 bit-exact |

**Read:** the Allo II=2 chip is ~1.5–3× slower per output than the hand-tuned RTL (e.g. mmm 0.167 vs
0.250) — the cost of the II=2 schedule vs the original's tight pipeline — at **identical correctness**
and comparable systolic fill (first-out cyc 537). Cosim cost ≈ 30–35 min/workload (RTL reused, no re-synth).

> **fft note (see DESIGN_RATIONALE §3, RESOLVED):** the II=2 fft "holdout" is not a structural failure —
> at the correct prime (3), **streaming drains all 8 rows bit-exact** (single-pass starves the middle
> butterfly rows; `prime=1` is what deadlocks, verified by the reconciliation sweep). fft is streaming-
> correct on the II=2 chip, just throughput-degraded and imbalanced (mid rows 64–66 vs 74 words).

Data: `final_eva_performance/results/allo_stream/` (per-workload `*_B300.log`, `reconcile/`).
Full B=300/B=512 with no L=2000 truncation needs a larger-L re-synth (≈13h).

---

## 4. Correctness (RTL cosim / golden cross-check — already established)

| workload | HLS-NOSCHED | HLS-II2 | oracle |
|---|---|---|---|
| mmm | ✅ 8/8 bit-exact | ✅ 8/8 | golden RTL / cosim |
| cordic ×4 | ✅ 8/8 | ✅ 8/8 (prime=3) | golden RTL / cosim |
| fft | ✅ 8/8 | ❌ ≤4/8 (structural, see DESIGN_RATIONALE §3) | golden RTL / cosim |

One runtime-programmable bitstream runs the whole shipped suite bit-exact (NOSCHED). See
`DESIGN_RATIONALE.md` for the II=2 fft holdout characterization.

---

## 4b. Bottleneck analysis — are the CONNECTIONS a limiter? (NO, evidence-backed 2026-08-05)

Question: do the inter-node connections (systolic links, router, credit plane) cause the two "not-great"
results — Fmax misses 300, throughput ~1.5–3× slower than golden RTL? **Answer: connections are NOT the
primary limiter of either. Fmax is the fabric fp16 adder; throughput is the fp `res→resq` recurrence (II=2).**

| result | limiter | connections' role | evidence |
|---|---|---|---|
| **Fmax = 254 MHz** (misses 300) | fabric fp16 **adder** inside `node_0_0` | **NONE** — ruled out | every routed critical path (239/251/254 chips) sources *inside* the PE; **0 FIFO/stream/link cells** on any critical path; inter-node links are **registered** → break inter-PE paths → Fmax per-node-bound |
| **Throughput II=2** (~1.5–3× vs golden) | fp **recurrence** (res→resq, distance-1) | **second-order** | **mmm stall breakdown: 100% DATA-stall, 0% CREDIT-stall** (instrumented Allo-sim, dedicated dbg counters, K=2: 32 grant/26 data/0 credit). fft cosim shows only **~11% router back-pressure** (mid rows 2,3,6,7 drain 64–66 words vs 74) — real but can't explain the 3.4× gap (that's the long fft program under II=2) |

**Method:** instrumented chip `prime/eva_sb_syscredit_rtprime_stalldbg2.py` — per-PE stall counters
`[idle, grant, data-stall(operand/raw), credit-stall(retire_ok)]` written to a dedicated `dbg[M,N,4]`
output (no mesh link touched, so all workloads uncorrupted). Harness `results/stall_breakdown/`.
**mmm (K=2) measured = 100% data / 0% credit.** fft/cordic stall NOT obtained: the 8×8 (64-PE) Allo
**simulator** spin-wait-lockstep doesn't scale (fft ran 11 h without finishing; fixed 8×8 golden programs
can't be shrunk like mmm). The fft/cordic exact credit-% would only *refine* the ~11% cosim figure — it
cannot overturn the Fmax (proven) or mmm (measured) findings. **Connection question closed: not the wall.**
Caveat: mmm's 0% credit assumes a fast consumer; a bandwidth-throttled downstream would raise credit-stalls.

## 5. Productivity (HLS value proposition)

| metric | RTL-orig | HLS | source |
|---|---|---|---|
| LOC (PE / mesh) | ⏳ count | ⏳ count | `cloc` on both trees |
| LOC ratio | — | ~3.6× smaller (prior finding) | memory: LOC+datatype portability |
| datatype retarget | manual DW swap | one knob (`float16`↔`int16`) | `eva_int16/`, `word_policy.h` |
| design entry | SystemVerilog + DW IP | Python (Allo df) | — |

---

## 6. Figures of merit (derived, once 2–3 filled)

- **GOPS** = 2 × MACs/output × (out/cyc) × Fmax  (fp16 MAC = 2 ops)
- **GOPS/W** = GOPS / power  — energy efficiency
- **GOPS/LUT** or GOPS/DSP — area efficiency
- **Fmax ratio** HLS/RTL and **area ratio** HLS/RTL — the headline HLS-vs-handwritten deltas

---

## 7. What accelerator / HLS papers report (checklist we're covering)

| dimension | typical metric | our source |
|---|---|---|
| performance | Fmax (MHz), throughput (GOPS / out-per-cyc / II), latency | §2, §3 |
| resources | LUT, FF, DSP, BRAM | §2 |
| power/energy | W, GOPS/W | §2, §6 |
| correctness | bit-exact vs golden | §4 |
| efficiency | GOPS/W, GOPS/DSP, perf/area | §6 |
| productivity (HLS papers) | LOC, design time, retargetability | §5 |
| fairness | same part/clock, same fp IP where possible | §0 |

---

## 8. Pending runs (to fill the ⏳ cells)

1. **RTL-orig static** — `run_synth.sh` (top=pe_array, REAL_FP=1) → §2a RTL column + §2b pe_core.
   Reports: `/work/shared/users/zsm9/eva_orig_rtl_pnr/rpt_route_{timing,util,power}.rpt`.
2. **RTL-orig dynamic** — `cd EVA_org_claude/EVA/rsim/perf && make sim` → §3 RTL column.
3. **HLS 8×8 static** — P&R the HLS-NOSCHED / HLS-II2 8×8 chips on the same part → §2a HLS columns.
4. **HLS dynamic** — generate HLS `pe_core` RTL, `make sim_hls` → §3 HLS column (or reuse cosim cyc).
5. **LOC** — `cloc` both trees → §5.
6. Derive §6 once §2–§3 have Fmax + out/cyc + power.
