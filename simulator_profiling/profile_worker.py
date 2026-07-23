#!/usr/bin/env python3
"""
profile_worker.py -- measure WHERE the Allo dataflow simulator spends time,
for ONE systolic config, in its own process.

Directly tests the doc's inferred claim ("OS thread scheduling >95%, compute
negligible") with measured quantities: sys-CPU fraction, involuntary vs
voluntary context switches, effective CPU utilization, peak RSS, and warm-sim
wall time + variance -- all isolated from build time.

Usage:
    profile_worker.py <side> <depth> <nruns>
Emits one JSON line on stdout: {"config":..., "pe":..., metrics...}.
Run inside the `allo` env with LLVM_BUILD_DIR / PYTHONPATH set; the driver
sets OMP_NUM_THREADS = PE count BEFORE launching this (libomp reads it once).
"""
import os, sys, json, time, resource, statistics
sys.path.insert(0, "/home/zsm9/allo_sup")

import numpy as np
import allo
from allo.ir.types import float32, Stream
import allo.dataflow as df


def build_region(side, depth):
    """Construct the parametric systolic GEMM region (square side x side PE grid,
    reduction depth K), matching tests/dataflow/test_systolic.py."""
    M = N = side
    K = depth
    P0, P1 = M + 2, N + 2

    @df.region()
    def top(A: float32[M, K], B: float32[K, N], C: float32[M, N]):
        fifo_A: Stream[float32, 4][P0, P1]
        fifo_B: Stream[float32, 4][P0, P1]

        @df.kernel(mapping=[P0, P1], args=[A, B, C])
        def gemm(local_A: float32[M, K], local_B: float32[K, N], local_C: float32[M, N]):
            i, j = df.get_pid()
            with allo.meta_if(i in {0, M + 1} and j in {0, N + 1}):
                pass
            with allo.meta_elif(j == 0):
                for k in range(K):
                    fifo_A[i, j + 1].put(local_A[i - 1, k])
            with allo.meta_elif(i == 0):
                for k in range(K):
                    fifo_B[i + 1, j].put(local_B[k, j - 1])
            with allo.meta_elif(i == M + 1 and j > 0):
                for k in range(K):
                    b: float32 = fifo_B[i, j].get()
            with allo.meta_elif(j == N + 1 and i > 0):
                for k in range(K):
                    a: float32 = fifo_A[i, j].get()
            with allo.meta_else():
                c: float32 = 0
                for k in range(K):
                    a: float32 = fifo_A[i, j].get()
                    b: float32 = fifo_B[i, j].get()
                    c += a * b
                    fifo_A[i, j + 1].put(a)
                    fifo_B[i + 1, j].put(b)
                local_C[i - 1, j - 1] = c

    return top, (M, N, K, P0, P1)


def main():
    side, depth, nruns = int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3])
    pe_total = (side + 2) * (side + 2)          # sections libomp will spawn
    pe_active = pe_total - 4                     # corners DCE'd (doc's count)
    nproc = os.cpu_count()

    top, (M, N, K, P0, P1) = build_region(side, depth)

    # ---- BUILD (excluded from the sim measurement) ----
    tb0 = time.perf_counter()
    sim = df.build(top, target="simulator")
    build_s = time.perf_counter() - tb0

    A = np.random.rand(M, K).astype(np.float32)
    B = np.random.rand(K, N).astype(np.float32)
    C = np.zeros((M, N), dtype=np.float32)

    # ---- correctness check + warm-up (first run discarded) ----
    sim(A, B, C)
    ref = A @ B
    max_err = float(np.max(np.abs(C - ref))) if nruns > 0 else float("nan")

    # ---- WARM SIM measurement: N isolated runs ----
    r0 = resource.getrusage(resource.RUSAGE_SELF)
    tw0 = time.perf_counter()
    per_run = []
    for _ in range(nruns):
        C[...] = 0
        t0 = time.perf_counter()
        sim(A, B, C)
        per_run.append((time.perf_counter() - t0) * 1e3)   # ms
    wall = time.perf_counter() - tw0
    r1 = resource.getrusage(resource.RUSAGE_SELF)

    utime = r1.ru_utime - r0.ru_utime
    stime = r1.ru_stime - r0.ru_stime
    nvcsw = r1.ru_nvcsw - r0.ru_nvcsw      # voluntary (sleep/futex wait)
    nivcsw = r1.ru_nivcsw - r0.ru_nivcsw   # involuntary (scheduler preemption)
    cpu = utime + stime

    out = {
        "config": f"{side}x{side}x{depth}",
        "pe_total": pe_total, "pe_active": pe_active,
        "nproc": nproc, "oversub": round(pe_total / nproc, 2),
        "nruns": nruns,
        "build_s": round(build_s, 3),
        "sim_ms_mean": round(statistics.mean(per_run), 3) if per_run else None,
        "sim_ms_sd": round(statistics.pstdev(per_run), 3) if len(per_run) > 1 else 0.0,
        "sim_ms_min": round(min(per_run), 3) if per_run else None,
        "sim_ms_max": round(max(per_run), 3) if per_run else None,
        "warm_wall_s": round(wall, 3),
        "cpu_utime_s": round(utime, 3),
        "cpu_stime_s": round(stime, 3),
        "sys_frac": round(stime / cpu, 3) if cpu > 0 else None,
        "cpu_busy_cores": round(cpu / wall, 2) if wall > 0 else None,
        "cpu_util_frac": round(cpu / wall / nproc, 3) if wall > 0 else None,
        "nvcsw_per_sim": round(nvcsw / nruns, 1) if nruns else None,
        "nivcsw_per_sim": round(nivcsw / nruns, 1) if nruns else None,
        "peak_rss_mb": round(r1.ru_maxrss / 1024, 1),
        "max_abs_err": max_err,
        "omp_threads": os.environ.get("OMP_NUM_THREADS", "unset"),
        "omp_wait_policy": os.environ.get("OMP_WAIT_POLICY", "unset"),
    }
    print(json.dumps(out))


if __name__ == "__main__":
    main()
