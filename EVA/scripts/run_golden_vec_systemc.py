#!/usr/bin/env python3
# Run a VERIFICATION-FOLDER chip (elastic / skid) on the SHIPPED GOLDEN EVA VECTORS,
# through the Allo SystemC backend + Catapult.
#
# WHY: `run_golden_systemc.py` gives v16/v3.0 real golden-EVA verification (programs from
# file_col_upp_*.mem, inputs from the golden tb .sv, outputs diffed against captured golden
# RTL logs). The elastic/skid chips had only a SYNTHETIC numpy-MMM check — not comparable.
# This closes that gap using the pre-encoded vectors in
#   /work/shared/users/zsm9/verification/vectors/Allo/<chip>/<workload>/<workload>.h
# whose EOUT "equals the RTL EVA output bit-for-bit" (see that folder's README).
#
#   CHIP=eva_fp16_elastic VEC=fp16_elastic WL=fft MODE=csim PRJ=/scratch/... \
#     python scripts/run_golden_vec_systemc.py
import os, re, sys, glob, importlib
import numpy as np

os.environ.setdefault("OMP_NUM_THREADS", "8")
os.environ.setdefault("MGC_HOME", "/opt/siemens/catapult/2024.2/Mgc_home")
MGC = os.environ["MGC_HOME"]
os.environ["PATH"] = f"{MGC}/bin:" + os.environ.get("PATH", "")
os.environ.setdefault("SYSTEMC_HOME", f"{MGC}/shared")
os.environ["LD_LIBRARY_PATH"] = f"{MGC}/lib:{MGC}/shared/lib:" + os.environ.get("LD_LIBRARY_PATH", "")
os.environ.setdefault("ALLO_COSIM_SYNTH_TIMEOUT", "54000")
os.environ.setdefault("ALLO_COSIM_SIM_TIMEOUT", "14400")

HERE = os.path.dirname(os.path.abspath(__file__)); ROOT = os.path.dirname(HERE)
sys.path.insert(0, "/home/zsm9/allo_sup")
sys.path.insert(0, os.path.join(ROOT, "chip"))
sys.path.insert(0, os.path.join(ROOT, "designs", "from_verification"))

VECROOT = os.environ.get("VECROOT", "/work/shared/users/zsm9/verification/vectors/Allo")
CHIP = os.environ.get("CHIP", "eva_fp16_elastic")
VEC  = os.environ.get("VEC",  "fp16_elastic")
WL   = os.environ.get("WL",   "fft")
MODE = os.environ.get("MODE", "csim")
PRJ  = os.environ["PRJ"]
# DTYPE: the driver was fp16-only (top arg, array dtypes, and the bit-compare all
# hardcoded float16). The int16 chips need the SAME bit-reinterpret path with int16 as
# the storage type -- vectors are hex words either way, so only the view type changes.
H = os.path.join(VECROOT, VEC, WL, f"{WL}.h")
assert os.path.exists(H), f"no vector header: {H}"

src = open(H).read()

# ---- DTYPE comes from the VECTOR HEADER, not from the chip name. -------------------
# TRAP (hit 2026-08-21): `int16_elastic/fft` holds the *fp16* golden vectors -- the real
# int16 ones live under the `_i16` suffix (`fft_i16`, `mmm_i16`, `cordic_*_i16`), while
# `int16_skid` uses the PLAIN names for int16. Running the int16 chip against the fp16
# vectors gives 16/16 mismatches that look like a broken chip and are not.
# Every vector header self-describes via `#define VECTOR_DTYPE`; absent => fp16.
_m = re.search(r'^#define\s+VECTOR_DTYPE\s+"([a-z0-9]+)"', src, re.M)
_vec_dt = "fp16" if not _m else ("fp16" if _m.group(1) in ("fp16", "float16") else "int16")
_chip_dt = "int16" if ("int16" in CHIP) else "fp16"
DTYPE = os.environ.get("DTYPE", _vec_dt)
assert DTYPE in ("fp16", "int16"), DTYPE
if _vec_dt != _chip_dt:
    sys.exit(f"DTYPE MISMATCH: chip {CHIP} is {_chip_dt} but vectors {VEC}/{WL} are "
             f"{_vec_dt}.\n  -> for int16_elastic use the _i16 workloads "
             f"(fft_i16, mmm_i16, cordic_*_i16); int16_skid uses the plain names.")
