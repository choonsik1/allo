#!/bin/bash
# HONEST II=1 8x8 TS = the FINAL II=2 chip with ONE change: bind_op latency 2 -> 1
# (Exp A recipe; shorter fp latency shrinks the res->resq recurrence -> honest II=1,
# NO dep-false). SAME source chip (rtprime_ts), SAME ports (out_cyc), SAME vectors,
# SAME TB, SAME inis as II=2 — only the kernel differs (1 token per bind_op) + a fresh
# csynth (RTL genuinely differs, can't reuse the II=2 pre-synth). Goal: do all 6 golden
# workloads PASS bit-exact at II=1, and what's the throughput. RTL -> shared 50GB folder.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
KII2=/work/shared/users/zsm9/eva_ts_8x8_rtl/kernel_ts_sched.cpp     # the II=2 kernel (source)
RTLDIR=/work/shared/users/zsm9/eva_sched8x8_ii1ts_rtl              # SHARED 50GB folder
WD=$RTLDIR/wd ; KII1=$RTLDIR/kernel_ii1_ts.cpp
DEST=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/sched8x8_ii1ts
mkdir -p $DEST $RTLDIR; SUM=$DEST/00_SUMMARY.txt; : > $SUM
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
declare -A PRIME=( [mmm]=6 [fft]=3 [cordic_cr]=3 [cordic_cv]=3 [cordic_hr]=3 [cordic_hv]=3 )
WLS="mmm fft cordic_cr cordic_cv cordic_hr cordic_hv"
echo "==== HONEST II=1 8x8 TS START $(date)  (II=2 kernel, bind_op lat 2->1, WD=$WD) ====" | tee $SUM

# [1] derive the II=1 kernel from the II=2 kernel: bind_op latency 2 -> 1 (nothing else)
[ -f "$KII2" ] || { echo "!! II=2 source kernel missing: $KII2" | tee -a $SUM; exit 1; }
sed '/bind_op/ s/latency=2/latency=1/' "$KII2" > "$KII1"
echo "  II=1 kernel: bind_lat1=$(grep -c 'bind_op.*latency=1' $KII1) bind_lat2=$(grep -c 'bind_op.*latency=2' $KII1) depfalse=$(grep -c dependent=false $KII1) (want lat2=0, depfalse=0)" | tee -a $SUM
cp $KII1 $DEST/kernel_ii1_ts_8x8.cpp

# [2] inis: same as II=2 (reuse vectors_ii2run_*.h + ts TB), only syn.file -> II=1 kernel
for WL in $WLS; do
cat > $SC/ci_ii1run_${WL}.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$KII1
syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS
tb.file=$SC/tb_replay_golden_prime_ts_full.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_ii2run_${WL}_8x8.h"
syn.compile.pipeline_loops=0
INI
  [ -f $SC/vectors_ii2run_${WL}_8x8.h ] || echo "  !! missing reused vectors_ii2run_${WL}_8x8.h" | tee -a $SUM
done

# [3] csynth ONCE -> shared RTL; confirm honest II=1 (Final II=1, no 200-880)
rm -rf $WD; mkdir -p $WD
echo "==== [2] csynth (shared 50GB) $(date) ====" | tee -a $SUM
v++ -c --mode hls --config $SC/ci_ii1run_mmm.ini --work_dir $WD > $DEST/csynth.log 2>&1
if [ ! -d $WD/hls/syn ]; then echo "!! CSYNTH FAILED" | tee -a $SUM; tail -18 $DEST/csynth.log | tee -a $SUM; exit 2; fi
echo "  Final-II histogram: $(grep -hoE 'Final II = [0-9]+' $DEST/csynth.log | sort | uniq -c | tr '\n' ' ')" | tee -a $SUM
echo "  200-880 count (want 0 = honest II=1 met): $(grep -c 200-880 $DEST/csynth.log)" | tee -a $SUM
cp -r $WD/hls/syn/report $DEST/csynth_report 2>/dev/null

# [4] cosim each workload vs golden (per-word bit-exact + out_cyc throughput), reuse RTL
for WL in $WLS; do
  echo "==== [3] cosim $WL prime=${PRIME[$WL]} $(date) ====" | tee -a $SUM
  { /usr/bin/time -v vitis-run --mode hls --cosim --config $SC/ci_ii1run_${WL}.ini --work_dir $WD ; } 2>&1 \
    | grep --line-buffered -vE "read while empty|is read while|WARNING \[HLS SIM\]" > $DEST/cosim_$WL.log
  echo "---- $WL verdict ----" | tee -a $SUM
  grep -E "rows bit-exact|FULL-STREAM: [0-9].*ALL-OK|drained [0-9]+ words, arrival|Elapsed \(wall" $DEST/cosim_$WL.log 2>/dev/null | tail -10 | sed 's/^/    /' | tee -a $SUM
  rm -rf $WD/hls/sim/verilog/*.wdb $WD/hls/sim/verilog/work 2>/dev/null
done
echo "==== HONEST II=1 8x8 TS DONE $(date) ====" | tee -a $SUM
echo "SCHED8X8_II1TS_COMPLETE"
