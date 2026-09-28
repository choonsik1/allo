# Golden 8x8 pe_array stimulus (mmm|fft), extracted from build_golden_cosim.py.
# Reuses the SAME nrev translation, activation extraction, and captured golden outputs
# that gave the bubble chip 80/80 bit-exact. Returns chip-agnostic stimulus.
import os, re, glob, numpy as np

GB   = "/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array"
GEXP = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/verification/golden/expected"
# WL -> (gold_subdir, in_edge, per_row, out_edge, out_sig, goldout)
CFG = {
 "mmm": ("mmm", "lft", 2, "btm", "sys_tx_btm_data", "pe_array_mmm.out"),
 "fft": ("fft", "lft", 2, "rgt", "sys_tx_rgt_data", "pe_array_fft.out"),
}
IN_IDX  = {"lft":0,"rgt":1,"top":2,"btm":3}
OUT_IDX = {"lft":0,"rgt":1,"top":2,"btm":3}

def nrev(g):
    op=(g>>12)&0xF; dst=(g>>8)&0xF; r1=(g>>4)&0xF; r2=g&0xF
    if op in (0x3,0xB):              return op|(dst<<4)|(r2<<8)
    if 0x4<=op<=0x7 or 0xC<=op<=0xF: return op|(dst<<4)|(r2<<8)|(r1<<12)
    return op|(dst<<4)|(r1<<8)|(r2<<12)

def build_golden_pe_array(chip, wl, f16, WL="mmm", LF=800, REPS=1):
    """Returns dict: rins,ins,ivs,outs(expected),out_edge,pc,gmax,drf. MESH=8."""
    subdir,in_edge,per_row,out_edge,out_sig,goldout = CFG[WL]
    GOLD = f"{GB}/{subdir}"; TBSV = f"{GOLD}/tb_pe_array_{subdir}.sv"; GOUT = f"{GEXP}/{goldout}"
    M=N=8; IRFD=8
    prog=np.zeros((M,N,IRFD),np.int32); NOP=chip.OP_MOV|(6<<4)|(6<<8); prog[:]=NOP
    drf={}; cfg0={}
    for f in sorted(glob.glob(f"{GOLD}/file_col_upp_*.mem")):
        j=int(re.search(r"_(\d+)\.mem",f).group(1))
        for line in open(f):
            m=re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)",line.strip())
            if not m: continue
            i=int(m[1],16); mode=int(m[2],2); addr=int(m[3],16); data=int(m[4],16)
            if   mode==1 and 8<=addr<=15: prog[i,j,addr-8]=nrev(data)
            elif mode==0:                 drf.setdefault(addr,np.zeros((M,N),np.float16))[i,j]=f16(data)
            elif mode==1 and addr==0:     cfg0[(i,j)]=(((data>>8)&7)+1,data&0xFF)
    # iter: mmm has finite (2 batches) -> REPS; fft is iter=Inf (itsz=0)
    def cfg(i,j):
        klen,sync=cfg0.get((i,j),(8,0))
        itr = 0   # Inf for BOTH (matches build_golden_cosim); streamed activations drive count
        return (klen, itr, sync)
    import eva_workloads as wl_mod
    chip.M,chip.N=M,N; chip.IRF_DEPTH=IRFD; chip.DATADRIVEN=1
    chip.NSTEP=chip.LANELEN=LF
    per_node=IRFD+len(drf)+2; pc=M*per_node+M+8
    rin_s=wl_mod.load_prog_packets(prog,M,N,data=[(a,drf[a]) for a in sorted(drf)],cfg=cfg)
    # activations from the golden tb (_inputs block); REPS copies for a steady-state stream
    blk=re.search(r"_inputs\s*=\s*\{(.*?)\};",open(TBSV).read(),re.S).group(1)
    vals=[int(x,16) for x in re.findall(r"16'h([0-9A-Fa-f]+)",blk)]
    zi=lambda *s:np.zeros(s,np.int32); zf=lambda *s:np.zeros(s,np.float16)
    ins=[zf(M,LF),zf(M,LF),zf(N,LF),zf(N,LF)]; ivs=[zi(M,LF) for _ in range(4)]
    rins=[zi(M,LF) for _ in range(4)]; routs=[zi(M,LF) for _ in range(4)]
    ie=IN_IDX[in_edge]
    for b in range(REPS):
        for k in range(N):
            for t in range(per_row):
                slot=pc+b*per_row+t
                if slot<LF:
                    ins[ie][k,slot]=f16(vals[per_row*k+t]); ivs[ie][k,slot]=1
    rins[3]=rin_s
    # golden expected outputs
    gold={}
    for line in open(GOUT):
        m=re.search(rf"{out_sig}\[(\d)\] = ([0-9a-f]+)",line)
        if m: gold.setdefault(int(m[1]),[]).append(int(m[2],16))
    oi=OUT_IDX[out_edge]; outs=[zf(M,LF),zf(M,LF),zf(N,LF),zf(N,LF)]
    GMAX=max((len(gold.get(k,[])) for k in range(N)),default=0)
    for k in range(N):
        seq=gold.get(k,[])
        for r in range(REPS):
            for t,h in enumerate(seq):
                slot=r*len(seq)+t
                if slot<LF: outs[oi][k,slot]=f16(h)
    return dict(rins=rins,ins=ins,ivs=ivs,routs=routs,outs=outs,out_edge=out_edge,
                out_idx=oi,pc=pc,gmax=GMAX*REPS,drf=drf,vals=vals,per_row=per_row)
