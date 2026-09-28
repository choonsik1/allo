#!/bin/bash
# gen (scheduled+ts, B=4) -> csynth -> cosim, for one forwarding _cosim chip.
# Arg1 = CHIP. Prints cyc/MMM from out_cyc gaps (the accurate II=1 array throughput).
set -e
CHIP=$1
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
WD=/tmp/tssched_$CHIP
cd $SC
echo "=== [1/3] gen scheduled+ts kernel (SLOW codegen for 4x4) ==="
PYTHONPATH=/home/zsm9/allo LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel \
  CHIP=$CHIP SZ=4 LFORCE=374 BATCH=4 \
  /home/zsm9/miniconda3/envs/allo/bin/python build_val_sched_ts.py
PRJ=$SC/prj_ts_${CHIP}_4x4_L374_b4_sched
INI=$SC/ci_ts_${CHIP}_4x4_b4_sched.ini
echo "=== [2/3] v++ csynth ==="
rm -rf $WD; mkdir -p $WD; cd $PRJ
v++ -c --mode hls --config $INI --work_dir $WD
echo "CSYNTH_EXIT=$?"
echo "=== node II (should be 1) ==="
find $WD -name "node_0_0_Pipeline*_csynth.rpt" -exec grep -H "l_S_t_0_t" {} \; 2>/dev/null | head -2
echo "=== [3/3] cosim (captures out_cyc) ==="
vitis-run --mode hls --cosim --config $INI --work_dir $WD
echo "COSIM_DONE_EXIT=$?"
echo "=== cyc/MMM RESULT ($CHIP) ==="
grep -iE "cyc/MMM|out_s\[.*@ cyc|PASS|FAIL|mismatch|>> col" $WD/*/sim/report/*.log 2>/dev/null | tail -40 || true
echo "=== DONE $CHIP ==="
