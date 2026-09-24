"""Build an EVA chip whose boot-packet source is the DRIM4HLS RISC-V core.

    python build_eva_chip.py [--2x2] [<project-dir>]

With no project dir the generated SystemC goes to stdout; with one, Allo writes
a full Catapult project there (sources, run.tcl, and ip_directives.tcl).

The chip module itself is unmodified: `RV_PKTSRC` is the hook it already
exposes for "something that emits boot packets", and here that something is a
processor rather than a generated kernel.
"""
import sys

sys.path.insert(0, "/home/zsm9/allo_ipwork")
sys.path.insert(0, "/home/zsm9/final_ip_integration/ip")
import allo
import allo.dataflow as df
from allo.ir.types import float16
import eva_fp16_skid_drv as chip

HERE = "/home/zsm9/final_ip_integration/drim_cat"
TWO_LANE = "--2x2" in sys.argv
args = [a for a in sys.argv[1:] if not a.startswith("--")]

# Each PE needs 11 boot packets, so NPKT scales with the number of PEs one core
# feeds -- 2 per lane at 2x2. NSTEP is the activation count, and LANELEN must
# match it or the skid buffers are sized for the wrong run length.
chip.M, chip.N = (2, 2) if TWO_LANE else (1, 1)
chip.NPKT = 22 if TWO_LANE else 11
chip.NSTEP = 400 if TWO_LANE else 200
chip.PRIME_TOKENS = 6
chip.STREAM_DEPTH = 8
chip.LANELEN = chip.NSTEP

chip.RV_PKTSRC = allo.IPModule(
    # One top per arity. drim_eva drives two packet lanes; drim_eva1 wraps it and
    # exposes one, because the chip calls the IP with a single argument at M == 1
    # and a two-port IP does not match that call.
    top="drim_eva" if TWO_LANE else "drim_eva1",
    impl=f"{HERE}/drim_eva.h",
    # Verbatim from upstream's core/hls_to_synth.tcl. These do not travel with
    # the IP on their own: instantiated in a design the paths change from
    # /drim4hls/... to /top/..., and without them decode_th fails with "could
    # not schedule even with unlimited resources" because its register file is
    # inferred as a RAM. Allo re-roots them into <project>/ip_directives.tcl.
    sc_directives=[
        "/drim4hls/decode/sentinel.rom:rsc          -MAP_TO_MODULE {[Register]}",
        "/drim4hls/decode/decode_th/regfile:rsc     -MAP_TO_MODULE {[Register]}",
        "/drim4hls/decode/decode_th/sentinel:rsc    -MAP_TO_MODULE {[Register]}",
        "/drim4hls/execute/csr.rom:rsc              -MAP_TO_MODULE {[Register]}",
        "/drim4hls/execute/execute_th/csr:rsc       -MAP_TO_MODULE {[Register]}",
    ],
)

top = chip.get_eva_top(float16)
if args:
    df.build(top, target="systemc", mode="csim", project=args[0])
    print("project written to", args[0])
else:
    print(df.build(top, target="systemc").hls_code)
