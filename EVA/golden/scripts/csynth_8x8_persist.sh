#!/bin/bash
# Re-csynth the SCHEDULED II=2 8x8 rtprime kernel ONCE and KEEP the RTL on persistent NFS
# (/work/shared/users, 9.6TB free) so every future prime-sweep cosim reuses it (no re-csynth).
# Then one mmm cosim to PROVE the kept RTL is cosim-reusable. Kernel is workload-independent.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
NFS=/work/shared/users/zsm9/eva_sched8x8_rtl
WD=$NFS/wd                        # <-- the PERSISTENT RTL work_dir (kept forever)
mkdir -p $WD $NFS/tmp
export TMPDIR=$NFS/tmp            # keep v++ scratch off /tmp (int16 P&R is using /tmp)
cd $SC
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
echo "using $(which v++)  WD=$WD  $(date)"
echo "kernel: $(grep -c 'HLS pipeline' prj_sii2_shared/kernel.cpp) pipelines, $(grep -c dependent=false prj_sii2_shared/kernel.cpp) dep-false (scheduled II=2)"

echo "==== [1] csynth ONCE -> persistent RTL (64 nodes, ~11h) $(date) ===="
rm -rf $WD; mkdir -p $WD
v++ -c --mode hls --config $SC/ci_sii2_mmm_8x8.ini --work_dir $WD > $NFS/csynth.log 2>&1
echo "  csynth rc=$?  node II: $(grep -hE 'l_S_t_1_t \|' $WD/hls/syn/report/*_csynth.rpt 2>/dev/null | head -1 | tr -s ' ')"
echo "  200-880 (expect >0 = II=2 honored): $(grep -c 200-880 $NFS/csynth.log)"
echo "  RTL .v files: $(find $WD -name '*.v' | wc -l)   WD size: $(du -sh $WD | cut -f1)"

echo "==== [2] validate: mmm cosim on the KEPT RTL (expect PASS 8/8) $(date) ===="
vitis-run --mode hls --cosim --config $SC/ci_sii2_mmm_8x8.ini --work_dir $WD > $NFS/cosim_mmm_validate.log 2>&1
grep -nE "Starting C post checking|rows bit-exact|PASS|FAIL|co-simulation finished" $NFS/cosim_mmm_validate.log | tail -6

echo "==== DONE $(date) ====  RTL kept at: $WD"
echo "CSYNTH_8X8_PERSIST_COMPLETE"