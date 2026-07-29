import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import allo
from allo.ir.types import int32, int1, UInt, Stream
import allo.dataflow as df
import numpy as np

# =====================================================================================
# RaveNoC-style router -- STAGE 2: WORMHOLE (multi-flit packets).
#
# Built on router_rvn_fused.py (one kernel per router, true request/grant crossbar,
# registered output).  ONE virtual channel on purpose: wormhole and VCs are separate
# concepts and this file isolates the new one.  Combining them is the next step.
#
# WHAT CHANGES vs single-flit.  A packet is now a SEQUENCE of flits -- HEAD, then any
# number of BODY, then TAIL -- and only the HEAD carries the destination.  That forces
# two locks, one at each end of the crossbar.  Both exist in the RTL:
#
#   1. INPUT ROUTE LOCK (vc_buffer.sv:73-76).  The HEAD's route is computed once and
#      HELD; BODY/TAIL carry payload where the coordinates used to be, so they must
#      inherit the head's decision rather than be re-routed.  RaveNoC sets a
#      packet-in-progress flag on HEAD and clears it on TAIL; hlock[] here.
#
#   2. OUTPUT RESERVATION (output_module.sv:96-98, `nflit_done`).  Once an output has
#      granted a HEAD it belongs to that input until the TAIL passes -- arbitration is
#      SUSPENDED for that port.  Without it two packets racing for one output would
#      interleave their flits and both would arrive corrupted.  obusy[]/oown[] here, and
#      the round-robin scan is skipped entirely while a port is reserved.
#
# That second lock is the whole point of wormhole and is what P3 below tests.  Note the
# cost it introduces: a reserved output cannot serve anyone else even if the owner has
# nothing ready this pass, so one slow packet blocks a port for its whole length. That
# is exactly the head-of-line problem VIRTUAL CHANNELS solve -- so wormhole is the
# reason RaveNoC needs VCs, and router_rvn_vc.py is the other half of this story.
#
# Flit layout gains a 2-bit type field:
#   data[0:16]  x_dest[16:19]  y_dest[19:22]  type[22:24]
# On BODY/TAIL the x/y bits are DON'T CARE -- P2 deliberately fills them with a wrong
# destination to prove the route lock is what steers them.
# =====================================================================================

NORTH, SOUTH, WEST, EAST, LOCAL = 0, 1, 2, 3, 4
DIR = 5
ROUTER_X, ROUTER_Y = 1, 1

DW, W = 16, 3
X_LO, Y_LO = DW, DW + W
T_LO = DW + 2 * W
PS = DW + 2 * W + 2          # 24
CMASK = (1 << W) - 1

T_HEAD, T_BODY, T_TAIL = 0, 1, 2

NUM_IT = 240
LANELEN = 24


@df.region()
def router_rvn_w(inj: int32[DIR, LANELEN], dlv: int32[DIR, LANELEN]):
    ext_in:  Stream[UInt(PS), 4][DIR]
    ext_out: Stream[UInt(PS), 4][DIR]

    @df.kernel(mapping=[1], args=[])
    def router():
        held: UInt(PS)[DIR] = 0
        hvld: int32[DIR] = 0
        hdst: int32[DIR] = 0
        hlock: int32[DIR] = 0      # input route lock: HEAD seen, TAIL not yet gone
        oreg: UInt(PS)[DIR] = 0
        ovld: int32[DIR] = 0
        rr: int32[DIR] = 0
        obusy: int32[DIR] = 0      # output reserved for a packet in flight
        oown: int32[DIR] = 0       # which input holds that reservation

        for t in range(NUM_IT):
            # (a) emit last pass's grant -- registered output, unchanged.
            with allo.meta_for(0, DIR) as o:
                if ovld[o] == 1:
                    e: int1 = ext_out[o].try_put(oreg[o])
                    if e == 1:
                        ovld[o] = 0

            # (b) accept one flit per port. ROUTE ONLY THE HEAD; BODY/TAIL inherit
            # hdst[] untouched, which is the input route lock.
            with allo.meta_for(0, DIR) as i:
                if hvld[i] == 0:
                    v: UInt(PS) = 0
                    ok: int1 = 0
                    v, ok = ext_in[i].try_get()
                    if ok == 1:
                        held[i] = v
                        ft: int32 = (v >> T_LO) & 3
                        if ft == T_HEAD:
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
                            hlock[i] = 1
                        hvld[i] = 1

            # (c) crossbar. Two paths: a RESERVED output serves only its owner, a FREE
            # output round-robins and a HEAD claims it.
            for op in range(DIR):
                if ovld[op] == 0:
                    won: int32 = 0

                    # (c1) reserved -- arbitration suspended, owner only.
                    if obusy[op] == 1:
                        s0: int32 = oown[op]
                        if hvld[s0] == 1 and hdst[s0] == op:
                            oreg[op] = held[s0]
                            f0: int32 = (held[s0] >> T_LO) & 3
                            hvld[s0] = 0
                            ovld[op] = 1
                            won = 1
                            if f0 == T_TAIL:      # packet complete: release both locks
                                obusy[op] = 0
                                hlock[s0] = 0

                    # (c2) free -- normal round robin. Note this is skipped while
                    # obusy==1 even if the owner had nothing ready, which is precisely
                    # the blocking wormhole is famous for.
                    if won == 0 and obusy[op] == 0:
                        for k in range(DIR):
                            sidx: int32 = rr[op] + k
                            if sidx >= DIR:
                                sidx -= DIR
                            if won == 0 and hvld[sidx] == 1 and hdst[sidx] == op:
                                oreg[op] = held[sidx]
                                f1: int32 = (held[sidx] >> T_LO) & 3
                                hvld[sidx] = 0
                                ovld[op] = 1
                                won = 1
                                nxt: int32 = sidx + 1
                                if nxt >= DIR:
                                    nxt -= DIR
                                rr[op] = nxt
                                if f1 == T_HEAD:   # claim the port for this packet
                                    obusy[op] = 1
                                    oown[op] = sidx
                                if f1 == T_TAIL:
                                    hlock[sidx] = 0

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


