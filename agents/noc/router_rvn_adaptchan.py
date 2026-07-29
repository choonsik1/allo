import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import allo
from allo.ir.types import int32, int1, UInt, Channel, valid_ready
import allo.dataflow as df
import numpy as np

# =====================================================================================
# CONGESTION-AWARE ROUTER over CHANNELS -- congestion arrives as a real SIDEBAND SIGNAL.
#
# This is router_rvn_adapt.py rebuilt on the new link concepts.  Two things change, and
# both fix a compromise the Stream version had to make:
#
#   1. ALL LINKS ARE Channel[.., valid_ready] -- RaveNoC's actual
#      s_flit_req_t/s_flit_resp_t handshake, no buffering anywhere.
#   2. CONGESTION ARRIVES OVER A CHANNEL, at RUNTIME, instead of being a build-time
#      constant.  The Stream version had to bake it in and rebuild per scenario; here a
#      `cmon` kernel publishes it and the router consumes it like any other signal.
#
# WHY A CHANNEL AND NOT A WIRE -- the distinction matters and is easy to get wrong.
# In a mesh, congestion flows BACKWARD along a link whose data flows forward, so A->B
# data plus B->A congestion is a CYCLE.
#   * A Wire is combinational, so a wire cycle is a COMBINATIONAL LOOP -- unschedulable.
#   * A Channel handshake is CYCLE-BASED, not zero-delay, so the same topology is a
#     legal dependency cycle. (Verified separately: bidirectional PE<->PE links build
#     and run.)
# So Channel is the right carrier for feedback; Wire stays right for FEED-FORWARD
# sidebands only (e.g. a request line from input module to output module).
#
# WHY A SEPARATE `cmon` KERNEL OWNS THE HOST ARRAY.  A kernel that forwards stream to
# stream CANNOT also own an array argument -- it silently moves no data (reproduced
# minimally in scratchpad/argtest.py: two identical routers, one args=[] which works and
# one owning an unused array arg which does not).  Giving the array to a separate
# publisher kernel and shipping the value over a link sidesteps that entirely, and is
# also what the hardware would do: the neighbour tells you its occupancy, you do not
# reach into its memory.
#
# The five congestion values are PACKED into one 15-bit word (3 bits each) so the
# sideband is a single channel rather than five -- fewer ports for Catapult to schedule,
# and it mirrors how a real status bus would be carried.
#
# STILL NOT DEADLOCK-FREE.  Adaptive routing gives up XY's guarantee: two packets making
# opposite turns can hold each other's channel forever.  Virtual channels or a turn model
# are the fix; this file has neither. Routing-policy demonstrator, not a mesh router.
#
# SYSTEMC ONLY -- Channel does not lower to the JIT simulator.
# =====================================================================================

NORTH, SOUTH, WEST, EAST, LOCAL = 0, 1, 2, 3, 4
DIR = 5

ROUTER_X = 2          # mid-grid, so BOTH dimensions can be unresolved in a test
ROUTER_Y = 2

DW = 16
W = 3
X_LO = DW
Y_LO = DW + W
PS = DW + 2 * W
CMASK = (1 << W) - 1

CW = 3                       # bits per congestion value (0..7)
CGMASK = (1 << CW) - 1
# Width of the packed congestion word: exactly DIR*CW = 15, NOT rounded up to 16.
# A STANDARD width (8/16/32/64) is emitted as a native C type (uint16_t) for locals but
# as ac_int<16,false> for the port -- and PopNB takes a non-const Message&, so the two
# will not bind and csim fails to compile. Non-standard widths map to ac_int on both
# sides. Every other router here uses 22/24 bits and never trips this.
CGW = DIR * CW               # 15

NUM_IT = 240                 # depth-0 links have no slack -- keep this generous
LANELEN = 16


