/* Copyright 2017 Columbia University, SLD Group */

//
// fedec.h - Robert Margelli
// fetch + decoding logic header file.
//

#ifndef __FEDEC__H
#define __FEDEC__H

#include <systemc.h>

#include <mc_connections.h>   // was cynw_flex_channels.h

#include "defines.hpp"
#include "globals.hpp"
#include "syn_directives.hpp"
#include "hl5_datatypes.hpp"
// Before the Connections::In/Out declarations below -- under synthesis they
// instantiate Wrapped<de_out_t> / Wrapped<mem_out_t>, and a specialisation seen
// after the first instantiation is ill-formed. No effect in simulation.
#include "hl5_marshall.hpp"


SC_MODULE(fedec)
{
public:
	// FlexChannel initiators
	Connections::Out< de_out_t > dout;
	Connections::In< mem_out_t > feed_from_wb;

	// Forward
	sc_in< reg_forward_t > fwd_exe;

	// End of simulation signal.
	sc_out < bool > program_end;

	// Fetch enable signal.
	sc_in < bool > fetch_en;

	// Entry point
	sc_in < unsigned > entry_point;

	// Clock and reset signals
	sc_in_clk clk;
	sc_in< bool > rst;

	// TODO: removeme
	// sc_out < bool > main_start;
	// sc_out < bool > main_end;

	// Instruction counters
	sc_out < long int > icount; 
	sc_out < long int > j_icount; 
	sc_out < long int > b_icount; 
	sc_out < long int > m_icount; 
	sc_out < long int > o_icount; 

	// Trap signals. TODO: not used. Left for future implementations.
	sc_signal< bool > trap; //sc_out
	sc_signal< sc_uint<LOG2_NUM_CAUSES> > trap_cause; //sc_out

	// --- Instruction memory, as an INTERFACE rather than storage -----------
	// Was `sc_uint<XLEN> *imem`, a pointer to an array owned by the testbench.
	// Stratus synthesised that directly because MAP_ICACHE declared the pointer
	// to be a memory; Catapult rejects it (CIN-224), and making it an internal
	// member array is worse than useless -- nothing can write it, so Catapult
	// correctly deletes the array and the whole decoder with it.
	//
	// So the memory moves OUTSIDE and only its port comes in. This costs no
	// timing: HL5 already computes the address, does `wait()`, then reads, which
	// is exactly a registered-address memory. The address is driven before that
	// same wait and the data is read after it.
	sc_out< sc_uint<PC_LEN> > imem_addr;
	sc_in < sc_uint<XLEN>   > imem_dout;

	// Thread prototype
	void fedec_th(void);

	// Function prototypes.
	sc_bv<PC_LEN> sign_extend_jump(sc_bv<21> imm);
	sc_bv<PC_LEN> sign_extend_branch(sc_bv<13> imm);

	// One ctor for both builds now: with imem outside the module there is no
	// array to hand in, so the __SYNTHESIS__ split is gone.
	SC_HAS_PROCESS(fedec);
	fedec(sc_module_name name)
		: dout("dout")
		, feed_from_wb("feed_from_wb")
		, fwd_exe("fwd_exe")
		, program_end("program_end")
		, fetch_en("fetch_en")
		, entry_point("entry_point")
		// , main_start("main_start")
		// , main_end("main_end")
		, j_icount("j_icount")
		, b_icount("b_icount")
		, m_icount("m_icount")
		, o_icount("o_icount")
		, clk("clk")
		, rst("rst")
		, trap("trap")
		, trap_cause("trap_cause")
		, imem_addr("imem_addr")
		, imem_dout("imem_dout")
	{
		SC_CTHREAD(fedec_th, clk.pos());
		reset_signal_is(rst, false);

		FLAT_REGFILE;
		FLAT_SENTINEL;
		MAP_ICACHE;
	}


	sc_uint<PC_LEN>   pc;           // Init. to -4, then before first insn fetch it will be updated to 0.
	sc_bv<INSN_LEN>   insn;         // Contains full instruction fetched from IMEM. Used in decoding.
	fe_in_t           self_feed;    // Contains branch and jump data.

	// Member variables (DECODE)
	mem_out_t   feedinput;
	de_out_t    output;
	// NB. x0 is included in this regfile so it is not a real hardcoded 0
	// constant. The writeback section of fedec has a guard fro writes on
	// x0. For double protection, some instructions that want to write into
	// x0 will have their regwrite signal forced to false.
	sc_bv<XLEN> regfile[REG_NUM];
	// Keeps track of in-flight instructions that are going to overwrite a
	// register. Implements a primitive stall mechanism for RAW hazards.
	sc_uint<TAG_WIDTH>  sentinel[REG_NUM];
	// TODO: Used for synchronizing with the wb stage and avoid
	// 'hiccuping'. It magically works.
	sc_uint<2>  position;
	bool freeze;
	sc_uint<TAG_WIDTH> tag;

	sc_uint<PC_LEN> return_address;
};

#endif
