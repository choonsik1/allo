#!/bin/bash
# VARIANT C: the II=1 8x8 HAZARD build. Reuses the SLOW scheduled codegen from
# run_sched8x8_all.sh (prj_gc_mmm_8x8_L800_sched/kernel.cpp) + injects dependence=false
# (=> II=1) WITHOUT re-generating. FP_LAT=1 is already baked; default binding => L=4-5,
# so the forward guard inflight>=1 is well below L. If any workload's RTL cosim MISMATCHES
# golden, the FP_LAT>=L invariant is empirically vindicated at 8x8 (a real II=1 bug that
# NOSCHED masked). Reuses B's per-WL vectors + inis (same TAG=gc), just swaps in the
# injected kernel and re-points syn.file. csynth ONCE (WL-independent), cosim all 6.
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
LOGD=$SC/sched8x8C_logs; mkdir -p $LOGD
SUM=$LOGD/00_SUMMARY.txt; : > $SUM
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
BASE=$SC/prj_gc_mmm_8x8_L800_sched/kernel.cpp
declare -A PRIME=( [mmm]=6 [fft]=1 [cordic_cr]=1 [cordic_cv]=1 [cordic_hr]=1 [cordic_hv]=1 )

[ -f "$BASE" ] || { echo "!! base scheduled kernel not present yet: $BASE" | tee $SUM; exit 1; }
echo "==== VARIANT C START $(date) ====" | tee $SUM

# inject dependence=false -> II=1 kernel (WL-independent), one shared project
CDIR=$SC/prj_gcC_shared_8x8_L800_sched; mkdir -p $CDIR
python3 $SC/inject_depfalse.py $BASE $CDIR/kernel.cpp | tee -a $SUM
CKP=$CDIR/kernel.cpp

# csynth ONCE -> confirm node II=1 + real L (default binding)
WD=/tmp/sched8x8C_csynth; rm -rf $WD; mkdir -p $WD; cd $CDIR
cat > $SC/ci_gcC_csynth.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$CKP
tb.file=$SC/tb_replay_golden.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_gc_mmm_8x8.h"
INI
echo "-- csynth (variant C) $(date) --" | tee -a $SUM
v++ -c --mode hls --config $SC/ci_gcC_csynth.ini --work_dir $WD > $LOGD/02_csynth.log 2>&1
echo "CSYNTH_EXIT=$? $(date)" | tee -a $SUM
echo "  node II (want achieved=1): $(grep -hE 'l_S_t_0_t' $WD/hls/syn/report/*_csynth.rpt 2>/dev/null | head -1)" | tee -a $SUM
echo "  FPU core latencies (L):    $(grep -ohE 'h(mul|add|sub)_[0-9]+ns_[0-9]+ns_[0-9]+_[0-9]+' $WD/hls/syn/report/*_csynth.rpt 2>/dev/null | sort -u | tr '\n' ' ')" | tee -a $SUM
cp -r $WD/hls/syn/report $LOGD/csynth_report 2>/dev/null

# cosim each workload against the SAME injected RTL (reuse B's per-WL vectors)
for WL in mmm fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  P=${PRIME[$WL]}; VEC=$SC/vectors_gc_${WL}_8x8.h
  echo "==== C $WL prime=$P $(date) ====" | tee -a $SUM
  if [ ! -f "$VEC" ]; then echo "  !! missing $VEC (run B/build first) - skip" | tee -a $SUM; continue; fi
  cat > $SC/ci_gcC_${WL}.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$CKP
tb.file=$SC/tb_replay_golden.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_gc_${WL}_8x8.h"
INI
  WD=/tmp/sched8x8C_$WL; rm -rf $WD; mkdir -p $WD; cd $CDIR
  { echo "-- csynth $(date) --"; v++ -c --mode hls --config $SC/ci_gcC_${WL}.ini --work_dir $WD || echo "$WL CSYNTH-FAIL"
    echo "-- cosim  $(date) --"; vitis-run --mode hls --cosim --config $SC/ci_gcC_${WL}.ini --work_dir $WD || echo "$WL COSIM-FAIL"
  } > $LOGD/11_${WL}_run.log 2>&1
  echo "---- C $WL RESULT ----" | tee -a $SUM
  grep -iE "row [0-9]:|bit-exact|C/RTL co-simulation finished|golden cosim.*PASS|golden cosim.*FAIL" \
     $WD/*/sim/report/*.log 2>/dev/null | tail -12 | tee -a $SUM
  cp $WD/hls/sim/report/top_cosim.rpt $LOGD/${WL}_cosim.rpt 2>/dev/null
  rm -rf $WD
done
echo "==== VARIANT C DONE $(date) ====" | tee -a $SUM
echo "SCHED8X8C_COMPLETE"
