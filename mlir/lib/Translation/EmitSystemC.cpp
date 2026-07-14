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
#include "mlir/IR/AffineExpr.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/SymbolTable.h"
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

// Address width for a memory of `total` elements: ceil(log2(total)), min 1.
static unsigned scAddrW(int64_t total) {
  unsigned w = 1;
  while ((int64_t(1) << w) < total)
    w++;
  return w;
}

// Data width (bits) of a memory element type — used to size the packed request.
static unsigned scDataW(Type elt) {
  if (auto it = llvm::dyn_cast<IntegerType>(elt))
    return it.getWidth() < 1 ? 1 : it.getWidth();
  if (llvm::isa<Float16Type>(elt))
    return 16;
  if (llvm::isa<Float64Type>(elt))
    return 64;
  return 32; // f32 / index / default
}

//===----------------------------------------------------------------------===//
// Hierarchy flattening (pre-pass).
// A @df.kernel body may invoke a `dataflow` SUB-REGION (or a delegating kernel
// that does). C++/HLS keeps such nesting as nested dataflow functions, but a
// SystemC kernel is an SC_THREAD and cannot structurally instantiate a
// sub-region. So before emitting we INLINE every call to a non-leaf callee into
// the top, transitively, until the top is a FLAT set of stream constructs +
// leaf-kernel calls (which emitTopModule already handles). A flat design has no
// non-leaf calls -> this is a no-op.
//===----------------------------------------------------------------------===//

// A leaf compute kernel: a df.kernel whose body calls no other kernel/sub-region
// (only compute + stream get/put, and possibly pure helper functions).
static bool callsKernelOrRegion(func::FuncOp f, ModuleOp m) {
  bool found = false;
  f.walk([&](func::CallOp c) {
    if (auto callee = m.lookupSymbol<func::FuncOp>(c.getCallee()))
      if (callee->hasAttr("df.kernel") || callee->hasAttr("dataflow"))
        found = true;
  });
  return found;
}
static bool isLeafKernel(func::FuncOp f, ModuleOp m) {
  return f->hasAttr("df.kernel") && !callsKernelOrRegion(f, m);
}

static void flattenHierarchy(ModuleOp module) {
  func::FuncOp top;
  for (auto f : module.getOps<func::FuncOp>())
    if (f->hasAttr("top"))
      top = f;
  if (!top)
    return;
  // Repeatedly inline every top-body call to a non-leaf callee, substituting the
  // callee's block args with the actual operands (clone carries the mapping to
  // cloned results, so inner stream/kernel operands are remapped correctly).
  bool changed = true;
  while (changed) {
    changed = false;
    SmallVector<func::CallOp> toInline;
    top.walk([&](func::CallOp call) {
      auto callee = module.lookupSymbol<func::FuncOp>(call.getCallee());
      if (callee && callee.getBlocks().size() == 1 &&
          !isLeafKernel(callee, module))
        toInline.push_back(call);
    });
    for (auto call : toInline) {
      auto callee = module.lookupSymbol<func::FuncOp>(call.getCallee());
      IRMapping map;
      for (auto pair : llvm::zip(callee.getArguments(), call.getOperands()))
        map.map(std::get<0>(pair), std::get<1>(pair));
      OpBuilder builder(call);
      for (auto &op : callee.front().without_terminator())
        builder.clone(op, map);
      call.erase();
      changed = true;
    }
  }
  // Erase the now-dead inlined funcs (delegating kernels + sub-regions); leaf
  // kernels + helpers stay (still referenced by the flattened top).
  bool erased = true;
  while (erased) {
    erased = false;
    for (auto f : llvm::make_early_inc_range(module.getOps<func::FuncOp>()))
      if (!f->hasAttr("top") && SymbolTable::symbolKnownUseEmpty(f, module)) {
        f.erase();
        erased = true;
      }
  }
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
  // If `v` is a df.kernel memref arg that is directional but NOT sequentially
  // streamable (random/strided/2-D), it becomes a random-access MEMORY PORT.
  // Returns its dir ('i' read-only supported now; 'o'/'b' not yet), else 0.
  char memPortArgDir(Value v);
  // True iff memref `v` is safe to stream: 1-D + only identity a[iv] load/stores.
  bool isSeqStreamable(Value v);

  // Emit a single affine expr (dims/symbols resolved via `operands`, split at
  // `numDims`) as a C++ index expression — a local reimplementation of the
  // base's file-local AffineExprEmitter (not reachable from this file).
  void emitAffineExprSC(AffineExpr e, ValueRange operands, unsigned numDims);
  // Emit the row-major FLAT element index (memory-port address) of an affine
  // load or store: Σ result[k] * stride[k].
  void emitFlatIndexCore(AffineMap map, ArrayRef<int64_t> shape,
                         ValueRange operands);
  void emitFlatIndex(affine::AffineLoadOp op);
  void emitFlatIndex(affine::AffineStoreOp op);
  // For a region boundary arg, the memory-port dir of the kernel arg it feeds.
  char regArgMemPort(func::FuncOp top, Value regArg);

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
    int fileIdx;        // input<fileIdx>.data / output<fileIdx>.data
  };
  SmallVector<IOArray> ioArrays;

  // Region boundary array routed to an internal memory (random-access port):
  //   dir 'i' -> AlloMem  (LOAD, req+rsp), preloaded from input<fileIdx>.data
  //   dir 'o' -> AlloMemW (STORE, req only), read out to output<fileIdx>.data
  struct MemArray {
    std::string base;   // region arg name (kernel binds base_req[/base_rsp])
    std::string ctype;  // element C type
    int64_t total;      // element count (memory depth)
    unsigned addrw, dataw;
    char dir;           // 'i' read-only, 'o' write-only
    int fileIdx;        // input<fileIdx>.data / output<fileIdx>.data
  };
  SmallVector<MemArray> memArrays;

  // One PHYSICAL memory per (kernel instance, memory-port arg). A boundary array
  // shared by several grid replicas is REPLICATED: each client gets its own
  // memory + channels. Reads preload every replica from the same input file;
  // writes (disjoint pid-indexed elements) are summed across replicas at readout.
  struct MemInst {
    std::string chan;   // unique base name (mp<call>_<arg>) for channels + memory
    std::string inst;   // kernel instance name (u<call>)
    std::string port;   // kernel port name (callee arg)
    std::string ctype;
    int64_t total;
    unsigned addrw, dataw;
    char dir;           // 'i' read / 'o' write
    int fileIdx;        // the region array's file index (preload / readout)
  };
  SmallVector<MemInst> memInsts;
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

