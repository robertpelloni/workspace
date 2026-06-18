/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: tfrt_ops.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::TF {

/// Invokes a program via IFRT on a device
/// This op calls an IFRT program uniquely identified by the given program id.
/// 
///     During lowering from a `tf_device.cluster_func` op to a `tf.IfrtCall` op,
///     the region owned by the former will be outlined to a function with a
///     `tfrt_ifrt_serving.program_id` attribute. After that, the runtime ensures
///     that the outlined function is compiled into an executable and is available
///     for lookup from `IfrtCall` TF ops.
/// 
///     `variable_arg_indices` is a sorted (ascending order) array and indicates which
///     element of `args` is a key to a loaded array corresponding to a variable.
class IfrtCallOp;

} // namespace mlir::TF
namespace mlir::TF {

/// Loads a restored variable tensor as a tensor future
/// This op loads a restored variable tensor as a tensor future. It is a
///     replacement of `tf.ReadVariableOp`.
/// 
///     This op returns a scalar string tensor containing the restored variable name, which 
///     is composed from `container_name` and `shared_name` from a `var_handle` and can be
///     used as a key within the runtime, as well as a future for the tensor.
/// 
///     The `tf.IfrtCall` kernel uses the output $array_key.
///     Other ops executed by TFRT may make use of $tensor_future.
class IfrtLoadVariableOp;

} // namespace mlir::TF
namespace mlir::TF {

/// Deserialize resource vars.
/// This Op is a variant of IfrtResourceDeserialize for use with the
///      TFRT/IFRT runtime. It is not a stable interface.
class IfrtResourceDeserializeOp;

} // namespace mlir::TF
namespace mlir::TF {

/// Restore variable tensors
/// This Op is similar to a combination of RestoreV2 and AssignVariable Op, but
///     this Op's execution is asynchronous.
/// 
///     This Op is specific to TFRT + IFRT runtime and is not a stable interface for
///     serialization.
/// 
///     This Op will restore the tensors asynchronously. There are N restored tensors
///     corresponding to N $var_handle. Each restored tensor is given a unique name,
///     typically a concatenation of `container_name` and `shared_name` from a `var_handle`.
///     The runtime shall handle the possibility that the tensors are not ready when requested
///     because the tensors are loaded asynchronously.
class IfrtRestoreVariableOp;

} // namespace mlir::TF
namespace mlir::TF {

/// Streams results back to the controller
/// This op is a TensorFlow op that represents "streamed outputs", where
///     intermediate results can be returned immediately without waiting for the
///     entire signature computation to complete.
/// 
///     This op takes `args` with their `names` (their cardinality must match) and
///     sends the given argument tensors back to the serving controller. This
///     triggers a controller-side stream callback (see `ScopedStreamCallback`).
/// 
///     In addition to the listed attributes, this op has two "hidden" attributes
///     that do not exist in SavedModel but are dynamically populated by the serving
///     runtime:
/// 
///     * `_controller_address`: Address of the remote instance to which tensors
///       will be sent via e.g. RPC.
///     * `_callback_id`: Identifier for the callback to be called from the
///       controller. See `ScopedStreamCallback`.
class PwStreamResultsOp;

} // namespace mlir::TF
namespace mlir::TF {

/// Get values from TFRT runtime's static resource.
/// Getting tensor values from TFRT runtime's static resource manager, using
///     the indices that are previously set in _TfrtSetResource op.
///     `shared_name` and `container` are used to store identifying information for
///     resource tensors that have been hoisted. This is important for resource
///     alias analysis and side effect analysis. These are empty for non-resource
///     type tensors.
class _TfrtGetResourceOp;

} // namespace mlir::TF
namespace mlir::TF {

/// Set values as TFRT runtime's static resource.
/// Setting a tensor value in TFRT runtime's static resource manager, using
///     index as its identifier. It can be retrieved by _TfrtGetResource using the
///     same index.
class _TfrtSetResourceOp;

} // namespace mlir::TF
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::TF {


//===----------------------------------------------------------------------===//
// ::mlir::TF::IfrtCallOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IfrtCallOpGenericAdaptorBase {
public:
  struct Properties {
    using program_idTy = ::mlir::IntegerAttr;
    program_idTy program_id;

    auto getProgramId() const {
      auto &propStorage = this->program_id;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setProgramId(const ::mlir::IntegerAttr &propValue) {
      this->program_id = propValue;
    }
    using variable_arg_indicesTy = ::mlir::ArrayAttr;
    variable_arg_indicesTy variable_arg_indices;

    auto getVariableArgIndices() const {
      auto &propStorage = this->variable_arg_indices;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setVariableArgIndices(const ::mlir::ArrayAttr &propValue) {
      this->variable_arg_indices = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.program_id == this->program_id &&
        rhs.variable_arg_indices == this->variable_arg_indices &&
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
  IfrtCallOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf.IfrtCall", odsAttrs.getContext());
  }

  IfrtCallOpGenericAdaptorBase(IfrtCallOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getProgramIdAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().program_id);
    return attr;
  }

  uint64_t getProgramId();
  ::mlir::ArrayAttr getVariableArgIndicesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().variable_arg_indices);
    return attr;
  }

  ::mlir::ArrayAttr getVariableArgIndices();
};

} // namespace detail
template <typename RangeT>
class IfrtCallOpGenericAdaptor : public detail::IfrtCallOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IfrtCallOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  IfrtCallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IfrtCallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IfrtCallOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IfrtCallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IfrtCallOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IfrtCallOpGenericAdaptor(RangeT values, const IfrtCallOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IfrtCallOp, typename = std::enable_if_t<std::is_same_v<LateInst, IfrtCallOp>>>
  IfrtCallOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class IfrtCallOpAdaptor : public IfrtCallOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IfrtCallOpGenericAdaptor::IfrtCallOpGenericAdaptor;
  IfrtCallOpAdaptor(IfrtCallOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IfrtCallOp : public ::mlir::Op<IfrtCallOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::DerivedAttributeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IfrtCallOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IfrtCallOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_args = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("Tin"), ::llvm::StringRef("Tout"), ::llvm::StringRef("program_id"), ::llvm::StringRef("variable_arg_indices")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTinAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTinAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getToutAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getToutAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getProgramIdAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getProgramIdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getVariableArgIndicesAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getVariableArgIndicesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf.IfrtCall");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getArgs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
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
  ::mlir::IntegerAttr getProgramIdAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().program_id);
  }

  uint64_t getProgramId();
  ::mlir::ArrayAttr getVariableArgIndicesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().variable_arg_indices);
  }

  ::mlir::ArrayAttr getVariableArgIndices();
  mlir::OperandElementTypeRange getTin();
  mlir::ResultElementTypeRange getTout();
  static bool isDerivedAttribute(::llvm::StringRef name);
  ::mlir::DictionaryAttr materializeDerivedAttributes();
  void setProgramIdAttr(::mlir::IntegerAttr attr) {
    getProperties().program_id = attr;
  }

  void setProgramId(uint64_t attrValue);
  void setVariableArgIndicesAttr(::mlir::ArrayAttr attr) {
    getProperties().variable_arg_indices = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ValueRange args, ::mlir::IntegerAttr program_id, ::mlir::ArrayAttr variable_arg_indices);
  static IfrtCallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ValueRange args, ::mlir::IntegerAttr program_id, ::mlir::ArrayAttr variable_arg_indices);
  static IfrtCallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ValueRange args, ::mlir::IntegerAttr program_id, ::mlir::ArrayAttr variable_arg_indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ValueRange args, uint64_t program_id, ::mlir::ArrayAttr variable_arg_indices);
  static IfrtCallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ValueRange args, uint64_t program_id, ::mlir::ArrayAttr variable_arg_indices);
  static IfrtCallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ValueRange args, uint64_t program_id, ::mlir::ArrayAttr variable_arg_indices);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IfrtCallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IfrtCallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IfrtCallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IfrtCallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::TF
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TF::IfrtCallOp)

