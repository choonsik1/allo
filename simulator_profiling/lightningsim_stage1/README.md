# LightningSim Stage 1 — per-kernel oracle on a PE from a *cyclic* mesh

**Result (2026-07-30): PASS. LightningSim `node_0_0` = 1014 cycles = csynth `node_0_0`
= 1014, exact.**

This is the result that decides whether LightningSim is useful to us at all. The full
Allo-EVA 2×2 mesh **cannot** be traced — it is cyclic, so a sequential csim cannot
satisfy its reads and the testbench segfaults (see `../../simulator_lightningsim_plan.md`
§2a). Cutting the mesh at the PE boundary removes the cycle and it works.

```
[   0-1023] top
        [   0-   0] entry_proc
        [   0-1005] pe_feed
        [   1-1014] node_0_0                          <-- the PE, 1014 cycles
                [   3-1014] node_0_0_Pipeline_l_S_t_0_t
        [   1-1023] pe_drain
```

## Finding the cost model could not have guessed

`node_0_0_Pipeline_l_S_t_0_t` spans cycles 3–1014 = **1012 cycles for 336 iterations →
II ≈ 3**, despite the source carrying `#pragma HLS pipeline II=1`. Our cost model assumes
`DEFAULT_II = 1` (measured on a *trivial* loop). This PE misses it by 3×. That is exactly
the class of error the ingestion plan in `../../simulator_cycle_model.md` exists to fix.

## Three things the harness must get right

1. **No `hls::stream` in the top-level signature.** Top-level stream ports make Vitis emit
   `streamcpy_hls` glue calling `fpga_fifo_not_empty_4` / `_pop_4` / `_push_4`, which
   LightningSim's runtime does not provide (it models top ports via `_autotb_Fifo*`).
   Link fails. Hence `pe_feed` / `pe_drain` inside a `#pragma HLS dataflow` `top`, with
   all streams internal — the same shape as the Stage 0 design that works.
2. **Drain counts must match production exactly**, or `builder.finish()` raises
   `ValueError: incomplete edges remain`. `node_0_0` writes each output **once before**
   the `t`-loop and **once per iteration**, so it produces `T+1 = 337`, not 336. Check
   write-site indentation to see which sites are inside the loop.
3. **LightningSim 0.2.6 needs a one-line patch** — see below.

## The required patch (upstream bug)

`lightningsim/trace_file.py:~418` infers a FIFO's width from the writing instruction's
payload and asserts the payload has an instruction source:

```python
source_instruction = payload.source
assert isinstance(source_instruction, Instruction)   # fires: source is None
```

For five of this PE's FIFOs the payload has **no** instruction source (constant or
argument), so the assert fires and the run dies. Replacing it with a default width lets
the run complete:

```python
if isinstance(source_instruction, Instruction):
    fifo_widths[...] = source_instruction.bitwidth
else:
    fifo_widths[...] = 32          # or the declared stream width
```

**Caveat:** 32 is a guess, and these are `ap_uint<26>` / `ap_uint<17>` streams. Width
feeds stall analysis, so a wrong width could perturb results — the cycle count matched
csynth exactly here, but that is one data point. The correct fix reads the declared
stream width rather than defaulting. 0.2.6 is a packaged conda binary, so patching
properly means building LightningSim from source.

## Reproduce

```bash
./extract_pe.sh <mesh_kernel.cpp> node_0_0 17 1511 /scratch/pe_test
cd /scratch/pe_test
export PATH=/opt/xilinx/Vitis_HLS/2023.2/bin:$PATH && vitis_hls -f run.tcl   # ~45 s
conda activate lightningsim && lightningsim --cli out.prj/solution1
```

`pe_harness.inc.cpp` is appended to the extracted PE by `extract_pe.sh`; it is
**specific to this PE's 12-in/12-out interface** and must be re-written per PE shape.
Generating it automatically is Stage 2.
