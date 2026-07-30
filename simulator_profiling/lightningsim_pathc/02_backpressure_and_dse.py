"""Path C part 2: does the solver model BACK-PRESSURE, and does its DSE work?

Producer writes N fast (1/cycle); consumer reads slowly (1 per 3 cycles). With a
deep FIFO the producer should finish early; with a shallow one it must stall.
If latency changes with depth, the solver is really modelling back-pressure.
"""
from lightningsim._core import SimulationBuilder
from lightningsim.trace_file import SimulationParameters

FIFO, N = 0, 8

def build():
    b = SimulationBuilder()
    b.call(0, 0, N, 0, False)
    for s in range(N):                 # producer: one write per cycle
        b.add_fifo_write(0, s, FIFO)
    b.return_("producer", N)
    b.call(0, 0, 3 * N, 0, False)
    for s in range(N):                 # consumer: one read every 3 cycles
        b.add_fifo_read(0, 3 * s, FIFO)
    b.return_("consumer", 3 * N)
    b.return_("top", 3 * N)
    return b.finish()

compiled = build()
print(f"graph: {compiled.node_count()} nodes, {compiled.edge_count()} edges\n")

print("depth   top_cycles   producer   consumer   observed_depth")
for depth in (1, 2, 4, 8, None):
    p = SimulationParameters(fifo_depths={FIFO: depth}, fifo_widths={FIFO: 32},
                             axi_delays={}, ap_ctrl_chain_top_port_count=None)
    try:
        sim = compiled.execute(p)
        subs = {m.name: m for m in sim.top_module.submodules}
        obs = [io.get_observed_depth() for io in sim.fifo_io.values()][0]
        print(f"{str(depth):>5}   {sim.top_module.end:>10}   "
              f"{subs['producer'].end:>8}   {subs['consumer'].end:>8}   {obs:>14}")
    except ValueError as e:
        print(f"{str(depth):>5}   DEADLOCK ({e})")

print("\n=== native DSE over FIFO depths ===")
space = compiled.get_fifo_design_space([FIFO], 32)
print(f"design space for fifo {FIFO}: {space}")
base = SimulationParameters(fifo_depths={FIFO: 1}, fifo_widths={FIFO: 32},
                            axi_delays={}, ap_ctrl_chain_top_port_count=None)
pts = compiled.dse(base, [{FIFO: d} for d in space])
for d, pt in zip(space, pts):
    print(f"  depth {d:>4} -> latency {pt.latency}, bram {pt.bram_count}")
