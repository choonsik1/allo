import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import allo
from allo.ir.types import int32, int1, UInt, Stream
import allo.dataflow as df
import numpy as np

# =====================================================================================
# RaveNoC-style router -- STAGE 1: VIRTUAL CHANNELS.
#
# This is router_rvn_fused.py (whole router in ONE @df.kernel, true request/grant
# crossbar, registered output) plus NumVirtChn virtual channels per input port.
#
# WHAT THE RTL DOES (src/router/{input_datapath,vc_buffer,output_module}.sv):
#   * input_datapath.sv instantiates NumVirtChn vc_buffers behind a demux keyed on the
#     incoming flit's vc_id.  Each vc_buffer is an INDEPENDENT fifo with its own route
#     state, so a flit parked in VC0 waiting on a busy output does not stop a VC1 flit.
#     The demux's ready_o is the ADDRESSED VC's ready -- if that one VC is full the
#     physical link stalls, even though other VCs have room.  That asymmetry is the
#     whole point of VCs and it is reproduced faithfully below.
#   * output_module.sv instantiates one rr_arbiter PER VC (genvar vc_id loop), each
#     arbitrating among the input ports *within* that VC; a mux then picks among the
#     per-VC winners for the single physical output.
#
# WHAT THIS FILE MAPS THEM TO:
#   held/hvld/hdst become 2-D: [DIR, NVC].  One flit slot per (input port, VC) --
#   FlitBuff=1, which is enough to expose head-of-line blocking and keeps the state
#   small.  rr becomes rr[DIR, NVC] (one rotating pointer per output PER VC, exactly the
#   genvar loop) and a second pointer vrr[DIR] rotates among the per-VC winners.
#
# TWO DELIBERATE DEVIATIONS, both documented rather than hidden:
#
#   (1) STAGING REGISTER.  A Stream cannot be peeked, so we cannot know a flit's vc_id
#       before consuming it, and we must not consume a flit whose VC slot is full.  Each
#       input port therefore gets a one-entry staging register: try_get lands there, the
#       route+vc are computed, and on a later pass the flit is placed into its VC slot
#       when that slot frees.  This is the model's stand-in for vc_buffer's combinational
#       ready_o -- identical flow control (the link stalls iff the ADDRESSED VC is full),
#       one extra pass of latency.  It is also why this file costs more cycles than the
#       base fused router.
#
#   (2) VC SELECT IS ROUND-ROBIN, NOT FIXED PRIORITY.  RaveNoC's output mux takes the
#       lowest (or highest) VC index that has a grant, so a saturated VC0 can starve VC1
#       at the output.  vrr[] rotates instead.  Cheap, and it keeps T4-style fairness
#       claims true across VCs as well as across ports.
#
# NVC is a build-time parameter (see build_router below) so the same source can be built
# with 1 VC and with 2 VCs and the two run against identical traffic -- that A/B is the
# head-of-line-blocking test at the bottom of this file.
# =====================================================================================

NORTH, SOUTH, WEST, EAST, LOCAL = 0, 1, 2, 3, 4
DIR = 5

ROUTER_X = 1
ROUTER_Y = 1

# flit layout (LSB-first): data[0:16] x_dest[16:19] y_dest[19:22] vc[22:24]
# The vc FIELD is a fixed 2 bits (room for 4 VCs) so the packing is identical for every
# NVC and an NVC=1 build can be fed the exact same host arrays as an NVC=2 build.
# The HARDWARE mask is VCMASK = NVC-1: with NVC=1 that is 0, i.e. a 1-VC router simply
# ignores the vc bits and dumps everything on VC0 -- which is what a 1-VC router is.
DW = 16
W = 3
VCW = 2
X_LO = DW
Y_LO = DW + W
VC_LO = DW + 2 * W
PS = DW + 2 * W + VCW          # 24
CMASK = (1 << W) - 1

# Harness budgets, NOT hardware.  Under-sizing either makes flits vanish in a way that
# looks exactly like a routing bug -- raise BOTH before suspecting the router.
# NUM_IT is up from the base file's 160 because the staging register adds a pass per
# flit and the per-VC arbiter loop adds work per pass.
NUM_IT = 320
LANELEN = 16

# Build-time knob.  build_router() rebinds this module global before the @df.region()
# below is (re)defined, so the kernel bodies close over the right value.
NVC = 2
VCMASK = NVC - 1


