# Golden-replay cross-check (functional, Allo simulator)

Runs a chip through the Allo functional simulator on the **real golden `EVA_untouched`
programs** (mmm / fft / cordic) and diffs bit-exact vs the captured golden-RTL outputs. This is
the *functional* (value) check; RTL cosim is the cycle-accurate one (see
[`../results/final_chips/`](../results/final_chips/)).

`run_golden_chip.py` aliases the module `eva` → the chip under test and runs a dedicated replay;
it honors `CHIP`, `PRIME`, `DEPTH`, `MARGIN` env vars. `replay_golden_{mmm,fft}.py` are
per-workload replays; `replay_golden_generic.py` is the shared driver.

## Run (allo env)
```bash
LLVM=/home/zsm9/miniconda3/envs/allo        # LLVM_BUILD_DIR
CHIP=<chip module>                          # e.g. a chip from results/final_chips/*/chip/

MARGIN=1200 CHIP=$CHIP LLVM_BUILD_DIR=$LLVM python run_golden_chip.py mmm              # -> 16/16
CHIP=$CHIP        LLVM_BUILD_DIR=$LLVM python run_golden_chip.py cordic                # -> 48/48
PRIME=1 MARGIN=1600 CHIP=$CHIP LLVM_BUILD_DIR=$LLVM python run_golden_chip.py fft      # -> 16/16
```

## Notes
- **MARGIN** = NSTEP headroom; the scoreboard family needs a large value to drain all lanes
  (`0/16` → raise MARGIN first).
- **fft needs PRIME=1** in functional sim — an OMP-starvation artifact on the cyclic butterfly,
  not a hardware requirement (RTL idles bubbles by valid bit and can't starve). RTL cosim at the
  normal prime settles it.
- Golden material: programs in `EVA_untouched/EVA/tb/pe_array/<wl>/`; captured outputs in
  `~/eva_tb_logs/pe_array_<wl>.out`.
