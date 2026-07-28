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

# packet layout (LSB-first):  data[0:16] dest_col[16:19] dest_row[19:22] valid[22]
DW = 16              # payload width
W  = 3              # coord width (3 bits -> 8x8 headroom)
COL_LO = DW          # dest_col starts here  -> [16:19]
ROW_LO = DW + W      # dest_row starts here  -> [19:22]
VLD    = DW + 2 * W  # valid bit position    -> 22
PS     = DW + 2 * W + 1  # total packet width -> 23
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

# ── connectivity check: ONE minimal PE on this node's Local port (rest of mesh = stub drv/col) ──
PE_R, PE_C = 2, 2        # node hosting the PE
PE_K       = 3           # the PE's "compute": multiply payload by this constant
PE_DR, PE_DC = 3, 3      # where the PE sends its result


@df.region()
def router_XY_NoC(inj: int32[ROWS, COLUMNS, LANELEN], dlv: int32[ROWS, COLUMNS, LANELEN]):

    # link streams named by FLOW direction (south=northbound->southbound etc); +1 perimeter for edge drv/col
    north: Stream[UInt(PS), 4][ROWS + 1, COLUMNS]
    south: Stream[UInt(PS), 4][ROWS + 1, COLUMNS]
    east:  Stream[UInt(PS), 4][ROWS, COLUMNS + 1]
    west:  Stream[UInt(PS), 4][ROWS, COLUMNS + 1]

    inject:  Stream[UInt(PS), 4][ROWS, COLUMNS]   # core -> router (new packets)
    deliver: Stream[UInt(PS), 4][ROWS, COLUMNS]   # router -> core (arrived packets)
    
    
    
    @df.kernel(mapping=[ROWS, COLUMNS], args=[])   # pure stream I/O -> no top-level array args
    def router_XY():
    
      # get coordinates for router identification
      row_id, col_id = df.get_pid() 
      
      
      # ── per-input arrays (index: 0=N 1=E 2=S 3=W 4=Local) ──
      pkt: UInt(PS)[DIR] = 0     # received packet per input
      vld: int32[DIR] = 0        # valid bit per input
      col: int32[DIR] = 0        # dest column per input
      row: int32[DIR] = 0        # dest row per input

      # ── round-robin state: per-output rotating priority pointer. Declared BEFORE the loop so it
      #    PERSISTS across cycles (a register); it is NOT reset each iteration. rr[o] = the input
      #    index the arbiter for output o should start scanning from this cycle. ──
      rr: int32[DIR] = 0

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

        # ── round-robin arbitration: at most one input granted per output port. Scan inputs
        #    starting at rr[o] and wrapping; first valid requester wins. Then advance rr[o] past
        #    the winner so a different input leads next cycle -> no input can starve. ──
        grant: int32[DIR] = 0        # winning input index for output port o
        out_vld: int32[DIR] = 0      # 1 if output port o is active this cycle
        for o in range(DIR):
            for i in range(DIR):     # i = offset from the rotating start position rr[o]
                d: int32 = rr[o] + i
                if d >= DIR:         # wrap (rr[o]<DIR and i<DIR => one subtract is enough; no % divider)
                    d -= DIR
                if vld[d] == 1 and dst[d] == o and out_vld[o] == 0:
                    grant[o] = d; out_vld[o] = 1
            if out_vld[o] == 1:      # rotate: just-served input drops to lowest priority next cycle
                nxt: int32 = grant[o] + 1
                if nxt >= DIR:
                    nxt -= DIR
                rr[o] = nxt

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

    # ── INJECT drivers: one per core; push pre-packed packets from `inj` into inject[r,c] ──
    # ── INJECT load kernel: SINGLE instance owns `inj` (one reader) and fans out to the per-node
    # inject[r,c] streams. The 16 stream indices are Python-unrolled (compile-time constants -> each
    # FIFO is statically selected); only `t` is a hardware loop. Single-reader of `inj` => csynth-legal
    # (mapping=[ROWS,COLUMNS] gave 16 readers of the whole array -> HLS 200-779/979). meta_if skips the
    # PE node so inject[PE_R,PE_C] keeps exactly one producer (pe_mul). ──
    @df.kernel(mapping=[1], args=[inj])
    def drv_inject(din: int32[ROWS, COLUMNS, LANELEN]):
        for t in range(NUM_IT):                          # hardware loop
            with allo.meta_for(0, ROWS) as r:            # COMPILE-TIME unroll -> stream idx is constant
                with allo.meta_for(0, COLUMNS) as c:
                    with allo.meta_if((r != PE_R) or (c != PE_C)):
                        w: UInt(PS) = 0                  # always-fire: bubble by default
                        if t < LANELEN:
                            w = din[r, c, t]             # this core's t-th packet (0 = bubble)
                        inject[r, c].put(w)

    # ── DELIVER store kernel: SINGLE instance drains every deliver[r,c] stream and owns `dlv`
    # (one writer). Same unroll + meta_if-skip-PE rationale as the load kernel above. ──
    @df.kernel(mapping=[1], args=[dlv])
    def col_deliver(dout: int32[ROWS, COLUMNS, LANELEN]):
        kp: int32[ROWS, COLUMNS] = 0                 # per-node write pointers (constant-indexed)
        for t in range(NUM_IT):                          # TIME OUTER (hardware): one item from every node each cycle
            with allo.meta_for(0, ROWS) as r:            # COMPILE-TIME unroll -> stream idx is constant
                with allo.meta_for(0, COLUMNS) as c:
                    with allo.meta_if((r != PE_R) or (c != PE_C)):
                        w: UInt(PS) = deliver[r, c].get()   # always-read every cycle
                        if w[VLD] == 1 and kp[r, c] < LANELEN:
                            dout[r, c, kp[r, c]] = w; kp[r, c] += 1

    # ── minimal PE on node (PE_R,PE_C): drain arrival -> multiply payload -> inject result ──
    # connectivity check only: proves a compute node can both consume from deliver[] and
    # produce into inject[] inside the same @df.region and route a result to another node.
    @df.kernel(mapping=[1], args=[])
    def pe_mul():
        for t in range(NUM_IT):
            a: UInt(PS) = deliver[PE_R, PE_C].get()  # drain this node's arrivals every cycle
            out: UInt(PS) = 0                        # bubble by default (always-fire)
            if a[VLD] == 1:
                prod: int32 = (a & 0xFFFF) * PE_K    # the "compute": single int multiply
                # repack result with dest header (shift+mask pack; no bitslices -> avoids trunci bug)
                out = (prod & 0xFFFF) | (PE_DC << COL_LO) | (PE_DR << ROW_LO) | (1 << VLD)
            inject[PE_R, PE_C].put(out)              # inject result (or bubble) into the router

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


