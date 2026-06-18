/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: PtrOps.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::ptr {

/// Pointer constant operation
/// The `constant` operation produces a pointer constant. The attribute must be
///     a typed attribute of pointer type.
/// 
///     Example:
/// 
///     ```mlir
///     // Create a null pointer
///     %null = ptr.constant #ptr.null : !ptr.ptr<#ptr.generic_space>
///     ```
class ConstantOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// Casts a `!ptr.ptr` value to a ptr-like value.
/// The `from_ptr` operation casts a `ptr` value to a ptr-like object. It's
///     important to note that:
///     - The ptr-like object cannot be a `!ptr.ptr`.
///     - The memory-space of both the `ptr` and ptr-like object must match.
///     - The cast is Pure (no UB and side-effect free).
/// 
///     The optional `metadata` operand exists to provide any ptr-like metadata
///     that might be required to perform the cast.
/// 
///     Example:
/// 
///     ```mlir
///     %typed_ptr = ptr.from_ptr %ptr : !ptr.ptr<#ptr.generic_space> -> !my.ptr<f32, #ptr.generic_space>
///     %memref = ptr.from_ptr %ptr metadata %md : !ptr.ptr<#ptr.generic_space> -> memref<f32, #ptr.generic_space>
/// 
///     // Cast the `%ptr` to a memref without utilizing metadata.
///     %memref = ptr.from_ptr %ptr : !ptr.ptr<#ptr.generic_space> -> memref<f32, #ptr.generic_space>
///     ```
class FromPtrOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// Gather operation
/// The `gather` operation performs conditional loads from multiple memory
///     locations specified by `ptrs` based on a mask `mask`. Elements of the
///     result corresponding to masked-off lanes are taken from the passthrough
///     operand.
/// 
///     The mask operand is a shaped type of `i1` elements that must have the same
///     shape as the result type.
/// 
///     Examples:
///     ```mlir
///     // Gather values from multiple memory locations
///     %result = ptr.gather %ptrs, %mask, %passthrough :
///       vector<4x!ptr.ptr<#ptr.generic_space>> -> vector<4xf32>
/// 
///     // Gather with alignment
///     %result = ptr.gather %ptrs, %mask, %passthrough alignment = 8 :
///       vector<4x!ptr.ptr<#ptr.generic_space>> -> vector<4xf32>
///     ```
class GatherOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// SSA value representing pointer metadata.
/// The `get_metadata` operation produces an opaque value that encodes the
///     metadata of the ptr-like type.
/// 
///     Example:
/// 
///     ```mlir
///     %metadata = ptr.get_metadata %memref : memref<?x?xf32>
///     ```
class GetMetadataOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// The `load` operation is used to read from memory. A load may be marked as
///     atomic, volatile, and/or nontemporal.
/// 
///     An atomic load only supports a limited set of value types, and requires
///     an explicit alignment.
/// 
///     Examples:
///     ```mlir
///     // A volatile load of a float variable.
///     %0 = ptr.load volatile %ptr : !ptr.ptr -> f32
/// 
///     // A nontemporal load of a float variable.
///     %0 = ptr.load %ptr nontemporal : !ptr.ptr -> f32
/// 
///     // An atomic load of an integer variable.
///     %0 = ptr.load %ptr atomic monotonic alignment = 8 : !ptr.ptr -> i64
///     ```
/// 
///     See the following link for more details on the meaning of `alignment`,
///     `volatile_`, `nontemporal`, `invariant`, `invariant_group`, `ordering`,
///     and `syncscope`:
///     https://llvm.org/docs/LangRef.html#load-instruction
class LoadOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// Masked load operation
/// The `masked_load` operation performs a conditional load from memory based
///     on  a mask. Elements of the result corresponding to masked-off lanes are
///     taken from the passthrough operand.
/// 
///     The mask operand is a shaped type of `i1` elements that must have the same
///     shape as the result type.
/// 
///     Examples:
///     ```mlir
///     // Masked load with passthrough on vectors
///     %result = ptr.masked_load %ptr, %mask, %passthrough :
///       !ptr.ptr<#ptr.generic_space> -> vector<4xf32>
/// 
///     // Masked load with passthrough on tensors
///     %result = ptr.masked_load %ptr, %mask, %passthrough :
///       !ptr.ptr<#ptr.generic_space> -> tensor<4xf32>
///     ```
class MaskedLoadOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// Masked store operation
/// The `masked_store` operation performs a conditional store to memory based
///     on  a mask. Only elements corresponding to set bits in the mask are written
///     to memory.
/// 
///     The mask operand is a shaped type of `i1` elements that must have the same
///     shape as the value being stored.
/// 
///     Examples:
///     ```mlir
///     // Masked store
///     ptr.masked_store %value, %ptr, %mask :
///       vector<4xf32>, !ptr.ptr<#ptr.generic_space>
/// 
///     // Masked store with alignment
///     ptr.masked_store %value, %ptr, %mask alignment = 8 :
///       vector<4xf32>, !ptr.ptr<#ptr.generic_space>
///     ```
class MaskedStoreOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// Pointer add operation
/// The `ptr_add` operation adds an int-like offset to one or more pointers to produce one or more new pointers.
/// 
///     The operation supports both scalar and shaped types with value semantics:
///     - When both base and offset are scalar: produces a single new pointer
///     - When base is shaped and offset is scalar: adds the same offset to each
///     pointer in the base
///     - When base is scalar and offset is shaped: adds the single pointer to each
///     offset in the shaped value
///     - When both are shaped: performs element-wise addition (shapes must be
///     compatible)
/// 
///     Example:
/// 
///     ```mlir
///     // Scalar base and offset
///     %x_off  = ptr.ptr_add %x, %off : !ptr.ptr<#ptr.generic_space>, i32
///     %x_off0 = ptr.ptr_add nusw %x, %off : !ptr.ptr<#ptr.generic_space>, i32
/// 
///     // Shaped base with scalar offset
///     %ptrs_off = ptr.ptr_add %ptrs, %off : vector<4x!ptr.ptr<#ptr.generic_space>>, i32
/// 
///     // Scalar base with shaped offset
///     %x_offs = ptr.ptr_add %x, %offs : !ptr.ptr<#ptr.generic_space>, vector<4xi32>
/// 
///     // Both base and offset are shaped
///     %ptrs_offs = ptr.ptr_add %ptrs, %offs : vector<4x!ptr.ptr<#ptr.generic_space>>, vector<4xi32>
///     ```
class PtrAddOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// Pointer difference operation
/// The `ptr_diff` operation computes the difference between two pointers,
///     returning an integer or index value representing the number of bytes
///     between them.
/// 
///     The operation supports both scalar and shaped types with value semantics:
///     - When both operands are scalar: produces a single difference value
///     - When both are shaped: performs element-wise subtraction,
///       shapes must be the same
/// 
///     The operation also supports the following flags:
///     - `none`: No flags are set.
///     - `nuw`: No Unsigned Wrap, if the subtraction causes an unsigned overflow
///       (that is: the result would be negative), the result is a poison value.
///     - `nsw`: No Signed Wrap, if the subtraction causes a signed overflow, the
///       result is a poison value.
/// 
///     NOTE: The pointer difference is calculated using an integer type specified
///     by the data layout. The final result will be sign-extended or truncated to
///     fit the result type as necessary.
/// 
///     Example:
/// 
///     ```mlir
///     // Scalar pointers
///     %diff = ptr.ptr_diff %p1, %p2 : !ptr.ptr<#ptr.generic_space> -> i64
/// 
///     // Shaped pointers
///     %diffs = ptr.ptr_diff nsw %ptrs1, %ptrs2 :
///       vector<4x!ptr.ptr<#ptr.generic_space>> -> vector<4xi64>
///     ```
class PtrDiffOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// Scatter operation
/// The `scatter` operation performs a conditional store of a value `value` to
///     multiple memory locations specified by `ptrs` based on a mask `mask`.
/// 
///     Only elements corresponding to set bits in the mask are written to memory.
///     The mask operand is a shaped type of `i1` elements that must have the same
///     shape as the value being stored.
/// 
///     Examples:
///     ```mlir
///     // Scatter values to multiple memory locations
///     ptr.scatter %value, %ptrs, %mask :
///       vector<4xf32>, vector<4x!ptr.ptr<#ptr.generic_space>>
/// 
///     // Scatter with alignment
///     ptr.scatter %value, %ptrs, %mask alignment = 8 :
///       vector<4xf32>, vector<4x!ptr.ptr<#ptr.generic_space>>
///     ```
class ScatterOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// The `store` operation is used to write to memory. A store may be marked as
///     atomic, volatile, and/or nontemporal.
/// 
///     An atomic store only supports a limited set of value types, and requires
///     an explicit alignment.
/// 
///     Examples:
///     ```mlir
///     // A volatile store of a float variable.
///     ptr.store volatile %val, %ptr : f32, !ptr.ptr
/// 
///     // A nontemporal store of a float variable.
///     ptr.store %val, %ptr nontemporal : f32, !ptr.ptr
/// 
///     // An atomic store of an integer variable.
///     ptr.store %val, %ptr atomic monotonic alignment = 8: i64, !ptr.ptr
///     ```
/// 
///     See the following link for more details on the meaning of `alignment`,
///     `volatile_`, `nontemporal`, `invariant_group`, `ordering`, and `syncscope`:
///     https://llvm.org/docs/LangRef.html#store-instruction
class StoreOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// Casts a ptr-like value to a `!ptr.ptr` value.
/// The `to_ptr` operation casts a ptr-like object to a `!ptr.ptr`. It's
///     important to note that:
///     - The ptr-like object cannot be a `!ptr.ptr`.
///     - The memory-space of both the `ptr` and ptr-like object must match.
///     - The cast is side-effect free.
/// 
///     Example:
/// 
///     ```mlir
///     %ptr0 = ptr.to_ptr %my_ptr : !my.ptr<f32, #ptr.generic_space> -> !ptr.ptr<#ptr.generic_space>
///     %ptr1 = ptr.to_ptr %memref : memref<f32, #ptr.generic_space> -> !ptr.ptr<#ptr.generic_space>
///     ```
class ToPtrOp;

} // namespace mlir::ptr
namespace mlir::ptr {

/// Type offset operation
/// The `type_offset` operation produces an int or index-typed SSA value
///     equal to a target-specific constant representing the offset of a single
///     element of the given type.
/// 
///     Example:
/// 
///     ```mlir
///     // Return the offset between two f32 stored in memory
///     %0 = ptr.type_offset f32 : index
///     // Return the offset between two memref descriptors stored in memory
///     %1 = ptr.type_offset memref<12 x f64> : i32
///     ```
class TypeOffsetOp;

} // namespace mlir::ptr
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::ConstantOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConstantOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::mlir::TypedAttr;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::TypedAttr>(propStorage);
    }
    void setValue(const ::mlir::TypedAttr &propValue) {
      this->value = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.value == this->value &&
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
  ConstantOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.constant", odsAttrs.getContext());
  }

  ConstantOpGenericAdaptorBase(ConstantOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypedAttr getValueAttr() {
    auto attr = ::llvm::cast<::mlir::TypedAttr>(getProperties().value);
    return attr;
  }

  ::mlir::TypedAttr getValue();
};

} // namespace detail
template <typename RangeT>
class ConstantOpGenericAdaptor : public detail::ConstantOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConstantOpGenericAdaptorBase;
public:
  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ConstantOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConstantOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConstantOpGenericAdaptor(RangeT values, const ConstantOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConstantOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConstantOp>>>
  ConstantOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ConstantOpAdaptor : public ConstantOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConstantOpGenericAdaptor::ConstantOpGenericAdaptor;
  ConstantOpAdaptor(ConstantOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConstantOp : public ::mlir::Op<ConstantOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ptr::PtrType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::ConstantLike, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConstantOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConstantOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("value")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getValueAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getValueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.constant");
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

  ::mlir::TypedValue<::mlir::ptr::PtrType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ptr::PtrType>>(*getODSResults(0).begin());
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
  ::mlir::TypedAttr getValueAttr() {
    return ::llvm::cast<::mlir::TypedAttr>(getProperties().value);
  }

  ::mlir::TypedAttr getValue();
  void setValueAttr(::mlir::TypedAttr attr) {
    getProperties().value = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::TypedAttr value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::TypedAttr value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::TypedAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypedAttr value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypedAttr value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypedAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::TypedAttr value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::TypedAttr value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::TypedAttr value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::ConstantOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::FromPtrOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FromPtrOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FromPtrOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.from_ptr", odsAttrs.getContext());
  }

  FromPtrOpGenericAdaptorBase(FromPtrOp op);

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
class FromPtrOpGenericAdaptor : public detail::FromPtrOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FromPtrOpGenericAdaptorBase;
  static constexpr int odsIndex_ptr = 0;
  static constexpr int odsIndex_metadata = 1;
public:
  FromPtrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FromPtrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : FromPtrOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FromPtrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FromPtrOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FromPtrOpGenericAdaptor(RangeT values, const FromPtrOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FromPtrOp, typename = std::enable_if_t<std::is_same_v<LateInst, FromPtrOp>>>
  FromPtrOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPtr() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMetadata() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FromPtrOpAdaptor : public FromPtrOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FromPtrOpGenericAdaptor::FromPtrOpGenericAdaptor;
  FromPtrOpAdaptor(FromPtrOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FromPtrOp : public ::mlir::Op<FromPtrOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::PtrLikeTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FromPtrOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FromPtrOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_ptr = 0;
  static constexpr int odsIndex_metadata = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.from_ptr");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ptr::PtrType> getPtr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ptr::PtrType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ptr::PtrMetadataType> getMetadata() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::ptr::PtrMetadataType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::ptr::PtrMetadataType>>(*operands.begin());
  }

  ::mlir::OpOperand &getPtrMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getMetadataMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::PtrLikeTypeInterface>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value ptr, /*optional*/::mlir::Value metadata);
  static FromPtrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value ptr, /*optional*/::mlir::Value metadata);
  static FromPtrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value ptr, /*optional*/::mlir::Value metadata);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/::mlir::Value metadata);
  static FromPtrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/::mlir::Value metadata);
  static FromPtrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/::mlir::Value metadata);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FromPtrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FromPtrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FromPtrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FromPtrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::FromPtrOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::GatherOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GatherOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = std::optional<int64_t>;
    alignmentTy alignment = std::nullopt;
    std::optional<int64_t> getAlignment() const {
      auto &propStorage = this->alignment;
      return propStorage;
    }
    void setAlignment(std::optional<int64_t> propValue) {
      auto &propStorage = this->alignment;
      propStorage = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
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
  GatherOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.gather", odsAttrs.getContext());
  }

  GatherOpGenericAdaptorBase(GatherOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

};

} // namespace detail
template <typename RangeT>
class GatherOpGenericAdaptor : public detail::GatherOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GatherOpGenericAdaptorBase;
  static constexpr int odsIndex_ptrs = 0;
  static constexpr int odsIndex_mask = 1;
  static constexpr int odsIndex_passthrough = 2;
