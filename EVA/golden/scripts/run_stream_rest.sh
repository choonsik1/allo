#!/bin/bash
# B=300 streaming cosim for fft + 4 cordic on the Allo ts chip, reusing the 13h RTL
# (workload-independent kernel). Warnings stripped inline. Serial (shared work_dir).
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
TS=/work/shared/users/zsm9/eva_ts_8x8_rtl
PRIME=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/final_eva_performance/results/allo_stream; mkdir -p $DEST
SUM=$DEST/00_stream_summary.txt
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo:$PRIME LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel
cd $SC
echo "==== Allo B=300 stream sweep (fft+cordic) START $(date) ====" | tee -a $SUM
# WL:PRIME  (mmm already done; these all use prime=3)
for entry in fft:3 cordic_cr:3 cordic_cv:3 cordic_hr:3 cordic_hv:3; do
  WL=${entry%%:*}; PR=${entry##*:}
  echo "---- $WL B=300 (prime=$PR) START $(date +%H:%M:%S) ----" | tee -a $SUM
  # reuse the 13h RTL: pre-place kernel so vector-gen skips re-synth
  PRJ=$SC/prj_gctsst_${WL}_8x8_L2000; mkdir -p $PRJ; cp $TS/kernel_ts_sched.cpp $PRJ/kernel.cpp
  # B=300 vectors
  CHIP=eva_sb_syscredit_rtprime_ts WL=$WL B=300 LFORCE=2000 TAG=gctsst MESH=8 PRIME=$PR \
    TB=tb_replay_golden_prime_ts.cpp /home/zsm9/miniconda3/envs/allo/bin/python build_golden_cosim.py \
    > $DEST/${WL}_vecgen.log 2>&1
  # ini (reuse the synthesized kernel + wd)
  cat > $SC/ci_stream_${WL}.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$TS/kernel_ts_sched.cpp
syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS
tb.file=$SC/tb_replay_golden_prime_ts.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_gctsst_${WL}_8x8.h"
syn.compile.pipeline_loops=0
INI
  # cosim, strip the "read while empty" warning flood inline
  { /usr/bin/time -v vitis-run --mode hls --cosim --config $SC/ci_stream_${WL}.ini --work_dir $TS/wd ; } 2>&1 \
    | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" > $DEST/${WL}_B300.log
  echo "  $WL result:" | tee -a $SUM
  grep -E "row [0-9]:|PASS:|FAIL:|Elapsed \(wall" $DEST/${WL}_B300.log 2>/dev/null | tail -12 | sed 's/^/    /' | tee -a $SUM
done
echo "==== SWEEP DONE $(date) ====" | tee -a $SUM
