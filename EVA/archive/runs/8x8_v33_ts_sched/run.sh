#!/bin/bash
# 8x8 FINAL candidate: v3.3 (Channel, no credit planes, TIMESTAMPED) SCHEDULED csyn.
# Detached so it survives session teardown. Re-runnable as-is.
cd /home/zsm9/final_eva_systemc
export CHIP=eva_v3_nocred_ts   # Channel links, both credit planes deleted, out_cyc_* ports
export MESH=8                  # 64 PEs
export SCHED=1                 # 64 x #pragma hls_pipeline_init_interval
export PARTITION=0             # MANDATORY: partition_rf is a no-op here, makes emit intractable
export NSTEP=800               # headroom so ONE RTL can host fft/cordic/mmm replays (Vitis used LFORCE=800)
export MODE=csyn
export PRJ=/scratch/zsm9/eva_runs/8x8_v33_ts_sched
export OMP_NUM_THREADS=8
/usr/bin/time -f "8x8 v3.3-ts sched csyn elapsed=%E cpu=%P maxrssMB=%M" \
  -o runs/8x8_v33_ts_sched/time.log \
  /home/zsm9/miniconda3/envs/allo/bin/python scripts/run_systemc.py \
  > runs/8x8_v33_ts_sched/run.log 2>&1
echo "rc=$?" >> runs/8x8_v33_ts_sched/time.log
