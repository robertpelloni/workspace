/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LinalgOps.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::linalg {

/// linalg index operation
/// The `linalg.index` operation returns the iteration index of the immediately
///     enclosing linalg structured operation for the iteration dimension `dim`. The
///     `dim` attribute specifies the position of the accessed dimension in the
///     indexing map domain.
/// 
///     Example:
/// 
///     ```mlir
///     #map = affine_map<(i, j) -> (i, j)>
///     linalg.generic {indexing_maps = [#map, #map],
///                     iterator_types = ["parallel", "parallel"]}
///       outs(%I, %J : memref<?x?xindex>, memref<?x?xindex>) {
///       ^bb0(%arg0 : index, %arg1 : index):
///       // Access the outer iteration dimension i
///       %i = linalg.index 0 : index
///       // Access the inner iteration dimension j
///       %j = linalg.index 1 : index
///       linalg.yield %i, %j : index, index
///     }
///     ```
/// 
///     This may lower to IR resembling:
/// 
///     ```mlir
///     %0 = dim %I, %c0 : memref<?x?xindex>
///     %1 = dim %I, %c1 : memref<?x?xindex>
///     scf.for %i = %c0 to %0 step %c1 {
///       scf.for %j = %c0 to %1 step %c1 {
///         store %i, %I[%i, %j] : memref<?x?xindex>
///         store %j, %J[%i, %j] : memref<?x?xindex>
///       }
///     }
///     ```
class IndexOp;

} // namespace mlir::linalg
namespace mlir::linalg {

/// Softmax operator
/// linalg.softmax computes a numerically stable version of softmax.
/// 
///     For a given input tensor and a specified dimension `d`, compute:
///       1. the max `m` along that dimension `d`
///       2. f(x) = exp(x - m)
///       3. sum f(x) along dimension d to get l(x).
///       4. compute the final result f(x) / l(x).
/// 
///     This is an aggregate linalg operation that further reduces to a small DAG of
///     structured operations.
/// 
///     Warning: Regarding the tiling capabilities, the implementation doesn't
///     check that the provided dimensions make sense. This is the responsability
///     of the transformation calling the tiling to ensure that the provided
///     sizes for each dimension make sense with respect to the semantic of
///     softmax.
class SoftmaxOp;

} // namespace mlir::linalg
namespace mlir::linalg {

/// Winograd filter transform operator
/// Winograd Conv2D algorithm will convert linalg Conv2D operator into batched
///     matrix multiply. Before the matrix multiply, it will convert filter and
///     input into a format suitable for batched matrix multiply. After the matrix
///     multiply, it will convert output to the final result tensor.
/// 
///     The algorithm F(m x m, r x r) is
/// 
///     Y = A^T x [(G x g x G^T) @ (B^T x d x B)] x A
/// 
///     The size of output Y is m x m. The size of filter g is r x r. The size of
///     input d is (m + r - 1) x (m + r - 1). A^T, A, G^T, G, B^T, and B are
///     transformation matrices.
/// 
///     This operator is defined to represent the high level concept of filter
///     transformation (G x g x G^T) in the Winograd Conv2D algorithm.
class WinogradFilterTransformOp;

} // namespace mlir::linalg
namespace mlir::linalg {

/// Winograd input transform operator
/// Winograd Conv2D algorithm will convert linalg Conv2D operator into batched
///     matrix multiply. Before the matrix multiply, it will convert filter and
///     input into a format suitable for batched matrix multiply. After the matrix
///     multiply, it will convert output to the final result tensor.
/// 
///     The algorithm F(m x m, r x r) is
/// 
///     Y = A^T x [(G x g x G^T) @ (B^T x d x B)] x A
/// 
///     The size of output Y is m x m. The size of filter g is r x r. The size of
///     input d is (m + r - 1) x (m + r - 1). A^T, A, G^T, G, B^T, and B are
///     transformation matrices.
/// 
///     This operator is defined to represent the high level concept of input
///     transformation (B^T x d x B) in the Winograd Conv2D algorithm.
class WinogradInputTransformOp;

} // namespace mlir::linalg
namespace mlir::linalg {

/// Winograd output transform operator
/// Winograd Conv2D algorithm will convert linalg Conv2D operator into batched
///     matrix multiply. Before the matrix multiply, it will convert filter and
///     input into a format suitable for batched matrix multiply. After the matrix
///     multiply, it will convert output to the final result tensor.
/// 
///     The algorithm F(m x m, r x r) is
/// 
///     Y = A^T x [(G x g x G^T) @ (B^T x d x B)] x A
/// 
///     The size of output Y is m x m. The size of filter g is r x r. The size of
///     input d is (m + r - 1) x (m + r - 1). A^T, A, G^T, G, B^T, and B are
///     transformation matrices.
/// 
///     This operator is defined to represent the high level concept of output
///     transformation (A^T x y x A) in the Winograd Conv2D algorithm.
class WinogradOutputTransformOp;

} // namespace mlir::linalg
namespace mlir::linalg {

/// Linalg yield operation
/// `linalg.yield` is a special terminator operation for blocks inside regions
///     in `linalg` generic ops. It returns values to the immediately enclosing
///     `linalg` generic op.
/// 
///     Example:
/// 
///     ```mlir
///     linalg.yield %f0, %f1 : f32, f32
///     ```
class YieldOp;

} // namespace mlir::linalg
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::linalg {


//===----------------------------------------------------------------------===//
// ::mlir::linalg::IndexOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IndexOpGenericAdaptorBase {
public:
  struct Properties {
    using dimTy = ::mlir::IntegerAttr;
    dimTy dim;

    auto getDim() const {
      auto &propStorage = this->dim;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setDim(const ::mlir::IntegerAttr &propValue) {
      this->dim = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dim == this->dim &&
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
  IndexOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("linalg.index", odsAttrs.getContext());
  }

  IndexOpGenericAdaptorBase(IndexOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getDimAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().dim);
    return attr;
  }

  uint64_t getDim();
};

} // namespace detail
template <typename RangeT>
class IndexOpGenericAdaptor : public detail::IndexOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IndexOpGenericAdaptorBase;
public:
  IndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IndexOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IndexOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IndexOpGenericAdaptor(RangeT values, const IndexOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IndexOp, typename = std::enable_if_t<std::is_same_v<LateInst, IndexOp>>>
  IndexOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class IndexOpAdaptor : public IndexOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IndexOpGenericAdaptor::IndexOpGenericAdaptor;
  IndexOpAdaptor(IndexOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IndexOp : public ::mlir::Op<IndexOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IndexOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IndexOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dim")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("linalg.index");
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

  ::mlir::TypedValue<::mlir::IndexType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getDimAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().dim);
  }

  uint64_t getDim();
  void setDimAttr(::mlir::IntegerAttr attr) {
    getProperties().dim = attr;
  }

  void setDim(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::IntegerAttr dim);
  static IndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::IntegerAttr dim);
  static IndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::IntegerAttr dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::IntegerAttr dim);
  static IndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::IntegerAttr dim);
  static IndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::IntegerAttr dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr dim);
  static IndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr dim);
  static IndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, uint64_t dim);
  static IndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, uint64_t dim);
  static IndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, uint64_t dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint64_t dim);
  static IndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, uint64_t dim);
  static IndexOp create(::mlir::ImplicitLocOpBuilder &builder, uint64_t dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint64_t dim);
  static IndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint64_t dim);
  static IndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint64_t dim);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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

} // namespace mlir::linalg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::IndexOp)

