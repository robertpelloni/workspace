/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace mlir::nvgpu {

/// device async token type
/// `nvgpu.device.async.token` is a type returned by an asynchronous operation
///     that runs on the GPU (device). It is used to establish an SSA-based link
///     between the async operation (e.g. DeviceAsyncCopy) and operations that
///     group or synchronize the async operations (e.g. DeviceAsyncCreateGroupOp,
///     DeviceAsyncWaitOp).
class DeviceAsyncTokenType;
/// mbarrier barrier type
/// This is the type for one or more mbarrier object in shared memory that is 
///     used to synchronize a variable number of threads.
/// 
///     If `num_barriers` is not set, the number of mbarrier objects is 1.
/// 
///     A mbarrier object is 64 bit with 8 byte alignment. The mbarrier object 
///     can be initiated and invalidated.
/// 
///     [See for more details in PTX ISA](https://docs.nvidia.com/cuda/parallel-thread-execution/#size-and-alignment-of-mbarrier-object)
class MBarrierGroupType;
class MBarrierTokenType;
/// TensorMap descriptor
/// `nvgpu.tma.descriptor` is a type that represents a TMA descriptor. It is 
///     128-byte object either in constant space or kernel paramater.
class TensorMapDescriptorType;
/// Warpgroup matrix descriptor type
/// The descriptor specifies the properties of the matrix in shared memory that 
///   is a multiplicand in the matrix multiply and accumulate operation. 
///   
///   The descriptor is a 64-bit value contained in a register with the following:
///   ```
///   +---------+-----+-----------+-----+-----------+-----+-----+-----------+-----+
///   |   0-13  |14-15|   16-29   |30-31|   32-45   |46-48|49-51|   52-61   |62-63|
///   +---------+-----+-----------+-----+-----------+-----+-----+-----------+-----+
///   |  14bits |2bits|   14bits  |2bits|   14bits  |2bits|3bits|   10bits  |2bits|
///   +---------+-----+-----------+-----+-----------+-----+-----+-----------+-----+
///   | BaseAddr|  0  | LeadingDim|  0  |   Stride  |  0  |Offst|     0     |Swzle|
///   +---------+-----+-----------+-----+-----------+-----+-----+-----------+-----+
///   ```
///    
///   [See for more details in PTX ISA](https://docs.nvidia.com/cuda/parallel-thread-execution/index.html#asynchronous-warpgroup-level-matrix-shared-memory-layout-matrix-descriptor)
class WarpgroupMatrixDescriptorType;
/// This type represents the result matrix obtained from `nvgpu.warpgroup.mma`. 
///     The `$fragmented` type signifies the distributed or fragmented result 
///     vector that is collectively owned by all the threads in the warp-group 
///     that executed `nvgpu.warpgroup.mma`.
///     [See the details of register fragment layout for accumulator matrix D]
///     (https://docs.nvidia.com/cuda/parallel-thread-execution/index.html#wgmma-64n16-d)
class WarpgroupAccumulatorType;
class DeviceAsyncTokenType : public ::mlir::Type::TypeBase<DeviceAsyncTokenType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvgpu.device.async.token";
  static constexpr ::llvm::StringLiteral dialectName = "nvgpu";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"device.async.token"};
  }

};
namespace detail {

struct MBarrierGroupTypeStorage;

} // namespace detail
class MBarrierGroupType : public ::mlir::Type::TypeBase<MBarrierGroupType, ::mlir::Type, detail::MBarrierGroupTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvgpu.mbarrier.group";
  static constexpr ::llvm::StringLiteral dialectName = "nvgpu";
  static MBarrierGroupType get(::mlir::MLIRContext *context, Attribute memorySpace, unsigned num_barriers);
  static MBarrierGroupType get(::mlir::MLIRContext *context, Attribute memorySpace);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mbarrier.group"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  Attribute getMemorySpace() const;
  unsigned getNumBarriers() const;
};
class MBarrierTokenType : public ::mlir::Type::TypeBase<MBarrierTokenType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvgpu.mbarrier.token";
  static constexpr ::llvm::StringLiteral dialectName = "nvgpu";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mbarrier.token"};
  }

};
namespace detail {

struct TensorMapDescriptorTypeStorage;

} // namespace detail
class TensorMapDescriptorType : public ::mlir::Type::TypeBase<TensorMapDescriptorType, ::mlir::Type, detail::TensorMapDescriptorTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvgpu.tensormap.descriptor";
  static constexpr ::llvm::StringLiteral dialectName = "nvgpu";
  static TensorMapDescriptorType get(::mlir::MLIRContext *context, MemRefType tensor, ::mlir::nvgpu::TensorMapSwizzleKind swizzle, ::mlir::nvgpu::TensorMapL2PromoKind l2promo, ::mlir::nvgpu::TensorMapOOBKind oob, ::mlir::nvgpu::TensorMapInterleaveKind interleave);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tensormap.descriptor"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  MemRefType getTensor() const;
  ::mlir::nvgpu::TensorMapSwizzleKind getSwizzle() const;
  ::mlir::nvgpu::TensorMapL2PromoKind getL2promo() const;
  ::mlir::nvgpu::TensorMapOOBKind getOob() const;
  ::mlir::nvgpu::TensorMapInterleaveKind getInterleave() const;
};
namespace detail {

struct WarpgroupMatrixDescriptorTypeStorage;

} // namespace detail
class WarpgroupMatrixDescriptorType : public ::mlir::Type::TypeBase<WarpgroupMatrixDescriptorType, ::mlir::Type, detail::WarpgroupMatrixDescriptorTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvgpu.warpgroup.descriptor";
  static constexpr ::llvm::StringLiteral dialectName = "nvgpu";
  static WarpgroupMatrixDescriptorType get(::mlir::MLIRContext *context, MemRefType tensor);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"warpgroup.descriptor"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  MemRefType getTensor() const;
};
namespace detail {

struct WarpgroupAccumulatorTypeStorage;

} // namespace detail
class WarpgroupAccumulatorType : public ::mlir::Type::TypeBase<WarpgroupAccumulatorType, ::mlir::Type, detail::WarpgroupAccumulatorTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "nvgpu.warpgroup.accumulator";
  static constexpr ::llvm::StringLiteral dialectName = "nvgpu";
  static WarpgroupAccumulatorType get(::mlir::MLIRContext *context, VectorType fragmented);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"warpgroup.accumulator"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  VectorType getFragmented() const;
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::DeviceAsyncTokenType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MBarrierGroupType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MBarrierTokenType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::TensorMapDescriptorType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::WarpgroupMatrixDescriptorType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::WarpgroupAccumulatorType)

#endif // GET_TYPEDEF_CLASSES

