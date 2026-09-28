# EVA-in-Allo — Chip Comparison, Verification & Findings

Consolidated results for the EVA accelerator rebuilt in Allo HLS, across four
execution-model variants. This is the authoritative writeup; per-chip detail
is in `README.md`, full history in `../BUBBLE_MODEL_PLAN.md` + agent memory.

## 1. The four chips

| chip | model | one-line |
|------|-------|----------|
| **eva_prime** | always-fire / bubble | baseline, faithful port of `eva.py`; II=4 |
| **eva_sb** | + scoreboard | metadata scoreboard retires fp latency as depth → II=1 (2025.1) |
| **eva_sb_syscredit** | + systolic credits | adds golden `rq/gt` backpressure → **lossless** |
| **eva_sb_nb** | event-driven (NB) | non-blocking router, no bubbles — **PARKED** (sim non-deterministic) |

## 2. Routed QoR (final_runs, 1×1 node, PLACE & ROUTE)

All controlled: same source params (M=N=1, NSTEP=10, BUF/DRF/IRF/SB depths,
`partition_rf` incl. irf), datatype fp16. Two consistent sets by tool+part.
Fmax = 1000/CP. Resources = post-impl LUT/FF/DSP.

**Set A — Vitis 2023.2 / xcu280** (all timing MET)
| design | II | routed CP | Fmax | LUT | FF | DSP |
|---|---|---|---|---|---|---|
| eva_prime | 3 | 3.077 ns | 325 MHz | 5602 | 4645 | 0 |
| eva_sb | 3 | 2.972 ns | 337 MHz | 4620 | 4300 | 0 |
| eva_sb_syscredit | 3 | 2.955 ns | 338 MHz | 5247 | 5536 | 0 |

**Set B — Vitis 2025.1 / xczu7ev** (clock target 3.33 ns)
| design | II | routed CP | Fmax | timing | LUT | FF | DSP |
|---|---|---|---|---|---|---|---|
| eva_prime | 3 | 3.112 ns | 321 MHz | ✅ met | 4642 | 5123 | 2 |
| eva_sb | **1** | 3.630 ns | 275 MHz | ❌ miss (WNS −0.30) | 3872 | 3656 | 6 |
| eva_sb_syscredit | **1** | 3.413 ns | 293 MHz | ❌ miss (WNS −0.083) | 4634 | 4461 | 6 |

*(eva_sb/syscredit also routed on 2023.2/xczu7ev at II=3: 3.130 & 2.944 ns, both MET.)*

**Headline findings**
1. **On 2023.2 the scoreboard buys nothing** — eva_prime, eva_sb, syscredit
   are all II=3 at ~325–338 MHz. Same schedule (irf partitioned → II=3; see
   §3a). The scoreboard's win is scheduler-gated.
2. **II=1 appears only on 2025.1** — the `dependence inter=false` pragmas
   (Allo has no primitive, §4) let the 2025.1 scheduler break the result-ring
   recurrence 2023.2 can't. But II=1 **costs clock**: 275–293 MHz, MISSING the
   300 MHz target, vs the II=3 baseline that MEETS it at 321 MHz.
3. **syscredit ≈ eva_sb cost**: +credit planes add ~600–800 LUT and, at II=1,
   actually route *faster* (3.413 vs 3.630 ns) — lossless is nearly free.
4. Tool artifact: 2025.1 maps fp16 to 6 DSP vs 2023.2's 0–2 (fp-core choice).

## 3a. Why `irf` partitioning changes II (fetch recurrence)
`irf` unpartitioned = a LUTRAM whose read is **registered (latency 1)**.
EVA's PC (`instr_cnt`) is loop-carried and its next value depends on the
just-fetched-and-decoded instruction (fetch → decode → grant → PC-advance).
So the irf read sits **inside a loop-carried recurrence**, and its 1-cycle
read latency adds directly to the II. Partitioning irf → combinational
register read (latency 0) → recurrence shrinks by 1 → II 4→3. (A read that
were *not* in a recurrence would not affect II — this is EVA-specific because
the program counter self-selects from the fetched instruction.)

