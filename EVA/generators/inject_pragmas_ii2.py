#!/usr/bin/env python3
# inject_pragmas_ii2.py IN OUT [BINDLAT]
# Turn a NOSCHED Allo EVA kernel into the SCHEDULED **II=2 (correct)** form by pasting the
# pragmas Allo's scheduler adds — EXCEPT dependence=false. So: pipeline II=1 (request) +
# array_partition + bind_op, but the resq/cmpq recurrence is left HONORED -> HLS falls back
# to II=2 (with a 200-880 warning) and is CORRECT. One regex pass hits all 64 identical nodes
# (per-node arrays carry a numeric suffix: resq, resq1, ... -> matched by \d*).
import re, sys
src = open(sys.argv[1]).read()
LAT = sys.argv[3] if len(sys.argv) > 3 else "2"
PART1D = ["irf","drf","drf_full","hold_cnt","rbcnt","rcred","scred","txp_v","txp_d","txp_r","sc_r",
          "resq","cmpq","sb_v","sb_dst","sb_cmp","sb_rtr","sb_inj","sb_dir","sb_id","sb_rvld","sb_ix","sb_long"]
PART2D = ["hold_v","rbuf"]
def decl_pat(base):   # trailing .* absorbs the "// Lxxx" comment after the ';'
    return re.compile(r"(?m)^([ \t]*[\w:]+(?:<\d+>)?[ \t]+(%s\d*)\[\d+\](?:\[\d+\])?;.*)$" % base)
n = {"part":0,"pipe":0,"bind":0}
for base in PART1D:
    src, c = decl_pat(base).subn(lambda m: m.group(1)+"\n  #pragma HLS array_partition variable=%s complete dim=1"%m.group(2), src); n["part"]+=c
for base in PART2D:
    src, c = decl_pat(base).subn(lambda m: m.group(1)+"\n  #pragma HLS array_partition variable=%s complete dim=1\n  #pragma HLS array_partition variable=%s complete dim=2"%(m.group(2),m.group(2)), src); n["part"]+=c
# pipeline II=1 ONLY on the node main loop (not driver/collector loops).
# split into functions; inject only inside node_* functions, only the FIRST l_S_t loop.
parts = re.split(r"(?m)^(void [A-Za-z_]\w*\()", src)
outp = [parts[0]]
for k in range(1, len(parts), 2):
    sig = parts[k]; body = parts[k+1] if k+1 < len(parts) else ""
    if sig.startswith("void node_"):
        body, c = re.subn(r"(?m)^([ \t]*l_S_t_\d+_t\d*: for \([^)]*\) \{.*)$",
                          lambda m: m.group(1)+"\n  #pragma HLS pipeline II=1", body, count=1); n["pipe"]+=c
    outp += [sig, body]
src = "".join(outp)
# bind_op on fp16 ops
for pat,op,impl in [(r"(half (v\d+) = v\d+ \* v\d+;)","hmul","maxdsp"),(r"(half (v\d+) = v\d+ \+ v\d+;)","hadd","fabric"),(r"(half (v\d+) = v\d+ - v\d+;)","hsub","fabric")]:
    src, c = re.subn(pat, lambda m,o=op,i=impl: m.group(1)+"\n#pragma HLS bind_op variable=%s op=%s impl=%s latency=%s"%(m.group(2),o,i,LAT), src); n["bind"]+=c
open(sys.argv[2],"w").write(src)
print("injected (II=2, NO dep-false):", n)
