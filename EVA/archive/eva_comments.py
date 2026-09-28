# eva_comments.py — FULLY-COMMENTED companion of eva.py (the EVA accelerator).
# The CODE is the exact same program as eva.py (verified by AST compare); only
# the commentary differs. Read this file to understand the design; run eva.py.
#
# EVA = M×N mesh of FUSED router+PE nodes, always-fire/bubble execution model:
# every inter-node link is an Allo Stream that carries exactly ONE word per
# emulated cycle — a real token or an all-zero BUBBLE — so no process ever
# waits for "data that may come later"; the whole fabric steps in lockstep.
# Each node overlays THREE 4-directional networks on the same grid:
#   systolic — data words {vld, data}            (golden systolic_tx/rx.sv)
#   router   — packets {rq, id, mode, addr, data} (golden router.sv)
#   credit   — reverse int words, one per router link — lossless back-pressure
# The chip is ROUTER-LOAD ONLY: programs, weights and config all arrive as
# router packets through the perimeter (rin_*); there is no direct program port.
#
# END-PUT PRIMED (RTL deadlock fix, 2026-07-05): every process emits its t=0
# outputs BEFORE its loop, and the in-loop puts sit at the END of the iteration.
# The word sequence on every stream is IDENTICAL to the older top-put form, but
# every feedback edge starts with one in-flight token, so the RTL schedule
# (which packs all reads before all writes inside one II) cannot deadlock.
# Validated: replay cosim 9/9 configs bit-exact vs this Python sim, 0 deadlocks.
#
# To change the data type: pass a different Ty to get_eva_top (float16 default).

import allo
from allo.ir.types import float16, int16, int32, UInt, AlloType, Stream, float32
import allo.dataflow as df
import numpy as np

# ── array + register-file dimensions ──
M, N = 4, 4                       # PE grid: rows, cols
NSTEP = 8                         # emulated cycles the always-fire fabric is stepped
PROG_CYCLES = 0                   # legacy PC-start offset (router-load mode uses the cfg start bit)
INSTR_SIZE = 0                    # legacy static kernel length (config packets carry it now)
ITER_SIZE  = 1                    # legacy static iteration count (config packets carry it now)
DATADRIVEN = 1                    # 1 = PC STALLS until operands valid (golden instr_gt); 0 = free-run
DRF_DEPTH, IRF_DEPTH = 8, 8       # data / instruction register-file depth
BUF_DEPTH = 2                     # per-input router skid depth (golden router_register = 2-deep)
LANELEN = NSTEP                   # words each perimeter lane streams to/from memory (1 per cycle)
# Memory is split PER SIDE (west/east = M row-lanes, north/south = N col-lanes) into separate
# in_*/out_* buffers. In real EVA a slot's driver+collector share ONE bank (array_memory.sv);
# a single Allo dataflow array can't be both driver-read and collector-written (csynth
# 200-976), so the shared-bank model is DEFERRED.

# ── EVA ISA opcodes (4-bit), from pe_pipeline.sv decode ──
OP_ADD, OP_SUB, OP_MULT, OP_MOV = 0x0, 0x1, 0x2, 0x3
OP_RTR0 = 0x4                     # 0x4..0x7 = router send, dir = opcode[1:0]
OP_GEQ, OP_LT = 0x8, 0x9
OP_CRTR0 = 0xC                    # 0xC..0xF = CONDITIONAL router send (inject iff condition_reg), dir = opcode[1:0]
# systolic send is a WRITEBACK TARGET (dst 0xC..0xF selects the direction), not an opcode

