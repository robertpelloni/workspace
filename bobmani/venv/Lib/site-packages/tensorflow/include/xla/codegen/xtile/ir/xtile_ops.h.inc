/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: xtile_ops.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace xla::xtile {

/// dot_scaled
/// $result = matrix_multiply(scale($lhs, $lhs_scale), scale($rhs, $rhs_scale)).
///         Where scale(x, s) is a function that applies the scale per block following microscaling spec.
class DotScaledOp;

} // namespace xla::xtile
namespace xla::xtile {

/// My custom entry function operation
/// This operation defines a custom entry function that is the starting
///     point for execution. It has a single-block region, takes a
///     variadic list of memrefs and exactly one tile id index arguments,
///     it has no return values.
class EntryFuncOp;

} // namespace xla::xtile
namespace xla::xtile {

/// Terminates the entry function
/// This operation terminates the entry function block. It has no operands
///     and produces no results.
class EntryFuncReturnOp;

} // namespace xla::xtile
namespace xla::xtile {

/// Extract a tile from a memref.
class ExtractTileOp;

} // namespace xla::xtile
namespace xla::xtile {

/// Insert a tile into a memref.
class InsertTileOp;

} // namespace xla::xtile
namespace xla::xtile {

/// Mask the values of a tensor.
/// Masks out the values of the input tensor that are outside the range of the
///     given mask upper bound. Masked values are set to the provided value.
class MaskOp;

} // namespace xla::xtile
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace xla::xtile {


//===----------------------------------------------------------------------===//
// ::xla::xtile::DotScaledOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DotScaledOpGenericAdaptorBase {
public:
  struct Properties {
    using fastMathTy = ::mlir::BoolAttr;
    fastMathTy fastMath;

    auto getFastMath() const {
      auto &propStorage = this->fastMath;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setFastMath(const ::mlir::BoolAttr &propValue) {
      this->fastMath = propValue;
    }
    using lhs_k_packTy = ::mlir::BoolAttr;
    lhs_k_packTy lhs_k_pack;

    auto getLhsKPack() const {
      auto &propStorage = this->lhs_k_pack;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setLhsKPack(const ::mlir::BoolAttr &propValue) {
      this->lhs_k_pack = propValue;
    }
    using rhs_k_packTy = ::mlir::BoolAttr;
    rhs_k_packTy rhs_k_pack;

    auto getRhsKPack() const {
      auto &propStorage = this->rhs_k_pack;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setRhsKPack(const ::mlir::BoolAttr &propValue) {
      this->rhs_k_pack = propValue;
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
        rhs.fastMath == this->fastMath &&
        rhs.lhs_k_pack == this->lhs_k_pack &&
        rhs.rhs_k_pack == this->rhs_k_pack &&
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
  DotScaledOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("xtile.dot_scaled", odsAttrs.getContext());
  }

  DotScaledOpGenericAdaptorBase(DotScaledOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getFastMathAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().fastMath);
    return attr;
  }

  bool getFastMath();
  ::mlir::BoolAttr getLhsKPackAttr();
  bool getLhsKPack();
  ::mlir::BoolAttr getRhsKPackAttr();
  bool getRhsKPack();
};

} // namespace detail
template <typename RangeT>
class DotScaledOpGenericAdaptor : public detail::DotScaledOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DotScaledOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_lhs_scale = 2;
  static constexpr int odsIndex_rhs_scale = 3;
public:
  DotScaledOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DotScaledOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DotScaledOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DotScaledOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : DotScaledOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DotScaledOpGenericAdaptor(RangeT values, const DotScaledOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DotScaledOp, typename = std::enable_if_t<std::is_same_v<LateInst, DotScaledOp>>>
  DotScaledOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getLhsScale() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getRhsScale() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DotScaledOpAdaptor : public DotScaledOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DotScaledOpGenericAdaptor::DotScaledOpGenericAdaptor;
  DotScaledOpAdaptor(DotScaledOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DotScaledOp : public ::mlir::Op<DotScaledOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DotScaledOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DotScaledOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_lhs_scale = 2;
  static constexpr int odsIndex_rhs_scale = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fastMath"), ::llvm::StringRef("lhs_k_pack"), ::llvm::StringRef("rhs_k_pack"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFastMathAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFastMathAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLhsKPackAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLhsKPackAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getRhsKPackAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getRhsKPackAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("xtile.dot_scaled");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getLhsScale() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::RankedTensorType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getRhsScale() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::RankedTensorType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*operands.begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getLhsScaleMutable();
  ::mlir::MutableOperandRange getRhsScaleMutable();
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
  ::mlir::BoolAttr getFastMathAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().fastMath);
  }

  bool getFastMath();
  ::mlir::BoolAttr getLhsKPackAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().lhs_k_pack);
  }

  bool getLhsKPack();
  ::mlir::BoolAttr getRhsKPackAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().rhs_k_pack);
  }

  bool getRhsKPack();
  void setFastMathAttr(::mlir::BoolAttr attr) {
    getProperties().fastMath = attr;
  }

  void setFastMath(bool attrValue);
  void setLhsKPackAttr(::mlir::BoolAttr attr) {
    getProperties().lhs_k_pack = attr;
  }

  void setLhsKPack(bool attrValue);
  void setRhsKPackAttr(::mlir::BoolAttr attr) {
    getProperties().rhs_k_pack = attr;
  }

  void setRhsKPack(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, ::mlir::BoolAttr fastMath, ::mlir::BoolAttr lhs_k_pack = nullptr, ::mlir::BoolAttr rhs_k_pack = nullptr);
  static DotScaledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, ::mlir::BoolAttr fastMath, ::mlir::BoolAttr lhs_k_pack = nullptr, ::mlir::BoolAttr rhs_k_pack = nullptr);
  static DotScaledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, ::mlir::BoolAttr fastMath, ::mlir::BoolAttr lhs_k_pack = nullptr, ::mlir::BoolAttr rhs_k_pack = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, ::mlir::BoolAttr fastMath, ::mlir::BoolAttr lhs_k_pack = nullptr, ::mlir::BoolAttr rhs_k_pack = nullptr);
  static DotScaledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, ::mlir::BoolAttr fastMath, ::mlir::BoolAttr lhs_k_pack = nullptr, ::mlir::BoolAttr rhs_k_pack = nullptr);
  static DotScaledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, ::mlir::BoolAttr fastMath, ::mlir::BoolAttr lhs_k_pack = nullptr, ::mlir::BoolAttr rhs_k_pack = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, bool fastMath, bool lhs_k_pack = true, bool rhs_k_pack = true);
  static DotScaledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, bool fastMath, bool lhs_k_pack = true, bool rhs_k_pack = true);
  static DotScaledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, bool fastMath, bool lhs_k_pack = true, bool rhs_k_pack = true);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, bool fastMath, bool lhs_k_pack = true, bool rhs_k_pack = true);
  static DotScaledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, bool fastMath, bool lhs_k_pack = true, bool rhs_k_pack = true);
  static DotScaledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value lhs_scale, /*optional*/::mlir::Value rhs_scale, bool fastMath, bool lhs_k_pack = true, bool rhs_k_pack = true);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DotScaledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DotScaledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DotScaledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DotScaledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
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
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace xla::xtile
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::xtile::DotScaledOp)

