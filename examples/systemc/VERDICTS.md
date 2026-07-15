# SystemC/Catapult backend — dataflow example verdicts

Every `tests/dataflow/test_*.py` example given a definitive verdict against the
SystemC backend (simulator vs `target="systemc", mode="csim"`, identical seeded
inputs). Float examples were also run as blind `float32→int32` copies to isolate
backend behavior from float support (float lowering is a separate, deprioritized
track). Harness: `scratchpad/harness.py`; driver: `scratchpad/driver.sh`.

## PASS — sim == systemc, bit-exact (10)
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

Plus the dedicated suite `tests/dataflow/test_systemc_backend.py` — **28/28 PASS**
(memory ports i/o/both, multi-client, hierarchy, empty/full, bit-slice packing,
stream depth).

## FAIL — real backend gap (6)
| example | class | root cause |
|---|---|---|
| tiled_gemm | mem-output readout race | top tiles correct, late tiles un-accumulated |
| pingpong_gemm | mem-output readout race | ping-pong `both` accumulator, same race |
| hierachical | mem-output readout race | MISMATCH on `both` C |
| wrap_movement | mem-output readout race | MISMATCH on `both` C |
| region_stateful | `@ Stateful` unsupported | region-scope persistent buffer; sim MLIRError / emit gap |
| hierachical_mesh | `@ Stateful` unsupported | emit: `__stateful_*_ctrl/daddr/size` undeclared in scope |

Two distinct real gaps:
1. **Memory-mapped OUTPUT readout race.** `o`/`both` outputs are sampled at a
   fixed testbench time; with variable per-tile completion the late tiles are
   still mid-compute → partial values. Stream outputs are immune (tb collects
   exactly N tokens = self-synchronizing). Fix = completion signal / single-shot
   settle for mem-mapped outputs (ties to the deferred single-shot work).
2. **`@ Stateful` persistent buffers** are not declared by the emitter
   (`__stateful_*` control/addr/size state). Needs stateful-decl emission.

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
- **10** examples + **28** suite tests PASS bit-exact.
- **6** real backend gaps: 4 mem-output readout race (single-shot), 2 `@ Stateful`.
- **3** NB empty/full spin (blocking-semantics gap).
- **3** float-blocked, **1** int8-pack mismatch, **2** timeout, **1** stream-arg N/A.
- **4** are unit/infra, not workloads.

Reproduce: `bash scratchpad/driver.sh` (env recipe in
`memory/catapult-systemc-memory-port-refs.md`).
