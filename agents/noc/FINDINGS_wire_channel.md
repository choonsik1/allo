# Wire / Channel / non-blocking — what we established, and what is still open

Written 2026-07-30. Covers the designs in `agents/noc/` that exercise the new link
concepts, and the toolchain gaps found while doing so. Read this before building another
Wire or Channel design — several of the constraints below are silent failures.

---

## 1. The headline result: a Wire has no synchronisation

**A `Wire` boundary does not give free modularity.** Established by controlled experiment
in `pe_split.py`: one computation (running dot product), one harness
(`feed → [mul ? acc] → sink`), three structures differing *only* at the mul→acc boundary.

| variant | boundary | JIT sim | csim |
|---|---|---|---|
| `mono`   | none (mul+acc one kernel) | PASS | **PASS** |
| `stream` | `Stream[int32,2]`         | PASS | **PASS** |
| `wire`   | `Wire[int32]`             | n/a  | **FAIL — all zeros** |

`mono` and `stream` bracket the result: the arithmetic *and* the 4-kernel split are both
sound, so the failure is attributable to the Wire boundary alone.

**Why**, from the emitted SystemC — neither loop has a `wait()` inside:

```cpp
// mul_0                        // acc_0
for (i1=0; i1<8; i1++) {        for (i2=0; i2<8; i2++) {
   ...Pop(fa), Pop(fb)...           int32_t v26 = v22.read();   // the wire
   v8.write(v21);   // the wire     ...Push(res)...
}                               }
```

Nothing makes `acc` iteration *i* coincide with `mul` iteration *i*. `acc`'s only blocking
op is its `Push` to `res`, which `sink` drains immediately — so `acc` races through all 8
reads before `mul` writes anything, and reads the signal's initial 0 every time.

**The lesson.** A `Stream`'s blocking `get`/`put` *are* the synchronisation — that is part
of what the FIFO buys, not just buffering. A `Wire` gives zero storage **and** zero
handshake, therefore **zero alignment**, and is only sound between kernels already
cycle-locked by something else.

`router_rvn_wire.py` passing csim was **luck** — its router and PE stayed in step because
other blocking ops paced both loops. Do not cite it as evidence that wires work.

### The sound idiom: Wire as a sideband on an ordering link

A Wire *is* sound when a blocking link supplies the barrier:

```
gen:   side.put(tag)    THEN  link.put(data)    # drive wire, THEN push
proc:  data = link.get() THEN tag = side.get()  # blocks, THEN read wire
```

`proc` cannot reach the wire read until `gen`'s push completed, and `gen` drove the wire
before pushing — so the value is current by construction. **Swap either pair and it is
racy.** Nothing in the type system enforces this; it is a discipline.

`wire_sideband.py` implements this (narrow FIFO + wire sideband, 48 → 32 FIFO bits for
identical behaviour) but is **NOT VALIDATED** — see §4.

---

## 2. What each concept actually buys

- **non-blocking (`try_*`)** — a PE can poll N ports without one idle port freezing it.
  Fully exercised: all six routers, validated on both backends.
- **`Channel`** — zero-buffer handshake, and *legal cyclic feedback* (a channel cycle is a
  dependency cycle, not a combinational loop, so backward congestion/credit signals work
  where a Wire cannot). `router_rvn_adaptchan.py` carries congestion as a runtime sideband
  over a Channel; T1–T6 pass on csim.
- **`Wire`** — zero storage, but see §1: only usable as a sideband on an ordering link, or
  between kernels with a shared cycle discipline that Allo does not currently enforce.

---

## 3. Designs, and their real status

| file | concepts | status |
|---|---|---|
| `router_rvn_ports/fused/vc/worm/mesh` | non-blocking, Stream | validated (JIT + csim) |
| `router_rvn_chan`, `router_rvn_fusedchan` | Channel | csim passed 2026-07-29 |
| `router_rvn_adaptchan` | Channel + runtime sideband | csim T1–T6 pass |
| `router_rvn_wire` | Wire | csim passed — **by luck, see §1** |
| `pe_split` | Wire vs Stream, controlled | **the §1 result** |
| `switch_comb` | Wire, CONNECT-HLS port | compiles, **hangs** (§4) |
| `wire_sideband` | Wire sideband idiom | **not validated** (§4) |

---

## 4. Open toolchain gaps (all silent or misleading)

1. **Wire-only loop bodies get no `wait()`.** The emitter's wait-insertion predicate covers
   Stream/Channel `try_*` but not Wire `get`/`put`, so a loop touching only wires runs all
   iterations in zero simulated time and deadlocks. `switch_comb.py` compiles and hangs for
   exactly this reason. One-line fix, same place as the `try_*` fix (d5291d3).
2. **`Channel` emission was crashing** (`getCatapultTypeName` assertion) with uncommitted
   `EmitSystemC.cpp` changes in the tree; `Stream` designs still emitted. This invalidated a
   whole bisect — always re-run a known-good file as a control before trusting a new failure.
3. **No implicit conversion from a link's `UInt` to a host array's `int32`.** Needs an
   explicit typed temp or the store fails with *"value to store must have the same type as
   memref element type"*. Hit by three separate designs.
4. **One host array per kernel.** Multi-array kernels HANG under csim while running fine on
   the JIT simulator. Every csim-proven shape has one array per kernel with compute kernels
   `args=[]`.
5. **Do not name locals `v0`/`v1`/`v2`…** — the SystemC emitter generates its own SSA names
   in that series; a collision emits `v2.write(...)` where `v2` is your int, not the port.
   Silent until g++.
6. **`wire_sideband.py` hangs under csim — BOTH variants.** The typed-temp fix (gap 3)
   cleared `sideband`'s build error, after which it hangs exactly like `packed`. The
   `packed` variant is the damning one: two kernels, one host array each, a single
   blocking `Stream`, no Wire anywhere — close to a shape that passed earlier in the day,
   and unexplained. Since the WIRE variant is not the one failing first, this is probably
   not a Wire problem at all. Parked; would need its own bisect against the known-good
   two-kernel control rather than more guessing.
7. **csynth still fails for every router.** Three distinct causes seen (memory/channel iomode
   collision, per-channel offset collision, a codegen assertion) — do not treat as one
   problem. NVIDIA's `WHVCRouter` does dozens of `PushNB`/`PopNB` per `SC_THREAD` iteration
   and *does* synthesise, so the shape is not inherently unschedulable. A MatchLib-style
   `run.tcl` was tried and did **not** help, so the difference is in the emitted code —
   remaining suspect is `wait()` at the top of the loop vs the bottom.

---

## 5. What I would do next

1. **Fix gap 4.1** (wire `wait()` predicate). Unblocks `switch_comb` and makes any wire
   result trustworthy rather than accidental.
2. **Validate `wire_sideband`.** It turns the negative §1 result into a positive one, and
   it is the only idiom in which a Wire is currently defensible.
3. **Simulator support for Channel/Wire.** Everything using the new concepts is SystemC-only
   — no `get_cycles()`, no fast iteration, no mesh scale. Any DSE cost model fitted today is
   fitted to buffered Streams only, which undercuts the whole direction.
4. **Credit-based flow control** (`Channel` both ways) — the only genuinely new *protocol*
   still unbuilt, and the one that would give a cost model two disciplines to compare.

**Caveat on all cost claims.** Everything above is *behavioural*. "A wire is cheaper than a
FIFO" is a structural argument from the declarations, not a measurement — that needs csynth,
which is still blocked.
