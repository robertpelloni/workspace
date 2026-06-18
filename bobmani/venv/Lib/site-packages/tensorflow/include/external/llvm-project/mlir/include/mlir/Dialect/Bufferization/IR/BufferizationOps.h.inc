/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: BufferizationOps.td                                                  *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::bufferization {

/// allocate buffer for a tensor
/// `bufferization.alloc_tensor` materializes an uninitialized tensor with a
///     given shape (dynamic or static). It always bufferizes to a new buffer
///     allocation of the given shape. The optional `copy` operand specifies the
///     contents of the tensors. If no `copy` operand is specified, reading from the
///     result of an `alloc_tensor` op yields an undefined value.
/// 
///     If `copy` is specified, no dynamic sizes should be passed, since they are
///     the same as the dynamic sizes of the `copy` operand.
/// 
///     `alloc_tensor` is a helper op for bufferization. The operation is provided
///     as an anchor that marks the beginning of a new tensor SSA use-def chain. It
///     can be used to control in-place bufferization decisions during One-Shot
///     Bufferize: The bufferized result of a `bufferization.alloc_tensor` does not
///     alias with any other buffer, so it can be used to resolve read-after-write
///     conflicts that would have been introduced by the in-place bufferization of
///     another op.
/// 
///     The optional `memory_space` attribute specifies the memory space when
///     bufferizing this op. The memory space is inferred from `copy` if specified.
///     If neither `copy` nor `memory_space` is specified, the default memory space
///     is used during bufferization.
/// 
///     The optional `size_hint` operand specifies the number of non-zero elements
///     for sparse tensors. The value of `size_hint` should be not less than 1 and
///     not larger than the linear size of the corresponding dense tensor type. If
///     this requirement is not met, the behavior of the operator is undefined.
/// 
///     Both dense and sparse tensor types are supported. The result of a
///     `bufferization.alloc_tensor` is a tensor value that can be used like any
///     other tensor value. In practice, it is often used as the "out" operand of
///     another op. Sparse tensor allocations should always be used in a local
///     construction operation and never escape the function boundary directly.
/// 
///     Example:
/// 
///     ```mlir
///     %c = bufferization.alloc_tensor(%d1, %d2) : tensor<?x?xf32, #SparseMatrix>
///     %0 = linalg.matmul
///       ins(%a, %b: tensor<?x?xf32, #SparseMatrix>, tensor<?x?xf32, #SparseMatrix>)
///       outs(%c: tensor<?x?xf32, #SparseMatrix>) -> tensor<?x?xf32, #SparseMatrix>
///     return %0 : tensor<?x?xf32, #SparseMatrix>
///     ```
/// 
///     ```mlir
///     %c = bufferization.alloc_tensor(%d1, %d2) size_hint = %noe
///       : tensor<?x?xf32, #SparseMatrix>
///     ```
/// 
///     Note: An `alloc_tensor` with a `copy` should also be expressed as an
///     `alloc_tensor` without `copy`, followed by a `copy_tensor`.
class AllocTensorOp;

} // namespace mlir::bufferization
namespace mlir::bufferization {

/// clone a memref
/// Clones the data in the input view into an implicitly defined output view.
/// 
///     Usage:
/// 
///     ```mlir
///     %arg1 = bufferization.clone %arg0 : memref<?xf32> to memref<?xf32>
///     ```
/// 
///     Valid implementations of this operation may alias the input and output
///     views or create an actual copy. Mutating the source or result
///     of the clone operation after the clone operation thus leads to undefined
///     behavior.
class CloneOp;

} // namespace mlir::bufferization
namespace mlir::bufferization {

/// deallocates the given memrefs if no alias is retained
/// This operation deallocates each of the given memrefs if there is no alias
///     to that memref in the list of retained memrefs and the corresponding
///     condition value is set. This condition can be used to indicate and pass on
///     ownership of memref values (or in other words, the responsibility of
///     deallocating that memref). If two memrefs alias each other, only one will be
///     deallocated to avoid double free situations.
/// 
///     The number of variadic `memref` operands (the memrefs to be deallocated)
///     must equal the number of variadic `condition` operands and correspond to
///     each other element-wise.
/// 
///     The `memref` operands must be the originally allocated memrefs, however, the
///     `retained` memref operands may be arbitrary memrefs.
/// 
///     This operation returns a variadic number of `updatedConditions` operands,
///     one updated condition per retained memref. An updated condition indicates
///     the ownership of the respective retained memref. It is computed as the
///     disjunction of all `conditions` operands where the corresponding to
///     `memrefs` operand aliases with the retained memref. If the retained memref
///     has no aliases among `memrefs`, the resulting updated condition is 'false'.
///     This is because all memrefs that need to be deallocated within one basic
///     block should be added to the same `bufferization.dealloc` operation at the
///     end of the block; if no aliasing memref is present, then it does not have to
///     be deallocated and thus we don't need to claim ownership. If the memrefs to
///     be deallocated are split over multiple dealloc operations (e.g., to avoid
///     aliasing checks at runtime between the `memref` operands), then the results
///     have to be manually combined using an `arith.ori` operation and all of them
///     still require the same list of `retained` memref operands unless the
///     (potentially empty) set of aliasing memrefs can be determined statically. In
///     that case, the `updatedCondition` operand can be replaced accordingly (e.g.,
///     by a canonicalizer).
/// 
///     Example:
///     ```mlir
///     %0:3 = bufferization.dealloc (%a0, %a1 : memref<2xf32>, memref<4xi32>)
///       if (%cond0, %cond1) retain (%r0, %r1, %r2 : memref<?xf32>, memref<f64>,
///       memref<2xi32>)
///     ```
///     Deallocation will be called on `%a0` if `%cond0` is 'true' and neither
///     `%r0`, `%r1`, or `%r2` are aliases of `%a0`. `%a1` will be deallocated when
///     `%cond1` is set to 'true' and none of `%r0`, `%r1`, `%r2`, and `%a0` are
///     aliases.
/// 
///     Note that this can be an expensive operation if there are many operands that
///     cannot be optimized away. The runtime cost of this operation (assuming that
///     nothing is optimized away) is `O(|memrefs|^2+|memrefs|*|retained|)`. The
///     cost in terms of memory space is `O(|memrefs|+|retained|)`. As a result, it
///     is recommended to place it carefully in the IR such that most operands can
///     be optimized away by running the `buffer-deallocation-simplification` pass.
class DeallocOp;

} // namespace mlir::bufferization
namespace mlir::bufferization {

/// release underlying storage format of given tensor
/// `bufferization.dealloc_tensor` is a buffer deallocation in tensor land. This
///     op can be used for manual buffer deallocation. Some bufferizations (such as
///     One-Shot Bufferize) take care of buffer deallocation, in which case this op
///     is usually not needed. Details can be found in the documentation of the
///     respective bufferization passes.
/// 
///     In case of a dense tensor, this op lowers to a `memref.dealloc` op during
///     bufferization.
/// 
///     In case of a sparse tensor, this op releases the underlying sparse storage
///     format for a tensor that materialized earlier through a `new` operation, a
///     `convert` operation with annotated destination tensor type (unless the
///     convert is folded away), or a `bufferization.alloc_tensor` operation. The
///     release operation should only be called once for any materialized tensor.
///     After this operation, any subsequent `memref` querying operation on the
///     tensor returns undefined results.
/// 
///     Example:
/// 
///     ```mlir
///     bufferization.dealloc_tensor %tensor : tensor<1024x1024xf64, #CSR>
///     ```
class DeallocTensorOp;

} // namespace mlir::bufferization
namespace mlir::bufferization {

/// copy a tensor
/// This op indicates that the data of the `source` tensor is guaranteed to
///     materialize in `dest`, which can be a tensor or a memref. In case of a
///     tensor, `source` materializes in the future buffer of `dest` and a the
///     updated destination tensor is returned. If this is not possible, e.g.,
///     because the destination tensor is read-only or because its original
///     contents are still read later, the input IR fails to bufferize. In case of a
///     memref, `source` materializes in `dest`, which is already a buffer. The op
///     has no results in that case.
/// 
///     `source`, `dest` and `result` (if present) must have the same runtime shape
///     and element type. If the op has a result, the types of `result` and `dest`
///     must match exactly (e.g., including any tensor encodings).
/// 
///     By default, this op bufferizes to a memcpy from the future buffer of the
///     `source` tensor to the future buffer of the `dest` tensor or to the `dest`
///     buffer. However, transformations such as "empty tensor elimination" may
///     rewrite IR such that a computation is performed directly in `dest` and no
///     memcpy is needed.
/// 
///     If `dest` is a buffer, the `writable` attribute must be specified and the
///     `restrict` keyword can be specified. These attributes have the same meaning
///     as the respective attributes of `bufferization.to_tensor`.
/// 
///     `writable` indicates that the `dest` buffer is considered writable. It does
///     not make sense to materialize a computation in a read-only buffer, so
///     `writable` is required.
/// 
///     `restrict` indicates that there is no `bufferization.to_tensor` op and no
///     other `bufferization.materialize_in_destination` op with `dest` (or an alias
///     thereof) and "restrict". Only ops with this attribute are considered for
///     "empty tensor elimination". As part of empty tensor elimination, a new
///     `to_tensor` op with `dest` may be inserted and the `restrict` attribute is
///     transferred from this op to the new `to_tensor` op. Having "restrict" on
///     this op guarantees that performing empty tensor elimination would not create
///     invalid IR (i.e., having multiple `to_tensor restrict` with aliasing
///     buffers).
/// 
///     Note: `writable` could be removed from this op because it must always be set
///     for memref destinations. This op has that attribute to make clear the
///     requirements on the `dest` operand in the op assembly format.
/// 
///     Note: If `dest` is a tensor, `tensor.insert_slice` could be used for the
///     same purpose, but since tensor dialect ops only indicate *what* should be
///     computed but not *where*, it could fold away, causing the computation to
///     materialize in a different buffer.
class MaterializeInDestinationOp;

} // namespace mlir::bufferization
namespace mlir::bufferization {

/// cast a tensor-like type to buffer-like type
/// An operation that returns the future buffer of a `tensor`.
/// 
///     ```mlir
///     // Result type is memref<4x?xf32, #layout, 0>
///     %m = bufferization.to_buffer %t : tensor<4x?xf32> to memref<4x?xf32, #layout, 0>
///     ```
/// 
///     This operation is a specialized variant of the built-in
///     `unrealized_conversion_cast` and is used to make sure that the IR stays
///     valid at any point during the bufferization.
/// 
///     The `read_only` attribute can optionally be set, indicating to the
///     bufferization that the buffer returned by this op (or an alias created from
///     the returned buffer) will not be written to.
class ToBufferOp;

} // namespace mlir::bufferization
namespace mlir::bufferization {

/// create a tensor-like type from a buffer-like type
/// An operation that creates a tensor from a buffer. The result value is a
///     tensor-like type that must match the corresponding buffer-like operand as
///     per TensorLikeType::verifyCompatibleBufferType(). For builtins (TensorType
///     and BaseMemRefType), this means that shapes and element types match between
///     the tensor and the buffer.
/// 
///     The opposite of this op is `to_buffer`. Together, these two ops are
///     useful for source/target materializations when doing type conversions
///     involving tensors and buffers.
/// 
///     Example:
/// 
///     ```mlir
///     // Produces a value of tensor<4x?xf32> type.
///     %t = bufferization.to_tensor %m : memref<4x?xf32, #layout, 0> to tensor<4x?xf32>
///     ```
/// 
///     If the `writable` unit attribute is set, the produced tensor is considered
///     "writable" during bufferization. Otherwise, every OpOperand that bufferizes
///     to a write to the future buffer of the resulting tensor (or an alias
///     thereof) will bufferize out-of-place to prevent emitting any writes to
///     `memref` during bufferization.
/// 
///     The `restrict` unit attribute (similar to the C `restrict` keyword)
///     indicates that the produced tensor result is the only way for the tensor
///     IR to gain access to the `memref` operand (or an alias thereof). E.g.,
///     there must be no other `to_tensor` op with the same or with an aliasing
///     `memref` operand.
/// 
///     Note: Only `to_tensor` ops with the `restrict` unit attribute are supported
///     by One-Shot Bufferize. Other IR is rejected. (To support `to_tensor`
///     without `restrict`, One-Shot Bufferize would have to analyze memref IR.)
///     Ops that have incorrect usage of `restrict` may bufferize incorrectly.
/// 
///     Example:
/// 
///     ```
///     %t = bufferization.to_tensor %m restrict writable : memref<4xf32> to tensor<4xf32>
/// 
///     // %t is writable, so the tensor.insert may bufferize in-place in the
///     // absence of other conflicts.
///     %r = tensor.insert %f into %t[%idx] : tensor<4xf32>
///     ```
/// 
///     `to_tensor` ops are not bufferized. They are expected to fold away after
///     bufferization. If there are non-bufferizable ops in the IR and
///     `allowUnknownOps` is set, they may be part of the resulting IR and not fold
///     away. However, such IR is no longer bufferizable with One-Shot Bufferize.
class ToTensorOp;

} // namespace mlir::bufferization
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::bufferization {


//===----------------------------------------------------------------------===//
// ::mlir::bufferization::AllocTensorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllocTensorOpGenericAdaptorBase {
public:
  struct Properties {
    using memory_spaceTy = ::mlir::Attribute;
    memory_spaceTy memory_space;

    auto getMemorySpace() const {
      auto &propStorage = this->memory_space;
      return ::llvm::dyn_cast_or_null<::mlir::Attribute>(propStorage);
    }
    void setMemorySpace(const ::mlir::Attribute &propValue) {
      this->memory_space = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 3>;
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
        rhs.memory_space == this->memory_space &&
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
  AllocTensorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("bufferization.alloc_tensor", odsAttrs.getContext());
  }

  AllocTensorOpGenericAdaptorBase(AllocTensorOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Attribute getMemorySpaceAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().memory_space);
    return attr;
  }

  ::std::optional<::mlir::Attribute> getMemorySpace();
};

} // namespace detail
template <typename RangeT>
class AllocTensorOpGenericAdaptor : public detail::AllocTensorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllocTensorOpGenericAdaptorBase;
  static constexpr int odsIndex_dynamic_sizes = 0;
  static constexpr int odsIndex_copy = 1;
  static constexpr int odsIndex_size_hint = 2;