// A df.kernel memref arg that is directional but NOT sequentially streamable is
// a random-access memory port. Only INPUT (read-only, LOAD) is wired for now;
// 'o'/'b' (store side) return their dir so the caller can error cleanly.
char SystemCModuleEmitter::memPortArgDir(Value v) {
  auto barg = llvm::dyn_cast<BlockArgument>(v);
  if (!barg || !llvm::isa<MemRefType>(v.getType()))
    return 0;
  auto func = llvm::dyn_cast<func::FuncOp>(barg.getOwner()->getParentOp());
  if (!func || !func->hasAttr("df.kernel"))
    return 0;
  char d = argDir(func, barg.getArgNumber());
  if (d != 'i' && d != 'o' && d != 'b')
    return 0;
  return isSeqStreamable(v) ? 0 : d; // streamable -> handled by the stream path
}

// Local reimplementation of the base's file-local affine-expr emitter: walk the
// expr, resolving dim/symbol positions to their operand SSA names via emitValue.
void SystemCModuleEmitter::emitAffineExprSC(AffineExpr e, ValueRange operands,
                                            unsigned numDims) {
  switch (e.getKind()) {
  case AffineExprKind::Constant:
    os << llvm::cast<AffineConstantExpr>(e).getValue();
    return;
  case AffineExprKind::DimId:
    emitValue(operands[llvm::cast<AffineDimExpr>(e).getPosition()]);
    return;
  case AffineExprKind::SymbolId:
    emitValue(operands[numDims + llvm::cast<AffineSymbolExpr>(e).getPosition()]);
    return;
  default:
    break;
  }
  auto bin = llvm::cast<AffineBinaryOpExpr>(e);
  if (e.getKind() == AffineExprKind::CeilDiv) {
    os << "((";
    emitAffineExprSC(bin.getLHS(), operands, numDims);
    os << " + ";
    emitAffineExprSC(bin.getRHS(), operands, numDims);
    os << " - 1) / ";
    emitAffineExprSC(bin.getRHS(), operands, numDims);
    os << ")";
    return;
  }
  const char *opstr = " + ";
  switch (e.getKind()) {
  case AffineExprKind::Add: opstr = " + "; break;
  case AffineExprKind::Mul: opstr = " * "; break;
  case AffineExprKind::Mod: opstr = " % "; break;
  case AffineExprKind::FloorDiv: opstr = " / "; break;
  default: assert(false && "unexpected affine expr kind"); break;
  }
  os << "(";
  emitAffineExprSC(bin.getLHS(), operands, numDims);
  os << opstr;
  emitAffineExprSC(bin.getRHS(), operands, numDims);
  os << ")";
}

