# Generate the SYSCREDIT forwarding chip at M=N=1 for csynth + P&R (mirror of
# scoreboard_allo_eva_final/variant_ii1/gen_kernel_fwd.py, but importing the
# credit chip eva_sb_syscredit_fwd and keeping its credit priming PRIME=6/D=8).
import os, sys, re
sys.path.insert(0, "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs")
sys.path.insert(1, "/home/zsm9/pe_core_implementation/Allo/EVA")
import eva_sb_syscredit_fwd as e

e.M, e.N = 1, 1
e.PRIME_TOKENS = 6        # credit priming (deep-prime, deadlock-safe)
e.STREAM_DEPTH = 8
e.NSTEP = 200
e.LANELEN = e.NSTEP

from allo.ir.types import float16
s = e.get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)   # base region (no div/sqrt)
P = os.path.join(os.path.dirname(os.path.abspath(__file__)), "allo_prj_syscredit_fwd")
s.build(target="vhls", mode="csyn", project=P)
print("generated HLS project at", P)

kp = os.path.join(P, "kernel.cpp")
# (1) union-converter patch (cosim/g++ compilability)
src = open(kp).read()
src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
             r"\1 = {};", src)
open(kp, "w").write(src)

# (2) dep-false on result rings + res/wb scalars (buys II=1)
src = open(kp).read()
for ring in ("resq", "cmpq"):
    src = src.replace(
        "#pragma HLS array_partition variable=%s complete dim=1" % ring,
        "#pragma HLS array_partition variable=%s complete dim=1\n"
        "#pragma HLS dependence variable=%s type=inter dependent=false" % (ring, ring))
for scal in ("res", "wb"):
    src = src.replace(
        "half %s;" % scal,
        "half %s;\n#pragma HLS dependence variable=%s type=inter dependent=false" % (scal, scal))
open(kp, "w").write(src)

# (3) bind_op latency=2 on fp16 ops (match FP_LAT so forwarded product is ready)
src = open(kp).read()
n = 0
src, c = re.subn(r"(half (v\d+) = v\d+ \* v\d+;)",
                 r"\1\n#pragma HLS bind_op variable=\2 op=hmul impl=maxdsp latency=2", src); n += c
src, c = re.subn(r"(half (v\d+) = v\d+ \+ v\d+;)",
                 r"\1\n#pragma HLS bind_op variable=\2 op=hadd impl=fabric latency=2", src); n += c
src, c = re.subn(r"(half (v\d+) = v\d+ - v\d+;)",
                 r"\1\n#pragma HLS bind_op variable=\2 op=hsub impl=fabric latency=2", src); n += c
open(kp, "w").write(src)
print(f"patched: union + dep-false(resq/cmpq/res/wb) + {n} bind_op latency=2")

# write csynth+impl ini (no TB needed for csynth/P&R)
ini = os.path.join(os.path.dirname(os.path.abspath(__file__)), "ci_1x1_syscredit_fwd.ini")
open(ini, "w").write(
    "part=xczu7ev-ffvc1156-2-e\n\n[hls]\nclock=3.333\nflow_target=vivado\n"
    "syn.top=top\nsyn.file=%s\nsyn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS\n"
    "syn.compile.pipeline_loops=0\n" % kp)
print("wrote", ini)
