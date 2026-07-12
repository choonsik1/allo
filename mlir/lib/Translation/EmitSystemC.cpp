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
#include "mlir/Dialect/Affine/IR/AffineOps.h"
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
// 
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

  // Connections: get/put emit .Pop()/.Push() instead of the base .read()/.write().
  void emitStreamGet(allo::StreamGetOp op) override;
  void emitStreamPut(allo::StreamPutOp op) override;
  // Non-blocking: try_get/try_put -> Connections .PopNB()/.PushNB() (fire-on-valid).
  // empty()/full() have no synthesizable Connections equivalent -> errored.
  void emitStreamTryGet(allo::StreamTryGetOp op) override;
  void emitStreamTryPut(allo::StreamTryPutOp op) override;
  void emitStreamEmpty(allo::StreamEmptyOp op) override;
  void emitStreamFull(allo::StreamFullOp op) override;

  // Sequential-stream body transform: a boundary memref arg becomes a Connections
  // stream port, so load a[i] -> port.Pop(), store b[i]=v -> port.Push(v).
  void emitAffineLoad(affine::AffineLoadOp op) override;
  void emitAffineStore(affine::AffineStoreOp op) override;
  // If `v` is a df.kernel memref arg turned into a stream, its dir ('i'/'o'); else 0.
  char streamArgDir(Value v);
  // True iff memref `v` is safe to stream: 1-D + only identity a[iv] load/stores.
  bool isSeqStreamable(Value v);

  // direction of stream arg `i` from the func's "stypes" attr: 'i','o', or 0.
  char streamDir(func::FuncOp func, unsigned i);
  // direction of memref arg `i` from the func's "arg_dirs" attr: 'i','o','b', or 0.
  char argDir(func::FuncOp func, unsigned i);

  // Region boundary arrays -> top-level Connections stream ports; the sc_main
  // testbench drives inputs and reads outputs (direction from arg_dirs).
  struct IOArray {
    std::string member; // top-level stream port name (e.g. "v11")
    std::string ctype;  // element C type (for the tb Combinational channel)
    int64_t total;      // flattened element count
    char dir;           // 'i' input (Push), 'o' output (Pop)
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

// arg_dirs is a string with one char per arg: 'i'=in, 'o'=out, 'b'=both, else '_'.
char SystemCModuleEmitter::argDir(func::FuncOp func, unsigned i) {
  auto attr = func->getAttrOfType<StringAttr>("arg_dirs");
  if (!attr)
    return 0;
  StringRef s = attr.getValue();
  if (i >= s.size())
    return 0;
  char c = s[i];
  return (c == 'i' || c == 'o' || c == 'b') ? c : 0;
}

// Safe-to-stream check: sequential single-pass access only. The stream transform
// ignores the load/store index, so it is correct ONLY if the array is 1-D and
// every access is an identity a[iv] (each element once, in order). Anything else
// (2-D, strided, reversed, gathered, re-read, or a non-load/store use) is NOT
// sequential and must use a memory port instead.
bool SystemCModuleEmitter::isSeqStreamable(Value v) {
  auto mt = llvm::dyn_cast<MemRefType>(v.getType());
  if (!mt || mt.getRank() != 1)
    return false;
  for (auto &use : v.getUses()) {
    Operation *op = use.getOwner();
    if (auto ld = llvm::dyn_cast<affine::AffineLoadOp>(op)) {
      if (!ld.getAffineMap().isIdentity())
        return false;
    } else if (auto st = llvm::dyn_cast<affine::AffineStoreOp>(op)) {
      if (!st.getAffineMap().isIdentity())
        return false;
    } else {
      return false; // any other use -> not a clean sequential scan
    }
    // Reject re-reads/re-writes: an identity a[iv] under an OUTER loop touches
    // each element more than once, which a stream (one element per handshake)
    // cannot reproduce. A 1-D single-pass scan sits inside exactly ONE loop.
    unsigned loops = 0;
    for (Operation *p = op->getParentOp();
         p && !llvm::isa<func::FuncOp>(p); p = p->getParentOp())
      if (llvm::isa<affine::AffineForOp>(p))
        loops++;
    if (loops != 1)
      return false;
  }
  return true;
}

// A df.kernel memref arg with a pure in/out direction is stream-ified into a
// Connections port; return that direction ('i'/'o'), else 0 (emit normally).
char SystemCModuleEmitter::streamArgDir(Value v) {
  auto barg = llvm::dyn_cast<BlockArgument>(v);
  if (!barg || !llvm::isa<MemRefType>(v.getType()))
    return 0;
  auto func = llvm::dyn_cast<func::FuncOp>(barg.getOwner()->getParentOp());
  if (!func || !func->hasAttr("df.kernel"))
    return 0;
  char d = argDir(func, barg.getArgNumber());
  // stream only pure in/out AND sequentially-safe args ('both' / random stay memref)
  return ((d == 'i' || d == 'o') && isSeqStreamable(v)) ? d : 0;
}

// Sequential-stream read:  <result> = <port>.Pop();   (index ignored — in order)
void SystemCModuleEmitter::emitAffineLoad(affine::AffineLoadOp op) {
  if (streamArgDir(op.getMemRef()) != 'i') {
    VhlsModuleEmitter::emitAffineLoad(op); // normal array load
    return;
  }
  indent();
  Value result = op.getResult();
  fixUnsignedType(result, op->hasAttr("unsigned"));
  emitValue(result);
  os << " = ";
  emitValue(op.getMemRef(), 0, false);
  os << ".Pop();";
  emitInfoAndNewLine(op);
}

// Sequential-stream write:  <port>.Push(<value>);   (index ignored — in order)
void SystemCModuleEmitter::emitAffineStore(affine::AffineStoreOp op) {
  if (streamArgDir(op.getMemRef()) != 'o') {
    VhlsModuleEmitter::emitAffineStore(op); // normal array store
    return;
  }
  indent();
  emitValue(op.getMemRef(), 0, false);
  os << ".Push(";
  emitValue(op.getValueToStore());
  os << ");";
  emitInfoAndNewLine(op);
}

//===----------------------------------------------------------------------===//
// emitFunction split: kernel module vs top wiring module
//===----------------------------------------------------------------------===//

void SystemCModuleEmitter::emitKernelModule(func::FuncOp func) {
  auto name = func.getName();
  os << "SC_MODULE(" << name << ") {\n";
  addIndent();

  // Clock + reset (required for synthesizable clocked threads).
  indent(); os << "sc_in_clk clk;\n";
  indent(); os << "sc_in<bool> rst;\n";

  // Ports + members from arguments.
  SmallVector<std::string, 4> streamPorts;
  for (auto arg : llvm::enumerate(func.getArguments())) {
    unsigned i = arg.index();
    Value v = arg.value();
    indent();
    if (auto st = llvm::dyn_cast<StreamType>(v.getType())) {
      // stream arg -> Connections::In/Out<T> port (direction from stypes)
      char d = streamDir(func, i);
      std::string pn = std::string(addName(v, /*isPtr=*/false).str());
      streamPorts.push_back(pn);
      os << (d == 'o' ? "Connections::Out< " : "Connections::In< ");
      os << getSCTypeName(st.getBaseType()) << " > " << pn << ";\n";
    } else if (auto mt = llvm::dyn_cast<MemRefType>(v.getType())) {
      char d = argDir(func, i);
      if (d == 'i' || d == 'o') {
        // sequential-stream: boundary array arg -> Connections stream port
        // (body's a[i]/b[i]=v become .Pop()/.Push() via the affine overrides)
        if (!isSeqStreamable(v))
          emitError(func, "SystemC backend: boundary array arg is not a "
                          "sequential 1-D scan (random/strided/2-D access) — "
                          "needs a memory port, not yet supported.");
        std::string pn = std::string(addName(v, /*isPtr=*/false).str());
        streamPorts.push_back(pn);
        os << (d == 'o' ? "Connections::Out< " : "Connections::In< ");
        os << getSCTypeName(mt.getElementType()) << " > " << pn << ";\n";
      } else {
        // non-directional memref -> internal array member (fallback)
        os << getSCTypeName(mt.getElementType()) << " " << addName(v, /*isPtr=*/false);
        for (auto s : mt.getShape())
          os << "[" << s << "]";
        os << ";\n";
      }
    }
  }

  // Constructor: name the ports + register a clocked, reset-aware thread.
  indent(); os << "SC_HAS_PROCESS(" << name << ");\n";
  indent(); os << name << "(sc_module_name n) : sc_module(n)";
  for (auto &pn : streamPorts)
    os << ", " << pn << "(\"" << pn << "\")";
  os << " {\n";
  addIndent();
  indent(); os << "SC_THREAD(run);\n";
  indent(); os << "sensitive << clk.pos();\n";
  indent(); os << "async_reset_signal_is(rst, false);\n";
  reduceIndent();
  indent(); os << "}\n";

  // run(): reset ports, wait, then free-running loop over the REUSED body.
  indent(); os << "void run() {\n";
  addIndent();
  for (auto &pn : streamPorts) {
    indent(); os << pn << ".Reset();\n";
  }
  indent(); os << "wait();\n";
  indent(); os << "while (1) {\n";
  addIndent();
  emitBlock(func.front()); // put/get now emit .Push()/.Pop()
  reduceIndent();
  indent(); os << "}\n";
  reduceIndent();
  indent(); os << "}\n";

  reduceIndent();
  os << "};\n\n";
}

// Connections get: <result> = <stream>[indices].Pop();
// (Base scalar path, with .read() -> .Pop(); block-streams deferred.)
void SystemCModuleEmitter::emitStreamGet(StreamGetOp op) {
  Value result = op.getResult();
  fixUnsignedType(result, op->hasAttr("unsigned"));
  auto stream = op->getOperand(0);
  int rank = 0;
  if (llvm::isa<StreamType>(stream.getType())) {
    unsigned dimIdx = 0;
    auto sst = llvm::dyn_cast<StreamType>(stream.getType());
    if (auto shapedType = llvm::dyn_cast<ShapedType>(sst.getBaseType())) {
      indent(); emitArrayDecl(result, false); os << ";\n";
      for (auto &shape : shapedType.getShape()) {
        indent();
        os << "for (int iv" << dimIdx << " = 0; iv" << dimIdx << " < " << shape
           << "; ++iv" << dimIdx++ << ") {\n";
        addIndent();
      }
      rank = dimIdx;
    }
  }
  indent();
  emitValue(result, rank);
  os << " = ";
  emitValue(stream, 0, false);
  if (llvm::isa<ShapedType>(stream.getType())) {
    auto idx = op->getAttrOfType<DenseI64ArrayAttr>("indices");
    for (int64_t v : idx.asArrayRef())
      os << "[" << v << "]";
  }
  os << ".Pop();";
  if (rank > 0) {
    os << "\n";
    for (int i = 0; i < rank; ++i) { reduceIndent(); indent(); os << "}\n"; }
  }
  emitInfoAndNewLine(op);
}

// Connections put: <stream>[indices].Push(<value>);
// (Base scalar path, with .write(v) -> .Push(v); block-streams deferred.)
void SystemCModuleEmitter::emitStreamPut(StreamPutOp op) {
  auto stream = op->getOperand(0);
  int rank = 0;
  if (llvm::isa<StreamType>(stream.getType())) {
    unsigned dimIdx = 0;
    auto sst = llvm::dyn_cast<StreamType>(stream.getType());
    if (auto shapedType = llvm::dyn_cast<ShapedType>(sst.getBaseType())) {
      for (auto &shape : shapedType.getShape()) {
        indent();
        os << "for (int iv" << dimIdx << " = 0; iv" << dimIdx << " < " << shape
           << "; ++iv" << dimIdx++ << ") {\n";
        addIndent();
      }
      rank = dimIdx;
    }
    indent();
    emitValue(stream, 0, false);
  } else {
    indent();
    emitValue(stream, 0, false);
    auto idx = op->getAttrOfType<DenseI64ArrayAttr>("indices");
    for (int64_t v : idx.asArrayRef())
      os << "[" << v << "]";
  }
  os << ".Push(";
  emitValue(op->getOperand(1), rank);
  os << ");";
  if (rank > 0) {
    os << "\n";
    for (int i = 0; i < rank; ++i) { reduceIndent(); indent(); os << "}\n"; }
  }
  emitInfoAndNewLine(op);
}

// Non-blocking get: <result>; <success> = <stream>[idx].PopNB(<result>);
// (Base try_get path, with .read_nb -> .PopNB.)
void SystemCModuleEmitter::emitStreamTryGet(StreamTryGetOp op) {
  Value result = op.getResult(0);
  Value success = op.getResult(1);
  fixUnsignedType(result, op->hasAttr("unsigned"));
  auto stream = op->getOperand(0);
  indent();
  emitValue(result);
  os << ";\n";
  indent();
  emitValue(success);
  os << " = ";
  emitValue(stream, 0, false);
  if (llvm::isa<ShapedType>(stream.getType())) {
    auto idx = op->getAttrOfType<DenseI64ArrayAttr>("indices");
    if (idx)
      for (int64_t v : idx.asArrayRef())
        os << "[" << v << "]";
  }
  os << ".PopNB(";
  emitValue(result);
  os << ");";
  emitInfoAndNewLine(op);
}

// Non-blocking put: <success> = <stream>[idx].PushNB(<value>);
void SystemCModuleEmitter::emitStreamTryPut(StreamTryPutOp op) {
  Value success = op.getResult();
  auto stream = op->getOperand(0);
  auto value = op->getOperand(1);
  indent();
  emitValue(success);
  os << " = ";
  emitValue(stream, 0, false);
  if (llvm::isa<ShapedType>(stream.getType())) {
    auto idx = op->getAttrOfType<DenseI64ArrayAttr>("indices");
    if (idx)
      for (int64_t v : idx.asArrayRef())
        os << "[" << v << "]";
  }
  os << ".PushNB(";
  emitValue(value);
  os << ");";
  emitInfoAndNewLine(op);
}

// Connections In/Out are latency-insensitive handshakes with no synthesizable
// empty()/full() introspection — use try_get()/try_put() (PopNB/PushNB) for
// fire-on-valid instead.
void SystemCModuleEmitter::emitStreamEmpty(StreamEmptyOp op) {
  emitError(op, "SystemC backend: stream empty() has no synthesizable Connections "
                "equivalent — use try_get() (PopNB) for fire-on-valid.");
}
void SystemCModuleEmitter::emitStreamFull(StreamFullOp op) {
  emitError(op, "SystemC backend: stream full() has no synthesizable Connections "
                "equivalent — use try_put() (PushNB) for fire-on-valid.");
}

void SystemCModuleEmitter::emitTopModule(func::FuncOp func) {
  auto parent = func->getParentOfType<ModuleOp>();
  os << "SC_MODULE(" << func.getName() << ") {\n";
  addIndent();

  // Clock + reset (fanned out to every submodule).
  indent(); os << "sc_in_clk clk;\n";
  indent(); os << "sc_in<bool> rst;\n";

  // Region boundary arrays -> top-level Connections stream ports (In=input,
  // Out=output; direction from arg_dirs). Recorded in ioArrays for the tb.
  for (auto arg : llvm::enumerate(func.getArguments())) {
    if (auto mt = llvm::dyn_cast<MemRefType>(arg.value().getType())) {
      char d = argDir(func, arg.index());
      std::string nm = std::string(addName(arg.value(), /*isPtr=*/false).str());
      std::string ct = std::string(getSCTypeName(mt.getElementType()).str());
      indent();
      os << (d == 'o' ? "Connections::Out< " : "Connections::In< ") << ct
         << " > " << nm << ";\n";
      int64_t total = 1;
      for (auto s : mt.getShape())
        total *= s;
      ioArrays.push_back({nm, ct, total, d});
    }
  }

  // The top body is stream_construct(s) + call(s). Collect them.
  SmallVector<StreamConstructOp, 4> channels;
  SmallVector<func::CallOp, 4> calls;
  for (auto &op : func.front()) {
    if (auto sc = llvm::dyn_cast<StreamConstructOp>(&op))
      channels.push_back(sc);
    else if (auto call = llvm::dyn_cast<func::CallOp>(&op))
      calls.push_back(call);
  }

  // Channel members: Connections::Combinational<T> vN;
  for (auto sc : channels) {
    auto st = llvm::dyn_cast<StreamType>(sc.getResult().getType());
    indent();
    os << "Connections::Combinational< " << getSCTypeName(st.getBaseType())
       << " > " << addName(sc.getResult(), /*isPtr=*/false) << ";\n";
  }
  // Submodule instance members: <callee> uN;
  SmallVector<std::string, 4> instNames;
  for (auto it : llvm::enumerate(calls)) {
    std::string inst = "u" + std::to_string(it.index());
    instNames.push_back(inst);
    indent();
    os << it.value().getCallee() << " " << inst << ";\n";
  }

  // Constructor: init list (channel names + instance names) + bindings.
  indent();
  os << "SC_CTOR(" << func.getName() << ")";
  std::string sep = " : ";
  for (auto &a : ioArrays) {
    os << sep << a.member << "(\"" << a.member << "\")";
    sep = ", ";
  }
  for (auto sc : channels) {
    os << sep << getName(sc.getResult()) << "(\"" << getName(sc.getResult())
       << "\")";
    sep = ", ";
  }
  for (auto it : llvm::enumerate(calls)) {
    os << sep << instNames[it.index()] << "(\"" << instNames[it.index()]
       << "\")";
    sep = ", ";
  }
  os << " {\n";
  addIndent();
  // Fan clk/rst into each instance; bind each STREAM operand to its channel;
  // record each MEMREF operand as a top-level I/O array for the testbench.
  for (auto it : llvm::enumerate(calls)) {
    auto call = it.value();
    auto callee = parent.lookupSymbol<func::FuncOp>(call.getCallee());
    indent(); os << instNames[it.index()] << ".clk(clk);\n";
    indent(); os << instNames[it.index()] << ".rst(rst);\n";
    // Stream operands AND stream-ified memref operands both bind port-to-port:
    //   u<k>.<calleeArg>(<channel-or-top-port>)
    for (auto opnd : llvm::enumerate(call.getOperands())) {
      if (llvm::isa<StreamType>(opnd.value().getType()) ||
          llvm::isa<MemRefType>(opnd.value().getType())) {
        indent();
        os << instNames[it.index()] << "."
           << getName(callee.getArgument(opnd.index())) << "("
           << getName(opnd.value()) << ");\n";
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
  std::string device_header = R"XXX(
//===------------------------------------------------------------*- C++ -*-===//
// Automatically generated file for SystemC (Catapult HLS / MatchLib Connections).
//===----------------------------------------------------------------------===//
#include <systemc.h>
#include <mc_connections.h>   // MatchLib Connections (LI valid/ready channels)
#include <mc_scverify.h>      // SCVerify testbench macros (CCS_MAIN / CCS_DESIGN)
#include <ac_int.h>
#include <ac_fixed.h>
#include <stdint.h>
#include <iostream>
// The reused Vivado-emitter body prints Vitis ap_(u)int types; alias them to
// Catapult's ac_int so the same body compiles. (TODO: emit ac_int/ac_fixed
// natively via a type-name override, like getCatapultTypeName in the Catapult
// emitter, and drop this shim.)
template <int W> using ap_int = ac_int<W, true>;
template <int W> using ap_uint = ac_int<W, false>;

)XXX";
  os << device_header;

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

  // Testbench: a Combinational channel per top stream port + clocked src/sink
  // threads. src Pushes a known pattern into every INPUT port; sink Pops + prints
  // every OUTPUT port then sc_stop()s. (Ignored by synthesis; only for csim.)
  if (!topName.empty()) {
    os << "SC_MODULE(tb) {\n";
    addIndent();
    indent(); os << "sc_clock clk;\n";
    indent(); os << "sc_signal<bool> rst;\n";
    indent(); os << topName << " dut;\n";
    for (auto &a : ioArrays) {
      indent();
      os << "Connections::Combinational< " << a.ctype << " > ch_" << a.member
         << ";\n";
    }
    indent(); os << "SC_HAS_PROCESS(tb);\n";
    indent();
    os << "tb(sc_module_name n) : sc_module(n), clk(\"clk\", 1, SC_NS), dut(\"dut\")";
    for (auto &a : ioArrays)
      os << ", ch_" << a.member << "(\"ch_" << a.member << "\")";
    os << " {\n";
    addIndent();
    indent(); os << "dut.clk(clk); dut.rst(rst);\n";
    for (auto &a : ioArrays) {
      indent();
      os << "dut." << a.member << "(ch_" << a.member << ");\n";
    }
    indent(); os << "SC_THREAD(src); sensitive << clk.posedge_event(); "
                    "async_reset_signal_is(rst, false);\n";
    indent(); os << "SC_THREAD(snk); sensitive << clk.posedge_event(); "
                    "async_reset_signal_is(rst, false);\n";
    reduceIndent();
    indent(); os << "}\n";
    // src: drive inputs
    indent(); os << "void src() {\n";
    addIndent();
    for (auto &a : ioArrays)
      if (a.dir == 'i') { indent(); os << "ch_" << a.member << ".ResetWrite();\n"; }
    indent(); os << "wait();\n";
    for (auto &a : ioArrays)
      if (a.dir == 'i') {
        indent();
        os << "for (int f = 0; f < " << a.total << "; ++f) ch_" << a.member
           << ".Push(f);\n";
      }
    reduceIndent();
    indent(); os << "}\n";
    // snk: read outputs, then stop
    indent(); os << "void snk() {\n";
    addIndent();
    for (auto &a : ioArrays)
      if (a.dir == 'o') { indent(); os << "ch_" << a.member << ".ResetRead();\n"; }
    indent(); os << "wait();\n";
    for (auto &a : ioArrays)
      if (a.dir == 'o') {
        indent();
        os << "std::cout << \"" << a.member << ":\"; for (int f = 0; f < "
           << a.total << "; ++f) std::cout << ' ' << ch_" << a.member
           << ".Pop(); std::cout << std::endl;\n";
      }
    indent(); os << "sc_stop();\n";
    reduceIndent();
    indent(); os << "}\n";
    reduceIndent();
    os << "};\n\n";

    os << "int sc_main(int, char *[]) {\n";
    addIndent();
    indent(); os << "tb t(\"t\");\n";
    indent(); os << "t.rst = 0; sc_start(1, SC_NS);\n";
    indent(); os << "t.rst = 1; sc_start();\n";
    indent(); os << "return 0;\n";
    reduceIndent();
    os << "}\n";
  }
}

//===----------------------------------------------------------------------===//
// Registration
// - entry point that actually runs emitter
//===----------------------------------------------------------------------===//

LogicalResult allo::emitSystemC(ModuleOp module, llvm::raw_ostream &os) {
  AlloEmitterState state(os); // creates shared emitter state around output stream os
  SystemCModuleEmitter(state).emitModule(module); // constructs emitter and walks whole module, printing SystemC
  return failure(state.encounteredError); // reports success/failure
}

void allo::registerEmitSystemCTranslation() { // registers emitter as an MLIR translation named emit-systemc
  static TranslateFromMLIRRegistration toSystemC(
      "emit-systemc", "Emit SystemC", emitSystemC,
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
