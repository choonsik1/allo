#!/usr/bin/env python3
"""
profile_knobs.py -- how much of the futex/scheduling cost is recoverable with
libomp RUNTIME KNOBS alone (no code change)? Each knob set is read by libomp
once at load, so every setting runs in a fresh process (fresh build). Swept on
oversubscribed configs where the scheduling cost dominates.

Knobs:
  baseline           -- nothing set (current behavior)
  wait=passive       -- OMP_WAIT_POLICY=passive  (threads sleep at barriers/locks)
  wait=active        -- OMP_WAIT_POLICY=active   (threads spin at barriers/locks)
  bind=close+cores   -- OMP_PROC_BIND=close, OMP_PLACES=cores   (pin, pack)
  bind=spread+cores  -- OMP_PROC_BIND=spread, OMP_PLACES=cores  (pin, scatter)
  passive+bind=close -- combo
"""
import os, sys, json, subprocess, time

HERE = os.path.dirname(os.path.abspath(__file__))
WORKER = os.path.join(HERE, "profile_worker.py")
CONFIGS = [(8, 8), (12, 8)]                 # 100 PE (1.56x), 196 PE (3.06x) oversub
NRUNS = int(os.environ.get("NRUNS", "20"))
KNOB_VARS = ["OMP_WAIT_POLICY", "OMP_PROC_BIND", "OMP_PLACES", "KMP_BLOCKTIME"]

KNOBS = [
    ("baseline",           {}),
    ("wait=passive",       {"OMP_WAIT_POLICY": "passive"}),
    ("wait=active",        {"OMP_WAIT_POLICY": "active"}),
    ("bind=close+cores",   {"OMP_PROC_BIND": "close",  "OMP_PLACES": "cores"}),
    ("bind=spread+cores",  {"OMP_PROC_BIND": "spread", "OMP_PLACES": "cores"}),
    ("passive+bind=close", {"OMP_WAIT_POLICY": "passive",
                            "OMP_PROC_BIND": "close", "OMP_PLACES": "cores"}),
]


def run(side, depth, knob_env):
    pe = (side + 2) * (side + 2)
    env = dict(os.environ)
    for v in KNOB_VARS:              # clear any leakage between settings
        env.pop(v, None)
    env.update(knob_env)
    env["OMP_NUM_THREADS"] = str(pe)
    p = subprocess.run([sys.executable, WORKER, str(side), str(depth), str(NRUNS)],
                       env=env, capture_output=True, text=True, timeout=900)
    line = [l for l in p.stdout.splitlines() if l.strip().startswith("{")]
    if not line:
        return None, p.stderr
    return json.loads(line[-1]), None


all_rows = {}
for side, depth in CONFIGS:
    cfg = f"{side}x{side}x{depth}"
    pe = (side + 2) * (side + 2)
    print(f"\n### config {cfg}  PE={pe}  oversub={pe/os.cpu_count():.2f}x  (NRUNS={NRUNS})")
    rows = []
    for name, knob in KNOBS:
        try:
            rec, err = run(side, depth, knob)
        except subprocess.TimeoutExpired:
            print(f"  {name:20s} TIMEOUT"); continue
        if rec is None:
            print(f"  {name:20s} FAILED: {(err or '').strip().splitlines()[-1:]}"); continue
        rec["knob"] = name
        rows.append(rec)
        ok = "PASS" if rec["max_abs_err"] < 1e-3 else "CHECK"
        print(f"  {name:20s} sim={rec['sim_ms_mean']:>8}±{rec['sim_ms_sd']:<7}ms "
              f"sys_frac={rec['sys_frac']:<6} busy={rec['cpu_busy_cores']:<6}c "
              f"ivcsw/sim={rec['nivcsw_per_sim']:<12} {ok}", flush=True)
    all_rows[cfg] = rows

# ---- per-config comparison table (vs baseline) ----
cols = [("knob", "knob", 20), ("sim_ms_mean", "sim ms", 9), ("sim_ms_sd", "±sd", 9),
        ("sys_frac", "sys_frac", 9), ("cpu_busy_cores", "busycore", 9),
        ("nivcsw_per_sim", "ivcsw/sim", 13), ("cpu_util_frac", "util", 7)]
for cfg, rows in all_rows.items():
    base = next((r for r in rows if r["knob"] == "baseline"), None)
    print("\n" + "=" * 96)
    print(f"config {cfg}   (speedup vs baseline in [])")
    print("".join(h.ljust(w) for _, h, w in cols))
    print("-" * 96)
    for r in rows:
        spd = ""
        if base and r["sim_ms_mean"]:
            spd = f"  [{base['sim_ms_mean']/r['sim_ms_mean']:.2f}x]"
        print("".join(str(r.get(k, "")).ljust(w) for k, _, w in cols) + spd)
    print("=" * 96)

json.dump(all_rows, open(os.path.join(HERE, "profile_knobs_results.json"), "w"), indent=2)
print(f"\nraw -> {os.path.join(HERE, 'profile_knobs_results.json')}")
