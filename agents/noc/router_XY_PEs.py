import os; os.environ.setdefault("OMP_NUM_THREADS", "256")   # >= #instances (80); set before allo
import allo
from allo.ir.types import float16, int16, int32, UInt, AlloType, Stream
import allo.dataflow as df
import numpy as np



# XY-router: 5-port unit (North, South, East, West, Local)
# 1. Input buffers: one FIFO per input to absorb backpressure and decouple upstream timing
# 2. Route computation: XY logic. compare flit's destination (x,y) against this node's coordinates
#    route in X until dx==0, then Y, then eject to local.
# 3. Switch allocation / arbitration: when two inputs request same output port in a cycle,
#    an arbiter picks a winner per output (e.g. Round-Robin)
# 4. Crossbar: 5x5 MUX that connects granted input to its output port
# 5. Output registers + flow control: register the outputs, implement backpressure (credit-based or valid/ready)

# Grid size
ROWS = 4
COLUMNS = 4

# packet layout (LSB-first):  data[0:16] dest_col[16:19] dest_row[19:22] valid[22] done[23]
DW = 16              # payload width
W  = 3              # coord width (3 bits -> 8x8 headroom)
COL_LO = DW          # dest_col starts here  -> [16:19]
ROW_LO = DW + W      # dest_row starts here  -> [19:22]
VLD    = DW + 2 * W      # valid bit position -> 22
DONE   = DW + 2 * W + 1  # done  bit position -> 23  (0=operand: PE computes & re-injects;
                         #                            1=result:  PE sinks it to dlv -> terminates)
PS     = DW + 2 * W + 2  # total packet width -> 24
CMASK  = (1 << W) - 1    # mask for a W-bit coord field  -> 0x7
#
# BIT-FIELD ENCODING (how one integer carries several fields):
#   each field lives at a fixed OFFSET (its low-bit position) and has a fixed WIDTH.
#   PACK   (build):  field_value << OFFSET, then OR all fields together.
#   UNPACK (read) :  (packet >> OFFSET) & ((1<<WIDTH)-1)
#                    >> brings the field down to bit 0; & MASK chops off higher fields.
#   MASK = (1<<WIDTH)-1 = "WIDTH ones" (W=3 -> 0b111 = 0x7); valid=1 bit -> mask 1.
#
#   Worked example: pack(data=0xABCD, col=3, row=2, valid=1)
#     = 0xABCD | (3<<16) | (2<<19) | (1<<22) = 0x53ABCD
#     unpack: (0x53ABCD>>16)&7=3 (col)  (0x53ABCD>>19)&7=2 (row)  (0x53ABCD>>22)&1=1 (valid)


# number of always-fire cycles to simulate (4x4 packet needs <=~7 hops; keep small — sim cost
# scales with this. feather uses 8; 2000 was ~250x too big and looked hung)
NUM_IT = 64
# tokens each driver injects / collector drains per lane (<= NUM_IT)
LANELEN = 8

# Directions
DIR = 5

# ── scale-up: EVERY node's Local port hosts a (minimal) PE; no inject/deliver stubs, only edges ──
# each PE: sources host seed packets from `inj`, and on each valid arrival computes payload*PE_K
# and records the result into `dlv` (sink -> the net terminates; no re-forward, no infinite bounce).
PE_K = 3                 # the PE's "compute": multiply arrived payload by this constant


