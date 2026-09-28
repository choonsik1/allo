# EVA forwarding scoreboard PE — final deliverable

Programmable EVA PE rebuilt in Allo HLS with **golden-style operand forwarding**
(read a producer's result straight from the `resq` ring instead of stalling to the
DRF). Two variants, each characterized 1×1 (csynth + P&R) and 4×4 (RTL cosim),
`xczu7ev`, Vitis 2025.1, fp16, II=1.

- **`non_syscredit_1x1/`** — `eva_sb_fwd`: scoreboard + forwarding, systolic plane uses
  the bubble / always-fire model (no systolic credits).
- **`syscredit_1x1/`** — `eva_sb_syscredit_fwd`: same PE **+ a lossless credit plane** on
  the systolic path (backpressure = golden req/grant).

## QoR (1×1, post-route, target 3.333 ns / 300 MHz — both miss target, route clean)

| chip | II | CP achieved | LUT | FF | CARRY8 | DSP |
|---|---|---|---|---|---|---|
| non-syscredit | 1 | **4.297 ns (~233 MHz)** | 4394 | 3239 | 156 | 2 |
| syscredit | 1 | **4.358 ns (~229 MHz)** | 5103 | 4042 | 268 | 2 |

Credit plane costs ~700 LUT / ~800 FF / +1.4 % CP.

## Throughput (cyc/MAC, RTL cosim)

| | 1×1 PE | 4×4 array (per column, II=1, `4x4/ts/`) |
|---|---|---|
| non-syscredit | **4 cyc/MAC** | **4.0 cyc/MMM** |
| syscredit | **4 cyc/MAC** | **~5.3 cyc/MMM** (credit backpressure ≈ +1.3) |

Values bit-exact in steady state; the first 1–2 outputs are pipeline-fill (discard,
as on any systolic array). 4 cyc/MAC = the single-issue scalar floor (a MAC = 4 instrs
at II=1); the array recovers throughput via N² columns in parallel.

## Layout (per chip)
```
<chip>_1x1/
  <chip>.py  gen*.py  kernel.cpp  *.ini      chip source + generator + generated HLS
  reports/   csynth.rpt + pnr_{summary,timing,utilization}.rpt
  rtl/       generated Verilog (1×1)
  4x4/       kernel + ini + vectors + tb + reports/top_cosim.rpt + rtl/   (mmm cosim PASS, B=1)
    ts/      scheduled + timestamped B=4 run: kernel + cyc_mmm.log + reports/top_cosim.rpt
```

## Reproduce
```bash
# 1×1 gen (allo env):  PYTHONPATH=/home/zsm9/allo_sup LLVM_BUILD_DIR=.../build_xcel python <chip>_1x1/gen*.py
# csynth+P&R (Vitis 2025.1):  v++ -c --mode hls --config <ini> --work_dir top
#                             vitis-run --mode hls --impl --config <ini> --work_dir top
# 4x4 cosim + timestamped ts: final_runs/cosim_8x8/eva_sb_nb/{build_val.py, run_ts_sched.sh}
```
C-sim is always all-zero (dataflow+feedback can't run in sequential csim); the RTL
cosim post-check block is authoritative.
