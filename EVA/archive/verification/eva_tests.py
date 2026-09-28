import os
# 4x4 mesh = M*N (PEs) + 8*(M+N) (drivers+collectors) = 80 kernel instances; the simulator wraps each in
# a blocking omp.section, so #threads must be >= #instances or it deadlocks. Set before importing allo.
os.environ.setdefault("OMP_NUM_THREADS", "256")

import warnings, time, sys
warnings.simplefilter('ignore')
import numpy as np, allo.dataflow as df
from allo.ir.types import float16
# tests live in Allo/EVA/tests/, the design (eva.py) one level up
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import eva as e
import eva_workloads as wl                       # load_prog_packets / pack_pkt (router-load helpers)

# ═════════════════════════════════════════════════════════════════════════════════════════════════
# EVA functional bring-up suite (CURRENT ROUTER-LOAD INTERFACE)
# Read top to bottom: single node -> systolic chain -> router -> core->router -> turn -> FFT shuffle
# -> full-mesh scaling. (The MMM / FFT compute workloads live in eva_workloads.py.)
#
#   python eva_tests.py               # run every test, print a summary
#   python eva_tests.py turn router   # run only the named tests
#
# ALL tests build THE SAME chip (eva.get_eva_top) and drive it exactly like the workloads do:
#   * programs (+ per-node kernel_len / sync-mask / START) are LOADED OVER THE ROUTER via
#     wl.load_prog_packets(...) into the SOUTH driver -> rins[3];  the chip takes NO direct prog arg.
#   * DATADRIVEN=1: a PE stalls until its operands are valid, so inputs are placed at cycle >= pc
#     (pc = the cycle by which all programming has been delivered). Collectors COMPACT valid tokens
#     from index 0, so a forwarded stream lands at out_*[row, 0:K] regardless of pipeline latency.
# ═════════════════════════════════════════════════════════════════════════════════════════════════

zi = lambda *s: np.zeros(s, dtype=np.int32)        # int32 zeros  (masks / router packets)
z  = lambda *s: np.zeros(s, dtype=np.float16)      # fp16  zeros  (systolic data)
_NOP = e.OP_MOV | (6 << 4) | (6 << 8)              # MOV r6,r6 -- touches nothing load-bearing

def _dims(M, N, margin=40):
    """Size the chip for a router-loaded, data-driven test. Returns (pc, LANELEN) where pc = the cycle
    by which every node's program+START has been delivered (place inputs at >= pc)."""
    e.M, e.N = M, N
    e.IRF_DEPTH = 8
    e.DATADRIVEN = 1
    per_node = e.IRF_DEPTH + 0 + 2                  # 8 IRF + 2 config regs (no twiddle data packets here)
    pc = M * per_node + M + 4                       # M nodes streamed up each column + transit + margin
    e.NSTEP = pc + margin
    e.LANELEN = e.NSTEP
    return pc, e.LANELEN

def io_bufs(M, N, L):
    """4-side I/O buffer sets in region order: systolic in/out + router in/out (all [w,e,n,s])."""
    ins  = [z(M, L), z(M, L), z(N, L), z(N, L)]     # in_w, in_e, in_n, in_s  (systolic inputs)
    outs = [z(M, L), z(M, L), z(N, L), z(N, L)]     # out_w..out_s            (systolic outputs)
    rins = [zi(M, L), zi(M, L), zi(N, L), zi(N, L)] # rin_w..rin_s            (router inputs)
    routs= [zi(M, L), zi(M, L), zi(N, L), zi(N, L)] # rout_w..rout_s          (router outputs)
    return ins, outs, rins, routs

def bubbles(M, N, L): return [zi(M, L), zi(M, L), zi(N, L), zi(N, L)]   # systolic valid mask = all idle

def pack(data=0x3C00, addr=5, mode=0, idf=15, rq=1):    # router packet (LSB-first), == wl.pack_pkt layout
    return int(data | (addr << 16) | (mode << 20) | (idf << 21) | (rq << 25))
