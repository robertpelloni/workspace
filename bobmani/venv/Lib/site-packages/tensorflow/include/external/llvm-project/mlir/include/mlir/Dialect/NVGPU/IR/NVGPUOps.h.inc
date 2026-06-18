/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: NVGPUOps.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::nvgpu {

/// device-side asynchronous copy
/// The `nvgpu.device_async_copy` op initiates an asynchronous copy operation of
///     elements from source (global memory) to the destination (shared memory)
///     without blocking the thread. The async copy is added to a group.
/// 
///     This op is meant to be used with `nvgpu.device_async_create_group` and
///     `nvgpu.device_async_wait` to synchronize copies as explained in those ops
///     descriptions.
/// 
///     `bypassL1` attribute is hint to the hardware to bypass the L1 cache during
///     async copy, this hint may be ignored by the hardware.
/// 
///     `dstElements` attribute is the total number of elements written to
///     destination (shared memory).
/// 
///     `srcElements` argument is the total number of elements read from
///     source (global memory).
/// 
///     `srcElements` is an optional argument and when present the op only reads
///     `srcElements` number of elements from the source (global memory) and zero fills
///     the rest of the elements in the destination (shared memory).
/// 
///     In order to do a copy and wait for the result we need the following
///     combination:
///     ```
///     // copy 1.
///     %cp1 = nvgpu.device_async_copy %A[%c0], %B[%c0], 4 :memref<16xf32> to memref<16xf32, 3>
///     // copy 2.
///     %cp2 = nvgpu.device_async_copy %C[%c0], %D[%c0], 4 : memref<16xf32> to memref<16xf32, 3>
///     // group 1 contains copy 1 and copy 2.
///     %token1 = nvgpu.device_async_create_group %cp1, %cp2
///     // copy 3.
///     %cp3 = nvgpu.device_async_copy %E[%c0], %F[%c0], 4 : memref<16xf32> to memref<16xf32, 3>
///     // group 2 contains copy 3.
///     %token2 = nvgpu.device_async_create_group %cp3
///     // after the wait copy 1 and copy 2 are complete.
///     nvgpu.device_async_wait %token1
///     // after the wait copy 3 is complete.
///     nvgpu.device_async_wait %token2
///     ```
/// 
///     Example:
/// 
///     ```mlir
///     %0 = nvgpu.device_async_copy %src[%c0, %c0], %dst[%c0, %c0, %c0], 4 :
///       memref<4x5xf32> to memref<2x7x5xf32, 3>
///     ```
class DeviceAsyncCopyOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// device side asynchronous create group operation
/// The `nvgpu.device_async_create_group` op creates a group of memory accesses
///     containing all the pending `device_async_copy` operations associated with
///     argument tokens. Each token can only be part of one group.
/// 
///     It returns a token that can be use to wait until the group fully completes.
/// 
///     This is meant to be used with `nvgpu.device_async_wait` to synchronize copies
///     as explained in those ops descriptions.
/// 
///     Groups are executed in the order they are created.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = nvgpu.device_async_create_group
///   ```
class DeviceAsyncCreateGroupOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Wait for async gpu ops to complete.
/// The `nvgpu.device_async_wait` op will block the execution thread until the group
///     associated with the source token is fully completed.
/// 
///     The optional `$numGroups` attribute gives an upper bound of the number of
///     groups uncompleted when the wait can unblock the thread. For example,  if
///     16 async groups are pushe and `$numGroups` is set to 12, then the thread
///     will unblock when 12 groups or fewer are in flight (4 groups have
///     completed).
/// 
///     Example:
/// 
///     ```mlir
///     nvgpu.device_async_wait %0
///     ```
class DeviceAsyncWaitOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// The `nvgpu.ldmatrix` op represents loading a matrix fragment from
///     memory to registers. The source and result type must be compatible
///     with lowering to the `nvvm.ldmatrix` instruction. This op represents
///     the distributed version of a `vector.transfer_read` as an intermediate
///     step between lowering from `vector.transfer_read` to `nvvm.ldmatrix`.
/// 
///     This operation is meant to follow the semantic of described here:
///     https://docs.nvidia.com/cuda/parallel-thread-execution/index.html#warp-level-matrix-instructions-ldmatrix
/// 
///     Example:
///     ```mlir
///     %0 = nvgpu.ldmatrix %sm[%c0, %c0] {numTiles = 4 : i32, transpose = false} :
///       memref<?x?xf16, 3> -> vector<4x2xf16>
///     ```
class LdMatrixOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Performs expect_tx operation on the `nvgpu.mbarrier.arrive`
/// A thread executing the Op performs an expect-tx operation on the mbarrier 
///     object at the location specified by the address operand $barrier. The 
///     expect-tx operation, with an $txcount argument, increases the tx-count of 
///     an mbarrier object by the value specified by $txcount. This makes the 
///     current phase of the mbarrier object to expect and track the completion of 
///     additional asynchronous transactions.
///     
///     The `$txCount` specifies the number of element to the expect-tx operation.
/// 
///     Example:
///     ```mlir
///       nvgpu.mbarrier.arrive.expect_tx %barrier, %ic0 : !nvgpu.mbarrier.barrier<memorySpace = #gpu.address_space<workgroup>>
///     ```
class MBarrierArriveExpectTxOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Performs arrive operation on the `nvgpu.mbarrier.arrive.nocomplete` as non-blocking.
/// The Op performs arrive-on operation on the `mbarrier` object and returns a 
///     `nvgpu.mbarrier.token`.
/// 
///     The Op does not cause the `nvgpu.mbarrier` to complete its current phase.
/// 
///     Example:
///     ```mlir
///       %token = nvgpu.mbarrier.arrive.noComplete %barrier, %count : !nvgpu.mbarrier.barrier<memorySpace = #gpu.address_space<workgroup>> -> !nvgpu.mbarrier.token
///     ```
class MBarrierArriveNoCompleteOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Performs arrive operation on the `nvgpu.mbarrier.arrive`.
/// The Op performs arrive-on operation on the `mbarrier` object and returns a 
///     `nvgpu.mbarrier.token`.
/// 
///     For more information, see
///     https://docs.nvidia.com/cuda/parallel-thread-execution/#arrive-on-operation-on-mbarrier-object
/// 
///     Example:
///     ```mlir
///       %token = nvgpu.mbarrier.arrive %barrier : !nvgpu.mbarrier.barrier<memorySpace = #gpu.address_space<workgroup>> -> !nvgpu.mbarrier.token
///     ```
class MBarrierArriveOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Creates a `nvgpu.mbarrier` object.
/// The Op generates one or more `mbarrier` object, which is a barrier created in 
///     shared memory and supports various synchronization behaviors for threads.
/// 
///     The `mbarrier` object has the following type and alignment requirements:
///       Type: .b64, Alignment: 8, Memory space: .shared
///     
///     Example:
///     ```mlir
///       %barrier = nvgpu.mbarrier.create -> !nvgpu.mbarrier.barrier<memorySpace = #gpu.address_space<workgroup>>
///     ```
class MBarrierCreateOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Return a pointer to an `nvgpu.mbarrier`.
/// The `nvgpu.mbarrier.get` operation retrieves a pointer to a specific 
///     `mbarrier` object from a group of barriers created by the `nvgpu.mbarrier.create` operation.
/// 
///     Example:
///     ```mlir
///       %mbars = nvgpu.mbarrier.create -> !nvgpu.mbarrier.group<memorySpace = #gpu.address_space<workgroup>, num_barriers = 10>
///       %mbar_pointer = nvgpu.mbarrier.get %mbars[%c2] : !nvgpu.mbarrier.group<memorySpace = #gpu.address_space<workgroup>>
///     ```
class MBarrierGetOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Initialize the `nvgpu.mbarrier`.
/// The Op initializes the `mbarrier` object with the given number of threads.
/// 
///     Example:
///     ```mlir
///       %num_threads = gpu.block_dim x
///       %barrier = nvgpu.mbarrier.create -> !nvgpu.mbarrier.barrier<memorySpace = #gpu.address_space<workgroup>>
///       nvgpu.mbarrier.init %barrier, %num_threads : !nvgpu.mbarrier.barrier<memorySpace = #gpu.address_space<workgroup>>
///     ```
class MBarrierInitOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Checks if the `nvgpu.mbarrier` has completed its current phase.
/// Checks whether the mbarrier object has completed the phase. It is is a 
///     non-blocking instruction which tests for the completion of the phase.
/// 
///     Example:
///     ```mlir
///       %isComplete = nvgpu.mbarrier.test.wait %barrier, %token : !nvgpu.mbarrier.barrier<memorySpace = #gpu.address_space<workgroup>>, !nvgpu.mbarrier.token
///     ```
class MBarrierTestWaitOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Waits for the `nvgpu.mbarrier` to complete its current phase.
/// Checks whether the mbarrier object has completed the phase. It is is a 
///     potentially blocking instruction which tests for the completion of the 
///     phase. Suspended thread resumes execution when the specified phase completes 
///     OR before the phase completes following a system-dependent time limit. 
/// 
///     The `$phaseParity` specifies either even phase (0) or odd phase (1) to 
///     wait.
/// 
///     Example:
///     ```mlir
///       nvgpu.mbarrier.try_wait.parity %barrier, %phaseParity, %ticks : !nvgpu.mbarrier.barrier<memorySpace = #gpu.address_space<workgroup>>
///     ```
class MBarrierTryWaitParityOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// The `nvgu.mma.sp.sync` operation performs a warp-distributed MMA operation
///   where operand A is "structured sparse". In this case, the `matrixA` operand
///   represents the (warp-distributed) non-zero values of operand A, and the
///   `sparse_metadata` operand provides the indices.
/// 
///   The full description of the sparsity storage format and distribution scheme is
///   described in the PTX docs. This operation is meant to follow the semantic
///   described in the PTX documentation here:
///   https://docs.nvidia.com/cuda/parallel-thread-execution/index.html#warp-level-matrix-instructions-for-sparse-mma
/// 
///   The way the indices are distributed among the threads in a warp is controlled
///   by the optional `sparsity_selector` operand, which is `0` by default. For
///   more information, please consult the PTX documentation linked above.
/// 
///   Example (targetingthe f16 16x8x32 `mma.sp` PTX instruction):
/// 
///   ```mlir
///   nvgpu.mma.sp.sync (%a, %b, %c) metadata (%meta) {mmaShape = [16, 8, 32]} :
///     (vector<4x2xf16>, vector<2x2xf16>, vector<2x2xf16>) -> vector<2x2xf16>
///   ```
class MmaSparseSyncOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// The `nvgpu.mma.sync` op represents the warp-level matrix-multiply-and-
///     accumulate (mma) operation that is compatible with `nvvm.mma.sync`.
///     The operands and results vector sizes are thread-level onwership to
///     the warp-level mma operation shape. `mmaShape` attribute holds the
///     warp-level matrix-multiply shape.
/// 
///     The `nvgpu.mma.sync` op serves as an intermediate point between lowering from
///     `vector.contract` to `nvvm.mma.sync`.
/// 
///     This operation is meant to follow the semantic of described here:
///       https://docs.nvidia.com/cuda/parallel-thread-execution/index.html#warp-level-matrix-instructions-mma
/// 
///     Example:
/// 
///     ```mlir
///     %res = nvgpu.mma.sync (%matrixA, %matrixB, %matrixC) {mmaShape = [16, 8, 16]} :
///         (vector<4x2xf16>, vector<2x2xf16>, vector<2x2xf32>) -> vector<2x2xf32>
///     ```
class MmaSyncOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// The reciprocal calculation for vector types
/// Reciprocal calculation for `vector` types using `nvvm.rcp` OPs.
/// 
///     Currently, only the `approx` rounding mode and `ftz` are supported, and only for the `f32` type.
/// 
///     The input and output must be of the same vector type and shape.
class RcpOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// TMA asynchronous load
/// The Op loads a tile memory region from global memory to shared memory by 
///     Tensor Memory Access (TMA).
///     
///     `$tensorMapDescriptor` is tensor map descriptor which has information about
///     tile shape. The descriptor is created by `nvgpu.tma.create.descriptor`
/// 
///     The Op uses `$barrier` mbarrier based completion mechanism.
class TmaAsyncLoadOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// TMA asynchronous store
/// The Op store a tile memory region from global memory to shared memory by 
///     Tensor Memory Access (TMA).
///     
///     `$tensorMapDescriptor` is tensor map descriptor which has information about
///     tile shape. The descriptor is created by `nvgpu.tma.create.descriptor`
class TmaAsyncStoreOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// TMA create descriptor
/// The Op creates a tensor map descriptor object representing tiled memory 
///     region. To do that it calls CUDA Driver's `cuTensorMapEncodeTiled`. The 
///     descriptor is used by Tensor Memory Access (TMA).
/// 
///     The `tensor` is the source tensor to be tiled. 
/// 
///     The `boxDimensions` is the size of the tiled memory region in each dimension.
/// 
///     For more information see below:
///     https://docs.nvidia.com/cuda/cuda-driver-api/group__CUDA__TENSOR__MEMORY.html
class TmaCreateDescriptorOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Insert fence given `nvgpu.tensormap.descriptor`
/// The Op fences the given `$tmaDescriptor`. This is necessary if the tensor map
///     descriptor was modified from the host using cudaMemcpy. In this case, the
///     kernel needs a fence after which it is safe to use `tensor.map`.
class TmaFenceOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Prefetch given `nvgpu.tensormap.descriptor`
/// The Op brings the cache line containing the given `$tmaDescriptor` for 
///     subsequent use by the `tma.async.load` instruction.
class TmaPrefetchOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Generate a warpgroup matrix descriptor
/// This Op builds a `nvgpu.warpgroup.descriptor` that is used by 
///   `nvgpu.warpgroup.mma` to perform warpgroup-level matrix multiply and 
///   accumulate.
/// 
///   The descriptor specifies the properties of the matrix in shared memory that 
///   is a multiplicand in the matrix multiply and accumulate operation.
class WarpgroupGenerateDescriptorOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// Initializes the accumulator matrix
/// This Op generates and initializes the accumulator matrix for 
///     `nvgpu.warpgroup.mma` op to perform matrix-multiply-and-accumulate.
class WarpgroupMmaInitAccumulatorOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// The `nvgpu.warpgroup.mma` op performs the warpgroup-level (4 warps) 
///     matrix-multiply-and-accumulate (mma) operation that results in 
///     `nvvm.wgmma.mma_async`. 
///     
///     The operands are `descriptorA` and `descriptorB` that are wgmma matrix 
///     descriptors that shows the properties of the matrix in shared memory. The 
///     results are thread-level ownership to the warpgroup-level mma operation 
///     shape. The shape is deduced from the descriptor types and output vector.
/// 
///     The Op encapsulates multiple `nvvm.wgmma.mma_async` operations to complete 
///     the given shape. As `nvvm.wgmma.async` Op, or its corresponding PTX 
///     instruction, is asynchronous, this Op groups the `nvvm.wgmma.async` and 
///     surrounds them between `wgmma.fence.aligned` and 
///     `wgmma.commit.group.sync.aligned`, `wgmma.wait.group.sync.aligned` Ops.
/// 
///     Example:
///     ```mlir
///       %r1,%r2 = nvgpu.warpgroup.mma %descA, %descB, %acc1, %acc2: 
///                  !nvgpu.warpgroup.descriptor<tensor = memref<128x64xf16, 3>>, 
///                  !nvgpu.warpgroup.descriptor<tensor = memref<64x128xf16, 3>>, 
///                  !nvgpu.warpgroup.accumulator<fragmented = vector<64x128xf32>>,
///                  !nvgpu.warpgroup.accumulator<fragmented = vector<64x128xf32>>
///                  -> 
///                  !nvgpu.warpgroup.accumulator<fragmented = vector<64x128xf32>>,
///                  !nvgpu.warpgroup.accumulator<fragmented = vector<64x128xf32>>
///     ```
class WarpgroupMmaOp;

} // namespace mlir::nvgpu
namespace mlir::nvgpu {

/// The `nvgpu.warpgroup.mma.store` op performs the store of fragmented result 
///     in $matrixD to given memref. 
/// 
///     [See the details of register fragment layout for accumulator matrix D]
///     (https://docs.nvidia.com/cuda/parallel-thread-execution/index.html#wgmma-64n16-d) 
/// 
///     Note that, the op must be run with warp group.
class WarpgroupMmaStoreOp;

} // namespace mlir::nvgpu
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::DeviceAsyncCopyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeviceAsyncCopyOpGenericAdaptorBase {
public:
  struct Properties {
    using bypassL1Ty = ::mlir::UnitAttr;
    bypassL1Ty bypassL1;

    auto getBypassL1() const {
      auto &propStorage = this->bypassL1;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setBypassL1(const ::mlir::UnitAttr &propValue) {
      this->bypassL1 = propValue;
    }
    using dstElementsTy = ::mlir::IntegerAttr;
    dstElementsTy dstElements;

    auto getDstElements() const {
      auto &propStorage = this->dstElements;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setDstElements(const ::mlir::IntegerAttr &propValue) {
      this->dstElements = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 5>;
    operandSegmentSizesTy operandSegmentSizes;
    ::llvm::ArrayRef<int32_t> getOperandSegmentSizes() const {
      auto &propStorage = this->operandSegmentSizes;
      return propStorage;
    }
    void setOperandSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->operandSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.bypassL1 == this->bypassL1 &&
        rhs.dstElements == this->dstElements &&
        rhs.operandSegmentSizes == this->operandSegmentSizes &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DeviceAsyncCopyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.device_async_copy", odsAttrs.getContext());
  }

  DeviceAsyncCopyOpGenericAdaptorBase(DeviceAsyncCopyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getDstElementsAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().dstElements);
    return attr;
  }

  ::llvm::APInt getDstElements();
  ::mlir::UnitAttr getBypassL1Attr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().bypassL1);
    return attr;
  }

  ::std::optional<bool> getBypassL1();
};

} // namespace detail
template <typename RangeT>
class DeviceAsyncCopyOpGenericAdaptor : public detail::DeviceAsyncCopyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeviceAsyncCopyOpGenericAdaptorBase;
  static constexpr int odsIndex_dst = 0;
  static constexpr int odsIndex_dstIndices = 1;
  static constexpr int odsIndex_src = 2;
  static constexpr int odsIndex_srcIndices = 3;
  static constexpr int odsIndex_srcElements = 4;
