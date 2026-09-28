# Convert the guarded chip's SYSTOLIC plane to a full elastic handshake (no credit, no bubbles):
#   producers: put a real word only if the neighbor FIFO is NOT full (else hold) -> full()-guard + conditional put
#   consumers: take a word only if the stream is NOT empty -> empty()-guard
# Router plane (rtr_ + cr_ credit) left untouched. Result should be lossless + deadlock-free on acyclic dataflow.
import re, sys
src = open("/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime_guarded.py").read()
n = {}
def rep(a, b):
    global src
    c = src.count(a); src = src.replace(a, b); return c

# --- NODE send-gate: hold (don't send/clear) when the target neighbor FIFO is full ---
n['sg0'] = rep("if txp_v[0] == 1:", "if txp_v[0] == 1 and not sys_n[i, j].full():")
n['sg1'] = rep("if txp_v[1] == 1:", "if txp_v[1] == 1 and not sys_s[i + 1, j].full():")
n['sg2'] = rep("if txp_v[2] == 1:", "if txp_v[2] == 1 and not sys_w[i, j].full():")
n['sg3'] = rep("if txp_v[3] == 1:", "if txp_v[3] == 1 and not sys_e[i, j + 1].full():")
# --- NODE puts (t=0 + in-loop): only put a real word ---
n['pe'] = rep("sys_e[i, j + 1].put(txe_r)", "if txe_r[0] == 1: sys_e[i, j + 1].put(txe_r)")
n['pw'] = rep("sys_w[i, j].put(txw_r)",     "if txw_r[0] == 1: sys_w[i, j].put(txw_r)")
n['ps'] = rep("sys_s[i + 1, j].put(txs_r)", "if txs_r[0] == 1: sys_s[i + 1, j].put(txs_r)")
n['pn'] = rep("sys_n[i, j].put(txn_r)",     "if txn_r[0] == 1: sys_n[i, j].put(txn_r)")
# --- NODE reads (demand-driven): also require the stream to be non-empty ---
for d, st in [(2, "sys_e[i, j]"), (3, "sys_w[i, j + 1]"), (0, "sys_s[i, j]"), (1, "sys_n[i + 1, j]")]:
    rxn = {2:"rx_w",3:"rx_e",0:"rx_n",1:"rx_s"}[d]
    a = f"if need_d[{d}] == 1 and hold_cnt[{d}] < 2: {rxn} = {st}.get()"
    b = f"if need_d[{d}] == 1 and hold_cnt[{d}] < 2 and not {st}.empty(): {rxn} = {st}.get()"
    n[f'rd{d}'] = rep(a, b)
# --- DRIVER inject: gate the whole inject on 'neighbor not full', put only real ---
def drv(m):
    cond, body, st = m.group(1), m.group(2), m.group(3)
    return cond[:-1] + f" and not {st}.full():" + body + f"if w[0] == 1: {st}.put(w)"
src, n['drv'] = re.subn(r"(if sp\[\w\] < LANELEN and t >= sp\[\w\]:)(.*?)(sys_\w+\[[^\]]+\])\.put\(w\)", drv, src, flags=re.DOTALL)
# --- COLLECTOR drain: take a word only if the stream is non-empty ---
src, n['col'] = re.subn(r"(\n([ \t]+))w: SYS_W = (sys_\w+\[[^\]]+\])\.get\(\)",
                        r"\1w: SYS_W = 0\1if not \3.empty(): w = \3.get()", src)

out = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime_elastic.py"
open(out, "w").write(src)
print("replacements:", n)
import py_compile; py_compile.compile(out, doraise=True); print("py_compile OK ->", out.split('/')[-1])
