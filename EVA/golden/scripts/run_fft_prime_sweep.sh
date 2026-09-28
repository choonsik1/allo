#!/bin/bash
# FFT prime sweep on the PERSISTENT scheduled II=2 8x8 RTL (cosim-only, NO re-csynth).
# Patches ONLY prime_cfg (VPRIME + PRIMECFG[8][8]) in the fft vectors header, then re-cosims
# the kept RTL. Tests whether raising prime restores the east-drain that fails at prime=1.
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
WD=/work/shared/users/zsm9/eva_sched8x8_rtl/wd
DEST=/work/shared/users/zsm9/eva_sched8x8_rtl/prime_sweep_fft
PY=/home/zsm9/miniconda3/envs/allo/bin/python
HDR=$SC/vectors_sii2_fft_8x8.h
INI=$SC/ci_sii2_fft_8x8.ini
mkdir -p $DEST; SUM=$DEST/00_SWEEP.txt; : > $SUM
cp $HDR $DEST/vectors_fft_orig.h    # backup original (prime=1)
cd $SC
source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
echo "== FFT prime sweep on kept RTL $WD  $(date) ==" | tee -a $SUM

for P in 1 2 3 4 5 6; do
  # patch VPRIME + the whole PRIMECFG[8][8] block to all-P (leaves data vectors untouched)
  $PY - "$HDR" "$P" <<'PYEOF'
import re, sys
hdr, p = sys.argv[1], int(sys.argv[2])
s = open(hdr).read()
s = re.sub(r'#define VPRIME \d+', '#define VPRIME %d' % p, s)
block = ('static const int32_t PRIMECFG[8][8] = {\n'
         + ',\n'.join('  {' + ', '.join([str(p)]*8) + '}' for _ in range(8))
         + '\n};')
s = re.sub(r'static const int32_t PRIMECFG\[8\]\[8\] = \{.*?\};', block, s, flags=re.S)
open(hdr, 'w').write(s)
print('  patched prime=%d (VPRIME=%d, PRIMECFG all=%d)' % (p, p, p))
PYEOF
  echo "==== [prime=$P] cosim fft $(date) ====" | tee -a $SUM
  vitis-run --mode hls --cosim --config $INI --work_dir $WD > $DEST/cosim_fft_p$P.log 2>&1
  # RTL verdict = the one AFTER 'Starting C post checking' (first is the C-sim all-zero artifact)
  RTLV=$(awk '/Starting C post checking/{f=1} f&&/one-bitstream cosim.*rows bit-exact/{print; exit}' $DEST/cosim_fft_p$P.log)
  ROWS=$(echo "$RTLV" | grep -oE "[0-9]+/8 rows")
  PF=$(echo "$RTLV" | grep -oE "PASS|FAIL")
  echo "  prime=$P -> ${PF:-NORESULT} (${ROWS:-no rows}) " | tee -a $SUM
done
# restore original header (prime=1)
cp $DEST/vectors_fft_orig.h $HDR
echo "== SWEEP DONE $(date) ==  (header restored to prime=1)" | tee -a $SUM
echo "FFT_PRIME_SWEEP_DONE"
