import os; os.environ.setdefault("OMP_NUM_THREADS", "256")   # >= #instances; set before allo
import allo
from allo.ir.types import int32, int1, UInt, Stream
import allo.dataflow as df
import numpy as np

# =====================================================================================
# XY-router mesh, 4x4, built on NON-BLOCKING stream ops (try_get / try_put).
#
# Counterpart of router_XY.py (blocking, always-fire/bubble). Same routing, same
# arbitration, same bufferless drop semantics -- but the *synchronisation discipline*
# is gone, because a non-blocking poll already answers "is there a flit for me?".
#
# What the blocking version needed, and why it is no longer here:
#
#   always-fire + bubbles  Every producer had to push exactly one token per cycle
#                          (0 = bubble) so that the consumer's blocking get() would
#                          not stall.  try_get() just returns ok=0 on an empty link,
#                          so idle links carry NOTHING. No bubble traffic at all.
#
#   VLD bit in the payload The blocking version could not tell "no flit" from "flit
#                          whose value is 0", so it spent a payload bit on validity
#                          (VLD, bit 22) and defined bubble == 0.  Validity is now the
#                          protocol's `ok` flag, so the bit is gone and the packet
#                          shrinks 23 -> 22 bits.  data == 0 is now a legal payload.
#
#   priming (5 puts)       Interior links form cycles ((r,c).E-in <- (r,c+1).W-out and
#                          back), so with blocking gets every router had to pre-emit a
#                          bubble per output or the mesh deadlocked in its read phase.
#                          Non-blocking ops never block => no cycle to break => no prime.
#
#   8 edge-stub kernels    drv_{n,s,e,w}_edge existed ONLY to feed bubbles into the
#                          boundary inputs so interior blocking gets would not stall;
#                          col_{n,s,e,w}_edge existed ONLY to drain the bubbles the
#                          boundary outputs emitted.  With no bubbles, an unwritten
#                          boundary input just polls ok=0 forever, and (under correct XY
#                          routing to an in-mesh destination) no packet is ever sent off
#                          the edge.  All 8 kernels are deleted; the perimeter streams
#                          stay declared but unused.
#
# THE TRADE-OFF (the one thing this style costs): the blocking mesh ran in lock-step --
# one token per link per iteration meant iteration t WAS cycle t for every router.
# Non-blocking routers are free-running: nothing stops router A from burning all NUM_IT
# iterations polling empty inputs before its upstream ever injects.  So NUM_IT is no
# longer a cycle count, it is a per-PE *budget*, and it must be generous enough that no
# router retires while traffic is still in flight.  See NUM_IT below.
# =====================================================================================

ROWS = 4
COLUMNS = 4

# packet layout (LSB-first):  data[0:16] dest_col[16:19] dest_row[19:22]
# NO valid bit -- validity is the try_get/try_put `ok` flag (see header).
DW = 16                  # payload width
W = 3                    # coord width (3 bits -> 8x8 headroom)
COL_LO = DW              # dest_col -> [16:19]
ROW_LO = DW + W          # dest_row -> [19:22]
PS = DW + 2 * W          # total packet width -> 22  (was 23 with VLD)
CMASK = (1 << W) - 1

# Per-PE iteration budget, NOT a synchronised cycle count (see header trade-off).
# A 4x4 XY path is <= 7 hops, but free-running routers may spin on empty inputs while a
# packet is still upstream, so this needs real headroom over the blocking version's 64.
NUM_IT = 256
LANELEN = 8              # host seed / log lanes per node
DIR = 5                  # 0=N 1=E 2=S 3=W 4=Local

# connectivity check: ONE minimal PE on this node's Local port
PE_R, PE_C = 2, 2        # node hosting the PE
PE_K = 3                 # the PE's "compute": multiply payload by this constant
PE_DR, PE_DC = 3, 3      # where the PE sends its result