public:
  DeviceAsyncCopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeviceAsyncCopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeviceAsyncCopyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeviceAsyncCopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : DeviceAsyncCopyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeviceAsyncCopyOpGenericAdaptor(RangeT values, const DeviceAsyncCopyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeviceAsyncCopyOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeviceAsyncCopyOp>>>
  DeviceAsyncCopyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDst() {
    return (*getODSOperands(0).begin());
  }

  RangeT getDstIndices() {
    return getODSOperands(1);
  }

  ValueT getSrc() {
    return (*getODSOperands(2).begin());
  }

  RangeT getSrcIndices() {
    return getODSOperands(3);
  }

  ValueT getSrcElements() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DeviceAsyncCopyOpAdaptor : public DeviceAsyncCopyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeviceAsyncCopyOpGenericAdaptor::DeviceAsyncCopyOpGenericAdaptor;
  DeviceAsyncCopyOpAdaptor(DeviceAsyncCopyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeviceAsyncCopyOp : public ::mlir::Op<DeviceAsyncCopyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::nvgpu::DeviceAsyncTokenType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeviceAsyncCopyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeviceAsyncCopyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dst = 0;
  static constexpr int odsIndex_dstIndices = 1;
  static constexpr int odsIndex_src = 2;
  static constexpr int odsIndex_srcIndices = 3;
  static constexpr int odsIndex_srcElements = 4;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("bypassL1"), ::llvm::StringRef("dstElements"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBypassL1AttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBypassL1AttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getDstElementsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getDstElementsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.device_async_copy");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getDst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getDstIndices() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(2).begin());
  }

  ::mlir::Operation::operand_range getSrcIndices() {
    return getODSOperands(3);
  }

  ::mlir::TypedValue<::mlir::IndexType> getSrcElements() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IndexType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*operands.begin());
  }

  ::mlir::OpOperand &getDstMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDstIndicesMutable();
  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getSrcIndicesMutable();
  ::mlir::MutableOperandRange getSrcElementsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::DeviceAsyncTokenType> getAsyncToken() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::DeviceAsyncTokenType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getDstElementsAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().dstElements);
  }

  ::llvm::APInt getDstElements();
  ::mlir::UnitAttr getBypassL1Attr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().bypassL1);
  }

  ::std::optional<bool> getBypassL1();
  void setDstElementsAttr(::mlir::IntegerAttr attr) {
    getProperties().dstElements = attr;
  }

  void setDstElements(::llvm::APInt attrValue);
  void setBypassL1Attr(::mlir::UnitAttr attr) {
    getProperties().bypassL1 = attr;
  }

  void setBypassL1(bool attrValue);
  ::mlir::Attribute removeBypassL1Attr() {
      auto attr = getProperties().bypassL1;
      getProperties().bypassL1 = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type asyncToken, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::mlir::IntegerAttr dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type asyncToken, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::mlir::IntegerAttr dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type asyncToken, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::mlir::IntegerAttr dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::mlir::IntegerAttr dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::mlir::IntegerAttr dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::mlir::IntegerAttr dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::mlir::IntegerAttr dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::mlir::IntegerAttr dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::mlir::IntegerAttr dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type asyncToken, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::llvm::APInt dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type asyncToken, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::llvm::APInt dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type asyncToken, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::llvm::APInt dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::llvm::APInt dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::llvm::APInt dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::llvm::APInt dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::llvm::APInt dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::llvm::APInt dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static DeviceAsyncCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value dst, ::mlir::ValueRange dstIndices, ::mlir::Value src, ::mlir::ValueRange srcIndices, ::llvm::APInt dstElements, /*optional*/::mlir::Value srcElements, /*optional*/::mlir::UnitAttr bypassL1);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeviceAsyncCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeviceAsyncCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeviceAsyncCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeviceAsyncCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeviceAsyncCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeviceAsyncCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeviceAsyncCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeviceAsyncCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::DeviceAsyncCopyOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::DeviceAsyncCreateGroupOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeviceAsyncCreateGroupOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DeviceAsyncCreateGroupOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.device_async_create_group", odsAttrs.getContext());
  }

  DeviceAsyncCreateGroupOpGenericAdaptorBase(DeviceAsyncCreateGroupOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class DeviceAsyncCreateGroupOpGenericAdaptor : public detail::DeviceAsyncCreateGroupOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeviceAsyncCreateGroupOpGenericAdaptorBase;
  static constexpr int odsIndex_inputTokens = 0;
public:
  DeviceAsyncCreateGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeviceAsyncCreateGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeviceAsyncCreateGroupOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeviceAsyncCreateGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DeviceAsyncCreateGroupOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeviceAsyncCreateGroupOpGenericAdaptor(RangeT values, const DeviceAsyncCreateGroupOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeviceAsyncCreateGroupOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeviceAsyncCreateGroupOp>>>
  DeviceAsyncCreateGroupOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputTokens() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DeviceAsyncCreateGroupOpAdaptor : public DeviceAsyncCreateGroupOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeviceAsyncCreateGroupOpGenericAdaptor::DeviceAsyncCreateGroupOpGenericAdaptor;
  DeviceAsyncCreateGroupOpAdaptor(DeviceAsyncCreateGroupOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeviceAsyncCreateGroupOp : public ::mlir::Op<DeviceAsyncCreateGroupOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::nvgpu::DeviceAsyncTokenType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeviceAsyncCreateGroupOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeviceAsyncCreateGroupOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputTokens = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.device_async_create_group");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputTokens() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getInputTokensMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::DeviceAsyncTokenType> getAsyncToken() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::DeviceAsyncTokenType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type asyncToken, ::mlir::ValueRange inputTokens);
  static DeviceAsyncCreateGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type asyncToken, ::mlir::ValueRange inputTokens);
  static DeviceAsyncCreateGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type asyncToken, ::mlir::ValueRange inputTokens);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeviceAsyncCreateGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeviceAsyncCreateGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeviceAsyncCreateGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeviceAsyncCreateGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeviceAsyncCreateGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeviceAsyncCreateGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeviceAsyncCreateGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeviceAsyncCreateGroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::DeviceAsyncCreateGroupOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::DeviceAsyncWaitOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeviceAsyncWaitOpGenericAdaptorBase {
public:
  struct Properties {
    using numGroupsTy = ::mlir::IntegerAttr;
    numGroupsTy numGroups;

    auto getNumGroups() const {
      auto &propStorage = this->numGroups;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setNumGroups(const ::mlir::IntegerAttr &propValue) {
      this->numGroups = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.numGroups == this->numGroups &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DeviceAsyncWaitOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.device_async_wait", odsAttrs.getContext());
  }

  DeviceAsyncWaitOpGenericAdaptorBase(DeviceAsyncWaitOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getNumGroupsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().numGroups);
    return attr;
  }

  ::std::optional<uint32_t> getNumGroups();
};

} // namespace detail
template <typename RangeT>
class DeviceAsyncWaitOpGenericAdaptor : public detail::DeviceAsyncWaitOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeviceAsyncWaitOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
public:
  DeviceAsyncWaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeviceAsyncWaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeviceAsyncWaitOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeviceAsyncWaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DeviceAsyncWaitOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeviceAsyncWaitOpGenericAdaptor(RangeT values, const DeviceAsyncWaitOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeviceAsyncWaitOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeviceAsyncWaitOp>>>
  DeviceAsyncWaitOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getAsyncDependencies() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DeviceAsyncWaitOpAdaptor : public DeviceAsyncWaitOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeviceAsyncWaitOpGenericAdaptor::DeviceAsyncWaitOpGenericAdaptor;
  DeviceAsyncWaitOpAdaptor(DeviceAsyncWaitOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeviceAsyncWaitOp : public ::mlir::Op<DeviceAsyncWaitOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeviceAsyncWaitOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeviceAsyncWaitOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("numGroups")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNumGroupsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNumGroupsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.device_async_wait");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::DeviceAsyncTokenType> getAsyncDependencies() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::DeviceAsyncTokenType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getAsyncDependenciesMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getNumGroupsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().numGroups);
  }

  ::std::optional<uint32_t> getNumGroups();
  void setNumGroupsAttr(::mlir::IntegerAttr attr) {
    getProperties().numGroups = attr;
  }

  void setNumGroups(::std::optional<uint32_t> attrValue);
  ::mlir::Attribute removeNumGroupsAttr() {
      auto attr = getProperties().numGroups;
      getProperties().numGroups = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value asyncDependencies, /*optional*/::mlir::IntegerAttr numGroups);
  static DeviceAsyncWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value asyncDependencies, /*optional*/::mlir::IntegerAttr numGroups);
  static DeviceAsyncWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value asyncDependencies, /*optional*/::mlir::IntegerAttr numGroups);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value asyncDependencies, /*optional*/::mlir::IntegerAttr numGroups);
  static DeviceAsyncWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value asyncDependencies, /*optional*/::mlir::IntegerAttr numGroups);
  static DeviceAsyncWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value asyncDependencies, /*optional*/::mlir::IntegerAttr numGroups);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeviceAsyncWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeviceAsyncWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeviceAsyncWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeviceAsyncWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::DeviceAsyncWaitOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::LdMatrixOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LdMatrixOpGenericAdaptorBase {
public:
  struct Properties {
    using numTilesTy = ::mlir::IntegerAttr;
    numTilesTy numTiles;

    auto getNumTiles() const {
      auto &propStorage = this->numTiles;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setNumTiles(const ::mlir::IntegerAttr &propValue) {
      this->numTiles = propValue;
    }
    using transposeTy = ::mlir::BoolAttr;
    transposeTy transpose;

    auto getTranspose() const {
      auto &propStorage = this->transpose;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setTranspose(const ::mlir::BoolAttr &propValue) {
      this->transpose = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.numTiles == this->numTiles &&
        rhs.transpose == this->transpose &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LdMatrixOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.ldmatrix", odsAttrs.getContext());
  }

  LdMatrixOpGenericAdaptorBase(LdMatrixOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getTransposeAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().transpose);
    return attr;
  }

  bool getTranspose();
  ::mlir::IntegerAttr getNumTilesAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().numTiles);
    return attr;
  }

  uint32_t getNumTiles();
};

} // namespace detail
template <typename RangeT>
class LdMatrixOpGenericAdaptor : public detail::LdMatrixOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LdMatrixOpGenericAdaptorBase;
  static constexpr int odsIndex_srcMemref = 0;
  static constexpr int odsIndex_indices = 1;
