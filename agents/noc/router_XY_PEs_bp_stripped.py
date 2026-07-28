"""XY router with credit backpressure, as a plain function. Connections agent-generated.

Stripped from router_XY_PEs_bp.py. STATEFUL: per-input FIFOs (buf/bcnt) + per-output
credits (cred). One cycle: take returning credits -> buffer valid inputs -> XY-route
each buffer head -> arbitrate per output (fixed priority, only with a credit) ->
crossbar (spend credit) -> pop granted inputs (return one credit upstream).

Ports (0=N 1=E 2=S 3=W 4=Local):
  in  : pkt_in[5]   forward inputs (opposite-flow links)
        cred_in[5]  returning credits for MY outputs (init allowance comes via wiring prime)
  out : pkt_out[5]  forward outputs (bubble = 0)
        cred_out[5] credit returns for MY inputs (1 = freed that input's slot)
The credit/buffer logic IS the router; stream mapping + priming are the wiring.
"""
from allo.ir.types import int32, UInt

DW = 16
W = 3
COL_LO = DW                 # dest_col [16:19]
ROW_LO = DW + W             # dest_row [19:22]
VLD = DW + 2 * W            # valid [22]
DONE = DW + 2 * W + 1       # done  [23]
PS = DW + 2 * W + 2         # packet width = 24
CMASK = (1 << W) - 1
DIR = 5
BUF_DEPTH = 2


def router_xy_bp(
    row_id: int32, col_id: int32,
    pkt_in: UInt(PS)[DIR], cred_in: int32[DIR],                        # in
    pkt_out: UInt(PS)[DIR], cred_out: int32[DIR],                      # out
    buf: UInt(PS)[DIR, BUF_DEPTH], bcnt: int32[DIR], cred: int32[DIR], # state
):
    # (A) collect returning credits for MY outputs
    for o in range(DIR):
        cred[o] += cred_in[o]

    # (B) buffer valid forward inputs (credit gating guarantees room)
    for d in range(DIR):
        if pkt_in[d][VLD] == 1 and bcnt[d] < BUF_DEPTH:
            buf[d, bcnt[d]] = pkt_in[d]; bcnt[d] += 1

    # (C) XY-route the head flit of each non-empty input buffer
    dstp: int32[DIR] = -1
    for d in range(DIR):
        if bcnt[d] > 0:
            h: UInt(PS) = buf[d, 0]
            hc: int32 = (h >> COL_LO) & CMASK
            hr: int32 = (h >> ROW_LO) & CMASK
            if   hc > col_id: dstp[d] = 1   # east
            elif hc < col_id: dstp[d] = 3   # west
            elif hr > row_id: dstp[d] = 2   # south
            elif hr < row_id: dstp[d] = 0   # north
            else:             dstp[d] = 4   # local

    # (D) arbitrate per output: fixed priority N>E>S>W>Local, only with a credit
    grant: int32[DIR] = -1
    gvld: int32[DIR] = 0
    for o in range(DIR):
        if cred[o] > 0:
            for d in range(DIR):
                if bcnt[d] > 0 and dstp[d] == o and gvld[o] == 0:
                    grant[o] = d; gvld[o] = 1

    # (E) crossbar: emit granted head, spend a credit, mark input for pop
    pop: int32[DIR] = 0
    for o in range(DIR):
        pkt_out[o] = 0
    for o in range(DIR):
        if gvld[o] == 1:
            gd: int32 = grant[o]
            pkt_out[o] = buf[gd, 0]
            cred[o] -= 1
            pop[gd] = 1

    # (F) pop granted inputs (FIFO shift), free a slot, return one credit upstream
    for d in range(DIR):
        cred_out[d] = 0
    for d in range(DIR):
        if pop[d] == 1:
            for s in range(BUF_DEPTH - 1):
                buf[d, s] = buf[d, s + 1]
            bcnt[d] -= 1
            cred_out[d] = 1
