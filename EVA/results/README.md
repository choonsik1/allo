# EVA results

- **[`EVALUATION.md`](EVALUATION.md)** — throughput (outputs/cycle) + P&R tables, methodology.
- **[`COMPARISON.md`](COMPARISON.md)** — vs the golden RTL: faithfulness, simplification audit, and the Allo-expressiveness gaps.
- **[`DESIGN_RATIONALE.md`](DESIGN_RATIONALE.md)** — why the two models (v2.0 blocking / v3.0 non-blocking).
- **⭐ [`final_chips/`](final_chips/)** — the deliverable: 4 verified chips (fp16/int16 × blocking/non-blocking), each with chip source + P&R reports + 8×8 cosim.
- `golden_cosim/` — golden-RTL cosim captures and logs (the oracle).
- `EVA_fft_cordic_programs.txt` — the fft / cordic program listings.

Older per-chip P&R and experiment outputs live in [`../archive/old_results/`](../archive/old_results/) —
superseded by `final_chips/` + `EVALUATION.md`, kept for provenance.