public:
  GatherOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GatherOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GatherOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GatherOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GatherOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GatherOpGenericAdaptor(RangeT values, const GatherOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GatherOp, typename = std::enable_if_t<std::is_same_v<LateInst, GatherOp>>>
  GatherOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPtrs() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMask() {
    return (*getODSOperands(1).begin());
  }

  ValueT getPassthrough() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GatherOpAdaptor : public GatherOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GatherOpGenericAdaptor::GatherOpGenericAdaptor;
  GatherOpAdaptor(GatherOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GatherOp : public ::mlir::Op<GatherOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GatherOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GatherOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_ptrs = 0;
  static constexpr int odsIndex_mask = 1;
  static constexpr int odsIndex_passthrough = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.gather");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getPtrs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getPassthrough() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getPtrsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMaskMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPassthroughMutable() {
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

  void setAlignment(std::optional<int64_t> newAlignment) {
    getProperties().setAlignment(newAlignment);
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value ptrs, Value mask, Value passthrough, unsigned alignment = 0);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value ptrs, Value mask, Value passthrough, unsigned alignment = 0);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value ptrs, Value mask, Value passthrough, unsigned alignment = 0);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptrs, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::GatherOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::GetMetadataOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetMetadataOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GetMetadataOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.get_metadata", odsAttrs.getContext());
  }

  GetMetadataOpGenericAdaptorBase(GetMetadataOp op);

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
class GetMetadataOpGenericAdaptor : public detail::GetMetadataOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetMetadataOpGenericAdaptorBase;
  static constexpr int odsIndex_ptr = 0;
