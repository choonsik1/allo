"""SystemC (Catapult) csim tests for router_rvn_chan.py -- the Channel[valid_ready] router.

Kept SEPARATE from router_rvn_chan.py on purpose: that file is the design, and its
__main__ is a codegen demo (it prints the emitted SystemC).  This driver is the test
harness.  It does not import or modify anything in the design file beyond its symbols.

WHY THERE IS NO SIMULATOR EQUIVALENT
    router_rvn_chan.py cannot run on the JIT simulator at all -- `Channel` does not lower
    to it.  csim is the ONLY backend that executes this design, which is also why the
    Channel variant went unvalidated far longer than the Stream ones.

HOW TO RUN
    conda activate allo
    export LLVM_BUILD_DIR=/work/shared/common/llvm-project-main/build-rhel8
    export PYTHONPATH=/home/zsm9/allo_sup:/home/zsm9/allo_sup/agents/noc
    export MGC_HOME=/opt/siemens/catapult/2024.2/Mgc_home
    export PATH=$MGC_HOME/bin:$PATH
    export SYSTEMC_HOME=$MGC_HOME/shared
    export ALLO_CXX_EXTRA="-L$CONDA_PREFIX/lib -Wl,-rpath,$CONDA_PREFIX/lib"
    export OMP_NUM_THREADS=8
    cd /home/zsm9/allo_sup/agents/noc && python csim_chan.py

    All four Catapult/SystemC exports are REQUIRED, not optional:
      * without SYSTEMC_HOME  -> "Set SYSTEMC_HOME for systemc csim"
      * without ALLO_CXX_EXTRA -> the g++ link fails; libsystemc wants GLIBCXX_3.4.26,
        which this host's system libstdc++ does not have, so it must pick up conda's.
    Do NOT use `python -c` -- allo parses kernels via inspect.getsource, which needs a
    real file ("could not get source code").

WHERE THE OUTPUT GOES
    Everything generated lands in ./csim_out/chan (override with $ALLO_CSIM_OUT):
      kernel.cpp   the emitted SystemC -- look for Connections::Combinational, a
                   handshake with NO storage, which is what makes this the faithful
                   s_flit_req_t/s_flit_resp_t rather than a buffered FIFO
      sim          the compiled binary that runs
      csim.sh      the exact g++ compile+run line, to rerun by hand
      *.data       the input/output arrays as marshalled to and from the design
"""
import os
import numpy as np
import allo.dataflow as df
import router_rvn_chan as C

PROJECT = os.environ.get(
    "ALLO_CSIM_OUT",
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "csim_out", "chan"))

D, L = C.DIR, C.LANELEN
NAME = {C.NORTH: "N", C.SOUTH: "S", C.WEST: "W", C.EAST: "E", C.LOCAL: "L"}


def pack(data, x, y):
    """Build a flit: payload in the low bits, destination coordinates above."""
    return int(data | (x << C.X_LO) | (y << C.Y_LO))


def run(mod, seeds):
    """seeds: (port, lane, flit). Returns the delivery array (filled in place by csim)."""
    inj = np.zeros((D, L), dtype=np.int32)
    dlv = np.zeros((D, L), dtype=np.int32)
    for p, lane, w in seeds:
        inj[p, lane] = w
    mod(inj, dlv)
    return dlv


def arrived(dlv, port):
    """Payloads delivered on `port`, in arrival order, coordinate bits stripped."""
    return [int(dlv[port, k]) & 0xFFFF for k in range(L) if dlv[port, k]]


def main():
    os.makedirs(PROJECT, exist_ok=True)
    print(f"[csim] generating + building into {PROJECT}", flush=True)
    mod = df.build(C.router_rvn_c, target="systemc", mode="csim", project=PROJECT)
    ok = True

    # T1 -- a flit on each non-local input, all addressed to THIS node: all must eject
    # on LOCAL. Exercises routing, arbitration and the output register at once.
    dlv = run(mod, [(p, 0, pack(0x100 + p, C.ROUTER_X, C.ROUTER_Y))
                    for p in (C.NORTH, C.SOUTH, C.WEST, C.EAST)])
    got = sorted(arrived(dlv, C.LOCAL))
    want = sorted(0x100 + p for p in (C.NORTH, C.SOUTH, C.WEST, C.EAST))
    print(f"\nT1 ejection            : {[hex(x) for x in got]}")
    print("T1", "PASS" if got == want else f"FAIL (wanted {[hex(x) for x in want]})")
    ok &= got == want

    # T2 -- injected locally, each destination must leave by the port XY picks:
    # x<X -> NORTH, x>X -> SOUTH, y<Y -> WEST, y>Y -> EAST.
    cases = [(0x201, C.ROUTER_X - 1, C.ROUTER_Y, C.NORTH),
             (0x202, C.ROUTER_X + 1, C.ROUTER_Y, C.SOUTH),
             (0x203, C.ROUTER_X, C.ROUTER_Y - 1, C.WEST),
             (0x204, C.ROUTER_X, C.ROUTER_Y + 1, C.EAST)]
    dlv = run(mod, [(C.LOCAL, k, pack(d, x, y))
                    for k, (d, x, y, _) in enumerate(cases)])
    print("\nT2 XY directions       :")
    hits = []
    for d, x, y, wnt in cases:
        hit = d in arrived(dlv, wnt)
        hits.append(hit)
        print(f"   dest({x},{y}) -> {NAME[wnt]} : {'ok' if hit else 'MISSING'}")
    print("T2", "PASS" if all(hits) else "FAIL")
    ok &= all(hits)

    # T3 -- two inputs contend for EAST on the same pass. NOTHING may be dropped: the
    # loser's flit is held at its input and retried. This is the property that separates
    # this router from a bufferless one, and the one most at risk under a depth-0
    # handshake, where a transfer needs both ends live in the same cycle.
    dlv = run(mod, [(C.NORTH, 0, pack(0x301, C.ROUTER_X, C.ROUTER_Y + 1)),
                    (C.SOUTH, 0, pack(0x302, C.ROUTER_X, C.ROUTER_Y + 1))])
    east = arrived(dlv, C.EAST)
    lossless = (0x301 in east) and (0x302 in east)
    print(f"\nT3 lossless contention : {[hex(x) for x in east]}")
    print("T3", "PASS (lossless)" if lossless else "FAIL (a flit was dropped)")
    ok &= lossless

    # T4 -- four saturating sources all target EAST. Round-robin must serve every one.
    # The count is reported per source AND in total so a shortfall is diagnosable:
    # fewer than 12 total = loss; 12 total but lopsided = starvation.
    seeds = [(p, lane, pack(0x400 + 0x10 * p + lane, C.ROUTER_X, C.ROUTER_Y + 1))
             for p in (C.NORTH, C.SOUTH, C.WEST, C.LOCAL) for lane in range(3)]
    dlv = run(mod, seeds)
    east = arrived(dlv, C.EAST)
    per = {p: sum(1 for lane in range(3) if (0x400 + 0x10 * p + lane) in east)
           for p in (C.NORTH, C.SOUTH, C.WEST, C.LOCAL)}
    fair = all(v > 0 for v in per.values())
    print("\nT4 fairness            : "
          + "  ".join(f"{NAME[p]}={v}/3" for p, v in per.items())
          + f"   ({len(east)}/12 delivered)")
    print("T4", "PASS (no source starved)" if fair else "FAIL (a source got nothing)")
    ok &= fair

    print("\n=== csim summary:", "ALL PASS" if ok else "FAILURES", "===")
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
