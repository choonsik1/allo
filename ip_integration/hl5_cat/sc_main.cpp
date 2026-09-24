/* Copyright 2017 Columbia University, SLD Group */

//
// main.cpp - Robert Margelli
// Instantiates the top-level module (system) and
// launches simulation (sc_start).
//

#include "system.hpp"

TOP *top = NULL;

extern void esc_elaborate()
{
	top = new TOP("top");
}

extern void  esc_cleanup()
{
	delete top;
}

int sc_main(int argc, char *argv[])
{
	esc_initialize(argc, argv);
	esc_elaborate();

	sc_clock        clk("clk", 10, SC_NS);
	sc_signal<bool> rst("rst");

	// Connections needs to be told which clock its channels run on, before the
	// first sc_start. Plain SystemC simulation gets away without it, but RTL
	// co-simulation aborts on
	//   "You must call Connections::set_sim_clk(&clk) before sc_start()".
	// Safe in both builds -- connections.h defines it either way.
	Connections::set_sim_clk(&clk);

	top->clk(clk);
	top->rst(rst);

	rst.write(false);
	sc_start(51, SC_NS);
	rst.write(true);

	sc_start();

	esc_log_pass();

	return 0;
}
