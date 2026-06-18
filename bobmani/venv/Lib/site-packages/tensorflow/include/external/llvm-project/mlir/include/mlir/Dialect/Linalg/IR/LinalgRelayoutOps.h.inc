/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LinalgRelayoutOps.td                                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::linalg {

/// linalg.pack operation
/// The "pack" operation converts a source tensor of rank `n` into a result
///     tensor of rank `n + k` with a tiled and packed layout (maybe with padding)
///     and optionally transposes the tiled source tensor dimensions.
/// 
///     `inner_tiles` (mandatory) specifies `k` tile sizes. These tile sizes
///     correspond to the least significant ("inner") result tensor dimension sizes,
///     in the same order. Tile sizes can be static or dynamic.
/// 
///     `inner_dims_pos` (mandatory) specifies `k` source tensor dimensions that are
///     being tiled, where `0 <= k <= n`.
///      - `inner_dims_pos[i]` specifies the source tensor dimension tiled by
///     `inner_tiles[i]` where `0 <= i < k`. All the values in `inner_dims_pos` are
///     within [0, n).
///      - The tiled dimensions (of size `inner_tiles`) are added to the end of the
///      result tensor in the order in which they appear, i.e.
///      `shape(result)[rank(source) + i] = inner_tiles[i]` for `0 <= i < k`.
///      - The following relationship for the tiled dimensions holds:
///      `shape(result)[inner_dims_pos[i]] = shape(source)[inner_dims_pos[i]] / inner_tiles[i]`,
///      where (⌈/⌉ indicates CeilDiv).
/// 
/// 
///     Example: If `inner_tiles = [16, 32]`, the result tensor has a shape of
///     `...x16x32`. If `inner_dims_pos = [0, 1]`, the 0th source dimension is tiled
///     by 16 and the 1st source dimension is tiled by 32. Other source dimensions
///     (if any) are not tiled. If `inner_dims_pos = [1, 0]`, the 1st dimension is
///     tiled by 16 and the 0th dimension is tiled by 32.
/// 
///     Example:
///     ```mlir
///     // NC to NCnc
///     %0 = linalg.pack %source inner_dims_pos = [0, 1] inner_tiles = [8, 32]
///         into %dest : tensor<128x256xf32> -> tensor<16x8 x 8x32 xf32>
///     //                                             \  /   \  /
///     //                                 Outer Dims: 16x8   Inner Dims: 8x32
/// 
///     // CHW to CHWhw
///     %0 = linalg.pack %source inner_dims_pos = [2, 1] inner_tiles = [4, 2]
///         into %dest : tensor<3x20x24xf32> -> tensor<3x10x6 x 4x2 xf32>
///     //                                              \  /    \ /
///     //                                 Outer Dims: 3x10x6  Inner Dims: 4x2
/// 
///     // HCW to HCWhw
///     %0 = linalg.pack %source inner_dims_pos = [2, 0] inner_tiles = [4, 2]
///         into %dest : tensor<18x3x32xf32> -> tensor<9x3x8 x 4x2 xf32>
///     //                                              \  /   \ /
///     //                                 Outer Dims: 9x3x8  Inner Dims: 4x2
///     ```
/// 
///     `outer_dims_perm` (optional) specifies a permutation for the outer
///     dimensions. If specified, it must have `n` elements.
/// 
///     Example:
///     ```mlir
///     // CK to KCck
///     %0 = linalg.pack %source outer_dims_perm = [1, 0] inner_dims_pos = [0, 1]
///         inner_tiles = [8, 32] into %dest
///         : tensor<128x256xf32> -> tensor<8x16 x 8x32 xf32>
///     //                                  \  /
///     //            compare with "NC to NCnc": outer dims are transposed
///     ```
/// 
///     `padding_value` specifies a padding value at the boundary on non-perfectly
///     divisible dimensions. Padding is optional:
///     - If absent, it is assumed that for all inner tiles,
///       `shape(source)[inner_dims_pos[i]] % inner_tiles[i] == 0`, i.e. all inner
///       tiles divide perfectly the corresponding outer dimension in the result
///       tensor. It is UB if the tile does not perfectly divide the dimension.
///     - If present, it will pad along high dimensions (high-padding) to make the
///       tile complete. Note that it is not allowed to have artificial padding that
///       is not strictly required by linalg.pack (i.e., padding past what is needed
///       to complete the last tile along each packed dimension). It is UB if extra
///       padding is requested.
///     It is not possible to verify the requirements statically with dynamic
///     shapes, so they are treated as UB.
/// 
///     Example:
///     ```mlir
///     %0 = linalg.pack %arg0 padding_value(%pad : f32) outer_dims_perm = [2, 1, 0]
///         inner_dims_pos = [1] inner_tiles = [2] into %arg1
///         : tensor<200x127x256xf32> -> tensor<256x64x200x2xf32>
///     //                 \
///     //                padded and tiled dim
///     //
///     // Source dimension 1 is tiled. 64 does not divide 127 evenly, so 1 padded
///     // element is added at the end.
///     //
///     // Note: Only tiled dimensions can be padded.
///     ```
/// 
///     Invalid example that has artificial padding:
///     ```mlir
///     %0 = linalg.pack %src padding_value(%cst : f32) inner_dims_pos = [0]
///         inner_tiles = [8] into %dest
///         : tensor<9xf32> -> tensor<3x8xf32>
///     //                             \
///     //            expect tensor<2x8xf32> because CeilDiv(9, 8) = 2
///     ```
class PackOp;

} // namespace mlir::linalg
namespace mlir::linalg {

/// linalg.unpack operation
/// The "unpack" operation converts a source tensor of rank `n` with a tiled and
///     packed layout to a result tensor of rank `n - k`.
/// 
///     `inner_tiles` (mandatory) specifies `k` tile sizes. These tile sizes
///     correspond to the least significant ("inner") source tensor dimension sizes.
///     The behavior of this op is undefined if:
///     - `inner_tiles` do not exactly match with the corresponding source tensor
///       dimension sizes.
///     - Or, `inner_tiles[i]` does not divide the size of dimension
///       `inner_dims_pos[i]` (assuming that `outer_dims_perm` is not specified)
///       evenly.
/// 
///     `inner_dims_pos` (mandatory) specifies `k` result tensor (i.e. unpacked
///     tensor) dimensions that were tiled with the `inner_tiles` to create the
///     packed source tensor. The source tensor (i.e. packed tensor) dimensions can
///     be unpacked given `inner_dims_pos` as follows.
///     - For `0 <= i < k` the following relationship holds:
///     `shape(result)[inner_dims_pos[i]] <= shape(source)[n-k+i] * shape(source)[inner_dims_pos[i]]`.
///     - For `0 <= j < n-k` and `j` not in `inner_dims_pos` the following relationship holds:
///     `shape(result)[j] = shape(source)[j]`.
/// 
///     `outer_dims_perm` (optional) specifies a permutation for the outer
///     dimensions. If specified, it must have `n - k` elements. If specified, this
///     permutation is applied before combining any dimensions.
/// 
///     Note, the unpack operation may drop any padding introduced by the pack
///     operation and hence the following holds
///     `NumElementsOf(source) >= NumElementsOf(result)`.
/// 
///     Examples:
/// 
///     ```mlir
///     // NCnc to NC:
///     %0 = linalg.unpack %source inner_dims_pos = [0, 1] inner_tiles = [8, 32]
///         into %dest : tensor<16x8 x 8x32 xf32> -> tensor<128x256xf32>
///     //                      \  /   \  /
///     //          Outer Dims: 16x8  Inner Dims: 8x32
/// 
///     // CK to KCck:
///     %0 = linalg.unpack %source outer_dims_perm = [1, 0] inner_dims_pos = [0, 1]
///         inner_tiles = [8, 32]
///         into %dest : tensor<8x16 x 8x32 xf32> -> tensor<128x256xf32>
///     //                      \  /   \  /
///     //          Outer Dims: 8x16  Inner Dims: 8x32
/// 
///     // CHW to CHWhw:
///     %0 = linalg.unpack %source inner_dims_pos = [2, 1] inner_tiles = [4, 2]
///         into %dest : tensor<3x10x6 x 4x2 xf32> -> tensor<3x20x24xf32>
///     //                       \  /    \ /
///     //          Outer Dims: 3x10x6  Inner Dims: 4x2
/// 
///     // HCW to HCWhw
///     %0 = linalg.unpack %source inner_dims_pos = [2, 0] inner_tiles = [4, 2]
///         into %dest : tensor<9x3x8 x 4x2 xf32> -> tensor<18x3x32xf32>
///     //                       \  /   \ /
///     //          Outer Dims: 9x3x8   Inner Dims: 4x2
///     ```
class UnPackOp;

} // namespace mlir::linalg
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::linalg {


//===----------------------------------------------------------------------===//
// ::mlir::linalg::PackOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PackOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_dims_posTy = ::mlir::DenseI64ArrayAttr;
    inner_dims_posTy inner_dims_pos;

    auto getInnerDimsPos() const {
      auto &propStorage = this->inner_dims_pos;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setInnerDimsPos(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->inner_dims_pos = propValue;
    }
    using outer_dims_permTy = ::mlir::DenseI64ArrayAttr;
    outer_dims_permTy outer_dims_perm;

    auto getOuterDimsPerm() const {
      auto &propStorage = this->outer_dims_perm;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setOuterDimsPerm(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->outer_dims_perm = propValue;
    }
    using static_inner_tilesTy = ::mlir::DenseI64ArrayAttr;
    static_inner_tilesTy static_inner_tiles;

    auto getStaticInnerTiles() const {
      auto &propStorage = this->static_inner_tiles;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticInnerTiles(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_inner_tiles = propValue;
    }
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
        rhs.inner_dims_pos == this->inner_dims_pos &&
        rhs.outer_dims_perm == this->outer_dims_perm &&
        rhs.static_inner_tiles == this->static_inner_tiles &&
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
  PackOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("linalg.pack", odsAttrs.getContext());
  }

  PackOpGenericAdaptorBase(PackOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getOuterDimsPermAttr();
  ::llvm::ArrayRef<int64_t> getOuterDimsPerm();
  ::mlir::DenseI64ArrayAttr getInnerDimsPosAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().inner_dims_pos);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getInnerDimsPos();
  ::mlir::DenseI64ArrayAttr getStaticInnerTilesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_inner_tiles);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticInnerTiles();
};

} // namespace detail
template <typename RangeT>
class PackOpGenericAdaptor : public detail::PackOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PackOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_padding_value = 2;
  static constexpr int odsIndex_inner_tiles = 3;