print(f"[dtype] vectors={_vec_dt} chip={_chip_dt} -> using {DTYPE}", flush=True)
def defint(name, default=None):
    m = re.search(rf"^#define\s+{name}\s+(-?\d+)", src, re.M)
    if m: return int(m.group(1))
    if default is None: raise KeyError(name)
    return default
VM, VN, VL = defint("VM"), defint("VN"), defint("VL")
VPC, VOUT  = defint("VPC"), defint("VOUT_IDX")
VPRIME     = defint("VECTOR_PRIME", 0)          # skid only

def arr(name):
    """Parse `static const <ty> NAME[R][C] = { {..}, .. };` into an (R,C) int array."""
    m = re.search(rf"static const [a-z0-9_ ]+{name}\[(\d+)\]\[(\d+)\]\s*=\s*\{{(.*?)\n\}};",
                  src, re.S)
    if not m: return None
    R, C, body = int(m.group(1)), int(m.group(2)), m.group(3)
    rows = re.findall(r"\{([^{}]*)\}", body)
    assert len(rows) == R, f"{name}: {len(rows)} rows, expected {R}"
    out = np.zeros((R, C), np.int64)
    for i, r in enumerate(rows):
        vals = [int(v, 0) for v in re.findall(r"-?(?:0[xX][0-9a-fA-F]+|\d+)", r)]
        # C99 partial initializers are legal and several headers use them (fp16_skid/fft
        # gives 800 of a declared 2000 per row); the unwritten tail is zero by the
        # standard, so pad rather than assert. A SHORT row is normal; an OVERLONG one
        # means the parse actually went wrong, so that stays fatal.
        assert len(vals) <= C, f"{name} row {i}: {len(vals)} vals, declared {C} -- parse error"
        if len(vals) < C and i == 0:
            print(f"  [vectors] {name}: partial initializer, {len(vals)}/{C} per row, "
                  f"zero-padding the tail (C99 semantics)", flush=True)
        out[i, :len(vals)] = vals
    return out

_NP = np.float16 if DTYPE == "fp16" else np.int16
f16 = lambda u: np.asarray(u, np.uint16).view(_NP)
INS  = [f16(arr(f"IN{i}"))  for i in range(4)]
IVS  = [arr(f"IV{i}").astype(np.int32)  for i in range(4)]
RINS = [arr(f"RIN{i}").astype(np.int32) for i in range(4)]
EOUT = [arr(f"EOUT{i}") for i in range(4)]
PRIMECFG = arr("PRIMECFG")

e = importlib.import_module(CHIP); sys.modules["eva"] = e
import allo.dataflow as df
from allo.ir.types import float16, int16
_ALLO = float16 if DTYPE == "fp16" else int16
e.M, e.N = VM, VN
e.NSTEP = e.LANELEN = VL
if hasattr(e, "RUN_BUDGET"):
    e.RUN_BUDGET = int(os.environ.get("BUDGET", str(6 * VL)))
_bud = getattr(e, "RUN_BUDGET", None)
print(f"=== GOLDEN VECTORS  chip={CHIP}  vec={VEC}/{WL}  {VM}x{VN}  VL={VL}  VPC={VPC}  "
      f"OUT_IDX={VOUT}  PRIME={VPRIME}  BUDGET={_bud}  MODE={MODE} ===", flush=True)

# REPLAY=1 reuses an ALREADY-BUILT cosim project: rewrite input*.data, re-run ncsim,
# read output*.data back. EVA is programmable (one_bitstream), so a second workload needs
# no rebuild -- ~1 min instead of ~5 h. replay_cosim.py cannot be used here because it
# assumes OUR port layout (leading prime_cfg); elastic has none.
REPLAY = os.environ.get("REPLAY", "0") == "1"
if not REPLAY:
    os.system(f"rm -rf {PRJ}")
top = e.get_eva_top_elastic(_ALLO) if hasattr(e, "get_eva_top_elastic") else e.get_eva_top(_ALLO)
if not REPLAY:
    mod = df.build(top, target="systemc", mode=("csim" if MODE == "csim" else MODE), project=PRJ)
    print(f"emitted -> {PRJ}; running {MODE} ...", flush=True)