@df.region()
# NOTE arg order = (inj, fwd, dlv): must match the kernel arg DISCOVERY order below
# (loader sees inj,fwd ; storer sees dlv) — the simulator binds arrays positionally to that order.
def router_XY_NoC(inj: int32[ROWS, COLUMNS, LANELEN],
                  fwd: int32[ROWS, COLUMNS, 2],      # per-PE forward target (row,col) for computed result
                  dlv: int32[ROWS, COLUMNS, LANELEN]):

    # link streams named by FLOW direction (south=northbound->southbound etc); +1 perimeter for edge drv/col
    north: Stream[UInt(PS), 4][ROWS + 1, COLUMNS]
    south: Stream[UInt(PS), 4][ROWS + 1, COLUMNS]
    east:  Stream[UInt(PS), 4][ROWS, COLUMNS + 1]
    west:  Stream[UInt(PS), 4][ROWS, COLUMNS + 1]

    inject:  Stream[UInt(PS), 4][ROWS, COLUMNS]   # core -> router (new packets)
    deliver: Stream[UInt(PS), 4][ROWS, COLUMNS]   # router -> core (arrived packets)

    # ── host<->PE feed-forward streams (replace direct array args on the replicated pe_node) ──
    # A mapped kernel can't take a whole top-level array (16 readers/writers -> HLS 200-779/979),
    # so the host arrays are owned by SINGLE load/store kernels that bridge array<->stream.
    seed_s: Stream[UInt(PS), 4][ROWS, COLUMNS]    # host seed packet, one per cycle (0 = bubble)
    sink_s: Stream[UInt(PS), 4][ROWS, COLUMNS]    # PE's sunk result, one per cycle (0 = bubble)
    fwd_s:  Stream[UInt(PS), 4][ROWS, COLUMNS]    # per-PE forward target, packed (fr<<W)|fc, sent ONCE


    @df.kernel(mapping=[ROWS, COLUMNS], args=[])   # pure stream I/O -> no top-level array args
    def router_XY():
    
      # get coordinates for router identification
      row_id, col_id = df.get_pid() 
      
      
      # ── per-input arrays (index: 0=N 1=E 2=S 3=W 4=Local) ──
      pkt: UInt(PS)[DIR] = 0     # received packet per input
      vld: int32[DIR] = 0        # valid bit per input
      col: int32[DIR] = 0        # dest column per input
      row: int32[DIR] = 0        # dest row per input
        
      # ── PRIME the pipe: emit one bubble per output BEFORE the loop so every interior link
      #    holds a token at t=0. Without this, neighbours circularly wait in their read phase
      #    (e.g. (r,c).E-in <- (r,c+1).W-out and vice-versa) -> deadlock. Edge-fed inputs are
      #    primed by the edge drivers, so this only matters for router<->router links.
      north[row_id, col_id].put(0)
      east[row_id, col_id + 1].put(0)
      south[row_id + 1, col_id].put(0)
      west[row_id, col_id].put(0)
      deliver[row_id, col_id].put(0)

      for t in range(NUM_IT):     # bounded always-fire loop (drivers must push NUM_IT tokens)


        # receive one packet per input (0=N 1=E 2=S 3=W 4=Local); read the OPPOSITE-flow stream
        pkt[0] = south[row_id, col_id].get()         # N input = southbound link arriving from above
        pkt[1] = west[row_id, col_id + 1].get()      # E input = westbound link arriving from the right
        pkt[2] = north[row_id + 1, col_id].get()     # S input = northbound link arriving from below
        pkt[3] = east[row_id, col_id].get()          # W input = eastbound link arriving from the left
        pkt[4] = inject[row_id, col_id].get()        # Local input = core injecting a new packet

        # decode each input: valid bit, dest column, dest row
        for d in range(DIR):
            p: UInt(PS) = pkt[d]
            vld[d] = (p >> VLD) & 1            # valid bit
            col[d] = (p >> COL_LO) & CMASK     # dest column
            row[d] = (p >> ROW_LO) & CMASK     # dest row

        # ── XY route compute: output port per input (0=N 1=E 2=S 3=W 4=Local) ──
        dst: int32[DIR] = 0          # chosen port; only meaningful when vld[d] == 1
        for d in range(DIR):
            if col[d] > col_id:    dst[d] = 1   # east  (dest column to my right)
            elif col[d] < col_id:  dst[d] = 3   # west  (dest column to my left)
            elif row[d] > row_id:  dst[d] = 2   # south (dest row below me)
            elif row[d] < row_id:  dst[d] = 0   # north (dest row above me)
            else:                  dst[d] = 4   # local (arrived: same row & col)

        # ── fixed-priority arbitration: at most one input granted per output port ──
        grant: int32[DIR] = 0        # winning input index for output port o
        out_vld: int32[DIR] = 0      # 1 if output port o is active this cycle
        for o in range(DIR):
            for d in range(DIR):     # d ascending => priority N>E>S>W>Local (first wins)
                if vld[d] == 1 and dst[d] == o and out_vld[o] == 0:
                    grant[o] = d; out_vld[o] = 1

        # ── crossbar: one output packet per port; 0 = bubble (default), else granted input ──
        outpkt: UInt(PS)[DIR] = 0
        for o in range(DIR):
            if out_vld[o] == 1:
                outpkt[o] = pkt[grant[o]]    # forward granted input's packet to port o

        # ── output write: send dir -> write that dir's flow stream (fires every cycle; bubble=0) ──
        north[row_id, col_id].put(outpkt[0])         # send North (northbound)
        east[row_id, col_id + 1].put(outpkt[1])      # send East  (eastbound)
        south[row_id + 1, col_id].put(outpkt[2])     # send South (southbound)
        west[row_id, col_id].put(outpkt[3])          # send West  (westbound)
        deliver[row_id, col_id].put(outpkt[4])       # eject Local -> core (arrived packet)

    # ── PE on EVERY node's Local port (replaces the inject-driver + deliver-collector stubs) ──
    # Each PE, every cycle, both CONSUMES its arrival (deliver[r,c]) and PRODUCES into inject[r,c]:
    #   - valid arrival, done==0 (operand): COMPUTE payload*PE_K, repack -> inject toward fwd[r,c]
    #       with done=1. This is the PE generating + injecting its OWN packet into the NoC.
    #   - valid arrival, done==1 (result):  SINK -> record payload to dlv[r,c]; inject a bubble.
    #       done=1 terminates the chain so a uniform PE doesn't re-forward forever.
    #   - no arrival:                       SOURCE a host seed from inj[r,c,t] (0 = bubble).
    @df.kernel(mapping=[ROWS, COLUMNS], args=[])   # pure stream I/O (host data arrives via seed_s/fwd_s)
    def pe_node():
        r, c = df.get_pid()
        fwdp: UInt(PS) = fwd_s[r, c].get()           # one-shot: this PE's packed forward target
        fr:   int32 = (fwdp >> W) & CMASK            # forward target row
        fc:   int32 = fwdp & CMASK                   # forward target col
        for t in range(NUM_IT):
            s: UInt(PS) = seed_s[r, c].get()         # always-read: host seed this cycle (0 = bubble)
            a: UInt(PS) = deliver[r, c].get()        # this PE's arrival this cycle
            out:  UInt(PS) = 0                       # default: inject a bubble
            snk:  UInt(PS) = 0                       # default: sink a bubble (always-fire on sink_s)
            if a[VLD] == 1:
                if a[DONE] == 1:                     # final result reached its dest -> sink
                    snk = a                          # forward whole packet; store records payload
                else:                                # operand -> compute & inject a NEW packet
                    res: int32 = (a & 0xFFFF) * PE_K
                    out = (res & 0xFFFF) | (fc << COL_LO) | (fr << ROW_LO) | (1 << VLD) | (1 << DONE)
            else:
                out = s                              # no arrival -> source the host seed (0 if bubble)
            inject[r, c].put(out)                    # PE -> router (the PE's injection path)
            sink_s[r, c].put(snk)                    # PE -> host store (result, or bubble)

    # ── LOAD kernel: SINGLE instance owns `inj`+`fwd`; fans seed/fwd out to per-PE streams ──
    @df.kernel(mapping=[1], args=[inj, fwd])
    def loader(seed: int32[ROWS, COLUMNS, LANELEN], fwdt: int32[ROWS, COLUMNS, 2]):
        with allo.meta_for(0, ROWS) as r:            # one-shot fwd: packed (fr<<W)|fc
            with allo.meta_for(0, COLUMNS) as c:
                fwd_s[r, c].put((fwdt[r, c, 0] << W) | fwdt[r, c, 1])
        for t in range(NUM_IT):                      # per-cycle seed (0 once t >= LANELEN)
            with allo.meta_for(0, ROWS) as r:
                with allo.meta_for(0, COLUMNS) as c:
                    w: UInt(PS) = 0
                    if t < LANELEN:
                        w = seed[r, c, t]
                    seed_s[r, c].put(w)

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

    # ── NORTH edge: bubble-driver feeds south[0,c]; drain-collector empties north[0,c] ──
    @df.kernel(mapping=[COLUMNS], args=[])
    def drv_n_edge():
        c = df.get_pid()
        for t in range(NUM_IT):
            south[0, c].put(0)                       # boundary injects only bubbles
    @df.kernel(mapping=[COLUMNS], args=[])
    def col_n_edge():
        c = df.get_pid()
        for t in range(NUM_IT):
            wn: UInt(PS) = north[0, c].get()         # drain north-edge output (discard)

    # ── SOUTH edge: bubble-driver feeds north[ROWS,c]; drain-collector empties south[ROWS,c] ──
    @df.kernel(mapping=[COLUMNS], args=[])
    def drv_s_edge():
        c = df.get_pid()
        for t in range(NUM_IT):
            north[ROWS, c].put(0)                     # boundary injects only bubbles
    @df.kernel(mapping=[COLUMNS], args=[])
    def col_s_edge():
        c = df.get_pid()
        for t in range(NUM_IT):
            ws: UInt(PS) = south[ROWS, c].get()       # drain south-edge output (discard)

    # ── WEST edge: bubble-driver feeds east[r,0]; drain-collector empties west[r,0] ──
    @df.kernel(mapping=[ROWS], args=[])
    def drv_w_edge():
        r = df.get_pid()
        for t in range(NUM_IT):
            east[r, 0].put(0)                         # boundary injects only bubbles
    @df.kernel(mapping=[ROWS], args=[])
    def col_w_edge():
        r = df.get_pid()
        for t in range(NUM_IT):
            ww: UInt(PS) = west[r, 0].get()           # drain west-edge output (discard)

    # ── EAST edge: bubble-driver feeds west[r,COLUMNS]; drain-collector empties east[r,COLUMNS] ──
    @df.kernel(mapping=[ROWS], args=[])
    def drv_e_edge():
        r = df.get_pid()
        for t in range(NUM_IT):
            west[r, COLUMNS].put(0)                   # boundary injects only bubbles
    @df.kernel(mapping=[ROWS], args=[])
    def col_e_edge():
        r = df.get_pid()
        for t in range(NUM_IT):
            we: UInt(PS) = east[r, COLUMNS].get()     # drain east-edge output (discard)


