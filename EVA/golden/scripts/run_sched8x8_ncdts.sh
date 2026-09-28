#!/bin/bash
# CREDIT-FREE-BY-SLACK experiment, timestamped, 8x8, scheduled II=2:
#   systolic credit plane (scr_) STRIPPED; router credit (cr_) kept.
#   buffers DEEPENED: link FIFO 8->16, router rbuf 2->4, PE hold_v 2->4.
#   Q: does deep slack replace the systolic credit throttle losslessly?  + out_cyc timestamps.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/sched8x8_nocred_deep_ts
WD=/work/shared/users/zsm9/eva_sched8x8_rtl/ncdts_wd
cd $SC; mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt; : > $SUM
PY=/home/zsm9/miniconda3/envs/allo/bin/python
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel
declare -A PRIME=( [mmm]=6 [fft]=1 [cordic_cr]=1 )
CHIP=eva_sb_syscredit_rtprime_nocred_deep_ts; TB=tb_replay_golden_ts.cpp; WLS="mmm fft cordic_cr"
echo "==== NOCRED+DEEP TS II=2 8x8 START $(date) (CHIP=$CHIP) ====" | tee $SUM
for WL in $WLS; do TAG=sncdts CHIP=$CHIP TB=$TB WL=$WL LFORCE=800 PRIME=${PRIME[$WL]} $PY build_golden_cosim.py > $DEST/gen_$WL.log 2>&1; done
BASEK=$SC/prj_sncdts_mmm_8x8_L800/kernel.cpp
[ -f $BASEK ] || { echo "!! NOSCHED codegen failed (see gen_mmm.log)" | tee -a $SUM; exit 1; }
echo "  NOSCHED 8x8 kernel: $(wc -l <$BASEK) lines  (nocred+deep)" | tee -a $SUM
INJK=$SC/prj_sncdts_shared/kernel.cpp; mkdir -p $SC/prj_sncdts_shared
$PY $PRIMEDIR/inject_pragmas_ii2.py $BASEK $INJK 2 | tee -a $SUM
echo "  injected: depfalse=$(grep -c dependent=false $INJK) (want 0 -> II=2)" | tee -a $SUM
for WL in $WLS; do sed -i "s#^syn.file=.*#syn.file=$INJK#" $SC/ci_sncdts_${WL}_8x8.ini; done
rm -rf $WD; mkdir -p $WD
echo "==== csynth $(date) ====" | tee -a $SUM
v++ -c --mode hls --config $SC/ci_sncdts_mmm_8x8.ini --work_dir $WD > $DEST/csynth.log 2>&1
echo "  200-880 (expect 0 = II=2): $(grep -c 200-880 $DEST/csynth.log)" | tee -a $SUM
for WL in $WLS; do
  echo "==== cosim $WL prime=${PRIME[$WL]} $(date) ====" | tee -a $SUM
  vitis-run --mode hls --cosim --config $SC/ci_sncdts_${WL}_8x8.ini --work_dir $WD > $DEST/cosim_$WL.log 2>&1
  grep -nE "Starting C post checking|rows bit-exact|PASS:|FAIL:" $DEST/cosim_$WL.log 2>/dev/null | tail -3 | tee -a $SUM
  rm -rf $WD/hls/sim/verilog/*.wdb $WD/hls/sim/verilog/work 2>/dev/null
done
echo "==== NOCRED+DEEP DONE $(date) ====" | tee -a $SUM
