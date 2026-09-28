import re, glob, os, sys, numpy as np
GB = "/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array"
NSWE = {0:"N",1:"S",2:"W",3:"E"}   # 0=N,1=S,2=W,3=E

def nrev(g):
    op=(g>>12)&0xF; dst=(g>>8)&0xF; r1=(g>>4)&0xF; r2=g&0xF
    if op in (0x3,0xB):              return op|(dst<<4)|(r2<<8)
    if 0x4<=op<=0x7 or 0xC<=op<=0xF: return op|(dst<<4)|(r2<<8)|(r1<<12)
    return op|(dst<<4)|(r1<<8)|(r2<<12)

def src(x):
    if x < 8:  return f"r{x}"
    if x >= 12: return f"IN_{NSWE[x&3]}"      # systolic input from a neighbor dir
    return f"r{x}"
def dstr(d):
    if d < 8:  return f"r{d}"
    if d >= 12: return f"OUT_{NSWE[d&3]}"      # systolic output to a neighbor dir
    return f"r{d}"

def decode(instr):
    op=instr&0xF; dst=(instr>>4)&0xF; s1=(instr>>8)&0xF; s2=(instr>>12)&0xF
    a,b,D = src(s1), src(s2), dstr(dst)
    if op==0x0: return f"{D} = {a} + {b}"
    if op==0x1: return f"{D} = {a} - {b}"
    if op==0x2: return f"{D} = {a} * {b}"
    if op==0x3: return f"{D} = {a}"                       # MOV
    if op==0x8: return f"{D} = ({a} >= {b}) ? 1 : -1"     # GEQ
    if op==0x9: return f"{D} = ({a} <  {b}) ? 1 : -1"     # LT
    if op==0xA: return f"{D} = {a} / {b}"                 # DIV (col0)
    if op==0xB: return f"{D} = sqrt({a})"                 # SQRT (col0)
    if 0x4<=op<=0x7: return f"ROUTE dir={NSWE[op&3]}: send {a} (id {s2})"   # RTR
    if 0xC<=op<=0xF: return f"if(cond) ROUTE dir={NSWE[op&3]}: send {a} (id {s2})"  # CRTR
    return f"?op{op:x} dst={dst} s1={s1} s2={s2}"

def f16(h): return float(np.uint16(h).view(np.float16))

def load(wl):
    prog={}; drf={}
    for f in sorted(glob.glob(f"{GB}/{wl}/file_col_upp_*.mem")):
        j=int(re.search(r"_(\d+)\.mem",f).group(1))
        for line in open(f):
            m=re.match(r"id = ([0-9A-Fa-f]+), mode = ([01]+), addr = ([0-9A-Fa-f]+), data = ([0-9A-Fa-f]+)",line.strip())
            if not m: continue
            i=int(m[1],16); mode=int(m[2],2); addr=int(m[3],16); data=int(m[4],16)
            if mode==1 and 8<=addr<=15: prog.setdefault((i,j),{})[addr-8]=nrev(data)
            elif mode==0:               drf.setdefault((i,j),{})[addr]=f16(data)
    return prog,drf

def report(wl, title, out):
    prog,drf=load(wl)
    pes=sorted(set(prog)|set(drf))
    # group PEs by identical (program, drf-consts) so we print unique templates
    def sig(pe):
        p=tuple(sorted(prog.get(pe,{}).items()))
        d=tuple(sorted((k,round(v,4)) for k,v in drf.get(pe,{}).items()))
        return (p,d)
    seen={}
    for pe in pes:
        seen.setdefault(sig(pe),[]).append(pe)
    out.append(f"\n{'='*70}\n{title}   ({wl})\n{'='*70}")
    out.append(f"PEs with a program: {len(pes)} ; distinct program templates: {len(seen)}")
    for k,(s,grp) in enumerate(sorted(seen.items(), key=lambda kv: kv[1][0])):
        p,d=s
        loc=", ".join(f"({i},{j})" for i,j in grp[:8])+(" ..." if len(grp)>8 else "")
        out.append(f"\n--- template #{k}  used by {len(grp)} PE(s): {loc} ---")
        if d: out.append("  loaded constants: "+", ".join(f"r{r}={v:g}" for r,v in d))
        for slot,instr in p:
            out.append(f"    [{slot}] {decode(instr)}")
        if not p: out.append("    (data only / no program)")

out=[f"EVA golden programs decoded into human-readable EVA-ISA ops.",
     f"Regs r0..r7 = local DRF; IN_x/OUT_x = systolic input/output to neighbor dir x (N/S/W/E).",
     f"ROUTE = router packet send. Each PE runs its short program every activation (systolic dataflow)."]
report("fft","FFT (radix butterflies)",out)
for cv,t in [("cordic_circular_rotation","CORDIC circular rotation (cos/sin)"),
             ("cordic_circular_vectoring","CORDIC circular vectoring (atan/magnitude)"),
             ("cordic_hyperbolic_rotation","CORDIC hyperbolic rotation (cosh/sinh)"),
             ("cordic_hyperbolic_vectoring","CORDIC hyperbolic vectoring (atanh)")]:
    report(cv,t,out)
txt="\n".join(out)
open("EVA_fft_cordic_programs.txt","w").write(txt)
print(txt)
