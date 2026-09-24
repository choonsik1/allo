# Copyright Allo authors. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

"""An RV32I soft processor as an Allo stream IP.

The IP (``rv_stream_ip.cpp``) is anjn/vhls-riscv with memory-mapped stream
ports: the RISC-V program issues `lw` from MMIO_IN and `sw` to MMIO_OUT, and
those become `hls::stream` read/write. So the sums below are computed by a
processor executing machine code, not by a fixed-function datapath -- the
dataflow region just feeds and drains it.

Milestone 1 of wiring the processor to the EVA PE grid: prove the IP survives
parse -> build -> hoist -> csynth in a plain region before facing the grid's
mapping=[M,N] kernels and stream arrays.
"""

from pathlib import Path
import numpy as np
import pytest

import allo
from allo.ir.types import int32, Stream
import allo.dataflow as df
import allo.backend.hls as hls

# NOT `N`: the EVA chips read module-level M/N for the grid shape, and Allo
# resolves a traced region's globals through the calling frames. A bare `N`
# here silently overrode the chip's N -- building a 2x32 grid instead of 2x2
# (136k lines of HLS) when this file is run as __main__.
VADD_N = 32
_IMPL = Path(__file__).resolve().parent / "rv_stream_ip.cpp"


def _make_ip():
    # The IP reads sin (arg 0) and writes sout (arg 1). C++ cannot express that
    # -- both are `hls::stream<int32_t>&` -- so the direction is declared here.
    return allo.IPModule(
        top="rv_stream_ip",
        impl=_IMPL,
        link_hls=False,
        input_idx=[0],
        output_idx=[1],
    )


def _build_region(rv_stream_ip):
    @df.region()
    def top(A: int32[VADD_N], B: int32[VADD_N], C: int32[VADD_N]):
        sIn: Stream[int32, 4]
        sOut: Stream[int32, 4]

        # Interleaved a,b,a,b... -- the order the program's two `lw`s consume.
        @df.kernel(mapping=[1], args=[A, B])
        def feed(a: int32[VADD_N], b: int32[VADD_N]):
            for i in range(VADD_N):
                sIn.put(a[i])
                sIn.put(b[i])

        # The IP needs its own kernel: its stream ports block, so it must be its
        # own concurrent process rather than share one with the feeder.
        @df.kernel(mapping=[1])
        def rv_wrap():
            rv_stream_ip(sIn, sOut)

        @df.kernel(mapping=[1], args=[C])
        def drain(c: int32[VADD_N]):
            for i in range(VADD_N):
                c[i] = sOut.get()

    return top


def test_rv_stream_ip_codegen():
    """The processor reaches the emitted HLS with stream ports intact."""
    top = _build_region(_make_ip())
    import tempfile

    with tempfile.TemporaryDirectory() as tmpdir:
        mod = df.build(top, target="vitis_hls", mode="csyn", project=tmpdir)
        code = mod.hls_code
        assert "hls::stream< int32_t >&" in code
        assert "rv_stream_ip(" in code
        assert (Path(tmpdir) / "rv_stream_ip.cpp").exists()
        assert '#include "rv_stream_ip.cpp"' in (
            Path(tmpdir) / "kernel.cpp"
        ).read_text()


@pytest.mark.skipif(
    not hls.is_available("vitis_hls"), reason="vitis_hls not on PATH"
)
def test_rv_stream_ip_csynth():
    """The whole region -- feeder, processor, drain -- synthesizes."""
    top = _build_region(_make_ip())
    import tempfile

    with tempfile.TemporaryDirectory() as tmpdir:
        mod = df.build(top, target="vitis_hls", mode="csyn", project=tmpdir)
        mod()


# --------------------------------------------------------------------------
# Milestone 2: the processor programs the EVA PE.
#
# The IP replaces rdrv_w, the kernel that injects router packets at the array's
# west edge. Instead of replaying a host-supplied packet array it emits its own
# boot sequence -- load the PE's instruction register file, load two operands
# into its data register file, set the iteration count, set fetch_en -- so the
# PE ends up executing code the processor gave it.
# --------------------------------------------------------------------------


