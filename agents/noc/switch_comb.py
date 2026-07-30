import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import allo
from allo.ir.types import int32, int1, UInt, Wire
import allo.dataflow as df
import numpy as np

# =====================================================================================
# switch_comb -- a 2x2 COMBINATIONAL switch, rebuilt in Allo on Wire links.
#
# Port of section3_switch_comb from Zhao & Hoe, "Using Vivado-HLS for Structural Design:
# a NoC Case Study" (arXiv:1710.10290v2, MIT licence).  Reference source lives at
# pe_core_implementation/inspo_router_noc/report_code_examples/section3_switch_comb/.
#
# WHAT IT IS.  Two inputs, two outputs, no state at all.  A flit is routed by the PARITY
# of its data -- odd to the Odd port, even to the Even port -- with fixed priority: input
# 1 beats input 2 when both want the same output.  Parity stands in for a routing
# function; the point of the design is the INTERFACE, not the routing.
#
# WHY THIS IS THE RIGHT FIRST WIRE DESIGN.  Their `VData {bool v; int d;}` is literally
# valid_only -- a valid bit travelling with the data and no ready line -- and their
# `acpt` outputs are the ready line, split out as separate bare wires.  So the original
# is `Channel[valid_ready]` decomposed into its constituent wires, which is exactly what
# our `Wire` models.  Every other example in that report adds buffering or pipelining;
# this one is pure combinational logic, so the link semantics are the whole content.
#
# THE STYLE2 DISCIPLINE, KEPT.  The paper gives two versions of the same logic. STYLE1
# writes `*Odd` in several branches; STYLE2 accumulates into a local temp and assigns
# each output port EXACTLY ONCE at the end.  That is not cosmetic: multiple writes to an
# output force HLS to add an output-valid signal you did not ask for, whereas a single
# write gives a bare `ap_none` wire (SKILLS.md section 6).  We keep STYLE2 -- and it may
# matter for our own Catapult trouble, where the complaint is about per-port write
# offsets.
#
# WHAT A WIRE FORCES.  No handshake, so every wire is written every cycle and read every
# cycle, unconditionally.  Validity is IN-BAND: bit VBIT of the word.  Note this design
# needs an explicit valid bit rather than our usual "0 means nothing" convention, because
# data 0 is a legal payload here -- it is even, so it routes to the Even port.
#
# THE ONE THING WE CANNOT COPY.  Their `acpt` is a BACKWARD combinational signal to the
# producer.  Inside one module that is fine, and it is fine here because the accepts flow
# forward to the collector rather than back to `drv`.  But compose two of these switches
# and the accept path closes a combinational loop, which a Wire cannot express -- at that
# point the accept has to become a Channel.  That boundary is the real lesson.
#
# SYSTEMC ONLY: the JIT simulator has no Wire support whatsoever.
# =====================================================================================

DW = 16                      # data width
VBIT = DW                    # valid bit sits just above the data
PS = DW + 1                  # 17 -- deliberately NOT a standard width (8/16/32/64),
                             # which would emit as a native C type for locals but ac_int
                             # for ports, and the two will not bind through PopNB.
DMASK = (1 << DW) - 1

NCYC = 16                    # one input pair per cycle; also the trace length


def vd(valid, data):
    """Pack a VData: valid bit + data. The host-side mirror of the in-band format."""
    return int(((valid & 1) << VBIT) | (data & DMASK))


@df.region()
def switch_comb(i1: int32[NCYC], i2: int32[NCYC],
                odd: int32[NCYC], even: int32[NCYC],
                ac1: int32[NCYC], ac2: int32[NCYC]):
    # Six wires: two in, two out, two accepts. No depth, no handshake -- a Wire is a
    # value that exists each cycle, nothing more.
    w_i1:  Wire[UInt(PS)]
    w_i2:  Wire[UInt(PS)]
    w_odd: Wire[UInt(PS)]
    w_ev:  Wire[UInt(PS)]
    w_a1:  Wire[int32]
    w_a2:  Wire[int32]

    # ── THE SWITCH: stateless. One loop iteration == one clock cycle. ──
    @df.kernel(mapping=[1], args=[])
    def sw():
        for t in range(NCYC):
            # Read both inputs unconditionally -- a Wire cannot be "not read".
            a: UInt(PS) = w_i1.get()
            b: UInt(PS) = w_i2.get()

            # NB: do NOT name locals v0/v1/v2/... -- the SystemC emitter generates its
            # own SSA names in that exact series, and a collision produces C++ like
            # `v2.write(...)` where v2 is your int, not the port. Silent until g++.
            vld1: int32 = (a >> VBIT) & 1
            vld2: int32 = (b >> VBIT) & 1
            p1: int32 = a & 1                  # parity of input 1's data
            p2: int32 = b & 1

            # STYLE2: accumulate into temps, never touch an output more than once.
            t_odd: UInt(PS) = 0                # valid bit clear == invalid
            t_ev:  UInt(PS) = 0
            t_a1:  int32 = 0
            t_a2:  int32 = 0

            # Odd port: input 1 has priority over input 2.
            if vld1 == 1 and p1 == 1:
                t_odd = a
                t_a1 = 1
            elif vld2 == 1 and p2 == 1:
                t_odd = b
                t_a2 = 1

            # Even port: same fixed priority. An input is odd XOR even, so at most one
            # of the two blocks can accept a given input -- the accepts cannot conflict.
            if vld1 == 1 and p1 == 0:
                t_ev = a
                t_a1 = 1
            elif vld2 == 1 and p2 == 0:
                t_ev = b
                t_a2 = 1

            # Each output written EXACTLY ONCE -- the STYLE2 rule.
            w_odd.put(t_odd)
            w_ev.put(t_ev)
            w_a1.put(t_a1)
            w_a2.put(t_a2)

    # ── DRIVER: presents one input pair per cycle. Writes every cycle, as a wire demands.
    @df.kernel(mapping=[1], args=[i1, i2])
    def drv(d1: int32[NCYC], d2: int32[NCYC]):
        for t in range(NCYC):
            x: UInt(PS) = d1[t]
            y: UInt(PS) = d2[t]
            w_i1.put(x)
            w_i2.put(y)

    # ── COLLECTOR: samples all four outputs every cycle, giving a cycle-by-cycle trace.
    @df.kernel(mapping=[1], args=[odd, even, ac1, ac2])
    def col(o: int32[NCYC], e: int32[NCYC], a1: int32[NCYC], a2: int32[NCYC]):
        for t in range(NCYC):
            # A wire yields UInt(PS); the host array is int32 and there is NO implicit
            # widening -- storing directly gives "value to store must have the same type
            # as memref element type". Go through an explicit int32 temp.
            ow: UInt(PS) = w_odd.get()
            ew: UInt(PS) = w_ev.get()
            oi: int32 = ow
            ei: int32 = ew
            o[t] = oi
            e[t] = ei
            a1[t] = w_a1.get()      # these wires are already int32
            a2[t] = w_a2.get()


