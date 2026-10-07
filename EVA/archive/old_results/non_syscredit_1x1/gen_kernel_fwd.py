# Generate the Allo EVA kernel at M=N=1, NSTEP=55 (test_passthrough config)
# for RTL cosim against tb_allo_1x1.cpp. Same overrides eva_tests._dims uses;
# schedule = the honest-baseline one (pipeline_node + partition_rf, no irf).
# Run:  cd allo_1x1_cosim && python gen_kernel.py   (allo conda env)
import os, sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # eva_sb.py = folder root
sys.path.insert(1, "/home/zsm9/pe_core_implementation/Allo/EVA")  # allo deps unchanged
import eva_sb_fwd as e   # the final scoreboard chip (single source, knobs)

e.M, e.N = 1, 1
# OPTION-A deep-prime config (the II=1 RTL needs the slack; see eva_prime_sb
# knob comment): 6 tokens/edge, depth-8 links; NSTEP stretched for the
# credit RTT (~2*TOKENS+2/round, 10 prog pkts at BUF_DEPTH=2/round ≈ 70 cyc)
e.PRIME_TOKENS = 6
e.STREAM_DEPTH = 8
e.NSTEP = 200          # widened window so all B=6 MACs land before the sim ends
e.LANELEN = e.NSTEP

from allo.ir.types import float16
s = e.get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)
P = os.path.join(os.path.dirname(os.path.abspath(__file__)), "allo_prj_fwd")
s.build(target="vhls", mode="csyn", project=P)
print("generated HLS project at", P)

# PATCH (documented Allo backend bug, cosim-blocking): the emitted fp16
# bitcast `union { uint16_t from; half to;}` has a deleted default ctor
# (half is non-trivial) -> g++ 8.3 refuses to compile the cosim C model.
# Aggregate-init `= {}` is semantics-neutral (member overwritten before
# read) and makes it compile. Proper fix belongs in the Allo vhls printer.
import re
kp = os.path.join(P, "kernel.cpp")
src = open(kp).read()
src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
             r"\1 = {};", src)
open(kp, "w").write(src)
print("patched union converters for cosim compilability")

# DEPENDENCE-false on the result rings (scripted version of the 07-06 hand
# edit; NO Allo primitive exists for this — the top_no_dep_pragma arm is the
# control): resq/cmpq are written at issue (ring tail) and read at retire
# (head) SB_DEPTH-1 iterations later, so the loop-carried dep is false.
# This is what buys II=1 on 2025.1. Skip with:  python gen_kernel.py --no-dep-pragma
if "--no-dep-pragma" not in sys.argv:
    src = open(kp).read()
    for ring in ("resq", "cmpq"):
        src = src.replace(
            "#pragma HLS array_partition variable=%s complete dim=1" % ring,
            "#pragma HLS array_partition variable=%s complete dim=1\n"
            "#pragma HLS dependence variable=%s type=inter dependent=false" % (ring, ring))
    # 2026-07-07: after the uint8 narrowing the II=1 blocker moved to a mux
    # temp between the ALU-result store (res) and the retire read (wb) —
    # HLS 200-880 on 'mux_case_*'. Both are scalars rewritten every
    # iteration in source (no true carried use), so inter-false is safe.
    for scal in ("res", "wb"):
        src = src.replace(
            "half %s;" % scal,
            "half %s;\n#pragma HLS dependence variable=%s type=inter dependent=false" % (scal, scal))
    open(kp, "w").write(src)
    print("injected dependence-false pragmas on resq/cmpq/res/wb")

# BIND_OP latency=2 on the fp16 ops (must MATCH eva_sb_fwd.FP_LAT=2). Default HLS
# binds hmul@4 / hadd@5 -> forwarding at FP_LAT=2 would read a not-yet-ready resq.
# Pin to latency=2 (golden EVA fp16 units are ~2-3 cyc) so a forwarded product is
# valid exactly when the MMM ADD needs it. Costs Fmax (2-cyc fp16 = longer path).
src = open(kp).read()
n = 0
src, c = re.subn(r"(half (v\d+) = v\d+ \* v\d+;)",
                 r"\1\n#pragma HLS bind_op variable=\2 op=hmul impl=maxdsp latency=2", src); n += c
src, c = re.subn(r"(half (v\d+) = v\d+ \+ v\d+;)",
                 r"\1\n#pragma HLS bind_op variable=\2 op=hadd impl=fabric latency=2", src); n += c
src, c = re.subn(r"(half (v\d+) = v\d+ - v\d+;)",
                 r"\1\n#pragma HLS bind_op variable=\2 op=hsub impl=fabric latency=2", src); n += c
open(kp, "w").write(src)
print("injected %d bind_op latency=2 pragmas (hmul/hadd/hsub)" % n)