def get_eva_top(Ty: AlloType = float16):
    # ── wire word formats, DERIVED from the data type (the one-arg datatype swap) ──
    DATA_W = Ty.bits                          # payload width (16 for fp16)
    ID_W, MODE_W, ADDR_W, RQ_W = 4, 1, 4, 1   # id, mode, addr, rq field widths

    # router packet = {rq,id,mode,addr,data} packed LSB-first into one UInt.
    # The payload is data-OPAQUE raw bits (fp16 rides the wire as its bit pattern).
    # (Vitis-HLS comparison point: a struct there; Allo packs one UInt instead.)
    D_OFF  = 0                                # data field starts at bit 0
    A_OFF  = D_OFF + DATA_W                   # addr field: remote RF slot to write
    MD_OFF = A_OFF + ADDR_W                   # mode field: 1=program, 0=data
    ID_OFF = MD_OFF + MODE_W                  # id field: destination coordinate on the axis
    RQ_OFF = ID_OFF + ID_W                    # rq/valid bit (top): rq==0 -> word is a bubble
    PKT_W  = RQ_OFF + RQ_W                    # = 26 bits for fp16
    # mask for recording a packet into an int32 rout array: Allo's vhls emission
    # SIGN-extends UInt->int32 stores (the sim zero-extends; same bug class as
    # Allo/bugs/uint_slice_signed_emission.py) -> force zero-extension explicitly
    PMASK  = (1 << PKT_W) - 1 if PKT_W < 32 else 0x7FFFFFFF
    Pkt    = UInt(PKT_W)

    SYS_W  = UInt(1 + DATA_W)                  # bit0 = vld, bits[1:1+DATA_W] = raw data

    @df.region()
    def top(
        # ── SYSTOLIC perimeter memory. One lane per row (w/e) or col (n/s). ──
        in_w: Ty[M, LANELEN], in_e: Ty[M, LANELEN],     # west/east driver data
        in_n: Ty[N, LANELEN], in_s: Ty[N, LANELEN],     # north/south driver data
        out_w: Ty[M, LANELEN], out_e: Ty[M, LANELEN],   # west/east collector data
        out_n: Ty[N, LANELEN], out_s: Ty[N, LANELEN],   # north/south collector data
        # ── ROUTER perimeter memory: each int32 holds one PRE-PACKED Pkt word
        # (the harness packs {rq,id,mode,addr,data}; rq=0 slots are bubbles). ──
        rin_w: int32[M, LANELEN], rin_e: int32[M, LANELEN],
        rin_n: int32[N, LANELEN], rin_s: int32[N, LANELEN],
        rout_w: int32[M, LANELEN], rout_e: int32[M, LANELEN],
        rout_n: int32[N, LANELEN], rout_s: int32[N, LANELEN],
        # ── systolic VALID masks (golden rq bit): a driver injects a real token
        # only where mask==1, else a bubble — idle cycles must not poison the
        # receiving node's hold registers. One mask slot per (lane, cycle). ──
        iv_w: int32[M, LANELEN], iv_e: int32[M, LANELEN],
        iv_n: int32[N, LANELEN], iv_s: int32[N, LANELEN],
    ):
        # ONLY inter-node links are streams; router<->core is LOCAL inside the
        # fused node kernel. Link-index convention for a node (i,j):
        #   eastward  net X_e: my west input = X_e[i,j],   my east output = X_e[i,j+1]
        #   westward  net X_w: my east input = X_w[i,j+1], my west output = X_w[i,j]
        #   southward net X_s: my north input = X_s[i,j],  my south output = X_s[i+1,j]
        #   northward net X_n: my south input = X_n[i+1,j], my north output = X_n[i,j]
        # ── SYSTOLIC network: payload {vld,data} ──
        sys_e: Stream[SYS_W, 2][M, N + 1]
        sys_w: Stream[SYS_W, 2][M, N + 1]
        sys_s: Stream[SYS_W, 2][M + 1, N]
        sys_n: Stream[SYS_W, 2][M + 1, N]
        # ── ROUTER mesh: payload Pkt (data-opaque) ──
        rtr_e: Stream[Pkt, 2][M, N + 1]
        rtr_w: Stream[Pkt, 2][M, N + 1]
        rtr_s: Stream[Pkt, 2][M + 1, N]
        rtr_n: Stream[Pkt, 2][M + 1, N]
        # ── REVERSE credit streams (lossless router): one per forward router
        # link, same geometry, flowing the OPPOSITE way. Carries 0/1 per cycle
        # ("downstream freed a buffer slot"), primed with BUF_DEPTH allowance.
        # Needed because the always-fire model has no non-blocking reads to
        # drop or retry on — without credits a full skid would LOSE packets. ──
        cr_e: Stream[int32, 2][M, N + 1]
        cr_w: Stream[int32, 2][M, N + 1]
        cr_s: Stream[int32, 2][M + 1, N]
        cr_n: Stream[int32, 2][M + 1, N]

        # The node takes NO external arrays — program and data arrive ONLY via
        # router-delivered packets. (A shared program array would be read by all
        # M*N instances -> HLS 200-779; router buffers have a single reader.)
        # Router + PE are FUSED in one kernel: avoids the router<->core stream
        # feedback cycle (crv/csd become plain locals below).
        @df.kernel(mapping=[M, N])
        def node():
            i, j = df.get_pid()
            # ── local register files (per-instance -> single-owner, csynth-legal) ──
            irf: int32[IRF_DEPTH] = 0          # instruction RF (filled by mode=1 packets)
            drf: Ty[DRF_DEPTH] = 0             # data RF (systolic rx + mode=0 packets + writeback)
            drf_full: int32[DRF_DEPTH] = 0     # per-slot FULL bit (meaningful only where dsmask set)
            dsmask: int32 = 0                  # DRF sync mask: which slots act as 1-deep mailboxes

            # ── router->core delivery port (crv_*): plain locals, rewritten each cycle ──
            crv_vld: int32 = 0                 # a packet was delivered to this core this cycle
            crv_data: Ty = 0                   # delivered payload, bitcast to Ty
            crv_addr: int32 = 0                # RF slot the packet writes (packet addr field)
            crv_mode: int32 = 0                # 1 = program (IRF/config), 0 = data (DRF)
            crv_raw:  int32 = 0                # payload as RAW bits (instruction word for IRF)

            # ── core->router inject port (csd_*): csd_pkt is HELD until actually sent ──
            csd_vld: int32 = 0                 # (unused; csd_pkt's rq bit is the valid)
            csd_pkt: Pkt = 0                   # packet the core wants to inject (built in writeback)
            csd_dir: int32 = 0                 # inject direction: 0=N 1=S 2=W 3=E (golden order)
            # ── this node's routing ids (golden per-axis DOR) ──
            row_id: int32 = i                  # matched by packets on the vertical (col) links
            col_id: int32 = j                  # matched by packets on the horizontal (row) links

            # ── REGISTERED outputs: each cycle emits LAST cycle's result, so the loop
            # body computes into regs and the puts need no fresh data. Init = bubble.
            # Faithful: golden router_register / systolic pipeline stages ARE output regs.
            oe_r: Pkt = 0; ow_r: Pkt = 0; on_r: Pkt = 0; os_r: Pkt = 0
            txn_r: SYS_W = 0; txs_r: SYS_W = 0; txw_r: SYS_W = 0; txe_r: SYS_W = 0

            # ── systolic-rx HOLD (golden sync_register): 2-deep per-dir FIFO,
            # write-when-space / read-consumes. dir d: 0=top/N 1=btm/S 2=lft/W 3=rgt/E.
            # 2-deep because e.g. the FFT butterfly reads the SAME dir twice
            # back-to-back (I0/I1 both syslft) — a 1-deep hold would drop one.
            hold_v: Ty[4, 2] = 0; hold_cnt: int32[4] = 0

            # ── lossless-router state. Input d: 0=W 1=E 2=N 3=S; output o: 0=E 1=W 2=S 3=N. ──
            rbuf:  Pkt[4, BUF_DEPTH] = 0       # per-input skid (arrivals that can't leave yet)
            rbcnt: int32[4] = 0                # skid occupancy (head = index 0)
            rcred: int32[4] = 0                # credits per OUTPUT = free slots downstream; send iff > 0

            # ── credit-RETURN regs (registered like data outs). Init = BUF_DEPTH = the
            # PRIME: the initial allowance granted to each upstream neighbor ("you may
            # send me BUF_DEPTH packets before hearing back") — bootstraps the credit
            # loop. Thereafter 0/1 = "I freed a slot on your link this cycle". ──
            cre_r: int32 = BUF_DEPTH; crw_r: int32 = BUF_DEPTH
            crs_r: int32 = BUF_DEPTH; crn_r: int32 = BUF_DEPTH

            # ── config-derived control (golden config_reg_0/1 decoded ON WRITE + fetch FSM) ──
            cfg_isz: int32 = 0                 # instr_size = kernel_length-1 (config_reg_0[10:8])
            cfg_itsz: int32 = 0                # iter_size  = loop count      (config_reg_1[7:0])
            fetch_en: int32 = 0                # 0 = idle (awaiting start bit), 1 = running
            instr_cnt: int32 = 0               # position in the kernel (0..cfg_isz), wraps
            iter_cnt: int32 = 0                # completed kernel loops (batches done)
            condition_reg: int32 = 0           # set by GEQ/LT, gates conditional RTR (0xC..0xF)

            # END-PUT prime (RTL deadlock fix): emit the t=0 outputs BEFORE the
            # loop — the regs hold their init values here, i.e. bubble packets/
            # words and the BUF_DEPTH credit allowance. The in-loop puts sit at
            # the iteration END, so every stream still carries exactly one word
            # per cycle, bit-identical to the old top-put order — but each
            # feedback edge now starts with a token in flight, which is what
            # makes the RTL's reads-before-writes schedule deadlock-free.
            rtr_e[i, j + 1].put(oe_r)
            rtr_w[i, j].put(ow_r)
            rtr_s[i + 1, j].put(os_r)
            rtr_n[i, j].put(on_r)
            sys_e[i, j + 1].put(txe_r)
            sys_w[i, j].put(txw_r)
            sys_s[i + 1, j].put(txs_r)
            sys_n[i, j].put(txn_r)
            cr_e[i, j].put(cre_r)
            cr_w[i, j + 1].put(crw_r)
            cr_s[i, j].put(crs_r)
            cr_n[i + 1, j].put(crn_r)

            # ── per-cycle loop: GET all inputs -> route -> execute -> latch regs -> PUT ──
            for t in range(NSTEP):
                # ROUTER ingress: read ONE packet from each incoming mesh link
                p_w: Pkt = rtr_e[i, j].get()         # arriving from the WEST  (eastward link)
                p_e: Pkt = rtr_w[i, j + 1].get()     # arriving from the EAST  (westward link)
                p_n: Pkt = rtr_s[i, j].get()         # arriving from the NORTH (southward link)
                p_s: Pkt = rtr_n[i + 1, j].get()     # arriving from the SOUTH (northward link)
                # (A) collect returning credits for MY outputs (o: 0=E 1=W 2=S 3=N)
                rcred[0] += cr_e[i, j + 1].get()     # East output freed slots downstream
                rcred[1] += cr_w[i, j].get()         # West
                rcred[2] += cr_s[i + 1, j].get()     # South
                rcred[3] += cr_n[i, j].get()         # North

                # (B) push each VALID arrival into its input skid. Never overflows:
                # an upstream only sent because it held a credit, and a credit
                # existed only because this skid had a free slot.
                fin: Pkt[4] = 0
                fin[0] = p_w; fin[1] = p_e; fin[2] = p_n; fin[3] = p_s
                for d in range(4):
                    if fin[d][RQ_OFF] == 1 and rbcnt[d] < BUF_DEPTH:
                        rbuf[d, rbcnt[d]] = fin[d]; rbcnt[d] += 1

                # (C) route each input HEAD: HIT (deliver to core) if its id field
                # matches my axis coordinate, else it continues STRAIGHT through.
                # Horizontal inputs (W,E) match col_id; vertical (N,S) match row_id.
                hd: Pkt[4] = 0; hvld: int32[4] = 0; hit: int32[4] = 0; axis: int32[4] = 0
                axis[0] = col_id; axis[1] = col_id; axis[2] = row_id; axis[3] = row_id
                for d in range(4):
                    if rbcnt[d] > 0:
                        hd[d] = rbuf[d, 0]; hvld[d] = 1
                        if hd[d][Ty.bits + 5 : Ty.bits + 9] == axis[d]: hit[d] = 1
                # core-receive arbitration: ONE delivered head per cycle, golden
                # static priority S(3) > N(2) > E(1) > W(0). crv_in = winner's input.
                o_crv: Pkt = 0; crv_in: int32 = -1
                if   hit[3] == 1: o_crv = hd[3]; crv_in = 3
                elif hit[2] == 1: o_crv = hd[2]; crv_in = 2
                elif hit[1] == 1: o_crv = hd[1]; crv_in = 1
                elif hit[0] == 1: o_crv = hd[0]; crv_in = 0

                # (D/E) per OUTPUT o (straight-through: input d feeds output o==d;
                # turns are core-mediated only): a pending CORE INJECT wins the
                # port, else the head forwards — either way only if a credit is
                # free. csd_dir is geographic (0=N 1=S 2=W 3=E) but outputs are
                # indexed 0=E 1=W 2=S 3=N, hence idir = 3 - csd_dir.
                o_out: Pkt[4] = 0; pop: int32[4] = 0; inj_done: int32 = 0
                idir: int32 = -1
                if csd_pkt[RQ_OFF] == 1: idir = 3 - csd_dir
                for o in range(4):
                    if rcred[o] > 0:
                        if idir == o:
                            o_out[o] = csd_pkt; rcred[o] -= 1; inj_done = 1
                        elif hvld[o] == 1 and hit[o] == 0:
                            o_out[o] = hd[o]; rcred[o] -= 1; pop[o] = 1
                if crv_in >= 0: pop[crv_in] = 1      # a delivered head also pops (no credit spent)

                # (F) dequeue popped heads (skid shift down) and owe one credit
                # back upstream for every input that freed a slot this cycle.
                ret: int32[4] = 0
                for d in range(4):
                    if pop[d] == 1:
                        for sft in range(BUF_DEPTH - 1):
                            rbuf[d, sft] = rbuf[d, sft + 1]
                        rbcnt[d] -= 1; ret[d] = 1
                cre_r = ret[0]; crw_r = ret[1]; crs_r = ret[2]; crn_r = ret[3]

                # latch this cycle's outputs; a sent inject clears, an unsent one
                # is HELD (csd_pkt keeps its rq bit) and retries next cycle.
                oe_r = o_out[0]; ow_r = o_out[1]; os_r = o_out[2]; on_r = o_out[3]
                if inj_done == 1: csd_pkt = 0

                # unpack the delivered packet into the local core-receive port
                crv_vld = o_crv[RQ_OFF]
                crv_data = o_crv[0 : Ty.bits].bitcast()    # payload bits -> Ty value
                crv_addr = o_crv[Ty.bits : Ty.bits + 4]    # RF slot to write
                crv_mode = o_crv[Ty.bits + 4]              # 1=program, 0=data
                crv_raw  = o_crv[0 : Ty.bits]              # payload kept RAW (IRF writes)

                # ── PE systolic RX: always-fire read of ALL 4 inputs keeps the FIFOs balanced ──
                rx_w: SYS_W = sys_e[i, j].get()       # operand arriving from WEST
                rx_e: SYS_W = sys_w[i, j + 1].get()   # from EAST
                rx_n: SYS_W = sys_s[i, j].get()       # from NORTH
                rx_s: SYS_W = sys_n[i + 1, j].get()   # from SOUTH

                # gather by EVA systolic dir (0=top/N 1=btm/S 2=lft/W 3=rgt/E) and
                # latch each VALID token into that dir's hold FIFO if there is room.
                # NOTE: the systolic net has NO credit back-pressure — a token
                # arriving at a full 2-deep hold is DROPPED (programs schedule
                # around this; do not "fix" it, it is the model's semantics).
                rxv: Ty[4] = 0; rxvld: int32[4] = 0
                rxv[0] = rx_n[1 : 1 + Ty.bits].bitcast(); rxvld[0] = rx_n[0]
                rxv[1] = rx_s[1 : 1 + Ty.bits].bitcast(); rxvld[1] = rx_s[0]
                rxv[2] = rx_w[1 : 1 + Ty.bits].bitcast(); rxvld[2] = rx_w[0]
                rxv[3] = rx_e[1 : 1 + Ty.bits].bitcast(); rxvld[3] = rx_e[0]
                for d in range(4):
                    if rxvld[d] == 1 and hold_cnt[d] < 2:
                        hold_v[d, hold_cnt[d]] = rxv[d]; hold_cnt[d] += 1

                # ── FETCH: config-driven cyclic PC (golden instruction_control).
                # pc = -1 means not executing (idle or all iterations done). ──
                pc: int32 = -1
                if fetch_en == 1: pc = instr_cnt
                instr: int32 = 0
                if pc >= 0: instr = irf[pc]
                # decode: instr = op[3:0] | dst[7:4] | s1[11:8] | s2[15:12]
                op: int32 = instr & 0xF
                dst: int32 = (instr >> 4) & 0xF
                s1: int32 = (instr >> 8) & 0xF
                s2: int32 = (instr >> 12) & 0xF
                # operand read: src 0..7 -> DRF; src 0xC..0xF -> systolic hold[src&3]
                # (oldest slot). Values are read speculatively; grant decides below.
                a: Ty = 0; b: Ty = 0
                if s1 >= 12: a = hold_v[s1 & 3, 0]
                else:        a = drf[s1]
                if s2 >= 12: b = hold_v[s2 & 3, 0]
                else:        b = drf[s2]

                # ── SCOREBOARD: a systolic operand is valid iff its hold FIFO has a
                # token; a DRF SYNC-slot operand (dsmask bit set) is valid iff its
                # full bit is set (read-when-full mailbox — this is what lets e.g.
                # the FFT shuffle's MOV wait for its partner packet with no NOP
                # padding). Plain DRF operands are always valid. ──
                a_vld: int32 = 1; b_vld: int32 = 1
                if s1 >= 12:
                    a_vld = 0
                    if hold_cnt[s1 & 3] > 0: a_vld = 1
                if s2 >= 12:
                    b_vld = 0
                    if hold_cnt[s2 & 3] > 0: b_vld = 1
                if s1 < DRF_DEPTH and ((dsmask >> s1) & 1) == 1:
                    if drf_full[s1] == 0: a_vld = 0
                if s2 < DRF_DEPTH and ((dsmask >> s2) & 1) == 1:
                    if drf_full[s2] == 0: b_vld = 0
                # GRANT (golden instr_gt): binary ops need BOTH operands, MOV/RTR
                # only a. DATADRIVEN=1 -> a missing operand STALLS the PC (held-PC).
                binop: int32 = 0
                if op == OP_ADD or op == OP_SUB or op == OP_MULT or op == OP_GEQ or op == OP_LT: binop = 1
                grant: int32 = 0
                if pc >= 0: grant = 1
                if pc >= 0 and DATADRIVEN == 1 and (a_vld == 0 or (binop == 1 and b_vld == 0)): grant = 0
                # advance the cyclic PC only on grant; wrap at cfg_isz, count
                # iterations, and drop back to idle after the last one.
                if grant == 1:
                    if instr_cnt == cfg_isz:
                        instr_cnt = 0
                        if iter_cnt == cfg_itsz - 1: fetch_en = 0
                        else: iter_cnt += 1
                    else: instr_cnt += 1

                # READ-CONSUMES on grant: a systolic read POPS its hold FIFO
                # (overflow shifts down). If both operands read the SAME dir there
                # is only one token -> pop once (the c2 != c1 guard).
                c1: int32 = -1; c2: int32 = -1
                if grant == 1 and s1 >= 12: c1 = s1 & 3
                if grant == 1 and s2 >= 12: c2 = s2 & 3
                if c1 >= 0:
                    hold_v[c1, 0] = hold_v[c1, 1]; hold_cnt[c1] -= 1
                if c2 >= 0 and c2 != c1:
                    hold_v[c2, 0] = hold_v[c2, 1]; hold_cnt[c2] -= 1

                # same read-consume for DRF sync slots: a granted read EMPTIES the
                # mailbox so the next producer write can land.
                if grant == 1 and s1 < DRF_DEPTH and ((dsmask >> s1) & 1) == 1: drf_full[s1] = 0
                if grant == 1 and s2 < DRF_DEPTH and ((dsmask >> s2) & 1) == 1: drf_full[s2] = 0

                # ── EXECUTE (eva_fpu semantics; GEQ/LT produce +-1.0 in Ty) ──
                res: Ty = 0
                if op == OP_ADD:    res = a + b
                elif op == OP_SUB:  res = a - b
                elif op == OP_MULT: res = a * b
                elif op == OP_GEQ:
                    if a >= b: res = 1.0
                    else:      res = -1.0
                elif op == OP_LT:
                    if a < b:  res = 1.0
                    else:      res = -1.0
                else:               res = a       # MOV and RTR forward operand a

                # result validity rides along so a bubble can't be re-validated
                # into a spurious token further down a forwarding chain.
                res_vld: int32 = a_vld
                if op == OP_ADD or op == OP_SUB or op == OP_MULT or op == OP_GEQ or op == OP_LT:
                    res_vld = a_vld * b_vld
                if grant == 0: res_vld = 0
                # CONDITION FLAG: a granted compare latches it; a later conditional
                # RTR (0xC..0xF) injects only while it is set. Held across cycles.
                if grant == 1 and op == OP_GEQ:
                    condition_reg = 0
                    if a >= b: condition_reg = 1
                if grant == 1 and op == OP_LT:
                    condition_reg = 0
                    if a < b: condition_reg = 1

                # ── WRITEBACK: ONE result -> ONE target (golden single wb/cycle):
                #   op 0x4..0x7 / 0xC..0xF -> router inject (dir = op & 3)
                #   dst 0xC..0xF           -> systolic tx  (dir = dst & 3)
                #   else                   -> DRF[dst]
                tx_n: SYS_W = 0; tx_s: SYS_W = 0
                tx_w: SYS_W = 0; tx_e: SYS_W = 0
                is_rtr: int32 = 0; do_inj: int32 = 0
                if op >= OP_RTR0 and op <= OP_RTR0 + 3: is_rtr = 1; do_inj = 1
                if op >= OP_CRTR0 and op <= OP_CRTR0 + 3:
                    is_rtr = 1
                    if condition_reg == 1: do_inj = 1
                if is_rtr == 1:
                    # HELD-INJECT: build a new packet only if the inject slot is
                    # free (rq==0). A prior inject still waiting for a credit is
                    # NOT overwritten — it keeps retrying (lossless).
                    if do_inj == 1 and csd_pkt[RQ_OFF] == 0:
                        csd_pkt[0 : Ty.bits] = res.bitcast()       # payload = result bits
                        csd_pkt[Ty.bits : Ty.bits + 4] = dst       # remote RF write address
                        csd_pkt[Ty.bits + 5 : Ty.bits + 9] = s2    # destination id (s2 field REUSED)
                        csd_pkt[RQ_OFF] = res_vld
                        csd_dir = op & 3

                elif dst >= 12:
                    # systolic send: dst&3 = 0:top 1:btm 2:lft 3:rgt; bubble if invalid
                    tw: SYS_W = 0
                    tw[0] = res_vld
                    tw[1 : 1 + Ty.bits] = res.bitcast()
                    if   (dst & 3) == 0: tx_n = tw
                    elif (dst & 3) == 1: tx_s = tw
                    elif (dst & 3) == 2: tx_w = tw
                    else:               tx_e = tw

                else:
                    # DRF write, only on a valid result. SYNC slot = write-when-empty
                    # (producer can't clobber an unread value); plain slot = last-wins.
                    if res_vld == 1:
                        if dst < DRF_DEPTH and ((dsmask >> dst) & 1) == 1:

                            if drf_full[dst] == 0:
                                drf[dst] = res;
                                drf_full[dst] = 1
                        else:
                            drf[dst] = res

                # latch systolic tx into the output regs (emitted by the end-puts)
                txn_r = tx_n; txs_r = tx_s; txw_r = tx_w; txe_r = tx_e
                # ── router-delivered packet lands LAST (after compute writeback, so a
                # same-cycle compute write to a sync slot blocks the delivery — no
                # silent overwrite). mode=1: addr 8..15 -> IRF; addr 0 -> config_reg_0
                # (sync mask, instr_size, START bit); addr 1 -> config_reg_1 (iter_size).
                # mode=0: DRF, honoring the sync-slot mailbox. ──
                if crv_vld == 1:
                    if crv_mode == 1:
                        # & 1: signedness-immune (Allo emits UInt slices as SIGNED
                        # intN; bare ==1 compares -1==1 when the top bit is set)
                        if ((crv_addr >> 3) & 1) == 1: irf[crv_addr & 7] = crv_raw
                        elif crv_addr == 0:
                            dsmask = crv_raw & 0xFF
                            cfg_isz = (crv_raw >> 8) & 0x7
                            if ((crv_raw >> 15) & 1) == 1: fetch_en = 1; instr_cnt = 0; iter_cnt = 0
                        elif crv_addr == 1: cfg_itsz = crv_raw & 0xFF
                    elif crv_addr < DRF_DEPTH and ((dsmask >> crv_addr) & 1) == 1:
                        if drf_full[crv_addr] == 0:
                            drf[crv_addr] = crv_data; drf_full[crv_addr] = 1
                    else:
                        drf[crv_addr] = crv_data

                # END-PUT: emit this iteration's results — the same words the
                # old top-put form would have emitted at the NEXT iteration's
                # top, so stream contents are unchanged by the priming.
                rtr_e[i, j + 1].put(oe_r)
                rtr_w[i, j].put(ow_r)
                rtr_s[i + 1, j].put(os_r)
                rtr_n[i, j].put(on_r)
                sys_e[i, j + 1].put(txe_r)
                sys_w[i, j].put(txw_r)
                sys_s[i + 1, j].put(txs_r)
                sys_n[i, j].put(txn_r)
                cr_e[i, j].put(cre_r)
                cr_w[i, j + 1].put(crw_r)
                cr_s[i, j].put(crs_r)
                cr_n[i + 1, j].put(crn_r)

        # ════════ SYSTOLIC perimeter ════════
        # One kernel per side, meta_for-unrolled over its lanes (compile-time
        # constant stream indices) = SINGLE-OWNER of its memory arrays, which is
        # the only csynth-legal sharing pattern. Always-fire: exactly one put
        # (drivers) / one get (collectors) per lane per cycle; a driver emits a
        # real token only where the iv_* mask is 1, else a bubble; past LANELEN
        # everything is bubbles. Drivers need no prime: they have no input to
        # wait on, their put is already the first action.
        @df.kernel(mapping=[1], args=[in_w, iv_w])
        def drv_w(din_w: Ty[M, LANELEN], vd_w: int32[M, LANELEN]):
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    w: SYS_W = 0                                 # default = bubble
                    if t < LANELEN:
                        w[0] = vd_w[r, t]                        # vld from the mask
                        w[1 : 1 + Ty.bits] = din_w[r, t].bitcast()   # fp16 -> raw bits
                    sys_e[r, 0].put(w)                           # west-perimeter inject

        @df.kernel(mapping=[1], args=[in_e, iv_e])
        def drv_e(din_e: Ty[M, LANELEN], vd_e: int32[M, LANELEN]):
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    w: SYS_W = 0
                    if t < LANELEN:
                        w[0] = vd_e[r, t]
                        w[1 : 1 + Ty.bits] = din_e[r, t].bitcast()
                    sys_w[r, N].put(w)                           # east-perimeter inject

        @df.kernel(mapping=[1], args=[in_n, iv_n])
        def drv_n(din_n: Ty[N, LANELEN], vd_n: int32[N, LANELEN]):
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    w: SYS_W = 0
                    if t < LANELEN:
                        w[0] = vd_n[c, t]
                        w[1 : 1 + Ty.bits] = din_n[c, t].bitcast()
                    sys_s[0, c].put(w)                           # north-perimeter inject

        @df.kernel(mapping=[1], args=[in_s, iv_s])
        def drv_s(din_s: Ty[N, LANELEN], vd_s: int32[N, LANELEN]):
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    w: SYS_W = 0
                    if t < LANELEN:
                        w[0] = vd_s[c, t]
                        w[1 : 1 + Ty.bits] = din_s[c, t].bitcast()
                    sys_n[M, c].put(w)                           # south-perimeter inject

        # Collectors: read every cycle (bubbles included — always-fire), append
        # only VALID words to the output lane; k[.] is the per-lane write ptr.
        @df.kernel(mapping=[1], args=[out_w])
        def col_w(dout_w: Ty[M, LANELEN]):
            k: int32[M] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    w: SYS_W = sys_w[r, 0].get()                 # west-perimeter drain
                    if w[0] == 1 and k[r] < LANELEN:
                        dout_w[r, k[r]] = w[1 : 1 + Ty.bits].bitcast()
                        k[r] += 1

        @df.kernel(mapping=[1], args=[out_e])
        def col_e(dout_e: Ty[M, LANELEN]):
            k: int32[M] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    w: SYS_W = sys_e[r, N].get()                 # east-perimeter drain
                    if w[0] == 1 and k[r] < LANELEN:
                        dout_e[r, k[r]] = w[1 : 1 + Ty.bits].bitcast()
                        k[r] += 1

        @df.kernel(mapping=[1], args=[out_n])
        def col_n(dout_n: Ty[N, LANELEN]):
            k: int32[N] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    w: SYS_W = sys_n[0, c].get()                 # north-perimeter drain
                    if w[0] == 1 and k[c] < LANELEN:
                        dout_n[c, k[c]] = w[1 : 1 + Ty.bits].bitcast()
                        k[c] += 1

        @df.kernel(mapping=[1], args=[out_s])
        def col_s(dout_s: Ty[N, LANELEN]):
            k: int32[N] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    w: SYS_W = sys_s[M, c].get()                 # south-perimeter drain
                    if w[0] == 1 and k[c] < LANELEN:
                        dout_s[c, k[c]] = w[1 : 1 + Ty.bits].bitcast()
                        k[c] += 1

        # ════════ ROUTER perimeter ════════
        # Golden EVA has real router_driver/router_collector FSMs (HEAD/BODY/TAIL
        # packet build from config). Here the harness PRE-PACKS each flit into an
        # int32 (rin_*), so a driver only credit-gates and injects. Per lane:
        # sp = source pointer, dcred = credits banked from the edge node. Each
        # cycle: drain the credit stream, then either skip a bubble slot (rq=0,
        # costs nothing), send the flit if a credit is held (HOLD, don't drop,
        # otherwise), or emit a bubble. Always exactly one put per cycle.
        @df.kernel(mapping=[1], args=[rin_w])
        def rdrv_w(rdin_w: int32[M, LANELEN]):
            dcred: int32[M] = 0; sp: int32[M] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    dcred[r] += cr_e[r, 0].get()         # credits from node(r,0) (t=0 = its prime)
                    pw: Pkt = 0                          # default = bubble
                    if sp[r] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_w[r, sp[r]]
                        if cand[RQ_OFF] == 0: sp[r] += 1                          # bubble slot: free skip
                        elif dcred[r] > 0: pw = cand; dcred[r] -= 1; sp[r] += 1   # send, spend a credit
                    rtr_e[r, 0].put(pw)

        @df.kernel(mapping=[1], args=[rin_e])
        def rdrv_e(rdin_e: int32[M, LANELEN]):
            dcred: int32[M] = 0; sp: int32[M] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    dcred[r] += cr_w[r, N].get()         # credits from node(r,N-1)
                    pw: Pkt = 0
                    if sp[r] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_e[r, sp[r]]
                        if cand[RQ_OFF] == 0: sp[r] += 1
                        elif dcred[r] > 0: pw = cand; dcred[r] -= 1; sp[r] += 1
                    rtr_w[r, N].put(pw)

        @df.kernel(mapping=[1], args=[rin_n])
        def rdrv_n(rdin_n: int32[N, LANELEN]):
            dcred: int32[N] = 0; sp: int32[N] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    dcred[c] += cr_s[0, c].get()         # credits from node(0,c)
                    pw: Pkt = 0
                    if sp[c] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_n[c, sp[c]]
                        if cand[RQ_OFF] == 0: sp[c] += 1
                        elif dcred[c] > 0: pw = cand; dcred[c] -= 1; sp[c] += 1
                    rtr_s[0, c].put(pw)

        @df.kernel(mapping=[1], args=[rin_s])
        def rdrv_s(rdin_s: int32[N, LANELEN]):
            dcred: int32[N] = 0; sp: int32[N] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    dcred[c] += cr_n[M, c].get()         # credits from node(M-1,c)
                    pw: Pkt = 0
                    if sp[c] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_s[c, sp[c]]
                        if cand[RQ_OFF] == 0: sp[c] += 1
                        elif dcred[c] > 0: pw = cand; dcred[c] -= 1; sp[c] += 1
                    rtr_n[M, c].put(pw)

        # Router collectors: per cycle, GET one word off the edge link (bubbles
        # too), record a real flit (masked with PMASK — see the sign-extension
        # note at the top) and owe 1 credit back; then PUT the credit. The prime
        # (BUF_DEPTH allowance) goes out BEFORE the loop, and the in-loop put
        # sits AFTER the get — same END-PUT pattern as the node, and the reason
        # the node<->collector credit feedback cannot deadlock in RTL.
        @df.kernel(mapping=[1], args=[rout_w])
        def rclc_w(rdout_w: int32[M, LANELEN]):
            k: int32[M] = 0
            cret: int32[M] = 0
            with allo.meta_for(0, M) as r:
                cret[r] = BUF_DEPTH
                cr_w[r, 0].put(cret[r])      # END-PUT prime: t=0 credit allowance
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    pw: Pkt = rtr_w[r, 0].get()
                    cret[r] = 0                          # default: drained only a bubble
                    if pw[RQ_OFF] == 1:
                        cret[r] = 1                      # real flit drained -> 1 credit back
                        if k[r] < LANELEN:
                            rdout_w[r, k[r]] = pw & PMASK
                            k[r] += 1
                    cr_w[r, 0].put(cret[r])  # END-PUT: credit goes out after the get

        @df.kernel(mapping=[1], args=[rout_e])
        def rclc_e(rdout_e: int32[M, LANELEN]):
            k: int32[M] = 0; cret: int32[M] = 0
            with allo.meta_for(0, M) as r:
                cret[r] = BUF_DEPTH
                cr_e[r, N].put(cret[r])      # END-PUT prime: t=0 credit allowance
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    pw: Pkt = rtr_e[r, N].get()
                    cret[r] = 0
                    if pw[RQ_OFF] == 1:
                        cret[r] = 1
                        if k[r] < LANELEN:
                            rdout_e[r, k[r]] = pw & PMASK
                            k[r] += 1
                    cr_e[r, N].put(cret[r])  # END-PUT: credit goes out after the get

        @df.kernel(mapping=[1], args=[rout_n])
        def rclc_n(rdout_n: int32[N, LANELEN]):
            k: int32[N] = 0; cret: int32[N] = 0
            with allo.meta_for(0, N) as c:
                cret[c] = BUF_DEPTH
                cr_n[0, c].put(cret[c])      # END-PUT prime: t=0 credit allowance
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    pw: Pkt = rtr_n[0, c].get()
                    cret[c] = 0
                    if pw[RQ_OFF] == 1:
                        cret[c] = 1
                        if k[c] < LANELEN:
                            rdout_n[c, k[c]] = pw & PMASK
                            k[c] += 1
                    cr_n[0, c].put(cret[c])  # END-PUT: credit goes out after the get

        @df.kernel(mapping=[1], args=[rout_s])
        def rclc_s(rdout_s: int32[N, LANELEN]):
            k: int32[N] = 0; cret: int32[N] = 0
            with allo.meta_for(0, N) as c:
                cret[c] = BUF_DEPTH
                cr_s[M, c].put(cret[c])      # END-PUT prime: t=0 credit allowance
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    pw: Pkt = rtr_s[M, c].get()
                    cret[c] = 0
                    if pw[RQ_OFF] == 1:
                        cret[c] = 1
                        if k[c] < LANELEN:
                            rdout_s[c, k[c]] = pw & PMASK
                            k[c] += 1
                    cr_s[M, c].put(cret[c])  # END-PUT: credit goes out after the get

    return top

