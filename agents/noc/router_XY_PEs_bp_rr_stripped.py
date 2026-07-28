"""XY router, credit backpressure + round-robin, as a plain function. Connections agent-gen.

Stripped from router_XY_PEs_bp_rr.py: the bp router (per-input FIFOs + per-output
credits) with round-robin arbitration (per-output rr pointer). Lossless AND fair.
One cycle: take credits -> buffer valid inputs -> XY-route each head -> round-robin
arbitrate under credit -> crossbar (spend credit) -> pop granted (return credit).

Ports (0=N 1=E 2=S 3=W 4=Local):
  in  : pkt_in[5], cred_in[5]      out : pkt_out[5], cred_out[5]
State: buf[5,BUF_DEPTH], bcnt[5], cred[5], rr[5]
"""
from allo.ir.types import int32, UInt

DW = 16
W = 3
COL_LO = DW
ROW_LO = DW + W
VLD = DW + 2 * W            # 22
DONE = DW + 2 * W + 1       # 23
PS = DW + 2 * W + 2         # 24
CMASK = (1 << W) - 1
DIR = 5
BUF_DEPTH = 2


def router_xy_bp_rr(
    row_id: int32, col_id: int32,
    pkt_in: UInt(PS)[DIR], cred_in: int32[DIR],                        # in
    pkt_out: UInt(PS)[DIR], cred_out: int32[DIR],                      # out
    buf: UInt(PS)[DIR, BUF_DEPTH], bcnt: int32[DIR], cred: int32[DIR], rr: int32[DIR],  # state
):
    for o in range(DIR):
        cred[o] += cred_in[o]

    for d in range(DIR):
        if pkt_in[d][VLD] == 1 and bcnt[d] < BUF_DEPTH:
            buf[d, bcnt[d]] = pkt_in[d]; bcnt[d] += 1

    dstp: int32[DIR] = -1
    for d in range(DIR):
        if bcnt[d] > 0:
            h: UInt(PS) = buf[d, 0]
            hc: int32 = (h >> COL_LO) & CMASK
            hr: int32 = (h >> ROW_LO) & CMASK
            if   hc > col_id: dstp[d] = 1
            elif hc < col_id: dstp[d] = 3
            elif hr > row_id: dstp[d] = 2
            elif hr < row_id: dstp[d] = 0
            else:             dstp[d] = 4

    # round-robin arbitration under credit
    grant: int32[DIR] = -1
    gvld: int32[DIR] = 0
    for o in range(DIR):
        if cred[o] > 0:
            for i in range(DIR):
                d: int32 = rr[o] + i
                if d >= DIR: d -= DIR
                if bcnt[d] > 0 and dstp[d] == o and gvld[o] == 0:
                    grant[o] = d; gvld[o] = 1
            if gvld[o] == 1:
                nxt: int32 = grant[o] + 1
                if nxt >= DIR: nxt -= DIR
                rr[o] = nxt

    pop: int32[DIR] = 0
    for o in range(DIR):
        pkt_out[o] = 0
    for o in range(DIR):
        if gvld[o] == 1:
            gd: int32 = grant[o]
            pkt_out[o] = buf[gd, 0]
            cred[o] -= 1
            pop[gd] = 1

    for d in range(DIR):
        cred_out[d] = 0
    for d in range(DIR):
        if pop[d] == 1:
            for s in range(BUF_DEPTH - 1):
                buf[d, s] = buf[d, s + 1]
            bcnt[d] -= 1
            cred_out[d] = 1
