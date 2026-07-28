import os; os.environ.setdefault("OMP_NUM_THREADS", "256")   # >= #instances; set before allo
import allo
from allo.ir.types import int32, UInt, Stream
import allo.dataflow as df
import numpy as np

# =====================================================================================
# XY-router mesh, ALL nodes are PEs, WITH credit-based backpressure (lossless).
#
# Difference vs router_XY_PEs.py (bufferless, drops arbiter losers): every link now has a
# companion REVERSE credit stream + each router input has a small FIFO (depth BUF_DEPTH).
#   - the arbiter loser is NOT dropped: it stays in its input buffer and retries next cycle
#   - credits stop the buffer overflowing: a node sends a real flit on an output only while it
#     holds a credit for that output (init = BUF_DEPTH); the downstream returns one credit each
#     time it pops (forwards) a flit, freeing a slot.  XY/DOR routing keeps this deadlock-free.
# This mirrors EVA's router_register (per-link buffer + handshake).  Streams stay always-fire:
# every forward stream AND every credit stream is read/written exactly once per cycle (bubble=0,
# credit=0 when idle); cyclic dependencies are broken by priming (forward=bubble, credit=allowance).
# =====================================================================================

# Grid size
ROWS = 4
COLUMNS = 4

# packet layout (LSB-first):  data[0:16] dest_col[16:19] dest_row[19:22] valid[22] done[23]
DW = 16
W  = 3
COL_LO = DW
ROW_LO = DW + W
VLD    = DW + 2 * W      # valid bit -> 22
DONE   = DW + 2 * W + 1  # done  bit -> 23  (0=operand: PE computes & re-injects; 1=result: PE sinks)
PS     = DW + 2 * W + 2  # total packet width -> 24
CMASK  = (1 << W) - 1

NUM_IT    = 128          # always-fire cycles (more headroom: backpressure serializes contention)
LANELEN   = 8            # host seed / log lanes per node
DIR       = 5            # 0=N 1=E 2=S 3=W 4=Local
BUF_DEPTH = 2            # per-input FIFO depth (EVA router_register = 2-deep); parameterized
PE_K      = 3            # the PE's "compute": multiply arrived payload by this constant


