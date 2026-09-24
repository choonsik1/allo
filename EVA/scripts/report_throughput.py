#!/usr/bin/env python3
"""Collect 8x8 throughput (cycle counts) from run_golden_vec_systemc.py runs.

    python3 scripts/report_throughput.py [rundir]        # default /scratch/zsm9/thru8

TWO NUMBERS, DIFFERENT THINGS -- never mix them in one column:

  MODEL cycles  `<PRJ>/cycles.txt`, written by the tb-patch in the driver. The emitted
                testbench single-steps a 1 ns clock until `done_sig`, so its loop counter
                is the cycle count of the SystemC/Connections MODEL. It is exact for the
                link handshakes (CONNECTIONS_ACCURATE_SIM carries the same ready/valid)
                but charges ONE tick per node-loop iteration where the RTL charges
                II*iter + depth.
                => ⚠️ IT IS DATATYPE-BLIND. fp16 and int16 elastic both report 44641 at
                8x8/fft. The ALU is not in the model, so csim can never separate the two
                datatypes. Use it for the dataflow schedule, never for a fp16-vs-int16
                claim.

  RTL cycles    `$finish ... at time N NS` from the ncsim transcript, against the 1 ns
                Connections clock => 1 NS == 1 cycle. This is the number to quote.
                It lands in the DRIVER's stdout on a build run (outside PRJ) and in
                `<PRJ>/replay_<wl>.log` on a replay, so both are searched.

Trip counts differ by design and are NOT comparable raw:
  elastic  node loop = `for it in range(BUDGET)`, BUDGET = max(RUN_BUDGET, 6*LANELEN)
  skid     node loop = `for t in range(NSTEP)`,   NSTEP  = VL
Elastic burns a 6x budget with no early exit, so total cycles flatter skid by
construction. Compare clocks/ITERATION for the microarchitecture and clocks/OUTPUT for
the program.
"""
import os, re, sys, glob

RUNDIR = sys.argv[1] if len(sys.argv) > 1 else "/scratch/zsm9/thru8"

BANNER = re.compile(r"chip=(\S+)\s+vec=(\S+)\s+(\d+)x(\d+)\s+VL=(\d+)\s+VPC=(\d+)\s+"
                    r"OUT_IDX=(\d+)\s+PRIME=(\d+)\s+BUDGET=(\S+)\s+MODE=(\S+)")
CLEAN  = re.compile(r"===\s+(\S+)\s+(\w+):\s+(\d+)/(\d+) lanes clean \| (\d+) outputs, (\d+) mismatches")
FINISH = re.compile(r"\$finish[^\n]*?at time\s+([\d,]+)\s*NS")


def rtl_cycles(paths):
    """Last `$finish at time N NS` across the given logs; 1 ns clock => N == cycles."""
    best = None
    for p in paths:
        try:
            txt = open(p, errors="ignore").read()
        except OSError:
            continue
        m = FINISH.findall(txt)
        if m:
            best = int(m[-1].replace(",", ""))
    return best


rows = []
for log in sorted(glob.glob(os.path.join(RUNDIR, "*.log"))):
    txt = open(log, errors="ignore").read()
    b = BANNER.search(txt)
    if not b:
        continue
    chip, vec, M, N, VL, VPC, OUTI, PRIME, BUD, MODE = b.groups()
    wl = vec.split("/")[-1]
    prj = os.path.join(RUNDIR, os.path.basename(log)[: -len(".log")].rsplit(f"_{wl}", 1)[0])
    if not os.path.isdir(prj):                      # log name != project name; recover
        cand = [d for d in glob.glob(os.path.join(RUNDIR, f"{MODE}_*")) if os.path.isdir(d)]
        cand = [d for d in cand if chip.replace("eva_", "") in d]
        prj = cand[0] if cand else prj

    model = None
    cf = os.path.join(prj, "cycles.txt")
    if os.path.exists(cf):
        try: model = int(open(cf).read().strip())
        except ValueError: pass

    rtl = rtl_cycles([log] + sorted(glob.glob(os.path.join(prj, "replay_*.log"))))

    # iterations: elastic reports BUDGET, skid reports None and runs NSTEP == VL
    iters = int(VL) if BUD == "None" else int(BUD)
    c = CLEAN.search(txt)
    outs, mism, lanes_ok, lanes = (int(c.group(5)), int(c.group(6)),
                                   int(c.group(3)), int(c.group(4))) if c else (0, -1, 0, 0)
    rows.append(dict(chip=chip.replace("eva_", ""), wl=wl, mode=MODE, mesh=f"{M}x{N}",
                     iters=iters, model=model, rtl=rtl, outs=outs, mism=mism,
                     ok=(lanes and lanes_ok == lanes)))

if not rows:
    sys.exit(f"no runs found under {RUNDIR}")

hdr = (f"{'chip':<20} {'wl':<10} {'mode':<6} {'mesh':<5} {'iters':>7} "
       f"{'model cyc':>10} {'RTL cyc':>9} {'RTL/iter':>9} {'outs':>6} {'mism':>5} {'ok':>4}")
print(hdr); print("-" * len(hdr))
for r in sorted(rows, key=lambda r: (r["mode"], r["chip"])):
    f = lambda v: "-" if v is None else f"{v:,}"
    ri = "-" if not r["rtl"] else f"{r['rtl']/r['iters']:.3f}"
    print(f"{r['chip']:<20} {r['wl']:<10} {r['mode']:<6} {r['mesh']:<5} {r['iters']:>7,} "
          f"{f(r['model']):>10} {f(r['rtl']):>9} {ri:>9} {r['outs']:>6} "
          f"{r['mism']:>5} {'PASS' if r['ok'] else 'FAIL':>4}")

print("\n⚠️ model cycles are DATATYPE-BLIND (no ALU in the SystemC model) -- fp16 and int16")
print("   of the same family report the same count. Quote RTL for any datatype claim.")
print("⚠️ elastic iters = BUDGET (6*LANELEN, no early exit); skid iters = NSTEP. Raw totals")
print("   are not comparable across families -- use RTL/iter, or cycles per output.")
