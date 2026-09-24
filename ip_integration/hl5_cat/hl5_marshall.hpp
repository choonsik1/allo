// Marshalling for HL5's channel payloads. Needed ONLY for synthesis.
//
// In simulation Connections keeps the payload as a C++ object and never
// instantiates the marshaller -- which is why marshal_probe.cpp compiled and
// the whole design ran without this file. Under synthesis Connections switches
// the port to SYN_PORT, flattens each payload to sc_lv<width>, and then demands
// Wrapped<T>::width and Wrapped<T>::Marshall.
//
// Specialising Wrapped<T> here, rather than adding a Marshall() method to each
// struct, keeps upstream/hl5_datatypes.hpp byte-identical to Columbia's.
#ifndef __HL5_MARSHALL__H
#define __HL5_MARSHALL__H

#include <connections/marshaller.h>
#include "hl5_datatypes.hpp"

// The pattern, on the smallest payload. Two rules matter:
//   * `width` must equal the sum of the field widths EXACTLY -- Marshaller
//     packs at a running cur_idx and the total has to land on Size.
//   * `m & f` resolves to the sc_bv / sc_uint overloads in marshaller.h
//     (SpecialUnsignedWrapper covers both), so no per-field casting is needed.
// Field ORDER is free, but must match between pack and unpack -- which it does
// here, because the same function does both.
template <>
class Wrapped<reg_forward_t>
{
public:
	reg_forward_t val;
	Wrapped() {}
	Wrapped(const reg_forward_t &v) : val(v) {}
	static const unsigned int width = XLEN + TAG_WIDTH;
	static const bool is_signed = false;
	template <unsigned int Size>
	void Marshall(Marshaller<Size> &m) {
		m &val.regfile_data;
		m &val.tag;
	}
};

// memwb -> fedec (the writeback loop).
template <>
class Wrapped<mem_out_t>
{
public:
	mem_out_t val;
	Wrapped() {}
	Wrapped(const mem_out_t &v) : val(v) {}
	static const unsigned int width = 1 + REG_ADDR + XLEN + TAG_WIDTH;
	static const bool is_signed = false;
	template <unsigned int Size>
	void Marshall(Marshaller<Size> &m) {
		m &val.regwrite;
		m &val.regfile_address;
		m &val.regfile_data;
		m &val.tag;
	}
};

// execute -> memwb.
template <>
class Wrapped<exe_out_t>
{
public:
	exe_out_t val;
	Wrapped() {}
	Wrapped(const exe_out_t &v) : val(v) {}
	static const unsigned int width =
		3 + 2 + 1 + 1 + XLEN + DATA_SIZE + REG_ADDR + TAG_WIDTH;
	static const bool is_signed = false;
	template <unsigned int Size>
	void Marshall(Marshaller<Size> &m) {
		m &val.ld;
		m &val.st;
		m &val.memtoreg;
		m &val.regwrite;
		m &val.alu_res;
		m &val.mem_datain;
		m &val.dest_reg;
		m &val.tag;
	}
};

// fedec -> execute. The widest payload: a whole decoded instruction.
// Note imm_u is sc_bv<XLEN-12>, so the width expression carries the -12.
template <>
class Wrapped<de_out_t>
{
public:
	de_out_t val;
	Wrapped() {}
	Wrapped(const de_out_t &v) : val(v) {}
	static const unsigned int width =
		1 + 1 + 3 + 2 + ALUOP_SIZE + ALUSRC_SIZE + XLEN + XLEN +
		REG_ADDR + PC_LEN + (XLEN - 12) + TAG_WIDTH;
	static const bool is_signed = false;
	template <unsigned int Size>
	void Marshall(Marshaller<Size> &m) {
		m &val.regwrite;
		m &val.memtoreg;
		m &val.ld;
		m &val.st;
		m &val.alu_op;
		m &val.alu_src;
		m &val.rs1;
		m &val.rs2;
		m &val.dest_reg;
		m &val.pc;
		m &val.imm_u;
		m &val.tag;
	}
};

#endif // __HL5_MARSHALL__H
