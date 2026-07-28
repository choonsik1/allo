import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import allo
from allo.ir.types import int32, int1, UInt, Channel, valid_ready
import allo.dataflow as df

# =====================================================================================
# RaveNoC-style router -- CHANNEL variant: every link is Channel[.., valid_ready].
#
# Deliberately a line-for-line copy of router_rvn_ports.py with ONE thing changed: the
# link type.  Same 10 port kernels, same routing, same latch-then-arbitrate, same output
# register.  Keeping the structure identical is the point -- it makes the pair a clean
# controlled experiment (Stream vs Channel) rather than two designs that differ in
# several ways at once.  The fused/split axis is the OTHER experiment, in
# router_rvn_fused.py; do not confuse the two comparisons.
#
# WHY CHANNEL IS THE FAITHFUL LINK:
# RaveNoC's flit interface is s_flit_req_t {fdata, vc_id, valid} + s_flit_resp_t {ready}.
# That IS valid/ready, so Channel[.., valid_ready] models the real protocol, whereas the
# Stream version modelled every link as a buffered FIFO.  In particular the 25 crossbar
# links here carry NO storage: RaveNoC's crossbar is the always_comb mapping blocks in
# router_ravenoc.sv -- wires and a handshake.  The Stream version's depth-2 crossbar was
# ~1.1 Kb of buffering the real router does not have, which matters if a DSE cost model
# is ever fitted to these designs.
#
# CANNOT RUN ON THE JIT SIMULATOR.  Channel is SystemC-only, so the T1-T4 numerical
# checks that validated router_rvn_ports.py do not exist here -- this file emits SystemC
# and is verified by csim / Catapult RTL cosim separately.  Treat it as UNVALIDATED
# until that runs: everything below is structurally identical to a design that passes,
# but "compiles" is not "works".
#
# WHAT TO WATCH FOR when it is tested:
#  * Depth-0 links remove the slack that hid timing sloppiness.  The output register
#    (emit LAST pass's winner, step (a)) is now load-bearing, not a nicety -- without it
#    a mesh closes a combinational loop through the handshake.
#  * A valid_ready handshake only completes when BOTH ends are live in the same cycle.
#    The Stream version could park a flit in a FIFO and let the consumer catch up later;
#    here a producer whose consumer is not currently in its try_get window simply fails
#    and retries.  Expect lower throughput than the Stream version, and watch for
#    livelock in the T3/T4 contention cases.
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

NUM_IT = 160
LANELEN = 16


@df.region()
def router_rvn_c(inj: int32[DIR, LANELEN], dlv: int32[DIR, LANELEN]):
    # Same three link sets as router_rvn_ports.py, but handshakes rather than FIFOs.
    # Note there is no depth argument: a Channel has no buffer at all.
    ext_in:  Channel[UInt(PS), valid_ready][DIR]
    xbar:    Channel[UInt(PS), valid_ready][DIR, DIR]
    ext_out: Channel[UInt(PS), valid_ready][DIR]

    # ── INPUT MODULE (RaveNoC input_module + input_router) ──────────────────────────
    @df.kernel(mapping=[DIR], args=[])
    def in_port():
        i = df.get_pid()
        held: UInt(PS) = 0
        hvld: int32 = 0
        hdst: int32 = 0
        stalls: int32 = 0

        for t in range(NUM_IT):
            if hvld == 0:
                v: UInt(PS) = 0
                ok: int1 = 0
                v, ok = ext_in[i].try_get()
                if ok == 1:
                    held = v
                    # route compute, RaveNoC input_router.sv XYAlg branch
                    xd: int32 = (v >> X_LO) & CMASK
                    yd: int32 = (v >> Y_LO) & CMASK
                    if xd == ROUTER_X and yd == ROUTER_Y:
                        hdst = LOCAL
                    elif xd == ROUTER_X:
                        if yd < ROUTER_Y:
                            hdst = WEST
                        else:
                            hdst = EAST
                    else:
                        if xd > ROUTER_X:
                            hdst = SOUTH
                        else:
                            hdst = NORTH
                    hvld = 1

            # Stream indices had to be compile-time constants; channel indices are no
            # different, so the crossbar is still one static call site per output gated
            # on the runtime route.
            if hvld == 1:
                with allo.meta_for(0, DIR) as o:
                    if hdst == o:
                        w: int1 = xbar[i, o].try_put(held)
                        # Reading the ok flag is mandatory -- an unread try_put is
                        # deleted outright by MemRefDCE, side effects included.
                        if w == 1:
                            hvld = 0
                        else:
                            stalls += 1

    # ── OUTPUT MODULE (RaveNoC output_module + rr_arbiter) ──────────────────────────
    @df.kernel(mapping=[DIR], args=[])
    def out_port():
        o = df.get_pid()
        hold: UInt(PS)[DIR] = 0
        hvld: int32[DIR] = 0
        rr: int32 = 0
        oreg: UInt(PS) = 0
        ovld: int32 = 0

        for t in range(NUM_IT):
            # (a) emit last pass's winner -- the output register, and with depth-0 links
            # the only thing breaking a combinational cycle in a mesh.
            if ovld == 1:
                e: int1 = ext_out[o].try_put(oreg)
                if e == 1:
                    ovld = 0

            # (b) latch before arbitrating: try_get consumes here exactly as it does on a
            # Stream, so each source still needs a private slot.
            with allo.meta_for(0, DIR) as s:
                if hvld[s] == 0:
                    gv: UInt(PS) = 0
                    gk: int1 = 0
                    gv, gk = xbar[s, o].try_get()
                    if gk == 1:
                        hold[s] = gv
                        hvld[s] = 1

            # (c) round-robin: scan from rr, first valid wins, pointer moves past it.
            if ovld == 0:
                won: int32 = 0
                for k in range(DIR):
                    sidx: int32 = rr + k
                    if sidx >= DIR:
                        sidx -= DIR
                    if won == 0 and hvld[sidx] == 1:
                        oreg = hold[sidx]
                        hvld[sidx] = 0
                        ovld = 1
                        won = 1
                        nxt: int32 = sidx + 1
                        if nxt >= DIR:
                            nxt -= DIR
                        rr = nxt

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


if __name__ == "__main__":
    # No numerical run: Channel does not lower to the JIT simulator. Emit SystemC and
    # eyeball that the channels appear as handshake ports rather than FIFOs.
    code = df.build(router_rvn_c, target="systemc").hls_code
    print(code[:1500])
    print("...")
    print(f"\n[systemc] emitted {len(code.splitlines())} lines")
