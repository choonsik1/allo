#!/bin/bash
# SCHEDULED rtprime 1x1: generate II=1 HLS (pipeline_node=True + depfalse + bind_op),
# then FULL flow. Full-top for csim/csynth/cosim (chosen); node_0_0 isolated for csynth.
# Every command is echoed; result paths are saved under reports/ (see tail of log).
set -o pipefail
PD=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
cd $PD
PY=/home/zsm9/miniconda3/envs/allo/bin/python
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
PRJ=$PD/prj_prime_1x1_L120_sched
FULLINI=$PD/ci_prime_1x1_sched.ini
NODEINI=$PD/ci_node_only_sched.ini
R=$PD/reports; mkdir -p $R/sched_1x1 $R/sched_node_only
run(){ echo "+ $*"; "$@"; }

echo "######## [0] GENERATE scheduled+depfalse+bindop HLS $(date) ########"
run env SZ=1 LFORCE=120 PRIME=6 FPLAT=1 $PY build_prime_sched.py
[ -f $PRJ/kernel.cpp ] || { echo "!! no kernel — gen failed"; exit 1; }
cp $PRJ/kernel.cpp $R/sched_1x1/kernel.cpp        # the HLS code deliverable
echo "HLS code -> reports/sched_1x1/kernel.cpp ($(wc -l <$PRJ/kernel.cpp) lines)"

echo "######## [1] CSIM (full-top) $(date) ########"
WDC=/tmp/prime_sched_csim; rm -rf $WDC; mkdir -p $WDC; cd $PRJ
run vitis-run --mode hls --csim --config $FULLINI --work_dir $WDC
grep -iE "PASS|FAIL|out_s|X@W|mismatch|row " $WDC/*/sim/report/*.log 2>/dev/null | tail -12 | tee $R/sched_1x1/csim_result.txt

echo "######## [2] CSYNTH (full-top) -> node II + Fmax $(date) ########"
WDS=/tmp/prime_sched_csynth; rm -rf $WDS; mkdir -p $WDS; cd $PRJ
run v++ -c --mode hls --config $FULLINI --work_dir $WDS
echo "  node_0_0 loop II (want achieved=1):"; grep -hE "l_S_t_0_t" $WDS/hls/syn/report/*_csynth.rpt 2>/dev/null | head
echo "  FPU core latencies:"; grep -ohE "h(mul|add|sub)_[0-9]+ns_[0-9]+ns_[0-9]+_[0-9]+" $WDS/hls/syn/report/*_csynth.rpt 2>/dev/null | sort -u
echo "  Est Fmax:"; grep -hE "Estimated Fmax|CP achieved" $WDS/logs/*.log $WDS/hls/syn/report/csynth.rpt 2>/dev/null | head
cp -r $WDS/hls/syn/report $R/sched_1x1/csynth_report 2>/dev/null

echo "######## [3] COSIM (full-top) -> bit-exact vs golden X@W $(date) ########"
WDCO=/tmp/prime_sched_cosim; rm -rf $WDCO; mkdir -p $WDCO; cd $PRJ
run v++ -c --mode hls --config $FULLINI --work_dir $WDCO
run vitis-run --mode hls --cosim --config $FULLINI --work_dir $WDCO
grep -iE "PASS|FAIL|out_s|X@W|mismatch|row |co-simulation finished" $WDCO/*/sim/report/*.log 2>/dev/null | tail -14 | tee $R/sched_1x1/cosim_result.txt
cp $WDCO/hls/sim/report/top_cosim.rpt $R/sched_1x1/top_cosim.rpt 2>/dev/null

echo "######## [4] CSYNTH node_0_0 ISOLATED (no drivers/collectors) $(date) ########"
WDN=/tmp/prime_sched_node; rm -rf $WDN; mkdir -p $WDN; cd $PRJ
run v++ -c --mode hls --config $NODEINI --work_dir $WDN
echo "  ISOLATED node_0_0 loop II (want achieved=1):"; grep -hE "l_S_t_0_t" $WDN/hls/syn/report/*_csynth.rpt 2>/dev/null | head
echo "  ISOLATED Est Fmax:"; grep -hE "Estimated Fmax" $WDN/logs/*.log 2>/dev/null | head
cp -r $WDN/hls/syn/report $R/sched_node_only/csynth_report 2>/dev/null

echo "######## DONE $(date) ########"
echo "RESULTS:"
echo "  HLS code (scheduled+depfalse+bindop): reports/sched_1x1/kernel.cpp"
echo "  full-top csim  : reports/sched_1x1/csim_result.txt"
echo "  full-top csynth: reports/sched_1x1/csynth_report/  (node II + Fmax above)"
echo "  full-top cosim : reports/sched_1x1/cosim_result.txt + top_cosim.rpt"
echo "  isolated node  : reports/sched_node_only/csynth_report/"
echo "PRIME_SCHED_COMPLETE"
