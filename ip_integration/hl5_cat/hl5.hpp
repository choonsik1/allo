/* Copyright 2017 Columbia University, SLD Group */

//
// hl5.h - Robert Margelli
// Header file of the hl5 CPU container.
// This module instantiates the stages and interconnects them.
//

#ifndef __HL5__H
#define __HL5__H

#include <mc_connections.h>   // was cynw_flex_channels.h; before systemc.h
#include <systemc.h>

#include "hl5_datatypes.hpp"
#include "defines.hpp"
#include "globals.hpp"

#include "fedec.hpp"     // was fedec_wrap.h -- Stratus generated those
#include "execute.hpp"
#include "memwb.hpp"

SC_MODULE(hl5)
{
public:
	// Declaration of clock and reset signals
	sc_in_clk      clk;
	sc_in < bool > rst;

	//End of simulation signal.
	sc_out < bool > program_end;

	// Fetch enable signal.
	sc_in < bool > fetch_en;

	// Entry point
	sc_in < unsigned > entry_point;

	// TODO: removeme
	// sc_out < bool > main_start;
	// sc_out < bool > main_end;

	// Instruction counters
	sc_out < long int > icount; 
	sc_out < long int > j_icount; 
	sc_out < long int > b_icount; 
	sc_out < long int > m_icount; 
	sc_out < long int > o_icount; 

	// --- Memory interfaces, promoted from fedec and memwb ------------------
	// The caches are no longer inside the CPU: it drives an address and reads
	// data back, so the RTL can be attached to a real memory (or to the
	// testbench arrays, which is what system.hpp does). This replaces Stratus's
	// MAP_ICACHE / MAP_DCACHE, which have no Catapult equivalent.
	sc_out< sc_uint<PC_LEN> > imem_addr;
	sc_in < sc_uint<XLEN>   > imem_dout;
	sc_out< sc_uint<XLEN> >   dmem_addr;
	sc_out< sc_uint<XLEN> >   dmem_wdata;
	sc_out< bool >            dmem_we;
	sc_in < sc_uint<XLEN> >   dmem_rdata;

	// --- Allo integration: the IP boundary ------------------------------
	// memwb's MMIO ports promoted to the top. These are the ONLY dataflow
	// channels hl5 exposes; de2exe/exe2mem/wb2de below stay private, so
	// parse_sc_module sees a 2-port IP rather than HL5's internal pipeline.
	Connections::In < sc_uint<XLEN> > mmio_in;
	Connections::Out< sc_uint<XLEN> > mmio_out;

	// Inter-stage Flex Channels.
	Connections::Combinational< de_out_t > de2exe_ch;
	Connections::Combinational< mem_out_t > wb2de_ch; // Writeback loop
	Connections::Combinational< exe_out_t > exe2mem_ch;

	// Forwarding
	sc_signal< reg_forward_t > fwd_exe_ch;

	SC_HAS_PROCESS(hl5);

	// The caches moved out, so the ctor no longer takes them.
	hl5(sc_module_name name)
		: clk("clk")
		, rst("rst")
		, program_end("program_end")
		, fetch_en("fetch_en")
		// , main_start("main_start")
		// , main_end("main_end")
		, entry_point("entry_point")
		, de2exe_ch("de2exe_ch")
		, exe2mem_ch("exe2mem_ch")
		, wb2de_ch("wb2de_ch")
		, fwd_exe_ch("fwd_exe_ch")
		, fede("Fedec")
		, exe("Execute")
		, mewb("Memory")
	{
		// FEDEC
		fede.clk(clk);
		fede.rst(rst);
		fede.dout(de2exe_ch);
		fede.feed_from_wb(wb2de_ch);
		fede.program_end(program_end);
		fede.fetch_en(fetch_en);
		fede.entry_point(entry_point);
		// fede.main_start(main_start);
		// fede.main_end(main_end);
		fede.fwd_exe(fwd_exe_ch);
		// Memory interface, straight through to the top.
		fede.imem_addr(imem_addr);
		fede.imem_dout(imem_dout);
		fede.icount(icount);
		fede.j_icount(j_icount);
		fede.b_icount(b_icount);
		fede.m_icount(m_icount);
		fede.o_icount(o_icount);

		// EXE
		exe.clk(clk);
		exe.rst(rst);
		exe.din(de2exe_ch);
		exe.dout(exe2mem_ch);
		exe.fwd_exe(fwd_exe_ch);

		// MEM
		mewb.clk(clk);
		mewb.rst(rst);
		mewb.din(exe2mem_ch);
		mewb.dout(wb2de_ch);
		mewb.fetch_en(fetch_en);
		mewb.dmem_addr(dmem_addr);
		mewb.dmem_wdata(dmem_wdata);
		mewb.dmem_we(dmem_we);
		mewb.dmem_rdata(dmem_rdata);
		// Allo: forward memwb's MMIO channels to hl5's own ports.
		mewb.mmio_in(mmio_in);
		mewb.mmio_out(mmio_out);
	}

	// Instantiate the modules
	fedec fede;
	execute exe;
	memwb mewb;
};

#endif  // end __HL5__H
