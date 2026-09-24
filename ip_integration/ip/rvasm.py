#!/usr/bin/env python3
"""A minimal RV32I assembler -- just enough to build the stream-IP test program.

Hand-encoding instructions as hex is easy to get subtly wrong and impossible to
review, and there is no RISC-V toolchain on this machine. This encodes the five
instruction formats we need (J-type is absent -- nothing here uses `jal`), and
`disasm_fields` re-decodes a word so a test can assert the encoding round-trips.
"""

# Register names -> numbers (only the ones the programs use).
REGS = {
    "x0": 0, "zero": 0,
    "t0": 5, "t1": 6, "t2": 7, "t3": 28,
    "a0": 10, "a1": 11, "a2": 12, "a3": 13, "a4": 14,
    "s0": 8, "s1": 9, "s2": 18,
}


# ---- Why this layer exists -----------------------------------------------
# None of it is part of the processor. `rv/kernel.cpp` is unmodified hardware
# that decodes whatever 32-bit words it finds in memory; this is the toolchain
# that produces those words. Upstream vhls-riscv loaded prebuilt riscv-tests
# .hex files through a `mem[]` port, but making the core a stream IP deleted
# that port -- the program now lives in a ROM baked in at compile time -- and
# no off-the-shelf program emits EVA router packets anyway. With no RISC-V
# toolchain on this machine, the words have to be built here.


def _r(name):
    """Resolve an ABI register name to its number.

    Exists so programs can say `ADDI("t3", "t0", 4)` instead of
    `ADDI(28, 5, 4)`, and so a typo raises instead of silently encoding x0.
    The numbering is irregular (t3=28, s2=18), which is exactly why it is a
    lookup table and not arithmetic.
    """
    if isinstance(name, int):
        return name
    if name not in REGS:
        raise KeyError(f"unknown register {name!r}; known: {sorted(REGS)}")
    return REGS[name]


def _chk(val, bits, signed):
    """Range-check an immediate and mask it to its field width.

    Exists because an out-of-range immediate would otherwise be silently
    truncated into a valid-looking instruction that does the wrong thing --
    the single easiest way to produce a program that is impossible to debug.
    Masking is also what turns a negative offset into two's complement.
    """
    lo, hi = (-(1 << (bits - 1)), (1 << (bits - 1)) - 1) if signed else (0, (1 << bits) - 1)
    if not lo <= val <= hi:
        raise ValueError(f"immediate {val} does not fit in {bits} bits (signed={signed})")
    return val & ((1 << bits) - 1)


# The five instruction formats. Each exists because RV32I places the same
# logical operand in a different bit position depending on the format, so the
# packing has to be written once per format and reused -- doing it per
# instruction is where hand-encoding goes wrong.

def r_type(funct7, rs2, rs1, funct3, rd, opcode):
    """Register-register ops. No immediate, so every field is contiguous."""
    return (funct7 << 25) | (_r(rs2) << 20) | (_r(rs1) << 15) | (funct3 << 12) | (_r(rd) << 7) | opcode


def i_type(imm, rs1, funct3, rd, opcode):
    """Register-immediate ops and loads. 12-bit signed immediate, one piece."""
    return (_chk(imm, 12, True) << 20) | (_r(rs1) << 15) | (funct3 << 12) | (_r(rd) << 7) | opcode


def s_type(imm, rs2, rs1, funct3, opcode):
    """Stores. The immediate is SPLIT: a store has no rd, so RISC-V reuses that
    field for the low 5 bits and keeps rs1/rs2/funct3 where every format has
    them."""
    i = _chk(imm, 12, True)
    return ((i >> 5) << 25) | (_r(rs2) << 20) | (_r(rs1) << 15) | (funct3 << 12) | ((i & 0x1F) << 7) | opcode


def b_type(imm, rs2, rs1, funct3, opcode):
    """Branches. The offset is scrambled across four discontiguous fields and
    bit 0 is implicit (offsets are even), which is why this is the format most
    worth having encoded once and tested."""
    if imm % 2:
        raise ValueError("branch offset must be even")
    i = _chk(imm, 13, True)
    return (
        (((i >> 12) & 1) << 31) | (((i >> 5) & 0x3F) << 25) | (_r(rs2) << 20)
        | (_r(rs1) << 15) | (funct3 << 12) | (((i >> 1) & 0xF) << 8)
        | (((i >> 11) & 1) << 7) | opcode
    )


