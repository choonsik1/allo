# Strip the SYSTOLIC credit plane (scr_) from eva_sb_syscredit_rtprime_no_cred.py:
#  - remove scr_ Stream decls, all scr_.put()/.get(), and scred/dcred credit accumulation
#  - node SEND gate:   `if txp_v[d]==1 and scred[d]>0:` -> `if txp_v[d]==1:`  (send now / bubble)
#  - driver INJECT gate: `elif dcred[r]>0:` -> `else:`  (inject whenever data ready / bubble)
#  Router credit (cr_) is LEFT INTACT for now. Backpressure now comes from the bounded sys_ FIFOs.
import re
fn = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime_no_cred.py"
lines = open(fn).read().split("\n")
out, dropped = [], 0
for ln in lines:
    s = ln.strip()
    if re.match(r"scr_[nsew]\s*:\s*Stream", s):                                dropped+=1; continue  # decl
    if re.match(r"scr_[nsew]\[.*\]\.put\(", s):                                 dropped+=1; continue  # put
    if re.search(r"(scred|dcred)\[\w+\]\s*\+=\s*scr_[nsew]\[.*\]\.get\(\)", s):  dropped+=1; continue  # credit get
    out.append(ln)
src = "\n".join(out)
# semantic gates
src, n1 = re.subn(r"if txp_v\[(\d)\] == 1 and scred\[\1\] > 0:", r"if txp_v[\1] == 1:", src)
src, n2 = re.subn(r"\s*;\s*scred\[\d\] -= 1", "", src)
src, n3 = re.subn(r"elif dcred\[(\w+)\] > 0:", "else:", src)
src, n4 = re.subn(r"\n[ \t]*dcred\[\w+\] -= 1", "", src)
# empty-block fixer: any ':' line whose body became empty -> insert 'pass'
L = src.split("\n"); fixed = []
for i, ln in enumerate(L):
    fixed.append(ln)
    if ln.rstrip().endswith(":") and not ln.strip().startswith("#"):
        ind = len(ln) - len(ln.lstrip()); j = i + 1
        while j < len(L) and L[j].strip() == "": j += 1
        if j >= len(L) or (len(L[j]) - len(L[j].lstrip())) <= ind:
            fixed.append(" " * (ind + 4) + "pass")
src = "\n".join(fixed)
open(fn, "w").write(src)
print(f"dropped scr_ lines={dropped}  sendgate={n1} scred-decr={n2} injectgate={n3} dcred-decr={n4}")
print("remaining scr_ refs:", len(re.findall(r"scr_[nsew]", src)), " scred/dcred refs:", len(re.findall(r"\b(scred|dcred)\b", src)))
import py_compile; py_compile.compile(fn, doraise=True); print("py_compile OK")
