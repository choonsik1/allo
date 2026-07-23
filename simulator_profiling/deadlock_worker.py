#!/usr/bin/env python3
"""
deadlock_worker.py <case> -- build + run ONE dataflow design that is either
correct (control) or deliberately deadlocking, to see what the simulator does.

Prints 'BUILD_DONE calling sim' before invoking (so the driver can tell a sim
hang from a build hang), then 'RESULT: COMPLETED' if sim(...) ever returns.
A deadlocking design is expected to block forever inside sim(...) -> the driver
kills it via `timeout`.
"""
import sys
sys.path.insert(0, "/home/zsm9/allo_sup")
import numpy as np
import allo
from allo.ir.types import int32, Stream
import allo.dataflow as df

CASE = sys.argv[1]


def build_control():
    """Correct producer/consumer: 4 puts, 4 gets. Should COMPLETE."""
    @df.region()
    def top(out: int32[4]):
        S: Stream[int32, 4][1]

        @df.kernel(mapping=[1])
        def prod():
            for i in range(4):
                x: int32 = i
                S[0].put(x)

        @df.kernel(mapping=[1], args=[out])
        def cons(o: int32[4]):
            for i in range(4):
                v: int32 = S[0].get()
                o[i] = v
    return top, (np.zeros(4, np.int32),)


def build_mismatch_get():
    """Consumer does one get too many: producer puts 4, consumer gets 5.
    5th get blocks forever on an empty FIFO whose producer has finished."""
    @df.region()
    def top(out: int32[5]):
        S: Stream[int32, 4][1]

        @df.kernel(mapping=[1])
        def prod():
            for i in range(4):
                x: int32 = i
                S[0].put(x)

        @df.kernel(mapping=[1], args=[out])
        def cons(o: int32[5]):
            for i in range(5):
                v: int32 = S[0].get()
                o[i] = v
    return top, (np.zeros(5, np.int32),)


def build_overfill_put():
    """Producer puts 8 into a depth-2 FIFO; consumer drains only 1.
    Producer blocks forever on a full FIFO."""
    @df.region()
    def top(out: int32[1]):
        S: Stream[int32, 2][1]

        @df.kernel(mapping=[1])
        def prod():
            for i in range(8):
                x: int32 = i
                S[0].put(x)

        @df.kernel(mapping=[1], args=[out])
        def cons(o: int32[1]):
            v: int32 = S[0].get()
            o[0] = v
    return top, (np.zeros(1, np.int32),)


def build_circular():
    """Circular wait: A gets S2 before putting S1; B gets S1 before putting S2.
    Both block on their initial get -> classic deadlock."""
    @df.region()
    def top(out: int32[2]):
        S1: Stream[int32, 2][1]
        S2: Stream[int32, 2][1]

        @df.kernel(mapping=[1], args=[out])
        def A(o: int32[2]):
            x: int32 = S2[0].get()
            S1[0].put(x)
            o[0] = x

        @df.kernel(mapping=[1])
        def B():
            y: int32 = S1[0].get()
            S2[0].put(y)
    return top, (np.zeros(2, np.int32),)


BUILDERS = {
    "control": build_control,
    "mismatch_get": build_mismatch_get,
    "overfill_put": build_overfill_put,
    "circular": build_circular,
}

top, args = BUILDERS[CASE]()
sim = df.build(top, target="simulator")
print("BUILD_DONE calling sim", flush=True)
sim(*args)
print("RESULT: COMPLETED", flush=True)
