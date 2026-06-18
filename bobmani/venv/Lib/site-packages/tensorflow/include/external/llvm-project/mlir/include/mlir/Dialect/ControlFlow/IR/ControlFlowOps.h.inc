/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ControlFlowOps.td                                                    *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::cf {

/// Assert operation with message attribute
/// Assert operation at runtime with single boolean operand and an error
///     message attribute.
///     If the argument is `true` this operation has no effect. Otherwise, the
///     program execution will abort. The provided error message may be used by a
///     runtime to propagate the error to the user.
/// 
///     Example:
/// 
///     ```mlir
///     cf.assert %b, "Expected ... to be true"
///     ```
class AssertOp;

} // namespace mlir::cf
namespace mlir::cf {

/// Branch operation
/// The `cf.br` operation represents a direct branch operation to a given
///     block. The operands of this operation are forwarded to the successor block,
///     and the number and type of the operands must match the arguments of the
///     target block.
/// 
///     Example:
/// 
///     ```mlir
///     ^bb2:
///       %2 = call @someFn()
///       cf.br ^bb3(%2 : tensor<*xf32>)
///     ^bb3(%3: tensor<*xf32>):
///     ```
class BranchOp;

} // namespace mlir::cf
namespace mlir::cf {

/// Conditional branch operation
/// The `cf.cond_br` terminator operation represents a conditional branch on a
///     boolean (1-bit integer) value. If the bit is set, then the first destination
///     is jumped to; if it is false, the second destination is chosen. The count
///     and types of operands must align with the arguments in the corresponding
///     target blocks.
/// 
///     The MLIR conditional branch operation is not allowed to target the entry
///     block for a region. The two destinations of the conditional branch operation
///     are allowed to be the same.
/// 
///     The following example illustrates a function with a conditional branch
///     operation that targets the same block.
/// 
///     Example:
/// 
///     ```mlir
///     func.func @select(%a: i32, %b: i32, %flag: i1) -> i32 {
///       // Both targets are the same, operands differ
///       cf.cond_br %flag, ^bb1(%a : i32), ^bb1(%b : i32)
/// 
///     ^bb1(%x : i32) :
///       return %x : i32
///     }
///     ```
class CondBranchOp;

} // namespace mlir::cf
namespace mlir::cf {

/// Switch operation
/// The `cf.switch` terminator operation represents a switch on a signless integer
///     value. If the flag matches one of the specified cases, then the
///     corresponding destination is jumped to. If the flag does not match any of
///     the cases, the default destination is jumped to. The count and types of
///     operands must align with the arguments in the corresponding target blocks.
/// 
///     Example:
/// 
///     ```mlir
///     cf.switch %flag : i32, [
///       default: ^bb1(%a : i32),
///       42: ^bb1(%b : i32),
///       43: ^bb3(%c : i32)
///     ]
///     ```
class SwitchOp;

} // namespace mlir::cf
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::cf {


//===----------------------------------------------------------------------===//
// ::mlir::cf::AssertOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AssertOpGenericAdaptorBase {
public:
  struct Properties {
    using msgTy = ::mlir::StringAttr;
    msgTy msg;

    auto getMsg() const {
      auto &propStorage = this->msg;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setMsg(const ::mlir::StringAttr &propValue) {
      this->msg = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.msg == this->msg &&
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
  AssertOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("cf.assert", odsAttrs.getContext());
  }

  AssertOpGenericAdaptorBase(AssertOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getMsgAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().msg);
    return attr;
  }

  ::llvm::StringRef getMsg();
};

} // namespace detail
template <typename RangeT>
class AssertOpGenericAdaptor : public detail::AssertOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AssertOpGenericAdaptorBase;
  static constexpr int odsIndex_arg = 0;