public:
  GetMetadataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetMetadataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetMetadataOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetMetadataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetMetadataOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetMetadataOpGenericAdaptor(RangeT values, const GetMetadataOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetMetadataOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetMetadataOp>>>
  GetMetadataOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPtr() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetMetadataOpAdaptor : public GetMetadataOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetMetadataOpGenericAdaptor::GetMetadataOpGenericAdaptor;
  GetMetadataOpAdaptor(GetMetadataOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetMetadataOp : public ::mlir::Op<GetMetadataOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ptr::PtrMetadataType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetMetadataOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetMetadataOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_ptr = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.get_metadata");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> getPtr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::PtrLikeTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getPtrMutable() {
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

  ::mlir::TypedValue<::mlir::ptr::PtrMetadataType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ptr::PtrMetadataType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value ptr);
  static GetMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value ptr);
  static GetMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value ptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value ptr);
  static GetMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value ptr);
  static GetMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value ptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptr);
  static GetMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptr);
  static GetMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptr);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::GetMetadataOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::LoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoadOpGenericAdaptorBase {
public:
  struct Properties {
    using syncscopeTy = ::mlir::StringAttr;
    syncscopeTy syncscope;

    auto getSyncscope() const {
      auto &propStorage = this->syncscope;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSyncscope(const ::mlir::StringAttr &propValue) {
      this->syncscope = propValue;
    }
    using alignmentTy = std::optional<int64_t>;
    alignmentTy alignment = std::nullopt;
    std::optional<int64_t> getAlignment() const {
      auto &propStorage = this->alignment;
      return propStorage;
    }
    void setAlignment(std::optional<int64_t> propValue) {
      auto &propStorage = this->alignment;
      propStorage = propValue;
    }
    using volatile_Ty = bool;
    volatile_Ty volatile_ = false;
    bool getVolatile_() const {
      auto &propStorage = this->volatile_;
      return propStorage;
    }
    void setVolatile_(bool propValue) {
      auto &propStorage = this->volatile_;
      propStorage = propValue;
    }
    using nontemporalTy = bool;
    nontemporalTy nontemporal = false;
    bool getNontemporal() const {
      auto &propStorage = this->nontemporal;
      return propStorage;
    }
    void setNontemporal(bool propValue) {
      auto &propStorage = this->nontemporal;
      propStorage = propValue;
    }
    using invariantTy = bool;
    invariantTy invariant = false;
    bool getInvariant() const {
      auto &propStorage = this->invariant;
      return propStorage;
    }
    void setInvariant(bool propValue) {
      auto &propStorage = this->invariant;
      propStorage = propValue;
    }
    using invariantGroupTy = bool;
    invariantGroupTy invariantGroup = false;
    bool getInvariantGroup() const {
      auto &propStorage = this->invariantGroup;
      return propStorage;
    }
    void setInvariantGroup(bool propValue) {
      auto &propStorage = this->invariantGroup;
      propStorage = propValue;
    }
    using orderingTy = ::mlir::ptr::AtomicOrdering;
    orderingTy ordering = AtomicOrdering::not_atomic;
    ::mlir::ptr::AtomicOrdering getOrdering() const {
      auto &propStorage = this->ordering;
      return propStorage;
    }
    void setOrdering(::mlir::ptr::AtomicOrdering propValue) {
      auto &propStorage = this->ordering;
      propStorage = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.syncscope == this->syncscope &&
        rhs.alignment == this->alignment &&
        rhs.volatile_ == this->volatile_ &&
        rhs.nontemporal == this->nontemporal &&
        rhs.invariant == this->invariant &&
        rhs.invariantGroup == this->invariantGroup &&
        rhs.ordering == this->ordering &&
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
  LoadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.load", odsAttrs.getContext());
  }

  LoadOpGenericAdaptorBase(LoadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

  bool getVolatile_() {
    return getProperties().getVolatile_();
  }

  bool getNontemporal() {
    return getProperties().getNontemporal();
  }

  bool getInvariant() {
    return getProperties().getInvariant();
  }

  bool getInvariantGroup() {
    return getProperties().getInvariantGroup();
  }

  ::mlir::ptr::AtomicOrdering getOrdering() {
    return getProperties().getOrdering();
  }

  ::mlir::StringAttr getSyncscopeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().syncscope);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSyncscope();
};

} // namespace detail
template <typename RangeT>
class LoadOpGenericAdaptor : public detail::LoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoadOpGenericAdaptorBase;
  static constexpr int odsIndex_ptr = 0;
public:
  LoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LoadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LoadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LoadOpGenericAdaptor(RangeT values, const LoadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LoadOp, typename = std::enable_if_t<std::is_same_v<LateInst, LoadOp>>>
  LoadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPtr() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LoadOpAdaptor : public LoadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LoadOpGenericAdaptor::LoadOpGenericAdaptor;
  LoadOpAdaptor(LoadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LoadOp : public ::mlir::Op<LoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_ptr = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("syncscope")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSyncscopeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSyncscopeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.load");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ptr::PtrType> getPtr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ptr::PtrType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getPtrMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

  bool getVolatile_() {
    return getProperties().getVolatile_();
  }

  bool getNontemporal() {
    return getProperties().getNontemporal();
  }

  bool getInvariant() {
    return getProperties().getInvariant();
  }

  bool getInvariantGroup() {
    return getProperties().getInvariantGroup();
  }

  ::mlir::ptr::AtomicOrdering getOrdering() {
    return getProperties().getOrdering();
  }

  void setAlignment(std::optional<int64_t> newAlignment) {
    getProperties().setAlignment(newAlignment);
  }

  void setVolatile_(bool newVolatile_) {
    getProperties().setVolatile_(newVolatile_);
  }

  void setNontemporal(bool newNontemporal) {
    getProperties().setNontemporal(newNontemporal);
  }

  void setInvariant(bool newInvariant) {
    getProperties().setInvariant(newInvariant);
  }

  void setInvariantGroup(bool newInvariantGroup) {
    getProperties().setInvariantGroup(newInvariantGroup);
  }

  void setOrdering(::mlir::ptr::AtomicOrdering newOrdering) {
    getProperties().setOrdering(newOrdering);
  }

  ::mlir::StringAttr getSyncscopeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().syncscope);
  }

  ::std::optional< ::llvm::StringRef > getSyncscope();
  void setSyncscopeAttr(::mlir::StringAttr attr) {
    getProperties().syncscope = attr;
  }

  void setSyncscope(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeSyncscopeAttr() {
      auto attr = getProperties().syncscope;
      getProperties().syncscope = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type type, Value ptr, unsigned alignment = 0, bool isVolatile = false, bool isNonTemporal = false, bool isInvariant = false, bool isInvariantGroup = false, AtomicOrdering ordering = AtomicOrdering::not_atomic, StringRef syncscope = StringRef());
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type type, Value ptr, unsigned alignment = 0, bool isVolatile = false, bool isNonTemporal = false, bool isInvariant = false, bool isInvariantGroup = false, AtomicOrdering ordering = AtomicOrdering::not_atomic, StringRef syncscope = StringRef());
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, Type type, Value ptr, unsigned alignment = 0, bool isVolatile = false, bool isNonTemporal = false, bool isInvariant = false, bool isInvariantGroup = false, AtomicOrdering ordering = AtomicOrdering::not_atomic, StringRef syncscope = StringRef());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariant, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::LoadOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::MaskedLoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MaskedLoadOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = std::optional<int64_t>;
    alignmentTy alignment = std::nullopt;
    std::optional<int64_t> getAlignment() const {
      auto &propStorage = this->alignment;
      return propStorage;
    }
    void setAlignment(std::optional<int64_t> propValue) {
      auto &propStorage = this->alignment;
      propStorage = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
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
  MaskedLoadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.masked_load", odsAttrs.getContext());
  }

  MaskedLoadOpGenericAdaptorBase(MaskedLoadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

};

} // namespace detail
template <typename RangeT>
class MaskedLoadOpGenericAdaptor : public detail::MaskedLoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MaskedLoadOpGenericAdaptorBase;
  static constexpr int odsIndex_ptr = 0;
  static constexpr int odsIndex_mask = 1;
  static constexpr int odsIndex_passthrough = 2;