def build_router(nvc):
    """Build a simulator for an nvc-virtual-channel router.

    NVC/VCMASK are module globals because allo resolves the constants in a kernel body
    from the region function's __globals__ at build time; rebinding them here and then
    defining + building the region in one go is what makes NVC a build parameter.
    """
    global NVC, VCMASK
    NVC = nvc
    VCMASK = nvc - 1

    @df.region()
    def router_rvn_v(inj: int32[DIR, LANELEN],
                     dlv: int32[DIR, LANELEN],
                     drain: int32[DIR]):
        # Only the physical port links exist as streams.  The crossbar, the VC buffers
        # and the arbiters are all local state inside the one router kernel.
        ext_in:  Stream[UInt(PS), 4][DIR]
        ext_out: Stream[UInt(PS), 4][DIR]

        @df.kernel(mapping=[1], args=[])
        def router():
            # ---- input datapath: one staging register + NVC vc_buffers per port ----
            stg:  UInt(PS)[DIR] = 0     # flit pulled off the link, not yet placed
            svld: int32[DIR] = 0
            sdst: int32[DIR] = 0        # its route (computed once, at pull time)
            svc:  int32[DIR] = 0        # its VC (the demux select of input_datapath.sv)

            held: UInt(PS)[DIR, NVC] = 0   # the NVC vc_buffers, FlitBuff = 1
            hvld: int32[DIR, NVC] = 0
            hdst: int32[DIR, NVC] = 0

            # ---- output modules: output register + one rr_arbiter PER VC ----
            oreg: UInt(PS)[DIR] = 0
            ovld: int32[DIR] = 0
            rr:   int32[DIR, NVC] = 0   # gen_rr_arbiters: pointer per (output, VC)
            vrr:  int32[DIR] = 0        # rotation among the per-VC winners

            for t in range(NUM_IT):
                # (a) EMIT first: what leaves now was granted LAST pass.  Registered
                # output, same loop breaker as the base file.
                with allo.meta_for(0, DIR) as o:
                    if ovld[o] == 1:
                        e: int1 = ext_out[o].try_put(oreg[o])
                        if e == 1:
                            ovld[o] = 0

                # (b) INPUT DATAPATH.
                with allo.meta_for(0, DIR) as i:
                    # (b1) demux: place the staged flit into ITS VC's buffer, and only
                    # into that one.  If that VC is occupied the flit waits here and the
                    # link behind it stalls -- this is vc_buffer's ready_o, and it is
                    # exactly the head-of-line behaviour VCs are meant to bound.
                    if svld[i] == 1:
                        sv: int32 = svc[i]
                        if hvld[i, sv] == 0:
                            held[i, sv] = stg[i]
                            hdst[i, sv] = sdst[i]
                            hvld[i, sv] = 1
                            svld[i] = 0
                    # (b2) pull the next flit off the link (same pass, so freeing the
                    # staging register above does not cost a bubble) and route it.
                    if svld[i] == 0:
                        v: UInt(PS) = 0
                        ok: int1 = 0
                        v, ok = ext_in[i].try_get()
                        if ok == 1:
                            stg[i] = v
                            xd: int32 = (v >> X_LO) & CMASK
                            yd: int32 = (v >> Y_LO) & CMASK
                            if xd == ROUTER_X and yd == ROUTER_Y:
                                sdst[i] = LOCAL
                            elif xd == ROUTER_X:
                                if yd < ROUTER_Y:
                                    sdst[i] = WEST
                                else:
                                    sdst[i] = EAST
                            else:
                                if xd > ROUTER_X:
                                    sdst[i] = SOUTH
                                else:
                                    sdst[i] = NORTH
                            svc[i] = (v >> VC_LO) & VCMASK
                            svld[i] = 1

                # (c) CROSSBAR = REQUEST/GRANT, now per VC.  Plain runtime loops: these
                # touch only local arrays.  `hvld[s,vc]==1 and hdst[s,vc]==op` is the
                # request wire req[vc][in_mod] of output_module.sv; the flit moves ONLY
                # on a grant, so nothing is latched speculatively.
                # Outer loop = the VC mux (vrr), inner loop = that VC's rr_arbiter (rr).
                for op in range(DIR):
                    if ovld[op] == 0:
                        won: int32 = 0
                        for kv in range(NVC):
                            vidx: int32 = vrr[op] + kv
                            if vidx >= NVC:
                                vidx -= NVC
                            for k in range(DIR):
                                sidx: int32 = rr[op, vidx] + k
                                if sidx >= DIR:
                                    sidx -= DIR
                                if won == 0 and hvld[sidx, vidx] == 1 and hdst[sidx, vidx] == op:
                                    oreg[op] = held[sidx, vidx]
                                    hvld[sidx, vidx] = 0    # grant, not peek
                                    ovld[op] = 1
                                    won = 1
                                    nxt: int32 = sidx + 1
                                    if nxt >= DIR:
                                        nxt -= DIR
                                    rr[op, vidx] = nxt      # winner -> lowest priority
                                    vnx: int32 = vidx + 1
                                    if vnx >= NVC:
                                        vnx -= NVC
                                    vrr[op] = vnx           # ... and so does its VC

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

        # The collector takes a per-output DRAIN MASK.  drain[o]==0 means "this output's
        # downstream neighbour is jammed": the collector never reads it, ext_out[o] fills
        # up, the output register can never retire, and output o is genuinely congested
        # all the way back into the input buffers.  That is the only way to build the
        # head-of-line-blocking scenario without inventing a fake stall knob inside the
        # router.  Every functional test passes drain = all ones.
        @df.kernel(mapping=[1], args=[dlv, drain])
        def col(dout: int32[DIR, LANELEN], dmask: int32[DIR]):
            kp: int32[DIR] = 0
            for t in range(NUM_IT):
                with allo.meta_for(0, DIR) as o:
                    if dmask[o] == 1:
                        wv: UInt(PS) = 0
                        wk: int1 = 0
                        wv, wk = ext_out[o].try_get()
                        if wk == 1 and kp[o] < LANELEN:
                            dout[o, kp[o]] = wv
                            kp[o] += 1

    return df.build(router_rvn_v, target="simulator")


