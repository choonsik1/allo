"""
probe_guard_emission.py -- is the deadlock guard being emitted, and is the
blocked-PE counter balanced?

Monkeypatches _emit_blocked_delta to record every (+1 / -1) the compiler emits,
then checks the invariant the circular-wait watchdog depends on:

    (#increments) - (#decrements) == n_pes

Each blocking spin loop emits a matched +1 (entering) / -1 (leaving) pair, and
each PE termination emits an unpaired +1 (a finished PE counts as permanently
blocked -- otherwise n_blocked could never reach n_pes once any PE exits).  So
the surplus must be exactly one per PE.  If it is not, n_blocked drifts and the
watchdog either never fires or fires spuriously.

Pairs with check_dce_survival.py, and you usually need BOTH:
  * this script  -> were the ops emitted at all?          (compiler side)
  * check_dce_*  -> did they survive to the JIT?          (pass-pipeline side)
When the atomics were being erased by MemRefDCE, this reported a healthy 10
calls while 0 ops reached LLVM.  Either check alone would have been misleading.

Also prints which allo checkout was imported -- `import allo` silently prefers
an installed /home/zsm9/allo over the working tree unless PYTHONPATH forces it,
and debugging an edit that was never loaded is a long afternoon.

Usage:
    python simulator_profiling/probe_guard_emission.py

Needs LLVM_BUILD_DIR set (the `allo` conda env sets it; do not override).
Exits non-zero if the counter is unbalanced or nothing was emitted.
"""
import sys

sys.path.insert(0, "/home/zsm9/allo_sup")
import allo.backend.simulator as S

print(f"imported allo from : {S.__file__}")
print(f"_DL_SLOTS          : {S._DL_SLOTS}")
print(f"_DL_POLLS          : {S._DL_POLLS}  (consecutive all-blocked polls to fire)")

deltas = []
_orig = S._emit_blocked_delta


def _spy(module, n, delta, ip):
    deltas.append(delta)
    return _orig(module, n, delta, ip)


S._emit_blocked_delta = _spy

import allo  # noqa: E402,F401
import allo.dataflow as df  # noqa: E402
from allo.ir.types import int32, Stream  # noqa: E402


@df.region()
def top(out: int32[2]):
    """Circular wait: 2 PEs, 2 blocking spin loops each (one get, one put)."""
    S1: Stream[int32, 2][1]
    S2: Stream[int32, 2][1]

    @df.kernel(mapping=[1], args=[out])
    def A(o: int32[2]):
        x: int32 = S2[0].get()
        S1[0].put(x)
        o[0] = x

    @df.kernel(mapping=[1])
    def B():
        y: int32 = S1[0].get()
        S2[0].put(y)


df.build(top, target="simulator")

n_pes = S._SIM_CTX["n_pes"]
incs = sum(1 for d in deltas if d > 0)
decs = sum(1 for d in deltas if d < 0)
print(f"\nn_pes              : {n_pes}")
print(f"streams            : {S._SIM_CTX['stream_ids']}")
print(f"+1 emitted         : {incs}   (spin-loop entries + {n_pes} PE terminations)")
print(f"-1 emitted         : {decs}   (spin-loop exits)")

if not deltas:
    print("\nFAIL: guard emitted nothing -- no clocked PEs, or the guard early-returned.")
    sys.exit(1)
if incs - decs != n_pes:
    print(f"\nFAIL: surplus is {incs - decs}, expected {n_pes} (one per PE termination).")
    print("The blocked counter will drift; circular-wait detection is unreliable.")
    sys.exit(1)
print(f"\nOK: balanced -- surplus {incs - decs} == n_pes {n_pes}.")