public:
  AssertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AssertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AssertOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AssertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AssertOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AssertOpGenericAdaptor(RangeT values, const AssertOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AssertOp, typename = std::enable_if_t<std::is_same_v<LateInst, AssertOp>>>
  AssertOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getArg() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AssertOpAdaptor : public AssertOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AssertOpGenericAdaptor::AssertOpGenericAdaptor;
  AssertOpAdaptor(AssertOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AssertOp : public ::mlir::Op<AssertOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AssertOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AssertOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_arg = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("msg")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMsgAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMsgAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("cf.assert");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getArg() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getArgMutable() {
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
  ::mlir::StringAttr getMsgAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().msg);
  }

  ::llvm::StringRef getMsg();
  void setMsgAttr(::mlir::StringAttr attr) {
    getProperties().msg = attr;
  }

  void setMsg(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value arg, ::mlir::StringAttr msg);
  static AssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value arg, ::mlir::StringAttr msg);
  static AssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value arg, ::mlir::StringAttr msg);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value arg, ::mlir::StringAttr msg);
  static AssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value arg, ::mlir::StringAttr msg);
  static AssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value arg, ::mlir::StringAttr msg);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value arg, ::llvm::StringRef msg);
  static AssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value arg, ::llvm::StringRef msg);
  static AssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value arg, ::llvm::StringRef msg);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value arg, ::llvm::StringRef msg);
  static AssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value arg, ::llvm::StringRef msg);
  static AssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value arg, ::llvm::StringRef msg);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(AssertOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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

} // namespace mlir::cf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::cf::AssertOp)

namespace mlir::cf {


//===----------------------------------------------------------------------===//
// ::mlir::cf::BranchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BranchOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BranchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("cf.br", odsAttrs.getContext());
  }

  BranchOpGenericAdaptorBase(BranchOp op);

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
class BranchOpGenericAdaptor : public detail::BranchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BranchOpGenericAdaptorBase;
  static constexpr int odsIndex_destOperands = 0;
