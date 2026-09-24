#!/usr/bin/env python3
"""End-to-end: the ported HL5 processor imported as an Allo SystemC IP.

Everything before this was tested against a hand-written SC_MODULE. This points
Allo's SystemC front end at the real thing -- 2000 lines of third-party RISC-V,
ported from Stratus -- and checks that:

  1. parse_sc_module finds exactly the two promoted MMIO ports, and none of
     hl5's three internal pipeline channels;
  2. direction comes from the port TYPE, so no input_idx/output_idx is needed;
  3. df.customize accepts it and emits func.func private with stream_dirs set.
"""
import os
import allo
from allo.ir.types import int32, Stream
import allo.dataflow as df

HERE = os.path.dirname(os.path.abspath(__file__))
HL5_HPP = os.path.join(HERE, "hl5.hpp")

hl5_ip = allo.IPModule(top="hl5", impl=HL5_HPP)

print("=== what the parser found in the real hl5.hpp")
print("  is_systemc :", hl5_ip.is_systemc)
print("  port names :", hl5_ip.sc_names)
print("  directions :", hl5_ip.sc_dirs)
print("  clock      :", hl5_ip.sc_clk)
print("  reset      :", hl5_ip.sc_rst)

assert hl5_ip.is_systemc is True
assert hl5_ip.sc_names == ["mmio_in", "mmio_out"], hl5_ip.sc_names
assert hl5_ip.sc_dirs == "io", hl5_ip.sc_dirs
assert hl5_ip.sc_clk == "clk"
assert hl5_ip.sc_rst is None       # two sc_in<bool>; the parser refuses to guess

Ty = int32


@df.region()
def top():
    # A bare annotation, no assignment -- that is how Allo declares a stream
    # at region scope; `df.Stream[...]()` is not the accepted form.
    to_cpu: Stream[Ty, 4]
    from_cpu: Stream[Ty, 4]

    @df.kernel(mapping=[1])
    def cpu():
        # The IP is called with the two streams; no indices are supplied,
        # because Connections::In/Out already stated the direction.
        hl5_ip(to_cpu, from_cpu)


s = df.customize(top)
ir = str(s.module)
print("\n=== the emitted declaration")
for line in ir.splitlines():
    if "hl5" in line:
        print(" ", line.strip())

assert "func.func private @hl5" in ir, "IP was not declared as an external func"
assert 'stream_dirs = "io"' in ir, "stream_dirs missing or wrong"
print("\nOK: real HL5 accepted as an Allo SystemC IP")
