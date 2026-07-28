# Routes to an accurate cycle model

Written 2026-07-28. Companion to `simulator_concept.md` (architecture) and the paper
analysis in `claude_simulator.md` §P1–P5. Decision note, not an implementation plan.

---

## 0. Correction to a recorded finding — the highest-accuracy route is NOT closed

`claude_simulator.md` and the `csynth-cost-model-ground-truth` note both record:

> Non-blocking designs give NO static schedule. Every loop reports `lat=- II=- depth=-`
> and overall latency `undef` … **schedule ingestion cannot be an accuracy route for
> NB designs.**

**That is too strong.** Re-reading `nb_stream.prj/out.prj/solution1/syn/report/csynth.rpt`:

```
|                  Modules & Loops         | … | Latency | Iteration | Interval | Trip | Pipelined |
| + top_nb*                                | … |    -    |     -     |    -     |  -   | dataflow  |
|  o l_S_i_0_i                             | … |    -    |     -     |    -     |  -   |    no     |
|   o VITIS_LOOP_24_1                      | … |    -    |     1     |    1     |  -   |   yes     |   <--
|   o VITIS_LOOP_44_1                      | … |    -    |     1     |    1     |  -   |   yes     |   <--
|  o l_S_store_res0_store_res0_l_0         | … |   11    |     9     |    1     |  4   |   yes     |   <--
```

What is `undef` is **aggregate latency and trip counts** — necessarily so, because the
retry loops are unbounded and the tool cannot know how many attempts happen.
**Per-iteration latency and II are reported**, including for the NB retry loops
themselves (1 cycle per attempt).

This is exactly the split trace-based simulation is built on: **the static schedule
supplies per-iteration timing; the dynamic trace supplies the trip counts the tool
cannot know.** The thing we concluded was missing is the thing the trace provides.

Caveat: the *outer* loops (`l_S_i_0_i`) still report `-`, so the schedule is partial —
usable for the pipelined inner regions, not a complete static timing of the design.

---

## 1. What "accurate" has to mean here

Two different consumers, two different bars:

| consumer | needs | a constant offset is… |
|---|---|---|
| **DSE ranking** (the agents' generator picking a design) | correct *ordering* of candidates | **harmless** |
| **Reporting** ("this design takes N cycles") | correct *magnitude* | **fatal** |

Today's model is calibrated at exactly **one point** (7 modelled vs 6 reported, 1.2×) on
two trivial integer PEs. Float, BRAM and pipelined-loop latencies are wholly
uncalibrated, and the makespan is 0.4× because `load_buf`/`store_res` are not clocked at
all. So we can currently defend neither bar — not because the model is bad, but because
**one data point cannot distinguish a good model from a lucky one.**

---

## 2. The three routes

### Route A — trace + static schedule (LightningSim / OmniSim)

Instrument LLVM IR to record executed basic blocks, join that trace to the csynth
schedule, build a graph of FIFO-access events with dependency edges, take the longest
path. **LightningSim: 99.9 % accurate, up to 95× faster than RTL co-sim. OmniSim:
0.09 % mean error, up to 35.9× over co-sim and 6.61× over LightningSim.**

- **Fit:** strong. Allo already lowers MLIR → LLVM, and loop names already join MLIR to
  the report by construction (`EmitVivadoHLS.cpp:972`).
- **Now viable for NB designs** — see §0. OmniSim's whole contribution is precisely the
  dataflow/NB designs commercial tools decline to simulate.
- **Real cost, and it is not the one we thought:** it needs a **csynth run per design**
  (~35 s). That is fatal *inside* a DSE inner loop, but it is not needed there — what
  varies in DSE is usually mapping/tiling/FIFO depth, not the PE body. **Schedule per
  kernel body can be extracted once and cached across configurations.**
- Retry-loop names come back as `VITIS_LOOP_24_1` (source-line) rather than the joined
  `l_…` form, so the MLIR↔report join needs a fallback for exactly the NB loops.

### Route B — per-PE local time (DAM-style; what we have)

Each PE owns a monotonic local time, advanced by a hand-authored latency table;
channels carry timestamps. DAM reports **~0.3 % (0.8 cycle)** vs RTL, up to 4 orders of
magnitude faster than cycle-stepped simulation.

- **Fit:** already built and working; no tool dependency; fast enough for a DSE inner loop.
- **Ceiling is the table, not the architecture.** DAM's 0.3 % is with *author-tuned*
  latencies. Ours are educated guesses validated once.
- This is the right **Tier 1** engine. It does not need replacing — it needs calibrating.

### Route C — calibrate against ground truth at scale

Not an alternative engine; the **measurement infrastructure both A and B need.**

- We already have a **proven** oracle: SystemC → Catapult → **Xcelium RTL co-sim**,
  demonstrated bit-exact on an allo-emitted design (2026-07-26). Crucially this yields
  **exact cycles for NB designs**, where csynth reports `undef`.
- So there are two complementary oracles: **csynth** = static, cheap, partial for NB;
  **RTL co-sim** = dynamic, exact, slow, works for everything.

---

## 3. Recommendation

**Build the oracle first (Route C), then a two-tier model.**

The binding constraint is not modelling sophistication — it is that **we cannot measure
accuracy**, so no improvement can be shown to be an improvement. One data point is not a
calibration; it is an anecdote. Concretely:

1. **Ground-truth harness.** A sweep of small designs (int/float mix, varying FIFO
   depth, blocking vs NB, 2–8 PEs) pushed through both oracles, emitting a table of
   *design → predicted cycles → csynth cycles → RTL cycles*. Reuse the existing csynth
   plumbing and the proven Xcelium recipe. **This is the single highest-value artefact**
   and everything below depends on it.
2. **Calibrate Tier 1** (Route B) against that table — per-op latencies, and the
   currently-unclocked `load_buf`/`store_res` wrappers that cause the 0.4× makespan.
   Report a *distribution* of error, not a single ratio.
3. **Add Tier 2** (Route A) for designs where magnitude matters: cache per-kernel
   schedules, join by loop name with a source-line fallback, longest-path over the
   event graph. Validate against the same table.

Tier 1 stays in the DSE inner loop; Tier 2 is the accuracy backstop. That mirrors how
DAM and OmniSim are positioned in the literature — approximate-but-fast vs
accurate-but-tool-coupled — rather than betting on one.

**What would change this recommendation:** if the DSE consumer only ever needs
*rankings*, Tier 2 may never be worth building, and the honest move is to calibrate
Tier 1 well and state its error bars. That is a question about how the agents' generator
consumes the number, and it should be answered before Tier 2 is started.

---

## 4. Open questions

- Do rankings actually need absolute accuracy? (Decides whether Tier 2 is ever built.)
- Does the csynth schedule stay valid across the mappings DSE varies, or does Vitis
  re-schedule per configuration? If it re-schedules, per-kernel caching breaks.
- Can Catapult/Xcelium co-sim be scripted headlessly for a sweep, or is it interactive?
- The `load_buf`/`store_res` gap: constant offset (harmless for ranking) or
  design-dependent (fatal for both)? Measurable with the §3.1 harness.

## Sources

- [LightningSim (arXiv 2304.11219)](https://arxiv.org/pdf/2304.11219)
- [OmniSim, MICRO'58 (ACM DL)](https://dl.acm.org/doi/full/10.1145/3725843.3756033) ·
  [arXiv 2508.19299](https://arxiv.org/html/2508.19299v1)
- DAM, ISCA'24 — `simulator_papers/DAM_ISCA24_dataflow_abstract.pdf`
- Local reports: `nb_stream.prj/…/csynth.rpt`, `blocking_stream_csynth.prj/…`
