#!/bin/bash
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
LOGD=$SC/nb_pnr_logs; mkdir -p $LOGD
OUT=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/nonblocking/reports/pnr_node_only
# wait for the B=20 streaming run to finish (free /tmp) before taking it
echo "NB-PNR: waiting for streaming to finish... $(date)" > $LOGD/run.log
while ! grep -q "STREAM DONE" $SC/stream_logs/SUMMARY.txt 2>/dev/null; do
  ps -eo ppid,args 2>/dev/null | awk '$1==1 && /run_stream8x8/{f=1} END{exit !f}' || break
  sleep 60
done
{ echo "NB-PNR START $(date)"
  source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
  INI=$SC/ci_nb_node_only.ini; WD=/tmp/pnr_nb_node
  rm -rf $WD; mkdir -p $WD; cd $SC/prj_eva_sb_nb_1x1_L120_nosched
  echo "-- csynth node_0_0 (non-blocking, II=3) $(date) --"; v++ -c --mode hls --config $INI --work_dir $WD
  echo "-- impl / P&R $(date) --"; vitis-run --mode hls --impl --config $INI --work_dir $WD
  echo "-- SAVE $(date) --"
  find $WD -path "*impl*report*" -name "*.rpt" -exec cp {} $OUT/ \; 2>/dev/null
  cp $WD/hls/impl/report/verilog/*.rpt $OUT/ 2>/dev/null
  echo "-- NB NODE-ONLY POST-ROUTE --"
  grep -iE "CP achieved post|Timing met|^LUT:|^FF:|^DSP:|^CLB:" $WD/logs/hls_run_impl.log 2>/dev/null | tail -8
  rm -rf $WD
  echo "NB-PNR DONE $(date)"
} >> $LOGD/run.log 2>&1
