"""
Example 1 -- fifo.sv, the Stream baseline.

WHAT IS MEASURED: cycles to move N_FLITS words through a depth-2, 32-bit FIFO with a
producer that writes whenever !full and a consumer that reads whenever !empty. Both run
every cycle, so this is the MAXIMUM-THROUGHPUT case -- the number to compare against an
Allo design streaming the same N_FLITS through Stream[int32, 2].

The window is [first accepted write .. last accepted read], counted in clock edges. It
deliberately EXCLUDES reset, because the Allo side's reset length is a Catapult artifact
(17 cycles) and has nothing to do with the link type being measured.

ASYMMETRY TO REPORT HONESTLY: fifo.sv exposes raw enables, so the full/empty checking
lives here in the testbench. Allo's Stream does that checking inside the generated
hardware. So the Allo design carries handshake logic this DUT does not -- that gap is the
cost of the abstraction, and it is the point of the comparison, not a flaw in it.

RaveNoC reset is ACTIVE-HIGH async.
"""
import os
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, ReadOnly

N_FLITS = int(os.getenv("N_FLITS", "64"))
PERIOD_NS = 2  # matches the Allo side's -CLOCK_PERIOD 2.0


async def reset(dut):
    dut.arst.value = 1
    dut.write_i.value = 0
    dut.read_i.value = 0
    dut.data_i.value = 0
    for _ in range(3):
        await RisingEdge(dut.clk)
    dut.arst.value = 0
    await RisingEdge(dut.clk)


@cocotb.test()
async def fifo_max_throughput(dut):
    cocotb.start_soon(Clock(dut.clk, PERIOD_NS, units="ns").start())
    await reset(dut)

    sent, got = 0, []
    cycles = 0
    first_write_cycle = None

    # DRIVE GREEDILY, THEN RECONSTRUCT. Deciding the enables from full_o/empty_o sampled in
    # the same cycle is circular: the value driving edge N must be set before edge N, but
    # the flags for that cycle are only settled at ReadOnly, after which cocotb forbids
    # driving. So do what the hardware does -- assert the enables unconditionally and let
    # the FIFO's internal guards (write_i && ~full_o) decide. We then reconstruct the
    # accepted transfers from the same expressions the DUT uses.
    #
    # Consequence: write_i is high while full, so error_o WILL assert. That is the FIFO
    # reporting a dropped write, not data loss -- `sent` only advances on an accepted
    # write, so data_i simply holds the same value until it is taken.
    dut.write_i.value = 1
    dut.read_i.value = 1
    dut.data_i.value = 1

    while len(got) < N_FLITS:
        await ReadOnly()
        full = int(dut.full_o.value)
        empty = int(dut.empty_o.value)
        wrote = int(dut.write_i.value) and not full
        read = int(dut.read_i.value) and not empty
        # data_o is combinational off the read pointer, so it is valid whenever !empty
        data = int(dut.data_o.value) if read else None

        await RisingEdge(dut.clk)
        cycles += 1
        if read:
            got.append(data)
        if wrote:
            if first_write_cycle is None:
                first_write_cycle = cycles
            sent += 1

        dut.write_i.value = 1 if sent < N_FLITS else 0
        dut.data_i.value = (sent + 1) if sent < N_FLITS else 0
        dut.read_i.value = 1

        assert cycles < 20 * N_FLITS + 100, "fifo bench did not converge -- livelock?"

    expected = list(range(1, N_FLITS + 1))
    assert got == expected, f"DATA MISMATCH: got {got[:8]}... expected {expected[:8]}..."

    window = cycles - (first_write_cycle - 1)
    dut._log.info("RESULT fifo N_FLITS=%d cycles=%d window=%d cycles_per_flit=%.3f",
                  N_FLITS, cycles, window, window / N_FLITS)
    print(f"##RESULT## design=ravenoc_fifo flits={N_FLITS} cycles={window} "
          f"per_flit={window/N_FLITS:.3f}")
