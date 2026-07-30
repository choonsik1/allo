# Path C — drive LightningSim's solver with our own events

**Result (2026-07-30): WORKS, and it handles cycles — which invoking the tool does not.**

Path C means importing `lightningsim._core` (the compiled Rust engine) as a library and
building the simulation graph ourselves, instead of letting LightningSim instrument Vitis
bitcode and run a testbench:

```
invoke:   Vitis .bc -> instrument -> run testbench -> trace -> resolve -> _core -> cycles
path C:   Allo's own execution -> we emit builder calls ---------------> _core -> cycles
```

No Vitis bitcode, no LLVM instrumentation, no testbench.

## What was proven

**1. The solver accepts hand-built graphs** (`01_minimal_graph.py`). Producer writes 4 to
a FIFO, consumer reads 4:

```
graph: 10 nodes, 18 edges
top: top [0-9]
   producer [0-4]
   consumer [0-5]     <-- lags by 1: the read-after-write dependency is derived
   fifo 0: 4 writes, 4 reads, observed depth 1
```

It is solving, not echoing: the consumer's end and the observed depth are computed.

**2. Back-pressure is modelled** (`02_backpressure_and_dse.py`). Producer writes 1/cycle,
consumer reads 1 per 3 cycles, N=8:

| fifo depth | top cycles | producer ends | observed depth |
|---|---|---|---|
| 1 | 37 | 21 (stalled hard) | 1 |
| 2 | 34 | 18 | 2 |
| 4 | 28 | 12 | 4 |
| 8 | 25 | 8 (free-running) | 5 |
| unbounded | 25 | 8 | 5 |

Shallower FIFO → producer stalls → longer makespan, converging to the unbounded case.

**3. Native FIFO-depth DSE works** — `compiled.dse(base, space)` returns latency **and**
BRAM count per point (depth 2 → 34 cycles, depth 8 → 25). This is close to the DSE cost
model we want, already built.

**4. Cycles resolve** (`03_cycles.py`) — the decisive result:

| case | result |
|---|---|
| feed-forward A→B, 2 FIFOs | OK `top[0-9]` |
| cycle, unprimed | **`deadlock detected`** — correct, an unprimed ring IS deadlocked |
| cycle, primed | **OK `top[0-14]`** |

**This is the finding that separates Path C from invoking the tool.** LightningSim cannot
*run* a cyclic design — its functional sim must complete a sequential pass first, which a
mesh cannot do (Stage 1: segfault). But the solver itself has no such limitation: given a
correctly-ordered event stream it resolves a primed ring and correctly flags an unprimed
one as deadlock. The Type A restriction lives in the **front end**, not the engine.

## Caveats — do not over-read this

- **Event order must be causally consistent.** The builder replays a trace, so a FIFO's
  write must be emitted before the matching read. Our simulator knows the true order
  because it executes, but emitting it correctly is real work.
- **A malformed graph fails at `finish()`** with `ValueError: incomplete edges remain`
  (unbalanced read/write counts). Encountered twice; both times it was our bug.
- **`stage` numbers still come from the schedule.** Path C removes the LightningSim
  runtime dependency, not the Vitis one — that is still Path B's parsing work.
- **`_core.pyi` is a private, unstable API** and a compiled binary. Pinning to it means
  pinning to a build; nothing guarantees the surface across versions.
- These are synthetic graphs of a few nodes. Nothing here proves it scales to a real
  mesh's event volume, nor that our stage numbers would be right.

## Run

```bash
conda activate lightningsim
python 01_minimal_graph.py && python 02_backpressure_and_dse.py && python 03_cycles.py
```

## Where to read next in the LightningSim repo

`lightningsim/trace_file.py::resolve_trace` (~370–520) is the spec for what Allo would
have to emit: how `safe_offset` and `start_stage`/`end_stage` come from the schedule, when
`call`/`return_` fire, how loops scale stages by `ii * loop_idx`.
