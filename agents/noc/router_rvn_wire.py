import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import allo
from allo.ir.types import int32, int1, UInt, Stream, Wire
import allo.dataflow as df
import numpy as np

# =====================================================================================
# ROUTER + ATTACHED PE, joined by a WIRE.  The simplest useful thing a Wire can do here.
#
# Everything else in agents/noc/ links kernels with Stream (buffered FIFO) or Channel
# (valid/ready handshake).  A Wire is neither: it is combinational, has NO buffer and NO
# handshake, and -- unlike Stream/Channel -- exposes no try_put/try_get at all, only
# put()/get().  That single fact dictates the whole design:
#
#   * NO BACKPRESSURE.  A Wire cannot refuse.  So the consumer MUST read every pass, and
#     the producer MUST write every pass, or the two sides disagree about what cycle
#     they are in.  Here the router writes the LOCAL ejection every pass and the PE reads
#     it every pass, unconditionally.
#   * VALIDITY IS IN-BAND.  With no ok flag, "no flit this cycle" has to be a value.
#     0 is that value (same convention the host lanes already use).  This is exactly the
#     `valid_only` protocol -- valid travels with the data, ready does not exist.
#   * LOSSY BY CONSTRUCTION.  If the PE is not ready, the flit is simply gone; there is
#     no mechanism to hold it.  That is the price of deleting the handshake, and it is
#     why the OTHER four router ports keep their Streams -- an inter-router link must not
#     drop flits, but a core that is architecturally guaranteed to accept one per cycle
#     can take a Wire.
#   * MUST BE ACYCLIC.  Wires are resolved by topological scheduling, so a Wire loop is a
#     combinational loop and cannot be scheduled.  The dataflow here is strictly
#     drv -> router -> [wire] -> pe -> col, one direction only.  This is why the PE's
#     RESULT path back out is a Stream, not a second Wire: router->pe->router would close
#     exactly the cycle that is illegal.
#
# So: Wire for the ejection port (router -> core), Stream everywhere a flit must not be
# dropped.  That split is the useful design, not "use Wire everywhere".
# =====================================================================================

NORTH, SOUTH, WEST, EAST, LOCAL = 0, 1, 2, 3, 4
DIR = 5
ROUTER_X, ROUTER_Y = 1, 1

DW, W = 16, 3
X_LO, Y_LO = DW, DW + W
PS = DW + 2 * W
CMASK = (1 << W) - 1

NUM_IT = 160
LANELEN = 16


