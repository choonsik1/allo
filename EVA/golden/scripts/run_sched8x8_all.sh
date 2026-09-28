#!/bin/bash
# FULL-SCHEDULE (real II=1) 8x8 campaign.
#   [1] generate the SCHEDULED 8x8 kernel ONCE (pipeline_node=True) — the SLOW codegen
#       (memory: intractable >3.5h; this run is the honest attempt to complete it).
#   [2] csynth it once -> confirm node_0_0 loop II=1 + real Fmax (what NOSCHED can't give).
#   [3] reuse that ONE kernel (it's workload-independent) to RTL-cosim all 6 golden
#       workloads bit-exact: mmm(prime=6) + fft/cordic_{cr,cv,hr,hv}(prime=1).
# Detached-safe. Logs to sched8x8_logs/.
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
LOGD=$SC/sched8x8_logs; mkdir -p $LOGD
PY=/home/zsm9/miniconda3/envs/allo/bin/python
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo
export LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel

declare -A PRIME=( [mmm]=6 [fft]=1 [cordic_cr]=1 [cordic_cv]=1 [cordic_hr]=1 [cordic_hv]=1 )
GENWL=mmm                                   # kernel is WL-independent; generate via mmm
KP=$SC/prj_gc_${GENWL}_8x8_L800_sched/kernel.cpp

bG() { # $1=WL $2=PRIME  (env must be literal assignments, not via $@)
  SCHED=1 TAG=gc CHIP=eva_sb_syscredit_fwd TB=tb_replay_golden.cpp LFORCE=800 \
    WL=$1 PRIME=$2 $PY build_golden_cosim.py
}

# ===== [1] SCHEDULED codegen (SLOW) =====
echo "==== [1] SCHED codegen START $(date) ====" | tee $LOGD/00_SUMMARY.txt
if [ -f $KP ]; then
  echo "  kernel already present ($(wc -l <$KP) lines) — skip codegen" | tee -a $LOGD/00_SUMMARY.txt
else
  bG $GENWL ${PRIME[$GENWL]} > $LOGD/01_codegen.log 2>&1
  echo "CODEGEN_EXIT=$? $(date)" | tee -a $LOGD/00_SUMMARY.txt
fi
if [ ! -f $KP ]; then
  echo "!! NO KERNEL — scheduled codegen failed/incomplete. See 01_codegen.log" | tee -a $LOGD/00_SUMMARY.txt
  echo "SCHED8X8_ABORT_NO_KERNEL"; exit 1
fi
echo "  kernel: $(wc -l <$KP) lines" | tee -a $LOGD/00_SUMMARY.txt

# ===== [2] csynth ONCE -> node II + Fmax =====
echo "==== [2] csynth START $(date) ====" | tee -a $LOGD/00_SUMMARY.txt
WD=/tmp/sched8x8_csynth; rm -rf $WD; mkdir -p $WD
cd $SC/prj_gc_${GENWL}_8x8_L800_sched
INI=$SC/ci_gc_${GENWL}_8x8_sched.ini
( v++ -c --mode hls --config $INI --work_dir $WD ) > $LOGD/02_csynth.log 2>&1
echo "CSYNTH_EXIT=$? $(date)" | tee -a $LOGD/00_SUMMARY.txt
echo "---- node_0_0 loop II (want achieved=1) ----" | tee -a $LOGD/00_SUMMARY.txt
find $WD -name "*node_0_0_Pipeline*_csynth.rpt" -exec grep -H "l_S_t_0_t" {} \; 2>/dev/null | tee -a $LOGD/00_SUMMARY.txt
echo "---- timing (target/estimated) ----" | tee -a $LOGD/00_SUMMARY.txt
grep -iE "CP achieved|Estimated|Target|clock" $WD/hls/syn/report/csynth.rpt 2>/dev/null | head -6 | tee -a $LOGD/00_SUMMARY.txt
cp -r $WD/hls/syn/report $LOGD/csynth_report 2>/dev/null

# ===== [3] cosim all 6 (reuse the one kernel) =====
for WL in mmm fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  P=${PRIME[$WL]}; WD=/tmp/sched8x8_$WL
  echo "==== [3] $WL prime=$P START $(date) ====" | tee -a $LOGD/00_SUMMARY.txt
  df -h /tmp | tail -1
  mkdir -p $SC/prj_gc_${WL}_8x8_L800_sched
  cp $KP $SC/prj_gc_${WL}_8x8_L800_sched/kernel.cpp      # reuse the scheduled kernel
  bG $WL $P > $LOGD/10_${WL}_build.log 2>&1     # writes vectors + ini (codegen skipped)
  INI=$SC/ci_gc_${WL}_8x8_sched.ini
  rm -rf $WD; mkdir -p $WD; cd $SC/prj_gc_${WL}_8x8_L800_sched
  { echo "-- csynth $(date) --"; v++ -c --mode hls --config $INI --work_dir $WD || echo "$WL CSYNTH-FAIL"
    echo "-- cosim  $(date) --"; vitis-run --mode hls --cosim --config $INI --work_dir $WD || echo "$WL COSIM-FAIL"
  } > $LOGD/11_${WL}_run.log 2>&1
  echo "---- $WL RESULT ----" | tee -a $LOGD/00_SUMMARY.txt
  grep -iE "row [0-9]:|bit-exact|C/RTL co-simulation finished|golden cosim.*PASS|golden cosim.*FAIL" \
     $WD/*/sim/report/*.log 2>/dev/null | tail -12 | tee -a $LOGD/00_SUMMARY.txt
  cp $WD/hls/sim/report/top_cosim.rpt $LOGD/${WL}_cosim.rpt 2>/dev/null
  rm -rf $WD
done
echo "==== ALL DONE $(date) ====" | tee -a $LOGD/00_SUMMARY.txt
echo "SCHED8X8_COMPLETE"
