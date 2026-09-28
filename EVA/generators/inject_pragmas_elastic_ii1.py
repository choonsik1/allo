#!/usr/bin/env python3
# inject_pragmas_elastic_ii1.py IN OUT — schedule the ELASTIC kernel for II=1:
#   partition RF/scoreboard + pipeline II=1 on the node it-loop + bind hmul/hadd latency=2
#   + dependence resq/cmpq inter RAW distance=2 dependent=TRUE (the honest II=1 enabler:
#   FP_LAT=2 guarantees the resq read is >=2 iterations after the write).
import re, sys
src = open(sys.argv[1]).read()
LAT = "2"
PART1D = ["irf","drf","drf_full","hold_cnt","txp_v","txp_d","ig_p","ig_v","oh_p","oh_v",
          "resq","cmpq","sb_v","sb_dst","sb_cmp","sb_rtr","sb_inj","sb_dir","sb_id","sb_rvld","sb_ix","sb_long"]
PART2D = ["hold_v"]
def decl_pat(base):
    return re.compile(r"(?m)^([ \t]*[\w:]+(?:<\d+>)?[ \t]+(%s\d*)\[\d+\](?:\[\d+\])?;.*)$" % base)
n = {"part":0,"pipe":0,"bind":0,"dep":0}
for base in PART1D:
    src,c = decl_pat(base).subn(lambda m: m.group(1)+"\n  #pragma HLS array_partition variable=%s complete dim=1"%m.group(2), src); n["part"]+=c
for base in PART2D:
    src,c = decl_pat(base).subn(lambda m: m.group(1)+"\n  #pragma HLS array_partition variable=%s complete dim=1\n  #pragma HLS array_partition variable=%s complete dim=2"%(m.group(2),m.group(2)), src); n["part"]+=c
# pipeline II=1 + dependence directives ONLY on the node's it loop (in node_ functions)
parts = re.split(r"(?m)^(void [A-Za-z_]\w*\()", src)
outp=[parts[0]]
for k in range(1,len(parts),2):
    sig=parts[k]; body=parts[k+1] if k+1<len(parts) else ""
    if sig.startswith("void node_"):
        def add(m):
            return (m.group(1)
              +"\n  #pragma HLS pipeline II=1"
              +"\n  #pragma HLS dependence variable=resq type=inter direction=RAW distance=2 dependent=true"
              +"\n  #pragma HLS dependence variable=cmpq type=inter direction=RAW distance=2 dependent=true")
        body,c = re.subn(r"(?m)^([ \t]*l_S_it_\d+_it\d*: for \([^)]*\) \{.*)$", add, body, count=1)
        n["pipe"]+=c; n["dep"]+=2*c
    outp += [sig, body]
src="".join(outp)
for pat,op,impl in [(r"(half (v\d+) = v\d+ \* v\d+;)","hmul","maxdsp"),(r"(half (v\d+) = v\d+ \+ v\d+;)","hadd","fabric")]:
    src,c = re.subn(pat, lambda m,o=op,i=impl: m.group(1)+"\n#pragma HLS bind_op variable=%s op=%s impl=%s latency=%s"%(m.group(2),o,i,LAT), src); n["bind"]+=c
open(sys.argv[2],"w").write(src)
print("injected (elastic II=1):", n)
