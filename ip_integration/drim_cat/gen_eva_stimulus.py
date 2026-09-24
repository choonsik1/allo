#!/usr/bin/env python3
"""Write the input*.data files Allo's generated SystemC testbench reads.

The emitted testbench loads each top-level array from a numbered file rather
than taking arguments, so driving EVA means producing these rather than writing
a testbench module. Mapping (kernel-appearance order, 1x1):

    input0   prime_cfg           1 value
    input1/2 in_w  / iv_w        the ACTIVATIONS -- the only real stimulus
    input3/4 in_e  / iv_e        unused
    input5/6 in_n  / iv_n        iv_n all 1: the valid-zero north seed
    input7/8 in_s  / iv_s        unused
    input9+  rin_w/e/n/s         router plane -- deliberately all zero

Stimulus matches tb_top.cpp's TARGET_MMM1X1 so the expected result is the
already-verified out_s = [6, 12, 3]: X = [2, 4, 1] against a stationary weight
of 3, landing on the west edge at PROG_CYCLES + KLEN*b.

Nothing is fed on the router plane at all -- the array's entire program comes
from the processor.
"""
import sys
TWO = "--2x2" in sys.argv
# VL must equal the chip's LANELEN == NSTEP.
VL, BATCH, KLEN, PROG_CYCLES, PRIME_TOKENS = (400 if TWO else 200), 3, 4, 16, 6
# tb_top.cpp: 1x1 drives one west row, 2x2 drives two.
#   1x1  X = [2,4,1]              vs W=3      -> out_s = [6,12,3]
#   2x2  X = [[2,4],[1,3],[5,2]]  vs [[1,3],[5,7]]
#        -> out_s col0 = [22,16,15], col1 = [34,24,29]
X = [[2.0, 4.0], [1.0, 3.0], [5.0, 2.0]] if TWO else [[2.0], [4.0], [1.0]]
ROWS = 2 if TWO else 1

def write(idx, vals):
    with open(f"input{idx}.data", "w") as f:
        f.write("\n".join(str(v) for v in vals) + "\n")

write(0, [PRIME_TOKENS])                       # prime_cfg

# in_w / iv_w are [ROWS][VL] flattened row-major, one west lane per row.
in_w = [0.0] * (VL * ROWS)
iv_w = [0]   * (VL * ROWS)
for i in range(ROWS):
    for b in range(BATCH):
        in_w[i * VL + PROG_CYCLES + KLEN * b] = X[b][i]
        iv_w[i * VL + PROG_CYCLES + KLEN * b] = 1
write(1, in_w)
write(2, iv_w)

COLS = ROWS                                    # square grid
write(3, [0.0] * (VL * ROWS)); write(4, [0] * (VL * ROWS))   # east: unused
write(5, [0.0] * (VL * COLS)); write(6, [1]   * (VL * COLS)) # north: seed
write(7, [0.0] * (VL * COLS)); write(8, [0] * (VL * COLS))   # south: unused

for i in range(9, 13):                          # router plane: nothing
    write(i, [0] * (VL * ROWS))

print("wrote input0..12.data; %dx%d, VL=%d, activations %s at cycles %s"
      % (ROWS, COLS, VL, X, [PROG_CYCLES + KLEN * b for b in range(BATCH)]))
