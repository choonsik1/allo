// Parameter-fixing wrappers for the three RaveNoC modules under measurement.
//
// NOT struct-flattening shims -- these three modules already have flat scalar ports, which
// is exactly why they were chosen (see ../PLAN_ravenoc_compare.md). The only thing these
// wrappers do is PIN THE PARAMETERS to the matched configuration, so the bench does not
// depend on tool-specific -defparam syntax and the config is visible in one place.
//
// Matched config (from tb/common_noc/constants.py, the "vanilla" flavor -- note the tb
// README's table says FLIT_BUFF=1 but the CODE says 2; the code wins):
//     flit width 32, buffer depth 2, 2 virtual channels, XY routing.
//
// RaveNoC reset is ACTIVE-HIGH async (`posedge arst`). Allo/Catapult RTL is active-LOW.
// Do not mix them up: an inverted reset silently leaves the DUT held in reset forever.

`timescale 1ns/1ps

// ---------------------------------------------------------------------------------------
// 1. fifo -- the Stream baseline. Raw write_i/read_i enables, no handshake: the CALLER
//    must consult full_o/empty_o. This is the storage half of what Allo's Stream[T,N]
//    bundles together with its protocol.
// ---------------------------------------------------------------------------------------
module fifo_w #(
  parameter int SLOTS = 2,
  parameter int WIDTH = 32
)(
  input                     clk,
  input                     arst,
  input                     write_i,
  input                     read_i,
  input        [WIDTH-1:0]  data_i,
  output       [WIDTH-1:0]  data_o,
  output                    error_o,
  output                    full_o,
  output                    empty_o,
  // Exposed for the occupancy measurement -- fifo.sv computes it for free from the
  // pointer difference (that is what the extra wrap bit buys), and it tells us whether
  // depth 2 is even the right depth under a given backpressure pattern.
  output [$clog2(SLOTS>1?SLOTS:2):0] ocup_o
);
  fifo #(.SLOTS(SLOTS), .WIDTH(WIDTH)) u_dut (
    .clk(clk), .arst(arst),
    .write_i(write_i), .read_i(read_i),
    .data_i(data_i), .data_o(data_o),
    .error_o(error_o), .full_o(full_o), .empty_o(empty_o),
    .ocup_o(ocup_o)
  );
endmodule

// ---------------------------------------------------------------------------------------
// 2. rr_arbiter -- the Wire example. req_i -> grant_o is COMBINATIONAL; the only state is
//    the round-robin priority pointer, advanced by update_i. N_OF_INPUTS=4 matches
//    output_module.sv, which instantiates one arbiter per VC over its 4 input ports.
// ---------------------------------------------------------------------------------------
module rr_arbiter_w #(
  parameter int N_OF_INPUTS = 4
)(
  input                          clk,
  input                          arst,
  input                          update_i,
  input        [N_OF_INPUTS-1:0] req_i,
  output       [N_OF_INPUTS-1:0] grant_o
);
  rr_arbiter #(.N_OF_INPUTS(N_OF_INPUTS)) u_dut (
    .clk(clk), .arst(arst),
    .update_i(update_i), .req_i(req_i), .grant_o(grant_o)
  );
endmodule

// NOTE: vc_buffer needs NO wrapper. Its widths come from ravenoc_pkg (FlitWidth, FlitBuff),
// which are driven by +define+ macros on the compile line -- see the Makefile.
