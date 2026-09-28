#!/bin/bash
# Validate the NON-BLOCKING (no-credit) chip on the FULL golden suite (8x8 RTL cosim,
# bit-exact vs golden). eva_sb_nb has only ever been verified on 4x4 mmm; this tests
# whether non-blocking-without-credits holds up on fft (router) + cordic. Waits for the
# streaming + nb-P&R runs to free /tmp. Serial, ENOSPC-safe.
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
LOGD=$SC/nb_golden_logs; mkdir -p $LOGD
OUT=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/nonblocking/golden_suite; mkdir -p $OUT
PY=/home/zsm9/miniconda3/envs/allo/bin/python
echo "NB-GOLD: waiting for streaming + nb-pnr to finish... $(date)" > $LOGD/SUMMARY.txt
while ! { grep -q "STREAM DONE" $SC/stream_logs/SUMMARY.txt 2>/dev/null && grep -q "NB-PNR DONE" $SC/nb_pnr_logs/run.log 2>/dev/null; }; do
  ps -eo ppid,args 2>/dev/null | awk '$1==1 && (/run_stream8x8/||/run_pnr_nb_node/){f=1} END{exit !f}' || { echo "  prior runs gone; proceeding $(date)" >> $LOGD/SUMMARY.txt; break; }
  sleep 120
done
echo "NB-GOLD START $(date)" | tee -a $LOGD/SUMMARY.txt
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
for WL in mmm fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  LOG=$LOGD/$WL.log; WD=/tmp/nbg_$WL
  { echo "==== NB-GOLD $WL START $(date) ===="
    if [ ! -f $SC/prj_nbgold_${WL}_8x8_L800/kernel.cpp ]; then
      ( cd $SC && PYTHONPATH=/home/zsm9/allo TAG=nbgold CHIP=eva_sb_nb TB=tb_replay_golden.cpp WL=$WL LFORCE=800 $PY $SC/build_golden_cosim.py )
    fi
    INI=$SC/ci_nbgold_${WL}_8x8.ini
    rm -rf $WD; mkdir -p $WD; cd $SC/prj_nbgold_${WL}_8x8_L800
    echo "-- csynth $(date) --"; v++ -c --mode hls --config $INI --work_dir $WD || echo "$WL CSYNTH-FAIL"
    echo "-- cosim $(date) --";  vitis-run --mode hls --cosim --config $INI --work_dir $WD || echo "$WL COSIM-FAIL"
    grep -iE "row [0-9]:|golden cosim.*rows|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -14
    OW=$OUT/$WL; mkdir -p $OW; cp $WD/hls/sim/report/top_cosim.rpt $OW/top_cosim.rpt 2>/dev/null
    { echo "# $WL on eva_sb_nb (NON-BLOCKING, no credit plane), 8x8 RTL cosim"; echo
      grep -iE "row [0-9]:|golden cosim.*rows|C/RTL co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -12; } > $OW/verdict.txt
    rm -rf $WD
    echo "==== NB-GOLD $WL DONE $(date) ===="; } > $LOG 2>&1
done
echo "NB-GOLD DONE $(date)" | tee -a $LOGD/SUMMARY.txt
for WL in mmm fft cordic_cr cordic_cv cordic_hr cordic_hv; do
  echo "  $WL: $(grep -iE 'golden cosim.*rows bit-exact' $LOGD/$WL.log 2>/dev/null | tail -1 | grep -oE '(PASS|FAIL).*[0-9]+/8 rows')" | tee -a $LOGD/SUMMARY.txt
done
