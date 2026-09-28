#!/bin/bash
# read_nb NON-BLOCKING EVA, FFT 8x8 cosim. Q: does the elastic (read_nb) chip pass fft
# in RTL where the demand chips DEADLOCK and the credit chip's II=2 fails fft?
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
WD=/work/shared/users/zsm9/nbfft_wd
DEST=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/nbfft_cosim
mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh; cd $SC
echo "==== nb read_nb FFT 8x8 START $(date) ====" | tee $SUM
mkdir -p $WD
if [ -d $WD/hls/syn ]; then
  echo "== csynth SKIPPED — reusing preserved RTL in $WD/hls/syn (no re-synth) ==" | tee -a $SUM
else
  echo "== csynth $(date) ==" | tee -a $SUM
  v++ -c --mode hls --config $SC/ci_nbfft_fft_8x8.ini --work_dir $WD > $DEST/csynth.log 2>&1 && echo "csynth OK" | tee -a $SUM
fi
echo "  read_nb in RTL kernel: $(grep -c read_nb $SC/prj_nbfft_fft_8x8_L800/kernel.cpp)" | tee -a $SUM
echo "== cosim $(date) ==" | tee -a $SUM
vitis-run --mode hls --cosim --config $SC/ci_nbfft_fft_8x8.ini --work_dir $WD > $DEST/cosim.log 2>&1
echo "-- verdict --" | tee -a $SUM
grep -nE "row [0-9]:|Deadlock detected|200-742|rows bit-exact|PASS:|FAIL:|co-simulation finished" $DEST/cosim.log 2>/dev/null | tail -15 | tee -a $SUM
echo "==== DONE rc=$? $(date) ====" | tee -a $SUM
