# Run the eva_tests.py suite against eva_prime_sb.py (SCOREBOARD variant)
# without modifying the originals: alias module name eva -> eva_prime_sb.
import os, sys, runpy
HERE = os.path.dirname(os.path.abspath(__file__))
EVA = "/home/zsm9/pe_core_implementation/Allo/EVA"
sys.path.insert(0, HERE)
sys.path.insert(1, EVA)
import eva_sb
sys.modules["eva"] = eva_sb
sys.path.insert(2, os.path.join(EVA, "tests"))  # eva_tests/eva_workloads moved 2026-07-06
runpy.run_path(os.path.join(EVA, "tests", "eva_tests.py"), run_name="__main__")
