# An HLS soft processor as an Allo stream IP, programming the EVA PE array

A third-party RISC-V core, wrapped as an Allo `IPModule` with `hls::stream`
ports, wired into the EVA PE grid over EVA's own router plane. The processor
carries the array's program in its ROM: it boots the PEs and they execute code
the processor gave them. Verified end-to-end in RTL co-simulation, up to a 2x2
grid computing a real matrix product.

The processor is [anjn/vhls-riscv](https://github.com/anjn/vhls-riscv) (a Vitis
HLS port of chadyuu/riscv-chisel-book). Its decode/execute/writeback logic is
unmodified; only its interface changed.

That work is finished. Two follow-on strands then asked the same question of
SystemC rather than Vitis HLS: **Allo gained a SystemC IP front end**
(`parse_sc_module`, §5), and **a second third-party processor, HL5, was ported
from Cadence Stratus to Catapult** so it can be picked up by it (§6). Both are
described below; §6 runs, §5 is complete on the Python side only.

---

## Results

All five designs pass RTL co-simulation. Vitis 2025.1, xczu7ev, 3.33 ns target.

| `emit` target | Design | Co-sim result | Timing |
|---|---|---|---|
| `1x1` | Processor **replaces** the west router driver | 3.0 on `out_e` | 6.562 ns |
| `2x2` | Processor **feeds** the driver; 4 PEs add | 3.0 on all 4 PEs | 2.433 ns |
| `2x2s` | Same, with the II=1 node schedule | 3.0 on all 4 PEs | 6.562 ns |
| `mmm` | 1x1 running EVA's golden MMM kernel | `out_s = [6, 12, 3]` | 2.427 ns |
| `mmm2x2` | 2x2 computing a real matrix product | `[22,16,15] / [34,24,29]` | 2.433 ns |

`mmm2x2` is the headline: `X = [[2,4],[1,3],[5,2]]` against `W = [[1,3],[5,7]]`,
four PEs each holding a different stationary weight, all programmed by one
RISC-V core inside the design. The host supplies only activations.

**Timing is set by the schedule, not the grid size.** `2x2s` reports exactly the
same 6.562 ns as `1x1` — the critical path is inside a single node and does not
lengthen with the array. `pipeline_node=True` buys II=1 and costs ~80% more FF
plus a 2.7x longer clock period; at 3.33 ns it does not close.

---

## Layout and rebuild

`ip/` holds 7 source files: `rv_stream_ip.cpp` (939, the IP — 6 tops over one
templated core), `rvasm.py` (390, RV32I assembler + EVA packet builders),
`tb_rv_stream_ip.cpp` (341, standalone g++ tests for all 6 tops, ~1 s),
`tb_top.cpp` (197, the shared co-sim testbench, `-DTARGET_*` selected),
`test_rv_stream_ip.py` (464, Allo tests + the `emit` generator), and the two chip
variants `eva_fp16_skid.py` / `eva_fp16_skid_drv.py` (1797 / 1834). `allo/` is a
git worktree on branch `ip-stream-integration`; `rv/` is upstream vhls-riscv, for
diffing against. `hl5_cat/` is the Catapult port of HL5 (§6) — self-contained,
with its own README and build recipe.

`emit` writes each project directory (`kernel.cpp` + `cosim_rv.ini`) on demand;
they hold nothing hand-written and are not kept in the tree.

```bash
cd ip
PYTHONPATH=/home/USERNAME/final_ip_integration/allo:. \
LLVM_BUILD_DIR=/home/USERNAME/miniconda3/envs/allo \
LD_LIBRARY_PATH=/home/USERNAME/miniconda3/envs/allo/lib \
  python test_rv_stream_ip.py emit {1x1|2x2|2x2s|mmm|mmm2x2}

source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh   # NOT 2023.2 -- see Traps
cd <target>.prj
v++ -c --mode hls --config cosim_rv.ini --work_dir cosim_work
vitis-run --mode hls --cosim --config cosim_rv.ini --work_dir cosim_work
```

---

## What was built

### 1. Allo gained stream-IP support, plus three bug fixes

The upstream `vincent-yeet/allo` stream-IP feature was cherry-picked onto
`allo_sup`. Three genuine bugs only surface once the IP meets a real mesh; each
was confirmed necessary by reverting it and rebuilding.