def pack(data, x, y, vc=0):
    return int(data | (x << X_LO) | (y << Y_LO) | (vc << VC_LO))


PORT_NAME = {NORTH: "N", SOUTH: "S", WEST: "W", EAST: "E", LOCAL: "L"}


def run(sim, seeds, label, drain=None):
    """seeds: (port, lane, data, x, y[, vc])."""
    inj = np.zeros((DIR, LANELEN), dtype=np.int32)
    dlv = np.zeros((DIR, LANELEN), dtype=np.int32)
    dm = np.ones(DIR, dtype=np.int32) if drain is None else np.array(drain, dtype=np.int32)
    for s in seeds:
        p, lane, data, x, y = s[0], s[1], s[2], s[3], s[4]
        vc = s[5] if len(s) > 5 else 0
        inj[p, lane] = pack(data, x, y, vc)
    sim(inj, dlv, dm)
    if label:
        print(f"\n--- {label} ---")
    return dlv


def arrived(dlv, port):
    return [int(dlv[port, k]) & 0xFFFF for k in range(LANELEN)]


def functional_tests(sim, tag):
    """The four tests from router_rvn_fused.py, verbatim in intent so the numbers are
    directly comparable.  All traffic sits on VC0 -- these check that adding VCs did not
    break the Stage 0 router."""
    allok = True

    dlv = run(sim, [(p, 0, 0x100 + p, ROUTER_X, ROUTER_Y)
                    for p in (NORTH, SOUTH, WEST, EAST)],
              f"[{tag}] T1: 4 inputs -> LOCAL (ejection)")
    got = arrived(dlv, LOCAL)
    ok1 = all((0x100 + p) in got for p in (NORTH, SOUTH, WEST, EAST))
    for p in (NORTH, SOUTH, WEST, EAST):
        print(f"  in {PORT_NAME[p]} -> LOCAL : "
              f"{'ok' if (0x100 + p) in got else 'MISSING'}")
    print("T1", "PASS" if ok1 else "FAIL")
    allok = allok and ok1

    cases = [(0x201, ROUTER_X - 1, ROUTER_Y, NORTH),
             (0x202, ROUTER_X + 1, ROUTER_Y, SOUTH),
             (0x203, ROUTER_X,     ROUTER_Y - 1, WEST),
             (0x204, ROUTER_X,     ROUTER_Y + 1, EAST)]
    dlv = run(sim, [(LOCAL, k, d, x, y) for k, (d, x, y, _) in enumerate(cases)],
              f"[{tag}] T2: LOCAL -> each direction (XY routing)")
    ok2 = True
    for d, x, y, want in cases:
        hit = d in arrived(dlv, want)
        print(f"  dest({x},{y}) -> {PORT_NAME[want]} : {'ok' if hit else 'MISSING'}")
        ok2 = ok2 and hit
    print("T2", "PASS" if ok2 else "FAIL")
    allok = allok and ok2

    dlv = run(sim, [(NORTH, 0, 0x301, ROUTER_X, ROUTER_Y + 1),
                    (SOUTH, 0, 0x302, ROUTER_X, ROUTER_Y + 1)],
              f"[{tag}] T3: 2 inputs contend for EAST (must be lossless)")
    east = arrived(dlv, EAST)
    ok3 = (0x301 in east) and (0x302 in east)
    print(f"  0x301 : {'delivered' if 0x301 in east else 'LOST'}")
    print(f"  0x302 : {'delivered' if 0x302 in east else 'LOST'}")
    print("T3", "PASS (lossless)" if ok3 else "FAIL (a flit was dropped)")
    allok = allok and ok3

    seeds = []
    for p in (NORTH, SOUTH, WEST, LOCAL):
        for lane in range(3):
            seeds.append((p, lane, 0x400 + 0x10 * p + lane, ROUTER_X, ROUTER_Y + 1))
    dlv = run(sim, seeds, f"[{tag}] T4: 4 sources -> EAST, round-robin fairness")
    east = arrived(dlv, EAST)
    per_src = {p: sum(1 for lane in range(3)
                      if (0x400 + 0x10 * p + lane) in east)
               for p in (NORTH, SOUTH, WEST, LOCAL)}
    for p, n in per_src.items():
        print(f"  source {PORT_NAME[p]} : {n}/3 delivered")
    ok4 = all(n > 0 for n in per_src.values())
    print("T4", "PASS (no source starved)" if ok4 else "FAIL (a source got nothing)")
    allok = allok and ok4
    return allok