namespace mlir::TF {


//===----------------------------------------------------------------------===//
// ::mlir::TF::IfrtLoadVariableOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IfrtLoadVariableOpGenericAdaptorBase {
public:
  struct Properties {
    using used_by_hostTy = ::mlir::BoolAttr;
    used_by_hostTy used_by_host;

    auto getUsedByHost() const {
      auto &propStorage = this->used_by_host;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setUsedByHost(const ::mlir::BoolAttr &propValue) {
      this->used_by_host = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.used_by_host == this->used_by_host &&
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
  IfrtLoadVariableOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf.IfrtLoadVariable", odsAttrs.getContext());
  }

  IfrtLoadVariableOpGenericAdaptorBase(IfrtLoadVariableOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getUsedByHostAttr();
  bool getUsedByHost();
};

} // namespace detail
template <typename RangeT>
class IfrtLoadVariableOpGenericAdaptor : public detail::IfrtLoadVariableOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IfrtLoadVariableOpGenericAdaptorBase;
  static constexpr int odsIndex_variable = 0;
public:
  IfrtLoadVariableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IfrtLoadVariableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IfrtLoadVariableOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IfrtLoadVariableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IfrtLoadVariableOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IfrtLoadVariableOpGenericAdaptor(RangeT values, const IfrtLoadVariableOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IfrtLoadVariableOp, typename = std::enable_if_t<std::is_same_v<LateInst, IfrtLoadVariableOp>>>
  IfrtLoadVariableOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getVariable() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class IfrtLoadVariableOpAdaptor : public IfrtLoadVariableOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IfrtLoadVariableOpGenericAdaptor::IfrtLoadVariableOpGenericAdaptor;
  IfrtLoadVariableOpAdaptor(IfrtLoadVariableOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IfrtLoadVariableOp : public ::mlir::Op<IfrtLoadVariableOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::DerivedAttributeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IfrtLoadVariableOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IfrtLoadVariableOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_variable = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("Tin"), ::llvm::StringRef("Tout"), ::llvm::StringRef("used_by_host")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTinAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTinAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getToutAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getToutAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getUsedByHostAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getUsedByHostAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf.IfrtLoadVariable");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getVariable() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getVariableMutable() {
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

  ::mlir::TypedValue<::mlir::TensorType> getArrayKey() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::TensorType> getTensorFuture() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(1).begin());
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
  ::mlir::BoolAttr getUsedByHostAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().used_by_host);
  }