// Row-major flatten of a (multi-dim) affine index -> one C++ expression.
void SystemCModuleEmitter::emitFlatIndexCore(AffineMap map,
                                             ArrayRef<int64_t> shape,
                                             ValueRange operands) {
  unsigned n = map.getNumResults();
  SmallVector<int64_t> stride(n);
  int64_t s = 1;
  for (int k = (int)n - 1; k >= 0; --k) {
    stride[k] = s;
    s *= shape[k];
  }
  os << "(";
  for (unsigned k = 0; k < n; ++k) {
    if (k)
      os << " + ";
    os << "(";
    emitAffineExprSC(map.getResult(k), operands, map.getNumDims());
    os << ")";
    if (stride[k] != 1)
      os << " * " << stride[k];
  }
  os << ")";
}
void SystemCModuleEmitter::emitFlatIndex(affine::AffineLoadOp op) {
  auto mt = llvm::cast<MemRefType>(op.getMemRef().getType());
  SmallVector<Value> operands(op.getMapOperands().begin(),
                              op.getMapOperands().end());
  emitFlatIndexCore(op.getAffineMap(), mt.getShape(), operands);
}
void SystemCModuleEmitter::emitFlatIndex(affine::AffineStoreOp op) {
  auto mt = llvm::cast<MemRefType>(op.getMemRef().getType());
  SmallVector<Value> operands(op.getMapOperands().begin(),
                              op.getMapOperands().end());
  emitFlatIndexCore(op.getAffineMap(), mt.getShape(), operands);
}

// For a region boundary arg, look up the kernel arg it feeds and return that
// kernel arg's memory-port direction (0 if it is a normal stream boundary).
char SystemCModuleEmitter::regArgMemPort(func::FuncOp top, Value regArg) {
  auto parent = top->getParentOfType<ModuleOp>();
  for (auto &op : top.front())
    if (auto call = llvm::dyn_cast<func::CallOp>(&op))
      for (auto opnd : llvm::enumerate(call.getOperands()))
        if (opnd.value() == regArg) {
          auto callee = parent.lookupSymbol<func::FuncOp>(call.getCallee());
          if (callee)
            if (char d = memPortArgDir(callee.getArgument(opnd.index())))
              return d;
        }
  return 0;
}

