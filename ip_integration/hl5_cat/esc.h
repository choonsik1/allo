// A Catapult-side replacement for Cadence Stratus's <esc.h>.
//
// ESC is Stratus's simulation-control library. HL5's DESIGN never touches it
// (grep src/ finds nothing) -- only the testbench does, for argv access, a
// pass log, and a time-unit helper. Reimplementing the seven functions it uses
// keeps the whole flow on Catapult instead of linking Stratus just to run a
// testbench.
#ifndef __ESC_SHIM_H
#define __ESC_SHIM_H

#include <systemc.h>
#include <cstdio>

// argv, stashed by esc_initialize and read back by esc_argv.
inline int&    _esc_argc() { static int a = 0;       return a; }
inline char**& _esc_argv() { static char** v = 0;    return v; }

inline void esc_initialize(int argc, char* argv[]) {
    _esc_argc() = argc;
    _esc_argv() = argv;
}

// tb.cpp reads argv 1..3: program file, HLS config name, report file.
// Stratus returns a usable string for a missing arg rather than crashing, so
// do the same -- a short arg list must not segfault the testbench.
inline const char* esc_argv(int i) {
    return (i >= 0 && i < _esc_argc()) ? _esc_argv()[i] : "";
}

// sc_main.cpp calls this after sc_start returns, as the "test passed" marker.
inline void esc_log_pass() { std::printf("Simulation PASSED\n"); }

// tb.cpp calls this to end the run once the program signals completion.
inline void esc_stop() { sc_core::sc_stop(); }

// tb.cpp: exec_start = esc_normalize_to_ps(sc_time_stamp()) / 1000, i.e. it
// expects PICOSECONDS as a double, then converts to ns itself.
inline double esc_normalize_to_ps(const sc_core::sc_time& t) {
    return t.to_seconds() * 1e12;
}

// esc_elaborate() and esc_cleanup() are NOT defined here: sc_main.cpp declares
// them extern and system.cpp supplies them. They are the user's hooks.

#endif // __ESC_SHIM_H
