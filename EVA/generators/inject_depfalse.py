#!/usr/bin/env python3
# inject_depfalse.py SRC DST  — turn an Option-1 scheduled kernel (pipeline_node=True,
# partition_rf=True, dep HONORED -> II~=fp_latency) into an Option-2 II=1 kernel by
# asserting the inter-iteration false-dependence on resq/cmpq/res/wb (Allo has no
# primitive; ported verbatim from variant_ii1/gen_kernel_fwd.py). This is exactly the
# assertion whose SAFETY CONDITION is FP_LAT >= fp-op latency (the whole point of the
# FP_LAT-hazard experiment). Reuses the SLOW codegen — pure text transform.
import sys
src = open(sys.argv[1]).read()
n = 0
for ring in ("resq", "cmpq"):
    tag = "#pragma HLS array_partition variable=%s complete dim=1" % ring
    if tag in src:
        src = src.replace(tag, tag + "\n#pragma HLS dependence variable=%s type=inter dependent=false" % ring); n += 1
for scal in ("res", "wb"):
    tag = "half %s;" % scal
    if tag in src:
        src = src.replace(tag, tag + "\n#pragma HLS dependence variable=%s type=inter dependent=false" % scal); n += 1
open(sys.argv[2], "w").write(src)
print(f"injected {n} dependence-false site(s) -> {sys.argv[2]}")