public:
  LdMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LdMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LdMatrixOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LdMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LdMatrixOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LdMatrixOpGenericAdaptor(RangeT values, const LdMatrixOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LdMatrixOp, typename = std::enable_if_t<std::is_same_v<LateInst, LdMatrixOp>>>
  LdMatrixOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSrcMemref() {
    return (*getODSOperands(0).begin());
  }

  RangeT getIndices() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LdMatrixOpAdaptor : public LdMatrixOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LdMatrixOpGenericAdaptor::LdMatrixOpGenericAdaptor;
  LdMatrixOpAdaptor(LdMatrixOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LdMatrixOp : public ::mlir::Op<LdMatrixOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LdMatrixOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LdMatrixOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_srcMemref = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("numTiles"), ::llvm::StringRef("transpose")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNumTilesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNumTilesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTransposeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTransposeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.ldmatrix");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSrcMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getSrcMemrefMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::BoolAttr getTransposeAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().transpose);
  }

  bool getTranspose();
  ::mlir::IntegerAttr getNumTilesAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().numTiles);
  }

  uint32_t getNumTiles();
  void setTransposeAttr(::mlir::BoolAttr attr) {
    getProperties().transpose = attr;
  }

  void setTranspose(bool attrValue);
  void setNumTilesAttr(::mlir::IntegerAttr attr) {
    getProperties().numTiles = attr;
  }

  void setNumTiles(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::BoolAttr transpose, ::mlir::IntegerAttr numTiles);
  static LdMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::BoolAttr transpose, ::mlir::IntegerAttr numTiles);
  static LdMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::BoolAttr transpose, ::mlir::IntegerAttr numTiles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::BoolAttr transpose, ::mlir::IntegerAttr numTiles);
  static LdMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::BoolAttr transpose, ::mlir::IntegerAttr numTiles);
  static LdMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::BoolAttr transpose, ::mlir::IntegerAttr numTiles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, bool transpose, uint32_t numTiles);
  static LdMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, bool transpose, uint32_t numTiles);
  static LdMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, bool transpose, uint32_t numTiles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, bool transpose, uint32_t numTiles);
  static LdMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, bool transpose, uint32_t numTiles);
  static LdMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, bool transpose, uint32_t numTiles);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LdMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LdMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LdMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LdMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::LdMatrixOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::MBarrierArriveExpectTxOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MBarrierArriveExpectTxOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MBarrierArriveExpectTxOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.mbarrier.arrive.expect_tx", odsAttrs.getContext());
  }

  MBarrierArriveExpectTxOpGenericAdaptorBase(MBarrierArriveExpectTxOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class MBarrierArriveExpectTxOpGenericAdaptor : public detail::MBarrierArriveExpectTxOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MBarrierArriveExpectTxOpGenericAdaptorBase;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_txcount = 1;
  static constexpr int odsIndex_mbarId = 2;
  static constexpr int odsIndex_predicate = 3;
public:
  MBarrierArriveExpectTxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MBarrierArriveExpectTxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MBarrierArriveExpectTxOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MBarrierArriveExpectTxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MBarrierArriveExpectTxOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MBarrierArriveExpectTxOpGenericAdaptor(RangeT values, const MBarrierArriveExpectTxOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MBarrierArriveExpectTxOp, typename = std::enable_if_t<std::is_same_v<LateInst, MBarrierArriveExpectTxOp>>>
  MBarrierArriveExpectTxOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBarriers() {
    return (*getODSOperands(0).begin());
  }

  ValueT getTxcount() {
    return (*getODSOperands(1).begin());
  }

  ValueT getMbarId() {
    return (*getODSOperands(2).begin());
  }

  ValueT getPredicate() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MBarrierArriveExpectTxOpAdaptor : public MBarrierArriveExpectTxOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MBarrierArriveExpectTxOpGenericAdaptor::MBarrierArriveExpectTxOpGenericAdaptor;
  MBarrierArriveExpectTxOpAdaptor(MBarrierArriveExpectTxOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MBarrierArriveExpectTxOp : public ::mlir::Op<MBarrierArriveExpectTxOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MBarrierArriveExpectTxOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MBarrierArriveExpectTxOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_txcount = 1;
  static constexpr int odsIndex_mbarId = 2;
  static constexpr int odsIndex_predicate = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.mbarrier.arrive.expect_tx");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType> getBarriers() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getTxcount() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getMbarId() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getPredicate() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getBarriersMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTxcountMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMbarIdMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getPredicateMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value barriers, ::mlir::Value txcount, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static MBarrierArriveExpectTxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value barriers, ::mlir::Value txcount, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static MBarrierArriveExpectTxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value barriers, ::mlir::Value txcount, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value txcount, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static MBarrierArriveExpectTxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value txcount, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static MBarrierArriveExpectTxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value txcount, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierArriveExpectTxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierArriveExpectTxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierArriveExpectTxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierArriveExpectTxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MBarrierArriveExpectTxOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::MBarrierArriveNoCompleteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MBarrierArriveNoCompleteOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MBarrierArriveNoCompleteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.mbarrier.arrive.nocomplete", odsAttrs.getContext());
  }

  MBarrierArriveNoCompleteOpGenericAdaptorBase(MBarrierArriveNoCompleteOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class MBarrierArriveNoCompleteOpGenericAdaptor : public detail::MBarrierArriveNoCompleteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MBarrierArriveNoCompleteOpGenericAdaptorBase;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_mbarId = 1;
  static constexpr int odsIndex_count = 2;
public:
  MBarrierArriveNoCompleteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MBarrierArriveNoCompleteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MBarrierArriveNoCompleteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MBarrierArriveNoCompleteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MBarrierArriveNoCompleteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MBarrierArriveNoCompleteOpGenericAdaptor(RangeT values, const MBarrierArriveNoCompleteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MBarrierArriveNoCompleteOp, typename = std::enable_if_t<std::is_same_v<LateInst, MBarrierArriveNoCompleteOp>>>
  MBarrierArriveNoCompleteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBarriers() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMbarId() {
    return (*getODSOperands(1).begin());
  }

  ValueT getCount() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MBarrierArriveNoCompleteOpAdaptor : public MBarrierArriveNoCompleteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MBarrierArriveNoCompleteOpGenericAdaptor::MBarrierArriveNoCompleteOpGenericAdaptor;
  MBarrierArriveNoCompleteOpAdaptor(MBarrierArriveNoCompleteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MBarrierArriveNoCompleteOp : public ::mlir::Op<MBarrierArriveNoCompleteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::nvgpu::MBarrierTokenType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MBarrierArriveNoCompleteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MBarrierArriveNoCompleteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_mbarId = 1;
  static constexpr int odsIndex_count = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.mbarrier.arrive.nocomplete");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType> getBarriers() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getMbarId() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCount() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getBarriersMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMbarIdMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getCountMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierTokenType> getToken() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierTokenType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type token, ::mlir::Value barriers, ::mlir::Value mbarId, ::mlir::Value count);
  static MBarrierArriveNoCompleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type token, ::mlir::Value barriers, ::mlir::Value mbarId, ::mlir::Value count);
  static MBarrierArriveNoCompleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type token, ::mlir::Value barriers, ::mlir::Value mbarId, ::mlir::Value count);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value barriers, ::mlir::Value mbarId, ::mlir::Value count);
  static MBarrierArriveNoCompleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value barriers, ::mlir::Value mbarId, ::mlir::Value count);
  static MBarrierArriveNoCompleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value barriers, ::mlir::Value mbarId, ::mlir::Value count);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value mbarId, ::mlir::Value count);
  static MBarrierArriveNoCompleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value mbarId, ::mlir::Value count);
  static MBarrierArriveNoCompleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value mbarId, ::mlir::Value count);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierArriveNoCompleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierArriveNoCompleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierArriveNoCompleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierArriveNoCompleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierArriveNoCompleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierArriveNoCompleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierArriveNoCompleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierArriveNoCompleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MBarrierArriveNoCompleteOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::MBarrierArriveOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MBarrierArriveOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MBarrierArriveOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.mbarrier.arrive", odsAttrs.getContext());
  }

  MBarrierArriveOpGenericAdaptorBase(MBarrierArriveOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class MBarrierArriveOpGenericAdaptor : public detail::MBarrierArriveOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MBarrierArriveOpGenericAdaptorBase;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_mbarId = 1;
public:
  MBarrierArriveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MBarrierArriveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MBarrierArriveOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MBarrierArriveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MBarrierArriveOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MBarrierArriveOpGenericAdaptor(RangeT values, const MBarrierArriveOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MBarrierArriveOp, typename = std::enable_if_t<std::is_same_v<LateInst, MBarrierArriveOp>>>
  MBarrierArriveOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBarriers() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMbarId() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MBarrierArriveOpAdaptor : public MBarrierArriveOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MBarrierArriveOpGenericAdaptor::MBarrierArriveOpGenericAdaptor;
  MBarrierArriveOpAdaptor(MBarrierArriveOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MBarrierArriveOp : public ::mlir::Op<MBarrierArriveOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::nvgpu::MBarrierTokenType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MBarrierArriveOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MBarrierArriveOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_mbarId = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.mbarrier.arrive");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType> getBarriers() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getMbarId() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getBarriersMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMbarIdMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierTokenType> getToken() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierTokenType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type token, ::mlir::Value barriers, ::mlir::Value mbarId);
  static MBarrierArriveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type token, ::mlir::Value barriers, ::mlir::Value mbarId);
  static MBarrierArriveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type token, ::mlir::Value barriers, ::mlir::Value mbarId);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value barriers, ::mlir::Value mbarId);
  static MBarrierArriveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value barriers, ::mlir::Value mbarId);
  static MBarrierArriveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value barriers, ::mlir::Value mbarId);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value mbarId);
  static MBarrierArriveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value mbarId);
  static MBarrierArriveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value mbarId);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierArriveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierArriveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierArriveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierArriveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierArriveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierArriveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierArriveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierArriveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MBarrierArriveOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::MBarrierCreateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MBarrierCreateOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MBarrierCreateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.mbarrier.create", odsAttrs.getContext());
  }

  MBarrierCreateOpGenericAdaptorBase(MBarrierCreateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class MBarrierCreateOpGenericAdaptor : public detail::MBarrierCreateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MBarrierCreateOpGenericAdaptorBase;
public:
  MBarrierCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MBarrierCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MBarrierCreateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MBarrierCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MBarrierCreateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MBarrierCreateOpGenericAdaptor(RangeT values, const MBarrierCreateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MBarrierCreateOp, typename = std::enable_if_t<std::is_same_v<LateInst, MBarrierCreateOp>>>
  MBarrierCreateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MBarrierCreateOpAdaptor : public MBarrierCreateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MBarrierCreateOpGenericAdaptor::MBarrierCreateOpGenericAdaptor;
  MBarrierCreateOpAdaptor(MBarrierCreateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MBarrierCreateOp : public ::mlir::Op<MBarrierCreateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::nvgpu::MBarrierGroupType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MBarrierCreateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MBarrierCreateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.mbarrier.create");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType> getBarriers() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type barriers);
  static MBarrierCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type barriers);
  static MBarrierCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type barriers);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static MBarrierCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static MBarrierCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MBarrierCreateOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::MBarrierGetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MBarrierGetOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MBarrierGetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.mbarrier.get", odsAttrs.getContext());
  }

  MBarrierGetOpGenericAdaptorBase(MBarrierGetOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class MBarrierGetOpGenericAdaptor : public detail::MBarrierGetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MBarrierGetOpGenericAdaptorBase;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_mbarId = 1;
public:
  MBarrierGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MBarrierGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MBarrierGetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MBarrierGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MBarrierGetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MBarrierGetOpGenericAdaptor(RangeT values, const MBarrierGetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MBarrierGetOp, typename = std::enable_if_t<std::is_same_v<LateInst, MBarrierGetOp>>>
  MBarrierGetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBarriers() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMbarId() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MBarrierGetOpAdaptor : public MBarrierGetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MBarrierGetOpGenericAdaptor::MBarrierGetOpGenericAdaptor;
  MBarrierGetOpAdaptor(MBarrierGetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MBarrierGetOp : public ::mlir::Op<MBarrierGetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MBarrierGetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MBarrierGetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_mbarId = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.mbarrier.get");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType> getBarriers() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getMbarId() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getBarriersMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMbarIdMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getMbarrierPointer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type mbarrierPointer, ::mlir::Value barriers, ::mlir::Value mbarId);
  static MBarrierGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type mbarrierPointer, ::mlir::Value barriers, ::mlir::Value mbarId);
  static MBarrierGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type mbarrierPointer, ::mlir::Value barriers, ::mlir::Value mbarId);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value mbarId);
  static MBarrierGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value mbarId);
  static MBarrierGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value mbarId);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MBarrierGetOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::MBarrierInitOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MBarrierInitOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MBarrierInitOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.mbarrier.init", odsAttrs.getContext());
  }

  MBarrierInitOpGenericAdaptorBase(MBarrierInitOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class MBarrierInitOpGenericAdaptor : public detail::MBarrierInitOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MBarrierInitOpGenericAdaptorBase;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_count = 1;
  static constexpr int odsIndex_mbarId = 2;
  static constexpr int odsIndex_predicate = 3;
public:
  MBarrierInitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MBarrierInitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MBarrierInitOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MBarrierInitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MBarrierInitOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MBarrierInitOpGenericAdaptor(RangeT values, const MBarrierInitOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MBarrierInitOp, typename = std::enable_if_t<std::is_same_v<LateInst, MBarrierInitOp>>>
  MBarrierInitOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBarriers() {
    return (*getODSOperands(0).begin());
  }

  ValueT getCount() {
    return (*getODSOperands(1).begin());
  }

  ValueT getMbarId() {
    return (*getODSOperands(2).begin());
  }

  ValueT getPredicate() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MBarrierInitOpAdaptor : public MBarrierInitOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MBarrierInitOpGenericAdaptor::MBarrierInitOpGenericAdaptor;
  MBarrierInitOpAdaptor(MBarrierInitOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MBarrierInitOp : public ::mlir::Op<MBarrierInitOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MBarrierInitOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MBarrierInitOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_count = 1;
  static constexpr int odsIndex_mbarId = 2;
  static constexpr int odsIndex_predicate = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.mbarrier.init");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType> getBarriers() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCount() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getMbarId() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getPredicate() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getBarriersMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getCountMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMbarIdMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getPredicateMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value barriers, ::mlir::Value count, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static MBarrierInitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value barriers, ::mlir::Value count, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static MBarrierInitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value barriers, ::mlir::Value count, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value count, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static MBarrierInitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value count, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static MBarrierInitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value count, ::mlir::Value mbarId, /*optional*/::mlir::Value predicate);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierInitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierInitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierInitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierInitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MBarrierInitOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::MBarrierTestWaitOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MBarrierTestWaitOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MBarrierTestWaitOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.mbarrier.test.wait", odsAttrs.getContext());
  }

  MBarrierTestWaitOpGenericAdaptorBase(MBarrierTestWaitOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class MBarrierTestWaitOpGenericAdaptor : public detail::MBarrierTestWaitOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MBarrierTestWaitOpGenericAdaptorBase;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_token = 1;
  static constexpr int odsIndex_mbarId = 2;
public:
  MBarrierTestWaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MBarrierTestWaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MBarrierTestWaitOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MBarrierTestWaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MBarrierTestWaitOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MBarrierTestWaitOpGenericAdaptor(RangeT values, const MBarrierTestWaitOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MBarrierTestWaitOp, typename = std::enable_if_t<std::is_same_v<LateInst, MBarrierTestWaitOp>>>
  MBarrierTestWaitOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBarriers() {
    return (*getODSOperands(0).begin());
  }

  ValueT getToken() {
    return (*getODSOperands(1).begin());
  }

  ValueT getMbarId() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MBarrierTestWaitOpAdaptor : public MBarrierTestWaitOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MBarrierTestWaitOpGenericAdaptor::MBarrierTestWaitOpGenericAdaptor;
  MBarrierTestWaitOpAdaptor(MBarrierTestWaitOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MBarrierTestWaitOp : public ::mlir::Op<MBarrierTestWaitOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MBarrierTestWaitOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MBarrierTestWaitOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_token = 1;
  static constexpr int odsIndex_mbarId = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.mbarrier.test.wait");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType> getBarriers() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierTokenType> getToken() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierTokenType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getMbarId() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getBarriersMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTokenMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMbarIdMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getWaitComplete() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type waitComplete, ::mlir::Value barriers, ::mlir::Value token, ::mlir::Value mbarId);
  static MBarrierTestWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type waitComplete, ::mlir::Value barriers, ::mlir::Value token, ::mlir::Value mbarId);
  static MBarrierTestWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type waitComplete, ::mlir::Value barriers, ::mlir::Value token, ::mlir::Value mbarId);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value barriers, ::mlir::Value token, ::mlir::Value mbarId);
  static MBarrierTestWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value barriers, ::mlir::Value token, ::mlir::Value mbarId);
  static MBarrierTestWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value barriers, ::mlir::Value token, ::mlir::Value mbarId);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value token, ::mlir::Value mbarId);
  static MBarrierTestWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value token, ::mlir::Value mbarId);
  static MBarrierTestWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value token, ::mlir::Value mbarId);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierTestWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierTestWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierTestWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierTestWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierTestWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierTestWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierTestWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierTestWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MBarrierTestWaitOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::MBarrierTryWaitParityOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MBarrierTryWaitParityOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MBarrierTryWaitParityOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.mbarrier.try_wait.parity", odsAttrs.getContext());
  }

  MBarrierTryWaitParityOpGenericAdaptorBase(MBarrierTryWaitParityOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class MBarrierTryWaitParityOpGenericAdaptor : public detail::MBarrierTryWaitParityOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MBarrierTryWaitParityOpGenericAdaptorBase;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_phaseParity = 1;
  static constexpr int odsIndex_ticks = 2;
  static constexpr int odsIndex_mbarId = 3;
public:
  MBarrierTryWaitParityOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MBarrierTryWaitParityOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MBarrierTryWaitParityOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MBarrierTryWaitParityOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MBarrierTryWaitParityOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MBarrierTryWaitParityOpGenericAdaptor(RangeT values, const MBarrierTryWaitParityOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MBarrierTryWaitParityOp, typename = std::enable_if_t<std::is_same_v<LateInst, MBarrierTryWaitParityOp>>>
  MBarrierTryWaitParityOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBarriers() {
    return (*getODSOperands(0).begin());
  }

  ValueT getPhaseParity() {
    return (*getODSOperands(1).begin());
  }

  ValueT getTicks() {
    return (*getODSOperands(2).begin());
  }

  ValueT getMbarId() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MBarrierTryWaitParityOpAdaptor : public MBarrierTryWaitParityOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MBarrierTryWaitParityOpGenericAdaptor::MBarrierTryWaitParityOpGenericAdaptor;
  MBarrierTryWaitParityOpAdaptor(MBarrierTryWaitParityOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MBarrierTryWaitParityOp : public ::mlir::Op<MBarrierTryWaitParityOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<4>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MBarrierTryWaitParityOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MBarrierTryWaitParityOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_barriers = 0;
  static constexpr int odsIndex_phaseParity = 1;
  static constexpr int odsIndex_ticks = 2;
  static constexpr int odsIndex_mbarId = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.mbarrier.try_wait.parity");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType> getBarriers() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getPhaseParity() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getTicks() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getMbarId() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(3).begin());
  }

  ::mlir::OpOperand &getBarriersMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPhaseParityMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTicksMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMbarIdMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value barriers, ::mlir::Value phaseParity, ::mlir::Value ticks, ::mlir::Value mbarId);
  static MBarrierTryWaitParityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value barriers, ::mlir::Value phaseParity, ::mlir::Value ticks, ::mlir::Value mbarId);
  static MBarrierTryWaitParityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value barriers, ::mlir::Value phaseParity, ::mlir::Value ticks, ::mlir::Value mbarId);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value phaseParity, ::mlir::Value ticks, ::mlir::Value mbarId);
  static MBarrierTryWaitParityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value phaseParity, ::mlir::Value ticks, ::mlir::Value mbarId);
  static MBarrierTryWaitParityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value barriers, ::mlir::Value phaseParity, ::mlir::Value ticks, ::mlir::Value mbarId);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierTryWaitParityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MBarrierTryWaitParityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierTryWaitParityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MBarrierTryWaitParityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MBarrierTryWaitParityOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::MmaSparseSyncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MmaSparseSyncOpGenericAdaptorBase {
public:
  struct Properties {
    using mmaShapeTy = ::mlir::ArrayAttr;
    mmaShapeTy mmaShape;

    auto getMmaShape() const {
      auto &propStorage = this->mmaShape;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setMmaShape(const ::mlir::ArrayAttr &propValue) {
      this->mmaShape = propValue;
    }
    using sparsitySelectorTy = ::mlir::IntegerAttr;
    sparsitySelectorTy sparsitySelector;

    auto getSparsitySelector() const {
      auto &propStorage = this->sparsitySelector;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setSparsitySelector(const ::mlir::IntegerAttr &propValue) {
      this->sparsitySelector = propValue;
    }
    using tf32EnabledTy = ::mlir::UnitAttr;
    tf32EnabledTy tf32Enabled;

    auto getTf32Enabled() const {
      auto &propStorage = this->tf32Enabled;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setTf32Enabled(const ::mlir::UnitAttr &propValue) {
      this->tf32Enabled = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.mmaShape == this->mmaShape &&
        rhs.sparsitySelector == this->sparsitySelector &&
        rhs.tf32Enabled == this->tf32Enabled &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MmaSparseSyncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.mma.sp.sync", odsAttrs.getContext());
  }

  MmaSparseSyncOpGenericAdaptorBase(MmaSparseSyncOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getMmaShapeAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().mmaShape);
    return attr;
  }

  ::mlir::ArrayAttr getMmaShape();
  ::mlir::IntegerAttr getSparsitySelectorAttr();
  uint32_t getSparsitySelector();
  ::mlir::UnitAttr getTf32EnabledAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().tf32Enabled);
    return attr;
  }

  ::std::optional<bool> getTf32Enabled();
};

} // namespace detail
template <typename RangeT>
class MmaSparseSyncOpGenericAdaptor : public detail::MmaSparseSyncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MmaSparseSyncOpGenericAdaptorBase;
  static constexpr int odsIndex_matrixA = 0;
  static constexpr int odsIndex_matrixB = 1;
  static constexpr int odsIndex_matrixC = 2;
  static constexpr int odsIndex_sparseMetadata = 3;