namespace xla::xtile {


//===----------------------------------------------------------------------===//
// ::xla::xtile::EntryFuncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EntryFuncOpGenericAdaptorBase {
public:
  struct Properties {
    using arg_attrsTy = ::mlir::ArrayAttr;
    arg_attrsTy arg_attrs;

    auto getArgAttrs() const {
      auto &propStorage = this->arg_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setArgAttrs(const ::mlir::ArrayAttr &propValue) {
      this->arg_attrs = propValue;
    }
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() const {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using num_opaque_argsTy = ::mlir::IntegerAttr;
    num_opaque_argsTy num_opaque_args;

    auto getNumOpaqueArgs() const {
      auto &propStorage = this->num_opaque_args;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setNumOpaqueArgs(const ::mlir::IntegerAttr &propValue) {
      this->num_opaque_args = propValue;
    }
    using res_attrsTy = ::mlir::ArrayAttr;
    res_attrsTy res_attrs;

    auto getResAttrs() const {
      auto &propStorage = this->res_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setResAttrs(const ::mlir::ArrayAttr &propValue) {
      this->res_attrs = propValue;
    }
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    using tile_infoTy = ::xla::xtile::TilingInfoAttr;
    tile_infoTy tile_info;

    auto getTileInfo() const {
      auto &propStorage = this->tile_info;
      return ::llvm::dyn_cast_or_null<::xla::xtile::TilingInfoAttr>(propStorage);
    }
    void setTileInfo(const ::xla::xtile::TilingInfoAttr &propValue) {
      this->tile_info = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.num_opaque_args == this->num_opaque_args &&
        rhs.res_attrs == this->res_attrs &&
        rhs.sym_name == this->sym_name &&
        rhs.tile_info == this->tile_info &&
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
  EntryFuncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("xtile.entry_func", odsAttrs.getContext());
  }

  EntryFuncOpGenericAdaptorBase(EntryFuncOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
  ::mlir::TypeAttr getFunctionTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
    return attr;
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::xla::xtile::TilingInfoAttr getTileInfoAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::xla::xtile::TilingInfoAttr>(getProperties().tile_info);
    return attr;
  }

  ::std::optional<::xla::xtile::TilingInfoAttr> getTileInfo();
  ::mlir::ArrayAttr getResAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::IntegerAttr getNumOpaqueArgsAttr();
  uint32_t getNumOpaqueArgs();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class EntryFuncOpGenericAdaptor : public detail::EntryFuncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EntryFuncOpGenericAdaptorBase;
public:
  EntryFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EntryFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : EntryFuncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EntryFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EntryFuncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EntryFuncOpGenericAdaptor(RangeT values, const EntryFuncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EntryFuncOp, typename = std::enable_if_t<std::is_same_v<LateInst, EntryFuncOp>>>
  EntryFuncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class EntryFuncOpAdaptor : public EntryFuncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EntryFuncOpGenericAdaptor::EntryFuncOpGenericAdaptor;
  EntryFuncOpAdaptor(EntryFuncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EntryFuncOp : public ::mlir::Op<EntryFuncOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EntryFuncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EntryFuncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("num_opaque_args"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("tile_info")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgAttrsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFunctionTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFunctionTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getNumOpaqueArgsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getNumOpaqueArgsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getTileInfoAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getTileInfoAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("xtile.entry_func");
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

  ::mlir::Region &getBody() {
    return (*this)->getRegion(0);
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  ::mlir::TypeAttr getFunctionTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::xla::xtile::TilingInfoAttr getTileInfoAttr() {
    return ::llvm::dyn_cast_or_null<::xla::xtile::TilingInfoAttr>(getProperties().tile_info);
  }

  ::std::optional<::xla::xtile::TilingInfoAttr> getTileInfo();
  ::mlir::ArrayAttr getResAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::IntegerAttr getNumOpaqueArgsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().num_opaque_args);
  }

  uint32_t getNumOpaqueArgs();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setFunctionTypeAttr(::mlir::TypeAttr attr) {
    getProperties().function_type = attr;
  }

  void setFunctionType(::mlir::FunctionType attrValue);
  void setArgAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().arg_attrs = attr;
  }

  void setTileInfoAttr(::xla::xtile::TilingInfoAttr attr) {
    getProperties().tile_info = attr;
  }

  void setResAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().res_attrs = attr;
  }

  void setNumOpaqueArgsAttr(::mlir::IntegerAttr attr) {
    getProperties().num_opaque_args = attr;
  }

  void setNumOpaqueArgs(uint32_t attrValue);
  ::mlir::Attribute removeArgAttrsAttr() {
      auto attr = getProperties().arg_attrs;
      getProperties().arg_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeTileInfoAttr() {
      auto attr = getProperties().tile_info;
      getProperties().tile_info = {};
      return attr;
  }

  ::mlir::Attribute removeResAttrsAttr() {
      auto attr = getProperties().res_attrs;
      getProperties().res_attrs = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::StringRef name, mlir::ArrayRef<mlir::Type> memref_arg_types, mlir::ArrayRef<mlir::NamedAttribute> attrs = {}, mlir::ArrayRef<mlir::DictionaryAttr> memref_arg_attrs = {});
  static EntryFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::StringRef name, mlir::ArrayRef<mlir::Type> memref_arg_types, mlir::ArrayRef<mlir::NamedAttribute> attrs = {}, mlir::ArrayRef<mlir::DictionaryAttr> memref_arg_attrs = {});
  static EntryFuncOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::StringRef name, mlir::ArrayRef<mlir::Type> memref_arg_types, mlir::ArrayRef<mlir::NamedAttribute> attrs = {}, mlir::ArrayRef<mlir::DictionaryAttr> memref_arg_attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::IntegerAttr num_opaque_args = nullptr);
  static EntryFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::IntegerAttr num_opaque_args = nullptr);
  static EntryFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::IntegerAttr num_opaque_args = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::IntegerAttr num_opaque_args = nullptr);
  static EntryFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::IntegerAttr num_opaque_args = nullptr);
  static EntryFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::IntegerAttr num_opaque_args = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, uint32_t num_opaque_args = 0);
  static EntryFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, uint32_t num_opaque_args = 0);
  static EntryFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, uint32_t num_opaque_args = 0);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, uint32_t num_opaque_args = 0);
  static EntryFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, uint32_t num_opaque_args = 0);
  static EntryFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::xla::xtile::TilingInfoAttr tile_info, /*optional*/::mlir::ArrayAttr res_attrs, uint32_t num_opaque_args = 0);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EntryFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EntryFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EntryFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EntryFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 6 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  //===------------------------------------------------------------------===//
  // Helper Methods
  //===------------------------------------------------------------------===//
  mlir::ValueRange getBufferArgs() {
    // +1 for the tile id argument.
    return getBody().getArguments().drop_back(getNumOpaqueArgs() + 1);
  }

  mlir::ValueRange getOpaqueArgs() {
    return getBody().getArguments().take_back(getNumOpaqueArgs() + 1)
        .drop_back();
  }

  mlir::Value getTileId() {
    return getBody().getArguments().back();
  }

  //===------------------------------------------------------------------===//
  // FunctionOpInterface Methods
  //===------------------------------------------------------------------===//

  /// Returns the region on the current operation that is callable.
  mlir::Region *getCallableRegion() { return &getBody(); }

  /// Returns the argument types of this function.
  mlir::ArrayRef<mlir::Type> getArgumentTypes() { return getFunctionType().getInputs(); }

  /// Returns the result types of this function.
  mlir::ArrayRef<mlir::Type> getResultTypes() { return getFunctionType().getResults(); }
};

} // namespace xla::xtile
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::xtile::EntryFuncOp)

