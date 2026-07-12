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
from allo.ir.types import int32, Stream
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


@pytest.mark.skipif(
    not os.environ.get("MGC_HOME"),
    reason="Catapult (MGC_HOME) not available — csim needs zhang-21",
)
def test_systemc_csim():
    """Compile + simulate the emitted SystemC through Catapult's SystemC."""
    top = _producer_consumer()
    with tempfile.TemporaryDirectory() as tmp:
        mod = df.build(top, target="systemc", mode="csim", project="test_systemc_backend")
        A = np.arange(8, dtype=np.int32)
        B = np.zeros(8, dtype=np.int32)
        mod(A, B)  # prints v11: 0..7 (A in) and v12: 1..8 (B = A + 1)
    # NOTE: Option A's self-contained testbench prints results to stdout; it does
    # not read them back into B yet, so we only assert the run completed.
    print("SystemC csim ran")


if __name__ == "__main__":
    test_systemc_emit()
    if os.environ.get("MGC_HOME"):
        test_systemc_csim()
    else:
        print("skipped csim (set MGC_HOME on zhang-21 to run it)")
