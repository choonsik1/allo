#!/bin/bash
# 4x4 RTL COSIM of v6 — router credits KEPT, systolic FULLY non-blocking rq/gt:
#   RX: try_get only when the 2-deep hold has room  (== assert gt when room)
#   TX: try_put, txp_v held until granted           (== hold rq until gt)
#   no systolic primes (always-fire artifact; also fixes CIN-150 multiple-writers)
#
# v6 FAILS csim at 4x4 — expected. HYPOTHESIS: an SC_THREAD body is SEQUENTIAL so the
# "have I room" check reads last-cycle state and the deadlock ring closes; real RTL
# resolves rq/gt COMBINATIONALLY (accept + free in the same cycle) and may work.
# cf. agents/noc/FINDINGS_wire_channel.md: "synthesisable and un-simulatable".
#
# NOTE hls.py compares RTL against its SOFTWARE GOLDEN and raises on mismatch. Here the
# golden is the broken csim, so a "cosim MISMATCH" is EXPECTED and is not the verdict —
# read cosb/output*.data directly and compare against numpy X@W.
cd /home/zsm9/final_eva_systemc
export CHIP=eva_v6
export MMM_MESH=4
export MMM_B=3
export PRIME=1
export MODE=cosim
export PRJ=/scratch/zsm9/eva_runs/4x4_v6_cosim_mmm
export OMP_NUM_THREADS=8
export ALLO_COSIM_SYNTH_TIMEOUT=36000
export ALLO_COSIM_SIM_TIMEOUT=7200
/usr/bin/time -f "4x4 v6 cosim elapsed=%E cpu=%P maxrssMB=%M" -o runs/4x4_v6_cosim_mmm/time.log \
  /home/zsm9/miniconda3/envs/allo/bin/python scripts/run_mmm_systemc.py \
  > runs/4x4_v6_cosim_mmm/run.log 2>&1
echo "rc=$?" >> runs/4x4_v6_cosim_mmm/time.log
