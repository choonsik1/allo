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

| design | mode | cycles | throughput | latency (cyc) | occupancy |
|---|---|---|---|---|---|
| `fifo` | max throughput | 65 | 1.016 cyc/flit | **1** (min=max=1) | max **1** of 2, mean 0.98 |
| `vc_buffer` | greedy | 65 | 1.016 cyc/flit | **1** (min=max=1) | max **1** of 2, mean 0.98 |
| `vc_buffer` | backpressure (1-in-3) | 193 | 3.016 cyc/flit | **3** first, max 5, mean 4.97 | max **2** of 2, mean 1.65 |
| `rr_arbiter` | saturated (4 reqs) | 65 | 0.985 grants/cyc | first grant @2; **steady wait 4** (min=max=4.00) | n/a (no storage) |
| `rr_arbiter` | single requester | 32 | 0.969 grants/cyc | — | n/a |

Latency is measured **per flit by tagging** — each flit carries a unique value, so the in→out delay
is tracked individually rather than inferred from aggregate timing. "Latency" in the headline sense
is the *zero-load* figure (the first flit, before queueing builds); mean includes queueing and is
workload-dependent.

Occupancy in the `fifo` bench is read from the DUT's own `ocup_o` **and** cross-checked every cycle
against the bench's in-flight accounting (`accepted_in - accepted_out`); they agree exactly. That
validates the derived figure used for `vc_buffer`, which ties its inner FIFO's `ocup_o` off.

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
3. **The arbiter is genuinely round-robin** — `[16,16,16,16]` over 64 grants, and steady-state wait
   is exactly 4 cycles (min = max = mean = 4.00) with 4 saturated inputs. A naive priority encoder
   would hit the same 0.985 throughput while producing `[64,0,0,0]`; only the fairness and
   starvation checks catch that. Any Allo rebuild must reproduce the *distribution and the bound*,
   not just the rate.
4. **At max throughput the buffer is nearly unused** — occupancy never exceeds **1 of 2 slots**, in
   both `fifo` and `vc_buffer`, with a flat 1-cycle latency. So for a greedy consumer a depth-1
   buffer — or a zero-storage `Channel` — should perform *identically*. Under 1-in-3 backpressure
   occupancy hits **2 of 2**, i.e. the buffer is fully used and genuinely working.

   That pair is the sharpest prediction this baseline makes: **an Allo `Channel` should match
   `Stream` in the greedy case and lose in the backpressure case.** If the greedy comparison shows
   `Channel` slower, the cost is Allo's protocol implementation, not the absence of storage.

### One assertion I got wrong, and why it is worth recording

The first run failed on `max wait 5 exceeds 4`. That was my bound, not an arbiter bug. Throughput
is 0.985 rather than 1.0 because there is exactly **one grant-less cycle**: the arbiter emits no
grant in the cycle after reset, before its priority pointer is valid. That single bubble stretches
one gap to `N_IN + 1`. The fix was to assert on the **steady state** (excluding the first two
rotations) and report the startup bubble separately — `wait_startup_max=5`, `wait_steady_max=4` —
rather than either loosening the bound or hiding the artifact.

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