public:
  PackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PackOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : PackOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PackOpGenericAdaptor(RangeT values, const PackOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PackOp, typename = std::enable_if_t<std::is_same_v<LateInst, PackOp>>>
  PackOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getPaddingValue() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getInnerTiles() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PackOpAdaptor : public PackOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PackOpGenericAdaptor::PackOpGenericAdaptor;
  PackOpAdaptor(PackOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PackOp : public ::mlir::Op<PackOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::linalg::RelayoutOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PackOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PackOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_padding_value = 2;
  static constexpr int odsIndex_inner_tiles = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<PackOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<PackOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<PackOp>::getDefaultDialect;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<PackOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<PackOp>::reifyDimOfResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_dims_pos"), ::llvm::StringRef("outer_dims_perm"), ::llvm::StringRef("static_inner_tiles"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerDimsPosAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerDimsPosAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOuterDimsPermAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getOuterDimsPermAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStaticInnerTilesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStaticInnerTilesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("linalg.pack");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getPaddingValue() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getInnerTiles() {
    return getODSOperands(3);
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getPaddingValueMutable();
  ::mlir::MutableOperandRange getInnerTilesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::RankedTensorType>() : ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*results.begin());
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
  ::mlir::DenseI64ArrayAttr getOuterDimsPermAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().outer_dims_perm);
  }

  ::llvm::ArrayRef<int64_t> getOuterDimsPerm();
  ::mlir::DenseI64ArrayAttr getInnerDimsPosAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().inner_dims_pos);
  }

  ::llvm::ArrayRef<int64_t> getInnerDimsPos();
  ::mlir::DenseI64ArrayAttr getStaticInnerTilesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_inner_tiles);
  }

  ::llvm::ArrayRef<int64_t> getStaticInnerTiles();
  void setOuterDimsPermAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().outer_dims_perm = attr;
  }

  void setOuterDimsPerm(::std::optional<::llvm::ArrayRef<int64_t>> attrValue);
  void setInnerDimsPosAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().inner_dims_pos = attr;
  }

  void setInnerDimsPos(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticInnerTilesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_inner_tiles = attr;
  }

  void setStaticInnerTiles(::llvm::ArrayRef<int64_t> attrValue);
  ::mlir::Attribute removeOuterDimsPermAttr() {
      auto attr = getProperties().outer_dims_perm;
      getProperties().outer_dims_perm = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value dest, ArrayRef<int64_t> innerDimsPos, ArrayRef<OpFoldResult> innerTiles, std::optional<Value> paddingValue = std::nullopt, ArrayRef<int64_t> outerDimsPerm = {});
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ArrayRef<int64_t> innerDimsPos, ArrayRef<OpFoldResult> innerTiles, std::optional<Value> paddingValue = std::nullopt, ArrayRef<int64_t> outerDimsPerm = {});
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ArrayRef<int64_t> innerDimsPos, ArrayRef<OpFoldResult> innerTiles, std::optional<Value> paddingValue = std::nullopt, ArrayRef<int64_t> outerDimsPerm = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::Value padding_value, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(PackOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  size_t getSourceRank() { return getSourceType().getRank(); };
  size_t getDestRank() { return getDestType().getRank(); };
  ShapedType getSourceType() {
    return ::llvm::cast<ShapedType>(getSource().getType()); };
  ShapedType getDestType() {
    return ::llvm::cast<ShapedType>(getDest().getType()); };

  MutableOperandRange getDpsInitsMutable() { return getDestMutable(); }

  /// Interface method for ConditionallySpeculatable.
  Speculation::Speculatability getSpeculatability();

  /// Return a mapping from positions `inner_dims_pos` to their
  /// tile factors.
  DenseMap<int64_t, OpFoldResult> getDimAndTileMapping();

  /// Return the tile sizes as OpFoldResult(s). Note, for Ops that simply
  /// define constants (e.g. `arith.constant`), this method returns
  /// Value/result of the Op (as opposed to the corresponding constant
  /// Attribute). E.g., for:
  ///   %size = arith.constant 1 : i32
  /// it will return %size, not 1. This is intended - replacing an SSA value
  /// with a constant attribute would require updating the corresponding dim
  /// from dynamic to static.
  SmallVector<OpFoldResult> getMixedTiles();

  /// Return the tile sizes as `int64_t`. If a tile size is dynamic
  /// a sentinel `kDynamic` is introduced at that position in
  /// the returned vector.
  SmallVector<int64_t> getStaticTiles();

  /// Retrieve all outer dims for this Pack/UnPack Op, i.e. all the leading
  /// dims excluding the trailing dims corresponding to `innerTiles`. Note
  /// that this will include both tiled and non-tiled dimensions. The order
  /// of the output dimensions is consistent with the shape of the packed
  /// tensor.
  ArrayRef<int64_t> getAllOuterDims();

  /// Similar to `getAllOuterDims`, but only retrieve the outer dims that
  /// have been tiled. Also, the order of the output dimensions is consistent
  /// with `inner_dims_pos` rather than the packed tensor.
  SmallVector<int64_t> getTiledOuterDims();

  // Method to get the shape of the result as `SmallVector<OpFoldResult>`.
  // This is a static method to allow getting the shape of the destination
  // expected while creating a `pack` op.
  static SmallVector<OpFoldResult> getResultShape(OpBuilder &builder,
      Location loc, ArrayRef<OpFoldResult> sourceDims,
      ArrayRef<OpFoldResult> innerTileDims, ArrayRef<int64_t> innerDimsPos,
      ArrayRef<int64_t> outerDimsPerm = {});

  // Method to get the `RankedTensorType` of the result based on the inner
  // tiles, position of the inner tiles (innerDimsPos)  and interchange vector
  // of outer loops (outerDimsPerm).
  static RankedTensorType inferPackedTensorType(RankedTensorType sourceType,
      ArrayRef<int64_t> innerTileSizes, ArrayRef<int64_t> innerDimsPos,
      ArrayRef<int64_t> outerDimsPerm = {});

  // Method to get the `MemRefType` of the result based on the inner
  // tiles, position of the inner tiles (innerDimsPos)  and interchange vector
  // of outer loops (outerDimsPerm).
  static MemRefType inferPackedMemRefType(MemRefType sourceType,
      ArrayRef<int64_t> innerTileSizes, ArrayRef<int64_t> innerDimsPos,
      ArrayRef<int64_t> outerDimsPerm = {});

  // Returns the shape of the packed type. It is a shared helper that helps
  // type inference methods in a way that ensures that they agree on which 
  // dimensions are dynamic.
  static SmallVector<int64_t> inferPackedShape(ArrayRef<int64_t> inputShape,
      ArrayRef<int64_t> innerTileSizes, ArrayRef<int64_t> innerDimsPos,
      ArrayRef<int64_t> outerDimsPerm = {});

  // Returns true if we have enough static information to catch undefined
  // behavior when the tile size does not divide perfectly the dimension of
  // the input tensor. Detecting UB requires that the input size and either
  // corresponding tile or output size are static.
  static bool requirePaddingValue(ArrayRef<int64_t> inputShape,
                                  ArrayRef<int64_t> innerDimsPos,
                                  ArrayRef<int64_t> outputShape,
                                  ArrayRef<int64_t> outerDimsPerm,
                                  ArrayRef<OpFoldResult> innerTiles);

  // Same as above function but here dynamic dimensions are assumed
  // to require padding.
  static bool requirePaddingValueStrict(ArrayRef<int64_t> inputShape,
                                        ArrayRef<int64_t> innerDimsPos,
                                        ArrayRef<int64_t> outputShape,
                                        ArrayRef<int64_t> outerDimsPerm,
                                        ArrayRef<OpFoldResult> innerTiles);

  static Value createDestinationTensor(OpBuilder &b, Location loc,
      Value source, ArrayRef<OpFoldResult> innerTileSizes,
      ArrayRef<int64_t> innerDimsPos, ArrayRef<int64_t> outerDimsPerm);

  /// Build and return a new PackOp that is a clone of the current PackOp with
  /// (innerDimsPos, innerTiles) (resp. outerDimsPerm) are permuted by
  /// innerPermutation (resp. outerPermutation).
  /// A new `tensor.empty` of the proper shape is built in the process.
  /// Asserts that:
  ///   - At least one of innerPermutation or outerPermutation is non-empty.
  ///   - If not empty, innerPermutation is a valid permutation of size
  ///     matching innerDimPos.
  ///   - If not empty, outerPermutation is a valid permutation of size
  ///     matching outerDimsPerm.
  PackOp createTransposedClone(OpBuilder &b,
                               Location loc,
                               ArrayRef<int64_t> innerPermutation,
                               ArrayRef<int64_t> outerPermutation);

  /// Check if this PackOp is like a simple pad operation.
  /// In other words, this operation:
  /// 1. adds useless dimensions (dimension of size 1),
  /// 2. pads the other ones, and
  /// 3. doesn't shuffle the dimensions
  bool isLikePad();
};

} // namespace mlir::linalg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::PackOp)

