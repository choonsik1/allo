#!/usr/bin/env python3
"""Generate test_mmio_in.mem -- exercises the LOAD half of the MMIO hook.

The store half (test_mmio.mem) only proves memwb can Push. This proves it can
Pop: the program reads two words from the channel, echoes the first back
verbatim, and increments the second so the value is shown to have travelled
through the register file and the ALU rather than being looped in memwb.

Expected output, given system.hpp's mmio_producer():
    MMIO OUT: 0xdeadbeef
    MMIO OUT: 0x101
"""
import sys, os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "ip"))
from rvasm import LUI, LW, SW, ADDI

MMIO_HI = 0x32          # LUI imm20; byte address 0x32000 == DCACHE_SIZE * 4
NOP = ADDI(0, 0, 0)
JAL_SELF = 0x0000006F   # jal x0, 0 -- the halt fedec recognises

prog = [
    LUI(6, MMIO_HI),    # x6 = 0x32000, the channel address
    LW(7, 6, 0),        # x7 = mmio_in.Pop()          <- blocks until fed
    NOP, NOP,           # separate the load-use hazard from the MMIO question
    SW(7, 6, 0),        # mmio_out.Push(x7)           -> 0xdeadbeef
    LW(8, 6, 0),        # x8 = mmio_in.Pop()          <- second value
    NOP, NOP,
    ADDI(8, 8, 1),      # x8 += 1: proves the value reached the regfile and ALU
    SW(8, 6, 0),        # mmio_out.Push(x8)           -> 0x101
]
# program_end fires on FETCH of the halt, and the testbench sc_stop()s there,
# so the last store needs slack to reach memwb. See README, "Findings".
prog += [NOP] * 8 + [JAL_SELF]

out = os.path.join(os.path.dirname(__file__), "test_mmio_in.mem")
with open(out, "w") as f:
    for i, word in enumerate(prog):
        f.write("%08x 0x%08x\n" % (i * 4, word & 0xFFFFFFFF))
print("wrote %s (%d instructions)" % (out, len(prog)))
