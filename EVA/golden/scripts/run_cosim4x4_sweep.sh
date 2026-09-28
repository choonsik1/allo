#!/bin/bash
# 4x4 RTL cosim sweep over the STANDARD-signature EVA variants (mmm ones).
# Records per-chip verdict: DEADLOCK (200-742) / PASS / other. ~15-25 min csynth each (serial).
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PY=/home/zsm9/miniconda3/envs/allo/bin/python
LOGD=$SC/cosim4x4_logs; mkdir -p $LOGD
SUM=$LOGD/SUMMARY.txt; : > $SUM
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo
cd $SC

# module:TAG  (standard signature only)
CHIPS=(
  "eva_sb_syscredit_rtprime:rtprime"
  "eva_sb_syscredit_rtprime_wbfwd:wbfwd"
  "eva_sb_syscredit_rtprime_no_cred:nocred"
  "eva_sb_syscredit_rtprime_guarded:guarded"
  "eva_sb_syscredit_rtprime_elastic:elastic"
  "eva_sb_syscredit_rtprime_elastic2:elastic2"
)
echo "==== 4x4 COSIM SWEEP START $(date) ====" | tee $SUM
for entry in "${CHIPS[@]}"; do
  CHIP="${entry%%:*}"; TAG="${entry##*:}"
  WD=/work/shared/users/zsm9/var4x4_${TAG}_wd
  L=$LOGD/$TAG.log
  echo "---- $TAG ($CHIP) $(date) ----" | tee -a $SUM
  { echo "== codegen =="; CHIP=$CHIP TAG=$TAG $PY build_var_4x4.py
    echo "== csynth =="; rm -rf $WD; mkdir -p $WD
    v++ -c --mode hls --config $SC/ci_${TAG}_mmm.ini --work_dir $WD && echo "csynth OK"
    echo "== cosim =="; vitis-run --mode hls --cosim --config $SC/ci_${TAG}_mmm.ini --work_dir $WD
  } > $L 2>&1
  # verdict
  if grep -q "200-742" $L; then V="DEADLOCK (200-742)"
  elif grep -qE "co-simulation finished: PASS|PASS: one-bitstream" $L; then V="PASS/completed"
  elif grep -q "C TB testing failed" $L; then V="C-SIM ABORT (empty-read)"
  elif grep -q "csynth OK" $L; then V="cosim-inconclusive (see log)"
  else V="BUILD/CSYNTH FAIL"; fi
  echo "  $TAG -> $V" | tee -a $SUM
  rm -rf $WD/hls/sim/verilog/*.wdb 2>/dev/null
done
echo "==== SWEEP DONE $(date) ====" | tee -a $SUM
echo "--- results ---"; grep " -> " $SUM
