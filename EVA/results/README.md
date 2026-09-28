# See COMPARISON.md for the authoritative results table, findings,
# expressiveness gaps, and open items.

# scoreboard_allo_eva_final — the two final Allo EVA scoreboard versions

One chip source, two validated configurations. `eva_sb.py` is the single
source of truth (scoreboard PE: metadata sb queue + result rings + retire-
before-fetch; END-PUT priming; uint8-narrowed types; knobs PRIME_TOKENS /
STREAM_DEPTH, defaults 1/2). Each variant folder is self-contained.

## variant_ii1/ — deep prime, II=1  (Vitis 2025.1)
PRIME_TOKENS=6, STREAM_DEPTH=8, NSTEP=120 (credit-RTT stretched, tb PC=80);
gen_kernel.py injects `dependence inter false` on resq/cmpq/res/wb — NOT
expressible in Allo (missing s.dependence primitive; this is the documented
exception to pure-Allo output). Results: node II=1 (iterLat 6), ROUTED
3.266 ns (~306 MHz, TIMING MET, xczu7ev), cosim PASS.
    python gen_kernel.py                          # allo conda env
    source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh   # (user shell)
    v++ -c --mode hls --config vitis25.ini --work_dir top
    vitis-run --mode hls --cosim --config vitis25.ini --work_dir top

## variant_pure/ — plain prime, pure Allo, II=3  (2023.2 or 2025.1)
Default knobs (T=1/D=2), NSTEP=55, NO pragmas — byte-pure Allo output
except the union compile-bug patch (documented in gen_kernel.py). II=3.
    python gen_kernel.py
    vitis_hls -f run_cosim_2023.tcl               # 2023.2 csynth+cosim
    # or vitis25.ini with v++/vitis-run as above

## eva_sb_syscredit.py — THIRD chip: golden-faithful sys-plane credits
The systolic plane gets the router plane's credit protocol = a registered
equivalent of golden EVA's rq/gt handshake (sync_register: stall-not-drop).
Senders hold words until credited; NOTHING is ever dropped -> workloads run
with their ORIGINAL schedules (no spacing/retiming), they only need enough
NSTEP ("run longer" is the only knob). Validated in sim: flood-rate inputs
4/4, MMM PASS with unmodified schedule at NSTEP x4. debug_sb.py = the
bisection harness that led here (chip name + spacing as args).
VALIDATED 2026-07-08: sim 7/7 suite (unchanged tests) + MMM (original
schedule) + FFT-8 (err 0.0019 = baseline) + flood-rate 4/4; RTL (2025.1,
variant_syscredit/: deep-prime T=6/D=8, NSTEP=200 - credit RTT applies to
the data path too): node II=1, cosim PASS, no deadlock. Reports in
reports/syscredit_*. Open: fft2r sim (loader lacks margin knob), routed
timing of this variant, QoR delta vs eva_sb.

## Verification harness (chip-level, config T=1)
- run_tests_sim.py       Allo simulator suite (7 tests) against eva_sb
- cosim_suite/           bit-exact RTL replay: dump_vectors.py (tests),
  dump_workloads.py (mmmr/fft2r/fft8r), run_suite.py (npz -> header ->
  kernel -> csynth+cosim -> verdict), tb_replay.cpp (the one generic TB)
    cd cosim_suite && python dump_vectors.py && python dump_workloads.py \
      && python run_suite.py            # hours; mesh + fft8r dominate
NOTE: sims need LLVM_BUILD_DIR=/home/zsm9/miniconda3/envs/allo (a wrong
/usr/lib/llvm-14 value fails with `Unknown function top` / __kmpc_*).
NOTE: the replay suite validates the T=1 config; running it at T=6 needs
per-test PC/NSTEP retiming (credit RTT ~= 2*TOKENS+2 per round; see
BUBBLE_MODEL_PLAN.md findings 07-05/07-06).

## reports/
- ii1_vitis25_csynth.rpt          II=1 csynth (node iterLat 6)
- ii1_vitis25_route_export.rpt    routed CP 3.266 ns (MET)
- ii1_vitis25_timing_routed.rpt   routed timing summary
- pure_vitis23_csynth_1x1_L10.rpt II=3 reference (2023.2)
(+ suite logs/summaries appended as runs complete)

Full findings history: ../BUBBLE_MODEL_PLAN.md (deadlock/priming/credit-RTT
laws, both Allo signedness bugs, the s.dependence expressiveness gap).
