/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: AMX.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::amx {

/// tile load operation
/// Loads a tile from memory defined by a `base` and `indices`, with the
///     shape defined by the 2-dim vector type of the result.
///     The tile's rows are populated by reading contiguous elements starting
///     at the `base`. For each tile row, the `base` is incremented by `stride`
///     number of elements.
/// 
///     The tile is loaded using the following indexing scheme:
/// 
///     ```
///     for row in enumerate(tile_rows):
///       mem_row = base[i0, i1, ..., iN + row * stride]
///       for col in enumerate(tile_cols):
///         tile[row, col] = mem_row[col]
///     ```
/// 
///     If the `stride` is not provided, then the `base` buffer must be at least
///     2-dimensional, and the `stride` is automatically inferred and corresponds
///     to the stride of the buffer's second innermost dimension.
/// 
///     The operation is eventually lowered into the "tileloadd" instruction
///     with the corresponding tile configuration.
/// 
///     With the write memory effect, each `amx.tile_load` operation serves as
///     a compilation hint to use a separate tile register.
/// 
///     Example:
/// 
///     ```mlir
///       // Tile load from a 2-D memref with implicit stride.
///       %0 = amx.tile_load %arg0[%c0, %c0] : memref<?x?xi8> into !amx.tile<16x64xi8>
/// 
///       // Tile load from a 1-D memref with explicit stride.
///       %0 = amx.tile_load %arg0[%c0], %stride : memref<?xi8> into !amx.tile<16x64xi8>
///     ```
class TileLoadOp;

} // namespace mlir::amx
namespace mlir::amx {

/// tile multiplication operation (floating-point)
/// Multiplies a "m x k" tile with a "k x n" tile and accumulates the results
///     into a "m x n" destination tile. Supports "f32 <- bf16 x bf16" (with
///     pairs of "bf16").
///     
///     The operation is eventually lowered into the "tdpbf16ps" instruction with
///     the corresponding tile configuration.
/// 
///     Example:
/// 
///     ```mlir
///       %0 = amx.tile_mulf %a, %b, %c
///         : !amx.tile<16x32xbf16>, !amx.tile<16x32xbf16>, !amx.tile<16x16xf32>
///     ```
class TileMulFOp;

} // namespace mlir::amx
namespace mlir::amx {

/// tile multiplication operation (integer)
/// Multiplies a "m x k" tile with a "k x n" tile and accumulates the results
///     into a "m x n" destination tile. Supports all "si32 <- s/ui8 x s/ui8"
///     combinations (4 bytes packed into dwords in the columns of both the
///     source operand tiles; the zero or sign extension is specified with
///     the attributes and default to sign extended).
///     
///     The operation is eventually lowered into one of the "tdpbssd",
///     "tdpbsud", "tdpbusd", or "tdpbuud" instructions with the corresponding
///     tile configuration.
/// 
///     Example:
/// 
///     ```mlir
///       %0 = amx.tile_muli %a zext, %b zext, %c
///         : !amx.tile<16x64xi8>, !amx.tile<16x64xi8>, !amx.tile<16x16xi32>
///     ```
class TileMulIOp;

} // namespace mlir::amx
namespace mlir::amx {

/// tile store operation
/// Stores a tile to memory defined by a `base` and `indices`, with the
///     shape defined by the 2-dim vector type of the value.
///     The tile's rows are written contiguously to the buffer starting at
///     the `base`. For each tile row, the `base` is incremented by `stride`
///     number of elements.
/// 
///     The tile is stored using the following indexing scheme:
/// 
///     ```
///     for row in enumerate(tile_rows):
///       mem_row = base[i0, i1, ..., iN + row * stride]
///       for col in enumerate(tile_cols):
///         mem_row[col] = tile[row, col]
///     ```
/// 
///     If the `stride` is not provided, then the `base` buffer must be at least
///     2-dimensional, and the `stride` is automatically inferred and corresponds
///     to the stride of the buffer's second innermost dimension.
/// 
///     The operation is eventually lowered into the "tilestored" instruction
///     with the corresponding tile configuration.
/// 
///     Example:
/// 
///     ```mlir
///       // Tile store to a 2-D memref with implicit stride.
///       amx.tile_store %arg1[%c0, %c0], %0 : memref<?x?xi8>, !amx.tile<16x64xi8>
/// 
///       // Tile store to a 1-D memref with explicit stride.
///       amx.tile_store %arg1[%c0], %0, %stride : memref<?xi8>, !amx.tile<16x64xi8>
///     ```
class TileStoreOp;

} // namespace mlir::amx
namespace mlir::amx {

/// tile zero operation
/// Zeroes the destination tile, with the shape defined by the 2-dim
///     vector type of the result.
///     
///     The operation is eventually lowered into the "tilezero" instruction
///     with the corresponding tile configuration.
///     
///     With the write memory effect, each `amx.tile_zero` operation serves as
///     a compilation hint to use a separate tile register.
/// 
///     Example:
/// 
///     ```mlir
///       %0 = amx.tile_zero : !amx.tile<16x16xbf16>
///     ```
class TileZeroOp;

} // namespace mlir::amx
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::amx {


//===----------------------------------------------------------------------===//
// ::mlir::amx::TileLoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TileLoadOpGenericAdaptorBase {
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
  TileLoadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("amx.tile_load", odsAttrs.getContext());
  }

  TileLoadOpGenericAdaptorBase(TileLoadOp op);

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
class TileLoadOpGenericAdaptor : public detail::TileLoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TileLoadOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_stride = 2;
public:
  TileLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TileLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TileLoadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TileLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TileLoadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TileLoadOpGenericAdaptor(RangeT values, const TileLoadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TileLoadOp, typename = std::enable_if_t<std::is_same_v<LateInst, TileLoadOp>>>
  TileLoadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getIndices() {
    return getODSOperands(1);
  }

  ValueT getStride() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TileLoadOpAdaptor : public TileLoadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TileLoadOpGenericAdaptor::TileLoadOpGenericAdaptor;
  TileLoadOpAdaptor(TileLoadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TileLoadOp : public ::mlir::Op<TileLoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::amx::TileType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::LLVM::OneToOneIntrinsicOpInterface::Trait, ::mlir::amx::AMXIntrinsicOp::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TileLoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TileLoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_stride = 2;
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
    return ::llvm::StringLiteral("amx.tile_load");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::IndexType> getStride() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IndexType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*operands.begin());
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  ::mlir::MutableOperandRange getStrideMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::amx::TileType> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSResults(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type res, Value base, ValueRange indices);
  static TileLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type res, Value base, ValueRange indices);
  static TileLoadOp create(::mlir::ImplicitLocOpBuilder &builder, Type res, Value base, ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::Value stride);
  static TileLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::Value stride);
  static TileLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::Value stride);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::Value stride);
  static TileLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::Value stride);
  static TileLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::Value stride);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getBase().getType());
  }
  TileType getTileType() {
    return ::llvm::cast<TileType>(getRes().getType());
  }

  std::string getIntrinsicName() {
    return "llvm.x86.tileloadd64.internal";
  }
  SmallVector<Value> getIntrinsicOperands(
      ::mlir::ArrayRef<Value> operands,
      const ::mlir::LLVMTypeConverter &typeConverter,
      ::mlir::RewriterBase &rewriter);
};

} // namespace mlir::amx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::amx::TileLoadOp)

