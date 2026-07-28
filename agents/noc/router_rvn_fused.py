import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import allo
from allo.ir.types import int32, int1, UInt, Stream
import allo.dataflow as df
import numpy as np

# =====================================================================================
# RaveNoC-style router -- FUSED variant: the whole router is ONE @df.kernel.
#
# Companion to router_rvn_ports.py (one kernel per port).  Same router, same routing,
# same round-robin; the ONLY difference is where the module boundary sits.  Keep both:
# they are the two ends of the modularity/cost trade and are meant to be compared.
#
#   router_rvn_ports.py   10 port kernels + drv + col = 12 PEs, 35 streams
#   router_rvn_fused.py    1 router kernel + drv + col =  3 PEs, 10 streams
#
# WHY THE STREAM COUNT COLLAPSES 35 -> 10:
# the 25-FIFO crossbar in the split version was never the hardware -- RaveNoC's crossbar
# is the two always_comb mapping blocks in router_ravenoc.sv, i.e. wires and a mux, with
# storage only in the input buffers and the output register.  Those 25 FIFOs existed
# purely because a kernel boundary must become a link.  Remove the boundary and the
# crossbar goes back to being what it is in the RTL: array indexing.  Only the 5 input
# and 5 output PORT links survive, and those are real.
#
# WHAT FUSION BUYS BACK -- TRUE REQUEST/GRANT:
# the split version had to latch each source at the output BEFORE arbitrating, because a
# Stream cannot be peeked and try_get consumes the losers.  Here the input registers are
# ordinary local arrays, so the arbiter can READ hvld[]/hdst[] without consuming: the
# pair (hvld[i]==1 && hdst[i]==o) IS RaveNoC's request wire (s_router_ports_t), and the
# flit moves only on a grant.  So this variant is the MORE faithful of the two --
# it drops both the phantom buffering and the extra pipeline stage.
#
# WHAT IT COSTS: a single PE serialises all five ports' work per pass, so expect the
# per-PE cycle count to be roughly the sum of the split version's rather than its max.
# That is the trade to measure -- compare get_cycles() between the two files.
#
# Stage 0 scope is unchanged: 1 VC, single-flit packets, XY routing.
# =====================================================================================

NORTH, SOUTH, WEST, EAST, LOCAL = 0, 1, 2, 3, 4
DIR = 5

ROUTER_X = 1
ROUTER_Y = 1

DW = 16
W = 3
X_LO = DW
Y_LO = DW + W
PS = DW + 2 * W
CMASK = (1 << W) - 1

# Harness budgets, not hardware -- see router_rvn_ports.py for how under-sizing these
# fakes a routing bug.  Raise BOTH before suspecting the router.
NUM_IT = 160
LANELEN = 16


@df.region()
def router_rvn_f(inj: int32[DIR, LANELEN], dlv: int32[DIR, LANELEN]):
    # Only the port links remain.  No crossbar streams: the crossbar is local state.
    ext_in:  Stream[UInt(PS), 4][DIR]
    ext_out: Stream[UInt(PS), 4][DIR]

    @df.kernel(mapping=[1], args=[])
    def router():
        # input modules (RaveNoC input_module x5), one register set per input port
        held: UInt(PS)[DIR] = 0
        hvld: int32[DIR] = 0
        hdst: int32[DIR] = 0
        # output modules (RaveNoC output_module x5): output register + per-output arbiter
        oreg: UInt(PS)[DIR] = 0
        ovld: int32[DIR] = 0
        rr: int32[DIR] = 0

        for t in range(NUM_IT):
            # (a) EMIT first: what leaves now was granted LAST pass.  Same output
            # register as the split version, and the same reason -- it is the loop
            # breaker once a mesh closes a cycle through depth-0 links.
            with allo.meta_for(0, DIR) as o:
                if ovld[o] == 1:
                    e: int1 = ext_out[o].try_put(oreg[o])
                    if e == 1:
                        ovld[o] = 0

            # (b) ACCEPT + ROUTE: one flit per input port, route computed once at latch
            # time, then held until an output grants it.  Holding is what makes the
            # router lossless -- a refused flit waits, it is never dropped.
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
                            hdst[i] = LOCAL
                        elif xd == ROUTER_X:
                            if yd < ROUTER_Y:
                                hdst[i] = WEST
                            else:
                                hdst[i] = EAST
                        else:
                            if xd > ROUTER_X:
                                hdst[i] = SOUTH
                            else:
                                hdst[i] = NORTH
                        hvld[i] = 1

            # (c) CROSSBAR = REQUEST/GRANT.  Plain runtime loops: these touch only local
            # arrays, so the compile-time-constant rule that forced meta_for on stream
            # indices does not apply.  `hvld[s]==1 and hdst[s]==op` is the request wire;
            # the flit moves ONLY here, on an actual grant -- nothing is latched
            # speculatively, so there is no phantom buffering and no extra stage.
            for op in range(DIR):
                if ovld[op] == 0:
                    won: int32 = 0
                    for k in range(DIR):
                        sidx: int32 = rr[op] + k
                        if sidx >= DIR:
                            sidx -= DIR
                        if won == 0 and hvld[sidx] == 1 and hdst[sidx] == op:
                            oreg[op] = held[sidx]
                            hvld[sidx] = 0      # input register freed: grant, not peek
                            ovld[op] = 1
                            won = 1
                            nxt: int32 = sidx + 1
                            if nxt >= DIR:
                                nxt -= DIR
                            rr[op] = nxt        # winner drops to lowest priority

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