  bool getUsedByHost();
  mlir::OperandElementTypeRange getTin();
  mlir::ResultElementTypeRange getTout();
  static bool isDerivedAttribute(::llvm::StringRef name);
  ::mlir::DictionaryAttr materializeDerivedAttributes();
  void setUsedByHostAttr(::mlir::BoolAttr attr) {
    getProperties().used_by_host = attr;
  }

  void setUsedByHost(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type array_key, ::mlir::Type tensor_future, ::mlir::Value variable, ::mlir::BoolAttr used_by_host);
  static IfrtLoadVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type array_key, ::mlir::Type tensor_future, ::mlir::Value variable, ::mlir::BoolAttr used_by_host);
  static IfrtLoadVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type array_key, ::mlir::Type tensor_future, ::mlir::Value variable, ::mlir::BoolAttr used_by_host);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value variable, ::mlir::BoolAttr used_by_host);
  static IfrtLoadVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value variable, ::mlir::BoolAttr used_by_host);
  static IfrtLoadVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value variable, ::mlir::BoolAttr used_by_host);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type array_key, ::mlir::Type tensor_future, ::mlir::Value variable, bool used_by_host = false);
  static IfrtLoadVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type array_key, ::mlir::Type tensor_future, ::mlir::Value variable, bool used_by_host = false);
  static IfrtLoadVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type array_key, ::mlir::Type tensor_future, ::mlir::Value variable, bool used_by_host = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value variable, bool used_by_host = false);
  static IfrtLoadVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value variable, bool used_by_host = false);
  static IfrtLoadVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value variable, bool used_by_host = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IfrtLoadVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IfrtLoadVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IfrtLoadVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IfrtLoadVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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

} // namespace mlir::TF
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TF::IfrtLoadVariableOp)

namespace mlir::TF {


//===----------------------------------------------------------------------===//
// ::mlir::TF::IfrtResourceDeserializeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IfrtResourceDeserializeOpGenericAdaptorBase {
public:
  struct Properties {
    using require_matching_crcTy = ::mlir::BoolAttr;
    require_matching_crcTy require_matching_crc;

