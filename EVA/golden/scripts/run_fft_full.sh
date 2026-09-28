#!/bin/bash
# fft B=300 FULL-STREAM correctness check: verify EVERY drained word matches the
# repeated golden pattern (not just the first). Separate wd -> parallel to the sweep.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
TS=/work/shared/users/zsm9/eva_ts_8x8_rtl
WD2=$TS/wd_fftfull
DEST=/home/zsm9/final_eva_performance/results/allo_stream; mkdir -p $DEST
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
cd $SC
echo "==== fft FULL-STREAM check START $(date) ====" | tee $DEST/fft_full.log
[ -d $WD2/hls/syn ] || { echo "copying wd (5.4G)..." | tee -a $DEST/fft_full.log; cp -r $TS/wd $WD2; }
cat > $SC/ci_fftfull.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$TS/kernel_ts_sched.cpp
syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS
tb.file=$SC/tb_replay_golden_prime_ts_full.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_gctsst_fft_8x8.h"
syn.compile.pipeline_loops=0
INI
{ /usr/bin/time -v vitis-run --mode hls --cosim --config $SC/ci_fftfull.ini --work_dir $WD2 ; } 2>&1 \
  | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" >> $DEST/fft_full.log
echo "==== DONE rc=$? $(date) ====" | tee -a $DEST/fft_full.log
echo "--- FULL-STREAM verdict ---" | tee -a $DEST/fft_full.log
grep -E "row [0-9] FULL-STREAM|PASS:|FAIL:|Elapsed \(wall" $DEST/fft_full.log | tee -a $DEST/00_fft_full_summary.txt