public:
  MmaSparseSyncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MmaSparseSyncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MmaSparseSyncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MmaSparseSyncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MmaSparseSyncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MmaSparseSyncOpGenericAdaptor(RangeT values, const MmaSparseSyncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MmaSparseSyncOp, typename = std::enable_if_t<std::is_same_v<LateInst, MmaSparseSyncOp>>>
  MmaSparseSyncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMatrixA() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMatrixB() {
    return (*getODSOperands(1).begin());
  }

  ValueT getMatrixC() {
    return (*getODSOperands(2).begin());
  }

  ValueT getSparseMetadata() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MmaSparseSyncOpAdaptor : public MmaSparseSyncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MmaSparseSyncOpGenericAdaptor::MmaSparseSyncOpGenericAdaptor;
  MmaSparseSyncOpAdaptor(MmaSparseSyncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MmaSparseSyncOp : public ::mlir::Op<MmaSparseSyncOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<4>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MmaSparseSyncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MmaSparseSyncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_matrixA = 0;
  static constexpr int odsIndex_matrixB = 1;
  static constexpr int odsIndex_matrixC = 2;
  static constexpr int odsIndex_sparseMetadata = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("mmaShape"), ::llvm::StringRef("sparsitySelector"), ::llvm::StringRef("tf32Enabled")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMmaShapeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMmaShapeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSparsitySelectorAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSparsitySelectorAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getTf32EnabledAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getTf32EnabledAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.mma.sp.sync");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getMatrixA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getMatrixB() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getMatrixC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getSparseMetadata() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(3).begin());
  }

  ::mlir::OpOperand &getMatrixAMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMatrixBMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMatrixCMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSparseMetadataMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getMmaShapeAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().mmaShape);
  }

  ::mlir::ArrayAttr getMmaShape();
  ::mlir::IntegerAttr getSparsitySelectorAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().sparsitySelector);
  }

  uint32_t getSparsitySelector();
  ::mlir::UnitAttr getTf32EnabledAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().tf32Enabled);
  }

  ::std::optional<bool> getTf32Enabled();
  void setMmaShapeAttr(::mlir::ArrayAttr attr) {
    getProperties().mmaShape = attr;
  }

  void setSparsitySelectorAttr(::mlir::IntegerAttr attr) {
    getProperties().sparsitySelector = attr;
  }

  void setSparsitySelector(uint32_t attrValue);
  void setTf32EnabledAttr(::mlir::UnitAttr attr) {
    getProperties().tf32Enabled = attr;
  }

  void setTf32Enabled(bool attrValue);
  ::mlir::Attribute removeTf32EnabledAttr() {
      auto attr = getProperties().tf32Enabled;
      getProperties().tf32Enabled = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value matrixA, Value matrixB, Value matrixC, Value sparseMetadata, ArrayRef<int64_t> mmaShape);
  static MmaSparseSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value matrixA, Value matrixB, Value matrixC, Value sparseMetadata, ArrayRef<int64_t> mmaShape);
  static MmaSparseSyncOp create(::mlir::ImplicitLocOpBuilder &builder, Value matrixA, Value matrixB, Value matrixC, Value sparseMetadata, ArrayRef<int64_t> mmaShape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, ::mlir::IntegerAttr sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSparseSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, ::mlir::IntegerAttr sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSparseSyncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, ::mlir::IntegerAttr sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, ::mlir::IntegerAttr sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSparseSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, ::mlir::IntegerAttr sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSparseSyncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, ::mlir::IntegerAttr sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, uint32_t sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSparseSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, uint32_t sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSparseSyncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, uint32_t sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, uint32_t sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSparseSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, uint32_t sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSparseSyncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::Value sparseMetadata, ::mlir::ArrayAttr mmaShape, uint32_t sparsitySelector, /*optional*/::mlir::UnitAttr tf32Enabled);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MmaSparseSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MmaSparseSyncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MmaSparseSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MmaSparseSyncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  std::array<int64_t, 3> getMmaShapeAsArray() {
    ArrayAttr mmaShape = this->getMmaShape();
    assert(mmaShape.size() == 3 && "mmaShape should be three integers");
    return {::llvm::cast<IntegerAttr>(mmaShape[0]).getInt(),
            ::llvm::cast<IntegerAttr>(mmaShape[1]).getInt(),
            ::llvm::cast<IntegerAttr>(mmaShape[2]).getInt()};
  }
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MmaSparseSyncOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::MmaSyncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MmaSyncOpGenericAdaptorBase {
public:
  struct Properties {
    using mmaShapeTy = ::mlir::ArrayAttr;
    mmaShapeTy mmaShape;

    auto getMmaShape() const {
      auto &propStorage = this->mmaShape;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setMmaShape(const ::mlir::ArrayAttr &propValue) {
      this->mmaShape = propValue;
    }
    using tf32EnabledTy = ::mlir::UnitAttr;
    tf32EnabledTy tf32Enabled;

    auto getTf32Enabled() const {
      auto &propStorage = this->tf32Enabled;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setTf32Enabled(const ::mlir::UnitAttr &propValue) {
      this->tf32Enabled = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.mmaShape == this->mmaShape &&
        rhs.tf32Enabled == this->tf32Enabled &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MmaSyncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.mma.sync", odsAttrs.getContext());
  }

  MmaSyncOpGenericAdaptorBase(MmaSyncOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getMmaShapeAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().mmaShape);
    return attr;
  }

  ::mlir::ArrayAttr getMmaShape();
  ::mlir::UnitAttr getTf32EnabledAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().tf32Enabled);
    return attr;
  }

  ::std::optional<bool> getTf32Enabled();
};

} // namespace detail
template <typename RangeT>
class MmaSyncOpGenericAdaptor : public detail::MmaSyncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MmaSyncOpGenericAdaptorBase;
  static constexpr int odsIndex_matrixA = 0;
  static constexpr int odsIndex_matrixB = 1;
  static constexpr int odsIndex_matrixC = 2;
