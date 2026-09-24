#!/usr/bin/env python3
"""Post-Assignment component breakdown + frequency + node-loop depth/II, one row per project.

    scripts/report_components.py <project-dir> [...]

THREE report traps this encodes (each one produced a wrong number before):
 1. `Area Scores` has THREE columns; Post-Assignment is the LAST -- reading col 1 is ~10-20% low.
 2. rtl.rpt has TWO timing sections; only "Timing Report / Critical Path" is the datapath
    delay. The "Register Input/Output Slack" block is INTERFACE paths.
 3. In cycle.rpt's Loops table, II is the `Init` column. `Throughput Cycles` (Loop Execution
    Profile) is a static stall estimate and `Total Cycles` is loop+nested -- neither is II.
Also: DataPath `REG` != `Total Reg` (the latter folds in FSM-REG, ~21 units). We report DataPath.
"""
import sys, os, re, glob

def find(d, n):
    if os.path.isfile(d): return d if os.path.basename(d) == n else None
    g = glob.glob(os.path.join(d, "**", n), recursive=True)
    return g[0] if g else None

def last_num(line):
    for t in reversed(line.split()):
        if re.fullmatch(r"[0-9.]+", t): return float(t)
    return None

def parse(proj):
    rtl, cyc = find(proj, "rtl.rpt"), find(proj, "cycle.rpt")
    if not rtl: return None
    L = open(rtl, errors="ignore").read().splitlines()
    comp, total, mx = {}, None, 0.0
    inpath = False
    for ln in L:
        if total is None and ln.strip().startswith("Total Area Score:"): total = last_num(ln)
        m = re.match(r"\s{4}(MUX|FUNC|LOGIC|REG):", ln)
        if m and m.group(1) not in comp: comp[m.group(1)] = last_num(ln)
        if ln.startswith("  Critical Path"): inpath = True
        elif inpath and "Max Delay:" in ln:
            mx = max(mx, float(ln.split()[2])); inpath = False
    depth = ii = "-"
    if cyc:
        C = open(cyc, errors="ignore").read().splitlines()
        try:
            h = next(i for i, l in enumerate(C) if "C-Steps" in l and "Init" in l)
        except StopIteration:
            h = None
        if h is not None:
            for ln in C[h + 2:]:
                if not ln.strip(): break
                f = ln.split()
                # steady-state node loop: `while` (elastic) or `...:it` (others)
                if len(f) >= 3 and (f[1] == "while" or f[1].endswith(":it") or f[1] == "it"):
                    depth, ii = f[3], f[-1]      # Comments is blank -> Init is the last field
                    break
    return dict(name=os.path.basename(os.path.normpath(proj)), mhz=(1000 / mx if mx else 0),
                depth=depth, ii=ii, total=total, **comp)

rows = [r for r in (parse(p) for p in sys.argv[1:]) if r]
hdr = f"{'chip':<32}{'MHz':>6}{'depth':>7}{'II':>4}{'REG':>10}{'FUNC':>10}{'MUX':>10}{'LOGIC':>10}{'TOTAL':>11}"
print(hdr); print("-" * len(hdr))
for r in rows:
    print(f"{r['name']:<32}{r['mhz']:>6.0f}{r['depth']:>7}{r['ii']:>4}"
          f"{r.get('REG',0):>10.1f}{r.get('FUNC',0):>10.1f}{r.get('MUX',0):>10.1f}"
          f"{r.get('LOGIC',0):>10.1f}{r['total']:>11.1f}")
