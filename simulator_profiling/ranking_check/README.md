# Ranking-agreement check — does our cost model order designs like the tools do?

**Question.** The cost model exists to *rank* candidate designs for DSE, so a constant
magnitude offset is harmless but a reordering is fatal. And we calibrate against **Vitis**
while EVA ships through **Catapult** — do the two schedulers even agree on ordering?

**Answer (2026-07-30): sim vs Vitis is perfect over 5 designs. The Catapult half is
BLOCKED and remains unresolved.**

## Designs

Five acyclic blocking producer/consumer variants, spreading element count and per-element
compute cost (`rank_designs.py`):

| design | elements | consumer work |
|---|---|---|
| `d1_int4` | 4 | `+ 1` |
| `d2_int16` | 16 | `+ 1` |
| `d3_fmul4` | 4 | `* 3.0` |
| `d4_fdiv4` | 4 | `100.0 / (v+1)` |
| `d5_fmul16` | 16 | `* 3.0` |

## Results

| design | our sim | Vitis csynth | Catapult |
|---|---|---|---|
| `d1_int4` | 5 | 8 | 10 c-steps |
| `d3_fmul4` | 8 | 16 | **float blocker** |
| `d2_int16` | 17 | 20 | 34 c-steps |
| `d5_fmul16` | 20 | 28 | **float blocker** |
| `d4_fdiv4` | 23 | 31 | **float blocker** |

Kendall τ over concordant/discordant pairs:

```
sim vs Vitis     : 5 designs, 10 concordant / 0 discordant  -> tau = +1.00
sim vs Catapult  : 2 designs,  1 concordant / 0 discordant  -> tau = +1.00
Vitis vs Catapult: 2 designs,  1 concordant / 0 discordant  -> tau = +1.00
```

## What this does and does not establish

**Established: our cost model ranks exactly like Vitis** across all 5 designs (10/10
pairs), despite magnitudes being 0.6–0.75× low. For DSE *ranking* — the actual use — the
model is already fit for purpose on this class of design. That is a stronger result than
the single 7-vs-6 calibration point suggested.

**NOT established: that the Vitis calibration transfers to Catapult.** Only 2 of 5
designs synthesise under Catapult, giving exactly **one** comparable pair. One pair cannot
distinguish agreement from luck.

**And the gap is exactly where it hurts.** The three designs Catapult rejects are all the
**float** ones — and float latencies are precisely where two schedulers are most likely to
disagree. So the check is blocked on the sub-population most likely to break it. The
int-only evidence is consistent but close to uninformative.

## Why Catapult rejects them

```
Error: no suitable constructor exists to convert from "int32_t" to "ac_ieee_float<binary32>"
Error: no operator "/" matches these operands: float / ac_ieee_float<binary32>
```

The known float-marshalling blocker (`Wrapped<ac_ieee_float>` specialisation). **Fixing it
unblocks this check** — that is the cheapest route to answering the Catapult question.

Also note Catapult reports `Latency = -1` (unbounded) for these Connections designs, the
same shape as Vitis's `undef` for non-blocking. The usable number is the scheduled
**c-step length** of the PE (`Prescheduled SEQUENTIAL '/cons_0/run' (total length N
c-steps)`), not a total latency.

## Environment fix needed to run Catapult at all

Catapult 2024.2 ships `mc_scverify.h`, which includes `sysc_sim.h` — **but does not ship
`sysc_sim.h`**. Synthesis fails at `go analyze` with `CRD-1696`. Workaround: a local stub
(`sysc_sim.h` here) plus `-I.` in `Input/CompilerFlags`.

## Reproduce

```bash
conda activate allo && export LLVM_BUILD_DIR=... PYTHONPATH=/home/zsm9/allo_sup
python rank_designs.py /scratch/rank_out          # sim makespans + emits vhls projects
python emit_sysc.py                               # emits SystemC for the Catapult side
# Vitis:    cd /scratch/rank_out/<d>.prj && vitis_hls -f run.tcl
# Catapult: cp catapult_synth.tcl sysc_sim.h <dir> && catapult -shell -f catapult_synth.tcl
```