public:
  MaskedLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MaskedLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MaskedLoadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MaskedLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MaskedLoadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MaskedLoadOpGenericAdaptor(RangeT values, const MaskedLoadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MaskedLoadOp, typename = std::enable_if_t<std::is_same_v<LateInst, MaskedLoadOp>>>
  MaskedLoadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPtr() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMask() {
    return (*getODSOperands(1).begin());
  }

  ValueT getPassthrough() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MaskedLoadOpAdaptor : public MaskedLoadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MaskedLoadOpGenericAdaptor::MaskedLoadOpGenericAdaptor;
  MaskedLoadOpAdaptor(MaskedLoadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MaskedLoadOp : public ::mlir::Op<MaskedLoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ShapedType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MaskedLoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MaskedLoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_ptr = 0;
  static constexpr int odsIndex_mask = 1;
  static constexpr int odsIndex_passthrough = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.masked_load");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ptr::PtrType> getPtr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ptr::PtrType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getPassthrough() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getPtrMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMaskMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPassthroughMutable() {
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

  ::mlir::TypedValue<::mlir::ShapedType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSResults(0).begin());
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
  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

  void setAlignment(std::optional<int64_t> newAlignment) {
    getProperties().setAlignment(newAlignment);
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value ptr, Value mask, Value passthrough, unsigned alignment = 0);
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value ptr, Value mask, Value passthrough, unsigned alignment = 0);
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value ptr, Value mask, Value passthrough, unsigned alignment = 0);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptr, ::mlir::Value mask, ::mlir::Value passthrough, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::MaskedLoadOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::MaskedStoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MaskedStoreOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = std::optional<int64_t>;
    alignmentTy alignment = std::nullopt;
    std::optional<int64_t> getAlignment() const {
      auto &propStorage = this->alignment;
      return propStorage;
    }
    void setAlignment(std::optional<int64_t> propValue) {
      auto &propStorage = this->alignment;
      propStorage = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
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
  MaskedStoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.masked_store", odsAttrs.getContext());
  }

  MaskedStoreOpGenericAdaptorBase(MaskedStoreOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

};

} // namespace detail
template <typename RangeT>
class MaskedStoreOpGenericAdaptor : public detail::MaskedStoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MaskedStoreOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_ptr = 1;
  static constexpr int odsIndex_mask = 2;
