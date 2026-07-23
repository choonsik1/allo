#!/usr/bin/env python3
"""
profile_heavy_driver.py -- sweep compute intensity (FLOP per reduction step) at a
FIXED oversubscribed systolic config, under active vs passive OMP_WAIT_POLICY.

Answers:
  (1) Does "compute negligible" break down as FLOP rises?  (watch sys_frac fall,
      busy_cores rise toward real work, sim_ms grow with FLOP)
  (2) Does the passive advantage shrink when PEs actually compute?  (watch the
      passive/active speedup approach 1.0)

Correctness: kernel is deterministic; each worker asserts max_dev==0 across its
runs, and we cross-check that active & passive produce the SAME checksum.
"""
import os, sys, json, subprocess

HERE = os.path.dirname(os.path.abspath(__file__))
WORKER = os.path.join(HERE, "profile_worker_heavy.py")
SIDE, DEPTH = 10, 8                       # 144 PE, 2.25x oversub on 64 cores
PE = (SIDE + 2) * (SIDE + 2)
INTERIOR = SIDE * SIDE                     # MAC PEs
FLOP_LIST = [0, 8192, 65536, 262144, 1048576]
POLICIES = ["active", "passive"]
NRUNS = int(os.environ.get("NRUNS", "15"))


def run(flop, policy):
    env = dict(os.environ)
    for v in ["OMP_WAIT_POLICY", "KMP_BLOCKTIME", "OMP_PROC_BIND", "OMP_PLACES"]:
        env.pop(v, None)
    env["OMP_WAIT_POLICY"] = policy        # explicit -> code default never fires
    env["OMP_NUM_THREADS"] = str(PE)
    p = subprocess.run([sys.executable, WORKER, str(SIDE), str(DEPTH), str(flop), str(NRUNS)],
                       env=env, capture_output=True, text=True, timeout=1200)
    line = [l for l in p.stdout.splitlines() if l.strip().startswith("{")]
    if not line:
        print(f"  FAILED flop={flop} {policy}: {p.stderr.strip().splitlines()[-3:]}")
        return None
    return json.loads(line[-1])


print(f"config {SIDE}x{SIDE}x{DEPTH}  PE={PE}  oversub={PE/os.cpu_count():.2f}x  "
      f"interior MAC PEs={INTERIOR}  total madds = {INTERIOR}*{DEPTH}*FLOP  (NRUNS={NRUNS})\n")

rows = []
for flop in FLOP_LIST:
    rec = {"flop": flop, "madds": INTERIOR * DEPTH * flop}
    ck = {}
    for pol in POLICIES:
        r = run(flop, pol)
        if r is None:
            continue
        rec[pol] = r
        ck[pol] = r["checksum"]
        print(f"  flop={flop:>8}  {pol:7s}  sim={r['sim_ms_mean']:>8}±{r['sim_ms_sd']:<6}ms "
              f"sys_frac={r['sys_frac']:<5} busy={r['cpu_busy_cores']:<6}c "
              f"ivcsw/sim={r['nivcsw_per_sim']:<10} dev={r['max_dev']}", flush=True)
    rec["checksum_match"] = (len(set(ck.values())) == 1) if len(ck) == len(POLICIES) else None
    rows.append(rec)
    print(f"    -> checksum match across policies: {rec['checksum_match']}\n", flush=True)

# ---- summary: the two questions ----
print("=" * 104)
print(f"{'FLOP':>9} {'~madds':>11} | {'active ms':>10} {'passive ms':>11} {'passive/active':>15} | "
      f"{'act sys':>8} {'pas sys':>8} | {'act busy':>9} {'pas busy':>9} | ck")
print("-" * 104)
for r in rows:
    a, p = r.get("active"), r.get("passive")
    if not (a and p):
        continue
    spd = a["sim_ms_mean"] / p["sim_ms_mean"] if p["sim_ms_mean"] else float("nan")
    print(f"{r['flop']:>9} {r['madds']:>11} | {a['sim_ms_mean']:>10} {p['sim_ms_mean']:>11} "
          f"{spd:>14.2f}x | {a['sys_frac']:>8} {p['sys_frac']:>8} | "
          f"{a['cpu_busy_cores']:>9} {p['cpu_busy_cores']:>9} | {'ok' if r['checksum_match'] else 'DIFF'}")
print("=" * 104)
print("Read: as FLOP rises, sys_frac should fall & busy_cores rise (compute stops being")
print("negligible), and passive/active should approach 1.0 (passive helps most when sync-bound).")

json.dump(rows, open(os.path.join(HERE, "profile_heavy_results.json"), "w"), indent=2)
print(f"\nraw -> {os.path.join(HERE, 'profile_heavy_results.json')}")
