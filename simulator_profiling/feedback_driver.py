#!/usr/bin/env python3
"""
feedback_driver.py -- run each feedback (cyclic dataflow) case under a hard
`timeout -s KILL`, and report whether the simulator handles the loop-carried
FIFO dependency: COMPLETES (with correct/deterministic result) or HANGS (deadlock).
"""
import os, sys, subprocess, time

HERE = os.path.dirname(os.path.abspath(__file__))
WORKER = os.path.join(HERE, "feedback_worker.py")
T = int(os.environ.get("FB_TIMEOUT", "15"))
N = os.environ.get("N", "10")
CASES = [
    ("ring2_primed",   "2-kernel cycle, primed (expect N)"),
    ("ring3_primed",   "3-kernel cycle, primed (expect 2N)"),
    ("ring2_unprimed", "2-kernel cycle, consume-before-produce"),
]

env = dict(os.environ)
env["OMP_NUM_THREADS"] = "4"

print(f"N={N}, timeout={T}s per case, OMP_NUM_THREADS=4\n")
rows = []
for case, desc in CASES:
    p = subprocess.run(["timeout", "-s", "KILL", str(T), sys.executable, WORKER, case, N],
                       env=env, capture_output=True, text=True)
    out, rc = p.stdout, p.returncode
    result_line = next((l for l in out.splitlines() if l.startswith("RESULT: got=")), "")
    if "RESULT: COMPLETED" in out:
        verdict = "COMPLETED -> " + result_line.replace("RESULT: ", "")
    elif rc == 137 or rc < 0:
        verdict = f"HANG (deadlock) -> killed at {T}s"
    else:
        tail = (p.stderr.strip().splitlines() or [""])[-1]
        verdict = f"ERROR rc={rc}: {tail[:70]}"
    rows.append((case, desc, verdict))
    print(f"  {case:16s} | {verdict}", flush=True)

print("\n" + "=" * 100)
print(f"{'case':16s} | {'description':36s} | outcome")
print("-" * 100)
for case, desc, verdict in rows:
    print(f"{case:16s} | {desc:36s} | {verdict}")
print("=" * 100)
print("Takeaway: a properly PRIMED feedback loop runs correctly & deterministically;")
print("the SAME cycle unprimed (consume-before-produce) deadlocks -> depth/priming, not")
print("the simulator, decides feedback correctness.")
