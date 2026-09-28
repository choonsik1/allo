#!/bin/bash
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
BASE=/work/shared/users/zsm9/eva_leanfulldsp8x8_rtl
WD=$BASE/wd_mmm
V=$WD/hls/sim/verilog
DEST=/home/zsm9/final_eva_performance/results/realcyc_mmm; mkdir -p $DEST
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
echo "== wait for rsync ==" 
for i in $(seq 1 120); do grep -q RSYNC_DONE $BASE/rsync_mmm.log 2>/dev/null && break; sleep 10; done
grep -q RSYNC_DONE $BASE/rsync_mmm.log || { echo "RSYNC FAIL"; exit 1; }
echo "rsync done. fresh wd ready $(date)"
cd $SC
echo "==== [1] mmm cosim in FRESH wd $(date) ===="
vitis-run --mode hls --cosim --config $SC/ci_leanfd_mmm.ini --work_dir $WD > $DEST/cosim.log 2>&1
echo "  cosim rc=$?  $(grep -cE 'co-simulation finished: PASS' $DEST/cosim.log) PASS"
echo "==== [2] inject monitor $(date) ===="
python3 - "$V/top.autotb.v" <<'PYEOF'
import sys
tb=sys.argv[1]; s=open(tb).read()
anchor="    forever #`AUTOTB_CLOCK_PERIOD_DIV2 AESL_clock = ~AESL_clock;\nend\n"
mon='''
integer rc_mon; integer fh_mon;
initial begin rc_mon=0; fh_mon=$fopen("output_realcyc.txt","w"); $fdisplay(fh_mon,"# edge address realcycle"); end
always @(posedge AESL_clock) rc_mon = rc_mon + 1;
always @(posedge AESL_clock) begin
    if (v75813_we0) begin $fdisplay(fh_mon,"W %0d %0d",v75813_address0,rc_mon); $fflush(fh_mon); end
    if (v75815_we0) begin $fdisplay(fh_mon,"E %0d %0d",v75815_address0,rc_mon); $fflush(fh_mon); end
    if (v75817_we0) begin $fdisplay(fh_mon,"N %0d %0d",v75817_address0,rc_mon); $fflush(fh_mon); end
    if (v75819_we0) begin $fdisplay(fh_mon,"S %0d %0d",v75819_address0,rc_mon); $fflush(fh_mon); end
end
'''
assert anchor in s, "anchor not found"
open(tb,"w").write(s.replace(anchor, anchor+mon, 1)); print("  monitor injected")
PYEOF
echo "==== [3] xsim $(date) ===="
cd $V; rm -f output_realcyc.txt; bash run_xsim.sh > $DEST/xsim.log 2>&1
cp output_realcyc.txt $DEST/output_realcyc_mmm.txt 2>/dev/null
cp output_realcyc.txt /home/zsm9/final_eva_performance/results/realcyc_data/mmm_output_realcyc.txt 2>/dev/null
echo "==== [4] parse (edge-agnostic) $(date) ====" | tee $DEST/summary.txt
grep -oE "^[WENS]" output_realcyc.txt | sort | uniq -c | tee -a $DEST/summary.txt
ED=$(grep -oE "^[WENS]" output_realcyc.txt | sort | uniq -c | sort -rn | head -1 | awk '{print $2}')
echo "  dominant edge=$ED  row0 real-cyc spacing:" | tee -a $DEST/summary.txt
awk -v e="$ED" '$1==e && $2<2000 {print $3}' output_realcyc.txt | awk 'NR>1{print $1-p} {p=$1}' | sort | uniq -c | sort -rn | head -5 | sed 's/^/    /' | tee -a $DEST/summary.txt
echo "MMM_FRESHWD_DONE $(date)" | tee -a $DEST/summary.txt
