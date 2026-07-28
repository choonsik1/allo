import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import allo
from allo.ir.types import int32, int1, UInt, Stream
import allo.dataflow as df
import numpy as np

# =====================================================================================
# RaveNoC-style MESH -- ROWS x COLS routers, one FUSED router kernel per node.
#
# The point of this file is a feasibility question, not a new design: the split router
# (router_rvn_ports.py) costs 10 PEs per node, so a 4x4 mesh would be 160 PEs and runs
# straight into the long-standing 4x4 simulator wall.  The fused router is 1 PE per node,
# so a 4x4 is 16 PEs + harness.  If that runs, the mesh is unblocked WITHOUT the Stage-2
# global cycle barrier; if it does not, the barrier is confirmed as genuinely required
# rather than merely suspected.  Set MESH=4 to switch.
#
# Router body is router_rvn_fused.py unchanged (true request/grant crossbar, per-output
# round-robin, registered output).  The only new thing here is the inter-router wiring.
#
# LINK CONVENTION -- taken from router_XY.py so both meshes wire identically.  Arrays are
# halo-sized (ROWS+1 / COLS+1) so that a neighbour index never runs off the end, and a
# stream index may be pid arithmetic (`north[r+1, c]`) but nothing more complex.
#   north[r, c]   northbound, leaving (r,c) upward      -> read by (r-1,c) as its S input
#   south[r+1, c] southbound, leaving (r,c) downward    -> read by (r+1,c) as its N input
#   east[r, c+1]  eastbound,  leaving (r,c) rightward   -> read by (r,c+1) as its W input
#   west[r, c]    westbound,  leaving (r,c) leftward    -> read by (r,c-1) as its E input
# so, read from the perspective of router (r,c), its five INPUTS are:
#   N <- south[r, c]      S <- north[r+1, c]      W <- east[r, c]
#   E <- west[r, c+1]     L <- inject[r, c]
#
# EDGE LINKS: the halo entries exist but are never written, because XY routing never
# sends a flit off-mesh so long as every destination is a real node.  Keep it that way --
# a flit written to an edge link would sit in a FIFO nobody drains and would block that
# input port permanently.  Tests below only ever address in-mesh coordinates.
# =====================================================================================

NORTH, SOUTH, WEST, EAST, LOCAL = 0, 1, 2, 3, 4
DIR = 5

MESH = int(os.environ.get("MESH", "2"))
ROWS = MESH
COLS = MESH

DW = 16
W = 3                     # 3-bit coords -> up to 8x8
X_LO = DW
Y_LO = DW + W
PS = DW + 2 * W
CMASK = (1 << W) - 1

# Multi-hop needs a far bigger drain budget than the single-router tests: a 4x4 corner-to-
# corner route is 6 hops and every hop costs several passes.  Under-sizing this looks
# exactly like a lost packet -- see router_rvn_ports.py.
NUM_IT = int(os.environ.get("NUM_IT", "400"))
LANELEN = 4