public:
  AllocTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllocTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllocTensorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllocTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : AllocTensorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllocTensorOpGenericAdaptor(RangeT values, const AllocTensorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllocTensorOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllocTensorOp>>>
  AllocTensorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDynamicSizes() {
    return getODSOperands(0);
  }

  ValueT getCopy() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getSizeHint() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllocTensorOpAdaptor : public AllocTensorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllocTensorOpGenericAdaptor::AllocTensorOpGenericAdaptor;
  AllocTensorOpAdaptor(AllocTensorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllocTensorOp : public ::mlir::Op<AllocTensorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::bufferization::BufferizableOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllocTensorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllocTensorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dynamic_sizes = 0;
  static constexpr int odsIndex_copy = 1;
  static constexpr int odsIndex_size_hint = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<AllocTensorOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<AllocTensorOp>::reifyDimOfResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("memory_space"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMemorySpaceAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMemorySpaceAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("bufferization.alloc_tensor");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDynamicSizes() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::TensorType> getCopy() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::TensorType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getSizeHint() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IndexType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getDynamicSizesMutable();
  ::mlir::MutableOperandRange getCopyMutable();
  ::mlir::MutableOperandRange getSizeHintMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(0).begin());
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
  ::mlir::Attribute getMemorySpaceAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().memory_space);
  }

  ::std::optional<::mlir::Attribute> getMemorySpace();
  void setMemorySpaceAttr(::mlir::Attribute attr) {
    getProperties().memory_space = attr;
  }

  ::mlir::Attribute removeMemorySpaceAttr() {
      auto attr = getProperties().memory_space;
      getProperties().memory_space = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, RankedTensorType type, ValueRange dynamicSizes);
  static AllocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, RankedTensorType type, ValueRange dynamicSizes);
  static AllocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, RankedTensorType type, ValueRange dynamicSizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, RankedTensorType type, ValueRange dynamicSizes, Value copy);
  static AllocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, RankedTensorType type, ValueRange dynamicSizes, Value copy);
  static AllocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, RankedTensorType type, ValueRange dynamicSizes, Value copy);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TensorType type, ValueRange dynamicSizes, Value copy, IntegerAttr memory_space);
  static AllocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TensorType type, ValueRange dynamicSizes, Value copy, IntegerAttr memory_space);
  static AllocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, TensorType type, ValueRange dynamicSizes, Value copy, IntegerAttr memory_space);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange dynamic_sizes, /*optional*/::mlir::Value copy, /*optional*/::mlir::Value size_hint, /*optional*/::mlir::Attribute memory_space);
  static AllocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange dynamic_sizes, /*optional*/::mlir::Value copy, /*optional*/::mlir::Value size_hint, /*optional*/::mlir::Attribute memory_space);
  static AllocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange dynamic_sizes, /*optional*/::mlir::Value copy, /*optional*/::mlir::Value size_hint, /*optional*/::mlir::Attribute memory_space);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange dynamic_sizes, /*optional*/::mlir::Value copy, /*optional*/::mlir::Value size_hint, /*optional*/::mlir::Attribute memory_space);
  static AllocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange dynamic_sizes, /*optional*/::mlir::Value copy, /*optional*/::mlir::Value size_hint, /*optional*/::mlir::Attribute memory_space);
  static AllocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange dynamic_sizes, /*optional*/::mlir::Value copy, /*optional*/::mlir::Value size_hint, /*optional*/::mlir::Attribute memory_space);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  LogicalResult bufferize(RewriterBase &rewriter,
                          const BufferizationOptions &options,
                          BufferizationState &state);

  bool resultBufferizesToMemoryWrite(OpResult opResult,
                                     const AnalysisState &state);

  bool bufferizesToAllocation(Value value) { return true; }

  bool bufferizesToMemoryRead(OpOperand &opOperand,
                              const AnalysisState &state);

  bool bufferizesToMemoryWrite(OpOperand &opOperand,
                               const AnalysisState &state);

  AliasingValueList getAliasingValues(
      OpOperand &opOperand, const AnalysisState &state);

  FailureOr<BufferLikeType> getBufferType(
      Value value, const BufferizationOptions &options,
      const BufferizationState &state,
      SmallVector<Value> &invocationStack);

  RankedTensorType getType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }

  // Return true if the size of the tensor is dynamic at `idx`
  bool isDynamicDim(unsigned idx) {
    return getType().isDynamicDim(idx);
  }

  // Return the argument position that contains the dynamic size of
  // the tensor at dimension `idx`. Asserts that the shape is
  // dynamic at that `idx`.
  unsigned getIndexOfDynamicSize(unsigned idx) {
    assert(!getCopy() && "no dim sizes specified when copying a tensor");
    assert(isDynamicDim(idx) && "expected dynamic size");
    ArrayRef<int64_t> shape = getType().getShape();
    return std::count_if(shape.begin(), shape.begin() + idx,
                         ShapedType::isDynamic);
  }

  // Return the Value of the dynamic size of the tensor at dimension
  // `idx`. Asserts that the shape is dynamic at that `idx.
  Value getDynamicSize(OpBuilder &b, unsigned idx);

  // Assert that the size of the result tensor is static at `idx`
  // and return the shape.
  int64_t getStaticSize(unsigned idx) {
    assert(!isDynamicDim(idx) && "expected static size");
    return getType().getShape()[idx];
  }
};

} // namespace mlir::bufferization
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::bufferization::AllocTensorOp)

