# build_prime_sched.py - the SCHEDULED (II=1) rtprime build: pipeline_node=True +
# partition_rf=True, then inject dependence=false (resq/cmpq/res/wb) and bind_op
# latency=2 on the fp16 ops (hmul/hadd/hsub) — the exact recipe that gives II=1 on
# 2025.1 (ported from variant_ii1/gen_fplat.py). Emits:
#   - kernel.cpp (scheduled+depfalse+bindop) = the HLS code deliverable
#   - ci_prime_{M}x{N}_sched.ini  (syn.top=top)        -> full-top csim/csynth/cosim
#   - ci_node_only_sched.ini      (syn.top=node_0_0)   -> isolated PE-core csynth/P&R
# Run: SZ=1 LFORCE=120 PRIME=6 PYTHONPATH=/home/zsm9/allo \
#        /home/zsm9/miniconda3/envs/allo/bin/python build_prime_sched.py
import os, sys, re
os.environ.setdefault("LLVM_BUILD_DIR", "/home/zsm9/allo/mlir/build_xcel")
sys.path.insert(0, "/home/zsm9/allo")
import numpy as np

PRIME_DIR = os.path.dirname(os.path.abspath(__file__))
FR   = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs"
VER  = os.path.join(FR, "verification")
sys.path.insert(0, PRIME_DIR); sys.path.insert(0, FR); sys.path.insert(0, VER)
sys.path.insert(0, "/home/zsm9/pe_core_implementation/Allo/EVA/archive/tests")
PART = "xczu7ev-ffvc1156-2-e"; CLK = "3.33"

CHIP  = os.environ.get("CHIP", "eva_sb_syscredit_rtprime")
SUF   = "_fifo" if CHIP.endswith("_fifo") else ""   # keep FIFO-variant artifacts separate
SZ    = int(os.environ.get("SZ", "1"))
LF    = int(os.environ.get("LFORCE", "120"))
PRIME = int(os.environ.get("PRIME", "6"))
FPLAT = int(os.environ.get("FPLAT", "1"))            # forward-ready threshold

chip = __import__(CHIP); sys.modules["eva"] = chip
chip.M = chip.N = SZ
chip.FP_LAT = FPLAT
import eva_workloads as WL
from allo.ir.types import float16

W = np.array([[((i + j) % 4) + 1 for j in range(SZ)] for i in range(SZ)], np.float16)
X = np.array([[(i % 3) + 1 for i in range(SZ)]], np.float16)
B = X.shape[0]
args, _ = WL.load_mmm_router(W, X)
for key in ("ins", "ivs", "outs", "rins", "routs"):
    args[key] = [np.pad(np.asarray(a), ((0, 0), (0, LF - np.asarray(a).shape[1]))) for a in args[key]]
chip.NSTEP = chip.LANELEN = LF
chip.PRIME_TOKENS = PRIME
M, N, L = int(chip.M), int(chip.N), LF
print(f"== build_prime_sched: {CHIP} {M}x{N} L={L} PRIME={PRIME} FP_LAT={FPLAT} SCHEDULED ==")

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
hdr = [f"#define VM {M}\n#define VN {N}\n#define VL {L}\n", f'#define VECNAME "primeSCHED_{CHIP}_{M}x{N}"\n',
       f"#define VPRIME {PRIME}\n"]
ins, ivs, rins = args["ins"], args["ivs"], args["rins"]
for i in range(4):
    hdr.append(c_arr(f"unsigned short IN{i}",   np.asarray(ins[i]).view(np.uint16), "0x%04x"))
    hdr.append(c_arr(f"int32_t IV{i}",          ivs[i],                              "%d"))
    hdr.append(c_arr(f"int32_t RIN{i}",         rins[i],                             "%d"))
    hdr.append(c_arr(f"unsigned short EOUT{i}", outs[i].view(np.uint16),             "0x%04x"))
    hdr.append(c_arr(f"int32_t EROUT{i}",       args["routs"][i],                    "%d"))