def vc_smoke_test(sim, tag):
    """T5: two flits on DIFFERENT VCs of the SAME input port, both to LOCAL.  Nothing is
    congested here -- this only checks the demux/arbiter plumbing does not lose a flit
    that rode in on VC1."""
    dlv = run(sim, [(NORTH, 0, 0x501, ROUTER_X, ROUTER_Y, 0),
                    (NORTH, 1, 0x502, ROUTER_X, ROUTER_Y, 1)],
              f"[{tag}] T5: VC0 + VC1 on one port -> LOCAL")
    loc = arrived(dlv, LOCAL)
    ok = (0x501 in loc) and (0x502 in loc)
    print(f"  0x501 (vc0) : {'delivered' if 0x501 in loc else 'LOST'}")
    print(f"  0x502 (vc1) : {'delivered' if 0x502 in loc else 'LOST'}")
    print("T5", "PASS" if ok else "FAIL")
    return ok


# ---------------------------------------------------------------------------------
# T6 -- HEAD-OF-LINE BLOCKING, the test VCs exist to pass.
#
# Traffic on input NORTH, in link order:
#     F1..F6  -> EAST   (EAST is jammed: drain[EAST]=0, so the collector never reads it)
#     B       -> LOCAL  (LOCAL is completely free)
#
# EAST can absorb exactly 5 flits before it backs up (ext_out depth 4 + the output
# register).  F6 therefore sticks in NORTH's VC buffer forever.  B is behind it on the
# link and is bound for a free output, so whether B is delivered is purely a question of
# whether F6 can be stepped over.
#
#   * 1 VC   : F6 owns the only buffer, B jams in the staging register.  B NEVER ARRIVES.
#   * 2 VCs, B tagged vc1 : F6 sits in VC0, B goes into VC1 and sails out to LOCAL.
#   * 2 VCs, B tagged vc0 (control) : B addresses the SAME buffer F6 holds, so the VC
#     hardware cannot help and B is blocked again.  This control is what proves the
#     difference is the VC and not the extra buffering.
# ---------------------------------------------------------------------------------
NFILL = 6


def hol_seeds(b_vc):
    seeds = [(NORTH, k, 0x610 + k, ROUTER_X, ROUTER_Y + 1, 0) for k in range(NFILL)]
    seeds.append((NORTH, NFILL, 0x6BB, ROUTER_X, ROUTER_Y, b_vc))
    return seeds


def hol_probe(sim, b_vc, tag):
    dm = np.ones(DIR, dtype=np.int32)
    dm[EAST] = 0                      # jam EAST
    dlv = run(sim, hol_seeds(b_vc), None, drain=dm)
    got = 0x6BB in arrived(dlv, LOCAL)
    print(f"  {tag:<34s} B(0x6BB)->LOCAL : {'DELIVERED' if got else 'blocked'}")
    return got


if __name__ == "__main__":
    print("building NVC=2 ...")
    sim2 = build_router(2)
    ok_2 = functional_tests(sim2, "NVC=2")
    ok_2 = vc_smoke_test(sim2, "NVC=2") and ok_2
    cyc2 = sim2.get_cycles().per_pe

    print("\nbuilding NVC=1 (same source, VCMASK=0) ...")
    sim1 = build_router(1)
    print("\n(sanity: the 1-VC build must still pass the Stage 0 tests)")
    ok_1 = functional_tests(sim1, "NVC=1")
    cyc1 = sim1.get_cycles().per_pe

    print("\n--- T6: head-of-line blocking (EAST jammed, B bound for free LOCAL) ---")
    h1 = hol_probe(sim1, 0, "NVC=1                 :")
    h2 = hol_probe(sim2, 1, "NVC=2, B on vc1       :")
    h2c = hol_probe(sim2, 0, "NVC=2, B on vc0 (ctrl):")
    ok6 = (not h1) and h2 and (not h2c)
    print("T6", "PASS -- VCs demonstrably break head-of-line blocking"
          if ok6 else "FAIL -- no VC benefit demonstrated")

    print("\nper-PE cycles NVC=1:", cyc1)
    print("per-PE cycles NVC=2:", cyc2)
    print("\nALL:", "PASS" if (ok_2 and ok_1 and ok6) else "FAIL")