namespace mlir::bufferization {


//===----------------------------------------------------------------------===//
// ::mlir::bufferization::CloneOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CloneOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CloneOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("bufferization.clone", odsAttrs.getContext());
  }

  CloneOpGenericAdaptorBase(CloneOp op);

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
class CloneOpGenericAdaptor : public detail::CloneOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CloneOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  CloneOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CloneOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CloneOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CloneOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CloneOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CloneOpGenericAdaptor(RangeT values, const CloneOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CloneOp, typename = std::enable_if_t<std::is_same_v<LateInst, CloneOp>>>
  CloneOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CloneOpAdaptor : public CloneOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CloneOpGenericAdaptor::CloneOpGenericAdaptor;
  CloneOpAdaptor(CloneOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CloneOp : public ::mlir::Op<CloneOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::BaseMemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::bufferization::AllocationOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CloneOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CloneOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::bufferization::AllocationOpInterface::Trait<CloneOp>::getHoistingKind;
  using ::mlir::bufferization::AllocationOpInterface::Trait<CloneOp>::buildPromotedAlloc;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("bufferization.clone");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::BaseMemRefType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
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

  ::mlir::TypedValue<::mlir::BaseMemRefType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value);
  static CloneOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value);
  static CloneOp create(::mlir::ImplicitLocOpBuilder &builder, Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input);
  static CloneOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input);
  static CloneOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static CloneOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static CloneOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CloneOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CloneOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CloneOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CloneOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::std::optional<::mlir::Operation*> buildDealloc(::mlir::OpBuilder&builder, ::mlir::Value alloc);
  static ::std::optional<::mlir::Value> buildClone(::mlir::OpBuilder&builder, ::mlir::Value alloc);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  Value getSource() { return getInput(); }
  Value getTarget() { return getOutput(); }
};

} // namespace mlir::bufferization
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::bufferization::CloneOp)

