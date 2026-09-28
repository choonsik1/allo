# build_prime.py - build the RUNTIME-PRIME chip (eva_sb_syscredit_rtprime) for a
# 4x4 mmm RTL cosim. Same load_mmm_router vectors as build_val.py, but adds the
# new per-tile input prime_cfg[M,N] (filled with $PRIME, default 6) and partitions
# it. After codegen, inspect kernel.cpp's `void top(` to author tb_replay_prime.cpp.
#   CHIP is fixed. Run: SZ=4 LFORCE=374 PRIME=6 \
#     PYTHONPATH=/home/zsm9/allo /home/zsm9/miniconda3/envs/allo/bin/python build_prime.py
import os, sys, re
os.environ.setdefault("LLVM_BUILD_DIR", "/home/zsm9/allo/mlir/build_xcel")
sys.path.insert(0, "/home/zsm9/allo")
import numpy as np

PRIME_DIR = os.path.dirname(os.path.abspath(__file__))
# reuse the existing 8x8 cosim harness dir for eva_workloads + verification deps
FR   = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs"
VER  = os.path.join(FR, "verification")
sys.path.insert(0, PRIME_DIR)      # the rtprime chip lives here
sys.path.insert(0, FR); sys.path.insert(0, VER)
sys.path.insert(0, "/home/zsm9/pe_core_implementation/Allo/EVA/archive/tests")
PART = "xczu7ev-ffvc1156-2-e"; CLK = "3.33"

CHIP  = "eva_sb_syscredit_rtprime"
SZ    = int(os.environ.get("SZ", "4"))
LF    = int(os.environ.get("LFORCE", "374"))
PRIME = int(os.environ.get("PRIME", "6"))

chip = __import__(CHIP); sys.modules["eva"] = chip
chip.M = chip.N = SZ               # region reads module-level M,N at build time
import eva_workloads as WL
from allo.ir.types import float16

W = np.array([[((i + j) % 4) + 1 for j in range(SZ)] for i in range(SZ)], np.float16)
X = np.array([[(i % 3) + 1 for i in range(SZ)]], np.float16)
B = X.shape[0]
args, _ = WL.load_mmm_router(W, X)
for key in ("ins", "ivs", "outs", "rins", "routs"):
    args[key] = [np.pad(np.asarray(a), ((0, 0), (0, LF - np.asarray(a).shape[1]))) for a in args[key]]
chip.NSTEP = chip.LANELEN = LF
chip.PRIME_TOKENS = PRIME          # sizes STREAM depth headroom / FIFO; runtime loop uses prime_cfg
M, N, L = int(chip.M), int(chip.N), LF
print(f"== build_prime: CHIP={CHIP} {M}x{N} L={L} PRIME(runtime)={PRIME} DEPTH={chip.STREAM_DEPTH} ==")

XW = X.astype(np.float32) @ W.astype(np.float32)
outs = [np.zeros((M, L), np.float16), np.zeros((M, L), np.float16),
        np.zeros((N, L), np.float16), np.zeros((N, L), np.float16)]
for b in range(B):
    for c in range(N):
        outs[3][c, b] = np.float16(XW[b, c])
print(f"  expected out_s (X@W) = {XW.tolist()}")

def c_arr(decl, a, fmt):
    a = np.asarray(a); rows = [", ".join(fmt % v for v in row) for row in a]
    return "static const %s[%d][%d] = {\n  {%s}\n};\n" % (decl, a.shape[0], a.shape[1], "},\n  {".join(rows))
hdr = [f"#define VM {M}\n#define VN {N}\n#define VL {L}\n", f'#define VECNAME "prime_{CHIP}_{M}x{N}"\n',
       f"#define VPRIME {PRIME}\n"]
ins, ivs, rins = args["ins"], args["ivs"], args["rins"]
for i in range(4):
    hdr.append(c_arr(f"unsigned short IN{i}",   np.asarray(ins[i]).view(np.uint16), "0x%04x"))
    hdr.append(c_arr(f"int32_t IV{i}",          ivs[i],                              "%d"))
    hdr.append(c_arr(f"int32_t RIN{i}",         rins[i],                             "%d"))
    hdr.append(c_arr(f"unsigned short EOUT{i}", outs[i].view(np.uint16),             "0x%04x"))
    hdr.append(c_arr(f"int32_t EROUT{i}",       args["routs"][i],                    "%d"))
# prime_cfg[M][N] all = PRIME
hdr.append(c_arr("int32_t PRIMECFG", np.full((M, N), PRIME, np.int32), "%d"))
hfile = os.path.join(PRIME_DIR, f"vectors_prime_{M}x{N}.h"); open(hfile, "w").write("".join(hdr))
print(f"  wrote {os.path.basename(hfile)}")

prj = os.path.join(PRIME_DIR, f"prj_prime_{M}x{N}_L{L}")
kp = os.path.join(prj, "kernel.cpp")
if os.path.exists(kp):
    print(f"  kernel exists: {os.path.relpath(kp, PRIME_DIR)}")
else:
    print(f"  generating kernel...", flush=True)
    s = chip.get_scheduled_eva(float16, pipeline_node=False, partition_rf=False)
    try:
        s.partition("prime_cfg")
        print("  partitioned prime_cfg")
    except Exception as e:
        print("  partition prime_cfg skipped:", str(e)[:120])
    s.build(target="vhls", mode="csyn", project=prj)
    src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
                 r"\1 = {};", open(kp).read())
    src = "#define ALLOW_EMPTY_HLS_STREAM_READS 1\n" + src
    open(kp, "w").write(src)
    print(f"  wrote {os.path.relpath(kp, PRIME_DIR)}  ({sum(1 for _ in open(kp))} lines)")

ini = os.path.join(PRIME_DIR, f"ci_prime_{M}x{N}.ini")
open(ini, "w").write(
    f"part={PART}\n\n[hls]\nflow_target=vivado\nclock={CLK}\nsyn.top=top\nsyn.file={kp}\n"
    f'tb.file={os.path.join(PRIME_DIR, "tb_replay_prime.cpp")}\n'
    f'tb.cflags=-I{PRIME_DIR} -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_prime_{M}x{N}.h"\n'
    f"syn.compile.pipeline_loops=0\n")
print(f"  wrote {os.path.basename(ini)}\nPRJ={prj}\nINI={ini}")
# echo the emitted top() port order so we can author the tb to match
print("\n== emitted top() signature (author tb_replay_prime.cpp to match this order) ==")
m = re.search(r"void top\(([^)]*)\)", open(kp).read())
if m: print("void top(" + m.group(1) + ")")