def run(pairs):
    """pairs: list of ((v1,d1),(v2,d2)) per cycle. Returns the per-cycle trace."""
    i1 = np.zeros(NCYC, dtype=np.int32); i2 = np.zeros(NCYC, dtype=np.int32)
    odd = np.zeros(NCYC, dtype=np.int32); even = np.zeros(NCYC, dtype=np.int32)
    a1 = np.zeros(NCYC, dtype=np.int32);  a2 = np.zeros(NCYC, dtype=np.int32)
    for k, ((v1, d1), (v2, d2)) in enumerate(pairs):
        i1[k] = vd(v1, d1)
        i2[k] = vd(v2, d2)
    mod(i1, i2, odd, even, a1, a2)
    return odd, even, a1, a2


def unpack(w):
    w = int(w)
    return (w >> VBIT) & 1, w & DMASK


if __name__ == "__main__":
    PROJECT = os.environ.get(
        "ALLO_CSIM_OUT", os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                      "csim_out", "switch_comb"))
    os.makedirs(PROJECT, exist_ok=True)
    print(f"[csim] generating + building into {PROJECT}", flush=True)
    # SYSTEMC ONLY -- target="simulator" cannot build a Wire (no Wire op handlers at all).
    mod = df.build(switch_comb, target="systemc", mode="csim", project=PROJECT)

    # The full truth table of the fixed-priority switch, one case per cycle.
    #             input 1          input 2         expectation
    cases = [
        ((1, 3), (1, 4), "1->Odd, 2->Even, both accepted"),
        ((1, 4), (1, 3), "1->Even, 2->Odd, both accepted"),
        ((1, 3), (1, 5), "both ODD  -> 1 wins, 2 refused"),
        ((1, 4), (1, 6), "both EVEN -> 1 wins, 2 refused"),
        ((0, 0), (1, 7), "1 invalid -> 2 takes Odd"),
        ((1, 0), (0, 0), "d=0 is EVEN and valid -> Even"),
    ]
    pairs = [(c[0], c[1]) for c in cases] + [((0, 0), (0, 0))] * (NCYC - len(cases))
    odd, even, a1, a2 = run(pairs)

    ok = True
    print()
    for k, (in1, in2, note) in enumerate(cases):
        ov, od = unpack(odd[k]); ev, ed = unpack(even[k])
        print(f"  cyc{k}  I1={in1} I2={in2} -> Odd={'(%d)' % od if ov else '-':>5s} "
              f"Even={'(%d)' % ed if ev else '-':>5s} acpt=({int(a1[k])},{int(a2[k])})   {note}")

    # --- checks, derived from the reference semantics ---
    def chk(name, cond):
        global ok
        print(f"  {name:<34s} {'PASS' if cond else 'FAIL'}")
        ok = ok and cond

    print()
    chk("S1 split odd/even",   unpack(odd[0]) == (1, 3) and unpack(even[0]) == (1, 4)
                               and a1[0] == 1 and a2[0] == 1)
    chk("S2 split, swapped",   unpack(odd[1]) == (1, 3) and unpack(even[1]) == (1, 4)
                               and a1[1] == 1 and a2[1] == 1)
    chk("S3 both odd, I1 wins", unpack(odd[2]) == (1, 3) and a1[2] == 1 and a2[2] == 0)
    chk("S4 both even, I1 wins", unpack(even[3]) == (1, 4) and a1[3] == 1 and a2[3] == 0)
    chk("S5 invalid I1 ignored", unpack(odd[4]) == (1, 7) and a1[4] == 0 and a2[4] == 1)
    chk("S6 data 0 is even",   unpack(even[5]) == (1, 0) and a1[5] == 1)
    chk("S7 idle cycles quiet", all(odd[k] == 0 and even[k] == 0
                                    for k in range(len(cases), NCYC)))

    print("\n=== switch_comb:", "ALL PASS" if ok else "FAILURES", "===")
    raise SystemExit(0 if ok else 1)
