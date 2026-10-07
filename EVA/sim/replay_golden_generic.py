# Generic golden-vector cross-check: replay any EVA_untouched pe_array workload
# (program from file_col_upp_*.mem + hardcoded TB inputs) through our Allo eva.py
# 8x8 chip and diff vs the captured golden RTL outputs (eva_tb_logs/pe_array_*.out).
import os, sys, re, glob
os.environ.setdefault("OMP_NUM_THREADS","256")
HERE=os.path.dirname(os.path.abspath(__file__)); sys.path.insert(0, os.path.join(HERE,".."))
import numpy as np, allo.dataflow as df
from allo.ir.types import float16
import eva as e
sys.modules["eva"]=e
import eva_workloads as wl
f16=lambda h: np.uint16(h).view(np.float16)
def nrev(g):
    op=(g>>12)&0xF; dst=(g>>8)&0xF; r1=(g>>4)&0xF; r2=g&0xF
    if op in (0x3,0xB):              return op|(dst<<4)|(r2<<8)
    if 0x4<=op<=0x7 or 0xC<=op<=0xF: return op|(dst<<4)|(r2<<8)|(r1<<12)
    return op|(dst<<4)|(r1<<8)|(r2<<12)
# ins order [in_w,in_e,in_n,in_s]; outs [out_w,out_e,out_n,out_s]; golden edge->index
IN_EDGE ={'lft':0,'rgt':1,'top':2,'btm':3}; OUT_EDGE={'lft':0,'rgt':1,'top':2,'btm':3}

def replay(name, gold_dir, tb, in_edge, per_row, out_edge, out_sig, goldout, ncol=8, margin=int(os.environ.get("MARGIN","140")), stride=1):  # scoreboard family needs MARGIN>=1200
    M=N=8; IRFD=8
    prog=np.zeros((M,N,IRFD),np.int32); NOP=e.OP_MOV|(6<<4)|(6<<8); prog[:]=NOP
    drf={}; cfg0={}
    for f in sorted(glob.glob(f"{gold_dir}/file_col_upp_*.mem")):
        j=int(re.search(r"_(\d+)\.mem",f).group(1))
        for line in open(f):
            m=re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)",line.strip())
            if not m: continue
            i=int(m[1],16); mode=int(m[2],2); addr=int(m[3],16); data=int(m[4],16)
            if mode==1 and 8<=addr<=15: prog[i,j,addr-8]=nrev(data)
            elif mode==0:               drf.setdefault(addr,np.zeros((M,N),np.float16))[i,j]=f16(data)
            elif mode==1 and addr==0:   cfg0[(i,j)]=(((data>>8)&7)+1, data&0xFF)
    def cfg(i,j):
        klen,sync=cfg0.get((i,j),(8,0)); return (klen,0,sync)     # iter=0 (Inf, golden default)
    e.M,e.N=M,N; e.IRF_DEPTH=IRFD; e.DATADRIVEN=1
    per_node=IRFD+len(drf)+2; pc=M*per_node+M+8; e.NSTEP=pc+margin; e.LANELEN=e.NSTEP; L=e.LANELEN
    rin_s=wl.load_prog_packets(prog,M,N,data=[(a,drf[a]) for a in sorted(drf)],cfg=cfg)
    # inputs from TB
    blk=re.search(r"_inputs\s*=\s*\{(.*?)\};", open(tb).read(), re.S).group(1)
    vals=[int(x,16) for x in re.findall(r"16'h([0-9A-Fa-f]+)", blk)]
    zi=lambda *s:np.zeros(s,np.int32); zf=lambda *s:np.zeros(s,np.float16)
    ins=[zf(M,L),zf(M,L),zf(N,L),zf(N,L)]; outs=[zf(M,L),zf(M,L),zf(N,L),zf(N,L)]
    rins=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]; routs=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
    ivs=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
    ie=IN_EDGE[in_edge]
    for k in range(ncol):
        for t in range(per_row):
            v=vals[per_row*k+t]
            ins[ie][k,pc+t*stride]=f16(v); ivs[ie][k,pc+t*stride]=1
    rins[3]=rin_s
    print(f"[{name}] building 8x8 (NSTEP={e.NSTEP}, drf slots={sorted(drf)})..."); sys.stdout.flush()
    mod=df.build(e.get_eva_top(float16),target='simulator')
    e.run_eva(mod, ins, ivs, outs, rins, routs)
    out=outs[OUT_EDGE[out_edge]]
    gold={}
    for line in open(goldout):
        m=re.search(rf"{out_sig}\[(\d)\] = ([0-9a-f]+)",line)
        if m: gold.setdefault(int(m[1]),[]).append(int(m[2],16))
    ok=tot=0; rows=[]
    for k in range(8):
        g=gold.get(k,[])
        for t in range(len(g)):
            ah=int(np.float16(out[k,t]).view(np.uint16)); gh=g[t]
            mt=(ah==gh); ok+=mt; tot+=1
            rows.append(f" {k} | {t} |  {ah:04x}  |  {gh:04x}  | {'OK' if mt else 'x'}")
    print("idx| t | Allo | gold | ?"); print("\n".join(rows))
    print(f"[{name}] Allo-vs-GOLDEN: {ok}/{tot} bit-exact\n"); return ok,tot

if __name__=="__main__":
  B="/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array"; LOG="/home/zsm9/eva_tb_logs"
  jobs=[("cordic_cr","cordic_circular_rotation","cordic_cr"),
      ("cordic_cv","cordic_circular_vectoring","cordic_cv"),
      ("cordic_hr","cordic_hyperbolic_rotation","cordic_hr"),
      ("cordic_hv","cordic_hyperbolic_vectoring","cordic_hv")]
  tot_ok=tot_all=0
  for short,dirn,logn in jobs:
    o,t=replay(short, f"{B}/{dirn}", f"{B}/{dirn}/tb_pe_array_{dirn}.sv",
               'lft',2,'rgt','sys_tx_rgt_data', f"{LOG}/pe_array_{logn}.out")
    tot_ok+=o; tot_all+=t
  print(f"==== CORDIC TOTAL: {tot_ok}/{tot_all} bit-exact ====")