# --- CYCLE COUNT ------------------------------------------------------------------
# The emitted testbench already single-steps a 1 ns clock until the DUT raises
# `done_sig`, so its loop counter IS the cycle count to completion -- the emitter just
# never prints it. Hoist `_c` out of the for-scope and dump it to cycles.txt (a FILE,
# not stdout: `./sim` runs with PRJ as cwd and hls.py swallows its stdout).
#
# ⚠️ This is the SystemC/Connections MODEL cycle count, not RTL. It is exact for the
# link handshakes (CONNECTIONS_ACCURATE_SIM models the same ready/valid) but charges
# ONE tick per node-loop iteration, where the RTL charges II*iter + depth. So calibrate
# model->RTL once with a cosim at a small mesh, then read 8x8 from csim in minutes --
# the same two-step the v16 line used (README: "measure in csim (seconds) from here on").
if not REPLAY:
    _kc = os.path.join(PRJ, "kernel.cpp")
    _s = open(_kc).read()
    _m = re.search(r"^  for \(long long _c = 0; _c < (\d+)LL && !t\.done_sig\.read\(\); \+\+_c\)"
                   r" sc_start\(1, SC_NS\);.*$", _s, re.M)
    assert _m, "tb cycle loop not found -- the emitter changed; re-check the sc_main shape"
    _cap = _m.group(1)
    _new = ("  { long long _c = 0;\n"
            f"    for (; _c < {_cap}LL && !t.done_sig.read(); ++_c) sc_start(1, SC_NS);\n"
            '    std::ofstream _cf("cycles.txt"); _cf << _c << "\\n"; }')
    open(_kc, "w").write(_s[:_m.start()] + _new + _s[_m.end():])
    print(f"[cycles] tb patched, cap={_cap} -> {PRJ}/cycles.txt", flush=True)

# --- EXTRA_TCL: inject directives Catapult exposes only via TCL (e.g. the pipeline stall
# --- mode, which has no source-pragma form). Applied after `go assembly`, before extract.
_extra = os.environ.get("EXTRA_TCL", "")
if _extra:
    _tcl = os.path.join(PRJ, "run.tcl")
    _s = open(_tcl).read()
    _ins = "go assembly\n" + "".join(l + "\n" for l in _extra.split(";") if l.strip()) + "go architect\n"
    assert "go assembly\n" in _s, "run.tcl has no `go assembly` anchor"
    open(_tcl, "w").write(_s.replace("go assembly\n", _ins, 1))
    print(f"EXTRA_TCL injected -> {_tcl}:\n  " + "\n  ".join(_extra.split(";")), flush=True)


zf = lambda r, c: np.zeros((r, c), _NP)
zi = lambda r, c: np.zeros((r, c), np.int32)
outs  = [zf(VM, VL), zf(VM, VL), zf(VN, VL), zf(VN, VL)]
routs = [zi(VM, VL), zi(VM, VL), zi(VN, VL), zi(VN, VL)]
call  = [INS[0], IVS[0], INS[1], IVS[1], INS[2], IVS[2], INS[3], IVS[3], *outs, *RINS, *routs]
if PRIMECFG is not None:                      # skid carries a prime plane
    call.insert(0, PRIMECFG.astype(np.int32))

if REPLAY:
    import subprocess
    SYN = os.path.join(PRJ, "cosb")
    ins_only = [a for a in call if a is not None][: (9 if PRIMECFG is not None else 8)] + list(RINS)
    for i, a in enumerate(ins_only):
        with open(f"{SYN}/input{i}.data", "w") as fh:
            for v in np.asarray(a).reshape(-1):
                fh.write(f"{float(v):.9g}\n" if np.asarray(a).dtype == np.float16 else f"{int(v)}\n")
    print(f"wrote {len(ins_only)} input files -> {SYN}", flush=True)
    mk = glob.glob(f"{SYN}/**/Verify_concat_sim_rtl_v_ncsim.mk", recursive=True)
    assert mk, "no ncsim makefile -- was this project built with MODE=cosim?"
    v1 = os.path.dirname(os.path.dirname(mk[0]))
    for fp in glob.glob(f"{SYN}/output*.data"):
        os.remove(fp)
    NC = os.environ.get("NC_ROOT", "/opt/cadence/XCELIUM2403")
    r = subprocess.run([f"{MGC}/bin/make", "-f", "./scverify/Verify_concat_sim_rtl_v_ncsim.mk",
                        f"NC_ROOT={NC}", f"NCSim_NC_ROOT={NC}", "SIMTOOL=ncsim", "sim"],
                       cwd=v1, capture_output=True, text=True, timeout=14400,
                       env=dict(os.environ, NC_ROOT=NC, NCSim_NC_ROOT=NC))
    open(f"{PRJ}/replay_{WL}.log", "w").write((r.stdout or "") + (r.stderr or ""))
    print(f"ncsim rc={r.returncode}", flush=True)
    dat = np.loadtxt(f"{SYN}/output{VOUT}.data").reshape(-1, VL)
    for k in range(dat.shape[0]):
        outs[VOUT][k] = dat[k]
