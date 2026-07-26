/*
 * Copyright Allo authors. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Minimal SystemC backend
 * Based on EmitCatapultHLS.cpp; subclasses the Vivado emitter so all loop/arith/
 * memref emission is REUSED. Only the module/thread STRUCTURE + sc_fifo channel
 * construction are SystemC-specific. put/get already emit .write()/.read() in the
 * base, which is exactly sc_fifo's API, so they are reused unchanged.
 *
 *   Stream[T,depth] -> sc_fifo<T>(depth) ; put->write ; get->read
 *   @df.kernel      -> SC_MODULE + SC_THREAD(run)
 *   @df.region/top  -> wiring SC_MODULE (sc_fifo members + submodule instances + port binds)
 */

#include "allo/Translation/EmitSystemC.h"
#include "allo/Dialect/AlloDialect.h"
#include "allo/Dialect/AlloOps.h"
#include "allo/Dialect/Visitor.h"
#include "allo/Translation/EmitVivadoHLS.h" // reuse the Vhls emitter base
#include "allo/Translation/EmitCatapultHLS.h" // reuse Catapult's ac_int type map
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
// getTypeName so port/channel types MATCH the reused
// body: i8/16/32/64 -> (u)intN_t, other widths -> ap_(u)int<N> (aliased to
// ac_int in the emitted header), f16 -> half, f32 -> float, fixed -> ap_(u)fixed.
// 
//===----------------------------------------------------------------------===//

static SmallString<32> getSCTypeName(Type valType) {
  // For integers WIDER than 64 bits, use the ap_int shim (an ac_int subclass,
  // defined in the preamble) rather than a plain ac_int: ac_int omits the
  // implicit >64-bit narrowing to a native int (e.g. `int x = <ac_int<66>>`),
  // which the shim provides via operator long long(). (<=64-bit and non-integer
  // types get Catapult-native ac_int/ac_fixed/ac_ieee_float from the shared map.
  // Under __SYNTHESIS__ the shim is a plain ac_int alias, so RTL is unaffected.)
  Type scalar = valType;
  if (auto st = llvm::dyn_cast<ShapedType>(scalar))
    scalar = st.getElementType();
  if (auto it = llvm::dyn_cast<IntegerType>(scalar)) {
    if (it.getWidth() > 64) {
      bool uns =
          it.getSignedness() == IntegerType::SignednessSemantics::Unsigned;
      return SmallString<32>((uns ? "ap_uint<" : "ap_int<") +
                             std::to_string(it.getWidth()) + ">");
    }
  }
  // Delegate to the shared Catapult type mapping so the SystemC flow emits
  // Catapult-native ac_int/ac_fixed/ac_ieee_float<binary32>.
  return SmallString<32>(allo::getCatapultTypeName(valType).str());
}

