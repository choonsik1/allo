#!/bin/bash
# B=20 STREAMING on the 8x8 chip for all 6 shipped workloads. Injects 20 back-to-back
# activations, verifies all 20 come out bit-exact (lossless, credit-plane backpressure)
# and measures sustained cyc/activation. Timestamped _cosim chip. Serial, ENOSPC-safe.
# Right primes: east-drain (fft/cordic)=1, south-drain (mmm)=6.
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
LOGD=$SC/stream_logs; mkdir -p $LOGD
FF=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final
OUT=$FF/golden_testbenches/streaming_B20; mkdir -p $OUT
PY=/home/zsm9/miniconda3/envs/allo/bin/python
B=20; L=2000
WLS=(fft cordic_cr cordic_cv cordic_hr cordic_hv mmm)
PRS=(1   1         1         1         1         6)
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh

run_one(){  # $1=WL $2=PRIME
  local WL=$1 PRIME=$2 LOG=$LOGD/$1.log WD=/tmp/strm_$1
  { echo "==== STREAM $WL (B=$B prime=$PRIME L=$L) START $(date) ===="; df -h /tmp|tail -1
    if [ ! -f $SC/prj_strm_${WL}_8x8_L${L}/kernel.cpp ]; then
      echo "-- codegen --"
      ( cd $SC && PYTHONPATH=/home/zsm9/allo_sup TAG=strm CHIP=eva_sb_syscredit_fwd_cosim \
        TB=tb_replay_golden_stream.cpp WL=$WL LFORCE=$L B=$B PRIME=$PRIME $PY $SC/build_golden_cosim.py )
    fi
    INI=$SC/ci_strm_${WL}_8x8.ini
    rm -rf $WD; mkdir -p $WD; cd $SC/prj_strm_${WL}_8x8_L${L}
    echo "-- csynth $(date) --"; v++ -c --mode hls --config $INI --work_dir $WD || echo "$WL CSYNTH-FAIL"
    echo "-- cosim $(date) --";  vitis-run --mode hls --cosim --config $INI --work_dir $WD || echo "$WL COSIM-FAIL"
    echo "-- RESULT $(date) --"
    grep -iE "row [0-9]: delivered|rows LOSSLESS|streaming .* rows lossless|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -14
    OW=$OUT/$WL; mkdir -p $OW
    cp $WD/hls/sim/report/top_cosim.rpt $OW/top_cosim.rpt 2>/dev/null
    { echo "# $WL streaming B=$B, prime=$PRIME, 8x8 timestamped RTL cosim"; echo
      grep -iE "row [0-9]: delivered|rows LOSSLESS|streaming .*rows lossless|C/RTL co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -14
    } > $OW/verdict.txt
    echo "-- cleanup --"; rm -rf $WD
    echo "==== STREAM $WL DONE $(date) ===="
  } > $LOG 2>&1
}
echo "STREAM B=$B START $(date)" | tee $LOGD/SUMMARY.txt
for i in "${!WLS[@]}"; do run_one "${WLS[$i]}" "${PRS[$i]}"; done
echo "STREAM DONE $(date)" | tee -a $LOGD/SUMMARY.txt
for W in fft cordic_cr cordic_cv cordic_hr cordic_hv mmm; do
  echo "  $W: $(grep -iE 'streaming .*rows lossless' $LOGD/$W.log 2>/dev/null | tail -1 | grep -oE '(PASS|FAIL).*rows lossless')" | tee -a $LOGD/SUMMARY.txt
done
