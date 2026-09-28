#!/bin/bash
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
LOGD=$SC/cosim_ts2_logs; RPTD=$LOGD/reports; mkdir -p $RPTD
FF=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final
GT=$FF/golden_testbenches
PY=/home/zsm9/miniconda3/envs/allo/bin/python
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
run_ts() {  # WL PRIME
  local WL=$1 PRIME=$2 LOG=$LOGD/$1.log WD=/tmp/wdts2_$1
  { echo "==== TS2-REST $WL (prime=$PRIME) START $(date) ===="; df -h /tmp | tail -1
    if [ ! -f $SC/prj_gcts_${WL}_8x8_L800/kernel.cpp ]; then
      ( cd $SC && PYTHONPATH=/home/zsm9/allo_sup TAG=gcts CHIP=eva_sb_syscredit_fwd_cosim TB=tb_replay_golden_ts.cpp \
        WL=$WL LFORCE=800 PRIME=$PRIME $PY $SC/build_golden_cosim.py )
    fi
    INI=$SC/ci_gcts_${WL}_8x8.ini
    rm -rf $WD; mkdir -p $WD; cd $SC/prj_gcts_${WL}_8x8_L800
    echo "-- csynth $(date) --"; v++ -c --mode hls --config $INI --work_dir $WD || echo "$WL CSYNTH-FAIL"
    echo "-- cosim $(date) --";  vitis-run --mode hls --cosim --config $INI --work_dir $WD || echo "$WL COSIM-FAIL"
    grep -iE "row [0-9]:|per-row avg|golden-ts cosim.*rows|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -16
    GTW=$GT/$WL; mkdir -p $GTW
    cp $WD/hls/sim/report/top_cosim.rpt $GTW/top_cosim.rpt 2>/dev/null
    { echo "# $WL — eva_sb_syscredit_fwd_cosim (timestamped), PRIME=$PRIME, 8x8 RTL cosim"; echo
      grep -iE "row [0-9]:|golden-ts cosim.*rows|per-row avg|C/RTL co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -14
    } > $GTW/verdict.txt
    rm -rf $WD
    echo "==== TS2-REST $WL DONE $(date) ===="
  } > $LOG 2>&1
}
echo "TS2-REST START $(date)" | tee $LOGD/REST_SUMMARY.txt
run_ts cordic_cv 1; run_ts cordic_hr 1; run_ts cordic_hv 1; run_ts mmm 6
echo "TS2-REST DONE $(date)" | tee -a $LOGD/REST_SUMMARY.txt
for W in cordic_cv cordic_hr cordic_hv mmm; do
  echo "  $W: $(grep -iE 'golden-ts cosim.*rows' $LOGD/$W.log|tail -1|grep -oE '(PASS|FAIL).*rows bit-exact')  $(grep -iE 'per-row avg' $LOGD/$W.log|tail -1|sed 's/.*==> //')" | tee -a $LOGD/REST_SUMMARY.txt
done
