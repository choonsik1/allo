#!/bin/bash
# Wait for the NFS silly-rename lock on sim/verilog to clear, then run the mmm real-cycle flow.
V=/work/shared/users/zsm9/eva_leanfulldsp8x8_rtl/wd/hls/sim/verilog
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
echo "waiting for NFS lock to clear on $V ..."
for i in $(seq 1 60); do   # up to ~30 min
  rm -rf $V 2>/dev/null
  if [ ! -d $V ] || [ -z "$(ls -A $V 2>/dev/null)" ]; then
    if rm -rf $V 2>/dev/null && [ ! -d $V ]; then echo "lock cleared after ${i} tries ($(date))"; break; fi
  fi
  sleep 30
done
if [ -d $V ] && [ -n "$(ls -A $V 2>/dev/null)" ]; then echo "STILL LOCKED after 30min — aborting"; exit 1; fi
echo "running mmm real-cycle flow $(date)"
bash $SC/run_mmm_realcyc.sh
