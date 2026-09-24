
import allo
from allo.ir.types import float16, int16, int32, UInt, AlloType, Stream, float32
import allo.dataflow as df
import numpy as np

M, N = 2,2
NSTEP = 10

DRF_DEPTH, IRF_DEPTH = 8, 8
BUF_DEPTH = 2

SB_DEPTH, RESQ_DEPTH = 5, 8
FWD = 1
FP_LAT = 1
MOV_LAT = 0

PRIME_TOKENS = 6
STREAM_DEPTH = 8
LANELEN = NSTEP

WSKID = 4
PREFILL = 2

OP_ADD, OP_SUB, OP_MULT, OP_MOV = 0x0, 0x1, 0x2, 0x3
OP_RTR0 = 0x4
OP_GEQ, OP_LT = 0x8, 0x9
OP_CRTR0 = 0xC
OP_DIV, OP_SQRT = 0xA, 0xB

def get_eva_top(Ty: AlloType = float16):
    DATA_W = Ty.bits
    ID_W, MODE_W, ADDR_W, RQ_W = 4, 1, 4, 1

    D_OFF  = 0
    A_OFF  = D_OFF + DATA_W
    MD_OFF = A_OFF + ADDR_W
    ID_OFF = MD_OFF + MODE_W
    RQ_OFF = ID_OFF + ID_W
    PKT_W  = RQ_OFF + RQ_W

    PMASK  = (1 << PKT_W) - 1 if PKT_W < 32 else 0x7FFFFFFF
    Pkt    = UInt(PKT_W)
    CrTy   = int32

    SYS_W  = UInt(1 + DATA_W)

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
        prime_cfg: int32[M, N],
    ):
        sys_e: Stream[SYS_W, STREAM_DEPTH][M, N + 1]
        sys_w: Stream[SYS_W, STREAM_DEPTH][M, N + 1]
        sys_s: Stream[SYS_W, STREAM_DEPTH][M + 1, N]
        sys_n: Stream[SYS_W, STREAM_DEPTH][M + 1, N]
        rtr_e: Stream[Pkt, STREAM_DEPTH][M, N + 1]
        rtr_w: Stream[Pkt, STREAM_DEPTH][M, N + 1]
        rtr_s: Stream[Pkt, STREAM_DEPTH][M + 1, N]
        rtr_n: Stream[Pkt, STREAM_DEPTH][M + 1, N]
        cr_e: Stream[CrTy, STREAM_DEPTH][M, N + 1]
        cr_w: Stream[CrTy, STREAM_DEPTH][M, N + 1]
        cr_s: Stream[CrTy, STREAM_DEPTH][M + 1, N]
        cr_n: Stream[CrTy, STREAM_DEPTH][M + 1, N]
        scr_e: Stream[CrTy, STREAM_DEPTH][M, N + 1]
        scr_w: Stream[CrTy, STREAM_DEPTH][M, N + 1]
        scr_s: Stream[CrTy, STREAM_DEPTH][M + 1, N]
        scr_n: Stream[CrTy, STREAM_DEPTH][M + 1, N]

        @df.kernel(mapping=[M, N], args=[prime_cfg])
        def node(pcfg: int32[M, N]):
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

            oe_r: Pkt = 0; ow_r: Pkt = 0; on_r: Pkt = 0; os_r: Pkt = 0
            txn_r: SYS_W = 0; txs_r: SYS_W = 0; txw_r: SYS_W = 0; txe_r: SYS_W = 0

            hold_v: Ty[4, 2] = 0; hold_cnt: UInt(8)[4] = 0

            rbuf:  Pkt[4, BUF_DEPTH] = 0
            rbcnt: UInt(8)[4] = 0
            rcred: UInt(8)[4] = 0

            cre_r: CrTy = BUF_DEPTH; crw_r: CrTy = BUF_DEPTH
            crs_r: CrTy = BUF_DEPTH; crn_r: CrTy = BUF_DEPTH

            scred: int32[4] = 0
            txp_v: int32[4] = 0
            txp_d: Ty[4] = 0
            sc_r: CrTy[4] = 2

            cfg_isz: int32 = 0
            cfg_itsz: int32 = 0
            fetch_en: UInt(8) = 0
            instr_cnt: UInt(8) = 0
            iter_cnt: UInt(8) = 0
            condition_reg: UInt(8) = 0

            sb_v: UInt(8)[SB_DEPTH] = 0;  sb_dst: UInt(8)[SB_DEPTH] = 0
            sb_cmp: UInt(8)[SB_DEPTH] = 0; sb_rtr: UInt(8)[SB_DEPTH] = 0
            sb_inj: UInt(8)[SB_DEPTH] = 0; sb_dir: UInt(8)[SB_DEPTH] = 0
            sb_id: UInt(8)[SB_DEPTH] = 0; sb_rvld: UInt(8)[SB_DEPTH] = 0
            sb_ix: UInt(8)[SB_DEPTH] = 0
            sb_long: UInt(8)[SB_DEPTH] = 0
            resq: Ty[RESQ_DEPTH] = 0
            cmpq: UInt(8)[RESQ_DEPTH] = 0
            resq_wr: UInt(8) = 0

            zpkt: Pkt = 0
            zsys: SYS_W = 0
            zcr: CrTy = 0
            for _pt in range(pcfg[i, j] - 1):
                rtr_e[i, j + 1].put(zpkt)
                rtr_w[i, j].put(zpkt)
                rtr_s[i + 1, j].put(zpkt)
                rtr_n[i, j].put(zpkt)
                sys_e[i, j + 1].put(zsys)
                sys_w[i, j].put(zsys)
                sys_s[i + 1, j].put(zsys)
                sys_n[i, j].put(zsys)
                cr_e[i, j].put(zcr)
                cr_w[i, j + 1].put(zcr)
                cr_s[i, j].put(zcr)
                cr_n[i + 1, j].put(zcr)
                scr_e[i, j].put(zcr)
                scr_w[i, j + 1].put(zcr)
                scr_s[i, j].put(zcr)
                scr_n[i + 1, j].put(zcr)

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
            scr_s[i, j].put(sc_r[0])
            scr_n[i + 1, j].put(sc_r[1])
            scr_e[i, j].put(sc_r[2])
            scr_w[i, j + 1].put(sc_r[3])

            for t in range(NSTEP):
                p_w: Pkt = rtr_e[i, j].get()
                p_e: Pkt = rtr_w[i, j + 1].get()
                p_n: Pkt = rtr_s[i, j].get()
                p_s: Pkt = rtr_n[i + 1, j].get()
                cg0: CrTy = cr_e[i, j + 1].get()
                rcred[0] += cg0
                cg1: CrTy = cr_w[i, j].get()
                rcred[1] += cg1
                cg2: CrTy = cr_s[i + 1, j].get()
                rcred[2] += cg2
                cg3: CrTy = cr_n[i, j].get()
                rcred[3] += cg3
                cg4: CrTy = scr_n[i, j].get()
                scred[0] += cg4
                cg5: CrTy = scr_s[i + 1, j].get()
                scred[1] += cg5
                cg6: CrTy = scr_w[i, j].get()
                scred[2] += cg6
                cg7: CrTy = scr_e[i, j + 1].get()
                scred[3] += cg7

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

                o_out: Pkt[4] = 0; pop: int32[4] = 0; inj_done: int32 = 0
                idir: int32 = -1
                if csd_pkt[RQ_OFF] == 1: idir = 3 - csd_dir
                for o in range(4):
                    if rcred[o] > 0:
                        if idir == o:
                            o_out[o] = csd_pkt; rcred[o] -= 1; inj_done = 1
                        elif hvld[o] == 1 and hit[o] == 0:
                            o_out[o] = hd[o]; rcred[o] -= 1; pop[o] = 1
                if crv_in >= 0: pop[crv_in] = 1

                ret: CrTy[4] = 0
                for d in range(4):
                    if pop[d] == 1:
                        for sft in range(BUF_DEPTH - 1):
                            rbuf[d, sft] = rbuf[d, sft + 1]
                        rbcnt[d] -= 1; ret[d] = 1
                cre_r = ret[0]; crw_r = ret[1]; crs_r = ret[2]; crn_r = ret[3]

                oe_r = o_out[0]; ow_r = o_out[1]; os_r = o_out[2]; on_r = o_out[3]
                if inj_done == 1: csd_pkt = 0

                crv_vld = o_crv[RQ_OFF]
                crv_data = o_crv[0 : Ty.bits].bitcast()
                crv_addr = o_crv[Ty.bits : Ty.bits + 4]
                crv_mode = o_crv[Ty.bits + 4]
                crv_raw  = o_crv[0 : Ty.bits]

                rx_w: SYS_W = sys_e[i, j].get()
                rx_e: SYS_W = sys_w[i, j + 1].get()
                rx_n: SYS_W = sys_s[i, j].get()
                rx_s: SYS_W = sys_n[i + 1, j].get()

                rxv: Ty[4] = 0; rxvld: int32[4] = 0
                rxv[0] = rx_n[1 : 1 + Ty.bits].bitcast(); rxvld[0] = rx_n[0]
                rxv[1] = rx_s[1 : 1 + Ty.bits].bitcast(); rxvld[1] = rx_s[0]
                rxv[2] = rx_w[1 : 1 + Ty.bits].bitcast(); rxvld[2] = rx_w[0]
                rxv[3] = rx_e[1 : 1 + Ty.bits].bitcast(); rxvld[3] = rx_e[0]
                for d in range(4):
                    if rxvld[d] == 1 and hold_cnt[d] < 2:
                        hold_v[d, hold_cnt[d]] = rxv[d]; hold_cnt[d] += 1

                retire_ok: int32 = 1
                if sb_v[0] == 1 and sb_rtr[0] == 0 and sb_dst[0] >= 12:
                    if sb_rvld[0] == 1 and txp_v[sb_dst[0] & 3] == 1: retire_ok = 0
                if sb_v[0] == 1 and retire_ok == 1:
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
                        if sb_rvld[0] == 1:
                            txp_v[sb_dst[0] & 3] = 1
                            txp_d[sb_dst[0] & 3] = wb
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
                raw: int32 = 0; cmp_busy: int32 = 0
                fwd_a: int32 = 0; fwd_a_ix: int32 = 0; raw_a: int32 = 0
                fwd_b: int32 = 0; fwd_b_ix: int32 = 0; raw_b: int32 = 0
                for k in range(SB_DEPTH - 1):
                    kk: int32 = k + 1
                    inflight: int32 = SB_DEPTH - 1 - kk
                    need: int32 = MOV_LAT
                    if sb_long[kk] == 1: need = FP_LAT
                    rdy: int32 = 0
                    if inflight >= need: rdy = 1
                    if sb_v[kk] == 1 and sb_rtr[kk] == 0 and sb_dst[kk] < 12:
                        if s1 < 12 and (sb_dst[kk] & 7) == (s1 & 7):
                            if FWD == 1 and rdy == 1: fwd_a = 1; fwd_a_ix = sb_ix[kk]; raw_a = 0
                            else:                     fwd_a = 0; raw_a = 1
                        if binop == 1 and s2 < 12 and (sb_dst[kk] & 7) == (s2 & 7):
                            if FWD == 1 and rdy == 1: fwd_b = 1; fwd_b_ix = sb_ix[kk]; raw_b = 0
                            else:                     fwd_b = 0; raw_b = 1
                    if sb_v[kk] == 1 and sb_cmp[kk] == 1: cmp_busy = 1
                raw = raw_a
                if binop == 1 and raw_b == 1: raw = 1
                if fwd_a == 1: a = resq[fwd_a_ix]; a_vld = 1
                if fwd_b == 1: b = resq[fwd_b_ix]; b_vld = 1
                is_cond: int32 = 0
                if op >= OP_CRTR0 and op <= OP_CRTR0 + 3: is_cond = 1

                grant: int32 = 0
                if pc >= 0: grant = 1
                if pc >= 0 and (a_vld == 0 or (binop == 1 and b_vld == 0)): grant = 0
                if pc >= 0 and (raw == 1 or (is_cond == 1 and cmp_busy == 1)): grant = 0
                if retire_ok == 0: grant = 0
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
                for d in range(4):
                    sc_r[d] = 0
                if c1 >= 0: sc_r[c1] = 1
                if c2 >= 0 and c2 != c1: sc_r[c2] = 1

                if grant == 1 and s1 < DRF_DEPTH and ((dsmask >> s1) & 1) == 1: drf_full[s1] = 0
                if grant == 1 and s2 < DRF_DEPTH and ((dsmask >> s2) & 1) == 1: drf_full[s2] = 0

                res: Ty = 0
                bbits: UInt(16) = b.bitcast()
                if op == OP_SUB: bbits = bbits ^ 0x8000
                b_eff: Ty = bbits.bitcast()
                if op == OP_ADD or op == OP_SUB: res = a + b_eff
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
                is_rtr: int32 = 0
                if op >= OP_RTR0 and op <= OP_RTR0 + 3: is_rtr = 1
                if retire_ok == 1:
                    for k in range(SB_DEPTH - 1):
                        sb_v[k] = sb_v[k + 1];     sb_dst[k] = sb_dst[k + 1]
                        sb_cmp[k] = sb_cmp[k + 1]; sb_rtr[k] = sb_rtr[k + 1]
                        sb_inj[k] = sb_inj[k + 1]; sb_dir[k] = sb_dir[k + 1]
                        sb_id[k] = sb_id[k + 1];   sb_rvld[k] = sb_rvld[k + 1]
                        sb_ix[k] = sb_ix[k + 1]; sb_long[k] = sb_long[k + 1]
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
                    sb_long[SB_DEPTH - 1] = binop
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

                txn_r = 0; txs_r = 0; txw_r = 0; txe_r = 0
                if txp_v[0] == 1 and scred[0] > 0:
                    twn: SYS_W = 0
                    twn[0] = 1
                    twn[1 : 1 + Ty.bits] = txp_d[0].bitcast()
                    txn_r = twn; txp_v[0] = 0; scred[0] -= 1
                if txp_v[1] == 1 and scred[1] > 0:
                    tws: SYS_W = 0
                    tws[0] = 1
                    tws[1 : 1 + Ty.bits] = txp_d[1].bitcast()
                    txs_r = tws; txp_v[1] = 0; scred[1] -= 1
                if txp_v[2] == 1 and scred[2] > 0:
                    tww: SYS_W = 0
                    tww[0] = 1
                    tww[1 : 1 + Ty.bits] = txp_d[2].bitcast()
                    txw_r = tww; txp_v[2] = 0; scred[2] -= 1
                if txp_v[3] == 1 and scred[3] > 0:
                    twe: SYS_W = 0
                    twe[0] = 1
                    twe[1 : 1 + Ty.bits] = txp_d[3].bitcast()
                    txe_r = twe; txp_v[3] = 0; scred[3] -= 1
                if crv_vld == 1:
                    if crv_mode == 1:
                        if ((crv_addr >> 3) & 1) == 1: irf[crv_addr & 7] = crv_raw
                        elif crv_addr == 0:
                            dsmask = crv_raw & 0xFF
                            cfg_isz = (crv_raw >> 8) & 0x7
                            if ((crv_raw >> 15) & 1) == 1: fetch_en = 1; instr_cnt = 0; iter_cnt = 0
                        elif crv_addr == 1: cfg_itsz = crv_raw & 0xFF
                    elif ((crv_addr >> 2) & 3) == 3:
                        txp_v[crv_addr & 3] = 1
                        txp_d[crv_addr & 3] = crv_data
                    elif crv_addr < DRF_DEPTH and ((dsmask >> crv_addr) & 1) == 1:
                        if drf_full[crv_addr] == 0:
                            drf[crv_addr] = crv_data; drf_full[crv_addr] = 1
                    else:
                        drf[crv_addr] = crv_data

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
                scr_s[i, j].put(sc_r[0])
                scr_n[i + 1, j].put(sc_r[1])
                scr_e[i, j].put(sc_r[2])
                scr_w[i, j + 1].put(sc_r[3])


        @df.kernel(mapping=[1], args=[in_w, iv_w, prime_cfg])
        def drv_w(din: Ty[M, LANELEN], vd: int32[M, LANELEN], pcfg: int32[M, N]):
            dcred: int32[M] = 0
            rp: int32[M] = 0
            wcnt: int32[M] = 0
            win_d: Ty[M, WSKID] = 0
            win_f: int32[M, WSKID] = 0
            win_s: int32[M, WSKID] = 0
            zw: SYS_W = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, M) as r:
                    sys_e[r, 0].put(zw)
            for _pf in range(PREFILL):
                with allo.meta_for(0, M) as r:
                    if rp[r] < LANELEN:
                        win_d[r, wcnt[r]] = din[r, rp[r]]
                        win_f[r, wcnt[r]] = vd[r, rp[r]]
                        win_s[r, wcnt[r]] = rp[r]
                        wcnt[r] += 1; rp[r] += 1
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    cin: CrTy = scr_e[r, 0].get()
                    dcred[r] += cin
                    w: SYS_W = 0
                    popd: int32 = 0
                    if wcnt[r] > 0 and t >= win_s[r, 0]:
                        if win_f[r, 0] == 0:
                            popd = 1
                        elif dcred[r] > 0:
                            w[0] = 1
                            w[1 : 1 + Ty.bits] = win_d[r, 0].bitcast()
                            dcred[r] -= 1
                            popd = 1
                    if popd == 1:
                        for sft in range(WSKID - 1):
                            win_d[r, sft] = win_d[r, sft + 1]
                            win_f[r, sft] = win_f[r, sft + 1]
                            win_s[r, sft] = win_s[r, sft + 1]
                        wcnt[r] -= 1
                    if rp[r] < LANELEN and wcnt[r] < WSKID:
                        win_d[r, wcnt[r]] = din[r, rp[r]]
                        win_f[r, wcnt[r]] = vd[r, rp[r]]
                        win_s[r, wcnt[r]] = rp[r]
                        wcnt[r] += 1; rp[r] += 1
                    sys_e[r, 0].put(w)

        @df.kernel(mapping=[1], args=[in_e, iv_e, prime_cfg])
        def drv_e(din: Ty[M, LANELEN], vd: int32[M, LANELEN], pcfg: int32[M, N]):
            dcred: int32[M] = 0
            rp: int32[M] = 0
            wcnt: int32[M] = 0
            win_d: Ty[M, WSKID] = 0
            win_f: int32[M, WSKID] = 0
            win_s: int32[M, WSKID] = 0
            zw: SYS_W = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, M) as r:
                    sys_w[r, N].put(zw)
            for _pf in range(PREFILL):
                with allo.meta_for(0, M) as r:
                    if rp[r] < LANELEN:
                        win_d[r, wcnt[r]] = din[r, rp[r]]
                        win_f[r, wcnt[r]] = vd[r, rp[r]]
                        win_s[r, wcnt[r]] = rp[r]
                        wcnt[r] += 1; rp[r] += 1
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    cin: CrTy = scr_w[r, N].get()
                    dcred[r] += cin
                    w: SYS_W = 0
                    popd: int32 = 0
                    if wcnt[r] > 0 and t >= win_s[r, 0]:
                        if win_f[r, 0] == 0:
                            popd = 1
                        elif dcred[r] > 0:
                            w[0] = 1
                            w[1 : 1 + Ty.bits] = win_d[r, 0].bitcast()
                            dcred[r] -= 1
                            popd = 1
                    if popd == 1:
                        for sft in range(WSKID - 1):
                            win_d[r, sft] = win_d[r, sft + 1]
                            win_f[r, sft] = win_f[r, sft + 1]
                            win_s[r, sft] = win_s[r, sft + 1]
                        wcnt[r] -= 1
                    if rp[r] < LANELEN and wcnt[r] < WSKID:
                        win_d[r, wcnt[r]] = din[r, rp[r]]
                        win_f[r, wcnt[r]] = vd[r, rp[r]]
                        win_s[r, wcnt[r]] = rp[r]
                        wcnt[r] += 1; rp[r] += 1
                    sys_w[r, N].put(w)

        @df.kernel(mapping=[1], args=[in_n, iv_n, prime_cfg])
        def drv_n(din: Ty[N, LANELEN], vd: int32[N, LANELEN], pcfg: int32[M, N]):
            dcred: int32[N] = 0
            rp: int32[N] = 0
            wcnt: int32[N] = 0
            win_d: Ty[N, WSKID] = 0
            win_f: int32[N, WSKID] = 0
            win_s: int32[N, WSKID] = 0
            zw: SYS_W = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, N) as r:
                    sys_s[0, r].put(zw)
            for _pf in range(PREFILL):
                with allo.meta_for(0, N) as r:
                    if rp[r] < LANELEN:
                        win_d[r, wcnt[r]] = din[r, rp[r]]
                        win_f[r, wcnt[r]] = vd[r, rp[r]]
                        win_s[r, wcnt[r]] = rp[r]
                        wcnt[r] += 1; rp[r] += 1
            for t in range(NSTEP):
                with allo.meta_for(0, N) as r:
                    cin: CrTy = scr_s[0, r].get()
                    dcred[r] += cin
                    w: SYS_W = 0
                    popd: int32 = 0
                    if wcnt[r] > 0 and t >= win_s[r, 0]:
                        if win_f[r, 0] == 0:
                            popd = 1
                        elif dcred[r] > 0:
                            w[0] = 1
                            w[1 : 1 + Ty.bits] = win_d[r, 0].bitcast()
                            dcred[r] -= 1
                            popd = 1
                    if popd == 1:
                        for sft in range(WSKID - 1):
                            win_d[r, sft] = win_d[r, sft + 1]
                            win_f[r, sft] = win_f[r, sft + 1]
                            win_s[r, sft] = win_s[r, sft + 1]
                        wcnt[r] -= 1
                    if rp[r] < LANELEN and wcnt[r] < WSKID:
                        win_d[r, wcnt[r]] = din[r, rp[r]]
                        win_f[r, wcnt[r]] = vd[r, rp[r]]
                        win_s[r, wcnt[r]] = rp[r]
                        wcnt[r] += 1; rp[r] += 1
                    sys_s[0, r].put(w)

        @df.kernel(mapping=[1], args=[in_s, iv_s, prime_cfg])
        def drv_s(din: Ty[N, LANELEN], vd: int32[N, LANELEN], pcfg: int32[M, N]):
            dcred: int32[N] = 0
            rp: int32[N] = 0
            wcnt: int32[N] = 0
            win_d: Ty[N, WSKID] = 0
            win_f: int32[N, WSKID] = 0
            win_s: int32[N, WSKID] = 0
            zw: SYS_W = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, N) as r:
                    sys_n[M, r].put(zw)
            for _pf in range(PREFILL):
                with allo.meta_for(0, N) as r:
                    if rp[r] < LANELEN:
                        win_d[r, wcnt[r]] = din[r, rp[r]]
                        win_f[r, wcnt[r]] = vd[r, rp[r]]
                        win_s[r, wcnt[r]] = rp[r]
                        wcnt[r] += 1; rp[r] += 1
            for t in range(NSTEP):
                with allo.meta_for(0, N) as r:
                    cin: CrTy = scr_n[M, r].get()
                    dcred[r] += cin
                    w: SYS_W = 0
                    popd: int32 = 0
                    if wcnt[r] > 0 and t >= win_s[r, 0]:
                        if win_f[r, 0] == 0:
                            popd = 1
                        elif dcred[r] > 0:
                            w[0] = 1
                            w[1 : 1 + Ty.bits] = win_d[r, 0].bitcast()
                            dcred[r] -= 1
                            popd = 1
                    if popd == 1:
                        for sft in range(WSKID - 1):
                            win_d[r, sft] = win_d[r, sft + 1]
                            win_f[r, sft] = win_f[r, sft + 1]
                            win_s[r, sft] = win_s[r, sft + 1]
                        wcnt[r] -= 1
                    if rp[r] < LANELEN and wcnt[r] < WSKID:
                        win_d[r, wcnt[r]] = din[r, rp[r]]
                        win_f[r, wcnt[r]] = vd[r, rp[r]]
                        win_s[r, wcnt[r]] = rp[r]
                        wcnt[r] += 1; rp[r] += 1
                    sys_n[M, r].put(w)
        @df.kernel(mapping=[1], args=[out_w, prime_cfg])
        def col_w(dout_w: Ty[M, LANELEN], pcfg: int32[M, N]):
            k: int32[M] = 0
            cret: CrTy[M] = 0
            zc: CrTy = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, M) as r:
                    scr_w[r, 0].put(zc)
            with allo.meta_for(0, M) as r:
                cret[r] = 2
                scr_w[r, 0].put(cret[r])
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    w: SYS_W = sys_w[r, 0].get()
                    cret[r] = 0
                    if w[0] == 1:
                        cret[r] = 1
                        if k[r] < LANELEN:
                            dout_w[r, k[r]] = w[1 : 1 + Ty.bits].bitcast()
                            k[r] += 1
                    scr_w[r, 0].put(cret[r])

        @df.kernel(mapping=[1], args=[out_e, prime_cfg])
        def col_e(dout_e: Ty[M, LANELEN], pcfg: int32[M, N]):
            k: int32[M] = 0
            cret: CrTy[M] = 0
            zc: CrTy = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, M) as r:
                    scr_e[r, N].put(zc)
            with allo.meta_for(0, M) as r:
                cret[r] = 2
                scr_e[r, N].put(cret[r])
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    w: SYS_W = sys_e[r, N].get()
                    cret[r] = 0
                    if w[0] == 1:
                        cret[r] = 1
                        if k[r] < LANELEN:
                            dout_e[r, k[r]] = w[1 : 1 + Ty.bits].bitcast()
                            k[r] += 1
                    scr_e[r, N].put(cret[r])

        @df.kernel(mapping=[1], args=[out_n, prime_cfg])
        def col_n(dout_n: Ty[N, LANELEN], pcfg: int32[M, N]):
            k: int32[N] = 0
            cret: CrTy[N] = 0
            zc: CrTy = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, N) as c:
                    scr_n[0, c].put(zc)
            with allo.meta_for(0, N) as c:
                cret[c] = 2
                scr_n[0, c].put(cret[c])
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    w: SYS_W = sys_n[0, c].get()
                    cret[c] = 0
                    if w[0] == 1:
                        cret[c] = 1
                        if k[c] < LANELEN:
                            dout_n[c, k[c]] = w[1 : 1 + Ty.bits].bitcast()
                            k[c] += 1
                    scr_n[0, c].put(cret[c])

        @df.kernel(mapping=[1], args=[out_s, prime_cfg])
        def col_s(dout_s: Ty[N, LANELEN], pcfg: int32[M, N]):
            k: int32[N] = 0
            cret: CrTy[N] = 0
            zc: CrTy = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, N) as c:
                    scr_s[M, c].put(zc)
            with allo.meta_for(0, N) as c:
                cret[c] = 2
                scr_s[M, c].put(cret[c])
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    w: SYS_W = sys_s[M, c].get()
                    cret[c] = 0
                    if w[0] == 1:
                        cret[c] = 1
                        if k[c] < LANELEN:
                            dout_s[c, k[c]] = w[1 : 1 + Ty.bits].bitcast()
                            k[c] += 1
                    scr_s[M, c].put(cret[c])


        @df.kernel(mapping=[1], args=[rin_w, prime_cfg])
        def rdrv_w(rdin: int32[M, LANELEN], pcfg: int32[M, N]):
            dcred: int32[M] = 0
            rp: int32[M] = 0; wcnt: int32[M] = 0
            win_p: Pkt[M, WSKID] = 0
            zp: Pkt = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, M) as r:
                    rtr_e[r, 0].put(zp)
            for _pf in range(PREFILL):
                with allo.meta_for(0, M) as r:
                    if rp[r] < LANELEN:
                        cnd: Pkt = 0
                        cnd[0 : Ty.bits + 10] = rdin[r, rp[r]]
                        win_p[r, wcnt[r]] = cnd
                        wcnt[r] += 1; rp[r] += 1
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    cin: CrTy = cr_e[r, 0].get()
                    dcred[r] += cin
                    pw: Pkt = 0
                    hp: Pkt = win_p[r, 0]
                    popd: int32 = 0
                    if wcnt[r] > 0:
                        if hp[RQ_OFF] == 0:
                            popd = 1
                        elif dcred[r] > 0:
                            pw = hp; dcred[r] -= 1; popd = 1
                    if popd == 1:
                        for sft in range(WSKID - 1):
                            win_p[r, sft] = win_p[r, sft + 1]
                        wcnt[r] -= 1
                    if rp[r] < LANELEN and wcnt[r] < WSKID:
                        cnd2: Pkt = 0
                        cnd2[0 : Ty.bits + 10] = rdin[r, rp[r]]
                        win_p[r, wcnt[r]] = cnd2
                        wcnt[r] += 1; rp[r] += 1
                    rtr_e[r, 0].put(pw)

        @df.kernel(mapping=[1], args=[rin_e, prime_cfg])
        def rdrv_e(rdin: int32[M, LANELEN], pcfg: int32[M, N]):
            dcred: int32[M] = 0
            rp: int32[M] = 0; wcnt: int32[M] = 0
            win_p: Pkt[M, WSKID] = 0
            zp: Pkt = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, M) as r:
                    rtr_w[r, N].put(zp)
            for _pf in range(PREFILL):
                with allo.meta_for(0, M) as r:
                    if rp[r] < LANELEN:
                        cnd: Pkt = 0
                        cnd[0 : Ty.bits + 10] = rdin[r, rp[r]]
                        win_p[r, wcnt[r]] = cnd
                        wcnt[r] += 1; rp[r] += 1
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    cin: CrTy = cr_w[r, N].get()
                    dcred[r] += cin
                    pw: Pkt = 0
                    hp: Pkt = win_p[r, 0]
                    popd: int32 = 0
                    if wcnt[r] > 0:
                        if hp[RQ_OFF] == 0:
                            popd = 1
                        elif dcred[r] > 0:
                            pw = hp; dcred[r] -= 1; popd = 1
                    if popd == 1:
                        for sft in range(WSKID - 1):
                            win_p[r, sft] = win_p[r, sft + 1]
                        wcnt[r] -= 1
                    if rp[r] < LANELEN and wcnt[r] < WSKID:
                        cnd2: Pkt = 0
                        cnd2[0 : Ty.bits + 10] = rdin[r, rp[r]]
                        win_p[r, wcnt[r]] = cnd2
                        wcnt[r] += 1; rp[r] += 1
                    rtr_w[r, N].put(pw)

        @df.kernel(mapping=[1], args=[rin_n, prime_cfg])
        def rdrv_n(rdin: int32[N, LANELEN], pcfg: int32[M, N]):
            dcred: int32[N] = 0
            rp: int32[N] = 0; wcnt: int32[N] = 0
            win_p: Pkt[N, WSKID] = 0
            zp: Pkt = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, N) as r:
                    rtr_s[0, r].put(zp)
            for _pf in range(PREFILL):
                with allo.meta_for(0, N) as r:
                    if rp[r] < LANELEN:
                        cnd: Pkt = 0
                        cnd[0 : Ty.bits + 10] = rdin[r, rp[r]]
                        win_p[r, wcnt[r]] = cnd
                        wcnt[r] += 1; rp[r] += 1
            for t in range(NSTEP):
                with allo.meta_for(0, N) as r:
                    cin: CrTy = cr_s[0, r].get()
                    dcred[r] += cin
                    pw: Pkt = 0
                    hp: Pkt = win_p[r, 0]
                    popd: int32 = 0
                    if wcnt[r] > 0:
                        if hp[RQ_OFF] == 0:
                            popd = 1
                        elif dcred[r] > 0:
                            pw = hp; dcred[r] -= 1; popd = 1
                    if popd == 1:
                        for sft in range(WSKID - 1):
                            win_p[r, sft] = win_p[r, sft + 1]
                        wcnt[r] -= 1
                    if rp[r] < LANELEN and wcnt[r] < WSKID:
                        cnd2: Pkt = 0
                        cnd2[0 : Ty.bits + 10] = rdin[r, rp[r]]
                        win_p[r, wcnt[r]] = cnd2
                        wcnt[r] += 1; rp[r] += 1
                    rtr_s[0, r].put(pw)

        @df.kernel(mapping=[1], args=[rin_s, prime_cfg])
        def rdrv_s(rdin: int32[N, LANELEN], pcfg: int32[M, N]):
            dcred: int32[N] = 0
            rp: int32[N] = 0; wcnt: int32[N] = 0
            win_p: Pkt[N, WSKID] = 0
            zp: Pkt = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, N) as r:
                    rtr_n[M, r].put(zp)
            for _pf in range(PREFILL):
                with allo.meta_for(0, N) as r:
                    if rp[r] < LANELEN:
                        cnd: Pkt = 0
                        cnd[0 : Ty.bits + 10] = rdin[r, rp[r]]
                        win_p[r, wcnt[r]] = cnd
                        wcnt[r] += 1; rp[r] += 1
            for t in range(NSTEP):
                with allo.meta_for(0, N) as r:
                    cin: CrTy = cr_n[M, r].get()
                    dcred[r] += cin
                    pw: Pkt = 0
                    hp: Pkt = win_p[r, 0]
                    popd: int32 = 0
                    if wcnt[r] > 0:
                        if hp[RQ_OFF] == 0:
                            popd = 1
                        elif dcred[r] > 0:
                            pw = hp; dcred[r] -= 1; popd = 1
                    if popd == 1:
                        for sft in range(WSKID - 1):
                            win_p[r, sft] = win_p[r, sft + 1]
                        wcnt[r] -= 1
                    if rp[r] < LANELEN and wcnt[r] < WSKID:
                        cnd2: Pkt = 0
                        cnd2[0 : Ty.bits + 10] = rdin[r, rp[r]]
                        win_p[r, wcnt[r]] = cnd2
                        wcnt[r] += 1; rp[r] += 1
                    rtr_n[M, r].put(pw)
        @df.kernel(mapping=[1], args=[rout_w, prime_cfg])
        def rclc_w(rdout_w: int32[M, LANELEN], pcfg: int32[M, N]):
            k: int32[M] = 0
            cret: CrTy[M] = 0
            zc: CrTy = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, M) as r:
                    cr_w[r, 0].put(zc)
            with allo.meta_for(0, M) as r:
                cret[r] = BUF_DEPTH
                cr_w[r, 0].put(cret[r])
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    pw: Pkt = rtr_w[r, 0].get()
                    cret[r] = 0
                    if pw[RQ_OFF] == 1:
                        cret[r] = 1
                        if k[r] < LANELEN:
                            rdout_w[r, k[r]] = pw & PMASK
                            k[r] += 1
                    cr_w[r, 0].put(cret[r])

        @df.kernel(mapping=[1], args=[rout_e, prime_cfg])
        def rclc_e(rdout_e: int32[M, LANELEN], pcfg: int32[M, N]):
            k: int32[M] = 0; cret: CrTy[M] = 0
            zc: CrTy = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, M) as r:
                    cr_e[r, N].put(zc)
            with allo.meta_for(0, M) as r:
                cret[r] = BUF_DEPTH
                cr_e[r, N].put(cret[r])
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    pw: Pkt = rtr_e[r, N].get()
                    cret[r] = 0
                    if pw[RQ_OFF] == 1:
                        cret[r] = 1
                        if k[r] < LANELEN:
                            rdout_e[r, k[r]] = pw & PMASK
                            k[r] += 1
                    cr_e[r, N].put(cret[r])

        @df.kernel(mapping=[1], args=[rout_n, prime_cfg])
        def rclc_n(rdout_n: int32[N, LANELEN], pcfg: int32[M, N]):
            k: int32[N] = 0; cret: CrTy[N] = 0
            zc: CrTy = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, N) as c:
                    cr_n[0, c].put(zc)
            with allo.meta_for(0, N) as c:
                cret[c] = BUF_DEPTH
                cr_n[0, c].put(cret[c])
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    pw: Pkt = rtr_n[0, c].get()
                    cret[c] = 0
                    if pw[RQ_OFF] == 1:
                        cret[c] = 1
                        if k[c] < LANELEN:
                            rdout_n[c, k[c]] = pw & PMASK
                            k[c] += 1
                    cr_n[0, c].put(cret[c])

        @df.kernel(mapping=[1], args=[rout_s, prime_cfg])
        def rclc_s(rdout_s: int32[N, LANELEN], pcfg: int32[M, N]):
            k: int32[N] = 0; cret: CrTy[N] = 0
            zc: CrTy = 0
            for _pt in range(pcfg[0, 0] - 1):
                with allo.meta_for(0, N) as c:
                    cr_s[M, c].put(zc)
            with allo.meta_for(0, N) as c:
                cret[c] = BUF_DEPTH
                cr_s[M, c].put(cret[c])
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    pw: Pkt = rtr_s[M, c].get()
                    cret[c] = 0
                    if pw[RQ_OFF] == 1:
                        cret[c] = 1
                        if k[c] < LANELEN:
                            rdout_s[c, k[c]] = pw & PMASK
                            k[c] += 1
                    cr_s[M, c].put(cret[c])

    return top


