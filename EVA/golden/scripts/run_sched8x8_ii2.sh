#!/bin/bash
# SCHEDULED II=2 8x8 (correct) via pragma-injection: NOSCHED 8x8 codegen -> inject
# pipeline+partition+bind_op (NO dep-false) -> II=2 correct. csynth ONCE (kernel is
# workload-independent for rtprime), cosim all 6 golden workloads vs golden.
# Disk-safe: single shared work_dir, cleaned between cosims (/tmp is only 15G).
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/sched8x8_ii2
cd $SC; mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt; : > $SUM
PY=/home/zsm9/miniconda3/envs/allo/bin/python
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
declare -A PRIME=( [mmm]=6 [fft]=1 [cordic_cr]=1 [cordic_cv]=1 [cordic_hr]=1 [cordic_hv]=1 )
CHIP=eva_sb_syscredit_rtprime; TB=tb_replay_golden_prime.cpp

echo "==== SCHED II=2 8x8 START $(date) ====" | tee $SUM

# [0] generate NOSCHED 8x8 kernel + per-workload vectors/inis (all 6), TAG=sii2
for WL in mmm fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  TAG=sii2 CHIP=$CHIP TB=$TB WL=$WL LFORCE=800 PRIME=${PRIME[$WL]} $PY build_golden_cosim.py > $DEST/gen_$WL.log 2>&1
done
BASEK=$SC/prj_sii2_mmm_8x8_L800/kernel.cpp
[ -f $BASEK ] || { echo "!! NOSCHED codegen failed (see gen_mmm.log)" | tee -a $SUM; exit 1; }
echo "  NOSCHED 8x8 kernel: $(wc -l <$BASEK) lines" | tee -a $SUM

# [1] INJECT pragmas -> scheduled II=2 kernel (shared, one file)
INJK=$SC/prj_sii2_shared/kernel.cpp; mkdir -p $SC/prj_sii2_shared
$PY $PRIMEDIR/inject_pragmas_ii2.py $BASEK $INJK 2 | tee -a $SUM
cp $INJK $DEST/kernel_sched_ii2_8x8.cpp
echo "  injected: partition=$(grep -c array_partition $INJK) pipeline=$(grep -c 'pipeline II=1' $INJK) depfalse=$(grep -c dependent=false $INJK) (want depfalse=0)" | tee -a $SUM

# point every workload ini at the shared injected kernel
for WL in mmm fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  sed -i "s#^syn.file=.*#syn.file=$INJK#" $SC/ci_sii2_${WL}_8x8.ini
done

# [2] csynth ONCE (mmm ini) -> shared RTL ; confirm node II=2 (no dep-false)
WD=/tmp/sii2_wd; rm -rf $WD; mkdir -p $WD
echo "==== [2] csynth (shared) $(date) ====" | tee -a $SUM
v++ -c --mode hls --config $SC/ci_sii2_mmm_8x8.ini --work_dir $WD > $DEST/csynth.log 2>&1
echo "  node II: $(grep -hE 'l_S_t_1_t \|' $WD/hls/syn/report/*_csynth.rpt 2>/dev/null | head -1 | tr -s ' ')" | tee -a $SUM
echo "  200-880 (expect >0 = dep honored -> II=2): $(grep -c 200-880 $DEST/csynth.log)" | tee -a $SUM
cp -r $WD/hls/syn/report $DEST/csynth_report 2>/dev/null

# [3] cosim each workload against the shared RTL (recompiles tb only)
for WL in mmm fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  echo "==== [3] cosim $WL prime=${PRIME[$WL]} $(date) ====" | tee -a $SUM; df -h /tmp | tail -1
  vitis-run --mode hls --cosim --config $SC/ci_sii2_${WL}_8x8.ini --work_dir $WD > $DEST/cosim_$WL.log 2>&1
  echo "---- $WL RTL verdict (after 'Starting C post checking') ----" | tee -a $SUM
  grep -nE "Starting C post checking|rows bit-exact|PASS|FAIL|row [0-9]:" $DEST/cosim_$WL.log 2>/dev/null | tail -8 | tee -a $SUM
  # keep RTL, wipe only the sim scratch to save disk
  rm -rf $WD/hls/sim/verilog/*.wdb $WD/hls/sim/verilog/work 2>/dev/null
done
echo "==== SCHED II=2 8x8 DONE $(date) ====" | tee -a $SUM
echo "SCHED8X8_II2_COMPLETE"
