options set Input/CppStandard c++11
options set Input/CompilerFlags {-DCCS_SYSC -I.}
solution new -state initial
solution file add design.cpp -type C++
directive set -DESIGN_HIERARCHY {cons_0}
go analyze
go compile
solution library add nangate-45nm_beh
directive set -CLOCKS {clk {-CLOCK_PERIOD 5.0}}
go assembly
go extract
project save
exit
