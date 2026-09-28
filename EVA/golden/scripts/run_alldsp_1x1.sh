#!/bin/bash
# All fp ALU ops on DSP: mul=fulldsp (best) + PATCH hadd/hsub fabric->fulldsp.
# Attacks the new wall (fabric fp add/sub). lat3 + clk_unc 0.9 -> II must stay 2.
set -o pipefail
ADIMPL=${1:-fulldsp}
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
DEST=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/alldsp_$ADIMPL; mkdir -p $DEST
WD=/work/shared/users/zsm9/alldsp_${ADIMPL}_wd
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
cd $SC; SUM=$DEST/00_SUMMARY.txt; : > $SUM
echo "== ALLDSP mul=fulldsp add/sub=$ADIMPL (lat3, clk_unc=0.9) START $(date) ==" | tee $SUM
EXPTAG=_alldsp FPLAT=2 DEPFALSE=0 MULIMPL=fulldsp CHIP=eva_sb_syscredit_rtprime_ts SZ=1 LFORCE=800 BATCH=40 PRIME=6 NOSCHED=0 \
  $PY build_val_sched_ts_prime_exp.py > $DEST/build.log 2>&1
BASEK=$(grep -E "^PRJ=" $DEST/build.log|tail -1|cut -d= -f2)/kernel.cpp
INI=$(grep -E "^INI=" $DEST/build.log|tail -1|cut -d= -f2)
[ -f "$BASEK" ] || { echo "EMIT FAIL"; tail -8 $DEST/build.log|tee -a $SUM; exit 1; }
# PATCH hadd/hsub impl fabric -> $ADIMPL
sed -i -e "s/op=hadd impl=fabric/op=hadd impl=$ADIMPL/g" -e "s/op=hsub impl=fabric/op=hsub impl=$ADIMPL/g" $BASEK
echo "  binds now: $(grep -oE 'op=h(mul|add|sub) impl=[a-z_]+' $BASEK | sort | uniq -c | tr '\n' ' ')" | tee -a $SUM
sed -e "s#^syn.file=.*#syn.file=$BASEK#" $INI > $DEST/ci.ini
grep -q clock_uncertainty $DEST/ci.ini || sed -i "/clock=/a syn.clock_uncertainty=0.9" $DEST/ci.ini
rm -rf $WD; mkdir -p $WD
echo "  csynth $(date)" | tee -a $SUM
v++ -c --mode hls --config $DEST/ci.ini --work_dir $WD > $DEST/csynth.log 2>&1
NV=$(ls $WD/hls/syn/verilog/*.v 2>/dev/null | wc -l); GS=$(find $WD -name global.setting.tcl 2>/dev/null|head -1)
if [ "$NV" -lt 1 ] || [ -z "$GS" ]; then echo "  CSYNTH INCOMPLETE (v=$NV db=${GS:-MISS})"|tee -a $SUM; tail -6 $DEST/csynth.log|tee -a $SUM; exit 2; fi
echo "  csynth OK ($NV verilog)" | tee -a $SUM
echo "  Final-II: $(grep -hoE 'Final II = [0-9]+' $DEST/csynth.log|sort|uniq -c|tr '\n' ' ')" | tee -a $SUM
echo "  node-loop-II: $(awk "/Implementing module 'node_0_0_Pipeline_l_S_t_1_t'/{f=1} f&&/Final II/{print;exit}" $DEST/csynth.log|grep -oE 'Final II = [0-9]+')" | tee -a $SUM
echo "  fp cores: $(grep -rhoE 'h(mul|add|sub)_16[^ \"./]*_1 ' $WD/hls/syn/verilog/*.v 2>/dev/null|sort -u|tr '\n' ' ')" | tee -a $SUM
echo "  impl $(date)" | tee -a $SUM
vitis-run --mode hls --impl --config $DEST/ci.ini --work_dir $WD > $DEST/impl.log 2>&1
TR=$(find $WD -path "*impl*" -name "top_timing_paths_routed.rpt" 2>/dev/null|head -1)
[ -z "$TR" ] && TR=$(find $WD -path "*impl*" -name "*timing_summary*routed*.rpt" 2>/dev/null|head -1)
if [ -z "$TR" ] || [ ! -f "$TR" ]; then echo "  IMPL FAIL: no routed report"|tee -a $SUM; tail -8 $DEST/impl.log|tee -a $SUM; exit 3; fi
W=$(grep -iE "Worst Slack|Slack \(" "$TR" 2>/dev/null|grep -oE '\-?[0-9]+\.[0-9]+ns'|head -1|tr -d ns)
[ -z "$W" ] && { echo "  IMPL FAIL: no slack in $TR"|tee -a $SUM; exit 3; }
python3 -c "w=float('$W'); p=3.33-w; print(f'  ROUTED add/sub=$ADIMPL: WNS={w:+.3f} -> {p:.3f} ns -> {1000/p:.0f} MHz  (fulldsp-mul-only=251; target 300)')" | tee -a $SUM
echo "  crit-src: $(grep -m1 'Source:' "$TR" | grep -oE 'h(mul|add|sub|cmp)_16[^/]*|sparsemux[^/]*' | head -1)  levels: $(grep -m1 'Logic Levels' "$TR")" | tee -a $SUM
echo "ALLDSP_${ADIMPL}_DONE $(date)" | tee -a $SUM