namespace xla::xtile {


//===----------------------------------------------------------------------===//
// ::xla::xtile::EntryFuncReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EntryFuncReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  EntryFuncReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("xtile.return", odsAttrs.getContext());
  }

  EntryFuncReturnOpGenericAdaptorBase(EntryFuncReturnOp op);

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
class EntryFuncReturnOpGenericAdaptor : public detail::EntryFuncReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EntryFuncReturnOpGenericAdaptorBase;
public:
  EntryFuncReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EntryFuncReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : EntryFuncReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EntryFuncReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EntryFuncReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EntryFuncReturnOpGenericAdaptor(RangeT values, const EntryFuncReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EntryFuncReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, EntryFuncReturnOp>>>
  EntryFuncReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class EntryFuncReturnOpAdaptor : public EntryFuncReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EntryFuncReturnOpGenericAdaptor::EntryFuncReturnOpGenericAdaptor;
  EntryFuncReturnOpAdaptor(EntryFuncReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EntryFuncReturnOp : public ::mlir::Op<EntryFuncReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<EntryFuncOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EntryFuncReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EntryFuncReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<EntryFuncReturnOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("xtile.return");
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static EntryFuncReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static EntryFuncReturnOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static EntryFuncReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static EntryFuncReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EntryFuncReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EntryFuncReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EntryFuncReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EntryFuncReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace xla::xtile
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::xtile::EntryFuncReturnOp)

namespace xla::xtile {


//===----------------------------------------------------------------------===//
// ::xla::xtile::ExtractTileOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtractTileOpGenericAdaptorBase {
public:
  struct Properties {
    using full_tile_shapeTy = ::mlir::DenseI64ArrayAttr;
    full_tile_shapeTy full_tile_shape;

    auto getFullTileShape() const {
      auto &propStorage = this->full_tile_shape;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setFullTileShape(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->full_tile_shape = propValue;
    }
    using stridesTy = ::mlir::DenseI64ArrayAttr;
    stridesTy strides;

    auto getStrides() const {
      auto &propStorage = this->strides;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStrides(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->strides = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.full_tile_shape == this->full_tile_shape &&
        rhs.strides == this->strides &&
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
  ExtractTileOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("xtile.extract", odsAttrs.getContext());
  }

  ExtractTileOpGenericAdaptorBase(ExtractTileOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getFullTileShapeAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().full_tile_shape);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getFullTileShape();
  ::mlir::DenseI64ArrayAttr getStridesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().strides);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStrides();
};

} // namespace detail
template <typename RangeT>
class ExtractTileOpGenericAdaptor : public detail::ExtractTileOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtractTileOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_offsets = 1;
public:
  ExtractTileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExtractTileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExtractTileOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExtractTileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExtractTileOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExtractTileOpGenericAdaptor(RangeT values, const ExtractTileOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExtractTileOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExtractTileOp>>>
  ExtractTileOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOffsets() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ExtractTileOpAdaptor : public ExtractTileOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExtractTileOpGenericAdaptor::ExtractTileOpGenericAdaptor;
  ExtractTileOpAdaptor(ExtractTileOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExtractTileOp : public ::mlir::Op<ExtractTileOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::bufferization::BufferizableOpInterface::Trait, ::xla::xtile::TiledBufferInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtractTileOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtractTileOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_offsets = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::bufferizesToElementwiseAccess;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::resultBufferizesToMemoryWrite;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::mustBufferizeInPlace;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::resolveConflicts;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::isNotConflicting;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::verifyAnalysis;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::getBufferType;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::isRepetitiveRegion;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::isParallelRegion;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::hasTensorSemantics;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<ExtractTileOp>::supportsUnstructuredControlFlow;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("full_tile_shape"), ::llvm::StringRef("strides")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFullTileShapeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFullTileShapeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStridesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStridesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("xtile.extract");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getOffsets() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getOffsetsMutable();
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
  ::mlir::DenseI64ArrayAttr getFullTileShapeAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().full_tile_shape);
  }

  ::llvm::ArrayRef<int64_t> getFullTileShape();
  ::mlir::DenseI64ArrayAttr getStridesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().strides);
  }

  ::llvm::ArrayRef<int64_t> getStrides();
  void setFullTileShapeAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().full_tile_shape = attr;
  }

  void setFullTileShape(::llvm::ArrayRef<int64_t> attrValue);
  void setStridesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().strides = attr;
  }

  void setStrides(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static ExtractTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static ExtractTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static ExtractTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static ExtractTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static ExtractTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static ExtractTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static ExtractTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static ExtractTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  bool bufferizesToAllocation(::mlir::Value value);
  bool bufferizesToMemoryRead(::mlir::OpOperand &opOperand, const ::mlir::bufferization::AnalysisState &state);
  bool bufferizesToMemoryWrite(::mlir::OpOperand &opOperand, const ::mlir::bufferization::AnalysisState &state);
  ::mlir::bufferization::AliasingValueList getAliasingValues(::mlir::OpOperand &opOperand, const ::mlir::bufferization::AnalysisState &state);
  ::mlir::bufferization::AliasingOpOperandList getAliasingOpOperands(::mlir::Value value, const ::mlir::bufferization::AnalysisState &state);
  ::llvm::LogicalResult bufferize(::mlir::RewriterBase &rewriter, const ::mlir::bufferization::BufferizationOptions &options, ::mlir::bufferization::BufferizationState &state);
  bool isWritable(::mlir::Value value, const ::mlir::bufferization::AnalysisState &state);
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
  mlir::TypedValue<mlir::MemRefType> getBuffer();
  mlir::TypedValue<mlir::RankedTensorType> getTile();
};

} // namespace xla::xtile
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::xtile::ExtractTileOp)

