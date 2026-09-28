# ============================================================
# PARKED 2026-07-10 (status): router NB conversion LOGIC-PROVEN
# (router test passed on a run) but bounded-loop+NB = NONDETER-
# MINISTIC race in Allo's dataflow sim. To resume: (1) free-
# running loop + per-kernel completion (collector spins to K
# results; node done-signal); (2) systolic ALSO NB (try_get +
# PE data-driven stall), NOT blocking+credits (that fights NB —
# see eva_sb_nb_credittry.bak); (3) RTL needs vhls printer ext
# for StreamEmpty/Full/TryGet/TryPut. Run: allo_sup, host brg-
# zhang-xcel, LLVM_BUILD_DIR=/work/shared/common/llvm-project-
# main/build. See memory 2026-07-10 for full context.
# ============================================================
# eva_sb_nb.py — FULL NON-BLOCKING EVA (router AND systolic NB).
# eva_sb_nb.py — EVENT-DRIVEN scoreboard EVA (NON-BLOCKING reads, NO bubbles).
# Departs from the always-fire/bubble model of every other chip here: instead
# of a blocking get on every link every cycle, a link is read ONLY when it has
# a word (try_get / empty()), and a sender emits ONLY real words (guarded by
# full()/try_put) — golden EVA's rq/gt elasticity. Consequences:
#   * router + systolic backpressure = the FIFO itself (full()) -> LOSSLESS
#     with NO credit planes and NO priming (the syscredit machinery vanishes).
#   * no read-before-write deadlock (NB reads never block on empty).
#   * loop is free-running (bounded transaction count), not for t in NSTEP.
# ⚠ REQUIRES the supervisor Allo branch (/home/zsh9/allo_sup): try_get/try_put/
#   empty/full live only there. ⚠ SIM-ONLY: the vhls HLS printer does NOT emit
#   StreamEmpty/Full/nb ops yet -> csynth/cosim need a printer extension first
#   (expressiveness datapoint next to bind_op / s.dependence).
# Staged rebuild: (1) router plane NB [this step], (2) systolic plane NB,
#   (3) drop credit/prime scaffolding, (4) free-running loop.
# Base: eva_sb.py (always-fire scoreboard). To change data type: change Ty.

import allo
from allo.ir.types import float16, int16, int32, UInt, AlloType, Stream, float32
import allo.dataflow as df
import numpy as np

M, N = 1,1
NSTEP = 10
PROG_CYCLES = 0
INSTR_SIZE = 0
ITER_SIZE  = 1
DATADRIVEN = 1
DRF_DEPTH, IRF_DEPTH = 8, 8
BUF_DEPTH = 2
# SCOREBOARD (mirrors vitis_bubble_scoreboard/eva_node.h): issue-to-retire
# depth = fp16 core latency (4) + 1; result ring > depth so a slot is never
# rewritten while in flight. NOTE: the enabling DEPENDENCE-inter-false pragma
# has NO Allo primitive - II gain on 2023.2 is the experiment here.
SB_DEPTH, RESQ_DEPTH = 5, 8
# OPTION-A knobs (credit-RTT fix for II=1 RTL, see bubble_model 07-05 night):
# defaults = the T=1/D=2 config validated by the replay suite; the II=1 RTL
# schedule needs ~6 tokens in flight (read-to-write span of the depth-6
# pipeline), so gen_kernel.py overrides these to 6/8 for the cosim kernel.
PRIME_TOKENS = 1   # initial tokens per stream (1 = plain END-PUT prime)
STREAM_DEPTH = 8   # link FIFO depth (was 2; deepened for NB elastic flow)
LANELEN = NSTEP
# Memory split per side into separate in_*/out_* buffers; the shared driver+collector bank
# (real EVA array_memory.sv) is DEFERRED — one Allo array can't be both read & written (csynth 200-976).

OP_ADD, OP_SUB, OP_MULT, OP_MOV = 0x0, 0x1, 0x2, 0x3
OP_RTR0 = 0x4                     # 0x4..0x7 = router send, dir = opcode[1:0]
OP_GEQ, OP_LT = 0x8, 0x9
OP_CRTR0 = 0xC                    # 0xC..0xF = CONDITIONAL router send (inject iff condition_reg), dir = opcode[1:0]

