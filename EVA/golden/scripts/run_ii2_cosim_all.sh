#!/bin/bash
# ============================================================================
# run_ii2_cosim_all.sh — re-run the FULL cosim suite on the FINAL II=2 chip
# (eva_sb_syscredit_rtprime_ts, the runtime-prime scheduled II=2 chip, 8x8).
#
# Reuses the PRE-SYNTHESIZED RTL at /work/shared/users/zsm9/eva_ts_8x8_rtl/wd
# (the workload-INDEPENDENT kernel_ts_sched.cpp, csynth'd once ~13h) — so each
# workload is a cosim-only run (~30 min), NO re-synthesis.
#
# For each workload it: (1) generates B=BATCH streaming vectors (build_golden_cosim),
# (2) cosims reusing the RTL, (3) prints per-row bit-exactness + out_cyc throughput.
#
# USAGE:   ./run_ii2_cosim_all.sh [BATCH]        (default BATCH=300)
# Results: final_eva_performance/results/ii2_cosim/<WL>.log + 00_SUMMARY.txt
# ============================================================================
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
TS=/work/shared/users/zsm9/eva_ts_8x8_rtl
KERN=$TS/kernel_ts_sched.cpp
DEST=/home/zsm9/final_eva_performance/results/ii2_cosim; mkdir -p $DEST
SUM=$DEST/00_SUMMARY.txt
BATCH=${1:-300}
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
cd $SC

if [ ! -d $TS/wd/hls/syn ]; then
  echo "ERROR: pre-synth RTL missing at $TS/wd/hls/syn — need the 13h csynth first (build_ts_8x8.sh)." | tee $SUM; exit 1
fi
echo "==== FINAL II=2 CHIP cosim suite (B=$BATCH, reuse RTL) START $(date) ====" | tee $SUM

# workload : prime  (mmm drains SOUTH p6; fft/cordic drain EAST p3)
for entry in mmm:6 fft:3 cordic_cr:3 cordic_cv:3 cordic_hr:3 cordic_hv:3; do
  WL=${entry%%:*}; PR=${entry##*:}
  echo "---- $WL (prime=$PR) $(date +%H:%M:%S) ----" | tee -a $SUM
  # pre-place the synth'd kernel so vec-gen SKIPS re-synth
  PRJ=$SC/prj_ii2run_${WL}_8x8_L2000; mkdir -p $PRJ; cp $KERN $PRJ/kernel.cpp
  CHIP=eva_sb_syscredit_rtprime_ts WL=$WL B=$BATCH LFORCE=2000 TAG=ii2run MESH=8 PRIME=$PR \
    TB=tb_replay_golden_prime_ts_full.cpp /home/zsm9/miniconda3/envs/allo/bin/python build_golden_cosim.py \
    > $DEST/${WL}_vecgen.log 2>&1
  cat > $SC/ci_ii2run_${WL}.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$KERN
syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS
tb.file=$SC/tb_replay_golden_prime_ts_full.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_ii2run_${WL}_8x8.h"
syn.compile.pipeline_loops=0
INI
  { /usr/bin/time -v vitis-run --mode hls --cosim --config $SC/ci_ii2run_${WL}.ini --work_dir $TS/wd ; } 2>&1 \
    | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" > $DEST/${WL}.log
  if grep -q "200-742\|Deadlock" $DEST/${WL}.log; then echo "  $WL -> DEADLOCK (200-742)" | tee -a $SUM
  else grep -E "rows bit-exact|FULL-STREAM: [0-9].*ALL-OK|Elapsed \(wall" $DEST/${WL}.log 2>/dev/null | tail -10 | sed 's/^/    /' | tee -a $SUM; fi
done
echo "==== II=2 COSIM SUITE DONE $(date) ====" | tee -a $SUM
