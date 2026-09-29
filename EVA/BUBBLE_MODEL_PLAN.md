# bubble_model — plan: EVA Vitis HLS rebuild in the Allo "always-fire / bubble" style

Goal: a second Vitis HLS version of the EVA rebuild that uses **only blocking stream
reads/writes**, with **a word sent on every stream every cycle** (a bubble when there is
nothing to say), exactly like `Allo/EVA/eva.py`. Purpose: an apples-to-apples
comparison between the Allo rebuild and a hand-written Vitis HLS implementation of the
*same execution model* (today's Vitis version uses a different model — event-driven
`read_nb` + FIFO backpressure — so QoR differences conflate model vs tool).

Reference model: `Allo/EVA/eva.py` (4×4, fused router+PE node, `for t in range(NSTEP)`
II=1 loop, three overlaid 4-dir networks).

## Status

The Allo rebuild is **complete and verified** — 8×8 RTL cosim bit-exact vs the golden EVA
RTL, with throughput and P&R numbers in [`results/final_chips/`](results/final_chips/) and
[`results/EVALUATION.md`](results/EVALUATION.md). Everything below is the original
architecture plan and findings log, kept for reference.

**Open technical point (II=1 forwarding safety).** For any II=1 (dep-false) build the
forwarding read `a = resq[fwd_a_ix]` is gated only by `inflight >= FP_LAT`, while the `resq`
slot commits `L` cycles after issue — so safety needs `FP_LAT >= L`. The shipped `FP_LAT=1`
with `L=3` sits on a ~1-stage scan-offset margin; NOSCHED builds dodge it (no pipeline
overlap). Note the final NOSCHED rtprime chip is **not** II=1 (its short-path Fmax is a
NOSCHED mirage); the real II=1 builds are the scheduled forwarding chips.

## 1. The two models, side by side

| | current Vitis_HLS (copied here) | eva.py bubble model (target) |
|---|---|---|
| stream discipline | `read_nb` polling, conditional `write` | blocking `get`/`put` on **every** link **every** iteration |
| validity | presence of a word = valid | in-band valid bit; all-zero word = bubble |
| backpressure | FIFO occupancy (implicit) | explicit **credit network** (3rd overlaid net, `cr_*`), `BUF_DEPTH=2` buffers + credit counters |
| node structure | 7 processes/node (4 `router_register` + mux + demux + PE) | **1 fused process/node** (router + core in one II=1 loop) |
| loop bound | free-running `while(true)` (`PE_FOREVER`, `COSIM_BOUND` hack) | bounded `for t in 0..NSTEP` — one iteration == one architectural cycle |
| systolic RX overflow | can't happen (blocking backpressure) | 2-deep `hold` buffer per dir; word **dropped** if full (program must schedule around it — same as eva.py) |
| time semantics | latency-insensitive, cycles decoupled | lockstep: iteration t of every process is architectural cycle t |

## 2. Node design (`eva_node.h`, templated `<ROW, COL>`)

Direct C++ port of eva.py's `node()` body, one `PE_FOREVER`-free bounded loop:

```
for (int t = 0; t < NSTEP; t++) {
#pragma HLS PIPELINE II=1
    // (1) PUT all 12 outputs from REGISTERED state (previous iteration's results):
    //     4 rtr_* packets, 4 sys_* words, 4 cr_* credit returns
    // (2) GET all 12 inputs (blocking):
    //     4 rtr packets -> rbuf[d] if rq && rbcnt<BUF_DEPTH
    //     4 credit ints -> rcred[o] += ...
    //     4 sys words   -> hold_v[d] if vld && hold_cnt<2   (drop otherwise)
    // (3) router section: axis-hit check (id vs row/col), core-deliver arbitration
    //     (S>N>E>W priority as in eva.py), per-output credit-gated forward,
    //     core-inject (csd_pkt) beats buffered traffic, pop/shift rbuf, credits out
    // (4) core section: fetch (pc/fetch_en/iter), scoreboard (dsmask/drf_full,
    //     hold_cnt as operand-valid), grant/stall (held-PC), ALU
    //     (ADD/SUB/MULT/MOV/GEQ/LT), RTR/CRTR inject, sys-TX (dst>=12),
    //     DRF writeback, packet-programming writeback (IRF/config/DRF preload)
    // (5) register next-cycle outputs (oe_r/ow_r/os_r/on_r, tx*_r, cr*_r)
}
```

