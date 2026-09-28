#!/bin/bash
# Trace-enabled fft cosim (prime=3) on the kept RTL -> dumps a waveform (WDB), then opens the
# XSim GUI viewer on the user's X display. Lets us inspect why node_{2,3,6,7}_7 never fire.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
NFS=/work/shared/users/zsm9/eva_sched8x8_rtl
WD=$NFS/wd; PY=/home/zsm9/miniconda3/envs/allo/bin/python
HDR=$SC/vectors_sii2_fft_8x8.h; INI=$SC/ci_fft_wave.ini
export DISPLAY="${WAVE_DISPLAY:-localhost:10.0}"   # user's X display captured at launch
cd $SC; source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
echo "== trace cosim (prime=3) DISPLAY=$DISPLAY  $(date) =="
# patch header -> prime=3 (non-deadlock; gives the 4/8 we want to inspect)
$PY - "$HDR" 3 <<'PY'
import re,sys; hdr,p=sys.argv[1],int(sys.argv[2]); s=open(hdr).read()
s=re.sub(r'#define VPRIME \d+','#define VPRIME %d'%p,s)
b='static const int32_t PRIMECFG[8][8] = {\n'+',\n'.join('  {'+', '.join([str(p)]*8)+'}' for _ in range(8))+'\n};'
s=re.sub(r'static const int32_t PRIMECFG\[8\]\[8\] = \{.*?\};',b,s,flags=re.S); open(hdr,'w').write(s)
PY
vitis-run --mode hls --cosim --config $INI --work_dir $WD > $NFS/fft_wave.log 2>&1
echo "== cosim rc=$? — locating WDB $(date) =="
WDB=$(find $WD -name "*.wdb" 2>/dev/null | head -1)
echo "  WDB = ${WDB:-NONE}   size=$(du -sh "$WDB" 2>/dev/null | cut -f1)"
if [ -n "$WDB" ]; then
  echo "== opening XSim GUI on $DISPLAY =="
  xsim --gui "$WDB" &
  echo "  GUI launched (pid $!)"
else
  echo "  !! no WDB produced — check trace config in fft_wave.log"
fi
echo "FFT_WAVE_DONE"
