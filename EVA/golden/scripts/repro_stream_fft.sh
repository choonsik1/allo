#!/bin/bash
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
FR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs
PY=/home/zsm9/miniconda3/envs/allo/bin/python
B=20; L=2000; WL=fft; PRIME=1; WD=/tmp/strm_fft_repro
LOG=$SC/stream_logs/fft_repro.log; mkdir -p $SC/stream_logs
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$FR:$SC
cd $SC
{
  echo "==== STREAM fft repro (B=$B prime=$PRIME L=$L, chip=fwd_cosim) START $(date) ===="
  if [ ! -f $SC/prj_strm_fft_8x8_L${L}/kernel.cpp ]; then
    echo "-- codegen --"
    TAG=strm CHIP=eva_sb_syscredit_fwd_cosim TB=tb_replay_golden_stream.cpp WL=$WL LFORCE=$L B=$B PRIME=$PRIME $PY $SC/build_golden_cosim.py
  fi
  INI=$SC/ci_strm_fft_8x8.ini
  rm -rf $WD; mkdir -p $WD; cd $SC/prj_strm_fft_8x8_L${L}
  echo "-- csynth $(date) --"; v++ -c --mode hls --config $INI --work_dir $WD || echo "fft CSYNTH-FAIL"
  echo "-- cosim $(date) --";  vitis-run --mode hls --cosim --config $INI --work_dir $WD || echo "fft COSIM-FAIL"
  echo "-- RESULT $(date) --"
  grep -iE "row [0-9]: delivered|rows LOSSLESS|streaming .*rows lossless|bit-exact|C/RTL co-simulation finished" $WD/*/sim/report/*.log $WD/hls/sim/report/*.log 2>/dev/null | tail -20
  echo "==== STREAM fft repro DONE $(date) ===="
} > $LOG 2>&1