def _build_eva_1x1():
    """The leanalu chip at M=N=1 with the processor driving the west router."""
    import eva_fp16_skid as chip
    from allo.ir.types import float16

    chip.M, chip.N = 1, 1
    # These must match the values baked into the IP's ROM: the program's loop
    # trip counts are constants, so a mismatch deadlocks rather than fails.
    # NSTEP=100: the PE needs ~80 steps at 1x1 to receive the 12 boot packets,
    # execute, and drain through the scoreboard and credit-gated systolic port.
    # Verified on Allo's CPU simulator against the stock chip -- 40 yields
    # nothing at all, and so does the chip's own golden MMM workload.
    chip.NSTEP = 100
    chip.PRIME_TOKENS = 6
    chip.STREAM_DEPTH = 8
    chip.LANELEN = chip.NSTEP

    chip.RV_PROGRAMMER = allo.IPModule(
        top="rv_eva_programmer",
        impl=_IMPL,
        link_hls=False,
        input_idx=[0],   # cr_in  -- link credits from the array
        output_idx=[1],  # rtr_out -- router packets into the array
    )
    # Do NOT clear RV_PROGRAMMER afterwards: the region body is traced during
    # the build, not here, so the name has to still resolve then.
    #
    # get_scheduled_eva + target="vhls" is the chip's own flow (see its gen.py).
    # It matters: target="vitis_hls" additionally enforces "output arguments must
    # appear at the end", which this region violates with or without the IP --
    # the stock chip fails that check at 1x1 too.
    return chip.get_scheduled_eva(float16, pipeline_node=True, partition_rf=True)


def test_eva_1x1_programmed_by_processor_codegen():
    """The IP survives hoisting next to the grid's mapping=[M,N] node kernel."""
    import tempfile

    s = _build_eva_1x1()
    with tempfile.TemporaryDirectory() as tmpdir:
        mod = s.build(target="vhls", mode="csyn", project=tmpdir)
        code = open(Path(tmpdir) / "kernel.cpp").read()
        # The processor's ports carry EVA's own stream element types.
        assert "hls::stream< ap_uint<26> >&" in code, "router packet port"
        assert "rv_eva_programmer(" in code
        assert (Path(tmpdir) / "rv_stream_ip.cpp").exists()


@pytest.mark.skipif(
    not hls.is_available("vitis_hls"), reason="vitis_hls not on PATH"
)
def test_eva_1x1_programmed_by_processor_csynth():
    """The whole array -- processor, PE, drivers, collectors -- synthesizes."""
    import tempfile

    s = _build_eva_1x1()
    with tempfile.TemporaryDirectory() as tmpdir:
        mod = s.build(target="vhls", mode="csyn", project=tmpdir)
        mod()


# --------------------------------------------------------------------------
# Milestone 3: the processor feeds EVA's own driver, at 2x2.
#
# More faithful than milestone 2. There the processor replaced rdrv_w and had
# to implement EVA's credit protocol itself; here it only produces the program
# image, and the stock driver buffers it into a local array and replays it.
# That is the split between a host and the array. One processor drives every
# west lane -- see rvprog in the chip for why it is not one per lane.
# --------------------------------------------------------------------------


