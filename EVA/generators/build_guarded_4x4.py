# Self-contained 4x4 cosim generator for the GUARDED (instruction-gated demand-read) chip.
# Emits: 4x4 vhls kernel + a vectors header (tb_replay_golden_prime format) + ini.
# Purpose: show the RTL-level DEADLOCK (HLS 200-742). Golden values are irrelevant
# (it deadlocks before producing output), so EOUT arrays are left zero.
import os, sys, numpy as np
os.environ["LLVM_BUILD_DIR"] = "/home/zsm9/allo/mlir/build_xcel"
sys.path.insert(0, "/home/zsm9/allo")
PRIME = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime"
TESTS = "/home/zsm9/pe_core_implementation/Allo/EVA/archive/tests"
SC    = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb"
sys.path.insert(0, PRIME); sys.path.insert(0, TESTS); sys.path.insert(0, SC)
import allo.dataflow as df
from allo.ir.types import float16
import eva_sb_syscredit_rtprime_guarded as e
import eva_workloads as WL

K = 4; L = 128
e.M = e.N = K; e.NSTEP = e.LANELEN = L
PRJ = f"{SC}/prj_g4_mmm_4x4_L{L}"
print(f"== codegen GUARDED 4x4 (L={L}) -> {PRJ}/kernel.cpp ==", flush=True)
df.build(e.get_eva_top(float16), target="vhls", mode="csyn", project=PRJ)
# post-codegen: fix Allo bare-union C++ compile bug (cosim C-model only)
import re as _re
_k=f"{PRJ}/kernel.cpp"; _s=open(_k).read()
_s,_n=_re.subn(r"(union \{[^}]*\}\s*_converter_\w+_to_\w+)\s*;", r"\1 = {};", _s)
open(_k,"w").write(_s); print(f"  fixed {_n} union decls")
   # generates kernel.cpp (no csynth)

# 4x4 ones-mmm input (systolic ins + valids + router-injected program), padded to L
W = np.ones((K, K), np.float16); X = np.ones((K, K), np.float16)
args, _ = WL.load_mmm_router(W, X)
def pad(a):
    a = np.asarray(a); n = np.zeros((a.shape[0], L), a.dtype); n[:, :a.shape[1]] = a; return n
ins  = [pad(x) for x in args["ins"]]     # in_w,in_e,in_n,in_s (fp16)
ivs  = [pad(x) for x in args["ivs"]]     # iv_w,e,n,s (int32)
rins = [pad(x) for x in args["rins"]]    # rin_w,e,n,s (int32) — carries the program

def carr(ty, name, a):
    a = np.asarray(a); rows = []
    for r in a:
        rows.append("  {" + ", ".join((f"0x{int(v)&0xffff:04x}" if ty=="unsigned short" else str(int(v))) for v in r) + "}")
    return f"static const {ty} {name}[{a.shape[0]}][{a.shape[1]}] = {{\n" + ",\n".join(rows) + "\n};\n"

def h2u(a):  # fp16 array -> uint16 bit patterns
    return np.asarray(a, np.float16).view(np.uint16)

H = [f"#define VM {K}\n#define VN {K}\n#define VL {L}\n#define VGMAX 4\n#define VOUT_IDX 3\n",
     f'#define VPC 0\n#define VECNAME "g4_mmm_guarded_4x4"\n']
H.append(carr("int32_t", "PRIMECFG", np.full((K, K), 6, np.int32)))
for idx, a in enumerate(ins):  H.append(carr("unsigned short", f"IN{idx}",  h2u(a)))
for idx, a in enumerate(ivs):  H.append(carr("int32_t",        f"IV{idx}",  a))
for idx, a in enumerate(rins): H.append(carr("int32_t",        f"RIN{idx}", a))
# golden outputs unused (deadlocks first) -> zeros
H.append(carr("unsigned short", "EOUT1", np.zeros((K, L), np.int32)))
H.append(carr("unsigned short", "EOUT3", np.zeros((K, L), np.int32)))
open(f"{SC}/vectors_g4_mmm.h", "w").write("".join(H))
print(f"  wrote vectors_g4_mmm.h  (VM=VN={K}, VL={L})", flush=True)

ini = (f"part=xczu7ev-ffvc1156-2-e\n\n[hls]\nflow_target=vivado\nclock=3.33\nsyn.top=top\n"
       f"syn.file={PRJ}/kernel.cpp\nsyn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS\n"
       f"tb.file={SC}/tb_replay_golden_prime.cpp\n"
       f'tb.cflags=-I{SC} -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_g4_mmm.h"\n'
       f"syn.compile.pipeline_loops=0\n")
open(f"{SC}/ci_g4_mmm.ini", "w").write(ini)
print(f"  wrote ci_g4_mmm.ini\n== DONE ==", flush=True)
