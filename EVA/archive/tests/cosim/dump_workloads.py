# Dump RTL-cosim replay vectors for the eva_workloads MMM variants, run
# against eva. Same run_eva interception as dump_vectors.py, plus the
# workload-specific chip params (IRF_DEPTH, DATADRIVEN) that the loaders
# mutate — run_suite.py must rebuild the kernel with the same values.
# Run:  cd Allo/EVA/tests/cosim && python dump_workloads.py    (allo conda env)
import os, sys
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))  # Allo/EVA -> eva.py (the primed design)
sys.path.insert(0, os.path.join(HERE, ".."))        # Allo/EVA/tests -> eva_tests / eva_workloads
import eva
import eva_workloads as WL

orig_run = eva.run_eva
state = {"name": "?"}

def dumping_run(mod, ins, ivs, outs, rins, routs):
    snap = {f"{p}{i}": a.copy() for p, arrs in
            (("in", ins), ("iv", ivs), ("rin", rins)) for i, a in enumerate(arrs)}
    orig_run(mod, ins, ivs, outs, rins, routs)
    snap.update({f"{p}{i}": a.copy() for p, arrs in
                 (("out", outs), ("rout", routs)) for i, a in enumerate(arrs)})
    fn = os.path.join(HERE, f"vec_{state['name']}_0.npz")
    np.savez(fn, M=eva.M, N=eva.N, NSTEP=eva.NSTEP,
             IRF=eva.IRF_DEPTH, DD=eva.DATADRIVEN, **snap)
    print(f"  dumped {os.path.basename(fn)}  (M={eva.M} N={eva.N} "
          f"NSTEP={eva.NSTEP} IRF={eva.IRF_DEPTH})")

eva.run_eva = dumping_run

W = np.array([[1, 3], [5, 7]], np.float16)          # golden EVA MMM values
b16 = lambda h: np.uint16(h).view(np.float16)
x2 = np.array([b16(0x2617) + 1j * b16(0x2AF7),      # golden EVA fft2 inputs
               b16(0x26A3) + 1j * b16(0x25FF)], np.complex64)
rng = np.random.default_rng(8)                       # same seed as __main__
x8 = (rng.uniform(-1, 1, 8) + 1j * rng.uniform(-1, 1, 8)).astype(np.complex64)
LOADERS = [
    ("mmmr",  lambda: WL.load_mmm_router(W, np.array([[2, 4]], np.float16))),
    ("fft2r", lambda: WL.load_fft2_router(x2)),
    ("fft8r", lambda: WL.load_fft8_router(x8)),
]
flt = sys.argv[1] if len(sys.argv) > 1 else ""
LOADERS = [(n, mk) for n, mk in LOADERS if flt in n]
for name, mk in LOADERS:
    state["name"] = name
    print(f"== {name} ==")
    ok, report = WL.run(mk())
    print(report.splitlines()[-1], "-> vectors only valid if PASS")
