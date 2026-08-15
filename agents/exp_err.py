import os, sys
os.environ.setdefault("OMP_NUM_THREADS", "4")
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.join(HERE, "noc"))
from allo.ir.types import float16, int32, UInt
import allo.dataflow as df
# BARE imports: call name == def name (router / pe). router vs pe don't collide.
from router_XY_PEs_bp_stripped import router, DIR, PS, BUF_DEPTH
from pe_alu import pe


@df.region()
def top_bp(A: int32[DIR], B: int32[DIR]):
    @df.kernel(mapping=[1], args=[A, B])
    def k(la: int32[DIR], lb: int32[DIR]):
        pin: UInt(PS)[DIR] = 0; cin: int32[DIR] = 0
        pout: UInt(PS)[DIR] = 0; cout: int32[DIR] = 0
        buf: UInt(PS)[DIR, BUF_DEPTH] = 0; bcnt: int32[DIR] = 0; cred: int32[DIR] = 0
        for d in range(DIR):
            pin[d] = la[d]; cin[d] = BUF_DEPTH
        router(1, 1, pin, cin, pout, cout, buf, bcnt, cred)   # bare def name
        for d in range(DIR):
            lb[d] = pout[d]


@df.region()
def top_alu(A: float16[2], B: float16[1]):
    @df.kernel(mapping=[1], args=[A, B])
    def k(la: float16[2], lb: float16[1]):
        r: float16 = pe(la[0], la[1], 2)                      # bare def name (value-returning)
        lb[0] = r


import numpy as np
try:
    m = df.build(top_bp, target="simulator")
    A = np.zeros(DIR, np.int32); B = np.zeros(DIR, np.int32)
    A[3] = int(0x55 | (3 << 16) | (1 << 19) | (1 << 22))       # W input, dest col3>col1 -> east
    m(A, B)
    print(f"[bp_router bare] BUILT+RAN  out[1]=0x{int(B[1]):x}  {'PASS' if int(B[1])==int(A[3]) else 'ROUTED-WRONG'}")
except Exception as e:
    print("[bp_router bare]", type(e).__name__, [getattr(d,'message',d) for d in (getattr(e,'error_diagnostics',None) or [])][:1])

try:
    m = df.build(top_alu, target="simulator")
    A = np.array([3.0, 4.0], np.float16); B = np.zeros(1, np.float16)
    m(A, B)
    print(f"[pe_alu bare]    BUILT+RAN  3*4={float(B[0])}  {'PASS' if abs(float(B[0])-12)<1e-2 else 'WRONG'}")
except Exception as e:
    print("[pe_alu bare]", type(e).__name__, [getattr(d,'message',d) for d in (getattr(e,'error_diagnostics',None) or [])][:1])
