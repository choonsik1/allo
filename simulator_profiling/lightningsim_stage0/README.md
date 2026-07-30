# LightningSim Stage 0 — proof that an Allo design can be traced

**Result (2026-07-30): PASS. LightningSim `top` = 21 cycles = csynth `top` = 21, exact.**

```
[ 0-20] top                <-- 21 cycles inclusive
        [ 0- 0] entry_proc
        [ 0- 4] producer_0
        [ 1- 5] consumer_0
        [ 6-20] store_res0.1    <-- 15 cycles our simulator charges ZERO
```

Design: Allo's blocking producer/consumer (producer writes i*10 for i in 0..3 into a
depth-4 stream; consumer drains it; store_res0 copies to the m_axi output).
Sources copied from `blocking_stream_csynth.prj`, with the three fixes below.

## Reproduce

```bash
cp -r . /somewhere/scratch && cd /somewhere/scratch
export PATH=/opt/xilinx/Vitis_HLS/2023.2/bin:$PATH
vitis_hls -f run.tcl                      # ~35 s
conda activate lightningsim
lightningsim --cli out.prj/solution1
```

## Three Allo-side blockers found (all fixable in the emitter — Stage 2)

1. **`host.cpp` is an OpenCL host program.** LightningSim builds whatever is registered
   with `add_files -tb`, so it tried to compile the OpenCL host and died on
   `CL/cl2.hpp: No such file`. Fix: a native `tb.cpp` calling `top()` directly.
2. **Generated `kernel.h` uses `int32_t` without including `<cstdint>`.** `kernel.cpp`
   only gets away with it because other headers come first. Any native testbench that
   includes `kernel.h` first fails to compile. Fix in the emitter, or include `<cstdint>`
   before `kernel.h`.
3. **`#pragma HLS pipeline II=1 rewind` breaks the link:**
   `undefined reference to _ssdm_op_Return`. LightningSim's runtime does not provide that
   intrinsic. Removing `rewind` fixes it.
   **Caveat: this perturbs the design.** With `rewind`, csynth reported `top` 19–20;
   without it, 21. So the comparison above is self-consistent (both 21) but is NOT the
   same design as the original `blocking_stream_csynth.prj`. A proper fix would stub
   `_ssdm_op_Return` rather than drop the pragma.

## Why the breakdown matters

Our simulator reports makespan **7** for this design; csynth and LightningSim both say
**21**. The breakdown localises the whole gap: `store_res0.1` occupies cycles 6–20 (15
cycles) and our cost model charges the `load_buf`/`store_res` wrappers **zero**.
7 + ~14 ≈ 21. This confirms the hypothesis recorded in `../../simulator_cycle_model.md`
§1 that the unclocked wrappers cause the 0.4x makespan — it was a guess, now measured.
