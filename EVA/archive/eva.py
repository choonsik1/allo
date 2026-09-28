# eva.py — EVA accelerator: M×N mesh of fused router+PE nodes, always-fire/bubble model.
# Each node carries two overlaid 4-dir networks: systolic (data word) + router (packets).
# To change data type: change Ty.

import allo
from allo.ir.types import float16, int16, int32, UInt, AlloType, Stream, float32
import allo.dataflow as df
import numpy as np

M, N = 1, 1
NSTEP = 10
PROG_CYCLES = 0
INSTR_SIZE = 0
ITER_SIZE  = 1
DATADRIVEN = 1
DRF_DEPTH, IRF_DEPTH = 8, 8
BUF_DEPTH = 2
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
        sys_e: Stream[SYS_W, 8][M, N + 1]
        sys_w: Stream[SYS_W, 8][M, N + 1]
        sys_s: Stream[SYS_W, 8][M + 1, N]
        sys_n: Stream[SYS_W, 8][M + 1, N]
        rtr_e: Stream[Pkt, 8][M, N + 1]
        rtr_w: Stream[Pkt, 8][M, N + 1]
        rtr_s: Stream[Pkt, 8][M + 1, N]
        rtr_n: Stream[Pkt, 8][M + 1, N]
        cr_e: Stream[int32, 8][M, N + 1]
        cr_w: Stream[int32, 8][M, N + 1]
        cr_s: Stream[int32, 8][M + 1, N]
        cr_n: Stream[int32, 8][M + 1, N]

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

            oe_r: Pkt = 0; ow_r: Pkt = 0; on_r: Pkt = 0; os_r: Pkt = 0
            txn_r: SYS_W = 0; txs_r: SYS_W = 0; txw_r: SYS_W = 0; txe_r: SYS_W = 0
            
            hold_v: Ty[4, 2] = 0; hold_cnt: int32[4] = 0
            
            rbuf:  Pkt[4, BUF_DEPTH] = 0
            rbcnt: int32[4] = 0
            rcred: int32[4] = 0
            
            cre_r: int32 = BUF_DEPTH; crw_r: int32 = BUF_DEPTH
            crs_r: int32 = BUF_DEPTH; crn_r: int32 = BUF_DEPTH

            cfg_isz: int32 = 0
            cfg_itsz: int32 = 0
            fetch_en: int32 = 0
            instr_cnt: int32 = 0
            iter_cnt: int32 = 0
            condition_reg: int32 = 0

            # END-PUT prime (RTL deadlock fix, see bubble_model plan 07-05):
            # emit the t=0 outputs BEFORE the loop (regs hold init values
            # here: bubble pkts/words + BUF_DEPTH credits); the in-loop puts
            # move to the iteration END. Stream word sequences are BIT-
            # IDENTICAL to eva.py; every feedback edge starts with one token
            # so the RTL's read-before-write schedule cannot deadlock.
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

            for t in range(NSTEP):
                p_w: Pkt = rtr_e[i, j].get()
                p_e: Pkt = rtr_w[i, j + 1].get()
                p_n: Pkt = rtr_s[i, j].get()
                p_s: Pkt = rtr_n[i + 1, j].get()
                rcred[0] += cr_e[i, j + 1].get()
                rcred[1] += cr_w[i, j].get()
                rcred[2] += cr_s[i + 1, j].get()
                rcred[3] += cr_n[i, j].get()

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
                
                ret: int32[4] = 0
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
                grant: int32 = 0
                if pc >= 0: grant = 1
                if pc >= 0 and DATADRIVEN == 1 and (a_vld == 0 or (binop == 1 and b_vld == 0)): grant = 0
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
                if grant == 1 and op == OP_GEQ:
                    condition_reg = 0
                    if a >= b: condition_reg = 1
                if grant == 1 and op == OP_LT:
                    condition_reg = 0
                    if a < b: condition_reg = 1

                tx_n: SYS_W = 0; tx_s: SYS_W = 0
                tx_w: SYS_W = 0; tx_e: SYS_W = 0
                is_rtr: int32 = 0; do_inj: int32 = 0
                if op >= OP_RTR0 and op <= OP_RTR0 + 3: is_rtr = 1; do_inj = 1
                if op >= OP_CRTR0 and op <= OP_CRTR0 + 3:
                    is_rtr = 1
                    if condition_reg == 1: do_inj = 1
                if is_rtr == 1:
                    if do_inj == 1 and csd_pkt[RQ_OFF] == 0:
                        csd_pkt[0 : Ty.bits] = res.bitcast()
                        csd_pkt[Ty.bits : Ty.bits + 4] = dst
                        csd_pkt[Ty.bits + 5 : Ty.bits + 9] = s2
                        csd_pkt[RQ_OFF] = res_vld
                        csd_dir = op & 3

                elif dst >= 12:
                    tw: SYS_W = 0
                    tw[0] = res_vld
                    tw[1 : 1 + Ty.bits] = res.bitcast()
                    if   (dst & 3) == 0: tx_n = tw
                    elif (dst & 3) == 1: tx_s = tw
                    elif (dst & 3) == 2: tx_w = tw
                    else:               tx_e = tw
                    
                else:
                    if res_vld == 1:
                        if dst < DRF_DEPTH and ((dsmask >> dst) & 1) == 1:

                            if drf_full[dst] == 0:
                                drf[dst] = res; 
                                drf_full[dst] = 1
                        else:
                            drf[dst] = res

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
                    elif ((crv_addr >> 2) & 3) == 3:
                        # ROUTER DATA pkt to sys addr 0xC..0xF writes the SYSTOLIC TX
                        # (golden pe_core.sv:353; LDL `LMOV systop` injects the systolic
                        # stream this way). dir = crv_addr&3: 0=N,1=S,2=W,3=E. Written
                        # directly to txX_r (always-fire, no credit) after the tx_* copy above.
                        twc: SYS_W = 0
                        twc[0] = 1
                        twc[1 : 1 + Ty.bits] = crv_data.bitcast()
                        if   (crv_addr & 3) == 0: txn_r = twc
                        elif (crv_addr & 3) == 1: txs_r = twc
                        elif (crv_addr & 3) == 2: txw_r = twc
                        else:                     txe_r = twc
                    elif crv_addr < DRF_DEPTH and ((dsmask >> crv_addr) & 1) == 1:
                        if drf_full[crv_addr] == 0:
                            drf[crv_addr] = crv_data; drf_full[crv_addr] = 1
                    else:
                        drf[crv_addr] = crv_data

                # END-PUT prime: the 12 puts, moved verbatim from the loop
                # top — regs now hold this iteration's results, i.e. exactly
                # what the old scheme emitted at the NEXT iteration's top
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

        @df.kernel(mapping=[1], args=[in_w, iv_w])
        def drv_w(din_w: Ty[M, LANELEN], vd_w: int32[M, LANELEN]):
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    w: SYS_W = 0
                    if t < LANELEN:
                        w[0] = vd_w[r, t]
                        w[1 : 1 + Ty.bits] = din_w[r, t].bitcast()
                    sys_e[r, 0].put(w)

        @df.kernel(mapping=[1], args=[in_e, iv_e])
        def drv_e(din_e: Ty[M, LANELEN], vd_e: int32[M, LANELEN]):
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    w: SYS_W = 0
                    if t < LANELEN:
                        w[0] = vd_e[r, t]
                        w[1 : 1 + Ty.bits] = din_e[r, t].bitcast()
                    sys_w[r, N].put(w)

        @df.kernel(mapping=[1], args=[in_n, iv_n])
        def drv_n(din_n: Ty[N, LANELEN], vd_n: int32[N, LANELEN]):
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    w: SYS_W = 0
                    if t < LANELEN:
                        w[0] = vd_n[c, t]
                        w[1 : 1 + Ty.bits] = din_n[c, t].bitcast()
                    sys_s[0, c].put(w)

        @df.kernel(mapping=[1], args=[in_s, iv_s])
        def drv_s(din_s: Ty[N, LANELEN], vd_s: int32[N, LANELEN]):
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    w: SYS_W = 0
                    if t < LANELEN:
                        w[0] = vd_s[c, t]
                        w[1 : 1 + Ty.bits] = din_s[c, t].bitcast()
                    sys_n[M, c].put(w)

        @df.kernel(mapping=[1], args=[out_w])
        def col_w(dout_w: Ty[M, LANELEN]):
            k: int32[M] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    w: SYS_W = sys_w[r, 0].get()
                    if w[0] == 1 and k[r] < LANELEN:
                        dout_w[r, k[r]] = w[1 : 1 + Ty.bits].bitcast()
                        k[r] += 1

        @df.kernel(mapping=[1], args=[out_e])
        def col_e(dout_e: Ty[M, LANELEN]):
            k: int32[M] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    w: SYS_W = sys_e[r, N].get()
                    if w[0] == 1 and k[r] < LANELEN:
                        dout_e[r, k[r]] = w[1 : 1 + Ty.bits].bitcast()
                        k[r] += 1

        @df.kernel(mapping=[1], args=[out_n])
        def col_n(dout_n: Ty[N, LANELEN]):
            k: int32[N] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    w: SYS_W = sys_n[0, c].get()
                    if w[0] == 1 and k[c] < LANELEN:
                        dout_n[c, k[c]] = w[1 : 1 + Ty.bits].bitcast()
                        k[c] += 1

        @df.kernel(mapping=[1], args=[out_s])
        def col_s(dout_s: Ty[N, LANELEN]):
            k: int32[N] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    w: SYS_W = sys_s[M, c].get()
                    if w[0] == 1 and k[c] < LANELEN:
                        dout_s[c, k[c]] = w[1 : 1 + Ty.bits].bitcast()
                        k[c] += 1

        @df.kernel(mapping=[1], args=[rin_w])
        def rdrv_w(rdin_w: int32[M, LANELEN]):
            dcred: int32[M] = 0; sp: int32[M] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    dcred[r] += cr_e[r, 0].get()
                    pw: Pkt = 0
                    if sp[r] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_w[r, sp[r]]
                        if cand[RQ_OFF] == 0: sp[r] += 1
                        elif dcred[r] > 0: pw = cand; dcred[r] -= 1; sp[r] += 1
                    rtr_e[r, 0].put(pw)

        @df.kernel(mapping=[1], args=[rin_e])
        def rdrv_e(rdin_e: int32[M, LANELEN]):
            dcred: int32[M] = 0; sp: int32[M] = 0
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    dcred[r] += cr_w[r, N].get()
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
                    dcred[c] += cr_s[0, c].get()
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
                    dcred[c] += cr_n[M, c].get()
                    pw: Pkt = 0
                    if sp[c] < LANELEN:
                        cand: Pkt = 0
                        cand[0 : Ty.bits + 10] = rdin_s[c, sp[c]]
                        if cand[RQ_OFF] == 0: sp[c] += 1
                        elif dcred[c] > 0: pw = cand; dcred[c] -= 1; sp[c] += 1
                    rtr_n[M, c].put(pw)

        @df.kernel(mapping=[1], args=[rout_w])
        def rclc_w(rdout_w: int32[M, LANELEN]):
            k: int32[M] = 0
            cret: int32[M] = 0
            with allo.meta_for(0, M) as r:
                cret[r] = BUF_DEPTH
                cr_w[r, 0].put(cret[r])      # END-PUT prime: t=0 credit
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    pw: Pkt = rtr_w[r, 0].get()
                    cret[r] = 0
                    if pw[RQ_OFF] == 1:
                        cret[r] = 1
                        if k[r] < LANELEN:
                            rdout_w[r, k[r]] = pw & PMASK
                            k[r] += 1
                    cr_w[r, 0].put(cret[r])  # END-PUT: moved after the get
                              
        @df.kernel(mapping=[1], args=[rout_e])
        def rclc_e(rdout_e: int32[M, LANELEN]):
            k: int32[M] = 0; cret: int32[M] = 0
            with allo.meta_for(0, M) as r:
                cret[r] = BUF_DEPTH
                cr_e[r, N].put(cret[r])      # END-PUT prime: t=0 credit
            for t in range(NSTEP):
                with allo.meta_for(0, M) as r:
                    pw: Pkt = rtr_e[r, N].get()
                    cret[r] = 0
                    if pw[RQ_OFF] == 1:
                        cret[r] = 1
                        if k[r] < LANELEN:
                            rdout_e[r, k[r]] = pw & PMASK
                            k[r] += 1
                    cr_e[r, N].put(cret[r])  # END-PUT: moved after the get

        @df.kernel(mapping=[1], args=[rout_n])
        def rclc_n(rdout_n: int32[N, LANELEN]):
            k: int32[N] = 0; cret: int32[N] = 0
            with allo.meta_for(0, N) as c:
                cret[c] = BUF_DEPTH
                cr_n[0, c].put(cret[c])      # END-PUT prime: t=0 credit
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    pw: Pkt = rtr_n[0, c].get()
                    cret[c] = 0
                    if pw[RQ_OFF] == 1:
                        cret[c] = 1
                        if k[c] < LANELEN:
                            rdout_n[c, k[c]] = pw & PMASK
                            k[c] += 1
                    cr_n[0, c].put(cret[c])  # END-PUT: moved after the get

        @df.kernel(mapping=[1], args=[rout_s])
        def rclc_s(rdout_s: int32[N, LANELEN]):
            k: int32[N] = 0; cret: int32[N] = 0
            with allo.meta_for(0, N) as c:
                cret[c] = BUF_DEPTH
                cr_s[M, c].put(cret[c])      # END-PUT prime: t=0 credit
            for t in range(NSTEP):
                with allo.meta_for(0, N) as c:
                    pw: Pkt = rtr_s[M, c].get()
                    cret[c] = 0
                    if pw[RQ_OFF] == 1:
                        cret[c] = 1
                        if k[c] < LANELEN:
                            rdout_s[c, k[c]] = pw & PMASK
                            k[c] += 1
                    cr_s[M, c].put(cret[c])  # END-PUT: moved after the get

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
                for buf in ("irf", "drf", "drf_full", "rbuf", "rbcnt", "rcred", "hold_v", "hold_cnt"):
                    s.partition(f"node_{i}_{j}:{buf}")
    if pipeline_node:
        for i in range(M):
            for j in range(N):
                s.pipeline(f"node_{i}_{j}:t", initiation_interval=1)
    return s

if __name__ == "__main__":
    # BASELINE always-fire (II=4).  Params (module-level): M=N=1, NSTEP=10, Ty=float16.
    # Run:  python eva.py   then   cd prj_eva && vitis_hls -f run.tcl
    import os, re
    P = os.path.join(os.path.dirname(os.path.abspath(__file__)), "prj_eva")
    s = get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)
    s.build(target="vhls", mode="csyn", project=P)
    kp = os.path.join(P, "kernel.cpp"); src = open(kp).read()
    src = re.sub(r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} _converter\w*);", r"\1 = {};", src)
    open(kp, "w").write(src)
    print("generated HLS project at", P)
