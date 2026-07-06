# Copyright Allo authors. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

import os
import tempfile

import numpy as np
import allo
from allo.ir.types import int32, Stream
import allo.dataflow as df

N = 16


@df.region()
def top_codegen(A: int32[N], B: int32[N * 2]):
    fifo: Stream[int32, 4]

    @df.kernel(mapping=[1], args=[A])
    def producer(local_A: int32[N]):
        for i in range(N):
            fifo.put(local_A[i])

    @df.kernel(mapping=[1], args=[B])
    def consumer(local_B: int32[N * 2]):
        # Non-blocking probe: read only when data is available, else a bubble.
        for i in range(N * 2):
            if fifo.empty() == 0:
                local_B[i] = fifo.get()
            else:
                local_B[i] = -1


def test_stream_empty_vhls_codegen():
    with tempfile.TemporaryDirectory() as tmpdir:
        prj = os.path.join(tmpdir, "stream_empty.prj")
        df.build(top_codegen, target="vhls", project=prj)
        with open(os.path.join(prj, "kernel.cpp")) as f:
            code = f.read()
        assert ".empty()" in code, "no .empty() in generated HLS code"
        print(code[code.index(".empty()") - 200 : code.index(".empty()") + 100])
        print("VHLS CODEGEN OK")


@df.region()
def top_sim(A: int32[N], B: int32[N + 1]):
    fifo: Stream[int32, 4]

    @df.kernel(mapping=[1], args=[A])
    def producer(local_A: int32[N]):
        for i in range(N):
            fifo.put(local_A[i])

    @df.kernel(mapping=[1], args=[B])
    def consumer(local_B: int32[N + 1]):
        c: int32 = 0
        n_bubbles: int32 = 0
        # Loop until all N items drained (bounded while) -- consumer can never
        # exit early, so the producer never blocks forever on a full FIFO.
        while c < N:
            if fifo.empty() == 0:
                local_B[c] = fifo.get()
                c = c + 1
            else:
                n_bubbles = n_bubbles + 1
        local_B[N] = n_bubbles  # report how many empty-probes fired


def test_stream_empty_simulator():
    # Requires LLVM_BUILD_DIR (for libomp/mlir runner libs); skip if unset.
    if not os.getenv("LLVM_BUILD_DIR"):
        import pytest

        pytest.skip("LLVM_BUILD_DIR not set")
    sim = df.build(top_sim, target="simulator")
    A = np.arange(N, dtype=np.int32)
    B = np.zeros(N + 1, dtype=np.int32)
    sim(A, B)
    reals, bubbles = B[:N], B[N]
    assert np.array_equal(reals, A), f"data mismatch: {reals} vs {A}"
    assert bubbles > 0, "empty() never returned true -- probe not exercised"
    print(f"SIMULATOR OK (all {N} values received, empty() fired {bubbles} times)")


if __name__ == "__main__":
    test_stream_empty_vhls_codegen()
    test_stream_empty_simulator()