@df.region()
def rvn_wire(inj: int32[DIR, LANELEN], dlv: int32[DIR, LANELEN], out: int32[LANELEN]):
    ext_in:  Stream[UInt(PS), 4][DIR]     # host -> router
    ext_out: Stream[UInt(PS), 4][DIR]     # router -> host (N/S/W/E only; LOCAL is the wire)
    ejec:    Wire[UInt(PS)]               # router LOCAL --wire--> pe   (no buffer, no handshake)
    res:     Stream[UInt(PS), 8]          # pe -> host (Stream: results must not be dropped)

    # ── ROUTER: the fused Stage-0 router, with LOCAL ejection moved onto the wire ──
    @df.kernel(mapping=[1], args=[])
    def router():
        held: UInt(PS)[DIR] = 0
        hvld: int32[DIR] = 0
        hdst: int32[DIR] = 0
        oreg: UInt(PS)[DIR] = 0
        ovld: int32[DIR] = 0
        rr: int32[DIR] = 0

        for t in range(NUM_IT):
            # (a) emit the four STREAM ports -- these can refuse, so they retry.
            with allo.meta_for(0, DIR) as o:
                with allo.meta_if(o != LOCAL):
                    if ovld[o] == 1:
                        e: int1 = ext_out[o].try_put(oreg[o])
                        if e == 1:
                            ovld[o] = 0

            # (a2) emit the WIRE port. Note what is missing: no try_, no ok flag, no
            # retry, no `if`. The wire is written EVERY pass -- the flit if there is one,
            # 0 if not -- because the PE reads every pass and a silent pass would desync
            # them. And the register is cleared unconditionally: the wire cannot refuse,
            # so there is nothing to hold on to.
            lv: UInt(PS) = 0
            if ovld[LOCAL] == 1:
                lv = oreg[LOCAL]
                ovld[LOCAL] = 0
            ejec.put(lv)

            # (b) accept + route (identical to router_rvn_fused.py)
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

            # (c) crossbar: request/grant over local arrays
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

    # ── PE: the attached core. Reads the wire EVERY pass, unconditionally. ──
    @df.kernel(mapping=[1], args=[])
    def pe():
        seen: int32 = 0
        for t in range(NUM_IT):
            # No try_get, no ok flag -- get() on a wire always returns *something*.
            # Validity is the value itself: 0 means "no flit this cycle".
            v: UInt(PS) = ejec.get()
            if v != 0:
                seen += 1
                # trivial "compute": payload + 1, so the host can tell the PE ran
                # rather than the flit having been passed through untouched.
                p: UInt(PS) = (v & 0xFFFF) + 1
                ok: int1 = res.try_put(p)
                # If res were full the result WOULD be lost -- the wire's losslessness
                # gap propagating downstream. Depth 8 keeps that from biting here.
                if ok == 1:
                    seen += 0

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
                with allo.meta_if(o != LOCAL):
                    wv: UInt(PS) = 0
                    wk: int1 = 0
                    wv, wk = ext_out[o].try_get()
                    if wk == 1 and kp[o] < LANELEN:
                        dout[o, kp[o]] = wv
                        kp[o] += 1

    @df.kernel(mapping=[1], args=[out])
    def sink(o2: int32[LANELEN]):
        n: int32 = 0
        for t in range(NUM_IT):
            rv: UInt(PS) = 0
            rk: int1 = 0
            rv, rk = res.try_get()
            if rk == 1 and n < LANELEN:
                o2[n] = rv
                n += 1


def pack(data, x, y):
    return int(data | (x << X_LO) | (y << Y_LO))


if __name__ == "__main__":
    sim = df.build(rvn_wire, target="simulator")

    # W1: flits addressed to THIS node eject over the wire, reach the PE, and come back
    # as payload+1. Proves the wire carries data and the PE consumed it.
    inj = np.zeros((DIR, LANELEN), dtype=np.int32)
    dlv = np.zeros((DIR, LANELEN), dtype=np.int32)
    out = np.zeros(LANELEN, dtype=np.int32)
    for k, p in enumerate((NORTH, SOUTH, WEST, EAST)):
        inj[p, 0] = pack(0x100 + p, ROUTER_X, ROUTER_Y)
    sim(inj, dlv, out)
    got = sorted(int(x) for x in out if x)
    want = sorted(0x100 + p + 1 for p in (NORTH, SOUTH, WEST, EAST))
    print("\n--- W1: 4 flits -> LOCAL over the WIRE -> PE (+1) ---")
    print(f"  expected {[hex(x) for x in want]}")
    print(f"  got      {[hex(x) for x in got]}")
    print("W1", "PASS" if got == want else "FAIL")

    # W2: a flit NOT addressed here must leave by a Stream port and never touch the wire.
    inj2 = np.zeros((DIR, LANELEN), dtype=np.int32)
    dlv2 = np.zeros((DIR, LANELEN), dtype=np.int32)
    out2 = np.zeros(LANELEN, dtype=np.int32)
    inj2[LOCAL, 0] = pack(0x777, ROUTER_X, ROUTER_Y + 1)      # -> EAST
    sim(inj2, dlv2, out2)
    east = [int(dlv2[EAST, k]) & 0xFFFF for k in range(LANELEN)]
    print("\n--- W2: non-local flit leaves by Stream, not the wire ---")
    print(f"  0x777 on EAST : {'yes' if 0x777 in east else 'NO'}")
    print(f"  PE saw nothing: {'yes' if not any(out2) else 'NO -- wire got a flit it should not have'}")
    print("W2", "PASS" if (0x777 in east and not any(out2)) else "FAIL")

    print("\nper-PE cycles:", sim.get_cycles().per_pe)
