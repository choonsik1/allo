#!/bin/bash
set -o pipefail
P=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
cd $P; PY=/home/zsm9/miniconda3/envs/allo/bin/python
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
DEST=$P/ii1_test; mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt; : > $SUM
echo "== ii1 variant (SB_DEPTH=8, FP_LAT=4, committed-only fwd) + dep-false II=1, 1x1 == $(date)" | tee -a $SUM
echo "== [0] generate scheduled+depfalse+bindop kernel ==" | tee -a $SUM
CHIP=eva_sb_syscredit_rtprime_ii1 SZ=1 LFORCE=120 PRIME=6 FPLAT=4 $PY build_prime_sched.py > $DEST/gen.log 2>&1
PRJ=$P/prj_prime_1x1_L120_sched_fp4; INI=$P/ci_prime_1x1_sched_fp4.ini
[ -f $PRJ/kernel.cpp ] || { echo "  GEN FAILED: $(tail -3 $DEST/gen.log)" | tee -a $SUM; echo II1_TEST_DONE; exit 1; }
echo "  kernel: $(wc -l <$PRJ/kernel.cpp) lines, depfalse=$(grep -c dependent=false $PRJ/kernel.cpp) bindop=$(grep -c 'HLS bind_op' $PRJ/kernel.cpp)" | tee -a $SUM
echo "== [1] csynth -> achieved II (want Final II=1, and correct) == $(date)" | tee -a $SUM
WD=/tmp/ii1_csynth; rm -rf $WD; mkdir -p $WD; cd $PRJ
v++ -c --mode hls --config $INI --work_dir $WD > $DEST/csynth.log 2>&1
echo "  Pipelining result: $(grep -hE 'Pipelining result|Final II' $DEST/csynth.log | grep l_S_t | head -1)" | tee -a $SUM
echo "  200-880 (II-violation) count: $(grep -c 200-880 $DEST/csynth.log)" | tee -a $SUM
echo "== [2] cosim -> bit-exact vs X@W? (out_s=1.0=0x3c00 correct, 0x0000=dep-false hazard) == $(date)" | tee -a $SUM
vitis-run --mode hls --cosim --config $INI --work_dir $WD > $DEST/cosim.log 2>&1
echo "  RTL verdict:" | tee -a $SUM
awk '/Starting C post checking/{f=1} f&&/(PASS|FAIL).*replay|out_s\[0\]\[0\]|out_s seen/{print "    "$0}' $DEST/cosim.log | tail -4 | tee -a $SUM
echo "== II1_TEST DONE $(date) ==" | tee -a $SUM
echo II1_TEST_DONE
