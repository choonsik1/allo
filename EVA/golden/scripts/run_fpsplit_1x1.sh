#!/bin/bash
# Force the scheduler to NOT chain the two DSP fp ops in one cycle, by bumping clock
# uncertainty (HLS schedules tighter -> inserts a register between the DSP stages ->
# Vivado can use MREG/PREG). Final chip config (II=2, no dep-false). Check: II stays 2,
# chain breaks, post-route Fmax rises toward 300.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/fpsplit_1x1
WD=/work/shared/users/zsm9/fpsplit_1x1_wd
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
cd $SC; SUM=$DEST/00_SUMMARY.txt; : > $SUM
UNC=${1:-0.9}   # clock uncertainty (ns); 0.9 ~= 27% of 3.33
echo "== FP-SPLIT 1x1 (clk_uncertainty=$UNC ns) START $(date) ==" | tee $SUM
# [1] emit final-chip node (II=2, NO dep-false, bind lat 2)
EXPTAG=_fpsplit FPLAT=2 DEPFALSE=0 MULIMPL=maxdsp CHIP=eva_sb_syscredit_rtprime_ts SZ=1 LFORCE=800 BATCH=40 PRIME=6 NOSCHED=0 \
  $PY build_val_sched_ts_prime_exp.py > $DEST/build.log 2>&1
BASEK=$(grep -E "^PRJ=" $DEST/build.log|tail -1|cut -d= -f2)/kernel.cpp
INI=$(grep -E "^INI=" $DEST/build.log|tail -1|cut -d= -f2)
[ -f "$BASEK" ] || { echo "EMIT FAIL"; tail -8 $DEST/build.log|tee -a $SUM; exit 1; }
# [2] ini + clock uncertainty (schedule tight, constrain 3.33)
sed -e "s#^syn.file=.*#syn.file=$BASEK#" $INI > $DEST/ci_fpsplit.ini
grep -q "syn.clock_uncertainty" $DEST/ci_fpsplit.ini || sed -i "/clock=/a syn.clock_uncertainty=$UNC" $DEST/ci_fpsplit.ini
echo "  ini clock lines:" | tee -a $SUM; grep -E "clock" $DEST/ci_fpsplit.ini | sed 's/^/    /' | tee -a $SUM
# [3] csynth
rm -rf $WD; mkdir -p $WD
echo "  csynth $(date)" | tee -a $SUM
v++ -c --mode hls --config $DEST/ci_fpsplit.ini --work_dir $WD > $DEST/csynth.log 2>&1
[ -d $WD/hls/syn ] || { echo "CSYNTH FAIL"; tail -20 $DEST/csynth.log|tee -a $SUM; exit 2; }
echo "  Final-II: $(grep -hoE 'Final II = [0-9]+' $DEST/csynth.log|sort|uniq -c|tr '\n' ' ')  200-880=$(grep -c 200-880 $DEST/csynth.log)  200-887(cant-meet-clk)=$(grep -c 200-887 $DEST/csynth.log)" | tee -a $SUM
echo "  fp ops per state (want mul & add SPLIT): 2-DSP-chain warnings=$(grep -ciE '200-887.*hmul|200-887.*hadd' $DEST/csynth.log)" | tee -a $SUM
# [4] impl -> routed Fmax
echo "  impl $(date)" | tee -a $SUM
vitis-run --mode hls --impl --config $DEST/ci_fpsplit.ini --work_dir $WD > $DEST/impl.log 2>&1
TR=$(find $WD -path "*impl*" -name "*timing_summary*routed*.rpt" 2>/dev/null|head -1)
W=$(grep -iE "Worst Slack" "$TR" 2>/dev/null|grep -oE '\-?[0-9]+\.[0-9]+ns'|head -1|tr -d ns)
python3 -c "w=float('${W:-0}'); p=3.33-w; print(f'  ROUTED: WNS={w:+.3f} -> period={p:.3f} ns -> Fmax={1000/p:.0f} MHz  (was 224 node; target 300)')" 2>/dev/null | tee -a $SUM
echo "FPSPLIT_1x1_DONE $(date)" | tee -a $SUM
