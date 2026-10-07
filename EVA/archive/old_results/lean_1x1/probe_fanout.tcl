open_checkpoint /work/shared/users/zsm9/lean_1x1_wd/hls/impl/verilog/project.runs/impl_1/bd_0_wrapper_routed.dcp
set p [get_timing_paths -max_paths 1 -setup]
puts "=== nets on the worst path, with fanout + driver ==="
foreach n [get_nets -of_objects [get_pins -of_objects $p]] {
  set fo [get_property FLAT_PIN_COUNT $n]
  if {$fo > 8} {
    set drv [get_pins -leaf -of_objects $n -filter {DIRECTION==OUT}]
    puts [format "  fo=%-4s  net=%s" $fo $n]
    puts "           driver=$drv"
  }
}
