# bubble_model — always-fire EVA: hand-Vitis vs Allo, verified by cosim

Two implementations of the same always-fire/bubble EVA architecture, plus the
replay infrastructure that proves their RTL executes and matches the Allo
simulator bit-for-bit. `BUBBLE_MODEL_PLAN.md` = canonical plan, findings log
(deadlock fix, both Allo signedness bugs) and status.

## vitis_bubble/ — hand-written C++ model
- `bubble_types.h`     packed word formats (PKT/sys/credit), fp16 bit-puns
- `eva_node.h`         the fused router+PE node, templated <ROW,COL>;
                       arms: EVA_COMB_FP (bind_op latency=0 fp, II=1),
                       EVA_PRIME (initial-token deadlock fix), EVA_NOPIPE
- `eva_perimeter.h`    drivers/collectors (4-lane + 1-lane variants)
- `eva_node_solo.cpp`  single-node csynth top
- `mesh_1x1_bubble.cpp` 1 PE + full perimeter (13 processes), cosim-proven
- `tb/tb_mesh_1x1_bubble.cpp` hand-written passthrough TB (cosim-only)
- `tcl/run_eva_node.tcl | run_mesh_1x1.tcl | run_mesh_1x1_comb.tcl |
   run_mesh_1x1_cosim.tcl`  — run from vitis_bubble/
- `reports_mesh_1x1/`  archived csynth reports (RPT_DIR to rename)

## allo_bubble/ — Allo-generated RTL, cosim-verified
Chip SOURCE lives in `Allo/EVA/eva_prime.py` (end-put primed variant of
eva.py; eva.py itself untouched) + `Allo/EVA/run_tests_prime.py` (sim suite
shim). Here:
- `allo_1x1_cosim/`    first Allo cosim bring-up: gen_kernel.py (1x1),
                       gen_kernel_4x4.py (QoR-compare kernel, csynth PARKED),
                       tb_allo_1x1.cpp (hand TB), run_allo_1x1_cosim.tcl
- `allo_cosim_suite/`  the REPLAY PIPELINE (verdict source of truth):
    dump_vectors.py    capture golden vectors from the 7 eva_tests
    dump_workloads.py  same for workloads (mmmr, fft2r, fft8r)
    vec_*.npz          captured inputs+outputs + chip params (M/N/NSTEP/IRF)
    run_suite.py       npz -> header -> cached kernel -> tcl -> cosim -> verdict
    tb_replay.cpp      THE one generic TB (bitwise compare, no test logic)
    log_*.txt          full vitis_hls log per replay
  Usage:  python dump_*.py  then  python run_suite.py [filter]   (allo env)
  Status: functional suite 9/9 bit-exact + mmmr PASS; 0 deadlocks.

## old_event_driven/ — reference only
Copies of the previous event-driven Vitis design (pe_core, router, 8x8
mesh/tile/fft + their tbs/tcls). Superseded by the bubble model; kept for
comparison arm 4 (context row) and code reference.
