#!/bin/bash
set -e
PD=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
cd $PD
PY=/home/zsm9/miniconda3/envs/allo/bin/python
echo "=== [1/3] codegen 1x1 rtprime (prime_cfg runtime) $(date) ==="
PYTHONPATH=/home/zsm9/allo_sup SZ=1 LFORCE=120 PRIME=6 $PY build_prime.py
INI=$PD/ci_prime_1x1.ini
WD=/tmp/pnr_rtprime_1x1
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
rm -rf $WD; mkdir -p $WD; cd $PD/prj_prime_1x1_L120
echo "=== [2/3] csynth $(date) ==="
v++ -c --mode hls --config $INI --work_dir $WD
echo "=== [3/3] impl / place-and-route $(date) ==="
vitis-run --mode hls --impl --config $INI --work_dir $WD
echo "=== SAVE all P&R reports $(date) ==="
OUT=$PD/reports/pnr_1x1; mkdir -p $OUT
# copy every impl/P&R report generated
find $WD -path "*impl*" \( -name "*.rpt" -o -name "*.xml" -o -name "*summary*" \) -exec cp {} $OUT/ \; 2>/dev/null
find $WD -name "*timing_summary*" -o -name "*utilization*placed*" -o -name "*.pb" 2>/dev/null | while read f; do cp "$f" $OUT/ 2>/dev/null; done
cp $WD/hls/impl/report/verilog/*.rpt $OUT/ 2>/dev/null || true
ls -la $OUT/ | tail -20
echo "=== POST-ROUTE FMAX + UTIL ==="
grep -riE "CP achieved post|Post-Routing|Slack|Estimated Fmax|clock period" $WD 2>/dev/null | grep -iE "post|achieved|fmax" | head -5
echo "=== DONE $(date) ==="