if __name__ == "__main__":
    import os, re
    M = N = int(os.environ.get("SIZE", 1))
    NSTEP = LANELEN = int(os.environ.get("L", 10))
    RUN_BUDGET = 6 * LANELEN

    s = df.customize(get_eva_top(float16))
    for i in range(M):
        for j in range(N):
            s.pipeline(f"node_{i}_{j}:t")
            for buf in "irf drf drf_full rbuf rbcnt rcred hold_v hold_cnt resq cmpq sb_v sb_dst sb_cmp sb_rtr sb_inj sb_dir sb_id sb_rvld sb_ix sb_long scred txp_v txp_d".split():
                s.partition(f"node_{i}_{j}:{buf}")
    for io in ("drv_w drv_e drv_n drv_s col_w col_e col_n col_s "
               "rdrv_w rdrv_e rdrv_n rdrv_s rclc_w rclc_e rclc_n rclc_s").split():
        s.pipeline(f"{io}_0:t")

    P = f"prj_{M}x{N}"
    s.build(target="vhls", mode="csyn", project=P)

    src = open(f"{P}/kernel.cpp").read()
    src = re.sub(r"(union \{[^}]*\}\s*_converter\w*)\s*;", r"\1 = {};", src)
    src = re.sub(r"half (\w+) = \w+ \* \w+;",
                 lambda m: m[0] + f"\n#pragma HLS bind_op variable={m[1]} op=hmul impl=maxdsp latency=2", src)
    src = re.sub(r"half (\w+) = \w+ \+ \w+;",
                 lambda m: m[0] + f"\n#pragma HLS bind_op variable={m[1]} op=hadd impl=fabric latency=2", src)
    open(f"{P}/kernel.cpp", "w").write(src)
    print("built", P, "— Allo pipeline+partition; injected:", 'bind_op only (NODEP)')
