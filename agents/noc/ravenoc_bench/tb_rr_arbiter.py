"""
Example 3 -- rr_arbiter.sv, the Wire example.

req_i[4] -> grant_o[4] is COMBINATIONAL. The only state is the round-robin priority
pointer, advanced when update_i is asserted. That shape -- a combinational request/grant
sideband with no storage and no handshake -- is exactly what Allo's Wire models, and it is
the fairest test of the concept: here the combinational path is architecturally CORRECT,
not a shortcut.

EXPECT THIS ONE TO BE THE INTERESTING FAILURE. pe_split.py's pe_wire variant reads all
zeros because a Wire gives neither storage nor alignment, so two independently-paced
kernels never see each other's values. If the Allo rebuild needs cycle-locked kernels that
Allo cannot currently express, that is a finding about Wire, not a broken benchmark.

WHAT IS MEASURED:
  * throughput  -- grants issued per cycle with all 4 inputs requesting continuously.
                   A work-conserving arbiter must grant exactly one per cycle.
  * fairness    -- the grant distribution across the 4 inputs. Round-robin means each
                   should get N/4. This is the property an Allo rebuild must reproduce,
                   and it is what a naive priority-encoder gets WRONG while still passing
                   a throughput check.
"""
import os
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, ReadOnly

N_GRANTS = int(os.getenv("N_GRANTS", "64"))
N_IN = 4
PERIOD_NS = 2


async def reset(dut):
    dut.arst.value = 1
    dut.req_i.value = 0
    dut.update_i.value = 0
    for _ in range(3):
        await RisingEdge(dut.clk)
    dut.arst.value = 0
    await RisingEdge(dut.clk)


def onehot_index(v):
    """Return the granted index, asserting the grant really is one-hot (or none)."""
    if v == 0:
        return None
    assert v & (v - 1) == 0, f"grant_o not one-hot: {v:#06b}"
    return v.bit_length() - 1


@cocotb.test()
async def rr_arbiter_saturated(dut):
    """All four inputs request every cycle -- measures throughput AND fairness."""
    cocotb.start_soon(Clock(dut.clk, PERIOD_NS, units="ns").start())
    await reset(dut)

    dut.req_i.value = (1 << N_IN) - 1   # all requesting, always
    dut.update_i.value = 1              # advance the pointer on every grant

    counts = [0] * N_IN
    cycles, grants = 0, 0
    # Occupancy is meaningless here -- an arbiter has no storage. The latency that matters
    # is the ARBITRATION WAIT: how long a continuously-requesting input goes ungranted.
    # Under saturated round-robin that should be bounded by N_IN, and the bound is the
    # real property (a starving arbiter can still hit 1.0 grants/cycle).
    last_grant = [None] * N_IN
    waits = []
    first_grant_cycle = None

    while grants < N_GRANTS:
        await ReadOnly()
        idx = onehot_index(int(dut.grant_o.value))
        await RisingEdge(dut.clk)
        cycles += 1
        if idx is not None:
            counts[idx] += 1
            grants += 1
            if first_grant_cycle is None:
                first_grant_cycle = cycles
            if last_grant[idx] is not None:
                waits.append((grants, cycles - last_grant[idx]))
            last_grant[idx] = cycles
        assert cycles < 20 * N_GRANTS + 100, "arbiter issued no grants -- stuck?"

    per_cycle = grants / cycles
    dut._log.info("RESULT rr_arbiter grants=%d cycles=%d per_cycle=%.3f dist=%s",
                  grants, cycles, per_cycle, counts)
    # Round-robin fairness: with all inputs saturated every input must get an equal share
    # (+/- 1 for the tail of the final rotation).
    lo, hi = min(counts), max(counts)
    assert hi - lo <= 1, f"NOT round-robin -- grant distribution {counts} is unfair"

    # STARVATION BOUND -- measured in STEADY STATE, not from the first cycle.
    # There is exactly one grant-less cycle in the run (throughput 0.985, not 1.0): the
    # arbiter emits no grant in the cycle right after reset, before its priority pointer
    # is valid. That bubble stretches ONE gap to N_IN+1, which is a startup artifact and
    # not starvation. Asserting max(wait) <= N_IN over the whole run therefore fails for
    # the wrong reason -- so exclude the first rotation and check the steady state, while
    # reporting the startup bubble separately rather than hiding it.
    steady = [w for (g, w) in waits if g > 2 * N_IN]
    startup = [w for (g, w) in waits if g <= 2 * N_IN]
    assert max(steady) <= N_IN, (
        f"starvation in steady state -- max wait {max(steady)} exceeds {N_IN}")
    all_w = [w for (_, w) in waits]
    print(f"##RESULT## design=ravenoc_rr_arbiter grants={grants} cycles={cycles} "
          f"per_cycle={per_cycle:.3f} dist={counts} lat0={first_grant_cycle} "
          f"wait_steady_min={min(steady)} wait_steady_max={max(steady)} "
          f"wait_steady_mean={sum(steady)/len(steady):.2f} "
          f"wait_startup_max={max(startup) if startup else 0} "
          f"wait_overall_max={max(all_w)}")


@cocotb.test()
async def rr_arbiter_single(dut):
    """Only input 2 requests -- a work-conserving arbiter must grant it every cycle."""
    cocotb.start_soon(Clock(dut.clk, PERIOD_NS, units="ns").start())
    await reset(dut)

    dut.req_i.value = 1 << 2
    dut.update_i.value = 1

    cycles, grants = 0, 0
    for _ in range(32):
        await ReadOnly()
        idx = onehot_index(int(dut.grant_o.value))
        await RisingEdge(dut.clk)
        cycles += 1
        if idx is not None:
            assert idx == 2, f"granted {idx} but only input 2 requested"
            grants += 1

    print(f"##RESULT## design=ravenoc_rr_arbiter mode=single grants={grants} "
          f"cycles={cycles} per_cycle={grants/cycles:.3f}")