namespace mlir::amx {


//===----------------------------------------------------------------------===//
// ::mlir::amx::TileMulFOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TileMulFOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TileMulFOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("amx.tile_mulf", odsAttrs.getContext());
  }

  TileMulFOpGenericAdaptorBase(TileMulFOp op);

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
class TileMulFOpGenericAdaptor : public detail::TileMulFOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TileMulFOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_acc = 2;
public:
  TileMulFOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TileMulFOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TileMulFOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TileMulFOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TileMulFOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TileMulFOpGenericAdaptor(RangeT values, const TileMulFOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TileMulFOp, typename = std::enable_if_t<std::is_same_v<LateInst, TileMulFOp>>>
  TileMulFOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getAcc() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TileMulFOpAdaptor : public TileMulFOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TileMulFOpGenericAdaptor::TileMulFOpGenericAdaptor;
  TileMulFOpAdaptor(TileMulFOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TileMulFOp : public ::mlir::Op<TileMulFOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::amx::TileType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::LLVM::OneToOneIntrinsicOpInterface::Trait, ::mlir::amx::AMXIntrinsicOp::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TileMulFOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TileMulFOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_acc = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("amx.tile_mulf");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::amx::TileType> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::amx::TileType> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::amx::TileType> getAcc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAccMutable() {
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

  ::mlir::TypedValue<::mlir::amx::TileType> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static TileMulFOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static TileMulFOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static TileMulFOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static TileMulFOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileMulFOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileMulFOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileMulFOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileMulFOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  TileType getLhsTileType() {
    return ::llvm::cast<TileType>(getLhs().getType());
  }
  TileType getRhsTileType() {
    return ::llvm::cast<TileType>(getRhs().getType());
  }
  TileType getTileType() {
    return ::llvm::cast<TileType>(getRes().getType());
  }

  std::string getIntrinsicName() {
    std::string intr = "llvm.x86.tdp";
    auto elementType =
      getLhsTileType().getElementType();
    intr += elementType.isF16() ? "fp16" : "bf16";
    intr += "ps.internal";
    return intr;
  }
  SmallVector<Value> getIntrinsicOperands(
      ::mlir::ArrayRef<Value> operands,
      const ::mlir::LLVMTypeConverter &typeConverter,
      ::mlir::RewriterBase &rewriter);
};

} // namespace mlir::amx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::amx::TileMulFOp)

namespace mlir::amx {


//===----------------------------------------------------------------------===//
// ::mlir::amx::TileMulIOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TileMulIOpGenericAdaptorBase {
public:
  struct Properties {
    using isZextLhsTy = ::mlir::UnitAttr;
    isZextLhsTy isZextLhs;

    auto getIsZextLhs() const {
      auto &propStorage = this->isZextLhs;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsZextLhs(const ::mlir::UnitAttr &propValue) {
      this->isZextLhs = propValue;
    }
    using isZextRhsTy = ::mlir::UnitAttr;
    isZextRhsTy isZextRhs;

    auto getIsZextRhs() const {
      auto &propStorage = this->isZextRhs;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsZextRhs(const ::mlir::UnitAttr &propValue) {
      this->isZextRhs = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.isZextLhs == this->isZextLhs &&
        rhs.isZextRhs == this->isZextRhs &&
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
  TileMulIOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("amx.tile_muli", odsAttrs.getContext());
  }

  TileMulIOpGenericAdaptorBase(TileMulIOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getIsZextLhsAttr();
  bool getIsZextLhs();
  ::mlir::UnitAttr getIsZextRhsAttr();
  bool getIsZextRhs();
};

} // namespace detail
template <typename RangeT>
class TileMulIOpGenericAdaptor : public detail::TileMulIOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TileMulIOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_acc = 2;
public:
  TileMulIOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TileMulIOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TileMulIOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TileMulIOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TileMulIOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TileMulIOpGenericAdaptor(RangeT values, const TileMulIOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TileMulIOp, typename = std::enable_if_t<std::is_same_v<LateInst, TileMulIOp>>>
  TileMulIOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getAcc() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TileMulIOpAdaptor : public TileMulIOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TileMulIOpGenericAdaptor::TileMulIOpGenericAdaptor;
  TileMulIOpAdaptor(TileMulIOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TileMulIOp : public ::mlir::Op<TileMulIOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::amx::TileType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::LLVM::OneToOneIntrinsicOpInterface::Trait, ::mlir::amx::AMXIntrinsicOp::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TileMulIOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TileMulIOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_acc = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("isZextLhs"), ::llvm::StringRef("isZextRhs")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIsZextLhsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIsZextLhsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIsZextRhsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIsZextRhsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("amx.tile_muli");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::amx::TileType> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::amx::TileType> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::amx::TileType> getAcc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAccMutable() {
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

  ::mlir::TypedValue<::mlir::amx::TileType> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSResults(0).begin());
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
  ::mlir::UnitAttr getIsZextLhsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().isZextLhs);
  }

  bool getIsZextLhs();
  ::mlir::UnitAttr getIsZextRhsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().isZextRhs);
  }

  bool getIsZextRhs();
  void setIsZextLhsAttr(::mlir::UnitAttr attr) {
    getProperties().isZextLhs = attr;
  }

  void setIsZextLhs(bool attrValue);
  void setIsZextRhsAttr(::mlir::UnitAttr attr) {
    getProperties().isZextRhs = attr;
  }

  void setIsZextRhs(bool attrValue);
  ::mlir::Attribute removeIsZextLhsAttr() {
      auto attr = getProperties().isZextLhs;
      getProperties().isZextLhs = {};
      return attr;
  }

  ::mlir::Attribute removeIsZextRhsAttr() {
      auto attr = getProperties().isZextRhs;
      getProperties().isZextRhs = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/::mlir::UnitAttr isZextLhs, /*optional*/::mlir::UnitAttr isZextRhs = nullptr);
  static TileMulIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/::mlir::UnitAttr isZextLhs, /*optional*/::mlir::UnitAttr isZextRhs = nullptr);
  static TileMulIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/::mlir::UnitAttr isZextLhs, /*optional*/::mlir::UnitAttr isZextRhs = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/::mlir::UnitAttr isZextLhs, /*optional*/::mlir::UnitAttr isZextRhs = nullptr);
  static TileMulIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/::mlir::UnitAttr isZextLhs, /*optional*/::mlir::UnitAttr isZextRhs = nullptr);
  static TileMulIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/::mlir::UnitAttr isZextLhs, /*optional*/::mlir::UnitAttr isZextRhs = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/bool isZextLhs = false, /*optional*/bool isZextRhs = false);
  static TileMulIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/bool isZextLhs = false, /*optional*/bool isZextRhs = false);
  static TileMulIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/bool isZextLhs = false, /*optional*/bool isZextRhs = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/bool isZextLhs = false, /*optional*/bool isZextRhs = false);
  static TileMulIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/bool isZextLhs = false, /*optional*/bool isZextRhs = false);
  static TileMulIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, /*optional*/bool isZextLhs = false, /*optional*/bool isZextRhs = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileMulIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileMulIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileMulIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileMulIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  TileType getLhsTileType() {
    return ::llvm::cast<TileType>(getLhs().getType());
  }
  TileType getRhsTileType() {
    return ::llvm::cast<TileType>(getRhs().getType());
  }
  TileType getTileType() {
    return ::llvm::cast<TileType>(getRes().getType());
  }

  std::string getIntrinsicName() {
    std::string intr = "llvm.x86.tdpb";
    intr += getIsZextLhs() ? "u" : "s";
    intr += getIsZextRhs() ? "u" : "s";
    intr += "d.internal";
    return intr;
  }
  SmallVector<Value> getIntrinsicOperands(
      ::mlir::ArrayRef<Value> operands,
      const ::mlir::LLVMTypeConverter &typeConverter,
      ::mlir::RewriterBase &rewriter);
};

} // namespace mlir::amx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::amx::TileMulIOp)