namespace xla::xtile {


//===----------------------------------------------------------------------===//
// ::xla::xtile::InsertTileOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InsertTileOpGenericAdaptorBase {
public:
  struct Properties {
    using full_tile_shapeTy = ::mlir::DenseI64ArrayAttr;
    full_tile_shapeTy full_tile_shape;

    auto getFullTileShape() const {
      auto &propStorage = this->full_tile_shape;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setFullTileShape(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->full_tile_shape = propValue;
    }
    using stridesTy = ::mlir::DenseI64ArrayAttr;
    stridesTy strides;

    auto getStrides() const {
      auto &propStorage = this->strides;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStrides(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->strides = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.full_tile_shape == this->full_tile_shape &&
        rhs.strides == this->strides &&
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
  InsertTileOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("xtile.insert", odsAttrs.getContext());
  }

  InsertTileOpGenericAdaptorBase(InsertTileOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getFullTileShapeAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().full_tile_shape);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getFullTileShape();
  ::mlir::DenseI64ArrayAttr getStridesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().strides);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStrides();
};

} // namespace detail
template <typename RangeT>
class InsertTileOpGenericAdaptor : public detail::InsertTileOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InsertTileOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_destination = 1;
  static constexpr int odsIndex_offsets = 2;
public:
  InsertTileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InsertTileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : InsertTileOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InsertTileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InsertTileOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InsertTileOpGenericAdaptor(RangeT values, const InsertTileOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InsertTileOp, typename = std::enable_if_t<std::is_same_v<LateInst, InsertTileOp>>>
  InsertTileOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getDestination() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOffsets() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class InsertTileOpAdaptor : public InsertTileOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InsertTileOpGenericAdaptor::InsertTileOpGenericAdaptor;
  InsertTileOpAdaptor(InsertTileOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InsertTileOp : public ::mlir::Op<InsertTileOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::bufferization::BufferizableOpInterface::Trait, ::xla::xtile::TiledBufferInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InsertTileOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InsertTileOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_destination = 1;
  static constexpr int odsIndex_offsets = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::bufferizesToElementwiseAccess;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::resultBufferizesToMemoryWrite;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::mustBufferizeInPlace;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::resolveConflicts;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::isNotConflicting;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::verifyAnalysis;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::getBufferType;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::isRepetitiveRegion;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::isParallelRegion;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::hasTensorSemantics;
  using ::mlir::bufferization::BufferizableOpInterface::Trait<InsertTileOp>::supportsUnstructuredControlFlow;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("full_tile_shape"), ::llvm::StringRef("strides")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFullTileShapeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFullTileShapeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStridesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStridesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("xtile.insert");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getDestination() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getOffsets() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestinationMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getOffsetsMutable();
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
  ::mlir::DenseI64ArrayAttr getFullTileShapeAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().full_tile_shape);
  }

