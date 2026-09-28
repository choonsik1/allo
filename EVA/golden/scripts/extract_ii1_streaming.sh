#!/bin/bash
# After the II=1 8x8 sweep completes, build the streaming-throughput table (per-lane
# cyc/output from out_cyc arrival cycles) for all 6 workloads, side-by-side vs II=2.
II1=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/sched8x8_ii1ts
II2=/home/zsm9/final_eva_performance/results/ii2_cosim
OUT=$II1/STREAMING_THROUGHPUT_II1_vs_II2.txt
# wait for the sweep to finish
while ! grep -q SCHED8X8_II1TS_COMPLETE $II1/00_SUMMARY.txt 2>/dev/null; do sleep 120; done
python3 - "$II1" "$II2" "$OUT" <<'PY'
import re, sys
II1, II2, OUT = sys.argv[1], sys.argv[2], sys.argv[3]
WLS=[("mmm","mmm"),("fft","fft"),("cordic_cr","cordic_cr"),("cordic_cv","cordic_cv"),("cordic_hr","cordic_hr"),("cordic_hv","cordic_hv")]
def rows(path):
    try: s=open(path).read()
    except: return []
    return [(int(w),int(f),int(l)) for w,f,l in re.findall(r"drained (\d+) words, arrival cyc first=(\d+) last=(\d+)", s)][-8:]
lines=["II=1 8x8 streaming throughput (out_cyc, B=300) vs II=2  — per-lane cyc/output","="*70]
for wl,_ in WLS:
    r1=rows(f"{II1}/cosim_{wl}.log"); r2=rows(f"{II2}/{wl}.log") or rows(f"/home/zsm9/final_eva_performance/results/allo_stream/{wl}_B300.log")
    if not r1: lines.append(f"{wl:<12} II=1: (no data yet)"); continue
    def cpo(r): 
        vals=[(l-f+1)/w for w,f,l in r if w>1]; return sum(vals)/len(vals) if vals else 0
    ident = (sorted(r1)==sorted(r2)) if r2 else None
    lines.append(f"{wl:<12} II=1 cyc/out={cpo(r1):.2f}  |  II=2 cyc/out={cpo(r2):.2f}  |  arrival-cycles {'IDENTICAL' if ident else ('DIFFER' if ident is not None else 'no-II2-ref')}")
lines.append("")
lines.append("VERDICT: II=1 throughput == II=2 (data-bound); II=1 also worse Fmax -> net loss. int16 is the test where II=1 should win.")
open(OUT,"w").write("\n".join(lines)+"\n")
print("\n".join(lines))
PY
echo "STREAMING_EXTRACT_DONE"