def get_eva_top(Ty: AlloType = float16):
    DATA_W = Ty.bits
    ID_W, MODE_W, ADDR_W, RQ_W = 4, 1, 4, 1

    # router packet = {rq,id,mode,addr,data} packed LSB-first into one UInt (data-OPAQUE, raw bits)
    D_OFF  = 0
    A_OFF  = D_OFF + DATA_W
    MD_OFF = A_OFF + ADDR_W
    ID_OFF = MD_OFF + MODE_W
    RQ_OFF = ID_OFF + ID_W
    PKT_W  = RQ_OFF + RQ_W
    # mask for recording a packet into an int32 rout array: Allo's vhls
    # emission SIGN-extends UInt->int32 stores (sim zero-extends; same bug
    # class as Allo/bugs/uint_slice_signed_emission.py) -> force zero-ext
    PMASK  = (1 << PKT_W) - 1 if PKT_W < 32 else 0x7FFFFFFF
    Pkt    = UInt(PKT_W)

    SYS_W  = UInt(1 + DATA_W)                  # bit0 = vld, bits[1:1+DATA_W] = raw data

    @df.region()
    def top(
        in_w: Ty[M, LANELEN], in_e: Ty[M, LANELEN],
        in_n: Ty[N, LANELEN], in_s: Ty[N, LANELEN],
        out_w: Ty[M, LANELEN], out_e: Ty[M, LANELEN],
        out_n: Ty[N, LANELEN], out_s: Ty[N, LANELEN],
        rin_w: int32[M, LANELEN], rin_e: int32[M, LANELEN],
        rin_n: int32[N, LANELEN], rin_s: int32[N, LANELEN],
        rout_w: int32[M, LANELEN], rout_e: int32[M, LANELEN],
        rout_n: int32[N, LANELEN], rout_s: int32[N, LANELEN],
        iv_w: int32[M, LANELEN], iv_e: int32[M, LANELEN],
        iv_n: int32[N, LANELEN], iv_s: int32[N, LANELEN],
    ):
        sys_e: Stream[SYS_W, STREAM_DEPTH][M, N + 1]
        sys_w: Stream[SYS_W, STREAM_DEPTH][M, N + 1]
        sys_s: Stream[SYS_W, STREAM_DEPTH][M + 1, N]
        sys_n: Stream[SYS_W, STREAM_DEPTH][M + 1, N]
        rtr_e: Stream[Pkt, STREAM_DEPTH][M, N + 1]
        rtr_w: Stream[Pkt, STREAM_DEPTH][M, N + 1]
        rtr_s: Stream[Pkt, STREAM_DEPTH][M + 1, N]
        rtr_n: Stream[Pkt, STREAM_DEPTH][M + 1, N]

        @df.kernel(mapping=[M, N])
        def node():
            i, j = df.get_pid()
            irf: int32[IRF_DEPTH] = 0
            drf: Ty[DRF_DEPTH] = 0
            drf_full: int32[DRF_DEPTH] = 0
            dsmask: int32 = 0
            
            crv_vld: int32 = 0
            crv_data: Ty = 0
            crv_addr: int32 = 0
            crv_mode: int32 = 0
            crv_raw:  int32 = 0
            
            csd_vld: int32 = 0
            csd_pkt: Pkt = 0
            csd_dir: int32 = 0
            row_id: int32 = i
            col_id: int32 = j

            txn_r: SYS_W = 0; txs_r: SYS_W = 0; txw_r: SYS_W = 0; txe_r: SYS_W = 0
            
            # NARROW COUNTERS (2026-07-07): routed CP = hold_cnt(int32, reg[31]!)
            # -> operand-vld -> grant -> consume -> hold_cnt', 22 logic levels
            # @186MHz. These regs are protocol-bounded but Vitis can't prove it
            # -> the narrow declaration asserts it; values never leave the
            # range, so sim + RTL behavior are unchanged.
            hold_v: Ty[4, 2] = 0; hold_cnt: UInt(8)[4] = 0
            crv_ever: int32 = 0; fe_ever: int32 = 0   # DEBUG probes
            
            rbuf:  Pkt[4, BUF_DEPTH] = 0
            rbcnt: UInt(8)[4] = 0

            cfg_isz: int32 = 0             # stays int32: RHS-only, and
            cfg_itsz: int32 = 0            # `cfg_itsz - 1` must be -1 at itsz=0
            fetch_en: UInt(8) = 0
            instr_cnt: UInt(8) = 0         # 0..cfg_isz <= 7
            iter_cnt: UInt(8) = 0          # 0..cfg_itsz-1 <= 254
            condition_reg: UInt(8) = 0

            # scoreboard: sb_* = parallel metadata arrays (no structs in
            # Allo), slot 0 retires this cycle; resq/cmpq = result rings
            sb_v: UInt(8)[SB_DEPTH] = 0;  sb_dst: UInt(8)[SB_DEPTH] = 0
            sb_cmp: UInt(8)[SB_DEPTH] = 0; sb_rtr: UInt(8)[SB_DEPTH] = 0
            sb_inj: UInt(8)[SB_DEPTH] = 0; sb_dir: UInt(8)[SB_DEPTH] = 0
            sb_id: UInt(8)[SB_DEPTH] = 0; sb_rvld: UInt(8)[SB_DEPTH] = 0
            sb_ix: UInt(8)[SB_DEPTH] = 0   # resq index, 0..RESQ_DEPTH-1
            resq: Ty[RESQ_DEPTH] = 0
            cmpq: UInt(8)[RESQ_DEPTH] = 0
            resq_wr: UInt(8) = 0           # ring ptr, masked &(RESQ_DEPTH-1)

            # OPTION-A extra prime: (PRIME_TOKENS-1) NEUTRAL leading tokens
            # per output (0-pkt / 0-word / 0-CREDIT — never re-put the reg
            # values: BUF_DEPTH credits twice = silent packet drops). The
            # whole fabric just sees T-1 no-op cycles first. T=1 -> no code.
            # SYSTOLIC-NB: no bubbles, no priming. Links carry ONLY real
            # tokens; try_get/try_put give backpressure. Router plane already NB.

            for t in range(NSTEP):
                # ROUTER INGRESS — NON-BLOCKING: read a packet only when the
                # link has one (no bubble consumed); no credit plane.
                # LOSSLESS ingress: pull a packet ONLY when its buffer has room,
                # else leave it in the link (upstream egress holds/retries).
                # Consuming-then-dropping when full loses program packets (e.g.
                # the config packet that sets fetch_en) -> PE never starts.
                p_w: Pkt = 0; p_e: Pkt = 0; p_n: Pkt = 0; p_s: Pkt = 0
                if rbcnt[0] < BUF_DEPTH:
                    gw, okw = rtr_e[i, j].try_get()
                    if okw: p_w = gw
                if rbcnt[1] < BUF_DEPTH:
                    ge, oke = rtr_w[i, j + 1].try_get()
                    if oke: p_e = ge
                if rbcnt[2] < BUF_DEPTH:
                    gn, okn = rtr_s[i, j].try_get()
                    if okn: p_n = gn
                if rbcnt[3] < BUF_DEPTH:
                    gs, oks = rtr_n[i + 1, j].try_get()
                    if oks: p_s = gs

                fin: Pkt[4] = 0
                fin[0] = p_w; fin[1] = p_e; fin[2] = p_n; fin[3] = p_s
                for d in range(4):
                    if fin[d][RQ_OFF] == 1 and rbcnt[d] < BUF_DEPTH:
                        rbuf[d, rbcnt[d]] = fin[d]; rbcnt[d] += 1
                        
                hd: Pkt[4] = 0; hvld: int32[4] = 0; hit: int32[4] = 0; axis: int32[4] = 0
                axis[0] = col_id; axis[1] = col_id; axis[2] = row_id; axis[3] = row_id
                for d in range(4):
                    if rbcnt[d] > 0:
                        hd[d] = rbuf[d, 0]; hvld[d] = 1
                        if hd[d][Ty.bits + 5 : Ty.bits + 9] == axis[d]: hit[d] = 1
                o_crv: Pkt = 0; crv_in: int32 = -1
                if   hit[3] == 1: o_crv = hd[3]; crv_in = 3
                elif hit[2] == 1: o_crv = hd[2]; crv_in = 2
                elif hit[1] == 1: o_crv = hd[1]; crv_in = 1
                elif hit[0] == 1: o_crv = hd[0]; crv_in = 0
                
                # ROUTER EGRESS — NON-BLOCKING try_put per output; success
                # (FIFO not full) IS the flow control, no credits. Inject beats
                # through-traffic (o: 0=E,1=W,2=S,3=N); a failed put = hold.
                pop: int32[4] = 0; inj_done: int32 = 0
                idir: int32 = -1
                if csd_pkt[RQ_OFF] == 1: idir = 3 - csd_dir
                if idir == 0:
                    if rtr_e[i, j + 1].try_put(csd_pkt): inj_done = 1
                elif hvld[0] == 1 and hit[0] == 0:
                    if rtr_e[i, j + 1].try_put(hd[0]): pop[0] = 1
                if idir == 1:
                    if rtr_w[i, j].try_put(csd_pkt): inj_done = 1
                elif hvld[1] == 1 and hit[1] == 0:
                    if rtr_w[i, j].try_put(hd[1]): pop[1] = 1
                if idir == 2:
                    if rtr_s[i + 1, j].try_put(csd_pkt): inj_done = 1
                elif hvld[2] == 1 and hit[2] == 0:
                    if rtr_s[i + 1, j].try_put(hd[2]): pop[2] = 1
                if idir == 3:
                    if rtr_n[i, j].try_put(csd_pkt): inj_done = 1
                elif hvld[3] == 1 and hit[3] == 0:
                    if rtr_n[i, j].try_put(hd[3]): pop[3] = 1
                if crv_in >= 0: pop[crv_in] = 1

                for d in range(4):
                    if pop[d] == 1:
                        for sft in range(BUF_DEPTH - 1):
                            rbuf[d, sft] = rbuf[d, sft + 1]
                        rbcnt[d] -= 1
                if inj_done == 1: csd_pkt = 0
                
                crv_vld = o_crv[RQ_OFF]
                if crv_vld == 1: crv_ever = 1        # DEBUG: any router pkt delivered here
                crv_data = o_crv[0 : Ty.bits].bitcast()
                crv_addr = o_crv[Ty.bits : Ty.bits + 4]
                crv_mode = o_crv[Ty.bits + 4]
                crv_raw  = o_crv[0 : Ty.bits]

                # SYSTOLIC-NB RX: pull a token only when hold_v has room, so
                # an unconsumed token stays in the FIFO -> backpressure, no drop.
                # d: 0=N,1=S,2=W,3=E (same source links as the old blocking gets)
                rxv: Ty[4] = 0; rxvld: int32[4] = 0
                if hold_cnt[0] < 2:
                    sgn, sqn = sys_s[i, j].try_get()
                    if sqn == 1: rxv[0] = sgn[1 : 1 + Ty.bits].bitcast(); rxvld[0] = 1
                if hold_cnt[1] < 2:
                    sgs, sqs = sys_n[i + 1, j].try_get()
                    if sqs == 1: rxv[1] = sgs[1 : 1 + Ty.bits].bitcast(); rxvld[1] = 1
                if hold_cnt[2] < 2:
                    sgw, sqw = sys_e[i, j].try_get()
                    if sqw == 1: rxv[2] = sgw[1 : 1 + Ty.bits].bitcast(); rxvld[2] = 1
                if hold_cnt[3] < 2:
                    sge, sqe = sys_w[i, j + 1].try_get()
                    if sqe == 1: rxv[3] = sge[1 : 1 + Ty.bits].bitcast(); rxvld[3] = 1
                for d in range(4):
                    if rxvld[d] == 1:
                        hold_v[d, hold_cnt[d]] = rxv[d]; hold_cnt[d] += 1
                   
                # (4b) RETIRE sb[0] (issued SB_DEPTH cycles ago) BEFORE fetch;
                # all three dispatch paths moved here, fed from the ring
                tx_n: SYS_W = 0; tx_s: SYS_W = 0
                tx_w: SYS_W = 0; tx_e: SYS_W = 0
                if sb_v[0] == 1:
                    wb: Ty = resq[sb_ix[0]]
                    if sb_cmp[0] == 1: condition_reg = cmpq[sb_ix[0]]
                    if sb_rtr[0] == 1:
                        if sb_inj[0] == 1 and csd_pkt[RQ_OFF] == 0:
                            csd_pkt[0 : Ty.bits] = wb.bitcast()
                            csd_pkt[Ty.bits : Ty.bits + 4] = sb_dst[0]
                            csd_pkt[Ty.bits + 5 : Ty.bits + 9] = sb_id[0]
                            csd_pkt[RQ_OFF] = sb_rvld[0]
                            csd_dir = sb_dir[0]
                    elif sb_dst[0] >= 12:
                        tw0: SYS_W = 0
                        tw0[0] = sb_rvld[0]
                        tw0[1 : 1 + Ty.bits] = wb.bitcast()
                        if   (sb_dst[0] & 3) == 0: tx_n = tw0
                        elif (sb_dst[0] & 3) == 1: tx_s = tw0
                        elif (sb_dst[0] & 3) == 2: tx_w = tw0
                        else:                      tx_e = tw0
                    else:
                        if sb_rvld[0] == 1:
                            if sb_dst[0] < DRF_DEPTH and ((dsmask >> sb_dst[0]) & 1) == 1:
                                if drf_full[sb_dst[0]] == 0:
                                    drf[sb_dst[0]] = wb
                                    drf_full[sb_dst[0]] = 1
                            else:
                                drf[sb_dst[0] & 7] = wb

                pc: int32 = -1
                if fetch_en == 1: pc = instr_cnt
                if fetch_en == 1: fe_ever = 1        # DEBUG: this node started fetching
                instr: int32 = 0
                if pc >= 0: instr = irf[pc]
                op: int32 = instr & 0xF
                dst: int32 = (instr >> 4) & 0xF
                s1: int32 = (instr >> 8) & 0xF
                s2: int32 = (instr >> 12) & 0xF
                a: Ty = 0; b: Ty = 0
                if s1 >= 12: a = hold_v[s1 & 3, 0]
                else:        a = drf[s1]
                if s2 >= 12: b = hold_v[s2 & 3, 0]
                else:        b = drf[s2]
                
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
                binop: int32 = 0
                if op == OP_ADD or op == OP_SUB or op == OP_MULT or op == OP_GEQ or op == OP_LT: binop = 1
                # RAW scan over in-flight sb[1..] (sb[0] retired above ->
                # forwarded); cmp_busy gates CRTR until condition_reg final
                raw: int32 = 0; cmp_busy: int32 = 0
                for k in range(SB_DEPTH - 1):
                    if sb_v[k + 1] == 1 and sb_rtr[k + 1] == 0 and sb_dst[k + 1] < 12:
                        if s1 < 12 and (sb_dst[k + 1] & 7) == (s1 & 7): raw = 1
                        if binop == 1 and s2 < 12 and (sb_dst[k + 1] & 7) == (s2 & 7): raw = 1
                    if sb_v[k + 1] == 1 and sb_cmp[k + 1] == 1: cmp_busy = 1
                is_cond: int32 = 0
                if op >= OP_CRTR0 and op <= OP_CRTR0 + 3: is_cond = 1

                grant: int32 = 0
                if pc >= 0: grant = 1
                if pc >= 0 and DATADRIVEN == 1 and (a_vld == 0 or (binop == 1 and b_vld == 0)): grant = 0
                if pc >= 0 and (raw == 1 or (is_cond == 1 and cmp_busy == 1)): grant = 0
                if grant == 1:
                    if instr_cnt == cfg_isz:
                        instr_cnt = 0
                        if iter_cnt == cfg_itsz - 1: fetch_en = 0
                        else: iter_cnt += 1
                    else: instr_cnt += 1
                    
                c1: int32 = -1; c2: int32 = -1
                if grant == 1 and s1 >= 12: c1 = s1 & 3
                if grant == 1 and s2 >= 12: c2 = s2 & 3
                if c1 >= 0:
                    hold_v[c1, 0] = hold_v[c1, 1]; hold_cnt[c1] -= 1
                if c2 >= 0 and c2 != c1:
                    hold_v[c2, 0] = hold_v[c2, 1]; hold_cnt[c2] -= 1
                    
                if grant == 1 and s1 < DRF_DEPTH and ((dsmask >> s1) & 1) == 1: drf_full[s1] = 0
                if grant == 1 and s2 < DRF_DEPTH and ((dsmask >> s2) & 1) == 1: drf_full[s2] = 0

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
                else:               res = a
                
                res_vld: int32 = a_vld
                if op == OP_ADD or op == OP_SUB or op == OP_MULT or op == OP_GEQ or op == OP_LT:
                    res_vld = a_vld * b_vld
                if grant == 0: res_vld = 0
                # ISSUE: result -> ring, metadata -> sb tail; dispatch
                # happens at retire (4b). CRTR reads condition_reg HERE -
                # final, because cmp_busy held the PC until compares retired.
                is_rtr: int32 = 0
                if op >= OP_RTR0 and op <= OP_RTR0 + 3: is_rtr = 1
                # shift the scoreboard down; tail defaults to a bubble
                for k in range(SB_DEPTH - 1):
                    sb_v[k] = sb_v[k + 1];     sb_dst[k] = sb_dst[k + 1]
                    sb_cmp[k] = sb_cmp[k + 1]; sb_rtr[k] = sb_rtr[k + 1]
                    sb_inj[k] = sb_inj[k + 1]; sb_dir[k] = sb_dir[k + 1]
                    sb_id[k] = sb_id[k + 1];   sb_rvld[k] = sb_rvld[k + 1]
                    sb_ix[k] = sb_ix[k + 1]
                sb_v[SB_DEPTH - 1] = 0
                if grant == 1:
                    resq[resq_wr] = res
                    cq: int32 = 0
                    if op == OP_GEQ:
                        if a >= b: cq = 1
                    if op == OP_LT:
                        if a < b: cq = 1
                    cmpq[resq_wr] = cq
                    sb_v[SB_DEPTH - 1] = 1
                    sb_dst[SB_DEPTH - 1] = dst
                    sb_ix[SB_DEPTH - 1] = resq_wr
                    sb_cmp[SB_DEPTH - 1] = 0
                    if op == OP_GEQ or op == OP_LT: sb_cmp[SB_DEPTH - 1] = 1
                    rtrf: int32 = is_rtr
                    if is_cond == 1: rtrf = 1
                    sb_rtr[SB_DEPTH - 1] = rtrf
                    inj: int32 = is_rtr
                    if is_cond == 1 and condition_reg == 1: inj = 1
                    sb_inj[SB_DEPTH - 1] = inj
                    sb_dir[SB_DEPTH - 1] = op & 3
                    sb_id[SB_DEPTH - 1] = s2
                    sb_rvld[SB_DEPTH - 1] = res_vld
                    resq_wr = (resq_wr + 1) & (RESQ_DEPTH - 1)

                txn_r = tx_n; txs_r = tx_s; txw_r = tx_w; txe_r = tx_e
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

                # END-PUT prime: the 12 puts, moved verbatim from the loop
                # top — regs now hold this iteration's results, i.e. exactly
                # what the old scheme emitted at the NEXT iteration's top
                # SYSTOLIC-NB TX: BLOCKING put of ONLY real words (pe_core style).
                # The write backpressure throttles the PE to the downstream rate;
                # NB reads keep every link draining, so blocking-write + NB-read
                # is deadlock-free AND keeps the elastic network balanced.
                if txe_r[0] == 1: sys_e[i, j + 1].put(txe_r)
                if txw_r[0] == 1: sys_w[i, j].put(txw_r)
                if txs_r[0] == 1: sys_s[i + 1, j].put(txs_r)
                if txn_r[0] == 1: sys_n[i, j].put(txn_r)

        @df.kernel(mapping=[1], args=[in_w, iv_w])
        def drv_w(din_w: Ty[M, LANELEN], vd_w: int32[M, LANELEN]):
            # SYSTOLIC-NB driver: walk sp through the input, deliver each REAL
            # word IN ORDER, advancing ONLY on try_put success -> retry until
            # accepted (NO drop). Invalid slots skipped. Flooded seed: excess
            # just isn't delivered (redundant); try_put is NB so never blocks.
            sp_w: int32[M] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    if sp_w[r] < LANELEN:
                        if vd_w[r, sp_w[r]] == 0:
                            sp_w[r] += 1
                        else:
                            w: SYS_W = 0
                            w[0] = 1
                            w[1 : 1 + Ty.bits] = din_w[r, sp_w[r]].bitcast()
                            if sys_e[r, 0].try_put(w):
                                sp_w[r] += 1

        @df.kernel(mapping=[1], args=[in_e, iv_e])
        def drv_e(din_e: Ty[M, LANELEN], vd_e: int32[M, LANELEN]):
            # SYSTOLIC-NB driver: walk sp through the input, deliver each REAL
            # word IN ORDER, advancing ONLY on try_put success -> retry until
            # accepted (NO drop). Invalid slots skipped. Flooded seed: excess
            # just isn't delivered (redundant); try_put is NB so never blocks.
            sp_e: int32[M] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    if sp_e[r] < LANELEN:
                        if vd_e[r, sp_e[r]] == 0:
                            sp_e[r] += 1
                        else:
                            w: SYS_W = 0
                            w[0] = 1
                            w[1 : 1 + Ty.bits] = din_e[r, sp_e[r]].bitcast()
                            if sys_w[r, N].try_put(w):
                                sp_e[r] += 1

        @df.kernel(mapping=[1], args=[in_n, iv_n])
        def drv_n(din_n: Ty[N, LANELEN], vd_n: int32[N, LANELEN]):
            # SYSTOLIC-NB driver: walk sp through the input, deliver each REAL
            # word IN ORDER, advancing ONLY on try_put success -> retry until
            # accepted (NO drop). Invalid slots skipped. Flooded seed: excess
            # just isn't delivered (redundant); try_put is NB so never blocks.
            sp_n: int32[N] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    if sp_n[c] < LANELEN:
                        if vd_n[c, sp_n[c]] == 0:
                            sp_n[c] += 1
                        else:
                            w: SYS_W = 0
                            w[0] = 1
                            w[1 : 1 + Ty.bits] = din_n[c, sp_n[c]].bitcast()
                            if sys_s[0, c].try_put(w):
                                sp_n[c] += 1

        @df.kernel(mapping=[1], args=[in_s, iv_s])
        def drv_s(din_s: Ty[N, LANELEN], vd_s: int32[N, LANELEN]):
            # SYSTOLIC-NB driver: walk sp through the input, deliver each REAL
            # word IN ORDER, advancing ONLY on try_put success -> retry until
            # accepted (NO drop). Invalid slots skipped. Flooded seed: excess
            # just isn't delivered (redundant); try_put is NB so never blocks.
            sp_s: int32[N] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    if sp_s[c] < LANELEN:
                        if vd_s[c, sp_s[c]] == 0:
                            sp_s[c] += 1
                        else:
                            w: SYS_W = 0
                            w[0] = 1
                            w[1 : 1 + Ty.bits] = din_s[c, sp_s[c]].bitcast()
                            if sys_n[M, c].try_put(w):
                                sp_s[c] += 1

        @df.kernel(mapping=[1], args=[out_w])
        def col_w(dout_w: Ty[M, LANELEN]):
            # SYSTOLIC-NB collector: try_get, never block on sparse NB output.
            k: int32[M] = 0
            seen: int32[M] = 0                       # DEBUG: real tokens on this edge
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    cwv, cwk = sys_w[r, 0].try_get()
                    if cwk == 1:
                        seen[r] += 1
                        if k[r] < LANELEN - 1:
                            dout_w[r, k[r]] = cwv[1 : 1 + Ty.bits].bitcast()
                            k[r] += 1
            with allo.meta_for(0, M) as r:
                dout_w[r, LANELEN - 1] = seen[r]   # DEBUG count in last slot

        @df.kernel(mapping=[1], args=[out_e])
        def col_e(dout_e: Ty[M, LANELEN]):
            # SYSTOLIC-NB collector: try_get, never block on sparse NB output.
            # BLOCKING: wait for the activation on each row -> keeps the node's
            # blocking east-TX from stalling (matched producer/consumer counts).
            with allo.meta_for(0, M) as r:
                v: SYS_W = sys_e[r, N].get()
                dout_e[r, 0] = v[1 : 1 + Ty.bits].bitcast()

        @df.kernel(mapping=[1], args=[out_n])
        def col_n(dout_n: Ty[N, LANELEN]):
            # SYSTOLIC-NB collector: try_get, never block on sparse NB output.
            k: int32[N] = 0
            seen: int32[N] = 0                       # DEBUG: real tokens on this edge
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    cnv, cnk = sys_n[0, c].try_get()
                    if cnk == 1:
                        seen[c] += 1
                        if k[c] < LANELEN - 1:
                            dout_n[c, k[c]] = cnv[1 : 1 + Ty.bits].bitcast()
                            k[c] += 1
            with allo.meta_for(0, N) as c:
                dout_n[c, LANELEN - 1] = seen[c]   # DEBUG count in last slot

        @df.kernel(mapping=[1], args=[out_s])
        def col_s(dout_s: Ty[N, LANELEN]):
            # SYSTOLIC-NB collector: try_get, never block on sparse NB output.
            # BLOCKING collector: wait for the (B=1) result on each column. Paces
            # to the node -> cannot exit before the result exists (fixes the
            # NOSCHED rate-mismatch). Deadlocks informatively if one never comes.
            with allo.meta_for(0, N) as c:
                v: SYS_W = sys_s[M, c].get()
                dout_s[c, 0] = v[1 : 1 + Ty.bits].bitcast()

        @df.kernel(mapping=[1], args=[rin_w])
        def rdrv_w(rdin_w: int32[M, LANELEN]):
            sp: int32[M] = 0                  # NB driver: no credits/prime
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    if sp[r] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_w[r, sp[r]]
                        if cand[RQ_OFF] == 0:
                            sp[r] += 1                       # bubble slot: skip
                        elif rtr_e[r, 0].try_put(cand):
                            sp[r] += 1                       # sent (FIFO room)

        @df.kernel(mapping=[1], args=[rin_e])
        def rdrv_e(rdin_e: int32[M, LANELEN]):
            sp: int32[M] = 0                  # NB driver: no credits/prime
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    if sp[r] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_e[r, sp[r]]
                        if cand[RQ_OFF] == 0:
                            sp[r] += 1                       # bubble slot: skip
                        elif rtr_w[r, N].try_put(cand):
                            sp[r] += 1                       # sent (FIFO room)

        @df.kernel(mapping=[1], args=[rin_n])
        def rdrv_n(rdin_n: int32[N, LANELEN]):
            sp: int32[N] = 0                  # NB driver: no credits/prime
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    if sp[c] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_n[c, sp[c]]
                        if cand[RQ_OFF] == 0:
                            sp[c] += 1                       # bubble slot: skip
                        elif rtr_s[0, c].try_put(cand):
                            sp[c] += 1                       # sent (FIFO room)

        @df.kernel(mapping=[1], args=[rin_s])
        def rdrv_s(rdin_s: int32[N, LANELEN]):
            sp: int32[N] = 0                  # NB driver: no credits/prime
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    if sp[c] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_s[c, sp[c]]
                        if cand[RQ_OFF] == 0:
                            sp[c] += 1                       # bubble slot: skip
                        elif rtr_n[M, c].try_put(cand):
                            sp[c] += 1                       # sent (FIFO room)

        @df.kernel(mapping=[1], args=[rout_w])
        def rclc_w(rdout_w: int32[M, LANELEN]):
            k: int32[M] = 0                   # NB collector: try_get, no credits
            seen: int32[M] = 0               # DEBUG: pkts escaping mesh on this edge
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    pw, okp = rtr_w[r, 0].try_get()
                    if okp and pw[RQ_OFF] == 1:
                        seen[r] += 1
                        if k[r] < LANELEN - 1:
                            rdout_w[r, k[r]] = pw & PMASK
                            k[r] += 1
            with allo.meta_for(0, M) as r:
                rdout_w[r, LANELEN - 1] = seen[r]
                              
        @df.kernel(mapping=[1], args=[rout_e])
        def rclc_e(rdout_e: int32[M, LANELEN]):
            k: int32[M] = 0                   # NB collector: try_get, no credits
            seen: int32[M] = 0               # DEBUG: pkts escaping mesh on this edge
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    pw, okp = rtr_e[r, N].try_get()
                    if okp and pw[RQ_OFF] == 1:
                        seen[r] += 1
                        if k[r] < LANELEN - 1:
                            rdout_e[r, k[r]] = pw & PMASK
                            k[r] += 1
            with allo.meta_for(0, M) as r:
                rdout_e[r, LANELEN - 1] = seen[r]

        @df.kernel(mapping=[1], args=[rout_n])
        def rclc_n(rdout_n: int32[N, LANELEN]):
            k: int32[N] = 0                   # NB collector: try_get, no credits
            seen: int32[N] = 0               # DEBUG: pkts escaping mesh on this edge
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    pw, okp = rtr_n[0, c].try_get()
                    if okp and pw[RQ_OFF] == 1:
                        seen[c] += 1
                        if k[c] < LANELEN - 1:
                            rdout_n[c, k[c]] = pw & PMASK
                            k[c] += 1
            with allo.meta_for(0, N) as c:
                rdout_n[c, LANELEN - 1] = seen[c]

        @df.kernel(mapping=[1], args=[rout_s])
        def rclc_s(rdout_s: int32[N, LANELEN]):
            k: int32[N] = 0                   # NB collector: try_get, no credits
            seen: int32[N] = 0               # DEBUG: pkts escaping mesh on this edge
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    pw, okp = rtr_s[M, c].try_get()
                    if okp and pw[RQ_OFF] == 1:
                        seen[c] += 1
                        if k[c] < LANELEN - 1:
                            rdout_s[c, k[c]] = pw & PMASK
                            k[c] += 1
            with allo.meta_for(0, N) as c:
                rdout_s[c, LANELEN - 1] = seen[c]

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
    s = df.customize(get_eva_top(Ty))
    if partition_rf:
        for i in range(M):
            for j in range(N):
                for buf in ("irf", "drf", "drf_full", "rbuf", "rbcnt", "hold_v", "hold_cnt",
                            # scoreboard state must be registers, not RAMs
                            "resq", "cmpq", "sb_v", "sb_dst", "sb_cmp", "sb_rtr",
                            "sb_inj", "sb_dir", "sb_id", "sb_rvld", "sb_ix"):
                    s.partition(f"node_{i}_{j}:{buf}")
    if pipeline_node:
        for i in range(M):
            for j in range(N):
                s.pipeline(f"node_{i}_{j}:t", initiation_interval=1)
    return s

if __name__ == "__main__":
    # 1x1 chip, NSTEP=10 — csynth QoR config. Usage:
    #   python eva_prime_sb.py
    #   cd eva_scoreboard_float16_t_t && vitis_hls -f run.tcl
    M, N = 1, 1
    NSTEP = 10
    LANELEN = NSTEP

    import os
    P = os.path.join(os.path.dirname(os.path.abspath(__file__)), "nb_fin_eva_scoreboard_float16_t_t")
    s = get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)
    s.build(target="vhls", mode="csyn", project=P)
    print("generated HLS project at", P)