@df.region()
# NOTE arg order = (inj, fwd, dlv): must match the kernel arg DISCOVERY order below
# (loader sees inj,fwd ; storer sees dlv) — the simulator binds arrays positionally to that order.
def router_XY_NoC(inj: int32[ROWS, COLUMNS, LANELEN],
                  fwd: int32[ROWS, COLUMNS, 2],      # per-PE forward target (row,col) for its result
                  dlv: int32[ROWS, COLUMNS, LANELEN]):
    # ── forward link streams (flow-direction named), +1 perimeter ──
    north: Stream[UInt(PS), 4][ROWS + 1, COLUMNS]
    south: Stream[UInt(PS), 4][ROWS + 1, COLUMNS]
    east:  Stream[UInt(PS), 4][ROWS, COLUMNS + 1]
    west:  Stream[UInt(PS), 4][ROWS, COLUMNS + 1]
    inject:  Stream[UInt(PS), 4][ROWS, COLUMNS]      # PE -> router
    deliver: Stream[UInt(PS), 4][ROWS, COLUMNS]      # router -> PE

    # ── reverse CREDIT streams (one per forward link, opposite flow, carry 0/1 or initial allowance) ──
    cr_north: Stream[int32, 4][ROWS + 1, COLUMNS]
    cr_south: Stream[int32, 4][ROWS + 1, COLUMNS]
    cr_east:  Stream[int32, 4][ROWS, COLUMNS + 1]
    cr_west:  Stream[int32, 4][ROWS, COLUMNS + 1]
    cr_inject:  Stream[int32, 4][ROWS, COLUMNS]      # router -> PE  (credit for PE's injects)
    cr_deliver: Stream[int32, 4][ROWS, COLUMNS]      # PE -> router  (credit for router's deliveries)

    # ── host<->PE feed-forward streams (replace direct array args on the replicated pe_node) ──
    # A mapped kernel can't take a whole top-level array (HLS 200-779/979), so single load/store
    # kernels own the arrays and bridge array<->stream. seed_s depth = LANELEN so the loader can
    # burst-preload all of a PE's seeds without blocking (the PE consumes them lazily via `sp`).
    seed_s: Stream[UInt(PS), LANELEN][ROWS, COLUMNS]  # host seeds, burst-preloaded once per PE
    sink_s: Stream[UInt(PS), 4][ROWS, COLUMNS]        # PE's sunk result, one per cycle (0 = bubble)
    fwd_s:  Stream[UInt(PS), 4][ROWS, COLUMNS]        # per-PE forward target, packed (fr<<W)|fc, once

    @df.kernel(mapping=[ROWS, COLUMNS], args=[])
    def router_XY():
        r, c = df.get_pid()

        buf:  UInt(PS)[DIR, BUF_DEPTH] = 0    # per-input FIFO storage (index 0 = head)
        bcnt: int32[DIR] = 0                  # per-input occupancy
        cred: int32[DIR] = 0                  # per-OUTPUT credit (free slots downstream); filled by prime
        rr:   int32[DIR] = 0                  # per-OUTPUT round-robin pointer; PERSISTS across cycles

        # ── PRIME: break the two cyclic read-before-write dependencies (forward + credit) ──
        north[r, c].put(0); east[r, c + 1].put(0); south[r + 1, c].put(0)   # forward outputs = bubble
        west[r, c].put(0);  deliver[r, c].put(0)
        cr_south[r, c].put(BUF_DEPTH); cr_west[r, c + 1].put(BUF_DEPTH)      # credit-for-my-inputs =
        cr_north[r + 1, c].put(BUF_DEPTH); cr_east[r, c].put(BUF_DEPTH)      #   initial allowance to
        cr_inject[r, c].put(BUF_DEPTH)                                       #   each upstream sender

        for t in range(NUM_IT):
            # (A) collect returning credits for MY outputs (0=N 1=E 2=S 3=W 4=Local)
            cred[0] += cr_north[r, c].get()
            cred[1] += cr_east[r, c + 1].get()
            cred[2] += cr_south[r + 1, c].get()
            cred[3] += cr_west[r, c].get()
            cred[4] += cr_deliver[r, c].get()

            # (B) read the 5 forward inputs; buffer the valid ones (bubbles ignored)
            fin: UInt(PS)[DIR] = 0
            fin[0] = south[r, c].get()        # N input
            fin[1] = west[r, c + 1].get()     # E input
            fin[2] = north[r + 1, c].get()    # S input
            fin[3] = east[r, c].get()         # W input
            fin[4] = inject[r, c].get()       # Local input
            for d in range(DIR):
                if fin[d][VLD] == 1 and bcnt[d] < BUF_DEPTH:
                    buf[d, bcnt[d]] = fin[d]   # push at tail (credit gating guarantees room)
                    bcnt[d] += 1

            # (C) XY route the HEAD flit of each non-empty input buffer
            dstp: int32[DIR] = -1               # chosen output port (-1 = no flit)
            for d in range(DIR):
                if bcnt[d] > 0:
                    h: UInt(PS) = buf[d, 0]
                    hc: int32 = (h >> COL_LO) & CMASK
                    hr: int32 = (h >> ROW_LO) & CMASK
                    if hc > c:     dstp[d] = 1   # east
                    elif hc < c:   dstp[d] = 3   # west
                    elif hr > r:   dstp[d] = 2   # south
                    elif hr < r:   dstp[d] = 0   # north
                    else:          dstp[d] = 4   # local (arrived)

            # (D) arbitrate per output: ROUND-ROBIN, only if a credit is available. Scan buffered
            #     inputs starting at rr[o] and wrapping; first requester from there wins. On a grant,
            #     advance rr[o] past the winner so it leads last next cycle -> no input starves.
            grant: int32[DIR] = -1
            gvld:  int32[DIR] = 0
            for o in range(DIR):
                if cred[o] > 0:
                    for i in range(DIR):        # i = offset from the rotating start position rr[o]
                        d: int32 = rr[o] + i
                        if d >= DIR:            # wrap (no % divider)
                            d -= DIR
                        if bcnt[d] > 0 and dstp[d] == o and gvld[o] == 0:
                            grant[o] = d; gvld[o] = 1
                    if gvld[o] == 1:            # rotate only on an actual grant
                        nxt: int32 = grant[o] + 1
                        if nxt >= DIR:
                            nxt -= DIR
                        rr[o] = nxt

            # (E) crossbar: emit granted head, spend a credit, mark its input for pop
            outpkt: UInt(PS)[DIR] = 0
            pop: int32[DIR] = 0
            for o in range(DIR):
                if gvld[o] == 1:
                    gd: int32 = grant[o]
                    outpkt[o] = buf[gd, 0]
                    cred[o] -= 1
                    pop[gd] = 1

            # (F) pop granted inputs (FIFO shift), free a slot, return one credit upstream
            ret: int32[DIR] = 0
            for d in range(DIR):
                if pop[d] == 1:
                    for s in range(BUF_DEPTH - 1):
                        buf[d, s] = buf[d, s + 1]
                    bcnt[d] -= 1
                    ret[d] = 1

            # (G) write forward outputs (bubble where no grant)
            north[r, c].put(outpkt[0])
            east[r, c + 1].put(outpkt[1])
            south[r + 1, c].put(outpkt[2])
            west[r, c].put(outpkt[3])
            deliver[r, c].put(outpkt[4])

            # (H) write credit returns for MY inputs (1 if I freed that input's slot this cycle)
            cr_south[r, c].put(ret[0])
            cr_west[r, c + 1].put(ret[1])
            cr_north[r + 1, c].put(ret[2])
            cr_east[r, c].put(ret[3])
            cr_inject[r, c].put(ret[4])

    # ── PE on every node: sources host seeds, computes on operands, sinks results; all lossless ──
    @df.kernel(mapping=[ROWS, COLUMNS], args=[])   # pure stream I/O (host data via seed_s/fwd_s/sink_s)
    def pe_node():
        r, c = df.get_pid()
        fwdp: UInt(PS) = fwd_s[r, c].get()          # one-shot: packed forward target (fr<<W)|fc
        fr:   int32 = (fwdp >> W) & CMASK
        fc:   int32 = fwdp & CMASK
        seed_local: UInt(PS)[LANELEN] = 0           # preload host seeds (consumed lazily below via sp)
        for i in range(LANELEN):
            seed_local[i] = seed_s[r, c].get()
        icred: int32 = 0          # credits I hold for injecting (free slots in router's Local buffer)
        txv:   int32 = 0          # is there a packet waiting to inject?
        txp:   UInt(PS) = 0       # the waiting packet (computed result OR sourced seed)
        sp:    int32 = 0          # seed pointer (advances only as seed slots are consumed)
        cr_deliver[r, c].put(1)   # PRIME: PE initially ready to accept one delivery
        for t in range(NUM_IT):
            icred += cr_inject[r, c].get()      # router returned credit(s) for my injects
            a: UInt(PS) = deliver[r, c].get()   # my delivery (valid only when I granted credit)
            snk: UInt(PS) = 0                   # sink-stream value this cycle (0 = bubble)
            if a[VLD] == 1:
                if a[DONE] == 1:                # final result -> sink (store kernel records it)
                    snk = a
                else:                           # operand -> compute; result becomes the pending tx
                    res: int32 = (a & 0xFFFF) * PE_K
                    txp = (res & 0xFFFF) | (fc << COL_LO) | (fr << ROW_LO) | (1 << VLD) | (1 << DONE)
                    txv = 1
            else:
                if txv == 0 and sp < LANELEN:   # idle delivery slot -> try to source a host seed
                    s: UInt(PS) = seed_local[sp]
                    sp += 1
                    if s != 0:
                        txp = s; txv = 1
            out: UInt(PS) = 0                   # inject the pending packet if I hold a credit
            if txv == 1 and icred > 0:
                out = txp; txv = 0; icred -= 1
            inject[r, c].put(out)
            dc: int32 = 0                       # accept next delivery only if my tx slot is now free
            if txv == 0:
                dc = 1
            cr_deliver[r, c].put(dc)
            sink_s[r, c].put(snk)               # always-fire on the sink stream

    # ── LOAD kernel: SINGLE instance owns `inj`+`fwd`; one-shot fwd + burst-preloads seeds ──
    @df.kernel(mapping=[1], args=[inj, fwd])
    def loader(seed: int32[ROWS, COLUMNS, LANELEN], fwdt: int32[ROWS, COLUMNS, 2]):
        with allo.meta_for(0, ROWS) as r:
            with allo.meta_for(0, COLUMNS) as c:
                fwd_s[r, c].put((fwdt[r, c, 0] << W) | fwdt[r, c, 1])
                with allo.meta_for(0, LANELEN) as i:
                    seed_s[r, c].put(seed[r, c, i])

    # ── STORE kernel: SINGLE instance drains sink_s and owns `dlv` (one writer) ──
    @df.kernel(mapping=[1], args=[dlv])
    def storer(log: int32[ROWS, COLUMNS, LANELEN]):
        kp: int32[ROWS, COLUMNS] = 0                 # per-PE write pointers (constant-indexed)
        for t in range(NUM_IT):
            with allo.meta_for(0, ROWS) as r:
                with allo.meta_for(0, COLUMNS) as c:
                    w: UInt(PS) = sink_s[r, c].get()
                    if w[VLD] == 1 and kp[r, c] < LANELEN:
                        log[r, c, kp[r, c]] = w & 0xFFFF; kp[r, c] += 1

    # ── edge stubs (now credit-aware): drivers feed boundary inputs w/ bubbles & drain credit;
    #    collectors drain boundary outputs & PRIME + return credits so interior never stalls ──
    @df.kernel(mapping=[COLUMNS], args=[])
    def drv_n_edge():
        c = df.get_pid()
        for t in range(NUM_IT):
            south[0, c].put(0); _u: int32 = cr_south[0, c].get()
    @df.kernel(mapping=[COLUMNS], args=[])
    def col_n_edge():
        c = df.get_pid()
        cr_north[0, c].put(BUF_DEPTH)
        for t in range(NUM_IT):
            w: UInt(PS) = north[0, c].get(); rc: int32 = 0
            if w[VLD] == 1: rc = 1
            cr_north[0, c].put(rc)

    @df.kernel(mapping=[COLUMNS], args=[])
    def drv_s_edge():
        c = df.get_pid()
        for t in range(NUM_IT):
            north[ROWS, c].put(0); _u: int32 = cr_north[ROWS, c].get()
    @df.kernel(mapping=[COLUMNS], args=[])
    def col_s_edge():
        c = df.get_pid()
        cr_south[ROWS, c].put(BUF_DEPTH)
        for t in range(NUM_IT):
            w: UInt(PS) = south[ROWS, c].get(); rc: int32 = 0
            if w[VLD] == 1: rc = 1
            cr_south[ROWS, c].put(rc)

    @df.kernel(mapping=[ROWS], args=[])
    def drv_w_edge():
        r = df.get_pid()
        for t in range(NUM_IT):
            east[r, 0].put(0); _u: int32 = cr_east[r, 0].get()
    @df.kernel(mapping=[ROWS], args=[])
    def col_w_edge():
        r = df.get_pid()
        cr_west[r, 0].put(BUF_DEPTH)
        for t in range(NUM_IT):
            w: UInt(PS) = west[r, 0].get(); rc: int32 = 0
            if w[VLD] == 1: rc = 1
            cr_west[r, 0].put(rc)

    @df.kernel(mapping=[ROWS], args=[])
    def drv_e_edge():
        r = df.get_pid()
        for t in range(NUM_IT):
            west[r, COLUMNS].put(0); _u: int32 = cr_west[r, COLUMNS].get()
    @df.kernel(mapping=[ROWS], args=[])
    def col_e_edge():
        r = df.get_pid()
        cr_east[r, COLUMNS].put(BUF_DEPTH)
        for t in range(NUM_IT):
            w: UInt(PS) = east[r, COLUMNS].get(); rc: int32 = 0
            if w[VLD] == 1: rc = 1
            cr_east[r, COLUMNS].put(rc)


