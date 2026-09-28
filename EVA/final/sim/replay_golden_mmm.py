# Replay the GOLDEN EVA_untouched MMM (exact program+weights+activations from
# tb/pe_array/mmm) through OUR Allo chip and diff vs the golden RTL outputs.
import os, sys, re, glob
os.environ.setdefault("OMP_NUM_THREADS", "256")
HERE=os.path.dirname(os.path.abspath(__file__)); sys.path.insert(0, os.path.join(HERE,".."))
import numpy as np, allo.dataflow as df
from allo.ir.types import float16
import eva as e
sys.modules["eva"]=e
import eva_workloads as wl
GOLD="/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array/mmm"
def f16(h): return np.uint16(h).view(np.float16)
def nrev(g):                       # GOLDEN [op|dst|rs1|rs2] -> OUR [op|dst<<4|s1<<8|s2<<12], per-opcode
    op=(g>>12)&0xF; dst=(g>>8)&0xF; r1=(g>>4)&0xF; r2=g&0xF
    if op in (0x3,0xB):            # MOV/SQRT: golden source=rs2([3:0]); our source=s1
        return op|(dst<<4)|(r2<<8)
    if 0x4<=op<=0x7 or 0xC<=op<=0xF:  # RTR/CRTR: golden src=rs2, cid=rs1 -> our s1=src, s2=id
        return op|(dst<<4)|(r2<<8)|(r1<<12)
    return op|(dst<<4)|(r1<<8)|(r2<<12)   # binary: s1=rs1, s2=rs2
M=N=8
# --- parse golden: prog[i,j,slot] (translated), weights[i,j] ---
IRFD=8
prog=np.zeros((M,N,IRFD),np.int32); NOP=e.OP_MOV|(6<<4)|(6<<8); prog[:]=NOP
W=np.zeros((M,N),np.float16)
for f in sorted(glob.glob(f"{GOLD}/file_col_upp_*.mem")):
    j=int(re.search(r"_(\d+)\.mem",f).group(1))
    for line in open(f):
        m=re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)",line.strip())
        if not m: continue
        i=int(m[1],16); mode=int(m[2],2); addr=int(m[3],16); data=int(m[4],16)
        if mode==1 and 8<=addr<=8+3: prog[i,j,addr-8]=nrev(data)   # IRF instr, translated
        if mode==0 and addr==0:      W[i,j]=f16(data)              # weight -> drf[0]
# --- chip params: 8x8, kernel=4 instrs, 2 iterations (2 activations) ---
e.M,e.N=M,N; e.IRF_DEPTH=IRFD; e.DATADRIVEN=1
per_node=IRFD+1+2; pc=M*per_node+M+8; e.NSTEP=pc+int(os.environ.get("MARGIN","80")); e.LANELEN=e.NSTEP  # scoreboard family needs MARGIN>=1200 (deep ring + credit drain)
L=e.LANELEN
rin_s=wl.load_prog_packets(prog,M,N,data=[(0,W)],cfg=(4,2,0))   # klen=4,iter=2,sync=0
# --- activations: mmm_inputs, 2 per row, injected from WEST at t=pc,pc+1 ---
mi=[0x38A4,0x392D,0x374D,0x3BF2,0x3AB8,0x3A93,0x3B8F,0x348E,0x3796,0x362C,0x3950,0x3959,0x2BC4,0x25C7,0x399D,0x3763]
zi=lambda *s:np.zeros(s,np.int32); zf=lambda *s:np.zeros(s,np.float16)
ins=[zf(M,L),zf(M,L),zf(N,L),zf(N,L)]; outs=[zf(M,L),zf(M,L),zf(N,L),zf(N,L)]
rins=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]; routs=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
ivw=zi(M,L)
for i in range(M):
    ins[0][i,pc]=f16(mi[2*i]);   ivw[i,pc]=1
    ins[0][i,pc+1]=f16(mi[2*i+1]); ivw[i,pc+1]=1
rins[3]=rin_s
print(f"building 8x8 Allo chip (NSTEP={e.NSTEP}) ... this is slow"); sys.stdout.flush()
mod=df.build(e.get_eva_top(float16),target='simulator')
e.run_eva(mod, ins,[ivw,zi(M,L),zi(N,L),zi(N,L)], outs, rins, routs)
out_s=outs[3]
# --- golden reference ---
gold={}
for line in open("/home/zsm9/eva_tb_logs/pe_array_mmm.out"):
    m=re.search(r"sys_tx_btm_data\[(\d)\] = ([0-9a-f]+)",line)
    if m: gold.setdefault(int(m[1]),[]).append(int(m[2],16))
print("\ncol | t | Allo out_s(hex) | golden(hex) | match")
ok=0;tot=0
for j in range(N):
    for t in range(2):
        ah=int(np.float16(out_s[j,t]).view(np.uint16)); gh=gold[j][t]
        mt=(ah==gh); ok+=mt; tot+=1
        print(f" {j}  | {t} |      {ah:04x}       |    {gh:04x}     | {'OK' if mt else 'x'}")
print(f"\nAllo-vs-GOLDEN: {ok}/{tot} bit-exact")
