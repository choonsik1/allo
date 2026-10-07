# =============================================================================
# build_val.py - VALIDATE the NB tb/vector flow against a KNOWN-GOOD chip.
# Builds any CHIP (default eva_sb = always-fire scoreboard that passed the old
# 2x2 cosim) through the SAME load_mmm_router vectors + tb_replay_nb.cpp used by
# the NB flow. If the good chip prints out_s=[5,8] -> the tb is correct and the
# NB chip is genuinely broken. If it ALSO prints zero -> the tb/port-map is the
# bug.  Run:  CHIP=eva_sb SZ=2 LFORCE=120 /home/zsm9/miniconda3/envs/allo/bin/python build_val.py
# =============================================================================
import os, sys
os.environ.setdefault("LLVM_BUILD_DIR", "/home/zsm9/allo/mlir/build_xcel")
sys.path.insert(0, "/home/zsm9/allo")
import re
import numpy as np

HERE  = os.path.dirname(os.path.abspath(__file__))
COSIM = os.path.dirname(HERE); FR = os.path.dirname(COSIM)
VER   = os.path.join(FR, "verification")
sys.path.insert(0, FR); sys.path.insert(0, VER)
PART = "xczu7ev-ffvc1156-2-e"; CLK = "3.33"

CHIP = os.environ.get("CHIP", "eva_sb")
SZ   = int(os.environ.get("SZ", "2"))
LF   = int(os.environ.get("LFORCE", "120"))

chip = __import__(CHIP)
sys.modules["eva"] = chip
import eva_workloads as WL
from allo.ir.types import float16
import allo.dataflow as df

W = np.array([[((i + j) % 4) + 1 for j in range(SZ)] for i in range(SZ)], np.float16)
X = np.array([[(i % 3) + 1 for i in range(SZ)]], np.float16)
B = X.shape[0]
args, _ = WL.load_mmm_router(W, X)
for key in ("ins", "ivs", "outs", "rins", "routs"):
    args[key] = [np.pad(np.asarray(a), ((0, 0), (0, LF - np.asarray(a).shape[1]))) for a in args[key]]
chip.NSTEP = chip.LANELEN = LF
M, N, L = int(chip.M), int(chip.N), LF
print(f"== build_val: CHIP={CHIP} {M}x{N} L={L} ==")

XW = X.astype(np.float32) @ W.astype(np.float32)
outs = [np.zeros((M, L), np.float16), np.zeros((M, L), np.float16),
        np.zeros((N, L), np.float16), np.zeros((N, L), np.float16)]
for b in range(B):
    for c in range(N):
        outs[3][c, b] = np.float16(XW[b, c])
print(f"  expected out_s (X@W) = {XW.tolist()}")

def c_arr(decl, a, fmt):
    a = np.asarray(a)
    rows = [", ".join(fmt % v for v in row) for row in a]
    return "static const %s[%d][%d] = {\n  {%s}\n};\n" % (decl, a.shape[0], a.shape[1], "},\n  {".join(rows))
hdr = [f"#define VM {M}\n#define VN {N}\n#define VL {L}\n", f'#define VECNAME "val_{CHIP}_{M}x{N}"\n']
ins, ivs, rins = args["ins"], args["ivs"], args["rins"]
for i in range(4):
    hdr.append(c_arr(f"unsigned short IN{i}",   np.asarray(ins[i]).view(np.uint16), "0x%04x"))
    hdr.append(c_arr(f"int32_t IV{i}",          ivs[i],                              "%d"))
    hdr.append(c_arr(f"int32_t RIN{i}",         rins[i],                             "%d"))
    hdr.append(c_arr(f"unsigned short EOUT{i}", outs[i].view(np.uint16),             "0x%04x"))
    hdr.append(c_arr(f"int32_t EROUT{i}",       args["routs"][i],                    "%d"))
hfile = os.path.join(HERE, f"vectors_val_{CHIP}_{M}x{N}.h"); open(hfile, "w").write("".join(hdr))
print(f"  wrote {os.path.basename(hfile)}")

prj = os.path.join(HERE, f"prj_val_{CHIP}_{M}x{N}_L{L}")
kp = os.path.join(prj, "kernel.cpp")
if os.path.exists(kp):
    print(f"  kernel exists: {os.path.relpath(kp, HERE)}")
else:
    print(f"  generating kernel...", flush=True)
    s = chip.get_scheduled_eva(float16, pipeline_node=False, partition_rf=False)
    s.build(target="vhls", mode="csyn", project=prj)
    src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
                 r"\1 = {};", open(kp).read())
    src = "#define ALLOW_EMPTY_HLS_STREAM_READS 1\n" + src
    open(kp, "w").write(src)
    print(f"  wrote {os.path.relpath(kp, HERE)}  ({sum(1 for _ in open(kp))} lines)")

ini = os.path.join(HERE, f"ci_val_{CHIP}_{M}x{N}.ini")
open(ini, "w").write(
    f"part={PART}\n\n[hls]\nflow_target=vivado\nclock={CLK}\nsyn.top=top\nsyn.file={kp}\n"
    f'tb.file={os.path.join(HERE, "tb_replay_nb.cpp")}\n'
    f'tb.cflags=-I{HERE} -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_val_{CHIP}_{M}x{N}.h"\n'
    f"syn.compile.pipeline_loops=0\n")
print(f"  wrote {os.path.basename(ini)}")
print(f"""
== COSIM (conda deactivate) ==
  cd {prj}
  v++ -c --mode hls --config {ini} --work_dir /tmp/val_{CHIP}
  vitis-run --mode hls --cosim --config {ini} --work_dir /tmp/val_{CHIP}
  # out_s=[5,8] => tb VALID (NB chip is the bug).  zero => tb/port-map is the bug.
""")
