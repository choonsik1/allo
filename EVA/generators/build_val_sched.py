# =============================================================================
# build_val_sched.py - SCHEDULED (pipelined) build of a forwarding+credits chip
# through the same load_mmm_router vectors + tb_replay_nb.cpp as build_val.py.
# The NOSCHED build proves CORRECTNESS; this one measures the real II/throughput
# of the pipelined node loop. Applies the II=1 forwarding recipe from
# variant_ii1/gen_kernel_fwd.py: dep-false on resq/cmpq/res/wb + bind_op
# latency=2 on the fp16 ops (must match FP_LAT).
#   Run:  CHIP=eva_sb_syscredit_fwd SZ=4 LFORCE=374 \
#         /home/zsm9/miniconda3/envs/allo/bin/python build_val_sched.py
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

CHIP = os.environ.get("CHIP", "eva_sb_syscredit_fwd")
SZ   = int(os.environ.get("SZ", "4"))
LF   = int(os.environ.get("LFORCE", "374"))

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
print(f"== build_val_sched: CHIP={CHIP} {M}x{N} L={L} SCHEDULED ==")

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
# reuse the SAME vectors header name build_val.py uses (identical vectors)
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

prj = os.path.join(HERE, f"prj_val_{CHIP}_{M}x{N}_L{L}_sched")
kp = os.path.join(prj, "kernel.cpp")
if os.path.exists(kp):
    print(f"  kernel exists: {os.path.relpath(kp, HERE)}")
else:
    print(f"  generating SCHEDULED kernel (pipeline_node=True, partition_rf=True)...", flush=True)
    s = chip.get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)
    s.build(target="vhls", mode="csyn", project=prj)
    src = open(kp).read()
    # (1) union-converter patch (cosim compilability; see gen_kernel_fwd.py)
    src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
                 r"\1 = {};", src)
    src = "#define ALLOW_EMPTY_HLS_STREAM_READS 1\n" + src
    # (2) dep-false on the result rings + res/wb scalars (buys II=1; no primitive)
    for ring in ("resq", "cmpq"):
        src = src.replace(
            "#pragma HLS array_partition variable=%s complete dim=1" % ring,
            "#pragma HLS array_partition variable=%s complete dim=1\n"
            "#pragma HLS dependence variable=%s type=inter dependent=false" % (ring, ring))
    for scal in ("res", "wb"):
        src = src.replace(
            "half %s;" % scal,
            "half %s;\n#pragma HLS dependence variable=%s type=inter dependent=false" % (scal, scal))
    # (3) bind_op latency=2 on fp16 ops (must MATCH FP_LAT so a forwarded product
    # is ready exactly when the MMM ADD reads it)
    n = 0
    src, c = re.subn(r"(half (v\d+) = v\d+ \* v\d+;)",
                     r"\1\n#pragma HLS bind_op variable=\2 op=hmul impl=maxdsp latency=2", src); n += c
    src, c = re.subn(r"(half (v\d+) = v\d+ \+ v\d+;)",
                     r"\1\n#pragma HLS bind_op variable=\2 op=hadd impl=fabric latency=2", src); n += c
    src, c = re.subn(r"(half (v\d+) = v\d+ - v\d+;)",
                     r"\1\n#pragma HLS bind_op variable=\2 op=hsub impl=fabric latency=2", src); n += c
    open(kp, "w").write(src)
    print(f"  wrote {os.path.relpath(kp, HERE)}  ({sum(1 for _ in open(kp))} lines); "
          f"injected dep-false(resq/cmpq/res/wb) + {n} bind_op latency=2")

ini = os.path.join(HERE, f"ci_val_{CHIP}_{M}x{N}_sched.ini")
open(ini, "w").write(
    f"part={PART}\n\n[hls]\nflow_target=vivado\nclock={CLK}\nsyn.top=top\nsyn.file={kp}\n"
    f'tb.file={os.path.join(HERE, "tb_replay_nb.cpp")}\n'
    f'tb.cflags=-I{HERE} -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_val_{CHIP}_{M}x{N}.h"\n')
# NOTE: no pipeline_loops=0 here -> the node loop IS pipelined (this is the point)
print(f"  wrote {os.path.basename(ini)}")
print(f"""
== COSIM (conda deactivate; system Vitis 2025.1) ==
  cd {prj}
  v++ -c --mode hls --config {ini} --work_dir /tmp/valsched_{CHIP}
  vitis-run --mode hls --cosim --config {ini} --work_dir /tmp/valsched_{CHIP}
  # PASS => scheduled (pipelined) forwarding+credits chip matches X@W; check II in csynth.rpt
""")