public:
  MmaSyncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MmaSyncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MmaSyncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MmaSyncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MmaSyncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MmaSyncOpGenericAdaptor(RangeT values, const MmaSyncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MmaSyncOp, typename = std::enable_if_t<std::is_same_v<LateInst, MmaSyncOp>>>
  MmaSyncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMatrixA() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMatrixB() {
    return (*getODSOperands(1).begin());
  }

  ValueT getMatrixC() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MmaSyncOpAdaptor : public MmaSyncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MmaSyncOpGenericAdaptor::MmaSyncOpGenericAdaptor;
  MmaSyncOpAdaptor(MmaSyncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MmaSyncOp : public ::mlir::Op<MmaSyncOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MmaSyncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MmaSyncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_matrixA = 0;
  static constexpr int odsIndex_matrixB = 1;
  static constexpr int odsIndex_matrixC = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("mmaShape"), ::llvm::StringRef("tf32Enabled")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMmaShapeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMmaShapeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTf32EnabledAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTf32EnabledAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.mma.sync");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getMatrixA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getMatrixB() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getMatrixC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getMatrixAMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMatrixBMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMatrixCMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getMmaShapeAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().mmaShape);
  }

  ::mlir::ArrayAttr getMmaShape();
  ::mlir::UnitAttr getTf32EnabledAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().tf32Enabled);
  }

  ::std::optional<bool> getTf32Enabled();
  void setMmaShapeAttr(::mlir::ArrayAttr attr) {
    getProperties().mmaShape = attr;
  }

  void setTf32EnabledAttr(::mlir::UnitAttr attr) {
    getProperties().tf32Enabled = attr;
  }

  void setTf32Enabled(bool attrValue);
  ::mlir::Attribute removeTf32EnabledAttr() {
      auto attr = getProperties().tf32Enabled;
      getProperties().tf32Enabled = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value matrixA, Value matrixB, Value matrixC, ArrayAttr mmaShape);
  static MmaSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value matrixA, Value matrixB, Value matrixC, ArrayAttr mmaShape);
  static MmaSyncOp create(::mlir::ImplicitLocOpBuilder &builder, Value matrixA, Value matrixB, Value matrixC, ArrayAttr mmaShape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value matrixA, Value matrixB, Value matrixC, ArrayRef<int64_t> mmaShape, bool tf32Enabled = false);
  static MmaSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value matrixA, Value matrixB, Value matrixC, ArrayRef<int64_t> mmaShape, bool tf32Enabled = false);
  static MmaSyncOp create(::mlir::ImplicitLocOpBuilder &builder, Value matrixA, Value matrixB, Value matrixC, ArrayRef<int64_t> mmaShape, bool tf32Enabled = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::ArrayAttr mmaShape, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::ArrayAttr mmaShape, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSyncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::ArrayAttr mmaShape, /*optional*/::mlir::UnitAttr tf32Enabled);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::ArrayAttr mmaShape, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::ArrayAttr mmaShape, /*optional*/::mlir::UnitAttr tf32Enabled);
  static MmaSyncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value matrixA, ::mlir::Value matrixB, ::mlir::Value matrixC, ::mlir::ArrayAttr mmaShape, /*optional*/::mlir::UnitAttr tf32Enabled);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MmaSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MmaSyncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MmaSyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MmaSyncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  std::array<int64_t, 3> getMmaShapeAsArray() {
    ArrayAttr mmaShape = this->getMmaShape();
    assert(mmaShape.size() == 3 && "mmaShape should be three integers");
    return {::llvm::cast<IntegerAttr>(mmaShape[0]).getInt(),
            ::llvm::cast<IntegerAttr>(mmaShape[1]).getInt(),
            ::llvm::cast<IntegerAttr>(mmaShape[2]).getInt()};
  }
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::MmaSyncOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::RcpOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RcpOpGenericAdaptorBase {
public:
  struct Properties {
    using ftzTy = ::mlir::UnitAttr;
    ftzTy ftz;

    auto getFtz() const {
      auto &propStorage = this->ftz;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setFtz(const ::mlir::UnitAttr &propValue) {
      this->ftz = propValue;
    }
    using roundingTy = ::mlir::nvgpu::RcpRoundingModeAttr;
    roundingTy rounding;

    auto getRounding() const {
      auto &propStorage = this->rounding;
      return ::llvm::dyn_cast_or_null<::mlir::nvgpu::RcpRoundingModeAttr>(propStorage);
    }
    void setRounding(const ::mlir::nvgpu::RcpRoundingModeAttr &propValue) {
      this->rounding = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.ftz == this->ftz &&
        rhs.rounding == this->rounding &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  RcpOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.rcp", odsAttrs.getContext());
  }

  RcpOpGenericAdaptorBase(RcpOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::nvgpu::RcpRoundingModeAttr getRoundingAttr();
  ::mlir::nvgpu::RcpRoundingMode getRounding();
  ::mlir::UnitAttr getFtzAttr();
  bool getFtz();
};

} // namespace detail
template <typename RangeT>
class RcpOpGenericAdaptor : public detail::RcpOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RcpOpGenericAdaptorBase;
  static constexpr int odsIndex_in = 0;
public:
  RcpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RcpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : RcpOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RcpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RcpOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RcpOpGenericAdaptor(RangeT values, const RcpOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RcpOp, typename = std::enable_if_t<std::is_same_v<LateInst, RcpOp>>>
  RcpOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getIn() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RcpOpAdaptor : public RcpOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RcpOpGenericAdaptor::RcpOpGenericAdaptor;
  RcpOpAdaptor(RcpOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RcpOp : public ::mlir::Op<RcpOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RcpOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RcpOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_in = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("ftz"), ::llvm::StringRef("rounding")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFtzAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFtzAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getRoundingAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getRoundingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.rcp");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::nvgpu::RcpRoundingModeAttr getRoundingAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::nvgpu::RcpRoundingModeAttr>(getProperties().rounding);
  }

  ::mlir::nvgpu::RcpRoundingMode getRounding();
  ::mlir::UnitAttr getFtzAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().ftz);
  }

  bool getFtz();
  void setRoundingAttr(::mlir::nvgpu::RcpRoundingModeAttr attr) {
    getProperties().rounding = attr;
  }

  void setRounding(::mlir::nvgpu::RcpRoundingMode attrValue);
  void setFtzAttr(::mlir::UnitAttr attr) {
    getProperties().ftz = attr;
  }

  void setFtz(bool attrValue);
  ::mlir::Attribute removeFtzAttr() {
      auto attr = getProperties().ftz;
      getProperties().ftz = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type out, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingModeAttr rounding, /*optional*/::mlir::UnitAttr ftz = nullptr);
  static RcpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type out, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingModeAttr rounding, /*optional*/::mlir::UnitAttr ftz = nullptr);
  static RcpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type out, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingModeAttr rounding, /*optional*/::mlir::UnitAttr ftz = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingModeAttr rounding, /*optional*/::mlir::UnitAttr ftz = nullptr);
  static RcpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingModeAttr rounding, /*optional*/::mlir::UnitAttr ftz = nullptr);
  static RcpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingModeAttr rounding, /*optional*/::mlir::UnitAttr ftz = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingModeAttr rounding, /*optional*/::mlir::UnitAttr ftz = nullptr);
  static RcpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingModeAttr rounding, /*optional*/::mlir::UnitAttr ftz = nullptr);
  static RcpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingModeAttr rounding, /*optional*/::mlir::UnitAttr ftz = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type out, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingMode rounding = RcpRoundingMode::APPROX, /*optional*/bool ftz = false);
  static RcpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type out, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingMode rounding = RcpRoundingMode::APPROX, /*optional*/bool ftz = false);
  static RcpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type out, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingMode rounding = RcpRoundingMode::APPROX, /*optional*/bool ftz = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingMode rounding = RcpRoundingMode::APPROX, /*optional*/bool ftz = false);
  static RcpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingMode rounding = RcpRoundingMode::APPROX, /*optional*/bool ftz = false);
  static RcpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingMode rounding = RcpRoundingMode::APPROX, /*optional*/bool ftz = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingMode rounding = RcpRoundingMode::APPROX, /*optional*/bool ftz = false);
  static RcpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingMode rounding = RcpRoundingMode::APPROX, /*optional*/bool ftz = false);
  static RcpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::nvgpu::RcpRoundingMode rounding = RcpRoundingMode::APPROX, /*optional*/bool ftz = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RcpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RcpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RcpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RcpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RcpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RcpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RcpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RcpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::RcpOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::TmaAsyncLoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TmaAsyncLoadOpGenericAdaptorBase {
public:
  struct Properties {
    using operandSegmentSizesTy = std::array<int32_t, 7>;
    operandSegmentSizesTy operandSegmentSizes;
    ::llvm::ArrayRef<int32_t> getOperandSegmentSizes() const {
      auto &propStorage = this->operandSegmentSizes;
      return propStorage;
    }
    void setOperandSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->operandSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.operandSegmentSizes == this->operandSegmentSizes &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TmaAsyncLoadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.tma.async.load", odsAttrs.getContext());
  }

  TmaAsyncLoadOpGenericAdaptorBase(TmaAsyncLoadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class TmaAsyncLoadOpGenericAdaptor : public detail::TmaAsyncLoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TmaAsyncLoadOpGenericAdaptorBase;
  static constexpr int odsIndex_dst = 0;
  static constexpr int odsIndex_barriers = 1;
  static constexpr int odsIndex_tensorMapDescriptor = 2;
  static constexpr int odsIndex_coordinates = 3;
  static constexpr int odsIndex_mbarId = 4;
  static constexpr int odsIndex_multicastMask = 5;
  static constexpr int odsIndex_predicate = 6;
public:
  TmaAsyncLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TmaAsyncLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TmaAsyncLoadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TmaAsyncLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TmaAsyncLoadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TmaAsyncLoadOpGenericAdaptor(RangeT values, const TmaAsyncLoadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TmaAsyncLoadOp, typename = std::enable_if_t<std::is_same_v<LateInst, TmaAsyncLoadOp>>>
  TmaAsyncLoadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDst() {
    return (*getODSOperands(0).begin());
  }

  ValueT getBarriers() {
    return (*getODSOperands(1).begin());
  }

  ValueT getTensorMapDescriptor() {
    return (*getODSOperands(2).begin());
  }

  RangeT getCoordinates() {
    return getODSOperands(3);
  }

  ValueT getMbarId() {
    return (*getODSOperands(4).begin());
  }

  ValueT getMulticastMask() {
    auto operands = getODSOperands(5);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getPredicate() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TmaAsyncLoadOpAdaptor : public TmaAsyncLoadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TmaAsyncLoadOpGenericAdaptor::TmaAsyncLoadOpGenericAdaptor;
  TmaAsyncLoadOpAdaptor(TmaAsyncLoadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TmaAsyncLoadOp : public ::mlir::Op<TmaAsyncLoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<4>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TmaAsyncLoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TmaAsyncLoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dst = 0;
  static constexpr int odsIndex_barriers = 1;
  static constexpr int odsIndex_tensorMapDescriptor = 2;
  static constexpr int odsIndex_coordinates = 3;
  static constexpr int odsIndex_mbarId = 4;
  static constexpr int odsIndex_multicastMask = 5;
  static constexpr int odsIndex_predicate = 6;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.tma.async.load");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getDst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType> getBarriers() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::MBarrierGroupType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType> getTensorMapDescriptor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType>>(*getODSOperands(2).begin());
  }

  ::mlir::Operation::operand_range getCoordinates() {
    return getODSOperands(3);
  }

  ::mlir::TypedValue<::mlir::IndexType> getMbarId() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getMulticastMask() {
    auto operands = getODSOperands(5);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getPredicate() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getDstMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBarriersMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTensorMapDescriptorMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getCoordinatesMutable();
  ::mlir::OpOperand &getMbarIdMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getMulticastMaskMutable();
  ::mlir::MutableOperandRange getPredicateMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value dst, ::mlir::Value barriers, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, ::mlir::Value mbarId, /*optional*/::mlir::Value multicastMask, /*optional*/::mlir::Value predicate);
  static TmaAsyncLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value dst, ::mlir::Value barriers, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, ::mlir::Value mbarId, /*optional*/::mlir::Value multicastMask, /*optional*/::mlir::Value predicate);
  static TmaAsyncLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value dst, ::mlir::Value barriers, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, ::mlir::Value mbarId, /*optional*/::mlir::Value multicastMask, /*optional*/::mlir::Value predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value dst, ::mlir::Value barriers, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, ::mlir::Value mbarId, /*optional*/::mlir::Value multicastMask, /*optional*/::mlir::Value predicate);
  static TmaAsyncLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value dst, ::mlir::Value barriers, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, ::mlir::Value mbarId, /*optional*/::mlir::Value multicastMask, /*optional*/::mlir::Value predicate);
  static TmaAsyncLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value dst, ::mlir::Value barriers, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, ::mlir::Value mbarId, /*optional*/::mlir::Value multicastMask, /*optional*/::mlir::Value predicate);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TmaAsyncLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TmaAsyncLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TmaAsyncLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TmaAsyncLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    return {};
  }

