#!/bin/bash
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
INI=$SC/ci_nbfix_mmm_8x8.ini; WD=/tmp/nbfix_mmm
rm -rf $WD; mkdir -p $WD; cd $SC/prj_nbfix_mmm_8x8_L300
echo "=== csynth $(date) ==="
v++ -c --mode hls --config $INI --work_dir $WD 2>&1 | tail -2
echo "=== cosim (30-min timeout guard) $(date) ==="
timeout 1800 vitis-run --mode hls --cosim --config $INI --work_dir $WD
rc=$?
echo "=== cosim exit=$rc $(date) ==="
if [ $rc -eq 124 ]; then echo ">>> STILL HANGING (timed out at 30min) — fix incomplete"; 
else
  echo ">>> TERMINATED. verdict:"
  grep -iE "row [0-9]:|golden cosim.*rows|co-simulation finished|leftover data" $WD/*/sim/report/*.log 2>/dev/null | tail -12
fi
rm -rf $WD
echo "=== DONE $(date) ==="