namespace mlir::bufferization {


//===----------------------------------------------------------------------===//
// ::mlir::bufferization::DeallocOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeallocOpGenericAdaptorBase {
public:
  struct Properties {
    using operandSegmentSizesTy = std::array<int32_t, 3>;
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
  DeallocOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("bufferization.dealloc", odsAttrs.getContext());
  }

  DeallocOpGenericAdaptorBase(DeallocOp op);

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
class DeallocOpGenericAdaptor : public detail::DeallocOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeallocOpGenericAdaptorBase;
  static constexpr int odsIndex_memrefs = 0;
  static constexpr int odsIndex_conditions = 1;
  static constexpr int odsIndex_retained = 2;
public:
  DeallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeallocOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : DeallocOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeallocOpGenericAdaptor(RangeT values, const DeallocOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeallocOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeallocOp>>>
  DeallocOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getMemrefs() {
    return getODSOperands(0);
  }

  RangeT getConditions() {
    return getODSOperands(1);
  }

  RangeT getRetained() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DeallocOpAdaptor : public DeallocOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeallocOpGenericAdaptor::DeallocOpGenericAdaptor;
  DeallocOpAdaptor(DeallocOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeallocOp : public ::mlir::Op<DeallocOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeallocOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeallocOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memrefs = 0;
  static constexpr int odsIndex_conditions = 1;
  static constexpr int odsIndex_retained = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<DeallocOp>::refineReturnTypes;
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
    return ::llvm::StringLiteral("bufferization.dealloc");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getMemrefs() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getConditions() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getRetained() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getMemrefsMutable();
  ::mlir::MutableOperandRange getConditionsMutable();
  ::mlir::MutableOperandRange getRetainedMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getUpdatedConditions() {
    return getODSResults(0);
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange updatedConditions, ::mlir::ValueRange memrefs, ::mlir::ValueRange conditions, ::mlir::ValueRange retained);
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange updatedConditions, ::mlir::ValueRange memrefs, ::mlir::ValueRange conditions, ::mlir::ValueRange retained);
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange updatedConditions, ::mlir::ValueRange memrefs, ::mlir::ValueRange conditions, ::mlir::ValueRange retained);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange memrefs, ::mlir::ValueRange conditions, ::mlir::ValueRange retained);
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange memrefs, ::mlir::ValueRange conditions, ::mlir::ValueRange retained);
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange memrefs, ::mlir::ValueRange conditions, ::mlir::ValueRange retained);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    return {};
  }

