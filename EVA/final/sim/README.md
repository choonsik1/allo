# Golden-SIMULATOR cross-check (functional, Allo simulator)

Runs the chip through the Allo functional simulator on the **real golden EVA_untouched
programs** (mmm / fft / cordic) and diffs bit-exact vs the captured golden-RTL outputs.
This is the *functional* check (values); RTL cosim (in each chip's `4x4/`) is the
cycle-accurate one.

`run_golden_chip.py` aliases module `eva` -> any chip in `final_runs/` and runs a
dedicated replay. It honors `CHIP`, `PRIME`, `DEPTH`, `MARGIN` env vars.

## Commands (from `Allo/EVA/tests/`, allo env) — all bit-exact on the fwd chip
```bash
LLVM=/home/zsm9/miniconda3/envs/allo    # LLVM_BUILD_DIR
CHIP=eva_sb_syscredit_fwd

# mmm  -> 16/16   (credit default PRIME=6; scoreboard needs a big MARGIN)
MARGIN=1200 CHIP=$CHIP LLVM_BUILD_DIR=$LLVM python run_golden_chip.py mmm

# cordic x4 -> 48/48   (PRIME=6)
CHIP=$CHIP LLVM_BUILD_DIR=$LLVM python run_golden_chip.py cordic

# fft -> 16/16   (needs PRIME=1: the butterfly deadlocks the credit plane at 6 in sim)
PRIME=1 MARGIN=1600 CHIP=$CHIP LLVM_BUILD_DIR=$LLVM python run_golden_chip.py fft
```

## Notes
- **PRIME**: mmm/cordic run at the chip default (6); **fft needs PRIME=1** — a
  functional-sim artifact (OMP starvation on the cyclic butterfly), most likely NOT a
  hardware requirement (RTL IDs bubbles by valid bit and can't starve). RTL cosim at
  PRIME=6 would settle it.
- **MARGIN**: the scoreboard family has deep ring + credit latency, so the functional
  sim needs a large NSTEP (`MARGIN`) to drain all lanes. `0/16` -> raise MARGIN first.
- Golden material: programs `/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array/<wl>/`,
  captured outputs `/home/zsm9/eva_tb_logs/pe_array_<wl>.out` (self-contained copy in
  `final_runs/verification/golden/`).
- `eva_sb_fwd` (non-syscredit) works the same at its own PRIME defaults.
```
```
