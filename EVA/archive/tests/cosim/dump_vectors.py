# Dump RTL-cosim replay vectors for every eva_tests test, run against
# eva.py (the END-PUT primed design). e.run_eva is wrapped to snapshot the
# inputs BEFORE the Allo-simulator run and the outputs AFTER it; each chip
# invocation becomes one vec_<test>_<k>.npz with M/N/NSTEP + all 20 arrays.
# Run:  cd Allo/EVA/tests/cosim && python dump_vectors.py    (allo conda env)
import os, sys
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))  # Allo/EVA -> eva.py (the primed design)
sys.path.insert(0, os.path.join(HERE, ".."))        # Allo/EVA/tests -> eva_tests / eva_workloads
import eva
import eva_tests as T

orig_run = eva.run_eva
state = {"name": "?", "k": 0}

def dumping_run(mod, ins, ivs, outs, rins, routs):
    snap = {f"{p}{i}": a.copy() for p, arrs in
            (("in", ins), ("iv", ivs), ("rin", rins)) for i, a in enumerate(arrs)}
    orig_run(mod, ins, ivs, outs, rins, routs)      # the real simulator run
    snap.update({f"{p}{i}": a.copy() for p, arrs in
                 (("out", outs), ("rout", routs)) for i, a in enumerate(arrs)})
    fn = os.path.join(HERE, f"vec_{state['name']}_{state['k']}.npz")
    np.savez(fn, M=eva.M, N=eva.N, NSTEP=eva.NSTEP, **snap)
    print(f"  dumped {os.path.basename(fn)}  (M={eva.M} N={eva.N} "
          f"NSTEP={eva.NSTEP})")
    state["k"] += 1

eva.run_eva = dumping_run

TESTS = [("passthrough", T.test_passthrough), ("row", T.test_row),
         ("router", T.test_router), ("core_send", T.test_core_send),
         ("turn", T.test_turn), ("shuffle", T.test_shuffle),
         ("mesh", T.test_mesh)]
for name, fn in TESTS:
    state["name"], state["k"] = name, 0
    print(f"== {name} ==")
    ok = fn()
    print(f"   sim {'PASS' if ok else 'FAIL'} (vectors only valid if PASS)")
