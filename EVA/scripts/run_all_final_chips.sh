#!/bin/bash
# Re-run the four FINAL verification chips through the SystemC backend + Catapult.
#
#   scripts/run_all_final_chips.sh csyn1     # area/timing @ 1 PE   (~10 min/chip)
#   scripts/run_all_final_chips.sh csyn8     # area/timing @ 8x8    (~2-6 h/chip)
#   scripts/run_all_final_chips.sh csim      # golden vectors, 6 workloads, no Catapult
#   scripts/run_all_final_chips.sh cosim     # golden vectors in RTL  (~5 h/chip, fft only)
#   CHIPS="fp16_elastic int16_skid" scripts/run_all_final_chips.sh csim   # subset
#
# Sources: designs/from_verification/eva_<chip>.py, copied 2026-08-21 from
#          /work/shared/users/zsm9/verification/<chip>/  (Aug-19 emitter revision).
set -u
ROOT=/home/zsm9/final_eva_systemc
PY=${PY:-/home/zsm9/miniconda3/envs/allo/bin/python}
OUT=${OUT:-/scratch/zsm9/final_chips}
CHIPS=${CHIPS:-"fp16_elastic int16_elastic fp16_skid int16_skid"}
# Workload names differ by chip: int16_elastic's PLAIN names are stale fp16 vectors,
# its real int16 set carries the _i16 suffix. int16_skid uses the plain names.
WLS_DEFAULT="fft mmm cordic_cr cordic_cv cordic_hr cordic_hv"
WLS_I16="fft_i16 mmm_i16 cordic_cr_i16 cordic_cv_i16 cordic_hr_i16 cordic_hv_i16"
CLK=${CLK:-2.0}
MODE_=${1:?usage: csyn1 | csyn8 | csim | cosim}
mkdir -p "$OUT"; cd "$ROOT"

dt() { case "$1" in int16*) echo int16;; *) echo fp16;; esac; }

for c in $CHIPS; do
  D=$(dt "$c")
  case "$MODE_" in
    csyn1|csyn8)
      M=1; [ "$MODE_" = csyn8 ] && M=8
      P="$OUT/csyn_${M}x${M}_${c}"; L="$OUT/csyn_${M}x${M}_${c}.log"
      echo ">>> csyn $c  ${M}x${M}  CLK=$CLK -> $L"
      CHIP=eva_$c DTYPE=$D MESH=$M NSTEP=${NSTEP:-215} CLK=$CLK PRJ="$P" \
        $PY scripts/csyn_probe.py > "$L" 2>&1
      echo "    rc=$?"; scripts/report_area.sh "$P" 2>/dev/null
      # archive IMMEDIATELY -- /scratch is reused by other projects and has eaten
      # finished results before (the Aug-19 8x8 cosims).
      scripts/archive_run.sh "$P" "eva_$c" "csyn_${M}x${M}" 2>/dev/null
      ;;
    csim|cosim)
      # cosim is ~5 h per BUILD, so only the first workload builds; the rest REPLAY
      # on that bitstream (~1 min each) -- EVA is programmable, same chip, new program.
      P="$OUT/${MODE_}_${c}"; first=1
      V=${c%_nb}
      case "$V" in int16_elastic) WL_SET="$WLS_I16";; *) WL_SET="$WLS_DEFAULT";; esac
      [ -n "${WLS:-}" ] && WL_SET="$WLS"
      for w in $WL_SET; do
        [ -d "/work/shared/users/zsm9/verification/vectors/Allo/$V/$w" ] || \
          { echo "    skip $w (no vectors for $V)"; continue; }
        R=0; [ "$MODE_" = cosim ] && [ $first -eq 0 ] && R=1
        L="$OUT/${MODE_}_${c}_${w}.log"
        echo ">>> $MODE_ $c/$w  (REPLAY=$R) -> $L"
        CHIP=eva_$c VEC=$V WL=$w DTYPE=$D MODE=$MODE_ REPLAY=$R PRJ="$P" \
          $PY scripts/run_golden_vec_systemc.py > "$L" 2>&1
        echo "    rc=$?  $(grep -a '=== .*lanes clean' "$L" | tail -1)"
        echo "        $(grep -a '=== CYCLES' "$L" | tail -1)"
        [ "$MODE_" = cosim ] && scripts/archive_run.sh "$P" "eva_$c" "cosim_${w}" 2>/dev/null
        first=0
      done
      ;;
    *) echo "unknown mode $MODE_"; exit 2;;
  esac
done
