# Shipped EVA testbenches — RTL cosim on our chip

Every shipped **golden EVA `pe_array` workload** (program from `EVA_untouched/.../file_col_upp_*.mem`,
inputs from the golden `.sv` tb) replayed on our chip and diffed **bit-exact vs the
captured golden RTL outputs** (`/home/zsm9/eva_tb_logs/pe_array_*.out`), 8×8, Vitis 2025.1.

- **Chip:** `eva_sb_syscredit_fwd` (forwarding PE + systolic credit plane).
- **Timestamped runs** use `eva_sb_syscredit_fwd_cosim` (adds `out_cyc` ports) →
  per-workload production-cycle / **cyc-per-value throughput** alongside correctness.
- C-simulation is always all-zero for these dataflow+feedback chips (known artifact);
  the **RTL cosim** verdict is authoritative.

## Key finding — credit priming is drain-direction-dependent
East-draining workloads (**fft, cordic**) need **PRIME=1**; too many credit tokens
starve the deeper rows. South-draining **mmm** is fine at PRIME=6.
- fft: PRIME=6 → 2/8 rows;  **PRIME=1 → 8/8** (bit-exact).
- cordic: PRIME=6 → 4/8 (partial, see `_superseded_prime6/`); PRIME=1 rerun in progress.

## ⭐ ONE-BITSTREAM CAPSTONE — all workloads on a SINGLE synthesized RTL
`one_bitstream/` — the runtime-prime chip (`eva_sb_syscredit_rtprime`) synthesized
**once** (byte-identical kernel across all workloads, md5 in `kernel_md5s.txt` = 1 distinct;
~411 MHz est), then EVERY workload cosim'd against that same RTL — only `prime_cfg`
(runtime input) + program/inputs differ. **All 8/8 bit-exact vs golden:**

| workload | prime_cfg | one-bitstream RTL cosim |
|---|---|---|
| **fft**       | 1 | ✅ **8/8** |
| **cordic_cr** | 1 | ✅ **8/8** |
| **cordic_cv** | 1 | ✅ **8/8** |
| **cordic_hr** | 1 | ✅ **8/8** |
| **cordic_hv** | 1 | ✅ **8/8** |
| **mmm**       | 6 | ✅ **8/8** |
| ldl           | — | ⛔ functional 0/16 — needs ISA mechanisms our PE lacks |

→ A single programmable EVA bitstream runs the whole shipped workload suite, bit-exact.

## Throughput (timestamped `_cosim` chip, per-workload) — COMPLETE
| workload | prime | correctness | cyc/val |
|---|---|---|---|
| fft       | 1 | 8/8 | **1.0**  (span 225..226) |
| cordic_cr | 1 | 8/8 | **16.0** (span 329..345) |
| cordic_cv | 1 | 8/8 | **16.0** |
| cordic_hr | 1 | 8/8 | **16.0** |
| cordic_hv | 1 | 8/8 | **16.0** |
| mmm       | 6 | 8/8 | **4.0**  (span 537..632) — the 4-instr MAC floor |

## Layout
```
<workload>/
  top_cosim.rpt   Vitis HLS C/RTL cosim report
  verdict.txt     per-row OK/x + "N/8 bit-exact" + cyc/val throughput + finished marker
_superseded_prime6/   cordic partials at the wrong prime (kept as record)
```

## Reproduce
```bash
# correctness+throughput, right primes (fft/cordic PRIME=1, mmm PRIME=6):
final_runs/cosim_8x8/eva_sb_nb/run_golden_ts2.sh
# builder (any workload):  TAG=gcts CHIP=eva_sb_syscredit_fwd_cosim WL=<wl> PRIME=<n> \
#   TB=tb_replay_golden_ts.cpp python build_golden_cosim.py
```