@df.region()
def mesh(inj: int32[ROWS, COLS, LANELEN], dlv: int32[ROWS, COLS, LANELEN]):
    north: Stream[UInt(PS), 4][ROWS + 1, COLS]
    south: Stream[UInt(PS), 4][ROWS + 1, COLS]
    east:  Stream[UInt(PS), 4][ROWS, COLS + 1]
    west:  Stream[UInt(PS), 4][ROWS, COLS + 1]
    inject:  Stream[UInt(PS), 4][ROWS, COLS]
    deliver: Stream[UInt(PS), 4][ROWS, COLS]

    @df.kernel(mapping=[ROWS, COLS], args=[])
    def router():
        r, c = df.get_pid()          # this node's address == RaveNoC ROUTER_X_ID/Y_ID
        held: UInt(PS)[DIR] = 0
        hvld: int32[DIR] = 0         # 0 = empty, 2 = latched but not yet routed, 1 = ready
        hdst: int32[DIR] = 0
        oreg: UInt(PS)[DIR] = 0
        ovld: int32[DIR] = 0
        rr: int32[DIR] = 0

        for t in range(NUM_IT):
            # (a) EMIT last pass's grants. Five separate links, so five explicit
            # statements -- each index expression differs, so no meta_for can fold them.
            if ovld[NORTH] == 1:
                e0: int1 = north[r, c].try_put(oreg[NORTH])
                if e0 == 1:
                    ovld[NORTH] = 0
            if ovld[SOUTH] == 1:
                e1: int1 = south[r + 1, c].try_put(oreg[SOUTH])
                if e1 == 1:
                    ovld[SOUTH] = 0
            if ovld[WEST] == 1:
                e2: int1 = west[r, c].try_put(oreg[WEST])
                if e2 == 1:
                    ovld[WEST] = 0
            if ovld[EAST] == 1:
                e3: int1 = east[r, c + 1].try_put(oreg[EAST])
                if e3 == 1:
                    ovld[EAST] = 0
            if ovld[LOCAL] == 1:
                e4: int1 = deliver[r, c].try_put(oreg[LOCAL])
                if e4 == 1:
                    ovld[LOCAL] = 0

            # (b) ACCEPT one flit per input port. Marked state 2 = "latched, unrouted" so
            # the route computation can be a single shared loop below instead of being
            # copy-pasted five times.
            if hvld[NORTH] == 0:
                v0: UInt(PS) = 0
                k0: int1 = 0
                v0, k0 = south[r, c].try_get()
                if k0 == 1:
                    held[NORTH] = v0
                    hvld[NORTH] = 2
            if hvld[SOUTH] == 0:
                v1: UInt(PS) = 0
                k1: int1 = 0
                v1, k1 = north[r + 1, c].try_get()
                if k1 == 1:
                    held[SOUTH] = v1
                    hvld[SOUTH] = 2
            if hvld[WEST] == 0:
                v2: UInt(PS) = 0
                k2: int1 = 0
                v2, k2 = east[r, c].try_get()
                if k2 == 1:
                    held[WEST] = v2
                    hvld[WEST] = 2
            if hvld[EAST] == 0:
                v3: UInt(PS) = 0
                k3: int1 = 0
                v3, k3 = west[r, c + 1].try_get()
                if k3 == 1:
                    held[EAST] = v3
                    hvld[EAST] = 2
            if hvld[LOCAL] == 0:
                v4: UInt(PS) = 0
                k4: int1 = 0
                v4, k4 = inject[r, c].try_get()
                if k4 == 1:
                    held[LOCAL] = v4
                    hvld[LOCAL] = 2

            # (c) ROUTE whatever was just latched. Touches no streams, so one plain loop
            # covers all five ports. RaveNoC input_router.sv, XYAlg branch: resolve x
            # against this node's row, then y against its column, then eject.
            for ip in range(DIR):
                if hvld[ip] == 2:
                    xd: int32 = (held[ip] >> X_LO) & CMASK
                    yd: int32 = (held[ip] >> Y_LO) & CMASK
                    if xd == r and yd == c:
                        hdst[ip] = LOCAL
                    elif xd == r:
                        if yd < c:
                            hdst[ip] = WEST
                        else:
                            hdst[ip] = EAST
                    else:
                        if xd > r:
                            hdst[ip] = SOUTH
                        else:
                            hdst[ip] = NORTH
                    hvld[ip] = 1

            # (d) CROSSBAR = request/grant, exactly as router_rvn_fused.py. Local arrays
            # only, so the arbiter can inspect requests without consuming them.
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
    def drv(din: int32[ROWS, COLS, LANELEN]):
        sp: int32[ROWS, COLS] = 0
        for t in range(NUM_IT):
            with allo.meta_for(0, ROWS) as r:
                with allo.meta_for(0, COLS) as c:
                    if sp[r, c] < LANELEN:
                        w: UInt(PS) = din[r, c, sp[r, c]]
                        if w != 0:
                            ok: int1 = inject[r, c].try_put(w)
                            if ok == 1:
                                sp[r, c] += 1
                        else:
                            sp[r, c] += 1

    @df.kernel(mapping=[1], args=[dlv])
    def col(dout: int32[ROWS, COLS, LANELEN]):
        kp: int32[ROWS, COLS] = 0
        for t in range(NUM_IT):
            with allo.meta_for(0, ROWS) as r:
                with allo.meta_for(0, COLS) as c:
                    wv: UInt(PS) = 0
                    wk: int1 = 0
                    wv, wk = deliver[r, c].try_get()
                    if wk == 1 and kp[r, c] < LANELEN:
                        dout[r, c, kp[r, c]] = wv
                        kp[r, c] += 1


