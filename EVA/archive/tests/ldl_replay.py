import sys, replay_golden_generic as R
B="/home/zsm9/allo/EVA/EVA_untouched/EVA/tb/pe_array"; LOG="/home/zsm9/eva_tb_logs"
stride=int(sys.argv[1]) if len(sys.argv)>1 else 8
R.replay("ldl", f"{B}/ldl", f"{B}/ldl/tb_pe_array_ldl.sv",
         'btm', 4, 'lft', 'sys_tx_lft_data', f"{LOG}/pe_array_ldl.out", ncol=4, margin=300, stride=stride)