    auto getRequireMatchingCrc() const {
      auto &propStorage = this->require_matching_crc;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setRequireMatchingCrc(const ::mlir::BoolAttr &propValue) {
      this->require_matching_crc = propValue;
    }
    using tensor_nameTy = ::mlir::StringAttr;
    tensor_nameTy tensor_name;

    auto getTensorName() const {
      auto &propStorage = this->tensor_name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setTensorName(const ::mlir::StringAttr &propValue) {
      this->tensor_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.require_matching_crc == this->require_matching_crc &&
        rhs.tensor_name == this->tensor_name &&
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
  IfrtResourceDeserializeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf.IfrtResourceDeserialize", odsAttrs.getContext());
  }

  IfrtResourceDeserializeOpGenericAdaptorBase(IfrtResourceDeserializeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getRequireMatchingCrcAttr();
  bool getRequireMatchingCrc();
  ::mlir::StringAttr getTensorNameAttr();
  ::llvm::StringRef getTensorName();
};

} // namespace detail
template <typename RangeT>
class IfrtResourceDeserializeOpGenericAdaptor : public detail::IfrtResourceDeserializeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IfrtResourceDeserializeOpGenericAdaptorBase;
  static constexpr int odsIndex_resource_var = 0;
  static constexpr int odsIndex_input_dir = 1;
public:
  IfrtResourceDeserializeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IfrtResourceDeserializeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IfrtResourceDeserializeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IfrtResourceDeserializeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IfrtResourceDeserializeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IfrtResourceDeserializeOpGenericAdaptor(RangeT values, const IfrtResourceDeserializeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IfrtResourceDeserializeOp, typename = std::enable_if_t<std::is_same_v<LateInst, IfrtResourceDeserializeOp>>>
  IfrtResourceDeserializeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getResourceVar() {
    return (*getODSOperands(0).begin());
  }

  ValueT getInputDir() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class IfrtResourceDeserializeOpAdaptor : public IfrtResourceDeserializeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IfrtResourceDeserializeOpGenericAdaptor::IfrtResourceDeserializeOpGenericAdaptor;
  IfrtResourceDeserializeOpAdaptor(IfrtResourceDeserializeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IfrtResourceDeserializeOp : public ::mlir::Op<IfrtResourceDeserializeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IfrtResourceDeserializeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IfrtResourceDeserializeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_resource_var = 0;
  static constexpr int odsIndex_input_dir = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("require_matching_crc"), ::llvm::StringRef("tensor_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getRequireMatchingCrcAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getRequireMatchingCrcAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTensorNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTensorNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf.IfrtResourceDeserialize");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getResourceVar() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::TensorType> getInputDir() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getResourceVarMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getInputDirMutable() {
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
  ::mlir::BoolAttr getRequireMatchingCrcAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().require_matching_crc);
  }

  bool getRequireMatchingCrc();
  ::mlir::StringAttr getTensorNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().tensor_name);
  }

  ::llvm::StringRef getTensorName();
  void setRequireMatchingCrcAttr(::mlir::BoolAttr attr) {
    getProperties().require_matching_crc = attr;
  }

  void setRequireMatchingCrc(::std::optional<bool> attrValue);
  void setTensorNameAttr(::mlir::StringAttr attr) {
    getProperties().tensor_name = attr;
  }

  void setTensorName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeRequireMatchingCrcAttr() {
      auto attr = getProperties().require_matching_crc;
      getProperties().require_matching_crc = {};
      return attr;
  }

