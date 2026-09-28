# Shared: build the golden pe_group 2x2 mmm stimulus (nrev-translated program + weights + activations).
# Returns (rin_s, in_w_activations_row0, row1, golden_out) — chip-agnostic.
import os,sys,re,glob,numpy as np
def build_golden_pegroup(chip, wl, f16, REPS=1):
    GOLD="/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_group/mmm"
    M=N=2; IRFD=8
    def nrev(g):
        op=(g>>12)&0xF; dst=(g>>8)&0xF; r1=(g>>4)&0xF; r2=g&0xF
        if op in (0x3,0xB):              return op|(dst<<4)|(r2<<8)
        if 0x4<=op<=0x7 or 0xC<=op<=0xF: return op|(dst<<4)|(r2<<8)|(r1<<12)
        return op|(dst<<4)|(r1<<8)|(r2<<12)
    prog=np.zeros((M,N,IRFD),np.int32); NOP=chip.OP_MOV|(6<<4)|(6<<8); prog[:]=NOP
    drf={}; cfg0={}
    files=sorted(glob.glob(f"{GOLD}/file_col_upp_*.mem"))     # _2, _3
    for jj,f in enumerate(files):                            # remap col 2,3 -> 0,1
        for line in open(f):
            m=re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)",line.strip())
            if not m: continue
            i=int(m[1],16); mode=int(m[2],2); addr=int(m[3],16); data=int(m[4],16)
            if   mode==1 and 8<=addr<=15: prog[i,jj,addr-8]=nrev(data)
            elif mode==0:                 drf.setdefault(addr,np.zeros((M,N),np.float16))[i,jj]=f16(data)
            elif mode==1 and addr==0:     cfg0[(i,jj)]=(((data>>8)&7)+1,data&0xFF)
    def cfg(i,j):
        klen,sync=cfg0.get((i,j),(4,0))
        import os as _o; it=int(_o.environ.get('ITER',str(2*REPS)))
        return (klen,it,sync)
    print(f"  [golden-pg] weights drf={sorted(drf)}: W={drf.get(0).tolist() if 0 in drf else '?'}")
    rin_s=wl.load_prog_packets(prog,M,N,data=[(a,drf[a]) for a in sorted(drf)],cfg=cfg)
    # activations from the golden pe_group tb: row0(sys_rx_lft_0)=[2,6], row1(lft_2)=[4,8]
    act={0:[2.0,6.0]*REPS, 1:[4.0,8.0]*REPS}   # row -> 2*REPS batches (golden workload repeated)
    golden={0:[0x4d80,0x51c0]*REPS, 1:[0x5040,0x54a0]*REPS}  # [22,46]/[34,74] repeated
    return rin_s, act, golden, drf
