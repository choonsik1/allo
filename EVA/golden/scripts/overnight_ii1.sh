#!/bin/bash
# ============================================================================
# overnight_ii1.sh — csynth + cosim the II=1 EVA chips at 4x4 for mmm, overnight.
# Runs three variants sequentially, each into its OWN result dir; never aborts
# the whole run if one fails (so you get whatever completes by morning).
#   1) wbfwd  NOSCHED II=1  (FWD=0 base)       -> anchor, expect 9.0 cyc/MMM
#   2) wbfwd  SCHED   II=1  (FWD=0 pipelined)  -> TEST the "9.0 identical" claim
#   3) fwd_cosim SCHED II=1 (FWD=1 forwarding) -> the fast ~4-6 cyc/MMM chip
# Results: final_eva_performance/results/allo_stream/overnight_ii1/
#   00_OVERNIGHT_SUMMARY.txt  +  {wbfwd_nosched,wbfwd_sched,fwd_cosim_sched}/
# ============================================================================
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
FR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs
OUT=/home/zsm9/final_eva_performance/results/allo_stream/overnight_ii1; mkdir -p $OUT
SUM=$OUT/00_OVERNIGHT_SUMMARY.txt
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
PY=/home/zsm9/miniconda3/envs/allo/bin/python
echo "==== OVERNIGHT II=1 csynth+cosim START $(date) ====" | tee $SUM

# --- wbfwd (FWD=0) via the existing 4x4 harness; redirect its fixed DEST after each ---
run_wbfwd () {   # $1 = arg4 (0=SCHED, 1=NOSCHED)   $2 = label
  echo "---- wbfwd ($2) START $(date) ----" | tee -a $SUM
  bash $SC/run_wbfwd_stream.sh 300 2000 6 $1 > $OUT/wbfwd_$2_driver.log 2>&1
  rm -rf $OUT/wbfwd_$2; cp -r /home/zsm9/final_eva_performance/results/allo_stream/wbfwd_ii1 $OUT/wbfwd_$2 2>/dev/null
  grep -E "cyc/MMM|bit-exact|co-simulation finished|CSYNTH FAIL|BUILD FAIL" $OUT/wbfwd_$2/00.log 2>/dev/null \
    | tail -8 | sed 's/^/    /' | tee -a $SUM
  echo "---- wbfwd ($2) END $(date) ----" | tee -a $SUM
}

# --- fwd_cosim (FWD=1) : emit (build_val_sched_ts) -> csynth (v++ -c) -> cosim ---
run_fwd_cosim () {   # $1=BATCH $2=L $3=NOSCHED(0/1)  $4=label
  local B=$1 L=$2 NS=$3 lbl=$4
  local D=$OUT/fwd_cosim_$lbl; mkdir -p $D
  export PYTHONPATH=/home/zsm9/allo_sup:$FR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
  echo "---- fwd_cosim ($lbl) B=$B L=$L START $(date) ----" | tee -a $SUM
  cd $SC
  CHIP=eva_sb_syscredit_fwd_cosim SZ=4 LFORCE=$L BATCH=$B NOSCHED=$NS $PY build_val_sched_ts.py > $D/build.log 2>&1
  local PRJ=$(grep -E "^PRJ=" $D/build.log | tail -1 | cut -d= -f2)
  local INI=$(grep -E "^INI=" $D/build.log | tail -1 | cut -d= -f2)
  echo "    PRJ=$PRJ" | tee -a $SUM
  if [ -z "$PRJ" ] || [ ! -f "$PRJ/kernel.cpp" ]; then
    echo "    fwd_cosim BUILD FAIL:" | tee -a $SUM; tail -15 $D/build.log | sed 's/^/      /' | tee -a $SUM
    echo "---- fwd_cosim ($lbl) END(build-fail) $(date) ----" | tee -a $SUM; return 1
  fi
  local WD=/work/shared/users/zsm9/fwd_cosim_${lbl}_wd; rm -rf $WD; mkdir -p $WD
  echo "    csynth $(date)" | tee -a $SUM
  v++ -c --mode hls --config $INI --work_dir $WD > $D/csynth.log 2>&1
  if [ ! -d $WD/hls/syn ]; then
    echo "    fwd_cosim CSYNTH FAIL:" | tee -a $SUM; tail -15 $D/csynth.log | sed 's/^/      /' | tee -a $SUM
    echo "---- fwd_cosim ($lbl) END(csynth-fail) $(date) ----" | tee -a $SUM; return 1
  fi
  echo "    csynth OK ($(ls $WD/hls/syn/verilog/*.v 2>/dev/null | wc -l) .v); cosim $(date)" | tee -a $SUM
  { /usr/bin/time -v vitis-run --mode hls --cosim --config $INI --work_dir $WD ; } 2>&1 \
    | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" > $D/cosim.log
  grep -E "cyc/MMM|col [0-9]|PASS|FAIL|co-simulation finished|Elapsed \(wall|MISMATCH" $D/cosim.log \
    | tail -14 | sed 's/^/    /' | tee -a $SUM
  echo "---- fwd_cosim ($lbl) END $(date) ----" | tee -a $SUM
}

run_wbfwd 1 nosched      # FWD=0 NOSCHED (anchor)
run_wbfwd 0 sched        # FWD=0 SCHED II=1 (the claim under test)
run_fwd_cosim 40 1000 0 sched   # FWD=1 SCHED II=1 (fast forwarding chip)

echo "==== OVERNIGHT II=1 DONE $(date) ====" | tee -a $SUM
echo "OVERNIGHT_II1_DONE" | tee -a $SUM
