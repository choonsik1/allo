"""XY router as a plain function. Connections are agent-generated.

Stripped from router_XY.py: the bufferless XY router is STATELESS -- one cycle is
5 packets in -> XY route -> fixed-priority arbitration -> crossbar -> 5 packets out.
Ports are pkt_in[5]/pkt_out[5] (0=N 1=E 2=S 3=W 4=Local). The stream mapping
(which link feeds which input, the opposite-flow indexing) and priming are the
wiring, not the router.
"""
from allo.ir.types import int32, UInt

DW = 16                     # payload width
W = 3                       # coord width
COL_LO = DW                 # dest_col [16:19]
ROW_LO = DW + W             # dest_row [19:22]
VLD = DW + 2 * W            # valid bit [22]
PS = DW + 2 * W + 1         # packet width = 23
CMASK = (1 << W) - 1        # 0x7
DIR = 5


def router_xy(row_id: int32, col_id: int32, pkt_in: UInt(PS)[DIR], pkt_out: UInt(PS)[DIR]):
    # pkt_in[5], pkt_out[5] : 0=N 1=E 2=S 3=W 4=Local ; bubble = 0
    vld: int32[DIR] = 0; col: int32[DIR] = 0; row: int32[DIR] = 0
    for d in range(DIR):
        p: UInt(PS) = pkt_in[d]
        vld[d] = (p >> VLD) & 1
        col[d] = (p >> COL_LO) & CMASK
        row[d] = (p >> ROW_LO) & CMASK

    # XY route: output port per input
    dst: int32[DIR] = 0
    for d in range(DIR):
        if   col[d] > col_id: dst[d] = 1   # east
        elif col[d] < col_id: dst[d] = 3   # west
        elif row[d] > row_id: dst[d] = 2   # south
        elif row[d] < row_id: dst[d] = 0   # north
        else:                 dst[d] = 4   # local

    # fixed-priority arbitration: one input per output (d ascending = N>E>S>W>Local)
    grant: int32[DIR] = 0; out_vld: int32[DIR] = 0
    for o in range(DIR):
        for d in range(DIR):
            if vld[d] == 1 and dst[d] == o and out_vld[o] == 0:
                grant[o] = d; out_vld[o] = 1

    # crossbar
    for o in range(DIR):
        pkt_out[o] = 0
        if out_vld[o] == 1:
            pkt_out[o] = pkt_in[grant[o]]
