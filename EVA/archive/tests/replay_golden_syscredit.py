# Golden cross-check harness. CHIP env selects the final_runs chip:
#   CHIP=eva_prime | eva_sb | eva_sb_syscredit (default). All import from final_runs.
import os, sys, re, glob
os.environ.setdefault("OMP_NUM_THREADS","256")
FR="/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs"
HERE=os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, FR); sys.path.insert(0, os.path.join(HERE,".."))
import numpy as np, allo.dataflow as df
from allo.ir.types import float16
CHIP=os.environ.get("CHIP","eva_sb_syscredit")
e=__import__(CHIP)
# PRIME/DEPTH: use the CHIP FILE's values by default (eva_sb*/=6/8, deadlock-safe);
# only override if the env var is EXPLICITLY set. (eva_prime hardcodes depth, no PRIME knob.)
if os.environ.get("PRIME") and hasattr(e,"PRIME_TOKENS"): e.PRIME_TOKENS=int(os.environ["PRIME"])
if os.environ.get("DEPTH") and hasattr(e,"STREAM_DEPTH"): e.STREAM_DEPTH=int(os.environ["DEPTH"])
sys.modules["eva"]=e                               # eva_workloads imports `eva`
import eva_workloads as wl
f16=lambda h: np.uint16(h).view(np.float16)
def nrev(g):
    op=(g>>12)&0xF; dst=(g>>8)&0xF; r1=(g>>4)&0xF; r2=g&0xF
    if op in (0x3,0xB):              return op|(dst<<4)|(r2<<8)
    if 0x4<=op<=0x7 or 0xC<=op<=0xF: return op|(dst<<4)|(r2<<8)|(r1<<12)
    return op|(dst<<4)|(r1<<8)|(r2<<12)
