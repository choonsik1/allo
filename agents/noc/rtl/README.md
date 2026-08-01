# Archived RTL

Catapult output, copied out of `csyn_out/` (which is gitignored and gets wiped by any rebuild).
Regenerate with `python <top>.py csyn`.

## What an ASIC flow needs

**Two files per design — that is all**, plus your own standard-cell `.db`/`.lib`:

| file | role |
|---|---|
| `rtl.v` | the complete netlist. **Self-contained**: every instantiated module is defined inside it, no Catapult library cells, no `$display`/`initial`/`ifdef`. |
| `rtl.v.dc.sdc` | constraints — `create_clock -period 2.0`, I/O delays on every port. |

Catapult's own DC script confirms it analyzes exactly one file:
`analyze -format verilog rtl.v` then `elaborate <top>`.

`cycle.rpt` is kept for reference (Catapult's own per-loop schedule). Not needed by the flow.
Deliberately NOT archived: `concat_rtl.v` (= `rtl.v` + a 2-line comment header, exists for cosim
only) and `rtl.v.dc` (a Design Compiler TCL *script*, not RTL — it hardcodes `MGC_HOME` and
Nangate paths, so treat it as a reference rather than running it).

## Three caveats

1. **The SDC is library-specific.** It names the driving cell explicitly:
   `set_driving_cell -library NangateOpenCellLibrary -lib_cell DFF_X1 -pin Q $data_inputs`.
   Swap for a cell in your library or DC errors on the constraint.
2. **The clock period is baked into the schedule, not just the SDC.** Set at HLS time
   (`-CLOCK_PERIOD 2.0`, characterized against `nangate-45nm_beh`). Relaxing the SDC is safe;
   **tightening it is not** — to target a faster clock, re-run csynth with a new period, because
   that changes how many operations Catapult packed per cycle.
3. **No memory macros anywhere.** Even `pe_stream`'s `AlloMem` synthesized to flops rather than a
   RAM instance. Convenient here, but any design with a real array will be enormous in gates —
   point Catapult at a memory library *before* csynth.

## Interface style of every emitted top

`clk`; `rst` **async ACTIVE-LOW** (`always @(posedge clk or negedge rst)`); a `done` output (an
Allo-added completion flag aggregated from the per-kernel dones — not part of the dataflow, tie
off if unused); and one `<v>_vld` / `<v>_rdy` / `<v>_dat[W-1:0]` triple per port. The block does
not self-start — something must drive and sink the handshake.

## The designs

| dir | source | what it shows | verified |
|---|---|---|---|
| `hello_channel/` | `../hello_channel.py` | the minimal `Channel[int32, valid_ready]`: prod → link → cons. 8 modules, 522 lines. The channel is three top-level wires (`v10_vld`/`v10_rdy`/`v10_dat`) joining `u0` straight to `u1` — no module, no register, no storage. | csim, csynth, **Xcelium cosim bit-exact** |
| `pe_channel/` | `../pe_split.py` | same PE split across a `Channel` boundary. 22 modules. | csim, csynth, **Xcelium cosim bit-exact** |
| `pe_stream/` | `../pe_split.py` | the control: identical arithmetic, but a `Stream[int32,2]` boundary. Costs 5 extra RTL modules (`AlloFifo` + enq/deq threads + an FSM each) and 137 more register bits, 128 of which are the four 32-bit FIFO datapath registers. | csim, csynth |
| `pe_wire/` | `../pe_split.py` | the `Wire` boundary. **Archived for reference only — this design FAILS csim (reads all zeros).** A Wire gives neither storage nor handshake, so it has no synchronisation at all. | csynth only |

The `pe_stream` vs `pe_channel` pair is the measurement: same computation, differing only in the
link type, which isolates what the handshake costs versus what the buffer costs.
