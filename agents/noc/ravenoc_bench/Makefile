# Cocotb benches for the three RaveNoC modules under comparison.
#
#   make fifo | vc_buffer | rr_arbiter | all
#
# Uses Xcelium, NOT Verilator. RaveNoC upstream is validated on Verilator 4.106 + cocotb
# 1.5.1; we are on Xcelium + cocotb 1.9.2 because that is the simulator this site licenses
# and the one the Allo/Catapult cosim side already uses -- keeping both sides on the same
# simulator is what makes the comparison meaningful. Consequence: Verilator tolerates a
# bare `output` net assigned in always_comb, Xcelium does not, which is why
# src/router/input_datapath.sv needed its full_o/empty_o patched to `output logic`.
#
# Env: conda activate ravenoc   (cocotb 1.9.2 -- NOT 2.x, which removed cocotb.fork)

RAVENOC ?= /work/shared/users/zsm9/noc_ref/ravenoc
SIM     ?= xcelium
TOPLEVEL_LANG ?= verilog

export CDS_LIC_FILE ?= 5280@en-license-05.coecis.cornell.edu

PKGS = $(RAVENOC)/bus_arch_sv_pkg/amba_axi_pkg.sv $(RAVENOC)/src/include/ravenoc_pkg.sv
COMPILE_ARGS += -incdir $(RAVENOC)/src/include -incdir $(RAVENOC)/bus_arch_sv_pkg

# Matched "vanilla" config -- see constants.py (the tb README's FLIT_BUFF=1 is stale; the
# code says 2). These macros drive ravenoc_pkg's parameters.
COMPILE_ARGS += -define FLIT_DATA_WIDTH=32
COMPILE_ARGS += -define FLIT_BUFF=2
COMPILE_ARGS += -define N_VIRT_CHN=2
COMPILE_ARGS += -define NOC_CFG_SZ_ROWS=2
COMPILE_ARGS += -define NOC_CFG_SZ_COLS=2

N_FLITS  ?= 64
N_GRANTS ?= 64
export N_FLITS
export N_GRANTS

ifeq ($(TARGET),fifo)
  VERILOG_SOURCES = $(PKGS) $(RAVENOC)/src/router/fifo.sv wrappers.sv
  TOPLEVEL = fifo_w
  MODULE   = tb_fifo
endif
ifeq ($(TARGET),vc_buffer)
  VERILOG_SOURCES = $(PKGS) $(RAVENOC)/src/router/fifo.sv $(RAVENOC)/src/router/vc_buffer.sv
  TOPLEVEL = vc_buffer
  MODULE   = tb_vc_buffer
endif
ifeq ($(TARGET),rr_arbiter)
  VERILOG_SOURCES = $(PKGS) $(RAVENOC)/src/router/rr_arbiter.sv wrappers.sv
  TOPLEVEL = rr_arbiter_w
  MODULE   = tb_rr_arbiter
endif

include $(shell cocotb-config --makefiles)/Makefile.sim

fifo:
	$(MAKE) TARGET=fifo sim
vc_buffer:
	$(MAKE) TARGET=vc_buffer sim
rr_arbiter:
	$(MAKE) TARGET=rr_arbiter sim
all: fifo vc_buffer rr_arbiter

.PHONY: fifo vc_buffer rr_arbiter all
