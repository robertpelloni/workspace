/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: QuantOps.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::quant {

/// Dequantize cast operation
/// Convert an input quantized value into its expressed floating-point value.
///     The dequantization process consists of the following steps:
/// 
///     ```
///     def dequantize(quantizedValue: quantizedType) -> expressedType:
///         storedValue = reinterpretCast(quantizedValue, storageType)
///         storedValueFloat = convertIntToFloat(storedValue, expressedType)
///         zeroPointFloat = convertIntToFloat(zeroPoint, expressedType)
///         expressedValue = (storedValueFloat - zeroPointFloat) * scale
///         return expressedValue
///     ```
/// 
///     Here, `storageType`, `expressedType`, `scale`, and `zeroPoint` are obtained
///     from the corresponding parameters encoded in `quantizedType`. For
///     per-channel quantization, the appropriate `scale` and `zeroPoint` values
///     are used for each tensor element computation according to the channel the
///     element belongs to.
///     
///     The numerical results produced by the algorithm above may vary depending on
///     the rounding methods used by `convertIntToFloat()`, subtraction (`-`), and
///     multiplication (`*`). This operation does not define specific rounding
///     methods; instead, it is the responsibility of a transform pipeline to
///     determine which rounding method to apply when this operation is broken down
///     into lower-level dialects.
/// 
///     The operation must satisfy the following syntactic constraints:
/// 
///     - Operand `input` must be a scalar or tensor of type `!quant.uniform`.
/// 
///     - The result type must be a floating-point scalar or tensor.
/// 
///     - The `expressedType` parameter of the `!quant.uniform` type of the input
///       must match the floating-point type of the result.
/// 
///     - The operand and result types must be both scalars or both tensors. If
///       tensors, they must be both ranked or both unranked. If ranked, both must
///       have the same shape, including matching static and dynamic dimensions.
/// 
///     - If the operand uses per-channel quantization, its `!quant.uniform` type
///       must adhere to the [Per-axis quantization
///       integrity](#per-axis-quantization-integrity) guidelines.
/// 
///     Examples:
/// 
///     ```
///     // Dequantize a scalar quantized value
///     %result = quant.dcast %input : !quant.uniform<i8:f32, 2.0> to f32
/// 
///     // Dequantize a dynamically shaped tensor of quantized values
///     %result = quant.dcast %input : tensor<?x!quant.uniform<i8:f32, 2.0>> to tensor<?xf32>
/// 
///     // Dequantize an unranked tensor using per-axis quantization information
///     %result = quant.dcast %input : tensor<*x!quant.uniform<i8:f32:1, {2.0, 3.0}>> to tensor<*xf32>
///     ```
class DequantizeCastOp;

} // namespace mlir::quant
namespace mlir::quant {

/// Quantize cast operation
/// Convert a floating-point value to a quantized type. The quantization
///     process consists of the following steps:
/// 
///     ```
///     def quantize(expressedValue: expressedType) -> quantizedType:
///         zeroPointFloat = convertIntToFloat(zeroPoint, expressedType)
///         scaledValue = expressedValue / scale
///         storedValueFloat = scaledValue + zeroPointFloat
///         storedValue = convertFloatToInt(storedValueFloat, storageType)
///         storedValueClamped = clamp(storedValue, storageMin, storageMax)
///         quantizedValue = reinterpretCast(storedValueClamped, quantizedType)
///         return quantizedValue
///     ```
/// 
///     Here, `storageType`, `storageMin`, `storageMax`, `expressedType`, `scale`,
///     and `zeroPoint` are obtained from the corresponding parameters encoded in
///     `quantizedType`. For per-channel quantization, the appropriate `scale` and
///     `zeroPoint` values are used for each tensor element computation according
///     to the channel the element belongs to.
/// 
///     The numerical results produced by the algorithm above may vary depending on
///     the rounding methods used by `convertIntToFloat()`, `convertFloatToInt()`,
///     `clamp()`, division (`/`), and addition (`+`). This operation does not
///     define specific rounding methods; instead, it is the responsibility of a
///     transform pipeline to determine which rounding method to apply when this
///     operation is broken down into lower-level dialects.
/// 
///     The operation must satisfy the following syntactic constraints:
/// 
///     - Operand `input` must be a floating-point scalar or tensor.
/// 
///     - The result type must be a scalar or tensor of type `!quant.uniform`.
/// 
///     - The `expressedType` parameter in the `!quant.uniform` type of the result
///       must match the floating-point type of the input.
/// 
///     - The operand and result types must be both scalars or both tensors. If
///       tensors, they must be both ranked or both unranked. If ranked, both must
///       have the same shape, including matching static and dynamic dimensions.
/// 
///     - If the result uses per-channel quantization, its `!quant.uniform` type
///       must adhere to the [Per-axis quantization
///       integrity](#per-axis-quantization-integrity) guidelines.
/// 
///     Examples:
/// 
///     ```
///     // Quantize a scalar floating-point value
///     %result = quant.qcast %input : f32 to !quant.uniform<i8:f32, 2.0>
/// 
///     // Quantize a dynamically shaped tensor of quantized values
///     %result = quant.qcast %input : tensor<?xf32> to tensor<?x!quant.uniform<i8:f32, 2.0>>
/// 
///     // Quantize an unranked tensor using per-axis quantization information
///     %result = quant.qcast %input : tensor<*xf32> to tensor<*x!quant.uniform<i8:f32:1, {2.0, 3.0}>>
///     ```
class QuantizeCastOp;

} // namespace mlir::quant
namespace mlir::quant {

/// Storage cast operation
/// Convert a value from a quantized type to the corresponding signless integer
///     storage type, or vice versa. This conversion simply involves a
///     reinterpretation of the input bits and does not involve any data
///     manipulation.
/// 
///     The following syntactic restrictions must be met:
/// 
///     - Operand `input` must be a scalar or tensor of a signless integer or
///       `!quant.uniform` type.
/// 
///     - The result must be a scalar or tensor of a signless integer or
///       `!quant.uniform` type.
/// 
///     - If the operand is a scalar or tensor of type integer, the result must be
///       a scalar or tensor of type `!quant.uniform`, and vice versa.
/// 
///     - The operand and result must be both scalars or both tensors. If tensors,
///       they must be both ranked or both unranked. If ranked, both must have the
///       same shape, including matching static and dynamic dimensions.
/// 
///     - The width of the `storageType` parameter of the quantized type of the
///       operand or result must match the width of the signless integer type of
///       the operand or result.
/// 
///     - If the operand or result uses per-channel quantization, its
///       `!quant.uniform` type must adhere to the [Per-axis quantization
///       integrity](#per-axis-quantization-integrity) guidelines.
/// 
///     Examples:
/// 
///     ```
///     // Cast a scalar quantized value into its storage type
///     %result = quant.scast %input : !quant.uniform<i8:f32, 2.0> to i8
/// 
///     // Cast a dynamically shaped tensor of quantized values into their storage type
///     %result = quant.scast %input : tensor<?x!quant.uniform<i8:f32, 2.0>> to tensor<?xi8>
/// 
///     // Cast an unranked tensor of signless integers into a quantized type using
///     // per-channel quantization
///     %result = quant.scast %input : tensor<*xi8> to tensor<*x!quant.uniform<i8:f32:1, {2.0, 3.0}>>
///     ```
class StorageCastOp;

} // namespace mlir::quant
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::quant {


//===----------------------------------------------------------------------===//
// ::mlir::quant::DequantizeCastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DequantizeCastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DequantizeCastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("quant.dcast", odsAttrs.getContext());
  }

  DequantizeCastOpGenericAdaptorBase(DequantizeCastOp op);

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
class DequantizeCastOpGenericAdaptor : public detail::DequantizeCastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DequantizeCastOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  DequantizeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DequantizeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DequantizeCastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DequantizeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DequantizeCastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DequantizeCastOpGenericAdaptor(RangeT values, const DequantizeCastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DequantizeCastOp, typename = std::enable_if_t<std::is_same_v<LateInst, DequantizeCastOp>>>
  DequantizeCastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DequantizeCastOpAdaptor : public DequantizeCastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DequantizeCastOpGenericAdaptor::DequantizeCastOpGenericAdaptor;
  DequantizeCastOpAdaptor(DequantizeCastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DequantizeCastOp : public ::mlir::Op<DequantizeCastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DequantizeCastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DequantizeCastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("quant.dcast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input);
  static DequantizeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static DequantizeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static DequantizeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static DequantizeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DequantizeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DequantizeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DequantizeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DequantizeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// Return the float type of the scalar or tensor result.
  FloatType getFloatType();

  /// Return the quantized type of the scalar or tensor input.
  quant::QuantizedType getQuantizedType();
};

} // namespace mlir::quant
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::quant::DequantizeCastOp)

