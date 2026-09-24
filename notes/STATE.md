# Project state — `/home/zsm9/allo_final`

Last updated 2026-09-24. Branch **`systemc-all`**.

## Worktrees

One repository (`/work/shared/users/zsm9/allo_new/.git`), three checkouts. Consolidated
from six on 2026-09-24; removing a worktree never removed a branch, and every branch
below is pushed to `mine`.

| Directory | Branch | Role |
|---|---|---|
| **`/home/zsm9/allo_final`** | **`systemc-all`** | **The final work. Start here.** |
| `/home/zsm9/allo_scratch` → `/work/shared/users/zsm9/allo_scratch` | `ext/x1-connections-backend` | Scratch. `git switch` to any other branch here. |
| `/work/shared/users/zsm9/allo_new` | `main` | Holds `.git`. Clean mirror of `origin/main`; do not commit here. |

## Remotes

| Remote | Points at | Role |
|---|---|---|
| `mine` | `choonsik1/allo` | Your fork. Everything is pushed here. |
| `origin` | `cornell-zhang/allo` | Upstream baseline. |
| `sup` | `sunwookim028/allo` | The fork this checkout came from (hence the old name `allo_sup`). |
| `fangtang`, `vincent` | collaborators' forks | Read-only reference. |

## Branches

| Branch | Role |
|---|---|
| **`systemc-all`** | **Final.** All three SystemC lines merged, plus `EVA/` and `ip_integration/`. |
| `SystemC-emitter` | The emitter line. Fully contained in `systemc-all`. |
| `systemc-ip-integration` | SC_MODULE-as-Allo-IP. Fully contained in `systemc-all`. |
| `ip-stream-integration` | Vitis `hls::stream` IP line. Fully contained in `systemc-all`. |
| `ext/x1-connections-backend` | External line + the `convert-math-to-llvm` fix. Forks from a **newer** `main` than `systemc-all`. |
| `main` | Tracks `origin/main`, unmodified. |
| `wire`, `fix/nb-stream-scalar`, `ext/sup-main` | Older lines, kept for reference. |
| `backup/pre-rebase-systemc-ip`, `backup-pre-docx-rewrite` | Safety snapshots. |

## What is on `systemc-all`

Beyond the merged emitter work, two directories that existed in no repository until
2026-09-24 and were committed verbatim, to be sorted through later:

- **`EVA/`** (134 files) — the EVA chips driven through the SystemC backend into
  Catapult. Designs, run/report harnesses, results archive, and a README carrying the
  measured area/timing tables and the traps behind them. Includes 8.6 MB of Catapult
  logs, force-added against `.gitignore` because they are the evidence for the archived
  numbers. Snapshot of `/home/zsm9/final_eva_systemc`, which is still the live working
  copy — **this is a copy, not the working tree**.
