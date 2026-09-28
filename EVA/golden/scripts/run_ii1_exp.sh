#!/bin/bash
# II=1 experiments on the FWD=1 rtprime chip, mmm 4x4, fresh work_dirs.
#  A: fp lat=1 (fabric) + NO dep-false  -> does HLS reach honest II=1? correct?
#  B: fp lat=2 + dep-false              -> II=1 via hazard; is mmm still correct?
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/final_eva_performance/results/allo_stream/ii1_exp; mkdir -p $DEST
SUM=$DEST/00_II1_EXP_SUMMARY.txt
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
cd $SC
echo "==== II=1 EXPERIMENTS (rtprime FWD=1, mmm 4x4) START $(date) ====" | tee $SUM

run () {  # $1=EXPTAG $2=FPLAT $3=DEPFALSE $4=MULIMPL  $5=label
  local D=$DEST/$1; mkdir -p $D
  echo "---- EXP $1 ($5) START $(date) ----" | tee -a $SUM
  EXPTAG=$1 FPLAT=$2 DEPFALSE=$3 MULIMPL=$4 \
    CHIP=eva_sb_syscredit_rtprime_ts SZ=4 LFORCE=2000 BATCH=300 PRIME=6 NOSCHED=0 \
    $PY build_val_sched_ts_prime_exp.py > $D/build.log 2>&1
  local PRJ=$(grep -E "^PRJ=" $D/build.log | tail -1 | cut -d= -f2)
  local INI=$(grep -E "^INI=" $D/build.log | tail -1 | cut -d= -f2)
  grep -E "EXP: FPLAT" $D/build.log | tail -1 | sed 's/^/    /' | tee -a $SUM
  if [ -z "$PRJ" ] || [ ! -f "$PRJ/kernel.cpp" ]; then echo "    BUILD FAIL"; tail -12 $D/build.log | sed 's/^/      /' | tee -a $SUM; echo "---- EXP $1 END(build-fail) ----" | tee -a $SUM; return 1; fi
  local WD=/work/shared/users/zsm9/ii1exp_${1}_wd; rm -rf $WD; mkdir -p $WD
  echo "    csynth $(date)" | tee -a $SUM
  v++ -c --mode hls --config $INI --work_dir $WD > $D/csynth.log 2>&1
  if [ ! -d $WD/hls/syn ]; then echo "    CSYNTH FAIL"; tail -12 $D/csynth.log | sed 's/^/      /' | tee -a $SUM; echo "---- EXP $1 END(csynth-fail) ----" | tee -a $SUM; return 1; fi
  # achieved II from the node pipeline report
  local IIline=$(grep -hE "Pipelining result.*l_S_t" $WD/hls/syn/report/*.rpt 2>/dev/null | head -1)
  echo "    achieved-II: $IIline" | tee -a $SUM
  echo "    cosim $(date)" | tee -a $SUM
  { /usr/bin/time -v vitis-run --mode hls --cosim --config $INI --work_dir $WD ; } 2>&1 \
    | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" > $D/cosim.log
  grep -E "cyc/MMM|bit-exact|co-simulation finished|PASS|FAIL" $D/cosim.log | tail -8 | sed 's/^/    /' | tee -a $SUM
  echo "---- EXP $1 END $(date) ----" | tee -a $SUM
}

run lat1nodep 1 0 fabric  "fp lat=1 fabric, NO dep-false (honest II=1 test)"
run depfalse  2 1 maxdsp  "fp lat=2, dep-false (II=1 hazard test on mmm)"
echo "==== II=1 EXPERIMENTS DONE $(date) ====" | tee -a $SUM
echo "II1_EXP_DONE" | tee -a $SUM
