#!/bin/bash
# PRIME-SLACK test: same lean 8x8 RTL, mmm B=1, vary prime tokens (6 -> 8, max under STREAM_DEPTH=8).
# If cyc/timestep drops below 9 -> the structural 9 is prime-slack/rewind-limited (fixable w/ deeper streams).
# If flat at 9 -> the 9 is the raw always-fire handshake critical path (needs architectural change).
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
BASE=/work/shared/users/zsm9/eva_leanfulldsp8x8_rtl; WD=$BASE/wd_load; KERN=$BASE/kernel_lean_fulldsp_sched.cpp
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/final_eva_performance/results/prime_test; mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt; : > $SUM
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
# wait for the load experiment to release wd_load
for i in $(seq 1 120); do grep -q LOAD_EXP_DONE /home/zsm9/final_eva_performance/results/load_exp/00_SUMMARY.txt 2>/dev/null && break; sleep 20; done
echo "== PRIME-SLACK test (lean 8x8, mmm B=1, NSTEP=2000) $(date) ==" | tee $SUM
cd $SC
for PR in 6 8; do
  echo "---- prime=$PR $(date) ----" | tee -a $SUM
  CHIP=eva_sb_syscredit_rtprime_ts WL=mmm B=1 LFORCE=2000 TAG=prime MESH=8 PRIME=$PR SCHED=0 \
    TB=tb_replay_golden_prime_ts_full.cpp $PY build_golden_cosim.py > $DEST/vecgen_p$PR.log 2>&1
  cat > $SC/ci_prime_p$PR.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$KERN
syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS
tb.file=$SC/tb_replay_golden_prime_ts_full.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_prime_mmm_8x8.h"
syn.compile.pipeline_loops=0
INI
  vitis-run --mode hls --cosim --config $SC/ci_prime_p$PR.ini --work_dir $WD > $DEST/cosim_p$PR.log 2>&1
  R=$WD/hls/sim/report/top_cosim.rpt
  LAT=$(grep -E "Verilog" "$R" 2>/dev/null | grep -oE "[0-9]{3,}" | head -1)
  PASS=$(grep -cE "co-simulation finished: PASS" $DEST/cosim_p$PR.log); DL=$(grep -cE "200-742|Deadlock" $DEST/cosim_p$PR.log)
  python3 -c "lat=${LAT:-0}; print(f'  prime=$PR: latency={lat} -> {lat/2000:.2f} cyc/timestep  (PASS=$PASS deadlock=$DL)')" | tee -a $SUM
done
echo "PRIME_TEST_DONE $(date)" | tee -a $SUM