def _build_eva_2x2_fed(scheduled=False):
    """The 2x2 grid with one processor feeding both west lanes' drivers.

    scheduled=True applies the 1x1 schedule (node loop at II=1, register-file
    buffers partitioned). It is off by default because that schedule made 2x2
    unsynthesizable on Vitis 2023.2; on 2025.1 both build, so the flag exists to
    measure what II=1 costs in timing.
    """
    import eva_fp16_skid_drv as chip
    from allo.ir.types import float16

    chip.M, chip.N = 2, 2
    # 12 packets per node (8 IRF + 2 DRF + 2 config) x N columns per lane, and
    # NSTEP long enough for all of them to land, execute and drain. Both must
    # match the IP's ROM -- see rv_stream_ip.cpp, PKTSRC_NPKT.
    chip.NPKT = 24
    chip.NSTEP = 200
    chip.PRIME_TOKENS = 6
    chip.STREAM_DEPTH = 8
    chip.LANELEN = chip.NSTEP

    chip.RV_PKTSRC = allo.IPModule(
        top="rv_eva_pktsrc",
        impl=_IMPL,
        link_hls=False,
        input_idx=[],        # pure producer -- no input stream at all
        output_idx=[0, 1],   # one program-image stream per west lane
    )
    # NOT pipeline_node/partition_rf, unlike the 1x1 builds above. This matches
    # build_prime.py, which is the chip's own multi-node flow (SZ defaults to 4).
    # With the 1x1 schedule, 2x2 fails pre-synthesis on
    #   "Non-shared array 'prime_cfg' failed dataflow checking: it can only have
    #    a single reader and a single writer"
    # because prime_cfg is a top-level int32[M,N] read by all 21 kernels. At 1x1
    # it is [1][1] and gets optimised to a scalar, so the problem is invisible
    # there. The stock chip fails identically at 2x2 with the 1x1 schedule, so
    # this is the chip's constraint, not the processor's.
    return chip.get_scheduled_eva(
        float16, pipeline_node=scheduled, partition_rf=scheduled
    )


def test_eva_2x2_fed_by_processor_codegen():
    """Four PEs, two processors, and the grid's own drivers in between."""
    import tempfile

    s = _build_eva_2x2_fed()
    with tempfile.TemporaryDirectory() as tmpdir:
        mod = s.build(target="vhls", mode="csyn", project=tmpdir)
        code = open(Path(tmpdir) / "kernel.cpp").read()
        assert "rv_eva_pktsrc(" in code
        # ONE processor drives both lanes -- see rvprog's meta_if in the chip.
        assert code.count("rv_eva_pktsrc(") == 1, "expected a single IP call"
        assert (Path(tmpdir) / "rv_stream_ip.cpp").exists()


@pytest.mark.skipif(
    not hls.is_available("vitis_hls"), reason="vitis_hls not on PATH"
)
def test_eva_2x2_fed_by_processor_csynth():
    """The whole 2x2 array plus both processors synthesizes."""
    import tempfile

    s = _build_eva_2x2_fed()
    with tempfile.TemporaryDirectory() as tmpdir:
        mod = s.build(target="vhls", mode="csyn", project=tmpdir)
        mod()


# --------------------------------------------------------------------------
# Milestone 4: a real workload.
#
# Everything above boots a PE to compute 1.0 + 2.0 -- enough to prove the
# plumbing, not that it is useful. Here the processor boots the PE with EVA's
# golden weight-stationary MMM kernel and a stationary weight, and the array
# multiplies a stream of activations against it. Same arrangement as milestone
# 3 (the processor feeds EVA's own driver); only the ROM differs.
#
# The processor supplies the program and the weight. Activations are the host's
# job -- they arrive on the west systolic edge at PROG_CYCLES + 4*b -- which is
# the correct split: a host does not tell the array how to keep time.
# --------------------------------------------------------------------------

MMM_WEIGHT = 3.0
MMM_ACTIVATIONS = (2.0, 4.0, 1.0)     # -> out_s = [6, 12, 3]
MMM_PROG_CYCLES = 16                  # first activation lands here
MMM_KLEN = 4


def _build_eva_mmm_1x1():
    """1x1 grid whose PE is booted by the processor to run the MMM kernel."""
    import eva_fp16_skid_drv as chip
    from allo.ir.types import float16

    chip.M, chip.N = 1, 1
    # 11 packets: 8 IRF + 1 DRF (the weight) + 2 config. Must equal the IP's
    # MMMSRC_NPKT -- the producer and the driver both loop on it as a constant,
    # so a mismatch deadlocks rather than fails.
    chip.NPKT = 11
    chip.NSTEP = 200
    chip.PRIME_TOKENS = 6
    chip.STREAM_DEPTH = 8
    chip.LANELEN = chip.NSTEP

    chip.RV_PKTSRC = allo.IPModule(
        top="rv_eva_mmm_src",
        impl=_IMPL,
        link_hls=False,
        input_idx=[],
        output_idx=[0],
    )
    return chip.get_scheduled_eva(
        float16, pipeline_node=False, partition_rf=False
    )


