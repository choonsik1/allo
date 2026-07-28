"""XY router, round-robin arbitration, as a plain function. Connections agent-generated.

Stripped from router_XY_rr.py. Bufferless (drops arbiter losers) but STATEFUL in one
small way: a per-output round-robin pointer rr[5] persists across cycles so no input
starves. One cycle: 5 packets in -> XY route -> round-robin arbitrate -> crossbar -> 5 out.
Ports 0=N 1=E 2=S 3=W 4=Local.
"""
from allo.ir.types import int32, UInt

DW = 16
W = 3
COL_LO = DW
ROW_LO = DW + W
VLD = DW + 2 * W            # 22
PS = DW + 2 * W + 1         # 23
CMASK = (1 << W) - 1
DIR = 5


def router_xy_rr(row_id: int32, col_id: int32, pkt_in: UInt(PS)[DIR], pkt_out: UInt(PS)[DIR], rr: int32[DIR]):
    # pkt_in[5], pkt_out[5]; rr[5] = per-output round-robin pointer (state)
    vld: int32[DIR] = 0; col: int32[DIR] = 0; row: int32[DIR] = 0
    for d in range(DIR):
        p: UInt(PS) = pkt_in[d]
        vld[d] = (p >> VLD) & 1
        col[d] = (p >> COL_LO) & CMASK
        row[d] = (p >> ROW_LO) & CMASK

    dst: int32[DIR] = 0
    for d in range(DIR):
        if   col[d] > col_id: dst[d] = 1
        elif col[d] < col_id: dst[d] = 3
        elif row[d] > row_id: dst[d] = 2
        elif row[d] < row_id: dst[d] = 0
        else:                 dst[d] = 4

    # round-robin arbitration: scan from rr[o], wrap, first requester wins; rotate on grant
    grant: int32[DIR] = 0; out_vld: int32[DIR] = 0
    for o in range(DIR):
        for i in range(DIR):
            d: int32 = rr[o] + i
            if d >= DIR: d -= DIR
            if vld[d] == 1 and dst[d] == o and out_vld[o] == 0:
                grant[o] = d; out_vld[o] = 1
        if out_vld[o] == 1:
            nxt: int32 = grant[o] + 1
            if nxt >= DIR: nxt -= DIR
            rr[o] = nxt

    for o in range(DIR):
        pkt_out[o] = 0
        if out_vld[o] == 1:
            pkt_out[o] = pkt_in[grant[o]]
