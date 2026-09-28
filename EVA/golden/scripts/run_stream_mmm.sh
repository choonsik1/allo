#!/bin/bash
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
TS=/work/shared/users/zsm9/eva_ts_8x8_rtl
DEST=/home/zsm9/final_eva_performance/results/allo_stream; mkdir -p $DEST
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
cd $SC
echo "==== Allo mmm B=300 stream cosim START $(date) ====" | tee $DEST/mmm_B300.log
/usr/bin/time -v vitis-run --mode hls --cosim --config $SC/ci_stream_mmm.ini --work_dir $TS/wd >> $DEST/mmm_B300.log 2>&1
echo "==== DONE rc=$? $(date) ====" | tee -a $DEST/mmm_B300.log
grep -E "row [0-9]:|drained|PASS:|FAIL:|Elapsed \(wall" $DEST/mmm_B300.log | tail -20 | tee -a $DEST/00_mmm_summary.txt