namespace mlir::quant {


//===----------------------------------------------------------------------===//
// ::mlir::quant::QuantizeCastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QuantizeCastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QuantizeCastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("quant.qcast", odsAttrs.getContext());
  }

  QuantizeCastOpGenericAdaptorBase(QuantizeCastOp op);

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
class QuantizeCastOpGenericAdaptor : public detail::QuantizeCastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QuantizeCastOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  QuantizeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QuantizeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : QuantizeCastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QuantizeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QuantizeCastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QuantizeCastOpGenericAdaptor(RangeT values, const QuantizeCastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QuantizeCastOp, typename = std::enable_if_t<std::is_same_v<LateInst, QuantizeCastOp>>>
  QuantizeCastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class QuantizeCastOpAdaptor : public QuantizeCastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QuantizeCastOpGenericAdaptor::QuantizeCastOpGenericAdaptor;
  QuantizeCastOpAdaptor(QuantizeCastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QuantizeCastOp : public ::mlir::Op<QuantizeCastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QuantizeCastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QuantizeCastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("quant.qcast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input);
  static QuantizeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static QuantizeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static QuantizeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static QuantizeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QuantizeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QuantizeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QuantizeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QuantizeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// Return the float type of the scalar or tensor input.
  FloatType getFloatType();

  /// Return the quantized type of the scalar or tensor result.
  quant::QuantizedType getQuantizedType();
};

} // namespace mlir::quant
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::quant::QuantizeCastOp)