def u_type(imm20, rd, opcode):
    """Upper-immediate ops. 20 bits landing in the top of the register, which
    is how a full 32-bit address like 0x8000 gets built in one instruction."""
    return (_chk(imm20, 20, False) << 12) | (_r(rd) << 7) | opcode


# The nine instructions the programs actually use -- each is one format call
# with the opcode/funct bits filled in, so a program reads as assembly.
def LUI(rd, imm20):      return u_type(imm20, rd, 0b0110111)      # build an MMIO base address
def ADDI(rd, rs1, imm):  return i_type(imm, rs1, 0b000, rd, 0b0010011)   # offsets, counters, constants
def ADD(rd, rs1, rs2):   return r_type(0b0000000, rs2, rs1, 0b000, rd, 0b0110011)  # sums, table indexing
def LW(rd, rs1, imm):    return i_type(imm, rs1, 0b010, rd, 0b0000011)   # stream READ when rs1 is MMIO
def SW(rs2, rs1, imm):   return s_type(imm, rs2, rs1, 0b010, 0b0100011)  # stream WRITE when rs1 is MMIO
def BNE(rs1, rs2, off):  return b_type(off, rs2, rs1, 0b001, 0b1100011)  # the loop back-edge
def ANDI(rd, rs1, imm):  return i_type(imm, rs1, 0b111, rd, 0b0010011)   # extract a valid bit
def BGE(rs1, rs2, off):  return b_type(off, rs2, rs1, 0b101, 0b1100011)  # "no packets left" / "no credit"
def SLLI(rd, rs1, sh):   return i_type(_chk(sh, 5, False), rs1, 0b001, rd, 0b0010011)  # index*4 for a word table


def disasm_fields(word):
    """Re-decode a word into its raw fields, for round-trip assertions.

    Exists so a test can check that an encoding survives encode -> decode
    unchanged, rather than trusting the shift-and-or by inspection.
    """
    return {
        "opcode": word & 0x7F,
        "rd": (word >> 7) & 0x1F,
        "funct3": (word >> 12) & 0x7,
        "rs1": (word >> 15) & 0x1F,
        "rs2": (word >> 20) & 0x1F,
        "funct7": (word >> 25) & 0x7F,
    }


# Memory-mapped stream ports. All sit above MEM_SIZE so they can never alias
# real memory; the core branches on the address before touching local_mem.
# Keep in sync with the same constants in rv_stream_ip.cpp.
MMIO_IN = 0x8000       # load  -> int32 input stream
MMIO_OUT = 0x8004      # store -> int32 output stream
MMIO_IN17 = 0x8008     # load  -> ap_uint<17> input stream (EVA systolic word)
MMIO_OUT17 = 0x800C    # store -> ap_uint<17> output stream
MMIO_OUT26 = 0x8010    # store -> ap_uint<26> output stream (EVA router packet)
MMIO_OUT26B = 0x8014   # store -> second router packet stream (west lane 1)


def vadd_program(n):
    """`n` iterations of: read two words from the input stream, write their sum.

    t0 = MMIO_IN, t1 = MMIO_OUT, t2 = loop counter.
    Returns (words, halt_pc).
    """
    prog = [
        LUI("t0", MMIO_IN >> 12),        # 0x00  t0 = 0x8000
        ADDI("t1", "t0", 4),             # 0x04  t1 = 0x8004
        ADDI("t2", "x0", n),             # 0x08  t2 = n
        # loop (0x0c):
        LW("a0", "t0", 0),               # 0x0c  a0 = stream.read()
        LW("a1", "t0", 0),               # 0x10  a1 = stream.read()
        ADD("a2", "a0", "a1"),           # 0x14  a2 = a0 + a1
        SW("a2", "t1", 0),               # 0x18  stream.write(a2)
        ADDI("t2", "t2", -1),            # 0x1c  t2 -= 1
        BNE("t2", "x0", 0x0C - 0x20),    # 0x20  if t2 != 0 goto loop
    ]                                    # 0x24  halt
    return prog, 0x24