@df.region()
def router_rvn_ac(inj: int32[DIR, LANELEN],
                  dlv: int32[DIR, LANELEN],
                  cong: int32[DIR]):
    ext_in:  Channel[UInt(PS), valid_ready][DIR]     # data in  (handshake, no buffer)
    ext_out: Channel[UInt(PS), valid_ready][DIR]     # data out
    cgch:    Channel[UInt(CGW), valid_ready]          # the SIDEBAND: packed congestion

    @df.kernel(mapping=[1], args=[])
    def router():
        held: UInt(PS)[DIR] = 0
        hvld: int32[DIR] = 0
        hdst: int32[DIR] = 0
        oreg: UInt(PS)[DIR] = 0
        ovld: int32[DIR] = 0
        rr: int32[DIR] = 0
        # Latched congestion. A LOCAL array, so cg[xdir] with a RUNTIME index is legal --
        # which is what the Stream version could not do (an indexable tuple global raises
        # "Unsupported global variable", so it had to bake in four scalar constants).
        cg: int32[DIR] = 0
        cvld: int32 = 0                          # have we heard from the neighbours yet?

        for t in range(NUM_IT):
            # (a) emit last pass's grants -- registered output.
            with allo.meta_for(0, DIR) as o:
                if ovld[o] == 1:
                    e: int1 = ext_out[o].try_put(oreg[o])
                    if e == 1:
                        ovld[o] = 0

            # (a2) sample the sideband. Non-blocking: if nothing arrived this cycle the
            # router keeps its previous view, exactly like a registered status input.
            cw: UInt(CGW) = 0
            ck: int1 = 0
            cw, ck = cgch.try_get()
            if ck == 1:
                with allo.meta_for(0, DIR) as d:
                    cg[d] = (cw >> (d * CW)) & CGMASK
                cvld = 1

            # (b) accept + ADAPTIVE route. Gated on cvld so routing never happens on a
            # stale all-zero view -- a real router would likewise not commit a route
            # before it has its neighbours' status.
            if cvld == 1:
                with allo.meta_for(0, DIR) as i:
                    if hvld[i] == 0:
                        v: UInt(PS) = 0
                        ok2: int1 = 0
                        v, ok2 = ext_in[i].try_get()
                        if ok2 == 1:
                            held[i] = v
                            xd: int32 = (v >> X_LO) & CMASK
                            yd: int32 = (v >> Y_LO) & CMASK
                            if xd == ROUTER_X and yd == ROUTER_Y:
                                hdst[i] = LOCAL               # arrived
                            elif xd == ROUTER_X:
                                if yd < ROUTER_Y:             # column only
                                    hdst[i] = WEST
                                else:
                                    hdst[i] = EAST
                            elif yd == ROUTER_Y:
                                if xd > ROUTER_X:             # row only
                                    hdst[i] = SOUTH
                                else:
                                    hdst[i] = NORTH
                            else:
                                # BOTH unresolved -> the adaptive choice. Both candidate
                                # directions and the congestion lookup are RUNTIME values
                                # here, which is the improvement over the Stream version.
                                xdir: int32 = NORTH
                                if xd > ROUTER_X:
                                    xdir = SOUTH
                                ydir: int32 = WEST
                                if yd > ROUTER_Y:
                                    ydir = EAST
                                # Ties favour x, so a congestion-free network behaves
                                # exactly like XY -- making A1 below a true baseline.
                                if cg[xdir] <= cg[ydir]:
                                    hdst[i] = xdir
                                else:
                                    hdst[i] = ydir
                            hvld[i] = 1

            # (c) crossbar: request/grant over local arrays.
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


    # NOTE: `cmon` is defined LAST on purpose. Region args are matched in KERNEL
    # APPEARANCE order on the csim path, so with cmon first the region's third arg
    # (cong) bound to the first kernel and the outputs came back misaligned
    # ("could not broadcast (5,16) into (5,)"). Keeping kernel order drv/col/cmon
    # aligned with the declared order inj/dlv/cong avoids it.
    # ── CONGESTION MONITOR: stands in for the neighbours. Owns the host array and
    # publishes it on the sideband channel. In a mesh this kernel disappears and the
    # value comes from the neighbouring router instead.
    @df.kernel(mapping=[1], args=[cong])
    def cmon(cg_in: int32[DIR]):
        word: UInt(CGW) = 0
        built: int32 = 0
        for t in range(NUM_IT):
            if built == 0:                      # pack once: 3 bits per direction
                with allo.meta_for(0, DIR) as d:
                    word |= (cg_in[d] & CGMASK) << (d * CW)
                built = 1
            # Republish every pass. A valid_ready put only completes when the router is
            # actually reading, so this keeps the router's view fresh without assuming
            # any particular rendezvous cycle.
            ok: int1 = cgch.try_put(word)
            if ok == 1:
                built = 1                       # consume the flag (unread -> DCE)


