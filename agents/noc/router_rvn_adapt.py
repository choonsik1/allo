import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import allo
from allo.ir.types import int32, int1, UInt, Stream
import allo.dataflow as df
import numpy as np

# =====================================================================================
# CONGESTION-AWARE (MINIMAL-ADAPTIVE) ROUTER.
#
# router_rvn_fused.py with one thing changed: the route function.  Everything else --
# the request/grant crossbar, the per-output round-robin, the registered output -- is
# untouched, so any behaviour difference is attributable to routing alone.
#
# WHAT "MINIMAL ADAPTIVE" MEANS.  For a flit at (RX,RY) heading to (xd,yd) there are at
# most TWO productive directions -- one that reduces the row distance, one that reduces
# the column distance.  XY always takes the x one first.  Minimal-adaptive takes EITHER,
# choosing whichever neighbour is less congested; "minimal" because it never picks a
# non-productive direction (no misrouting, no livelock).  Three cases:
#
#   both coords match            -> LOCAL          (deterministic: arrived)
#   only the column is wrong     -> WEST/EAST      (deterministic: one productive port)
#   only the row is wrong        -> NORTH/SOUTH    (deterministic: one productive port)
#   BOTH wrong                   -> the choice     <- the only adaptive decision
#
# So the adaptivity is confined to the "both dimensions unresolved" case, which is
# exactly where XY's ordering was arbitrary in the first place.
#
# WHERE THE CONGESTION SIGNAL COMES FROM, AND WHY IT IS NOT A WIRE.
# `cong[d]` is the backpressure at the neighbour reached through output port d (0 = free,
# larger = more congested).  Here it is a HOST input so tests can drive it directly and
# the routing decision is observable in isolation.  In a mesh it would come from the
# neighbouring router -- and it MUST cross a register to get here:
#
#     router A's congestion -> B, and B's -> A, is a CYCLE.  A pure Wire is
#     combinational, so a wire cycle is a combinational loop and cannot be scheduled.
#
# Real NoCs register it and act on a one-cycle-stale value; that is not an approximation
# forced on us, it is what the hardware does.  So the mesh version of this file wants a
# depth-1 Stream (or a Channel) for the congestion path, NOT a Wire.  Wires remain right
# for FEED-FORWARD sidebands (e.g. a request line from input module to output module),
# where no cycle exists.
#
# THE COST OF ADAPTIVITY -- STATE IT, DO NOT BURY IT.  XY is deadlock-free by
# construction: forcing every packet to finish x before starting y makes a cyclic channel
# dependency impossible.  This router gives that up.  Two packets can hold the channel the
# other needs (one turned x->y, the other y->x) and neither can advance.  The standard fix
# is virtual channels (see router_rvn_vc.py) or a turn model that forbids one turn.  This
# file does NEITHER, so it is a routing-policy demonstrator, not a drop-in mesh router.
# =====================================================================================

NORTH, SOUTH, WEST, EAST, LOCAL = 0, 1, 2, 3, 4
DIR = 5

ROUTER_X = 2          # placed mid-grid so BOTH dimensions can be unresolved in a test
ROUTER_Y = 2

DW = 16
W = 3
X_LO = DW
Y_LO = DW + W
PS = DW + 2 * W
CMASK = (1 << W) - 1

NUM_IT = 160
LANELEN = 16


# Congestion is a BUILD parameter, not a runtime input -- see make_router() below for
# why (an allo bug makes a stream-forwarding kernel that OWNS an array arg move no data).
CONG = (0, 0, 0, 0, 0)

# Derived build-time preferences: 1 = take the x direction, 0 = take the y direction.
# One per (x-candidate, y-candidate) pair; only these four combinations can arise.
PREF_NW = 1
PREF_NE = 1
PREF_SW = 1
PREF_SE = 1