namespace mlir::linalg {


//===----------------------------------------------------------------------===//
// ::mlir::linalg::UnPackOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnPackOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_dims_posTy = ::mlir::DenseI64ArrayAttr;
    inner_dims_posTy inner_dims_pos;

    auto getInnerDimsPos() const {
      auto &propStorage = this->inner_dims_pos;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setInnerDimsPos(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->inner_dims_pos = propValue;
    }
    using outer_dims_permTy = ::mlir::DenseI64ArrayAttr;
    outer_dims_permTy outer_dims_perm;

    auto getOuterDimsPerm() const {
      auto &propStorage = this->outer_dims_perm;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setOuterDimsPerm(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->outer_dims_perm = propValue;
    }
    using static_inner_tilesTy = ::mlir::DenseI64ArrayAttr;
    static_inner_tilesTy static_inner_tiles;

    auto getStaticInnerTiles() const {
      auto &propStorage = this->static_inner_tiles;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticInnerTiles(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_inner_tiles = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inner_dims_pos == this->inner_dims_pos &&
        rhs.outer_dims_perm == this->outer_dims_perm &&
        rhs.static_inner_tiles == this->static_inner_tiles &&
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
  UnPackOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("linalg.unpack", odsAttrs.getContext());
  }

  UnPackOpGenericAdaptorBase(UnPackOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getOuterDimsPermAttr();
  ::llvm::ArrayRef<int64_t> getOuterDimsPerm();
  ::mlir::DenseI64ArrayAttr getInnerDimsPosAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().inner_dims_pos);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getInnerDimsPos();
  ::mlir::DenseI64ArrayAttr getStaticInnerTilesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_inner_tiles);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticInnerTiles();
};

} // namespace detail
template <typename RangeT>
class UnPackOpGenericAdaptor : public detail::UnPackOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnPackOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_inner_tiles = 2;
public:
  UnPackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnPackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : UnPackOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnPackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnPackOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnPackOpGenericAdaptor(RangeT values, const UnPackOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnPackOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnPackOp>>>
  UnPackOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getInnerTiles() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UnPackOpAdaptor : public UnPackOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnPackOpGenericAdaptor::UnPackOpGenericAdaptor;
  UnPackOpAdaptor(UnPackOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnPackOp : public ::mlir::Op<UnPackOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::linalg::RelayoutOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnPackOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnPackOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_inner_tiles = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<UnPackOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<UnPackOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<UnPackOp>::getDefaultDialect;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<UnPackOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<UnPackOp>::reifyDimOfResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_dims_pos"), ::llvm::StringRef("outer_dims_perm"), ::llvm::StringRef("static_inner_tiles")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerDimsPosAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerDimsPosAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOuterDimsPermAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getOuterDimsPermAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStaticInnerTilesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStaticInnerTilesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("linalg.unpack");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getInnerTiles() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getInnerTilesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::RankedTensorType>() : ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*results.begin());
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
  ::mlir::DenseI64ArrayAttr getOuterDimsPermAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().outer_dims_perm);
  }