public:
};

} // namespace mlir::bufferization
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::bufferization::DeallocOp)

namespace mlir::bufferization {


//===----------------------------------------------------------------------===//
// ::mlir::bufferization::DeallocTensorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeallocTensorOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DeallocTensorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("bufferization.dealloc_tensor", odsAttrs.getContext());
  }

  DeallocTensorOpGenericAdaptorBase(DeallocTensorOp op);

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
class DeallocTensorOpGenericAdaptor : public detail::DeallocTensorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeallocTensorOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  DeallocTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeallocTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeallocTensorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeallocTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DeallocTensorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeallocTensorOpGenericAdaptor(RangeT values, const DeallocTensorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeallocTensorOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeallocTensorOp>>>
  DeallocTensorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DeallocTensorOpAdaptor : public DeallocTensorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeallocTensorOpGenericAdaptor::DeallocTensorOpGenericAdaptor;
  DeallocTensorOpAdaptor(DeallocTensorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeallocTensorOp : public ::mlir::Op<DeallocTensorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::bufferization::BufferizableOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeallocTensorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeallocTensorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("bufferization.dealloc_tensor");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTensorMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor);
  static DeallocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor);
  static DeallocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static DeallocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static DeallocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeallocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeallocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeallocTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeallocTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  bool bufferizesToMemoryRead(OpOperand &opOperand,
                              const AnalysisState &state) const {
    return false;
  }

  bool bufferizesToMemoryWrite(OpOperand &opOperand,
                               const AnalysisState &state) const {
    return false;
  }

  AliasingValueList getAliasingValues(
      OpOperand &opOperand, const AnalysisState &state) const {
    return {};
  }

  LogicalResult bufferize(RewriterBase &rewriter,
                          const BufferizationOptions &options,
                          BufferizationState &state);
};

} // namespace mlir::bufferization
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::bufferization::DeallocTensorOp)

