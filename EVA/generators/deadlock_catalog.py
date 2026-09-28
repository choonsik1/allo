# deadlock_catalog.py — run EVERY EVA variant through Allo-sim mmm (K=2) and record the
# exact outcome (PASS / all-zero / computes-0 / DEADLOCK + the stuck FIFO). Builds the
# empirical justification table for DESIGN_RATIONALE.md §4. Allo-sim only (seconds/chip).
#
#   PYTHONPATH=/home/zsm9/allo python deadlock_catalog.py [K] [L]
import os, sys, importlib, traceback
os.environ["LLVM_BUILD_DIR"] = "/home/zsm9/miniconda3/envs/allo"
sys.path.insert(0, "/home/zsm9/allo")
import numpy as np
PRIME = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final/final_final/prime"
FINAL = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/scoreboard_allo_eva_final"
TESTS = "/home/zsm9/pe_core_implementation/Allo/EVA/archive/tests"
for p in (PRIME, FINAL, TESTS): sys.path.insert(0, p)
import allo.dataflow as df
from allo.ir.types import float16
import eva_workloads as WL

K = int(sys.argv[1]) if len(sys.argv) > 1 else 2
L = int(sys.argv[2]) if len(sys.argv) > 2 else 200

# (module, label). n_out handling is auto-detected via TypeError fallback.
CHIPS = [
    ("eva_sb_syscredit_rtprime",         "rtprime (FINAL: always-fire + credit)"),
    ("eva_sb_syscredit_rtprime_wbfwd",   "wbfwd (honest II=1, FWD=0)"),
    ("eva_sb_syscredit_rtprime_no_cred", "no_cred (strip systolic credit, always-fire)"),
    ("eva_sb_syscredit_rtprime_guarded", "guarded (demand systolic read)"),
    ("eva_sb_syscredit_rtprime_demand",  "demand (demand read + real-only send)"),
    ("eva_sb_syscredit_rtprime_demand2", "demand2 (+ n_in bounds)"),
    ("eva_sb_syscredit_rtprime_demand3", "demand3 (read after decode)"),
    ("eva_sb_syscredit_rtprime_elastic", "elastic (full/empty guards)"),
    ("eva_sb_syscredit_rtprime_elastic2","elastic2"),
    ("eva_sb_nb",                        "eva_sb_nb (full non-blocking try_get/try_put)"),
]

def pad(a):
    a = np.asarray(a); n = np.zeros((a.shape[0], L), a.dtype); n[:, :a.shape[1]] = a; return n

def make_args(args, sig):
    pcfg = np.full((K, K), 6, np.int32)
    iw, ie, in_, is_ = args["ins"]; vw, ve, vn, vs = args["ivs"]
    ow, oe, on, os_ = args["outs"]
    z  = np.zeros(K, np.int32)
    kk = np.full(K, K, np.int32)                  # per-lane count = K
    R  = (*args["rins"], *args["routs"])
    if sig == "std":       # 21 args: pcfg + in/iv x4 + out x4 + rin/rout
        return (pcfg, iw, vw, ie, ve, in_, vn, is_, vs, ow, oe, on, os_, *R)
    if sig == "nout":      # 25: + n_out on collectors (demand)
        return (pcfg, iw, vw, ie, ve, in_, vn, is_, vs,
                ow, z, oe, z, on, z, os_, kk, *R)
    if sig == "ninnout":   # 29: + n_in on drivers + n_out on collectors (demand2/3)
        return (pcfg, iw, vw, kk, ie, ve, z, in_, vn, kk, is_, vs, z,
                ow, z, oe, z, on, z, os_, kk, *R)
    if sig == "noprime":   # 20: no prime_cfg (eva_sb_nb)
        return (iw, vw, ie, ve, in_, vn, is_, vs, ow, oe, on, os_, *R)

def run(modname):
    e = importlib.import_module(modname); sys.modules["eva"] = e
    importlib.reload(WL)
    e.M = e.N = K; e.NSTEP = e.LANELEN = L
    mod = df.build(e.get_eva_top(float16), target="simulator")
    W = np.ones((K, K), np.float16); X = np.ones((K, K), np.float16)
    args, _ = WL.load_mmm_router(W, X)
    for key in ("ins", "ivs", "outs", "rins", "routs"):
        args[key] = [pad(x) for x in args[key]]
    gold = float(np.float16(K))
    import re
    for sig in ("std", "nout", "ninnout", "noprime"):   # try each until arg-count matches
        for a in args["outs"]: a[:] = 0
        try:
            mod(*make_args(args, sig))
        except AssertionError as ae:
            if "input arguments mismatch" in str(ae): continue     # wrong sig -> try next
            return "ERROR", f"AssertionError: {str(ae)[:60]}"
        except Exception as ex:
            if "Deadlock" in type(ex).__name__:
                m = re.search(r"stream '([^']+)'", str(ex))
                return "DEADLOCK", f"circular wait, stuck FIFO {m.group(1) if m else '?'}"
            return "ERROR", f"{type(ex).__name__}: {str(ex)[:60]}"
        out_s = np.asarray(args["outs"][3])
        hits = int(np.sum(np.isclose(out_s.astype(np.float32), gold, atol=1e-2)))
        nz = int((out_s != 0).sum())
        tag = f" [sig={sig}]"
        if hits >= K * K: return "PASS", f"{hits}/{K*K} correct{tag}"
        if nz == 0:       return "ALL-ZERO", f"drained nothing (buffer drop / wrong emission){tag}"
        return "COMPUTES-WRONG", f"{hits}/{K*K} correct, nz={nz}{tag}"
    return "SIG-MISMATCH", "no known signature matched"

print(f"=== EVA deadlock catalog  (Allo-sim, mmm ones, K={K}, L={L}) ===\n", flush=True)
print(f"{'variant':<46} {'verdict':<16} detail")
print("-" * 100)
for mod, label in CHIPS:
    try:
        v, d = run(mod)
    except Exception as ex:
        v, d = "BUILD-FAIL", f"{type(ex).__name__}: {str(ex)[:50]}"
    print(f"{label:<46} {v:<16} {d}", flush=True)
