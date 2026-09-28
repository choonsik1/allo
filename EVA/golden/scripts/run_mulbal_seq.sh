#!/bin/bash
SC=/home/zsm9/pe_core_implementation/Vitis_HLS/bubble_model/final_runs/cosim_8x8/eva_sb_nb
echo "SEQ START $(date)"
bash $SC/run_mulbal_1x1.sh fabric;  echo "fabric rc=$?"
bash $SC/run_mulbal_1x1.sh fulldsp; echo "fulldsp rc=$?"
echo "SEQ ALLDONE $(date)"
