#!/usr/bin/env python3
"""
profile_driver.py -- sweep systolic configs, one subprocess per config
(OMP_NUM_THREADS = PE count, set before libomp loads), collect the
profile_worker.py metrics, and print a table + save raw JSON.

Run inside the `allo` env with LLVM_BUILD_DIR / PYTHONPATH already exported.
"""
import os, sys, json, subprocess, time

HERE = os.path.dirname(os.path.abspath(__file__))
WORKER = os.path.join(HERE, "profile_worker.py")

# (side, depth) -> PE grid (side+2)^2, reduction depth K. Matches the doc's sweep.
CONFIGS = [(2, 2), (4, 4), (6, 6), (8, 8), (10, 8), (12, 8), (14, 8), (16, 8)]
NRUNS = int(os.environ.get("NRUNS", "30"))

rows = []
for side, depth in CONFIGS:
    pe_total = (side + 2) * (side + 2)
    env = dict(os.environ)
    env["OMP_NUM_THREADS"] = str(pe_total)   # libomp reads once, in the child
    t0 = time.perf_counter()
    print(f"[run] {side}x{side}x{depth}  PE={pe_total}  OMP_NUM_THREADS={pe_total} ...",
          flush=True)
    try:
        p = subprocess.run(
            [sys.executable, WORKER, str(side), str(depth), str(NRUNS)],
            env=env, capture_output=True, text=True, timeout=900,
        )
        line = [l for l in p.stdout.splitlines() if l.strip().startswith("{")]
        if not line:
            print("  FAILED (no JSON). stderr tail:\n   " +
                  "\n   ".join(p.stderr.strip().splitlines()[-8:]))
            continue
        rec = json.loads(line[-1])
        rec["wall_total_s"] = round(time.perf_counter() - t0, 1)
        rows.append(rec)
        err = rec.get("max_abs_err")
        verdict = "PASS" if (err is not None and err == err and err < 1e-3) else "CHECK"
        print(f"  ok  build={rec['build_s']}s  sim={rec['sim_ms_mean']}±{rec['sim_ms_sd']}ms"
              f"  sys_frac={rec['sys_frac']}  busy={rec['cpu_busy_cores']}c"
              f"  nivcsw/sim={rec['nivcsw_per_sim']}  rss={rec['peak_rss_mb']}MB"
              f"  err={err:.2e} {verdict}",
              flush=True)
    except subprocess.TimeoutExpired:
        print("  TIMEOUT")

# ---- table ----
cols = [
    ("config", "config", 9), ("pe_active", "PE", 5), ("oversub", "PE/core", 8),
    ("build_s", "build s", 8), ("sim_ms_mean", "sim ms", 8), ("sim_ms_sd", "±sd", 7),
    ("cpu_busy_cores", "busycore", 9), ("sys_frac", "sys_frac", 9),
    ("nvcsw_per_sim", "vcsw/sim", 9), ("nivcsw_per_sim", "ivcsw/sim", 10),
    ("cpu_util_frac", "util", 6), ("peak_rss_mb", "RSS MB", 8),
    ("max_abs_err", "max_err", 12),
]
print("\n" + "=" * 120)
print("".join(h.ljust(w) for _, h, w in cols))
print("-" * 120)
for r in rows:
    print("".join(str(r.get(k, "")).ljust(w) for k, _, w in cols))
print("=" * 120)

# ---- correctness verdict (vs numpy A @ B, in-process each config) ----
errs = [r.get("max_abs_err") for r in rows if r.get("max_abs_err") is not None]
worst = max(errs) if errs else float("nan")
ok = errs and all(e == e and e < 1e-3 for e in errs)   # e==e filters NaN
print(f"\nCORRECTNESS: {'ALL PASS' if ok else 'CHECK'} "
      f"({len(errs)}/{len(rows)} configs checked vs numpy A@B; "
      f"worst max_abs_err = {worst:.2e}, tol = 1e-3)")

out = os.path.join(HERE, "profile_results.json")
with open(out, "w") as f:
    json.dump(rows, f, indent=2)
print(f"\nraw -> {out}")
