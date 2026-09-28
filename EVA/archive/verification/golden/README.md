# golden/ — self-contained golden cross-check data

Bundled copy of the ONLY non-Allo inputs the golden cross-check needs, so
`verification/` runs without depending on `/home/zsm9/allo/...` or
`/home/zsm9/eva_tb_logs/...`.

## programs/
The original EVA_untouched RTL's per-workload programs (copied verbatim from
`EVA_untouched/EVA/tb/pe_array/<workload>/`). Each dir holds:
- `file_col_upp_0..7.mem` — the actual instructions + weights/twiddles the golden
  chip runs, as router packets (`id=..,mode=..,addr=..,data=..`). **The harness
  parses these**, translates the encoding (`nrev()`), and loads them onto our chip.
- `tb_pe_array_<wl>.sv` — the golden testbench. **The harness parses the hardcoded
  input vectors** (`*_inputs = { 16'h.. }`) out of it and injects those exact values.
- `.txt` / `assembler.py` — human-readable program + the golden assembler (reference).

Workloads: mmm, fft, cordic_{circular,hyperbolic}_{rotation,vectoring}, ldl.

## expected/
`pe_array_<name>.out` — the outputs a real **VCS run of the original RTL** produced
(captured 2026-04-22). **The harness diffs our chip's outputs against these,
bit-for-bit.** Names: mmm, fft, cordic_{cr,cv,hr,hv}, ldl.

## To regenerate expected/ (optional, needs VCS)
`SNPSLMD_LICENSE_FILE=27020@en-license-05.coecis.cornell.edu`; run
`EVA_org_claude/EVA/rsim/pe_array` `make sim <wl>=1` and capture `sys_tx_*` lines.

Used by `../replay_golden_syscredit.py` (paths are `__file__`-relative).
