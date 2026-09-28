#!/bin/bash
# P&R the CORRECT scheduled II=2 rtprime (exp1 = no dep-false, RTL PASS) to get its
# real post-route Fmax/area. node_0_0 isolated (PE-core QoR, compare vs II=1's 4.76ns)
# + full 1x1 top. Results -> final_chip_1x1/ii2/{pnr_node_only,pnr_full}/.
set -o pipefail
PD=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
FF=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final
cd $PD
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
PRJ=$PD/prj_prime_1x1_sched_nodep
KP=$PRJ/kernel.cpp
DEST=$FF/final_chip_1x1/ii2; mkdir -p $DEST/pnr_node_only $DEST/pnr_full
cp $KP $DEST/kernel_scheduled_ii2_nodepfalse.cpp
run(){ echo "+ $*"; "$@"; }

# node-only ini (syn.top=node_0_0, no tb needed for impl)
cat > $PD/ci_ii2_node.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=node_0_0
syn.file=$KP
syn.compile.pipeline_loops=0
INI

echo "######## [1] P&R node_0_0 ISOLATED (PE-core, II=2) $(date) ########"
WDN=/tmp/ii2_pnr_node; rm -rf $WDN; mkdir -p $WDN; cd $PRJ
run v++ -c --mode hls --config $PD/ci_ii2_node.ini --work_dir $WDN
echo "  node II: $(grep -hE 'l_S_t_1_t ' $WDN/hls/syn/report/*_csynth.rpt 2>/dev/null | grep -E 'yes|no' | tr -s ' ' | head -1)"
run vitis-run --mode hls --impl --config $PD/ci_ii2_node.ini --work_dir $WDN
echo "  NODE-ONLY post-route:" | tee $DEST/pnr_node_only/summary.txt
grep -hiE "CP achieved post|Timing met|Timing not met|^LUT|^FF|^DSP|Slack|WNS" $WDN/hls/impl/report/verilog/*.rpt 2>/dev/null | head -14 | tee -a $DEST/pnr_node_only/summary.txt
find $WDN -path "*impl*report*" \( -name "*.rpt" -o -name "*summary*" \) -exec cp {} $DEST/pnr_node_only/ \; 2>/dev/null

echo "######## [2] P&R full-top 1x1 chip (II=2) $(date) ########"
WDF=/tmp/ii2_pnr_full; rm -rf $WDF; mkdir -p $WDF; cd $PRJ
run v++ -c --mode hls --config $PD/ci_sched_nodep.ini --work_dir $WDF
run vitis-run --mode hls --impl --config $PD/ci_sched_nodep.ini --work_dir $WDF
echo "  FULL-TOP post-route:" | tee $DEST/pnr_full/summary.txt
grep -hiE "CP achieved post|Timing met|Timing not met|^LUT|^FF|^DSP|Slack|WNS" $WDF/hls/impl/report/verilog/*.rpt 2>/dev/null | head -14 | tee -a $DEST/pnr_full/summary.txt
find $WDF -path "*impl*report*" \( -name "*.rpt" -o -name "*summary*" \) -exec cp {} $DEST/pnr_full/ \; 2>/dev/null

echo "######## DONE $(date) ########"
echo "II2_PNR_COMPLETE"