namespace mlir::quant {


//===----------------------------------------------------------------------===//
// ::mlir::quant::StorageCastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StorageCastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StorageCastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("quant.scast", odsAttrs.getContext());
  }

  StorageCastOpGenericAdaptorBase(StorageCastOp op);

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
class StorageCastOpGenericAdaptor : public detail::StorageCastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StorageCastOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  StorageCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StorageCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : StorageCastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StorageCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StorageCastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StorageCastOpGenericAdaptor(RangeT values, const StorageCastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StorageCastOp, typename = std::enable_if_t<std::is_same_v<LateInst, StorageCastOp>>>
  StorageCastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StorageCastOpAdaptor : public StorageCastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StorageCastOpGenericAdaptor::StorageCastOpGenericAdaptor;
  StorageCastOpAdaptor(StorageCastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StorageCastOp : public ::mlir::Op<StorageCastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StorageCastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StorageCastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("quant.scast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input);
  static StorageCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static StorageCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static StorageCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static StorageCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StorageCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StorageCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StorageCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StorageCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// Return the integer type used either in the input or the result.
  IntegerType getIntegerType();

  /// Return the quantized type used either in the input or the result.
  quant::QuantizedType getQuantizedType();
};

} // namespace mlir::quant
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::quant::StorageCastOp)


#endif // GET_OP_CLASSES