def pack(data, x, y):
    return int(data | (x << X_LO) | (y << Y_LO))


def run(sim, seeds, label):
    """seeds: (src_r, src_c, lane, data, dst_r, dst_c)"""
    inj = np.zeros((ROWS, COLS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLS, LANELEN), dtype=np.int32)
    for sr, sc, lane, data, dr, dc in seeds:
        inj[sr, sc, lane] = pack(data, dr, dc)
    sim(inj, dlv)
    print(f"\n--- {label} ---")
    return dlv


def at(dlv, r, c):
    return [int(dlv[r, c, k]) & 0xFFFF for k in range(LANELEN)]


if __name__ == "__main__":
    print(f"mesh {ROWS}x{COLS}  ->  {ROWS*COLS} router PEs + drv + col "
          f"= {ROWS*COLS+2} PEs   (NUM_IT={NUM_IT})")
    sim = df.build(mesh, target="simulator")

    # M1: one packet, corner to opposite corner -- the longest XY route in the mesh, so
    # it exercises both the x phase and the y phase and every intermediate hop.
    hops = (ROWS - 1) + (COLS - 1)
    dlv = run(sim, [(0, 0, 0, 0xA1, ROWS - 1, COLS - 1)],
              f"M1: (0,0) -> ({ROWS-1},{COLS-1}), {hops} hops")
    m1 = 0xA1 in at(dlv, ROWS - 1, COLS - 1)
    print(f"  0xA1 at ({ROWS-1},{COLS-1}) : {'arrived' if m1 else 'MISSING'}")
    print("M1", "PASS" if m1 else "FAIL")

    # M2: every node sends one packet to its diagonal neighbour (wrapping). A permutation,
    # so every router routes and every link carries traffic simultaneously.
    seeds, expect = [], {}
    for r in range(ROWS):
        for c in range(COLS):
            dr, dc = (r + 1) % ROWS, (c + 1) % COLS
            d = 0xB000 + r * 16 + c
            seeds.append((r, c, 0, d, dr, dc))
            expect[(dr, dc)] = d
    dlv = run(sim, seeds, "M2: all-node permutation (every node sends and receives)")
    bad = [(k, v) for k, v in expect.items() if v not in at(dlv, k[0], k[1])]
    for (r, c), d in sorted(expect.items()):
        print(f"  node ({r},{c}) expects {hex(d)} : "
              f"{'ok' if d in at(dlv, r, c) else 'MISSING'}")
    print("M2", "PASS" if not bad else f"FAIL ({len(bad)}/{len(expect)} missing)")

    cyc = sim.get_cycles().per_pe
    rt = {k: v for k, v in cyc.items() if k.startswith("router")}
    print(f"\nrouter PEs: {len(rt)}   min={min(rt.values())}  max={max(rt.values())}"
          f"  spread={max(rt.values())/max(1,min(rt.values())):.1f}x")
    print("drv/col:", {k: v for k, v in cyc.items() if not k.startswith("router")})
