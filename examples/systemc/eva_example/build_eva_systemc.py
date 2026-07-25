"""Emit + compile + run the EVA (eva_sb_syscredit_rtprime) chip through the Allo
SystemC backend.

Self-contained: the rtprime chip source sits alongside this script, and the
emitted SystemC project is written to ./generated/ (kernel.cpp, csim.sh, ...).

Run from this directory with the SystemC env set (see README.md):
    python build_eva_systemc.py
"""
import os, sys
os.environ.setdefault("OMP_NUM_THREADS", "8")

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)  # eva_sb_syscredit_rtprime.py is alongside this script

import eva_sb_syscredit_rtprime as e
e.M, e.N = 1, 1                 # 1x1 mesh (single PE)
e.NSTEP = 55                    # cycle budget; LANELEN follows
e.LANELEN = e.NSTEP

import allo.dataflow as df
from allo.ir.types import float16

print("allo:", df.__file__)
print(f"config: M=N=1  NSTEP=LANELEN={e.LANELEN}")

PRJ = os.path.join(HERE, "generated")
os.system(f"rm -rf {PRJ}")
mod = df.build(e.get_eva_top(float16), target="systemc", mode="csim", project=PRJ)
print("=== EVA SystemC emit OK ->", PRJ)

kp = os.path.join(PRJ, "kernel.cpp")
if os.path.exists(kp):
    src = open(kp).read()
    print(f"kernel.cpp lines={src.count(chr(10))}  "
          f"SC_MODULEs={src.count('SC_MODULE(')}  AlloFifo={src.count('AlloFifo<')}")
    print("Compile + run:  cd generated && ./csim.sh")