  ::mlir::Attribute removeTensorNameAttr() {
      auto attr = getProperties().tensor_name;
      getProperties().tensor_name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/::mlir::BoolAttr require_matching_crc, /*optional*/::mlir::StringAttr tensor_name = nullptr);
  static IfrtResourceDeserializeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/::mlir::BoolAttr require_matching_crc, /*optional*/::mlir::StringAttr tensor_name = nullptr);
  static IfrtResourceDeserializeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/::mlir::BoolAttr require_matching_crc, /*optional*/::mlir::StringAttr tensor_name = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/::mlir::BoolAttr require_matching_crc, /*optional*/::mlir::StringAttr tensor_name = nullptr);
  static IfrtResourceDeserializeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/::mlir::BoolAttr require_matching_crc, /*optional*/::mlir::StringAttr tensor_name = nullptr);
  static IfrtResourceDeserializeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/::mlir::BoolAttr require_matching_crc, /*optional*/::mlir::StringAttr tensor_name = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/bool require_matching_crc = true, /*optional*/::llvm::StringRef tensor_name = "");
  static IfrtResourceDeserializeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/bool require_matching_crc = true, /*optional*/::llvm::StringRef tensor_name = "");
  static IfrtResourceDeserializeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/bool require_matching_crc = true, /*optional*/::llvm::StringRef tensor_name = "");
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/bool require_matching_crc = true, /*optional*/::llvm::StringRef tensor_name = "");
  static IfrtResourceDeserializeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/bool require_matching_crc = true, /*optional*/::llvm::StringRef tensor_name = "");
  static IfrtResourceDeserializeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value resource_var, ::mlir::Value input_dir, /*optional*/bool require_matching_crc = true, /*optional*/::llvm::StringRef tensor_name = "");
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IfrtResourceDeserializeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IfrtResourceDeserializeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IfrtResourceDeserializeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IfrtResourceDeserializeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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

} // namespace mlir::TF
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TF::IfrtResourceDeserializeOp)

namespace mlir::TF {


//===----------------------------------------------------------------------===//
// ::mlir::TF::IfrtRestoreVariableOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IfrtRestoreVariableOpGenericAdaptorBase {
public:
  struct Properties {
    using restored_dtypesTy = ::mlir::ArrayAttr;
    restored_dtypesTy restored_dtypes;

    auto getRestoredDtypes() const {
      auto &propStorage = this->restored_dtypes;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setRestoredDtypes(const ::mlir::ArrayAttr &propValue) {
      this->restored_dtypes = propValue;
    }
    using truncate_in_castTy = ::mlir::DenseBoolArrayAttr;
    truncate_in_castTy truncate_in_cast;

    auto getTruncateInCast() const {
      auto &propStorage = this->truncate_in_cast;
      return ::llvm::cast<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setTruncateInCast(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->truncate_in_cast = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.restored_dtypes == this->restored_dtypes &&
        rhs.truncate_in_cast == this->truncate_in_cast &&
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
  IfrtRestoreVariableOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf.IfrtRestoreVariableOp", odsAttrs.getContext());
  }

  IfrtRestoreVariableOpGenericAdaptorBase(IfrtRestoreVariableOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getRestoredDtypesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().restored_dtypes);
    return attr;
  }

  ::mlir::ArrayAttr getRestoredDtypes();
  ::mlir::DenseBoolArrayAttr getTruncateInCastAttr() {
    auto attr = ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().truncate_in_cast);
    return attr;
  }

  ::llvm::ArrayRef<bool> getTruncateInCast();
};

} // namespace detail
template <typename RangeT>
class IfrtRestoreVariableOpGenericAdaptor : public detail::IfrtRestoreVariableOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IfrtRestoreVariableOpGenericAdaptorBase;
  static constexpr int odsIndex_prefix = 0;
  static constexpr int odsIndex_tensor_names = 1;
  static constexpr int odsIndex_shape_and_slices = 2;
  static constexpr int odsIndex_var_handles = 3;