## 3. Verification & Backpressure (the 3 working chips)
| | eva_prime | eva_sb | eva_sb_syscredit |
|---|---|---|---|
| Backpressure / lossless | drop ❌ | drop ❌ | **credits, lossless ✅** |
| Sim functional | 7/7 + MMM + FFT2/8 | 7/7 + workloads | **11/11** + MMM + FFT2/8 |
| RTL cosim (bit-exact) | 9 tests + MMM + FFT2 + FFT8 | **12/12** (+ FFT8) | 11/11 (FFT8 blocked, §7) |

## 3. Clocks-per-result (the honest throughput metric)

II alone misleads. On **serial (RAW-dependent) kernels** — EVA's actual
workloads — a dependent instruction costs ~1+SB_DEPTH architectural cycles on
the scoreboard, so:

| chip | clk / dependent-instruction |
|------|------------------------------|
| eva_prime | II=4 × 1 = **4** |
| eva_sb / syscredit | II=1 × ~6 = **~6** |

**Scoreboard II=1 does NOT beat baseline on serial code** — it pays off only
with ILP ≥ SB_DEPTH or interleaved independent streams. Report II=1 with this
asterisk.

## 4. Expressiveness gaps (what Allo CANNOT express — the extension case)

| capability | needed for | status | evidence |
|---|---|---|---|
| `bind_op latency=0` | combinational fp (II=1 monolithic) | no primitive | comb arm inexpressible |
| `s.dependence inter=false` | scoreboard ring → II=1 | **no primitive** | II=3→1 flips on exactly 2 hand-added pragmas (kernel.cpp:211/218) |
| non-blocking streams | event-driven / elastic model | **sim-only** (HLS printer emits nothing) | `eva_sb_nb` runs in sim on `allo_sup`, cannot csynth |

These three are the concrete motivating cases for extending the Allo backend.

## 5. Findings vs golden EVA RTL

- **Golden systolic plane uses `rq/gt` backpressure** (`sync_register.sv`:
  2-slot, stall-not-drop). `eva.py`'s drop-on-full is a **modeling deviation**
  faithfully carried into eva_prime/eva_sb. `eva_sb_syscredit` repairs it.
- Ironically the **old event-driven Vitis** model (FIFO backpressure) is
  *closer to golden* on this axis than the always-fire model built to match
  eva.py.
- The `eva_workloads` input-spacing constants are artifacts of the drop
  deviation, not EVA architecture. (eva_sb workloads only run when the
  perimeter feed rate is dilated to the slower scoreboard consumption rate.)

## 6. Bugs found & worked around (all in Allo backend)

1. **UInt bit-slice emitted SIGNED** → `(x>>15)==1` unreachable → dead-PE DCE.
   Fixed by signedness-immune guards. (`Allo/bugs/uint_slice_signed_emission.py`)
2. **UInt→int32 store sign-extends** in vhls vs zero-ext in sim → only rq=1
   packets recorded to `rout_*` expose it. Worked around with `PMASK`.
3. **fp16 bitcast union has deleted default ctor** → g++8.3 refuses → all Allo
   fp16 designs un-cosim-able. Scripted `= {}` patch in `gen_kernel.py`.
4. **RTL deadlock** (always-fire read-before-write) → initial-token priming +
   credit-RTT-scaled NSTEP.

## 8. Full simplification audit vs golden `EVA_untouched` RTL

Careful feature-by-feature comparison (golden RTL read 2026-07-11:
`pe_pipeline{,_extended}.sv`, `instruction_control.sv`, `pe_core{,_extended}.sv`,
`data_register_file*.sv`, `instruction_register_file*.sv`, `router*.sv`,
`sync_register.sv`, `systolic_{rx,tx,driver,collector}*.sv`, `array_memory.sv`,
`shared_memory.sv`, `private_memory.sv`, `array_control_registers.sv`,
`pe_array.sv`, `pe_group{,_extended}.sv`).

