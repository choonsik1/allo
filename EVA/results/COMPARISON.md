# EVA vs golden RTL — faithfulness, simplifications & Allo-expressiveness gaps

How the Allo rebuild relates to the original hand-written EVA RTL (`EVA_untouched`): what it
reproduces bit-exact, what it simplifies or omits, and the things Allo *can't* express (the motivation
for extending the backend). Chip-by-chip numbers are in [`EVALUATION.md`](EVALUATION.md); design
choices in [`DESIGN_RATIONALE.md`](DESIGN_RATIONALE.md).

## 1. Golden cross-check — Allo == golden RTL, bit-exact

The Allo rebuild is checked directly against the original EVA RTL (not just Allo-sim vs Allo-RTL): the
golden program + weights + activations from `EVA_untouched/tb/pe_array/*` are run through the Allo 8×8
mesh and diffed against the golden RTL's captured edge outputs.

| workload | result | vs |
|---|---|---|
| **MMM** | **16/16 bit-exact** | golden `sys_tx_btm` (`tb/pe_array/mmm`) |
| **FFT (8-pt)** | **16/16 bit-exact** | golden `sys_tx_rgt` (west-in / east-out, twiddle DRF, RTR shuffle, complex butterfly) |

Both confirm the compute *and* interconnect are golden-faithful. The final chips extend this to all six
workloads at 8×8 RTL cosim — see [`EVALUATION.md`](EVALUATION.md).

## 2. Faithful (verified identical to golden)

Base ISA exact: ADD/SUB/MULT/MOV `0x0–3`, RTR `0x4–7` (dir = op[1:0]), GEQ/LT `0x8/9`, CRTR `0xC–F`;
compare result = fp16 ±1.0 (`0x3C00`/`0xBC00`); sticky condition reg for CRTR. Packet widths
id4/mode1/addr4/data16/rq1. Fetch/iter control (fetch_st, instr_size, iter_size=0=forever). DRF/IRF
depth 8. DRF full/empty sync-mailbox (stall-when-full, no bypass).

## 3. Simplifications / omissions vs golden

| # | golden feature | our Allo | status |
|---|---|---|---|
| A1 | DIV/SQRT ops (`fpu_extended`, op `0xA/0xB`) | `top_extended` region, col-0 gated | **built** (csynth ok) |
| A2 | heterogeneous col-0 PEs | `meta_if(j==0)` gates div/sqrt to col 0 | **built** (1×2 verified) |
| A3 | cycle-accurate FPU pipe + forwarding | HLS-inferred + scoreboard abstraction | not cycle-accurate |
| B1 | 8×8 = 64 PE, 4×4 groups of 2×2 | flat M×N | **8×8 sim + RTL cosim + node P&R done** (`final_chips`); full-hierarchy grouping abstracted |
| C1 | systolic `rq/gt` lossless backpressure | drop in early chips; **credit plane faithful** (v2.0) | **done** |
| C2 | router 2-slot skid + fixed priority | approximate depth / arbitration | partial |
| D1 | shared driver+collector array bank | split `in_`/`out_` buffers | Allo single-owner limit (200-976) |
| D2 | dual per-PE banks + cross-tile shared | per-PE banks yes; one-array-two-owner no | partial |
| D3 | AXI host/DMA port | none (or `m_axi`, cosim-blocked) | not integrated |
| E1–E3 | DMA addr-gen FSM · control-register plane · banked IRF | plain feeder / single bank | buildable, not done (functionally equivalent) |
| F1 | RISC-V CPU tile | RV32IM core exists (`Allo_IPs/`) | separate track (C-tile; out of scope for the A-tile eval) |
| G1 | ISA field encoding (`[15:12]=OP…`) | different field positions | **bridged by a semantic translator** (opcodes/semantics match; only field positions + MOV/SQRT operand slot differ) |

DIV/SQRT detail: the extended region resizes the scoreboard to `SB_DEPTH, RESQ_DEPTH = 13, 16` for the
12-cycle sqrt / 8-cycle div (the base region stays 5/8). DIV+SQRT are numerically verified end-to-end
(6 vectors pass); sqrt sim needed `convert-math-to-llvm` added to the simulator backend (logged in
`BACKEND_CHANGES.md`).

## 4. What Allo can't express — the extension case

| capability | needed for | status |
|---|---|---|
| `bind_op latency=0` | combinational fp (monolithic II=1) | no primitive |
| `s.dependence inter=false` | break the scoreboard result-ring recurrence → II=1 | no primitive (hand-added pragmas) |
| non-blocking streams | the event-driven / elastic (v3.0) model | needed a SystemC / printer backend extension |

These are the concrete motivating cases for the Allo backend work — the SystemC emitter + latency-
insensitive channels (see the repo root `README.md`).

## 5. Backend bugs found & worked around (all in the Allo backend)

1. **UInt bit-slice emitted signed** → `(x>>15)==1` unreachable → dead-PE DCE. Fixed with
   signedness-immune guards (`Allo/bugs/uint_slice_signed_emission.py`).
2. **UInt→int32 store sign-extends** in vhls vs zero-extends in sim → worked around with `PMASK`.
3. **fp16 bitcast union has a deleted default ctor** → g++ refuses → all fp16 designs un-cosim-able.
   Scripted `= {}` patch in codegen.
4. **RTL deadlock** (always-fire read-before-write) → initial-token priming + credit-RTT-scaled NSTEP.
