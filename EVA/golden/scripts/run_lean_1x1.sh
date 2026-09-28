#!/bin/bash
# 1x1 synth+P&R of the IMPROVED chip: leanalu (#1 hsub deleted via sign-flip) + fulldsp mul.
# De-risks the 13h 8x8: does #1 push Fmax past 251, II still 2, where does the wall go?
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/lean_1x1; mkdir -p $DEST
WD=/work/shared/users/zsm9/lean_1x1_wd
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
cd $SC; SUM=$DEST/00_SUMMARY.txt; : > $SUM
echo "== LEAN 1x1 (leanalu #1 + fulldsp mul, clk_unc=0.9) START $(date) ==" | tee $SUM
EXPTAG=_lean FPLAT=2 DEPFALSE=0 MULIMPL=fulldsp CHIP=eva_sb_syscredit_rtprime_ts_leanalu SZ=1 LFORCE=800 BATCH=40 PRIME=6 NOSCHED=0 \
  $PY build_val_sched_ts_prime_exp.py > $DEST/build.log 2>&1
BASEK=$(grep -E "^PRJ=" $DEST/build.log|tail -1|cut -d= -f2)/kernel.cpp
INI=$(grep -E "^INI=" $DEST/build.log|tail -1|cut -d= -f2)
[ -f "$BASEK" ] || { echo "EMIT FAIL"; tail -12 $DEST/build.log|tee -a $SUM; exit 1; }
grep "EXP:" $DEST/build.log | tee -a $SUM
echo "  hsub instances in kernel (want 0 = #1 worked): $(grep -c 'op=hsub' $BASEK)" | tee -a $SUM
echo "  binds: $(grep -oE 'op=h(mul|add|sub) impl=[a-z_]+' $BASEK|sort|uniq -c|tr '\n' ' ')" | tee -a $SUM
sed -e "s#^syn.file=.*#syn.file=$BASEK#" $INI > $DEST/ci.ini
grep -q clock_uncertainty $DEST/ci.ini || sed -i "/clock=/a syn.clock_uncertainty=0.9" $DEST/ci.ini
rm -rf $WD; mkdir -p $WD
echo "  csynth $(date)" | tee -a $SUM
v++ -c --mode hls --config $DEST/ci.ini --work_dir $WD > $DEST/csynth.log 2>&1
NV=$(ls $WD/hls/syn/verilog/*.v 2>/dev/null|wc -l); GS=$(find $WD -name global.setting.tcl 2>/dev/null|head -1)
if [ "$NV" -lt 1 ] || [ -z "$GS" ]; then echo "  CSYNTH INCOMPLETE (v=$NV db=${GS:-MISS})"|tee -a $SUM; tail -8 $DEST/csynth.log|tee -a $SUM; exit 2; fi
echo "  csynth OK ($NV verilog)" | tee -a $SUM
echo "  Final-II: $(grep -hoE 'Final II = [0-9]+' $DEST/csynth.log|sort|uniq -c|tr '\n' ' ')" | tee -a $SUM
echo "  node-loop-II: $(awk "/Implementing module 'node_0_0_Pipeline_l_S_t_1_t'/{f=1} f&&/Final II/{print;exit}" $DEST/csynth.log|grep -oE 'Final II = [0-9]+')" | tee -a $SUM
echo "  impl $(date)" | tee -a $SUM
vitis-run --mode hls --impl --config $DEST/ci.ini --work_dir $WD > $DEST/impl.log 2>&1
TR=$(find $WD -path "*impl*" -name "top_timing_paths_routed.rpt" 2>/dev/null|head -1)
[ -z "$TR" ] && TR=$(find $WD -path "*impl*" -name "*timing_summary*routed*.rpt" 2>/dev/null|head -1)
if [ -z "$TR" ] || [ ! -f "$TR" ]; then echo "  IMPL FAIL: no routed report"|tee -a $SUM; tail -8 $DEST/impl.log|tee -a $SUM; exit 3; fi
W=$(grep -iE "Worst Slack|Slack \(" "$TR"|grep -oE '\-?[0-9]+\.[0-9]+ns'|head -1|tr -d ns)
[ -z "$W" ] && { echo "  IMPL FAIL: no slack"|tee -a $SUM; exit 3; }
python3 -c "w=float('$W'); p=3.33-w; print(f'  ROUTED lean+fulldsp: WNS={w:+.3f} -> {p:.3f} ns -> {1000/p:.0f} MHz  (fulldsp-only=251; target 300)')"|tee -a $SUM
echo "  crit-src: $(grep -m1 'Source:' "$TR"|grep -oE 'h(mul|add|sub|cmp)_16[^/]*|sparsemux[^/]*'|head -1)   $(grep -m1 'Logic Levels' "$TR"|tr -s ' ')"|tee -a $SUM
echo "LEAN_1x1_DONE $(date)" | tee -a $SUM
