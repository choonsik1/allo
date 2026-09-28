#!/bin/bash
set -o pipefail
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
NFS=/work/shared/users/zsm9/eva_sched8x8_rtl
WD=$NFS/wd; PY=/home/zsm9/miniconda3/envs/allo/bin/python
DEST=$NFS/cordic_cosim; mkdir -p $DEST; SUM=$DEST/00_SUMMARY.txt; : > $SUM
cd $SC; source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
echo "== cordic cosim on kept scheduled II=2 RTL, prime=3 $(date) ==" | tee -a $SUM
for W in cordic_cr cordic_cv cordic_hr cordic_hv; do
  HDR=$SC/vectors_sii2_${W}_8x8.h; INI=$SC/ci_sii2_${W}_8x8.ini
  $PY - "$HDR" 3 <<'PY'
import re,sys; hdr,p=sys.argv[1],int(sys.argv[2]); s=open(hdr).read()
s=re.sub(r'#define VPRIME \d+','#define VPRIME %d'%p,s)
b='static const int32_t PRIMECFG[8][8] = {\n'+',\n'.join('  {'+', '.join([str(p)]*8)+'}' for _ in range(8))+'\n};'
s=re.sub(r'static const int32_t PRIMECFG\[8\]\[8\] = \{.*?\};',b,s,flags=re.S); open(hdr,'w').write(s)
PY
  echo "==== [$W prime=3] cosim $(date) ====" | tee -a $SUM
  vitis-run --mode hls --cosim --config $INI --work_dir $WD > $DEST/cosim_$W.log 2>&1
  L=$DEST/cosim_$W.log
  rows=$(awk '/post checking/{f=1} f&&/rows bit-exact/{print;exit}' $L | grep -oE '[0-9]+/8 rows')
  if grep -q "Deadlock detected\|200-742" $L; then v="DEADLOCK";
  elif grep -q "212-1000 \*\*\* C/RTL co-simulation finished: PASS" $L; then v="PASS ${rows}";
  elif [ -n "$rows" ]; then v="${rows} (FAIL, no deadlock)";
  else v="NORESULT"; fi
  echo "  $W -> $v" | tee -a $SUM
done
echo "== CORDIC COSIM DONE $(date) ==" | tee -a $SUM
echo "CORDIC_COSIM_DONE"