public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::TmaAsyncLoadOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::TmaAsyncStoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TmaAsyncStoreOpGenericAdaptorBase {
public:
  struct Properties {
    using operandSegmentSizesTy = std::array<int32_t, 4>;
    operandSegmentSizesTy operandSegmentSizes;
    ::llvm::ArrayRef<int32_t> getOperandSegmentSizes() const {
      auto &propStorage = this->operandSegmentSizes;
      return propStorage;
    }
    void setOperandSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->operandSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.operandSegmentSizes == this->operandSegmentSizes &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TmaAsyncStoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.tma.async.store", odsAttrs.getContext());
  }

  TmaAsyncStoreOpGenericAdaptorBase(TmaAsyncStoreOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class TmaAsyncStoreOpGenericAdaptor : public detail::TmaAsyncStoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TmaAsyncStoreOpGenericAdaptorBase;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_tensorMapDescriptor = 1;
  static constexpr int odsIndex_coordinates = 2;
  static constexpr int odsIndex_predicate = 3;
public:
  TmaAsyncStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TmaAsyncStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TmaAsyncStoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TmaAsyncStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TmaAsyncStoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TmaAsyncStoreOpGenericAdaptor(RangeT values, const TmaAsyncStoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TmaAsyncStoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, TmaAsyncStoreOp>>>
  TmaAsyncStoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSrc() {
    return (*getODSOperands(0).begin());
  }

  ValueT getTensorMapDescriptor() {
    return (*getODSOperands(1).begin());
  }

  RangeT getCoordinates() {
    return getODSOperands(2);
  }

  ValueT getPredicate() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TmaAsyncStoreOpAdaptor : public TmaAsyncStoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TmaAsyncStoreOpGenericAdaptor::TmaAsyncStoreOpGenericAdaptor;
  TmaAsyncStoreOpAdaptor(TmaAsyncStoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TmaAsyncStoreOp : public ::mlir::Op<TmaAsyncStoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TmaAsyncStoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TmaAsyncStoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_tensorMapDescriptor = 1;
  static constexpr int odsIndex_coordinates = 2;
  static constexpr int odsIndex_predicate = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.tma.async.store");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType> getTensorMapDescriptor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getCoordinates() {
    return getODSOperands(2);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getPredicate() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTensorMapDescriptorMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getCoordinatesMutable();
  ::mlir::MutableOperandRange getPredicateMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, /*optional*/::mlir::Value predicate);
  static TmaAsyncStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, /*optional*/::mlir::Value predicate);
  static TmaAsyncStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, /*optional*/::mlir::Value predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, /*optional*/::mlir::Value predicate);
  static TmaAsyncStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, /*optional*/::mlir::Value predicate);
  static TmaAsyncStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value tensorMapDescriptor, ::mlir::ValueRange coordinates, /*optional*/::mlir::Value predicate);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TmaAsyncStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TmaAsyncStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TmaAsyncStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TmaAsyncStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    return {};
  }

