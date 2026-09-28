# Cosim the whole eva_tests suite: for each vec_*.npz (see dump_vectors.py)
# emit vectors_<vec>.h, generate the Allo kernel for that (M,N,NSTEP) config
# (cached per config, union-patched for g++), write a flat tcl, run
# vitis_hls csynth+cosim, and report the verdict per vector set.
# Run:  cd Allo/EVA/tests/cosim && python run_suite.py [name-filter]
import glob, os, re, subprocess, sys
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
VITIS = "/opt/xilinx/Vitis_HLS/2023.2/bin/vitis_hls"
sys.path.insert(0, os.path.join(HERE, "..", ".."))  # Allo/EVA -> eva.py
import eva as e
from allo.ir.types import float16

def c_arr(name, a, fmt):
    rows = [", ".join(fmt % v for v in row) for row in a]
    body = "},\n  {".join(rows)
    return "static const %s[%d][%d] = {\n  {%s}\n};\n" % (name, a.shape[0], a.shape[1], body)

def write_header(vec, d):
    M, N, L = int(d["M"]), int(d["N"]), int(d["NSTEP"])
    s = ["#define VM %d\n#define VN %d\n#define VL %d\n" % (M, N, L),
         '#define VECNAME "%s"\n' % vec]
    for i in range(4):
        s.append(c_arr("unsigned short IN%d" % i, d["in%d" % i].view(np.uint16), "0x%04x"))
        s.append(c_arr("int32_t IV%d" % i, d["iv%d" % i], "%d"))
        s.append(c_arr("int32_t RIN%d" % i, d["rin%d" % i], "%d"))
        s.append(c_arr("unsigned short EOUT%d" % i, d["out%d" % i].view(np.uint16), "0x%04x"))
        s.append(c_arr("int32_t EROUT%d" % i, d["rout%d" % i], "%d"))
    open(os.path.join(HERE, "vectors_%s.h" % vec), "w").write("".join(s))
    return M, N, L

def gen_kernel(M, N, L, IRF=8, DD=1):
    prj = os.path.join(HERE, "allo_prj_%dx%d_L%d_I%d_D%d" % (M, N, L, IRF, DD))
    if os.path.exists(os.path.join(prj, "kernel.cpp")):
        return prj
    e.M, e.N, e.NSTEP, e.LANELEN = M, N, L, L
    e.IRF_DEPTH, e.DATADRIVEN = IRF, DD
    s = e.get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)
    s.build(target="vhls", mode="csyn", project=prj)
    kp = os.path.join(prj, "kernel.cpp")             # union-ctor patch (g++)
    src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);",
                 r"\1 = {};", open(kp).read())
    open(kp, "w").write(src)
    return prj

TCL = """open_project prj_%s -reset
set_top top
add_files %s/kernel.cpp -cflags "-DALLOW_EMPTY_HLS_STREAM_READS"
add_files -tb tb_replay.cpp -cflags {-I. -DALLOW_EMPTY_HLS_STREAM_READS -DVECHDR="vectors_%s.h"}
open_solution "solution1"
config_compile -pipeline_loops 0
set_part {xcu280-fsvh2892-2L-e}
create_clock -period 3.33
csynth_design
cosim_design
exit
"""

flt = sys.argv[1] if len(sys.argv) > 1 else ""
results = []
for f in sorted(glob.glob(os.path.join(HERE, "vec_*.npz"))):
    vec = os.path.basename(f)[4:-4]
    if flt and flt not in vec:
        continue
    d = np.load(f)
    M, N, L = write_header(vec, d)
    IRF = int(d["IRF"]) if "IRF" in d else 8      # older dumps: suite defaults
    DD  = int(d["DD"])  if "DD"  in d else 1
    prj = gen_kernel(M, N, L, IRF, DD)
    open(os.path.join(HERE, "run_%s.tcl" % vec), "w").write(
        TCL % (vec, os.path.basename(prj), vec))
    print("== %s (%dx%d L%d) ==" % (vec, M, N, L), flush=True)
    log = subprocess.run([VITIS, "-f", "run_%s.tcl" % vec], cwd=HERE,
                         capture_output=True, text=True).stdout
    open(os.path.join(HERE, "log_%s.txt" % vec), "w").write(log)
    m = re.findall(r"(PASS|FAIL): replay", log)
    ok = "co-simulation finished: PASS" in log and (m and m[-1] == "PASS")
    dl = "DEADLOCK" in log
    results.append((vec, "PASS" if ok else ("DEADLOCK" if dl else "FAIL")))
    print("   %s" % results[-1][1], flush=True)

print("\nSUMMARY"); [print("  %-16s %s" % r) for r in results]
