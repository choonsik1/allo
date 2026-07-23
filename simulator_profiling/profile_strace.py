#!/usr/bin/env python3
"""
profile_strace.py -- syscall breakdown (futex / nanosleep / sched_yield) of the
simulator, via `strace -f -c`. strace ptrace-intercepts every syscall on every
thread, so it HEAVILY perturbs timing -- these counts are used only to show the
COMPOSITION of the kernel time (what the sys_frac ~0.79 is made of), and are
merged with the CLEAN timing/rusage from profile_results.json.

Per-sim counts = counts(NRUNS=1) - counts(NRUNS=0)   (subtracts build + warmup).
Each config runs in its own process with OMP_NUM_THREADS = PE count.
Env: STRACE_TIMEOUT (s, per strace invocation; default 240).
"""
import os, sys, json, subprocess, time

HERE = os.path.dirname(os.path.abspath(__file__))
WORKER = os.path.join(HERE, "profile_worker.py")
CONFIGS = [(2, 2), (4, 4), (6, 6), (8, 8), (10, 8), (12, 8), (14, 8), (16, 8)]
SYS = ["futex", "nanosleep", "clock_nanosleep", "sched_yield"]
TIMEOUT = int(os.environ.get("STRACE_TIMEOUT", "240"))


def strace_counts(side, depth, nruns):
    """Return ({syscall: calls}, {syscall: seconds}) from strace -c summary."""
    pe = (side + 2) * (side + 2)
    env = dict(os.environ)
    env["OMP_NUM_THREADS"] = str(pe)
    cmd = ["strace", "-f", "-c", "-e", "trace=" + ",".join(SYS),
           sys.executable, WORKER, str(side), str(depth), str(nruns)]
    p = subprocess.run(cmd, env=env, capture_output=True, text=True, timeout=TIMEOUT)
    counts = {s: 0 for s in SYS}
    secs = {s: 0.0 for s in SYS}
    for line in p.stderr.splitlines():
        parts = line.split()
        # % time, seconds, usecs/call, calls, [errors], syscall
        if len(parts) >= 5 and parts[-1] in SYS:
            try:
                secs[parts[-1]] = float(parts[1])
                counts[parts[-1]] = int(parts[3])
            except (ValueError, IndexError):
                pass
    return counts, secs


rows = []
for side, depth in CONFIGS:
    cfg = f"{side}x{side}x{depth}"
    pe = (side + 2) * (side + 2)
    print(f"[strace] {cfg} PE={pe} ...", flush=True)
    try:
        t0 = time.perf_counter()
        c1, s1 = strace_counts(side, depth, 1)   # build + warmup + 1 timed sim
        c0, _ = strace_counts(side, depth, 0)    # build + warmup
        persim = {s: max(c1[s] - c0[s], 0) for s in SYS}
        nsleep = persim["nanosleep"] + persim["clock_nanosleep"]
        total_secs = sum(s1.values()) or 1e-9
        rec = {
            "config": cfg, "pe": pe,
            "futex_per_sim": persim["futex"],
            "nanosleep_per_sim": nsleep,
            "sched_yield_per_sim": persim["sched_yield"],
            "futex_time_frac": round(s1["futex"] / total_secs, 3),
            "strace_wall_s": round(time.perf_counter() - t0, 1),
        }
        rows.append(rec)
        print(f"  futex/sim={rec['futex_per_sim']}  nsleep/sim={rec['nanosleep_per_sim']}"
              f"  yield/sim={rec['sched_yield_per_sim']}"
              f"  (futex {rec['futex_time_frac']*100:.0f}% of syscall-time, {rec['strace_wall_s']}s)",
              flush=True)
    except subprocess.TimeoutExpired:
        rows.append({"config": cfg, "pe": pe, "timeout": True})
        print(f"  TIMEOUT (> {TIMEOUT}s) -- skipped", flush=True)

# ---- merge with clean timing table ----
try:
    clean = {r["config"]: r for r in json.load(open(os.path.join(HERE, "profile_results.json")))}
except Exception:
    clean = {}
for r in rows:
    base = clean.get(r["config"], {})
    r["sys_frac"] = base.get("sys_frac")
    r["ivcsw_per_sim"] = base.get("nivcsw_per_sim")

cols = [
    ("config", "config", 9), ("pe", "PE", 5), ("sys_frac", "sys_frac", 9),
    ("ivcsw_per_sim", "ivcsw/sim", 12), ("futex_per_sim", "futex/sim", 12),
    ("sched_yield_per_sim", "yield/sim", 12), ("nanosleep_per_sim", "nsleep/sim", 11),
    ("futex_time_frac", "futex%time", 11),
]
print("\n" + "=" * 96)
print("".join(h.ljust(w) for _, h, w in cols))
print("-" * 96)
for r in rows:
    if r.get("timeout"):
        print(f"{r['config'].ljust(9)}{str(r['pe']).ljust(5)}TIMEOUT (>{TIMEOUT}s)")
        continue
    print("".join(str(r.get(k, "")).ljust(w) for k, _, w in cols))
print("=" * 96)
print("NOTE: counts are strace-perturbed (composition, not exact magnitudes);")
print("      sys_frac & ivcsw/sim are the CLEAN unstraced values from profile_results.json.")

out = os.path.join(HERE, "profile_strace_results.json")
json.dump(rows, open(out, "w"), indent=2)
print(f"\nraw -> {out}")
