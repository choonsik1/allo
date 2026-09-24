import os, sys
os.environ.setdefault("OMP_NUM_THREADS", "8")
os.environ["MGC_HOME"] = "/opt/siemens/catapult/2024.2/Mgc_home"
os.environ["PATH"] = f"{os.environ['MGC_HOME']}/bin:" + os.environ.get("PATH", "")
sys.path.insert(0, "/home/zsm9/allo_sup")
HERE = "/home/zsm9/allo_sup/examples/systemc/eva_example"
sys.path.insert(0, HERE)

import eva_sb_syscredit_rtprime as e
e.M, e.N = 1, 1
e.NSTEP = 55
e.LANELEN = e.NSTEP

import allo.dataflow as df
from allo.ir.types import float16

MODE = os.environ.get("SCMODE", "csyn")
PRJ = f"/work/shared/users/zsm9/eva_systemc_{MODE}"
os.system(f"rm -rf {PRJ}")
print(f"=== EVA SystemC target, mode={MODE}, 1x1 (Catapult HLS) ===", flush=True)
mod = df.build(e.get_eva_top(float16), target="systemc", mode=MODE, project=PRJ)
print(f"emitted -> {PRJ}; running Catapult ...", flush=True)
mod()
print(f"=== DONE mode={MODE} -> {PRJ} ===")
