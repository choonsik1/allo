# demand3: move the demand read to AFTER the real fetch/decode (use actual s1/s2/op), right
# before the operand fetch -> no duplicate hoisted decode, read populates hold_v just-in-time.
import re
D = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime_demand2.py"
O = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/eva_sb_syscredit_rtprime_demand3.py"
src = open(D).read()

# 1) remove the hoisted-decode + read + buffer block (both regions)
blk = re.compile(
    r" *# DEMAND-DRIVEN guarded read:.*?\n"
    r"(?: *#.*\n)?"
    r"(?:.*\n)*?"                       # decode + reads + rxv
    r" *for d in range\(4\):\n"
    r" *if rxvld\[d\] == 1 and hold_cnt\[d\] < 2:\n"
    r" *hold_v\[d, hold_cnt\[d\]\] = rxv\[d\]; hold_cnt\[d\] \+= 1\n")
src, nrm = blk.subn("", src)

# 2) insert the read (using real s1/s2/op) right after the s2 decode
MOVED = (
    "                s2: int32 = (instr >> 12) & 0xF\n"
    "                # DEMAND read (just-in-time, real s1/s2): pull systolic operand(s) into hold_v\n"
    "                binop_d: int32 = 0\n"
    "                if op == OP_ADD or op == OP_SUB or op == OP_MULT or op == OP_GEQ or op == OP_LT: binop_d = 1\n"
    "                need_d: int32[4] = 0\n"
    "                if s1 >= 12: need_d[s1 & 3] = 1\n"
    "                if binop_d == 1 and s2 >= 12: need_d[s2 & 3] = 1\n"
    "                rx_w: SYS_W = 0\n"
    "                if need_d[2] == 1 and hold_cnt[2] < 2: rx_w = sys_e[i, j].get()\n"
    "                rx_e: SYS_W = 0\n"
    "                if need_d[3] == 1 and hold_cnt[3] < 2: rx_e = sys_w[i, j + 1].get()\n"
    "                rx_n: SYS_W = 0\n"
    "                if need_d[0] == 1 and hold_cnt[0] < 2: rx_n = sys_s[i, j].get()\n"
    "                rx_s: SYS_W = 0\n"
    "                if need_d[1] == 1 and hold_cnt[1] < 2: rx_s = sys_n[i + 1, j].get()\n"
    "                rxv: Ty[4] = 0; rxvld: int32[4] = 0\n"
    "                rxv[0] = rx_n[1 : 1 + Ty.bits].bitcast(); rxvld[0] = rx_n[0]\n"
    "                rxv[1] = rx_s[1 : 1 + Ty.bits].bitcast(); rxvld[1] = rx_s[0]\n"
    "                rxv[2] = rx_w[1 : 1 + Ty.bits].bitcast(); rxvld[2] = rx_w[0]\n"
    "                rxv[3] = rx_e[1 : 1 + Ty.bits].bitcast(); rxvld[3] = rx_e[0]\n"
    "                for d in range(4):\n"
    "                    if rxvld[d] == 1 and hold_cnt[d] < 2:\n"
    "                        hold_v[d, hold_cnt[d]] = rxv[d]; hold_cnt[d] += 1\n")
src, nin = re.subn(r" {16}s2: int32 = \(instr >> 12\) & 0xF\n", MOVED, src)

open(O, "w").write(src)
print(f"removed hoisted-read blocks={nrm}  inserted moved-read after s2={nin}")
import py_compile; py_compile.compile(O, doraise=True); print("py_compile OK -> eva_sb_syscredit_rtprime_demand3.py")