def flit(data, x, y, ftype):
    return int((data & 0xFFFF) | (x << X_LO) | (y << Y_LO) | (ftype << T_LO))


def packet(base, x, y, nbody):
    """HEAD + nbody BODY + TAIL, payloads base, base+1, ... (all non-zero)."""
    out = [flit(base, x, y, T_HEAD)]
    for b in range(nbody):
        # BODY/TAIL carry a DELIBERATELY WRONG destination -- if they are ever
        # re-routed instead of following the head's lock, they go somewhere else.
        out.append(flit(base + 1 + b, 0, 0, T_BODY))
    out.append(flit(base + 1 + nbody, 0, 0, T_TAIL))
    return out


def decode(dlv, port):
    """[(payload, type)] in arrival order."""
    r = []
    for k in range(LANELEN):
        v = int(dlv[port, k])
        if v:
            r.append((v & 0xFFFF, (v >> T_LO) & 3))
    return r


TN = {T_HEAD: "H", T_BODY: "B", T_TAIL: "T"}


def run(seeds):
    inj = np.zeros((DIR, LANELEN), dtype=np.int32)
    dlv = np.zeros((DIR, LANELEN), dtype=np.int32)
    for port, flits in seeds:
        for k, f in enumerate(flits):
            inj[port, k] = f
    sim(inj, dlv)
    return dlv


if __name__ == "__main__":
    sim = df.build(router_rvn_w, target="simulator")

    # P1 -- a 4-flit packet (H,B,B,T) from NORTH to this node ejects on LOCAL, in order.
    dlv = run([(NORTH, packet(0x100, ROUTER_X, ROUTER_Y, 2))])
    got = decode(dlv, LOCAL)
    want = [(0x100, T_HEAD), (0x101, T_BODY), (0x102, T_BODY), (0x103, T_TAIL)]
    print("\n--- P1: 4-flit packet NORTH -> LOCAL, in order ---")
    print("  got :", [(hex(p), TN[t]) for p, t in got])
    print("P1", "PASS" if got == want else "FAIL")

    # P2 -- ROUTE LOCK. Same packet, but its BODY/TAIL carry dest (0,0), which XY would
    # send NORTH. If the lock works they follow the head to LOCAL and nothing reaches N.
    north = decode(dlv, NORTH)
    print("\n--- P2: route lock (BODY/TAIL carry a WRONG dest) ---")
    print(f"  flits leaked to NORTH : {len(north)} (want 0)")
    print(f"  full packet on LOCAL  : {len(got)}/4")
    print("P2", "PASS" if (not north and len(got) == 4) else "FAIL")

    # P3 -- NO INTERLEAVING. Two 3-flit packets, NORTH and SOUTH, both to EAST. The
    # output reservation must let one finish before the other starts.
    dlv = run([(NORTH, packet(0x200, ROUTER_X, ROUTER_Y + 1, 1)),
               (SOUTH, packet(0x300, ROUTER_X, ROUTER_Y + 1, 1))])
    east = decode(dlv, EAST)
    print("\n--- P3: two packets contend for EAST (must not interleave) ---")
    print("  EAST order :", [(hex(p), TN[t]) for p, t in east])
    # every flit must belong to the same packet as the one before it, until a TAIL
    ok3, cur = len(east) == 6, -1
    for p, t in east:
        grp = p & 0xF00
        if t == T_HEAD:
            if cur != -1:
                ok3 = False       # a HEAD arrived while a packet was still open
            cur = grp
        else:
            if grp != cur:
                ok3 = False       # a flit from the OTHER packet cut in
            if t == T_TAIL:
                cur = -1
    print("P3", "PASS (packets stayed contiguous)" if ok3 else "FAIL (interleaved)")

    print("\nper-PE cycles:", sim.get_cycles().per_pe)
