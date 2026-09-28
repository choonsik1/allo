# build_val_sched_ts.py - SCHEDULED (II=1, pipelined) + TIMESTAMPED (out_cyc) 4x4
# mmm cosim for a forwarding _cosim chip. Streams B=BATCH MMMs so tb_replay_nb_ts
# can read out_cyc gaps -> steady-state cyc/MMM (the ACCURATE II=1 array throughput).
# Recipe = build_val_sched (pipeline_node/partition_rf + dep-false + bind_op lat=2)
# + _cosim chip (out_cyc ports) + tb_replay_nb_ts.cpp + B>1.
#   CHIP=eva_sb_syscredit_fwd_cosim SZ=4 LFORCE=374 BATCH=4 \
#     PYTHONPATH=/home/zsm9/allo_sup LLVM_BUILD_DIR=/home/zsm9/allo_sup/mlir/build_xcel \
#     python build_val_sched_ts.py
import os, sys
os.environ.setdefault("LLVM_BUILD_DIR", "/home/zsm9/allo_sup/mlir/build_xcel")
sys.path.insert(0, "/home/zsm9/allo_sup")
import re
import numpy as np

HERE  = os.path.dirname(os.path.abspath(__file__))
COSIM = os.path.dirname(HERE); FR = os.path.dirname(COSIM)
VER   = os.path.join(FR, "verification")
sys.path.insert(0, FR); sys.path.insert(0, VER)
PART = "xczu7ev-ffvc1156-2-e"; CLK = "3.33"

CHIP  = os.environ.get("CHIP", "eva_sb_syscredit_fwd_cosim")
SZ    = int(os.environ.get("SZ", "4"))
LF    = int(os.environ.get("LFORCE", "374"))
BATCH = int(os.environ.get("BATCH", "4"))
NOSCHED = os.environ.get("NOSCHED", "0") == "1"
EXPTAG  = os.environ.get("EXPTAG", "")
FPLAT   = os.environ.get("FPLAT", "2")
DEPFALSE= os.environ.get("DEPFALSE", "1") == "1"
MULIMPL = os.environ.get("MULIMPL", "maxdsp")

chip = __import__(CHIP)
sys.modules["eva"] = chip
import eva_workloads as WL
from allo.ir.types import float16
import allo.dataflow as df

W = np.array([[((i + j) % 4) + 1 for j in range(SZ)] for i in range(SZ)], np.float16)
X = np.tile(np.array([[(i % 3) + 1 for i in range(SZ)]], np.float16), (BATCH, 1))  # B identical rows
B = X.shape[0]
args, _ = WL.load_mmm_router(W, X)
for key in ("ins", "ivs", "outs", "rins", "routs"):
    args[key] = [np.pad(np.asarray(a), ((0, 0), (0, LF - np.asarray(a).shape[1]))) for a in args[key]]
chip.NSTEP = chip.LANELEN = LF
M, N, L = int(chip.M), int(chip.N), LF
print(f"== build_val_sched_ts: CHIP={CHIP} {M}x{N} L={L} B={B} SCHEDULED+TS ==", flush=True)

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
hdr = [f"#define VM {M}\n#define VN {N}\n#define VL {L}\n", f'#define VECNAME "ts_{CHIP}_{M}x{N}_b{B}"\n']
ins, ivs, rins = args["ins"], args["ivs"], args["rins"]
for i in range(4):
    hdr.append(c_arr(f"unsigned short IN{i}",   np.asarray(ins[i]).view(np.uint16), "0x%04x"))
    hdr.append(c_arr(f"int32_t IV{i}",          ivs[i],                              "%d"))
    hdr.append(c_arr(f"int32_t RIN{i}",         rins[i],                             "%d"))
    hdr.append(c_arr(f"unsigned short EOUT{i}", outs[i].view(np.uint16),             "0x%04x"))
    hdr.append(c_arr(f"int32_t EROUT{i}",       args["routs"][i],                    "%d"))