namespace mlir::bufferization {


//===----------------------------------------------------------------------===//
// ::mlir::bufferization::MaterializeInDestinationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MaterializeInDestinationOpGenericAdaptorBase {
public:
  struct Properties {
    using restrictTy = ::mlir::UnitAttr;
    restrictTy restrict;

    auto getRestrict() const {
      auto &propStorage = this->restrict;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setRestrict(const ::mlir::UnitAttr &propValue) {
      this->restrict = propValue;
    }
    using writableTy = ::mlir::UnitAttr;
    writableTy writable;

    auto getWritable() const {
      auto &propStorage = this->writable;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setWritable(const ::mlir::UnitAttr &propValue) {
      this->writable = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.restrict == this->restrict &&
        rhs.writable == this->writable &&
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
  MaterializeInDestinationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("bufferization.materialize_in_destination", odsAttrs.getContext());
  }

  MaterializeInDestinationOpGenericAdaptorBase(MaterializeInDestinationOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getRestrictAttr();
  bool getRestrict();
  ::mlir::UnitAttr getWritableAttr();
  bool getWritable();
};

} // namespace detail
template <typename RangeT>
class MaterializeInDestinationOpGenericAdaptor : public detail::MaterializeInDestinationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MaterializeInDestinationOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
public:
  MaterializeInDestinationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MaterializeInDestinationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MaterializeInDestinationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MaterializeInDestinationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MaterializeInDestinationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MaterializeInDestinationOpGenericAdaptor(RangeT values, const MaterializeInDestinationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MaterializeInDestinationOp, typename = std::enable_if_t<std::is_same_v<LateInst, MaterializeInDestinationOp>>>
  MaterializeInDestinationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDest() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MaterializeInDestinationOpAdaptor : public MaterializeInDestinationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MaterializeInDestinationOpGenericAdaptor::MaterializeInDestinationOpGenericAdaptor;
  MaterializeInDestinationOpAdaptor(MaterializeInDestinationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MaterializeInDestinationOp : public ::mlir::Op<MaterializeInDestinationOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::bufferization::BufferizableOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait, ::mlir::SubsetOpInterface::Trait, ::mlir::SubsetInsertionOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MaterializeInDestinationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MaterializeInDestinationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<MaterializeInDestinationOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<MaterializeInDestinationOp>::reifyDimOfResult;
  using ::mlir::SubsetOpInterface::Trait<MaterializeInDestinationOp>::getAccessedHyperrectangularSlice;
  using ::mlir::SubsetInsertionOpInterface::Trait<MaterializeInDestinationOp>::getDestinationOperand;
  using ::mlir::SubsetInsertionOpInterface::Trait<MaterializeInDestinationOp>::getUpdatedDestination;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("restrict"), ::llvm::StringRef("writable")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getRestrictAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getRestrictAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getWritableAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getWritableAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("bufferization.materialize_in_destination");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getResult() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::TensorType>() : ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*results.begin());
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
  ::mlir::UnitAttr getRestrictAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().restrict);
  }

