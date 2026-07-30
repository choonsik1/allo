"""Is the cycle failure about ORDERING, or structural?"""
from lightningsim._core import SimulationBuilder
from lightningsim.trace_file import SimulationParameters
N = 4

def attempt(label, emit):
    b = SimulationBuilder()
    try:
        emit(b)
        c = b.finish()
        p = SimulationParameters(fifo_depths={0: 2, 1: 2}, fifo_widths={0: 32, 1: 32},
                                 axi_delays={}, ap_ctrl_chain_top_port_count=None)
        s = c.execute(p)
        print(f"{label:<46} OK  top[{s.top_module.start}-{s.top_module.end}]")
    except ValueError as e:
        print(f"{label:<46} FAIL  {e}")

# 1. feed-forward, two FIFOs both A->B  (should work)
def ff(b):
    b.call(0, 0, N, 0, False)
    for s in range(N): b.add_fifo_write(0, s, 0); b.add_fifo_write(0, s, 1)
    b.return_("A", N)
    b.call(0, 0, N, 0, False)
    for s in range(N): b.add_fifo_read(0, s, 0); b.add_fifo_read(0, s, 1)
    b.return_("B", N)
    b.return_("top", 2 * N)

# 2. cycle, A first (A's reads of f1 precede B's writes)
def cyc_a_first(b):
    b.call(0, 0, N, 0, False)
    for s in range(N): b.add_fifo_write(0, s, 0); b.add_fifo_read(0, s, 1)
    b.return_("A", N)
    b.call(0, 0, N, 0, False)
    for s in range(N): b.add_fifo_read(0, s, 0); b.add_fifo_write(0, s, 1)
    b.return_("B", N)
    b.return_("top", 2 * N)

# 3. cycle, primed: B emits all f1 writes first, then A, then B's f0 reads
def cyc_primed(b):
    b.call(0, 0, N, 0, False)
    for s in range(N): b.add_fifo_write(0, s, 1)
    b.return_("B_pre", N)
    b.call(0, 0, N, 0, False)
    for s in range(N): b.add_fifo_write(0, s, 0); b.add_fifo_read(0, s, 1)
    b.return_("A", N)
    b.call(0, 0, N, 0, False)
    for s in range(N): b.add_fifo_read(0, s, 0)
    b.return_("B_post", N)
    b.return_("top", 3 * N)

attempt("1. feed-forward A->B (2 fifos)", ff)
attempt("2. cycle, A emitted first", cyc_a_first)
attempt("3. cycle, split/primed into 3 phases", cyc_primed)
