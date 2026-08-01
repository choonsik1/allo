# RaveNoC reference numbers (Phase 1)

Measured 2026-08-01 with Xcelium 24.03 + cocotb 1.9.2. **The RTL is unmodified RaveNoC**;
only the benches, `wrappers.sv` (parameter pinning), and the Makefile are ours.

Matched "vanilla" config: **32-bit flits, buffer depth 2, 2 VCs, XY routing**, 2.0 ns clock.
Taken from `tb/common_noc/constants.py` (`flit_buff = 2`) — note the tb README's flavor table
says `FLIT_BUFF = 1` and is **stale**; the code wins, and depth 2 is what matches
`Stream[int32,2]` on the Allo side.

## Why we wrote our own benches

RaveNoC ships 8 testbenches but **all of them drive `ravenoc_wrapper`**, the AXI top — so they
measure the full NoC + network interface + CDC + CSR path. Our Allo designs have no AXI NI, so
that number is not comparable. Seven of the eight report no timing at all; the eighth
(`test_throughput.py`) reports MB/s across a clock-domain crossing, derived from a `get_sim_time`
delta, and is never checked against a threshold.

**RaveNoC publishes no performance numbers** — no benchmarks, throughput, latency, area or
utilisation figures in the README or anywhere in the repo. Every reference number here is ours.

The author sanctions this approach: the tb README states the AXI wrapper exists only because
"Verilator 4.106 cannot handle easy structs/arrays in the top level" and that "during standard
IP usage, `ravenoc_wrapper` must not be part of filelist."

## Results

| design | mode | units | cycles | per unit |
|---|---|---|---|---|
| `fifo` | max throughput | 64 flits | 65 | **1.016 cyc/flit** |
| `vc_buffer` | greedy | 64 flits | 65 | **1.016 cyc/flit** |
| `vc_buffer` | backpressure (1-in-3) | 64 flits | 193 | **3.016 cyc/flit** |
| `rr_arbiter` | saturated (4 reqs) | 64 grants | 65 | **0.985 grants/cyc**, dist `[16,16,16,16]` |
| `rr_arbiter` | single requester | 31 grants | 32 | 0.969 |

The measurement window is `[first accepted transfer .. last accepted transfer]`, in clock edges.
It deliberately **excludes reset**, because the Allo side's 17-cycle Catapult reset is an artifact
of the flow and has nothing to do with the link type under test.

## What the numbers say

1. **The handshake is free.** `vc_buffer` = `fifo` + a valid/ready handshake on both ends, and
   costs **zero** extra cycles (65 vs 65). So any Allo `Stream` overhead we measure is not
   inherent to the protocol — RaveNoC's handshake is combinational glue.
2. **Backpressure tracks the duty cycle exactly** (3.016 against a 1-in-3 ready pattern), i.e.
   the buffer adds no latency of its own; the consumer is the sole limit. This is the mode where
   a zero-storage `Channel` should diverge from a depth-2 `Stream`, so it is the discriminating
   measurement of the whole comparison.
3. **The arbiter is genuinely round-robin** — `[16,16,16,16]` over 64 grants. A naive priority
   encoder would hit the same 0.985 throughput while producing `[64,0,0,0]`; only the fairness
   assertion catches that. Any Allo rebuild must reproduce the distribution, not just the rate.

## Methodology caveat (do not misread the numbers)

In the greedy `fifo` case the bench drives `write_i` unconditionally and lets the DUT's own
`write_i && ~full_o` guard decide, then reconstructs accepted transfers from that same
expression. Deciding the enable from `full_o` sampled in the same cycle is circular — the value
driving edge N must be set before edge N, but the flags settle at ReadOnly, after which cocotb
forbids driving.

Consequence: **`error_o` asserts on dropped writes**, which is why the `error_o == 0` assertion
was removed. Data integrity is still checked and passes (`sent` only advances on an accepted
write, so `data_i` holds until taken). These numbers are *not* evidence that no protocol
violations occurred.

## Running them

```bash
conda activate ravenoc          # cocotb 1.9.2 -- NOT 2.x, which removed cocotb.fork
cd agents/noc/ravenoc_bench
make fifo | make vc_buffer | make rr_arbiter | make all
```

Xcelium, not Verilator: upstream validates on Verilator 4.106 + cocotb 1.5.1, but keeping both
sides of the comparison on the same simulator is what makes it meaningful, and Xcelium is what
the Allo/Catapult cosim path already uses. One consequence — Verilator tolerates a bare `output`
net assigned in `always_comb`, Xcelium does not, which is why `src/router/input_datapath.sv`
needed `full_o`/`empty_o` patched to `output logic` (that module is not among the three measured
here; original saved at `/tmp/input_datapath.sv.orig`).

## Next

Phase 2 — build the Allo counterparts and measure against these. Hard constraint: each region
must take its flit arrays as `args=[...]`, or the synthesized top is `(clk, rst, done)` with no
data ports and cannot be driven at all.
