/* Copyright 2017 Columbia University, SLD Group */

//
// system.h - Robert Margelli
// Top-level model header file.
// Instantiates the CPU, TB, IMEM, DMEM.
//

#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <mc_connections.h>   // was cynw_flex_channels.h; before systemc.h
#include <systemc.h>
// SCVerify: lets the same testbench drive either the SystemC hl5 or the
// generated RTL. CCS_DESIGN(hl5) expands to `hl5` in a normal build (the
// __VA_ARGS__ fallback in mc_scverify.h) and to the RTL co-sim wrapper when
// Catapult builds the Verify_rtl_* flow, so the g++ recipe is unaffected.
#include <mc_scverify.h>


#include "hl5_datatypes.hpp"
#include "defines.hpp"
#include "globals.hpp"

#include "hl5.hpp"          // was hl5_wrap.h -- Stratus generated it

#include "tb.hpp"

SC_MODULE(TOP)
{
public:
	// Clock and reset
	sc_in<bool> clk;
	sc_in<bool> rst;

	// End of simulation signal.
	sc_signal < bool > program_end;
	// Fetch enable signal.
	sc_signal < bool > fetch_en;
	// CPU Reset
	sc_signal < bool > cpu_rst;
	// Entry point
	sc_signal < unsigned > entry_point;

	// TODO: removeme
	// sc_signal < bool > main_start;
	// sc_signal < bool > main_end;

	// Instruction counters
	sc_signal < long int > icount; 
	sc_signal < long int > j_icount; 
	sc_signal < long int > b_icount; 
	sc_signal < long int > m_icount; 
	sc_signal < long int > o_icount; 

	// Cache modeled as arryas
	sc_uint<XLEN> imem[ICACHE_SIZE];
	sc_uint<XLEN> dmem[DCACHE_SIZE];

	// The CPU no longer holds these arrays -- it drives an address and reads
	// data back, so the memories live out here and are modelled by the two
	// processes below. tb.cpp still loads the program into imem exactly as
	// before; only who dereferences it changed.
	sc_signal< sc_uint<PC_LEN> > imem_addr_s;
	sc_signal< sc_uint<XLEN>   > imem_dout_s;
	sc_signal< sc_uint<XLEN>   > dmem_addr_s;
	sc_signal< sc_uint<XLEN>   > dmem_wdata_s;
	sc_signal< bool            > dmem_we_s;
	sc_signal< sc_uint<XLEN>   > dmem_rdata_s;

	// Allo: hl5's MMIO channels must terminate somewhere or elaboration fails
	// with E109 "port not bound". Both ends are driven by testbench threads
	// below: mmio_producer() feeds mmio_in, mmio_monitor() drains mmio_out.
	// The producer offers a fixed short sequence, so a program that loads more
	// times than that will block forever on Pop() -- correct behaviour for a
	// starved channel, and the soft/ programs never touch these addresses.
	Connections::Combinational< sc_uint<XLEN> > mmio_in_ch;
	Connections::Combinational< sc_uint<XLEN> > mmio_out_ch;

	// Read on the NEGEDGE ONLY -- deliberately not sensitive to the address.
	//
	// Making these sensitive to the address signal as well models an
	// asynchronous RAM, which is what the original array access was, and it
	// simulates fine in pure SystemC. Under RTL co-simulation it DEADLOCKS: the
	// address is driven X at time 0, address -> data -> address closes a
	// zero-delay path through the RTL wrapper, and the simulation spins in
	// delta cycles at 0 s forever.
	//
	// Sampling on the negedge costs nothing. The CPU drives the address during
	// a cycle, the memory latches it half a cycle later, and the CPU reads the
	// data at the next posedge -- the same cycle it did before. A write lands
	// on the posedge, so a read at the following negedge still sees it.
	//
	// The modulo is not cosmetic: an MMIO access puts MMIO_BASE (== DCACHE_SIZE)
	// on dmem_addr, one past the end of the array. memwb ignores the read data
	// on that path, but the index still has to be in range.
	void imem_read() {
		imem_dout_s.write(imem[imem_addr_s.read().to_uint() % ICACHE_SIZE]);
	}
	void dmem_read() {
		dmem_rdata_s.write(dmem[dmem_addr_s.read().to_uint() % DCACHE_SIZE]);
	}
	// Synchronous write. dmem_addr still holds the access address at this edge
	// -- memwb does not drive the next one until later in the cycle.
	void dmem_write() {
		if (dmem_we_s.read())
			dmem[dmem_addr_s.read().to_uint() % DCACHE_SIZE] = dmem_wdata_s.read();
	}

	// Debug probe for the instruction-fetch interface. Compiles into both the
	// SystemC and the RTL co-simulation build, so the two traces can be diffed
	// -- that is what localises a co-sim divergence. Off unless HL5_PROBE is
	// set in the environment, so normal runs stay quiet.
	int  probe_cyc;
	bool probe_on;
	void fetch_probe() {
		if (probe_on && (probe_cyc < 20 || probe_cyc % 200 == 0)) {
			std::cout << "PROBE " << probe_cyc
			          << " rst=" << cpu_rst.read()
			          << " fe=" << fetch_en.read()
			          << " iaddr=" << imem_addr_s.read().to_uint()
			          << " idout=0x" << std::hex
			          << imem_dout_s.read().to_uint() << std::dec
			          << " daddr=" << dmem_addr_s.read().to_uint()
			          << " dwe=" << dmem_we_s.read() << std::endl;
		}
		probe_cyc++;
	}

	// Allo: drive mmio_in so the LOAD direction of the hook can be tested.
	// Owns mmio_in_ch's WRITE end exclusively -- ResetWrite() moved here out of
	// mmio_monitor(), because two threads may not drive one channel end.
	void mmio_producer() {
		mmio_in_ch.ResetWrite();
		wait();
		mmio_in_ch.Push(0xdeadbeef);
		mmio_in_ch.Push(0x00000100);
		while (true) wait();   // never return from an SC_CTHREAD
	}

	// Allo: drain mmio_out and report what the program stored there. Without a
	// consumer a Push() blocks forever, so this is what makes the MMIO hook
	// testable at all. Resetting both ends also clears the two remaining
	// CONNECTIONS-101 warnings about the testbench-side channel ends.
	void mmio_monitor() {
		mmio_out_ch.ResetRead();   // mmio_in_ch's write end is mmio_producer's now
		wait();
		while (true) {
			sc_uint<XLEN> v = mmio_out_ch.Pop();
			std::cout << "MMIO OUT: 0x" << std::hex << v.to_uint()
			          << std::dec << std::endl;
		}
	}

	/* The testbench, DUT, IMEM and DMEM modules. */
	tb   *m_tb;
	// The DUT is named through CCS_DESIGN so SCVerify can substitute the RTL
	// wrapper for it. Identical to `hl5 *m_dut;` in a normal build.
	CCS_DESIGN(hl5) *m_dut;

	SC_CTOR(TOP)
		: clk("clk")
		, rst("rst")
		, program_end("program_end")
		, fetch_en("fetch_en")
		, cpu_rst("cpu_rst")
		, entry_point("entry_point")
	{
		m_tb = new tb("tb", imem, dmem);

		m_dut = new CCS_DESIGN(hl5)("dut");   // the caches are out here now

		// Connect the design module
		// Memory interfaces
		m_dut->imem_addr(imem_addr_s);
		m_dut->imem_dout(imem_dout_s);
		m_dut->dmem_addr(dmem_addr_s);
		m_dut->dmem_wdata(dmem_wdata_s);
		m_dut->dmem_we(dmem_we_s);
		m_dut->dmem_rdata(dmem_rdata_s);

		m_dut->clk(clk);
		m_dut->rst(cpu_rst);
		m_dut->entry_point(entry_point);
		m_dut->program_end(program_end);
		m_dut->fetch_en(fetch_en);
		// m_dut->main_start(main_start);
		// m_dut->main_end(main_end);
		m_dut->icount(icount);
		m_dut->j_icount(j_icount);
		m_dut->b_icount(b_icount);
		m_dut->m_icount(m_icount);
		m_dut->o_icount(o_icount);
		// Allo: terminate the MMIO channels (see the declaration above).
		m_dut->mmio_in(mmio_in_ch);
		m_dut->mmio_out(mmio_out_ch);
		// The memory models: reads latch on the negedge, the write on the
		// posedge. No address sensitivity -- see the note on the methods.
		SC_METHOD(imem_read);  sensitive << clk.neg();
		SC_METHOD(dmem_read);  sensitive << clk.neg();
		SC_METHOD(dmem_write); sensitive << clk.pos();
		probe_cyc = 0;
		probe_on  = (getenv("HL5_PROBE") != NULL);
		SC_METHOD(fetch_probe); sensitive << clk.pos();

		// Allo: register the MMIO drain (Connections needs a clocked thread).
		SC_CTHREAD(mmio_monitor, clk.pos());
		// cpu_rst, NOT rst: Connections requires every process on a given
		// clock to share a reset spec, and the DUT's stages use cpu_rst
		// (bound above). Using rst here trips CONNECTIONS-212.
		reset_signal_is(cpu_rst, false);
		// Allo: and the MMIO feed. Same clock and same reset spec, for the
		// same CONNECTIONS-212 reason; reset_signal_is applies to the thread
		// declared immediately before it, so this pair must stay together.
		SC_CTHREAD(mmio_producer, clk.pos());
		reset_signal_is(cpu_rst, false);

		// Connect the testbench
		m_tb->clk(clk);
		m_tb->rst(rst);
		m_tb->cpu_rst(cpu_rst);
		m_tb->entry_point(entry_point);
		m_tb->program_end(program_end);
		m_tb->fetch_en(fetch_en);
		// m_tb->main_start(main_start);
		// m_tb->main_end(main_end);
		m_tb->icount(icount);
		m_tb->j_icount(j_icount);
		m_tb->b_icount(b_icount);
		m_tb->m_icount(m_icount);
		m_tb->o_icount(o_icount);
	}

	~TOP()
	{
		delete m_tb;
		delete m_dut;
		delete imem;
		delete dmem;
	}

};

#endif // SYSTEM_H_INCLUDED

