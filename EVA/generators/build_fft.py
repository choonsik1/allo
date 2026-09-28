# build_fft.py - generate an 8x8 FFT RTL-COSIM project (kernel + vectors + ini)
# for a fwd chip, replaying the GOLDEN EVA_untouched 8-pt FFT (tb/pe_array/fft) and
# comparing out_e (EAST) vs the captured golden RTL sys_tx_rgt outputs. This is the
# cosim analog of archive/tests/replay_golden_fft.py (which runs the functional sim);
# here we emit vhls + vectors + tb_replay_fft.cpp for a cycle-accurate RTL cosim.
#   PRIME/DEPTH via env (default = chip file); NOSCHED default (fast codegen).
#   CHIP=eva_sb_syscredit_fwd LFORCE=400 PYTHONPATH=/home/zsh/allo_sup ... python build_fft.py
import os, sys, re, glob
os.environ.setdefault("LLVM_BUILD_DIR", "/home/zsm9/allo_sup/mlir/build_xcel")
sys.path.insert(0, "/home/zsm9/allo_sup")
import numpy as np

HERE  = os.path.dirname(os.path.abspath(__file__))
COSIM = os.path.dirname(HERE); FR = os.path.dirname(COSIM)
VER   = os.path.join(FR, "verification")
sys.path.insert(0, FR); sys.path.insert(0, VER)
PART = "xczu7ev-ffvc1156-2-e"; CLK = "3.33"
GOLD = "/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array/fft"
GOUT = "/home/zsm9/eva_tb_logs/pe_array_fft.out"

CHIP = os.environ.get("CHIP", "eva_sb_syscredit_fwd")
LF   = int(os.environ.get("LFORCE", "400"))

chip = __import__(CHIP); sys.modules["eva"] = chip
if os.environ.get("PRIME") and hasattr(chip, "PRIME_TOKENS"): chip.PRIME_TOKENS = int(os.environ["PRIME"])
if os.environ.get("DEPTH") and hasattr(chip, "STREAM_DEPTH"): chip.STREAM_DEPTH = int(os.environ["DEPTH"])
import eva_workloads as wl
from allo.ir.types import float16
import allo.dataflow as df
f16 = lambda h: np.uint16(h).view(np.float16)

def nrev(g):                       # GOLDEN [op|dst|rs1|rs2] -> OUR encoding, per-opcode
    op=(g>>12)&0xF; dst=(g>>8)&0xF; r1=(g>>4)&0xF; r2=g&0xF
    if op in (0x3,0xB):              return op|(dst<<4)|(r2<<8)
    if 0x4<=op<=0x7 or 0xC<=op<=0xF: return op|(dst<<4)|(r2<<8)|(r1<<12)
    return op|(dst<<4)|(r1<<8)|(r2<<12)

M = N = 8; IRFD = 8
prog = np.zeros((M,N,IRFD), np.int32); NOP = chip.OP_MOV|(6<<4)|(6<<8); prog[:] = NOP
wr = np.zeros((M,N), np.float16); wi = np.zeros((M,N), np.float16); cfg0 = {}
for f in sorted(glob.glob(f"{GOLD}/file_col_upp_*.mem")):
    j = int(re.search(r"_(\d+)\.mem", f).group(1))
    for line in open(f):
        m = re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)", line.strip())
        if not m: continue
        i=int(m[1],16); mode=int(m[2],2); addr=int(m[3],16); data=int(m[4],16)
        if   mode==1 and 8<=addr<=15: prog[i,j,addr-8] = nrev(data)
        elif mode==0 and addr==0:     wr[i,j] = f16(data)
        elif mode==0 and addr==1:     wi[i,j] = f16(data)
        elif mode==1 and addr==0:     cfg0[(i,j)] = (((data>>8)&7)+1, data&0xFF)
def cfg(i,j):
    klen,sync = cfg0.get((i,j),(8,0)); return (klen, 0, sync)   # iter=Inf

chip.M, chip.N = M, N; chip.IRF_DEPTH = IRFD; chip.DATADRIVEN = 1
chip.NSTEP = chip.LANELEN = LF; L = LF
rin_s = wl.load_prog_packets(prog, M, N, data=[(0,wr),(1,wi)], cfg=cfg)
fin = [0x2618,0x26A4,0x2AF7,0x2600,0x2C01,0x2D5A,0x1EB6,0x2A19,0x28BC,0x2E5F,0x2BBB,0x2A05,0x1565,0x2C17,0x2D5C,0x23B6]
pc = M*(IRFD+2+2)+M+8
print(f"== build_fft: CHIP={CHIP} 8x8 L={L} pc={pc} PRIME={getattr(chip,'PRIME_TOKENS','-')}/D={getattr(chip,'STREAM_DEPTH','-')} ==", flush=True)

