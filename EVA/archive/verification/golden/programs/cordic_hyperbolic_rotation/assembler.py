#!/usr/bin/env python3

import numpy as np
import re
import os
import sys

def opcode_decode(opcode):
    if opcode == "ADD":
        return "0000"
    elif opcode == "SUB":
        return "0001"
    elif opcode == "MULT":
        return "0010"
    elif opcode == "MOV":
        return "0011"
    elif opcode == "UMOV":
        return "0100"
    elif opcode == "DMOV":
        return "0101"
    elif opcode == "LMOV":
        return "0110"
    elif opcode == "RMOV":
        return "0111"
    elif opcode == "GEQ":
        return "1000"
    elif opcode == "LE":
        return "1001"
    elif opcode == "DIV":
        return "1010"
    elif opcode == "SQRT":
        return "1011"
    else:
        print("ERROR: invalid opcode {}!".format(opcode))

def reg_decode(reg):
    if reg == "systop":
        return "1100"
    elif reg == "sysbtm":
        return "1101"
    elif reg == "syslft":
        return "1110"
    elif reg == "sysrgt":
        return "1111"
    else:
        print("ERROR: invalid reg identifier {}!".format(reg))

###############
#  Assembler  #
###############

def assemble(asm_file_name, bin_file_name):
    bin_file_lst = []
    core_id = ""
    inst_pt = 0
    is_in_inst = 0
    is_in_data = 0
    is_in_conf = 0

    with open(asm_file_name,"r") as asm_file:
        for line in asm_file:
            line = line.strip()

            match = re.search(r"^\s*\-+\s+Core\s+(\w+)", line)
            if match:
                core_id = hex(int(match.group(1)))[2:].upper()
                inst_pt = 0
                conf_bin = ""

            if re.search(r"^\s*Instructions", line):
                is_in_inst = 1
                is_in_data = 0
                is_in_conf = 0
            elif re.search(r"^\s*Data", line):
                is_in_inst = 0
                is_in_data = 1
                is_in_conf = 0
            elif re.search(r"^\s*Configuration", line):
                is_in_inst = 0
                is_in_data = 0
                is_in_conf = 1
            elif re.search(r"^\s*\-+\s+Core\s+(\w+)", line):
                is_in_inst = 0
                is_in_data = 0
                is_in_conf = 0

            # instruction assemble
            if is_in_inst:
                inst = re.search(r"^\s*(\w+)\s+(.*)$", line)
                if inst:
                    inst_pt += 1
                    inst_bin = ""

                    opcode = inst.group(1)
                    if opcode in ["ADD", "SUB", "MULT", "GEQ", "LE", "DIV"]:
                        inst_bin += opcode_decode(opcode)
                        regs = re.search(r"^(\w+)\,\s+(\w+)\,\s+(\w+)", inst.group(2))
                        reg_lst = [regs.group(1), regs.group(2), regs.group(3)]
                        for reg in reg_lst:
                            if re.search(r"^sys", reg):
                                inst_bin += reg_decode(reg)
                            elif re.search(r"^r[0-7]$", reg):
                                regnum = re.search(r"^r([0-7])$", reg)
                                inst_bin += bin(int(regnum.group(1)))[2:].zfill(4)
                            else:
                                print("ERROR: invalid reg identifier {}!".format(reg))

                    elif opcode in ["MOV", "SQRT"]:
                        inst_bin += opcode_decode(opcode)
                        regs = re.search(r"^(\w+)\,\s+(\w+)", inst.group(2))
                        reg_lst = [regs.group(1), "r0", regs.group(2)]
                        for reg in reg_lst:
                            if re.search(r"^sys", reg):
                                inst_bin += reg_decode(reg)
                            elif re.search(r"^r[0-7]$", reg):
                                regnum = re.search(r"^r([0-7])$", reg)
                                inst_bin += bin(int(regnum.group(1)))[2:].zfill(4)
                            else:
                                print("ERROR: invalid reg identifier {}!".format(reg))
                    
                    elif opcode in ["UMOV", "DMOV", "LMOV", "RMOV"]:
                        inst_bin += opcode_decode(opcode)
                        fields = re.search(r"^(\w+)\((\w+)\)\,\s+(\w+)", inst.group(2))
                        dst, cid, src = fields.group(1), fields.group(2), fields.group(3)
                        if re.search(r"^sys", dst):
                            inst_bin += reg_decode(dst)
                        elif re.search(r"^r[0-7]$", dst):
                            regnum = re.search(r"^r([0-7])$", dst)
                            inst_bin += bin(int(regnum.group(1)))[2:].zfill(4)
                        else:
                            print("ERROR: invalid reg identifier {}!".format(dst))

                        if re.search(r"^[0-7]$", cid): # !!! REVISIT: temp cid 0 - 7
                            inst_bin += bin(int(cid))[2:].zfill(4)
                        else:
                            print("ERROR: invalid core id {}!".format(cid))

                        if re.search(r"^sys", src):
                            inst_bin += reg_decode(src)
                        elif re.search(r"^r[0-7]$", src):
                            regnum = re.search(r"^r([0-7])$", src)
                            inst_bin += bin(int(regnum.group(1)))[2:].zfill(4)
                        else:
                            print("ERROR: invalid reg identifier {}!".format(src))

                    else:
                        print("ERROR: invalid opcode {}!".format(opcode))

                    reg_addr = hex(inst_pt + 7)[2:].upper()
                    reg_bin = hex(int(inst_bin, 2))[2:].zfill(4).upper()
                    bin_file_line = "id = {}, mode = 1, addr = {}, data = {}\n".format(core_id, reg_addr, reg_bin)
                    bin_file_lst.append(bin_file_line)

            # data assemble
            if is_in_data:
                store = re.search(r"^\s*(\w+)\:\s+(.*)", line)
                if store:
                    regnum = re.search(r"^r([0-7])$", store.group(1))
                    if regnum:
                        reg_addr = hex(int(regnum.group(1)))[2:].upper()
                        datanum = re.search(r"^([-+]?[0-9]+\.[0-9]+)", store.group(2))
                        
                        if datanum:
                            data_bin = hex(np.float16(datanum.group(1)).view('H'))[2:].zfill(4).upper()
                        else:
                            print("ERROR: invalid fp number {}!".format(datanum.group(1)))

                    else:
                        print("ERROR: invalid reg identifier {}!".format(regnum.group(1)))

                    bin_file_line = "id = {}, mode = 0, addr = {}, data = {}\n".format(core_id, reg_addr, data_bin)
                    bin_file_lst.append(bin_file_line)

            # configuration assemble
            if is_in_conf:
                iteration = re.search(r"^\s*iteration\:\s+(\w+)", line)
                if iteration:
                    if iteration.group(1) != "Inf":
                        iter_num = iteration.group(1)
                        conf_bin = hex(int(iter_num))[2:0].zfill(4).upper()
                        bin_file_line = "id = {}, mode = 1, addr = 1, data = {}\n".format(core_id, conf_bin)
                        bin_file_lst.append(bin_file_line)

                data_rf_sync_mask = re.search(r"data_rf_sync_mask:\s+([01]+)", line)
                if data_rf_sync_mask:
                    if (inst_pt == 0):
                        conf_bin = "8" + hex(0)[2:].upper() + hex(int(data_rf_sync_mask.group(1), 2))[2:].zfill(2).upper()
                    else:
                        conf_bin = "8" + hex(inst_pt - 1)[2:].upper() + hex(int(data_rf_sync_mask.group(1), 2))[2:].zfill(2).upper()
                    bin_file_line = "id = {}, mode = 1, addr = 0, data = {}\n".format(core_id, conf_bin)
                    bin_file_lst.append(bin_file_line)
             
    bin_file = open(bin_file_name, "w")
    for line in bin_file_lst:
        bin_file.write(line)
    bin_file.close()

if __name__=="__main__":
    if sys.argv[1] == "compile":
        files = os.listdir("./")
        files = [f for f in files if re.search(r"file_col_upp_[0-7].txt", f)]
        for f in files:
            file_name_wo_ext = f.split(".")[0]
            asm_file_name = file_name_wo_ext + ".txt"
            bin_file_name = file_name_wo_ext + ".mem.gen"
            assemble(asm_file_name, bin_file_name)
    elif sys.argv[1] == "apply":
        files = os.listdir("./")
        files = [f for f in files if re.search(r"file_col_upp_[0-7].txt", f)]
        for f in files:
            file_name_wo_ext = f.split(".")[0]
            os.system("cat " + file_name_wo_ext + ".mem.gen" + " > " + file_name_wo_ext + ".mem")
