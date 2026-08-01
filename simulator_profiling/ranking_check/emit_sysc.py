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

OUT = "/tmp/claude-1838657/-home-zsm9-allo-sup/62bf0b45-33d6-4696-8750-0593894b78f6/scratchpad/sysc_out"
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

import os
os.makedirs(OUT, exist_ok=True)
DESIGNS = [("d1_int4", 4, "int_add"), ("d2_int16", 16, "int_add"),
           ("d3_fmul4", 4, "f_mul"), ("d4_fdiv4", 4, "f_div"),
           ("d5_fmul16", 16, "f_mul")]
for name, n, kind in DESIGNS:
    top, _ = make(n, kind)
    try:
        code = df.build(top, target="systemc").hls_code
        open(os.path.join(OUT, f"{name}.cpp"), "w").write(code)
        print(f"{name:<12} emitted {len(code)} bytes")
    except Exception as e:
        print(f"{name:<12} EMIT FAILED: {type(e).__name__}: {str(e)[:80]}")
