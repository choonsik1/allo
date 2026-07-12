# Copyright Allo authors. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

"""SystemC / Catapult (MatchLib Connections) backend — target="systemc".

Emits a dataflow @df.region as SystemC: each @df.kernel becomes an SC_MODULE
with Connections::In/Out ports + a clocked free-running thread, streams become
Connections::Combinational channels, and region boundary arrays are hoisted to
top-level array members (memory-port style, direction from arg_dirs).

test_systemc_emit runs anywhere (pure codegen). test_systemc_csim compiles +
simulates the emitted SystemC and is SKIPPED unless Catapult is available
(MGC_HOME / zhang-21 only).
"""

import os
import tempfile

import numpy as np
import pytest

import allo
from allo.ir.types import int32, int1, Stream
import allo.dataflow as df


def _producer_consumer():
    N = 8

    @df.region()
    def top(A: int32[N], B: int32[N]):
        fifo: Stream[int32, 4][1]

        @df.kernel(mapping=[1], args=[A])
        def producer(a: int32[N]):
            for i in range(N):
                fifo[0].put(a[i])

        @df.kernel(mapping=[1], args=[B])
        def consumer(b: int32[N]):
            for i in range(N):
                b[i] = fifo[0].get() + 1

    return top


def _systolic_chain(P=4, N=8):
    """array->stream feed + mapping=[P] PE chain (each +1) + stream->array drain."""

    @df.region()
    def top(A: int32[N], B: int32[N]):
        link: Stream[int32, 4][P + 1]

        @df.kernel(mapping=[1], args=[A])
        def feed(a: int32[N]):
            for k in range(N):
                link[0].put(a[k])

        @df.kernel(mapping=[P])
        def pe():
            i = df.get_pid()
            for k in range(N):
                v: int32 = link[i].get()
                w: int32 = v + 1
                link[i + 1].put(w)

        @df.kernel(mapping=[1], args=[B])
        def drain(b: int32[N]):
            for k in range(N):
                b[k] = link[P].get()

    return top, P, N


def test_systemc_golden():
    """The designs the SystemC backend emits are functionally correct, checked
    against the backend-agnostic Allo simulator. This makes the reference
    trustworthy for the csim / RTL-cosim checks (numpy -> simulator -> csim -> RTL)."""
    # producer/consumer: B = A + 1
    top = _producer_consumer()
    A = np.arange(8, dtype=np.int32)
    B = np.zeros(8, dtype=np.int32)
    df.build(top, target="simulator")(A, B)
    np.testing.assert_array_equal(B, A + 1)
    # systolic chain: B = A + P
    chain, P, N = _systolic_chain()
    A2 = np.arange(N, dtype=np.int32)
    B2 = np.zeros(N, dtype=np.int32)
    df.build(chain, target="simulator")(A2, B2)
    np.testing.assert_array_equal(B2, A2 + P)
    print("simulator golden OK: producer/consumer B=A+1, chain B=A+P")


def test_systemc_mem_port_reread():
    """A re-read (identity a[k] under an OUTER loop, each element touched twice)
    is not a single-pass scan, so the INPUT array a routes to a random-access
    memory port (AlloMem) — a LOAD may fire many times, which is correct."""

    N = 8

    @df.region()
    def top(A: int32[N], B: int32[N]):
        fifo: Stream[int32, 4][1]

        @df.kernel(mapping=[1], args=[A])
        def producer(a: int32[N]):
            for r in range(2):
                for k in range(N):
                    fifo[0].put(a[k])  # a[k] re-read across the r loop -> mem port

        @df.kernel(mapping=[1], args=[B])
        def consumer(b: int32[N]):
            for i in range(N):
                s: int32 = 0
                for r in range(2):
                    s = fifo[0].get()
                b[i] = s

    code = df.build(top, target="systemc").hls_code
    assert "AlloMem<" in code  # re-read input -> internal memory
    assert "_req.Push(" in code and "_rsp.Pop()" in code
    print("re-read input -> memory port")