public:
  BranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : BranchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BranchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BranchOpGenericAdaptor(RangeT values, const BranchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BranchOp, typename = std::enable_if_t<std::is_same_v<LateInst, BranchOp>>>
  BranchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDestOperands() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BranchOpAdaptor : public BranchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BranchOpGenericAdaptor::BranchOpGenericAdaptor;
  BranchOpAdaptor(BranchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BranchOp : public ::mlir::Op<BranchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::OneSuccessor, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BranchOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BranchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BranchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_destOperands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::BranchOpInterface::Trait<BranchOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("cf.br");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDestOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getDestOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Block *getDest() {
    return (*this)->getSuccessor(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Block *dest, ValueRange destOperands = {});
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Block *dest, ValueRange destOperands = {});
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, Block *dest, ValueRange destOperands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(BranchOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::SuccessorOperands getSuccessorOperands(unsigned index);
  ::mlir::Block *getSuccessorForOperands(::llvm::ArrayRef<::mlir::Attribute> operands);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  void setDest(Block *block);

  /// Erase the operand at 'index' from the operand list.
  void eraseOperand(unsigned index);
};

} // namespace mlir::cf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::cf::BranchOp)

namespace mlir::cf {


//===----------------------------------------------------------------------===//
// ::mlir::cf::CondBranchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CondBranchOpGenericAdaptorBase {
public:
  struct Properties {
    using branch_weightsTy = ::mlir::DenseI32ArrayAttr;
    branch_weightsTy branch_weights;

    auto getBranchWeights() const {
      auto &propStorage = this->branch_weights;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(propStorage);
    }
    void setBranchWeights(const ::mlir::DenseI32ArrayAttr &propValue) {
      this->branch_weights = propValue;
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
        rhs.branch_weights == this->branch_weights &&
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
  CondBranchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("cf.cond_br", odsAttrs.getContext());
  }

  CondBranchOpGenericAdaptorBase(CondBranchOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI32ArrayAttr getBranchWeightsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(getProperties().branch_weights);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<int32_t>> getBranchWeights();
};

} // namespace detail
template <typename RangeT>
class CondBranchOpGenericAdaptor : public detail::CondBranchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CondBranchOpGenericAdaptorBase;
  static constexpr int odsIndex_condition = 0;
  static constexpr int odsIndex_trueDestOperands = 1;
  static constexpr int odsIndex_falseDestOperands = 2;
public:
  CondBranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CondBranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CondBranchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CondBranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : CondBranchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CondBranchOpGenericAdaptor(RangeT values, const CondBranchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CondBranchOp, typename = std::enable_if_t<std::is_same_v<LateInst, CondBranchOp>>>
  CondBranchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getCondition() {
    return (*getODSOperands(0).begin());
  }

  RangeT getTrueDestOperands() {
    return getODSOperands(1);
  }

  RangeT getFalseDestOperands() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CondBranchOpAdaptor : public CondBranchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CondBranchOpGenericAdaptor::CondBranchOpGenericAdaptor;
  CondBranchOpAdaptor(CondBranchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CondBranchOp : public ::mlir::Op<CondBranchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::NSuccessors<2>::Impl, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::BranchOpInterface::Trait, ::mlir::WeightedBranchOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CondBranchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CondBranchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_condition = 0;
  static constexpr int odsIndex_trueDestOperands = 1;
  static constexpr int odsIndex_falseDestOperands = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::BranchOpInterface::Trait<CondBranchOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("branch_weights"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBranchWeightsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBranchWeightsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("cf.cond_br");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCondition() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getTrueDestOperands() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getFalseDestOperands() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getConditionMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getTrueDestOperandsMutable();
  ::mlir::MutableOperandRange getFalseDestOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Block *getTrueDest() {
    return (*this)->getSuccessor(0);
  }

  ::mlir::Block *getFalseDest() {
    return (*this)->getSuccessor(1);
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
  ::mlir::DenseI32ArrayAttr getBranchWeightsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(getProperties().branch_weights);
  }

  ::std::optional<::llvm::ArrayRef<int32_t>> getBranchWeights();
  void setBranchWeightsAttr(::mlir::DenseI32ArrayAttr attr) {
    getProperties().branch_weights = attr;
  }

  void setBranchWeights(::std::optional<::llvm::ArrayRef<int32_t>> attrValue);
  ::mlir::Attribute removeBranchWeightsAttr() {
      auto attr = getProperties().branch_weights;
      getProperties().branch_weights = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value condition, Block *trueDest, ValueRange trueOperands, Block *falseDest, ValueRange falseOperands, ArrayRef<int32_t> branchWeights = {});
  static CondBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value condition, Block *trueDest, ValueRange trueOperands, Block *falseDest, ValueRange falseOperands, ArrayRef<int32_t> branchWeights = {});
  static CondBranchOp create(::mlir::ImplicitLocOpBuilder &builder, Value condition, Block *trueDest, ValueRange trueOperands, Block *falseDest, ValueRange falseOperands, ArrayRef<int32_t> branchWeights = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value condition, Block *trueDest, Block *falseDest, ValueRange falseOperands = {}, ArrayRef<int32_t> branchWeights = {});
  static CondBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value condition, Block *trueDest, Block *falseDest, ValueRange falseOperands = {}, ArrayRef<int32_t> branchWeights = {});
  static CondBranchOp create(::mlir::ImplicitLocOpBuilder &builder, Value condition, Block *trueDest, Block *falseDest, ValueRange falseOperands = {}, ArrayRef<int32_t> branchWeights = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value condition, ::mlir::ValueRange trueDestOperands, ::mlir::ValueRange falseDestOperands, /*optional*/::mlir::DenseI32ArrayAttr branch_weights, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CondBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value condition, ::mlir::ValueRange trueDestOperands, ::mlir::ValueRange falseDestOperands, /*optional*/::mlir::DenseI32ArrayAttr branch_weights, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CondBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value condition, ::mlir::ValueRange trueDestOperands, ::mlir::ValueRange falseDestOperands, /*optional*/::mlir::DenseI32ArrayAttr branch_weights, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value condition, ::mlir::ValueRange trueDestOperands, ::mlir::ValueRange falseDestOperands, /*optional*/::mlir::DenseI32ArrayAttr branch_weights, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CondBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value condition, ::mlir::ValueRange trueDestOperands, ::mlir::ValueRange falseDestOperands, /*optional*/::mlir::DenseI32ArrayAttr branch_weights, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CondBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value condition, ::mlir::ValueRange trueDestOperands, ::mlir::ValueRange falseDestOperands, /*optional*/::mlir::DenseI32ArrayAttr branch_weights, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CondBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CondBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CondBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CondBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::SuccessorOperands getSuccessorOperands(unsigned index);
  ::mlir::Block *getSuccessorForOperands(::llvm::ArrayRef<::mlir::Attribute> operands);
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
    // These are the indices into the dests list.
    enum { trueIndex = 0, falseIndex = 1 };

    // Accessors for operands to the 'true' destination.
    Value getTrueOperand(unsigned idx) {
      assert(idx < getNumTrueOperands());
      return getOperand(getTrueDestOperandIndex() + idx);
    }

    void setTrueOperand(unsigned idx, Value value) {
      assert(idx < getNumTrueOperands());
      setOperand(getTrueDestOperandIndex() + idx, value);
    }

    unsigned getNumTrueOperands()  { return getTrueOperands().size(); }

    /// Erase the operand at 'index' from the true operand list.
    void eraseTrueOperand(unsigned index)  {
      getTrueDestOperandsMutable().erase(index);
    }

    // Accessors for operands to the 'false' destination.
    Value getFalseOperand(unsigned idx) {
      assert(idx < getNumFalseOperands());
      return getOperand(getFalseDestOperandIndex() + idx);
    }
    void setFalseOperand(unsigned idx, Value value) {
      assert(idx < getNumFalseOperands());
      setOperand(getFalseDestOperandIndex() + idx, value);
    }

    operand_range getTrueOperands() { return getTrueDestOperands(); }
    operand_range getFalseOperands() { return getFalseDestOperands(); }

    unsigned getNumFalseOperands() { return getFalseOperands().size(); }

    /// Erase the operand at 'index' from the false operand list.
    void eraseFalseOperand(unsigned index) {
      getFalseDestOperandsMutable().erase(index);
    }

  private:
    /// Get the index of the first true destination operand.
    unsigned getTrueDestOperandIndex() { return 1; }

    /// Get the index of the first false destination operand.
    unsigned getFalseDestOperandIndex() {
      return getTrueDestOperandIndex() + getNumTrueOperands();
    }
};

} // namespace mlir::cf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::cf::CondBranchOp)

namespace mlir::cf {


//===----------------------------------------------------------------------===//
// ::mlir::cf::SwitchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SwitchOpGenericAdaptorBase {
public:
  struct Properties {
    using case_operand_segmentsTy = ::mlir::DenseI32ArrayAttr;
    case_operand_segmentsTy case_operand_segments;

    auto getCaseOperandSegments() const {
      auto &propStorage = this->case_operand_segments;
      return ::llvm::cast<::mlir::DenseI32ArrayAttr>(propStorage);
    }
    void setCaseOperandSegments(const ::mlir::DenseI32ArrayAttr &propValue) {
      this->case_operand_segments = propValue;
    }
    using case_valuesTy = ::mlir::DenseIntElementsAttr;
    case_valuesTy case_values;

    auto getCaseValues() const {
      auto &propStorage = this->case_values;
      return ::llvm::dyn_cast_or_null<::mlir::DenseIntElementsAttr>(propStorage);
    }
    void setCaseValues(const ::mlir::DenseIntElementsAttr &propValue) {
      this->case_values = propValue;
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
        rhs.case_operand_segments == this->case_operand_segments &&
        rhs.case_values == this->case_values &&
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
  SwitchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("cf.switch", odsAttrs.getContext());
  }

  SwitchOpGenericAdaptorBase(SwitchOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseIntElementsAttr getCaseValuesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseIntElementsAttr>(getProperties().case_values);
    return attr;
  }

  ::std::optional< ::mlir::DenseIntElementsAttr > getCaseValues();
  ::mlir::DenseI32ArrayAttr getCaseOperandSegmentsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI32ArrayAttr>(getProperties().case_operand_segments);
    return attr;
  }

  ::llvm::ArrayRef<int32_t> getCaseOperandSegments();
};

} // namespace detail
template <typename RangeT>
class SwitchOpGenericAdaptor : public detail::SwitchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SwitchOpGenericAdaptorBase;
  static constexpr int odsIndex_flag = 0;
  static constexpr int odsIndex_defaultOperands = 1;
  static constexpr int odsIndex_caseOperands = 2;
public:
  SwitchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SwitchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SwitchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SwitchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : SwitchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SwitchOpGenericAdaptor(RangeT values, const SwitchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SwitchOp, typename = std::enable_if_t<std::is_same_v<LateInst, SwitchOp>>>
  SwitchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getFlag() {
    return (*getODSOperands(0).begin());
  }

  RangeT getDefaultOperands() {
    return getODSOperands(1);
  }

  ::llvm::SmallVector<RangeT> getCaseOperands() {
    auto tblgenTmpOperands = getODSOperands(2);
    auto sizes = getCaseOperandSegments();

    ::llvm::SmallVector<RangeT> tblgenTmpOperandGroups;
    for (int i = 0, e = sizes.size(); i < e; ++i) {
      tblgenTmpOperandGroups.push_back(tblgenTmpOperands.take_front(sizes[i]));
      tblgenTmpOperands = tblgenTmpOperands.drop_front(sizes[i]);
    }
    return tblgenTmpOperandGroups;
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SwitchOpAdaptor : public SwitchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SwitchOpGenericAdaptor::SwitchOpGenericAdaptor;
  SwitchOpAdaptor(SwitchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SwitchOp : public ::mlir::Op<SwitchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::AtLeastNSuccessors<1>::Impl, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::BranchOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SwitchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SwitchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_flag = 0;
  static constexpr int odsIndex_defaultOperands = 1;
  static constexpr int odsIndex_caseOperands = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::BranchOpInterface::Trait<SwitchOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("case_operand_segments"), ::llvm::StringRef("case_values"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCaseOperandSegmentsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCaseOperandSegmentsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getCaseValuesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getCaseValuesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("cf.switch");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getFlag() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getDefaultOperands() {
    return getODSOperands(1);
  }

  ::mlir::OperandRangeRange getCaseOperands() {
    return getODSOperands(2).split(getCaseOperandSegmentsAttr());
  }

  ::mlir::OpOperand &getFlagMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDefaultOperandsMutable();
  ::mlir::MutableOperandRangeRange getCaseOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Block *getDefaultDestination() {
    return (*this)->getSuccessor(0);
  }

  ::mlir::SuccessorRange getCaseDestinations() {
    return {std::next((*this)->successor_begin(), 1), (*this)->successor_end()};
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
  ::mlir::DenseIntElementsAttr getCaseValuesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseIntElementsAttr>(getProperties().case_values);
  }

  ::std::optional< ::mlir::DenseIntElementsAttr > getCaseValues();
  ::mlir::DenseI32ArrayAttr getCaseOperandSegmentsAttr() {
    return ::llvm::cast<::mlir::DenseI32ArrayAttr>(getProperties().case_operand_segments);
  }

  ::llvm::ArrayRef<int32_t> getCaseOperandSegments();
  void setCaseValuesAttr(::mlir::DenseIntElementsAttr attr) {
    getProperties().case_values = attr;
  }

  void setCaseOperandSegmentsAttr(::mlir::DenseI32ArrayAttr attr) {
    getProperties().case_operand_segments = attr;
  }

  void setCaseOperandSegments(::llvm::ArrayRef<int32_t> attrValue);
  ::mlir::Attribute removeCaseValuesAttr() {
      auto attr = getProperties().case_values;
      getProperties().case_values = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value flag, Block *defaultDestination, ValueRange defaultOperands, ArrayRef<APInt> caseValues = {}, BlockRange caseDestinations = {}, ArrayRef<ValueRange> caseOperands = {});
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value flag, Block *defaultDestination, ValueRange defaultOperands, ArrayRef<APInt> caseValues = {}, BlockRange caseDestinations = {}, ArrayRef<ValueRange> caseOperands = {});
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, Value flag, Block *defaultDestination, ValueRange defaultOperands, ArrayRef<APInt> caseValues = {}, BlockRange caseDestinations = {}, ArrayRef<ValueRange> caseOperands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value flag, Block *defaultDestination, ValueRange defaultOperands, ArrayRef<int32_t> caseValues = {}, BlockRange caseDestinations = {}, ArrayRef<ValueRange> caseOperands = {});
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value flag, Block *defaultDestination, ValueRange defaultOperands, ArrayRef<int32_t> caseValues = {}, BlockRange caseDestinations = {}, ArrayRef<ValueRange> caseOperands = {});
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, Value flag, Block *defaultDestination, ValueRange defaultOperands, ArrayRef<int32_t> caseValues = {}, BlockRange caseDestinations = {}, ArrayRef<ValueRange> caseOperands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value flag, Block *defaultDestination, ValueRange defaultOperands, DenseIntElementsAttr caseValues = {}, BlockRange caseDestinations = {}, ArrayRef<ValueRange> caseOperands = {});
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value flag, Block *defaultDestination, ValueRange defaultOperands, DenseIntElementsAttr caseValues = {}, BlockRange caseDestinations = {}, ArrayRef<ValueRange> caseOperands = {});
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, Value flag, Block *defaultDestination, ValueRange defaultOperands, DenseIntElementsAttr caseValues = {}, BlockRange caseDestinations = {}, ArrayRef<ValueRange> caseOperands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value flag, ::mlir::ValueRange defaultOperands, ::llvm::ArrayRef<::mlir::ValueRange> caseOperands, /*optional*/::mlir::DenseIntElementsAttr case_values, ::mlir::Block *defaultDestination, ::mlir::BlockRange caseDestinations);
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value flag, ::mlir::ValueRange defaultOperands, ::llvm::ArrayRef<::mlir::ValueRange> caseOperands, /*optional*/::mlir::DenseIntElementsAttr case_values, ::mlir::Block *defaultDestination, ::mlir::BlockRange caseDestinations);
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value flag, ::mlir::ValueRange defaultOperands, ::llvm::ArrayRef<::mlir::ValueRange> caseOperands, /*optional*/::mlir::DenseIntElementsAttr case_values, ::mlir::Block *defaultDestination, ::mlir::BlockRange caseDestinations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value flag, ::mlir::ValueRange defaultOperands, ::llvm::ArrayRef<::mlir::ValueRange> caseOperands, /*optional*/::mlir::DenseIntElementsAttr case_values, ::mlir::Block *defaultDestination, ::mlir::BlockRange caseDestinations);
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value flag, ::mlir::ValueRange defaultOperands, ::llvm::ArrayRef<::mlir::ValueRange> caseOperands, /*optional*/::mlir::DenseIntElementsAttr case_values, ::mlir::Block *defaultDestination, ::mlir::BlockRange caseDestinations);
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value flag, ::mlir::ValueRange defaultOperands, ::llvm::ArrayRef<::mlir::ValueRange> caseOperands, /*optional*/::mlir::DenseIntElementsAttr case_values, ::mlir::Block *defaultDestination, ::mlir::BlockRange caseDestinations);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::SuccessorOperands getSuccessorOperands(unsigned index);
  ::mlir::Block *getSuccessorForOperands(::llvm::ArrayRef<::mlir::Attribute> operands);
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
  /// Return the operands for the case destination block at the given index.
  OperandRange getCaseOperands(unsigned index) {
    return getCaseOperands()[index];
  }

  /// Return a mutable range of operands for the case destination block at the
  /// given index.
  MutableOperandRange getCaseOperandsMutable(unsigned index) {
    return getCaseOperandsMutable()[index];
  }
};

} // namespace mlir::cf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::cf::SwitchOp)


#endif // GET_OP_CLASSES

