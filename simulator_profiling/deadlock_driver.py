#!/usr/bin/env python3
"""
deadlock_driver.py -- run each deadlock_worker.py case under a hard
`timeout -s KILL`, and report whether the simulator COMPLETES, ERRORS
(detects), or HANGS (no detection -> must be killed externally).
"""
import os, sys, subprocess, time

HERE = os.path.dirname(os.path.abspath(__file__))
WORKER = os.path.join(HERE, "deadlock_worker.py")
T = int(os.environ.get("DL_TIMEOUT", "20"))
CASES = [
    ("control",      "correct: 4 puts / 4 gets"),
    ("mismatch_get", "consumer gets 1 more than produced"),
    ("overfill_put", "producer overfills depth-2 FIFO"),
    ("circular",     "two kernels each get-before-put"),
]

env = dict(os.environ)
env["OMP_NUM_THREADS"] = "4"

print(f"timeout = {T}s per case,  OMP_NUM_THREADS=4\n")
results = []
for case, desc in CASES:
    t0 = time.perf_counter()
    p = subprocess.run(["timeout", "-s", "KILL", str(T), sys.executable, WORKER, case],
                       env=env, capture_output=True, text=True)
    dt = time.perf_counter() - t0
    out, rc = p.stdout, p.returncode
    reached_sim = "BUILD_DONE" in out
    completed = "RESULT: COMPLETED" in out
    if completed:
        verdict = f"COMPLETED ({dt:.1f}s)"
    elif rc == 137 or rc < 0:                      # 128+SIGKILL, or negative signal
        where = "in sim" if reached_sim else "in BUILD(!)"
        verdict = f"HANG {where} -> killed at {T}s  [no detection]"
    else:
        tail = (p.stderr.strip().splitlines() or [""])[-1]
        verdict = f"ERROR rc={rc}: {tail[:60]}"
    results.append((case, desc, verdict))
    print(f"  {case:14s} | {desc:36s} | {verdict}", flush=True)

print("\n" + "=" * 92)
print(f"{'case':14s} | {'description':36s} | outcome")
print("-" * 92)
for case, desc, verdict in results:
    print(f"{case:14s} | {desc:36s} | {verdict}")
print("=" * 92)
print("A correct sim COMPLETES fast; a deadlock that HANGS means the simulator does NOT")
print("detect deadlock -- it blocks forever and must be killed by an external timeout.")
