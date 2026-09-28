#!/bin/bash
# LOAD experiment: same lean 8x8 RTL, same NSTEP(=2000), mmm at B=1 (light) vs B=300 (heavy).
# cyc/timestep = total_cosim_latency / NSTEP. If B=1 << B=300 -> LOAD/backpressure. If equal -> structural(mesh).
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
BASE=/work/shared/users/zsm9/eva_leanfulldsp8x8_rtl
WD=$BASE/wd_load; KERN=$BASE/kernel_lean_fulldsp_sched.cpp
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/final_eva_performance/results/load_exp; mkdir -p $DEST
SUM=$DEST/00_SUMMARY.txt; : > $SUM
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
echo "== wait rsync ==" ; for i in $(seq 1 120); do grep -q RSYNC_LOAD_DONE $BASE/rsync_load.log 2>/dev/null && break; sleep 10; done
grep -q RSYNC_LOAD_DONE $BASE/rsync_load.log || { echo "RSYNC FAIL"|tee $SUM; exit 1; }
echo "== LOAD EXPERIMENT (lean 8x8, mmm, NSTEP=2000) START $(date) ==" | tee $SUM
cd $SC
for B in 1 300; do
  echo "---- mmm B=$B $(date) ----" | tee -a $SUM
  # generate mmm vectors at this B (NSTEP=LFORCE=2000)
  CHIP=eva_sb_syscredit_rtprime_ts WL=mmm B=$B LFORCE=2000 TAG=load MESH=8 PRIME=6 SCHED=0 \
    TB=tb_replay_golden_prime_ts_full.cpp $PY build_golden_cosim.py > $DEST/vecgen_B$B.log 2>&1
  cat > $SC/ci_load_B$B.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$KERN
syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS
tb.file=$SC/tb_replay_golden_prime_ts_full.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_load_mmm_8x8.h"
syn.compile.pipeline_loops=0
INI
  vitis-run --mode hls --cosim --config $SC/ci_load_B$B.ini --work_dir $WD > $DEST/cosim_B$B.log 2>&1
  R=$WD/hls/sim/report/top_cosim.rpt
  LAT=$(grep -E "Verilog" "$R" 2>/dev/null | grep -oE "[0-9]{3,}" | head -1)
  PASS=$(grep -cE "co-simulation finished: PASS" $DEST/cosim_B$B.log)
  python3 -c "lat=${LAT:-0}; print(f'  B=$B: total_latency={lat} cyc, NSTEP=2000 -> {lat/2000:.2f} cyc/timestep  (PASS=$PASS)')" | tee -a $SUM
done
echo "LOAD_EXP_DONE $(date)" | tee -a $SUM
