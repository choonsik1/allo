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

## 5. Further literature (beyond the four already read)

Grouped by what each would actually contribute. **Bold = read these first.**

### 5a. Trace-based / pre-RTL simulation (same family as OmniSim)

- **LightningSim** (FPGA'23) — OmniSim's predecessor and the cleaner statement of the
  method: trace LLVM IR, map static HLS scheduling onto the trace, compute stalls and
  deadlocks from inter-function interaction. **99.9 % accurate, up to 95× faster than
  RTL co-sim.** Closest thing to a reference implementation for Route A, and it operates
  at the level Allo already lowers to.
- **Aladdin** (ISCA'14) — pre-RTL power/performance from a **dynamic data dependence
  graph**, no RTL generated; within 10 % of RTL flows. Older and coarser than
  LightningSim, but it is the origin of the "constrain an unconstrained DDDG" framing
  and is worth reading for *why* the graph is built the way it is. `gem5-Aladdin`
  extends it to accelerator+memory-system co-simulation.

### 5b. Analytical throughput models (no trace, no tool run — cheapest tier)

Potentially a **Tier 0** below our current engine: closed-form throughput for a dataflow
graph, fast enough to evaluate thousands of candidates.

- **Throughput and FIFO sizing for latency-insensitive designs** (INRIA) — max-plus /
  marked-graph analysis giving optimal FIFO sizes at maximum achievable throughput.
  Directly relevant: FIFO depth is a DSE knob we currently model only dynamically.
- **FIFOAdvisor** (arXiv 2510.20981, 2025) — a DSE framework for automated FIFO sizing
  of HLS designs; SDF buffer sizing via static analysis plus an SDC optimisation model.
  The most current statement of this line and closest to our DSE use case.
- **The role of back-pressure in latency-insensitive systems** (Carloni, Columbia) — the
  foundational semantics for what back-pressure *is*. Useful for making
  `valid_only` / `valid_ready` / wire precise rather than ad hoc.

### 5c. Learned surrogates (predict cycles instead of simulating them)

Relevant only if DSE needs to score far more candidates than either tier can simulate.

- **IronMan** (GLSVLSI'21) — GNN performance predictor + RL DSE; reduces HLS tool
  prediction error by 5.7× in timing, 10.9× in resources.
- **Hierarchical GNN source-to-post-route QoR** (DATE'24) — predicts *post-route* QoR
  from C source ([code](https://github.com/sjtu-zhao-lab/hierarchical-gnn-for-hls)).
- Caveat worth stating plainly: a surrogate needs a **large labelled corpus**, which is
  the §3.1 harness again. Learned models do not remove the ground-truth requirement —
  they raise it. Do not start here.

### 5d. Directly adjacent to our open problems

- **Latency-insensitivity testing for dataflow HLS designs** (FPGA'25, Edinburgh) —
  *does a design's result depend on timing?* This is OmniSim's Type A/B/C question posed
  as a testing problem, and it is the same property our determinism work asserts.
  **Most relevant single new paper for the non-blocking/livelock gap.**
- **StreamTensor** (arXiv 2509.13694, 2025) — streaming dataflow accelerators for LLM
  inference; useful as a workload/topology source once the model needs realistic designs
  rather than 2-PE toys.

## Sources

- [LightningSim (arXiv 2304.11219)](https://arxiv.org/pdf/2304.11219)
- [OmniSim, MICRO'58 (ACM DL)](https://dl.acm.org/doi/full/10.1145/3725843.3756033) ·
  [arXiv 2508.19299](https://arxiv.org/html/2508.19299v1)
- DAM, ISCA'24 — `simulator_papers/DAM_ISCA24_dataflow_abstract.pdf`
- [Aladdin, ISCA'14](https://people.eecs.berkeley.edu/~ysshao/assets/papers/shao2014-isca.pdf) ·
  [code](https://github.com/harvard-acc/ALADDIN)
- [Throughput and FIFO sizing for latency-insensitive designs (INRIA)](https://inria.hal.science/inria-00381644v1/document)
- [FIFOAdvisor (arXiv 2510.20981)](https://arxiv.org/pdf/2510.20981)
- [Back-pressure in latency-insensitive systems (Carloni)](https://www.cs.columbia.edu/~luca/research/rbilsENTCS06.pdf)
- [Latency-insensitivity testing for dataflow HLS designs, FPGA'25](https://www.pure.ed.ac.uk/ws/portalfiles/portal/486717247/ChengEtalFPGA2025LatencyInsensitivityTesting.pdf)
- [IronMan (ACM DL)](https://dl.acm.org/doi/abs/10.1145/3453688.3461495)
- [Hierarchical GNN QoR, DATE'24 (arXiv 2401.08696)](https://arxiv.org/pdf/2401.08696)
- [StreamTensor (arXiv 2509.13694)](https://arxiv.org/pdf/2509.13694)
- Local reports: `nb_stream.prj/…/csynth.rpt`, `blocking_stream_csynth.prj/…`