def pack(data, col, row, valid=1, done=0):               # build a packet integer (layout at top)
    return int(data | (col << COL_LO) | (row << ROW_LO) | (valid << VLD) | (done << DONE))


def run(sim, jobs, label):
    # jobs: list of (src_r,src_c, cmp_r,cmp_c, fwd_r,fwd_c, operand, lane)
    #   host seeds operand at src (addressed to the COMPUTE PE), the compute PE multiplies by PE_K
    #   and injects the result toward (fwd_r,fwd_c), where that PE sinks it into dlv.
    inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    fwd = np.zeros((ROWS, COLUMNS, 2), dtype=np.int32)
    for sr, sc, cr, cc, fr, fc, op, lane in jobs:
        inj[sr, sc, lane] = pack(data=op, col=cc, row=cr, done=0)   # operand -> compute PE
        fwd[cr, cc, 0] = fr; fwd[cr, cc, 1] = fc                    # compute PE forwards result here
    sim(inj, fwd, dlv)                                # arg order matches region sig (inj, fwd, dlv)
    ok = True
    print(f"\n--- {label} ---")
    for sr, sc, cr, cc, fr, fc, op, lane in jobs:
        expect = (op * PE_K) & 0xFFFF
        hit = expect in [int(dlv[fr, fc, k]) for k in range(LANELEN)]
        print(f"  seed 0x{op:02x}@({sr},{sc}) -> compute({cr},{cc})*{PE_K} -> "
              f"result 0x{expect:04x} sink@({fr},{fc}) : {'OK' if hit else 'MISSING'}")
        ok = ok and hit
    print(f"{label.split(':')[0]}", "PASS" if ok else "FAIL")
    return ok


if __name__ == "__main__":
    sim = df.build(router_XY_NoC, target="simulator")

    # Part A: single PE->PE relay (2D route in, 2D route out) — connectivity sanity
    #   (0,0) sources operand 0x7 -> compute PE (2,2) -> result -> sink PE (3,3)
    run(sim, [(0, 0, 2, 2, 3, 3, 0x07, 0)], "PE-RELAY: single chain")

    # Part B: 4 concurrent PE->PE chains, one per column (column-disjoint => no contention).
    #   col j: source (0,j) -> compute (1,j) -> sink (3,j)
    jobs = [(0, j, 1, j, 3, j, (j + 2), 0) for j in range(COLUMNS)]
    run(sim, jobs, "PE-MULTI: 4 concurrent chains")

    # generate HLS code (allo dataflow example style, e.g. test_stream_of_blocks.py)
    print(df.build(router_XY_NoC, target="vhls").hls_code)
       
        
      
      
      
      
      
      
      
      
      
      
    
    
    
    
    