def test_eva_mmm_1x1_codegen():
    """The MMM processor reaches the emitted HLS."""
    import tempfile

    s = _build_eva_mmm_1x1()
    with tempfile.TemporaryDirectory() as tmpdir:
        mod = s.build(target="vhls", mode="csyn", project=tmpdir)
        code = open(Path(tmpdir) / "kernel.cpp").read()
        assert "rv_eva_mmm_src(" in code
        assert (Path(tmpdir) / "rv_stream_ip.cpp").exists()


MMM2X2_W = ((1.0, 3.0), (5.0, 7.0))          # node (i,j) holds W[i][j]
MMM2X2_X = ((2.0, 4.0), (1.0, 3.0), (5.0, 2.0))
# -> out_s column j = [22,16,15] for j=0 and [34,24,29] for j=1


def _build_eva_mmm_2x2():
    """2x2 grid running a real matrix product, programmed by one processor.

    Unlike the 2x2 add, the two west lanes carry DIFFERENT images here: each
    node holds its own stationary weight. That is what the two-output-stream IP
    is for -- meta_for would give every lane the same ROM.
    """
    import eva_fp16_skid_drv as chip
    from allo.ir.types import float16

    chip.M, chip.N = 2, 2
    chip.NPKT = 22          # 2 nodes x 11 packets, per lane; == MMMSRC2_NPKT
    chip.NSTEP = 400
    chip.PRIME_TOKENS = 6
    chip.STREAM_DEPTH = 8
    chip.LANELEN = chip.NSTEP

    chip.RV_PKTSRC = allo.IPModule(
        top="rv_eva_mmm_src_2x2",
        impl=_IMPL,
        link_hls=False,
        input_idx=[],
        output_idx=[0, 1],
    )
    return chip.get_scheduled_eva(
        float16, pipeline_node=False, partition_rf=False
    )


def test_eva_mmm_2x2_codegen():
    """One processor, two lanes, four PEs running a matrix product."""
    import tempfile

    s = _build_eva_mmm_2x2()
    with tempfile.TemporaryDirectory() as tmpdir:
        mod = s.build(target="vhls", mode="csyn", project=tmpdir)
        code = open(Path(tmpdir) / "kernel.cpp").read()
        assert "rv_eva_mmm_src_2x2(" in code
        # ONE processor instance, not one per lane.
        assert code.count("rv_eva_mmm_src_2x2(") == 1


# --------------------------------------------------------------------------
# Emitting a cosim-able project.
#
# The tests above build into temp dirs, which is right for pytest but leaves
# nothing to run csynth/cosim against. This does the whole recipe: build, patch
# the source the way the chip's own flow does, and write the .ini.
#
#     python test_rv_stream_ip.py emit {1x1|2x2|2x2s|mmm|mmm2x2}
#
# The testbench is the shared tb_top.cpp, selected by a -DTARGET_* flag, so
# a project directory contains only generated files and can be deleted.
#
# then, from the project directory:
#
#     source /opt/xilinx/Vitis/2025.1/Vitis/settings64.sh
#     v++ -c --mode hls --config cosim_rv.ini --work_dir cosim_work
#     vitis-run --mode hls --cosim --config cosim_rv.ini --work_dir cosim_work
#
# USE VITIS 2025.1, NOT 2023.2, for anything above 1x1. prime_cfg is a
# top-level int32[M,N] read by all 21 kernels, and 2023.2's dataflow checker
# rejects that outright:
#     [HLS 200-779] Non-shared array '...' failed dataflow checking: it can
#     only have a single reader and a single writer
# 2025.1 handles it by generating a Block_entry_<arg>_rd_proc broadcast reader.
# At 1x1 the array is [1][1] and gets optimised to a scalar, which is the only
# reason 2023.2 works there. This is not caused by the IP -- the stock chip and
# the base eva_sb_syscredit_rtprime chip fail identically on 2023.2 at 2x2.
# Things that do NOT fix it, all tried: s.partition("prime_cfg") (wrong target
# format, and the chip's own build_prime.py swallows the exception, so it has
# never taken effect), s.partition("top:prime_cfg") (emits no pragma),
# "#pragma HLS stable", and build_prime.py's pipeline_node/partition_rf=False.
# --------------------------------------------------------------------------

