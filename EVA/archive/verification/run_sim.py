# Sim-level functional verification for a final_runs chip (Allo simulator).
# Runs the canonical eva_tests suite (7 tests). Usage:
#   LLVM_BUILD_DIR=/home/zsm9/miniconda3/envs/allo \
#   python run_sim.py {eva|eva_sb|eva_sb_syscredit}
# Aliases module 'eva' -> the chosen chip; the chip's module-level params
# (M=N=1, NSTEP=10) are overridden per-test by eva_tests._dims as usual.
import os, sys, runpy
HERE = os.path.dirname(os.path.abspath(__file__))                   # verification/
FR  = os.path.dirname(HERE)                                         # parent (Allo/EVA) — chips live here
LOCAL_TESTS = os.path.join(HERE, "eva_tests.py")                    # the LOCAL copy in this folder
chip = sys.argv[1] if len(sys.argv) > 1 else "eva"
sys.path.insert(0, FR)                       # the chip .py lives here (parent dir)
sys.path.insert(0, HERE)                     # eva_workloads.py / eva_tests.py live here
mod = __import__(chip)
sys.modules["eva"] = mod
print("== sim tests vs %s ==" % chip)
# strip the chip arg so eva_tests' __main__ doesn't read it as a test-name filter;
# any args AFTER the chip pass through (e.g. `run_sim.py eva turn router`).
sys.argv = [LOCAL_TESTS] + sys.argv[2:]
runpy.run_path(LOCAL_TESTS, run_name="__main__")
