import os, sys
os.environ["LLVM_BUILD_DIR"] = "/home/zsm9/allo_sup/mlir/build_xcel"
sys.path.insert(0, "/home/zsm9/allo_sup")
PRIME = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime"
sys.path.insert(0, PRIME)
import allo.dataflow as df
from allo.ir.types import float16
import eva_sb_syscredit_rtprime as e

M = int(os.environ.get("MESH", "1"))
e.M = e.N = M
e.NSTEP = 64
e.LANELEN = 64
OUTDIR = os.environ.get("OUTDIR", "/work/shared/users/zsm9/eva_systemc")
os.makedirs(OUTDIR, exist_ok=True)

print(f"=== SystemC codegen: {M}x{M} EVA rtprime (scheduled base chip) ===", flush=True)
top = e.get_eva_top(float16)
mod = df.build(top, target="systemc")
code = mod.hls_code
outp = f"{OUTDIR}/eva_systemc_{M}x{M}.cpp"
open(outp, "w").write(code)
print(f"OK: SystemC generated -> {outp}")
print(f"    {len(code)} chars, {code.count(chr(10))+1} lines")
for kw in ["SC_MODULE", "sc_in", "sc_out", "SC_THREAD", "SC_METHOD",
           "sc_fifo", "Connections", "ac_channel", "wait()", "#pragma"]:
    print(f"    {kw:14s}: {code.count(kw)}")