# ---- EVA router packet ---------------------------------------------------
# Everything below is COPIED from the chip's own generator, not invented here:
#   eva_pkt          == eva_workloads.pack_pkt          (line 35)
#   pe_instr         == eva_workloads.enc               (line 28)
#   MMM_KERNEL, NOP  == the constants in load_mmm_router (line 376)
#   eva_boot_packets == the per-node loop of load_prog_packets (lines 38-74)
# Re-expressed rather than imported because eva_workloads.py does `import eva`
# (no such module on that path any more), is built on numpy whole-array lane
# images, and reads chip globals at call time -- none of which suits generating
# a plain list[int] to paste into a C++ ROM.
#
# Verified equivalent, not assumed: eva_pkt matches pack_pkt over every
# addr/mode/id/rq combination, pe_instr matches enc over all 65536 field
# combinations, and eva_mmm_packets reproduces load_prog_packets' 11-packet
# boot sequence byte-for-byte. The one behavioural difference is that these
# mask each field while the originals do not -- identical for in-range values,
# but these truncate where the originals would overflow into the next field.
#
# Pkt = UInt(26), packed LSB-first (see the chip's D_OFF/A_OFF/MD_OFF/ID_OFF):
#   data [0:16)  addr [16:20)  mode [20]  id [21:25)  rq [25]
# mode=1 is an instruction/config write, mode=0 a data write. A packet entering
# from the west is consumed by the node whose col_id equals its id field.
def eva_pkt(data, addr, mode, ident=0, rq=1):
    return ((rq & 1) << 25) | ((ident & 0xF) << 21) | ((mode & 1) << 20) \
        | ((addr & 0xF) << 16) | (data & 0xFFFF)


def pe_instr(op, dst, s1, s2):
    """One EVA PE instruction word: op | dst<<4 | s1<<8 | s2<<12.

    Register indices >= 12 name a systolic port (dir = idx & 3, 0=N 1=S 2=W 3=E),
    so dst=15 sends the result out the east link. Indices < 8 are DRF slots.
    """
    return (op & 0xF) | ((dst & 0xF) << 4) | ((s1 & 0xF) << 8) | ((s2 & 0xF) << 12)


IRF_DEPTH = 8
NOP = 0x773          # MOV r7, r7 -- r7 is the router receive register, so this
                     # is a genuine no-op. Same padding value the chip's own
                     # workload generator uses.


def eva_boot_packets(instr_words, drf_values, itsz, smask=0, ident=0):
    """The packet sequence that boots a PE: load IRF, load DRF, configure, GO.

    This is what a host normally streams in through rin_s. Emitting it from the
    processor instead is the point of the exercise: the PE runs code the
    processor put there.

    Mirrors eva_workloads.load_prog_packets, which is the chip's ground truth --
    matching it exactly is what made this work. Two things that are easy to get
    wrong and that a short sequence silently fails on:

      * ALL IRF_DEPTH slots must be written, not just the ones the kernel uses.
        Unwritten slots are not reliably no-ops. Pad with NOP.
      * config_reg_0 must be LAST. Writing it flips fetch_en, and the PE starts
        executing on the next step -- so every IRF slot, every DRF value and the
        iteration count have to already be in place.
    """
    pkts = []
    slots = list(instr_words) + [NOP] * (IRF_DEPTH - len(instr_words))
    for k in range(IRF_DEPTH):
        # addr bit3 set selects the IRF: irf[addr & 7] = data
        pkts.append(eva_pkt(slots[k], 0x8 | (k & 7), mode=1, ident=ident))
    for slot, v in drf_values:
        # mode=0 is a data write; the 16 payload bits are bitcast to fp16.
        pkts.append(eva_pkt(v, slot, mode=0, ident=ident))
    pkts.append(eva_pkt(itsz & 0xFF, 1, mode=1, ident=ident))   # cfg1 = iter count
    # cfg0: dsmask[7:0] | isz[10:8] | fetch_en[15]. fetch_en starts the PE.
    # isz is the LAST instruction index, not the count: the node advances with
    # `if instr_cnt == cfg_isz: wrap else: instr_cnt += 1`. So a one-instruction
    # program needs isz = 0. (load_prog_packets agrees -- it sends klen - 1.)
    cfg0 = (1 << 15) | (((len(instr_words) - 1) & 0x7) << 8) | (smask & 0xFF)
    pkts.append(eva_pkt(cfg0, 0, mode=1, ident=ident))
    return pkts


