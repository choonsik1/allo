# =============================================================================
# build_nb.py - build the FULL non-blocking EVA cosim project (kernel + vectors
# + tb + ini). The Allo simulator CANNOT run the NB chip (bounded-loop+NB race
# hangs), so the expected output is computed ANALYTICALLY (X@W) instead of by
# the sim. We compare only out_s (the mmm result) in cosim.
#
# REQUIRES the non-blocking (NB) Allo branch (NB ops). Run:
#   PYTHONPATH=/home/zsm9/allo LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel \
#     /home/zsm9/miniconda3/envs/allo/bin/python build_nb.py
# env: SZ=4 (mesh/matrix size), LFORCE=374 (kernel length), NOSCHED=1 (default
#      fast/correctness; NOSCHED=0 for II=1 -- slow codegen).
# Then cosim on the host (conda deactivate):
#   cd prj_eva_sb_nb_<SZ>x<SZ>_L<L>[...]
#   v++ -c --mode hls --config ../ci_eva_sb_nb.ini --work_dir top
#   vitis-run --mode hls --cosim --config ../ci_eva_sb_nb.ini --work_dir top
# =============================================================================
import os, sys
# --- point at the non-blocking (NB) Allo branch (NB ops) BEFORE importing allo ---
os.environ.setdefault("LLVM_BUILD_DIR", "/home/zsm9/allo/mlir/build_xcel")
sys.path.insert(0, "/home/zsm9/allo")
import re
import numpy as np

HERE  = os.path.dirname(os.path.abspath(__file__))     # cosim_8x8/eva_sb_nb
COSIM = os.path.dirname(HERE)                            # cosim_8x8
FR    = os.path.dirname(COSIM)                           # final_runs
VER   = os.path.join(FR, "verification")                # eva_workloads.py
sys.path.insert(0, FR); sys.path.insert(0, VER)
PART = "xczu7ev-ffvc1156-2-e"; CLK = "3.33"

SZ      = int(os.environ.get("SZ", "4"))
LF      = int(os.environ.get("LFORCE", "200"))
NOSCHED = os.environ.get("NOSCHED", "1") == "1"
CHIP    = os.environ.get("CHIP", "eva_sb_nb")           # which NB chip source
BINDOP  = os.environ.get("BINDOP", "0") == "1"          # inject bind_op latency=3 (pe_core II=1)
BATCH   = int(os.environ.get("BATCH", "1"))             # streamed MMMs (ITER_SIZE=B, back-to-back)
TS      = ("_ts" in CHIP) or ("_cosim" in CHIP)          # timestamp chip (out_cyc ports) -> tb_replay_nb_ts.cpp
TAG     = ("" if not NOSCHED else "_nosched") + ("_bindop" if BINDOP else "") + (f"_b{BATCH}" if BATCH > 1 else "")

chip = __import__(CHIP)
sys.modules["eva"] = chip                               # eva_workloads uses `eva`
import eva_workloads as WL
from allo.ir.types import float16
import allo.dataflow as df

# ---- inputs + golden.  GOLDEN_NPZ = a PROVEN vec_*.npz (dumped from a working
# chip via dump_synth_mmm) => use its exact inputs AND golden outputs (validated
# flow, chip-independent).  Fallback = analytical X@W (unvalidated, 2x2 broken).
GOLDEN = os.environ.get("GOLDEN_NPZ", "") if BATCH == 1 else ""   # batched => analytical (npz is B=1)
if GOLDEN:
    gp = GOLDEN if os.path.isabs(GOLDEN) else os.path.join(COSIM, GOLDEN)
    d = np.load(gp)
    chip.M, chip.N = int(d["M"]), int(d["N"])
    def _pad(a): return np.pad(np.asarray(a), ((0, 0), (0, LF - np.asarray(a).shape[1])))
    args = {k: [_pad(d[f"{p}{i}"]) for i in range(4)]
            for k, p in (("ins", "in"), ("ivs", "iv"), ("rins", "rin"), ("routs", "rout"))}
    outs = [_pad(d[f"out{i}"]) for i in range(4)]        # GOLDEN outputs (compacted)
    chip.NSTEP = chip.LANELEN = LF
    M, N, L = int(chip.M), int(chip.N), LF
    g = outs[3].view(np.uint16)
    print(f"== build_nb: GOLDEN={os.path.basename(gp)} {M}x{N} L={L} SCHED={not NOSCHED} ==")
    print(f"  golden out_s[col][0] = {[hex(g[c, 0]) for c in range(N)]}")
else:
    W = np.array([[((i + j) % 4) + 1 for j in range(SZ)] for i in range(SZ)], np.float16)
    X = np.tile(np.array([[(i % 3) + 1 for i in range(SZ)]], np.float16), (BATCH, 1))  # BATCH identical rows
    B = X.shape[0]   # = BATCH -> cfg_itsz=B -> B streamed MMMs, B results/column
    args, _ = WL.load_mmm_router(W, X)
    for key in ("ins", "ivs", "outs", "rins", "routs"):
        args[key] = [np.pad(np.asarray(a), ((0, 0), (0, LF - np.asarray(a).shape[1]))) for a in args[key]]
    chip.NSTEP = chip.LANELEN = LF
    M, N, L = int(chip.M), int(chip.N), LF
    XW = X.astype(np.float32) @ W.astype(np.float32)
    outs = [np.zeros((M, L), np.float16), np.zeros((M, L), np.float16),
            np.zeros((N, L), np.float16), np.zeros((N, L), np.float16)]
    for b in range(B):
        for c in range(N):
            outs[3][c, b] = np.float16(XW[b, c])
    print(f"== build_nb: {M}x{N} L={L} SCHED={not NOSCHED} (analytical) ==")
    print(f"  expected out_s (X@W) = {XW.tolist()}")

