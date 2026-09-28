open_checkpoint /work/shared/users/zsm9/lean_1x1_wd/hls/impl/verilog/project.runs/impl_1/bd_0_wrapper_routed.dcp
set pe [get_cells -hier -filter {NAME =~ *node_0_0_U0}]
puts "\n===A=== PE-ONLY (node_0_0_U0) ==="
report_utilization -cells $pe -file $::env(OUT)/pe_util.rpt
puts "\n===B=== FULL 1x1 TOP ==="
report_utilization -file $::env(OUT)/top_util.rpt
