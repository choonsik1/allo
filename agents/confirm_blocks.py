"""Confirm every stripped block builds on the simulator, called by its unique def name.
Blocks are grouped by packet width because a block's annotation constants (PS) resolve
via one shared namespace -> a single module must use ONE value per constant name
(real designs use one router variant, so this is fine). Run: `confirm_blocks.py <group>`
with group in {narrow23, wide24, eva, alu}.
"""
import os, sys
os.environ.setdefault("OMP_NUM_THREADS", "4")
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE); sys.path.insert(0, os.path.join(HERE, "noc"))
from allo.ir.types import int32, UInt, float16
import allo.dataflow as df

group = sys.argv[1] if len(sys.argv) > 1 else "narrow23"
CASES = []

if group == "narrow23":                       # PS=23 routers
    from router_XY_stripped import router_xy, PS, DIR
    from router_XY_rr_stripped import router_xy_rr

    @df.region()
    def t_xy(A: int32[DIR], B: int32[DIR]):
        @df.kernel(mapping=[1], args=[A, B])
        def k(la: int32[DIR], lb: int32[DIR]):
            pin: UInt(PS)[DIR] = 0; pout: UInt(PS)[DIR] = 0
            for d in range(DIR): pin[d] = la[d]
            router_xy(1, 1, pin, pout)
            for d in range(DIR): lb[d] = pout[d]

    @df.region()
    def t_rr(A: int32[DIR], B: int32[DIR]):
        @df.kernel(mapping=[1], args=[A, B])
        def k(la: int32[DIR], lb: int32[DIR]):
            pin: UInt(PS)[DIR] = 0; pout: UInt(PS)[DIR] = 0; rr: int32[DIR] = 0
            for d in range(DIR): pin[d] = la[d]
            router_xy_rr(1, 1, pin, pout, rr)
            for d in range(DIR): lb[d] = pout[d]
    CASES = [("router_xy", t_xy), ("router_xy_rr", t_rr)]

elif group == "wide24":                        # PS=24 routers
    from router_XY_PEs_stripped import router_xy_pes, PS, DIR
    from router_XY_PEs_bp_stripped import router_xy_bp, BUF_DEPTH
    from router_XY_PEs_bp_rr_stripped import router_xy_bp_rr

    @df.region()
    def t_pes(A: int32[DIR], B: int32[DIR]):
        @df.kernel(mapping=[1], args=[A, B])
        def k(la: int32[DIR], lb: int32[DIR]):
            pin: UInt(PS)[DIR] = 0; pout: UInt(PS)[DIR] = 0
            for d in range(DIR): pin[d] = la[d]
            router_xy_pes(1, 1, pin, pout)
            for d in range(DIR): lb[d] = pout[d]

    @df.region()
    def t_bp(A: int32[DIR], B: int32[DIR]):
        @df.kernel(mapping=[1], args=[A, B])
        def k(la: int32[DIR], lb: int32[DIR]):
            pin: UInt(PS)[DIR] = 0; cin: int32[DIR] = 0
            pout: UInt(PS)[DIR] = 0; cout: int32[DIR] = 0
            buf: UInt(PS)[DIR, BUF_DEPTH] = 0; bcnt: int32[DIR] = 0; cred: int32[DIR] = 0
            for d in range(DIR): pin[d] = la[d]; cin[d] = BUF_DEPTH
            router_xy_bp(1, 1, pin, cin, pout, cout, buf, bcnt, cred)
            for d in range(DIR): lb[d] = pout[d]

    @df.region()
    def t_bprr(A: int32[DIR], B: int32[DIR]):
        @df.kernel(mapping=[1], args=[A, B])
        def k(la: int32[DIR], lb: int32[DIR]):
            pin: UInt(PS)[DIR] = 0; cin: int32[DIR] = 0
            pout: UInt(PS)[DIR] = 0; cout: int32[DIR] = 0
            buf: UInt(PS)[DIR, BUF_DEPTH] = 0; bcnt: int32[DIR] = 0
            cred: int32[DIR] = 0; rr: int32[DIR] = 0
            for d in range(DIR): pin[d] = la[d]; cin[d] = BUF_DEPTH
            router_xy_bp_rr(1, 1, pin, cin, pout, cout, buf, bcnt, cred, rr)
            for d in range(DIR): lb[d] = pout[d]
    CASES = [("router_xy_pes", t_pes), ("router_xy_bp", t_bp), ("router_xy_bp_rr", t_bprr)]

elif group == "eva":
    from eva_blocks import eva_router, eva_pe, Pkt, Ty as ETy, BUF_DEPTH as EBD, IRF_DEPTH, DRF_DEPTH

    @df.region()
    def t_evar(A: int32[1]):
        @df.kernel(mapping=[1], args=[A])
        def k(la: int32[1]):
            pkt_in: Pkt[4] = 0; cred_in: int32[4] = 0
            inject_ready: int32[1] = 0; pkt_out: Pkt[4] = 0; cred_out: int32[4] = 0
            eject_word: Pkt[1] = 0; eject_vld: int32[1] = 0
            rbuf: Pkt[4, EBD] = 0; rbcnt: int32[4] = 0; rcred: int32[4] = 0
            csd_pkt: Pkt[1] = 0; csd_dir: int32[1] = 0
            eva_router(1, 1, pkt_in, cred_in, 0, 0, inject_ready, pkt_out, cred_out,
                       eject_word, eject_vld, 0, rbuf, rbcnt, rcred, csd_pkt, csd_dir)
            la[0] = eject_vld[0]

    @df.region()
    def t_evap(A: int32[1]):
        @df.kernel(mapping=[1], args=[A])
        def k(la: int32[1]):
            ext_val: ETy[4] = 0; ext_vld: int32[4] = 0; ext_consume: int32[4] = 0
            send_valid: int32[1] = 0; send_kind: int32[1] = 0; send_dir: int32[1] = 0
            send_data: ETy[1] = 0; send_dst: int32[1] = 0; send_id: int32[1] = 0
            irf: int32[IRF_DEPTH] = 0; drf: ETy[DRF_DEPTH] = 0
            drf_full: int32[DRF_DEPTH] = 0; ctl: int32[7] = 0
            wd: ETy = 0                              # float param (not int literal)
            eva_pe(0, 0, ext_val, ext_vld, 0, 0, 0, wd, 0, 0,
                   ext_consume, send_valid, send_kind, send_dir, send_data, send_dst, send_id,
                   irf, drf, drf_full, ctl)
            la[0] = send_valid[0]
    CASES = [("eva_router", t_evar), ("eva_pe", t_evap)]

elif group == "alu":
    from pe_alu import alu_pe

    @df.region()
    def t_alu(A: float16[2], B: float16[1]):
        @df.kernel(mapping=[1], args=[A, B])
        def k(la: float16[2], lb: float16[1]):
            r: float16 = alu_pe(la[0], la[1], 2)
            lb[0] = r
    CASES = [("alu_pe", t_alu)]

for name, top in CASES:
    try:
        df.build(top, target="simulator")
        print(f"OK   {name}")
    except Exception as e:
        msg = [getattr(d, 'message', d) for d in (getattr(e, 'error_diagnostics', None) or [])][:1]
        print(f"FAIL {name}: {type(e).__name__} {msg}")