| File | Bug | Without it |
|---|---|---|
| `ir/builder.py` | Call args built as value expressions before the IPModule branch | `'tuple' object has no attribute 'result'` on `cr_e[0,0]` — **every mesh design fails** |
| `passes.py` | `analyze_use_def` walked the body of a bodyless `func.func private` | `IndexError: External function does not have a body` — only when the schedule calls `partition` (so `1x1`/`2x2s`, not the rest) |
| `backend/hls.py` | The IP was both `#include`d into `kernel.cpp` *and* `add_files`'d | duplicate definitions, `Error in llvm-link` — at csynth, not codegen |

Branch `ip-stream-integration`, pushed to `mine/ip-stream-integration`
(`git@github.com:choonsik1/allo.git`), 4 commits, +2510/-45 across 13 files.

### 2. The processor became a stream IP

Upstream `kernel.cpp` contains **zero** streams (`grep stream` finds only
`#include <iostream>`); its interface was an `ap_uint<8>` memory array plus a
result pointer, which Allo cannot wire into a dataflow region.

**Only 15 of the original 375 lines were touched**, at six sites: the header
(`kernel.hpp` → inline includes, MMIO addresses, ROMs; `MEM_SIZE` 32 KB → 1 KB),
the signature (→ `template <typename Ports> rv_core(Ports&, prog, words, halt)`),
the program source (`memcpy` from `mem[]` → little-endian ROM unpack), the halt
constant, the deleted result port, and — the only change in the execute path — an
address test in front of the existing load/store, routing MMIO addresses to
`io.load()` / `io.store()` and everything else to `local_mem` unchanged.

Untouched: fetch, the entire decode table, the register file, the ALU, branch
resolution, CSR, writeback select. No instruction's behaviour changed. The MMIO
load is **blocking**, deliberately: the CPU stalls on an empty FIFO exactly like
Allo's `stream.get()`, so the processor paces itself against EVA's credit
protocol with no wrapper logic outside the core.

**Six tops**, all the same core with a different ROM and port bundle:

| Top | Ports | Role |
|---|---|---|
| `rv_stream_ip` | 2x int32 | milestone 1: 32 stream-fed additions |
| `rv_eva_collector` | sys in, credits out, raw out | an east-edge collector (unused) |
| `rv_eva_programmer` | credits in, packets out | **replaces** `rdrv_w`; implements EVA's credit protocol |
| `rv_eva_pktsrc` | 2x packets out | **feeds** `rdrv_w`, 2x2 add |
| `rv_eva_mmm_src` | 1x packets out | 1x1 MMM |
| `rv_eva_mmm_src_2x2` | 2x packets out | 2x2 MMM, different weight per node |

Port *bundles* rather than one fat port list, because Vitis rejects a stream port
that is never read or written — dummy streams for unused ports fail RTL generation.

### 3. Two ways to connect it

**The processor replaces the driver** (`eva_fp16_skid.py`). `rdrv_w`'s body
becomes a single IP call, so the processor *is* the driver and must implement
EVA's credit protocol itself: prime `PRIME_TOKENS-1` empty packets, then per step
take a credit and emit a packet or a bubble, always exactly one `put`.

**The processor feeds the driver** (`eva_fp16_skid_drv.py`) — more EVA-faithful,
and what the final designs use:

```
RV processor  (program + weights in ROM)
      │  one stream per west lane
      ▼
rdrv_w  — EVA's own kernel, unchanged except for where packets come from
      │  buf[lane][NPKT]   ← a local array: "the Allo memory"
      │  stock credit-gated replay
      ▼
router plane → each PE loads irf[0..7], drf, config → starts
      ▼
PEs compute; partial sums accumulate down each column → out_s
```

The processor plays the host's role — it produces the program image — and the
array keeps its own timing logic. Deadlock-freedom is static: the driver reads
exactly `NPKT` words and the processor writes exactly `NPKT`.

**One processor drives every lane, not one per lane.** `meta_for(0, M)`
instantiates the *same* top M times, so all M instances carry the same ROM — fine
while every PE runs the same program, impossible once each node needs its own
weight. So the IP takes one output stream per lane and the store address selects
it (`MMIO_OUT26` → lane 0, `MMIO_OUT26B` → lane 1); `rvprog` gates arity with
`allo.meta_if(M == 1)`, a build-time branch.

### 4. The workload

`mmm`/`mmm2x2` run EVA's golden weight-stationary MMM kernel, verbatim from
`eva_workloads.load_mmm_router`:

```
I0  MOV  r1, SYSLFT           activation in from the west
I1  MULT r2, r0, r1           r0 = drf[0] = the stationary weight
I2  MOV  SYSRGT, r1           forward the activation east
I3  ADD  SYSBTM, r2, SYSTOP   accumulate with north, send south
```