  ::llvm::ArrayRef<int64_t> getFullTileShape();
  ::mlir::DenseI64ArrayAttr getStridesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().strides);
  }

  ::llvm::ArrayRef<int64_t> getStrides();
  void setFullTileShapeAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().full_tile_shape = attr;
  }

  void setFullTileShape(::llvm::ArrayRef<int64_t> attrValue);
  void setStridesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().strides = attr;
  }

  void setStrides(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static InsertTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static InsertTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static InsertTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static InsertTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::mlir::DenseI64ArrayAttr full_tile_shape, ::mlir::DenseI64ArrayAttr strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static InsertTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static InsertTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static InsertTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static InsertTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value destination, ::mlir::ValueRange offsets, ::llvm::ArrayRef<int64_t> full_tile_shape, ::llvm::ArrayRef<int64_t> strides);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertTileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertTileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  bool bufferizesToAllocation(::mlir::Value value);
  bool bufferizesToMemoryRead(::mlir::OpOperand &opOperand, const ::mlir::bufferization::AnalysisState &state);
  bool bufferizesToMemoryWrite(::mlir::OpOperand &opOperand, const ::mlir::bufferization::AnalysisState &state);
  ::mlir::bufferization::AliasingValueList getAliasingValues(::mlir::OpOperand &opOperand, const ::mlir::bufferization::AnalysisState &state);
  ::mlir::bufferization::AliasingOpOperandList getAliasingOpOperands(::mlir::Value value, const ::mlir::bufferization::AnalysisState &state);
  ::llvm::LogicalResult bufferize(::mlir::RewriterBase &rewriter, const ::mlir::bufferization::BufferizationOptions &options, ::mlir::bufferization::BufferizationState &state);
  bool isWritable(::mlir::Value value, const ::mlir::bufferization::AnalysisState &state);
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
  mlir::TypedValue<mlir::MemRefType> getBuffer();
  mlir::TypedValue<mlir::RankedTensorType> getTile();
};

} // namespace xla::xtile
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::xtile::InsertTileOp)

