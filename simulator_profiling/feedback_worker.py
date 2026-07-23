#!/usr/bin/env python3
"""
feedback_worker.py <case> [N] -- build + run ONE *cyclic* (feedback) dataflow
design on the simulator. Tests whether the run-to-completion OMP + blocking-FIFO
model handles a loop-carried FIFO dependency (a graph cycle), which all prior
tests (feed-forward systolic) never exercised.

Cases:
  ring2_primed    A<->B cycle, A produces before consuming (loop primed).
                  A token circulates and B adds 1 each round -> expect N.
  ring3_primed    A->B->C->A cycle, B and C each add 1 -> expect 2N.
  ring2_unprimed  same topology as ring2 but A consumes before producing;
                  both kernels block on an empty FIFO -> deadlock.

Runs the sim 3x to also confirm the result is deterministic (blocking FIFOs are
timing-immune even with cycles). Prints a RESULT line and 'RESULT: COMPLETED'
if sim returns; a deadlocking case hangs and is killed by the driver's timeout.
"""
import sys
sys.path.insert(0, "/home/zsm9/allo_sup")
import numpy as np
import allo
from allo.ir.types import int32, Stream
import allo.dataflow as df

CASE = sys.argv[1]
N = int(sys.argv[2]) if len(sys.argv) > 2 else 10


def build_ring2_primed():
    @df.region()
    def top(out: int32[1]):
        fwd: Stream[int32, 2][1]      # A -> B
        back: Stream[int32, 2][1]     # B -> A  (the feedback edge)

        @df.kernel(mapping=[1], args=[out])
        def A(o: int32[1]):
            t: int32 = 0
            for k in range(N):
                fwd[0].put(t)          # produce FIRST -> primes the loop
                u: int32 = back[0].get()
                t = u
            o[0] = t

        @df.kernel(mapping=[1])
        def B():
            for k in range(N):
                x: int32 = fwd[0].get()
                y: int32 = x + 1
                back[0].put(y)
    return top, N


def build_ring2_unprimed():
    @df.region()
    def top(out: int32[1]):
        fwd: Stream[int32, 2][1]
        back: Stream[int32, 2][1]

        @df.kernel(mapping=[1], args=[out])
        def A(o: int32[1]):
            t: int32 = 0
            for k in range(N):
                u: int32 = back[0].get()   # consume FIRST -> nobody primed it
                fwd[0].put(u)
                t = u
            o[0] = t

        @df.kernel(mapping=[1])
        def B():
            for k in range(N):
                x: int32 = fwd[0].get()
                y: int32 = x + 1
                back[0].put(y)
    return top, None


def build_ring3_primed():
    @df.region()
    def top(out: int32[1]):
        ab: Stream[int32, 2][1]
        bc: Stream[int32, 2][1]
        ca: Stream[int32, 2][1]        # feedback edge C -> A

        @df.kernel(mapping=[1], args=[out])
        def A(o: int32[1]):
            t: int32 = 0
            for k in range(N):
                ab[0].put(t)
                u: int32 = ca[0].get()
                t = u
            o[0] = t

        @df.kernel(mapping=[1])
        def B():
            for k in range(N):
                x: int32 = ab[0].get()
                y: int32 = x + 1
                bc[0].put(y)

        @df.kernel(mapping=[1])
        def C():
            for k in range(N):
                x: int32 = bc[0].get()
                y: int32 = x + 1
                ca[0].put(y)
    return top, 2 * N


BUILDERS = {
    "ring2_primed": build_ring2_primed,
    "ring2_unprimed": build_ring2_unprimed,
    "ring3_primed": build_ring3_primed,
}

top, expected = BUILDERS[CASE]()
sim = df.build(top, target="simulator")
print("BUILD_DONE calling sim", flush=True)
outs = []
for _ in range(3):
    o = np.zeros(1, np.int32)
    sim(o)
    outs.append(int(o[0]))
got = outs[0]
det = all(x == got for x in outs)
ok = (expected is None) or (got == expected)
print(f"RESULT: got={got} expected={expected} match={ok} deterministic={det} runs={outs}",
      flush=True)
print("RESULT: COMPLETED", flush=True)