public:
  IfrtRestoreVariableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IfrtRestoreVariableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IfrtRestoreVariableOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IfrtRestoreVariableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IfrtRestoreVariableOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IfrtRestoreVariableOpGenericAdaptor(RangeT values, const IfrtRestoreVariableOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IfrtRestoreVariableOp, typename = std::enable_if_t<std::is_same_v<LateInst, IfrtRestoreVariableOp>>>
  IfrtRestoreVariableOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPrefix() {
    return (*getODSOperands(0).begin());
  }

  ValueT getTensorNames() {
    return (*getODSOperands(1).begin());
  }

  ValueT getShapeAndSlices() {
    return (*getODSOperands(2).begin());
  }

  RangeT getVarHandles() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class IfrtRestoreVariableOpAdaptor : public IfrtRestoreVariableOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IfrtRestoreVariableOpGenericAdaptor::IfrtRestoreVariableOpGenericAdaptor;
  IfrtRestoreVariableOpAdaptor(IfrtRestoreVariableOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IfrtRestoreVariableOp : public ::mlir::Op<IfrtRestoreVariableOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IfrtRestoreVariableOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IfrtRestoreVariableOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_prefix = 0;
  static constexpr int odsIndex_tensor_names = 1;
  static constexpr int odsIndex_shape_and_slices = 2;
  static constexpr int odsIndex_var_handles = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("restored_dtypes"), ::llvm::StringRef("truncate_in_cast")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getRestoredDtypesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getRestoredDtypesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTruncateInCastAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTruncateInCastAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf.IfrtRestoreVariableOp");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getPrefix() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::TensorType> getTensorNames() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::TensorType> getShapeAndSlices() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(2).begin());
  }

  ::mlir::Operation::operand_range getVarHandles() {
    return getODSOperands(3);
  }

  ::mlir::OpOperand &getPrefixMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTensorNamesMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getShapeAndSlicesMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getVarHandlesMutable();
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
  ::mlir::ArrayAttr getRestoredDtypesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().restored_dtypes);
  }

  ::mlir::ArrayAttr getRestoredDtypes();
  ::mlir::DenseBoolArrayAttr getTruncateInCastAttr() {
    return ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().truncate_in_cast);
  }

  ::llvm::ArrayRef<bool> getTruncateInCast();
  void setRestoredDtypesAttr(::mlir::ArrayAttr attr) {
    getProperties().restored_dtypes = attr;
  }

  void setTruncateInCastAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().truncate_in_cast = attr;
  }

  void setTruncateInCast(::llvm::ArrayRef<bool> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::mlir::DenseBoolArrayAttr truncate_in_cast);
  static IfrtRestoreVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::mlir::DenseBoolArrayAttr truncate_in_cast);
  static IfrtRestoreVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::mlir::DenseBoolArrayAttr truncate_in_cast);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::mlir::DenseBoolArrayAttr truncate_in_cast);
  static IfrtRestoreVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::mlir::DenseBoolArrayAttr truncate_in_cast);
  static IfrtRestoreVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::mlir::DenseBoolArrayAttr truncate_in_cast);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::llvm::ArrayRef<bool> truncate_in_cast);
  static IfrtRestoreVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::llvm::ArrayRef<bool> truncate_in_cast);
  static IfrtRestoreVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::llvm::ArrayRef<bool> truncate_in_cast);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::llvm::ArrayRef<bool> truncate_in_cast);
  static IfrtRestoreVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::llvm::ArrayRef<bool> truncate_in_cast);
  static IfrtRestoreVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value prefix, ::mlir::Value tensor_names, ::mlir::Value shape_and_slices, ::mlir::ValueRange var_handles, ::mlir::ArrayAttr restored_dtypes, ::llvm::ArrayRef<bool> truncate_in_cast);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IfrtRestoreVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IfrtRestoreVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IfrtRestoreVariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IfrtRestoreVariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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

} // namespace mlir::TF
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TF::IfrtRestoreVariableOp)

namespace mlir::TF {


//===----------------------------------------------------------------------===//
// ::mlir::TF::PwStreamResultsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PwStreamResultsOpGenericAdaptorBase {
public:
  struct Properties {
    using namesTy = ::mlir::ArrayAttr;
    namesTy names;

    auto getNames() const {
      auto &propStorage = this->names;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setNames(const ::mlir::ArrayAttr &propValue) {
      this->names = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.names == this->names &&
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
  PwStreamResultsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf.PwStreamResults", odsAttrs.getContext());
  }

  PwStreamResultsOpGenericAdaptorBase(PwStreamResultsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().names);
    return attr;
  }

