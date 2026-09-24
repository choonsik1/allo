#!/bin/bash
# 8x8 RTL COSIM of the SOUND design (v3.0: Channel links, credits KEPT) + timestamps,
# replaying the shipped golden EVA fft. Detached; survives logout.
#   - unscheduled (SCHED bought 0 throughput at 1x1 and enlarges the scheduling problem)
#   - project on /scratch (local, no NFS quota); logs on /home (small)
cd /home/zsm9/final_eva_systemc
export CHIP=eva_v3_channel_ts   # Channel + credits + out_cyc_* ports
export WL=fft
export MESH=8
export REPS=8                   # validated: 128/128 outputs, 0 mismatches in csim
export MARGIN=800
export PRIME=1
export TS=1
export MODE=cosim
export PRJ=/scratch/zsm9/eva_runs/8x8_v30ts_cosim_fft
export OMP_NUM_THREADS=8
export ALLO_COSIM_SYNTH_TIMEOUT=54000    # 15 h; the v3.3 csyn took 6 h
export ALLO_COSIM_SIM_TIMEOUT=14400      # 4 h for the RTL sim
/usr/bin/time -f "8x8 v3.0ts cosim fft elapsed=%E cpu=%P maxrssMB=%M" \
  -o runs/8x8_v30ts_cosim_fft/time.log \
  /home/zsm9/miniconda3/envs/allo/bin/python scripts/run_golden_systemc.py \
  > runs/8x8_v30ts_cosim_fft/run.log 2>&1
echo "rc=$?" >> runs/8x8_v30ts_cosim_fft/time.log
