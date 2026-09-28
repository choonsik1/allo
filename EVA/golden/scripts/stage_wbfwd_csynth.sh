#!/bin/bash
# Stage: csynth the ts_wbfwd (honest-II=1, FWD=0, out_cyc) chip at 4x4 so we can
# stream mmm and measure cyc/MMM + latency. build_golden_cosim.py emits + csynths
# (SCHED=1 = pipeline_node II=1 attempt). Kernel is workload-independent -> reuse
# for the streaming cosim afterward. ~tens of min (4x4, not 8x8's 13h).
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIME=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/final_eva_performance/results/allo_stream/wbfwd; mkdir -p $DEST
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo:$PRIME LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel
cd $SC
echo "==== ts_wbfwd 4x4 csynth (SCHED II=1) START $(date) ====" | tee $DEST/csynth.log
CHIP=eva_sb_syscredit_rtprime_ts_wbfwd WL=mmm MESH=4 LFORCE=2000 TAG=wbf SCHED=1 PRIME=6 \
  TB=tb_replay_golden_prime_ts.cpp /home/zsm9/miniconda3/envs/allo/bin/python build_golden_cosim.py \
  >> $DEST/csynth.log 2>&1
echo "==== csynth rc=$? $(date) ====" | tee -a $DEST/csynth.log
# report the ACHIEVED II from the synth report (is it really II=1?)
echo "--- achieved II (node loop) ---" | tee -a $DEST/csynth.log
grep -rhoE "II=[0-9]+|Pipelined.*II|Initiation Interval.*[0-9]" $SC/prj_wbf_mmm_4x4_L2000_sched/*.rpt \
  $SC/prj_wbf_mmm_4x4_L2000_sched/hls/syn/report/*.rpt 2>/dev/null | sort -u | head | tee -a $DEST/csynth.log
echo "WBFWD_CSYNTH_DONE" | tee -a $DEST/csynth.log