// Sequential-stream read:  <result> = <port>.Pop();   (index ignored — in order)
void SystemCModuleEmitter::emitAffineLoad(affine::AffineLoadOp op) {
  // Random-access INPUT memory port: LOAD via req/resp handshake.
  if (memPortArgDir(op.getMemRef()) == 'i') {
    Value result = op.getResult();
    fixUnsignedType(result, op->hasAttr("unsigned"));
    auto mt = llvm::cast<MemRefType>(op.getMemRef().getType());
    int64_t total = 1;
    for (auto d : mt.getShape())
      total *= d;
    std::string reqT = "ac_int<" +
                       std::to_string(1 + scAddrW(total) +
                                      scDataW(mt.getElementType())) +
                       ", false>";
    auto nm = getName(op.getMemRef());
    indent();
    emitValue(result);
    os << ";\n";
    indent();
    os << nm << "_req.Push( (" << reqT << ")(";
    emitFlatIndex(op);
    os << ") << 1 );\n"; // opcode bit0 = 0 (LOAD), addr in bits [1..]
    indent();
    emitValue(result);
    os << " = " << nm << "_rsp.Pop();";
    emitInfoAndNewLine(op);
    return;
  }
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
  // Random-access OUTPUT memory port: STORE via a packed req (no response).
  if (memPortArgDir(op.getMemRef()) == 'o') {
    auto mt = llvm::cast<MemRefType>(op.getMemRef().getType());
    int64_t total = 1;
    for (auto d : mt.getShape())
      total *= d;
    unsigned addrw = scAddrW(total);
    std::string reqT =
        "ac_int<" + std::to_string(1 + addrw + scDataW(mt.getElementType())) +
        ", false>";
    auto nm = getName(op.getMemRef());
    indent();
    // req = (wdata << (1+ADDRW)) | (addr << 1) | 1   (opcode bit0 = 1 = STORE)
    os << nm << "_req.Push( ((" << reqT << ")(";
    emitValue(op.getValueToStore());
    os << ") << " << (1 + addrw) << ") | ((" << reqT << ")(";
    emitFlatIndex(op);
    os << ") << 1) | (" << reqT << ")1 );";
    emitInfoAndNewLine(op);
    return;
  }
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
      if ((d == 'i' || d == 'o') && isSeqStreamable(v)) {
        // sequential-stream: boundary array arg -> Connections stream port
        // (body's a[i]/b[i]=v become .Pop()/.Push() via the affine overrides)
        std::string pn = std::string(addName(v, /*isPtr=*/false).str());
        streamPorts.push_back(pn);
        os << (d == 'o' ? "Connections::Out< " : "Connections::In< ");
        os << getSCTypeName(mt.getElementType()) << " > " << pn << ";\n";
      } else if (d == 'i') {
        // random-access INPUT array -> memory port: Out<req> + In<T>.
        // Body loads become req.Push(LOAD,addr)/result=rsp.Pop() (affine over.).
        std::string pn = std::string(addName(v, /*isPtr=*/false).str());
        int64_t total = 1;
        for (auto s : mt.getShape())
          total *= s;
        std::string reqT =
            "ac_int<" +
            std::to_string(1 + scAddrW(total) + scDataW(mt.getElementType())) +
            ", false>";
        std::string reqn = pn + "_req", rspn = pn + "_rsp";
        streamPorts.push_back(reqn);
        streamPorts.push_back(rspn);
        os << "Connections::Out< " << reqT << " > " << reqn << ";\n";
        indent();
        os << "Connections::In< " << getSCTypeName(mt.getElementType()) << " > "
           << rspn << ";\n";
      } else if (d == 'o') {
        // random-access OUTPUT array -> write-only memory port: Out<req> only.
        // Body stores become req.Push(STORE,addr,val) (affine store override).
        std::string pn = std::string(addName(v, /*isPtr=*/false).str());
        int64_t total = 1;
        for (auto s : mt.getShape())
          total *= s;
        std::string reqT =
            "ac_int<" +
            std::to_string(1 + scAddrW(total) + scDataW(mt.getElementType())) +
            ", false>";
        std::string reqn = pn + "_req";
        streamPorts.push_back(reqn);
        os << "Connections::Out< " << reqT << " > " << reqn << ";\n";
      } else if (d == 'b') {
        emitError(func, "SystemC backend: random-access BOTH (read+write) array "
                        "memory port not yet supported.");
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

// empty()/full() map to the port introspection MatchLib Connections ports do
// provide: In<T>.Empty() (consumer port) and Out<T>.Full() (producer port).
//   <result> = <stream>[idx].Empty();   /   .Full();
// These are cycle-accurate in SIM; HLS synthesis rejects them only under the
// strict CONNECTIONS_ASSERT_ON_QUERY flag (off by default), so they are
// csim-faithful (like try_get/try_put, prefer a one-shot check, not a spin).
void SystemCModuleEmitter::emitStreamEmpty(StreamEmptyOp op) {
  Value result = op.getResult();
  fixUnsignedType(result, op->hasAttr("unsigned"));
  auto stream = op->getOperand(0);
  indent();
  emitValue(result);
  os << " = ";
  emitValue(stream, 0, false);
  if (llvm::isa<ShapedType>(stream.getType()))
    if (auto idx = op->getAttrOfType<DenseI64ArrayAttr>("indices"))
      for (int64_t v : idx.asArrayRef())
        os << "[" << v << "]";
  os << ".Empty();";
  emitInfoAndNewLine(op);
}
void SystemCModuleEmitter::emitStreamFull(StreamFullOp op) {
  Value result = op.getResult();
  fixUnsignedType(result, op->hasAttr("unsigned"));
  auto stream = op->getOperand(0);
  indent();
  emitValue(result);
  os << " = ";
  emitValue(stream, 0, false);
  if (llvm::isa<ShapedType>(stream.getType()))
    if (auto idx = op->getAttrOfType<DenseI64ArrayAttr>("indices"))
      for (int64_t v : idx.asArrayRef())
        os << "[" << v << "]";
  os << ".Full();";
  emitInfoAndNewLine(op);
}

void SystemCModuleEmitter::emitTopModule(func::FuncOp func) {
  auto parent = func->getParentOfType<ModuleOp>();
  os << "SC_MODULE(" << func.getName() << ") {\n";
  addIndent();

  // Clock + reset (fanned out to every submodule).
  indent(); os << "sc_in_clk clk;\n";
  indent(); os << "sc_in<bool> rst;\n";

  // Region boundary arrays -> top-level Connections stream ports (In=input,
  // Out=output; direction from arg_dirs). A random-access array is routed to an
  // internal AlloMem instead (memArrays). Input/output file indices are global
  // over ALL 'i'/'o' args in arg order, matching hls.py's input/output split.
  int inCount = 0, outCount = 0;
  for (auto arg : llvm::enumerate(func.getArguments())) {
    auto mt = llvm::dyn_cast<MemRefType>(arg.value().getType());
    if (!mt)
      continue;
    std::string nm = std::string(addName(arg.value(), /*isPtr=*/false).str());
    std::string ct = std::string(getSCTypeName(mt.getElementType()).str());
    int64_t total = 1;
    for (auto s : mt.getShape())
      total *= s;
    // Random-access array -> internal memory (no top-level port): INPUT reads
    // from input<k>.data, OUTPUT is read out to output<k>.data.
    char mp = regArgMemPort(func, arg.value());
    if (mp == 'i') {
      memArrays.push_back({nm, ct, total, scAddrW(total),
                           scDataW(mt.getElementType()), 'i', inCount++});
      continue;
    }
    if (mp == 'o') {
      memArrays.push_back({nm, ct, total, scAddrW(total),
                           scDataW(mt.getElementType()), 'o', outCount++});
      continue;
    }
    char d = argDir(func, arg.index());
    int fidx = (d == 'o') ? outCount++ : inCount++;
    indent();
    os << (d == 'o' ? "Connections::Out< " : "Connections::In< ") << ct
       << " > " << nm << ";\n";
    ioArrays.push_back({nm, ct, total, d, fidx});
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

  // Channel members. A Stream's depth (from its type) picks the flavor:
  //   depth 0  -> a bare Connections::Combinational (combinational wire)
  //   depth>=1 -> an AlloFifo<T,depth> between two _in/_out wires (buffered)
  for (auto sc : channels) {
    auto st = llvm::dyn_cast<StreamType>(sc.getResult().getType());
    std::string T = std::string(getSCTypeName(st.getBaseType()).str());
    std::string nm = std::string(addName(sc.getResult(), /*isPtr=*/false).str());
    if (st.getDepth() == 0) {
      indent();
      os << "Connections::Combinational< " << T << " > " << nm << ";\n";
    } else {
      indent();
      os << "Connections::Combinational< " << T << " > " << nm << "_in;\n";
      indent();
      os << "Connections::Combinational< " << T << " > " << nm << "_out;\n";
      indent();
      os << "AlloFifo< " << T << ", " << st.getDepth() << " > " << nm
         << "_fifo;\n";
    }
  }
  // Submodule instance members: <callee> uN;
  SmallVector<std::string, 4> instNames;
  for (auto it : llvm::enumerate(calls)) {
    std::string inst = "u" + std::to_string(it.index());
    instNames.push_back(inst);
    indent();
    os << it.value().getCallee() << " " << inst << ";\n";
  }
  // Discover one physical memory per (call, memory-port arg). A grid replica
  // that uses a shared boundary array gets its OWN memory (replication), keyed
  // uniquely by mp<call>_<arg>; its file index comes from the region array.
  for (auto it : llvm::enumerate(calls)) {
    auto callee = parent.lookupSymbol<func::FuncOp>(it.value().getCallee());
    for (auto opnd : llvm::enumerate(it.value().getOperands())) {
      Value ov = opnd.value();
      if (!llvm::isa<MemRefType>(ov.getType()))
        continue;
      Value carg = callee.getArgument(opnd.index());
      char mp = memPortArgDir(carg);
      if (!mp)
        continue;
      auto mt = llvm::cast<MemRefType>(carg.getType());
      int64_t total = 1;
      for (auto s : mt.getShape())
        total *= s;
      int fidx = -1;
      for (auto &m : memArrays)
        if (m.base == std::string(getName(ov).str()))
          fidx = m.fileIdx;
      memInsts.push_back(
          {"mp" + std::to_string(it.index()) + "_" +
               std::to_string(opnd.index()),
           instNames[it.index()], std::string(getName(carg).str()),
           std::string(getSCTypeName(mt.getElementType()).str()), total,
           scAddrW(total), scDataW(mt.getElementType()), mp, fidx});
    }
  }
  // Memory-port members: a req channel + memory (+ rsp channel for reads).
  //   'i' -> AlloMem  (req + rsp channels)
  //   'o' -> AlloMemW (req channel only)
  for (auto &mi : memInsts) {
    std::string reqT =
        "ac_int<" + std::to_string(1 + mi.addrw + mi.dataw) + ", false>";
    indent();
    os << "Connections::Combinational< " << reqT << " > " << mi.chan
       << "_req_ch;\n";
    if (mi.dir == 'i') {
      indent();
      os << "Connections::Combinational< " << mi.ctype << " > " << mi.chan
         << "_rsp_ch;\n";
    }
    indent();
    os << (mi.dir == 'o' ? "AlloMemW< " : "AlloMem< ") << mi.ctype << ", "
       << mi.total << ", " << mi.addrw << ", " << mi.dataw << " > " << mi.chan
       << "_mem;\n";
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
    auto st = llvm::dyn_cast<StreamType>(sc.getResult().getType());
    std::string nm = std::string(getName(sc.getResult()).str());
    if (st.getDepth() == 0) {
      os << sep << nm << "(\"" << nm << "\")";
    } else {
      os << sep << nm << "_in(\"" << nm << "_in\")";
      os << ", " << nm << "_out(\"" << nm << "_out\")";
      os << ", " << nm << "_fifo(\"" << nm << "_fifo\")";
    }
    sep = ", ";
  }
  for (auto it : llvm::enumerate(calls)) {
    os << sep << instNames[it.index()] << "(\"" << instNames[it.index()]
       << "\")";
    sep = ", ";
  }
  for (auto &mi : memInsts) {
    os << sep << mi.chan << "_req_ch(\"" << mi.chan << "_req_ch\")";
    if (mi.dir == 'i')
      os << ", " << mi.chan << "_rsp_ch(\"" << mi.chan << "_rsp_ch\")";
    os << ", " << mi.chan << "_mem(\"" << mi.chan << "_mem\")";
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
    // Bind each operand to the port THIS callee actually emitted for it. A grid
    // shares one boundary array across all replicas, but only the replica that
    // uses it (feeder/body/drain) has a port; unused args are internal members
    // and must NOT be bound. Decide per-(call,arg) from the callee's OWN arg.
    for (auto opnd : llvm::enumerate(call.getOperands())) {
      Value ov = opnd.value();
      Value carg = callee.getArgument(opnd.index());
      if (auto sty = llvm::dyn_cast<StreamType>(ov.getType())) {
        // stream operand -> stream channel. For a buffered stream (depth>=1) the
        // producer (Out) binds the FIFO's input wire, the consumer (In) its
        // output wire; a depth-0 stream is the bare Combinational.
        std::string chan = std::string(getName(ov).str());
        if (sty.getDepth() != 0)
          chan += (streamDir(callee, opnd.index()) == 'o') ? "_in" : "_out";
        indent();
        os << instNames[it.index()] << "." << getName(carg) << "(" << chan
           << ");\n";
      } else if (llvm::isa<MemRefType>(ov.getType())) {
        char mp = memPortArgDir(carg);
        std::string ca = std::string(getName(carg).str());
        std::string rb = std::string(getName(ov).str());
        if (mp) {
          // random-access memory port: bind req (+ rsp) to THIS client's own
          // (replicated) memory channels (mp<call>_<arg>).
          std::string chan = "mp" + std::to_string(it.index()) + "_" +
                             std::to_string(opnd.index());
          indent();
          os << instNames[it.index()] << "." << ca << "_req(" << chan
             << "_req_ch);\n";
          if (mp == 'i') {
            indent();
            os << instNames[it.index()] << "." << ca << "_rsp(" << chan
               << "_rsp_ch);\n";
          }
        } else if (streamArgDir(carg)) {
          // sequential-scan boundary -> single stream port
          indent();
          os << instNames[it.index()] << "." << ca << "(" << rb << ");\n";
        }
        // else: unused arg -> internal array member, nothing to bind.
      }
    }
  }
  // Wire each buffered-stream FIFO: clk/rst + its _in/_out wires.
  for (auto sc : channels) {
    auto st = llvm::dyn_cast<StreamType>(sc.getResult().getType());
    if (st.getDepth() == 0)
      continue;
    std::string nm = std::string(getName(sc.getResult()).str());
    indent(); os << nm << "_fifo.clk(clk);\n";
    indent(); os << nm << "_fifo.rst(rst);\n";
    indent(); os << nm << "_fifo.in(" << nm << "_in);\n";
    indent(); os << nm << "_fifo.out(" << nm << "_out);\n";
  }
  // Wire each internal memory: clk/rst + req channel (+ rsp channel for reads).
  for (auto &mi : memInsts) {
    indent(); os << mi.chan << "_mem.clk(clk);\n";
    indent(); os << mi.chan << "_mem.rst(rst);\n";
    indent(); os << mi.chan << "_mem.req(" << mi.chan << "_req_ch);\n";
    if (mi.dir == 'i') {
      indent(); os << mi.chan << "_mem.rsp(" << mi.chan << "_rsp_ch);\n";
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
  // Flatten any @df.region hierarchy (sub-regions called from kernels) into a
  // flat top before emission — SystemC can't nest regions inside a thread.
  flattenHierarchy(module);

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
#include <fstream>
#include <algorithm>
// The reused body emits bare max()/min() for the Allo max/min intrinsics (Vitis
// resolves them via hls::); bind them to std:: so the same body compiles here.
using std::max;
using std::min;
// The reused Vivado-emitter body prints Vitis ap_(u)int types; alias them to
// Catapult's ac_int so the same body compiles. (TODO: emit ac_int/ac_fixed
// natively via a type-name override, like getCatapultTypeName in the Catapult
// emitter, and drop this shim.)
// For W<=64, ap_(u)int is a plain ac_int alias. For W>64, ac_int has NO implicit
// conversion to a native int, so the reused body's narrowing `int32_t x = wide;`
// (e.g. a GEMM accumulator widened past 64 bits) fails to compile. Add one via a
// thin subclass ONLY in that range — ac_int's own operators remain exact/derived-
// to-base matches, so arithmetic still resolves to them (no builtin ambiguity).
template <int W, bool Big = (W > 64)> struct ap_sel {
  using s = ac_int<W, true>;
  using u = ac_int<W, false>;
};
template <int W> struct ap_sel<W, true> {
  struct s : ac_int<W, true> {
    using ac_int<W, true>::ac_int;
    operator long long() const { return this->to_int64(); }
  };
  struct u : ac_int<W, false> {
    using ac_int<W, false>::ac_int;
    operator unsigned long long() const { return this->to_uint64(); }
  };
};
template <int W> using ap_int = typename ap_sel<W>::s;
template <int W> using ap_uint = typename ap_sel<W>::u;

// Random-access memory port for a non-sequential boundary array (SystemC/
// Connections flow — internal memory, the only kind SystemC supports; useref
// 14.9.1). Request packed into one ac_int: bit0 = opcode (0=LOAD,1=STORE),
// [ADDRW] addr, [DATAW] wdata. Response = the read value T. One txn/cycle.
// The kernel is the CLIENT (Out<req>/In<rsp>); this module holds the storage.
template <typename T, int SIZE, int ADDRW, int DATAW>
SC_MODULE(AlloMem) {
  sc_in_clk clk;
  sc_in<bool> rst;
  Connections::In< ac_int<1 + ADDRW + DATAW, false> > req;
  Connections::Out<T> rsp;
  T mem[SIZE];
  SC_HAS_PROCESS(AlloMem);
  AlloMem(sc_module_name n) : sc_module(n), req("req"), rsp("rsp") {
    SC_THREAD(run);
    sensitive << clk.pos();
    async_reset_signal_is(rst, false);
  }
  void run() {
    req.Reset();
    rsp.Reset();
    wait();
    while (1) {
      ac_int<1 + ADDRW + DATAW, false> r = req.Pop();
      ac_int<ADDRW, false> a = r.template slc<ADDRW>(1);
      if (r[0])
        mem[a] = (T)(int64_t)r.template slc<DATAW>(1 + ADDRW).to_int64();
      else
        rsp.Push(mem[a]);
      wait();
    }
  }
};

// Write-only random-access memory port for a non-sequential OUTPUT array. Same
// packed request as AlloMem but STORE-only, so there is NO response port (a
// store is fire-and-forget; nothing to bind an rsp Out to). The testbench reads
// mem[] out after the run.  ⚠ the int64 cast makes float wdata lossy (defer).
template <typename T, int SIZE, int ADDRW, int DATAW>
SC_MODULE(AlloMemW) {
  sc_in_clk clk;
  sc_in<bool> rst;
  Connections::In< ac_int<1 + ADDRW + DATAW, false> > req;
  T mem[SIZE];
  SC_HAS_PROCESS(AlloMemW);
  AlloMemW(sc_module_name n) : sc_module(n), req("req") {
    SC_THREAD(run);
    sensitive << clk.pos();
    async_reset_signal_is(rst, false);
  }
  void run() {
    req.Reset();
    for (int z = 0; z < SIZE; z++) // 0-init so unwritten elements sum-merge as 0
      mem[z] = 0;
    wait();
    while (1) {
      ac_int<1 + ADDRW + DATAW, false> r = req.Pop();
      ac_int<ADDRW, false> a = r.template slc<ADDRW>(1);
      mem[a] = (T)(int64_t)r.template slc<DATAW>(1 + ADDRW).to_int64();
      wait();
    }
  }
};

// Depth-N buffered stream channel (Stream[T, N>=1]) — a SHIFT-REGISTER FIFO that
// Catapult can schedule. The read is the STATIC index buf[0] and the only
// runtime-indexed access is the append write buf[count], so there is NO
// same-cycle runtime read+write to buf (a ring buffer's buf[head]-read +
// buf[tail]-write couldn't be scheduled: the tool can't prove head != tail).
// Non-blocking, throughput 1: a dequeue frees a slot an enqueue can fill the
// same cycle. (Connections::Fifo is the official channel but trips a Catapult
// 2024.2 front-end assertion, sif_ci_expr:2080, on its named constructor.)
template <typename T, int N>
SC_MODULE(AlloFifo) {
  sc_in_clk clk;
  sc_in<bool> rst;
  Connections::In<T> in;
  Connections::Out<T> out;
  SC_HAS_PROCESS(AlloFifo);
  AlloFifo(sc_module_name nm) : sc_module(nm), in("in"), out("out") {
    SC_THREAD(run);
    sensitive << clk.pos();
    async_reset_signal_is(rst, false);
  }
  void run() {
    T buf[N];
    int count = 0;
    in.Reset();
    out.Reset();
    wait();
    while (1) {
      // enqueue and dequeue decisions are INDEPENDENT (both from the
      // start-of-cycle count) so the in.rdy / out.vld handshakes don't chain,
      // which is what let Catapult schedule the fixed-timing Connections I/O.
      bool deq = (count > 0) && out.PushNB(buf[0]);
      bool enq = false;
      T v;
      if (count < N)
        enq = in.PopNB(v);
      if (deq) { // shift the queue down by one (static indices)
        for (int k = 0; k < N - 1; k++)
          buf[k] = buf[k + 1];
        count--;
      }
      if (enq) { // append the new element (only runtime-indexed access)
        buf[count] = v;
        count++;
      }
      wait();
    }
  }
};

)XXX";
  os << device_header;

  // Helper functions (pure compute — no `top`/`df.kernel`/`dataflow` attr) are
  // emitted first as plain C++ free functions (reusing the base emitter's
  // return-by-pointer convention, matching the `helper(a,b,&r)` call sites the
  // kernel bodies already emit). They must precede the modules that call them.
  for (auto func : module.getOps<func::FuncOp>()) {
    if (!func->hasAttr("top") && !func->hasAttr("df.kernel") &&
        !func->hasAttr("dataflow"))
      VhlsModuleEmitter::emitFunction(func);
  }

  StringRef topName;
  for (auto func : module.getOps<func::FuncOp>()) {
    if (func->hasAttr("top")) {
      topName = func.getName();
      emitTopModule(func);
    } else if (func->hasAttr("df.kernel")) {
      emitKernelModule(func);
    }
    // else: sub-region (`dataflow` attr) — hierarchy, TODO (structural).
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
    // src: drive each INPUT port from input<k>.data (written by hls.py from A)
    indent(); os << "void src() {\n";
    addIndent();
    for (auto &a : ioArrays)
      if (a.dir == 'i') { indent(); os << "ch_" << a.member << ".ResetWrite();\n"; }
    indent(); os << "wait();\n";
    for (auto &a : ioArrays)
      if (a.dir == 'i') {
        indent();
        os << "{ std::ifstream _f(\"input" << a.fileIdx << ".data\"); " << a.ctype
           << " _v; for (int f = 0; f < " << a.total << "; ++f) { _f >> _v; ch_"
           << a.member << ".Push(_v); } }\n";
      }
    reduceIndent();
    indent(); os << "}\n";
    // A stream OUTPUT (snk drains it) drives sc_stop; if there are only
    // memory-port outputs, fall back to a time-based run (below).
    bool hasStreamOut = false;
    for (auto &a : ioArrays)
      if (a.dir == 'o')
        hasStreamOut = true;
    int64_t maxTotal = 1;
    for (auto &a : ioArrays)
      maxTotal = std::max(maxTotal, a.total);
    for (auto &m : memArrays)
      maxTotal = std::max(maxTotal, m.total);
    int64_t simCycles = maxTotal * 8 + 200;

    // snk: write each OUTPUT port to output<k>.data (read back into B by hls.py)
    indent(); os << "void snk() {\n";
    addIndent();
    for (auto &a : ioArrays)
      if (a.dir == 'o') { indent(); os << "ch_" << a.member << ".ResetRead();\n"; }
    indent(); os << "wait();\n";
    for (auto &a : ioArrays)
      if (a.dir == 'o') {
        indent();
        os << "{ std::ofstream _f(\"output" << a.fileIdx
           << ".data\"); for (int f = 0; f < " << a.total << "; ++f) _f << ch_"
           << a.member << ".Pop() << \"\\n\"; }\n";
      }
    if (hasStreamOut) { indent(); os << "sc_stop();\n"; }
    reduceIndent();
    indent(); os << "}\n";
    reduceIndent();
    os << "};\n\n";

    os << "int sc_main(int, char *[]) {\n";
    addIndent();
    indent(); os << "tb t(\"t\");\n";
    // Preload every INPUT memory (each shared-read replica gets its own copy)
    // from the array's input file (csim only: direct hierarchical poke of
    // AlloMem.mem[], done before reset is released).
    for (auto &mi : memInsts)
      if (mi.dir == 'i') {
        indent();
        os << "{ std::ifstream _f(\"input" << mi.fileIdx << ".data\"); "
           << mi.ctype << " _v; for (int f = 0; f < " << mi.total
           << "; ++f) { _f >> _v; t.dut." << mi.chan << "_mem.mem[f] = _v; } }\n";
      }
    indent(); os << "t.rst = 0; sc_start(1, SC_NS);\n";
    // A stream output stops the sim via sc_stop; otherwise run a fixed, generous
    // number of cycles (the kernel re-writes idempotently, so any time past one
    // full pass is safe) then read the memory-port outputs.
    indent(); os << "t.rst = 1;\n";
    if (hasStreamOut) {
      indent(); os << "sc_start();\n";
    } else {
      indent(); os << "sc_start(" << simCycles << ", SC_NS);\n";
    }
    // Read each OUTPUT array out to output<k>.data (into B by hls.py). Shared-
    // write arrays are SPLIT across replicas that each wrote disjoint elements
    // (zero-initialized elsewhere), so sum the replicas element-wise.
    for (auto &m : memArrays)
      if (m.dir == 'o') {
        indent();
        os << "{ std::ofstream _f(\"output" << m.fileIdx << ".data\");\n";
        indent();
        os << "  for (int f = 0; f < " << m.total << "; ++f) {\n";
        indent();
        os << "    long long _s = 0;\n";
        for (auto &mi : memInsts)
          if (mi.dir == 'o' && mi.fileIdx == m.fileIdx) {
            indent();
            os << "    _s += (long long) t.dut." << mi.chan << "_mem.mem[f];\n";
          }
        indent();
        os << "    _f << _s << \"\\n\";\n";
        indent();
        os << "  } }\n";
      }
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
