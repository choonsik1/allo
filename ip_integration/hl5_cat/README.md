# HL5 → Catapult, with an Allo MMIO stream hook

[sld-columbia/hl5](https://github.com/sld-columbia/hl5) is a SystemC RISC-V
written for Cadence Stratus. This retargets it to Catapult/MatchLib and adds
memory-mapped stream ports, so it can become an Allo SystemC IP.

## Status: it runs, and the MMIO hook works

| | |
|---|---|
| Compiles with no Cadence headers | ✅ |
| Links against Catapult SystemC 2.3.3 | ✅ |
| Elaborates | ✅ |
| **Executes RISC-V correctly** | ✅ `7+5=12` lands in the right register |
| **MMIO store → channel** | ✅ `sw` to `0x32000` emits `MMIO OUT: 0x2a` |
| **MMIO load ← channel** | ✅ `lw` echoes `0xdeadbeef`, and `+1` returns `0x101` |
| **Accepted by Allo as a SystemC IP** | ✅ `func.func private @hl5`, `stream_dirs = "io"` |
| **Synthesised by Catapult** | ✅ **the whole CPU**, 7543 lines of Verilog, 2.0 ns met |
| RTL verified against the SystemC | ❌ fetch is provably correct, but co-sim never completes |

**`Simulation PASSED` is not a verdict.** `esc_log_pass()` prints it
unconditionally at the end of `sc_main`, and Columbia's `tb.cpp` has its
correctness check entirely commented out — it prints instruction counts and
writes a report, and verifies nothing. The real evidence is `fedec`'s register
trace (`5: 0x2a`, `6: 0x32000`, `INSTR TOT: 14` for `test_mmio`) and the
`MMIO OUT:` lines from the monitor in `system.hpp`. Those are what the ✅ rows
above rest on.

Three short programs are not a validation suite either: only
`lui`/`addi`/`lw`/`sw` are exercised, so branches, mul/div, sub-word loads and
the CSR path are all untested. Running HL5's own `soft/` programs needs a
RISC-V cross-compiler, which is **not installed on this machine**.

## Build and run

Self-contained — the four upstream files still needed are vendored in
`upstream/` (Apache 2.0, commit `3170ec9`). No clone required.

```bash
C=/opt/siemens/catapult/2024.2/Mgc_home

g++ -std=c++11 -o hl5_sim sc_main.cpp system.cpp tb.cpp \
    memwb.cpp execute.cpp fedec.cpp \
    -I. -Iupstream -I$C/shared/include \
    -L$C/shared/lib -lsystemc -Wl,-rpath,$C/shared/lib

LD_LIBRARY_PATH=/home/USERNAME/miniconda3/envs/allo/lib:$C/shared/lib \
  ./hl5_sim test_basic.mem catapult_port report.txt
```

Four environment traps, each of which cost a debug cycle:

- **`-I.` must come first.** The ported headers shadow HL5's originals by
  include-path order.
- **Any source that includes a ported header must sit beside it.** A quoted
  `#include` searches the including file's own directory *before* any `-I`, so
  `sc_main.cpp`/`system.cpp`/`tb.cpp` are copied here purely for co-location.
  `system.cpp` and `tb.cpp` are still byte-identical to Columbia's;
  `sc_main.cpp` has one added call (`Connections::set_sim_clk`, needed by RTL
  co-simulation). Nothing else in the patch-set approach can fix the layout.
- **`LD_LIBRARY_PATH` needs a newer libstdc++** — the system one predates
  `GLIBCXX_3.4.26`, which both the binary and Catapult's `libsystemc` require.
- **`.mem` values need an `0x` prefix.** They are read into `sc_uint<XLEN>`,
  whose `operator>>` ignores `std::hex` and infers the base from the prefix.
  Addresses are plain `unsigned`, so they do not.

## What changed: ~110 lines in ~2000

| File | Edits |
|---|---|
| `syn_directives.hpp` | replaced whole (56 lines) |
| `fedec.hpp/.cpp` | 9 |
| `execute.hpp/.cpp` | 9 |
| `memwb.hpp/.cpp` | 9 + **14** for the MMIO hook |
| `hl5.hpp` | 10 + **4** to promote the MMIO ports |
| `system.hpp` | 5 + **~30** for MMIO channels, the monitor and the producer |
| `tb.hpp` | 2 |
| `esc.h` | **new**, 46 lines |
| `hl5_marshall.hpp` | **new**, 110 lines — synthesis only |
| `synth.tcl` | **new**, the Catapult run |
| `directives.tcl` | **new**, the constraints `syn_directives.hpp` defers |

The same six-line pattern in every stage: one include swapped, two port types,
two deleted `clk_rst` lines, `Reset()` ×2, one `Pop()`, one `Push()`.

| Stratus | Catapult / MatchLib |
|---|---|
| `cynw_flex_channels.h` | `mc_connections.h` (and **before** `<systemc.h>`) |
| `put_get_channel<T>` | `Connections::Combinational<T>` |
| `get_initiator<T>` / `put_initiator<T>` | `Connections::In<T>` / `Out<T>` |
| `.get()` / `.put(x)` | `.Pop()` / `.Push(x)` |
| `.reset_get()` / `.reset_put()` | `.Reset()` |
| `din.clk_rst(clk, rst)` | **deleted** — ports have no clk/rst |
| `*_wrapper` types, `*_wrap.h` | the raw modules; Stratus generated those |
| `<esc.h>` | `esc.h` here — a 46-line shim |

Columbia's decode, ALU, forwarding and load/store logic are untouched.

## Findings

**Payload marshalling is a non-issue for simulation and REQUIRED for
synthesis.** `marshal_probe.cpp` shows `Connections::Combinational<mem_out_t>`
compiles against HL5's structs *as written*, and the design simulates on that
basis — but a `Combinational` in SIM mode never instantiates the marshaller. The
moment Catapult synthesises, the port becomes `SYN_PORT`, the payload is
flattened to `sc_lv<width>`, and compilation fails with *no instance of function
template `Wrapped<T>::Marshall`*. So the original risk assessment was right and
the early "non-issue" reading was drawn from a simulation-only test.

The cost turned out small, and none of it lands on Columbia's file.
`Wrapped<T>` is specialisable from outside, so `hl5_marshall.hpp` supplies
`width` and `Marshall()` for the four channel payloads and
`upstream/hl5_datatypes.hpp` stays byte-identical. Two rules: `width` must equal
the field-width sum exactly, and the specialisation must be visible *before* the
first `Connections::In/Out<T>` declaration.

**Connections ports have no `clk`/`rst`.** `clk_rst(clk, rst)` does not
translate — `InBlocking` carries only data/val/rdy and `Reset()` inherits timing
from the enclosing `SC_CTHREAD`. Those lines delete.

**The three raw `HLS_*` calls need no in-place edit.** Dropping
`cynw_flex_channels.h` leaves them undefined, so `syn_directives.hpp` absorbs
them; `execute` and `fedec` were pure substitution.

**`HLS_DEFINE_PROTOCOL` turned out survivable.** All 8 uses are defined empty,
so Catapult reschedules HL5's hand-timed regions — including the startup
handshake at `memwb.cpp:26,28`, two `Push`es around a `wait()`. The pipeline
still resets, runs and halts correctly. This was the largest *unknown* risk.

**Every Connections port must be `Reset()` in its thread's reset block.**
Adding `mmio_in`/`mmio_out` without that produced `CONNECTIONS-101` warnings and
undriven val/rdy.

**Processes sharing a clock must share a reset spec.** The testbench monitor
resets on `cpu_rst`, not `rst`, or Connections raises `CONNECTIONS-212`.

**`program_end` fires on *fetch*, not retire.** `fedec` asserts it the cycle it
fetches `jal x0,0`, and the testbench calls `sc_stop()` on that — so a store in
the last few instructions never reaches `memwb`. Test programs need drain NOPs
before the halt. This is HL5 testbench behaviour, not a port artifact.

## The Allo MMIO hook

A load/store whose **word** address is `>= MMIO_BASE` (`== DCACHE_SIZE`, so byte
address `0x32000`) is a channel access. One guard covers all seven `dmem` sites,
because they share a computed `aligned_address`:

```cpp
if (aligned_address >= MMIO_BASE) {
    if (load)       mem_dout = mmio_in.Pop();          // blocking
    else if (store) mmio_out.Push(input.mem_datain.to_uint());
}
else if (...)   // the original switches, untouched
```

The load arm writes `mem_dout` exactly as `LW_LOAD` does, so writeback is
unaware. `MMIO_BASE` derives from `DCACHE_SIZE` rather than being hardcoded. The
original `sc_assert(aligned_address < DCACHE_SIZE)` was widened by one word
rather than deleted — it is active under `#ifndef STRATUS_HLS`, i.e. here.

`hl5.hpp` promotes these to the top, so Allo's `parse_sc_module` reports exactly
two ports — `dirs='io'`, `names=['mmio_in','mmio_out']`, `clk='clk'`,
`rst=None`. The three internal `Combinational` channels are correctly invisible;
`rst` is `None` because `hl5` has two `sc_in<bool>` (`rst`, `fetch_en`) and the
parser refuses to guess.

## Catapult synthesis

`synth.tcl` synthesises one stage. `execute` is the natural first target: two
Connections ports, no memory pointer, and it holds the ALU/mul/div, so it is the
QoR-interesting stage.

```bash
cd hl5_cat && catapult -shell -f synth.tcl              # execute
STAGE=memwb catapult -shell -f synth.tcl                # see the caveat below
```

Result for `execute`, Nangate 45 nm (ships with Catapult), 2.0 ns clock:

| | |
|---|---|
| Timing | **met**, slack +0.112 ns |
| Total area score | 18966 (registers 8140, 43%) |
| Real operations | 1085 |
| Latency / throughput | 195 / 197 cycles |
| RTL emitted | 4947 lines of Verilog (also VHDL) |

The Connections handshake became real hardware — `ccs_conn_in_wait` and
`ccs_conn_out_wait` cells appear in the bill of materials, which is the stream
interface Allo would drive. There is one 32×32 `mgc_mul` for `MUL`.

**Latency 195 is bad, and expected.** `DIV_UNROLL`, `MUL_SPLIT` and `ADD_SPLIT`
are defined empty in `syn_directives.hpp`, so the divider is left fully
sequential. Those constraints belong in a Catapult directives tcl that has not
been written; this run establishes that the port *synthesises*, not that it
synthesises well.

One thing had to change to get here, beyond `hl5_marshall.hpp`:

- **`perf_th` is dropped under `__SYNTHESIS__`.** It does nothing but
  `csr[MCYCLE_I]++` while `execute_th` also touches `csr`, and Catapult rejects
  a variable shared between two `SC_CTHREAD`s (`HIER-41`) where Stratus allowed
  it. The counter is not in the pipeline's dataflow, so the synthesised RTL
  simply does not advance `mcycle`. Simulation is unaffected.

An earlier note here claimed `-DSTRATUS_HLS` was also needed. **It was not, and
it never took effect.** `options set Input/CompilerFlags` is accepted and reads
back, but the value never reaches the EDG front end — the "Front End called with
arguments" log line shows only `-I` flags. HL5's simulation-only blocks are
therefore compiled into the design and Catapult tolerates them.

### The caches became memory interfaces

Both stages originally held a raw pointer to a testbench-owned array (`imem`,
`dmem`) that Stratus synthesised via `MAP_ICACHE`/`MAP_DCACHE`. Catapult rejects
the pointer (`CIN-224`), and making the array a module member is worse than
useless: **an internal array nothing outside can write carries no information,
so Catapult correctly deletes it and everything downstream.** That collapsed
`fedec` to 10 operations from a 729-line decoder and `memwb` to 7.

So the memories moved **out of the CPU** and only their ports came in:

```
fedec:  sc_out<sc_uint<PC_LEN>> imem_addr;   sc_in<sc_uint<XLEN>> imem_dout;
memwb:  sc_out<sc_uint<XLEN>>   dmem_addr;   sc_in<sc_uint<XLEN>> dmem_rdata;
        sc_out<sc_uint<XLEN>>   dmem_wdata;  sc_out<bool>         dmem_we;
```

**This costs no timing at all**, which is the nice part. HL5 already computed the
address, called `wait()`, and only then indexed the array — precisely a
registered-address memory. The address is now driven before that same `wait()`
and the data read after it, so not one cycle moved. `hl5.hpp` promotes all six
ports, and `system.hpp` models the memories against the arrays `tb.cpp` still
loads, so the testbench is unchanged.

Two details that are easy to get wrong:

- **`dmem_we` must be deasserted every iteration**, before the `wait()`. Without
  it the strobe raised at the end of one access is still high when the memory
  next samples, and the following address gets a spurious write.
- **Every output port must be driven in the reset action** — Catapult does not
  preserve state across reset (`CIN-233`). The write strobe in particular has to
  come out of reset low.

`memwb`'s eight `dmem[...]` sites collapse to one fetched word: every load reads
it and every sub-word store modifies it, so `SB`/`SH` read-modify-write for free.
`fedec` had a single access site.

### The whole CPU synthesises

Nangate 45 nm, 2.0 ns clock. Each stage runs standalone, and `STAGE=hl5`
synthesises the assembled processor as a three-block hierarchy — all four
modules are named in `DESIGN_HIERARCHY`, so the stages stay separate blocks
rather than being inlined into one flat process.

| top | real ops | area score | RTL lines | slack |
|---|---|---|---|---|
| `execute` | 1085 | 18966 | 4947 | +0.112 ns |
| `fedec` | 248 | 3273 | 1337 | +0.005 ns |
| `memwb` | 39 | 2431 | 1208 | +1.189 ns |
| **`hl5`** | **1372** | **24933** | **7543** | **+0.005 ns** |

Those are the numbers **without** `directives.tcl`; see below for what the
restored constraints buy.

### directives.tcl — restoring what Stratus carried in source

`syn_directives.hpp` defines `DIV_UNROLL`, `MUL_SPLIT`, `ADD_SPLIT` and the
`FLAT_*`/`MAP_*` macros as empty because none has a Catapult source-level twin.
`directives.tcl` is where they land, sourced after `go assembly` (which is when
loops and array resources exist to be named):

| directive | effect |
|---|---|
| `DIVIDE_LOOP -UNROLL 4` | matches HL5's own `DIV_UROLL4` |
| `csr:rsc -MAP_TO_MODULE {[Register]}` | what `HLS_FLATTEN_ARRAY(csr)` meant |
| `regfile:rsc -MAP_TO_MODULE {[Register]}` | reports a MISS — Catapult already flattens it, so there is no resource. Left in as a tripwire. |

|  | before | after |
|---|---|---|
| `execute` latency / throughput | 195 / 197 | **163 / 165** |
| `hl5` latency / throughput | 202 / 197 | **170 / 165** |
| `hl5` area score | 24933 | 28337 (+14%) |
| slack | +0.005 ns | +0.005 ns |

**But the divider is not the bottleneck it looked like.** Unrolling it *fully*
(32x, `HL5_DIV_UNROLL=yes`) gives latency 162 against 163 at 4x — nothing — for
17% more area. So restoring HL5's directives is worth about 16% of the latency
and the remaining ~163 cycles come from somewhere else, most likely long
dependency chains being spread across cycles by the 2.0 ns clock. The theory
that empty directives explained the QoR is only partly true.

**Pipelining is deliberately off.** HL5's directive set contains no pipeline
directive, so adding one is an extension rather than a restoration — and at II=1
it does not schedule (`SCHD-3`, *"Feedback path is too long"*), which is the
forwarding and channel feedback each stage closes every iteration. Set
`HL5_PIPELINE_II` to experiment.

`hl5` reports the three blocks separately — `/hl5/fedec/fedec_th`,
`/hl5/execute/execute_th`, `/hl5/memwb/memwb_th` — and its critical path is
`fedec`'s, unchanged from the standalone run. Latency 202. `hl5_top.cpp` exists
only to give the header-only container a translation unit.

The three internal `Connections` channels become ready/valid buses of exactly the
marshalled widths, which independently confirms `hl5_marshall.hpp`'s arithmetic:

```
de2exe_ch_vld/rdy/dat[138:0]     exe2mem_ch_vld/rdy/dat[79:0]
wb2de_ch_vld/rdy/dat[41:0]
```

The synthesised top is the IP boundary this project has been building towards:

```verilog
module hl5 (
  clk, rst, program_end, fetch_en, entry_point,
  icount, j_icount, b_icount, m_icount, o_icount,
  imem_addr, imem_dout,                              // instruction memory
  dmem_addr, dmem_wdata, dmem_we, dmem_rdata,        // data memory
  mmio_in_vld,  mmio_in_rdy,  mmio_in_dat,           // <- Allo drives these
  mmio_out_vld, mmio_out_rdy, mmio_out_dat
);
```

The memory interfaces appear as real ports — `fedec` exposes `imem_addr`,
`imem_dout`; `memwb` exposes `dmem_addr`, `dmem_wdata`, `dmem_we`, `dmem_rdata`
— so the RTL can be attached to an actual memory. `fedec`'s +0.005 ns is a pass
but has no margin.

The Allo IP boundary is untouched by all of this: `parse_sc_module` still reports
exactly `['mmio_in', 'mmio_out']`, because it looks only for `Connections::In`
and `Out` and the six memory ports are plain `sc_in`/`sc_out`.

### RTL verification (SCVerify) — set up, not yet passing

`synth.tcl` wires SCVerify for `STAGE=hl5`, so the same testbench can drive
either the SystemC or the generated Verilog:

```bash
cd hl5_cat && catapult -shell -f synth.tcl        # STAGE=hl5 is not the default
cd <run>/hl5_synth/hl5.v1
NC_ROOT=/opt/cadence/XCELIUM2403 CDS_INST_DIR=$NC_ROOT \
  make -f scverify/Verify_rtl_v_ncsim.mk sim
```

Three things it needed: `CCS_DESIGN(hl5)` in `system.hpp` so SCVerify can
substitute the RTL wrapper (it expands to plain `hl5` otherwise); the testbench
added to the solution with `-exclude true`; and `Connections::set_sim_clk(&clk)`
in `sc_main.cpp`, without which co-simulation aborts on an assertion.

**Simulator availability decided the flow.** Questa is SCVerify's default and is
not installed. **VCS is installed but unusable** — its SystemC support accepts
only g++ 7.3 / 9.2 / 9.5, and this box has only Catapult's own 10.3.0 and
gcc-toolset-13, with VCS's bundled `gnu/linux` package empty. Xcelium works, and
needs `NC_ROOT` set explicitly.

**An asynchronous memory model deadlocks co-simulation.** The memory processes in
`system.hpp` were originally sensitive to the address signal as well as the
clock, modelling the async RAM that HL5's array access actually was. That
simulates fine in SystemC and hangs RTL co-simulation in delta cycles at 0 s
forever: the address is X at time 0 and address → data → address closes a
zero-delay path through the wrapper. Latching reads on the negedge only fixes it
and costs no timing.

**The fetch interface is CORRECT.** A per-cycle probe on `imem_addr`/`imem_dout`
(`HL5_PROBE=1`, `fetch_probe()` in `system.hpp`) diffed against the same probe in
the SystemC build shows the RTL fetching the right words in the right order:

```
             SystemC                         RTL
cycle  8     iaddr=0 idout=0x2a00293         iaddr=0 idout=0x2a00293
next         cycle 11 -> iaddr=1, 0x32337    cycle 15 -> iaddr=1, 0x32337
```

So there is no memory-interface bug, and the earlier guess about a registered
`imem_addr` was wrong.

**What the RTL is, is slow.** It advances roughly 7x fewer instructions per cycle
than the SystemC, which is what `execute`'s **throughput of 197 cycles** predicts
— `DIV_UNROLL`/`MUL_SPLIT`/`ADD_SPLIT` are defined empty, so the divider is fully
sequential and every instruction pays for it.

**Co-simulation has still never completed.** 45 minutes in, the probe showed the
CPU still on instruction 1. Whether that is purely the 197-cycle throughput or a
real stall on top of it is **unresolved** — the probe window was capped at 80
cycles and a rebuild of the instrumentation did not take effect inside the
SCVerify make flow, so there is no visibility past that point. Equivalence
remains unproven.

The productive next step is probably not to chase the co-simulation: it is to
write the Catapult directives tcl that `syn_directives.hpp` defers (Open item 1).
Fixing the 197-cycle throughput addresses the real QoR deficiency *and* makes
verification tractable, instead of fighting a symptom of it.

## Test programs

All three generated by `../ip/rvasm.py`, which was written for a different
processor and needed no changes.

- `test_basic.mem` — `7+5=12`, a normal store, halt
- `test_mmio.mem` — stores 42 to `0x32000`, 8 drain NOPs, halt → `MMIO OUT: 0x2a`
- `test_mmio_in.mem` — the load direction, from `gen_test_mmio_in.py`: reads two
  words from the channel, echoes the first, increments the second →
  `MMIO OUT: 0xdeadbeef` then `MMIO OUT: 0x101`. The `+1` is the point — it
  shows the value travelled through the register file and the ALU rather than
  being looped back inside `memwb`. Fed by `mmio_producer()` in `system.hpp`,
  which owns `mmio_in_ch`'s write end (two threads may not drive one end, so
  `ResetWrite()` moved out of `mmio_monitor()`).

