#!/bin/bash
# Real P&R (post-route Fmax) for the II=1 chip (fp lat=1 fabric, NO dep-false) at 1x1.
# emit (SZ=1) -> v++ csynth -> vitis-run --impl (place+route) -> routed WNS -> Fmax.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/final_eva_performance/results/allo_stream/ii1_exp/pnr_1x1; mkdir -p $DEST
SUM=$DEST/00_PNR_1x1_SUMMARY.txt
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
cd $SC
echo "==== II=1 1x1 P&R (fp lat=1 fabric, no dep-false) START $(date) ====" | tee $SUM
# 1) emit the 1x1 II=1 kernel + ini
EXPTAG=_lat1nodep FPLAT=1 DEPFALSE=0 MULIMPL=fabric \
  CHIP=eva_sb_syscredit_rtprime_ts SZ=1 LFORCE=800 BATCH=40 PRIME=6 NOSCHED=0 \
  $PY build_val_sched_ts_prime_exp.py > $DEST/build.log 2>&1
PRJ=$(grep -E "^PRJ=" $DEST/build.log | tail -1 | cut -d= -f2)
INI=$(grep -E "^INI=" $DEST/build.log | tail -1 | cut -d= -f2)
grep -E "EXP: FPLAT" $DEST/build.log | tail -1 | sed 's/^/  /' | tee -a $SUM
if [ -z "$PRJ" ] || [ ! -f "$PRJ/kernel.cpp" ]; then echo "BUILD FAIL"; tail -12 $DEST/build.log | tee -a $SUM; exit 1; fi
WD=/work/shared/users/zsm9/pnr_ii1_1x1_wd; rm -rf $WD; mkdir -p $WD
# 2) csynth
echo "  csynth $(date)" | tee -a $SUM
v++ -c --mode hls --config $INI --work_dir $WD > $DEST/csynth.log 2>&1
[ -d $WD/hls/syn ] || { echo "CSYNTH FAIL"; tail -12 $DEST/csynth.log | tee -a $SUM; exit 1; }
grep -hE "Pipelining result.*l_S_t_1_t'" $WD/../*.log 2>/dev/null | head -1 | sed 's/^/  node-II: /' | tee -a $SUM
# 3) P&R
echo "  impl (place+route) $(date)" | tee -a $SUM
vitis-run --mode hls --impl --config $INI --work_dir $WD > $DEST/impl.log 2>&1
echo "  impl rc=$? $(date)" | tee -a $SUM
# 4) extract routed WNS -> real period/Fmax
echo "==== ROUTED TIMING ====" | tee -a $SUM
TR=$(find $WD -path "*impl*" -name "*timing_summary*routed*.rpt" 2>/dev/null | head -1)
echo "  report: $TR" | tee -a $SUM
grep -iE "Worst Slack|Design Timing Summary|WNS" "$TR" 2>/dev/null | grep -iE "Worst Slack|-?[0-9]\.[0-9]+ns" | head -4 | sed 's/^/  /' | tee -a $SUM
python3 - "$TR" <<'PY' 2>/dev/null | tee -a $SUM
import re,sys
try:
    s=open(sys.argv[1]).read()
    m=re.search(r"Worst Slack\s+(-?\d+\.\d+)ns", s)
    if m:
        wns=float(m.group(1)); period=3.33-wns; print(f"  WNS={wns:+.3f} ns  ->  period={period:.3f} ns  ->  Fmax={1000/period:.1f} MHz  (target 3.33 ns)")
except Exception as e: print("  (extract failed:",e,")")
PY
echo "==== PNR_1x1_DONE $(date) ====" | tee -a $SUM
