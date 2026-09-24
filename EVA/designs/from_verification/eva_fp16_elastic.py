
import allo
from allo.ir.types import float16, int16, int32, UInt, AlloType, Stream, float32
import allo.dataflow as df
import numpy as np

M, N = 2, 2
LANELEN = 10
RUN_BUDGET = 4 * LANELEN + 64

DRF_DEPTH, IRF_DEPTH = 8, 8

SB_DEPTH, RESQ_DEPTH = 5, 8
FWD = 1
FP_LAT = 1
MOV_LAT = 1
DATADRIVEN = 1

STREAM_DEPTH = 8

OP_ADD, OP_SUB, OP_MULT, OP_MOV = 0x0, 0x1, 0x2, 0x3
OP_RTR0 = 0x4
OP_GEQ, OP_LT = 0x8, 0x9
OP_CRTR0 = 0xC


def get_eva_top_elastic(Ty: AlloType = float16):
    DATA_W = Ty.bits
    ID_W, MODE_W, ADDR_W, RQ_W = 4, 1, 4, 1

    BUDGET = RUN_BUDGET if RUN_BUDGET >= 6 * LANELEN else 6 * LANELEN

    IS_FLOAT = Ty in (float16, float32)
    SIGNBIT = 1 << (DATA_W - 1)

    D_OFF  = 0
    A_OFF  = D_OFF + DATA_W
    MD_OFF = A_OFF + ADDR_W
    ID_OFF = MD_OFF + MODE_W
    RQ_OFF = ID_OFF + ID_W
    PKT_W  = RQ_OFF + RQ_W

    PMASK  = (1 << PKT_W) - 1 if PKT_W < 32 else 0x7FFFFFFF
    Pkt    = UInt(PKT_W)

    SDATA  = UInt(DATA_W)

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
        sys_e: Stream[SDATA, STREAM_DEPTH][M, N + 1]
        sys_w: Stream[SDATA, STREAM_DEPTH][M, N + 1]
        sys_s: Stream[SDATA, STREAM_DEPTH][M + 1, N]
        sys_n: Stream[SDATA, STREAM_DEPTH][M + 1, N]
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

            csd_pkt: Pkt = 0
            csd_dir: int32 = 0
            row_id: int32 = i
            col_id: int32 = j

            hold_v: Ty[4, 2] = 0; hold_cnt: UInt(8)[4] = 0

            ig_p: Pkt[4] = 0;   ig_v: int32[4] = 0
            oh_p: Pkt[4] = 0;   oh_v: int32[4] = 0
            txp_v: int32[4] = 0
            txp_d: Ty[4] = 0

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


            for it in range(BUDGET):
                if oh_v[0] == 1 and rtr_e[i, j + 1].full() == 0:
                    rtr_e[i, j + 1].put(oh_p[0]); oh_v[0] = 0
                if oh_v[1] == 1 and rtr_w[i, j].full() == 0:
                    rtr_w[i, j].put(oh_p[1]); oh_v[1] = 0
                if oh_v[2] == 1 and rtr_s[i + 1, j].full() == 0:
                    rtr_s[i + 1, j].put(oh_p[2]); oh_v[2] = 0
                if oh_v[3] == 1 and rtr_n[i, j].full() == 0:
                    rtr_n[i, j].put(oh_p[3]); oh_v[3] = 0

                if txp_v[0] == 1 and sys_n[i, j].full() == 0:
                    sys_n[i, j].put(txp_d[0].bitcast()); txp_v[0] = 0
                if txp_v[1] == 1 and sys_s[i + 1, j].full() == 0:
                    sys_s[i + 1, j].put(txp_d[1].bitcast()); txp_v[1] = 0
                if txp_v[2] == 1 and sys_w[i, j].full() == 0:
                    sys_w[i, j].put(txp_d[2].bitcast()); txp_v[2] = 0
                if txp_v[3] == 1 and sys_e[i, j + 1].full() == 0:
                    sys_e[i, j + 1].put(txp_d[3].bitcast()); txp_v[3] = 0

                if ig_v[0] == 0 and rtr_e[i, j].empty() == 0:
                    ig_p[0] = rtr_e[i, j].get(); ig_v[0] = 1
                if ig_v[1] == 0 and rtr_w[i, j + 1].empty() == 0:
                    ig_p[1] = rtr_w[i, j + 1].get(); ig_v[1] = 1
                if ig_v[2] == 0 and rtr_s[i, j].empty() == 0:
                    ig_p[2] = rtr_s[i, j].get(); ig_v[2] = 1
                if ig_v[3] == 0 and rtr_n[i + 1, j].empty() == 0:
                    ig_p[3] = rtr_n[i + 1, j].get(); ig_v[3] = 1

                if hold_cnt[0] < 2 and sys_s[i, j].empty() == 0:
                    wN: SDATA = sys_s[i, j].get()
                    hold_v[0, hold_cnt[0]] = wN.bitcast(); hold_cnt[0] += 1
                if hold_cnt[1] < 2 and sys_n[i + 1, j].empty() == 0:
                    wS: SDATA = sys_n[i + 1, j].get()
                    hold_v[1, hold_cnt[1]] = wS.bitcast(); hold_cnt[1] += 1
                if hold_cnt[2] < 2 and sys_e[i, j].empty() == 0:
                    wW: SDATA = sys_e[i, j].get()
                    hold_v[2, hold_cnt[2]] = wW.bitcast(); hold_cnt[2] += 1
                if hold_cnt[3] < 2 and sys_w[i, j + 1].empty() == 0:
                    wE: SDATA = sys_w[i, j + 1].get()
                    hold_v[3, hold_cnt[3]] = wE.bitcast(); hold_cnt[3] += 1

                hd: Pkt[4] = 0; hvld: int32[4] = 0; hit: int32[4] = 0
                axis: int32[4] = 0
                axis[0] = col_id; axis[1] = col_id; axis[2] = row_id; axis[3] = row_id
                for d in range(4):
                    if ig_v[d] == 1:
                        hd[d] = ig_p[d]; hvld[d] = 1
                        if hd[d][Ty.bits + 5 : Ty.bits + 9] == axis[d]: hit[d] = 1
                o_crv: Pkt = 0; crv_in: int32 = -1
                if   hit[3] == 1: o_crv = hd[3]; crv_in = 3
                elif hit[2] == 1: o_crv = hd[2]; crv_in = 2
                elif hit[1] == 1: o_crv = hd[1]; crv_in = 1
                elif hit[0] == 1: o_crv = hd[0]; crv_in = 0

                idir: int32 = -1
                if csd_pkt[RQ_OFF] == 1: idir = 3 - csd_dir
                inj_done: int32 = 0
                for o in range(4):
                    if oh_v[o] == 0:
                        if idir == o:
                            oh_p[o] = csd_pkt; oh_v[o] = 1; inj_done = 1
                        elif ig_v[o] == 1 and hit[o] == 0:
                            oh_p[o] = ig_p[o]; oh_v[o] = 1; ig_v[o] = 0
                if inj_done == 1: csd_pkt = 0

                crv_vld = o_crv[RQ_OFF]
                crv_data = o_crv[0 : Ty.bits].bitcast()
                crv_addr = o_crv[Ty.bits : Ty.bits + 4]
                crv_mode = o_crv[Ty.bits + 4]
                crv_raw  = o_crv[0 : Ty.bits]

                retire_ok: int32 = 1
                if sb_v[0] == 1 and sb_rtr[0] == 0 and sb_dst[0] >= 12:
                    if sb_rvld[0] == 1 and txp_v[sb_dst[0] & 3] == 1: retire_ok = 0
                if sb_v[0] == 1 and sb_rtr[0] == 1 and sb_inj[0] == 1:
                    if csd_pkt[RQ_OFF] == 1: retire_ok = 0
                if sb_v[0] == 1 and sb_rtr[0] == 0 and sb_dst[0] < 12:
                    if sb_rvld[0] == 1 and sb_dst[0] < DRF_DEPTH:
                        if ((dsmask >> sb_dst[0]) & 1) == 1:
                            if drf_full[sb_dst[0]] == 1: retire_ok = 0
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
                if pc >= 0 and DATADRIVEN == 1 and (a_vld == 0 or (binop == 1 and b_vld == 0)): grant = 0
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

                if grant == 1 and s1 < DRF_DEPTH and ((dsmask >> s1) & 1) == 1: drf_full[s1] = 0
                if grant == 1 and s2 < DRF_DEPTH and ((dsmask >> s2) & 1) == 1: drf_full[s2] = 0

                res: Ty = 0
                with allo.meta_if(IS_FLOAT):
                    bbits: UInt(DATA_W) = b.bitcast()
                    if op == OP_SUB: bbits = bbits ^ SIGNBIT
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
                with allo.meta_else():
                    if op == OP_ADD: res = a + b
                    elif op == OP_SUB: res = a - b
                    elif op == OP_MULT: res = a * b
                    elif op == OP_GEQ:
                        if a >= b: res = 1
                        else:      res = -1
                    elif op == OP_LT:
                        if a < b:  res = 1
                        else:      res = -1
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


                if crv_vld == 1 and crv_in >= 0:
                    accept: int32 = 1
                    if crv_mode == 0:
                        if ((crv_addr >> 2) & 3) == 3:
                            if txp_v[crv_addr & 3] == 1: accept = 0
                        elif crv_addr < DRF_DEPTH and ((dsmask >> crv_addr) & 1) == 1:
                            if drf_full[crv_addr] == 1: accept = 0
                    if accept == 1:
                        ig_v[crv_in] = 0
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
                            drf[crv_addr] = crv_data; drf_full[crv_addr] = 1
                        else:
                            # Option B (config-before-data fix): a register written by the router is
                            # FULL regardless of whether dsmask was known yet, so a pre-config delivery
                            # is a pending word instead of a silently dropped one (the rows-2,3,6,7 bug).
                            # INVARIANT: drf_full is cleared ONLY in the dsmask'd-consume path (grant);
                            # the CFG0 branch that sets dsmask must never touch drf_full.
                            drf[crv_addr] = crv_data; drf_full[crv_addr] = 1


        @df.kernel(mapping=[1], args=[in_w, iv_w])
        def drv_w(din_w: Ty[M, LANELEN], vd_w: int32[M, LANELEN]):
            sp: int32[M] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, M) as r:
                    if sp[r] < LANELEN:
                        if vd_w[r, sp[r]] == 0:
                            sp[r] += 1
                        elif sys_e[r, 0].full() == 0:
                            sys_e[r, 0].put(din_w[r, sp[r]].bitcast())
                            sp[r] += 1

        @df.kernel(mapping=[1], args=[in_e, iv_e])
        def drv_e(din_e: Ty[M, LANELEN], vd_e: int32[M, LANELEN]):
            sp: int32[M] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, M) as r:
                    if sp[r] < LANELEN:
                        if vd_e[r, sp[r]] == 0:
                            sp[r] += 1
                        elif sys_w[r, N].full() == 0:
                            sys_w[r, N].put(din_e[r, sp[r]].bitcast())
                            sp[r] += 1

        @df.kernel(mapping=[1], args=[in_n, iv_n])
        def drv_n(din_n: Ty[N, LANELEN], vd_n: int32[N, LANELEN]):
            sp: int32[N] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, N) as c:
                    if sp[c] < LANELEN:
                        if vd_n[c, sp[c]] == 0:
                            sp[c] += 1
                        elif sys_s[0, c].full() == 0:
                            sys_s[0, c].put(din_n[c, sp[c]].bitcast())
                            sp[c] += 1

        @df.kernel(mapping=[1], args=[in_s, iv_s])
        def drv_s(din_s: Ty[N, LANELEN], vd_s: int32[N, LANELEN]):
            sp: int32[N] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, N) as c:
                    if sp[c] < LANELEN:
                        if vd_s[c, sp[c]] == 0:
                            sp[c] += 1
                        elif sys_n[M, c].full() == 0:
                            sys_n[M, c].put(din_s[c, sp[c]].bitcast())
                            sp[c] += 1

        @df.kernel(mapping=[1], args=[out_w])
        def col_w(dout_w: Ty[M, LANELEN]):
            k: int32[M] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, M) as r:
                    if sys_w[r, 0].empty() == 0:
                        w: SDATA = sys_w[r, 0].get()
                        if k[r] < LANELEN:
                            dout_w[r, k[r]] = w.bitcast()
                            k[r] += 1

        @df.kernel(mapping=[1], args=[out_e])
        def col_e(dout_e: Ty[M, LANELEN]):
            k: int32[M] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, M) as r:
                    if sys_e[r, N].empty() == 0:
                        w: SDATA = sys_e[r, N].get()
                        if k[r] < LANELEN:
                            dout_e[r, k[r]] = w.bitcast()
                            k[r] += 1

        @df.kernel(mapping=[1], args=[out_n])
        def col_n(dout_n: Ty[N, LANELEN]):
            k: int32[N] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, N) as c:
                    if sys_n[0, c].empty() == 0:
                        w: SDATA = sys_n[0, c].get()
                        if k[c] < LANELEN:
                            dout_n[c, k[c]] = w.bitcast()
                            k[c] += 1

        @df.kernel(mapping=[1], args=[out_s])
        def col_s(dout_s: Ty[N, LANELEN]):
            k: int32[N] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, N) as c:
                    if sys_s[M, c].empty() == 0:
                        w: SDATA = sys_s[M, c].get()
                        if k[c] < LANELEN:
                            dout_s[c, k[c]] = w.bitcast()
                            k[c] += 1

        @df.kernel(mapping=[1], args=[rin_w])
        def rdrv_w(rdin_w: int32[M, LANELEN]):
            sp: int32[M] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, M) as r:
                    if sp[r] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_w[r, sp[r]]
                        if cand[RQ_OFF] == 0:
                            sp[r] += 1
                        elif rtr_e[r, 0].full() == 0:
                            rtr_e[r, 0].put(cand); sp[r] += 1

        @df.kernel(mapping=[1], args=[rin_e])
        def rdrv_e(rdin_e: int32[M, LANELEN]):
            sp: int32[M] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, M) as r:
                    if sp[r] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_e[r, sp[r]]
                        if cand[RQ_OFF] == 0:
                            sp[r] += 1
                        elif rtr_w[r, N].full() == 0:
                            rtr_w[r, N].put(cand); sp[r] += 1

        @df.kernel(mapping=[1], args=[rin_n])
        def rdrv_n(rdin_n: int32[N, LANELEN]):
            sp: int32[N] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, N) as c:
                    if sp[c] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_n[c, sp[c]]
                        if cand[RQ_OFF] == 0:
                            sp[c] += 1
                        elif rtr_s[0, c].full() == 0:
                            rtr_s[0, c].put(cand); sp[c] += 1

        @df.kernel(mapping=[1], args=[rin_s])
        def rdrv_s(rdin_s: int32[N, LANELEN]):
            sp: int32[N] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, N) as c:
                    if sp[c] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_s[c, sp[c]]
                        if cand[RQ_OFF] == 0:
                            sp[c] += 1
                        elif rtr_n[M, c].full() == 0:
                            rtr_n[M, c].put(cand); sp[c] += 1

        @df.kernel(mapping=[1], args=[rout_w])
        def rclc_w(rdout_w: int32[M, LANELEN]):
            k: int32[M] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, M) as r:
                    if rtr_w[r, 0].empty() == 0:
                        pw: Pkt = rtr_w[r, 0].get()
                        if pw[RQ_OFF] == 1 and k[r] < LANELEN:
                            rdout_w[r, k[r]] = pw & PMASK
                            k[r] += 1

        @df.kernel(mapping=[1], args=[rout_e])
        def rclc_e(rdout_e: int32[M, LANELEN]):
            k: int32[M] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, M) as r:
                    if rtr_e[r, N].empty() == 0:
                        pw: Pkt = rtr_e[r, N].get()
                        if pw[RQ_OFF] == 1 and k[r] < LANELEN:
                            rdout_e[r, k[r]] = pw & PMASK
                            k[r] += 1

        @df.kernel(mapping=[1], args=[rout_n])
        def rclc_n(rdout_n: int32[N, LANELEN]):
            k: int32[N] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, N) as c:
                    if rtr_n[0, c].empty() == 0:
                        pw: Pkt = rtr_n[0, c].get()
                        if pw[RQ_OFF] == 1 and k[c] < LANELEN:
                            rdout_n[c, k[c]] = pw & PMASK
                            k[c] += 1

        @df.kernel(mapping=[1], args=[rout_s])
        def rclc_s(rdout_s: int32[N, LANELEN]):
            k: int32[N] = 0
            for it in range(BUDGET):
                with allo.meta_for(0, N) as c:
                    if rtr_s[M, c].empty() == 0:
                        pw: Pkt = rtr_s[M, c].get()
                        if pw[RQ_OFF] == 1 and k[c] < LANELEN:
                            rdout_s[c, k[c]] = pw & PMASK
                            k[c] += 1

    return top


