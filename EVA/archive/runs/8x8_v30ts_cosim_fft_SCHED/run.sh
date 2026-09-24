#!/bin/bash
# 8x8 RTL COSIM, SCHEDULED — v3.0+ts (Channel links, credits KEPT) + 64 x
# #pragma hls_pipeline_init_interval. Detached; survives logout.
# Preflight (csim, 8x8, SCHED=1): 64 pragmas, 8/8 rows, 0 mismatches, 7.53 cyc/val.
cd /home/zsm9/final_eva_systemc
export CHIP=eva_v3_channel_ts
export WL=fft
export MESH=8
export SCHED=1                 # 64 pipeline pragmas (one per node)
export PARTITION=0             # MANDATORY: partition_rf is a no-op but makes emit intractable
export REPS=8
export MARGIN=800
export PRIME=1
export TS=1
export MODE=cosim
export PRJ=/scratch/zsm9/eva_runs/8x8_v30ts_cosim_fft_SCHED
export OMP_NUM_THREADS=8
export ALLO_COSIM_SYNTH_TIMEOUT=72000    # 20 h; unscheduled took 7 h, pragmas enlarge scheduling
export ALLO_COSIM_SIM_TIMEOUT=14400
/usr/bin/time -f "8x8 v3.0ts SCHED cosim fft elapsed=%E cpu=%P maxrssMB=%M" \
  -o runs/8x8_v30ts_cosim_fft_SCHED/time.log \
  /home/zsm9/miniconda3/envs/allo/bin/python scripts/run_golden_systemc.py \
  > runs/8x8_v30ts_cosim_fft_SCHED/run.log 2>&1
echo "rc=$?" >> runs/8x8_v30ts_cosim_fft_SCHED/time.log