def unpack(w):  return (w & 0xFFFF, (w >> 16) & 0xF, (w >> 20) & 1, (w >> 21) & 0xF, (w >> 25) & 1)
def f16(bits):  return float(np.uint16(bits).view(np.float16))


# ─── TEST 1: single-node systolic passthrough ─────────────────────────────────────────────────────
# One node loops MOV west-rx -> east-tx K times (klen=1, iter=K). A K-long ramp enters the west input
# (from cycle pc); each iteration forwards one token east. Collector compacts -> out_e[0,0:K] == ramp.
def test_passthrough():
    M, N, K = 1, 1, 6
    pc, L = _dims(M, N)
    INSTR = e.OP_MOV | (0xF << 4) | (0xE << 8)      # MOV west-rx(0xE) -> east-tx(0xF&3=3) = 0xEF3
    prog = zi(M, N, e.IRF_DEPTH); prog[:] = _NOP; prog[0, 0, 0] = INSTR
    rin_s = wl.load_prog_packets(prog, M, N, cfg=(1, K, 0))         # klen=1, loop K times, no sync
    mod = df.build(e.get_eva_top(float16), target='simulator')
    ins, outs, rins, routs = io_bufs(M, N, L)
    ramp = np.arange(1, K + 1, dtype=np.float16)
    ivw = zi(M, L)
    for t in range(K):
        ins[0][0, pc + t] = ramp[t]; ivw[0, pc + t] = 1
    rins[3] = rin_s
    e.run_eva(mod, ins, [ivw, zi(M, L), zi(N, L), zi(N, L)], outs, rins, routs)
    got = outs[1][0, :K]
    ok = np.array_equal(got, ramp)
    print(f"  ramp in   = {ramp.astype(np.float32)}")
    print(f"  out_e[0]  = {got.astype(np.float32)}")
    print(f"  {'PASS' if ok else 'FAIL'}: out_e[0,0:{K}] {'==' if ok else '!='} ramp")
    return ok


# ─── TEST 2: multi-hop systolic row ─────────────────────────────────────────────────────────────
# 1xN row, every node loops MOV west-rx -> east-tx. K tokens ride the row through all N nodes and exit
# the east collector; data-driven stalls (no static skew) + compaction -> out_e[0,0:K] == ramp.
def _row(N, K=4):
    M = 1
    pc, L = _dims(M, N)
    INSTR = e.OP_MOV | (0xF << 4) | (0xE << 8)
    prog = zi(M, N, e.IRF_DEPTH); prog[:] = _NOP; prog[:, :, 0] = INSTR
    rin_s = wl.load_prog_packets(prog, M, N, cfg=(1, K, 0))
    mod = df.build(e.get_eva_top(float16), target='simulator')
    ins, outs, rins, routs = io_bufs(M, N, L)
    ramp = np.arange(1, K + 1, dtype=np.float16)
    ivw = zi(M, L)
    for t in range(K):
        ins[0][0, pc + t] = ramp[t]; ivw[0, pc + t] = 1
    rins[3] = rin_s
    e.run_eva(mod, ins, [ivw, zi(M, L), zi(N, L), zi(N, L)], outs, rins, routs)
    got = outs[1][0, :K]
    ok = np.array_equal(got, ramp)
    print(f"  1x{N}: out_e[0,0:{K}]={got.astype(np.float32)} vs ramp={ramp.astype(np.float32)}  {'PASS' if ok else 'FAIL'}")
    return ok

def test_row():
    return all([_row(2), _row(4)])


