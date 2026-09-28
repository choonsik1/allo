#!/bin/bash
# SCHEDULED II=1 8x8 (honest, dep-false + FWD=0) via pragma-injection: NOSCHED 8x8 codegen
# from the wbfwd (FWD=0) chip -> inject pipeline+partition+bind_op (ii2) -> ADD dep-false
# (add_depfalse_ii1) -> II=1. csynth ONCE, cosim all 6 golden workloads vs golden.
# RTL work_dir on the SHARED 50GB folder (/work/shared), not /tmp.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/sched8x8_ii1
WD=/work/shared/users/zsm9/eva_sched8x8_rtl/sii1_wd            # SHARED 50GB folder
cd $SC; mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt; : > $SUM
PY=/home/zsm9/miniconda3/envs/allo/bin/python
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
declare -A PRIME=( [mmm]=6 [fft]=1 [cordic_cr]=1 [cordic_cv]=1 [cordic_hr]=1 [cordic_hv]=1 )
CHIP=eva_sb_syscredit_rtprime_wbfwd; TB=tb_replay_golden_prime.cpp   # FWD=0 -> dep-false is SAFE

echo "==== SCHED II=1 8x8 START $(date)  (CHIP=$CHIP, WD=$WD) ====" | tee $SUM

# [0] NOSCHED 8x8 kernel (from wbfwd chip) + per-workload vectors/inis (all 6), TAG=sii1
for WL in mmm fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  TAG=sii1 CHIP=$CHIP TB=$TB WL=$WL LFORCE=800 PRIME=${PRIME[$WL]} $PY build_golden_cosim.py > $DEST/gen_$WL.log 2>&1
done
BASEK=$SC/prj_sii1_mmm_8x8_L800/kernel.cpp
[ -f $BASEK ] || { echo "!! NOSCHED codegen failed (see gen_mmm.log)" | tee -a $SUM; exit 1; }
echo "  NOSCHED 8x8 kernel: $(wc -l <$BASEK) lines" | tee -a $SUM

# [1a] inject pipeline+partition+bind_op (ii2), then [1b] ADD dep-false -> II=1
INJ2=$SC/prj_sii1_shared/kernel_ii2.cpp; INJK=$SC/prj_sii1_shared/kernel.cpp; mkdir -p $SC/prj_sii1_shared
$PY $PRIMEDIR/inject_pragmas_ii2.py $BASEK $INJ2 2 | tee -a $SUM
$PY $PRIMEDIR/add_depfalse_ii1.py $INJ2 $INJK 2>&1 | tee -a $SUM
DF=$(grep -c dependent=false $INJK)
echo "  injected: partition=$(grep -c array_partition $INJK) pipeline=$(grep -c 'pipeline II=1' $INJK) depfalse=$DF (want depfalse>0 -> II=1)" | tee -a $SUM
[ "$DF" -gt 0 ] || { echo "!! dep-false injection FAILED (depfalse=0) -> would be II=2, ABORTING" | tee -a $SUM; exit 2; }
cp $INJK $DEST/kernel_sched_ii1_8x8.cpp

for WL in mmm fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  sed -i "s#^syn.file=.*#syn.file=$INJK#" $SC/ci_sii1_${WL}_8x8.ini
done

# [2] csynth ONCE -> shared RTL ; confirm node II=1 (dep-false -> NO 200-880)
rm -rf $WD; mkdir -p $WD
echo "==== [2] csynth (shared 50GB) $(date) ====" | tee -a $SUM
v++ -c --mode hls --config $SC/ci_sii1_mmm_8x8.ini --work_dir $WD > $DEST/csynth.log 2>&1
echo "  node II: $(grep -hE 'l_S_t_1_t \|' $WD/hls/syn/report/*_csynth.rpt 2>/dev/null | head -1 | tr -s ' ')" | tee -a $SUM
echo "  200-880 (expect 0 = dep-false honored -> II=1): $(grep -c 200-880 $DEST/csynth.log)" | tee -a $SUM
cp -r $WD/hls/syn/report $DEST/csynth_report 2>/dev/null

# [3] cosim each workload vs golden; RTL verdict is AFTER 'Starting C post checking'
for WL in mmm fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  echo "==== [3] cosim $WL prime=${PRIME[$WL]} $(date) ====" | tee -a $SUM
  vitis-run --mode hls --cosim --config $SC/ci_sii1_${WL}_8x8.ini --work_dir $WD > $DEST/cosim_$WL.log 2>&1
  echo "---- $WL RTL verdict (after 'Starting C post checking') ----" | tee -a $SUM
  grep -nE "Starting C post checking|rows bit-exact|PASS|FAIL|row [0-9]:|latency|Total.*cycles" $DEST/cosim_$WL.log 2>/dev/null | tail -10 | tee -a $SUM
  rm -rf $WD/hls/sim/verilog/*.wdb $WD/hls/sim/verilog/work 2>/dev/null
done
echo "==== SCHED II=1 8x8 DONE $(date) ====" | tee -a $SUM
echo "SCHED8X8_II1_COMPLETE"
