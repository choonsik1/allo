# Run a DEDICATED golden-replay (mmm/fft/cordic) on ANY final_runs chip by
# aliasing module `eva` -> the chosen chip, then executing the replay as __main__.
# These dedicated replays carry the CORRECT per-workload config (mmm iter=2,
# fft/cordic iter=Inf) -- unlike the generic syscredit harness (iter=0 -> mmm silent).
#   CHIP=eva_sb_syscredit_fwd LLVM_BUILD_DIR=/home/zsm9/miniconda3/envs/allo \
#     python run_golden_chip.py {mmm|fft|cordic}
import os, sys, runpy
CHIP  = os.environ.get("CHIP", "eva")
FR    = "/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs"
TESTS = os.path.dirname(os.path.abspath(__file__))  # replays + eva_workloads live alongside
sys.path.insert(0, TESTS)                     # eva_workloads.py
sys.path.insert(0, FR)                        # the chip .py lives here
if CHIP != "eva":
    chip = __import__(CHIP)
    # optional credit-priming overrides (FFT needs PRIME<=2; cordic/mmm ok at chip default 6)
    if os.environ.get("PRIME") and hasattr(chip, "PRIME_TOKENS"): chip.PRIME_TOKENS = int(os.environ["PRIME"])
    if os.environ.get("DEPTH") and hasattr(chip, "STREAM_DEPTH"): chip.STREAM_DEPTH = int(os.environ["DEPTH"])
    sys.modules["eva"] = chip                 # dedicated replay does `import eva as e` -> gets this
    print(f"== golden replay on CHIP={CHIP} (aliased as eva) "
          f"PRIME={getattr(chip,'PRIME_TOKENS','-')}/D={getattr(chip,'STREAM_DEPTH','-')} ==")
wl = sys.argv[1] if len(sys.argv) > 1 else "mmm"
script = {"mmm": "replay_golden_mmm.py", "fft": "replay_golden_fft.py",
          "cordic": "replay_golden_generic.py"}[wl]
sys.argv = [script]                           # cordic (generic) runs all 4 variants in __main__
runpy.run_path(os.path.join(TESTS, script), run_name="__main__")
