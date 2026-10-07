#!/bin/bash
set -e
PD=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
cd $PD
INI=$PD/ci_node_only.ini
WD=/tmp/pnr_node_only
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
rm -rf $WD; mkdir -p $WD; cd $PD/prj_prime_1x1_L120
echo "=== [1/2] csynth node_0_0 (PE core only) $(date) ==="
v++ -c --mode hls --config $INI --work_dir $WD
echo "=== [2/2] impl / P&R $(date) ==="
vitis-run --mode hls --impl --config $INI --work_dir $WD
echo "=== SAVE reports $(date) ==="
OUT=$PD/reports/pnr_node_only; mkdir -p $OUT
find $WD -path "*impl*report*" \( -name "*.rpt" -o -name "*summary*" \) -exec cp {} $OUT/ \; 2>/dev/null
cp $WD/hls/impl/report/verilog/*.rpt $OUT/ 2>/dev/null || true
cp $WD/hls/syn/report/*csynth.rpt $OUT/ 2>/dev/null || true
echo "=== NODE-ONLY POST-ROUTE ==="
grep -iE "CP achieved post|Timing met|Timing not met|^LUT:|^FF:|^DSP:|II|Interval" $WD/hls/impl/report/verilog/*.rpt $WD/logs/hls_run_impl.log 2>/dev/null | head -12
echo "=== DONE $(date) ==="