namespace mlir::amx {


//===----------------------------------------------------------------------===//
// ::mlir::amx::TileStoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TileStoreOpGenericAdaptorBase {
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
  TileStoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("amx.tile_store", odsAttrs.getContext());
  }

  TileStoreOpGenericAdaptorBase(TileStoreOp op);

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
class TileStoreOpGenericAdaptor : public detail::TileStoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TileStoreOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_val = 2;
  static constexpr int odsIndex_stride = 3;
public:
  TileStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TileStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TileStoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TileStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TileStoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TileStoreOpGenericAdaptor(RangeT values, const TileStoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TileStoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, TileStoreOp>>>
  TileStoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getIndices() {
    return getODSOperands(1);
  }

  ValueT getVal() {
    return (*getODSOperands(2).begin());
  }

  ValueT getStride() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TileStoreOpAdaptor : public TileStoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TileStoreOpGenericAdaptor::TileStoreOpGenericAdaptor;
  TileStoreOpAdaptor(TileStoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TileStoreOp : public ::mlir::Op<TileStoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::LLVM::OneToOneIntrinsicOpInterface::Trait, ::mlir::amx::AMXIntrinsicOp::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TileStoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TileStoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_val = 2;
  static constexpr int odsIndex_stride = 3;
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
    return ::llvm::StringLiteral("amx.tile_store");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::amx::TileType> getVal() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getStride() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IndexType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*operands.begin());
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  ::mlir::OpOperand &getValMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getStrideMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value base, ValueRange indices, Value val);
  static TileStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value base, ValueRange indices, Value val);
  static TileStoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value base, ValueRange indices, Value val);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value val, /*optional*/::mlir::Value stride);
  static TileStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value val, /*optional*/::mlir::Value stride);
  static TileStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value val, /*optional*/::mlir::Value stride);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value val, /*optional*/::mlir::Value stride);
  static TileStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value val, /*optional*/::mlir::Value stride);
  static TileStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value val, /*optional*/::mlir::Value stride);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getBase().getType());
  }
  TileType getTileType() {
    return ::llvm::cast<TileType>(getVal().getType());
  }

  std::string getIntrinsicName() {
    return "llvm.x86.tilestored64.internal";
  }
  SmallVector<Value> getIntrinsicOperands(
      ::mlir::ArrayRef<Value> operands,
      const ::mlir::LLVMTypeConverter &typeConverter,
      ::mlir::RewriterBase &rewriter);
};

} // namespace mlir::amx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::amx::TileStoreOp)