  bool getRestrict();
  ::mlir::UnitAttr getWritableAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().writable);
  }

  bool getWritable();
  void setRestrictAttr(::mlir::UnitAttr attr) {
    getProperties().restrict = attr;
  }

  void setRestrict(bool attrValue);
  void setWritableAttr(::mlir::UnitAttr attr) {
    getProperties().writable = attr;
  }

  void setWritable(bool attrValue);
  ::mlir::Attribute removeRestrictAttr() {
      auto attr = getProperties().restrict;
      getProperties().restrict = {};
      return attr;
  }

  ::mlir::Attribute removeWritableAttr() {
      auto attr = getProperties().writable;
      getProperties().writable = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value dest);
  static MaterializeInDestinationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest);
  static MaterializeInDestinationOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static MaterializeInDestinationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static MaterializeInDestinationOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static MaterializeInDestinationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static MaterializeInDestinationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static MaterializeInDestinationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static MaterializeInDestinationOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static MaterializeInDestinationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static MaterializeInDestinationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaterializeInDestinationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaterializeInDestinationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaterializeInDestinationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaterializeInDestinationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  bool operatesOnEquivalentSubset(::mlir::SubsetOpInterface candidate, ::llvm::function_ref<bool(Value, Value)> equivalenceFn);
  bool operatesOnDisjointSubset(::mlir::SubsetOpInterface candidate, ::llvm::function_ref<bool(Value, Value)> equivalenceFn);
  ::mlir::OpOperand &getSourceOperand();
  bool isEquivalentSubset(::mlir::Value candidate, ::llvm::function_ref<bool(Value, Value)> equivalenceFn);
  ::mlir::Value buildSubsetExtraction(::mlir::OpBuilder &builder, Location loc);
  ::llvm::SmallVector<::mlir::Value> getValuesNeededToBuildSubsetExtraction();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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
  LogicalResult bufferize(RewriterBase &rewriter,
                          const BufferizationOptions &options,
                          BufferizationState &state);

  bool bufferizesToMemoryRead(OpOperand &opOperand,
                              const AnalysisState &state);

  bool bufferizesToMemoryWrite(OpOperand &opOperand,
                               const AnalysisState &state);

  bool bufferizesToElementwiseAccess(const AnalysisState &state,
                                     ArrayRef<OpOperand *> opOperands);

  bool mustBufferizeInPlace(OpOperand &opOperand,
                            const AnalysisState &state);

  AliasingValueList getAliasingValues(
      OpOperand &opOperand, const AnalysisState &state);

  RankedTensorType getType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }

  MutableOperandRange getDpsInitsMutable();

  bool isWritable(Value value, const AnalysisState &state);
};

} // namespace mlir::bufferization
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::bufferization::MaterializeInDestinationOp)

namespace mlir::bufferization {


//===----------------------------------------------------------------------===//
// ::mlir::bufferization::ToBufferOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToBufferOpGenericAdaptorBase {
public:
  struct Properties {
    using read_onlyTy = ::mlir::UnitAttr;
    read_onlyTy read_only;

    auto getReadOnly() const {
      auto &propStorage = this->read_only;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setReadOnly(const ::mlir::UnitAttr &propValue) {
      this->read_only = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.read_only == this->read_only &&
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
  ToBufferOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("bufferization.to_buffer", odsAttrs.getContext());
  }

  ToBufferOpGenericAdaptorBase(ToBufferOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getReadOnlyAttr();
  bool getReadOnly();
};

} // namespace detail
template <typename RangeT>
class ToBufferOpGenericAdaptor : public detail::ToBufferOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToBufferOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  ToBufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToBufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ToBufferOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToBufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToBufferOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToBufferOpGenericAdaptor(RangeT values, const ToBufferOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToBufferOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToBufferOp>>>
  ToBufferOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ToBufferOpAdaptor : public ToBufferOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToBufferOpGenericAdaptor::ToBufferOpGenericAdaptor;
  ToBufferOpAdaptor(ToBufferOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToBufferOp : public ::mlir::Op<ToBufferOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::bufferization::BufferLikeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::bufferization::BufferizableOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultShape, ::mlir::OpTrait::SameOperandsAndResultElementType, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToBufferOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToBufferOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("read_only")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getReadOnlyAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getReadOnlyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("bufferization.to_buffer");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::bufferization::TensorLikeType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::bufferization::TensorLikeType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTensorMutable() {
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

  ::mlir::TypedValue<::mlir::bufferization::BufferLikeType> getBuffer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::bufferization::BufferLikeType>>(*getODSResults(0).begin());
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
  ::mlir::UnitAttr getReadOnlyAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().read_only);
  }

  bool getReadOnly();
  void setReadOnlyAttr(::mlir::UnitAttr attr) {
    getProperties().read_only = attr;
  }

  void setReadOnly(bool attrValue);
  ::mlir::Attribute removeReadOnlyAttr() {
      auto attr = getProperties().read_only;
      getProperties().read_only = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type buffer, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr read_only);
  static ToBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type buffer, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr read_only);
  static ToBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type buffer, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr read_only);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr read_only);
  static ToBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr read_only);
  static ToBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr read_only);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type buffer, ::mlir::Value tensor, /*optional*/bool read_only = false);
  static ToBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type buffer, ::mlir::Value tensor, /*optional*/bool read_only = false);
  static ToBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type buffer, ::mlir::Value tensor, /*optional*/bool read_only = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/bool read_only = false);
  static ToBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/bool read_only = false);
  static ToBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/bool read_only = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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
  //===------------------------------------------------------------------===//
  // BufferizableOpInterface implementation
  //===------------------------------------------------------------------===//

  // Note: ToBufferOp / ToTensorOp are temporary ops that are inserted at the
  // bufferization boundary. When One-Shot bufferization is complete, there
  // should be no such ops left over. If `allowUnknownOps` (or after running a
  // partial bufferization pass), such ops may be part of the resulting IR,
  // but such IR may no longer be analyzable by One-Shot analysis.

  bool bufferizesToMemoryRead(OpOperand &opOperand,
                              const AnalysisState &state) const {
    // It is unknown whether the resulting memref will be read or not.
    return true;
  }

  bool bufferizesToMemoryWrite(OpOperand &opOperand,
                               const AnalysisState &state) {
    return !getReadOnly();
  }

  AliasingValueList getAliasingValues(
      OpOperand &opOperand, const AnalysisState &state) const {
    return {};
  }

  LogicalResult bufferize(RewriterBase &rewriter,
                          const BufferizationOptions &options,
                          BufferizationState &state);
};

} // namespace mlir::bufferization
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::bufferization::ToBufferOp)

