#!/bin/bash
# Pull the numbers that actually belong in the paper out of a Catapult rtl.rpt.
#
# TWO TRAPS this script exists to prevent, both of which produced wrong numbers before:
#  1. `Area Scores` has THREE columns -- Post-Scheduling / Post-DP&FSM / Post-Assignment.
#     Post-Assignment (the LAST one) is the real number; reading column 1 overstates it.
#  2. `rtl.rpt` has TWO timing sections. "Timing Report / Critical Path" is the real
#     datapath delay. "Register Input and Register-to-Output Slack" is INTERFACE paths --
#     quoting it as the critical path is wrong (it once produced a bogus -0.3388).
#
#   scripts/report_area.sh <project-dir-or-rtl.rpt> [...]
for arg in "$@"; do
  if [ -d "$arg" ]; then R=$(find "$arg" -name rtl.rpt | head -1); else R="$arg"; fi
  if [ ! -f "$R" ]; then echo "$arg: no rtl.rpt"; continue; fi
  echo "=== $R"
  nb=$(grep -c "Total Area Score:" "$R")
  # last occurrence = top-level rollup; 3rd numeric column = Post-Assignment
  grep "Total Area Score:" "$R" | tail -1 | awk -v n="$nb" \
    '{printf "  Area Score (Post-Assign) : %12s   [%s block(s) in report]\n", $NF, n}'
  grep "TOTAL AREA (After Assignment)" "$R" | tail -1 | awk \
    '{printf "  TOTAL AREA               : %12s\n", $5}'
  # worst critical path across all blocks = the one that decides whether timing closes
  awk '/^  Critical Path/{f=1} f&&/Max Delay:/{d=$3;f=0; if(d+0>m){m=d+0}} END{
        if(m) printf "  Max delay (worst)        : %12.4f ns   -> %.0f MHz\n", m, 1000/m}' "$R"
  awk '/^  Critical Path/{f=1} f&&/Slack:/{s=$2+0;f=0; if(!init||s<w){w=s;init=1}} END{
        if(init) printf "  Slack (worst)            : %12.4f ns   %s\n", w, (w>=0?"MEETS":"MISSES")}' "$R"
done
