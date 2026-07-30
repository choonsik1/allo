import os; os.environ.setdefault("OMP_NUM_THREADS", "16")
import sys
import allo
from allo.ir.types import int32, UInt, Stream, Wire
import allo.dataflow as df
import numpy as np

# =====================================================================================
# NARROW FIFO + WIRE SIDEBAND -- using a Wire for what a Wire is actually good at.
#
# THE SETUP.  A two-stage pipeline where the consumer needs a PAYLOAD and a derived TAG
# at the same instant.  Two ways to get both across the boundary:
#
#   packed    ONE wide FIFO carries payload+tag   Stream[UInt(24),2] = 48 bits stored
#   sideband  narrow FIFO carries payload only,   Stream[UInt(16),2] = 32 bits stored
#             the tag rides a Wire                + Wire[UInt(8)]    =  0 bits stored
#
# Same arithmetic, same harness, one structural change: a 33% narrower FIFO for identical
# behaviour.  That is the concrete form of "a wire is free".
#
# WHY THE TAG IS THE RIGHT THING TO MOVE.  It is DERIVED from the payload and consumed in
# the SAME expression (`c[i] = d * (tg + 1)`).  There is no instant where the consumer
# holds one and waits for the other, so the tag has nothing to gain from being buffered.
# Anything that must survive backpressure independently does NOT belong on a wire.
#
# WHY THIS WIRE IS SOUND, WHERE pe_split.py's WAS NOT.
# A Wire gives zero storage AND zero handshake, therefore zero alignment -- on its own,
# producer and consumer free-run and the reader samples garbage.  pe_split.py showed
# exactly that: `acc` read a wire with nothing ordering it against `mul` and got the
# signal's initial 0 eight times running.
#
# Here the ordering is explicit and the blocking FIFO supplies the barrier:
#      gen:   side.put(tg)   THEN   link.put(d)      <- drive wire, THEN push
#      proc:  d = link.get() THEN   tg = side.get()  <- blocks, THEN read wire
# `proc` cannot reach the wire read until `gen`'s push completed, and `gen` drove the wire
# BEFORE pushing.  So the value is current by construction, not by luck.
#
# SWAP THOSE TWO LINES IN EITHER KERNEL AND THE DESIGN IS RACY.  That is the whole
# discipline: a Wire is a sideband on a link that already provides ordering, never a
# standalone boundary between independently-paced kernels.
#
# SYSTEMC ONLY -- the JIT simulator has no Wire support, so `packed` can run on both but
# `sideband` cannot; the comparison has to be done on csim.
# =====================================================================================

DW = 16                      # payload: needs buffering, must survive backpressure
TW = 8                       # tag: derived metadata, needed at the same instant only
PACKED_W = DW + TW           # 24 -- one wide FIFO carries both
NARROW_W = DW                # 16 -- the FIFO carries payload ONLY
N = 8                        # elements pushed through the pipeline


# ── BASELINE: one wide FIFO. Payload and tag are both buffered. ──
@df.region()
def pipe_packed(A: int32[N], C: int32[N]):
    link: Stream[UInt(PACKED_W), 2]            # 2 slots x 24 bits = 48 bits stored

    @df.kernel(mapping=[1], args=[A])
    def gen(a: int32[N]):
        for i in range(N):
            d: UInt(DW) = a[i] & 0xFFFF        # payload
            tg: UInt(TW) = a[i] & 3            # tag: derived from the data
            packed: UInt(PACKED_W) = (tg << DW) | d
            link.put(packed)                   # both fields into the wide word

    @df.kernel(mapping=[1], args=[C])
    def proc(c: int32[N]):
        for i in range(N):
            w: UInt(PACKED_W) = link.get()     # blocking: one wide word
            dw: UInt(DW) = w & 0xFFFF          # unpack payload
            tw: UInt(TW) = (w >> DW) & 0xFF    # unpack tag
            d: int32 = dw
            tg: int32 = tw
            c[i] = d * (tg + 1)                # the work needs BOTH, same instant


# ── SIDEBAND: narrow FIFO + a Wire. Same behaviour, 1/3 less FIFO. ──
@df.region()
def pipe_sideband(A: int32[N], C: int32[N]):
    link: Stream[UInt(NARROW_W), 2]            # 2 slots x 16 bits = 32 bits stored
    side: Wire[UInt(TW)]                       # combinational: no depth, no handshake

    @df.kernel(mapping=[1], args=[A])
    def gen(a: int32[N]):
        for i in range(N):
            d: UInt(DW) = a[i] & 0xFFFF
            tg: UInt(TW) = a[i] & 3
            side.put(tg)                       # (1) drive the wire FIRST ...
            link.put(d)                        # (2) ... THEN push. The push is the barrier.

    @df.kernel(mapping=[1], args=[C])
    def proc(c: int32[N]):
        for i in range(N):
            # A link yields its own UInt type; there is NO implicit conversion to the
            # int32 of the host array. Go through explicit typed temps or the store
            # fails with "value to store must have the same type as memref element type".
            dw: UInt(NARROW_W) = link.get()    # (3) BLOCKS until gen pushed
            tw: UInt(TW) = side.get()          # (4) safe: wire driven before that push
            d: int32 = dw
            tg: int32 = tw
            c[i] = d * (tg + 1)                # identical arithmetic to the packed variant


VARIANTS = {"packed": pipe_packed, "sideband": pipe_sideband}
FIFO_BITS = {"packed": 2 * PACKED_W, "sideband": 2 * NARROW_W}
SHAPE = {"packed":   f"Stream[UInt({PACKED_W}),2]                 ",
         "sideband": f"Stream[UInt({NARROW_W}),2] + Wire[UInt({TW})]"}


def golden(a):
    d = (a & 0xFFFF).astype(np.int64)
    tg = (a & 3).astype(np.int64)
    return (d * (tg + 1)).astype(np.int32)


if __name__ == "__main__":
    which = sys.argv[1] if len(sys.argv) > 1 else "all"
    target = sys.argv[2] if len(sys.argv) > 2 else "systemc"
    names = list(VARIANTS) if which == "all" else [which]

    a = np.array([7, 12, 5, 30, 9, 44, 3, 21], dtype=np.int32)
    want = golden(a)
    print(f"target={target}\n  A        = {a}\n  expected = {want}\n", flush=True)

    results = {}
    for nm in names:
        if target == "simulator" and nm == "sideband":
            print(f"  {nm:<9s} SKIPPED (Wire has no JIT-simulator support)", flush=True)
            continue
        c = np.zeros(N, dtype=np.int32)
        if target == "simulator":
            mod = df.build(VARIANTS[nm], target="simulator")
        else:
            prj = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                               "csim_out", f"sb_{nm}")
            os.makedirs(prj, exist_ok=True)
            mod = df.build(VARIANTS[nm], target="systemc", mode="csim", project=prj)
        mod(a, c)
        ok = bool((c == want).all())
        results[nm] = ok
        print(f"  {nm:<9s} {SHAPE[nm]}  FIFO={FIFO_BITS[nm]:>3d} bits  "
              f"C={c}  {'PASS' if ok else 'FAIL'}", flush=True)

    if len(results) > 1 and all(results.values()):
        saved = FIFO_BITS['packed'] - FIFO_BITS['sideband']
        print(f"\n  Identical results, {saved} fewer FIFO bits "
              f"({100*saved//FIFO_BITS['packed']}% narrower) -- the tag cost nothing.")
    raise SystemExit(0 if all(results.values()) else 1)
