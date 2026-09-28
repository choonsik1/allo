# Compose the "credit-free by slack" experiment chip, timestamped, 8x8:
#   base   = eva_sb_syscredit_rtprime_ts.py  (final rtprime + out_cyc timestamps)
#   deepen = link FIFO (STREAM_DEPTH 8->16), router rbuf (BUF_DEPTH 2->4),
#            PE operand hold (hold_v depth 2->HOLD_DEPTH=4, pop-shift generalized)
#   strip  = SYSTOLIC credit plane (scr_) only; router credit (cr_) LEFT INTACT.
# Hypothesis: with credit gone, deep hold_v absorbs the transient producer/consumer
# imbalance that scr_ credit used to throttle -> lossless without the credit plane.
import re, sys
P = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime/"
# argv: "ts" (default) -> timestamped base; "plain" -> non-ts base (for fast Allo-sim golden check)
which = sys.argv[1] if len(sys.argv) > 1 else "ts"
if which == "ts":
    B = P + "eva_sb_syscredit_rtprime_ts.py"
    O = P + "eva_sb_syscredit_rtprime_nocred_deep_ts.py"
else:
    B = P + "eva_sb_syscredit_rtprime.py"
    O = P + "eva_sb_syscredit_rtprime_nocred_deep.py"
print(f"BASE={B.split('/')[-1]}  ->  OUT={O.split('/')[-1]}")
src = open(B).read()

# ---- 1) DEEPEN constants -------------------------------------------------
src, c1 = re.subn(r"(?m)^BUF_DEPTH = 2 ", "BUF_DEPTH = 4 ", src)
src, c2 = re.subn(r"(?m)^STREAM_DEPTH = 8\b", "STREAM_DEPTH = 16", src)
# add HOLD_DEPTH right after the BUF_DEPTH line
src, c3 = re.subn(r"(?m)^(BUF_DEPTH = 4 .*)$", r"\1\nHOLD_DEPTH = 4 # PE operand hold depth (was hardcoded 2)", src)

# ---- 2) DEEPEN PE operand hold (hold_v) ----------------------------------
src, h1 = re.subn(r"hold_v: Ty\[4, 2\]", "hold_v: Ty[4, HOLD_DEPTH]", src)
src, h2 = re.subn(r"hold_cnt\[d\] < 2", "hold_cnt[d] < HOLD_DEPTH", src)
# generalize the 2-deep single-shift pop into a full shift loop (both regions, c1 & c2)
def gen_pop(m):
    v = m.group(1)  # c1 or c2
    ind = " " * 20
    return (f"for sft in range(HOLD_DEPTH - 1): hold_v[{v}, sft] = hold_v[{v}, sft + 1]\n"
            f"{ind}hold_cnt[{v}] -= 1")
src, h3 = re.subn(r"hold_v\[(c[12]), 0\] = hold_v\[\1, 1\]; hold_cnt\[\1\] -= 1", gen_pop, src)

# ---- 3) STRIP systolic credit plane (scr_) -------------------------------
# 3a) remove the collector scr-ONLY credit pre-put priming loop as a unit
#     (its body is a single scr_.put -> line-strip would leave a dangling 'with')
src, pp = re.subn(
    r" *(?:for _pt in range\(pcfg\[0, 0\] - 1\):"
    r"|with allo\.meta_for\(0, PRIME_TOKENS - 1\) as _pt:)\n"
    r" *with allo\.meta_for\(0, [MN]\) as [rc]:\n"
    r" *scr_[nsew]\[[^\]]*\]\.put\(zc\)\n",
    "", src)
print(f"removed collector scr-only pre-put loops: {pp}")
kept, dropped = [], 0
for ln in src.split("\n"):
    s = ln.strip()
    if re.match(r"scr_[nsew]\s*:\s*Stream", s):                                  dropped += 1; continue  # decl
    if re.match(r"scr_[nsew]\[.*\]\.put\(", s):                                  dropped += 1; continue  # put
    if re.search(r"(scred|dcred)\[\w+\]\s*\+=\s*scr_[nsew]\[.*\]\.get\(\)", s):  dropped += 1; continue  # credit get
    kept.append(ln)
src = "\n".join(kept)
# node SEND gate: fire on data ready, no credit
src, g1 = re.subn(r"if txp_v\[(\d)\] == 1 and scred\[\1\] > 0:", r"if txp_v[\1] == 1:", src)
src, g2 = re.subn(r"; scred\[\d\] -= 1", "", src)
# SYSTOLIC driver INJECT gate ONLY (block-form, colon-at-EOL): inject whenever ready.
# The ROUTER injectors' gate is inline ("elif dcred>0: pw=cand; ...") and is LEFT INTACT
# so router credit (cr_) keeps working.
src, g3 = re.subn(r"(?m)elif dcred\[(\w+)\] > 0:$", "else:", src)
src, g4 = re.subn(r"\n[ \t]*dcred\[\w+\] -= 1", "", src)

open(O, "w").write(src)
print(f"consts: BUF={c1} STREAM={c2} HOLD_add={c3}")
print(f"hold_v: decl={h1} cap={h2} pop-loop={h3}")
print(f"strip:  scr_lines={dropped} sendgate={g1} scred_decr={g2} injectgate={g3} dcred_decr={g4}")
print("remaining scr_ refs:", len(re.findall(r"scr_[nsew]", src)),
      " scred/dcred refs:", len(re.findall(r"\b(scred|dcred)\b", src)))
import py_compile; py_compile.compile(O, doraise=True)
print("py_compile OK ->", O.split("/")[-1])
