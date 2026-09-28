# build_golden_cosim.py - generalized 8x8 RTL-cosim builder for ANY shipped EVA
# pe_array workload (mmm / fft / cordic_{cr,cv,hr,hv}). Emits vhls kernel + vectors
# + ini + reuses tb_replay_golden.cpp, replaying the golden program (file_col_upp)
# with golden TB inputs and comparing the golden output edge vs eva_tb_logs/*.out.
# Mirrors build_fft.py's emit path; per-workload config = generic replay's table.
#   CHIP=eva_sb_syscredit_fwd WL=cordic_cr LFORCE=800 [PRIME=6] \
#     PYTHONPATH=/home/zsm9/allo python build_golden_cosim.py
import os, sys, re, glob
os.environ.setdefault("LLVM_BUILD_DIR", "/home/zsm9/allo/mlir/build_xcel")
sys.path.insert(0, "/home/zsm9/allo")
import numpy as np

HERE  = os.path.dirname(os.path.abspath(__file__))
COSIM = os.path.dirname(HERE); FR = os.path.dirname(COSIM)
VER   = os.path.join(FR, "verification")
sys.path.insert(0, FR); sys.path.insert(0, VER)
sys.path.insert(0, "/home/zsm9/pe_core_implementation/Allo/EVA/archive/tests")
PART = "xczu7ev-ffvc1156-2-e"; CLK = "3.33"
GB   = "/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array"
LOG  = "/home/zsm9/eva_tb_logs"

# (gold_subdir, tb.sv, in_edge, per_row, out_edge, out_sig, goldout)
# in/out edges: lft->in_w(0)/west, rgt->out_e(1)/east, top->out_n(2), btm->out_s(3)/south
CFG = {
 "mmm":       ("mmm",                        "lft", 2, "btm", "sys_tx_btm_data", "pe_array_mmm.out"),
 "fft":       ("fft",                        "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_fft.out"),
 "cordic_cr": ("cordic_circular_rotation",   "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_cr.out"),
 "cordic_cv": ("cordic_circular_vectoring",  "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_cv.out"),
 "cordic_hr": ("cordic_hyperbolic_rotation", "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_hr.out"),
 "cordic_hv": ("cordic_hyperbolic_vectoring","lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_cordic_hv.out"),
}
IN_IDX  = {"lft":0, "rgt":1, "top":2, "btm":3}
OUT_IDX = {"lft":0, "rgt":1, "top":2, "btm":3}

CHIP = os.environ.get("CHIP", "eva_sb_syscredit_fwd")
TAG  = os.environ.get("TAG", "gc")            # "gc"=correctness, "gcts"=timestamped
TB   = os.environ.get("TB", "tb_replay_golden.cpp")
WL   = os.environ.get("WL", "cordic_cr")
LF   = int(os.environ.get("LFORCE", "800"))
B    = int(os.environ.get("B", "1"))   # activations streamed back-to-back
subdir, in_edge, per_row, out_edge, out_sig, goldfile = CFG[WL]
GOLD = f"{GB}/{subdir}"
TBSV = f"{GOLD}/tb_pe_array_{subdir}.sv"
GOUT = f"{LOG}/{goldfile}"

chip = __import__(CHIP); sys.modules["eva"] = chip
if os.environ.get("PRIME") and hasattr(chip, "PRIME_TOKENS"): chip.PRIME_TOKENS = int(os.environ["PRIME"])
if os.environ.get("DEPTH") and hasattr(chip, "STREAM_DEPTH"): chip.STREAM_DEPTH = int(os.environ["DEPTH"])
import eva_workloads as wl
from allo.ir.types import float16
import allo.dataflow as df
f16 = lambda h: np.uint16(h).view(np.float16)

def nrev(g):
    op=(g>>12)&0xF; dst=(g>>8)&0xF; r1=(g>>4)&0xF; r2=g&0xF
    if op in (0x3,0xB):              return op|(dst<<4)|(r2<<8)
    if 0x4<=op<=0x7 or 0xC<=op<=0xF: return op|(dst<<4)|(r2<<8)|(r1<<12)
    return op|(dst<<4)|(r1<<8)|(r2<<12)