# ─── TEST 3: router transit vs deliver (pure router net, no core) ───────────────────────────────
# Inject ONE packet at the WEST router perimeter (rins[0]); NO program loaded (cores idle -> the router
# forwards on its own). Horizontal nets match col_id (column index): id >= N -> transits to rout_e;
# id < N -> delivered to node(0,id) and consumed (never reaches rout_e).
def _router(idf):
    M, N = 1, 2
    pc, L = _dims(M, N)
    PKT = pack(idf=idf)
    mod = df.build(e.get_eva_top(float16), target='simulator')
    ins, outs, rins, routs = io_bufs(M, N, L)
    rins[0][0, 0] = PKT                                             # west perimeter, cycle 0 (no prog needed)
    e.run_eva(mod, ins, bubbles(M, N, L), outs, rins, routs)
    should_transit = idf >= e.N
    hit = PKT in [int(x) for x in routs[1][0]]
    ok = (hit == should_transit)
    kind = "TRANSIT" if should_transit else "DELIVER"
    print(f"  id={idf} ({kind}): rout_e[0]={[hex(int(x)) for x in routs[1][0]]}  "
          f"packet {'reached' if hit else 'consumed'}  {'PASS' if ok else 'FAIL'}")
    return ok

def test_router():
    return all([_router(15), _router(1)])                          # transit (no match) + deliver (col 1)


# ─── TEST 4: core-send inject (core -> router) ──────────────────────────────────────────────────
# node(0,0) runs ONE RTR-east instr forwarding its west-rx operand (5.0) onto the router net, id=15
# (no col match) -> rides east through node(0,1), exits the east router collector (rout_e).
def test_core_send():
    M, N = 1, 2
    pc, L = _dims(M, N)
    INSTR = (e.OP_RTR0 + 3) | (0x0 << 4) | (0xE << 8) | (0xF << 12)  # RTR east | dst0 | s1=west-rx | s2=id15
    VAL = np.float16(5.0); VBITS = int(VAL.view(np.uint16))
    prog = zi(M, N, e.IRF_DEPTH); prog[:] = _NOP; prog[0, 0, 0] = INSTR
    rin_s = wl.load_prog_packets(prog, M, N, cfg=(1, 1, 0))         # both nodes START; node(0,1) just NOPs+transits
    mod = df.build(e.get_eva_top(float16), target='simulator')
    ins, outs, rins, routs = io_bufs(M, N, L)
    ivw = zi(M, L); ins[0][0, pc] = VAL; ivw[0, pc] = 1             # one real west token, after programming
    rins[3] = rin_s
    e.run_eva(mod, ins, [ivw, zi(M, L), zi(N, L), zi(N, L)], outs, rins, routs)
    print(f"  core sends fp16 {float(VAL)} (0x{VBITS:04x}) east, id=15 -> rout_e[0]={[hex(int(x)) for x in routs[1][0]]}")
    ok = False
    for w in [int(x) for x in routs[1][0] if int(x) != 0]:
        payload, _, _, idf, rq = unpack(w)
        print(f"    captured: payload=0x{payload:04x} ({f16(payload)}) id={idf} rq={rq}")
        if payload == VBITS and idf == 15 and rq == 1: ok = True
    print(f"  {'PASS' if ok else 'FAIL'}: core RTR packet {'exited east with correct payload+id' if ok else 'NOT found'}")
    return ok


