"""Callable check for the harder param shapes:
  (1) bp router  -- 2-D state (buf[5,2]), int32[5] state, credit ports, in+out mutation
  (2) eva pe     -- 21 params incl. Ty[1] 1-element out ports (build+run = inlines OK)
  (3) pe_alu     -- return-style pure ALU
"""
import os, sys
os.environ.setdefault("OMP_NUM_THREADS", "4")
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(HERE, "noc"))
import numpy as np
import allo
from allo.ir.types import float16, int32, UInt
import allo.dataflow as df

# Allo resolves a call by its BARE name in the caller's globals -> import each
# block function under a distinct alias (they're all named router/pe).
from router_XY_PEs_bp_stripped import router as bp_router
from router_XY_PEs_bp_stripped import DIR, PS, BUF_DEPTH, VLD, COL_LO, ROW_LO
from eva_blocks import pe as eva_pe, Ty as EVA_Ty, IRF_DEPTH, DRF_DEPTH
from pe_alu import pe as alu_pe


def bp_pack(data, col, row, valid=1):
    return int(data | (col << COL_LO) | (row << ROW_LO) | (valid << VLD))


# ---- (1) bp router: 2-D state + credits ----
@df.region()
def top_bp(A: int32[DIR], B: int32[DIR]):
    @df.kernel(mapping=[1], args=[A, B])
    def k(la: int32[DIR], lb: int32[DIR]):
        pin: UInt(PS)[DIR] = 0
        cin: int32[DIR] = 0
        pout: UInt(PS)[DIR] = 0
        cout: int32[DIR] = 0
        buf: UInt(PS)[DIR, BUF_DEPTH] = 0
        bcnt: int32[DIR] = 0
        cred: int32[DIR] = 0
        for d in range(DIR):
            pin[d] = la[d]
            cin[d] = BUF_DEPTH          # prime output credits so a head can fire
        bp_router(1, 1, pin, cin, pout, cout, buf, bcnt, cred)
        for d in range(DIR):
            lb[d] = pout[d]


# ---- (2) eva pe: 21-param signature incl Ty[1] out ports (build+run = inline OK) ----
@df.region()
def top_eva(A: int32[1]):
    @df.kernel(mapping=[1], args=[A])
    def k(la: int32[1]):
        ext_val: EVA_Ty[4] = 0
        ext_vld: int32[4] = 0
        ext_consume: int32[4] = 0
        send_valid: int32[1] = 0; send_kind: int32[1] = 0; send_dir: int32[1] = 0
        send_data: EVA_Ty[1] = 0; send_dst: int32[1] = 0; send_id: int32[1] = 0
        irf: int32[IRF_DEPTH] = 0
        drf: EVA_Ty[DRF_DEPTH] = 0
        drf_full: int32[DRF_DEPTH] = 0
        ctl: int32[7] = 0
        eva_pe(0, 0, ext_val, ext_vld, 0, 0, 0, 0, 0, 0,
               ext_consume, send_valid, send_kind, send_dir, send_data, send_dst, send_id,
               irf, drf, drf_full, ctl)
        la[0] = send_valid[0]           # observe an output so it's not DCE'd


# ---- (3) pe_alu: return-style pure ALU ----
@df.region()
def top_alu(A: float16[2], B: float16[1]):
    @df.kernel(mapping=[1], args=[A, B])
    def k(la: float16[2], lb: float16[1]):
        r: float16 = alu_pe(la[0], la[1], 2)   # OP_MULT
        lb[0] = r


if __name__ == "__main__":
    # (1)
    try:
        m = df.build(top_bp, target="simulator")
        A = np.zeros(DIR, np.int32); B = np.zeros(DIR, np.int32)
        A[3] = bp_pack(0x55, col=3, row=1)     # W input, dest col 3 > col 1 -> east (o=1)
        m(A, B)
        ok = int(B[1]) == int(A[3]) and int(B[1]) != 0
        print(f"(1) bp router (2-D state + credits): {'PASS' if ok else 'FAIL'}  out[1]=0x{int(B[1]):x}")
    except Exception as e:
        print("(1) bp router: BUILD/RUN ERROR:", repr(e)[:200])

    # (2)
    try:
        m = df.build(top_eva, target="simulator")
        A = np.zeros(1, np.int32)
        m(A)
        print(f"(2) eva pe (21 params, Ty[1] out ports): PASS (built+ran, send_valid={int(A[0])})")
    except Exception as e:
        print("(2) eva pe: BUILD/RUN ERROR:", repr(e)[:200])

    # (3)
    try:
        m = df.build(top_alu, target="simulator")
        A = np.array([3.0, 4.0], np.float16); B = np.zeros(1, np.float16)
        m(A, B)
        ok = abs(float(B[0]) - 12.0) < 1e-3
        print(f"(3) pe_alu (return-style ALU): {'PASS' if ok else 'FAIL'}  3*4={float(B[0])}")
    except Exception as e:
        print("(3) pe_alu: BUILD/RUN ERROR:", repr(e)[:200])