zi = lambda *s: np.zeros(s, np.int32); zf = lambda *s: np.zeros(s, np.float16)
ins = [zf(M,L),zf(M,L),zf(N,L),zf(N,L)]; ivs = [zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
rins= [zi(M,L),zi(M,L),zi(N,L),zi(N,L)]; routs=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
for i in range(M):
    ins[0][i,pc]   = f16(fin[2*i]);   ivs[0][i,pc]   = 1
    ins[0][i,pc+1] = f16(fin[2*i+1]); ivs[0][i,pc+1] = 1
rins[3] = rin_s

# expected out_e (EAST) from golden RTL capture -> place at out_e[j][0], [1]
gold = {}
for line in open(GOUT):
    m = re.search(r"sys_tx_rgt_data\[(\d)\] = ([0-9a-f]+)", line)
    if m: gold.setdefault(int(m[1]), []).append(int(m[2],16))
outs = [zf(M,L),zf(M,L),zf(N,L),zf(N,L)]
for j in range(N):
    for t in range(min(2, len(gold.get(j,[])))):
        outs[1][j,t] = f16(gold[j][t])     # out_e = index 1
print(f"  golden out_e[j][0] = {[hex(gold[j][0]) for j in range(N)]}")

def c_arr(decl, a, fmt):
    a = np.asarray(a); rows = [", ".join(fmt % v for v in row) for row in a]
    return "static const %s[%d][%d] = {\n  {%s}\n};\n" % (decl, a.shape[0], a.shape[1], "},\n  {".join(rows))
hdr = [f"#define VM {M}\n#define VN {N}\n#define VL {L}\n", f'#define VECNAME "fft_{CHIP}_8x8"\n', f"#define VPC {pc}\n"]
for i in range(4):
    hdr.append(c_arr(f"unsigned short IN{i}",   np.asarray(ins[i]).view(np.uint16), "0x%04x"))
    hdr.append(c_arr(f"int32_t IV{i}",          ivs[i],                              "%d"))
    hdr.append(c_arr(f"int32_t RIN{i}",         rins[i],                             "%d"))
    hdr.append(c_arr(f"unsigned short EOUT{i}", outs[i].view(np.uint16),             "0x%04x"))
    hdr.append(c_arr(f"int32_t EROUT{i}",       routs[i],                            "%d"))
hfile = os.path.join(HERE, f"vectors_fft_{CHIP}_8x8.h"); open(hfile,"w").write("".join(hdr))
print(f"  wrote {os.path.basename(hfile)}")

prj = os.path.join(HERE, f"prj_fft_{CHIP}_8x8_L{L}")
kp  = os.path.join(prj, "kernel.cpp")
if os.path.exists(kp):
    print(f"  kernel exists: {os.path.relpath(kp, HERE)}")
else:
    print("  generating 8x8 NOSCHED kernel (this is the slow step; ~minutes)...", flush=True)
    s = chip.get_scheduled_eva(float16, pipeline_node=False, partition_rf=False)
    s.build(target="vhls", mode="csyn", project=prj)
    src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
                 r"\1 = {};", open(kp).read())
    src = "#define ALLOW_EMPTY_HLS_STREAM_READS 1\n" + src
    open(kp,"w").write(src)
    print(f"  wrote {os.path.relpath(kp, HERE)} ({sum(1 for _ in open(kp))} lines)")

ini = os.path.join(HERE, f"ci_fft_{CHIP}_8x8.ini")
open(ini,"w").write(
    f"part={PART}\n\n[hls]\nflow_target=vivado\nclock={CLK}\nsyn.top=top\nsyn.file={kp}\n"
    f'tb.file={os.path.join(HERE, "tb_replay_fft.cpp")}\n'
    f'tb.cflags=-I{HERE} -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_fft_{CHIP}_8x8.h"\n'
    f"syn.compile.pipeline_loops=0\n")
print(f"  wrote {os.path.basename(ini)}\nPRJ={prj}\nINI={ini}")