# The golden weight-stationary MMM kernel, verbatim from
# eva_workloads.load_mmm_router. Four instructions that live once in irf[0..3]
# and loop cfg_itsz times, so any batch count fits the 8-slot IRF:
#   I0  MOV  r1, SYSLFT          activation in from the west neighbour
#   I1  MULT r2, r0, r1          r0 is the stationary weight in drf[0]
#   I2  MOV  SYSRGT, r1          forward the activation east
#   I3  ADD  SYSBTM, r2, SYSTOP  accumulate with the north partial, send south
MMM_KERNEL = (0xE13, 0x1022, 0x1F3, 0xC2D0)
MMM_KLEN = 4


def eva_mmm_packets(weight_fp16, batch, ident=0):
    """Boot one PE to run the golden MMM kernel on a stationary weight.

    `weight_fp16` is a raw fp16 bit pattern; `batch` becomes cfg_itsz, the
    number of times the kernel loops. Activations must then arrive on the west
    systolic edge at PROG_CYCLES + MMM_KLEN * b -- that part is the host's job,
    not the processor's.
    """
    return eva_boot_packets(
        MMM_KERNEL, [(0, weight_fp16)], itsz=batch, ident=ident
    )


def eva_pktsrc2_program(lane0, lane1):
    """Program image for TWO west lanes, from one processor.

    `meta_for(0, M)` instantiates the same IP top M times, so M instances all
    carry the same ROM -- fine when every PE runs the same program, useless once
    each node needs its own stationary weight. So one processor drives both
    lanes instead, writing lane 0 to MMIO_OUT26 and lane 1 to MMIO_OUT26B.

    The two images must be the same length; the ROM is lane0 then lane1, and
    the two loops below walk it as one contiguous table.

    t0 = lane 0 port, t1 = lane 1 port, s0 = table base, s1 = index,
    s2 = loop bound, a1 = packet, a2 = scratch address.
    """
    assert len(lane0) == len(lane1), "lanes must carry equal-length images"
    n = len(lane0)
    code = [
        LUI("t0", MMIO_OUT26 >> 12),              # 0x00  t0 = 0x8000
        ADDI("t0", "t0", MMIO_OUT26 & 0xFFF),     # 0x04  t0 = MMIO_OUT26
        ADDI("t1", "t0", MMIO_OUT26B - MMIO_OUT26),  # 0x08  t1 = MMIO_OUT26B
        ADDI("s0", "x0", 0),                      # 0x0c  patched: table offset
        ADDI("s1", "x0", 0),                      # 0x10  idx = 0
        ADDI("s2", "x0", n),                      # 0x14  bound = n
        SLLI("a2", "s1", 2),                      # 0x18  lane0: a2 = idx*4
        ADD("a2", "a2", "s0"),                    # 0x1c
        LW("a1", "a2", 0),                        # 0x20  pkt = table[idx]
        SW("a1", "t0", 0),                        # 0x24  lane0.write(pkt)
        ADDI("s1", "s1", 1),                      # 0x28
        BNE("s1", "s2", 0x18 - 0x2C),             # 0x2c
        ADDI("s2", "x0", 2 * n),                  # 0x30  bound = 2n
        SLLI("a2", "s1", 2),                      # 0x34  lane1: a2 = idx*4
        ADD("a2", "a2", "s0"),                    # 0x38
        LW("a1", "a2", 0),                        # 0x3c  pkt = table[idx]
        SW("a1", "t1", 0),                        # 0x40  lane1.write(pkt)
        ADDI("s1", "s1", 1),                      # 0x44
        BNE("s1", "s2", 0x34 - 0x48),             # 0x48
    ]                                             # 0x4c  halt
    halt_pc = 4 * len(code)
    code[3] = ADDI("s0", "x0", halt_pc)
    return code + list(lane0) + list(lane1), halt_pc


