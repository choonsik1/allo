// Catapult replacement for HL5's Stratus syn_directives.hpp.
// HL5's sources only ever use these friendly names, never raw HLS_* macros,
// so retargeting every directive is a one-file job.
#ifndef __SYN_DIRECTIVES__H
#define __SYN_DIRECTIVES__H

// HL5 guards its simulation-only code with `#ifndef STRATUS_HLS` -- iostream,
// stringstream, SC_REPORT_INFO, sc_assert, colormod. Under Catapult that code
// must be excluded too, or synthesis dies on things like
// "No definition for method 'ios_base::ios_base'".
//
// It cannot be done from the tcl: `options set Input/CompilerFlags {-D...}` is
// accepted and reads back, but the value never reaches the EDG front end. So
// derive it from __SYNTHESIS__, which Catapult DOES define. Doing it here
// covers all three stages at one point -- this header is included by every
// stage header before any guard is evaluated -- and needs no edit to any of
// Columbia's 15 `#ifndef STRATUS_HLS` sites.
#if defined(__SYNTHESIS__) && !defined(STRATUS_HLS)
#define STRATUS_HLS
#endif

// Placement/scheduling hints with no Catapult source-level twin. Catapult
// takes these from the tcl directives file instead, so they compile away.
#define FLAT_PROGRAM
#define FLAT_REGFILE
#define FLAT_SENTINEL

// Memory mapping: Stratus binds imem/dmem to a named RAM in the source;
// Catapult does it with `directive set /.../imem -MAP_TO_MODULE ram` in tcl.
#define MAP_ICACHE
#define MAP_DCACHE

// Cycle-accurate protocol regions. Stratus pins the enclosed statements to
// exact cycles; Catapult has no source-level equivalent -- its scheduler owns
// cycle assignment. THE ONE PORT RISK: dropping these lets Catapult reschedule
// the reset/handshake sequences, so the pipeline may still be correct but not
// cycle-identical to the paper. Verify with HL5's own soft/ test programs.
#define PROTO_FEDEC_RST
#define PROTO_FEDEC_BODY
#define PROTO_EXE_RST
#define PROTO_EXE_BODY
#define PROTO_PERF_RST
#define PROTO_PERF_BODY
#define PROTO_MEMWB_RST
#define PROTO_MEMWB_BODY

// Stratus asserts dmem's iterations are independent so it can pipeline the
// memory loop. Catapult's equivalent is a source pragma, but it must sit
// immediately before the loop -- a macro expanding to a pragma does not work
// (# is not substitutable), so this is empty and the constraint moves to tcl.
#define BREAK_DMEM_DEP

// Unroll / operator-split. HL5 uses these as STATEMENTS (`DIV_UNROLL;`) inside
// a block, but Catapult's hls_unroll must immediately precede its loop, so a
// _Pragma here would attach to nothing. Empty is also HL5's own default: the
// originals expand to nothing unless DIV_UROLL4 / MUL_SPLIT8 / ADD_SPLIT8 are
// defined at build time, and the stock build defines none of them.
#define DIV_UNROLL
#define MUL_SPLIT
#define ADD_SPLIT

// Three raw Stratus macros bypass the friendly names above:
//   execute.hpp:80  HLS_FLATTEN_ARRAY(csr);
//   fedec.cpp:28    HLS_UNROLL_LOOP(ON);
//   execute.cpp:22  HLS_BREAK_PROTOCOL("div_break_proto");
// Dropping cynw_flex_channels.h leaves them undefined, so absorbing them here
// means those two files need NO in-place edit -- only the include and the port
// types change, exactly as in memwb. HLS_UNROLL_LOOP is variadic because HL5
// calls it both as (ON) and as (AGGRESSIVE, 4, "name").
#define HLS_FLATTEN_ARRAY(...)
#define HLS_UNROLL_LOOP(...)
#define HLS_BREAK_PROTOCOL(...)

#endif // __SYN_DIRECTIVES__H