def test_systemc_nonblocking():
    """try_get / try_put emit as Connections .PopNB() / .PushNB() (fire-on-valid).
    NOTE: a *working* fire-on-valid design must do one try per cycle (not spin) —
    spin-until-success deadlocks a free-running SC_THREAD. This checks emission."""

    N = 8

    @df.region()
    def top(A: int32[N], B: int32[N]):
        S: Stream[int32, 4][1]

        @df.kernel(mapping=[1], args=[A])
        def producer(a: int32[N]):
            for i in range(N):
                ok: int1 = 0
                while ok == 0:
                    ok = S[0].try_put(a[i])

        @df.kernel(mapping=[1], args=[B])
        def consumer(b: int32[N]):
            for i in range(N):
                v: int32 = 0
                ok: int1 = 0
                while ok == 0:
                    v, ok = S[0].try_get()
                b[i] = v

    code = df.build(top, target="systemc").hls_code
    assert ".PopNB(" in code and ".PushNB(" in code
    print("try_get/try_put -> PopNB/PushNB")


def test_systemc_rejects_empty_full():
    """empty()/full() have no synthesizable Connections equivalent -> rejected
    (Connections is a handshake, not an introspectable FIFO; use try_get/try_put)."""

    N = 8

    @df.region()
    def top(A: int32[N], B: int32[N]):
        S: Stream[int32, 1][1]

        @df.kernel(mapping=[1], args=[A])
        def producer(a: int32[N]):
            for i in range(N):
                S[0].put(a[i])

        @df.kernel(mapping=[1], args=[B])
        def consumer(b: int32[N]):
            for i in range(N):
                e: int1 = S[0].empty()  # no synthesizable Connections equivalent
                b[i] = S[0].get()

    with pytest.raises(Exception, match="Failed to emit"):
        df.build(top, target="systemc")
    print("empty() correctly rejected")


def test_systemc_emit():
    """Pure codegen — no toolchain needed. Checks the Connections stream shape."""
    top = _producer_consumer()
    code = df.build(top, target="systemc").hls_code

    # Connections shell (synthesizable), not the old sc_fifo model
    assert "sc_fifo" not in code
    assert "Connections::In<" in code
    assert "Connections::Out<" in code
    assert "Connections::Combinational<" in code
    assert ".Pop()" in code and ".Push(" in code
    assert "while (1)" in code
    assert "SC_HAS_PROCESS" in code
    # sequential-stream: boundary arrays become Connections stream PORTS
    # (no array members, no pointers), and a[i]/b[i]=v become Pop()/Push()
    assert "[8]" not in code  # no int32_t vN[8]; array member survives
    assert "nullptr" not in code  # no kernel array pointer
    print("SystemC emit shape OK")


def _mem_port_reverse():
    """B[i] = A[N-1-i] + 1 : A read reversed -> random-access INPUT memory port;
    B is a normal sequential output stream."""
    N = 8

    @df.region()
    def top(A: int32[N], B: int32[N]):
        @df.kernel(mapping=[1], args=[A, B])
        def rev(a: int32[N], b: int32[N]):
            for i in range(N):
                b[i] = a[N - 1 - i] + 1

    return top, N


def test_systemc_mem_port_emit():
    """A non-sequential INPUT array is routed to an internal AlloMem addressed by
    a Connections req/resp handshake (the only memory kind the SystemC flow
    supports), NOT silently mis-streamed. The flat address is the reversed index."""
    top, _ = _mem_port_reverse()
    code = df.build(top, target="systemc").hls_code
    assert "AlloMem<" in code  # internal random-access memory instantiated
    assert "_req.Push(" in code and "_rsp.Pop()" in code  # LOAD handshake
    assert "_req_ch" in code and "_rsp_ch" in code  # wired at top
    assert ".mem[f] =" in code  # tb preloads the memory from input file
    print("random INPUT access -> memory port emitted")