namespace mlir::bufferization {


//===----------------------------------------------------------------------===//
// ::mlir::bufferization::ToTensorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToTensorOpGenericAdaptorBase {
public:
  struct Properties {
    using restrictTy = ::mlir::UnitAttr;
    restrictTy restrict;

    auto getRestrict() const {
      auto &propStorage = this->restrict;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setRestrict(const ::mlir::UnitAttr &propValue) {
      this->restrict = propValue;
    }
    using writableTy = ::mlir::UnitAttr;
    writableTy writable;

    auto getWritable() const {
      auto &propStorage = this->writable;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setWritable(const ::mlir::UnitAttr &propValue) {
      this->writable = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.restrict == this->restrict &&
        rhs.writable == this->writable &&
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
  ToTensorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("bufferization.to_tensor", odsAttrs.getContext());
  }

  ToTensorOpGenericAdaptorBase(ToTensorOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getRestrictAttr();
  bool getRestrict();
  ::mlir::UnitAttr getWritableAttr();
  bool getWritable();
};

} // namespace detail
template <typename RangeT>
class ToTensorOpGenericAdaptor : public detail::ToTensorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToTensorOpGenericAdaptorBase;
  static constexpr int odsIndex_buffer = 0;
public:
  ToTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ToTensorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToTensorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToTensorOpGenericAdaptor(RangeT values, const ToTensorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToTensorOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToTensorOp>>>
  ToTensorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBuffer() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ToTensorOpAdaptor : public ToTensorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToTensorOpGenericAdaptor::ToTensorOpGenericAdaptor;
  ToTensorOpAdaptor(ToTensorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToTensorOp : public ::mlir::Op<ToTensorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::bufferization::TensorLikeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::bufferization::BufferizableOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultShape, ::mlir::OpTrait::SameOperandsAndResultElementType, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToTensorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToTensorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_buffer = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("restrict"), ::llvm::StringRef("writable")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getRestrictAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getRestrictAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getWritableAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getWritableAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("bufferization.to_tensor");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::bufferization::BufferLikeType> getBuffer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::bufferization::BufferLikeType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getBufferMutable() {
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

  ::mlir::TypedValue<::mlir::bufferization::TensorLikeType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::bufferization::TensorLikeType>>(*getODSResults(0).begin());
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
  ::mlir::UnitAttr getRestrictAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().restrict);
  }

  bool getRestrict();
  ::mlir::UnitAttr getWritableAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().writable);
  }

  bool getWritable();
  void setRestrictAttr(::mlir::UnitAttr attr) {
    getProperties().restrict = attr;
  }

  void setRestrict(bool attrValue);
  void setWritableAttr(::mlir::UnitAttr attr) {
    getProperties().writable = attr;
  }

  void setWritable(bool attrValue);
  ::mlir::Attribute removeRestrictAttr() {
      auto attr = getProperties().restrict;
      getProperties().restrict = {};
      return attr;
  }

  ::mlir::Attribute removeWritableAttr() {
      auto attr = getProperties().writable;
      getProperties().writable = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value buffer, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static ToTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value buffer, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static ToTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value buffer, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value buffer, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static ToTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value buffer, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static ToTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value buffer, /*optional*/::mlir::UnitAttr restrict, /*optional*/::mlir::UnitAttr writable = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value buffer, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static ToTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value buffer, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static ToTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value buffer, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value buffer, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static ToTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value buffer, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static ToTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value buffer, /*optional*/bool restrict = false, /*optional*/bool writable = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
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
  /// The result of a to_tensor is always a tensor.
  ::mlir::bufferization::TensorLikeType getType() {
    return getResult().getType();
  }

  //===------------------------------------------------------------------===//
  // BufferizableOpInterface implementation
  //===------------------------------------------------------------------===//

  LogicalResult bufferize(RewriterBase &rewriter,
                          const BufferizationOptions &options,
                          BufferizationState &state) const {
    // to_tensor/to_buffer pairs fold away after bufferization.
    return success();
  }

  bool isWritable(Value value, const AnalysisState &state);

  FailureOr<BufferLikeType> getBufferType(
      Value value, const BufferizationOptions &options,
      const BufferizationState &state, SmallVector<Value> &invocationStack) {
    return getBuffer().getType();
  }
};

} // namespace mlir::bufferization
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::bufferization::ToTensorOp)


#endif // GET_OP_CLASSES

