"""Experiment: can a @df.kernel CALL a stripped block function (an array-mutating,
locals-declaring, void helper), or must the block logic be inlined?

Uses the stateless router_XY_stripped.router. A single kernel loads a packet into a
local pkt_in[5], CALLS router(...), and reads pkt_out[5] back out. If Allo builds +
routes correctly, the generator can emit `call block(...)`; if it errors, the
generator must inline the block body.
"""
import os, sys
os.environ.setdefault("OMP_NUM_THREADS", "4")
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "noc"))
import numpy as np
import allo
from allo.ir.types import int32, UInt
import allo.dataflow as df
from router_XY_stripped import router, PS, DIR, VLD, COL_LO, ROW_LO


def pack(data, col, row, valid=1):
    return int(data | (col << COL_LO) | (row << ROW_LO) | (valid << VLD))


@df.region()
def top(A: int32[DIR], B: int32[DIR]):
    @df.kernel(mapping=[1], args=[A, B])
    def k(la: int32[DIR], lb: int32[DIR]):
        pin: UInt(PS)[DIR] = 0
        pout: UInt(PS)[DIR] = 0
        for d in range(DIR):
            pin[d] = la[d]
        router(1, 1, pin, pout)          # <-- CALL under test (node at (1,1))
        for d in range(DIR):
            lb[d] = pout[d]


if __name__ == "__main__":
    mod = df.build(top, target="simulator")
    A = np.zeros(DIR, np.int32)
    B = np.zeros(DIR, np.int32)
    # packet on the West input (d=3), dest (row=1,col=3): col 3 > my col 1 -> exit East (o=1)
    A[3] = pack(data=0x55, col=3, row=1)
    mod(A, B)
    print("in :", [hex(int(x)) for x in A])
    print("out:", [hex(int(x)) for x in B])
    print("CALLABLE-PASS" if int(B[1]) == int(A[3]) and int(B[1]) != 0
          else "CALLABLE-FAIL (built but routed wrong)")