def eva_pktsrc_program(packets):
    """The PE program image, emitted as a plain stream of packets.

    The `rdrv_w`-replacement variant (eva_programmer_program, below) makes the
    processor *be* the router driver, so it has to implement EVA's credit
    protocol itself. This one instead hands the image to EVA's own driver, which
    buffers it and does the credit-gated replay -- the role a host normally
    plays. The processor therefore has no input stream and no protocol at all:
    it writes len(packets) words and halts.

    t0 = MMIO_OUT26 (packets out), s0 = packet table base, s1 = index,
    s2 = count, a1 = packet, a2 = scratch address.
    """
    code = [
        LUI("t0", MMIO_OUT26 >> 12),              # 0x00  t0 = 0x8000
        ADDI("t0", "t0", MMIO_OUT26 & 0xFFF),     # 0x04  t0 = MMIO_OUT26
        ADDI("s0", "x0", 0),                      # 0x08  patched: table offset
        ADDI("s1", "x0", 0),                      # 0x0c  ptr = 0
        ADDI("s2", "x0", len(packets)),           # 0x10  npkts
        SLLI("a2", "s1", 2),                      # 0x14  loop: a2 = ptr * 4
        ADD("a2", "a2", "s0"),                    # 0x18  a2 = &table[ptr]
        LW("a1", "a2", 0),                        # 0x1c  pkt = table[ptr]
        SW("a1", "t0", 0),                        # 0x20  rtr_out.write(pkt)
        ADDI("s1", "s1", 1),                      # 0x24  ptr += 1
        BNE("s1", "s2", 0x14 - 0x28),             # 0x28  repeat
    ]                                             # 0x2c  halt
    halt_pc = 4 * len(code)
    # The packet table follows the code in the same ROM image, so its byte
    # offset is exactly where the code ends.
    code[2] = ADDI("s0", "x0", halt_pc)
    return code + list(packets), halt_pc


def eva_programmer_program(nstep, prime_tokens, packets):
    """The EVA west router driver (`rdrv_w`), as RV32I machine code.

    Replaces the Allo kernel that injects router packets at the array's west
    edge. Instead of replaying a host-supplied array it carries the packets in
    its own ROM, so the processor is what programs the PE.

    The protocol it must honour, from rdrv_w:

        for _ in range(prime_tokens - 1): rtr_e.put(0)
        for t in range(nstep):
            dcred += cr_e.get()
            pw = 0
            if <packet left> and dcred > 0: pw = packet; dcred -= 1
            rtr_e.put(pw)          # exactly one put per step, bubble or not

    t0 = MMIO_IN (credits in), t1 = MMIO_OUT26 (packets out), s0 = packet table
    base, s1 = packet index, s2 = packet count, a4 = credits held, t2 = counter.
    """
    code = [
        LUI("t0", MMIO_IN >> 12),                 # 0x00  t0 = MMIO_IN
        ADDI("t1", "t0", MMIO_OUT26 - MMIO_IN),   # 0x04  t1 = MMIO_OUT26
        ADDI("s0", "x0", 0),                      # 0x08  patched: table byte offset
        ADDI("s1", "x0", 0),                      # 0x0c  ptr = 0
        ADDI("s2", "x0", len(packets)),           # 0x10  npkts
        ADDI("a4", "x0", 0),                      # 0x14  dcred = 0
        ADDI("t2", "x0", prime_tokens - 1),       # 0x18  prime counter
        SW("x0", "t1", 0),                        # 0x1c  prime: rtr_out.write(0)
        ADDI("t2", "t2", -1),                     # 0x20
        BNE("t2", "x0", 0x1C - 0x24),             # 0x24
        ADDI("t2", "x0", nstep),                  # 0x28  step counter
        LW("a0", "t0", 0),                        # 0x2c  loop: credit = cr_in.read()
        ADD("a4", "a4", "a0"),                    # 0x30  dcred += credit
        ADDI("a1", "x0", 0),                      # 0x34  pw = 0 (bubble)
        BGE("s1", "s2", 0x54 - 0x38),             # 0x38  no packets left -> emit
        BGE("x0", "a4", 0x54 - 0x3C),             # 0x3c  no credit -> emit
        SLLI("a2", "s1", 2),                      # 0x40  a2 = ptr * 4
        ADD("a2", "a2", "s0"),                    # 0x44  a2 = &table[ptr]
        LW("a1", "a2", 0),                        # 0x48  pw = table[ptr]
        ADDI("s1", "s1", 1),                      # 0x4c  ptr += 1
        ADDI("a4", "a4", -1),                     # 0x50  dcred -= 1
        SW("a1", "t1", 0),                        # 0x54  emit: rtr_out.write(pw)
        ADDI("t2", "t2", -1),                     # 0x58
        BNE("t2", "x0", 0x2C - 0x5C),             # 0x5c
    ]                                             # 0x60  halt
    halt_pc = 4 * len(code)
    # The packet table follows the code in the same ROM image, so its byte
    # offset is exactly where the code ends.
    code[2] = ADDI("s0", "x0", halt_pc)
    return code + list(packets), halt_pc


