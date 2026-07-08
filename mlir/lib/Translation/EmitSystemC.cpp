/*
 * Copyright Allo authors. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Minimal SystemC (sc_fifo) backend — Track B / X1.
 * Based on EmitCatapultHLS.cpp; subclasses the Vivado emitter so all loop/arith/
 * memref emission is REUSED. Only the module/thread STRUCTURE + sc_fifo channel
 * construction are SystemC-specific. put/get already emit .write()/.read() in the
 * base, which is exactly sc_fifo's API, so they are reused unchanged.
 *
 * Target = the hand-verified golden in
 *   Allo_extension/systemc_backend/golden_producer_consumer.cpp
 *   Stream[T,depth] -> sc_fifo<T>(depth) ; put->write ; get->read
 *   @df.kernel      -> SC_MODULE + SC_THREAD(run)
 *   @df.region/top  -> wiring SC_MODULE (sc_fifo members + submodule instances + port binds)
 */

#include "allo/Translation/EmitSystemC.h"
#include "allo/Dialect/AlloDialect.h"
#include "allo/Dialect/AlloOps.h"
#include "allo/Dialect/Visitor.h"
#include "allo/Translation/EmitVivadoHLS.h" // reuse the Vhls emitter base
#include "allo/Translation/Utils.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Tools/mlir-translate/Translation.h"
#include "llvm/Support/raw_ostream.h"

using namespace mlir;
using namespace allo;

//===----------------------------------------------------------------------===//
// Type name for SC interface (ports / channels). Mirrors the Vhls emitter's
// (file-local, uncallable) getTypeName so port/channel types MATCH the reused
// body: i8/16/32/64 -> (u)intN_t, other widths -> ap_(u)int<N> (aliased to
// ac_int in the emitted header), f16 -> half, f32 -> float, fixed -> ap_(u)fixed.
//===----------------------------------------------------------------------===//

static SmallString<32> getSCTypeName(Type valType) {
  if (auto arrayType = llvm::dyn_cast<ShapedType>(valType))
    valType = arrayType.getElementType();

  if (llvm::isa<Float16Type>(valType))
    return SmallString<32>("half");
  else if (llvm::isa<Float32Type>(valType))
    return SmallString<32>("float");
  else if (llvm::isa<Float64Type>(valType))
    return SmallString<32>("double");
  else if (llvm::isa<IndexType>(valType))
    return SmallString<32>("int");
  else if (auto intType = llvm::dyn_cast<IntegerType>(valType)) {
    if (intType.getWidth() == 1)
      return SmallString<32>("bool");
    std::string sign =
        (intType.getSignedness() == IntegerType::SignednessSemantics::Unsigned)
            ? "u"
            : "";
    switch (intType.getWidth()) {
    case 8:
    case 16:
    case 32:
    case 64:
      return SmallString<32>(sign + "int" + std::to_string(intType.getWidth()) +
                             "_t");
    default:
      return SmallString<32>("ap_" + sign + "int<" +
                             std::to_string(intType.getWidth()) + ">");
    }
  } else if (auto fx = llvm::dyn_cast<allo::FixedType>(valType))
    return SmallString<32>("ap_fixed<" + std::to_string(fx.getWidth()) + ", " +
                           std::to_string(fx.getWidth() - fx.getFrac()) + ">");
  else if (auto ufx = llvm::dyn_cast<allo::UFixedType>(valType))
    return SmallString<32>("ap_ufixed<" + std::to_string(ufx.getWidth()) + ", " +
                           std::to_string(ufx.getWidth() - ufx.getFrac()) + ">");

  assert(false && "getSCTypeName: unsupported type");
  return SmallString<32>();
}

//===----------------------------------------------------------------------===//
// SystemC emitter — subclass of the Vhls emitter (reuse body emission).
//===----------------------------------------------------------------------===//

namespace {

class SystemCModuleEmitter : public allo::hls::VhlsModuleEmitter {
public:
  explicit SystemCModuleEmitter(AlloEmitterState &state)
      : allo::hls::VhlsModuleEmitter(state) {}

  void emitModule(ModuleOp module) override;

private:
  void emitKernelModule(func::FuncOp func); // @df.kernel -> SC_MODULE + SC_THREAD
  void emitTopModule(func::FuncOp func);    // @df.region/top -> wiring SC_MODULE

  // direction of stream arg `i` from the func's "stypes" attr: 'i','o', or 0.
  char streamDir(func::FuncOp func, unsigned i);

