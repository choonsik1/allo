# Generalized 4x4 cosim generator for any STANDARD-signature EVA chip (prime_cfg, no n_out).
# CHIP env selects the module. Emits 4x4 vhls kernel (+ union-fix) + vectors + ini.
#   CHIP=eva_sb_syscredit_rtprime_guarded python build_var_4x4.py
import os, sys, importlib, re, numpy as np
os.environ["LLVM_BUILD_DIR"] = "/home/zsm9/allo_sup/mlir/build_xcel"
sys.path.insert(0, "/home/zsm9/allo_sup")
PRIME = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime"
TESTS = "/home/zsm9/pe_core_implementation/Allo/EVA/archive/tests"
SC    = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb"
sys.path.insert(0, PRIME); sys.path.insert(0, TESTS); sys.path.insert(0, SC)
import allo.dataflow as df
from allo.ir.types import float16
import eva_workloads as WL

CHIP = os.environ.get("CHIP", "eva_sb_syscredit_rtprime_guarded")
TAG  = os.environ.get("TAG", CHIP.replace("eva_sb_syscredit_rtprime", "v").replace("__", "_"))
K = 4; L = 128
e = importlib.import_module(CHIP)
e.M = e.N = K; e.NSTEP = e.LANELEN = L
PRJ = f"{SC}/prj_{TAG}_4x4_L{L}"
print(f"== codegen {CHIP} 4x4 (L={L}) -> {PRJ}/kernel.cpp ==", flush=True)
df.build(e.get_eva_top(float16), target="vhls", mode="csyn", project=PRJ)
# union-fix (upstream Allo bare-union cosim bug)
_k = f"{PRJ}/kernel.cpp"; _s = open(_k).read()
_s, _n = re.subn(r"(union \{[^}]*\}\s*_converter_\w+_to_\w+)\s*;", r"\1 = {};", _s)
open(_k, "w").write(_s); print(f"  fixed {_n} union decls", flush=True)

W = np.ones((K, K), np.float16); X = np.ones((K, K), np.float16)
args, _ = WL.load_mmm_router(W, X)
pad = lambda a: (lambda n: (n.__setitem__((slice(None), slice(0, np.asarray(a).shape[1])), a), n)[1])(
    np.zeros((np.asarray(a).shape[0], L), np.asarray(a).dtype))
ins  = [pad(x) for x in args["ins"]]
ivs  = [pad(x) for x in args["ivs"]]
rins = [pad(x) for x in args["rins"]]

def carr(ty, name, a):
    a = np.asarray(a)
    rows = ["  {" + ", ".join((f"0x{int(v)&0xffff:04x}" if ty=="unsigned short" else str(int(v))) for v in r) + "}" for r in a]
    return f"static const {ty} {name}[{a.shape[0]}][{a.shape[1]}] = {{\n" + ",\n".join(rows) + "\n};\n"
h2u = lambda a: np.asarray(a, np.float16).view(np.uint16)

H = [f"#define VM {K}\n#define VN {K}\n#define VL {L}\n#define VGMAX 4\n#define VOUT_IDX 3\n",
     f'#define VPC 0\n#define VECNAME "{TAG}_mmm_4x4"\n', carr("int32_t","PRIMECFG",np.full((K,K),6,np.int32))]
for i,a in enumerate(ins):  H.append(carr("unsigned short", f"IN{i}",  h2u(a)))
for i,a in enumerate(ivs):  H.append(carr("int32_t",        f"IV{i}",  a))
for i,a in enumerate(rins): H.append(carr("int32_t",        f"RIN{i}", a))
H.append(carr("unsigned short","EOUT1",np.zeros((K,L),np.int32)))
H.append(carr("unsigned short","EOUT3",np.zeros((K,L),np.int32)))
open(f"{SC}/vectors_{TAG}_mmm.h","w").write("".join(H))
ini = (f"part=xczu7ev-ffvc1156-2-e\n\n[hls]\nflow_target=vivado\nclock=3.33\nsyn.top=top\n"
       f"syn.file={PRJ}/kernel.cpp\nsyn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS\n"
       f"tb.file={SC}/tb_replay_golden_prime.cpp\n"
       f'tb.cflags=-I{SC} -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_{TAG}_mmm.h"\n'
       f"syn.compile.pipeline_loops=0\n")
open(f"{SC}/ci_{TAG}_mmm.ini","w").write(ini)
print(f"  wrote vectors_{TAG}_mmm.h + ci_{TAG}_mmm.ini\n== DONE {CHIP} ==", flush=True)
