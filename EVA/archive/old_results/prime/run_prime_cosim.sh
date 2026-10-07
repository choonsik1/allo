#!/bin/bash
set -e
PD=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
cd $PD
INI=$PD/ci_prime_4x4.ini
WD=/tmp/prime_4x4
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
echo "using $(which v++) [$(v++ --version 2>/dev/null | grep -oE 'v2025\.[0-9]+' | head -1)]  $(date)"
rm -rf $WD; mkdir -p $WD; cd $PD/prj_prime_4x4_L374
echo "=== [1/2] csynth (watch for 200-779 multi-reader on prime_cfg) === $(date)"
v++ -c --mode hls --config $INI --work_dir $WD
echo "=== [2/2] cosim === $(date)"
vitis-run --mode hls --cosim --config $INI --work_dir $WD
echo "=== RESULT === $(date)"
grep -iE "RUNTIME-PRIME replay|out_s seen|prime_cfg\[0\]|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -20 || true
echo "=== DONE === $(date)"