// Address width for a memory of `total` elements: ceil(log2(total)), min 1.
static unsigned scAddrW(int64_t total) {
  unsigned w = 1;
  while ((int64_t(1) << w) < total) // 2´w
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

// Re-parented onto CatapultModuleEmitter (instead of VhlsModuleEmitter) so the
// SystemC flow reuses Catapult-native codegen: ac_int/ac_fixed types AND the
// Catapult loop/design pragmas (#pragma hls_pipeline_init_interval / hls_unroll
// / hls_design) via the inherited emitLoopDirectives -- the base Vivado emitter
// would otherwise emit Xilinx "#pragma HLS ..." which Catapult ignores. This
// emitter's own overrides (SC_MODULE structure, Connections/sc_signal links,
// Pop/Push get-put, affine load/store) still win.
class SystemCModuleEmitter : public allo::CatapultModuleEmitter {
public:
  explicit SystemCModuleEmitter(AlloEmitterState &state)
      : allo::CatapultModuleEmitter(state) {
    // SystemC/Catapult-native flow: f16 constants -> explicit half(...) ctor.
    state.acFloatConstCtor = true;
    state.explicitWideNarrow = true;
  }

  void emitModule(ModuleOp module) override;

private:
  void emitKernelModule(func::FuncOp func); // @df.kernel -> SC_MODULE + SC_THREAD
  void emitTopModule(func::FuncOp func);    // @df.region/top -> wiring SC_MODULE

  // Connections: get/put emit .Pop()/.Push() instead of the base .read()/.write().
  void emitStreamGet(allo::StreamGetOp op) override;
  void emitStreamPut(allo::StreamPutOp op) override;
  void emitChannelGet(allo::ChannelGetOp op) override;
  void emitChannelPut(allo::ChannelPutOp op) override;
  void emitWireGet(allo::WireGetOp op) override;
  void emitWirePut(allo::WirePutOp op) override;
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

  // The base emitValue uses EmitVivadoHLS's file-local getTypeName (ap_int/
  // ap_fixed). Override so scalar SSA decls in kernel bodies get Catapult-native
  // types (ac_int/ac_fixed) via getSCTypeName, matching the port/signal decls.
  void emitValue(Value val, unsigned rank = 0, bool isPtr = false,
                 std::string name = "") override;
  // The base emits a `union{ from; to; }` bit-converter for a bitcast; that has
  // a deleted ctor when a member is non-trivial (ac_ieee_float<binary16>). Emit
  // a std::memcpy bit-reinterpret instead (both operands are equal-width POD).
  void emitBitcast(arith::BitcastOp op) override;

  // Bit ops: the base emits the Vitis `ap_int` proxy forms (`x(hi,lo)`, `x[i]`)
  // via the ap_int-subclass shim, which does not interoperate with ac_int
  // (`ap_rng` won't assign to ac_int). Emit the NATIVE ac_int API instead:
  //   get slice -> num.slc<W>(lo)      set slice -> res=num; res.set_slc(lo,val)
  //   get bit   -> num[idx]            set bit   -> res=num; res[idx]=val
  void emitGetBit(allo::GetIntBitOp op) override;
  void emitSetBit(allo::SetIntBitOp op) override;
  void emitGetSlice(allo::GetIntSliceOp op) override;
  void emitSetSlice(allo::SetIntSliceOp op) override;

  // Random-access accesses to a memory-port arg via the memref dialect (dynamic
  // / 2-D indices) -- mirror the affine load/store rewrites (req.Push/rsp.Pop);
  // non-mem-port memrefs (local %alloc arrays) fall back to the base emitter.
  void emitLoad(memref::LoadOp op) override;
  void emitStore(memref::StoreOp op) override;
  // If `v` is a df.kernel memref arg turned into a stream, its dir ('i'/'o'); else 0.
  char streamArgDir(Value v);
  // If `v` is a df.kernel memref arg that is directional but NOT sequentially
  // streamable (random/strided/2-D), it becomes a random-access MEMORY PORT.
  // Returns its dir ('i' read-only supported now; 'o'/'b' not yet), else 0.
  char memPortArgDir(Value v);
  // Row-major flatten of direct (memref-dialect) index Values -> one C++ expr.
  void emitFlatIndexMemref(ValueRange indices, ArrayRef<int64_t> shape);
  // Shared memory-port transaction emitters (flat index supplied by callback,
  // so the affine and memref call sites reuse the same req/rsp lowering).
  void emitMemPortLoad(Value memref, Value result, bool isUnsigned,
                       llvm::function_ref<void()> emitIdx);
  void emitMemPortStore(Value memref, Value value,
                        llvm::function_ref<void()> emitIdx);
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
  //   dir 'i' -> AlloMem  (LOAD, req+rsp), preloaded from input<inIdx>.data
  //   dir 'o' -> AlloMemW (STORE, req only), read out to output<outIdx>.data
  //   dir 'b' -> AlloMem  (LOAD+STORE, req+rsp): preloaded AND read out (in-place)
  struct MemArray {
    std::string base;   // region arg name (kernel binds base_req[/base_rsp])
    std::string ctype;  // element C type
    int64_t total;      // element count (memory depth)
    unsigned addrw, dataw;
    char dir;           // 'i' read-only, 'o' write-only, 'b' read+write
    int inIdx;          // input<inIdx>.data  (preload; -1 if none)
    int outIdx;         // output<outIdx>.data (read-out; -1 if none)
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
    char dir;           // 'i' read / 'o' write / 'b' read+write
    int inIdx, outIdx;  // the region array's input/output file indices (-1 = none)
  };
  SmallVector<MemInst> memInsts;

  // A stream used by exactly ONE kernel (a self-FIFO: one kernel does
  // put+get+empty+full) can't map to a directional Connections port pair, so it
  // is realized as a local ac_channel member and its ops route to the inherited
  // Catapult (ac_channel) implementations.
  llvm::DenseSet<Value> localStreamArgs;       // the kernel block-arg Values
  llvm::DenseSet<Value> localStreamConstructs; // the top-level construct results
  bool isLocalStream(Value v) { return localStreamArgs.count(v) > 0; }

  // A boundary memref array used as a seq-streamable directional arg by MORE THAN
  // ONE kernel call (fan-in output: N producers; fan-out input: N consumers) can't
  // map to a single Connections::Combinational (exactly one writer + one reader; a
  // 2nd bind aborts MatchLib's ConManager). These callee block-args are forced to
  // the random-access memory-port path (per-PE AlloMem[W] replica) instead.
  llvm::DenseSet<Value> forceMemPortArgs;
  bool forceMemPort(Value v) { return forceMemPortArgs.count(v) > 0; }

  // When ONE kernel call passes the SAME stream/channel to MULTIPLE arg positions
  // (e.g. a drain PE that merges two sources with two put-sites into one output
  // stream), the callee has several block-args aliasing one channel. Emitting a
  // port per arg would bind >1 sc_out to one signal (SystemC E115). Map each such
  // duplicate block-arg -> the FIRST (primary) block-arg so they share one port.
  llvm::DenseMap<Value, Value> streamArgAlias;
  Value aliasOf(Value v) { return streamArgAlias.lookup(v); }

  // Number of df.kernel MODULE INSTANCES in the top (calls.size()). The single-
  // shot testbench advances the clock until this many kernels have finished one
  // pass (each bumps the csim-only __allo_done counter) before reading memory.
  int numKernelInsts = 0;
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
  // AND single-driver (multi-producer/consumer is forced to the memory-port path).
  return ((d == 'i' || d == 'o') && isSeqStreamable(v) && !forceMemPort(v)) ? d : 0;
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
  if (forceMemPort(v))
    return d; // multi-driver boundary: forced off the stream path onto memory
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

// Row-major flatten of direct index Values (memref dialect): Σ idx[k]*stride[k].
void SystemCModuleEmitter::emitFlatIndexMemref(ValueRange indices,
                                               ArrayRef<int64_t> shape) {
  unsigned n = indices.size();
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
    os << "(" << std::string(getName(indices[k]).str()) << ")";
    if (stride[k] != 1)
      os << " * " << stride[k];
  }
  os << ")";
}

// LOAD from a random-access memory port: result = mem[idx] -> req.Push(LOAD,
// addr); result = rsp.Pop();  (flat index emitted by `emitIdx`).
void SystemCModuleEmitter::emitMemPortLoad(Value memref, Value result,
                                           bool isUnsigned,
                                           llvm::function_ref<void()> emitIdx) {
  fixUnsignedType(result, isUnsigned);
  auto mt = llvm::cast<MemRefType>(memref.getType());
  int64_t total = 1;
  for (auto d : mt.getShape())
    total *= d;
  std::string reqT = "ac_int<" +
                     std::to_string(1 + scAddrW(total) +
                                    scDataW(mt.getElementType())) +
                     ", false>";
  auto nm = getName(memref);
  indent();
  emitValue(result);
  os << ";\n";
  indent();
  os << nm << "_req.Push( (" << reqT << ")(";
  emitIdx();
  os << ") << 1 );\n"; // opcode bit0 = 0 (LOAD), addr in bits [1..]
  indent();
  emitValue(result);
  os << " = " << nm << "_rsp.Pop();";
}

// STORE to a random-access memory port: mem[idx] = value -> a packed req (no
// response; AlloMem/AlloMemW applies it).  (flat index emitted by `emitIdx`.)
void SystemCModuleEmitter::emitMemPortStore(Value memref, Value value,
                                            llvm::function_ref<void()> emitIdx) {
  auto mt = llvm::cast<MemRefType>(memref.getType());
  int64_t total = 1;
  for (auto d : mt.getShape())
    total *= d;
  unsigned addrw = scAddrW(total);
  std::string reqT =
      "ac_int<" + std::to_string(1 + addrw + scDataW(mt.getElementType())) +
      ", false>";
  auto nm = getName(memref);
  indent();
  // req = (wdata << (1+ADDRW)) | (addr << 1) | 1   (opcode bit0 = 1 = STORE)
  os << nm << "_req.Push( ((" << reqT << ")(";
  // Transport the raw bit pattern for a float (an ac_int has no ctor from
  // half/ac_ieee_float); AlloMem/AlloMemW reconstruct via _mem_decode<T>.
  bool isFloat = llvm::isa<FloatType>(value.getType());
  if (isFloat)
    os << "_fbits(";
  emitValue(value);
  if (isFloat)
    os << ")";
  os << ") << " << (1 + addrw) << ") | ((" << reqT << ")(";
  emitIdx();
  os << ") << 1) | (" << reqT << ")1 );";
}

// memref.load: mem-port arg -> req/rsp; local %alloc array -> base emitter.
void SystemCModuleEmitter::emitLoad(memref::LoadOp op) {
  if (char d = memPortArgDir(op.getMemRef()); d == 'i' || d == 'b') {
    auto mt = llvm::cast<MemRefType>(op.getMemRef().getType());
    emitMemPortLoad(op.getMemRef(), op.getResult(), op->hasAttr("unsigned"),
                    [&]() { emitFlatIndexMemref(op.getIndices(), mt.getShape()); });
    emitInfoAndNewLine(op);
    return;
  }
  VhlsModuleEmitter::emitLoad(op); // normal local-array load
}

// memref.store: mem-port arg -> req; local %alloc array -> base emitter.
void SystemCModuleEmitter::emitStore(memref::StoreOp op) {
  if (char d = memPortArgDir(op.getMemRef()); d == 'o' || d == 'b') {
    auto mt = llvm::cast<MemRefType>(op.getMemRef().getType());
    emitMemPortStore(op.getMemRef(), op.getValueToStore(),
                     [&]() { emitFlatIndexMemref(op.getIndices(), mt.getShape()); });
    emitInfoAndNewLine(op);
    return;
  }
  VhlsModuleEmitter::emitStore(op); // normal local-array store
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

// Same shape as the base emitValue, but routes the type name through
// getSCTypeName (-> Catapult ac_int/ac_fixed) instead of the base's file-local
// getTypeName (-> Xilinx ap_int/ap_fixed).
void SystemCModuleEmitter::emitValue(Value val, unsigned rank, bool isPtr,
                                     std::string name) {
  assert(!(rank && isPtr) && "should be either an array or a pointer.");

  // Value has been declared before or is a constant number.
  if (isDeclared(val)) {
    os << getName(val);
    for (unsigned i = 0; i < rank; ++i)
      os << "[iv" << i << "]";
    return;
  }

  os << getSCTypeName(val.getType()) << " ";

  if (name == "") {
    os << addName(val, isPtr);
    for (unsigned i = 0; i < rank; ++i)
      os << "[iv" << i << "]";
  } else {
    os << addName(val, isPtr, name);
  }
}

// bitcast (e.g. fp16 <-> uint16 packing) via std::memcpy. The base's union
// converter has a deleted default ctor when a member is non-trivial, which
// ac_ieee_float<binary16> ('half') is.
void SystemCModuleEmitter::emitBitcast(arith::BitcastOp op) {
  Value result = op.getResult();
  fixUnsignedType(result, op->hasAttr("unsigned"));
  Value operand = op.getOperand();
  fixUnsignedType(operand, op->hasAttr("unsigned"));

  // Declare the result, then a same-width source temp, then memcpy the bits.
  indent();
  emitValue(result);
  os << ";\n";
  std::string rn = std::string(getName(result).str());
  indent();
  os << getSCTypeName(operand.getType()) << " _bc_" << rn << " = "
     << std::string(getName(operand).str()) << ";\n";
  indent();
  os << "std::memcpy(&" << rn << ", &_bc_" << rn << ", sizeof(" << rn << "));";
  emitInfoAndNewLine(op);
}

// --- native ac_int bit ops (replace the Vitis ap_int proxy forms) ---

void SystemCModuleEmitter::emitGetBit(allo::GetIntBitOp op) {
  Value result = op.getResult();
  fixUnsignedType(result, op->hasAttr("unsigned"));
  Value num = op.getNum();
  unsigned nw = num.getType().getIntOrFloatBitWidth();
  indent();
  emitValue(result); // declares "<T> <res>"
  os << ";\n";
  std::string rn = std::string(getName(result).str());
  // num may be a native C int (int32_t) with no bit-index op -> copy into an
  // ac_int temp first, which always supports [i]/.slc/.set_slc.
  indent();
  os << "ac_int<" << nw << ", true> _bs_" << rn << " = ";
  emitValue(num);
  os << ";\n";
  indent();
  os << rn << " = _bs_" << rn << "[";
  emitValue(op.getIndex());
  os << "];";
  emitInfoAndNewLine(op);
}

void SystemCModuleEmitter::emitSetBit(allo::SetIntBitOp op) {
  Value result = op.getResult();
  Value num = op.getNum();
  unsigned nw = num.getType().getIntOrFloatBitWidth();
  indent();
  emitValue(result); // "<T> <res>"
  os << ";\n";
  std::string rn = std::string(getName(result).str());
  indent();
  os << "ac_int<" << nw << ", true> _bs_" << rn << " = ";
  emitValue(num);
  os << ";\n";
  indent();
  os << "_bs_" << rn << "[";
  emitValue(op.getIndex());
  os << "] = ";
  emitValue(op.getVal());
  os << ";\n";
  indent();
  os << rn << " = _bs_" << rn << ";";
  emitInfoAndNewLine(op);
}

void SystemCModuleEmitter::emitGetSlice(allo::GetIntSliceOp op) {
  Value result = op.getResult();
  fixUnsignedType(result, op->hasAttr("unsigned"));
  Value num = op.getNum();
  unsigned nw = num.getType().getIntOrFloatBitWidth();
  unsigned w = result.getType().getIntOrFloatBitWidth();
  indent();
  emitValue(result); // "<T> <res>"
  os << ";\n";
  std::string rn = std::string(getName(result).str());
  indent();
  os << "ac_int<" << nw << ", true> _bs_" << rn << " = ";
  emitValue(num);
  os << ";\n";
  indent();
  os << rn << " = _bs_" << rn << ".slc<" << w << ">(";
  emitValue(op.getLo());
  os << ");";
  emitInfoAndNewLine(op);
}

void SystemCModuleEmitter::emitSetSlice(allo::SetIntSliceOp op) {
  Value result = op.getResult();
  Value num = op.getNum();
  unsigned nw = num.getType().getIntOrFloatBitWidth();
  // ac_int::set_slc(lo, val) requires an ac_int val (its width = #bits set);
  // the emitted val may be a plain C int -> wrap it in an ac_int of the val's
  // bit width so the right number of bits is written. The dst likewise needs an
  // ac_int temp (a native int32_t has no .set_slc).
  unsigned vw = op.getVal().getType().getIntOrFloatBitWidth();
  indent();
  emitValue(result); // "<T> <res>"
  os << ";\n";
  std::string rn = std::string(getName(result).str());
  indent();
  os << "ac_int<" << nw << ", true> _bs_" << rn << " = ";
  emitValue(num);
  os << ";\n";
  indent();
  os << "_bs_" << rn << ".set_slc(";
  emitValue(op.getLo());
  os << ", ac_int<" << vw << ", false>(";
  emitValue(op.getVal());
  os << "));\n";
  indent();
  os << rn << " = _bs_" << rn << ";";
  emitInfoAndNewLine(op);
}

// Sequential-stream read:  <result> = <port>.Pop();   (index ignored — in order)
void SystemCModuleEmitter::emitAffineLoad(affine::AffineLoadOp op) {
  // Random-access INPUT ('i') or read+write ('b') memory port: LOAD via req/resp.
  if (char d = memPortArgDir(op.getMemRef()); d == 'i' || d == 'b') {
    emitMemPortLoad(op.getMemRef(), op.getResult(), op->hasAttr("unsigned"),
                    [&]() { emitFlatIndex(op); });
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
  // Random-access OUTPUT ('o') or read+write ('b') memory port: STORE via a
  // packed req (no response; the AlloMem/AlloMemW applies it).
  if (char d = memPortArgDir(op.getMemRef()); d == 'o' || d == 'b') {
    emitMemPortStore(op.getMemRef(), op.getValueToStore(),
                     [&]() { emitFlatIndex(op); });
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
  SmallVector<std::string, 4> wireOutPorts; // sc_out wire ports: need reset action
  for (auto arg : llvm::enumerate(func.getArguments())) {
    unsigned i = arg.index();
    Value v = arg.value();
    // Duplicate stream/channel arg: reuse the primary arg's port (already named,
    // since it sits at a lower index). No new port, no reset, no binding.
    if (Value primary = aliasOf(v)) {
      state.nameTable[v] = getName(primary);
      continue;
    }
    indent();
    if (auto st = llvm::dyn_cast<StreamType>(v.getType())) {
      std::string pn = std::string(addName(v, /*isPtr=*/false).str());
      if (isLocalStream(v)) {
        // self-FIFO (one kernel both produces AND queries it): realized as a
        // bounded MatchLib AlloFifo wired as a self-loop at the top. This one
        // kernel therefore needs BOTH ends -- an Out (enq: put/try_put/full) and
        // an In (deq: get/try_get/empty). A bounded FIFO makes Full()/Empty()
        // correct, unlike an unbounded ac_channel.
        std::string T = std::string(getSCTypeName(st.getBaseType()).str());
        std::string en = pn + "_enq", dq = pn + "_deq";
        streamPorts.push_back(en);
        streamPorts.push_back(dq);
        os << "Connections::Out< " << T << " > " << en << ";\n";
        indent();
        os << "Connections::In< " << T << " > " << dq << ";\n";
      } else {
        // stream arg -> Connections::In/Out<T> port (direction from stypes)
        char d = streamDir(func, i);
        streamPorts.push_back(pn);
        os << (d == 'o' ? "Connections::Out< " : "Connections::In< ");
        os << getSCTypeName(st.getBaseType()) << " > " << pn << ";\n";
      }
    } else if (auto ct = llvm::dyn_cast<ChannelType>(v.getType())) {
      // channel arg -> Connections::In/Out<T> port (combinational, no buffer)
      char d = streamDir(func, i);
      std::string pn = std::string(addName(v, /*isPtr=*/false).str());
      streamPorts.push_back(pn);
      os << (d == 'o' ? "Connections::Out< " : "Connections::In< ");
      os << getSCTypeName(ct.getBaseType()) << " > " << pn << ";\n";
    } else if (auto wt = llvm::dyn_cast<WireType>(v.getType())) {
      // wire arg -> raw sc_in/sc_out<T> port (combinational, no handshake).
      // NOT added to streamPorts: sc ports have no Connections .Reset(). A driven
      // sc_out must still be set in the reset action (Catapult CIN-233), so an
      // OUT wire is tracked separately in wireOutPorts.
      char d = streamDir(func, i);
      std::string pn = std::string(addName(v, /*isPtr=*/false).str());
      if (d == 'o')
        wireOutPorts.push_back(pn);
      os << (d == 'o' ? "sc_out< " : "sc_in< ");
      os << getSCTypeName(wt.getBaseType()) << " > " << pn << ";\n";
    } else if (auto mt = llvm::dyn_cast<MemRefType>(v.getType())) {
      char d = argDir(func, i);
      if ((d == 'i' || d == 'o') && isSeqStreamable(v) && !forceMemPort(v)) {
        // sequential-stream: boundary array arg -> Connections stream port
        // (body's a[i]/b[i]=v become .Pop()/.Push() via the affine overrides)
        std::string pn = std::string(addName(v, /*isPtr=*/false).str());
        streamPorts.push_back(pn);
        os << (d == 'o' ? "Connections::Out< " : "Connections::In< ");
        os << getSCTypeName(mt.getElementType()) << " > " << pn << ";\n";
      } else if (d == 'i' || d == 'b') {
        // random-access INPUT ('i') or read+write ('b') array -> memory port:
        // Out<req> + In<T>. Body loads become req.Push(LOAD,addr)/rsp.Pop() and
        // (for 'b') stores become req.Push(STORE,addr,val) (affine overrides).
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
  // Raw sc_out wire ports must be driven in the reset action (Catapult CIN-233).
  for (auto &pn : wireOutPorts) {
    indent(); os << pn << ".write(0);\n";
  }
  indent(); os << "wait();\n";
  // Single-shot: run the body EXACTLY ONCE, then idle. Free-running (while(1)
  // around the body) is safe for stream kernels (they re-block on an empty input
  // after one pass) but WRONG for a read-modify-write `both` memory accumulator
  // (C[i]+=... re-accumulates every pass). Running once is correct for both, and
  // lets the tb read memory outputs after a real completion instead of guessing a
  // settle time. The idle `while(1) wait()` keeps the clocked thread alive.
  emitBlock(func.front()); // put/get now emit .Push()/.Pop()
  os << "#ifndef __SYNTHESIS__\n";
  indent(); os << "__allo_done++; // csim: this kernel finished its single pass\n";
  os << "#endif\n";
  indent(); os << "while (1) { wait(); }\n";
  reduceIndent();
  indent(); os << "}\n";

  reduceIndent();
  os << "};\n\n";
}

// Wire get: <result> = <wire>.read();  (raw combinational, no handshake)
void SystemCModuleEmitter::emitWireGet(WireGetOp op) {
  Value result = op.getResult();
  fixUnsignedType(result, op->hasAttr("unsigned"));
  indent();
  emitValue(result);
  os << " = ";
  emitValue(op->getOperand(0), 0, false);
  os << ".read();";
  emitInfoAndNewLine(op);
}

// Wire put: <wire>.write(<value>);  (raw combinational, no handshake)
void SystemCModuleEmitter::emitWirePut(WirePutOp op) {
  indent();
  emitValue(op->getOperand(0), 0, false);
  os << ".write(";
  emitValue(op->getOperand(1));
  os << ");";
  emitInfoAndNewLine(op);
}

// Connections channel get: <result> = <channel>.Pop();  (scalar handshake link)
void SystemCModuleEmitter::emitChannelGet(ChannelGetOp op) {
  Value result = op.getResult();
  fixUnsignedType(result, op->hasAttr("unsigned"));
  indent();
  emitValue(result);
  os << " = ";
  emitValue(op->getOperand(0), 0, false);
  os << ".Pop();";
  emitInfoAndNewLine(op);
}

// Connections channel put: <channel>.Push(<value>);  (scalar handshake link)
void SystemCModuleEmitter::emitChannelPut(ChannelPutOp op) {
  indent();
  emitValue(op->getOperand(0), 0, false);
  os << ".Push(";
  emitValue(op->getOperand(1));
  os << ");";
  emitInfoAndNewLine(op);
}

// Connections get: <result> = <stream>[indices].Pop();
// (Base scalar path, with .read() -> .Pop(); block-streams deferred.)
void SystemCModuleEmitter::emitStreamGet(StreamGetOp op) {
  if (isLocalStream(op->getOperand(0))) {
    // self-FIFO consumer end: <result> = <stream>_deq.Pop();
    Value result = op.getResult();
    fixUnsignedType(result, op->hasAttr("unsigned"));
    indent();
    emitValue(result);
    os << " = " << std::string(getName(op->getOperand(0)).str()) << "_deq.Pop();";
    emitInfoAndNewLine(op);
    return;
  }
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
  if (isLocalStream(op->getOperand(0))) {
    // self-FIFO producer end: <stream>_enq.Push(<value>);
    indent();
    os << std::string(getName(op->getOperand(0)).str()) << "_enq.Push(";
    emitValue(op->getOperand(1));
    os << ");";
    emitInfoAndNewLine(op);
    return;
  }
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
  if (isLocalStream(op->getOperand(0))) {
    // self-FIFO consumer end: <result>; <success> = <stream>_deq.PopNB(<result>);
    Value r = op.getResult(0), s = op.getResult(1);
    fixUnsignedType(r, op->hasAttr("unsigned"));
    indent();
    emitValue(r);
    os << ";\n";
    indent();
    emitValue(s);
    os << " = " << std::string(getName(op->getOperand(0)).str()) << "_deq.PopNB(";
    emitValue(r);
    os << ");";
    emitInfoAndNewLine(op);
    return;
  }
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
  if (isLocalStream(op->getOperand(0))) {
    // self-FIFO producer end: <success> = <stream>_enq.PushNB(<value>);
    Value s = op.getResult();
    indent();
    emitValue(s);
    os << " = " << std::string(getName(op->getOperand(0)).str()) << "_enq.PushNB(";
    emitValue(op->getOperand(1));
    os << ");";
    emitInfoAndNewLine(op);
    return;
  }
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
  if (isLocalStream(op->getOperand(0))) {
    // self-FIFO consumer end: <result> = <stream>_deq.Empty();
    Value result = op.getResult();
    fixUnsignedType(result, op->hasAttr("unsigned"));
    indent();
    emitValue(result);
    os << " = " << std::string(getName(op->getOperand(0)).str())
       << "_deq.Empty();";
    emitInfoAndNewLine(op);
    return;
  }
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
  if (isLocalStream(op->getOperand(0))) {
    // self-FIFO producer end: <result> = <stream>_enq.Full();
    Value result = op.getResult();
    fixUnsignedType(result, op->hasAttr("unsigned"));
    indent();
    emitValue(result);
    os << " = " << std::string(getName(op->getOperand(0)).str())
       << "_enq.Full();";
    emitInfoAndNewLine(op);
    return;
  }
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
    // Random-access array -> internal memory (no top-level port): INPUT preloads
    // from input<k>.data, OUTPUT reads out to output<k>.data, BOTH does both.
    char mp = regArgMemPort(func, arg.value());
    if (mp == 'i' || mp == 'o' || mp == 'b') {
      unsigned aw = scAddrW(total), dw = scDataW(mt.getElementType());
      int ii = (mp == 'i' || mp == 'b') ? inCount++ : -1;
      int oo = (mp == 'o' || mp == 'b') ? outCount++ : -1;
      memArrays.push_back({nm, ct, total, aw, dw, mp, ii, oo});
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
  SmallVector<ChannelConstructOp, 4> chanOps; // handshake channels (combinational)
  SmallVector<WireConstructOp, 4> wireOps;    // raw combinational wires (sc_signal)
  SmallVector<func::CallOp, 4> calls;
  for (auto &op : func.front()) {
    if (auto sc = llvm::dyn_cast<StreamConstructOp>(&op))
      channels.push_back(sc);
    else if (auto cc = llvm::dyn_cast<ChannelConstructOp>(&op))
      chanOps.push_back(cc);
    else if (auto wc = llvm::dyn_cast<WireConstructOp>(&op))
      wireOps.push_back(wc);
    else if (auto call = llvm::dyn_cast<func::CallOp>(&op))
      calls.push_back(call);
  }
  numKernelInsts = calls.size(); // single-shot tb waits for this many completions

  // Channel members. A Stream's depth (from its type) picks the flavor:
  //   depth 0  -> a bare Connections::Combinational (combinational wire)
  //   depth>=1 -> an AlloFifo<T,depth> between two _in/_out wires (buffered)
  for (auto sc : channels) {
    // A self-FIFO (one kernel produces+queries) is a NORMAL buffered stream here:
    // its _in/_out Combinational wires + AlloFifo are declared just like any other
    // depth>=1 stream; the one kernel simply binds BOTH ends (see the bind loop).
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
  // Channel members: a handshake Channel is always a combinational link.
  for (auto cc : chanOps) {
    auto ct = llvm::dyn_cast<ChannelType>(cc.getResult().getType());
    std::string T = std::string(getSCTypeName(ct.getBaseType()).str());
    std::string nm = std::string(addName(cc.getResult(), /*isPtr=*/false).str());
    indent();
    os << "Connections::Combinational< " << T << " > " << nm << ";\n";
  }
  // Wire members: a raw combinational wire is an sc_signal<T>.
  for (auto wc : wireOps) {
    auto wt = llvm::dyn_cast<WireType>(wc.getResult().getType());
    std::string T = std::string(getSCTypeName(wt.getBaseType()).str());
    std::string nm = std::string(addName(wc.getResult(), /*isPtr=*/false).str());
    indent();
    os << "sc_signal< " << T << " > " << nm << ";\n";
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
      int ii = -1, oo = -1;
      for (auto &m : memArrays)
        if (m.base == std::string(getName(ov).str())) {
          ii = m.inIdx;
          oo = m.outIdx;
        }
      memInsts.push_back(
          {"mp" + std::to_string(it.index()) + "_" +
               std::to_string(opnd.index()),
           instNames[it.index()], std::string(getName(carg).str()),
           std::string(getSCTypeName(mt.getElementType()).str()), total,
           scAddrW(total), scDataW(mt.getElementType()), mp, ii, oo});
    }
  }
  // Memory-port members: a req channel + memory (+ rsp channel for read-capable
  // ports). 'i'/'b' -> AlloMem (req + rsp); 'o' -> AlloMemW (req only).
  for (auto &mi : memInsts) {
    std::string reqT =
        "ac_int<" + std::to_string(1 + mi.addrw + mi.dataw) + ", false>";
    indent();
    os << "Connections::Combinational< " << reqT << " > " << mi.chan
       << "_req_ch;\n";
    if (mi.dir != 'o') { // 'i' and 'b' read -> need a response channel
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
  for (auto cc : chanOps) {
    std::string nm = std::string(getName(cc.getResult()).str());
    os << sep << nm << "(\"" << nm << "\")";
    sep = ", ";
  }
  for (auto wc : wireOps) {
    std::string nm = std::string(getName(wc.getResult()).str());
    os << sep << nm << "(\"" << nm << "\")";
    sep = ", ";
  }
  for (auto it : llvm::enumerate(calls)) {
    os << sep << instNames[it.index()] << "(\"" << instNames[it.index()]
       << "\")";
    sep = ", ";
  }
  for (auto &mi : memInsts) {
    os << sep << mi.chan << "_req_ch(\"" << mi.chan << "_req_ch\")";
    if (mi.dir != 'o')
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
      // Duplicate stream/channel arg: the primary already bound the shared port,
      // and getName(carg) now resolves to it -- binding again would double-bind.
      if (aliasOf(carg))
        continue;
      if (auto sty = llvm::dyn_cast<StreamType>(ov.getType())) {
        if (localStreamConstructs.count(ov)) {
          // self-FIFO: this ONE kernel is both producer and consumer. Bind its
          // enq (Out) to the fifo input wire and its deq (In) to the output wire
          // (depth 0 -> both bind the bare Combinational).
          std::string base = std::string(getName(ov).str());
          std::string cin = base, cout = base;
          if (sty.getDepth() != 0) {
            cin += "_in";
            cout += "_out";
          }
          std::string cargn = std::string(getName(carg).str());
          indent();
          os << instNames[it.index()] << "." << cargn << "_enq(" << cin << ");\n";
          indent();
          os << instNames[it.index()] << "." << cargn << "_deq(" << cout
             << ");\n";
          continue;
        }
        // stream operand -> stream channel. For a buffered stream (depth>=1) the
        // producer (Out) binds the FIFO's input wire, the consumer (In) its
        // output wire; a depth-0 stream is the bare Combinational.
        std::string chan = std::string(getName(ov).str());
        if (sty.getDepth() != 0)
          chan += (streamDir(callee, opnd.index()) == 'o') ? "_in" : "_out";
        indent();
        os << instNames[it.index()] << "." << getName(carg) << "(" << chan
           << ");\n";
      } else if (llvm::isa<ChannelType>(ov.getType())) {
        // channel operand -> bare Combinational (combinational, no _in/_out)
        std::string chan = std::string(getName(ov).str());
        indent();
        os << instNames[it.index()] << "." << getName(carg) << "(" << chan
           << ");\n";
      } else if (llvm::isa<WireType>(ov.getType())) {
        // wire operand -> sc_signal (raw combinational)
        std::string sig = std::string(getName(ov).str());
        indent();
        os << instNames[it.index()] << "." << getName(carg) << "(" << sig
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
          if (mp != 'o') { // 'i' and 'b' bind the response channel too
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
    if (mi.dir != 'o') {
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
  // The SystemC backend is a DATAFLOW backend: it emits SC_MODULEs + a self-
  // contained sc_main testbench for @df.region / @df.kernel designs. A plain
  // (customize) kernel has no dataflow region, so it would emit only as a bodiless
  // helper function with no top module and no testbench -- it compiles but cannot
  // be simulated (there is nothing to drive). Fail early with a clear message so
  // the user picks the right backend, instead of a confusing csim failure later.
  bool hasDataflow = false;
  for (auto f : module.getOps<func::FuncOp>())
    if (f->hasAttr("dataflow") || f->hasAttr("df.kernel")) {
      hasDataflow = true;
      break;
    }
  if (!hasDataflow) {
    module.emitError(
        "target=\"systemc\" requires a dataflow design (@df.region with "
        "@df.kernel); this module has no dataflow region, so no top module or "
        "testbench can be generated. Use target=\"vhls\" for non-dataflow "
        "(customize) kernels.");
    state.encounteredError = true;
    return;
  }

  // Flatten any @df.region hierarchy (sub-regions called from kernels) into a
  // flat top before emission — SystemC can't nest regions inside a thread.
  flattenHierarchy(module);

  // A stream passed to exactly ONE kernel call is a self-FIFO (one kernel both
  // produces and queries it) -> realize as a local ac_channel, not a directional
  // Connections port. Mark the construct result + the callee's block arg.
  for (auto topf : module.getOps<func::FuncOp>()) {
    if (!topf->hasAttr("dataflow"))
      continue;
    llvm::DenseMap<Value, int> cnt;
    SmallVector<func::CallOp> callv;
    topf.walk([&](func::CallOp c) {
      callv.push_back(c);
      for (Value o : c.getArgOperands())
        if (llvm::isa<StreamType>(o.getType()))
          cnt[o]++;
    });
    for (auto c : callv) {
      auto callee = module.lookupSymbol<func::FuncOp>(c.getCallee());
      if (!callee)
        continue;
      for (auto it : llvm::enumerate(c.getArgOperands()))
        if (llvm::isa<StreamType>(it.value().getType()) && cnt[it.value()] == 1) {
          localStreamConstructs.insert(it.value());
          localStreamArgs.insert(callee.getArgument(it.index()));
        }
    }
  }

  // A boundary array that would seq-stream but is driven/consumed by >1 kernel
  // call (fan-in output / fan-out input) must go to the memory-port path instead
  // -- binding a 2nd producer/consumer to one Combinational aborts MatchLib.
  for (auto topf : module.getOps<func::FuncOp>()) {
    if (!topf->hasAttr("dataflow"))
      continue;
    llvm::DenseMap<Value, int> useCnt; // seq-streamable directional uses per array
    SmallVector<func::CallOp> callv;
    topf.walk([&](func::CallOp c) { callv.push_back(c); });
    auto seqDirArg = [&](func::CallOp c, unsigned idx, char &d) -> Value {
      auto callee = module.lookupSymbol<func::FuncOp>(c.getCallee());
      if (!callee)
        return nullptr;
      Value carg = callee.getArgument(idx);
      d = argDir(callee, idx);
      if ((d == 'i' || d == 'o' || d == 'b') && isSeqStreamable(carg))
        return carg;
      return nullptr;
    };
    for (auto c : callv)
      for (auto it : llvm::enumerate(c.getArgOperands())) {
        char d;
        if (llvm::isa<MemRefType>(it.value().getType()) &&
            seqDirArg(c, it.index(), d))
          useCnt[it.value()]++;
      }
    for (auto c : callv)
      for (auto it : llvm::enumerate(c.getArgOperands())) {
        char d;
        Value carg;
        if (llvm::isa<MemRefType>(it.value().getType()) && useCnt[it.value()] > 1 &&
            (carg = seqDirArg(c, it.index(), d)))
          forceMemPortArgs.insert(carg);
      }
  }

  // Same stream/channel passed to MULTIPLE arg positions of one call -> alias the
  // duplicate callee block-args onto the first so they share a single port.
  for (auto topf : module.getOps<func::FuncOp>()) {
    if (!topf->hasAttr("dataflow"))
      continue;
    topf.walk([&](func::CallOp c) {
      auto callee = module.lookupSymbol<func::FuncOp>(c.getCallee());
      if (!callee)
        return;
      llvm::DenseMap<Value, Value> primaryArg; // operand -> its first callee arg
      for (auto it : llvm::enumerate(c.getArgOperands())) {
        Value ov = it.value();
        if (!llvm::isa<StreamType>(ov.getType()) &&
            !llvm::isa<ChannelType>(ov.getType()))
          continue;
        Value carg = callee.getArgument(it.index());
        if (Value first = primaryArg.lookup(ov))
          streamArgAlias[carg] = first;
        else
          primaryArg[ov] = carg;
      }
    });
  }

  std::string device_header = R"XXX(
//===------------------------------------------------------------*- C++ -*-===//
// Automatically generated file for SystemC (Catapult HLS / MatchLib Connections).
//===----------------------------------------------------------------------===//
#include <systemc.h>
#include <mc_connections.h>   // MatchLib Connections (LI valid/ready channels)
#include <mc_scverify.h>      // SCVerify testbench macros (CCS_MAIN / CCS_DESIGN)
#include <ac_int.h>
#include <ac_fixed.h>
#include <ac_channel.h>     // local self-FIFO streams (one-kernel put+get+status)
#include <ac_std_float.h>   // IEEE floats: ac_ieee_float<binaryNN>
#include <cstring>          // std::memcpy for bit-reinterpret (bitcast)
#include <stdint.h>
// f16: Catapult has no native `half`; alias it to ac_ieee_float<binary16>.
// (f32 -> ac_ieee_float<binary32> is emitted directly by getCatapultTypeName.)
typedef ac_ieee_float<binary16> half;
#include <iostream>
#include <fstream>
#include <iomanip>          // std::setprecision for lossless float tb output
#include <algorithm>
// --- float support helpers (half / ac_ieee_float<binary32> / double) ---
// Floats have no implicit int/stream conversions (and half is non-trivial), so
// memory ports (which transport a raw bit pattern in an ac_int req word) and the
// testbench (text I/O + waveform trace) need these shims.
// float -> raw bits (memcpy handles half=2B, ac_ieee_float<binary32>=4B, double=8B).
template <class T> inline unsigned long long _fbits(const T &v) {
  unsigned long long b = 0; std::memcpy(&b, &v, sizeof(T)); return b;
}
// Reconstruct a memory element from the DATAW raw bits: value-cast for integers,
// bit-reinterpret for floats (a value-cast would corrupt the float).
template <typename T> inline T _mem_decode(unsigned long long r) { return (T)(long long)r; }
template <> inline half _mem_decode<half>(unsigned long long r) {
  uint16_t u = (uint16_t)r; half h; std::memcpy(&h, &u, sizeof(u)); return h;
}
template <>
inline ac_ieee_float<binary32> _mem_decode<ac_ieee_float<binary32> >(unsigned long long r) {
  uint32_t u = (uint32_t)r; ac_ieee_float<binary32> f; std::memcpy(&f, &u, sizeof(u)); return f;
}
template <> inline double _mem_decode<double>(unsigned long long r) {
  double d; std::memcpy(&d, &r, sizeof(d)); return d;
}
// tb: data files hold float text -> read a float and convert.
inline std::istream &operator>>(std::istream &is, half &h) { float f; is >> f; h = half(f); return is; }
inline std::istream &operator>>(std::istream &is, ac_ieee_float<binary32> &h) {
  float f; is >> f; h = ac_ieee_float<binary32>(f); return is;
}
// tb/Connections waveform trace of a float (trace its raw bit pattern). Needed
// because Connections/sc_signal ports templated on these types call sc_trace.
inline void sc_trace(sc_core::sc_trace_file *tf, const half &h, const std::string &n) {
  sc_trace(tf, (unsigned short)_fbits(h), n);
}
inline void sc_trace(sc_core::sc_trace_file *tf, const ac_ieee_float<binary32> &h,
                     const std::string &n) {
  sc_trace(tf, (unsigned)_fbits(h), n);
}
// Single-shot completion counter (csim/testbench ONLY). Each kernel bumps this
// once, right after its body finishes its single pass; the sc_main testbench for
// memory-mapped-output designs advances the clock until all kernels are done
// before reading the memories out. Declared unconditionally so the tb compiles
// under __SYNTHESIS__ too, but the kernel's increment is guarded out of synthesis
// (see emitKernelModule) so the synthesized logic stays side-effect free.
static long __allo_done = 0;
// The reused body emits bare max()/min() for the Allo max/min intrinsics (Vitis
// resolves them via hls::); bind them to std:: so the same body compiles here.
using std::max;
using std::min;
// The reused Vivado-emitter body prints Vitis ap_(u)int types; alias them to
// Catapult's ac_int so the same body compiles. (TODO: emit ac_int/ac_fixed
// natively via a type-name override, like getCatapultTypeName in the Catapult
// emitter, and drop this shim.)
// ap_(u)int is a thin ac_int subclass adding the two Vitis affordances the reused
// body relies on and ac_int lacks:
//  (1) the x(hi,lo) BIT-RANGE operator (packed streams unpack via v(31,16) etc) —
//      a proxy that extracts on read and inserts on write, for const/runtime hi,lo;
//  (2) for W>64 only, an implicit narrowing conversion (`int32_t x = wide;`, e.g. a
//      GEMM accumulator past 64 bits) which ac_int omits above 64 bits.
// Adding operator() doesn't disturb arithmetic (it's the call operator, not a
// conversion); the W>64 narrowing stays gated so ac_int's own operators keep
// winning overload resolution (no builtin-conversion ambiguity).
//
// CSYNTH NOTE: the subclass-of-ac_int form below is CSIM-ONLY. Catapult's front-
// end treats ac_int as a builtin, so a struct deriving from it trips
// "struct assignment from non-struct type" (CIN-15) on every `v = <ac_int expr>;`
// — breaking synthesis branch-wide. Under __SYNTHESIS__ we therefore fall back to
// a PLAIN ac_int alias, which loses the two csim affordances (the x(hi,lo) bit-
// range and the >64-bit implicit narrowing). Consequence: every non-bit-slicing
// design synthesizes; a design that actually bit-slices (packed streams) fails at
// its `(hi,lo)` site instead — a clear, local error, and those need native ac_int
// .slc emission anyway. csim keeps the full-featured shim so behavior is unchanged.
#ifdef __SYNTHESIS__
template <int W> using ap_int = ac_int<W, true>;
template <int W> using ap_uint = ac_int<W, false>;
#else
template <class AC> struct ap_rng {
  AC &r;
  int hi, lo;
  ap_rng(AC &x, int h, int l) : r(x), hi(h), lo(l) {}
  operator long long() const { // read bits [hi:lo]
    AC m = (AC(1) << (hi - lo + 1)) - 1;
    return ((r >> lo) & m).to_int64();
  }
  template <class V> ap_rng &operator=(V v) { // write bits [hi:lo] = v
    AC m = (AC(1) << (hi - lo + 1)) - 1;
    r = (r & ~(m << lo)) | ((AC(v) & m) << lo);
    return *this;
  }
};
template <int W, bool Big = (W > 64)> struct ap_sel {
  struct s : ac_int<W, true> {
    using ac_int<W, true>::ac_int;
    ap_rng<ac_int<W, true>> operator()(int hi, int lo) { return {*this, hi, lo}; }
  };
  struct u : ac_int<W, false> {
    using ac_int<W, false>::ac_int;
    ap_rng<ac_int<W, false>> operator()(int hi, int lo) { return {*this, hi, lo}; }
  };
};
template <int W> struct ap_sel<W, true> {
  struct s : ac_int<W, true> {
    using ac_int<W, true>::ac_int;
    ap_rng<ac_int<W, true>> operator()(int hi, int lo) { return {*this, hi, lo}; }
    operator long long() const { return this->to_int64(); }
  };
  struct u : ac_int<W, false> {
    using ac_int<W, false>::ac_int;
    ap_rng<ac_int<W, false>> operator()(int hi, int lo) { return {*this, hi, lo}; }
    operator unsigned long long() const { return this->to_uint64(); }
  };
};
template <int W> using ap_int = typename ap_sel<W>::s;
template <int W> using ap_uint = typename ap_sel<W>::u;
#endif

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
        mem[a] = _mem_decode<T>(r.template slc<DATAW>(1 + ADDRW).to_int64());
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
      mem[z] = _mem_decode<T>(0);
    wait();
    while (1) {
      ac_int<1 + ADDRW + DATAW, false> r = req.Pop();
      ac_int<ADDRW, false> a = r.template slc<ADDRW>(1);
      mem[a] = _mem_decode<T>(r.template slc<DATAW>(1 + ADDRW).to_int64());
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
        // Wide read temp so a char-width element (int8_t/uint8_t) parses as an
        // integer, not a single character (see the memory-port preload note).
        bool isF = (a.ctype == "half" || a.ctype == "double" ||
                    a.ctype.find("ieee_float") != std::string::npos);
        std::string rt = isF ? a.ctype : std::string("long long");
        os << "{ std::ifstream _f(\"input" << a.fileIdx << ".data\"); " << rt
           << " _v; for (int f = 0; f < " << a.total << "; ++f) { _f >> _v; ch_"
           << a.member << ".Push((" << a.ctype << ")_v); } }\n";
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

    // snk: write each OUTPUT port to output<k>.data (read back into B by hls.py)
    indent(); os << "void snk() {\n";
    addIndent();
    for (auto &a : ioArrays)
      if (a.dir == 'o') { indent(); os << "ch_" << a.member << ".ResetRead();\n"; }
    indent(); os << "wait();\n";
    for (auto &a : ioArrays)
      if (a.dir == 'o') {
        indent();
        // Symmetric to the input read: cast a char-width element to a wide int so
        // operator<< prints its NUMERIC value, not a character; floats keep full
        // round-trippable precision.
        bool isF = (a.ctype == "half" || a.ctype == "double" ||
                    a.ctype.find("ieee_float") != std::string::npos);
        if (isF)
          os << "{ std::ofstream _f(\"output" << a.fileIdx
             << ".data\"); for (int f = 0; f < " << a.total
             << "; ++f) _f << std::setprecision(9) << ch_" << a.member
             << ".Pop() << \"\\n\"; }\n";
        else
          os << "{ std::ofstream _f(\"output" << a.fileIdx
             << ".data\"); for (int f = 0; f < " << a.total
             << "; ++f) _f << (long long)(ch_" << a.member
             << ".Pop()) << \"\\n\"; }\n";
      }
    if (hasStreamOut) { indent(); os << "sc_stop();\n"; }
    reduceIndent();
    indent(); os << "}\n";
    reduceIndent();
    os << "};\n\n";

    os << "int sc_main(int, char *[]) {\n";
    addIndent();
    // static (not a stack local): the tb inlines the whole design (every
    // sub-module + AlloFifo buf[] + AlloMem mem[]), which at large mesh sizes
    // (e.g. EVA 8x8) overflows the ~8MB stack. Static storage has no such cap;
    // sc_main runs once so the single construction is unchanged.
    indent(); os << "static tb t(\"t\");\n";
    // Preload every INPUT memory (each shared-read replica gets its own copy)
    // from the array's input file (csim only: direct hierarchical poke of
    // AlloMem.mem[], done before reset is released).
    for (auto &mi : memInsts)
      if (mi.dir != 'o') { // 'i' and 'b' preload from their input file
        indent();
        // Read integers into a WIDE temp: a char-width element (int8_t/uint8_t is
        // signed/unsigned char) would otherwise trigger operator>>'s FORMATTED
        // CHARACTER extraction (reads '6','5' from "65"), not integer parsing.
        // Floats keep their own operator>> overload.
        bool isF = (mi.ctype == "half" || mi.ctype == "double" ||
                    mi.ctype.find("ieee_float") != std::string::npos);
        std::string rt = isF ? mi.ctype : std::string("long long");
        os << "{ std::ifstream _f(\"input" << mi.inIdx << ".data\"); " << rt
           << " _v; for (int f = 0; f < " << mi.total << "; ++f) { _f >> _v; t.dut."
           << mi.chan << "_mem.mem[f] = (" << mi.ctype << ")_v; } }\n";
      }
    indent(); os << "t.rst = 0; sc_start(1, SC_NS);\n";
    // A stream output stops the sim via sc_stop (self-synchronizing: the sink
    // drains exactly N tokens). Memory-mapped outputs have no such token, so we
    // SINGLE-SHOT: advance the clock until every kernel has finished its one pass
    // (__allo_done == numKernelInsts), then settle any in-flight STORE handshakes,
    // then read the memories. This replaces the old fixed maxTotal*8 guess, which
    // under-ran deep/tiled designs (late tiles caught mid-compute) and, with the
    // former free-running body, over-accumulated `both` outputs.
    indent(); os << "t.rst = 1;\n";
    if (hasStreamOut) {
      indent(); os << "sc_start();\n";
    } else {
      // Generous safety cap: the loop EXITS as soon as all kernels finish (real
      // completion), so this only bounds wall-clock if the design deadlocks.
      int64_t capCycles = maxTotal * 2000 + 200000;
      indent();
      os << "for (long long _c = 0; _c < " << capCycles << "LL && __allo_done < "
         << numKernelInsts << "; ++_c) sc_start(1, SC_NS); // wait for completion\n";
      indent();
      os << "sc_start(" << (memInsts.empty() ? 64 : 256)
         << ", SC_NS); // settle in-flight memory writes\n";
    }
    // Read each OUTPUT array out to output<k>.data (into B by hls.py). Shared-
    // write arrays are SPLIT across replicas that each wrote disjoint elements
    // (zero-initialized elsewhere), so sum the replicas element-wise.
    for (auto &m : memArrays)
      if (m.dir != 'i') { // 'o' and 'b' read out to their output file
        indent();
        os << "{ std::ofstream _f(\"output" << m.outIdx << ".data\");\n";
        indent();
        os << "  for (int f = 0; f < " << m.total << "; ++f) {\n";
        // float memories accumulate/write as float; integers as before.
        bool isFloat = (m.ctype == "half" || m.ctype == "double" ||
                        m.ctype.find("ieee_float") != std::string::npos);
        indent();
        os << (isFloat ? "    float _s = 0;\n" : "    long long _s = 0;\n");
        for (auto &mi : memInsts)
          if (mi.dir != 'i' && mi.outIdx == m.outIdx) {
            indent();
            if (isFloat)
              os << "    _s += t.dut." << mi.chan << "_mem.mem[f].to_float();\n";
            else
              os << "    _s += (long long) t.dut." << mi.chan
                 << "_mem.mem[f];\n";
          }
        indent();
        // float outputs: write full round-trippable precision (float32 needs 9
        // significant digits) so the data-file text doesn't lose bits.
        if (isFloat)
          os << "    _f << std::setprecision(9) << _s << \"\\n\";\n";
        else
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
