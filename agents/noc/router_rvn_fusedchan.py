import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import allo
from allo.ir.types import int32, int1, UInt, Channel, valid_ready
import allo.dataflow as df
import numpy as np

# =====================================================================================
# FUSED router + CHANNEL links -- the most hardware-faithful variant of the set.
#
# This is router_rvn_fused.py with `Stream` swapped for `Channel[.., valid_ready]` on the
# port links.  It completes the 2x2 of (kernel granularity) x (link type):
#
#                      Stream links            Channel links
#   split per port     router_rvn_ports.py     router_rvn_chan.py
#   fused one kernel   router_rvn_fused.py     >>> THIS FILE <<<
#
# WHY THIS COMBINATION IS THE FAITHFUL ONE.  The two infidelities in the other variants
# are independent, and this file removes both at once:
#
#   1. FUSION removes phantom crossbar storage.  Split into per-port kernels, every
#      (input, output) pair must become a link -- 25 of them -- because a kernel boundary
#      IS a link.  RaveNoC's crossbar is not storage at all: it is the two always_comb
#      mapping blocks in router_ravenoc.sv, wires and a mux.  Fusing puts the crossbar
#      back into local arrays where it belongs, and as a bonus the arbiter can then READ
#      requests without consuming them -- true request/grant (s_router_ports_t), instead
#      of the split version's latch-then-arbitrate workaround forced by try_get consuming.
#   2. CHANNEL removes phantom link storage.  A Stream is a buffered FIFO; RaveNoC's
#      links are `s_flit_req_t{fdata, valid}` + `s_flit_resp_t{ready}` -- a pure
#      handshake with NO buffer.  Channel[.., valid_ready] IS that protocol.
#
# Result: 10 links, all handshakes, zero buffering anywhere except the router's own
# registers (held/oreg) -- which is exactly what the RTL has.  Compare:
#   router_rvn_ports.py  35 links, 25 of them depth-2 FIFOs (~1.1 Kb of phantom storage)
#   router_rvn_fused.py  10 links, still buffered FIFOs
#   this file            10 links, no storage at all
#
# CANNOT RUN ON THE JIT SIMULATOR.  Channel does not lower to it, so csim is the only
# backend -- see the __main__ block.  The Stream fused variant remains the one to use
# when you want get_cycles() or fast iteration.
#
# WHAT TO WATCH.  With depth-0 links there is no slack: a transfer completes only if both
# ends are live in the same cycle, where a Stream could park a flit in a FIFO and let the
# consumer catch up.  Expect lower throughput than the Stream variant and keep NUM_IT
# generous -- an under-sized budget here looks exactly like packet loss.
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

# Harness budgets, not hardware. Larger than the Stream variant's 160 on purpose: the
# depth-0 handshake removes the FIFO slack that let a producer run ahead.
NUM_IT = 240
LANELEN = 16


@df.region()
def router_rvn_fc(inj: int32[DIR, LANELEN], dlv: int32[DIR, LANELEN]):
    # The ONLY links in the design. No depth argument -- a Channel has no buffer.
    # There is no crossbar link set at all: the crossbar is local state in the kernel.
    ext_in:  Channel[UInt(PS), valid_ready][DIR]
    ext_out: Channel[UInt(PS), valid_ready][DIR]

    @df.kernel(mapping=[1], args=[])
    def router():
        # input modules (RaveNoC input_module x5): one register set per input port
        held: UInt(PS)[DIR] = 0
        hvld: int32[DIR] = 0        # occupied? -- doubles as the request wire
        hdst: int32[DIR] = 0        # routed output, computed once at latch time
        # output modules (output_module x5): output register + per-output arbiter
        oreg: UInt(PS)[DIR] = 0
        ovld: int32[DIR] = 0
        rr: int32[DIR] = 0          # round-robin pointer (rr_arbiter's mask_ff)

        for t in range(NUM_IT):
            # (a) EMIT first: what leaves now was granted LAST cycle. The output register
            # is the loop breaker -- and with depth-0 handshake links it is load-bearing,
            # not a nicety: without it a mesh would close a combinational cycle.
            with allo.meta_for(0, DIR) as o:
                if ovld[o] == 1:
                    e: int1 = ext_out[o].try_put(oreg[o])
                    # The ok flag MUST be read or MemRefDCE deletes the whole try_put.
                    # On failure ovld stays 1 -> this output stops granting in (c),
                    # which is how backpressure propagates with no credit logic.
                    if e == 1:
                        ovld[o] = 0

            # (b) ACCEPT + ROUTE. One flit per input port, routed once, then held until
            # an output grants it -- holding is what makes the router lossless.
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

            # (c) CROSSBAR = REQUEST/GRANT. Plain runtime loops: these touch only local
            # arrays, so the compile-time-constant rule that forces meta_for on LINK
            # indices does not apply here. `hvld[s]==1 and hdst[s]==op` is the request
            # wire, read WITHOUT consuming; the flit moves ONLY on a grant.
            for op in range(DIR):
                if ovld[op] == 0:
                    won: int32 = 0
                    for k in range(DIR):
                        sidx: int32 = rr[op] + k
                        if sidx >= DIR:
                            sidx -= DIR
                        if won == 0 and hvld[sidx] == 1 and hdst[sidx] == op:
                            oreg[op] = held[sidx]
                            hvld[sidx] = 0      # grant, not peek
                            ovld[op] = 1
                            won = 1
                            nxt: int32 = sidx + 1
                            if nxt >= DIR:
                                nxt -= DIR
                            rr[op] = nxt        # winner -> lowest priority

    @df.kernel(mapping=[1], args=[inj])
    def drv(din: int32[DIR, LANELEN]):
        sp: int32[DIR] = 0
        for t in range(NUM_IT):
            with allo.meta_for(0, DIR) as i:
                if sp[i] < LANELEN:
                    w: UInt(PS) = din[i, sp[i]]
                    if w != 0:                       # 0 == empty lane
                        ok: int1 = ext_in[i].try_put(w)
                        if ok == 1:
                            sp[i] += 1               # advance ONLY on success
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