# runtime-prime chip: emit PRIMECFG[M,N] (prime seed) for tb_replay_nb_ts_prime
PR = int(os.environ.get("PRIME", "6"))
hdr.append(c_arr("int32_t PRIMECFG", np.full((M, N), PR, np.int32), "%d"))
hfile = os.path.join(HERE, f"vectors_ts_{CHIP}_{M}x{N}_b{B}.h"); open(hfile, "w").write("".join(hdr))
print(f"  wrote {os.path.basename(hfile)}")

TAG = "nosched" if NOSCHED else "sched"
prj = os.path.join(HERE, f"prj_ts_{CHIP}_{M}x{N}_L{L}_b{B}_{TAG}{EXPTAG}")
kp = os.path.join(prj, "kernel.cpp")
if os.path.exists(kp):
    print(f"  kernel exists: {os.path.relpath(kp, HERE)}")
else:
    print(f"  generating {TAG.upper()} kernel (pipeline_node={not NOSCHED})...", flush=True)
    s = chip.get_scheduled_eva(float16, pipeline_node=not NOSCHED, partition_rf=not NOSCHED)
    s.build(target="vhls", mode="csyn", project=prj)
    src = open(kp).read()
    src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
                 r"\1 = {};", src)
    src = "#define ALLOW_EMPTY_HLS_STREAM_READS 1\n" + src
    n = 0
    if not NOSCHED:   # II=1 pragmas only meaningful for the scheduled build
        for ring in ("resq", "cmpq"):
            src = src.replace(
                "#pragma HLS array_partition variable=%s complete dim=1" % ring,
                "#pragma HLS array_partition variable=%s complete dim=1\n"
                "#pragma HLS dependence variable=%s type=inter dependent=false" % (ring, ring))
        for scal in ("res", "wb"):
            src = src.replace(
                "half %s;" % scal,
                "half %s;\n#pragma HLS dependence variable=%s type=inter dependent=false" % (scal, scal))
        src, c = re.subn(r"(half (v\d+) = v\d+ \* v\d+;)",
                         r"\1\n#pragma HLS bind_op variable=\2 op=hmul impl=maxdsp latency=2", src); n += c
        src, c = re.subn(r"(half (v\d+) = v\d+ \+ v\d+;)",
                         r"\1\n#pragma HLS bind_op variable=\2 op=hadd impl=fabric latency=2", src); n += c
        src, c = re.subn(r"(half (v\d+) = v\d+ - v\d+;)",
                         r"\1\n#pragma HLS bind_op variable=\2 op=hsub impl=fabric latency=2", src); n += c
    src = src.replace("latency=2", "latency=%s" % FPLAT)
    src = src.replace("op=hmul impl=maxdsp", "op=hmul impl=%s" % MULIMPL)
    if not DEPFALSE:
        src = re.sub(r"\n#pragma HLS dependence variable=\w+ type=inter dependent=false", "", src)
    print("  EXP: FPLAT=%s MULIMPL=%s DEPFALSE=%s depfalse_lines=%d bind_lat1=%d" % (FPLAT,MULIMPL,DEPFALSE, src.count("dependent=false"), src.count("latency=1")))
    open(kp, "w").write(src)
    print(f"  wrote kernel ({sum(1 for _ in open(kp))} lines); {TAG} + {n} bind_op")

ini = os.path.join(HERE, f"ci_ts_{CHIP}_{M}x{N}_b{B}_{TAG}{EXPTAG}.ini")
open(ini, "w").write(
    f"part={PART}\n\n[hls]\nflow_target=vivado\nclock={CLK}\nsyn.top=top\nsyn.file={kp}\n"
    f'tb.file={os.path.join(HERE, "tb_replay_nb_ts_prime.cpp")}\n'
    f'tb.cflags=-I{HERE} -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_ts_{CHIP}_{M}x{N}_b{B}.h"\n')
print(f"  wrote {os.path.basename(ini)}\nPRJ={prj}\nINI={ini}")