def run_eva(mod, ins, ivs, outs, rins, routs):
    """Invoke a built EVA module with args in the module's TRUE (discovery) order.

    prog/win/win1/dsync are GONE -> program + data are loaded via router packets in rins (rin_s).
    Each systolic driver declares args=[in_X, iv_X], so Allo discovers input+mask as a PAIR:
        (in_w,iv_w), (in_e,iv_e), (in_n,iv_n), (in_s,iv_s),
        out_w, out_e, out_n, out_s, rin_w..rin_s, rout_w..rout_s
      ins  = [in_w, in_e, in_n, in_s]      ivs  = [iv_w, iv_e, iv_n, iv_s]   (int32 masks)
      outs = [out_w, out_e, out_n, out_s]  rins/routs = [*_w, *_e, *_n, *_s] (int32 packets)
    """
    iw, ie, in_, is_ = ins
    vw, ve, vn, vs = ivs
    mod(iw, vw, ie, ve, in_, vn, is_, vs, *outs, *rins, *routs)

def get_scheduled_eva(Ty: AlloType = float16, pipeline_node=True, partition_rf=True):
    # Schedule = the two knobs the Vitis hand version also uses:
    #  - partition the per-node register files / skids / holds into REGISTERS
    #    (otherwise the drf store->load recurrence serializes the node loop),
    #  - request II=1 on every node instance's cycle loop (`t`).
    # NOTE: irf is NOT in the partition list -> it maps to LUTRAM and its read
    # sits on the routed critical path (known lever: partitioning irf is worth
    # 1 II / removes the RAMS32 hop).
    s = df.customize(get_eva_top(Ty))
    if partition_rf:
        for i in range(M):
            for j in range(N):
                for buf in ("drf", "drf_full", "rbuf", "rbcnt", "rcred", "hold_v", "hold_cnt"):
                    s.partition(f"node_{i}_{j}:{buf}")
    if pipeline_node:
        for i in range(M):
            for j in range(N):
                s.pipeline(f"node_{i}_{j}:t", initiation_interval=1)
    return s

if __name__ == "__main__":

    import os
    P = os.path.join(os.path.dirname(os.path.abspath(__file__)), "hls_gen_dd_pipe_float32")
    s = get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)
    s.build(target="vhls", mode="csyn", project=P)
    print("generated HLS project at", P)