if __name__ == "__main__":
    import os, re
    M = N = int(os.environ.get("SIZE", 1))
    NSTEP = LANELEN = int(os.environ.get("L", 10))
    RUN_BUDGET = 6 * LANELEN

    s = df.customize(get_eva_top_elastic(float16))
    for i in range(M):
        for j in range(N):
            s.pipeline(f"node_{i}_{j}:it")
            for buf in "irf drf drf_full hold_v hold_cnt ig_p ig_v oh_p oh_v txp_d txp_v resq cmpq sb_v sb_dst sb_cmp sb_rtr sb_inj sb_dir sb_id sb_rvld sb_ix sb_long".split():
                s.partition(f"node_{i}_{j}:{buf}")
    for io in ("drv_w drv_e drv_n drv_s col_w col_e col_n col_s "
               "rdrv_w rdrv_e rdrv_n rdrv_s rclc_w rclc_e rclc_n rclc_s").split():
        s.pipeline(f"{io}_0:it")
    # 2026-08-17: partition the per-lane data ARG arrays (din/vd -> drv, dout -> col) complete dim=1
    # so all 8 lanes access in parallel — resolves the 8-lanes-2-ports limit that pins drv/col at II=4.
    for io in "drv_w drv_e drv_n drv_s".split():
        s.partition(f"{io}_0:din_{io[-1]}", dim=1)
        s.partition(f"{io}_0:vd_{io[-1]}", dim=1)
    for io in "col_w col_e col_n col_s".split():
        s.partition(f"{io}_0:dout_{io[-1]}", dim=1)

    P = f"prj_{M}x{N}"
    s.build(target="vhls", mode="csyn", project=P)

    src = open(f"{P}/kernel.cpp").read()
    src = re.sub(r"(union \{[^}]*\}\s*_converter\w*)\s*;", r"\1 = {};", src)
    assert MOV_LAT >= 1, "distance-2 dependence requires MOV_LAT>=1 (else BUG A)"
    # The distance-2 dependence MUST sit INSIDE each node loop, right after its
    # pipeline pragma. At function/array-declaration scope Vitis silently treats
    # it as a no-op, the res->resq recurrence is not waived, and the node loop
    # falls back to II=2 (the pragma is present with the right name but out of
    # scope). Split per node function, use that function's actual resq/cmpq
    # instance names, and insert after the node loop's pipeline pragma.
    parts = re.split(r"(?m)^(void node_[0-9]+_[0-9]+\()", src)
    ndep = 0
    for k in range(1, len(parts), 2):
        body = parts[k + 1]
        deps = ""
        for ring in ("resq", "cmpq"):
            mm = re.search(rf"\b({ring}\d*)\[", body)
            if mm:
                deps += (f"\n  #pragma HLS dependence variable={mm.group(1)} "
                         f"type=inter direction=RAW distance=2 dependent=true")
        if deps:
            body, n = re.subn(
                r"(l_S_(?:it|t)[a-z0-9_]*: for [^\n]*\n\s*#pragma HLS pipeline II=1)",
                lambda mm2: mm2.group(1) + deps, body, count=1)
            assert n == 1, "node loop pipeline anchor not found for dependence injection"
            ndep += 1
            parts[k + 1] = body
    src = "".join(parts)
    assert ndep == M * N, f"dependence injected into {ndep} node funcs, expected {M*N}"
    src = re.sub(r"half (\w+) = \w+ \* \w+;",
                 lambda m: m[0] + f"\n#pragma HLS bind_op variable={m[1]} op=hmul impl=maxdsp latency=2", src)
    src = re.sub(r"half (\w+) = \w+ \+ \w+;",
                 lambda m: m[0] + f"\n#pragma HLS bind_op variable={m[1]} op=hadd impl=fabric latency=2", src)
    open(f"{P}/kernel.cpp", "w").write(src)
    print("built", P, "— Allo pipeline+partition; injected:", 'dep+bind_op')