### Faithful (verified identical)
- Base ISA exact: ADD/SUB/MULT/MOV 0x0–3, RTR 0x4–7 (dir=op[1:0]), GEQ/LT 0x8/9,
  CRTR 0xC–F. Compare result = fp16 ±1.0 (0x3C00/0xBC00). Sticky condition reg
  for CRTR. Packet widths id4/mode1/addr4/data16/rq1. Fetch/iter control
  (fetch_st, instr_size, iter_size=0=forever). DRF/IRF depth 8. DRF full/empty
  sync-mailbox (stall-when-full, no bypass).

### Simplifications / omissions
| # | omission | golden | our Allo | buildable? |
|---|---|---|---|---|
| A1 | **DIV/SQRT ops** | `fpu_extended.sv` op 0xA/0xB, fp16_div/sqrt_ppl, 2cyc | **DONE** → `top_extended` region | **BUILT (csynth ok)** |
| A2 | **Heterogeneous col-0 PEs** | `pe_core_extended` only in physical col 0 | **DONE** → `meta_if(j==0)` gates div/sqrt to col 0 | **BUILT (1×2 verified)** |
| A3 | cycle-accurate FPU pipe + forwarding | 4/5-stage, add/mult=1 div/sqrt=2, hazard-stall+fwd | HLS-inferred + scoreboard abstraction | **NO (not cycle-accurate)** |
| B1 | **8×8 = 64 PE, 4×4 groups of 2×2** | full hierarchy | flat M×N, routed only 1×1 | **YES sim / PARTIAL P&R (codegen scale)** |
| C1 | systolic rq/gt lossless backpressure | sync_register 2-slot stall-not-drop | prime/sb drop; **syscredit faithful** | **DONE (syscredit)** |
| C2 | router 2-slot skid + fixed priority | per-dir skid, col>row, core-send>fwd | approximate depth/arb | **PARTIAL** |
| D1 | **shared driver+collector array bank** | one dp_ram both read+written | split in_/out_ buffers | **NO (Allo 200-976 single-owner)** |
| D2 | dual per-PE banks (rtr+sys) + cross-tile shared | private_memory/shared_memory cross-access | neither | **PARTIAL (banks yes, one-array-2-owner no)** |
| D3 | **AXI host/DMA port** | 3-deep AXI rd, 2×16→32 pack | none | **YES (m_axi) but cosim-blocked** |
| E1 | driver/collector DMA addr-gen FSM | st_addr/incr/len, local/remote sel | plain feeder | **YES** |
| E2 | array_control_registers plane | CNFG/BYPS/TRIG/CFGREGF per side/PE | only instr/iter/fetch | **YES (tedious)** |
| E3 | banked IRF (2-bank even/odd) | interleave | single bank | **YES (functionally equiv already)** |
| F1 | **RISC-V CPU tile** | riscv_alu, riscv_alu_div | absent (PE-array only) | **YES (have RV32IM core) but out of scope** |
| G1 | **ISA instruction ENCODING** | `[15:12]=OP,[11:8]=DST,[7:4]=RS1,[3:0]=RS2`; MOV/SQRT src=RS2 | `[3:0]=OP,[7:4]=DST,[11:8]=S1,[15:12]=S2`; MOV/SQRT src=S1 | **bridged by translator** (semantic, not raw nibble-reverse) |

**Golden RTL cross-check (2026-07-11):** `Allo/EVA/tests/replay_golden_mmm.py`
runs the golden EVA_untouched MMM program+weights+activations (from
`tb/pe_array/mmm`, translated per G1) through our 8×8 `eva.py` and diffs against
the golden RTL's captured `sys_tx_btm` outputs (`/home/zsm9/eva_tb_logs/pe_array_mmm.out`):
**16/16 BIT-EXACT** — first true Allo==golden-RTL check (prior cosim only proved
Allo-sim==Allo-RTL). Encoding deviation G1 surfaced here (opcode values/semantics
match; only field positions + MOV/SQRT operand slot differ).

**FFT cross-check (2026-07-11):** `replay_golden_fft.py` — golden 8-pt FFT
(`tb/pe_array/fft`, west in / east out `sys_tx_rgt`, 2 twiddle DRF slots, RTR
shuffles, complex butterfly) → **16/16 BIT-EXACT** vs golden RTL. Validates the
G1 translator on RTR/CRTR (UMOV/DMOV) too. So both MMM and FFT confirm the Allo
rebuild's compute + interconnect are golden-faithful. NEXT: router/ldl/cordic.

