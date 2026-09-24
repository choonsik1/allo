# Catapult synthesis of one HL5 stage.
#   catapult -shell -f synth.tcl               # defaults to execute
#   STAGE=memwb catapult -shell -f synth.tcl   # (needs the dmem story first)
#
# execute is the natural first target: two Connections ports and no memory
# pointer, so it synthesises standalone. fedec and memwb both hold a raw
# pointer to an array owned by the testbench (imem / dmem), which Stratus
# resolved with MAP_ICACHE / MAP_DCACHE and Catapult cannot -- the array has to
# become a module member before those two can be run through this.

set MGC  $env(MGC_HOME)
set HERE [file normalize [file dirname [info script]]]
set STAGE [expr {[info exists env(STAGE)] ? $env(STAGE) : "execute"}]

options set Input/CppStandard c++11
options set Input/SearchPath "$HERE $HERE/upstream $MGC/shared/include" -append
# NOTE: `options set Input/CompilerFlags {-DSTRATUS_HLS}` does NOT work here.
# The option is accepted and reads back, but the value never reaches the EDG
# front end -- check the "Front End called with arguments" line in the log and
# you will see only the -I flags. So HL5's simulation-only blocks (stringstream,
# SC_REPORT_INFO, sc_assert, all under #ifndef STRATUS_HLS) ARE compiled into
# the design, and Catapult tolerates them. Do not re-add the line believing it
# does something; find the real mechanism first.
#
# Catapult DOES define __SYNTHESIS__ (verified with an #error probe), which is
# what memwb.hpp keys its dmem declaration off.

project new -name ${STAGE}_synth
if {$STAGE eq "hl5"} {
    # The whole CPU. All four modules are named in DESIGN_HIERARCHY so each
    # stage is synthesised as its own block and hl5 wires them together;
    # naming only hl5 would inline the stages into one flat process.
    foreach f {hl5_top fedec execute memwb} {
        solution file add "$HERE/$f.cpp" -type C++
    }
    # The testbench, marked -exclude so it is compiled but NOT synthesised.
    # SCVerify reuses it to drive the generated RTL, swapping the DUT out via
    # the CCS_DESIGN(hl5) in system.hpp.
    foreach f {sc_main system tb} {
        solution file add "$HERE/$f.cpp" -type C++ -exclude true
    }
    go analyze
    directive set -DESIGN_HIERARCHY {hl5 fedec execute memwb}
} else {
    solution file add "$HERE/${STAGE}.cpp" -type C++
    go analyze
    directive set -DESIGN_HIERARCHY $STAGE
}
go compile

# Nangate 45 nm open-cell, which ships with Catapult -- a generic ASIC target,
# not the Xilinx part the Vitis half of this project used. The two numbers are
# not comparable.
if {$STAGE eq "hl5"} {
    # SCVerify: run the generated RTL against the SystemC using this same
    # testbench. Questa is the default and is NOT installed here; VCS is.
    # Questa is the default and is NOT installed here. VCS is installed but
    # cannot be used: its SystemC support accepts only g++ 7.3 / 9.2 / 9.5, and
    # the only compilers on this box are Catapult's own 10.3.0 and
    # gcc-toolset-13 (VCS's bundled gnu/linux package is empty). So Xcelium.
    flow package require /SCVerify
    flow package option set /SCVerify/USE_MSIM       false
    flow package option set /SCVerify/USE_QUESTASIM  false
    flow package option set /SCVerify/USE_VCS        false
    flow package option set /SCVerify/USE_NCSIM      true
    # sc_main takes the program image and a report path, exactly as the
    # hand-run binary does.
    flow package option set /SCVerify/INVOKE_ARGS \
        "$HERE/test_mmio.mem catapult_port report.txt"
}

solution library add nangate-45nm_beh
solution library add ccs_sample_mem
go libraries

directive set -CLOCKS {clk {-CLOCK_PERIOD 2.0 -CLOCK_EDGE rising}}
go assembly

# The constraints syn_directives.hpp defers. Sourced here because loops and
# array resources only exist to be named once the design is assembled.
source "$HERE/directives.tcl"

go architect
go allocate
go schedule
go dpfsm
go extract

puts "=== SYNTHESIS COMPLETE for $STAGE"
project save
exit 0
