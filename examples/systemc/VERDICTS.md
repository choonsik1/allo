# SystemC/Catapult backend — dataflow example verdicts

Every `tests/dataflow/test_*.py` example given a definitive verdict against the
SystemC backend (simulator vs `target="systemc", mode="csim"`, identical seeded
inputs). Float examples were also run as blind `float32→int32` copies to isolate
backend behavior from float support (float lowering is a separate, deprioritized
track). Harness: `scratchpad/harness.py`; driver: `scratchpad/driver.sh`.

## PASS — sim == systemc, bit-exact (14)
| example | datatype | note |
|---|---|---|
| systolic | int32 (from float) | classic output-stationary systolic |
| 1D_systolic | int32 (from float) | 1-D relay array |
| weight_stationary_gemm | int32 (from float) | WS GEMM |
| tiled_systolic | int32 | stream-output GEMM (self-synchronizing) |
| daisy_chain_gemm | int32 | chained regions |
| smith_waterman_systolic | int32 | DP wavefront |
| producer_consumer | int32 | B = A+1 over a Stream |
| df_unit | UInt(16) | stream load/store, C = A |
| region_toparg_aliasing | int32 | #592 aliasing regression |
| stream_of_blocks | int32 | stream-of-blocks pattern |
| **tiled_gemm** | int32 (from float) | **FIXED by single-shot** — `both` C accumulator, mapping=[2,2] |
| **pingpong_gemm** | int32 (from float) | **FIXED by single-shot** — ping-pong `both` accumulator |
| **hierachical** | int32 (from float) | **FIXED by single-shot** — `both` C |
| **wrap_movement** | int32 (from float) | **FIXED by single-shot** — `both` C |

**Single-shot execution (implemented).** Each kernel now runs its body EXACTLY
ONCE (was free-running `while(1){body}`), then idles; the memory-output testbench
advances the clock until all kernels signal completion (csim `__allo_done` counter
== #kernel-instances) before reading the memories, replacing the old fixed
`maxTotal*8` guess. This fixed the four `both`-accumulator designs (were partial /
over-accumulated). Requires the harness to zero-init `both` accumulators (real
accumulators start at 0; the actual tests do `C=np.zeros`) — otherwise the
multi-replica sum-merge over-counts a nonzero preload by (numReplicas-1)×
(a separate, narrow limitation for nonzero-init tiled accumulators).

Plus the dedicated suite `tests/dataflow/test_systemc_backend.py` — **28/28 PASS**
(memory ports i/o/both, multi-client, hierarchy, empty/full, bit-slice packing,
stream depth).

## FAIL — real backend gap (2)
| example | class | root cause |
|---|---|---|
| region_stateful | `@ Stateful` unsupported | region-scope persistent buffer; sim MLIRError / emit gap |
| hierachical_mesh | `@ Stateful` unsupported | emit: `__stateful_*_ctrl/daddr/size` undeclared in scope |

Remaining real gap: **`@ Stateful` persistent buffers** are not declared by the
emitter (`__stateful_*` control/addr/size state). Needs stateful-decl emission.
(The mem-mapped-output readout race that previously failed tiled_gemm /
pingpong_gemm / hierachical / wrap_movement is FIXED — see single-shot above.)

## KNOWN ISSUE — csynth compile broken branch-wide (pre-existing, from 2b1e66f)
Catapult `go compile` aborts on `ac_int.h(2259): struct assignment from non-struct
type (CIN-15)` for EVERY design (confirmed on a pure-stream design with the
emitter both with and without the single-shot change → not single-shot's fault).
Root cause: the `ap_int`/`ap_uint` bit-slice shim added in commit 2b1e66f is a
`struct s : ac_int<W,...>` SUBCLASS; Catapult's front-end rejects assignment to an
ac_int-derived struct. csim is unaffected. Fix = native ac_int type-name emission
(the standing TODO) or a synthesis-safe shim. Tracked separately from single-shot.

## FAIL — non-blocking `empty()/full()` spin (3)
| example | note |
|---|---|
| stream_nb_scalar | NB self-loop: `while empty(): spin` never yields → deadlock |
| stream_nb_simple | same |
| decoupled_mesh | empty/full mesh (+ float) |

`Empty()/Full()` emit correctly (sim-only Connections queries), but a kernel that
busy-waits on them in a self-loop never advances in the clocked SC_THREAD model.
Needs blocking semantics or a yield.

## BLOCKED on float (int-port artifact, not a backend bug) (3)
| example | evidence |
|---|---|
| mlp | residual float `0.000000` in a data/bias init → int copy incomplete |
| systolic_conv | residual float literal |
| cooperative_gemv | 3 residual float lines in int copy |

Underlying feature = float lowering (separate track). Not counted against the
integer backend.

## MISMATCH — int8 bit-packing (1)
| example | note |
|---|---|
| packed_systolic | int8 packed lanes; compiles, but sim≠systemc — ac_int bit-slice packing suspect |

## TIMEOUT — inconclusive (2)
| example | note |
|---|---|
| unified_systolic | no NB ops; sim non-termination or slow codegen (>200s) |
| nested_subregion_streams | sub-region streams; >240s |

## N/A — harness cannot drive (1)
| example | note |
|---|---|
| multi_cache_gemm | top takes **Stream-typed** args (L3_A/B/C); no array to poke |

## Not workloads — stream-op / infra unit tests (4)
`stream_ops_hls`, `stream_ops_ir`, `stream_ops_sim` (op-API unit tests, exercised
transitively by the suite), `systemc_backend` (the suite itself).

---
### Scoreboard
- **14** examples + **28** suite tests PASS bit-exact (was 10; +4 from single-shot).
- **2** real backend gaps: `@ Stateful` persistent buffers (both cases).
- **3** NB empty/full spin (blocking-semantics gap).
- **3** float-blocked, **1** int8-pack mismatch, **2** timeout, **1** stream-arg N/A.
- **4** are unit/infra, not workloads.
- KNOWN ISSUE: csynth compile broken branch-wide (ac_int subclass shim, 2b1e66f) —
  csim unaffected, separate from single-shot.

Reproduce: `bash scratchpad/driver.sh` (env recipe in
`memory/catapult-systemc-memory-port-refs.md`).
