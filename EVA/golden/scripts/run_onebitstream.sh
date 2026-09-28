#!/bin/bash
# ONE-BITSTREAM CAPSTONE: the runtime-prime chip (eva_sb_syscredit_rtprime) synthesized
# ONCE, then EVERY shipped workload run against that SAME RTL — only prime_cfg (1 for
# fft/cordic, 6 for mmm) + program/inputs differ. Proves a single programmable EVA
# bitstream runs the whole workload suite. Waits for the ts2 campaign (ENOSPC-safe).
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
cd $SC
LOGD=$SC/onebitstream_logs; mkdir -p $LOGD
FF=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final
OUT=$FF/golden_testbenches/one_bitstream; mkdir -p $OUT
PY=/home/zsm9/miniconda3/envs/allo/bin/python
# workload -> prime (east-drain fft/cordic=1, south-drain mmm=6)
WLS=(fft cordic_cr cordic_cv cordic_hr cordic_hv mmm)
PRS=(1   1         1         1         1         6)

echo "ONEBITSTREAM: waiting for ts2 campaign to finish... $(date)" | tee $LOGD/SUMMARY.txt
while ! grep -q "TS2 DONE" $SC/cosim_ts2_logs/SUMMARY.txt 2>/dev/null; do
  ps -eo ppid,args 2>/dev/null | awk '$1==1 && /run_golden_ts2/{f=1} END{exit !f}' || { echo "  ts2 driver gone; proceeding $(date)"; break; }
  sleep 60
done
echo "ONEBITSTREAM START $(date)" | tee -a $LOGD/SUMMARY.txt
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh

# 1) generate per-workload vectors on the SHARED rtprime kernel (correct primes)
for i in "${!WLS[@]}"; do
  WL=${WLS[$i]} P=${PRS[$i]}
  echo "-- gen vectors $WL (prime=$P) $(date)" | tee -a $LOGD/SUMMARY.txt
  PYTHONPATH=/home/zsm9/allo TAG=obs CHIP=eva_sb_syscredit_rtprime TB=tb_replay_golden_prime.cpp \
    WL=$WL LFORCE=800 PRIME=$P $PY build_golden_cosim.py > $LOGD/gen_$WL.log 2>&1
done

# 2) prove kernels identical, pick the shared one
md5sum $SC/prj_obs_*_8x8_L800/kernel.cpp | awk '{print $1}' | sort -u > $LOGD/kernel_md5s.txt
NMD5=$(wc -l < $LOGD/kernel_md5s.txt)
echo "distinct rtprime kernels across all workloads: $NMD5 (1 = one bitstream)" | tee -a $LOGD/SUMMARY.txt
KPRJ=$SC/prj_obs_fft_8x8_L800

# 3) shared ini: fixed kernel + tb, vectors swapped via vectors_obs_current.h
SINI=$SC/ci_obs_shared.ini
cat > $SINI <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$KPRJ/kernel.cpp
tb.file=$SC/tb_replay_golden_prime.cpp
tb.cflags=-I$SC -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_obs_current.h"
syn.compile.pipeline_loops=0
INI

# 4) csynth the shared kernel ONCE
WD=/tmp/obs_shared
rm -rf $WD; mkdir -p $WD
echo "-- [csynth ONCE] the shared rtprime bitstream $(date) --" | tee -a $LOGD/SUMMARY.txt
cp $SC/vectors_obs_fft_8x8.h $SC/vectors_obs_current.h
( cd $KPRJ && v++ -c --mode hls --config $SINI --work_dir $WD ) > $LOGD/csynth.log 2>&1
echo "   csynth exit=$? $(date)" | tee -a $LOGD/SUMMARY.txt

# 5) cosim EACH workload against the SAME synthesized RTL (swap stimulus only)
for i in "${!WLS[@]}"; do
  WL=${WLS[$i]} P=${PRS[$i]}
  echo "-- [cosim] $WL on shared bitstream (prime=$P) $(date) --" | tee -a $LOGD/SUMMARY.txt
  cp $SC/vectors_obs_${WL}_8x8.h $SC/vectors_obs_current.h
  ( cd $KPRJ && vitis-run --mode hls --cosim --config $SINI --work_dir $WD ) > $LOGD/cosim_$WL.log 2>&1
  v=$(grep -iE "one-bitstream cosim.*rows bit-exact" $WD/*/sim/report/*.log 2>/dev/null | grep -iE "PASS|FAIL" | tail -1)
  cp $WD/hls/sim/report/top_cosim.rpt $OUT/${WL}_cosim.rpt 2>/dev/null
  { echo "# $WL on the SHARED rtprime bitstream, prime_cfg=$P"; echo
    grep -iE "row [0-9]:|one-bitstream cosim.*rows|C/RTL co-simulation finished" $WD/*/sim/report/*.log 2>/dev/null | tail -12
  } > $OUT/${WL}_verdict.txt
  echo "   $WL: ${v:-<no verdict>}" | tee -a $LOGD/SUMMARY.txt
done
rm -rf $WD
echo "ONEBITSTREAM DONE $(date)" | tee -a $LOGD/SUMMARY.txt
cp $LOGD/SUMMARY.txt $OUT/SUMMARY.txt
cp $LOGD/kernel_md5s.txt $OUT/kernel_md5s.txt
