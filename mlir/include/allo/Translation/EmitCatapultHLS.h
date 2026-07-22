/*
 * Copyright Allo authors. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ALLO_TRANSLATION_EMITCATAPULTHLS_H
#define ALLO_TRANSLATION_EMITCATAPULTHLS_H

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Types.h"
#include "llvm/ADT/SmallString.h"

namespace mlir {
namespace allo {

// Map an MLIR type to its Catapult / Algorithmic-C C++ name (ac_int, ac_fixed,
// ac_ieee_float<binary32>, int32_t, ...). Shared with the SystemC emitter so
// both flows use Catapult-native types instead of Xilinx ap_int/ap_fixed.
llvm::SmallString<16> getCatapultTypeName(Type valType);

LogicalResult emitCatapultHLS(ModuleOp module, llvm::raw_ostream &os);
void registerEmitCatapultHLSTranslation();

} // namespace allo
} // namespace mlir

#endif // ALLO_TRANSLATION_EMITCATAPULTHLS_H 