Four instructions living once in `irf[0..3]`, looping `cfg_itsz` times, so any
batch count fits the 8-slot IRF. The processor supplies the program and the
weights; the host supplies only activations on the west systolic edge at
`PROG_CYCLES + 4*b` and a valid-zero north seed. **Nothing is fed on the router
plane by the host at all.**

### 5. Allo gained a SystemC IP front end

Allo could import an IP only if it was a **Vitis HLS function**: `parse_cpp_function`
regexes a signature and `builder.py` emits a `func.call`. SystemC states the same
thing differently — a stream port is a `Connections::In/Out<T>` *member* of an
`SC_MODULE` you instantiate and bind, not a parameter of a function you call.

`parse_sc_module` (in `allo/backend/ip.py`, ~60 lines with the dispatch) reads
that form: `_sc_module_body` extracts `SC_MODULE(name){...}` by brace matching (a
regex cannot — `SC_CTOR` and the threads nest braces), `_SC_PORT` finds the
`Connections` members reusing the existing `_TEMPLATE_ARGS` so nested payloads
like `ac_int<32,true>` parse, and `_SC_CLK`/`_SC_RST` find the clock and reset.
`IPModule` tries HLS first and falls back to SystemC.

The payoff is that the **SystemC API is simpler than the HLS one**: the port type
already states the direction, so `input_idx`/`output_idx` become unnecessary. Six
lines in `builder.py` let the parsed `sc_dirs` outrank them. Everything
downstream is shared and needed no work at all, because Allo's `STREAM` sentinel
is backend-neutral — `stream_dirs`, `move_stream_to_interface` and `copy_ext_libs`
all test `shape is STREAM` and never read the type string.

Verified against the real thing, not a toy: `hl5_cat/test_hl5_as_allo_ip.py`
points the front end at the 2000-line ported HL5 processor (§6) and gets
`func.func private @hl5(!allo.stream<i32,4>, !allo.stream<i32,4>)` plus
`call @hl5(...) {stream_dirs = "io"}` — with **no** `input_idx`/`output_idx`
supplied. The parser reports exactly the two promoted MMIO ports and none of
HL5's three internal pipeline channels. Ambiguity is refused rather than
guessed: HL5 has two `sc_in<bool>` (`rst`, `fetch_en`), so it yields
`rst=None`.

**The emitter half is not started.** `EmitSystemC.cpp` must instantiate the IP as
a submodule and bind its ports by name, instead of today's "wrapper `SC_MODULE`
whose thread calls the IP as a function". The hook is narrower than it sounds:
the emitter already instantiates a module per top-level `func.call`
(`EmitSystemC.cpp:1952`) and already reads a per-arg `stypes` direction string.

### 6. HL5, ported from Cadence Stratus to Catapult