_PART = "xczu7ev-ffvc1156-2-e"
_CLK = "3.333"


def emit_project(which="1x1"):
    """Write a synthesis/cosim-ready project. Returns its path."""
    import re

    here = Path(__file__).resolve().parent
    # (builder, project dir, testbench -D flag)
    targets = {
        "1x1":    (_build_eva_1x1,   "eva_rv.prj",       "TARGET_ADD1X1"),
        "2x2":    (_build_eva_2x2_fed, "eva_rv2x2.prj",  "TARGET_ADD2X2"),
        "2x2s":   (lambda: _build_eva_2x2_fed(scheduled=True),
                                     "eva_rv2x2s.prj",   "TARGET_ADD2X2"),
        "mmm":    (_build_eva_mmm_1x1, "eva_rvmmm.prj",  "TARGET_MMM1X1"),
        "mmm2x2": (_build_eva_mmm_2x2, "eva_rvmmm2x2.prj", "TARGET_MMM2X2"),
    }
    if which not in targets:
        raise ValueError(
            f"unknown target {which!r} (use {'/'.join(targets)})"
        )
    build, dirname, tbflag = targets[which]
    s, prj = build(), here / dirname

    s.build(target="vhls", mode="csyn", project=str(prj))

    # A union whose member has a non-trivial constructor (half) needs an
    # explicit initializer or the C++ testbench fails to compile. The chip's
    # own gen.py applies exactly this patch.
    kp = prj / "kernel.cpp"
    src, n = re.subn(
        r"(union \{ (?:uint16_t from; half to|half from; uint16_t to);\} "
        r"_converter\w*);",
        r"\1 = {};",
        kp.read_text(),
    )
    kp.write_text(src)

    # One shared testbench for every design, selected by -DTARGET_*. It stays in
    # the source directory, so a project dir holds only generated files.
    tb = here / "tb_top.cpp"
    (prj / "cosim_rv.ini").write_text(
        f"part={_PART}\n\n[hls]\nflow_target=vivado\nclock={_CLK}\n"
        f"syn.top=top\nsyn.file={kp}\ntb.file={tb}\n"
        f"tb.cflags=-DALLOW_EMPTY_HLS_STREAM_READS -D{tbflag}\n"
        f"syn.cflags=-DALLOW_EMPTY_HLS_STREAM_READS\n"
        f"syn.compile.pipeline_loops=0\n"
    )
    print(f"emitted {prj}  ({n} unions patched, {tbflag})")
    print("  build with Vitis 2025.1 -- see the note above")
    return prj


if __name__ == "__main__":
    import sys

    if len(sys.argv) > 1 and sys.argv[1] == "emit":
        emit_project(sys.argv[2] if len(sys.argv) > 2 else "1x1")
        raise SystemExit(0)

    test_rv_stream_ip_codegen()
    print("codegen OK")
    test_eva_1x1_programmed_by_processor_codegen()
    print("eva codegen OK")
    test_eva_2x2_fed_by_processor_codegen()
    print("eva 2x2 fed codegen OK")
    if hls.is_available("vitis_hls"):
        test_rv_stream_ip_csynth()
        print("csynth OK")
        test_eva_1x1_programmed_by_processor_csynth()
        print("eva csynth OK")