# ─── TEST 5: turn routing — the EVA signature "column -> core -> row" turn (2x2) ─────────────────
# 1. A packet at the NORTH perimeter of col 0 (rins[2]), id=0, addr=3, rides the VERTICAL net south;
#    vertical nets match row_id, so node(0,0) DELIVERS it into drf[3]. drf[3] is a SYNC slot (smask bit
#    3) so the delivery marks it full and node(0,0)'s RTR waits for it (READ-WHEN-FULL, no static timing).
# 2. node(0,0) then RTR-EAST drf[3] with id=15 -> the packet turns onto the HORIZONTAL net, transits
#    node(0,1), exits rout_e[0]; rout_s stays empty (consumed at row 0, not leaked south).
# The north packet is injected at cycle pc (after config), so drf[3]'s sync bit is already set when it lands.
def test_turn():
    M, N = 2, 2
    pc, L = _dims(M, N)
    VAL = np.float16(7.0); VBITS = int(VAL.view(np.uint16)); ADDR = 3
    NPKT = pack(data=VBITS, addr=ADDR, mode=0, idf=0, rq=1)         # id=0 -> delivered at row 0
    TURN = (e.OP_RTR0 + 3) | (0x0 << 4) | (ADDR << 8) | (0xF << 12) # RTR-east drf[3], id=15
    prog = zi(M, N, e.IRF_DEPTH); prog[:] = _NOP; prog[0, 0, 0] = TURN
    def cfg(i, j):
        if i == 0 and j == 0: return (1, 1, 0x08)                  # RTR kernel, drf[3] = sync register
        return (1, 1, 0)                                           # others NOP (node(0,1) transits the turn)
    rin_s = wl.load_prog_packets(prog, M, N, cfg=cfg)
    mod = df.build(e.get_eva_top(float16), target='simulator')
    ins, outs, rins, routs = io_bufs(M, N, L)
    rins[2][0, pc] = NPKT                                          # north perimeter, col 0, after config
    rins[3] = rin_s
    e.run_eva(mod, ins, bubbles(M, N, L), outs, rins, routs)
    print(f"  north pkt 0x{NPKT:07x} (data={float(VAL)} id=0) -> deliver@node(0,0).drf[3] -> RTR-east id=15")
    print(f"  rout_e[0]={[hex(int(x)) for x in routs[1][0]]}   rout_s[0]={[hex(int(x)) for x in routs[3][0]]} (should be empty)")
    ok = False
    for w in [int(x) for x in routs[1][0] if int(x) != 0]:
        payload, _, _, idf, rq = unpack(w)
        if payload == VBITS and idf == 15 and rq == 1: ok = True
    leaked = any(int(x) != 0 for x in routs[3][0])
    ok = ok and not leaked
    print(f"  {'PASS' if ok else 'FAIL'}: column->core->row turn {'completed' if ok else 'did NOT complete'}")
    return ok


# ─── TEST 6: router shuffle — the FFT inter-stage cross-row swap (golden col_upp_1), M=3 N=1 ─────
# row0 and row2 swap one value through the ROUTER (distance-2, transits row1). r7 is a SYNC register
# (smask bit 7): the recv MOV rX,r7 STALLS until the partner packet delivers -- the DATA-DRIVEN
# equivalent of golden's blocking sync register (NO NOP pad, so each kernel is 6 instrs and fits the IRF).
#   core0: r0<-in,r1<-in; DMOV r7@id2 <- r1 (send south); MOV r1,r7 (wait+recv); fwd r0,r1 EAST
#   core2: r0<-in,r1<-in; UMOV r7@id0 <- r0 (send north); MOV r0,r7 (wait+recv); fwd r0,r1 EAST
# Net swap: out_e[0]=[A0,C0], out_e[2]=[A1,C1]  (row0.r1 <-> row2.r0 exchanged).
def test_shuffle():
    M, N = 3, 1
    pc, L = _dims(M, N)
    MOV = e.OP_MOV
    mov = lambda dst, src: MOV | (dst << 4) | (src << 8)
    SYSLFT, SYSRGT = 0xE, 0xF
    DMOV = (e.OP_RTR0 + 1) | (7 << 4) | (1 << 8) | (2 << 12)        # send r1 SOUTH to core2.r7
    UMOV = (e.OP_RTR0 + 0) | (7 << 4) | (0 << 8) | (0 << 12)        # send r0 NORTH to core0.r7
    seq0 = [mov(0, SYSLFT), mov(1, SYSLFT), DMOV, mov(1, 7), mov(SYSRGT, 0), mov(SYSRGT, 1)]  # 6 instrs
    seq2 = [mov(0, SYSLFT), mov(1, SYSLFT), UMOV, mov(0, 7), mov(SYSRGT, 0), mov(SYSRGT, 1)]
    prog = zi(M, N, e.IRF_DEPTH); prog[:] = _NOP
    for k, ins_ in enumerate(seq0): prog[0, 0, k] = ins_
    for k, ins_ in enumerate(seq2): prog[2, 0, k] = ins_
    def cfg(i, j):
        if i in (0, 2): return (6, 1, 0x80)                        # shuffle kernel, r7 = sync register
        return (1, 1, 0)                                           # row1 = NOP (its router transit-forwards)
    rin_s = wl.load_prog_packets(prog, M, N, cfg=cfg)
    mod = df.build(e.get_eva_top(float16), target='simulator')
    ins, outs, rins, routs = io_bufs(M, N, L)
    A0, A1, C0, C1 = [np.float16(v) for v in (2.0, 3.0, 5.0, 7.0)]
    ivw = zi(M, L)
    ins[0][0, pc], ins[0][0, pc + 1] = A0, A1; ivw[0, pc:pc + 2] = 1
    ins[0][2, pc], ins[0][2, pc + 1] = C0, C1; ivw[2, pc:pc + 2] = 1
    rins[3] = rin_s
    e.run_eva(mod, ins, [ivw, zi(M, L), zi(N, L), zi(N, L)], outs, rins, routs)
    r0, r2 = outs[1][0].astype(np.float32), outs[1][2].astype(np.float32)
    exp0, exp2 = [float(A0), float(C0)], [float(A1), float(C1)]
    ok = (list(r0[:2]) == exp0) and (list(r2[:2]) == exp2)
    print(f"  out_e[0]={r0[:2]} (exp {exp0})  out_e[2]={r2[:2]} (exp {exp2})  {'PASS' if ok else 'FAIL'}")
    return ok


