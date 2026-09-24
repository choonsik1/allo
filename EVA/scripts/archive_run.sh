#!/bin/bash
# Archive a finished run into a DATED, CHIP-NAMED folder under the shared area.
#
#   scripts/archive_run.sh <PRJ-dir> <chip> <tag>      e.g. ... eva_fp16_skid csyn_1x1
#   DATE=2026-08-21 scripts/archive_run.sh ...         (override the date)
#
# -> /work/shared/users/zsm9/eva_results/<DATE>/<chip>__<tag>/{rtl,reports,src}
#
# WHY: runs used to live only in /scratch, which other projects reuse. The Aug-19 v3.0 and
# elastic 8x8 cosim results were LOST that way -- the README still lists them as "running"
# and their scratch dirs are gone. Archive as soon as a run finishes, not at the end.
set -u
PRJ="${1:?usage: archive_run.sh <PRJ> <chip> <tag>}"; CHIP="${2:?}"; TAG="${3:?}"
DATE="${DATE:-$(date +%F)}"
DEST="/work/shared/users/zsm9/eva_results/$DATE/${CHIP}__${TAG}"
[ -d "$PRJ" ] || { echo "no such project dir: $PRJ"; exit 1; }
mkdir -p "$DEST/rtl" "$DEST/reports" "$DEST/src"

# Catapult solution dir: <something>.v<N>. Do not assume it is called top.v1 -- these
# chips name the top after the kernel.
T=$(find "$PRJ" -maxdepth 4 -type d -name '*.v[0-9]*' 2>/dev/null | head -1)
if [ -n "$T" ]; then
  cp "$T"/rtl.v "$T"/concat_rtl.v "$T"/rtl.v.dc "$T"/rtl.v.dc.sdc "$DEST/rtl/" 2>/dev/null
  cp "$T"/rtl.rpt "$T"/cycle.rpt "$T"/*.rpt "$DEST/reports/" 2>/dev/null
else
  echo "  (warning: no Catapult solution dir found -- reports may be incomplete)"
fi
find "$PRJ" -maxdepth 3 -name 'rtl.rpt' -o -maxdepth 3 -name 'cycle.rpt' 2>/dev/null \
  | while read -r f; do cp -n "$f" "$DEST/reports/" 2>/dev/null; done
for L in "$PRJ"/build/catapult.log "$PRJ"/synth.log "$PRJ"/cosim.log "$PRJ"/../$(basename "$PRJ").log; do
  [ -f "$L" ] && gzip -c "$L" > "$DEST/reports/$(basename "$L").gz"
done
cp "$PRJ"/kernel.cpp "$PRJ"/run.tcl "$DEST/src/" 2>/dev/null
for S in designs/from_verification/${CHIP}.py chip/${CHIP}.py; do
  [ -f "$S" ] && cp "$S" "$DEST/src/"
done
# a one-page summary so the folder is readable without re-parsing rtl.rpt
{ echo "chip=$CHIP  tag=$TAG  date=$DATE"; echo "source_prj=$PRJ"; echo
  scripts/report_area.sh "$DEST" 2>/dev/null; } > "$DEST/SUMMARY.txt"
cat "$DEST/SUMMARY.txt"
echo "=== archived -> $DEST  ($(du -sh "$DEST" | cut -f1)) ==="
