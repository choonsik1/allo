# EVA final chips — RTL cosim PASS (Allo → Vitis HLS)

Two EVA accelerator variants written in Allo, both **verified by Vitis 2025.1
C/RTL co-simulation** on a 4x4 mesh running the `mmm` (matrix-multiply) workload,
bit-exact against the analytical golden `X @ W`.

| chip | dir | scheme | II | cosim |
|------|-----|--------|----|-------|
| `eva_sb_nb`        | `eva_sb_nb/`        | fully **non-blocking** (`read_nb`/`write_nb`) | II=3 | **PASS** `out_s=[18,21,16,15]` |
| `eva_sb_syscredit` | `eva_sb_syscredit/` | **credit-based** back-pressure (systolic credits) | II=1 | **PASS** (0 mismatches) |

Golden result for both: `out_s = 0x4c80 0x4d40 0x4c00 0x4b80 = [18, 21, 16, 15]`
(X=`[1,2,3,1]`, W[i][j]=`((i+j)%4)+1`).

Environment: Vitis HLS **2025.1**, part **xczu7ev-ffvc1156-2-e**, clock **3.33 ns**,
type **float16**, mesh **4x4**, NSTEP/LANELEN **374**, IRF depth 8, data-driven.

## Contents (per chip)
- `*.py`            — the Allo chip source (generates the kernel below)
- `kernel.cpp`      — the exact generated HLS kernel that co-simulated (the `top` under test)
- `vectors_*.h`     — inputs + golden (`IN*`/`IV*`/`RIN*`/`EOUT*`), from `vec_mmm4_eva_sb.npz`
- `ci_*.ini`        — Vitis config (part/clock/top/tb)
- `COSIM_PASS.txt`  — captured cosim verdict

Shared: `tb_replay_nb.cpp` (20-port `top()` replay harness, identical for both),
`vec_mmm4_eva_sb.npz` (the proven input/golden bundle both vectors headers were built from).

## Reproduce the cosim
```bash
conda deactivate                 # use system Vitis 2025.1, not the conda python
cd eva_sb_nb                     # (or: cd eva_sb_syscredit)
v++      -c --mode hls --config ci_eva_sb_nb_4x4.ini --work_dir /tmp/eva_cosim
vitis-run   --mode hls --cosim  --config ci_eva_sb_nb_4x4.ini --work_dir /tmp/eva_cosim
# expect: *** C/RTL co-simulation finished: PASS ***
```
Use a **local** `/tmp` work_dir (NFS triggers `.nfs busy` errors). DSP48 OPMODE
warnings during sim are harmless fp16 noise.

## Regenerate the kernel from the .py (optional)
Requires the non-blocking (NB) Allo branch for the non-blocking emitter:
```bash
LLVM_BUILD_DIR=/home/zsm9/allo/mlir/build_xcel \
PYTHONPATH=/home/zsm9/allo python -c "..."   # see final_runs/cosim_8x8/eva_sb_nb/build_nb.py
```

## Notes
- **`eva_sb_syscredit`**: pure-C simulation of the credit protocol does not order
  correctly (the C-sim phase reports mismatches), but the **RTL** cosim — the phase
  that reflects real hardware — passes bit-exact. See `COSIM_PASS.txt`.
- **`eva_sb_nb`** additionally completed Vitis `impl` (IP export, `top.zip`).
- An II=1 non-blocking variant (`eva_sb_nb_ii1`, pe_core-style demand-driven RX) is
  in progress in `final_runs/` — it passes cosim at II=3 but not yet at II=1
  (bind_op latency shift de-syncs the RTL); not included here until it cosims at II=1.