namespace mlir::amx {


//===----------------------------------------------------------------------===//
// ::mlir::amx::TileZeroOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TileZeroOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TileZeroOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("amx.tile_zero", odsAttrs.getContext());
  }

  TileZeroOpGenericAdaptorBase(TileZeroOp op);

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
class TileZeroOpGenericAdaptor : public detail::TileZeroOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TileZeroOpGenericAdaptorBase;
public:
  TileZeroOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TileZeroOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TileZeroOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TileZeroOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TileZeroOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TileZeroOpGenericAdaptor(RangeT values, const TileZeroOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TileZeroOp, typename = std::enable_if_t<std::is_same_v<LateInst, TileZeroOp>>>
  TileZeroOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class TileZeroOpAdaptor : public TileZeroOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TileZeroOpGenericAdaptor::TileZeroOpGenericAdaptor;
  TileZeroOpAdaptor(TileZeroOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TileZeroOp : public ::mlir::Op<TileZeroOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::amx::TileType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::LLVM::OneToOneIntrinsicOpInterface::Trait, ::mlir::amx::AMXIntrinsicOp::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TileZeroOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TileZeroOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("amx.tile_zero");
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

  ::mlir::TypedValue<::mlir::amx::TileType> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::amx::TileType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res);
  static TileZeroOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res);
  static TileZeroOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static TileZeroOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static TileZeroOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileZeroOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileZeroOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileZeroOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileZeroOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  TileType getTileType() {
    return ::llvm::cast<TileType>(getRes().getType());
  }

  std::string getIntrinsicName() {
    return "llvm.x86.tilezero.internal";
  }
  SmallVector<Value> getIntrinsicOperands(
      ::mlir::ArrayRef<Value> operands,
      const ::mlir::LLVMTypeConverter &typeConverter,
      ::mlir::RewriterBase &rewriter);
};

} // namespace mlir::amx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::amx::TileZeroOp)


#endif // GET_OP_CLASSES