## Use from Allo

`test_hl5_as_allo_ip.py` imports this file as an IP and builds a region around it:

```python
hl5_ip = allo.IPModule(top="hl5", impl="hl5.hpp")   # no input_idx/output_idx
...
hl5_ip(to_cpu, from_cpu)
```

Run it with the conda `allo` interpreter (the system `python3` has no numpy):

```bash
PY=/home/USERNAME/miniconda3/envs/allo/bin/python
PYTHONPATH=/home/USERNAME/final_ip_integration/allo:. \
LLVM_BUILD_DIR=/home/USERNAME/miniconda3/envs/allo \
LD_LIBRARY_PATH=/home/USERNAME/miniconda3/envs/allo/lib $PY test_hl5_as_allo_ip.py
```

It emits `func.func private @hl5(!allo.stream<i32,4>, !allo.stream<i32,4>)` and
`call @hl5(...) {stream_dirs = "io"}`, with **no** `input_idx`/`output_idx`
supplied — direction came from `Connections::In`/`Out`. Note streams are
declared as a bare annotation at region scope (`to_cpu: Stream[Ty, 4]`);
`df.Stream[...]()` is not the accepted form. In the printed IR the call reads
`@hl5(%arg1, %arg0)`, which is use-order SSA numbering and not a swap:
`%arg1` is `to_cpu`, matching the source.