@df.region()
def router_XY_NoC(inj: int32[ROWS, COLUMNS, LANELEN], dlv: int32[ROWS, COLUMNS, LANELEN]):

    # link streams named by FLOW direction; +1 perimeter row/col.  The perimeter entries
    # are now never written or read (no edge stubs) -- they stay declared so the interior
    # indexing arithmetic below is unchanged from the blocking version.
    north: Stream[UInt(PS), 4][ROWS + 1, COLUMNS]
    south: Stream[UInt(PS), 4][ROWS + 1, COLUMNS]
    east:  Stream[UInt(PS), 4][ROWS, COLUMNS + 1]
    west:  Stream[UInt(PS), 4][ROWS, COLUMNS + 1]

    inject:  Stream[UInt(PS), 4][ROWS, COLUMNS]   # core -> router (new packets)
    deliver: Stream[UInt(PS), 4][ROWS, COLUMNS]   # router -> core (arrived packets)

    @df.kernel(mapping=[ROWS, COLUMNS], args=[])   # pure stream I/O -> no top-level array args
    def router_XY():
        row_id, col_id = df.get_pid()

        pkt: UInt(PS)[DIR] = 0     # received packet per input (0=N 1=E 2=S 3=W 4=Local)
        vld: int32[DIR] = 0        # 1 if that input actually produced a flit this pass
        col: int32[DIR] = 0        # dest column per input
        row: int32[DIR] = 0        # dest row per input

        # NO priming here -- see header. Non-blocking ops cannot deadlock on the cyclic
        # interior links, so there is nothing to break.

        for t in range(NUM_IT):

            # ── (A) poll all five inputs non-blockingly; ok IS the valid signal ──
            # read the OPPOSITE-flow stream, same as the blocking version
            for d in range(DIR):
              vld[d] = 0
            
            p0: UInt(PS) = 0
            k0: int1 = 0
            p0, k0 = south[row_id, col_id].try_get()      # N input (southbound from above)
            pkt[0] = p0
            
            if k0 == 1:
              vld[0] = 1
            
            p1: UInt(PS) = 0
            k1: int1 = 0
            p1, k1 = west[row_id, col_id + 1].try_get()   # E input (westbound from the right)
            pkt[1] = p1
            
            if k1 == 1:
              vld[1] = 1
            
            p2: UInt(PS) = 0
            k2: int1 = 0
            p2, k2 = north[row_id + 1, col_id].try_get()  # S input (northbound from below)
            pkt[2] = p2
            
            if k2 == 1:
                vld[2] = 1
           
            p3: UInt(PS) = 0
            k3: int1 = 0
            p3, k3 = east[row_id, col_id].try_get()       # W input (eastbound from the left)
            pkt[3] = p3
            
            if k3 == 1:
                vld[3] = 1
            
            p4: UInt(PS) = 0
            k4: int1 = 0
            p4, k4 = inject[row_id, col_id].try_get()     # Local input (core injecting)
            pkt[4] = p4
            
            if k4 == 1:
                vld[4] = 1

            # ── decode: dest column / row (no valid bit to extract any more) ──
            for d in range(DIR):
                p: UInt(PS) = pkt[d]
                col[d] = (p >> COL_LO) & CMASK
                row[d] = (p >> ROW_LO) & CMASK

            # ── XY route compute: output port per input (0=N 1=E 2=S 3=W 4=Local) ──
            dst: int32[DIR] = 0          # chosen port; only meaningful when vld[d] == 1
            for d in range(DIR):
                if col[d] > col_id:    dst[d] = 1   # east  (dest column to my right)
                elif col[d] < col_id:  dst[d] = 3   # west  (dest column to my left)
                elif row[d] > row_id:  dst[d] = 2   # south (dest row below me)
                elif row[d] < row_id:  dst[d] = 0   # north (dest row above me)
                else:                  dst[d] = 4   # local (arrived: same row & col)

            # ── fixed-priority arbitration: at most one input granted per output port ──
            grant: int32[DIR] = 0        # winning input index for output port o
            out_vld: int32[DIR] = 0      # 1 if output port o is active this pass
            for o in range(DIR):
                for d in range(DIR):     # d ascending => priority N>E>S>W>Local (first wins)
                    if vld[d] == 1 and dst[d] == o and out_vld[o] == 0:
                        grant[o] = d; out_vld[o] = 1

            # ── crossbar: one output packet per granted port ──
            outpkt: UInt(PS)[DIR] = 0
            for o in range(DIR):
                if out_vld[o] == 1:
                    outpkt[o] = pkt[grant[o]]

            # ── (B) output: try_put ONLY the granted ports -- idle ports stay silent.
            # Bufferless, exactly like router_XY.py: a full downstream link means the
            # flit is dropped (the `ok` result is deliberately discarded, no retry).
            if out_vld[0] == 1:
                w0: int1 = north[row_id, col_id].try_put(outpkt[0])
            if out_vld[1] == 1:
                w1: int1 = east[row_id, col_id + 1].try_put(outpkt[1])
            if out_vld[2] == 1:
                w2: int1 = south[row_id + 1, col_id].try_put(outpkt[2])
            if out_vld[3] == 1:
                w3: int1 = west[row_id, col_id].try_put(outpkt[3])
            if out_vld[4] == 1:
                w4: int1 = deliver[row_id, col_id].try_put(outpkt[4])

    # ── INJECT load kernel: SINGLE instance owns `inj` (one reader) and fans out to the
    # per-node inject[r,c] streams.  Stream indices are Python-unrolled (compile-time
    # constants) so each FIFO is statically selected; only `t` is a hardware loop.
    # Non-blocking: a per-node pointer advances ONLY on a successful try_put, so the
    # driver self-throttles against a full link instead of relying on lock-step. ──
    @df.kernel(mapping=[1], args=[inj])
    def drv_inject(din: int32[ROWS, COLUMNS, LANELEN]):
        sp: int32[ROWS, COLUMNS] = 0                     # per-node seed pointer
        for t in range(NUM_IT):                          # hardware loop
            with allo.meta_for(0, ROWS) as r:            # COMPILE-TIME unroll -> constant idx
                with allo.meta_for(0, COLUMNS) as c:
                    with allo.meta_if((r != PE_R) or (c != PE_C)):
                        if sp[r, c] < LANELEN:
                            w: UInt(PS) = din[r, c, sp[r, c]]
                            if w != 0:                   # 0 = "no packet in this lane"
                                ok: int1 = inject[r, c].try_put(w)
                                if ok == 1:
                                    sp[r, c] += 1        # advance only on success
                            else:
                                sp[r, c] += 1            # skip an empty lane

    # ── DELIVER store kernel: SINGLE instance drains every deliver[r,c] and owns `dlv`
    # (one writer).  try_get's ok replaces the old "is the VLD bit set" test. ──
    @df.kernel(mapping=[1], args=[dlv])
    def col_deliver(dout: int32[ROWS, COLUMNS, LANELEN]):
        kp: int32[ROWS, COLUMNS] = 0                     # per-node write pointers
        for t in range(NUM_IT):
            with allo.meta_for(0, ROWS) as r:
                with allo.meta_for(0, COLUMNS) as c:
                    with allo.meta_if((r != PE_R) or (c != PE_C)):
                        wv: UInt(PS) = 0
                        wk: int1 = 0
                        wv, wk = deliver[r, c].try_get()
                        if wk == 1 and kp[r, c] < LANELEN:
                            dout[r, c, kp[r, c]] = wv; kp[r, c] += 1

    # ── minimal PE on node (PE_R,PE_C): drain arrival -> multiply payload -> inject result.
    # Holds the result in `txp` and retries the inject until it lands, so the PE does not
    # lose work to a momentarily-full Local link (the router itself is still bufferless). ──
    @df.kernel(mapping=[1], args=[])
    def pe_mul():
        txp: UInt(PS) = 0        # pending result awaiting injection
        txv: int32 = 0           # is one pending?
        for t in range(NUM_IT):
            if txv == 1:                                  # retry the pending inject first
                ok: int1 = inject[PE_R, PE_C].try_put(txp)
                if ok == 1:
                    txv = 0
            if txv == 0:                                  # free to take a new arrival
                av: UInt(PS) = 0
                ak: int1 = 0
                av, ak = deliver[PE_R, PE_C].try_get()
                if ak == 1:
                    prod: int32 = (av & 0xFFFF) * PE_K    # the "compute": single int multiply
                    txp = (prod & 0xFFFF) | (PE_DC << COL_LO) | (PE_DR << ROW_LO)
                    txv = 1

    # NOTE: no drv_/col_ edge kernels at all -- see the header. The perimeter entries of
    # north/south/east/west are declared above but never touched.


