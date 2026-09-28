open_checkpoint /work/shared/users/zsm9/lean_1x1_wd/hls/impl/verilog/project.runs/impl_1/bd_0_wrapper_routed.dcp

puts "\n########## (A) PE-ONLY  (node_0_0_U0, EXCLUDES drivers/collectors) ##########\n"
set pe [get_cells -hier -filter {NAME =~ *node_0_0_U0}]
report_utilization -cells $pe
report_timing -from [get_cells -hier -filter {NAME =~ *node_0_0_U0*}] \
              -to   [get_cells -hier -filter {NAME =~ *node_0_0_U0*}] -max_paths 3
set p [get_timing_paths -from [get_cells -hier -filter {NAME =~ *node_0_0_U0*}] \
                        -to   [get_cells -hier -filter {NAME =~ *node_0_0_U0*}] -max_paths 1]
puts [format "\n>>> PE-ONLY: WNS=%.3f ns -> period=%.3f ns -> Fmax=%.0f MHz\n" \
      [get_property SLACK $p] [expr 3.33-[get_property SLACK $p]] [expr 1000.0/(3.33-[get_property SLACK $p])]]

puts "\n########## (B) FULL 1x1 TOP  (PE + drivers + collectors + routers) ##########\n"
report_utilization
report_timing_summary -no_detailed_paths
set g [get_timing_paths -max_paths 1 -setup]
puts [format "\n>>> FULL-TOP: WNS=%.3f ns -> period=%.3f ns -> Fmax=%.0f MHz  (this is the 254 headline)\n" \
      [get_property SLACK $g] [expr 3.33-[get_property SLACK $g]] [expr 1000.0/(3.33-[get_property SLACK $g])]]
