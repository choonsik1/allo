# B=20 streaming on the 8×8 chip (sustained throughput + losslessness)

Beyond the single-shot golden replay, this injects **20 back-to-back activations**
of each workload into the 8×8 chip (timestamped `eva_sb_syscredit_fwd_cosim`, right
primes: east-drain=1, mmm=6) and checks the output edge for **20 bit-exact copies**
of the golden result per row. Per row it reports **delivered/20** (losslessness under
continuous load — the credit plane's real test) and the **sustained cyc/activation**
(steady-state throughput, not the 2-sample single-shot estimate).

Driver: `final_runs/cosim_8x8/eva_sb_nb/run_stream8x8.sh` + `tb_replay_golden_stream.cpp`.
Each `<wl>/` has `top_cosim.rpt` + `verdict.txt` (per-row delivered count + cyc/activation).

## Results
| workload | delivered/row | sustained cyc/activation | note |
|---|---|---|---|
| **fft**       | **20/20 LOSSLESS** | ~1.0-region, **16.0** | credit plane sustains continuous load; router (fft is the only router-driving workload) holds up losslessly |
| **cordic_cr** | 10/20 (uniform, all rows) | 48.0 | ⚠️ **under investigation** — see below |
| cordic_cv/hr/hv | (run in progress) | | |
| mmm           | (run in progress) | | |

## ⚠️ The cordic_cr 10/20 result — NOT yet confirmed as a chip drop
Every row delivered *exactly* 10/20 at a regular 48 cyc/activation. That **uniformity**
argues against random congestion drops (which would be irregular) and toward something
**systematic** — most likely a **harness assumption**, not lost data:
- the streaming test assumes 20 identical input activations → 20 identical outputs
  (true for fft here, and for the earlier mmm B=16 lossless demo);
- cordic's input-consumption cadence may not be the assumed 2-inputs/activation, so the
  40 contiguous injected inputs may only cleanly drive ~10 activations.
Decisive check pending: **fft already streamed 20/20 lossless on the same credit chip**,
so the chip *can* do it; if **mmm** (known-stateless MAC) also streams 20/20 here, the
cordic result is isolated to cordic + this harness, not a credit-plane drop. Root cause
to be resolved before calling it a pass/fail.
