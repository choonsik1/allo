#!/bin/bash
# Copy just the REUSABLE artifacts of a finished run to the shared folder.
# Deliberately excludes Catapult working dirs / xsim.dir / .data vectors, which are
# what made the older eva_*_rtl dirs balloon to 16 GB.
#   usage: scripts/archive_rtl.sh <PRJ-dir> <dest-name> [chip-source.py]
set -e
PRJ="$1"; NAME="$2"; SRC="$3"
DEST="/work/shared/users/zsm9/$NAME"
T=$(find "$PRJ" -type d -name 'top.v*' | head -1)
[ -n "$T" ] || { echo "no Catapult solution dir under $PRJ"; exit 1; }
mkdir -p "$DEST/rtl" "$DEST/reports" "$DEST/src"
cp "$T"/rtl.v "$T"/concat_rtl.v "$T"/rtl.v.dc "$T"/rtl.v.dc.sdc \
   "$T"/rtl.v_order*.txt "$DEST/rtl/" 2>/dev/null || true
cp "$T"/rtl.rpt "$DEST/reports/" 2>/dev/null || true
for L in "$PRJ"/build/catapult.log "$PRJ"/synth.log "$PRJ"/cosim.log; do
  [ -f "$L" ] && gzip -c "$L" > "$DEST/reports/$(basename $L).gz"
done
cp "$PRJ"/kernel.cpp "$PRJ"/run.tcl "$DEST/src/" 2>/dev/null || true
[ -n "$SRC" ] && cp "$SRC" "$DEST/src/"
echo "=== archived to $DEST ==="; du -sh "$DEST"; du -sh "$DEST"/*
echo "=== shared quota ==="; quota -s 2>/dev/null | tail -2
