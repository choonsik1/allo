"""Ranking-agreement check: do our simulator, Vitis and Catapult RANK designs the same?

The cost model exists to pick between designs, so what matters is ordering, not
magnitude. Five acyclic blocking producer/consumer variants chosen to spread the
ranking: element count and per-element compute cost both vary.
"""
import sys, os, shutil
sys.path.insert(0, "/home/zsm9/allo_sup")
import numpy as np
import allo
import allo.dataflow as df
from allo.ir.types import int32, float32, Stream

OUT = sys.argv[1] if len(sys.argv) > 1 else "/tmp/rank_out"
os.makedirs(OUT, exist_ok=True)

def make(n, kind):
    """producer writes n elements; consumer applies `kind` work per element."""
    if kind == "int_add":
        @df.region()
        def top(o: int32[16]):
            S: Stream[int32, 4][1]
            @df.kernel(mapping=[1])
            def prod():
                for i in range(n):
                    x: int32 = i
                    S[0].put(x)
            @df.kernel(mapping=[1], args=[o])
            def cons(out: int32[16]):
                for i in range(n):
                    v: int32 = S[0].get()
                    out[i] = v + 1
        return top, (np.zeros(16, np.int32),)
    if kind == "f_mul":
        @df.region()
        def top(o: float32[16]):
            S: Stream[float32, 4][1]
            @df.kernel(mapping=[1])
            def prod():
                for i in range(n):
                    x: float32 = i
                    S[0].put(x)
            @df.kernel(mapping=[1], args=[o])
            def cons(out: float32[16]):
                for i in range(n):
                    v: float32 = S[0].get()
                    out[i] = v * 3.0
        return top, (np.zeros(16, np.float32),)
    if kind == "f_div":
        @df.region()
        def top(o: float32[16]):
            S: Stream[float32, 4][1]
            @df.kernel(mapping=[1])
            def prod():
                for i in range(n):
                    x: float32 = i
                    S[0].put(x)
            @df.kernel(mapping=[1], args=[o])
            def cons(out: float32[16]):
                for i in range(n):
                    v: float32 = S[0].get()
                    out[i] = 100.0 / (v + 1.0)
        return top, (np.zeros(16, np.float32),)
    raise ValueError(kind)

DESIGNS = [("d1_int4", 4, "int_add"), ("d2_int16", 16, "int_add"),
           ("d3_fmul4", 4, "f_mul"), ("d4_fdiv4", 4, "f_div"),
           ("d5_fmul16", 16, "f_mul")]

results = {}
for name, n, kind in DESIGNS:
    top, args = make(n, kind)
    sim = df.build(top, target="simulator")
    sim(*args)
    c = sim.get_cycles()
    results[name] = c.makespan
    print(f"{name:<12} sim_makespan={c.makespan:<6} per_pe={c.per_pe}", flush=True)
    # emit HLS C++ for the Vitis/Catapult side
    top2, _ = make(n, kind)
    df.build(top2, target="vhls", mode="csyn", project=os.path.join(OUT, f"{name}.prj"))

print("\nSIM RANKING (fastest first):")
for k, v in sorted(results.items(), key=lambda kv: kv[1]):
    print(f"  {k:<12} {v}")
import json; json.dump(results, open(os.path.join(OUT, "sim.json"), "w"), indent=1)
