#!/bin/bash
# TIMESTAMPED golden cosim pass. WAITS for the correctness serial campaign to finish,
# then re-runs each shipped pe_array workload on the _cosim (out_cyc) chip, serial +
# ENOSPC-safe, to get per-workload production-cycle / throughput numbers (cyc/val)
# alongside the bit-exact PASS/FAIL. fft@prime=1, cordic/mmm@prime=6.
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
CORR=$SC/cosim_serial_logs/SUMMARY.txt
LOGD=$SC/cosim_ts_logs; RPTD=$LOGD/reports; mkdir -p $RPTD
PY=/home/zsm9/miniconda3/envs/allo/bin/python

echo "TS PASS: waiting for correctness campaign to finish... $(date)" | tee $LOGD/SUMMARY.txt
while ! grep -q "SERIAL COSIM DONE" $CORR 2>/dev/null; do
  pgrep -f run_all_cosim_serial >/dev/null 2>&1 || { echo "  correctness driver gone; proceeding $(date)"; break; }
  sleep 60
done
echo "TS PASS START $(date)" | tee -a $LOGD/SUMMARY.txt
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh

run_ts() {  # $1=WL  $2=PRIME
  local WL=$1 PRIME=$2 LOG=$LOGD/$1.log WD=/tmp/wdts_$1
  { echo "==== TS $WL START $(date) ===="; df -h /tmp | tail -1
    if [ ! -f $SC/prj_gcts_${WL}_8x8_L800/kernel.cpp ]; then
      echo "-- codegen --"
      PYTHONPATH=/home/zsm9/allo TAG=gcts CHIP=eva_sb_syscredit_fwd_cosim TB=tb_replay_golden_ts.cpp \
        WL=$WL LFORCE=800 PRIME=$PRIME $PY build_golden_cosim.py
    else echo "-- kernel exists, skip codegen --"; fi
    INI=$SC/ci_gcts_${WL}_8x8.ini
    rm -rf $WD; mkdir -p $WD; cd $SC/prj_gcts_${WL}_8x8_L800
    echo "-- csynth $(date) --"; v++ -c --mode hls --config $INI --work_dir $WD || echo "$WL CSYNTH-FAIL"
    echo "-- cosim $(date) --";  vitis-run --mode hls --cosim --config $INI --work_dir $WD || echo "$WL COSIM-FAIL"
    echo "-- RESULT $(date) --"
    grep -iE "row [0-9]:|cyc/val|per-row avg|golden-ts cosim \(|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -20
    cp $WD/hls/sim/report/top_cosim.rpt $RPTD/${WL}_cosim.rpt 2>/dev/null
    echo "-- cleanup --"; rm -rf $WD
    echo "==== TS $WL DONE $(date) ===="
  } > $LOG 2>&1
}

run_ts fft 1
for WL in cordic_cr cordic_cv cordic_hr cordic_hv mmm; do run_ts $WL 6; done

echo "TS COSIM DONE $(date)" | tee -a $LOGD/SUMMARY.txt
echo "==== timestamped verdicts (correctness + throughput) ====" | tee -a $LOGD/SUMMARY.txt
for WL in fft cordic_cr cordic_cv cordic_hr cordic_hv mmm; do
  verd=$(grep -iE "golden-ts cosim \(" $LOGD/$WL.log 2>/dev/null | tail -1)
  thru=$(grep -iE "per-row avg" $LOGD/$WL.log 2>/dev/null | tail -1)
  echo "  $WL: ${verd:-<no verdict>}  ${thru}" | tee -a $LOGD/SUMMARY.txt
done
