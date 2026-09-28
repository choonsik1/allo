#!/bin/bash
# ITEM 3 isolator: lean chip SZ=4 (4x4), synthetic mmm, scheduled II=2 (get_scheduled_eva + binds).
# cyc/timestep = total_cosim_latency / NSTEP. Compare to 8x8 mmm = 9.02. Only SIZE moves.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
NFS=/work/shared/users/zsm9/eva_lean4x4_rtl; WD=$NFS/wd
DEST=/home/zsm9/final_eva_performance/results/lean4x4_iso; mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt; : > $SUM
export TMPDIR=$NFS/tmp
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo_sup:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
LF=800
cd $SC
echo "== ITEM3 lean 4x4 isolator (mmm, NSTEP=$LF) START $(date) ==" | tee $SUM
# [1] scheduled codegen SZ=4 (get_scheduled_eva + binds, II=2)
echo "-- [1] scheduled codegen SZ=4 (~15-30min) $(date) --" | tee -a $SUM
EXPTAG=_iso4 FPLAT=2 DEPFALSE=0 MULIMPL=fulldsp CHIP=eva_sb_syscredit_rtprime_ts_leanalu SZ=4 LFORCE=$LF BATCH=1 PRIME=6 NOSCHED=0 \
  $PY build_val_sched_ts_prime_exp.py > $DEST/build.log 2>&1
K1=$(grep -E "^PRJ=" $DEST/build.log | tail -1 | cut -d= -f2)/kernel.cpp
INI0=$(grep -E "^INI=" $DEST/build.log | tail -1 | cut -d= -f2)
[ -f "$K1" ] || { echo "CODEGEN FAIL"; tail -12 $DEST/build.log | tee -a $SUM; exit 1; }
echo "  kernel: $(wc -l <$K1) lines; binds: $(grep -oE 'op=h(mul|add) impl=[a-z_]+' $K1|sort|uniq -c|tr '\n' ' '); pipeline: $(grep -c 'pragma HLS pipeline' $K1)" | tee -a $SUM
# [3] csynth (16 nodes) — reuse the generated ini, add clock_uncertainty
sed -e "s#^syn.file=.*#syn.file=$K1#" $INI0 > $SC/ci_iso4.ini
grep -q clock_uncertainty $SC/ci_iso4.ini || sed -i "/clock=/a syn.clock_uncertainty=0.9" $SC/ci_iso4.ini
echo "-- [3] csynth 16 nodes (~hrs) $(date) --" | tee -a $SUM
rm -rf $WD; mkdir -p $WD
v++ -c --mode hls --config $SC/ci_iso4.ini --work_dir $WD > $NFS/csynth.log 2>&1
[ -d $WD/hls/syn ] || { echo "CSYNTH FAIL"; tail -15 $NFS/csynth.log | tee -a $SUM; exit 2; }
echo "  csynth OK; node II: $(grep -hoE 'Final II = [0-9]+' $NFS/csynth.log|sort|uniq -c|tr '\n' ' ')" | tee -a $SUM
# [4] cosim -> cyc/timestep
echo "-- [4] cosim mmm $(date) --" | tee -a $SUM
vitis-run --mode hls --cosim --config $SC/ci_iso4.ini --work_dir $WD > $DEST/cosim.log 2>&1
R=$WD/hls/sim/report/top_cosim.rpt
LAT=$(grep -E "Verilog" "$R" 2>/dev/null | grep -oE "[0-9]{3,}" | head -1)
PASS=$(grep -cE "co-simulation finished: PASS" $DEST/cosim.log)
python3 -c "lat=${LAT:-0}; print(f'  ⭐ lean 4x4 mmm: latency={lat}, NSTEP=$LF -> {lat/$LF:.2f} cyc/timestep  (8x8 lean mmm=9.02; PASS=$PASS)')" | tee -a $SUM
echo "LEAN4X4_ISO_DONE $(date)" | tee -a $SUM