hdr.append(c_arr("int32_t PRIMECFG", np.full((M, N), PRIME, np.int32), "%d"))
hfile = os.path.join(PRIME_DIR, f"vectors_prime_{M}x{N}{SUF}.h"); open(hfile, "w").write("".join(hdr))
print(f"  wrote {os.path.basename(hfile)}")

prj = os.path.join(PRIME_DIR, f"prj_wbfwd_{M}x{N}_L{L}_fp{FPLAT}")
kp = os.path.join(prj, "kernel.cpp")
if os.path.exists(kp):
    print(f"  kernel exists: {os.path.relpath(kp, PRIME_DIR)}")
else:
    print(f"  generating SCHEDULED kernel (pipeline_node=True, partition_rf=True)...", flush=True)
    s = chip.get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)
    try:
        s.partition("prime_cfg"); print("  partitioned prime_cfg")
    except Exception as e:
        print("  partition prime_cfg skipped:", str(e)[:120])
    s.build(target="vhls", mode="csyn", project=prj)
    src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
                 r"\1 = {};", open(kp).read())
    src = "#define ALLOW_EMPTY_HLS_STREAM_READS 1\n" + src
    # (a) dependence=false on the result rings + scalars -> enables II=1
    for ring in ("resq", "cmpq"):
        src = src.replace("#pragma HLS array_partition variable=%s complete dim=1" % ring,
                          "#pragma HLS array_partition variable=%s complete dim=1\n"
                          "#pragma HLS dependence variable=%s type=inter dependent=false" % (ring, ring))
    for scal in ("res", "wb"):
        src = src.replace("half %s;" % scal,
                          "half %s;\n#pragma HLS dependence variable=%s type=inter dependent=false" % (scal, scal))
    # (b) bind_op latency=2 on fp16 ops (hmul/hadd/hsub)
    nb = 0
    src, c = re.subn(r"(half (v\d+) = v\d+ \* v\d+;)",
                     r"\1\n#pragma HLS bind_op variable=\2 op=hmul impl=maxdsp latency=2", src); nb += c
    src, c = re.subn(r"(half (v\d+) = v\d+ \+ v\d+;)",
                     r"\1\n#pragma HLS bind_op variable=\2 op=hadd impl=fabric latency=2", src); nb += c
    src, c = re.subn(r"(half (v\d+) = v\d+ - v\d+;)",
                     r"\1\n#pragma HLS bind_op variable=\2 op=hsub impl=fabric latency=2", src); nb += c
    open(kp, "w").write(src)
    print(f"  wrote {os.path.relpath(kp, PRIME_DIR)}  ({sum(1 for _ in open(kp))} lines); injected depfalse + {nb} bind_op")

# full-top ini (csim / csynth / cosim)
ini = os.path.join(PRIME_DIR, f"ci_wbfwd_{M}x{N}_fp{FPLAT}.ini")
open(ini, "w").write(
    f"part={PART}\n\n[hls]\nflow_target=vivado\nclock={CLK}\nsyn.top=top\nsyn.file={kp}\n"
    f"syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS\n"
    f'tb.file={os.path.join(PRIME_DIR, "tb_replay_prime.cpp")}\n'
    f'tb.cflags=-I{PRIME_DIR} -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_prime_{M}x{N}{SUF}.h"\n'
    f"syn.compile.pipeline_loops=0\n")
# node-only ini (isolated PE-core csynth / P&R)
nini = os.path.join(PRIME_DIR, f"ci_wbfwd_node_{M}x{N}_fp{FPLAT}.ini")
open(nini, "w").write(
    f"part={PART}\n\n[hls]\nflow_target=vivado\nclock={CLK}\nsyn.top=node_0_0\nsyn.file={kp}\n"
    f"syn.compile.pipeline_loops=0\n")
print(f"  wrote {os.path.basename(ini)} (full-top) + {os.path.basename(nini)} (node-only)\nPRJ={prj}")
