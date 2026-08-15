# agents/

An experiment in **LLM/agent-driven interconnect design**: fix the compute blocks, and let an
agent choose only how they are *wired together*.

The premise is that block logic (a router's arbiter, a PE's ALU) is the part you want written
by a human and verified once, while the interconnect — which link primitive, which topology,
what FIFO depth — is a large, mechanical design space worth searching. So the blocks here are
stripped down to plain callable functions with a declared `PORT_SPEC`, and the agent emits
only the connections between them. A verifier then checks the emitted wiring against
[`INTERCONNECT.md`](INTERCONNECT.md) and each block's `PORT_SPEC`.

## The contract

**[`INTERCONNECT.md`](INTERCONNECT.md)** is the agent-facing reference: the three link
primitives, their methods, and the rules for combining them. Ground truth is
`allo/ir/types.py` (types and methods) and `allo/backend/hls.py` (the backend guard) — the
document exists so an agent does not invent API outside that table.

## Blocks

| File | Block |
|---|---|
| `eva_blocks.py` | EVA blocks as plain functions — router, switch, PE — with agent-generated connections |
| `pe_alu.py` | the simplest possible PE: `(op1, op2, opcode) -> result`, no state, no sequencer |
| `eva_pe_router_split.py` | the EVA design split into router + PE |
| `eva_sb_syscredit_rtprime.py` | EVA switchbox with system-credit flow control |

## Callability experiments

The load-bearing question for this whole approach is whether a `@df.kernel` can *call* a
stripped block function — one that mutates arrays and declares locals — without losing
anything at lowering. These scripts answer it:

| File | Checks |
|---|---|
| `confirm_blocks.py` | every stripped block builds on the simulator, called by its own name |
| `exp_block_callable.py` | can a kernel call an array-mutating, locals-declaring block at all |
| `exp_block_callable2.py` | the harder parameter shapes — 2-D state (`buf[5,2]`), `int32[...]` params |
| `exp_err.py` | error paths |
| `cosim_split_sim.py` | smoke test for the split EVA (router + single-cycle PE) on the JIT simulator |

## Status

Exploratory. The blocks build and the callability results are in the scripts' own output;
the generator that would consume `INTERCONNECT.md` is not built yet. See
[`../notes/STATE.md`](../notes/STATE.md) for where this sits relative to the rest of the work.

**Known finding worth keeping:** block parameters must be annotated — an unannotated
parameter silently changes how the block lowers.
