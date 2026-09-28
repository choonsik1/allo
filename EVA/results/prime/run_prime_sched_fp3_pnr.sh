#!/bin/bash
# SCHEDULED rtprime 1x1 at the CORRECT FP_LAT=3 (matches L=3 = bind_op-clamped fp16
# latency; the FP_LAT>=L safety condition for the dep-false forwarding). Then P&R.
#   [0] gen FP_LAT=3 scheduled+depfalse+bindop kernel
#   [1] cosim full-top -> bit-exact vs X@W at the SAFE FP_LAT (should stay correct)
#   [2] csynth full-top -> node II (want 1) + Fmax
#   [3] P&R node_0_0 ISOLATED -> real post-route Fmax + LUT/FF/DSP (the PE-core QoR)
#   [4] P&R full-top        -> real post-route Fmax of the whole 1x1 chip
# Results -> final_chip_1x1/fp3/  (+ pnr_node_only/ , pnr_full/)
set -o pipefail
PD=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
FF=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final
cd $PD
PY=/home/zsm9/miniconda3/envs/allo/bin/python
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel
PRJ=$PD/prj_prime_1x1_L120_sched_fp3
FULLINI=$PD/ci_prime_1x1_sched_fp3.ini
NODEINI=$PD/ci_node_only_sched_fp3.ini
DEST=$FF/final_chip_1x1/fp3; mkdir -p $DEST/pnr_node_only $DEST/pnr_full
run(){ echo "+ $*"; "$@"; }

echo "######## [0] GEN FP_LAT=3 scheduled+depfalse+bindop $(date) ########"
run env SZ=1 LFORCE=120 PRIME=6 FPLAT=3 $PY build_prime_sched.py
[ -f $PRJ/kernel.cpp ] || { echo "!! no kernel"; exit 1; }
cp $PRJ/kernel.cpp $DEST/kernel_scheduled_fp3.cpp
echo "  HLS -> fp3/kernel_scheduled_fp3.cpp ($(wc -l <$PRJ/kernel.cpp) lines)"

echo "######## [1] COSIM full-top (safe FP_LAT=3, want bit-exact) $(date) ########"
WD=/tmp/prime_fp3_cosim; rm -rf $WD; mkdir -p $WD; cd $PRJ
run v++ -c --mode hls --config $FULLINI --work_dir $WD
run vitis-run --mode hls --cosim --config $FULLINI --work_dir $WD
grep -iE "PASS|FAIL|out_s|X@W|mismatch|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -12 | tee $DEST/cosim_result.txt
cp $WD/hls/sim/report/top_cosim.rpt $DEST/top_cosim.rpt 2>/dev/null
echo "  node II (want 1):"; grep -hE "l_S_t_1_t \|| l_S_t_.*yes" $WD/hls/syn/report/*_csynth.rpt 2>/dev/null | grep yes | head
echo "  FPU latencies:"; grep -ohE "h(mul|add|sub)_[0-9]+ns_[0-9]+ns_[0-9]+_[0-9]+" $WD/hls/syn/report/*_csynth.rpt 2>/dev/null | sort -u
cp -r $WD/hls/syn/report $DEST/csynth_report 2>/dev/null

echo "######## [3] P&R node_0_0 ISOLATED (PE-core post-route QoR) $(date) ########"
WDN=/tmp/prime_fp3_pnr_node; rm -rf $WDN; mkdir -p $WDN; cd $PRJ
run v++ -c --mode hls --config $NODEINI --work_dir $WDN
run vitis-run --mode hls --impl --config $NODEINI --work_dir $WDN
echo "  NODE-ONLY post-route:"; grep -hiE "CP achieved post|Timing met|Timing not met|^LUT|^FF|^DSP|Slack" $WDN/hls/impl/report/verilog/*.rpt 2>/dev/null | head -12 | tee $DEST/pnr_node_only/summary.txt
find $WDN -path "*impl*report*" \( -name "*.rpt" -o -name "*summary*" \) -exec cp {} $DEST/pnr_node_only/ \; 2>/dev/null

echo "######## [4] P&R full-top 1x1 chip (post-route) $(date) ########"
WDF=/tmp/prime_fp3_pnr_full; rm -rf $WDF; mkdir -p $WDF; cd $PRJ
run v++ -c --mode hls --config $FULLINI --work_dir $WDF
run vitis-run --mode hls --impl --config $FULLINI --work_dir $WDF
echo "  FULL-TOP post-route:"; grep -hiE "CP achieved post|Timing met|Timing not met|^LUT|^FF|^DSP|Slack" $WDF/hls/impl/report/verilog/*.rpt 2>/dev/null | head -12 | tee $DEST/pnr_full/summary.txt
find $WDF -path "*impl*report*" \( -name "*.rpt" -o -name "*summary*" \) -exec cp {} $DEST/pnr_full/ \; 2>/dev/null

echo "######## DONE $(date) ########"
echo "RESULTS in final_chip_1x1/fp3/: kernel_scheduled_fp3.cpp, cosim_result.txt, csynth_report/, pnr_node_only/, pnr_full/"
echo "PRIME_FP3_PNR_COMPLETE"