def test_systemc_rejects_store_side_mem_port():
    """The store side of a memory port (random-access OUTPUT/BOTH) is not wired
    yet and must still be rejected cleanly, not silently mis-emitted."""

    N = 8

    @df.region()
    def top(A: int32[N], B: int32[N]):
        fifo: Stream[int32, 4][1]

        @df.kernel(mapping=[1], args=[A])
        def producer(a: int32[N]):
            for i in range(N):
                fifo[0].put(a[i])

        @df.kernel(mapping=[1], args=[B])
        def consumer(b: int32[N]):
            for i in range(N):
                b[N - 1 - i] = fifo[0].get()  # reversed WRITE -> store-side port

    with pytest.raises(Exception, match="Failed to emit"):
        df.build(top, target="systemc")
    print("store-side memory port correctly rejected")


@pytest.mark.skipif(
    not os.environ.get("MGC_HOME"),
    reason="Catapult (MGC_HOME) not available — csim needs zhang-21",
)
def test_systemc_mem_port_csim():
    """Compile + simulate the memory-port design: A preloaded into AlloMem, read
    reversed over the req/resp handshake, +1, streamed to B. Assert B == A[::-1]+1."""
    top, N = _mem_port_reverse()
    with tempfile.TemporaryDirectory() as tmp:
        mod = df.build(top, target="systemc", mode="csim", project=tmp)
        A = np.arange(N, dtype=np.int32)
        B = np.zeros(N, dtype=np.int32)
        mod(A, B)
        np.testing.assert_array_equal(B, A[::-1] + 1)
    print("SystemC memory-port csim B == A[::-1] + 1")


def test_systemc_grid():
    """mapping=[P] is unrolled into P kernel SC_MODULEs, wired as a neighbor chain."""

    P, N = 4, 8

    @df.region()
    def top(A: int32[N], B: int32[N]):
        link: Stream[int32, 4][P + 1]

        @df.kernel(mapping=[1], args=[A])
        def feed(a: int32[N]):
            for k in range(N):
                link[0].put(a[k])

        @df.kernel(mapping=[P])
        def pe():
            i = df.get_pid()
            for k in range(N):
                v: int32 = link[i].get()
                w: int32 = v + 1
                link[i + 1].put(w)

        @df.kernel(mapping=[1], args=[B])
        def drain(b: int32[N]):
            for k in range(N):
                b[k] = link[P].get()

    code = df.build(top, target="systemc").hls_code
    for p in range(P):  # each grid instance is its own module
        assert f"SC_MODULE(pe_{p})" in code
    # P+1 link channels in the top (+ tb channels), so at least P+1
    assert code.count("Connections::Combinational<") >= P + 1
    print(f"grid of {P} PEs emitted + wired")


@pytest.mark.skipif(
    not os.environ.get("MGC_HOME"),
    reason="Catapult (MGC_HOME) not available — csim needs zhang-21",
)
def test_systemc_csim():
    """Compile + simulate the emitted SystemC; results flow back into B (Option B:
    A -> input0.data -> design -> output0.data -> B), so we assert B == A + 1."""
    top = _producer_consumer()
    with tempfile.TemporaryDirectory() as tmp:
        mod = df.build(top, target="systemc", mode="csim", project=tmp)
        A = np.arange(8, dtype=np.int32)
        B = np.zeros(8, dtype=np.int32)
        mod(A, B)
        np.testing.assert_array_equal(B, A + 1)
    print("SystemC csim B == A + 1")


@pytest.mark.skipif(
    not os.environ.get("MGC_HOME"),
    reason="Catapult (MGC_HOME) not available — csim needs zhang-21",
)
def test_systemc_csim_grid():
    """End-to-end csim of a mapping=[P] grid with data-through-args: B == A + P."""
    chain, P, N = _systolic_chain()
    with tempfile.TemporaryDirectory() as tmp:
        mod = df.build(chain, target="systemc", mode="csim", project=tmp)
        A = np.arange(N, dtype=np.int32)
        B = np.zeros(N, dtype=np.int32)
        mod(A, B)
        np.testing.assert_array_equal(B, A + P)
    print(f"SystemC csim grid B == A + {P}")


if __name__ == "__main__":
    test_systemc_emit()
    if os.environ.get("MGC_HOME"):
        test_systemc_csim()
    else:
        print("skipped csim (set MGC_HOME on zhang-21 to run it)")
