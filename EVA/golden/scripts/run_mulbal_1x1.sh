#!/bin/bash
# Rebalance the fp16 MUL core at constant latency-3 by swapping HLS impl (maxdsp->
# fabric/fulldsp). Keep clk_uncertainty=0.9. Goal: keep II=2, close 3.33ns. $1=impl.
set -o pipefail
IMPL=${1:-fabric}
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/mulbal_$IMPL; mkdir -p $DEST
WD=/work/shared/users/zsm9/mulbal_${IMPL}_wd
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
cd $SC; SUM=$DEST/00_SUMMARY.txt; : > $SUM
echo "== MULBAL impl=$IMPL (lat3, clk_unc=0.9) START $(date) ==" | tee $SUM
EXPTAG=_mulbal$IMPL FPLAT=2 DEPFALSE=0 MULIMPL=$IMPL CHIP=eva_sb_syscredit_rtprime_ts SZ=1 LFORCE=800 BATCH=40 PRIME=6 NOSCHED=0 \
  $PY build_val_sched_ts_prime_exp.py > $DEST/build.log 2>&1
BASEK=$(grep -E "^PRJ=" $DEST/build.log|tail -1|cut -d= -f2)/kernel.cpp
INI=$(grep -E "^INI=" $DEST/build.log|tail -1|cut -d= -f2)
[ -f "$BASEK" ] || { echo "EMIT FAIL"; tail -8 $DEST/build.log|tee -a $SUM; exit 1; }
grep "EXP:" $DEST/build.log | tee -a $SUM
echo "  hmul bind in kernel: $(grep -m1 'op=hmul' $BASEK | sed 's/^ *//')" | tee -a $SUM
sed -e "s#^syn.file=.*#syn.file=$BASEK#" $INI > $DEST/ci.ini
grep -q clock_uncertainty $DEST/ci.ini || sed -i "/clock=/a syn.clock_uncertainty=0.9" $DEST/ci.ini
rm -rf $WD; mkdir -p $WD
echo "  csynth $(date)" | tee -a $SUM
v++ -c --mode hls --config $DEST/ci.ini --work_dir $WD > $DEST/csynth.log 2>&1
# GUARD: csynth must produce RTL + the vpp DB the impl needs (else it was killed)
NV=$(ls $WD/hls/syn/verilog/*.v 2>/dev/null | wc -l)
GS=$(find $WD -name global.setting.tcl 2>/dev/null | head -1)
if [ "$NV" -lt 1 ] || [ -z "$GS" ]; then echo "  CSYNTH INCOMPLETE (verilog=$NV, db=${GS:-MISSING}) -- likely killed" | tee -a $SUM; tail -6 $DEST/csynth.log | tee -a $SUM; exit 2; fi
echo "  csynth OK ($NV verilog files)" | tee -a $SUM
echo "  Final-II: $(grep -hoE 'Final II = [0-9]+' $DEST/csynth.log|sort|uniq -c|tr '\n' ' ')" | tee -a $SUM
echo "  node-loop-II: $(awk "/Implementing module 'node_0_0_Pipeline_l_S_t_1_t'/{f=1} f&&/Final II/{print; exit}" $DEST/csynth.log | grep -oE 'Final II = [0-9]+')" | tee -a $SUM
echo "  fp mul cores: $(grep -rhoE 'hmul_16[^ \"./]*' $WD/hls/syn/report/*.rpt $WD/hls/syn/verilog/*.v 2>/dev/null|sort -u|tr '\n' ' ')" | tee -a $SUM
echo "  impl $(date)" | tee -a $SUM
vitis-run --mode hls --impl --config $DEST/ci.ini --work_dir $WD > $DEST/impl.log 2>&1
TR=$(find $WD -path "*impl*" -name "*timing_summary*routed*.rpt" 2>/dev/null|head -1)
# GUARD: no routed report => impl failed. Do NOT default WNS to 0 (fake 300).
if [ -z "$TR" ] || [ ! -f "$TR" ]; then echo "  IMPL FAIL: no routed timing report" | tee -a $SUM; tail -8 $DEST/impl.log | tee -a $SUM; exit 3; fi
W=$(grep -iE "Worst Slack" "$TR" 2>/dev/null|grep -oE '\-?[0-9]+\.[0-9]+ns'|head -1|tr -d ns)
if [ -z "$W" ]; then echo "  IMPL FAIL: report has no Worst Slack ($TR)" | tee -a $SUM; exit 3; fi
python3 -c "w=float('$W'); p=3.33-w; print(f'  ROUTED impl=$IMPL: WNS={w:+.3f} -> {p:.3f} ns -> {1000/p:.0f} MHz  (maxdsp=239; target 300)')" | tee -a $SUM
echo "MULBAL_${IMPL}_DONE $(date)" | tee -a $SUM
