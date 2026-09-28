#!/bin/bash
set -o pipefail
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
cd /home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
echo "==== mmm CYCDUMP cosim START $(date) ===="
{ /usr/bin/time -v vitis-run --mode hls --cosim --config /home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb/ci_ii2run_mmm_cycdump.ini --work_dir /work/shared/users/zsm9/eva_ts_8x8_rtl/wd ; } 2>&1   | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" > /home/zsm9/final_eva_performance/results/ii2_cosim/mmm_cycdump.log
echo "==== mmm CYCDUMP cosim DONE rc=$? $(date) ===="
echo "MMM_CYCDUMP_DONE" >> /home/zsm9/final_eva_performance/results/ii2_cosim/mmm_cycdump.log