  ::mlir::ArrayAttr getNames();
};

} // namespace detail
template <typename RangeT>
class PwStreamResultsOpGenericAdaptor : public detail::PwStreamResultsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PwStreamResultsOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  PwStreamResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PwStreamResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PwStreamResultsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PwStreamResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PwStreamResultsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PwStreamResultsOpGenericAdaptor(RangeT values, const PwStreamResultsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PwStreamResultsOp, typename = std::enable_if_t<std::is_same_v<LateInst, PwStreamResultsOp>>>
  PwStreamResultsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PwStreamResultsOpAdaptor : public PwStreamResultsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PwStreamResultsOpGenericAdaptor::PwStreamResultsOpGenericAdaptor;
  PwStreamResultsOpAdaptor(PwStreamResultsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PwStreamResultsOp : public ::mlir::Op<PwStreamResultsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::DerivedAttributeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PwStreamResultsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PwStreamResultsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_args = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("T"), ::llvm::StringRef("names")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNamesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf.PwStreamResults");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getArgs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getArgsMutable();
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
  ::mlir::ArrayAttr getNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().names);
  }

  ::mlir::ArrayAttr getNames();
  mlir::OperandElementTypeRange getT();
  static bool isDerivedAttribute(::llvm::StringRef name);
  ::mlir::DictionaryAttr materializeDerivedAttributes();
  void setNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().names = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange args, ::mlir::ArrayAttr names);
  static PwStreamResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange args, ::mlir::ArrayAttr names);
  static PwStreamResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange args, ::mlir::ArrayAttr names);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::ArrayAttr names);
  static PwStreamResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::ArrayAttr names);
  static PwStreamResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::ArrayAttr names);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PwStreamResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PwStreamResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PwStreamResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PwStreamResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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

} // namespace mlir::TF
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TF::PwStreamResultsOp)

namespace mlir::TF {


//===----------------------------------------------------------------------===//
// ::mlir::TF::_TfrtGetResourceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class _TfrtGetResourceOpGenericAdaptorBase {
public:
  struct Properties {
    using containerTy = ::mlir::ArrayAttr;
    containerTy container;

    auto getContainer() const {
      auto &propStorage = this->container;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setContainer(const ::mlir::ArrayAttr &propValue) {
      this->container = propValue;
    }
    using indicesTy = ::mlir::ArrayAttr;
    indicesTy indices;

    auto getIndices() const {
      auto &propStorage = this->indices;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setIndices(const ::mlir::ArrayAttr &propValue) {
      this->indices = propValue;
    }
    using shared_nameTy = ::mlir::ArrayAttr;
    shared_nameTy shared_name;

    auto getSharedName() const {
      auto &propStorage = this->shared_name;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setSharedName(const ::mlir::ArrayAttr &propValue) {
      this->shared_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.container == this->container &&
        rhs.indices == this->indices &&
        rhs.shared_name == this->shared_name &&
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
  _TfrtGetResourceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf._TfrtGetResource", odsAttrs.getContext());
  }

  _TfrtGetResourceOpGenericAdaptorBase(_TfrtGetResourceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getIndicesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().indices);
    return attr;
  }

  ::mlir::ArrayAttr getIndices();
  ::mlir::ArrayAttr getSharedNameAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().shared_name);
    return attr;
  }

  ::mlir::ArrayAttr getSharedName();
  ::mlir::ArrayAttr getContainerAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().container);
    return attr;
  }

  ::mlir::ArrayAttr getContainer();
};

} // namespace detail
template <typename RangeT>
class _TfrtGetResourceOpGenericAdaptor : public detail::_TfrtGetResourceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::_TfrtGetResourceOpGenericAdaptorBase;
public:
  _TfrtGetResourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  _TfrtGetResourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : _TfrtGetResourceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  _TfrtGetResourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : _TfrtGetResourceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  _TfrtGetResourceOpGenericAdaptor(RangeT values, const _TfrtGetResourceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = _TfrtGetResourceOp, typename = std::enable_if_t<std::is_same_v<LateInst, _TfrtGetResourceOp>>>
  _TfrtGetResourceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class _TfrtGetResourceOpAdaptor : public _TfrtGetResourceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using _TfrtGetResourceOpGenericAdaptor::_TfrtGetResourceOpGenericAdaptor;
  _TfrtGetResourceOpAdaptor(_TfrtGetResourceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class _TfrtGetResourceOp : public ::mlir::Op<_TfrtGetResourceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::TF::NoConstantFold, ResourceHandleAllocatorInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = _TfrtGetResourceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = _TfrtGetResourceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("container"), ::llvm::StringRef("indices"), ::llvm::StringRef("shared_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getContainerAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getContainerAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIndicesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIndicesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSharedNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSharedNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf._TfrtGetResource");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
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
  ::mlir::ArrayAttr getIndicesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().indices);
  }

  ::mlir::ArrayAttr getIndices();
  ::mlir::ArrayAttr getSharedNameAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().shared_name);
  }

  ::mlir::ArrayAttr getSharedName();
  ::mlir::ArrayAttr getContainerAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().container);
  }

  ::mlir::ArrayAttr getContainer();
  void setIndicesAttr(::mlir::ArrayAttr attr) {
    getProperties().indices = attr;
  }

  void setSharedNameAttr(::mlir::ArrayAttr attr) {
    getProperties().shared_name = attr;
  }

  void setContainerAttr(::mlir::ArrayAttr attr) {
    getProperties().container = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ArrayAttr indices, ::mlir::ArrayAttr shared_name, ::mlir::ArrayAttr container);
  static _TfrtGetResourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ArrayAttr indices, ::mlir::ArrayAttr shared_name, ::mlir::ArrayAttr container);
  static _TfrtGetResourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ArrayAttr indices, ::mlir::ArrayAttr shared_name, ::mlir::ArrayAttr container);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static _TfrtGetResourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static _TfrtGetResourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static _TfrtGetResourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static _TfrtGetResourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  llvm::SmallVector<ResourceHandleValueAndId, 4> GetResourceHandleValueAndIdList(llvm::SmallDenseMap<ResourceHandle, int64_t>&resource_handle_id_map, int64_t&next_id);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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

} // namespace mlir::TF
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TF::_TfrtGetResourceOp)

