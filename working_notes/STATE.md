# Project state

Branch **`main`** (staged on `main-with-eva`, which fast-forwards into `main`).
Fork `choonsik1/allo`; upstream `cornell-zhang/allo`.

## Branches
| Branch | Role |
|---|---|
| **`main`** | the consolidated work — SystemC emitter + IP integration + `EVA/`. **Start here.** |
| `ext/x1-connections-backend` | external line + the `convert-math-to-llvm` fix; forks a newer upstream than `main`. |
| `fix/nb-stream-scalar` | one builder fix (scalar NB-stream guard) pending a clean merge into `main`. |
| `backup/pre-rebase-systemc-ip` | pre-rebase safety snapshot. |

## What's on `main`
- the **SystemC / Catapult backend** (`mlir/.../EmitSystemC.cpp`) + the JIT dataflow simulator;
- **`EVA/`** — the EVA accelerator (A-tile) in Allo, its golden cross-check, and the verified
  4-chip deliverable (`EVA/results/final_chips/`, see `EVA/README.md`);
- **`ip_integration/`** — a RISC-V core wrapped as an Allo `IPModule`, driving the EVA PE grid.

## ⚠️ Build trap — two build trees, one tracked symlink
`allo/_mlir` is a **tracked** symlink whose correct target is host-specific, so the branch can't be
clean on both machines. `devtools/rebuild.sh` picks the tree by hostname and flips the symlink (and
marks it `--skip-worktree`; undo with `git update-index --no-skip-worktree allo/_mlir`). Each build
tree's CMake cache pins its host's compiler, so rebuild per host.

## Known gaps in the backend
- **Bit-slicing under csynth** — `(hi,lo)` bit-range is csim-only; packed-stream designs fail at the
  slice site (root cause + fix in `BACKEND.md`).
- **Bounded-loop pipelining** — a finite loop emits as a Catapult reset action, not pipelined; only
  run-forever loops get the `while(1)` shape.
- **Inner-loop directives** — emitter doesn't auto-emit UNROLL/PIPELINE on inner loops (manual
  `s.pipeline` works).
- **Induction-variable width inflation** — frontend widens intermediates (`x*2+1` on int32 → 65 bits);
  identical on `vhls` and `catapult`, so it's a frontend issue affecting all backends.
- *(Done 2026-08: stateful `x: T @ Stateful` now emits in the SC_THREAD reset action — csim+cosim
  bit-exact, `tests/dataflow/test_stateful_systemc.py`.)*

## Next candidates
1. Period bisection for real Fmax (most Genus Fmax are lower bounds — it stops at constraint-met).
2. Full dataflow sweep after the `hls_resource` emitter change.
3. `rvn_router` II=1 — blocked by the `vmask → pdst → odst` arbiter recurrence.
4. WHVCRouter II=1 — blocked by `popm → bhd`.
5. Induction-variable width narrowing — a ~34% area lever benefiting every backend.

## Outside this repo
- **NoC evaluation** — `final_noc/` (its own repo): Allo vs MatchLib/RaveNoC + Genus synthesis;
  authoritative numbers in its `designs/*/RESULTS.md`.
- **EVA SystemC working copy** — `final_eva_systemc` (snapshotted here under `EVA/`).
