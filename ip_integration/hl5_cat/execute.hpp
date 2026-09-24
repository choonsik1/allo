/* Copyright 2017 Columbia University, SLD Group */

//
// execute.h - Robert Margelli
// execute stage header file.
//
// Division algorithm for DIV, DIVU, REM, REMU instructions. Division by zero
// and overflow semantics are compliant with the RISC-V specs (page 32).
//

#include <systemc.h>
#include <mc_connections.h>   // was cynw_flex_channels.h

#include "defines.hpp"
#include "globals.hpp"
#include "hl5_datatypes.hpp"
// Must precede the Connections::In/Out declarations below: under synthesis they
// instantiate Wrapped<de_out_t> / Wrapped<exe_out_t>, and a specialisation seen
// after the first instantiation is ill-formed. Harmless in simulation.
#include "hl5_marshall.hpp"

#include "syn_directives.hpp"

#ifndef __EXECUTE__H
#define __EXECUTE__H

#define BIT(_N) (1 << _N)

// Signed division quotient and remainder struct.
struct div_res_t{
	sc_int<XLEN> quotient;
	sc_int<XLEN> remainder;
};

// Unsigned division quotient and remainder struct.
struct u_div_res_t{
	sc_uint<XLEN> quotient;
	sc_uint<XLEN> remainder;
};

SC_MODULE(execute)
{
	// FlexChannel initiators
	Connections::In< de_out_t > din;
	Connections::Out< exe_out_t > dout;

	// Forward
	sc_out< reg_forward_t > fwd_exe;

	// Clock and reset signals
	sc_in_clk clk;
	sc_in<bool> rst;

	// Thread prototype
	void execute_th(void);
	void perf_th(void);

	// Support functions
	sc_bv<XLEN> sign_extend_imm_s(sc_bv<12> imm);       // Sign extend the S-type immediate field.
	sc_bv<XLEN> zero_ext_zimm(sc_bv<ZIMM_SIZE> zimm);   // Zero extend the zimm field for CSRRxI instructions.
	sc_uint<CSR_IDX_LEN> get_csr_index(sc_bv<CSR_ADDR> csr_addr); // Get csr index given the 12-bit CSR address.
	void set_csr_value(sc_uint<CSR_IDX_LEN> csr_index, sc_bv<XLEN> rs1, sc_uint<LOG2_CSR_OP_NUM> operation, sc_bv<2> rw_permission);  // Perform requested CSR operation (write/set/clear).

	// Divider functions
	u_div_res_t udiv_func(sc_uint<XLEN> num, sc_uint<XLEN> den);
	div_res_t div_func(sc_int<XLEN> num, sc_int<XLEN> den);

	// Constructor
	SC_CTOR(execute)
		: din("din")
		, dout("dout")
		, fwd_exe("fwd_exe")
		, clk("clk")
		, rst("rst")
	{
		SC_CTHREAD(execute_th, clk.pos());
		reset_signal_is(rst, false);

		// perf_th does nothing but csr[MCYCLE_I]++ every cycle, and execute_th
		// also touches csr for the CSR instructions. Catapult rejects a
		// variable shared between two SC_CTHREADs (HIER-41); Stratus allowed
		// it. The counter is not in the pipeline's dataflow, so it is dropped
		// from the synthesised RTL -- mcycle simply does not advance there.
		// Simulation is unaffected: __SYNTHESIS__ is Catapult-only.
#ifndef __SYNTHESIS__
		SC_CTHREAD(perf_th, clk.pos());
		reset_signal_is(rst, false);
#endif

		HLS_FLATTEN_ARRAY(csr);
	}

	// Member variables
	de_out_t input;
	exe_out_t output;
	sc_uint<XLEN> csr[CSR_NUM]; // Control and status registers.
};


#endif
