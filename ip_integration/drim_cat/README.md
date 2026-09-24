# DRIM4HLS with an Allo MMIO stream hook

[ic-lab-duth/DRIM4HLS](https://github.com/ic-lab-duth/DRIM4HLS) is a 32-bit
RISC-V written in SystemC with MatchLib Connections, targeting Catapult. Unlike
HL5 it needs **no port work at all** -- it is natively what the HL5 port had to
be converted into. This adds the memory-mapped stream ports that make it an
Allo SystemC IP.

`upstream/` records the provenance (commit `ad1d23c`, Apache 2.0); the files
here are those sources plus the hook below.

## What changed: 4 files

| file | change |
|---|---|
| `writeback.h` | the two MMIO ports, their `Reset()`s, and the address hook |
| `drim4hls.h` | promotes the ports to the top, forwards them to `wb` |
| `top.cpp` | terminates the channels, drains `mmio_out`, and takes the program from argv |
| `gen_eva_program.py` | **new** -- generates `eva_boot.mem` |

Upstream's `sc_main` hardcodes a path into the original author's home directory
(`/home/dpatsidis/Desktop/...`) with the argv handling commented out, so the
loader silently reads nothing, `imem` stays all zero, and the CPU fetches zeros
for ~230k cycles before dying on "Unimplemented instruction". That cost a debug
cycle; the argument is now taken from the command line.

The hook, in `writeback_th` before the existing dmem branches:

```cpp
if (aligned_address >= MMIO_BASE) {
    if (input.ld != NO_LOAD)       mem_dout = mmio_in.Pop();   // blocking
    else if (input.st != NO_STORE) mmio_out.Push(...);
}
else if (input.ld != NO_LOAD) { ... }   // the original, untouched
```

`MMIO_BASE == DCACHE_SIZE`, so real memory sits entirely below it and the two
can never alias. The load arm writes `mem_dout` exactly as `LW_LOAD` does, so
writeback needs no further change; the store arm issues no dmem transaction at
all. Decode, the ALU and the register file are untouched -- the processor still
executes RV32I exactly as upstream, it just discovers that some addresses are
channels.

This is the same hook as `hl5_cat/` and as the Vitis `rv_stream_ip.cpp`, which
is the point: it is what gives a memory-mapped processor a streaming interface.

## As an Allo IP

```python
allo.IPModule(top="drim4hls", impl="drim4hls.h", sc_clk="clk", sc_rst="rst")
```

`sc_clk`/`sc_rst` are required: DRIM4HLS declares `sc_in<bool> clk` rather than
`sc_in_clk`, so there are two `sc_in<bool>` and the parser refuses to guess.

Six ports are exposed -- `imem2de_data`, `fe2imem_data`, `dmem2wb_data`,
`wb2dmem_data`, `mmio_in`, `mmio_out` (`dirs = "ioioio"`) -- with the six
inter-stage `Combinational` channels correctly invisible.

## The MMIO path is verified

`gen_eva_program.py` emits `eva_boot.mem`: RV32I that walks a packet table in
dmem and stores each word to `MMIO_BASE`. The table is EVA's own 1x1 MMM boot
sequence, from `../ip/rvasm.py` (`eva_mmm_packets`) -- the same generator the
Vitis processor uses, so the expected output is known-good.

```bash
C=/opt/siemens/catapult/2024.2/Mgc_home
g++ -std=c++11 -o drimsim top.cpp -I. -I$C/shared/include     -L$C/shared/lib -lsystemc -Wl,-rpath,$C/shared/lib
LD_LIBRARY_PATH=/home/USERNAME/miniconda3/envs/allo/lib:$C/shared/lib   ./drimsim eva_boot.mem | grep "MMIO OUT"
```

All 11 packets come out and match the golden generator exactly:

    MMIO OUT: 0x2180e13   IRF[0] = 0xE13  MOV r1, SYSLFT
    MMIO OUT: 0x2191022   IRF[1]          MULT r2, r0, r1
    ...                   IRF[4..7] NOP-padded -- all 8 slots written
    MMIO OUT: 0x2003c00   mode=0 data: DRF[0] = fp16 1.0
    MMIO OUT: 0x2110003   cfg1 = iteration count 3
    MMIO OUT: 0x2108300   cfg0 LAST -- bit15 fetch_en, isz=3

So the processor emits a correct EVA boot sequence through the hook.

## Status

- Parses as a 6-port IP, and Allo emits an instantiation binding all of them: ✅
- Compiles, runs, and emits 11 correct EVA boot packets: ✅
- **Synthesised by Catapult** with the hook, and the MMIO ports are real
  ready/valid hardware: ✅ (see below)
- `mmio_in` (the load direction) is untested.
- `drim_eva.h` wraps it into a **1-port packet producer** -- see below.

## drim_eva.h: the shape Allo wants

DRIM4HLS cannot look like the Vitis processor on its own: that one is a pure
producer with its program in a ROM baked into the design, while DRIM4HLS fetches
over a channel and so needs memory served to it. `drim_eva.h` supplies both
memories and exposes ONLY the packet stream:

```
ports  : ['mmio_out']      dirs: 'o'      clk/rst: clk / rst
```

which is exactly `rv_eva_pktsrc`'s shape, so the Allo side needs no special
case. It also keeps DRIM4HLS's struct payloads (`imem_out_t`, `dmem_in_t`, ...)
off the Allo boundary entirely -- the only type that crosses is `sc_uint<XLEN>`.
And because the wrapper declares `sc_in_clk clk` plus a single `sc_in<bool>`,
the clock/reset ambiguity disappears and no `sc_clk=`/`sc_rst=` override is
needed.

The memory servers are adapted from `top.cpp`'s, with two deliberate changes:
the `rand()` stall counts are gone (an IP inside a dataflow region should be
deterministic) and so are the per-access debug prints. The program comes from
`eva_program.h`, generated by `gen_eva_program.py --header` -- baked in, the way
the Vitis processor carries its ROM.

Verified standalone: the wrapper alone, with no external testbench memory,
emits all 11 packets.

## End to end: DRIM4HLS boots an EVA PE that computes

The 1x1 EVA chip built for `target="systemc"` with `RV_PKTSRC` pointed at
`drim_eva` -- 4759 lines of generated SystemC, 21 kernels plus a third-party
RISC-V -- compiles, links, runs, and produces the golden result:

    out_s = [6, 12, 3]

which is what `ip/tb_top.cpp`'s `TARGET_MMM1X1` gets from the Vitis processor.
So a completely different core, on a completely different backend, boots the
same PE to the same answer.

```bash
# 1x1: W = 3, X = [2,4,1]              -> out_s = [6, 12, 3]
python gen_eva_program.py  --header > eva_program.h
python gen_eva_stimulus.py

# 2x2: W = [[1,3],[5,7]], X = [[2,4],[1,3],[5,2]]
#      -> out_s col0 = [22,16,15], col1 = [34,24,29]
python gen_eva_program.py  --2x2 --header > eva_program.h
python gen_eva_stimulus.py --2x2
# then build the chip with target="systemc" (M=N=2, NPKT=22, NSTEP=400)
```

**2x2 is verified too.** One processor drives BOTH west lanes, picking the lane
by store address -- `MMIO_BASE` -> lane 0, `MMIO_BASE+1` -> lane 1 -- exactly
the `MMIO_OUT26` / `MMIO_OUT26B` trick the Vitis IP uses, and for the same
reason: `meta_for` would give every instance the same program, which is useless
once each node holds its own stationary weight. Each lane carries two boot
sequences concatenated, with different weights and different `ident`s (on the
west edge the packet's id field selects the COLUMN). The index register is not
reset between the two loops: the images sit back to back in the table, so
raising the bound to `2n` and falling through walks the second one.

**Allo's generated testbench reads `input*.data` files rather than taking
arguments**, so driving EVA means generating stimulus, not writing a testbench
module. `gen_eva_stimulus.py` writes all 13, mapped in kernel-appearance order;
the only real stimulus is `X = [2, 4, 1]` on the west edge at
`PROG_CYCLES + KLEN*b` plus `iv_n` all 1 as the valid-zero north seed. Nothing
is fed on the router plane -- the array's whole program comes from the
processor.

The weight must match: `eva_mmm_packets(0x4200, ...)` is fp16 3.0, which is what
`TARGET_MMM1X1` uses. With a different weight the expected output changes and
there is no golden number to check against.
- Not connected to EVA. That needs a program that stores packets to
  `MMIO_BASE`, and something serving instruction memory over
  `fe2imem_data`/`imem2de_data` -- DRIM4HLS fetches over a channel rather than
  from a ROM baked into the design, which is the main difference from the
  Vitis processor.

## Catapult synthesis

`synth.tcl` is upstream's `core/hls_to_synth.tcl` with the paths flattened for
this tree -- same Nangate libraries, same 10 ns clock, same register mappings
for the decode/execute arrays. No directives archaeology and no shim were
needed, which is the difference between a design written for Catapult and one
retargeted to it.

```bash
cd drim_cat && catapult -shell -f synth.tcl
```

The top is **`drim4hls`, the processor -- not `drim_eva`**. That wrapper holds
51200-word imem/dmem arrays and their server threads; it exists to make the CPU
look like a pure producer to Allo and is a simulation harness, not hardware.

| | |
|---|---|
| Timing | **met**, slack +2.71 ns |
| Total area score | 55352 |
| Real operations | 2261 |
| Latency / throughput | 37 / 32 |
| RTL | 16798 lines of Verilog |

Four blocks: `fetch` 19 ops, `decode` 917, `execute` 1234, `writeback` 91.

The MMIO hook survives synthesis as ready/valid ports beside the memory
interfaces, so the stream interface Allo drives exists in hardware:

```verilog
module drim4hls (
  clk, rst, program_end, icount, ...,
  imem2de_data_vld/rdy/dat,  fe2imem_data_vld/rdy/dat,
  dmem2wb_data_vld/rdy/dat,  wb2dmem_data_vld/rdy/dat,
  mmio_in_vld/rdy/dat,       mmio_out_vld/rdy/dat
);
```

For contrast, HL5 after restoring its Stratus directives manages throughput 165
and +0.005 ns of slack. DRIM4HLS gets throughput 32 with real margin.

## Synthesising the GENERATED chip

`synth_chip.tcl` puts Allo's SystemC output through Catapult -- a different
question from synthesising DRIM4HLS. That is hand-written SystemC designed for
Catapult; this is generated code, and nothing previously established that it is
synthesisable at all.

```bash
# emit the 1x1 chip with target="systemc" into gen.cpp, then:
catapult -shell -f synth_chip.tcl
```

`tb` and `sc_main` sit in the same generated file and cannot be `-exclude`'d
separately, so the design is named explicitly by `DESIGN_HIERARCHY`.

**It synthesises.** Nangate 45 nm at 10 ns: timing met with +2.71 ns slack,
**57792 lines of Verilog**, 23 processes -- all 17 EVA kernels, `AlloMem`, plus
DRIM4HLS's four pipeline stages and the wrapper's memory servers.

### An IP's synthesis directives do NOT travel with the IP

The first attempt failed outright:

    Design 'top' could not schedule partition '/top/decode/decode_th'
      - could not schedule even with unlimited resources

`decode_th` is DRIM4HLS's, not Allo's. It synthesises fine standalone because
upstream's tcl maps `regfile`/`sentinel`/`csr` to registers -- but instantiated
inside an Allo design the paths move from `/drim4hls/decode/...` to
`/top/decode/...`, those directives stop applying, the register file becomes a
RAM, and the stage becomes unschedulable.

`parse_sc_module` carries ports, types, clock and reset across the boundary, but
nothing carries the constraints an IP needs in order to SYNTHESISE. Whoever
synthesises the assembled design has to know them and rewrite the paths by hand,
which `synth_chip.tcl` now does. An `sc_directives=` on `IPModule`, path-
rewritten at emit time, would close this properly.

### The area number is not a QoR number

Area score 5367696 -- dominated by memory, not logic. `dmemory_th` reports a
reset length of **102401** cycles: that is `drim_eva`'s 51200-word imem and dmem
being cleared. Those arrays exist to make the CPU look like a pure producer in
SIMULATION; synthesising them is meaningless, and a real design would strip the
wrapper or map them to external memory. Slack is identical to the standalone
DRIM4HLS run to seven decimals, so the critical path is still inside the
processor and the EVA logic is not setting it.
