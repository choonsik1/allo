# Run the eva_tests.py suite against EVA/eva_prime.py (END-PUT primed variant)
# by aliasing module name eva -> eva_prime before anything imports it.
#
# NOTE 2026-07-06: EVA/eva.py IS now the primed version (eva_prime.py was
# copied over it), so `python eva_tests.py` tests the same design and this
# wrapper is only useful while eva_prime.py still exists as a separate file.
import os, sys, runpy
HERE = os.path.dirname(os.path.abspath(__file__))
EVA  = os.path.join(HERE, "..")
sys.path.insert(0, EVA)
sys.path.insert(0, HERE)
import eva_prime
sys.modules["eva"] = eva_prime
runpy.run_path(os.path.join(HERE, "eva_tests.py"), run_name="__main__")