namespace mlir::linalg {


//===----------------------------------------------------------------------===//
// ::mlir::linalg::SoftmaxOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SoftmaxOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::IntegerAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setDimension(const ::mlir::IntegerAttr &propValue) {
      this->dimension = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
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
  SoftmaxOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("linalg.softmax", odsAttrs.getContext());
  }

  SoftmaxOpGenericAdaptorBase(SoftmaxOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().dimension);
    return attr;
  }

  uint64_t getDimension();
};

} // namespace detail
template <typename RangeT>
class SoftmaxOpGenericAdaptor : public detail::SoftmaxOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SoftmaxOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_output = 1;
public:
  SoftmaxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SoftmaxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SoftmaxOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SoftmaxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SoftmaxOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SoftmaxOpGenericAdaptor(RangeT values, const SoftmaxOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SoftmaxOp, typename = std::enable_if_t<std::is_same_v<LateInst, SoftmaxOp>>>
  SoftmaxOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getOutput() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SoftmaxOpAdaptor : public SoftmaxOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SoftmaxOpGenericAdaptor::SoftmaxOpGenericAdaptor;
  SoftmaxOpAdaptor(SoftmaxOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SoftmaxOp : public ::mlir::Op<SoftmaxOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait, ::mlir::linalg::AggregatedOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::TilingInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SoftmaxOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SoftmaxOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_output = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<SoftmaxOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<SoftmaxOp>::reifyDimOfResult;
  using ::mlir::TilingInterface::Trait<SoftmaxOp>::generateResultTileValue;
  using ::mlir::TilingInterface::Trait<SoftmaxOp>::getTiledImplementationFromOperandTiles;
  using ::mlir::TilingInterface::Trait<SoftmaxOp>::getIterationDomainTileFromOperandTiles;
  using ::mlir::TilingInterface::Trait<SoftmaxOp>::getIterationDomainTileFromResultTile;
  using ::mlir::TilingInterface::Trait<SoftmaxOp>::generateScalarImplementation;
  using ::mlir::TilingInterface::Trait<SoftmaxOp>::isOpFusableWithConsumerSlice;
  using ::mlir::TilingInterface::Trait<SoftmaxOp>::isOpFusableWithProducerSlices;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("linalg.softmax");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getOutputMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResult() {
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
  ::mlir::IntegerAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().dimension);
  }

  uint64_t getDimension();
  void setDimensionAttr(::mlir::IntegerAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::Value input, ::mlir::Value output, ::mlir::IntegerAttr dimension);
  static SoftmaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::Value input, ::mlir::Value output, ::mlir::IntegerAttr dimension);
  static SoftmaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::Value input, ::mlir::Value output, ::mlir::IntegerAttr dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::Value input, ::mlir::Value output, uint64_t dimension);
  static SoftmaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::Value input, ::mlir::Value output, uint64_t dimension);
  static SoftmaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::Value input, ::mlir::Value output, uint64_t dimension);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SoftmaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SoftmaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SoftmaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SoftmaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  FailureOr<SmallVector<Value>> decomposeOperation(OpBuilder &b);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  ::mlir::SmallVector<::mlir::utils::IteratorType> getLoopIteratorTypes();
  ::mlir::SmallVector<::mlir::Range> getIterationDomain(::mlir::OpBuilder &b);
  ::mlir::FailureOr<::mlir::TilingResult> getTiledImplementation(::mlir::OpBuilder &b, ::mlir::ArrayRef<::mlir::OpFoldResult>  offsets, ::mlir::ArrayRef<::mlir::OpFoldResult>  sizes);
  ::llvm::LogicalResult getResultTilePosition(::mlir::OpBuilder &b, unsigned resultNumber, ::mlir::ArrayRef<::mlir::OpFoldResult>  offsets, ::mlir::ArrayRef<::mlir::OpFoldResult>  sizes, ::mlir::SmallVector<::mlir::OpFoldResult> &resultOffsets, ::mlir::SmallVector<::mlir::OpFoldResult> &resultSizes);
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
  ShapedType getInputOperandType() {
    return cast<ShapedType>(getInput().getType());
  }
  ShapedType getOutputOperandType() {
    return cast<ShapedType>(getOutput().getType());
  }
  int64_t getInputOperandRank() {
    return getInputOperandType().getRank();
  }
  int64_t getOutputOperandRank() {
    return getOutputOperandType().getRank();
  }
  MutableOperandRange getDpsInitsMutable() { return getOutputMutable(); }
};

} // namespace mlir::linalg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::SoftmaxOp)