# ---- vectors header --------------------------------------------------------
def c_arr(decl, a, fmt):
    a = np.asarray(a)
    rows = [", ".join(fmt % v for v in row) for row in a]
    return "static const %s[%d][%d] = {\n  {%s}\n};\n" % (decl, a.shape[0], a.shape[1], "},\n  {".join(rows))
hdr = [f"#define VM {M}\n#define VN {N}\n#define VL {L}\n", f'#define VECNAME "nb_{M}x{N}"\n']
ins, ivs, rins, routs = args["ins"], args["ivs"], args["rins"], args["routs"]
for i in range(4):
    hdr.append(c_arr(f"unsigned short IN{i}",   np.asarray(ins[i]).view(np.uint16), "0x%04x"))
    hdr.append(c_arr(f"int32_t IV{i}",          ivs[i],                              "%d"))
    hdr.append(c_arr(f"int32_t RIN{i}",         rins[i],                             "%d"))
    hdr.append(c_arr(f"unsigned short EOUT{i}", outs[i].view(np.uint16),             "0x%04x"))
    hdr.append(c_arr(f"int32_t EROUT{i}",       routs[i],                            "%d"))
hfile = os.path.join(HERE, f"vectors_{CHIP}_{M}x{N}{TAG}.h"); open(hfile, "w").write("".join(hdr))
print(f"  wrote {os.path.basename(hfile)}")

# ---- generate the NB kernel (allo emits read_nb/write_nb) ---------------
prj = os.path.join(HERE, f"prj_{CHIP}_{M}x{N}_L{L}{TAG}")
kp = os.path.join(prj, "kernel.cpp")
if os.path.exists(kp):
    print(f"  kernel exists: {os.path.relpath(kp, HERE)}")
else:
    print(f"  generating NB kernel (SCHED={not NOSCHED})...", flush=True)
    s = chip.get_scheduled_eva(float16, pipeline_node=not NOSCHED, partition_rf=not NOSCHED)
    s.build(target="vhls", mode="csyn", project=prj)
    src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
                 r"\1 = {};", open(kp).read())
    if not NOSCHED:   # II=1 dependence pragmas for the scoreboard (matches build_cosim_8x8)
        src = re.sub(r"(half ((?:res|wb)\d*);)",
                     r"\1\n#pragma HLS dependence variable=\2 type=inter dependent=false", src)
        src = re.sub(r"(#pragma HLS array_partition variable=((?:resq|cmpq)\d*) complete dim=1)",
                     r"\1\n#pragma HLS dependence variable=\2 type=inter dependent=false", src)
    if BINDOP:   # pe_core II=1 lever: pin fp16 ops to latency=3 (SB_DEPTH=5 >= 3+1 OK)
        src = re.sub(r"(half (v\d+) = v\d+ \* v\d+;)", r"\1\n#pragma HLS bind_op variable=\2 op=hmul impl=maxdsp latency=3", src)
        src = re.sub(r"(half (v\d+) = v\d+ \+ v\d+;)", r"\1\n#pragma HLS bind_op variable=\2 op=hadd impl=fabric latency=3", src)
        src = re.sub(r"(half (v\d+) = v\d+ - v\d+;)",  r"\1\n#pragma HLS bind_op variable=\2 op=hsub impl=fabric latency=3", src)
        print(f"  [bindop] injected {src.count('bind_op')} bind_op pragmas (latency=3)")
    src = "#define ALLOW_EMPTY_HLS_STREAM_READS 1\n" + src
    open(kp, "w").write(src)
    print(f"  wrote {os.path.relpath(kp, HERE)}  ({sum(1 for _ in open(kp))} lines, "
          f"{src.count('read_nb')} read_nb / {src.count('write_nb')} write_nb)")

# ---- config ----------------------------------------------------------------
ini = os.path.join(HERE, f"ci_{CHIP}_{M}x{N}{TAG}.ini")
open(ini, "w").write(
    f"part={PART}\n\n[hls]\nflow_target=vivado\nclock={CLK}\nsyn.top=top\nsyn.file={kp}\n"
    f'tb.file={os.path.join(HERE, "tb_replay_nb_ts.cpp") if TS else os.path.join(HERE, "tb_replay_nb.cpp")}\n'
    f'tb.cflags=-I{HERE} -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_{CHIP}_{M}x{N}{TAG}.h"\n'
    f"syn.compile.pipeline_loops=0\n")
print(f"  wrote {os.path.basename(ini)}")
print(f"""
== COSIM ON HOST (conda deactivate) ==
  cd {prj}
  v++ -c --mode hls --config {ini} --work_dir top
  vitis-run --mode hls --cosim --config {ini} --work_dir top
  # DEADLOCK? => NB still blocks somewhere.  PASS => NB chip works + no deadlock.
""")