- **`ip_integration/`** (76 files, 852 KB) — a third-party RISC-V core wrapped as an Allo
  `IPModule` and wired into the EVA PE grid. `ip/` is the integration; `rv/`, `hl5_cat/`
  and `drim_cat/` carry vendored cores, each with its upstream `LICENSE` and a
  provenance README (both Apache 2.0, matching allo's own).

## ⚠️ Build trap — two build trees, one tracked symlink

`allo/_mlir` is a **tracked** symlink, but which build it must point at is
**host-specific**, so the branch can never be clean on both machines:

| Build dir | Host | Built | Emitter | Portability |
|---|---|---|---|---|
| `mlir/build` | `zhang-21` (gcc-toolset-13) | 2026-08-25 | **old** (pre-merge) | runs on both hosts |
| `mlir/build_xcel` | `brg-zhang-xcel` (`/usr/bin/c++`) | 2026-09-24 | **merged** | xcel only |

`devtools/rebuild.sh` picks the tree by hostname and flips the symlink. On xcel the
symlink is flipped to `build_xcel` and marked `git update-index --skip-worktree`, so the
local flip neither shows as dirty nor can be committed. **To undo that marking:**
`git update-index --no-skip-worktree allo/_mlir`.

`mlir/build` cannot be rebuilt on xcel — its CMake cache pins
`/opt/rh/gcc-toolset-13/root/usr/bin/c++`, which does not exist there.

⚠️ `devtools/rebuild.sh` does `cd "$(dirname "$0")"`, which lands in `devtools/` where
there is no `mlir/`. Run its steps from the repo root instead, or fix the `cd` to `..`.

## ⚠️ `/home/zsm9/allo_sup` is a compatibility symlink

The worktree was renamed `allo_sup` → `allo_final` on 2026-09-24. The compiled
extensions bake an absolute `RUNPATH` (`$ORIGIN:/home/zsm9/allo_sup/mlir/build/...`) and
the build tree holds four absolute symlinks into the old name, so
`/home/zsm9/allo_sup` → `/home/zsm9/allo_final` was left in place. It is load-bearing
for any build tree configured before the rename, and it also keeps `EVA/archive/**`
driver snapshots resolving. A rebuild regenerates those paths for the tree it rebuilds.

Old build artifacts are backed up at
`/work/shared/users/zsm9/allo_build_backups/2026-09-24/` (both trees' loadable libs plus
the original symlink target).

## The EVA and NoC evaluations live outside this repo

- **EVA** — `/home/zsm9/final_eva_systemc` (not a git repo; snapshotted here as `EVA/`).
  Its scripts import allo via `sys.path.insert(0, "/home/zsm9/allo_final")`.
- **NoC** — `/home/zsm9/final_noc` (its own git repo). Authoritative numbers in
  `final_noc/designs/whvcrouter/RESULTS.md` and
  `final_noc/designs/router_rvn_equiv/reports/README.md`.

Headline NoC (Genus 20.1 high effort, Nangate 45nm, 2.0 ns, `concat_rtl.v`, 0 black boxes):

| design | Allo | reference | verdict |
|---|---|---|---|
| WHVCRouter | 2 cyc/step, 510 MHz, 32,415 µm² | MatchLib 1 cyc, 509 MHz, 31,784 µm² | MatchLib 2.04× per area |
| Crossbar | 1 cyc/step, 746 MHz, 6,466 µm² | MatchLib 3 cyc, 775 MHz, 6,056 µm² | **Allo 2.71× per area** |
| RaveNoC-equivalent | 2 cyc/step, 606 MHz, 10,001 µm² | RaveNoC 1 cyc, 567 MHz, 7,857 µm² | RaveNoC 2.38× per area |

## Known gaps in the backend

- ~~**Stateful category**~~ — **DONE 2026-08-16.** `x: T @ Stateful` now emits in the
  SC_THREAD reset action (per-instance, reset-initialised) rather than as the Vitis
  function-scope `static`. Scalar + array, csim and cosim bit-exact:
  `tests/dataflow/test_stateful_systemc.py`.
- **Bit-slicing under csynth** — the `(hi,lo)` bit-range is csim-only, so packed-stream
  designs fail at their slice site. Root cause and the fix that would delete it are in
  `BACKEND.md`.
- **Bounded-loop pipelining** — a finite loop emits as a Catapult reset action and is
  therefore not pipelined; only run-forever loops get the `while(1)` shape.
- **Inner-loop directives** — the emitter builds the reset + `while(1)` + bounded-for
  shape but does not auto-label or emit UNROLL/PIPELINE on inner loops. Manual
  `s.pipeline` does work.
- **Induction-variable width inflation** — the frontend widens intermediates to 33/65
  bits (`x*2+1` on an `int32` yields 65 bits). Verified identical on `vhls` and
  `catapult`, so it is a frontend issue affecting **all** backends, not an emitter bug.

## Next candidates

1. Period bisection for real Fmax — every Fmax except the WHVCRouter pair is a lower
   bound (slack +192 to +1170 ps), because Genus stops optimising once the constraint
   is met.
2. Full dataflow sweep after the `hls_resource` emitter change (only
   `test_systemc_backend.py` was re-run: 26 passed, 2 pre-existing failures).
3. `rvn_router` II=1 — blocked by the `vmask → pdst → odst` arbiter recurrence.
4. WHVCRouter II=1 — blocked by `popm → bhd`.
5. Induction-variable width narrowing (see above) — a 34% area lever, and it would
   benefit every backend.

## Provenance note

`STATE.md` and `BRANCHES.md` as inherited from the `sup` fork described
`sunwookim028/allo`'s branch topology and PR queue, none of which exists in this
checkout. They are in `archive/` unchanged.
