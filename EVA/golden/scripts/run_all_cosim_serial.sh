#!/bin/bash
# SERIAL cosim driver (ENOSPC-safe): /tmp is only 15G, so run ONE 8x8 csynth+cosim
# at a time, save its report to a persistent dir, then delete the work dir before the
# next. All kernels are already codegen'd (prj_*/kernel.cpp on /home). Order: fft@prime1
# first (the runtime-prime payoff), then the 5 golden pe_array workloads.
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
LOGD=$SC/cosim_serial_logs; RPTD=$LOGD/reports; mkdir -p $RPTD
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh

run_one() {  # $1=tag  $2=prj_dir  $3=ini  $4=verdict_grep
  local TAG=$1 PRJ=$2 INI=$3 VG=$4 WD=/tmp/wd_$1 LOG=$LOGD/$1.log
  { echo "==== $TAG START $(date) ===="
    df -h /tmp | tail -1
    rm -rf $WD; mkdir -p $WD; cd $PRJ
    echo "-- csynth $(date) --"; v++ -c --mode hls --config $INI --work_dir $WD || { echo "$TAG CSYNTH-FAIL"; }
    echo "-- cosim $(date) --";  vitis-run --mode hls --cosim --config $INI --work_dir $WD || { echo "$TAG COSIM-FAIL"; }
    echo "-- RESULT $(date) --"
    grep -iE "$VG|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -14
    cp $WD/hls/sim/report/top_cosim.rpt $RPTD/${TAG}_cosim.rpt 2>/dev/null
    echo "-- cleanup work dir --"; rm -rf $WD
    echo "==== $TAG DONE $(date) ===="
  } > $LOG 2>&1
}

echo "SERIAL COSIM START $(date)" | tee $LOGD/SUMMARY.txt
run_one fft_prime1 $SC/prj_fft_eva_sb_syscredit_fwd_8x8_L800 $SC/ci_fft_eva_sb_syscredit_fwd_8x8.ini "FFT 8x8 cosim \("
for WL in cordic_cr cordic_cv cordic_hr cordic_hv mmm; do
  run_one $WL $SC/prj_gc_${WL}_8x8_L800 $SC/ci_gc_${WL}_8x8.ini "golden cosim \("
done
echo "SERIAL COSIM DONE $(date)" | tee -a $LOGD/SUMMARY.txt
echo "==== verdicts ====" | tee -a $LOGD/SUMMARY.txt
for TAG in fft_prime1 cordic_cr cordic_cv cordic_hr cordic_hv mmm; do
  v=$(grep -iE "FFT 8x8 cosim \(|golden cosim \(" $LOGD/${TAG}.log 2>/dev/null | tail -1)
  echo "  $TAG: ${v:-<no verdict / build-fail>}" | tee -a $LOGD/SUMMARY.txt
done
