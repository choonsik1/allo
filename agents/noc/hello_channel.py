import os; os.environ.setdefault("OMP_NUM_THREADS", "8")
import sys
import allo
from allo.ir.types import int32, Channel, valid_ready
import allo.dataflow as df
import numpy as np

# =====================================================================================
# THE SMALLEST POSSIBLE CHANNEL DESIGN -- a producer and a consumer joined by one
# combinational (zero-buffer) valid/ready link. Nothing else.
#
# Written as the reference example: if you want to see what a Channel becomes in SystemC
# and in RTL, this is the design to read, because there is nothing else in it to confuse
# the picture. Two kernels, one link, one loop each.
#
# WHAT "COMBINATIONAL CHANNEL" MEANS HERE.
#   Stream[T,N]  = FIFO: N slots of storage AND a handshake.
#   Channel[T,valid_ready] = the handshake WITHOUT the storage. A transfer happens when
#       producer and consumer are both live in the same cycle; nothing is buffered.
#   Wire[T]      = neither storage nor handshake -- and therefore no synchronisation at
#       all, which is why a Wire boundary between independently-paced kernels reads
#       garbage (see pe_split.py). A Channel does NOT have that problem: the blocking
#       put/get are the synchronisation.
#
# WHAT TO LOOK FOR IN THE EMITTED SYSTEMC (csim_out/hello_channel/kernel.cpp):
#   * the link becomes ONE object:  Connections::Combinational<ac_int<32,true>> vNN;
#     with prod bound to it as an Out and cons as an In. There is NO AlloFifo module --
#     compare against a Stream design, where every link additionally instantiates
#     AlloFifo<T,N> and TWO Combinationals (in and out).
#   * each kernel is an SC_MODULE with one SC_THREAD; `put`/`get` become Push/Pop.
#
# BUILD NOTES (each of these cost real debugging time elsewhere):
#   * SYSTEMC ONLY. Channel does not lower to the JIT simulator -- target="simulator"
#     will not build this.
#   * ONE host array per kernel. prod owns A, cons owns B. Kernels owning two or more
#     arrays HANG under csim while running fine on the JIT simulator.
#   * int32 throughout, deliberately: a link of UInt(W) yields its own type and there is
#     no implicit conversion when storing into an int32 host array.
#   * Do NOT name locals v0/v1/v2... -- the emitter generates its own SSA names in that
#     series and a collision silently produces wrong C++.
# =====================================================================================

N = 8


@df.region()
def hello_channel(A: int32[N], B: int32[N]):
    # THE combinational link: a valid/ready handshake with no buffer at all.
    link: Channel[int32, valid_ready]

    @df.kernel(mapping=[1], args=[A])
    def prod(a: int32[N]):
        for i in range(N):
            link.put(a[i])          # blocking: completes when cons is ready

    @df.kernel(mapping=[1], args=[B])
    def cons(b: int32[N]):
        for i in range(N):
            b[i] = link.get()       # blocking: waits until prod offers


if __name__ == "__main__":
    mode = sys.argv[1] if len(sys.argv) > 1 else "csim"
    here = os.path.dirname(os.path.abspath(__file__))
    prj = os.path.join(here, "csim_out" if mode == "csim" else "csyn_out",
                       "hello_channel")
    os.makedirs(prj, exist_ok=True)
    print(f"[{mode}] project -> {prj}", flush=True)

    if mode == "csim":
        mod = df.build(hello_channel, target="systemc", mode="csim", project=prj)
        a = np.arange(1, N + 1, dtype=np.int32) * 11
        b = np.zeros(N, dtype=np.int32)
        mod(a, b)
        ok = bool((b == a).all())
        print(f"  A = {a}\n  B = {b}\n  {'PASS' if ok else 'FAIL'} (B must equal A)")
        print(f"\n  emitted SystemC: {prj}/kernel.cpp")
        raise SystemExit(0 if ok else 1)
    else:
        # csyn takes NO arguments -- it is a build-only mode.
        df.build(hello_channel, target="systemc", mode="csyn", project=prj)()
        print("  CSYN OK")
        print(f"  RTL: {prj}/Catapult/hello_channel.v1/rtl.v")
