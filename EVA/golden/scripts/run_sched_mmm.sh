#!/bin/bash
# Detached driver: generate the SCHEDULED forwarding+credits 4x4 kernel, csynth,
# then RTL cosim it against the mmm X@W vectors. Log to /tmp/scfwd_sched_mmm.log.
set -e
HERE=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
CHIP=eva_sb_syscredit_fwd
PRJ=$HERE/prj_val_${CHIP}_4x4_L374_sched
INI=$HERE/ci_val_${CHIP}_4x4_sched.ini
WD=/tmp/valsched_${CHIP}

echo "=== [1/3] generate scheduled kernel (allo env) ==="
cd $HERE
CHIP=$CHIP SZ=4 LFORCE=374 /home/zsm9/miniconda3/envs/allo/bin/python build_val_sched.py

echo "=== [2/3] v++ csynth (Vitis 2025.1) ==="
rm -rf $WD
cd $PRJ
v++ -c --mode hls --config $INI --work_dir $WD
echo "CSYNTH_EXIT=$?"

echo "=== [3/3] RTL cosim ==="
vitis-run --mode hls --cosim --config $INI --work_dir $WD
echo "COSIM_DONE_EXIT=$?"
echo "=== II from csynth ==="
grep -i -m4 "Interval\|II\|Latency" $WD/hls/syn/report/*_csynth.rpt 2>/dev/null | head -20 || true
echo "=== ALL DONE ==="