public:
  MaskedStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MaskedStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MaskedStoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MaskedStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MaskedStoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MaskedStoreOpGenericAdaptor(RangeT values, const MaskedStoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MaskedStoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, MaskedStoreOp>>>
  MaskedStoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getPtr() {
    return (*getODSOperands(1).begin());
  }

  ValueT getMask() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MaskedStoreOpAdaptor : public MaskedStoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MaskedStoreOpGenericAdaptor::MaskedStoreOpGenericAdaptor;
  MaskedStoreOpAdaptor(MaskedStoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MaskedStoreOp : public ::mlir::Op<MaskedStoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MaskedStoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MaskedStoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_ptr = 1;
  static constexpr int odsIndex_mask = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.masked_store");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ptr::PtrType> getPtr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ptr::PtrType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPtrMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMaskMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

  void setAlignment(std::optional<int64_t> newAlignment) {
    getProperties().setAlignment(newAlignment);
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value, Value ptr, Value mask, unsigned alignment = 0);
  static MaskedStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value, Value ptr, Value mask, unsigned alignment = 0);
  static MaskedStoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value value, Value ptr, Value mask, unsigned alignment = 0);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static MaskedStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static MaskedStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static MaskedStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static MaskedStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::MaskedStoreOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::PtrAddOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PtrAddOpGenericAdaptorBase {
public:
  struct Properties {
    using flagsTy = ::mlir::ptr::PtrAddFlags;
    flagsTy flags = PtrAddFlags::none;
    ::mlir::ptr::PtrAddFlags getFlags() const {
      auto &propStorage = this->flags;
      return propStorage;
    }
    void setFlags(::mlir::ptr::PtrAddFlags propValue) {
      auto &propStorage = this->flags;
      propStorage = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.flags == this->flags &&
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
  PtrAddOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.ptr_add", odsAttrs.getContext());
  }

  PtrAddOpGenericAdaptorBase(PtrAddOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ptr::PtrAddFlags getFlags() {
    return getProperties().getFlags();
  }

};

} // namespace detail
template <typename RangeT>
class PtrAddOpGenericAdaptor : public detail::PtrAddOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PtrAddOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_offset = 1;
public:
  PtrAddOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PtrAddOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PtrAddOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PtrAddOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PtrAddOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PtrAddOpGenericAdaptor(RangeT values, const PtrAddOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PtrAddOp, typename = std::enable_if_t<std::is_same_v<LateInst, PtrAddOp>>>
  PtrAddOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBase() {
    return (*getODSOperands(0).begin());
  }

  ValueT getOffset() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PtrAddOpAdaptor : public PtrAddOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PtrAddOpGenericAdaptor::PtrAddOpGenericAdaptor;
  PtrAddOpAdaptor(PtrAddOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PtrAddOp : public ::mlir::Op<PtrAddOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ViewLikeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PtrAddOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PtrAddOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_offset = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<PtrAddOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.ptr_add");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOffset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getOffsetMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  ::mlir::ptr::PtrAddFlags getFlags() {
    return getProperties().getFlags();
  }

  void setFlags(::mlir::ptr::PtrAddFlags newFlags) {
    getProperties().setFlags(newFlags);
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags = PtrAddFlags::none);
  static PtrAddOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags = PtrAddFlags::none);
  static PtrAddOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags = PtrAddFlags::none);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags = PtrAddFlags::none);
  static PtrAddOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags = PtrAddFlags::none);
  static PtrAddOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags = PtrAddFlags::none);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags = PtrAddFlags::none);
  static PtrAddOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags = PtrAddFlags::none);
  static PtrAddOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::Value offset, /*optional*/::mlir::ptr::PtrAddFlags flags = PtrAddFlags::none);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PtrAddOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PtrAddOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PtrAddOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PtrAddOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PtrAddOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PtrAddOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PtrAddOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PtrAddOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// `ViewLikeOp::getViewSource` method.
  Value getViewSource() { return getBase(); }

  /// Returns the ptr type of the operation.
  ptr::PtrType getPtrType();
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::PtrAddOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::PtrDiffOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PtrDiffOpGenericAdaptorBase {
public:
  struct Properties {
    using flagsTy = ::mlir::ptr::PtrDiffFlags;
    flagsTy flags = PtrDiffFlags::none;
    ::mlir::ptr::PtrDiffFlags getFlags() const {
      auto &propStorage = this->flags;
      return propStorage;
    }
    void setFlags(::mlir::ptr::PtrDiffFlags propValue) {
      auto &propStorage = this->flags;
      propStorage = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.flags == this->flags &&
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
  PtrDiffOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.ptr_diff", odsAttrs.getContext());
  }

  PtrDiffOpGenericAdaptorBase(PtrDiffOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ptr::PtrDiffFlags getFlags() {
    return getProperties().getFlags();
  }

};

} // namespace detail
template <typename RangeT>
class PtrDiffOpGenericAdaptor : public detail::PtrDiffOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PtrDiffOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
public:
  PtrDiffOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PtrDiffOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PtrDiffOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PtrDiffOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PtrDiffOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PtrDiffOpGenericAdaptor(RangeT values, const PtrDiffOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PtrDiffOp, typename = std::enable_if_t<std::is_same_v<LateInst, PtrDiffOp>>>
  PtrDiffOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLhs() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRhs() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PtrDiffOpAdaptor : public PtrDiffOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PtrDiffOpGenericAdaptor::PtrDiffOpGenericAdaptor;
  PtrDiffOpAdaptor(PtrDiffOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PtrDiffOp : public ::mlir::Op<PtrDiffOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultShape> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PtrDiffOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PtrDiffOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.ptr_diff");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  ::mlir::ptr::PtrDiffFlags getFlags() {
    return getProperties().getFlags();
  }

  void setFlags(::mlir::ptr::PtrDiffFlags newFlags) {
    getProperties().setFlags(newFlags);
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags = PtrDiffFlags::none);
  static PtrDiffOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags = PtrDiffFlags::none);
  static PtrDiffOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags = PtrDiffFlags::none);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags = PtrDiffFlags::none);
  static PtrDiffOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags = PtrDiffFlags::none);
  static PtrDiffOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::ptr::PtrDiffFlags flags = PtrDiffFlags::none);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PtrDiffOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PtrDiffOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PtrDiffOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PtrDiffOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// Returns the operand's ptr type.
  ptr::PtrType getPtrType();
  /// Returns the result's underlying int type.
  Type getIntType();
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::PtrDiffOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::ScatterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ScatterOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = std::optional<int64_t>;
    alignmentTy alignment = std::nullopt;
    std::optional<int64_t> getAlignment() const {
      auto &propStorage = this->alignment;
      return propStorage;
    }
    void setAlignment(std::optional<int64_t> propValue) {
      auto &propStorage = this->alignment;
      propStorage = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
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
  ScatterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.scatter", odsAttrs.getContext());
  }

  ScatterOpGenericAdaptorBase(ScatterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

};

} // namespace detail
template <typename RangeT>
class ScatterOpGenericAdaptor : public detail::ScatterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ScatterOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_ptrs = 1;
  static constexpr int odsIndex_mask = 2;