# ─── TEST 7: full-mesh scaling / deadlock smoke (4x4) ───────────────────────────────────────────
# All-bubble inputs, no program loaded, on a 4x4 grid (M*N + 8*(M+N) = 80 kernel instances). No value
# check -- proves the whole fabric builds and steps to completion without deadlocking (needs
# OMP_NUM_THREADS >= 80, set at the top of this file).
def test_mesh(M=4, N=4):
    pc, L = _dims(M, N, margin=20)
    print(f"  M={M} N={N} NSTEP={e.NSTEP} (instances = {M*N + 8*(M+N)})")
    t0 = time.time()
    mod = df.build(e.get_eva_top(float16), target='simulator')
    print(f"  build {time.time()-t0:.1f}s", flush=True)
    ins, outs, rins, routs = io_bufs(M, N, L)
    t1 = time.time()
    e.run_eva(mod, ins, bubbles(M, N, L), outs, rins, routs)
    print(f"  returned in {time.time()-t1:.1f}s -- NO DEADLOCK")
    return True


# ─── runner ─────────────────────────────────────────────────────────────────────────────────────
TESTS = [
    ("passthrough", test_passthrough),   # single node, systolic
    ("row",         test_row),           # multi-hop systolic
    ("router",      test_router),        # router transit + deliver
    ("core_send",   test_core_send),     # core -> router inject
    ("turn",        test_turn),          # column -> core -> row turn
    ("shuffle",     test_shuffle),       # FFT cross-row swap via router (stall-based r7 sync)
    ("mesh",        test_mesh),          # full-mesh scaling / deadlock smoke
]

if __name__ == "__main__":
    sel = set(sys.argv[1:])
    chosen = [(n, f) for n, f in TESTS if not sel or n in sel]
    if not chosen:
        print(f"no test matched {sel}; available: {[n for n, _ in TESTS]}"); sys.exit(2)
    results = []
    for name, fn in chosen:
        print("=" * 80); print(f"TEST: {name}"); print("=" * 80)
        try:
            ok = fn()
        except Exception as ex:
            ok = False; print(f"  ERROR: {ex}")
        results.append((name, ok))
    print("\n" + "=" * 80 + "\nSUMMARY")
    for name, ok in results:
        print(f"  {name:12s} {'PASS' if ok else 'FAIL'}")
    npass = sum(ok for _, ok in results)
    print(f"  {npass}/{len(results)} passed")
    sys.exit(0 if npass == len(results) else 1)
