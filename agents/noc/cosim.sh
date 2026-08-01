#!/bin/bash
# ---------------------------------------------------------------------------------------
# RTL cosim for a csyn'd design: Catapult SCVerify + Cadence Xcelium (NOT Questa/VCS).
#
#   ./cosim.sh <top>          e.g. ./cosim.sh hello_channel
#
# Expects csyn_out/<top>/Catapult/<top>.v1/ to exist (run `python <top>.py csyn` first).
#
# PREREQUISITE -- STIMULUS. csyn never writes input<k>.data, so the RTL would be driven with
# nothing and produce garbage. You must run csim *inside the csyn project directory* first:
#     python -c "... df.build(..., mode='csim', project='csyn_out/<top>') ..."
# That writes input0.data and a golden output0.data next to Catapult/. This script checks.
#
# TWO PATCHES ARE APPLIED BELOW. Both are Catapult-side, not Allo bugs:
#   1. SCVerify only ever emits a Questa makefile (hard `include ccs_questasim.mk`, not
#      SIMTOOL-conditional) -- swapped for ccs_ncsim.mk.
#   2. Catapult's generated scverify/sysc_sim.h uses Connections::Out<> without including
#      mc_connections.h, so it does not compile.
# ---------------------------------------------------------------------------------------
set -e
TOP=${1:?usage: ./cosim.sh <top>}
HERE=$(dirname "$(readlink -f "$0")")
PRJ=$HERE/csyn_out/$TOP
D=$PRJ/Catapult/$TOP.v1

[ -d "$D" ] || { echo "ERROR: no $D -- run 'python $TOP.py csyn' first"; exit 1; }
ls "$PRJ"/input*.data >/dev/null 2>&1 || {
  echo "ERROR: no input*.data in $PRJ."
  echo "       csyn does not write stimulus; run csim with project=$PRJ first."; exit 1; }

export MGC_HOME=/opt/siemens/catapult/2024.2/Mgc_home
export PATH=$MGC_HOME/bin:$PATH
export MGLS_LICENSE_FILE=1717@en-license-05.coecis.cornell.edu
export CDS_LIC_FILE=5280@en-license-05.coecis.cornell.edu
export NCSim_NC_ROOT=/opt/cadence/XCELIUM2403   # ccs_ncsim.mk errors "NC_ROOT must be set" without it
unset LD_PRELOAD                                # libtinfo/ncurses wrong-ELF preload noise

# patch 1: Questa-only makefile -> Xcelium
sed 's#include $(MGC_HOME)/shared/include/mkfiles/ccs_questasim.mk#include $(MGC_HOME)/shared/include/mkfiles/ccs_ncsim.mk#' \
    "$D/scverify/Verify_concat_sim_rtl_v_msim.mk" > "$D/scverify/Verify_ncsim.mk"
# patch 2: missing include in the Catapult-generated transactor
grep -q mc_connections.h "$D/scverify/sysc_sim.h" || \
  sed -i 's|^#include <systemc.h>$|#include <systemc.h>\n#include <mc_connections.h>|' "$D/scverify/sysc_sim.h"

cd "$D"
MK="scverify/Verify_ncsim.mk"
$MGC_HOME/bin/make -f $MK NCSim_NC_ROOT=$NCSim_NC_ROOT build > /tmp/co_${TOP}_build.log 2>&1
echo "BUILD OK   (/tmp/co_${TOP}_build.log)"
$MGC_HOME/bin/make -f $MK NCSim_NC_ROOT=$NCSim_NC_ROOT sim   > /tmp/co_${TOP}_sim.log   2>&1
echo "SIM OK     (/tmp/co_${TOP}_sim.log)"

# The verdict is NOT in the make log. It is the rewritten output<k>.data, plus the xmsim log.
echo "--- cycles ---"
grep -h "stopped at time" "$D/scverify/concat_sim_rtl_v_msim/sim.log" || true
echo "--- RTL outputs (compare against your reference) ---"
for f in "$PRJ"/output*.data; do echo "$(basename "$f"): $(tr '\n' ' ' < "$f")"; done

# NOTE ON VERIFYING: mtime ordering does NOT prove the RTL wrote these files. To be sure,
# overwrite output0.data with garbage and re-run the `sim` target alone; the RTL must
# regenerate the expected values.
