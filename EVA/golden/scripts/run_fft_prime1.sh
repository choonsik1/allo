#!/bin/bash
set -e
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
echo "=== [1/3] gen 8x8 FFT kernel PRIME=1 L=800 (re-codegen ~70min) === $(date)"
PYTHONPATH=/home/zsm9/allo LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel \
  CHIP=eva_sb_syscredit_fwd LFORCE=800 PRIME=1 \
  /home/zsm9/miniconda3/envs/allo/bin/python build_fft.py
INI=$SC/ci_fft_eva_sb_syscredit_fwd_8x8.ini
WD=/tmp/fft_cosim_P1
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
rm -rf $WD; mkdir -p $WD; cd $SC/prj_fft_eva_sb_syscredit_fwd_8x8_L800
echo "=== [2/3] csynth === $(date)"
v++ -c --mode hls --config $INI --work_dir $WD
echo "=== [3/3] cosim === $(date)"
vitis-run --mode hls --cosim --config $INI --work_dir $WD
echo "=== FFT PRIME=1 RESULT === $(date)"
grep -iE "row [0-9]:|FFT 8x8 cosim|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -14 || true
echo "=== DONE === $(date)"