namespace xla::xtile {


//===----------------------------------------------------------------------===//
// ::xla::xtile::MaskOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MaskOpGenericAdaptorBase {
public:
  struct Properties {
    using boundsTy = ::mlir::DenseI64ArrayAttr;
    boundsTy bounds;

    auto getBounds() const {
      auto &propStorage = this->bounds;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setBounds(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->bounds = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.bounds == this->bounds &&
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
  MaskOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("xtile.mask", odsAttrs.getContext());
  }

  MaskOpGenericAdaptorBase(MaskOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getBoundsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().bounds);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getBounds();
};

} // namespace detail
template <typename RangeT>
class MaskOpGenericAdaptor : public detail::MaskOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MaskOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_value = 1;
public:
  MaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MaskOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MaskOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MaskOpGenericAdaptor(RangeT values, const MaskOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MaskOp, typename = std::enable_if_t<std::is_same_v<LateInst, MaskOp>>>
  MaskOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getValue() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MaskOpAdaptor : public MaskOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MaskOpGenericAdaptor::MaskOpGenericAdaptor;
  MaskOpAdaptor(MaskOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MaskOp : public ::mlir::Op<MaskOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MaskOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MaskOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_value = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("bounds")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBoundsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBoundsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("xtile.mask");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValueMutable() {
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
  ::mlir::DenseI64ArrayAttr getBoundsAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().bounds);
  }

  ::llvm::ArrayRef<int64_t> getBounds();
  void setBoundsAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().bounds = attr;
  }