def make_router(cong):
    """Construct the region for a given per-direction congestion vector.

    `cong` is baked in at build time by rebinding the module global before the region is
    defined -- allo resolves constants in a kernel body from the region function's
    __globals__ at build time. Same trick as build_router(nvc) in router_rvn_vc.py.

    WHY NOT A RUNTIME ARG: giving the router kernel `args=[cong]` makes the design
    deliver NOTHING on the simulator -- reproduced minimally (scratchpad/argtest.py):
    two identical routers, one with args=[] (works) and one owning an unused array arg
    (moves no data). drv/col own arrays fine, so it is specific to the kernel doing the
    stream-to-stream forwarding. Baking the value in sidesteps it entirely.
    """
    global CONG, PREF_NW, PREF_NE, PREF_SW, PREF_SE
    CONG = tuple(cong)
    PREF_NW = 1 if CONG[NORTH] <= CONG[WEST] else 0
    PREF_NE = 1 if CONG[NORTH] <= CONG[EAST] else 0
    PREF_SW = 1 if CONG[SOUTH] <= CONG[WEST] else 0
    PREF_SE = 1 if CONG[SOUTH] <= CONG[EAST] else 0

    @df.region()
    def router_rvn_a(inj: int32[DIR, LANELEN], dlv: int32[DIR, LANELEN]):
        ext_in:  Stream[UInt(PS), 4][DIR]
        ext_out: Stream[UInt(PS), 4][DIR]

        @df.kernel(mapping=[1], args=[])
        def router():
            held: UInt(PS)[DIR] = 0
            hvld: int32[DIR] = 0
            hdst: int32[DIR] = 0
            oreg: UInt(PS)[DIR] = 0
            ovld: int32[DIR] = 0
            rr: int32[DIR] = 0

            for t in range(NUM_IT):
                # (a) emit last pass's grants -- registered output, unchanged.
                with allo.meta_for(0, DIR) as o:
                    if ovld[o] == 1:
                        e: int1 = ext_out[o].try_put(oreg[o])
                        if e == 1:
                            ovld[o] = 0

                # (b) accept + ADAPTIVE route.
                with allo.meta_for(0, DIR) as i:
                    if hvld[i] == 0:
                        v: UInt(PS) = 0
                        ok: int1 = 0
                        v, ok = ext_in[i].try_get()
                        if ok == 1:
                            held[i] = v
                            xd: int32 = (v >> X_LO) & CMASK
                            yd: int32 = (v >> Y_LO) & CMASK
                            if xd == ROUTER_X and yd == ROUTER_Y:
                                hdst[i] = LOCAL              # arrived
                            elif xd == ROUTER_X:
                                # row already right -> only the column is productive
                                if yd < ROUTER_Y:
                                    hdst[i] = WEST
                                else:
                                    hdst[i] = EAST
                            elif yd == ROUTER_Y:
                                # column already right -> only the row is productive
                                if xd > ROUTER_X:
                                    hdst[i] = SOUTH
                                else:
                                    hdst[i] = NORTH
                            else:
                                # BOTH dimensions unresolved: two productive ports exist,
                                # and choosing between them is the whole adaptive decision.
                                #
                                # Congestion is baked in at build time, so "which side
                                # wins" is a BUILD-TIME boolean -- one per (xdir, ydir)
                                # pair, and there are only four pairs. That matters
                                # because allo resolves SCALAR int globals in a kernel
                                # body but NOT an indexable tuple global: `CONG[xdir]`
                                # with a runtime xdir raises "Unsupported global
                                # variable". Four scalars sidestep it and cost nothing.
                                #
                                # Each PREF_* is 1 if the x direction is preferred (i.e.
                                # no more congested). Ties favour x, so the
                                # no-congestion case behaves EXACTLY like XY -- which is
                                # what makes A1 a true baseline.
                                if xd > ROUTER_X:                 # xdir = SOUTH
                                    if yd > ROUTER_Y:             # ydir = EAST
                                        if PREF_SE == 1:
                                            hdst[i] = SOUTH
                                        else:
                                            hdst[i] = EAST
                                    else:                         # ydir = WEST
                                        if PREF_SW == 1:
                                            hdst[i] = SOUTH
                                        else:
                                            hdst[i] = WEST
                                else:                             # xdir = NORTH
                                    if yd > ROUTER_Y:             # ydir = EAST
                                        if PREF_NE == 1:
                                            hdst[i] = NORTH
                                        else:
                                            hdst[i] = EAST
                                    else:                         # ydir = WEST
                                        if PREF_NW == 1:
                                            hdst[i] = NORTH
                                        else:
                                            hdst[i] = WEST
                            hvld[i] = 1

                # (c) crossbar: request/grant over local arrays (identical to the base file).
                for op in range(DIR):
                    if ovld[op] == 0:
                        won: int32 = 0
                        for k in range(DIR):
                            sidx: int32 = rr[op] + k
                            if sidx >= DIR:
                                sidx -= DIR
                            if won == 0 and hvld[sidx] == 1 and hdst[sidx] == op:
                                oreg[op] = held[sidx]
                                hvld[sidx] = 0
                                ovld[op] = 1
                                won = 1
                                nxt: int32 = sidx + 1
                                if nxt >= DIR:
                                    nxt -= DIR
                                rr[op] = nxt

        @df.kernel(mapping=[1], args=[inj])
        def drv(din: int32[DIR, LANELEN]):
            sp: int32[DIR] = 0
            for t in range(NUM_IT):
                with allo.meta_for(0, DIR) as i:
                    if sp[i] < LANELEN:
                        w: UInt(PS) = din[i, sp[i]]
                        if w != 0:
                            ok: int1 = ext_in[i].try_put(w)
                            if ok == 1:
                                sp[i] += 1
                        else:
                            sp[i] += 1

        @df.kernel(mapping=[1], args=[dlv])
        def col(dout: int32[DIR, LANELEN]):
            kp: int32[DIR] = 0
            for t in range(NUM_IT):
                with allo.meta_for(0, DIR) as o:
                    wv: UInt(PS) = 0
                    wk: int1 = 0
                    wv, wk = ext_out[o].try_get()
                    if wk == 1 and kp[o] < LANELEN:
                        dout[o, kp[o]] = wv
                        kp[o] += 1


    return router_rvn_a