namespace mlir::linalg {


//===----------------------------------------------------------------------===//
// ::mlir::linalg::WinogradFilterTransformOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WinogradFilterTransformOpGenericAdaptorBase {
public:
  struct Properties {
    using fmrTy = mlir::linalg::WinogradConv2DFmrAttr;
    fmrTy fmr;

    auto getFmr() const {
      auto &propStorage = this->fmr;
      return ::llvm::cast<mlir::linalg::WinogradConv2DFmrAttr>(propStorage);
    }
    void setFmr(const mlir::linalg::WinogradConv2DFmrAttr &propValue) {
      this->fmr = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fmr == this->fmr &&
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
  WinogradFilterTransformOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("linalg.winograd_filter_transform", odsAttrs.getContext());
  }

  WinogradFilterTransformOpGenericAdaptorBase(WinogradFilterTransformOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  mlir::linalg::WinogradConv2DFmrAttr getFmrAttr() {
    auto attr = ::llvm::cast<mlir::linalg::WinogradConv2DFmrAttr>(getProperties().fmr);
    return attr;
  }

  mlir::linalg::WinogradConv2DFmr getFmr();
};

} // namespace detail
template <typename RangeT>
class WinogradFilterTransformOpGenericAdaptor : public detail::WinogradFilterTransformOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WinogradFilterTransformOpGenericAdaptorBase;
  static constexpr int odsIndex_filter = 0;
  static constexpr int odsIndex_output = 1;
public:
  WinogradFilterTransformOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WinogradFilterTransformOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WinogradFilterTransformOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WinogradFilterTransformOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WinogradFilterTransformOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WinogradFilterTransformOpGenericAdaptor(RangeT values, const WinogradFilterTransformOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WinogradFilterTransformOp, typename = std::enable_if_t<std::is_same_v<LateInst, WinogradFilterTransformOp>>>
  WinogradFilterTransformOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getFilter() {
    return (*getODSOperands(0).begin());
  }

  ValueT getOutput() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WinogradFilterTransformOpAdaptor : public WinogradFilterTransformOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WinogradFilterTransformOpGenericAdaptor::WinogradFilterTransformOpGenericAdaptor;
  WinogradFilterTransformOpAdaptor(WinogradFilterTransformOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WinogradFilterTransformOp : public ::mlir::Op<WinogradFilterTransformOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::TilingInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WinogradFilterTransformOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WinogradFilterTransformOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_filter = 0;
  static constexpr int odsIndex_output = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::TilingInterface::Trait<WinogradFilterTransformOp>::generateResultTileValue;
  using ::mlir::TilingInterface::Trait<WinogradFilterTransformOp>::getTiledImplementationFromOperandTiles;
  using ::mlir::TilingInterface::Trait<WinogradFilterTransformOp>::getIterationDomainTileFromOperandTiles;
  using ::mlir::TilingInterface::Trait<WinogradFilterTransformOp>::getIterationDomainTileFromResultTile;
  using ::mlir::TilingInterface::Trait<WinogradFilterTransformOp>::generateScalarImplementation;
  using ::mlir::TilingInterface::Trait<WinogradFilterTransformOp>::isOpFusableWithConsumerSlice;
  using ::mlir::TilingInterface::Trait<WinogradFilterTransformOp>::isOpFusableWithProducerSlices;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fmr")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFmrAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFmrAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("linalg.winograd_filter_transform");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getFilter() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getFilterMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getOutputMutable() {
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

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
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
  mlir::linalg::WinogradConv2DFmrAttr getFmrAttr() {
    return ::llvm::cast<mlir::linalg::WinogradConv2DFmrAttr>(getProperties().fmr);
  }

  mlir::linalg::WinogradConv2DFmr getFmr();
  void setFmrAttr(mlir::linalg::WinogradConv2DFmrAttr attr) {
    getProperties().fmr = attr;
  }

  void setFmr(mlir::linalg::WinogradConv2DFmr attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradFilterTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradFilterTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradFilterTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradFilterTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradFilterTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradFilterTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradFilterTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradFilterTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value filter, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WinogradFilterTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WinogradFilterTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WinogradFilterTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WinogradFilterTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::SmallVector<::mlir::utils::IteratorType> getLoopIteratorTypes();
  ::mlir::SmallVector<::mlir::Range> getIterationDomain(::mlir::OpBuilder &b);
  ::mlir::FailureOr<::mlir::TilingResult> getTiledImplementation(::mlir::OpBuilder &b, ::mlir::ArrayRef<::mlir::OpFoldResult>  offsets, ::mlir::ArrayRef<::mlir::OpFoldResult>  sizes);
  ::llvm::LogicalResult getResultTilePosition(::mlir::OpBuilder &b, unsigned resultNumber, ::mlir::ArrayRef<::mlir::OpFoldResult>  offsets, ::mlir::ArrayRef<::mlir::OpFoldResult>  sizes, ::mlir::SmallVector<::mlir::OpFoldResult> &resultOffsets, ::mlir::SmallVector<::mlir::OpFoldResult> &resultSizes);
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
  ShapedType getFilterOperandType() {
    return cast<ShapedType>(getFilter().getType());
  }
  ShapedType getOutputOperandType() {
    return cast<ShapedType>(getOutput().getType());
  }
  int64_t getFilterOperandRank() {
    return getFilterOperandType().getRank();
  }
  int64_t getOutputOperandRank() {
    return getOutputOperandType().getRank();
  }
  int64_t getFilterFDim() {
    return 0;
  }
  int64_t getFilterHDim() {
    return 1;
  }
  int64_t getFilterWDim() {
    return 2;
  }
  int64_t getFilterCDim() {
    return 3;
  }
  MutableOperandRange getDpsInitsMutable() { return getOutputMutable(); }
};

} // namespace mlir::linalg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::WinogradFilterTransformOp)

namespace mlir::linalg {


//===----------------------------------------------------------------------===//
// ::mlir::linalg::WinogradInputTransformOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WinogradInputTransformOpGenericAdaptorBase {
public:
  struct Properties {
    using fmrTy = mlir::linalg::WinogradConv2DFmrAttr;
    fmrTy fmr;

    auto getFmr() const {
      auto &propStorage = this->fmr;
      return ::llvm::cast<mlir::linalg::WinogradConv2DFmrAttr>(propStorage);
    }
    void setFmr(const mlir::linalg::WinogradConv2DFmrAttr &propValue) {
      this->fmr = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fmr == this->fmr &&
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
  WinogradInputTransformOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("linalg.winograd_input_transform", odsAttrs.getContext());
  }

  WinogradInputTransformOpGenericAdaptorBase(WinogradInputTransformOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  mlir::linalg::WinogradConv2DFmrAttr getFmrAttr() {
    auto attr = ::llvm::cast<mlir::linalg::WinogradConv2DFmrAttr>(getProperties().fmr);
    return attr;
  }

  mlir::linalg::WinogradConv2DFmr getFmr();
};

} // namespace detail
template <typename RangeT>
class WinogradInputTransformOpGenericAdaptor : public detail::WinogradInputTransformOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WinogradInputTransformOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_output = 1;
public:
  WinogradInputTransformOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WinogradInputTransformOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WinogradInputTransformOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WinogradInputTransformOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WinogradInputTransformOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WinogradInputTransformOpGenericAdaptor(RangeT values, const WinogradInputTransformOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WinogradInputTransformOp, typename = std::enable_if_t<std::is_same_v<LateInst, WinogradInputTransformOp>>>
  WinogradInputTransformOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getOutput() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WinogradInputTransformOpAdaptor : public WinogradInputTransformOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WinogradInputTransformOpGenericAdaptor::WinogradInputTransformOpGenericAdaptor;
  WinogradInputTransformOpAdaptor(WinogradInputTransformOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WinogradInputTransformOp : public ::mlir::Op<WinogradInputTransformOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::TilingInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WinogradInputTransformOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WinogradInputTransformOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_output = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::TilingInterface::Trait<WinogradInputTransformOp>::generateResultTileValue;
  using ::mlir::TilingInterface::Trait<WinogradInputTransformOp>::getTiledImplementationFromOperandTiles;
  using ::mlir::TilingInterface::Trait<WinogradInputTransformOp>::getIterationDomainTileFromOperandTiles;
  using ::mlir::TilingInterface::Trait<WinogradInputTransformOp>::getIterationDomainTileFromResultTile;
  using ::mlir::TilingInterface::Trait<WinogradInputTransformOp>::generateScalarImplementation;
  using ::mlir::TilingInterface::Trait<WinogradInputTransformOp>::isOpFusableWithConsumerSlice;
  using ::mlir::TilingInterface::Trait<WinogradInputTransformOp>::isOpFusableWithProducerSlices;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fmr")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFmrAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFmrAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("linalg.winograd_input_transform");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getOutputMutable() {
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

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
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
  mlir::linalg::WinogradConv2DFmrAttr getFmrAttr() {
    return ::llvm::cast<mlir::linalg::WinogradConv2DFmrAttr>(getProperties().fmr);
  }

  mlir::linalg::WinogradConv2DFmr getFmr();
  void setFmrAttr(mlir::linalg::WinogradConv2DFmrAttr attr) {
    getProperties().fmr = attr;
  }

  void setFmr(mlir::linalg::WinogradConv2DFmr attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradInputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradInputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradInputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradInputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradInputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradInputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradInputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradInputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WinogradInputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WinogradInputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WinogradInputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WinogradInputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::SmallVector<::mlir::utils::IteratorType> getLoopIteratorTypes();
  ::mlir::SmallVector<::mlir::Range> getIterationDomain(::mlir::OpBuilder &b);
  ::mlir::FailureOr<::mlir::TilingResult> getTiledImplementation(::mlir::OpBuilder &b, ::mlir::ArrayRef<::mlir::OpFoldResult>  offsets, ::mlir::ArrayRef<::mlir::OpFoldResult>  sizes);
  ::llvm::LogicalResult getResultTilePosition(::mlir::OpBuilder &b, unsigned resultNumber, ::mlir::ArrayRef<::mlir::OpFoldResult>  offsets, ::mlir::ArrayRef<::mlir::OpFoldResult>  sizes, ::mlir::SmallVector<::mlir::OpFoldResult> &resultOffsets, ::mlir::SmallVector<::mlir::OpFoldResult> &resultSizes);
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
  ShapedType getInputOperandType() {
    return cast<ShapedType>(getInput().getType());
  }
  ShapedType getOutputOperandType() {
    return cast<ShapedType>(getOutput().getType());
  }
  int64_t getInputOperandRank() {
    return getInputOperandType().getRank();
  }
  int64_t getOutputOperandRank() {
    return getOutputOperandType().getRank();
  }
  int64_t getInputNDim() {
    return 0;
  }
  int64_t getInputHDim() {
    return 1;
  }
  int64_t getInputWDim() {
    return 2;
  }
  int64_t getInputCDim() {
    return 3;
  }
  int64_t getOutputAlphaHDim() {
    return 0;
  }
  int64_t getOutputAlphaWDim() {
    return 1;
  }
  int64_t getOutputTileHDim() {
    return 2;
  }
  int64_t getOutputTileWDim() {
    return 3;
  }
  int64_t getOutputNDim() {
    return 4;
  }
  int64_t getOutputCDim() {
    return 5;
  }
  MutableOperandRange getDpsInitsMutable() { return getOutputMutable(); }
};

} // namespace mlir::linalg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::WinogradInputTransformOp)

namespace mlir::linalg {


//===----------------------------------------------------------------------===//
// ::mlir::linalg::WinogradOutputTransformOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WinogradOutputTransformOpGenericAdaptorBase {
public:
  struct Properties {
    using fmrTy = mlir::linalg::WinogradConv2DFmrAttr;
    fmrTy fmr;

    auto getFmr() const {
      auto &propStorage = this->fmr;
      return ::llvm::cast<mlir::linalg::WinogradConv2DFmrAttr>(propStorage);
    }
    void setFmr(const mlir::linalg::WinogradConv2DFmrAttr &propValue) {
      this->fmr = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fmr == this->fmr &&
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
  WinogradOutputTransformOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("linalg.winograd_output_transform", odsAttrs.getContext());
  }

  WinogradOutputTransformOpGenericAdaptorBase(WinogradOutputTransformOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  mlir::linalg::WinogradConv2DFmrAttr getFmrAttr() {
    auto attr = ::llvm::cast<mlir::linalg::WinogradConv2DFmrAttr>(getProperties().fmr);
    return attr;
  }

  mlir::linalg::WinogradConv2DFmr getFmr();
};

} // namespace detail
template <typename RangeT>
class WinogradOutputTransformOpGenericAdaptor : public detail::WinogradOutputTransformOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WinogradOutputTransformOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_output = 1;
public:
  WinogradOutputTransformOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WinogradOutputTransformOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WinogradOutputTransformOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WinogradOutputTransformOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WinogradOutputTransformOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WinogradOutputTransformOpGenericAdaptor(RangeT values, const WinogradOutputTransformOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WinogradOutputTransformOp, typename = std::enable_if_t<std::is_same_v<LateInst, WinogradOutputTransformOp>>>
  WinogradOutputTransformOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getOutput() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WinogradOutputTransformOpAdaptor : public WinogradOutputTransformOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WinogradOutputTransformOpGenericAdaptor::WinogradOutputTransformOpGenericAdaptor;
  WinogradOutputTransformOpAdaptor(WinogradOutputTransformOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WinogradOutputTransformOp : public ::mlir::Op<WinogradOutputTransformOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::TilingInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WinogradOutputTransformOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WinogradOutputTransformOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_output = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::TilingInterface::Trait<WinogradOutputTransformOp>::generateResultTileValue;
  using ::mlir::TilingInterface::Trait<WinogradOutputTransformOp>::getTiledImplementationFromOperandTiles;
  using ::mlir::TilingInterface::Trait<WinogradOutputTransformOp>::getIterationDomainTileFromOperandTiles;
  using ::mlir::TilingInterface::Trait<WinogradOutputTransformOp>::getIterationDomainTileFromResultTile;
  using ::mlir::TilingInterface::Trait<WinogradOutputTransformOp>::generateScalarImplementation;
  using ::mlir::TilingInterface::Trait<WinogradOutputTransformOp>::isOpFusableWithConsumerSlice;
  using ::mlir::TilingInterface::Trait<WinogradOutputTransformOp>::isOpFusableWithProducerSlices;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fmr")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFmrAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFmrAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("linalg.winograd_output_transform");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getOutputMutable() {
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

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
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
  mlir::linalg::WinogradConv2DFmrAttr getFmrAttr() {
    return ::llvm::cast<mlir::linalg::WinogradConv2DFmrAttr>(getProperties().fmr);
  }

  mlir::linalg::WinogradConv2DFmr getFmr();
  void setFmrAttr(mlir::linalg::WinogradConv2DFmrAttr attr) {
    getProperties().fmr = attr;
  }

  void setFmr(mlir::linalg::WinogradConv2DFmr attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradOutputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradOutputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradOutputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static WinogradOutputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmrAttr fmr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradOutputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradOutputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradOutputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static WinogradOutputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value output, mlir::linalg::WinogradConv2DFmr fmr);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WinogradOutputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WinogradOutputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WinogradOutputTransformOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WinogradOutputTransformOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::SmallVector<::mlir::utils::IteratorType> getLoopIteratorTypes();
  ::mlir::SmallVector<::mlir::Range> getIterationDomain(::mlir::OpBuilder &b);
  ::mlir::FailureOr<::mlir::TilingResult> getTiledImplementation(::mlir::OpBuilder &b, ::mlir::ArrayRef<::mlir::OpFoldResult>  offsets, ::mlir::ArrayRef<::mlir::OpFoldResult>  sizes);
  ::llvm::LogicalResult getResultTilePosition(::mlir::OpBuilder &b, unsigned resultNumber, ::mlir::ArrayRef<::mlir::OpFoldResult>  offsets, ::mlir::ArrayRef<::mlir::OpFoldResult>  sizes, ::mlir::SmallVector<::mlir::OpFoldResult> &resultOffsets, ::mlir::SmallVector<::mlir::OpFoldResult> &resultSizes);
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
  ShapedType getValueOperandType() {
    return cast<ShapedType>(getValue().getType());
  }
  ShapedType getOutputOperandType() {
    return cast<ShapedType>(getOutput().getType());
  }
  int64_t getValueOperandRank() {
    return getValueOperandType().getRank();
  }
  int64_t getOutputOperandRank() {
    return getOutputOperandType().getRank();
  }
  int64_t getValueAlphaHDim() {
    return 0;
  }
  int64_t getValueAlphaWDim() {
    return 1;
  }
  int64_t getValueTileHDim() {
    return 2;
  }
  int64_t getValueTileWDim() {
    return 3;
  }
  int64_t getValueNDim() {
    return 4;
  }
  int64_t getValueFDim() {
    return 5;
  }
  int64_t getOutputNDim() {
    return 0;
  }
  int64_t getOutputHDim() {
    return 1;
  }
  int64_t getOutputWDim() {
    return 2;
  }
  int64_t getOutputFDim() {
    return 3;
  }
  MutableOperandRange getDpsInitsMutable() { return getOutputMutable(); }
};

} // namespace mlir::linalg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::WinogradOutputTransformOp)

namespace mlir::linalg {


//===----------------------------------------------------------------------===//
// ::mlir::linalg::YieldOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class YieldOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  YieldOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("linalg.yield", odsAttrs.getContext());
  }

  YieldOpGenericAdaptorBase(YieldOp op);

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
class YieldOpGenericAdaptor : public detail::YieldOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::YieldOpGenericAdaptorBase;
  static constexpr int odsIndex_values = 0;
public:
  YieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  YieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : YieldOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  YieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : YieldOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  YieldOpGenericAdaptor(RangeT values, const YieldOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = YieldOp, typename = std::enable_if_t<std::is_same_v<LateInst, YieldOp>>>
  YieldOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getValues() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class YieldOpAdaptor : public YieldOpGenericAdaptor<::mlir::ValueRange> {
public:
  using YieldOpGenericAdaptor::YieldOpGenericAdaptor;
  YieldOpAdaptor(YieldOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = YieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = YieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_values = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<YieldOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("linalg.yield");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getValues() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getValuesMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange values);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange values);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange values);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::linalg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::linalg::YieldOp)


#endif // GET_OP_CLASSES