M = N = int(os.environ.get("MESH","8")); IRFD = 8
prog = np.zeros((M,N,IRFD), np.int32); NOP = chip.OP_MOV|(6<<4)|(6<<8); prog[:] = NOP
drf = {}; cfg0 = {}
for f in sorted(glob.glob(f"{GOLD}/file_col_upp_*.mem")):
    j = int(re.search(r"_(\d+)\.mem", f).group(1))
    for line in open(f):
        m = re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)", line.strip())
        if not m: continue
        i=int(m[1],16); mode=int(m[2],2); addr=int(m[3],16); data=int(m[4],16)
        if   mode==1 and 8<=addr<=15: prog[i,j,addr-8] = nrev(data)
        elif mode==0:                 drf.setdefault(addr, np.zeros((M,N),np.float16))[i,j] = f16(data)
        elif mode==1 and addr==0:     cfg0[(i,j)] = (((data>>8)&7)+1, data&0xFF)
def cfg(i,j):
    klen,sync = cfg0.get((i,j),(8,0)); return (klen, 0, sync)   # iter=Inf

chip.M, chip.N = M, N; chip.IRF_DEPTH = IRFD; chip.DATADRIVEN = 1
per_node = IRFD + len(drf) + 2; pc = M*per_node + M + 8
chip.NSTEP = chip.LANELEN = LF; L = LF
rin_s = wl.load_prog_packets(prog, M, N, data=[(a, drf[a]) for a in sorted(drf)], cfg=cfg)
# golden TB inputs
blk  = re.search(r"_inputs\s*=\s*\{(.*?)\};", open(TBSV).read(), re.S).group(1)
vals = [int(x,16) for x in re.findall(r"16'h([0-9A-Fa-f]+)", blk)]
print(f"== build_golden_cosim: WL={WL} CHIP={CHIP} 8x8 L={L} pc={pc} in={in_edge} out={out_edge} "
      f"PRIME={getattr(chip,'PRIME_TOKENS','-')} drf={sorted(drf)} #inputs={len(vals)} ==", flush=True)