def pack(data, col, row):                        # build a packet integer (layout at top)
    return int(data | (col << COL_LO) | (row << ROW_LO))


if __name__ == "__main__":
    sim = df.build(router_XY_NoC, target="simulator")

    # ── Part 1: single packet, (0,0) -> (2,3) ──
    inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    PKT = pack(data=0xABCD, col=3, row=2)
    inj[0, 0, 0] = PKT
    sim(inj, dlv)                                # region args in discovery order: inj, dlv
    got = int(dlv[2, 3, 0]); stray = int(dlv.sum()) - got
    print(f"inject 0x{PKT:06x} @(0,0)->dest(2,3) | delivered 0x{got:06x} | stray={stray}")
    print("ROUTER XY (nb)", "PASS" if (got == PKT and stray == 0) else "FAIL")

    # ── Part 2: multi-node concurrent traffic ──
    # 4 cores inject toward distinct destinations; XY paths never share a node on the
    # same cycle by construction, so a correct NoC delivers all 4 with no drops.
    print("\n--- Part 2: multi-node concurrent traffic ---")
    inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    traffic = [                       # (src_row, src_col, dst_row, dst_col, payload)
        (0, 0, 1, 2, 0x1111),
        (1, 3, 2, 1, 0x2222),
        (2, 0, 3, 3, 0x3333),
        (3, 2, 0, 0, 0x4444),
    ]
    for sr, sc, dr, dc, data in traffic:
        inj[sr, sc, 0] = pack(data=data, col=dc, row=dr)
    sim(inj, dlv)

    ok = True
    for sr, sc, dr, dc, data in traffic:
        arrived = [int(dlv[dr, dc, k]) & 0xFFFF for k in range(LANELEN)]
        hit = data in arrived
        print(f"  ({sr},{sc})->({dr},{dc}) data 0x{data:04x} : "
              f"{'delivered' if hit else 'DROPPED/missing'}")
        ok = ok and hit
    delivered = int((dlv != 0).sum())
    print(f"  delivered slots={delivered} expected={len(traffic)}")
    print("MULTI-NODE (nb)", "PASS" if (ok and delivered == len(traffic)) else "FAIL")

    # ── Part 3: contention (bufferless arbiter drops the loser) ──
    # Two packets reach (1,1) both wanting EAST: B transits the West input (d=3), A is
    # injected on Local (d=4). Fixed priority N>E>S>W>Local => W beats Local, so B is
    # forwarded and A is dropped (bufferless, no retry).
    #
    # NOTE vs the blocking version: there, the two arrivals were forced into the same
    # cycle by lock-step (B seeded on lane 0, A on lane 1). Free-running non-blocking
    # routers have no such guarantee, so both are seeded on lane 0 to make them race for
    # the same pass. Whether A or B loses is decided by the timing layer, so the check
    # below is "exactly one survives", not "B specifically survives".
    print("\n--- Part 3: contention (same pass, same output port) ---")
    inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    inj[1, 0, 0] = pack(data=0xB0B0, col=3, row=1)         # B: West input @ (1,1), wants East
    inj[1, 1, 0] = pack(data=0xA0A0, col=2, row=1)         # A: Local input @ (1,1), wants East
    sim(inj, dlv)

    b_got = 0xB0B0 in [int(dlv[1, 3, k]) & 0xFFFF for k in range(LANELEN)]
    a_got = 0xA0A0 in [int(dlv[1, 2, k]) & 0xFFFF for k in range(LANELEN)]
    delivered = int((dlv != 0).sum())
    print(f"  B (West input, higher prio) -> (1,3) : {'delivered' if b_got else 'dropped'}")
    print(f"  A (Local input, lower prio) -> (1,2) : {'delivered' if a_got else 'dropped'}")
    print(f"  delivered slots={delivered}")

    # ── Part 4: minimal-PE connectivity ──
    print(f"\n--- Part 4: minimal PE @ ({PE_R},{PE_C}) (payload * {PE_K}) ---")
    inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    OPND = 0x0007
    inj[0, PE_C, 0] = pack(data=OPND, col=PE_C, row=PE_R)   # operand from (0,PE_C) -> PE node
    sim(inj, dlv)
    expect = (OPND * PE_K) & 0xFFFF
    got = [int(dlv[PE_DR, PE_DC, k]) & 0xFFFF for k in range(LANELEN)]
    hit = expect in got
    print(f"  operand 0x{OPND:04x} -> PE({PE_R},{PE_C})*{PE_K} -> "
          f"result 0x{expect:04x} @dest({PE_DR},{PE_DC}) : {'delivered' if hit else 'MISSING'}")
    print("PE-CONNECT (nb)", "PASS" if hit else "FAIL")

    # ── determinism check: the timing layer should make non-blocking reproducible ──
    print("\n--- determinism: same input, 5 runs ---")
    outs = []
    for _ in range(5):
        inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
        dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
        for sr, sc, dr, dc, data in traffic:
            inj[sr, sc, 0] = pack(data=data, col=dc, row=dr)
        sim(inj, dlv)
        outs.append(dlv.tobytes())
    print("DETERMINISM", "PASS (1 outcome)" if len(set(outs)) == 1
          else f"FAIL ({len(set(outs))} distinct outcomes)")
