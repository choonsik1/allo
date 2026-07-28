"""
check_dce_survival.py -- did the IR we emitted actually reach the JIT?

Counts an op BEFORE the lowering pipeline (right after build_dataflow_simulator)
and AFTER it, and fails loudly if the count drops.

Why this exists: MemRefDCE.cpp:28 erases ANY op that has results and no uses,
with NO side-effect check --

    if (op->getNumResults() != 0 && op->use_empty()) { op->erase(); }

so a side-effecting op whose result we ignore is deleted silently. That bit the
circular-wait watchdog: all 10 memref.atomic_rmw ops were emitted and then
removed before LLVM, leaving the watchdog as dead code that produced no error,
no warning, and no detection. Same trap as a try_put whose `ok` flag is unread.

The lesson generalises: "my emission helper ran" does NOT mean "the op is in the
final module". probe_guard_emission.py proved the helper was called 10 times
while 0 ops survived -- only this before/after comparison localised the loss to
the pass pipeline.

Usage:
    python simulator_profiling/check_dce_survival.py [pre_op] [post_op]

Defaults to memref.atomic_rmw -> llvm.atomicrmw. Exits non-zero if any dropped.
Needs LLVM_BUILD_DIR set (the `allo` conda env sets it; do not override).
"""
import sys

sys.path.insert(0, "/home/zsm9/allo_sup")
import allo  # noqa: F401
import allo.dataflow as df
from allo.ir.types import int32, Stream
import allo.backend.simulator as S

# Pre-lowering op spelling, and what it becomes after conversion to LLVM.
PRE_OP = sys.argv[1] if len(sys.argv) > 1 else "atomic_rmw"
POST_OP = sys.argv[2] if len(sys.argv) > 2 else "atomicrmw"

_seen = {}
_orig = S.build_dataflow_simulator


def _capture(module, top_name):
    """Snapshot the module before the pass pipeline runs."""
    result = _orig(module, top_name)
    _seen["pre"] = str(module).count(PRE_OP)
    return result


S.build_dataflow_simulator = _capture


@df.region()
def top(out: int32[2]):
    """Circular wait: A needs S2 before filling S1, B needs S1 before filling S2.
    Chosen because this is the case whose detection the dropped atomics broke."""
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


mod = df.build(top, target="simulator")
pre = _seen.get("pre", 0)
post = str(mod.module).count(POST_OP)

print(f"emitted  ({PRE_OP:>12}): {pre}")
print(f"survived ({POST_OP:>12}): {post}")
if pre == 0:
    print("\nFAIL: nothing emitted -- the guard never ran (check _SIM_CTX['n_pes']).")
    sys.exit(1)
if post < pre:
    print(f"\nFAIL: {pre - post} op(s) dropped by the pass pipeline.")
    print("Almost certainly MemRefDCE erasing a result-producing op with no uses.")
    print("Fix: consume the result (e.g. sink it into a live global slot).")
    sys.exit(1)
print("\nOK: every emitted op survived to the JIT.")