public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::TmaAsyncStoreOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::TmaCreateDescriptorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TmaCreateDescriptorOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TmaCreateDescriptorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.tma.create.descriptor", odsAttrs.getContext());
  }

  TmaCreateDescriptorOpGenericAdaptorBase(TmaCreateDescriptorOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class TmaCreateDescriptorOpGenericAdaptor : public detail::TmaCreateDescriptorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TmaCreateDescriptorOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_boxDimensions = 1;
public:
  TmaCreateDescriptorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TmaCreateDescriptorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TmaCreateDescriptorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TmaCreateDescriptorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TmaCreateDescriptorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TmaCreateDescriptorOpGenericAdaptor(RangeT values, const TmaCreateDescriptorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TmaCreateDescriptorOp, typename = std::enable_if_t<std::is_same_v<LateInst, TmaCreateDescriptorOp>>>
  TmaCreateDescriptorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTensor() {
    return (*getODSOperands(0).begin());
  }

  RangeT getBoxDimensions() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TmaCreateDescriptorOpAdaptor : public TmaCreateDescriptorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TmaCreateDescriptorOpGenericAdaptor::TmaCreateDescriptorOpGenericAdaptor;
  TmaCreateDescriptorOpAdaptor(TmaCreateDescriptorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TmaCreateDescriptorOp : public ::mlir::Op<TmaCreateDescriptorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::nvgpu::TensorMapDescriptorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TmaCreateDescriptorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TmaCreateDescriptorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_boxDimensions = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.tma.create.descriptor");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::UnrankedMemRefType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::UnrankedMemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getBoxDimensions() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getTensorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getBoxDimensionsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType> getTensorMap() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type tensorMap, ::mlir::Value tensor, ::mlir::ValueRange boxDimensions);
  static TmaCreateDescriptorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type tensorMap, ::mlir::Value tensor, ::mlir::ValueRange boxDimensions);
  static TmaCreateDescriptorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type tensorMap, ::mlir::Value tensor, ::mlir::ValueRange boxDimensions);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::ValueRange boxDimensions);
  static TmaCreateDescriptorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::ValueRange boxDimensions);
  static TmaCreateDescriptorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::ValueRange boxDimensions);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TmaCreateDescriptorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TmaCreateDescriptorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TmaCreateDescriptorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TmaCreateDescriptorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::TmaCreateDescriptorOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::TmaFenceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TmaFenceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TmaFenceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.tma.fence.descriptor", odsAttrs.getContext());
  }

  TmaFenceOpGenericAdaptorBase(TmaFenceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class TmaFenceOpGenericAdaptor : public detail::TmaFenceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TmaFenceOpGenericAdaptorBase;
  static constexpr int odsIndex_tensorMapDescriptor = 0;
public:
  TmaFenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TmaFenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TmaFenceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TmaFenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TmaFenceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TmaFenceOpGenericAdaptor(RangeT values, const TmaFenceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TmaFenceOp, typename = std::enable_if_t<std::is_same_v<LateInst, TmaFenceOp>>>
  TmaFenceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTensorMapDescriptor() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TmaFenceOpAdaptor : public TmaFenceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TmaFenceOpGenericAdaptor::TmaFenceOpGenericAdaptor;
  TmaFenceOpAdaptor(TmaFenceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TmaFenceOp : public ::mlir::Op<TmaFenceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TmaFenceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TmaFenceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensorMapDescriptor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.tma.fence.descriptor");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType> getTensorMapDescriptor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTensorMapDescriptorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensorMapDescriptor);
  static TmaFenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensorMapDescriptor);
  static TmaFenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensorMapDescriptor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensorMapDescriptor);
  static TmaFenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensorMapDescriptor);
  static TmaFenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensorMapDescriptor);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TmaFenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TmaFenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TmaFenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TmaFenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::TmaFenceOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::TmaPrefetchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TmaPrefetchOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TmaPrefetchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.tma.prefetch.descriptor", odsAttrs.getContext());
  }

  TmaPrefetchOpGenericAdaptorBase(TmaPrefetchOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class TmaPrefetchOpGenericAdaptor : public detail::TmaPrefetchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TmaPrefetchOpGenericAdaptorBase;
  static constexpr int odsIndex_tensorMapDescriptor = 0;
  static constexpr int odsIndex_predicate = 1;
public:
  TmaPrefetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TmaPrefetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TmaPrefetchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TmaPrefetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TmaPrefetchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TmaPrefetchOpGenericAdaptor(RangeT values, const TmaPrefetchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TmaPrefetchOp, typename = std::enable_if_t<std::is_same_v<LateInst, TmaPrefetchOp>>>
  TmaPrefetchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTensorMapDescriptor() {
    return (*getODSOperands(0).begin());
  }

  ValueT getPredicate() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TmaPrefetchOpAdaptor : public TmaPrefetchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TmaPrefetchOpGenericAdaptor::TmaPrefetchOpGenericAdaptor;
  TmaPrefetchOpAdaptor(TmaPrefetchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TmaPrefetchOp : public ::mlir::Op<TmaPrefetchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TmaPrefetchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TmaPrefetchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensorMapDescriptor = 0;
  static constexpr int odsIndex_predicate = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.tma.prefetch.descriptor");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType> getTensorMapDescriptor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getPredicate() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getTensorMapDescriptorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getPredicateMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensorMapDescriptor, /*optional*/::mlir::Value predicate);
  static TmaPrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensorMapDescriptor, /*optional*/::mlir::Value predicate);
  static TmaPrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensorMapDescriptor, /*optional*/::mlir::Value predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensorMapDescriptor, /*optional*/::mlir::Value predicate);
  static TmaPrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensorMapDescriptor, /*optional*/::mlir::Value predicate);
  static TmaPrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensorMapDescriptor, /*optional*/::mlir::Value predicate);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TmaPrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TmaPrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TmaPrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TmaPrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::TmaPrefetchOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::WarpgroupGenerateDescriptorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WarpgroupGenerateDescriptorOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WarpgroupGenerateDescriptorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.warpgroup.generate.descriptor", odsAttrs.getContext());
  }

  WarpgroupGenerateDescriptorOpGenericAdaptorBase(WarpgroupGenerateDescriptorOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class WarpgroupGenerateDescriptorOpGenericAdaptor : public detail::WarpgroupGenerateDescriptorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WarpgroupGenerateDescriptorOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_tensorMap = 1;
public:
  WarpgroupGenerateDescriptorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WarpgroupGenerateDescriptorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WarpgroupGenerateDescriptorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WarpgroupGenerateDescriptorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WarpgroupGenerateDescriptorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WarpgroupGenerateDescriptorOpGenericAdaptor(RangeT values, const WarpgroupGenerateDescriptorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WarpgroupGenerateDescriptorOp, typename = std::enable_if_t<std::is_same_v<LateInst, WarpgroupGenerateDescriptorOp>>>
  WarpgroupGenerateDescriptorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTensor() {
    return (*getODSOperands(0).begin());
  }

  ValueT getTensorMap() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WarpgroupGenerateDescriptorOpAdaptor : public WarpgroupGenerateDescriptorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WarpgroupGenerateDescriptorOpGenericAdaptor::WarpgroupGenerateDescriptorOpGenericAdaptor;
  WarpgroupGenerateDescriptorOpAdaptor(WarpgroupGenerateDescriptorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WarpgroupGenerateDescriptorOp : public ::mlir::Op<WarpgroupGenerateDescriptorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::nvgpu::WarpgroupMatrixDescriptorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WarpgroupGenerateDescriptorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WarpgroupGenerateDescriptorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_tensorMap = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.warpgroup.generate.descriptor");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType> getTensorMap() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::TensorMapDescriptorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getTensorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTensorMapMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::WarpgroupMatrixDescriptorType> getDescriptor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::WarpgroupMatrixDescriptorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type descriptor, ::mlir::Value tensor, ::mlir::Value tensorMap);
  static WarpgroupGenerateDescriptorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type descriptor, ::mlir::Value tensor, ::mlir::Value tensorMap);
  static WarpgroupGenerateDescriptorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type descriptor, ::mlir::Value tensor, ::mlir::Value tensorMap);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::Value tensorMap);
  static WarpgroupGenerateDescriptorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::Value tensorMap);
  static WarpgroupGenerateDescriptorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::Value tensorMap);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WarpgroupGenerateDescriptorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WarpgroupGenerateDescriptorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WarpgroupGenerateDescriptorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WarpgroupGenerateDescriptorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::WarpgroupGenerateDescriptorOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::WarpgroupMmaInitAccumulatorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WarpgroupMmaInitAccumulatorOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WarpgroupMmaInitAccumulatorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.warpgroup.mma.init.accumulator", odsAttrs.getContext());
  }

  WarpgroupMmaInitAccumulatorOpGenericAdaptorBase(WarpgroupMmaInitAccumulatorOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class WarpgroupMmaInitAccumulatorOpGenericAdaptor : public detail::WarpgroupMmaInitAccumulatorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WarpgroupMmaInitAccumulatorOpGenericAdaptorBase;
public:
  WarpgroupMmaInitAccumulatorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WarpgroupMmaInitAccumulatorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WarpgroupMmaInitAccumulatorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WarpgroupMmaInitAccumulatorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WarpgroupMmaInitAccumulatorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WarpgroupMmaInitAccumulatorOpGenericAdaptor(RangeT values, const WarpgroupMmaInitAccumulatorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WarpgroupMmaInitAccumulatorOp, typename = std::enable_if_t<std::is_same_v<LateInst, WarpgroupMmaInitAccumulatorOp>>>
  WarpgroupMmaInitAccumulatorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WarpgroupMmaInitAccumulatorOpAdaptor : public WarpgroupMmaInitAccumulatorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WarpgroupMmaInitAccumulatorOpGenericAdaptor::WarpgroupMmaInitAccumulatorOpGenericAdaptor;
  WarpgroupMmaInitAccumulatorOpAdaptor(WarpgroupMmaInitAccumulatorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WarpgroupMmaInitAccumulatorOp : public ::mlir::Op<WarpgroupMmaInitAccumulatorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::nvgpu::WarpgroupAccumulatorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WarpgroupMmaInitAccumulatorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WarpgroupMmaInitAccumulatorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.warpgroup.mma.init.accumulator");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::WarpgroupAccumulatorType> getMatrixC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::WarpgroupAccumulatorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type matrixC);
  static WarpgroupMmaInitAccumulatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type matrixC);
  static WarpgroupMmaInitAccumulatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type matrixC);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static WarpgroupMmaInitAccumulatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static WarpgroupMmaInitAccumulatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WarpgroupMmaInitAccumulatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WarpgroupMmaInitAccumulatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WarpgroupMmaInitAccumulatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WarpgroupMmaInitAccumulatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::WarpgroupMmaInitAccumulatorOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::WarpgroupMmaOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WarpgroupMmaOpGenericAdaptorBase {
public:
  struct Properties {
    using transposeATy = ::mlir::UnitAttr;
    transposeATy transposeA;

    auto getTransposeA() const {
      auto &propStorage = this->transposeA;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setTransposeA(const ::mlir::UnitAttr &propValue) {
      this->transposeA = propValue;
    }
    using transposeBTy = ::mlir::UnitAttr;
    transposeBTy transposeB;

    auto getTransposeB() const {
      auto &propStorage = this->transposeB;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setTransposeB(const ::mlir::UnitAttr &propValue) {
      this->transposeB = propValue;
    }
    using waitGroupTy = ::mlir::IntegerAttr;
    waitGroupTy waitGroup;

    auto getWaitGroup() const {
      auto &propStorage = this->waitGroup;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setWaitGroup(const ::mlir::IntegerAttr &propValue) {
      this->waitGroup = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.transposeA == this->transposeA &&
        rhs.transposeB == this->transposeB &&
        rhs.waitGroup == this->waitGroup &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WarpgroupMmaOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.warpgroup.mma", odsAttrs.getContext());
  }

  WarpgroupMmaOpGenericAdaptorBase(WarpgroupMmaOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getWaitGroupAttr();
  uint64_t getWaitGroup();
  ::mlir::UnitAttr getTransposeAAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().transposeA);
    return attr;
  }

  ::std::optional<bool> getTransposeA();
  ::mlir::UnitAttr getTransposeBAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().transposeB);
    return attr;
  }

  ::std::optional<bool> getTransposeB();
};

} // namespace detail
template <typename RangeT>
class WarpgroupMmaOpGenericAdaptor : public detail::WarpgroupMmaOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WarpgroupMmaOpGenericAdaptorBase;
  static constexpr int odsIndex_descriptorA = 0;
  static constexpr int odsIndex_descriptorB = 1;
  static constexpr int odsIndex_matrixC = 2;
public:
  WarpgroupMmaOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WarpgroupMmaOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WarpgroupMmaOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WarpgroupMmaOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WarpgroupMmaOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WarpgroupMmaOpGenericAdaptor(RangeT values, const WarpgroupMmaOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WarpgroupMmaOp, typename = std::enable_if_t<std::is_same_v<LateInst, WarpgroupMmaOp>>>
  WarpgroupMmaOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDescriptorA() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDescriptorB() {
    return (*getODSOperands(1).begin());
  }

  ValueT getMatrixC() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WarpgroupMmaOpAdaptor : public WarpgroupMmaOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WarpgroupMmaOpGenericAdaptor::WarpgroupMmaOpGenericAdaptor;
  WarpgroupMmaOpAdaptor(WarpgroupMmaOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WarpgroupMmaOp : public ::mlir::Op<WarpgroupMmaOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::nvgpu::WarpgroupAccumulatorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WarpgroupMmaOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WarpgroupMmaOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_descriptorA = 0;
  static constexpr int odsIndex_descriptorB = 1;
  static constexpr int odsIndex_matrixC = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("transposeA"), ::llvm::StringRef("transposeB"), ::llvm::StringRef("waitGroup")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTransposeAAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTransposeAAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTransposeBAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTransposeBAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getWaitGroupAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getWaitGroupAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.warpgroup.mma");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::WarpgroupMatrixDescriptorType> getDescriptorA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::WarpgroupMatrixDescriptorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::nvgpu::WarpgroupMatrixDescriptorType> getDescriptorB() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::WarpgroupMatrixDescriptorType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::nvgpu::WarpgroupAccumulatorType> getMatrixC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::WarpgroupAccumulatorType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getDescriptorAMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDescriptorBMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMatrixCMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::WarpgroupAccumulatorType> getMatrixD() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::WarpgroupAccumulatorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getWaitGroupAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().waitGroup);
  }

  uint64_t getWaitGroup();
  ::mlir::UnitAttr getTransposeAAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().transposeA);
  }

  ::std::optional<bool> getTransposeA();
  ::mlir::UnitAttr getTransposeBAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().transposeB);
  }

  ::std::optional<bool> getTransposeB();
  void setWaitGroupAttr(::mlir::IntegerAttr attr) {
    getProperties().waitGroup = attr;
  }

  void setWaitGroup(::std::optional<uint64_t> attrValue);
  void setTransposeAAttr(::mlir::UnitAttr attr) {
    getProperties().transposeA = attr;
  }

  void setTransposeA(bool attrValue);
  void setTransposeBAttr(::mlir::UnitAttr attr) {
    getProperties().transposeB = attr;
  }

  void setTransposeB(bool attrValue);
  ::mlir::Attribute removeWaitGroupAttr() {
      auto attr = getProperties().waitGroup;
      getProperties().waitGroup = {};
      return attr;
  }

  ::mlir::Attribute removeTransposeAAttr() {
      auto attr = getProperties().transposeA;
      getProperties().transposeA = {};
      return attr;
  }

  ::mlir::Attribute removeTransposeBAttr() {
      auto attr = getProperties().transposeB;
      getProperties().transposeB = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type matrixD, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/::mlir::IntegerAttr waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static WarpgroupMmaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type matrixD, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/::mlir::IntegerAttr waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static WarpgroupMmaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type matrixD, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/::mlir::IntegerAttr waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/::mlir::IntegerAttr waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static WarpgroupMmaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/::mlir::IntegerAttr waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static WarpgroupMmaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/::mlir::IntegerAttr waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type matrixD, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/uint64_t waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static WarpgroupMmaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type matrixD, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/uint64_t waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static WarpgroupMmaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type matrixD, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/uint64_t waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/uint64_t waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static WarpgroupMmaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/uint64_t waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static WarpgroupMmaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value descriptorA, ::mlir::Value descriptorB, /*optional*/uint64_t waitGroup, /*optional*/::mlir::UnitAttr transposeA, /*optional*/::mlir::UnitAttr transposeB, ::mlir::Value matrixC);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WarpgroupMmaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WarpgroupMmaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WarpgroupMmaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WarpgroupMmaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::WarpgroupMmaOp)