def pack(data, x, y):
    return int(data | (x << X_LO) | (y << Y_LO))


PORT_NAME = {NORTH: "N", SOUTH: "S", WEST: "W", EAST: "E", LOCAL: "L"}


def run(sim, seeds, label):
    inj = np.zeros((DIR, LANELEN), dtype=np.int32)
    dlv = np.zeros((DIR, LANELEN), dtype=np.int32)
    for p, lane, data, x, y in seeds:
        inj[p, lane] = pack(data, x, y)
    sim(inj, dlv)
    print(f"\n--- {label} ---")
    return dlv


def arrived(dlv, port):
    return [int(dlv[port, k]) & 0xFFFF for k in range(LANELEN)]


if __name__ == "__main__":
    sim = df.build(router_rvn_f, target="simulator")

    # Same four tests as router_rvn_ports.py, so the two files are directly comparable.
    dlv = run(sim, [(p, 0, 0x100 + p, ROUTER_X, ROUTER_Y)
                    for p in (NORTH, SOUTH, WEST, EAST)],
              "T1: 4 inputs -> LOCAL (ejection)")
    got = arrived(dlv, LOCAL)
    ok1 = all((0x100 + p) in got for p in (NORTH, SOUTH, WEST, EAST))
    for p in (NORTH, SOUTH, WEST, EAST):
        print(f"  in {PORT_NAME[p]} -> LOCAL : "
              f"{'ok' if (0x100 + p) in got else 'MISSING'}")
    print("T1", "PASS" if ok1 else "FAIL")

    cases = [(0x201, ROUTER_X - 1, ROUTER_Y, NORTH),
             (0x202, ROUTER_X + 1, ROUTER_Y, SOUTH),
             (0x203, ROUTER_X,     ROUTER_Y - 1, WEST),
             (0x204, ROUTER_X,     ROUTER_Y + 1, EAST)]
    ok2 = True
    dlv = run(sim, [(LOCAL, k, d, x, y) for k, (d, x, y, _) in enumerate(cases)],
              "T2: LOCAL -> each direction (XY routing)")
    for d, x, y, want in cases:
        hit = d in arrived(dlv, want)
        print(f"  dest({x},{y}) -> {PORT_NAME[want]} : {'ok' if hit else 'MISSING'}")
        ok2 = ok2 and hit
    print("T2", "PASS" if ok2 else "FAIL")

    dlv = run(sim, [(NORTH, 0, 0x301, ROUTER_X, ROUTER_Y + 1),
                    (SOUTH, 0, 0x302, ROUTER_X, ROUTER_Y + 1)],
              "T3: 2 inputs contend for EAST (must be lossless)")
    east = arrived(dlv, EAST)
    both = (0x301 in east) and (0x302 in east)
    print(f"  0x301 : {'delivered' if 0x301 in east else 'LOST'}")
    print(f"  0x302 : {'delivered' if 0x302 in east else 'LOST'}")
    print("T3", "PASS (lossless)" if both else "FAIL (a flit was dropped)")

    seeds = []
    for p in (NORTH, SOUTH, WEST, LOCAL):
        for lane in range(3):
            seeds.append((p, lane, 0x400 + 0x10 * p + lane, ROUTER_X, ROUTER_Y + 1))
    dlv = run(sim, seeds, "T4: 4 sources -> EAST, round-robin fairness")
    east = arrived(dlv, EAST)
    per_src = {p: sum(1 for lane in range(3)
                      if (0x400 + 0x10 * p + lane) in east)
               for p in (NORTH, SOUTH, WEST, LOCAL)}
    for p, n in per_src.items():
        print(f"  source {PORT_NAME[p]} : {n}/3 delivered")
    ok4 = all(n > 0 for n in per_src.values())
    print("T4", "PASS (no source starved)" if ok4 else "FAIL (a source got nothing)")

    print("\nper-PE cycles:", sim.get_cycles().per_pe)