public:
  ScatterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ScatterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ScatterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ScatterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ScatterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ScatterOpGenericAdaptor(RangeT values, const ScatterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ScatterOp, typename = std::enable_if_t<std::is_same_v<LateInst, ScatterOp>>>
  ScatterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getPtrs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getMask() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ScatterOpAdaptor : public ScatterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ScatterOpGenericAdaptor::ScatterOpGenericAdaptor;
  ScatterOpAdaptor(ScatterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ScatterOp : public ::mlir::Op<ScatterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ScatterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ScatterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_ptrs = 1;
  static constexpr int odsIndex_mask = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.scatter");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getPtrs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPtrsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMaskMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

  void setAlignment(std::optional<int64_t> newAlignment) {
    getProperties().setAlignment(newAlignment);
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value, Value ptrs, Value mask, unsigned alignment = 0);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value, Value ptrs, Value mask, unsigned alignment = 0);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, Value value, Value ptrs, Value mask, unsigned alignment = 0);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptrs, ::mlir::Value mask, /*optional*/std::optional<int64_t> alignment = std::nullopt);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::ScatterOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::StoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StoreOpGenericAdaptorBase {
public:
  struct Properties {
    using syncscopeTy = ::mlir::StringAttr;
    syncscopeTy syncscope;

    auto getSyncscope() const {
      auto &propStorage = this->syncscope;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSyncscope(const ::mlir::StringAttr &propValue) {
      this->syncscope = propValue;
    }
    using alignmentTy = std::optional<int64_t>;
    alignmentTy alignment = std::nullopt;
    std::optional<int64_t> getAlignment() const {
      auto &propStorage = this->alignment;
      return propStorage;
    }
    void setAlignment(std::optional<int64_t> propValue) {
      auto &propStorage = this->alignment;
      propStorage = propValue;
    }
    using volatile_Ty = bool;
    volatile_Ty volatile_ = false;
    bool getVolatile_() const {
      auto &propStorage = this->volatile_;
      return propStorage;
    }
    void setVolatile_(bool propValue) {
      auto &propStorage = this->volatile_;
      propStorage = propValue;
    }
    using nontemporalTy = bool;
    nontemporalTy nontemporal = false;
    bool getNontemporal() const {
      auto &propStorage = this->nontemporal;
      return propStorage;
    }
    void setNontemporal(bool propValue) {
      auto &propStorage = this->nontemporal;
      propStorage = propValue;
    }
    using invariantGroupTy = bool;
    invariantGroupTy invariantGroup = false;
    bool getInvariantGroup() const {
      auto &propStorage = this->invariantGroup;
      return propStorage;
    }
    void setInvariantGroup(bool propValue) {
      auto &propStorage = this->invariantGroup;
      propStorage = propValue;
    }
    using orderingTy = ::mlir::ptr::AtomicOrdering;
    orderingTy ordering = AtomicOrdering::not_atomic;
    ::mlir::ptr::AtomicOrdering getOrdering() const {
      auto &propStorage = this->ordering;
      return propStorage;
    }
    void setOrdering(::mlir::ptr::AtomicOrdering propValue) {
      auto &propStorage = this->ordering;
      propStorage = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.syncscope == this->syncscope &&
        rhs.alignment == this->alignment &&
        rhs.volatile_ == this->volatile_ &&
        rhs.nontemporal == this->nontemporal &&
        rhs.invariantGroup == this->invariantGroup &&
        rhs.ordering == this->ordering &&
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
  StoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.store", odsAttrs.getContext());
  }

  StoreOpGenericAdaptorBase(StoreOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

  bool getVolatile_() {
    return getProperties().getVolatile_();
  }

  bool getNontemporal() {
    return getProperties().getNontemporal();
  }

  bool getInvariantGroup() {
    return getProperties().getInvariantGroup();
  }

  ::mlir::ptr::AtomicOrdering getOrdering() {
    return getProperties().getOrdering();
  }

  ::mlir::StringAttr getSyncscopeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().syncscope);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSyncscope();
};

} // namespace detail
template <typename RangeT>
class StoreOpGenericAdaptor : public detail::StoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StoreOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_ptr = 1;
public:
  StoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : StoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StoreOpGenericAdaptor(RangeT values, const StoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, StoreOp>>>
  StoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getPtr() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StoreOpAdaptor : public StoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StoreOpGenericAdaptor::StoreOpGenericAdaptor;
  StoreOpAdaptor(StoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StoreOp : public ::mlir::Op<StoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_ptr = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("syncscope")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSyncscopeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSyncscopeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.store");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ptr::PtrType> getPtr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ptr::PtrType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPtrMutable() {
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  std::optional<int64_t> getAlignment() {
    return getProperties().getAlignment();
  }

  bool getVolatile_() {
    return getProperties().getVolatile_();
  }

  bool getNontemporal() {
    return getProperties().getNontemporal();
  }

  bool getInvariantGroup() {
    return getProperties().getInvariantGroup();
  }

  ::mlir::ptr::AtomicOrdering getOrdering() {
    return getProperties().getOrdering();
  }

  void setAlignment(std::optional<int64_t> newAlignment) {
    getProperties().setAlignment(newAlignment);
  }

  void setVolatile_(bool newVolatile_) {
    getProperties().setVolatile_(newVolatile_);
  }

  void setNontemporal(bool newNontemporal) {
    getProperties().setNontemporal(newNontemporal);
  }

  void setInvariantGroup(bool newInvariantGroup) {
    getProperties().setInvariantGroup(newInvariantGroup);
  }

  void setOrdering(::mlir::ptr::AtomicOrdering newOrdering) {
    getProperties().setOrdering(newOrdering);
  }

  ::mlir::StringAttr getSyncscopeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().syncscope);
  }

  ::std::optional< ::llvm::StringRef > getSyncscope();
  void setSyncscopeAttr(::mlir::StringAttr attr) {
    getProperties().syncscope = attr;
  }

  void setSyncscope(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeSyncscopeAttr() {
      auto attr = getProperties().syncscope;
      getProperties().syncscope = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value, Value ptr, unsigned alignment = 0, bool isVolatile = false, bool isNonTemporal = false, bool isInvariantGroup = false, AtomicOrdering ordering = AtomicOrdering::not_atomic, StringRef syncscope = StringRef());
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value, Value ptr, unsigned alignment = 0, bool isVolatile = false, bool isNonTemporal = false, bool isInvariantGroup = false, AtomicOrdering ordering = AtomicOrdering::not_atomic, StringRef syncscope = StringRef());
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value value, Value ptr, unsigned alignment = 0, bool isVolatile = false, bool isNonTemporal = false, bool isInvariantGroup = false, AtomicOrdering ordering = AtomicOrdering::not_atomic, StringRef syncscope = StringRef());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value ptr, /*optional*/std::optional<int64_t> alignment, /*optional*/bool volatile_, /*optional*/bool nontemporal, /*optional*/bool invariantGroup, /*optional*/::mlir::ptr::AtomicOrdering ordering, /*optional*/::mlir::StringAttr syncscope);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::StoreOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::ToPtrOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToPtrOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ToPtrOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.to_ptr", odsAttrs.getContext());
  }

  ToPtrOpGenericAdaptorBase(ToPtrOp op);

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
class ToPtrOpGenericAdaptor : public detail::ToPtrOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToPtrOpGenericAdaptorBase;
  static constexpr int odsIndex_ptr = 0;
