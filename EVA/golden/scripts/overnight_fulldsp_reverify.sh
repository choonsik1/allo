#!/bin/bash
# FULLDSP 8x8 re-verify: csynth the winning variant (mul=fulldsp, add/sub=fabric) ONCE
# (~13h) then run the FULL streaming cosim suite (mmm/fft/cordic x4, B=300) reusing it.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
NFS=/work/shared/users/zsm9/eva_fulldsp8x8_rtl
WD=$NFS/wd; KERN=$NFS/kernel_fulldsp.cpp
DEST=/home/zsm9/final_eva_performance/results/fulldsp_cosim; mkdir -p $DEST
SUM=$DEST/00_SUMMARY.txt
export TMPDIR=$NFS/tmp
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
cd $SC; : > $SUM
echo "==== FULLDSP 8x8 RE-VERIFY START $(date) ====" | tee $SUM

echo "---- [1] csynth fulldsp 8x8 (64 nodes, ~13h) $(date) ----" | tee -a $SUM
rm -rf $WD; mkdir -p $WD
v++ -c --mode hls --config $SC/ci_fulldsp8x8_csynth.ini --work_dir $WD > $NFS/csynth.log 2>&1
NV=$(find $WD -name '*.v' 2>/dev/null | wc -l); GS=$(find $WD -name global.setting.tcl 2>/dev/null | head -1)
if [ "$NV" -lt 1 ] || [ -z "$GS" ]; then echo "  CSYNTH FAIL (v=$NV db=${GS:-MISS})" | tee -a $SUM; tail -12 $NFS/csynth.log | tee -a $SUM; exit 2; fi
echo "  csynth OK: $NV .v files; 200-880(II=2 honored)=$(grep -c 200-880 $NFS/csynth.log)" | tee -a $SUM
echo "  node II: $(grep -hE 'l_S_t_1_t' $WD/hls/syn/report/*_csynth.rpt 2>/dev/null | head -1 | tr -s ' ')" | tee -a $SUM

echo "---- [2] streaming cosim suite (B=300, reuse fulldsp RTL) $(date) ----" | tee -a $SUM
for entry in mmm:6 fft:3 cordic_cr:3 cordic_cv:3 cordic_hr:3 cordic_hv:3; do
  WL=${entry%%:*}; PR=${entry##*:}
  echo "  ---- $WL (prime=$PR) $(date +%H:%M:%S) ----" | tee -a $SUM
  PRJ=$SC/prj_fulldsp_${WL}_8x8_L2000; mkdir -p $PRJ; cp $KERN $PRJ/kernel.cpp
  CHIP=eva_sb_syscredit_rtprime_ts WL=$WL B=300 LFORCE=2000 TAG=fulldsp MESH=8 PRIME=$PR \
    TB=tb_replay_golden_prime_ts_full.cpp $PY build_golden_cosim.py > $DEST/${WL}_vecgen.log 2>&1
  cat > $SC/ci_fulldsp_${WL}.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$KERN
syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS
tb.file=$SC/tb_replay_golden_prime_ts_full.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_fulldsp_${WL}_8x8.h"
syn.compile.pipeline_loops=0
INI
  { vitis-run --mode hls --cosim --config $SC/ci_fulldsp_${WL}.ini --work_dir $WD ; } 2>&1 \
    | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" > $DEST/${WL}.log
  if grep -q "200-742\|Deadlock" $DEST/${WL}.log; then echo "    $WL -> DEADLOCK" | tee -a $SUM
  else grep -E "rows bit-exact|FULL-STREAM: [0-9].*ALL-OK|ALL-OK|PASS|FAIL" $DEST/${WL}.log 2>/dev/null | tail -6 | sed 's/^/      /' | tee -a $SUM; fi
done
echo "==== FULLDSP RE-VERIFY DONE $(date) ====" | tee -a $SUM
echo "FULLDSP_REVERIFY_COMPLETE" | tee -a $SUM
