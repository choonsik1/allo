#!/bin/bash
# RECONCILE the fft II=2 streaming discrepancy: rtprime_ts (8/8 at B=300,p3) vs the
# fwd_cosim deadlock (B=20,p1). Both used build_golden_cosim IN-array batching, so the
# axes left are CHIP + B + PRIME. Here we vary B & PRIME on the rtprime RTL we already
# have (reuse the 13h wd, no csynth). Decisive point = B=20,p1 (deadlock's exact B+prime
# on the rtprime chip): if it PASSES -> deadlock is fwd_cosim-specific (chip axis).
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
TS=/work/shared/users/zsm9/eva_ts_8x8_rtl
PRIME=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/final_eva_performance/results/allo_stream/reconcile; mkdir -p $DEST
SUM=$DEST/00_reconcile.txt
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIME LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
cd $SC
echo "==== fft II=2 RECONCILE (rtprime_ts RTL, vary B/prime) START $(date) ====" | tee $SUM
# label:B:PRIME
for entry in "deadlock-match:20:1" "prime-iso:300:1" "B-iso:20:3"; do
  LAB=${entry%%:*}; rest=${entry#*:}; BB=${rest%%:*}; PR=${rest##*:}
  TAG=rec_${LAB}
  echo "---- $LAB  B=$BB prime=$PR  $(date +%H:%M:%S) ----" | tee -a $SUM
  PRJ=$SC/prj_${TAG}_fft_8x8_L2000; mkdir -p $PRJ; cp $TS/kernel_ts_sched.cpp $PRJ/kernel.cpp
  CHIP=eva_sb_syscredit_rtprime_ts WL=fft B=$BB LFORCE=2000 TAG=$TAG MESH=8 PRIME=$PR \
    TB=tb_replay_golden_prime_ts_full.cpp /home/zsm9/miniconda3/envs/allo/bin/python build_golden_cosim.py \
    > $DEST/${LAB}_vecgen.log 2>&1
  cat > $SC/ci_${TAG}.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$TS/kernel_ts_sched.cpp
syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS
tb.file=$SC/tb_replay_golden_prime_ts_full.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_${TAG}_fft_8x8.h"
syn.compile.pipeline_loops=0
INI
  { /usr/bin/time -v vitis-run --mode hls --cosim --config $SC/ci_${TAG}.ini --work_dir $TS/wd ; } 2>&1 \
    | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" > $DEST/${LAB}_B${BB}_p${PR}.log
  echo "  $LAB verdict:" | tee -a $SUM
  if grep -q "200-742\|Deadlock" $DEST/${LAB}_B${BB}_p${PR}.log; then echo "    -> DEADLOCK (200-742)" | tee -a $SUM
  else grep -E "FULL-STREAM|PASS:|FAIL:|Elapsed \(wall" $DEST/${LAB}_B${BB}_p${PR}.log | tail -11 | sed 's/^/    /' | tee -a $SUM; fi
done
echo "==== RECONCILE DONE $(date) ====" | tee -a $SUM