  void setBounds(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::DenseI64ArrayAttr bounds, ::mlir::Value value);
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::DenseI64ArrayAttr bounds, ::mlir::Value value);
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::DenseI64ArrayAttr bounds, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::DenseI64ArrayAttr bounds, ::mlir::Value value);
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::DenseI64ArrayAttr bounds, ::mlir::Value value);
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::DenseI64ArrayAttr bounds, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::DenseI64ArrayAttr bounds, ::mlir::Value value);
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::DenseI64ArrayAttr bounds, ::mlir::Value value);
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::DenseI64ArrayAttr bounds, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::llvm::ArrayRef<int64_t> bounds, ::mlir::Value value);
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::llvm::ArrayRef<int64_t> bounds, ::mlir::Value value);
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::llvm::ArrayRef<int64_t> bounds, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::llvm::ArrayRef<int64_t> bounds, ::mlir::Value value);
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::llvm::ArrayRef<int64_t> bounds, ::mlir::Value value);
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::llvm::ArrayRef<int64_t> bounds, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::llvm::ArrayRef<int64_t> bounds, ::mlir::Value value);
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::llvm::ArrayRef<int64_t> bounds, ::mlir::Value value);
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::llvm::ArrayRef<int64_t> bounds, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  // Get the dimensions where the mask bound is smaller than the dimension
  // size. The returned array is sorted in increasing order.
  llvm::SmallVector<int64_t> getMaskedDimensions();
};

} // namespace xla::xtile
MLIR_DECLARE_EXPLICIT_TYPE_ID(::xla::xtile::MaskOp)


#endif // GET_OP_CLASSES

