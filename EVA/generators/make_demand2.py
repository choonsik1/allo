# _demand2: add n_in[lane] bound to the systolic DRIVERS (mirror of n_out on collectors).
# Each driver injects at most n_in[lane] REAL words then idles -> matches the node's on-demand
# consumption, so the all-1s accumulator-seed mask no longer over-supplies.
import re
D = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime_demand.py"
O = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime_demand2.py"
src = open(D).read(); c = {}

# 1) top() add n_in inputs (both regions)
src, c['sig'] = re.subn(r"(        n_out_w: int32\[M\], n_out_e: int32\[M\], n_out_n: int32\[N\], n_out_s: int32\[N\],\n)",
    r"\1        n_in_w: int32[M], n_in_e: int32[M], n_in_n: int32[N], n_in_s: int32[N],\n", src)

# 2) driver kernel args (+ n_in)
for side, dim, inp, iv in [("w","M","in_w","iv_w"),("e","M","in_e","iv_e"),("n","N","in_n","iv_n"),("s","N","in_s","iv_s")]:
    a = f"@df.kernel(mapping=[1], args=[{inp}, {iv}, prime_cfg])\n        def drv_{side}(din_{side}: Ty[{dim}, LANELEN], vd_{side}: int32[{dim}, LANELEN], pcfg: int32[M, N]):"
    b = f"@df.kernel(mapping=[1], args=[{inp}, {iv}, prime_cfg, n_in_{side}])\n        def drv_{side}(din_{side}: Ty[{dim}, LANELEN], vd_{side}: int32[{dim}, LANELEN], pcfg: int32[M, N], nin: int32[{dim}]):"
    c[f'da{side}'] = src.count(a); src = src.replace(a, b)

# 3) declare inj counter next to each driver sp counter
src, c['inj'] = re.subn(r"(\n([ \t]+))sp: int32\[(\w)\] = 0", r"\1sp: int32[\3] = 0\1inj: int32[\3] = 0", src)
# 4) gate the inject on 'still under budget'
src, c['gate'] = re.subn(r"if sp\[(\w)\] < LANELEN and t >= sp\[\1\]:", r"if sp[\1] < LANELEN and t >= sp[\1] and inj[\1] < nin[\1]:", src)
# 5) count each REAL inject (after the din bitcast + sp increment)
src, c['cnt'] = re.subn(r"(w\[1 : 1 \+ Ty\.bits\] = din_\w+\[(\w), sp\[\2\]\]\.bitcast\(\)\n([ \t]+)sp\[\2\] \+= 1)",
                        r"\1\n\3inj[\2] += 1", src)

open(O, "w").write(src)
print("counts:", c)
import py_compile; py_compile.compile(O, doraise=True); print("py_compile OK -> eva_sb_syscredit_rtprime_demand2.py")
