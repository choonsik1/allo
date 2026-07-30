"""Path C probe: drive LightningSim's compiled solver with events we generate
ourselves -- no Vitis bitcode, no instrumentation, no testbench.

Models Allo's Stage 0 design: producer writes 4 elements into a depth-4 FIFO,
consumer reads 4. If the solver accepts externally-built graphs, this is the
route to using it as an Allo backend.
"""
from lightningsim._core import SimulationBuilder
from lightningsim.trace_file import SimulationParameters

FIFO = 0
N = 4

b = SimulationBuilder()
# enter producer: (safe_offset, start_stage, end_stage, start_delay, inherit_ap_continue)
b.call(0, 0, N, 0, False)
for s in range(N):
    b.add_fifo_write(0, s, FIFO)
b.return_("producer", N)

b.call(0, 0, N, 0, False)
for s in range(N):
    b.add_fifo_read(0, s, FIFO)
b.return_("consumer", N)

b.return_("top", 2 * N)

compiled = b.finish()
print(f"graph: {compiled.node_count()} nodes, {compiled.edge_count()} edges")

params = SimulationParameters(
    fifo_depths={FIFO: 4},
    fifo_widths={FIFO: 32},
    axi_delays={},
    ap_ctrl_chain_top_port_count=None,
)
sim = compiled.execute(params)
top = sim.top_module
print(f"top: {top.name} [{top.start}-{top.end}]")
for m in top.submodules:
    print(f"   {m.name} [{m.start}-{m.end}]")
for fifo, io in sim.fifo_io.items():
    print(f"   fifo {fifo.id}: {len(io.writes)} writes, {len(io.reads)} reads, "
          f"observed depth {io.get_observed_depth()}")