def pack(data, x, y):
    return int(data | (x << X_LO) | (y << Y_LO))


NAME = {NORTH: "N", SOUTH: "S", WEST: "W", EAST: "E", LOCAL: "L"}


def run_cong(seeds, congestion):
    """Build a router with this congestion baked in, then run the traffic through it."""
    sim = df.build(make_router(congestion), target="simulator")
    inj = np.zeros((DIR, LANELEN), dtype=np.int32)
    dlv = np.zeros((DIR, LANELEN), dtype=np.int32)
    for p, lane, w in seeds:
        inj[p, lane] = w
    sim(inj, dlv)
    return dlv


def arrived(dlv, port):
    return [int(dlv[port, k]) & 0xFFFF for k in range(LANELEN) if dlv[port, k]]


def where(dlv, payload):
    """Which output port did this payload leave by? -1 if it never arrived."""
    for p in (NORTH, SOUTH, WEST, EAST, LOCAL):
        if payload in arrived(dlv, p):
            return p
    return -1


if __name__ == "__main__":
    free = [0, 0, 0, 0, 0]
    ok = True

    # A flit from LOCAL to (ROUTER_X+1, ROUTER_Y+1): BOTH dimensions unresolved, so the
    # productive pair is {SOUTH (row), EAST (column)} and the router must choose.
    dst_x, dst_y = ROUTER_X + 1, ROUTER_Y + 1

    # A1 -- no congestion: ties go to x, so this must match plain XY (SOUTH).
    dlv = run_cong([(LOCAL, 0, pack(0xA01, dst_x, dst_y))], free)
    got = where(dlv, 0xA01)
    print(f"\nA1 no congestion        : left by {NAME.get(got, 'NOWHERE')}  (XY baseline = S)")
    print("A1", "PASS" if got == SOUTH else "FAIL")
    ok &= got == SOUTH

    # A2 -- the x neighbour (SOUTH) is congested: the router must DIVERT to EAST.
    # This is the whole point of the design.
    cg = [0, 0, 0, 0, 0]
    cg[SOUTH] = 7
    dlv = run_cong([(LOCAL, 0, pack(0xA02, dst_x, dst_y))], cg)
    got = where(dlv, 0xA02)
    print(f"\nA2 SOUTH congested      : left by {NAME.get(got, 'NOWHERE')}  (want E -- diverted)")
    print("A2", "PASS (adapted)" if got == EAST else "FAIL (did not adapt)")
    ok &= got == EAST

    # A3 -- congest the OTHER one instead: it must swing back to SOUTH. Proves the
    # decision tracks the signal rather than being a fixed alternative.
    cg = [0, 0, 0, 0, 0]
    cg[EAST] = 7
    dlv = run_cong([(LOCAL, 0, pack(0xA03, dst_x, dst_y))], cg)
    got = where(dlv, 0xA03)
    print(f"\nA3 EAST congested       : left by {NAME.get(got, 'NOWHERE')}  (want S -- swung back)")
    print("A3", "PASS (adapted)" if got == SOUTH else "FAIL")
    ok &= got == SOUTH

    # A4 -- CONTROL. Only ONE dimension is wrong, so there is exactly one productive
    # port and congestion must be IGNORED. Without this, A2 could be explained by "the
    # router just avoids congested ports", which would be misrouting, not minimal-adaptive.
    cg = [0, 0, 0, 0, 0]
    cg[EAST] = 7
    dlv = run_cong([(LOCAL, 0, pack(0xA04, ROUTER_X, ROUTER_Y + 1))], cg)   # column only
    got = where(dlv, 0xA04)
    print(f"\nA4 control, 1 productive: left by {NAME.get(got, 'NOWHERE')}  "
          f"(want E even though E is congested)")
    print("A4", "PASS (stayed minimal)" if got == EAST else "FAIL (misrouted)")
    ok &= got == EAST

    print("\n=== summary:", "ALL PASS" if ok else "FAILURES", "===")
