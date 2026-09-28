#!/bin/bash
# II=1 wbfwd chip (eva_sb_syscredit_rtprime_ts_wbfwd = FINAL rtprime +/- 2 lines,
# FWD=0, out_cyc, prime_cfg) mmm streaming at 4x4. Adapted 4x4 harness:
# build_val_sched_ts_prime.py (emits PRIMECFG) + tb_replay_nb_ts_prime.cpp (prime_cfg).
# Emits+csynths SCHEDULED, then cosim -> cyc/MMM + latency + achieved II.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/final_eva_performance/results/allo_stream/wbfwd_ii1; mkdir -p $DEST
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel
cd $SC
BATCH=${1:-300}; L=${2:-2000}; PR=${3:-6}; SCHED=${4:-0}   # SCHED=0 -> NOSCHED (correct base); 1 -> pipelined II=1 attempt
echo "==== wbfwd mmm stream: build+csynth (SZ=4 B=$BATCH L=$L prime=$PR NOSCHED=$SCHED) START $(date) ====" | tee $DEST/00.log
CHIP=eva_sb_syscredit_rtprime_ts_wbfwd SZ=4 LFORCE=$L BATCH=$BATCH PRIME=$PR NOSCHED=$SCHED \
  /home/zsm9/miniconda3/envs/allo/bin/python build_val_sched_ts_prime.py > $DEST/build.log 2>&1
rc=$?; echo "build rc=$rc $(date)" | tee -a $DEST/00.log
PRJ=$(grep -E "^PRJ=" $DEST/build.log | tail -1 | cut -d= -f2)
INI=$(grep -E "^INI=" $DEST/build.log | tail -1 | cut -d= -f2)
echo "  PRJ=$PRJ  INI=$INI" | tee -a $DEST/00.log
if [ -z "$PRJ" ] || [ ! -f "$PRJ/kernel.cpp" ]; then echo "BUILD FAIL:" | tee -a $DEST/00.log; tail -12 $DEST/build.log | tee -a $DEST/00.log; exit 1; fi
# --- CSYNTH (build only emits the project; synthesize into a fresh work_dir) ---
WD=/work/shared/users/zsm9/wbfwd_ii1_wd; rm -rf $WD; mkdir -p $WD
echo "==== csynth $(date) ====" | tee -a $DEST/00.log
v++ -c --mode hls --config $INI --work_dir $WD > $DEST/csynth.log 2>&1
if [ ! -d $WD/hls/syn ]; then echo "CSYNTH FAILED:" | tee -a $DEST/00.log; tail -15 $DEST/csynth.log | tee -a $DEST/00.log; exit 1; fi
echo "  csynth OK ($(ls $WD/hls/syn/verilog/*.v 2>/dev/null | wc -l) .v files)" | tee -a $DEST/00.log
echo "==== cosim $(date) ====" | tee -a $DEST/00.log
{ /usr/bin/time -v vitis-run --mode hls --cosim --config $INI --work_dir $WD ; } 2>&1 \
  | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" > $DEST/cosim.log
echo "==== DONE rc=$? $(date) ====" | tee -a $DEST/00.log
grep -E "cyc/MMM|col [0-9]|PASS|FAIL|Elapsed \(wall|MISMATCH" $DEST/cosim.log | tail -20 | tee -a $DEST/00.log
echo "WBFWD_STREAM_DONE" | tee -a $DEST/00.log
