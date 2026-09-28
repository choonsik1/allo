#!/bin/bash
# Build the TIMESTAMPED final chip (eva_sb_syscredit_rtprime_ts = rtprime + out_cyc) at 8x8, L=2000:
# NOSCHED codegen -> inject II=2 pragmas -> PERSISTENT csynth on NFS. Kernel is workload-independent;
# vectors + ts tb come later for cosim. Detached, survives /exit.
set -o pipefail
PRIME=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
TS=/work/shared/users/zsm9/eva_ts_8x8_rtl
PY=/home/zsm9/miniconda3/envs/allo/bin/python
mkdir -p $TS/tmp; export TMPDIR=$TS/tmp
NOSCHED=$TS/prj_ts_nosched; INJ=$TS/kernel_ts_sched.cpp; WD=$TS/wd
cd $PRIME
echo "== [0] codegen NOSCHED ts kernel 8x8 L=2000 $(date) =="
LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel PYTHONPATH=/home/zsm9/allo_sup:$PRIME $PY - <<PYEOF
import os,sys
sys.path.insert(0,"$PRIME")
import eva_sb_syscredit_rtprime_ts as chip
sys.modules["eva"]=chip
from allo.ir.types import float16
chip.M=chip.N=8; chip.IRF_DEPTH=8; chip.DATADRIVEN=1
chip.NSTEP=chip.LANELEN=2000; chip.PRIME_TOKENS=6
print("  building 8x8 NOSCHED L=2000 (out_cyc timestamps)...",flush=True)
s=chip.get_scheduled_eva(float16, pipeline_node=False, partition_rf=False)
import shutil; shutil.rmtree("$NOSCHED",ignore_errors=True)
s.build(target="vhls", mode="csyn", project="$NOSCHED")
k="$NOSCHED/kernel.cpp"; src="#define ALLOW_EMPTY_HLS_STREAM_READS 1\n"+open(k).read()
open(k,"w").write(src)
import re
print("  kernel lines:",src.count(chr(10)),"top args:",len(re.findall(r'v\d+\[\d+\]\[\d+\]',src.split('void top')[1][:6000])) if 'void top' in src else '?')
PYEOF
[ -f $NOSCHED/kernel.cpp ] || { echo "!! codegen FAILED"; exit 1; }

echo "== [1] inject II=2 pragmas $(date) =="
$PY $PRIME/inject_pragmas_ii2.py $NOSCHED/kernel.cpp $INJ 2
echo "  injected: pipeline=$(grep -c 'HLS pipeline' $INJ) depfalse=$(grep -c dependent=false $INJ) partition=$(grep -c 'HLS array_partition' $INJ)"

echo "== [2] make ini + persistent csynth (~13h) $(date) =="
cat > $TS/ci_ts_8x8.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$INJ
syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS
syn.compile.pipeline_loops=0
INI
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
rm -rf $WD; mkdir -p $WD
v++ -c --mode hls --config $TS/ci_ts_8x8.ini --work_dir $WD > $TS/csynth.log 2>&1
echo "  csynth rc=$?  node II: $(grep -hE 'l_S_t_1_t \|' $WD/hls/syn/report/*_csynth.rpt 2>/dev/null | head -1 | tr -s ' ')"
echo "  200-880 (II=2 honored): $(grep -c 200-880 $TS/csynth.log)   nodes: $(ls $WD/hls/syn/report/node_*_csynth.rpt 2>/dev/null | wc -l)"
echo "== TS 8x8 CSYNTH DONE $(date) ==  RTL at $WD"
echo "BUILD_TS_8X8_DONE"
