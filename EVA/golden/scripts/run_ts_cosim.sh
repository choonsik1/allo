#!/bin/bash
# Auto-cosim the TIMESTAMPED ts 8x8 chip once its csynth finishes. fft FIRST (late-vs-never:
# do rows 2,3,6,7 appear anywhere in the L=2000 window? + arrival cycles), then mmm/cordic
# regression (+ throughput cycles). Cosim-only on the kept ts RTL. Detached-friendly.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
TS=/work/shared/users/zsm9/eva_ts_8x8_rtl
WD=$TS/wd; KERN=$TS/kernel_ts_sched.cpp
DEST=$TS/ts_cosim; mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt; : > $SUM
cd $SC; source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
echo "waiting for ts csynth to finish... $(date)" | tee -a $SUM
while ! grep -q BUILD_TS_8X8_DONE $TS/build.out 2>/dev/null; do sleep 120; done
echo "csynth done, starting ts cosims $(date)" | tee -a $SUM
mkports(){ # $1=WL
  cat > $SC/ci_ts_$1.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$KERN
syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS
tb.file=$SC/tb_replay_golden_prime_ts.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_ts_$1_8x8.h"
syn.compile.pipeline_loops=0
INI
}
for WL in fft mmm cordic_cr cordic_cv cordic_hr cordic_hv; do
  mkports $WL
  echo "==== [$WL] ts cosim (L=2000) $(date) ====" | tee -a $SUM
  vitis-run --mode hls --cosim --config $SC/ci_ts_$WL.ini --work_dir $WD > $DEST/cosim_$WL.log 2>&1
  L=$DEST/cosim_$WL.log
  V=$(awk '/Starting C post checking/{f=1} f&&/ts cosim/{print;exit}' $L)
  DL=$(grep -q "Deadlock detected\|200-742" $L && echo " [DEADLOCK]" || echo "")
  echo "  $WL -> ${V:-NORESULT}${DL}" | tee -a $SUM
  # per-row arrival cycles (the late-vs-never evidence)
  awk '/Starting C post checking/{f=1} f&&/row [0-9]:/{print "     "$0}' $L | tee -a $SUM
done
echo "== TS COSIM DONE $(date) ==" | tee -a $SUM
echo "TS_COSIM_DONE"