def pack(data, x, y):
    return int(data | (x << X_LO) | (y << Y_LO))


NAME = {NORTH: "N", SOUTH: "S", WEST: "W", EAST: "E", LOCAL: "L"}


if __name__ == "__main__":
    # SYSTEMC ONLY. Needs, beyond conda/LLVM_BUILD_DIR/PYTHONPATH:
    #   export MGC_HOME=/opt/siemens/catapult/2024.2/Mgc_home
    #   export PATH=$MGC_HOME/bin:$PATH
    #   export SYSTEMC_HOME=$MGC_HOME/shared
    #   export ALLO_CXX_EXTRA="-L$CONDA_PREFIX/lib -Wl,-rpath,$CONDA_PREFIX/lib"
    PROJECT = os.environ.get(
        "ALLO_CSIM_OUT", os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                      "csim_out", "adaptchan"))
    os.makedirs(PROJECT, exist_ok=True)
    print(f"[csim] generating + building into {PROJECT}", flush=True)
    mod = df.build(router_rvn_ac, target="systemc", mode="csim", project=PROJECT)

    def run(seeds, congestion):
        inj = np.zeros((DIR, LANELEN), dtype=np.int32)
        dlv = np.zeros((DIR, LANELEN), dtype=np.int32)
        cg = np.array(congestion, dtype=np.int32)
        for p, lane, w in seeds:
            inj[p, lane] = w
        mod(inj, dlv, cg)                 # congestion is a RUNTIME input now
        return dlv

    def where(dlv, payload):
        for p in (NORTH, SOUTH, WEST, EAST, LOCAL):
            if payload in [int(dlv[p, k]) & 0xFFFF for k in range(LANELEN) if dlv[p, k]]:
                return p
        return -1

    dst_x, dst_y = ROUTER_X + 1, ROUTER_Y + 1     # both dimensions unresolved
    ok = True

    # A1 -- no congestion: ties go to x, so this must match plain XY.
    got = where(run([(LOCAL, 0, pack(0xA01, dst_x, dst_y))], [0, 0, 0, 0, 0]), 0xA01)
    print(f"\nA1 no congestion        : left by {NAME.get(got, 'NOWHERE')}  (XY baseline = S)")
    print("A1", "PASS" if got == SOUTH else "FAIL"); ok &= got == SOUTH

    # A2 -- congest the x neighbour: must divert to EAST.
    cg = [0, 0, 0, 0, 0]; cg[SOUTH] = 7
    got = where(run([(LOCAL, 0, pack(0xA02, dst_x, dst_y))], cg), 0xA02)
    print(f"\nA2 SOUTH congested      : left by {NAME.get(got, 'NOWHERE')}  (want E -- diverted)")
    print("A2", "PASS (adapted)" if got == EAST else "FAIL (did not adapt)"); ok &= got == EAST

    # A3 -- congest the other one: must swing back. Proves it tracks the signal.
    cg = [0, 0, 0, 0, 0]; cg[EAST] = 7
    got = where(run([(LOCAL, 0, pack(0xA03, dst_x, dst_y))], cg), 0xA03)
    print(f"\nA3 EAST congested       : left by {NAME.get(got, 'NOWHERE')}  (want S -- swung back)")
    print("A3", "PASS (adapted)" if got == SOUTH else "FAIL"); ok &= got == SOUTH

    # A4 -- CONTROL: only one productive port, and it is congested. Must still take it,
    # or the router is misrouting rather than being minimal-adaptive.
    cg = [0, 0, 0, 0, 0]; cg[EAST] = 7
    got = where(run([(LOCAL, 0, pack(0xA04, ROUTER_X, ROUTER_Y + 1))], cg), 0xA04)
    print(f"\nA4 control, 1 productive: left by {NAME.get(got, 'NOWHERE')}  (want E though congested)")
    print("A4", "PASS (stayed minimal)" if got == EAST else "FAIL (misrouted)"); ok &= got == EAST

    print("\n=== csim summary:", "ALL PASS" if ok else "FAILURES", "===")
    raise SystemExit(0 if ok else 1)
