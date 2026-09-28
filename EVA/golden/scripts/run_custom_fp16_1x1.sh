#!/bin/bash
# Custom-fp16 1x1: emit SCHED kernel -> patch (half->float16, kill union reinterprets,
# strip bind_op/dep-false) -> csynth (II?) -> impl (Fmax?). Skips cosim (needs TB patch);
# does it AFTER, only if Fmax clears the ~116 MHz break-even.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb ; CFP16=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/custom_fp16 ; DEST=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/custom_fp16/run_1x1
PRIMEDIR=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime
WD=/work/shared/users/zsm9/custom_fp16_1x1_wd
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
export PYTHONPATH=/home/zsm9/allo:$PRIMEDIR LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel
PY=/home/zsm9/miniconda3/envs/allo/bin/python
cd $SC ; SUM=$DEST/00_SUMMARY.txt ; : > $SUM
echo "== custom_fp16 1x1 START $(date) ==" | tee $SUM

# [1] emit SCHED 1x1 (rtprime_ts, pipeline II=1 + partition + dep-false + bind_op)
EXPTAG=_cfp16 FPLAT=2 DEPFALSE=1 MULIMPL=maxdsp CHIP=eva_sb_syscredit_rtprime_ts SZ=1 LFORCE=800 BATCH=40 PRIME=6 NOSCHED=0 \
  $PY build_val_sched_ts_prime_exp.py > $DEST/build.log 2>&1
BASEK=$(grep -E "^PRJ=" $DEST/build.log|tail -1|cut -d= -f2)/kernel.cpp
[ -f "$BASEK" ] || { echo "EMIT FAIL"; tail -10 $DEST/build.log|tee -a $SUM; exit 1; }
echo "  emitted $(wc -l <$BASEK) lines" | tee -a $SUM

# [2] PATCH kernel -> custom_fp16
KP=$DEST/kernel_cfp16.cpp
$PY - "$BASEK" "$KP" <<'PYEOF'
import re,sys
src=open(sys.argv[1]).read()
hdr='#include "custom_fp16.h"\n'
src = (src[:src.index(chr(10))+1]+hdr+src[src.index(chr(10))+1:]) if src.startswith('#define') else hdr+src
pat=re.compile(r'union \{ (uint16_t|half) from; (uint16_t|half) to;\} (\w+) = \{\};\s*\n\s*\3\.from = ([\w\.]+);\s*\n\s*(\w+) = \3\.to;')
def rep(m):
    ft,tt,_,s,dst=m.groups()
    return f'{dst} = float16(ap_uint<16>({s}));' if tt=='half' else f'{dst} = ({s}).to_bits();'
src,nc=pat.subn(rep,src)
src=re.sub(r'\bhalf\b','float16',src)
src,nb=re.subn(r'\n[ \t]*#pragma HLS bind_op[^\n]*','',src)
src,nd=re.subn(r'\n[ \t]*#pragma HLS dependence[^\n]*dependent=false[^\n]*','',src)
open(sys.argv[2],'w').write(src)
print(f"PATCH unions={nc} bind_op_removed={nb} depfalse_removed={nd} leftover_unions={src.count('union {')}")
PYEOF
grep "PATCH" $DEST/build.log 2>/dev/null; tail -1 $DEST/build.log | grep PATCH | tee -a $SUM
$PY - "$BASEK" "$KP" 2>&1 | grep PATCH | tee -a $SUM || true
echo "  patched leftover unions: $(grep -c 'union {' $KP)" | tee -a $SUM

# [3] ini
cat > $DEST/ci_cfp16.ini <<INI
part=xczu7ev-ffvc1156-2-e

[hls]
flow_target=vivado
clock=3.33
syn.top=top
syn.file=$KP
syn.cflags=-I$CFP16 -DALLOW_EMPTY_HLS_STREAM_READS
INI

# [4] csynth
rm -rf $WD; mkdir -p $WD
echo "  csynth $(date)" | tee -a $SUM
v++ -c --mode hls --config $DEST/ci_cfp16.ini --work_dir $WD > $DEST/csynth.log 2>&1
if [ ! -d $WD/hls/syn ]; then echo "  CSYNTH FAIL:" | tee -a $SUM; tail -25 $DEST/csynth.log|tee -a $SUM; exit 2; fi
echo "  Final-II: $(grep -hoE 'Final II = [0-9]+' $DEST/csynth.log|sort|uniq -c|tr '\n' ' ')  200-880=$(grep -c 200-880 $DEST/csynth.log)" | tee -a $SUM
echo "  vendor fp cores (want NONE): $(grep -rhoE '(hmul|hadd|hsub)_16ns[^ \"]*' $WD/hls/syn/report/*.rpt 2>/dev/null|sort -u|tr '\n' ' ')[none=good]" | tee -a $SUM
echo "  csynth est clock: $(grep -A2 'Target | Estimated' $WD/hls/syn/report/csynth.rpt 2>/dev/null|grep ap_clk|head -1)" | tee -a $SUM

# [5] impl (Fmax)
echo "  impl $(date)" | tee -a $SUM
vitis-run --mode hls --impl --config $DEST/ci_cfp16.ini --work_dir $WD > $DEST/impl.log 2>&1
TR=$(find $WD -path "*impl*" -name "*timing_summary*routed*.rpt"|head -1)
WNS=$(grep -iE "Worst Slack" "$TR" 2>/dev/null|grep -oE '\-?[0-9]+\.[0-9]+ns'|head -1)
echo "  routed WNS=$WNS  -> period = 3.33 - WNS ; Fmax = 1000/period  (break-even ~116 MHz)" | tee -a $SUM
echo "CUSTOM_FP16_1x1_DONE $(date)" | tee -a $SUM
