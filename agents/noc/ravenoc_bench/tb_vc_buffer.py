"""
Example 2 -- vc_buffer.sv, the Channel / non-blocking example.

vc_buffer is fifo.sv PLUS a valid/ready handshake on both ends. So its Allo counterpart is
Stream[int32,2] (storage + protocol), and the contrast against a bare
Channel[int32, valid_ready] (protocol, ZERO storage) is what isolates the buffer's
contribution. Both Allo variants get run against the numbers from here.

TWO STIMULUS MODES, because a zero-storage Channel only differs from a FIFO when the
consumer is not always ready:
  * "greedy"       -- consumer ready every cycle. Max throughput. A FIFO and a Channel
                      should look nearly identical here.
  * "backpressure" -- consumer ready on a fixed 1-in-3 pattern. This is where storage
                      earns its keep: the FIFO absorbs, the Channel stalls the producer.
The pattern is FIXED, not random, so the Allo run is driven by exactly the same sequence.

vc_id is carried through untouched (a sideband -- the Wire idiom). We check it survives.
"""
import os
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, ReadOnly

N_FLITS = int(os.getenv("N_FLITS", "64"))
PERIOD_NS = 2
VC_ID = 1


async def reset(dut):
    dut.arst.value = 1
    dut.valid_i.value = 0
    dut.ready_i.value = 0
    dut.fdata_i.value = 0
    dut.vc_id_i.value = VC_ID
    for _ in range(3):
        await RisingEdge(dut.clk)
    dut.arst.value = 0
    await RisingEdge(dut.clk)


async def run(dut, ready_pattern, label):
    cocotb.start_soon(Clock(dut.clk, PERIOD_NS, units="ns").start())
    await reset(dut)

    sent, got, cycles = 0, [], 0
    first_xfer = None
    dut.valid_i.value = 1
    dut.fdata_i.value = 1

    while len(got) < N_FLITS:
        rdy = ready_pattern(cycles)
        dut.ready_i.value = rdy

        await ReadOnly()
        in_fire = int(dut.valid_i.value) and int(dut.ready_o.value)
        out_fire = int(dut.valid_o.value) and rdy
        odata = int(dut.fdata_o.value) if out_fire else None
        ovc = int(dut.vc_id_o.value) if out_fire else None

        await RisingEdge(dut.clk)
        cycles += 1
        if out_fire:
            got.append(odata)
            assert ovc == VC_ID, f"vc_id corrupted: {ovc} != {VC_ID}"
        if in_fire:
            if first_xfer is None:
                first_xfer = cycles
            sent += 1

        dut.valid_i.value = 1 if sent < N_FLITS else 0
        dut.fdata_i.value = (sent + 1) if sent < N_FLITS else 0

        assert cycles < 40 * N_FLITS + 100, f"{label}: did not converge -- livelock?"

    expected = list(range(1, N_FLITS + 1))
    assert got == expected, f"{label} DATA MISMATCH: {got[:8]}... != {expected[:8]}..."

    window = cycles - (first_xfer - 1)
    dut._log.info("RESULT vc_buffer/%s cycles=%d per_flit=%.3f", label, window, window / N_FLITS)
    print(f"##RESULT## design=ravenoc_vc_buffer mode={label} flits={N_FLITS} "
          f"cycles={window} per_flit={window/N_FLITS:.3f}")


@cocotb.test()
async def vc_buffer_greedy(dut):
    await run(dut, lambda c: 1, "greedy")


@cocotb.test()
async def vc_buffer_backpressure(dut):
    # fixed 1-in-3 duty cycle -- deterministic, so the Allo side sees the identical sequence
    await run(dut, lambda c: 1 if (c % 3 == 0) else 0, "backpressure")
