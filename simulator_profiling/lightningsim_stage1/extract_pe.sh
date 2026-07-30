#!/bin/bash
# Build a standalone per-kernel LightningSim project from a mesh kernel.cpp.
#   ./extract_pe.sh <mesh_kernel.cpp> <pe_name> <first_line> <last_line> <outdir>
# Example (Allo-EVA 2x2, node_0_0 spans lines 17..1511):
#   ./extract_pe.sh .../allo_prj_2x2_L336_I8_D1/kernel.cpp node_0_0 17 1511 ./pe_test
set -euo pipefail
SRC=$1; PE=$2; A=$3; B=$4; OUT=$5
mkdir -p "$OUT"
{ sed -n '1,16p' "$SRC"; echo; sed -n "${A},${B}p" "$SRC"; cat pe_harness.inc.cpp; } > "$OUT/kernel.cpp"
printf '#ifndef KERNEL_H\n#define KERNEL_H\n#include <cstdint>\nextern "C" { void top(int32_t *out); }\n#endif\n' > "$OUT/kernel.h"
cp tb.cpp run.tcl "$OUT/"
echo "Wrote $OUT. Now: cd $OUT && vitis_hls -f run.tcl && lightningsim --cli out.prj/solution1"
