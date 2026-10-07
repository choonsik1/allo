# Replay GOLDEN EVA_untouched 8-pt FFT (tb/pe_array/fft) through our Allo chip,
# diff vs golden RTL sys_tx_rgt outputs. Reuses the semantic translator (incl RTR).
import os, sys, re, glob
os.environ.setdefault("OMP_NUM_THREADS","256")
HERE=os.path.dirname(os.path.abspath(__file__)); sys.path.insert(0, os.path.join(HERE,".."))
import numpy as np, allo.dataflow as df
from allo.ir.types import float16
import eva as e
sys.modules["eva"]=e
import eva_workloads as wl
GOLD="/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array/fft"
def f16(h): return np.uint16(h).view(np.float16)
def nrev(g):                       # GOLDEN [op|dst|rs1|rs2] -> OUR encoding, per-opcode
    op=(g>>12)&0xF; dst=(g>>8)&0xF; r1=(g>>4)&0xF; r2=g&0xF
    if op in (0x3,0xB):            return op|(dst<<4)|(r2<<8)              # MOV/SQRT: src=rs2 -> s1
    if 0x4<=op<=0x7 or 0xC<=op<=0xF: return op|(dst<<4)|(r2<<8)|(r1<<12)  # RTR/CRTR: s1=src, s2=cid
    return op|(dst<<4)|(r1<<8)|(r2<<12)                                   # binary: s1=rs1,s2=rs2
M=N=8; IRFD=8
prog=np.zeros((M,N,IRFD),np.int32); NOP=e.OP_MOV|(6<<4)|(6<<8); prog[:]=NOP
wr=np.zeros((M,N),np.float16); wi=np.zeros((M,N),np.float16)
cfg0={}   # (i,j)->(instr_size,sync); iter defaults Inf (golden sends no CFG1)
for f in sorted(glob.glob(f"{GOLD}/file_col_upp_*.mem")):
    j=int(re.search(r"_(\d+)\.mem",f).group(1))
    for line in open(f):
        m=re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)",line.strip())
        if not m: continue
        i=int(m[1],16); mode=int(m[2],2); addr=int(m[3],16); data=int(m[4],16)
        if mode==1 and 8<=addr<=15: prog[i,j,addr-8]=nrev(data)
        elif mode==0 and addr==0:   wr[i,j]=f16(data)
        elif mode==0 and addr==1:   wi[i,j]=f16(data)
        elif mode==1 and addr==0:   cfg0[(i,j)]=(((data>>8)&7)+1, data&0xFF)   # (klen, sync)
# per-node cfg: klen from CFG0, iter=0 (=Inf, golden default), sync from CFG0
def cfg(i,j):
    klen,sync=cfg0.get((i,j),(8,0)); return (klen, 0, sync)
e.M,e.N=M,N; e.IRF_DEPTH=IRFD; e.DATADRIVEN=1
per_node=IRFD+2+2; pc=M*per_node+M+8; e.NSTEP=pc+int(os.environ.get("MARGIN","120")); e.LANELEN=e.NSTEP; L=e.LANELEN  # scoreboard family needs MARGIN>=1200
rin_s=wl.load_prog_packets(prog,M,N,data=[(0,wr),(1,wi)],cfg=cfg)
fin=[0x2618,0x26A4,0x2AF7,0x2600,0x2C01,0x2D5A,0x1EB6,0x2A19,0x28BC,0x2E5F,0x2BBB,0x2A05,0x1565,0x2C17,0x2D5C,0x23B6]
zi=lambda *s:np.zeros(s,np.int32); zf=lambda *s:np.zeros(s,np.float16)
ins=[zf(M,L),zf(M,L),zf(N,L),zf(N,L)]; outs=[zf(M,L),zf(M,L),zf(N,L),zf(N,L)]
rins=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]; routs=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
ivw=zi(M,L)
for i in range(M):
    ins[0][i,pc]=f16(fin[2*i]);   ivw[i,pc]=1
    ins[0][i,pc+1]=f16(fin[2*i+1]); ivw[i,pc+1]=1
rins[3]=rin_s
print(f"building 8x8 FFT (NSTEP={e.NSTEP})..."); sys.stdout.flush()
mod=df.build(e.get_eva_top(float16),target='simulator')
e.run_eva(mod, ins,[ivw,zi(M,L),zi(N,L),zi(N,L)], outs, rins, routs)
out_e=outs[1]   # EAST collector
gold={}
for line in open("/home/zsm9/eva_tb_logs/pe_array_fft.out"):
    m=re.search(r"sys_tx_rgt_data\[(\d)\] = ([0-9a-f]+)",line)
    if m: gold.setdefault(int(m[1]),[]).append(int(m[2],16))
print("\nrow | t | Allo out_e(hex) | golden(hex) | match")
ok=0;tot=0
for j in range(N):
    for t in range(2):
        ah=int(np.float16(out_e[j,t]).view(np.uint16)); gh=gold[j][t] if t<len(gold.get(j,[])) else None
        mt=(gh is not None and ah==gh); ok+=mt; tot+=1
        gs=f"{gh:04x}" if gh is not None else "----"
        print(f" {j}  | {t} |      {ah:04x}       |    {gs}     | {'OK' if mt else 'x'}")
print(f"\nAllo-vs-GOLDEN FFT: {ok}/{tot} bit-exact")