## Open

1. **QoR is improved but not explained.** `directives.tcl` restores HL5's
   constraints and buys ~16% (latency 202 → 170 on the whole CPU), but a full
   divider unroll buys nothing beyond that, so most of the remaining ~163 cycles
   in `execute` are still unaccounted for. Finding out what they are — most
   likely dependency chains spread by the 2.0 ns clock — is the open question.
2. **RTL not verified.** SCVerify runs under Xcelium and the fetch interface is
   provably correct, but co-simulation never completes at 197 cycles/instruction.
   Unresolved whether that is throughput alone or a stall on top of it.
3. **Only ~8 instructions exercised.** Branches, mul/div, sub-word loads and the
   CSR path are all unvalidated -- see the note under Status.
4. **No RISC-V toolchain** on this machine, so HL5's `soft/` suite (aes256,
   dhrystone, fft) cannot be built.
5. **Allo can accept this IP but not yet emit a design containing it.**
   `EmitSystemC.cpp` still wraps an IP in an SC_MODULE whose thread CALLS it as
   a function; it must instantiate it as a submodule and bind ports by name.
6. **The IP boundary may be the wrong shape.** Real EVA's CPU does not stream
   packets: it writes four descriptor words and pulses a trigger, and a hardware
   DMA (`router_driver_slice.sv`) synthesises packet headers. If this IP should
   mirror that, `mmio_*` wants to be a descriptor/trigger interface rather than
   a packet stream.
