// HL5 memwb stage, retargeted from Cadence Stratus to Catapult/MatchLib.
// Diff vs src/memwb.hpp: the include, the two port types, and the ctor's
// clk_rst calls. Everything else -- dmem, the thread, the sign-extend
// helpers, the member variables -- is byte-identical to the original.
#ifndef __MEMWB__H
#define __MEMWB__H

#include <mc_connections.h>   // was "cynw_flex_channels.h"; before systemc.h
#include <systemc.h>          // so SC_INCLUDE_DYNAMIC_PROCESSES lands first

#include "defines.hpp"
#include "globals.hpp"
#include "syn_directives.hpp"
#include "hl5_datatypes.hpp"
// Before the Connections::In/Out declarations below -- under synthesis they
// instantiate Wrapped<exe_out_t> / Wrapped<mem_out_t>, and a specialisation
// seen after the first instantiation is ill-formed. No effect in simulation.
#include "hl5_marshall.hpp"


SC_MODULE(memwb)
{
	// Was: get_initiator< exe_out_t > din;  put_initiator< mem_out_t > dout;
	// Connections carries direction in the type, so In/Out replace the
	// initiator pair one-for-one. Payloads are HL5's own structs, unchanged --
	// the marshalling probe proved Connections accepts them as written.
	Connections::In< exe_out_t >  din;
	Connections::Out< mem_out_t > dout;

	// --- Allo integration: memory-mapped stream ports -------------------
	// A load/store whose word address is >= MMIO_BASE is a channel access,
	// not a dmem access. DCACHE_SIZE words of real memory sit below it, so
	// the two can never alias. Same trick as the vhls-riscv IP; it is what
	// gives a memory-mapped processor a streaming interface.
	static const unsigned MMIO_BASE = DCACHE_SIZE;
	Connections::In< sc_uint<XLEN> >  mmio_in;
	Connections::Out< sc_uint<XLEN> > mmio_out;

	// Clock and reset signals
	sc_in_clk clk;
	sc_in<bool> rst;

	// Enable fetch
	sc_in<bool> fetch_en;   // Used to synchronize writeback with fetch at reset.

	// --- Data memory, as an INTERFACE rather than storage ------------------
	// Was `sc_uint<XLEN> *dmem`, a pointer to a testbench-owned array that
	// Stratus synthesised via MAP_DCACHE. Catapult cannot, and an internal
	// member array is worse: nothing outside can write it, so Catapult deletes
	// it and the load/store logic with it.
	//
	// One word wide, one access per instruction. Reads are free of extra
	// latency because HL5 already has a `wait()` between computing the address
	// and using it. Writes take effect on the cycle after `dmem_we` is raised.
	// The sub-word stores (SB/SH) are read-modify-write, which works because
	// the read data for the same address is already in hand by then.
	sc_out< sc_uint<XLEN> > dmem_addr;
	sc_out< sc_uint<XLEN> > dmem_wdata;
	sc_out< bool >          dmem_we;
	sc_in < sc_uint<XLEN> > dmem_rdata;

	// Thread prototype
	void memwb_th(void);
	// Function prototypes.
	sc_bv<XLEN> ext_sign_byte(sc_bv<BYTE> read_data);           // Sign extend byte read from memory. For LB
	sc_bv<XLEN> ext_unsign_byte(sc_bv<BYTE> read_data);         // Zero extend byte read from memory. For LBU
	sc_bv<XLEN> ext_sign_halfword(sc_bv<BYTE*2> read_data);     // Sign extend half-word read from memory. For LH
	sc_bv<XLEN> ext_unsign_halfword(sc_bv<BYTE*2> read_data);   // Zero extend half-word read from memory. For LHU

	// Constructor
	// One ctor for both builds now: with dmem outside the module there is no
	// array to hand in, so the __SYNTHESIS__ split is gone.
	SC_HAS_PROCESS(memwb);
	memwb(sc_module_name name)
		: din("din")
		, dout("dout")
		, clk("clk")
		, rst("rst")
		, fetch_en("fetch_en")
		, dmem_addr("dmem_addr")
		, dmem_wdata("dmem_wdata")
		, dmem_we("dmem_we")
		, dmem_rdata("dmem_rdata")
	{
		SC_CTHREAD(memwb_th, clk.pos());
		reset_signal_is(rst, false);
		// Was: din.clk_rst(clk, rst); dout.clk_rst(clk, rst);
		// DELETED, not translated. A Connections port has no clk/rst member
		// (InBlocking carries only data/val/rdy) -- Reset() is called from
		// inside the SC_CTHREAD and inherits its timing from the two lines
		// above. Stratus needed clk_rst because FlexChannels tracked their own.

		MAP_DCACHE;
	}

	// Member variables
	exe_out_t   input;
	mem_out_t   output;
	sc_bv<DATA_SIZE> mem_dout;  // Temporarily stores the value read from memory with a load instruction
};

#endif