public:
  ToPtrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToPtrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ToPtrOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToPtrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToPtrOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToPtrOpGenericAdaptor(RangeT values, const ToPtrOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToPtrOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToPtrOp>>>
  ToPtrOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPtr() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ToPtrOpAdaptor : public ToPtrOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToPtrOpGenericAdaptor::ToPtrOpGenericAdaptor;
  ToPtrOpAdaptor(ToPtrOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToPtrOp : public ::mlir::Op<ToPtrOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::ptr::PtrType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToPtrOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToPtrOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_ptr = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.to_ptr");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> getPtr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::PtrLikeTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getPtrMutable() {
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

  ::mlir::TypedValue<::mlir::ptr::PtrType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ptr::PtrType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value ptr);
  static ToPtrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value ptr);
  static ToPtrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value ptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value ptr);
  static ToPtrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value ptr);
  static ToPtrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value ptr);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToPtrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToPtrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToPtrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToPtrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::ToPtrOp)

namespace mlir::ptr {


//===----------------------------------------------------------------------===//
// ::mlir::ptr::TypeOffsetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TypeOffsetOpGenericAdaptorBase {
public:
  struct Properties {
    using elementTypeTy = ::mlir::TypeAttr;
    elementTypeTy elementType;