  ::llvm::ArrayRef<int64_t> getOuterDimsPerm();
  ::mlir::DenseI64ArrayAttr getInnerDimsPosAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().inner_dims_pos);
  }

  ::llvm::ArrayRef<int64_t> getInnerDimsPos();
  ::mlir::DenseI64ArrayAttr getStaticInnerTilesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_inner_tiles);
  }

  ::llvm::ArrayRef<int64_t> getStaticInnerTiles();
  void setOuterDimsPermAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().outer_dims_perm = attr;
  }

  void setOuterDimsPerm(::std::optional<::llvm::ArrayRef<int64_t>> attrValue);
  void setInnerDimsPosAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().inner_dims_pos = attr;
  }

  void setInnerDimsPos(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticInnerTilesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_inner_tiles = attr;
  }

  void setStaticInnerTiles(::llvm::ArrayRef<int64_t> attrValue);
  ::mlir::Attribute removeOuterDimsPermAttr() {
      auto attr = getProperties().outer_dims_perm;
      getProperties().outer_dims_perm = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value dest, ArrayRef<int64_t> innerDimsPos, ArrayRef<OpFoldResult> innerTiles, ArrayRef<int64_t> outerDimsPerm = {});
  static UnPackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ArrayRef<int64_t> innerDimsPos, ArrayRef<OpFoldResult> innerTiles, ArrayRef<int64_t> outerDimsPerm = {});
  static UnPackOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ArrayRef<int64_t> innerDimsPos, ArrayRef<OpFoldResult> innerTiles, ArrayRef<int64_t> outerDimsPerm = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static UnPackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static UnPackOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static UnPackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static UnPackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::mlir::DenseI64ArrayAttr outer_dims_perm, ::mlir::DenseI64ArrayAttr inner_dims_pos, ::mlir::ValueRange inner_tiles, ::mlir::DenseI64ArrayAttr static_inner_tiles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static UnPackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static UnPackOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static UnPackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static UnPackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, /*optional*/::llvm::ArrayRef<int64_t> outer_dims_perm, ::llvm::ArrayRef<int64_t> inner_dims_pos, ::mlir::ValueRange inner_tiles, ::llvm::ArrayRef<int64_t> static_inner_tiles);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnPackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnPackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnPackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnPackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(UnPackOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  size_t getSourceRank() { return getSourceType().getRank(); };
  size_t getDestRank() { return getDestType().getRank(); };
  ShapedType getSourceType() {
    return ::llvm::cast<ShapedType>(getSource().getType()); };
  ShapedType getDestType() {
    return ::llvm::cast<ShapedType>(getDest().getType()); };

  MutableOperandRange getDpsInitsMutable() { return getDestMutable(); }

  /// Interface method for ConditionallySpeculatable.
  Speculation::Speculatability getSpeculatability();

  /// Return a mapping from positions `inner_dims_pos` to their
  /// tile factors.
  DenseMap<int64_t, OpFoldResult> getDimAndTileMapping();

  /// Return the tile sizes as OpFoldResult(s). Note, for Ops that simply
  /// define constants (e.g. `arith.constant`), this method returns
  /// Value/result of the Op (as opposed to the corresponding constant
  /// Attribute). E.g., for:
  ///   %size = arith.constant 1 : i32
  /// it will return %size, not 1. This is intended - replacing an SSA value
  /// with a constant attribute would require updating the corresponding dim
  /// from dynamic to static.
  SmallVector<OpFoldResult> getMixedTiles();

  /// Return the tile sizes as `int64_t`. If a tile size is dynamic
  /// a sentinel `kDynamic` is introduced at that position in
  /// the returned vector.
  SmallVector<int64_t> getStaticTiles();

  /// Retrieve all outer dims for this Pack/UnPack Op, i.e. all the leading
  /// dims excluding the trailing dims corresponding to `innerTiles`. Note
  /// that this will include both tiled and non-tiled dimensions. The order
  /// of the output dimensions is consistent with the shape of the packed
  /// tensor.
  ArrayRef<int64_t> getAllOuterDims();

  /// Similar to `getAllOuterDims`, but only retrieve the outer dims that
  /// have been tiled. Also, the order of the output dimensions is consistent
  /// with `inner_dims_pos` rather than the packed tensor.
  SmallVector<int64_t> getTiledOuterDims();

  static Value createDestinationTensor(OpBuilder &b, Location loc,
      Value source, ArrayRef<OpFoldResult> innerTileSizes,
      ArrayRef<int64_t> innerDimsPos, ArrayRef<int64_t> outerDimsPerm);

  /// Build and return a new UnPackOp that is a clone of the current UnPackOp
  /// with (innerDimsPos, innerTiles) (resp. outerDimsPerm) are permuted by
  /// innerPermutation (resp. outerPermutation).
  /// Asserts that:
  ///   - At least one of innerPermutation or outerPermutation is non-empty.
  ///   - If not empty, innerPermutation is a valid permutation of size
  ///     matching innerDimPos.
  ///   - If not empty, outerPermutation is a valid permutation of size
  ///     matching outerDimsPerm.
  UnPackOp createTransposedClone(OpBuilder &b,
                                 Location loc,
                                 Value transposedSource,
                                 ArrayRef<int64_t> innerPermutation,
                                 ArrayRef<int64_t> outerPermutation);

  /// Returns true if it is statically known that the `sliceOp` result shape
  /// is compatible with the `unPackOp`. I.e., it does not drop any tile.
  bool canFoldSliceOp(tensor::ExtractSliceOp sliceOp);

  /// Check if this UnPackOp is like a simple unpad operation.
  /// In other words, this operation:
  /// 1. drops useless dimensions (dimension of size 1), and
  /// 2. reduces dimensions in place (i.e., no transpose.)
  bool isLikeUnPad();
};

} // namespace mlir::linalg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::UnPackOp)


#endif // GET_OP_CLASSES

