# PE-only timing + utilization, from the REAL routed 1x1 design (node in its true context).
open_checkpoint /work/shared/users/zsm9/lean_1x1_wd/hls/impl/verilog/project.runs/impl_1/bd_0_wrapper_routed.dcp
set pe [get_cells -hier -filter {NAME =~ *node_0_0_U0}]
puts "PE cell: $pe"
# worst paths that BOTH start and end inside the PE (its own critical path)
report_timing -from [get_cells -hier -filter {NAME =~ *node_0_0_U0*}] \
              -to   [get_cells -hier -filter {NAME =~ *node_0_0_U0*}] \
              -max_paths 10 -file ./pe_timing_paths.rpt
report_utilization -cells $pe -file ./pe_utilization.rpt
# headline slack for the PE
set p [get_timing_paths -from [get_cells -hier -filter {NAME =~ *node_0_0_U0*}] \
                        -to   [get_cells -hier -filter {NAME =~ *node_0_0_U0*}] -max_paths 1]
set w [get_property SLACK $p]
puts [format "PE-ONLY: WNS=%.3f -> period=%.3f ns -> Fmax=%.0f MHz" $w [expr 3.33-$w] [expr 1000.0/(3.33-$w)]]