Rules that make it deadlock-free (same as eva.py): every process puts **before** it
gets, outputs come from registers, all link streams are **depth 2**. First iteration
puts init values (bubbles; credit streams init `BUF_DEPTH` from the *downstream* side).

Key port decisions:
- **Types** (`bubble_types.h`, new — don't reuse `pe_types.h` structs):
  - `sys_word_t = ap_uint<1+DATA_W>` (bit0 = vld) or struct `{bool vld; word_t data;}` —
    struct preferred for readability; HLS packs it to the same wires either way.
  - `rtr_pkt_t`: add the missing **`rq` valid bit** — `{rq, id(4b), mode, addr(4b), data}`
    (eva.py PKT layout LSB-first: data, addr, mode, id, rq). Bubble = rq==0.
  - `credit_t = ap_uint<2>` (0..BUF_DEPTH credits returned per cycle).
  - Constants: `M=N=4`, `NSTEP` (runtime arg or template), `BUF_DEPTH=2`,
    `DRF_DEPTH=IRF_DEPTH=8`, `word_t` swappable (fp16 default, fp32 variant).
- **ID check**: eva.py compares pkt id (4b) against `col_id`/`row_id` per axis
  (`axis[]={col,col,row,row}`) — no perimeter-bit special case inside the node
  (perimeter exit happens by forwarding off the edge). Port that, not the current
  `router_register.cpp` `id[3]` perimeter test.
- **Pragmas**: `ARRAY_PARTITION complete` on `drf, drf_full, irf, rbuf, rbcnt, rcred,
  hold_v, hold_cnt` (mirror of `s.partition` list in `get_scheduled_eva`), II=1 pipeline.
- **fp16 mult**: Allo's II=1 comes from a **combinational** fp16 multiply
  (memory: bind_op latency=0 reproduces it). Decide per experiment arm:
  default-latency mult (fair "what the tool does") vs `BIND_OP impl=... latency=0`
  (fair "same hardware as Allo"). Plan: build BOTH, it's one pragma.

## 3. Mesh + perimeter (`mesh_4x4_bubble.cpp`)

- One flat `DATAFLOW` region: 16 `eva_node<R,C>` + 16 perimeter processes.
- Three overlaid stream planes × 4 directions, Allo link-index convention
  (IN=[i,j], OUT=[i,j+1]): `sys_e/w[M][N+1]`, `sys_s/n[M+1][N]`, same shape for
  `rtr_*` and `cr_*`. All `#pragma HLS STREAM depth=2`.
- Perimeter = direct ports of eva.py's 16 kernels:
  - `drv_w/e/n/s`: per-lane arrays `in_X[M][LANELEN]` + valid mask `iv_X` → put a
    (vld,data) word every cycle, bubble past LANELEN.
  - `col_w/e/n/s`: get every cycle, append to `out_X[lane][k++]` when vld.
  - `rdrv_*`: credit-gated packet injection from `rin_X[M][LANELEN]` (int32-packed
    packets, same encoding as the Allo tests) — get credit every cycle, put packet
    or bubble.
  - `rclc_*`: put credit return every cycle (init `BUF_DEPTH`), get packet, record
    to `rout_X` when rq.
- Top signature mirrors `run_eva()`'s argument set (in/iv/out per side + rin/rout per
  side) so **the same test vectors and router-packet programs drive both
  implementations**. Memory arrays as AXI/ap_memory ports like today's tile tops.

## 4. Testbench + verification

- `tb/tb_mesh_4x4_bubble.cpp`: generate the same stimulus as an Allo test
  (start with the dependent-mult / MMM program from `Allo/EVA/eva_tests.py` /
  `eva_workloads.py`), run, compare outputs. Ideally: dump the exact
  `ins/ivs/rins` arrays from a passing Allo simulator run to `.mem` files and replay
  them here — bit-identical cross-check between the two implementations.