    auto getElementType() const {
      auto &propStorage = this->elementType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setElementType(const ::mlir::TypeAttr &propValue) {
      this->elementType = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.elementType == this->elementType &&
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
  TypeOffsetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ptr.type_offset", odsAttrs.getContext());
  }

  TypeOffsetOpGenericAdaptorBase(TypeOffsetOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getElementTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().elementType);
    return attr;
  }

  ::mlir::Type getElementType();
};

} // namespace detail
template <typename RangeT>
class TypeOffsetOpGenericAdaptor : public detail::TypeOffsetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TypeOffsetOpGenericAdaptorBase;
public:
  TypeOffsetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TypeOffsetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TypeOffsetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TypeOffsetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TypeOffsetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TypeOffsetOpGenericAdaptor(RangeT values, const TypeOffsetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TypeOffsetOp, typename = std::enable_if_t<std::is_same_v<LateInst, TypeOffsetOp>>>
  TypeOffsetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class TypeOffsetOpAdaptor : public TypeOffsetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TypeOffsetOpGenericAdaptor::TypeOffsetOpGenericAdaptor;
  TypeOffsetOpAdaptor(TypeOffsetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TypeOffsetOp : public ::mlir::Op<TypeOffsetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TypeOffsetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TypeOffsetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("elementType")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getElementTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getElementTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ptr.type_offset");
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

  ::mlir::TypedValue<::mlir::Type> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  ::mlir::TypeAttr getElementTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().elementType);
  }

  ::mlir::Type getElementType();
  void setElementTypeAttr(::mlir::TypeAttr attr) {
    getProperties().elementType = attr;
  }

  void setElementType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::TypeAttr elementType);
  static TypeOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::TypeAttr elementType);
  static TypeOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::TypeAttr elementType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr elementType);
  static TypeOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr elementType);
  static TypeOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr elementType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Type elementType);
  static TypeOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Type elementType);
  static TypeOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Type elementType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Type elementType);
  static TypeOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Type elementType);
  static TypeOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Type elementType);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypeOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypeOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypeOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypeOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
  /// Returns the type offset according to `layout`. If `layout` is `nullopt`
  /// the nearest layout the op will be used for the computation.
  llvm::TypeSize getTypeSize(std::optional<DataLayout> layout = std::nullopt);
};

} // namespace mlir::ptr
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ptr::TypeOffsetOp)


#endif // GET_OP_CLASSES

