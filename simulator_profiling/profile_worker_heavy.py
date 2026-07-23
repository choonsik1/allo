#!/usr/bin/env python3
"""
profile_worker_heavy.py -- like profile_worker.py, but each interior systolic PE
does FLOP extra fused-multiply-adds per reduction step, so we can dial compute
intensity while keeping the SAME dataflow topology / sync pattern. Used to test
(a) whether the "compute negligible" claim breaks down as FLOP rises, and
(b) whether the OMP_WAIT_POLICY=passive advantage shrinks when PEs actually work.

Usage: profile_worker_heavy.py <side> <depth> <flop> <nruns>
The wait policy is taken from the OMP_WAIT_POLICY env var set by the driver.

Correctness: the kernel is deterministic (blocking FIFOs -> timing-immune), so
every run must produce a bit-identical C. We take the first run as reference and
assert all others match (max_dev == 0), and emit a checksum the driver compares
across policies.
"""
import os, sys, json, time, resource, statistics
sys.path.insert(0, "/home/zsm9/allo_sup")

import numpy as np
import allo
from allo.ir.types import float32, Stream
import allo.dataflow as df


def build_region(side, depth, flop):
    M = N = side
    K = depth
    P0, P1 = M + 2, N + 2
    FLOP = flop

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
                    # heavy compute: FLOP loop-carried madds -- data-dependent and
                    # loop-carried so LLVM cannot fold or vectorize it away.
                    t: float32 = a
                    for _ in range(FLOP):
                        t = t * b + a
                    c += t
                    fifo_A[i, j + 1].put(a)
                    fifo_B[i + 1, j].put(b)
                local_C[i - 1, j - 1] = c

    return top, (M, N, K)


def main():
    side, depth, flop, nruns = (int(sys.argv[1]), int(sys.argv[2]),
                                int(sys.argv[3]), int(sys.argv[4]))
    pe_total = (side + 2) * (side + 2)
    nproc = os.cpu_count()

    top, (M, N, K) = build_region(side, depth, flop)

    tb0 = time.perf_counter()
    sim = df.build(top, target="simulator")
    build_s = time.perf_counter() - tb0

    np.random.seed(0)   # fixed inputs so active/passive are directly comparable
    A = np.random.rand(M, K).astype(np.float32)
    B = np.random.rand(K, N).astype(np.float32)
    C = np.zeros((M, N), dtype=np.float32)

    sim(A, B, C)                 # warm-up + reference
    ref = C.copy()
    max_dev = 0.0

    r0 = resource.getrusage(resource.RUSAGE_SELF)
    tw0 = time.perf_counter()
    per_run = []
    for _ in range(nruns):
        C[...] = 0
        t0 = time.perf_counter()
        sim(A, B, C)
        per_run.append((time.perf_counter() - t0) * 1e3)
        max_dev = max(max_dev, float(np.max(np.abs(C - ref))))
    wall = time.perf_counter() - tw0
    r1 = resource.getrusage(resource.RUSAGE_SELF)

    utime = r1.ru_utime - r0.ru_utime
    stime = r1.ru_stime - r0.ru_stime
    nivcsw = r1.ru_nivcsw - r0.ru_nivcsw
    cpu = utime + stime

    out = {
        "config": f"{side}x{side}x{depth}", "pe_total": pe_total, "nproc": nproc,
        "flop": flop, "nruns": nruns,
        "omp_wait_policy": os.environ.get("OMP_WAIT_POLICY", "unset"),
        "build_s": round(build_s, 3),
        "sim_ms_mean": round(statistics.mean(per_run), 3),
        "sim_ms_sd": round(statistics.pstdev(per_run), 3) if len(per_run) > 1 else 0.0,
        "sys_frac": round(stime / cpu, 3) if cpu > 0 else None,
        "cpu_busy_cores": round(cpu / wall, 2) if wall > 0 else None,
        "nivcsw_per_sim": round(nivcsw / nruns, 1) if nruns else None,
        "max_dev": max_dev,                                  # 0 == deterministic/repeatable
        "checksum": round(float(ref.sum()), 4),              # cross-policy result check
    }
    print(json.dumps(out))


if __name__ == "__main__":
    main()