namespace mlir::nvgpu {


//===----------------------------------------------------------------------===//
// ::mlir::nvgpu::WarpgroupMmaStoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WarpgroupMmaStoreOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WarpgroupMmaStoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("nvgpu.warpgroup.mma.store", odsAttrs.getContext());
  }

  WarpgroupMmaStoreOpGenericAdaptorBase(WarpgroupMmaStoreOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class WarpgroupMmaStoreOpGenericAdaptor : public detail::WarpgroupMmaStoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WarpgroupMmaStoreOpGenericAdaptorBase;
  static constexpr int odsIndex_matrixD = 0;
  static constexpr int odsIndex_dstMemref = 1;
public:
  WarpgroupMmaStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WarpgroupMmaStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WarpgroupMmaStoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WarpgroupMmaStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WarpgroupMmaStoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WarpgroupMmaStoreOpGenericAdaptor(RangeT values, const WarpgroupMmaStoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WarpgroupMmaStoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, WarpgroupMmaStoreOp>>>
  WarpgroupMmaStoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMatrixD() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDstMemref() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WarpgroupMmaStoreOpAdaptor : public WarpgroupMmaStoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WarpgroupMmaStoreOpGenericAdaptor::WarpgroupMmaStoreOpGenericAdaptor;
  WarpgroupMmaStoreOpAdaptor(WarpgroupMmaStoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WarpgroupMmaStoreOp : public ::mlir::Op<WarpgroupMmaStoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WarpgroupMmaStoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WarpgroupMmaStoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_matrixD = 0;
  static constexpr int odsIndex_dstMemref = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("nvgpu.warpgroup.mma.store");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::nvgpu::WarpgroupAccumulatorType> getMatrixD() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::nvgpu::WarpgroupAccumulatorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getDstMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getMatrixDMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDstMemrefMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value matrixD, ::mlir::Value dstMemref);
  static WarpgroupMmaStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value matrixD, ::mlir::Value dstMemref);
  static WarpgroupMmaStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value matrixD, ::mlir::Value dstMemref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value matrixD, ::mlir::Value dstMemref);
  static WarpgroupMmaStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value matrixD, ::mlir::Value dstMemref);
  static WarpgroupMmaStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value matrixD, ::mlir::Value dstMemref);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WarpgroupMmaStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WarpgroupMmaStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WarpgroupMmaStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WarpgroupMmaStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::nvgpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::nvgpu::WarpgroupMmaStoreOp)


#endif // GET_OP_CLASSES

