
## SystemC backend: single-shot kernel execution (EmitSystemC.cpp)
- Kernel run() body now executes ONCE then idles (`body; while(1) wait();`) instead
  of free-running `while(1){body}`. Fixes `both` (read-modify-write) memory
  accumulators that re-accumulated every pass.
- csim `__allo_done` counter (guarded out of __SYNTHESIS__): each kernel bumps it
  after its single pass; the memory-output testbench advances the clock until all
  kernel instances complete before reading memories, replacing a fixed cycle count.
- Net: +4 dataflow examples pass bit-exact (tiled_gemm, pingpong_gemm, hierachical,
  wrap_movement). Suite 28/28 unchanged. Synthesis-neutral (idle loop + guarded
  counter). NOTE: csynth already broken branch-wide by the ap_int subclass shim
  (2b1e66f) — unrelated.
