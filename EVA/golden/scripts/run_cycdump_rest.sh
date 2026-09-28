#!/bin/bash
set -o pipefail
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
cd /home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
SUM=/home/zsm9/final_eva_performance/results/ii2_cosim/00_CYCDUMP_SUMMARY.txt
echo "==== CYCDUMP batch (fft+cordic×4) — waiting for mmm to free the wd $(date) ====" | tee $SUM
# mmm cosim shares /work/shared/users/zsm9/eva_ts_8x8_rtl/wd — wait for it to finish
while ! grep -q MMM_CYCDUMP_DONE /home/zsm9/final_eva_performance/results/ii2_cosim/mmm_cycdump.log 2>/dev/null; do sleep 30; done
echo "  mmm done; starting batch $(date)" | tee -a $SUM
for WL in fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  echo "---- $WL CYCDUMP $(date) ----" | tee -a $SUM
  sed 's/-DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR/-DALLOW_EMPTY_HLS_STREAM_READS -DDUMP_CYC -DVECHDR/'       /home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb/ci_ii2run_${WL}.ini > /home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb/ci_ii2run_${WL}_cycdump.ini
  { /usr/bin/time -v vitis-run --mode hls --cosim --config /home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb/ci_ii2run_${WL}_cycdump.ini --work_dir /work/shared/users/zsm9/eva_ts_8x8_rtl/wd ; } 2>&1     | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" > /home/zsm9/final_eva_performance/results/ii2_cosim/${WL}_cycdump.log
  n=$(grep -c CYCDUMP /home/zsm9/final_eva_performance/results/ii2_cosim/${WL}_cycdump.log 2>/dev/null)
  v=$(grep -E "co-simulation finished: (PASS|FAIL)" /home/zsm9/final_eva_performance/results/ii2_cosim/${WL}_cycdump.log | tail -1)
  echo "    $WL: $n CYCDUMP lines | $v" | tee -a $SUM
done
echo "==== CYCDUMP batch DONE $(date) ====" | tee -a $SUM
echo "CYCDUMP_BATCH_DONE" | tee -a $SUM
