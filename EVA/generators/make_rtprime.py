#!/usr/bin/env python3
# Transform eva_sb_syscredit_rtprime.py IN PLACE: convert the compile-time
# PRIME_TOKENS meta_for priming into a RUNTIME loop bounded by a new per-tile
# top-level input `prime_cfg: int32[M, N]`. MAIN region only (lines < `return top`).
import re, sys
F = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime.py"
src = open(F).read()
lines = src.split("\n")

# locate main region end (first "    return top")
main_end = next(i for i, l in enumerate(lines) if l == "    return top")
head = "\n".join(lines[:main_end + 1])       # main region (incl. return top)
tail = "\n".join(lines[main_end + 1:])        # extended region + get_scheduled + __main__  (UNTOUCHED)

n = {"sig": 0, "node_dec": 0, "node_def": 0, "drv_dec": 0, "drv_def": 0, "node_prime": 0, "drv_prime": 0}

# 1) top() signature: add prime_cfg as last arg (before the closing "    ):")
head, c = re.subn(r"(        iv_n: int32\[N, LANELEN\], iv_s: int32\[N, LANELEN\],\n)(    \):)",
                  r"\1        prime_cfg: int32[M, N],\n\2", head, count=1); n["sig"] = c

# 2) node decorator + def  (mapping=[M, N])
head, c = re.subn(r"@df\.kernel\(mapping=\[M, N\]\)\n(\s*)def node\(\):",
                  r"@df.kernel(mapping=[M, N], args=[prime_cfg])\n\1def node(pcfg: int32[M, N]):",
                  head, count=1); n["node_dec"] = n["node_def"] = c

# 3) driver decorators: append prime_cfg to the args=[...] list
head, c = re.subn(r"(@df\.kernel\(mapping=\[1\], args=\[[^\]]*)\]\)",
                  r"\1, prime_cfg])", head); n["drv_dec"] = c

# 4) driver defs: append pcfg param before "):"  (defs right after a mapping=[1] decorator)
#    match "def NAME(<params>):" where NAME is a driver (drv_/col_/rin_/rout_/...); all main
#    mapping=[1] defs. We append ", pcfg: int32[M, N]" before the closing "):".
def add_param(m):
    return m.group(0)[:-2] + ", pcfg: int32[M, N]):"
head, c = re.subn(r"        def (?!node)([a-z0-9_]+)\(([^)]*)\):", add_param, head); n["drv_def"] = c

# 5) prime loops: first PRIME meta_for = node -> pcfg[i, j]; rest = drivers -> pcfg[0, 0]
PRIME = "with allo.meta_for(0, PRIME_TOKENS - 1) as _pt:"
# node (first occurrence)
head = head.replace(PRIME, "for _pt in range(pcfg[i, j] - 1):", 1); n["node_prime"] = 1
# drivers (all remaining)
cnt = head.count(PRIME)
head = head.replace(PRIME, "for _pt in range(pcfg[0, 0] - 1):"); n["drv_prime"] = cnt

open(F, "w").write(head + "\n" + tail)
print("transform counts:", n)
assert n["sig"] == 1, "top() signature not patched"
assert n["node_dec"] == 1, "node decorator/def not patched"
print("OK")
