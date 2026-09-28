#!/bin/bash
# After the ts regression finishes, sweep fft prime = 2,4,6 on the ts chip (L=2000, timestamps).
# Confirms the 4/8 structural plateau is prime-independent + gives arrival cycles per prime.
# Cosim-only on the kept ts RTL. Detached-friendly.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
TS=/work/shared/users/zsm9/eva_ts_8x8_rtl
WD=$TS/wd; PY=/home/zsm9/miniconda3/envs/allo/bin/python
HDR=$SC/vectors_ts_fft_8x8.h; INI=$SC/ci_ts_fft.ini
DEST=$TS/ts_fft_primesweep; mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt; : > $SUM
cd $SC; source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
echo "waiting for ts regression to finish... $(date)" | tee -a $SUM
while ! grep -q TS_COSIM_DONE $TS/ts_cosim.out 2>/dev/null; do sleep 120; done
echo "regression done, sweeping fft prime on ts chip $(date)" | tee -a $SUM
for P in 2 4 6; do
  $PY - "$HDR" "$P" <<'PY'
import re,sys; hdr,p=sys.argv[1],int(sys.argv[2]); s=open(hdr).read()
s=re.sub(r'#define VPRIME \d+','#define VPRIME %d'%p,s)
b='static const int32_t PRIMECFG[8][8] = {\n'+',\n'.join('  {'+', '.join([str(p)]*8)+'}' for _ in range(8))+'\n};'
s=re.sub(r'static const int32_t PRIMECFG\[8\]\[8\] = \{.*?\};',b,s,flags=re.S); open(hdr,'w').write(s)
PY
  echo "==== [fft prime=$P] ts cosim (L=2000) $(date) ====" | tee -a $SUM
  vitis-run --mode hls --cosim --config $INI --work_dir $WD > $DEST/cosim_fft_p$P.log 2>&1
  L=$DEST/cosim_fft_p$P.log
  V=$(awk '/Starting C post checking/{f=1} f&&/ts cosim/{print;exit}' $L)
  DL=$(grep -q "Deadlock detected\|200-742" $L && echo " [DEADLOCK]" || echo "")
  echo "  prime=$P -> ${V:-NORESULT}${DL}" | tee -a $SUM
  awk '/Starting C post checking/{f=1} f&&/row [0-9]:/{print "     "$0}' $L | tee -a $SUM
done
$PY - "$HDR" 3 <<'PY'
import re,sys; hdr=sys.argv[1]; s=open(hdr).read(); s=re.sub(r'#define VPRIME \d+','#define VPRIME 3',s)
b='static const int32_t PRIMECFG[8][8] = {\n'+',\n'.join('  {'+', '.join(['3']*8)+'}' for _ in range(8))+'\n};'
s=re.sub(r'static const int32_t PRIMECFG\[8\]\[8\] = \{.*?\};',b,s,flags=re.S); open(hdr,'w').write(s)
PY
echo "== TS FFT PRIMESWEEP DONE $(date) (header restored to prime=3) ==" | tee -a $SUM
echo "TS_FFT_PRIMESWEEP_DONE"
