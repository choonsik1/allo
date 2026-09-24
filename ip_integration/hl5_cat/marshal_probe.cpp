// Does Catapult's MatchLib Connections accept an HL5 payload struct as-is?
// mem_out_t provides ctor/copy/==/= (what Stratus FlexChannels need) but no
// Marshall()/bitwidth trait. If Connections needs those, this fails to compile
// and every struct in hl5_datatypes.hpp (608 lines) needs work.
#include <systemc.h>
#include <mc_connections.h>
#include "hl5_datatypes.hpp"

Connections::Combinational<mem_out_t> ch;   // the whole question, one line

int sc_main(int, char**) { return 0; }
