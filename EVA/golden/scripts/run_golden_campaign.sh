#!/bin/bash
# EVA shipped-testbench RTL-cosim campaign: replay each golden pe_array workload
# on eva_sb_syscredit_fwd (8x8), diff vs eva_tb_logs golden. 2 workloads at a time.
# (fft runs separately at prime=1.)  Results -> golden_campaign_logs/<wl>.log + SUMMARY.
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
LOGD=$SC/golden_campaign_logs; mkdir -p $LOGD
PY=/home/zsm9/miniconda3/envs/allo/bin/python
CHIP=eva_sb_syscredit_fwd; LF=800; PRIME=6
WORKLOADS=(cordic_cr cordic_cv cordic_hr cordic_hv mmm)

one_wl() {
  local WL=$1; local LOG=$LOGD/${WL}.log
  { echo "==== $WL START $(date) ===="
    echo "-- [1/3] codegen --"
    if [ ! -f $SC/prj_gc_${WL}_8x8_L${LF}/kernel.cpp ]; then
      PYTHONPATH=/home/zsm9/allo_sup CHIP=$CHIP WL=$WL LFORCE=$LF PRIME=$PRIME $PY build_golden_cosim.py
    else echo "  kernel exists, skip"; fi
    INI=$SC/ci_gc_${WL}_8x8.ini; WD=/tmp/gc_${WL}
    source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
    rm -rf $WD; mkdir -p $WD; cd $SC/prj_gc_${WL}_8x8_L${LF}
    echo "-- [2/3] csynth $(date) --"
    v++ -c --mode hls --config $INI --work_dir $WD
    echo "-- [3/3] cosim $(date) --"
    vitis-run --mode hls --cosim --config $INI --work_dir $WD
    echo "-- RESULT $(date) --"
    grep -iE "row [0-9]:|golden cosim|co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -12
    echo "==== $WL DONE $(date) ===="
  } > $LOG 2>&1
}

echo "CAMPAIGN START $(date)  workloads: ${WORKLOADS[*]}" | tee $LOGD/SUMMARY.txt
i=0
while [ $i -lt ${#WORKLOADS[@]} ]; do
  a=${WORKLOADS[$i]}; b=${WORKLOADS[$((i+1))]}
  echo "  batch: $a $b  ($(date))" | tee -a $LOGD/SUMMARY.txt
  one_wl "$a" &  P1=$!
  [ -n "$b" ] && { one_wl "$b" & P2=$!; }
  wait $P1; [ -n "$b" ] && wait $P2
  i=$((i+2))
done
echo "CAMPAIGN DONE $(date)" | tee -a $LOGD/SUMMARY.txt
echo "==== per-workload verdicts ====" | tee -a $LOGD/SUMMARY.txt
for WL in "${WORKLOADS[@]}"; do
  v=$(grep -iE "golden cosim \(" $LOGD/${WL}.log 2>/dev/null | tail -1)
  echo "  $WL: ${v:-<no verdict>}" | tee -a $LOGD/SUMMARY.txt
done