Full prose list + buildability rationale: chat log 2026-07-11.

### A1 DIV/SQRT implemented — `top_extended` region (2026-07-11)
`final_runs/eva_sb_syscredit.py` now holds a SECOND dataflow region
`get_eva_top_extended` / `top_extended` — a verbatim copy of the base region
(base `get_eva_top` byte-identical, untouched) plus `OP_DIV=0xA` (`res=a/b`) and
`OP_SQRT=0xB` (`res=sqrt(a)`, via fp16→fp32→`allo.sqrt`→fp16 since `math.SqrtOp`
has no f16 path). Build: `python eva_sb_syscredit.py extended` →
`fin_prj_eva_sb_syscredit_extended`. **csynth PASS on 2023.2/xcu280** (exit 0,
RTL for `top_extended`, Fmax ~250 MHz).

**Scoreboard resized for div/sqrt latency** (2026-07-11): the extended execute
stage synthesizes `fsqrt_32ns_32ns_32_12` (**12-cyc** sqrt) + `hdiv_16ns_16ns_16_8`
(**8-cyc** div). Base rule = `SB_DEPTH = op_latency+1` (5 = add-4 +1), so the
extended region shadows the globals to `SB_DEPTH,RESQ_DEPTH = 13,16` (13 ≥ 12;
RESQ pow2 > SB for the `&(RESQ-1)` ring mask) — via a closure local in
`get_eva_top_extended`, so the **base region stays 5/8**.

**II=1 verification needs 2025.1**, NOT this host: on **2023.2 the scheduler
caps II regardless** — the *base* region measures **II=3** here (confirmed
2026-07-11, matches Set A), and the extended region **II=13** (the 12-cyc
analog). II=1 only appears on 2025.1 where the `dependence inter=false` pragmas
(all 4 present in the extended kernel) are honored and break the resq
recurrence. WITHOUT the resize (`SB_DEPTH=5<12`) the ring can't hold the sqrt
result → even 2025.1 couldn't reach II=1; WITH it (13≥12) it should, mirroring
base II=3→II=1. Prepared: `final_runs/vitis25_syscredit_extended.ini`
(`syn.top=top_extended`) → run on zhang-21, check `Final II` of `l_S_t_0_t`.

Caveats: **Sim can't verify sqrt** — this host's LLVM JIT (dataflow simulator
pipeline, `backend/simulator.py`) omits `convert-math-to-llvm`, so `math.sqrt`
reaches translation untranslated (`missing LLVMTranslationDialectInterface`);
`allo.sqrt` itself is genuine (LLVM backend `test_float64_math_ops` runs it).
div sims fine; sqrt sim now WORKS via `convert-math-to-llvm` added to
`allo_ext/allo/backend/simulator.py` (logged in `allo_ext/BACKEND_CHANGES.md`;
pristine install untouched — run sim with `PYTHONPATH=/home/zsm9/allo_ext`).
DIV+SQRT numerically verified through the full chip (6 vectors PASS,
`verification/test_divsqrt_sim.py`). SQRT reads operand a (matches
`allo/tests/dataflow/eva_pe_core.py`); golden reads operand-2.

**Column-0 gating (A2, DONE):** div/sqrt arms wrapped in
`with allo.meta_if(j == 0):` — a build-time pid gate, so only physical column 0
synthesizes fsqrt/hdiv (golden's heterogeneous mesh). Verified on a 1×2 build:
`node_0_0` has sqrt+div, `node_0_1` has neither (26 fewer lines). A DIV/SQRT
opcode on a non-col-0 PE falls through to MOV. At M=N=1 identical to before.

## 7. Open items

- syscredit **routed timing** (P&R) — needs 2025.1 (zhang-21); ini prepared.
- syscredit **fft8r RTL** — blocked on 8×5 Allo codegen blowup.
- eva_sb **fft8r RTL** — running (overnight batch, F=2).
- NB chip — parked; needs event-driven-termination in Allo sim + printer ext.
- The 3 expressiveness gaps → Allo extension track.
