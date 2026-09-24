# Catapult synthesis of drim4hls WITH the Allo MMIO ports.
#   cd drim_cat && catapult -shell -f synth.tcl
#
# Adapted from upstream's core/hls_to_synth.tcl: same libraries, same 10 ns
# clock, same register mappings for the decode/execute arrays. Two differences:
# our sources are flat rather than under ./src/, and the design now carries the
# two MMIO Connections ports, so this also answers whether the hook synthesises.
#
# The TOP is drim4hls, the processor -- NOT drim_eva. That wrapper exists to
# make the CPU look like a pure producer to Allo and holds 51200-word imem and
# dmem arrays plus their server threads; it is a simulation harness, not
# hardware. What ships is the CPU with a memory interface.

set HERE [file normalize [file dirname [info script]]]
options set Input/CppStandard c++11
options set Input/SearchPath "$HERE" -append

project new -name drim4hls_synth
foreach f {fetch.h drim4hls.h top.cpp writeback.h execute.h decode.h} {
    solution file add "$HERE/$f"
}
solution file set "$HERE/top.cpp" -exclude true   ;# testbench, not design
go compile

solution library add nangate-45nm_beh -- -rtlsyntool OasysRTL -vendor Nangate -technology 045nm
solution library add ram_nangate-45nm-dualport_beh
solution library add ram_nangate-45nm-separate_beh
solution library add ram_nangate-45nm-singleport_beh
solution library add ram_nangate-45nm-register-file_beh
solution library add rom_nangate-45nm_beh
solution library add rom_nangate-45nm-sync_regin_beh
solution library add rom_nangate-45nm-sync_regout_beh
go libraries

directive set -CLOCKS {clk {-CLOCK_PERIOD 10 -CLOCK_HIGH_TIME 5 -CLOCK_OFFSET 0.000000 -CLOCK_UNCERTAINTY 0.0}}
go assembly

# Upstream's array mappings: small, randomly addressed every cycle, so they want
# registers rather than a RAM.
directive set /drim4hls/decode/sentinel.rom:rsc -MAP_TO_MODULE {[Register]}
directive set /drim4hls/decode/decode_th/regfile:rsc -MAP_TO_MODULE {[Register]}
directive set /drim4hls/decode/decode_th/sentinel:rsc -MAP_TO_MODULE {[Register]}
directive set /drim4hls/execute/csr.rom:rsc -MAP_TO_MODULE {[Register]}
directive set /drim4hls/execute/execute_th/csr:rsc -MAP_TO_MODULE {[Register]}
go architect
go allocate
go extract

puts "=== SYNTHESIS COMPLETE for drim4hls"
project save
exit 0