  // Top-level array I/O: which submodule instance.member holds each array
  // (recorded in emitTopModule, driven/printed by the sc_main testbench).
  struct IOArray {
    std::string inst;   // submodule instance (e.g. "u0")
    std::string member; // array member name  (e.g. "v0")
    int64_t total;      // flattened element count
    unsigned rank;      // number of dimensions (for the [0]...[0] flatten)
  };
  SmallVector<IOArray> ioArrays;
};

} // namespace

// stypes is a string with one char per arg: '_' = not a stream, 'i' = in, 'o' = out.
char SystemCModuleEmitter::streamDir(func::FuncOp func, unsigned i) {
  auto attr = func->getAttrOfType<StringAttr>("stypes");
  if (!attr)
    return 0;
  StringRef s = attr.getValue();
  if (i >= s.size())
    return 0;
  char c = s[i];
  return (c == 'i' || c == 'o') ? c : 0;
}

//===----------------------------------------------------------------------===//
// emitFunction split: kernel module vs top wiring module
//===----------------------------------------------------------------------===//

void SystemCModuleEmitter::emitKernelModule(func::FuncOp func) {
  auto name = func.getName();
  os << "SC_MODULE(" << name << ") {\n";
  addIndent();

  // Ports + members from arguments.
  for (auto arg : llvm::enumerate(func.getArguments())) {
    unsigned i = arg.index();
    Value v = arg.value();
    indent();
    if (auto st = llvm::dyn_cast<StreamType>(v.getType())) {
      // stream arg -> sc_fifo_in/out<T> port (direction from stypes)
      char d = streamDir(func, i);
      os << (d == 'o' ? "sc_fifo_out< " : "sc_fifo_in< ");
      os << getSCTypeName(st.getBaseType()) << " > " << addName(v, /*isPtr=*/false)
         << ";\n";
    } else if (auto mt = llvm::dyn_cast<MemRefType>(v.getType())) {
      // memref arg -> plain array member (TODO: I/O policy — ports vs channels)
      os << getSCTypeName(mt.getElementType()) << " " << addName(v, /*isPtr=*/false);
      for (auto s : mt.getShape())
        os << "[" << s << "]";
      os << ";\n";
    }
  }

  // Constructor + thread.
  indent();
  os << "SC_CTOR(" << name << ") { SC_THREAD(run); }\n";
  indent();
  os << "void run() {\n";
  addIndent();
  emitBlock(func.front()); // REUSE: affine.for / loads / arith / put(write) / get(read)
  reduceIndent();
  indent();
  os << "}\n";

  reduceIndent();
  os << "};\n\n";
}

void SystemCModuleEmitter::emitTopModule(func::FuncOp func) {
  auto parent = func->getParentOfType<ModuleOp>();
  os << "SC_MODULE(" << func.getName() << ") {\n";
  addIndent();

  // The top body is stream_construct(s) + call(s). Collect them.
  SmallVector<StreamConstructOp, 4> channels;
  SmallVector<func::CallOp, 4> calls;
  for (auto &op : func.front()) {
    if (auto sc = llvm::dyn_cast<StreamConstructOp>(&op))
      channels.push_back(sc);
    else if (auto call = llvm::dyn_cast<func::CallOp>(&op))
      calls.push_back(call);
  }

  // Channel members: sc_fifo<T> vN;
  for (auto sc : channels) {
    auto st = llvm::dyn_cast<StreamType>(sc.getResult().getType());
    indent();
    os << "sc_fifo< " << getSCTypeName(st.getBaseType()) << " > "
       << addName(sc.getResult(), /*isPtr=*/false) << ";\n";
  }
  // Submodule instance members: <callee> uN;
  SmallVector<std::string, 4> instNames;
  for (auto it : llvm::enumerate(calls)) {
    std::string inst = "u" + std::to_string(it.index());
    instNames.push_back(inst);
    indent();
    os << it.value().getCallee() << " " << inst << ";\n";
  }

  // Constructor: init list (fifo depths + instance names) + port bindings.
  indent();
  os << "SC_CTOR(" << func.getName() << ")";
  std::string sep = " : ";
  for (auto sc : channels) {
    auto st = llvm::dyn_cast<StreamType>(sc.getResult().getType());
    os << sep << getName(sc.getResult()) << "(" << (st ? st.getDepth() : 0)
       << ")";
    sep = ", ";
  }
  for (auto it : llvm::enumerate(calls)) {
    os << sep << instNames[it.index()] << "(\"" << instNames[it.index()]
       << "\")";
    sep = ", ";
  }
  os << " {\n";
  addIndent();
  // Bind each call's STREAM operand to the channel; record each MEMREF operand
  // as a top-level I/O array (instance.member) for the testbench to drive/read.
  for (auto it : llvm::enumerate(calls)) {
    auto call = it.value();
    auto callee = parent.lookupSymbol<func::FuncOp>(call.getCallee());
    for (auto opnd : llvm::enumerate(call.getOperands())) {
      if (llvm::isa<StreamType>(opnd.value().getType())) {
        indent();
        os << instNames[it.index()] << "."
           << getName(callee.getArgument(opnd.index())) << "("
           << getName(opnd.value()) << ");\n";
      } else if (auto mt =
                     llvm::dyn_cast<MemRefType>(opnd.value().getType())) {
        int64_t total = 1;
        for (auto d : mt.getShape())
          total *= d;
        ioArrays.push_back(
            {instNames[it.index()],
             std::string(getName(callee.getArgument(opnd.index())).str()),
             total, (unsigned)mt.getShape().size()});
      }
    }
  }
  reduceIndent();
  indent();
  os << "}\n";

  reduceIndent();
  os << "};\n\n";
}