To test §5 against something real rather than a hand-written module,
[sld-columbia/hl5](https://github.com/sld-columbia/hl5) — a SystemC RISC-V from a
CICC 2020 paper — was retargeted from Stratus to Catapult/MatchLib. See
`hl5_cat/README.md`. It compiles with no Cadence headers, elaborates, executes
RISC-V correctly, and both directions of the channel work: a store to
`0x32000` emits `MMIO OUT: 0x2a`, and a load returns a value the producer fed —
echoed verbatim, then incremented, proving it reached the register file and the
ALU. And **the whole CPU goes through Catapult synthesis** at 2.0 ns on Nangate
45 nm — 1372 operations, 7543 lines of Verilog, as a three-block hierarchy that
keeps `fedec`, `execute` and `memwb` as separate blocks. The synthesised top is
the IP boundary this project was aiming at: `imem_*`/`dmem_*` memory interfaces,
and `mmio_in`/`mmio_out` as real ready/valid ports — the stream interface Allo
drives. The three inter-stage channels become ready/valid buses at exactly the
marshalled widths (139/80/42 bits), which independently confirms
`hl5_marshall.hpp`.

Getting `fedec` and `memwb` there needed one architectural change. Both held a
pointer to a testbench-owned cache array, which Stratus synthesised via
`MAP_ICACHE`/`MAP_DCACHE`; Catapult rejects the pointer, and an internal member
array is worse, because **an array nothing outside can write carries no
information and Catapult correctly deletes it and everything downstream** — that
collapsed `fedec` from a 729-line decoder to 10 operations. So the caches moved
out of the CPU and only their ports came in. It cost no timing: HL5 already
computed the address, waited a cycle, then indexed the array, which is exactly a
registered-address memory.

**~62 lines changed in ~2000.** The one finding that made it cheap: every Stratus
directive already sits behind a project-local friendly macro in one 58-line
`syn_directives.hpp` — HL5's sources write `PROTO_MEMWB_RST`, never a raw `HLS_*`
— so retargeting *all* directives is a one-file job and the ~2400 lines of RISC-V
logic are untouched. Each stage then takes the same six-line treatment: one
include swapped, two port types, two deleted `clk_rst` lines, `Reset()` ×2, one
`Pop()`, one `Push()`.

Of the two risks identified before starting, one evaporated and one came back.
`HLS_DEFINE_PROTOCOL`, which has no Catapult source-level twin, was survivable
defined empty: Catapult reschedules HL5's hand-timed regions, including the
startup handshake, and the pipeline still resets, runs and halts.

**Payload marshalling did not evaporate — it was hiding.** A `Combinational`
channel in simulation never instantiates the marshaller, so the design compiled
and ran without any. Synthesis switches the port to `SYN_PORT`, flattens the
payload to `sc_lv<width>` and demands `Wrapped<T>::Marshall`. The fix is
`hl5_marshall.hpp`: `Wrapped<T>` is specialisable from outside, so the four
channel payloads get `width` and `Marshall()` without a single edit to the
608-line `hl5_datatypes.hpp`.

The Allo boundary is an MMIO hook in `memwb`: a word address `>= MMIO_BASE`
(`== DCACHE_SIZE`) is a channel access rather than memory. One guard covers all
seven `dmem` sites because they share a computed `aligned_address`, and the load
arm writes `mem_dout` exactly as `LW_LOAD` does, so writeback is unaware.
`hl5.hpp` promotes the two ports to the top, so `parse_sc_module` sees a clean
2-port IP — `dirs='io'`, `names=['mmio_in','mmio_out']` — with HL5's three
internal pipeline channels correctly invisible.

---

## The PE boot sequence

Ground truth is `eva_workloads.load_prog_packets`. Packet layout (fp16):
`data[0:16] | addr<<16 | mode<<20 | id<<21 | rq<<25`. Per node, **in this order**:

1. **All 8 IRF slots**, `addr = 8+s`, `mode = 1`, unused ones padded with
   `NOP = 0x773`. Writing only the slots the kernel uses produces **no output at all**.
2. DRF values, `mode = 0`, `addr = slot`; payload is the raw fp16 bit pattern.
3. `config_reg_1` = iteration count, `addr = 1`, `mode = 1`.
4. `config_reg_0` **last**, `addr = 0`, `mode = 1`:
   `(1<<15) | ((klen-1)&0x7)<<8 | smask`. Writing it flips `fetch_en`, so
   everything else must already be in place.

`cfg_isz` is the **last instruction index, not the count** — the node advances
with `if instr_cnt == cfg_isz`, and `load_prog_packets` sends `klen-1`.

---

## Traps

Each of these cost real debugging time.

**Vitis 2023.2 cannot build this above 1x1.** `prime_cfg` is a top-level
`int32[M,N]` read by all 21 kernels, and 2023.2's dataflow checker rejects that
(`[HLS 200-779] Non-shared array ... single reader and a single writer`). At 1x1
it is `[1][1]` and gets optimised to a scalar, the only reason 2023.2 works
there; 2025.1 generates a `Block_entry_<arg>_rd_proc` broadcast reader instead.
Not caused by the IP — the stock chip fails identically. Things that do **not**
fix it, all tried: `s.partition("prime_cfg")` (wrong target format, and
`build_prime.py`'s own call is swallowed by its `try/except`, so it has never
taken effect), `s.partition("top:prime_cfg")` (emits no pragma), `#pragma HLS
stable`, `pipeline_node/partition_rf=False`.

**Never put a bare `N` (or `M`) at module level in a file that builds an EVA
chip.** Allo resolves a traced region's globals through the calling frames, so a
stray `N = 32` shadowed the chip's `N` and silently built a **2x32** grid (136k
lines of HLS) instead of 2x2. Hence `VADD_N` in `test_rv_stream_ip.py`.

**`NSTEP` must be far larger than `load_mmm_router`'s formula suggests.** It
gives ~26 at 1x1, stale for this leanalu variant: a one-instruction kernel needs
≥80, the chip's own golden MMM ~120. Below that everything is silently all-zero —
easy to misread as a bad packet sequence.

**No START skew is needed at 2x2.** `load_mmm_router`'s "needs the i+3j skew"
warning applies to a non-data-driven mode. With `DATADRIVEN = 1` the PC stalls
until operands are valid, so the skew emerges from the stalls.

**Do not write a top's signature inside a comment in the IP.** `IPModule` finds
the function with a regex over the whole file, so `void <top>(...)` in a comment
matches first and the parser is handed hundreds of lines as the parameter list.

