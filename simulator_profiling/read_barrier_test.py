# Read-barrier determinism test: blocking producer (deterministic) + fixed-count
# try_get consumer. Without the Phase-3 read barrier the success count varies with
# the OS scheduler; with it, the answer should be identical across runs.
import sys
sys.path.insert(0, "/home/zsm9/allo_sup")
import numpy as np
import allo
from allo.ir.types import int32, int1, Stream
import allo.dataflow as df

@df.region()
def top(out: int32[1]):
    S: Stream[int32, 16][1]           # deep FIFO so the producer never blocks
    @df.kernel(mapping=[1])
    def producer():
        for i in range(8):
            x: int32 = i
            S[0].put(x)               # blocking, deterministic
    @df.kernel(mapping=[1], args=[out])
    def consumer(o: int32[1]):
        got: int32 = 0
        for k in range(16):           # fixed number of non-blocking gets
            v, ok = S[0].try_get()
            if ok:
                got += 1
        o[0] = got

sim = df.build(top, target="simulator")
res = []
for _ in range(30):
    o = np.zeros(1, dtype=np.int32)
    sim(o)
    res.append(int(o[0]))
distinct = sorted(set(res))
print("got across 30 runs:", res)
print("distinct outcomes:", distinct,
      "->", "DETERMINISTIC" if len(distinct) == 1 else f"NON-DET ({len(distinct)} distinct)")
