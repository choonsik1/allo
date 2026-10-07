# Golden stimuli + captured outputs (for driving the Allo EVA chips)

Self-contained snapshot of the **golden EVA RTL** stimuli and their captured outputs, so any
Allo chip (bubble / skid / elastic) can be driven with the exact reference workload and checked
bit-exact. Nothing here is derived from our chips — it all comes from the golden RTL under
`/home/zsm9/allo/EVA/EVA_untouched/EVA/` (the spec) and the VCS runs of it.

## Layout
```
gen/
  golden_pegroup_stim.py   # 2x2 stimulus generator (build_golden_pegroup)
  golden_pe_array_stim.py  # 8x8 stimulus generator (build_golden_pe_array)
pe_group_2x2/              # 2x2 = cols 2,3 of the 8x8, REMAPPED to cols 0,1
  mmm/  file_col_upp_2.mem file_col_upp_3.mem   # program (golden ISA — needs nrev())
        activations.txt                          # WEST activation stream (fp16 hex + value)
        golden_out.txt                           # captured SOUTH outputs [22,46]/[34,74]
  fft/  file_col_upp_2.mem file_col_upp_3.mem NOTE.txt   # 2x2 FFT has NO output (structural)
pe_array_8x8/             # full 8x8
  mmm/ fft/  file_col_upp_0..7.mem               # programs
  pe_array_{mmm,fft,cordic_cr,cordic_cv,cordic_hr,cordic_hv,ldl}.out  # captured golden outputs (80/80 bit-exact)
```

## The 2x2 MMM oracle (the one we use as the small correctness check)
- **Program**: `mmm/file_col_upp_2.mem`, `_3.mem` (golden `id=,mode=,addr=,data=` lines).
- **Weights** (from the program's mode=0 DRF write, addr 0): `W = [[1,3],[5,7]]`.
- **Activations** (WEST edge, hardcoded in the golden tb): row0 `[2,6]`, row1 `[4,8]`.
- **Captured golden output** (SOUTH edge `sys_tx_btm_data`): col0 `[22,46]` = `[0x4d80,0x51c0]`,
  col1 `[34,74]` = `[0x5040,0x54a0]`. Self-consistent: `out = Wᵀ@act`.
- Captured by adding a `$display` monitor on `sys_tx_btm_2/3.data` to
  `EVA_org_claude/EVA/tb/pe_group/mmm/tb_pe_group_mmm.sv` and running VCS (the untouched pe_group
  tb does not `$display` outputs). fp16 hex→value = `np.uint16(h).view(np.float16)`.

## How the generators turn this into chip stimulus
`gen/golden_pegroup_stim.py :: build_golden_pegroup(chip, wl, f16, REPS)` and
`gen/golden_pe_array_stim.py :: build_golden_pe_array(chip, wl, f16, WL, LF, REPS)`:
1. parse the `.mem` → `nrev()` **semantic translation** (golden ISA differs from ours: field
   order reversed + MOV/SQRT source slot — you CANNOT feed golden `.mem` raw);
2. `wl.load_prog_packets(prog, M, N, data=weights, cfg=...)` → `rin_s` (SOUTH router driver stream:
   `id=row` packets ride NORTH up each column, deliver to node(row,col), write its RF, last packet
   flips `fetch_en`);
3. activations → WEST `in_w`/`iv_w`; expected outputs → `EOUT[out_idx]`.
The 2x2 remaps cols 2,3 → 0,1 via `enumerate` (the pe_array generator takes the col straight from
the filename, so it is 8x8-only — do NOT point it at pe_group `.mem`).

## Driving an Allo chip with it
A generator (see [`../../../generators/`](../../../generators/)) parses the `.mem` program
(`nrev()` translation), emits a `vectors.h` (IN/IV/RIN/EOUT, + `PRIMECFG` for runtime-prime chips),
and cosims it against the captured golden. Testbenches are in
[`../../testbenches/`](../../testbenches/): `tb_skid_cosim.cpp` (blocking/credit chips — has
`prime_cfg`) and `tb_replay_golden.cpp` (elastic — no `prime_cfg`); the two differ only by `prime_cfg`.

## Gotchas (learned the hard way)
- **NEVER** use synthetic `load_mmm_router` for multi-PE — "exact for 1×1 only" (omits the `i+3j`
  systolic skew), 2x2+ comes out wrong. Multi-PE MUST use these golden programs.
- `iter=0` (Inf) for both mmm and fft — streamed activations drive the count (matches the proven
  `build_golden_cosim.py`). Baking a finite iter desyncs `rin_s`.
- 2x2 FFT has no golden output (structural) — use MMM at 2x2, or the 8x8 for FFT.
- Golden RTL source of truth stays under `EVA_untouched/`; these copies are a mirror for portability.