**csim is always all-zero** — dataflow plus feedback cannot run sequentially. The
testbench therefore always `return 0`s and prints an `RVCHECK` verdict; a nonzero
exit would abort co-sim before the RTL run. Every log shows a csim `FAIL` line
followed by the RTL `PASS`.

**Regenerated `kernel.cpp` needs a union patch** before the C++ testbench will
compile (a union with a `half` member needs an explicit initializer).
`emit_project()` applies it, as the chip's own `gen.py` does.

---

## Verification

| Level | What it covers | Runtime |
|---|---|---|
| `tb_rv_stream_ip.cpp` | all 6 IP tops against their protocols, ROM structure | ~1 s |
| CPU simulator | array behaviour, boot sequences, NSTEP, golden results | seconds |
| `pytest test_rv_stream_ip.py` | codegen: IP reaches the HLS with stream ports intact | minutes |
| csynth | legality, timing, resources | minutes |
| **RTL co-sim** | the real functional check | tens of minutes |

The CPU simulator (`df.build(..., target="simulator")`) found every functional bug
here. Call the top with 21 args, **`prime_cfg` first** — the chip's own `run_eva()`
helper is stale and omits it — and set `LLVM_BUILD_DIR` or the JIT cannot find
`libmlir_runner_utils.so`. It does **not** enforce Vitis's dataflow rules, so it
will happily run a design that fails pre-synthesis: use it for behaviour, not
legality.

The standalone tests have teeth: swapping `config_reg_0`/`config_reg_1` — the
mistake that silently yields zero output — is caught in a second by `test_pktsrc`
rather than by a co-sim.

---

## Known gaps

- **`ip/` and `hl5_cat/` are pushed** to `choonsik1/pe_core_implementation` under
  `Allo_IPs/rv_stream_eva/` and `Allo_IPs/hl5_catapult/`; the Allo fixes live on
  branch `ip-stream-integration` of `choonsik1/allo`. The `allo/` worktree here is
  deliberately excluded — it has its own remote, and its `mlir/build` symlink
  points into `allo_sup`.
- **The two chip files stay separate on purpose.** 95% identical (85 differing
  lines of 1797), but the difference is in the region *graph*: the feed variant
  declares an extra `Stream` and an extra kernel, and a `Stream` declaration is an
  annotated assignment at region scope that cannot sit inside `meta_if` — unused
  in replace mode, exactly the case Vitis rejects. Merging would mean duplicating
  the 1700-line region or dropping a verified architecture.
- **`rvprog`'s `meta_if` handles M=1 and M=2 only.** 4x4 needs more branches or a
  generated call, and an IP with M output streams.
- **`rv_eva_collector` is unused** — built and tested, never wired in.
- **The CPU-sim shim fails** (`test_stream_ip_sim.py`, 4 tests): allo_sup's FIFO
  struct has 7 fields against upstream's 3, so the shim's call-site lowering never
  fires. The HLS path was the deliverable.

Gaps specific to the SystemC strands:

- **§5's emitter half is not started**, so Allo can *accept* a SystemC IP but not
  yet *generate a design containing one*. That is C++ in the MLIR translation
  layer and cannot be validated without a SystemC build.
- **HL5 is validated by three short programs, not a suite.** Only
  `lui`/`addi`/`lw`/`sw` are exercised; branches, mul/div, sub-word loads and the
  CSR path are not. Running HL5's own `soft/` programs needs a RISC-V
  cross-compiler that is not installed on this machine.
- **HL5's QoR is improved but not explained.** `hl5_cat/directives.tcl` restores
  the constraints Stratus carried in source (divider unroll, array flattening),
  taking the whole CPU from latency 202 to 170 for +14% area. But unrolling the
  divider *fully* buys nothing further, so most of the remaining cycles are
  still unaccounted for.
- **The generated RTL is not verified against the SystemC.** SCVerify is wired
  up and runs under Xcelium, but the RTL hangs after `fetch_en` asserts, so
  equivalence is unproven. `fedec` also sets the critical path with only
  +0.005 ns of slack — a pass with no margin.
- **HL5's testbench checks nothing.** `Simulation PASSED` is printed
  unconditionally and Columbia's correctness block is commented out; the real
  evidence is `fedec`'s register trace and the `MMIO OUT:` lines.
- **The IP boundary may be the wrong shape.** Real EVA's CPU does not stream
  packets — it writes four descriptor words and pulses a trigger, and a hardware
  DMA (`router_driver_slice.sv`) synthesises the packet headers. If this IP
  should mirror that, `mmio_*` wants to be a descriptor/trigger interface rather
  than a packet stream.
