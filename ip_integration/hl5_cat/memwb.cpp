/* Copyright 2017 Columbia University, SLD Group */

//
// memory.cpp - Robert Margelli  [Catapult/MatchLib port: 6 channel calls]
// Implementation of the memwb stage ie combined memory and writeback stages.
//

#include "memwb.hpp"

void memwb::memwb_th(void)
{
MEMWB_RST:
	{
		PROTO_MEMWB_RST;
		din.Reset();
		dout.Reset();
		// Allo: every Connections port must be Reset() in the thread's reset
		// block or the channel warns CONNECTIONS-101 and its val/rdy start
		// undriven. Adding ports without this is the easy mistake.
		mmio_in.Reset();
		mmio_out.Reset();
		// Every output port must be driven in the reset action -- Catapult will
		// not preserve state across reset (CIN-233). The write strobe is the
		// one that matters: it must come out of reset low.
		dmem_addr.write(0);
		dmem_wdata.write(0);
		dmem_we.write(false);

		// Write dummy data to decode feedback.
		output.regfile_address = "00000";
		output.regfile_data    = (sc_bv<XLEN>)0;
		output.regwrite        = "0";
		output.tag             = 0;
	}

	// Catapult rejects a channel transaction anywhere before the main loop --
	// it counts all of that as the thread's reset block (MIO-2). HL5's startup
	// handshake (wait for fetch_en, then prime the writeback loop with two
	// dummy outputs so fedec can issue) therefore moves INSIDE the loop, behind
	// a first-iteration flag. Same statements, same order, same cycles; Stratus
	// tolerated them where they were because HLS_DEFINE_PROTOCOL pinned them.
	bool primed = false;

MEMWB_BODY:
	while(true) {
		PROTO_MEMWB_BODY;
		BREAK_DMEM_DEP;

		if (!primed) {
			do {wait();} while(!fetch_en); // Synchronize with fetch at startup.
			dout.Push(output);
			wait();
			dout.Push(output);
			primed = true;
		}

		// Get
		input = din.Pop();

		// Compute
		// *** Memory access.

		// WARNING: only supporting aligned memory accesses

		// Preprocess address
		unsigned int aligned_address = input.alu_res.to_uint();
		unsigned char byte_index = (unsigned char) ((aligned_address & 0x3) << 3);
		unsigned char halfword_index = (unsigned char) ((aligned_address & 0x2) << 3);

		aligned_address = aligned_address >> 2;
		sc_uint<BYTE> db;
		sc_uint<2 * BYTE> dh;
		sc_uint<XLEN> dw;

		// Drive the address before the wait below, so the external memory has a
		// full cycle to respond. The wait was already here.
		dmem_addr.write(aligned_address);
		// Deassert the write strobe for THIS cycle. Without it the strobe
		// raised at the end of the previous iteration is still high when the
		// memory next samples, and the new address gets a spurious write.
		dmem_we.write(false);

		wait();

		// The word at aligned_address, valid now. Every load reads it and every
		// sub-word store modifies it, so one fetch covers all eight sites.
		sc_uint<XLEN> rdw = dmem_rdata.read();
		bool          wen = false;   // raised only by the store branch below
		sc_uint<XLEN> wdw = rdw;

#ifndef STRATUS_HLS
		if (sc_uint<3>(input.ld) != NO_LOAD || sc_uint<2>(input.st) != NO_STORE) {
#ifndef VERBOSE
			if (input.mem_datain.to_uint() == 0x11111111 ||
			    input.mem_datain.to_uint() == 0x22222222 ||
			    input.mem_datain.to_uint() == 0x11223344 ||
			    input.mem_datain.to_uint() == 0x88776655 ||
			    input.mem_datain.to_uint() == 0x12345678 ||
			    input.mem_datain.to_uint() == 0x87654321) {
#endif
				std::stringstream stm;
				stm << hex << "D$ access here2 -> 0x" << aligned_address << ". Value: " << input.mem_datain.to_uint() << std::endl;
				SC_REPORT_INFO(sc_object::name(), stm.str().c_str());
#ifndef VERBOSE
			}
#endif
			// Allo: MMIO_BASE == DCACHE_SIZE, so a channel access would trip
			// the original bound check. Widen it by exactly one word rather
			// than deleting it -- a stray address is still caught.
			sc_assert(aligned_address < DCACHE_SIZE || aligned_address == MMIO_BASE);
		}
#endif

		// Allo: an address at or above MMIO_BASE is a channel, not memory.
		// Placed before the normal path so the dmem switches below are
		// untouched; the load arm feeds mem_dout exactly as a LW would, so
		// writeback needs no change either.
		if (aligned_address >= MMIO_BASE) {
			if (sc_uint<3>(input.ld) != NO_LOAD)
				mem_dout = mmio_in.Pop();                     // blocking
			else if (sc_uint<2>(input.st) != NO_STORE)
				mmio_out.Push(input.mem_datain.to_uint());
		}
		else if (sc_uint<3>(input.ld) != NO_LOAD) {    // a load is requested
			switch(sc_uint<3>(input.ld)) {         // LOAD
			case LB_LOAD:
				db = rdw.range(byte_index + BYTE - 1, byte_index);
				mem_dout = ext_sign_byte(db);
				break;
			case LH_LOAD:
				dh = rdw.range(halfword_index + 2 * BYTE - 1, halfword_index);
				mem_dout = ext_sign_halfword(dh);
				break;
			case LW_LOAD:
				dw = rdw;
				mem_dout = dw;
				break;
			case LBU_LOAD:
				db = rdw.range(byte_index + BYTE - 1, byte_index);
				mem_dout = ext_unsign_byte(db);
				break;
			case LHU_LOAD:
				dh = rdw.range(halfword_index + 2 * BYTE - 1, halfword_index);
				mem_dout = ext_unsign_halfword(dh);
				break;
			default:
				break;  // NO_LOAD
			}
		}
		else if (sc_uint<2>(input.st) != NO_STORE) {  // a store is requested
			switch (sc_uint<2>(input.st)) {         // STORE
			case SB_STORE:  // store 8 bits of rs2
				db = input.mem_datain.range(BYTE - 1, 0).to_uint();
				wdw.range(byte_index + BYTE -1, byte_index) = db;  wen = true;
				break;
			case SH_STORE:  // store 16 bits of rs2
				dh = input.mem_datain.range(2 * BYTE - 1, 0).to_uint();
				wdw.range(halfword_index + 2 * BYTE - 1, halfword_index) = dh;  wen = true;
				break;
			case SW_STORE:  // store rs2
				dw = input.mem_datain.to_uint();
				wdw = dw;  wen = true;
				break;
			default:
				break;  // NO_STORE
			}
		}
		// Drive the write port once, after the branches. wen is false unless a
		// store ran, so a load or an MMIO access leaves memory untouched.
		dmem_wdata.write(wdw);
		dmem_we.write(wen);

		// *** END of memory access.

		/* Writeback */
		output.regwrite         = input.regwrite;
		output.regfile_address  = input.dest_reg;
		output.regfile_data     = (input.memtoreg == "1")? mem_dout : input.alu_res;
		output.tag              = input.tag;

		// Put
		dout.Push(output);
	}
}


/* Support functions */

// Sign extend byte read from memory. For LB
sc_bv<XLEN> memwb::ext_sign_byte(sc_bv<BYTE> read_data)
{
	if (read_data.range(7,7) == "1")
		return (sc_bv<BYTE*3>("111111111111111111111111"), read_data);
	else
		return (sc_bv<BYTE*3>("000000000000000000000000"), read_data);
}

// Zero extend byte read from memory. For LBU
sc_bv<XLEN> memwb::ext_unsign_byte(sc_bv<BYTE> read_data)
{
        return ("000000000000000000000000", read_data);
}

// Sign extend half-word read from memory. For LH
sc_bv<XLEN> memwb::ext_sign_halfword(sc_bv<BYTE*2> read_data)
{
	if (read_data.range(15,15) == "1")
		return (sc_bv<BYTE*2>("1111111111111111"), read_data);
	else
		return (sc_bv<BYTE*2>("0000000000000000"), read_data);
}

// Zero extend half-word read from memory. For LHU
sc_bv<XLEN> memwb::ext_unsign_halfword(sc_bv<BYTE*2> read_data)
{
        return ("0000000000000000", read_data);
}