IN_EDGE={'lft':0,'rgt':1,'top':2,'btm':3}; OUT_EDGE={'lft':0,'rgt':1,'top':2,'btm':3}
def replay(name, gd, tb, in_edge, per_row, out_edge, sig, goldout, ncol=8, margin=260):
    M=N=8; IRFD=8
    prog=np.zeros((M,N,IRFD),np.int32); NOP=e.OP_MOV|(6<<4)|(6<<8); prog[:]=NOP
    drf={}; cfg0={}
    for f in sorted(glob.glob(f"{gd}/file_col_upp_*.mem")):
        j=int(re.search(r"_(\d+)\.mem",f).group(1))
        for line in open(f):
            m=re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)",line.strip())
            if not m: continue
            i=int(m[1],16); mode=int(m[2],2); addr=int(m[3],16); data=int(m[4],16)
            if mode==1 and 8<=addr<=15: prog[i,j,addr-8]=nrev(data)
            elif mode==0:               drf.setdefault(addr,np.zeros((M,N),np.float16))[i,j]=f16(data)
            elif mode==1 and addr==0:   cfg0[(i,j)]=(((data>>8)&7)+1, data&0xFF)
    def cfg(i,j):
        klen,sync=cfg0.get((i,j),(8,0)); return (klen,0,sync)
    e.M,e.N=M,N; e.IRF_DEPTH=IRFD; e.DATADRIVEN=1
    per_node=IRFD+len(drf)+2; pc=M*per_node+M+8; e.NSTEP=pc+margin; e.LANELEN=e.NSTEP; L=e.LANELEN
    rin_s=wl.load_prog_packets(prog,M,N,data=[(a,drf[a]) for a in sorted(drf)],cfg=cfg)
    blk=re.search(r"_inputs\s*=\s*\{(.*?)\};", open(tb).read(), re.S).group(1)
    vals=[int(x,16) for x in re.findall(r"16'h([0-9A-Fa-f]+)", blk)]
    zi=lambda *s:np.zeros(s,np.int32); zf=lambda *s:np.zeros(s,np.float16)
    ins=[zf(M,L),zf(M,L),zf(N,L),zf(N,L)]; outs=[zf(M,L),zf(M,L),zf(N,L),zf(N,L)]
    rins=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]; routs=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]; ivs=[zi(M,L),zi(M,L),zi(N,L),zi(N,L)]
    ie=IN_EDGE[in_edge]
    for k in range(ncol):
        for t in range(per_row):
            ins[ie][k,pc+t]=f16(vals[per_row*k+t]); ivs[ie][k,pc+t]=1
    rins[3]=rin_s
    _pt=getattr(e,"PRIME_TOKENS","fixed"); _sd=getattr(e,"STREAM_DEPTH","8(hardcoded)")
    print(f"[{name}] building 8x8 {CHIP} (NSTEP={e.NSTEP}, PRIME={_pt}/D={_sd}, drf={sorted(drf)})..."); sys.stdout.flush()
    _top = e.get_eva_top_extended if (os.environ.get("EXT") and hasattr(e,"get_eva_top_extended")) else e.get_eva_top   # EXT=1 -> div/sqrt col-0 region (syscredit only)
    mod=df.build(_top(float16),target='simulator')
    e.run_eva(mod, ins, ivs, outs, rins, routs)
    out=outs[OUT_EDGE[out_edge]]
    if os.environ.get("DUMPALL"):
        names=["out_w(LEFT)","out_e(RIGHT)","out_n(TOP)","out_s(BOTTOM)"]
        for oi,nm in enumerate(names):
            arr=outs[oi]; nz=int((np.abs(arr)>0).sum())
            samp=[f"{int(np.float16(arr[a,b]).view(np.uint16)):04x}" for a in range(min(4,arr.shape[0])) for b in range(min(4,arr.shape[1])) if arr[a,b]!=0][:8]
            print(f"  {nm}: {nz} nonzero  sample={samp}")
    gold={}
    for line in open(goldout):
        m=re.search(rf"{sig}\[(\d)\] = ([0-9a-f]+)",line)
        if m: gold.setdefault(int(m[1]),[]).append(int(m[2],16))
    ok=tot=0; det=[]
    for k in range(8):
        for t in range(len(gold.get(k,[]))):
            ah=int(np.float16(out[k,t]).view(np.uint16)); mt=(ah==gold[k][t]); ok+=mt; tot+=1
            det.append(f"  {k}|{t} allo={ah:04x} gold={gold[k][t]:04x} {'OK' if mt else 'x'}")
    if os.environ.get("DETAIL"): print("\n".join(det))
    print(f"[{name}] syscredit-vs-GOLDEN: {ok}/{tot} bit-exact"); return name,ok,tot

B="/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array"; LOG="/home/zsm9/eva_tb_logs"
CORD={"cordic_cr":"cordic_circular_rotation","cordic_cv":"cordic_circular_vectoring",
      "cordic_hr":"cordic_hyperbolic_rotation","cordic_hv":"cordic_hyperbolic_vectoring"}
if __name__=="__main__":
    wl_name=sys.argv[1] if len(sys.argv)>1 else "all"
    marg=int(sys.argv[2]) if len(sys.argv)>2 else 260
    if wl_name in CORD:
        d=CORD[wl_name]
        replay(wl_name,f"{B}/{d}",f"{B}/{d}/tb_pe_array_{d}.sv",'lft',2,'rgt','sys_tx_rgt_data',f"{LOG}/pe_array_{wl_name}.out",margin=marg)
    elif wl_name=="ldl":
        replay("ldl",f"{B}/ldl",f"{B}/ldl/tb_pe_array_ldl.sv",'btm',4,'lft','sys_tx_lft_data',f"{LOG}/pe_array_ldl.out",ncol=4,margin=marg)
    elif wl_name=="fft":
        replay("fft",f"{B}/fft",f"{B}/fft/tb_pe_array_fft.sv",'lft',2,'rgt','sys_tx_rgt_data',f"{LOG}/pe_array_fft.out",margin=marg)
    elif wl_name=="mmm":
        replay("mmm",f"{B}/mmm",f"{B}/mmm/tb_pe_array_mmm.sv",'lft',2,'btm','sys_tx_btm_data',f"{LOG}/pe_array_mmm.out",margin=marg)