namespace mlir::TF {


//===----------------------------------------------------------------------===//
// ::mlir::TF::_TfrtSetResourceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class _TfrtSetResourceOpGenericAdaptorBase {
public:
  struct Properties {
    using indexTy = ::mlir::IntegerAttr;
    indexTy index;

    auto getIndex() const {
      auto &propStorage = this->index;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setIndex(const ::mlir::IntegerAttr &propValue) {
      this->index = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.index == this->index &&
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
  _TfrtSetResourceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf._TfrtSetResource", odsAttrs.getContext());
  }

  _TfrtSetResourceOpGenericAdaptorBase(_TfrtSetResourceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getIndexAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().index);
    return attr;
  }

  uint64_t getIndex();
};

} // namespace detail
template <typename RangeT>
class _TfrtSetResourceOpGenericAdaptor : public detail::_TfrtSetResourceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::_TfrtSetResourceOpGenericAdaptorBase;
  static constexpr int odsIndex_arg = 0;
public:
  _TfrtSetResourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  _TfrtSetResourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : _TfrtSetResourceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  _TfrtSetResourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : _TfrtSetResourceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  _TfrtSetResourceOpGenericAdaptor(RangeT values, const _TfrtSetResourceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = _TfrtSetResourceOp, typename = std::enable_if_t<std::is_same_v<LateInst, _TfrtSetResourceOp>>>
  _TfrtSetResourceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class _TfrtSetResourceOpAdaptor : public _TfrtSetResourceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using _TfrtSetResourceOpGenericAdaptor::_TfrtSetResourceOpGenericAdaptor;
  _TfrtSetResourceOpAdaptor(_TfrtSetResourceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class _TfrtSetResourceOp : public ::mlir::Op<_TfrtSetResourceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = _TfrtSetResourceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = _TfrtSetResourceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_arg = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("index")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIndexAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIndexAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf._TfrtSetResource");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getArg() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
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
  ::mlir::IntegerAttr getIndexAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().index);
  }

  uint64_t getIndex();
  void setIndexAttr(::mlir::IntegerAttr attr) {
    getProperties().index = attr;
  }

  void setIndex(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value arg, ::mlir::IntegerAttr index);
  static _TfrtSetResourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value arg, ::mlir::IntegerAttr index);
  static _TfrtSetResourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value arg, ::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value arg, ::mlir::IntegerAttr index);
  static _TfrtSetResourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value arg, ::mlir::IntegerAttr index);
  static _TfrtSetResourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value arg, ::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value arg, uint64_t index);
  static _TfrtSetResourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value arg, uint64_t index);
  static _TfrtSetResourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value arg, uint64_t index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value arg, uint64_t index);
  static _TfrtSetResourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value arg, uint64_t index);
  static _TfrtSetResourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value arg, uint64_t index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static _TfrtSetResourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static _TfrtSetResourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static _TfrtSetResourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static _TfrtSetResourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace mlir::TF
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TF::_TfrtSetResourceOp)


#endif // GET_OP_CLASSES

