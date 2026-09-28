#!/bin/bash
# CORRECTED timestamped golden campaign (right primes): east-drain workloads
# (fft, cordic) need PRIME=1; mmm (south-drain) uses PRIME=6. Timestamped _cosim
# chip -> each run yields BOTH bit-exact correctness (X/8 rows) AND cyc/val throughput.
# cordic_cr FIRST to verify the prime=1 hypothesis before the rest spend time.
# Serial + ENOSPC-safe (/tmp is 15G). No wait (prior correctness driver already dead).
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
LOGD=$SC/cosim_ts2_logs; RPTD=$LOGD/reports; mkdir -p $RPTD
FF=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final
GT=$FF/golden_testbenches
PY=/home/zsm9/miniconda3/envs/allo/bin/python
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh

run_ts() {  # $1=WL  $2=PRIME
  local WL=$1 PRIME=$2 LOG=$LOGD/$1.log WD=/tmp/wdts2_$1
  { echo "==== TS2 $WL (prime=$PRIME) START $(date) ===="; df -h /tmp | tail -1
    if [ ! -f $SC/prj_gcts_${WL}_8x8_L800/kernel.cpp ]; then
      echo "-- codegen (prime=$PRIME) --"
      ( cd $SC && PYTHONPATH=/home/zsm9/allo_sup TAG=gcts CHIP=eva_sb_syscredit_fwd_cosim TB=tb_replay_golden_ts.cpp \
        WL=$WL LFORCE=800 PRIME=$PRIME $PY $SC/build_golden_cosim.py )
    else echo "-- kernel exists, skip codegen --"; fi
    INI=$SC/ci_gcts_${WL}_8x8.ini
    rm -rf $WD; mkdir -p $WD; cd $SC/prj_gcts_${WL}_8x8_L800
    echo "-- csynth $(date) --"; v++ -c --mode hls --config $INI --work_dir $WD || echo "$WL CSYNTH-FAIL"
    echo "-- cosim $(date) --";  vitis-run --mode hls --cosim --config $INI --work_dir $WD || echo "$WL COSIM-FAIL"
    echo "-- RESULT $(date) --"
    grep -iE "row [0-9]:|cyc/val|per-row avg|golden-ts cosim|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -20
    cp $WD/hls/sim/report/top_cosim.rpt $RPTD/${WL}_cosim.rpt 2>/dev/null
    # --- save report + concise verdict into final_final/golden_testbenches/<wl>/ ---
    GTW=$GT/$WL; mkdir -p $GTW
    cp $WD/hls/sim/report/top_cosim.rpt $GTW/top_cosim.rpt 2>/dev/null
    { echo "# $WL — eva_sb_syscredit_fwd_cosim (timestamped), PRIME=$PRIME, 8x8 RTL cosim"; echo
      grep -iE "row [0-9]:|golden-ts cosim.*rows|per-row avg|C/RTL co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -14
    } > $GTW/verdict.txt
    echo "-- cleanup --"; rm -rf $WD
    echo "==== TS2 $WL DONE $(date) ===="
  } > $LOG 2>&1
}

echo "TS2 START $(date)" | tee $LOGD/SUMMARY.txt
run_ts cordic_cr 1        # verify hypothesis FIRST
run_ts fft 1
run_ts cordic_cv 1
run_ts cordic_hr 1
run_ts cordic_hv 1
run_ts mmm 6
echo "TS2 DONE $(date)" | tee -a $LOGD/SUMMARY.txt
echo "==== verdicts (correctness + throughput) ====" | tee -a $LOGD/SUMMARY.txt
for WL in cordic_cr fft cordic_cv cordic_hr cordic_hv mmm; do
  verd=$(grep -iE "golden-ts cosim" $LOGD/$WL.log 2>/dev/null | grep -iE "PASS|FAIL" | tail -1)
  thru=$(grep -iE "per-row avg" $LOGD/$WL.log 2>/dev/null | tail -1)
  echo "  $WL: ${verd:-<no verdict>}  ${thru}" | tee -a $LOGD/SUMMARY.txt
done