- **csim will NOT work for the mesh** (blocking feedback between dataflow processes;
  Vitis csim runs them sequentially — same limitation as today's 2-process node).
  Verification path = **cosim only** for mesh; single `eva_node` can be csim'd with a
  tb that pre-loads all 12 input streams per iteration and drains outputs.
- Bounded `for t < NSTEP` loops mean cosim terminates naturally — **no
  `COSIM_BOUND`/`PE_FOREVER` machinery needed** in this model (keep `ap_ctrl_hs`).

## 5. Build + comparison experiments

- `tcl/run_mesh_4x4_bubble.tcl` (2023.2 flow) + `vitis25` .ini variant (see
  `tcl/vitis25/`); same part as the Allo routed runs for the comparison table.
- Comparison arms (all routed, not csynth-est — per the fairness-audit finding):
  1. Allo eva.py (existing routed numbers: fp16 ~306–355 MHz, II=1).
  2. This bubble model, default fp16 mult latency.
  3. This bubble model, `bind_op latency=0` (Allo-equivalent combinational mult).
  4. Existing event-driven Vitis version (tile numbers) — context row.
- Report: Fmax, II, LUT/FF/DSP/BRAM, LOC, and a short "expressiveness" note
  (what each style forced us to write).

## 6. Work order

1. `bubble_types.h` (types + constants + packing helpers). 
2. `eva_node.h` fused node — csynth solo first: check II=1 and the 12-put/12-get
   schedule before any wiring.
3. Single-node csim tb (streams pre-loaded per cycle) — functional check vs a
   hand-computed trace of 2–3 instructions + one routed packet.
4. `mesh_4x4_bubble.cpp` + perimeter kernels + top.
5. Cosim with the MMM/dependent-mult program replayed from Allo test vectors.
6. FFT-8 program port (packets from `eva_tests.py` fft8 loader) — optional stretch.
7. csynth + route both mult arms; fill the comparison table; update this file +
   README with results.

## 🚨 FINDING 2026-07-05: always-fire RTL DEADLOCKS in cosim (read-before-write)

mesh_1x1_bubble cosim (test_passthrough replay, EVA_NSTEP=55): RTL deadlock,
cycle = node blocked reading cr_s1 <-> rclc_s blocked reading rtr_s1.
ROOT CAUSE (verbose.sched.rpt, cosim project): Vitis schedules the node loop
as ALL 12 stream READS in ST_2, ALL 12 WRITES in ST_3 — the INVERSE of the C
put-before-get order (cross-stream FIFO order is not preserved; a stalled
read freezes the same iteration's later write states) -> the credit loop has
zero initial tokens -> deadlock. EVA_NOPIPE (unpipelined) changes nothing:
same state order. NOT a wiring bug; the C model is deadlock-free (Allo
simulator threads run it fine).
IMPLICATION: the Allo-generated eva.py RTL has the same source structure and
has NEVER been cosim'd (QoR baseline is csynth+route only) -> it plausibly
deadlocks identically. TEST IT: regenerate kernel.cpp at M=N=1/NSTEP=55,
drive with the SAME tb (ALLOW_EMPTY flow), cosim.
FIX DIRECTION for our arm: writes must land in an EARLIER FSM state than
reads (then pipelining gives 1-token slack per iteration); candidates =
forced write-stage (latency region pragma), write_nb, or the event-driven
read_nb structure. UNSOLVED as of session end.

✅ FIXED (EVA_PRIME arm, cosim PASS 2026-07-05): initial-token priming
(user's idea). Recipe, validated stepwise: (1) EVERY process pre-puts ONE
NEUTRAL word per output stream before its loop (bubble pkt rq=0 / sys vld=0
/ credit 0 — NOT init reg values: those double-prime the credit plane ->
silent rbuf drops). One token per EDGE, incl. rdrv's rtr edge even though
its put data-depends on its get. (2) rdrv loop PIPELINE off under EVA_PRIME:
its pipelined iterLat=4 puts the write 3 iters behind the read, and a stall
pipeline freezes pending writes when a read blocks -> lookahead would need
iterLat tokens (brittle); unpipelining makes lookahead 0. Loop bodies
UNTOUCHED. Cost: +1 cycle link latency vs eva.py (cycle-exact replay shifts
1/hop; functional tests unaffected - data-driven stall + compacting
collectors). Failed alternatives for the record: LATENCY max=0 region
(packs puts into one state but AFTER the reads), EVA_NOPIPE (state order
unchanged). TODO: prime the 4-lane rtr_drv/rtr_clc for mesh 4x4; csynth QoR
of EVA_PRIME arm; PORT TO eva.py (pre-loop puts are legal Allo -> this fix
IS Allo-expressible, unlike read_nb/split-process).

✅ ALLO SIDE ALSO FIXED (2026-07-05 late): priming ported to eva.py (9 PRIME
edits: node 12 neutral pre-puts, rdrv_* bubble pkt/lane, rclc_* 0-credit/
lane) + `config_compile -pipeline_loops 0` in the cosim tcl (perimeter
pipelining is Vitis AUTO, not Allo-requested -> schedule-neutral disable;
node keeps s.pipeline II=1). allo_1x1_cosim cosim PASS - FIRST EXECUTING
Allo-generated EVA RTL. ⚠ REGRESSION: primed eva.py sim = 6/7, SHUFFLE
FAILS (out_e[2]=[0,0]) - the +1 link latency changes operand skew between
different-hop-count paths -> sync-slot/hold-drop loses tokens. RESOLVED -> END-PUT variant, in a SEPARATE FILE `Allo/EVA/eva_prime.py`
(eva.py reverted to committed state, untouched): node pre-loop put block
(init regs incl BUF_DEPTH credits) + loop puts moved to iteration END +
rclc_* pre-put/put-after-get; rdrv/drv/col untouched (5 edit sites).
`run_tests_prime.py` = suite shim (aliases eva->eva_prime).
✅ VALIDATED 2026-07-05: sim suite 7/7 (SHUFFLE RESTORED - streams bit-
identical, as designed) AND 1x1 RTL cosim PASS (regenerated kernel).
eva_prime.py = first Allo EVA source that both passes the full functional
suite AND generates RTL that executes. Note for later: II=1 comb-arm node
pipelines deep enough that its own read-lookahead may need the same
unpipeline/extra-token treatment when it gets cosim'd.

FULL-SUITE REPLAY (allo_cosim_suite/, 2026-07-05 night): dump_vectors.py
captures sim-golden in/out vectors per test; tb_replay.cpp + run_suite.py
replay them against the generated RTL bit-for-bit. Result: NO deadlocks
anywhere (priming scales to 4x4/32 processes); 6/9 bit-exact PASS
(passthrough,row x2,router_1,shuffle,mesh); 3 FAIL (router_0, core_send,
turn) -> root cause = 🐛 NEW ALLO BUG INSTANCE: UInt->int32 array STORE
sign-extends in vhls emission but zero-extends in sim (rout_e[0] =
0xffe53c00 vs 0x03e53c00, low 26 bits identical; only rq=1 packets recorded
to rout_* expose it = exactly the 3 transit/inject tests). Same class as
uint_slice_signed_emission. WORKAROUND in eva_prime.py: PMASK
((1<<PKT_W)-1) on the 4 rclc rout stores (no-op in sim -> vectors stay
valid). TODO Allo/bugs minimal repro (uint store variant).
✅ FINAL 2026-07-05: after PMASK, router_0/core_send_0/turn_0 all PASS ->
**SUITE 9/9 BIT-EXACT, 0 DEADLOCKS** = the eva_prime RTL reproduces the
Allo simulator word-for-word on the ENTIRE functional suite incl. the 4x4
mesh. NEXT: MMM/FFT (eva_workloads) through the same dump/replay pipeline;
parked 4x4 csynth QoR compare (allo_prj_4x4 generated, not csynth'd);
end-put port to the C++ bubble model + 4-lane perimeter; Allo/bugs repro.

CONFIRMED on the ALLO side (allo_1x1_cosim/, same tb): the Allo-generated
1x1 kernel deadlocks with the IDENTICAL cycle (node_0_0 <-> rclc_s_0 credit
loop, same sim timestamp). => BOTH comparison arms' QoR numbers describe RTL
that HANGS under the always-fire protocol; the table needs an "RTL executes"
row, currently NO for both. Also found en route: Allo emits fp16 bitcasts as
`union { uint16_t from; half to; }` (deleted default ctor) -> g++8.3 refuses
-> ALL Allo fp16 designs are un-cosim-able as generated; scripted `= {}`
patch in allo_1x1_cosim/gen_kernel.py (semantics-neutral, documented);
TODO minimal repro in Allo/bugs/ (fp16 union emission).

## 🏆 2026-07-08c: eva_sb_syscredit — golden-faithful SYS-CREDIT chip WORKS

Third final chip (scoreboard_allo_eva_final/eva_sb_syscredit.py): the sys
plane gets the rtr plane's credit protocol = registered equivalent of
golden rq/gt (stall-not-drop). Node: per-dir pending-TX slot + retire
structural stall + consume-returns (init 2 = sync_register capacity);
drivers = golden-tb equivalents (hold value until credited, never before
its original slot); collectors return credits (rclc pattern). All existing
machinery kept (end-put prime incl. new scr planes, Option-A knobs,
scoreboard, PMASK, narrowing). NB-reads were considered and REJECTED for
this: loss happens at the sender's unconditional fire, NB read fixes
nothing; NB primitives (non-blocking (NB) Allo branch) would enable the EVENT-DRIVEN
model in Allo instead — a possible 4th chip, different model.
VALIDATED (sim): flood-rate (1 word/cycle — the eva_sb killer) 4/4 PASS
both debug kernels; **MMM PASSES with the ORIGINAL unmodified schedule**,
only NSTEP x4 (lossless => late is safe; "run longer" replaces retiming).
✅ VALIDATED 2026-07-08 eve: sim 7/7 suite UNCHANGED + MMM(orig schedule)
+ FFT-8(err .0019 = baseline) + flood 4/4; RTL 2025.1 deep-prime: II=1
kept (retire-stall costs nothing), cosim PASS no deadlock — NSTEP 120->200
(credit RTT now on data/output paths: perimeter ~2 words/RTT). Open: fft2r
sim, routed timing, QoR delta vs eva_sb.

## 🔑 FINDING 2026-07-08b: golden EVA sys plane = BACKPRESSURE, drop-on-full is an eva.py DEVIATION

Checked EVA_untouched (tb/pe_group/mmm/tb_pe_group_mmm.sv + rtl/pe_core/
systolic_rx.sv + components sync_register.sv): golden systolic links use an
rq/gt HANDSHAKE - sync_register has 2 slots (prim+oflw, = our depth-2 hold)
and `wr_gt_o = ~oflw_data_vld`, write only when granted -> full buffer
STALLS THE SENDER (tb holds each activation until gt), nothing is dropped,
NO spacing constants exist in the golden flow. Hardware self-pacing.
=> eva.py's "hold-full DROPS" is NOT a golden quirk - it is a MODELING
DEVIATION introduced by the always-fire lockstep simplification (elastic
rq/gt -> fire-every-cycle + drop). Both our chips faithfully port eva.py,
so: equivalent to eva.py EXACTLY; equivalent to golden ONLY under schedules
that never overrun (all original workloads - hence bit-exact replays pass).
Under overload golden stalls losslessly, ours drops silently - which is
exactly why the (slower) scoreboard PE broke workloads that a golden-style
chip would just have run slower. Ironic: the OLD event-driven Vitis model
(read_nb + FIFO backpressure) is CLOSER to golden on this axis than the
always-fire model. The workload spacing constants in eva_workloads are
artifacts of the deviation, not EVA architecture.
Options: (a) document deviation, keep model (Allo-vs-Vitis comparison holds
- both sides share the model); (b) golden-faithful variant = credit/elastic
sys plane (like the rtr plane already has). Belongs in
EVA_VS_HLS_DEVIATIONS.md as a headline item.

## 🔑 FINDING 2026-07-08: scoreboard "workload failures" = RATE MISMATCH, not a bug

mmmr/fft2r/fft8r FAIL in SIM vs eva_sb (mmm all-zero) while 7/7 tests pass.
Bisection (scoreboard_allo_eva_final/debug_sb.py, minimal RAW + preload
kernels vs eva_prime control): every emitted value CORRECT, but exactly the
tail values missing at ANY margin -> the inputs, not the outputs. Root
cause: a RAW-dependent instruction costs ~1+SB_DEPTH arch cycles (consumer
holds PC until producer retires), so serial kernels run ~6x fewer instrs/
cycle; EVA workload stimuli are RATE-MATCHED to the original PE (e.g. MMM
feeds X at 4-cycle spacing = old kernel period), and the always-fire sys
plane has NO backpressure - depth-2 holds DROP on full (golden quirk) ->
surplus inputs silently discarded. PROOF: same kernels with inputs spaced
8 cycles = 4/4 PASS on eva_sb.
Consequences: (1) scoreboard chip needs rate-scaled stimulus (spacing x
~(SB_DEPTH+2), NSTEP scaled) - stimulus-side only; (2) HONEST METRIC:
clocks-per-result, not II - scoreboard II=1 x ~6 arch-cycles ~ 6 clk/instr
vs original II=4 x 1 = 4 clk/instr on SERIAL kernels; II=1 pays off only
with ILP >= SB_DEPTH or interleaved streams; (3) no-backpressure + rate
mismatch = silent data loss (architecture property worth reporting).

## 🏆 STATUS 2026-07-08: ALLO SCOREBOARD II=1 COSIM PASS (Vitis 2025.1)

allo_bubble_scoreboard, genuine 2025.1: node II=1 (iterLat 6) with scripted
dependence-false pragmas (resq/cmpq/res/wb — no Allo primitive; gen_kernel.py
injects, --no-dep-pragma = control) + uint8 narrowing + OPTION-A deep prime
(PRIME_TOKENS=6, STREAM_DEPTH=8, NSTEP=120, tb PC=80 per credit-RTT law)
→ passthrough replay PASS. Full mirror of the C++ result. Timing est −9.95
(retire→forward→issue chain) — routed pre-narrowing was ~186 MHz; P&R rerun
post-narrowing = next QoR datapoint.

## STATUS 2026-07-06: SCOREBOARD variants — II 4->3 BOTH SIDES, cosim PASS

Single-process scoreboard (pe_core.cpp idiom: metadata sb queue depth 5 +
resq/cmpq rings + retire-before-fetch + RAW/cmp_busy hold-PC-and-bubble),
always-fire shell and priming untouched. `vitis_bubble_scoreboard/` (C++,
~90 lines in eva_node.h, DEPENDENCE inter false on rings) and
`allo_bubble_scoreboard/eva_prime_sb.py` (same structure, parallel arrays,
NO dependence primitive needed!). RESULTS (2023.2/xcu280/3.33ns, real
pipelined fp cores): Vitis solo node II=3 est ~215MHz, cosim PASS; Allo 1x1
node II=3 iterLat 6, cosim PASS, sim suite 7/7. Comb arm obsoleted (fake
II at 46MHz). II=1 shot = 2025.1 scheduler (pe_core precedent). Finding:
scoreboard pattern FULLY Allo-expressible incl. II gain on 2023.2 — the
missing s.dependence primitive did NOT block II=3.

## STATUS 2026-07-05b: mesh_1x1_bubble csynth'd, schedules now IDENTICAL to Allo

`mesh_1x1_bubble.cpp` (1 node + full 12-process perimeter) + `tcl/run_mesh_1x1.tcl`
(2 arms, archives csynth.rpt to $RPT_DIR, default `reports_mesh_1x1/`).
`eva_node.h` irf partition REMOVED -> partition list == get_scheduled_eva's.
Result (2023.2/xcu280/3.33ns, perimeter loops all II=1 in every config):
  - WITH irf partitioned (before): node II=3 default / II=1 comb.
  - irf UNPARTITIONED (now):       node II=4 default / II=2 comb.
  => irf partition = exactly 1 II on both arms; hand-Vitis default arm now
  matches the honest Allo baseline II=4 EXACTLY under the identical schedule.
  irf partition is expressible in BOTH tools (s.partition) -> best-effort table
  row should partition irf on both sides.

## STATUS 2026-07-05: `eva_perimeter.h` DONE (not csynth'd)

Verbatim port of eva.py's 16 perimeter kernels as 4 functions x 4 side
instances: `sys_drv`(drv_*:314-352), `sys_col`(col_*:354-392),
`rtr_drv`(rdrv_*:394-448), `rtr_clc`(rclc_*:450-513). Per-lane helpers =
the meta_for body; lane order/put-before-get/BUF_DEPTH-priming/rq==0-skip
quirks preserved. g++ -fsyntax-only PASS solo + with eva_node.h.
⚠ scratch `Allo/scratch/rebuild/EVA/eva.py` still has the OLD broken guards
(lines 501/505) — only `Allo/EVA/eva.py` (302/306) is fixed; fix uncommitted.

## STATUS 2026-07-04 (session end)

Done: folder + final-file copies; `bubble_types.h` COMPLETE (packed `ap_uint`
words — chosen over structs for verbatim eva.py port + bit-identical vector
replay; ptr-pun bitcast helpers per rtr_driver.cpp:72 idiom; `EVA_NSTEP`
macro-overridable). `eva_node.h` COMPLETE (verbatim node() port per the crib:
templated <ROW,COL>, 24 stream ports, put-12-before-get-12, S>N>E>W deliver,
id=s2 inject quirk, sys-drop-on-full kept, DRF &7 masks, EVA_COMB_FP arm w/
BIND_OP fabric latency=0 — impl choice UNCONFIRMED until csynth); g++
-fsyntax-only vs 2023.2 headers PASS. NOT yet csynth'd.
NOTE: user wants code written ~5 lines per edit so they can follow the diffs.

## Porting crib: eva.py node() -> eva_node<ROW,COL> (verified against eva.py)

Node port naming: `*_in_X` = word arriving FROM side X; `*_out_X` = word
leaving TOWARD side X; `cr_out_X` = credit toward X (pays for my X input);
`cr_in_X` = credit from X (replenishes my X output).

- eva.py registered outs -> ports: `oe_r`->rtr_out_e, `ow_r`->rtr_out_w,
  `os_r`->rtr_out_s, `on_r`->rtr_out_n; `tx{e,w,s,n}_r`->sys_out_{e,w,s,n};
  CREDITS CROSS: `cre_r`->**cr_out_w** (eva.py puts cr_e[i,j], consumed by the
  WEST neighbor), `crw_r`->**cr_out_e**, `crs_r`->**cr_out_n**, `crn_r`->**cr_out_s**.
- gets: p_w/p_e/p_n/p_s = rtr_in_w/e/n/s; rcred[0]+=cr_in_e, [1]+=cr_in_w,
  [2]+=cr_in_s, [3]+=cr_in_n; rx_w/e/n/s = sys_in_w/e/n/s.
- Index conventions (three DIFFERENT d/o maps — do not mix):
  - router input d (fin/rbuf/rbcnt/pop/ret): 0=from-W, 1=E, 2=N, 3=S;
    axis[] = {COL, COL, ROW, ROW} (row links match col id, col links row id).
  - router output o (o_out/rcred): 0=to-E, 1=W, 2=S, 3=N. Forwarding is
    STRAIGHT-THROUGH d==o (from-W -> to-E etc.); turns are core-mediated only.
  - systolic hold d (hold_v/hold_cnt): 0=top, 1=btm, 2=lft, 3=rgt, filled from
    rx_n, rx_s, rx_w, rx_e; operand src>=12 reads hold_v[src&3][0].
- Core-deliver priority: hit[3] > hit[2] > hit[1] > hit[0] (S > N > E > W);
  delivered head is popped WITHOUT consuming a credit (pop[crv_in]=1 only).
- Inject: idir = 3 - csd_dir (op&3: 0=up->N out, 1=down->S, 2=left->W,
  3=right->E); inject beats through-traffic on its output port, needs credit;
  csd_pkt fields: data=res, addr=dst, **id=s2**, mode=0, rq=res_vld.
- Sys TX (dst>=12): dst&3: 0=tx_n, 1=tx_s, 2=tx_w, 3=tx_e.
- Init: rcred[]=0 but registered credit outs start at BUF_DEPTH (first put
  primes the neighbors); everything else 0; per-iteration order is put-12 ->
  get-12 -> router -> systolic ingress -> fetch/scoreboard -> ALU -> dest ->
  crv writeback (crv_* are same-iteration wires, not registers).
- DRF indices 8..11 are OOB in eva.py (relies on programs) -> mask `&7` in C++.
- crv writeback: mode=1: addr[3]->irf[addr&7]=raw16; addr==0-> dsmask=raw&0xFF,
  cfg_isz=(raw>>8)&7, raw[15]->fetch_en=1+zero counters; addr==1->cfg_itsz=raw&0xFF.
  mode=0: sync slot (dsmask[addr] && !full) or plain drf write.
- Expect **II=3 with default fp16 mult** (latency-4); add an `EVA_COMB_FP`
  macro arm wrapping `#pragma HLS BIND_OP variable=res op=hmul/hadd/hsub
  latency=0` for the Allo-equivalent combinational arm.

Next concrete steps:
1. ~~`eva_node.h`~~ DONE (see STATUS).
2. ~~`eva_node_solo.cpp` + `tcl/run_eva_node.tcl`~~ DONE — csynth 2023.2
   results (xcu280, 3.33 ns target, solo node, csynth-EST only):
   - default arm: **II=3** (loop depth 5), est clock 5.19 ns (~193 MHz est),
     8-step latency 29 cyc, 3.7k FF / 8.7k LUT, 0 DSP/BRAM.
   - EVA_COMB_FP arm: **II=1** (loop depth 3) — BIND_OP fabric latency=0
     ACCEPTED; est clock 22.38 ns (csynth-est; routed is ground truth — the
     Allo comb design also estimated far worse than its 306-355 MHz routed),
     8-step latency 13 cyc, 2.4k FF / 8.4k LUT.
   Matches the II=3-vs-II=1 prediction from the fp16-mult finding exactly.
3. Then single-node csim tb, then mesh (§6 steps 3-7); routed numbers for
   the comparison table come from the mesh/tile runs, not the solo node.

## 🚨 FINDING 2026-07-04: the Allo EVA QoR baseline is INVALID (dead-PE DCE)

Investigating why our comb arm estimated 22.4ns while "Allo estimated ~6.2ns":
csynth'd the committed Allo `kernel.cpp` `node_0_0` standalone (same
2023.2/xcu280/3.33ns) → II=1, est 161.8MHz, but **zero fp ops in the schedule,
no drf registers in the RTL, and `irf` emitted as RAM_AUTO_0R0W** (0 read / 0
write ports). Root cause: Allo emits eva.py's UInt bit-slices as SIGNED
(`int16_t v246 = pkt(15,0); int32_t crv_raw = v246;` = sign-extend), so
`(crv_raw >> 15) == 1` compares -1==1 when bit15 is set → `fetch_en = 1`
unreachable (same for `(crv_addr >> 3) == 1` → IRF writes dead) → Vitis DCE'd
the entire instruction/ALU/DRF datapath. The Allo simulator treats the same
slice as unsigned (sim passes), so the divergence was invisible without cosim.

Consequences for THIS plan: comparison arm 1 (Allo 306-355MHz II=1) is a
router-with-dead-PE number — the table must use a REBUILT Allo baseline with
signedness-immune guards in eva.py (`(crv_raw & 0x8000) != 0`,
`(crv_addr >> 3) & 1 == 1`) — and our solo results (default II=3; bind_op
latency=0 II=1 with hadd est 19.7ns) are the first HONEST Vitis numbers for
this execution model. The old flat-comb 194MHz routed datapoint remains valid.
Follow-ups: minimal Allo/bugs repro for the signed-slice emission; fix eva.py;
rebuild + re-route Allo baseline.

UPDATE 2026-07-05 — baseline REBUILT with fixed guards (`((x>>15)&1)==1`
style, eva.py 2-line fix; sim 7/7 PASS unchanged; repro committed as
`Allo/bugs/uint_slice_signed_emission.py`). Honest Allo csynth
(2023.2/xcu280/3.33ns): datapath ALIVE (hadd/hmul/hsub 16_4_no_dsp latency-4,
0 DSP), node loop **II=4** (depth 5, was "II=1" gutted), node 4797 FF/8927 LUT
(was 1134/4492 gutted), top est Fmax 180 MHz. Same 200-880 drf+fetch_en
recurrences as our hand-written default arm. csynth scoreboard so far:
hand-written bubble node II=3 < Allo II=4; both need bind_op latency=0 for
II=1 (which Allo cannot express — no bind_op primitive). ROUTED (same run,
export_design -flow impl): **~302.7 MHz timing MET** (CP 3.304ns, WNS +0.026),
36.3K LUT / 34.1K FF / 0 DSP; crit path = int CARRY8 into node irf write,
fp16 pipelined (latency-4) stays off-path — honest cost is II=4, not Fmax.
Reports archived: `Allo/scratch/rebuild/EVA/guardfix_reports/` (out.prj
deleted). Comparison arm 1 for the table = THIS baseline (II=4 @ ~303 MHz).

## Open items / risks

- eva.py's systolic net **drops** words when a hold buffer is full — intentional
  model property, must NOT be "fixed" here or the comparison breaks.
- eva.py bit-slice writeback quirks (e.g. `csd_pkt[Ty.bits+5 : Ty.bits+9] = s2` — id
  field carries s2) must be ported verbatim, including field offsets.
- Node loop carries everything (drf, rbuf, credits) — II=1 depends on the whole
  body fitting one cycle of dependence; if HLS reports II>1, check first for
  false inter-array dependences (add `DEPENDENCE false` on partitioned arrays).
- The original files copied into this folder are the *starting reference*; the bubble
  model is a rewrite, not an edit — expect `router.cpp`/`router_register.cpp`/
  `pe_core.cpp` to be superseded by `eva_node.h` and eventually deleted from here.
