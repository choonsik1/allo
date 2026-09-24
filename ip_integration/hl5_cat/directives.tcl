# Catapult directives for HL5 -- the constraints Stratus carried in source and
# Catapult takes from tcl. Sourced by synth.tcl after `go assembly`, which is
# when the loops and array resources exist to be named.
#
# syn_directives.hpp defines DIV_UNROLL, MUL_SPLIT, ADD_SPLIT, FLAT_* and
# MAP_* as empty because none of them has a Catapult source-level twin. This
# file is where they actually land.

# Design paths are prefixed by the top when the whole CPU is the design, and
# bare when a single stage is. Everything below is written against $B.
set B [expr {$STAGE eq "hl5" ? "/hl5" : ""}]

# Which stages are in this design, so a directive is never aimed at a module
# that is not there (Catapult errors on an unknown path rather than skipping).
set STAGES [expr {$STAGE eq "hl5" ? {fedec execute memwb} : [list $STAGE]}]

# Apply one directive, reporting rather than aborting if the path does not
# exist. Loop and resource names depend on how Catapult inlined the source, so
# a wrong guess should be visible, not fatal.
proc try_directive {args} {
    if {[catch {eval directive set $args} e]} {
        puts "DIRECTIVE-MISS: $args  ($e)"
        return 0
    }
    puts "DIRECTIVE-OK: $args"
    return 1
}

# --- The QoR lever -----------------------------------------------------------
# DIVIDE_LOOP (execute.cpp:19) is 32 sequential iterations sitting in the
# execute thread's body, so EVERY instruction pays its latency, not just DIV.
# That is where latency 195 / throughput 197 comes from.
#
# Unroll by 4, matching HL5's own DIV_UROLL4 rather than unrolling all 32: a
# full unroll replicates the datapath 32x for an instruction that is rare in
# the test programs, and the point here is to relieve the shared body.
# Sweepable: HL5_DIV_UNROLL=4 (default, matches HL5's DIV_UROLL4), 8, or `yes`
# for a full 32x unroll.
set DU [expr {[info exists env(HL5_DIV_UNROLL)] ? $env(HL5_DIV_UNROLL) : 4}]
if {"execute" in $STAGES} {
    try_directive $B/execute/execute_th/DIVIDE_LOOP -UNROLL $DU
}

# --- Array mapping: what FLAT_REGFILE and HLS_FLATTEN_ARRAY(csr) meant --------
# Both are small and randomly addressed every cycle, so they want to be
# registers, not a RAM -- a single-port memory would serialise the two register
# reads a decode needs. This is the Catapult spelling of Stratus's flatten.
if {"execute" in $STAGES} {
    try_directive $B/execute/execute_th/csr:rsc -MAP_TO_MODULE {[Register]}
}
# NOTE regfile reports DIRECTIVE-MISS ("Unknown path"), and that is correct:
# Catapult already flattens it to registers on its own, so there is no memory
# resource to map. Left in place because the miss is the evidence -- if a future
# change turns it into a RAM, this line starts applying and says so.
if {"fedec" in $STAGES} {
    try_directive $B/fedec/fedec_th/regfile:rsc -MAP_TO_MODULE {[Register]}
}

# --- Pipelining the stage bodies: OFF by default -----------------------------
# Note HL5's own directive set has NO pipeline directive -- it is FLAT_*, MAP_*,
# PROTO_*, BREAK_DMEM_DEP, DIV_UNROLL, MUL_SPLIT, ADD_SPLIT and nothing else. So
# pipelining is an addition, not a restoration, and at II=1 it does not schedule:
#   "Feedback path is too long to schedule design with current pipeline and
#    clock constraints" (SCHD-3)
# which is the forwarding and channel feedback the stages close every iteration.
# Set HL5_PIPELINE_II in the environment to experiment; leave it unset for a
# faithful port.
set II [expr {[info exists env(HL5_PIPELINE_II)] ? $env(HL5_PIPELINE_II) : 0}]
if {$II > 0} {
    foreach s $STAGES {
        switch $s {
            execute { try_directive $B/execute/execute_th/EXE_BODY   -PIPELINE_INIT_INTERVAL $II }
            fedec   { try_directive $B/fedec/fedec_th/FEDEC_BODY     -PIPELINE_INIT_INTERVAL $II }
            memwb   { try_directive $B/memwb/memwb_th/MEMWB_BODY     -PIPELINE_INIT_INTERVAL $II }
        }
    }
}
