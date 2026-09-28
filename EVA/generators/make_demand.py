# _demand chip: PURE BLOCKING elastic, no full()/empty().
#   node read  : demand-driven blocking (if instr needs dir d: get)   [kept from guarded]
#   node/driver: put only REAL words (blocking)                        [real-only send]
#   collector  : blocking, bounded by n_out[lane] (new input)          [terminates, no empty]
import re
G = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime_guarded.py"
O = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime_demand.py"
src = open(G).read(); c = {}

# 1) NODE send real-only (t=0 + in-loop, both regions)
for tx, st in [("txe_r","sys_e[i, j + 1]"),("txw_r","sys_w[i, j]"),("txs_r","sys_s[i + 1, j]"),("txn_r","sys_n[i, j]")]:
    a = f"{st}.put({tx})"; b = f"if {tx}[0] == 1: {st}.put({tx})"
    c[tx] = src.count(a); src = src.replace(a, b)

# 2) DRIVER put real-only (only sys puts of 'w'; node puts use txX_r)
src, c['drv'] = re.subn(r"(sys_\w+\[[^\]]+\])\.put\(w\)", r"if w[0] == 1: \1.put(w)", src)

# 3) top() add per-lane n_out inputs (both region signatures)
src, c['sig'] = re.subn(r"(        prime_cfg: int32\[M, N\],\n)",
    r"\1        n_out_w: int32[M], n_out_e: int32[M], n_out_n: int32[N], n_out_s: int32[N],\n", src)

# 4) COLLECTOR kernel args (+nout) — both regions
for side, dim in [("w","M"),("e","M"),("n","N"),("s","N")]:
    a = f"@df.kernel(mapping=[1], args=[out_{side}, prime_cfg])\n        def col_{side}(dout_{side}: Ty[{dim}, LANELEN], pcfg: int32[M, N]):"
    b = f"@df.kernel(mapping=[1], args=[out_{side}, prime_cfg, n_out_{side}])\n        def col_{side}(dout_{side}: Ty[{dim}, LANELEN], pcfg: int32[M, N], nout: int32[{dim}]):"
    c[f'ca{side}'] = src.count(a); src = src.replace(a, b)

# 5) COLLECTOR body: gate the blocking get by k<nout (all incoming words are real)
def cb(m):
    ind, st, idx, dout = m.group(1), m.group(2), m.group(3), m.group(4)
    return (f"{ind}if k[{idx}] < nout[{idx}]:"
            f"{ind}    w: SYS_W = {st}.get()"
            f"{ind}    {dout}[{idx}, k[{idx}]] = w[1 : 1 + Ty.bits].bitcast()"
            f"{ind}    k[{idx}] += 1")
pat = (r"(\n[ \t]+)w: SYS_W = (sys_\w+\[[^\]]+\])\.get\(\)"
       r"\1cret\[(\w)\] = 0"
       r"\1if w\[0\] == 1:"
       r"\1    cret\[\3\] = 1"
       r"\1    if k\[\3\] < LANELEN:"
       r"\1        (dout_\w+)\[\3, k\[\3\]\] = w\[1 : 1 \+ Ty\.bits\]\.bitcast\(\)"
       r"\1        k\[\3\] \+= 1")
src, c['cbody'] = re.subn(pat, cb, src)

open(O, "w").write(src)
print("counts:", c)
import py_compile; py_compile.compile(O, doraise=True); print("py_compile OK -> eva_sb_syscredit_rtprime_demand.py")
