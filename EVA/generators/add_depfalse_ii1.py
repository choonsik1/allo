# Convert an II=2 inject_pragmas_ii2 kernel -> II=1 by adding dependence=false on the
# resq/cmpq result rings + res/wb scalars (all 64 node-suffixed instances). SAFE only with
# FWD=0 (wbfwd chip). Loud-asserts each target fired so it can't silently stay II=2.
import sys, re
src = open(sys.argv[1]).read(); c = {}
for ring in ("resq", "cmpq"):
    src, n = re.subn(r"(#pragma HLS array_partition variable=(%s\d*) complete dim=1)" % ring,
                     r"\1\n  #pragma HLS dependence variable=\2 type=inter dependent=false", src); c[ring] = n
for scal in ("res", "wb"):
    src, n = re.subn(r"(half (%s\d*);)" % scal,
                     r"\1\n#pragma HLS dependence variable=\2 type=inter dependent=false", src); c[scal] = n
open(sys.argv[2], "w").write(src)
tot = src.count("dependent=false")
print(f"add_depfalse_ii1: resq={c['resq']} cmpq={c['cmpq']} res={c['res']} wb={c['wb']}  total dependent=false={tot}")
assert c["resq"] > 0 and c["cmpq"] > 0, "RING dep-false MISSED -> would silently stay II=2: %s" % c
assert c["res"] > 0 and c["wb"] > 0, "SCALAR dep-false missed: %s" % c