def pack(data, col, row, valid=1):                       # build a packet integer (layout at top)
    return int(data | (col << COL_LO) | (row << ROW_LO) | (valid << VLD))


if __name__ == "__main__":
    # functional sim: core (0,0) injects a packet for core (2,3); check it arrives there only
    sim = df.build(router_XY_NoC, target="simulator")
    inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    PKT = pack(data=0xABCD, col=3, row=2)
    inj[0, 0, 0] = PKT
    sim(inj, dlv)                                        # region args in discovery order: inj, dlv
    got = int(dlv[2, 3, 0]); stray = int(dlv.sum()) - got
    print(f"inject 0x{PKT:06x} @(0,0)->dest(2,3) | delivered 0x{got:06x} | stray={stray}")
    print("ROUTER XY", "PASS" if (got == PKT and stray == 0) else "FAIL")

    # ── Part 2: multi-node concurrent traffic (stress the NoC / arbiter) ──
    # 4 cores inject on the SAME cycle (lane 0) toward distinct destinations. XY paths
    # weave through the mesh but (by construction) never share a node on the same cycle,
    # so a correct NoC delivers all 4 with no drops. Each payload is unique so we can
    # identify where it landed.
    print("\n--- Part 2: multi-node concurrent traffic ---")
    inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    traffic = [                       # (src_row, src_col, dst_row, dst_col, payload)
        (0, 0, 1, 2, 0x1111),
        (1, 3, 2, 1, 0x2222),
        (2, 0, 3, 3, 0x3333),
        (3, 2, 0, 0, 0x4444),
    ]
    for sr, sc, dr, dc, data in traffic:
        inj[sr, sc, 0] = pack(data=data, col=dc, row=dr)   # all injected at cycle t=0
    sim(inj, dlv)

    ok = True
    for sr, sc, dr, dc, data in traffic:
        arrived = [int(dlv[dr, dc, k]) & 0xFFFF for k in range(LANELEN)]   # payloads at dest node
        hit = data in arrived
        print(f"  ({sr},{sc})->({dr},{dc}) data 0x{data:04x} : "
              f"{'delivered' if hit else 'DROPPED/missing'}")
        ok = ok and hit
    delivered = int((dlv != 0).sum())                      # one non-zero slot per delivered packet
    print(f"  delivered slots={delivered} expected={len(traffic)}")
    print("MULTI-NODE", "PASS" if (ok and delivered == len(traffic)) else "FAIL")

    # ── Part 3: contention sub-test (bufferless arbiter drops the loser) ──
    # Two packets reach node (1,1) on the SAME cycle (t=1) both wanting the EAST output:
    #   B = transit from the West input  (d=3)  -- (1,0)->(1,3), injected lane 0
    #   A = injected at the Local input  (d=4)  -- (1,1)->(1,2), injected lane 1
    # Fixed priority N>E>S>W>Local => W(d=3) beats Local(d=4): B is forwarded, A is dropped
    # (no input buffering / no retry). Expected: B arrives, A is missing.
    print("\n--- Part 3: contention (same cycle, same output port) ---")
    inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    inj[1, 0, 0] = pack(data=0xB0B0, col=3, row=1)         # B: West input @ (1,1), wants East
    inj[1, 1, 1] = pack(data=0xA0A0, col=2, row=1)         # A: Local input @ (1,1), wants East
    sim(inj, dlv)

    b_got = 0xB0B0 in [int(dlv[1, 3, k]) & 0xFFFF for k in range(LANELEN)]   # winner -> (1,3)
    a_got = 0xA0A0 in [int(dlv[1, 2, k]) & 0xFFFF for k in range(LANELEN)]   # loser  -> (1,2)
    delivered = int((dlv != 0).sum())
    print(f"  B (West input, higher prio) -> (1,3) : {'delivered' if b_got else 'MISSING'}")
    print(f"  A (Local input, lower prio) -> (1,2) : {'dropped (expected)' if not a_got else 'DELIVERED?!'}")
    print(f"  delivered slots={delivered} expected=1 (loser dropped)")
    print("CONTENTION", "PASS" if (b_got and not a_got and delivered == 1) else "FAIL")

    # ── Part 4: minimal-PE connectivity (single int multiply on node (PE_R,PE_C)) ──
    # send an operand TO the PE node; the PE multiplies the payload by PE_K and forwards the
    # result to (PE_DR,PE_DC). Proves a compute node can consume deliver[] AND produce inject[]
    # inside the same region and route a result onward (the actual PE<->router connectivity test).
    print(f"\n--- Part 4: minimal PE @ ({PE_R},{PE_C}) (payload * {PE_K}) ---")
    inj = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    dlv = np.zeros((ROWS, COLUMNS, LANELEN), dtype=np.int32)
    OPND = 0x0007
    inj[0, PE_C, 0] = pack(data=OPND, col=PE_C, row=PE_R)   # operand from (0,PE_C) -> PE node
    sim(inj, dlv)
    expect = (OPND * PE_K) & 0xFFFF                          # PE multiplies, result -> (PE_DR,PE_DC)
    got = [int(dlv[PE_DR, PE_DC, k]) & 0xFFFF for k in range(LANELEN)]
    hit = expect in got
    print(f"  operand 0x{OPND:04x} -> PE({PE_R},{PE_C})*{PE_K} -> "
          f"result 0x{expect:04x} @dest({PE_DR},{PE_DC}) : {'delivered' if hit else 'MISSING'}")
    print("PE-CONNECT", "PASS" if hit else "FAIL")

    # generate HLS code (allo dataflow example style, e.g. test_stream_of_blocks.py)
    print(df.build(router_XY_NoC, target="vhls").hls_code)
       
        
      
      
      
      
      
      
      
      
      
      
    
    
    
    
    