zi = lambda *s: np.zeros(s, np.int32); zf = lambda *s: np.zeros(s, np.float16)
ins = [zf(M,L),zf(M,L),zf(N,L),zf(N,L)]; ivs = [zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
rins= [zi(M,L),zi(M,L),zi(N,L),zi(N,L)]; routs=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
ie = IN_IDX[in_edge]
is_cordic = WL.startswith("cordic")        # cordic lanes are ASYMMETRIC (matches golden TB)
for b in range(B):                         # B back-to-back activations (streaming)
    for k in range(N):
        # CORDIC lane asymmetry (matches tb_pe_array_cordic_*): even lanes carry only
        # the x operand (1 word/op); odd lanes carry z then y (2 words/op). The 0x0000
        # "dummy" at vals[2k+1] on even lanes is a placeholder and must NOT be driven
        # (iv=1 on it => a spurious 0.0 operand that skews throughput; correctness is
        # unaffected since the design buffers it, but the input rate is wrong). mmm/fft
        # are symmetric (2 real words on every lane), so words = per_row there.
        words = (1 if (k % 2 == 0) else 2) if is_cordic else per_row
        base = pc + b*words                # per-lane contiguous reps (even: B slots, odd: 2B)
        for t in range(words):
            ins[ie][k, base + t] = f16(vals[per_row*k + t])
            ivs[ie][k, base + t] = 1
rins[3] = rin_s

# golden expected outputs -> place at outs[out_idx][k][t]
gold = {}
for line in open(GOUT):
    m = re.search(rf"{out_sig}\[(\d)\] = ([0-9a-f]+)", line)
    if m: gold.setdefault(int(m[1]), []).append(int(m[2],16))
oi = OUT_IDX[out_edge]
outs = [zf(M,L),zf(M,L),zf(N,L),zf(N,L)]
GMAX = max((len(gold.get(k,[])) for k in range(N)), default=0)
for k in range(N):
    for t in range(min(GMAX, len(gold.get(k,[])))):
        outs[oi][k, t] = f16(gold[k][t])
print(f"  golden {out_sig}[k][0] = {[hex(gold[k][0]) if gold.get(k) else '-' for k in range(N)]}  (GMAX={GMAX})")

def c_arr(decl, a, fmt):
    a = np.asarray(a); rows = [", ".join(fmt % v for v in row) for row in a]
    return "static const %s[%d][%d] = {\n  {%s}\n};\n" % (decl, a.shape[0], a.shape[1], "},\n  {".join(rows))
hdr = [f"#define VM {M}\n#define VN {N}\n#define VL {L}\n", f'#define VECNAME "{TAG}_{WL}_{CHIP}_8x8"\n',
       f"#define VPC {pc}\n#define VOUT_IDX {oi}\n#define VGMAX {GMAX}\n#define VB {B}\n"]
for i in range(4):
    hdr.append(c_arr(f"unsigned short IN{i}",   np.asarray(ins[i]).view(np.uint16), "0x%04x"))
    hdr.append(c_arr(f"int32_t IV{i}",          ivs[i],                              "%d"))
    hdr.append(c_arr(f"int32_t RIN{i}",         rins[i],                             "%d"))
    hdr.append(c_arr(f"unsigned short EOUT{i}", outs[i].view(np.uint16),             "0x%04x"))
    hdr.append(c_arr(f"int32_t EROUT{i}",       routs[i],                            "%d"))
# runtime-prime chips take a per-tile prime_cfg[M,N] input (== the workload's prime).
HASPRIME = "rtprime" in CHIP
if HASPRIME:
    PR = int(os.environ.get("PRIME", "6"))
    hdr.insert(2, f"#define VHASPRIME 1\n#define VPRIME {PR}\n")
    hdr.append(c_arr("int32_t PRIMECFG", np.full((M, N), PR, np.int32), "%d"))
hfile = os.path.join(HERE, f"vectors_{TAG}_{WL}_8x8.h"); open(hfile,"w").write("".join(hdr))
print(f"  wrote {os.path.basename(hfile)}")

# SCHED=1 -> real II=1 build: node loop pipelined (pipeline_node=True), rf partitioned,
# and DON'T disable pipeline_loops. Separate _sched project so it never clobbers NOSCHED.
# The scheduled 8x8 kernel is workload-INDEPENDENT (depends only on M,N,L,chip cfg), so it
# can be generated once and reused (copy kernel.cpp into other WLs' _sched prj) across all 6.
SCHED = int(os.environ.get("SCHED", "0"))
SUFFIX = "_sched" if SCHED else ""
prj = os.path.join(HERE, f"prj_{TAG}_{WL}_8x8_L{L}{SUFFIX}")
kp  = os.path.join(prj, "kernel.cpp")
if os.path.exists(kp):
    print(f"  kernel exists: {os.path.relpath(kp, HERE)}")
else:
    if SCHED:
        print("  generating 8x8 SCHEDULED kernel (pipeline_node=True, SLOW >hrs)...", flush=True)
        s = chip.get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)
    else:
        print("  generating 8x8 NOSCHED kernel (~minutes)...", flush=True)
        s = chip.get_scheduled_eva(float16, pipeline_node=False, partition_rf=False)
    s.build(target="vhls", mode="csyn", project=prj)
    src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
                 r"\1 = {};", open(kp).read())
    src = "#define ALLOW_EMPTY_HLS_STREAM_READS 1\n" + src
    open(kp,"w").write(src)
    print(f"  wrote {os.path.relpath(kp, HERE)} ({sum(1 for _ in open(kp))} lines)")

ini = os.path.join(HERE, f"ci_{TAG}_{WL}_8x8{SUFFIX}.ini")
open(ini,"w").write(
    f"part={PART}\n\n[hls]\nflow_target=vivado\nclock={CLK}\nsyn.top=top\nsyn.file={kp}\n"
    f'tb.file={os.path.join(HERE, TB)}\n'
    f'tb.cflags=-I{HERE} -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_{TAG}_{WL}_8x8.h"\n'
    + ("" if SCHED else "syn.compile.pipeline_loops=0\n"))
print(f"  wrote {os.path.basename(ini)}\nPRJ={prj}\nINI={ini}")