else:
    mod(*call)

# --- Report cycles ------------------------------------------------------------------
# Two independent counts, and they measure different things -- keep them apart:
#   MODEL  cycles.txt from the patched tb (csim, and the cosim software golden)
#   RTL    the ncsim `$finish ... at time N NS` with the 1 ns Connections clock
# The RTL number is the one to quote; the model number is what makes 8x8 cheap.
_cyc_model = _cyc_rtl = None
_cf = os.path.join(PRJ, "cycles.txt")
if os.path.exists(_cf):
    _cyc_model = int(open(_cf).read().strip())
for _lg in sorted(glob.glob(f"{PRJ}/*.log") + glob.glob(f"{PRJ}/**/*.log", recursive=True)):
    try: _txt = open(_lg, errors="ignore").read()
    except OSError: continue
    _fm = re.findall(r"\$finish[^\n]*?at time\s+([\d,]+)\s*NS", _txt)
    if _fm: _cyc_rtl = int(_fm[-1].replace(",", ""))
_iters = _bud if _bud is not None else VL          # elastic: BUDGET; skid: NSTEP(=VL)
print(f"=== CYCLES {VEC}/{WL} {VM}x{VN} MODE={MODE}: model={_cyc_model} rtl={_cyc_rtl} "
      f"iters={_iters} ===", flush=True)
if _cyc_model: print(f"    model clocks/iteration = {_cyc_model/_iters:.3f}", flush=True)
if _cyc_rtl:   print(f"    RTL   clocks/iteration = {_cyc_rtl/_iters:.3f}", flush=True)

# ALL_EDGES probe: the compare only ever looks at outs[VOUT]. If a "missing" value left
# via a DIFFERENT port it would never be seen -- and a wrong-port exit refutes the
# router-jam/quiescence story outright. Cost: four counts, no behaviour change.
if os.environ.get("ALL_EDGES", "0") == "1":
    _names = ["out_w(0)", "out_e(1)", "out_n(2)", "out_s(3)"]
    print("  [ALL_EDGES] nonzero counts per edge, per lane:")
    for _i, _a in enumerate(outs):
        _per = [int((np.asarray(_a)[r] != 0).sum()) for r in range(np.asarray(_a).shape[0])]
        print(f"    {_names[_i]:<10} total={sum(_per):<5} per-lane={_per}"
              + ("   <-- compared" if _i == VOUT else ""))

# Compare lane-by-lane against EOUT<VOUT>: golden = its leading NONZERO entries.
gold, got = EOUT[VOUT], outs[VOUT]
rows_ok = tot = mism = 0
nrows = 0
for k in range(gold.shape[0]):
    _row = list(gold[k])
    _last = max([i for i, v in enumerate(_row) if v != 0], default=-1)
    if _last < 0: continue
    _interior_zeros = [i for i, v in enumerate(_row[:_last + 1]) if v == 0]
    if _interior_zeros:
        print(f"  lane {k}: WARNING {len(_interior_zeros)} interior zero(s) in golden run "
              f"at {_interior_zeros[:5]} -- the nonzero filter would MISALIGN the compare; "
              f"using the full run to index {_last} instead.")
    g = _row[:_last + 1]
    nrows += 1
    mine = [int(_NP(got[k, t]).view(np.uint16)) for t in range(len(g))]
    bad  = [i for i, v in enumerate(mine) if v != g[i]]
    ok = not bad
    rows_ok += ok; tot += len(g); mism += len(bad)
    print(f"  lane {k}: {'OK ' if ok else ' x '} n={len(g)} "
          f"gold={[hex(v) for v in g[:2]]} got={[hex(v) for v in mine[:2]]}"
          + ("" if ok else f"  [{len(bad)} mism @ idx {bad[:4]}"
             + f" gold={[hex(g[i]) for i in bad[:4]]} got={[hex(mine[i]) for i in bad[:4]]}]"))
print(f"=== {VEC}/{WL} {MODE}: {rows_ok}/{nrows} lanes clean | {tot} outputs, {mism} mismatches ===")
sys.exit(0 if nrows and rows_ok == nrows else 1)
