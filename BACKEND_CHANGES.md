# allo_ext backend changes (branch ext/x1-connections-backend)

Log of edits to this worktree's Allo backend, so they can be reviewed / reverted
/ upstreamed. Do NOT edit the pristine /home/zsm9/allo install.

## 2026-07-11 — dataflow simulator: lower the `math` dialect

**File:** `allo/backend/simulator.py` (the `LLVMOMPModule` lowering PassManager,
just before `convert-arith-to-llvm`).

**Change:** added one pass — `convert-math-to-llvm,` — to the dataflow simulator
lowering pipeline.

**Why:** the pipeline lowered `arith/func/memref/scf/cf/index/openmp` to LLVM
but NOT the `math` dialect, so `math.*` ops (e.g. `allo.sqrt` → `math.SqrtOp`,
used by the EVA extended PE div/sqrt column) reached LLVM-IR translation with no
registered interface:
`error: cannot be converted to LLVM IR: missing LLVMTranslationDialectInterface
registration for dialect for op: math.sqrt`.
The standard (non-dataflow) `backend/llvm.py` already lowers math via
`lower_allo_to_llvm`; only the simulator pipeline was missing it.

**Effect:** the dataflow simulator can now JIT-execute math ops (sqrt/exp/log/
sin/cos/...). No-op for designs without math ops (nothing to lower). Does NOT
touch vhls/HLS codegen (separate path).

**Validated:** `final_runs/verification/test_divsqrt_sim.py` — EVA `top_extended`
chip, DIV + SQRT through the full mesh, 6 vectors PASS (e.g. 6/2=3, sqrt(9)=3,
sqrt(2)=1.414 at fp16). Run with `PYTHONPATH=/home/zsm9/allo_ext`.

**Revert:** delete the `"convert-math-to-llvm,"` line.

**Upstream candidate:** yes — the simulator pipeline arguably should always lower
math (matches llvm.py). Small, safe, additive.