//===----------------------------------------------------------------------===//
// emitModule — header + dispatch each func to kernel/top emission.
//===----------------------------------------------------------------------===//

void SystemCModuleEmitter::emitModule(ModuleOp module) {
  const char *header = R"XXX(
//===------------------------------------------------------------*- C++ -*-===//
// Automatically generated SystemC (sc_fifo) from Allo dataflow.
//===----------------------------------------------------------------------===//
#include <systemc.h>
#include <ac_int.h>
#include <stdint.h>
#include <iostream>
// The reused Vivado-emitter body prints Vitis ap_(u)int types; alias them to
// Catapult's ac_int so the same body compiles under SystemC. (TODO: emit ac_int
// natively via a type-name override, like the Catapult emitter.)
template <int W> using ap_int = ac_int<W, true>;
template <int W> using ap_uint = ac_int<W, false>;

)XXX";
  os << header;

  StringRef topName;
  for (auto func : module.getOps<func::FuncOp>()) {
    if (func->hasAttr("top")) {
      topName = func.getName();
      emitTopModule(func);
    } else if (func->hasAttr("df.kernel")) {
      emitKernelModule(func);
    }
    // else: helper funcs — TODO
  }

  // sc_main testbench: drive top-level input arrays with a known pattern
  // ([f] = f, flattened), run, then print every top-level array so the data
  // is observable/checkable. Arrays live inside submodule instances, accessed
  // as top_inst.<inst>.<member>; flattened via a pointer to element 0.
  if (!topName.empty()) {
    os << "int sc_main(int, char *[]) {\n";
    addIndent();
    indent();
    os << topName << " top_inst(\"top_inst\");\n";

    auto flatPtr = [&](const IOArray &a) {
      std::string s = "top_inst." + a.inst + "." + a.member;
      for (unsigned r = 0; r < a.rank; ++r)
        s += "[0]";
      return "&" + s;
    };

    // drive inputs
    for (auto &a : ioArrays) {
      indent();
      os << "{ auto *p = " << flatPtr(a) << "; for (int f = 0; f < " << a.total
         << "; ++f) p[f] = f; }\n";
    }

    indent();
    os << "sc_start();\n";

    // print all top-level arrays after the run
    for (auto &a : ioArrays) {
      indent();
      os << "{ auto *p = " << flatPtr(a) << "; std::cout << \"" << a.inst << "."
         << a.member << ":\"; for (int f = 0; f < " << a.total
         << "; ++f) std::cout << ' ' << p[f]; std::cout << std::endl; }\n";
    }

    indent();
    os << "return 0;\n";
    reduceIndent();
    os << "}\n";
  }
}

//===----------------------------------------------------------------------===//
// Registration
//===----------------------------------------------------------------------===//

LogicalResult allo::emitSystemC(ModuleOp module, llvm::raw_ostream &os) {
  AlloEmitterState state(os);
  SystemCModuleEmitter(state).emitModule(module);
  return failure(state.encounteredError);
}

void allo::registerEmitSystemCTranslation() {
  static TranslateFromMLIRRegistration toSystemC(
      "emit-systemc", "Emit SystemC (sc_fifo)", emitSystemC,
      [&](DialectRegistry &registry) {
        // clang-format off
        registry.insert<
          mlir::allo::AlloDialect,
          mlir::func::FuncDialect,
          mlir::arith::ArithDialect,
          mlir::scf::SCFDialect,
          mlir::affine::AffineDialect,
          mlir::math::MathDialect,
          mlir::memref::MemRefDialect,
          mlir::linalg::LinalgDialect
        >();
        // clang-format on
      });
}