def eva_collector_program(nstep, prime_tokens):
    """The EVA east collector (`col_e`), as RV32I machine code.

    Replaces the Allo kernel that consumes the systolic plane at the array's
    east edge. The protocol it has to honour, from col_e:

        for _ in range(prime_tokens - 1): scr_e.put(0)
        scr_e.put(2)                       # advertised hold capacity
        for t in range(nstep):
            w = sys_e.get()
            scr_e.put(1 if w[0] else 0)    # one credit per *real* word
            <unpack w[1:17] into out_e if valid>

    The unpack stays in Allo (a drain kernel reading res_out), because it is a
    bitcast to fp16 -- cheap in Allo, pointless in RV32I. The processor does the
    part that is actually protocol: valid-bit test and credit accounting.

    The raw word is forwarded on *every* step, not only valid ones, so the drain
    kernel always reads exactly nstep words. Forwarding only valid words would
    deadlock it whenever fewer arrive than it expects.

    t0 = MMIO_IN17 (sys in), t1 = MMIO_OUT (credit out), t3 = MMIO_OUT17 (res out),
    t2 = loop counter.
    """
    prime = [
        LUI("t0", MMIO_IN17 >> 12),          # 0x00  t0 = 0x8000 (fixed up below)
        ADDI("t0", "t0", MMIO_IN17 & 0xFFF),  # 0x04  t0 = MMIO_IN17
        ADDI("t1", "x0", 0),                  # 0x08  placeholder, patched below
        ADDI("t3", "x0", 0),                  # 0x0c  placeholder, patched below
        ADDI("t2", "x0", prime_tokens - 1),   # 0x10  prime counter
    ]
    # t1 = MMIO_OUT, t3 = MMIO_OUT17, both derived from t0 so no second LUI.
    prime[2] = ADDI("t1", "t0", MMIO_OUT - MMIO_IN17)
    prime[3] = ADDI("t3", "t0", MMIO_OUT17 - MMIO_IN17)

    body = [
        # prime loop (0x14):
        SW("x0", "t1", 0),                    # 0x14  scr_out.write(0)
        ADDI("t2", "t2", -1),                 # 0x18
        BNE("t2", "x0", 0x14 - 0x1C),         # 0x1c  repeat
        ADDI("a3", "x0", 2),                  # 0x20
        SW("a3", "t1", 0),                    # 0x24  scr_out.write(2)
        ADDI("t2", "x0", nstep),              # 0x28  step counter
        # main loop (0x2c):
        LW("a0", "t0", 0),                    # 0x2c  w = sys_in.read()
        ANDI("a1", "a0", 1),                  # 0x30  vld = w & 1
        SW("a1", "t1", 0),                    # 0x34  scr_out.write(vld)
        SW("a0", "t3", 0),                    # 0x38  res_out.write(w)
        ADDI("t2", "t2", -1),                 # 0x3c
        BNE("t2", "x0", 0x2C - 0x40),         # 0x40  repeat
    ]                                         # 0x44  halt
    return prime + body, 0x44


if __name__ == "__main__":
    import sys

    n = int(sys.argv[1]) if len(sys.argv) > 1 else 32
    prog, halt = vadd_program(n)
    print(f"// {len(prog)} instructions, halt_pc = 0x{halt:02x}, n = {n}")
    for i, w in enumerate(prog):
        print(f"0x{w:08x},  // 0x{i*4:02x}")
