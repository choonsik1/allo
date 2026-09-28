#!/bin/bash
set -o pipefail
P=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
cd $P; PY=/home/zsm9/miniconda3/envs/allo/bin/python
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$P LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
DEST=$P/wbfwd_test; mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt; : > $SUM
echo "== WB-only-forwarding variant (FWD=0, WB->DRF discipline = Vitis pe_core.cpp) + dep-false II=1, 1x1 == $(date)" | tee -a $SUM
echo "== [0] generate scheduled+depfalse+bindop wbfwd kernel ==" | tee -a $SUM
CHIP=eva_sb_syscredit_rtprime_wbfwd SZ=1 LFORCE=120 PRIME=6 FPLAT=1 $PY build_wbfwd_sched.py > $DEST/gen.log 2>&1
PRJ=$P/prj_wbfwd_1x1_L120_fp1; INI=$P/ci_wbfwd_1x1_fp1.ini
[ -f $PRJ/kernel.cpp ] || { echo "  GEN FAILED: $(tail -3 $DEST/gen.log)" | tee -a $SUM; echo WBFWD_TEST_DONE; exit 1; }
echo "  kernel: $(wc -l <$PRJ/kernel.cpp) lines, depfalse=$(grep -c dependent=false $PRJ/kernel.cpp), resq-fwd-reads=$(grep -cE 'a = resq\[v|b = resq\[v|resq\[.*fwd' $PRJ/kernel.cpp) (want ~0 = FWD=0 removed forwarding)" | tee -a $SUM
echo "== [1] csynth -> achieved II == $(date)" | tee -a $SUM
WD=/tmp/wbfwd_csynth; rm -rf $WD; mkdir -p $WD; cd $PRJ
v++ -c --mode hls --config $INI --work_dir $WD > $DEST/csynth.log 2>&1
echo "  $(grep -hE 'Pipelining result' $DEST/csynth.log | grep l_S_t | head -1)" | tee -a $SUM
echo "  200-880 count: $(grep -c 200-880 $DEST/csynth.log)" | tee -a $SUM
echo "== [2] cosim -> bit-exact vs X@W? (0x3c00=CORRECT honest II=1! / 0x0000=still hazard) == $(date)" | tee -a $SUM
vitis-run --mode hls --cosim --config $INI --work_dir $WD > $DEST/cosim.log 2>&1
awk '/Starting C post checking/{f=1} f&&/(PASS|FAIL).*replay|out_s\[0\]\[0\]|out_s seen/{print "    "$0}' $DEST/cosim.log | tail -4 | tee -a $SUM
echo "== WBFWD_TEST DONE $(date) ==" | tee -a $SUM
echo WBFWD_TEST_DONE
