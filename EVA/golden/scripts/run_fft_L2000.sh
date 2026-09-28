#!/bin/bash
# Longer-L FFT drain-window test on the syscredit_fwd 8x8 chip.
# L800 gave 2/8 rows (rows 0,1 correct; rows 2-7 emitted NOTHING at EAST).
# This pushes L=2000 to distinguish: drain-window latency vs structural
# (deeper rows never programmed/fed under credit backpressure).
set -e
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
echo "=== [1/3] gen 8x8 FFT kernel at L=2000 (re-codegen, ~70min) === $(date)"
PYTHONPATH=/home/zsm9/allo_sup LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel \
  CHIP=eva_sb_syscredit_fwd LFORCE=2000 \
  /home/zsm9/miniconda3/envs/allo/bin/python build_fft.py
INI=$SC/ci_fft_eva_sb_syscredit_fwd_8x8.ini
WD=/tmp/fft_cosim_L2000
rm -rf $WD; mkdir -p $WD; cd $SC/prj_fft_eva_sb_syscredit_fwd_8x8_L2000
# switch to Vitis 2025.1 for csynth+cosim (default shell has 2023.2)
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
echo "using v++: $(which v++)  [$(v++ --version 2>/dev/null | grep -oE 'v2025\.[0-9]+' | head -1)]"
echo "=== [2/3] csynth === $(date)"
v++ -c --mode hls --config $INI --work_dir $WD
echo "=== [3/3] cosim === $(date)"
vitis-run --mode hls --cosim --config $INI --work_dir $WD
echo "=== FFT L=2000 RESULT === $(date)"
grep -iE "row [0-9]:|FFT 8x8 cosim|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -14 || true
echo "=== DONE === $(date)"