def pack(data, col, row, valid=1, done=0):
    return int(data | (col << COL_LO) | (row << ROW_LO) | (valid << VLD) | (done << DONE))


def run(sim, jobs, label):
    # job = (src_r,src_c, cmp_r,cmp_c, fwd_r,fwd_c, operand, lane)
    inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    fwd = np.zeros((ROWS, COLUMNS, 2), dtype=np.int32)
    for sr, sc, cr, cc, fr, fc, op, lane in jobs:
        inj[sr, sc, lane] = pack(data=op, col=cc, row=cr, done=0)
        fwd[cr, cc, 0] = fr; fwd[cr, cc, 1] = fc
    sim(inj, fwd, dlv)                                # arg order matches region sig (inj, fwd, dlv)
    ok = True
    print(f"\n--- {label} ---")
    for sr, sc, cr, cc, fr, fc, op, lane in jobs:
        expect = (op * PE_K) & 0xFFFF
        hit = expect in [int(dlv[fr, fc, k]) for k in range(LANELEN)]
        print(f"  seed 0x{op:02x}@({sr},{sc}) -> compute({cr},{cc})*{PE_K} -> "
              f"0x{expect:04x} sink@({fr},{fc}) : {'OK' if hit else 'MISSING'}")
        ok = ok and hit
    print(f"{label.split(':')[0]}", "PASS" if ok else "FAIL")
    return ok


if __name__ == "__main__":
    sim = df.build(router_XY_NoC, target="simulator")

    # Part A: single PE->PE relay (regression vs bufferless)
    run(sim, [(0, 0, 2, 2, 3, 3, 0x07, 0)], "PE-RELAY: single chain")

    # Part B: 4 column-disjoint chains (no contention) — regression
    run(sim, [(0, j, 1, j, 3, j, (j + 2), 0) for j in range(COLUMNS)], "PE-MULTI: 4 disjoint chains")

    # Part C: CONTENTION fan-in — 4 sources all target the SAME compute PE (2,2), which forwards
    # every result to the SAME sink (1,1). Heavy delivery + inject contention; a bufferless router
    # would DROP all but one per cycle. With credit backpressure all 4 must arrive (serialized).
    run(sim, [(0, 0, 2, 2, 1, 1, 2, 0),
              (0, 3, 2, 2, 1, 1, 3, 0),
              (3, 0, 2, 2, 1, 1, 4, 0),
              (3, 3, 2, 2, 1, 1, 5, 0)], "CONTENTION: 4->1 fan-in (lossless)")

    print(df.build(router_XY_NoC, target="vhls").hls_code)