NAME = {NORTH: "N", SOUTH: "S", WEST: "W", EAST: "E", LOCAL: "L"}


if __name__ == "__main__":
    # SYSTEMC ONLY -- Channel does not lower to the JIT simulator.
    #   export MGC_HOME=/opt/siemens/catapult/2024.2/Mgc_home
    #   export PATH=$MGC_HOME/bin:$PATH
    #   export SYSTEMC_HOME=$MGC_HOME/shared
    #   export ALLO_CXX_EXTRA="-L$CONDA_PREFIX/lib -Wl,-rpath,$CONDA_PREFIX/lib"
    # The last is NOT optional on this host: libsystemc needs GLIBCXX_3.4.26.
    PROJECT = os.environ.get(
        "ALLO_CSIM_OUT", os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                      "csim_out", "fusedchan"))
    os.makedirs(PROJECT, exist_ok=True)
    print(f"[csim] generating + building into {PROJECT}", flush=True)
    mod = df.build(router_rvn_fc, target="systemc", mode="csim", project=PROJECT)

    def run(seeds):
        inj = np.zeros((DIR, LANELEN), dtype=np.int32)
        dlv = np.zeros((DIR, LANELEN), dtype=np.int32)
        for p, lane, w in seeds:
            inj[p, lane] = w
        mod(inj, dlv)
        return dlv

    def arrived(dlv, port):
        return [int(dlv[port, k]) & 0xFFFF for k in range(LANELEN) if dlv[port, k]]

    ok = True

    # T1 -- every non-local input, all addressed here, must eject on LOCAL.
    dlv = run([(p, 0, pack(0x100 + p, ROUTER_X, ROUTER_Y))
               for p in (NORTH, SOUTH, WEST, EAST)])
    got = sorted(arrived(dlv, LOCAL))
    want = sorted(0x100 + p for p in (NORTH, SOUTH, WEST, EAST))
    print(f"\nT1 ejection            : {[hex(x) for x in got]}")
    print("T1", "PASS" if got == want else f"FAIL (wanted {[hex(x) for x in want]})")
    ok &= got == want

    # T2 -- injected locally, each destination leaves by the XY-chosen port.
    cases = [(0x201, ROUTER_X - 1, ROUTER_Y, NORTH),
             (0x202, ROUTER_X + 1, ROUTER_Y, SOUTH),
             (0x203, ROUTER_X, ROUTER_Y - 1, WEST),
             (0x204, ROUTER_X, ROUTER_Y + 1, EAST)]
    dlv = run([(LOCAL, k, pack(d, x, y)) for k, (d, x, y, _) in enumerate(cases)])
    print("\nT2 XY directions       :")
    hits = []
    for d, x, y, wnt in cases:
        hit = d in arrived(dlv, wnt)
        hits.append(hit)
        print(f"   dest({x},{y}) -> {NAME[wnt]} : {'ok' if hit else 'MISSING'}")
    print("T2", "PASS" if all(hits) else "FAIL")
    ok &= all(hits)

    # T3 -- two inputs contend for EAST; the loser is HELD and retried, never dropped.
    # This is the property most at risk on a depth-0 handshake, where a transfer needs
    # both ends live in the same cycle instead of parking in a FIFO.
    dlv = run([(NORTH, 0, pack(0x301, ROUTER_X, ROUTER_Y + 1)),
               (SOUTH, 0, pack(0x302, ROUTER_X, ROUTER_Y + 1))])
    east = arrived(dlv, EAST)
    lossless = (0x301 in east) and (0x302 in east)
    print(f"\nT3 lossless contention : {[hex(x) for x in east]}")
    print("T3", "PASS (lossless)" if lossless else "FAIL (a flit was dropped)")
    ok &= lossless

    # T4 -- four saturating sources on one output. Totals are printed so a shortfall is
    # diagnosable: <12 total means loss, 12 but lopsided means starvation.
    seeds = [(p, lane, pack(0x400 + 0x10 * p + lane, ROUTER_X, ROUTER_Y + 1))
             for p in (NORTH, SOUTH, WEST, LOCAL) for lane in range(3)]
    dlv = run(seeds)
    east = arrived(dlv, EAST)
    per = {p: sum(1 for lane in range(3) if (0x400 + 0x10 * p + lane) in east)
           for p in (NORTH, SOUTH, WEST, LOCAL)}
    fair = all(v > 0 for v in per.values())
    print("\nT4 fairness            : "
          + "  ".join(f"{NAME[p]}={v}/3" for p, v in per.items())
          + f"   ({len(east)}/12 delivered)")
    print("T4", "PASS (no source starved)" if fair else "FAIL (a source got nothing)")
    ok &= fair

    print("\n=== csim summary:", "ALL PASS" if ok else "FAILURES", "===")
    raise SystemExit(0 if ok else 1)
