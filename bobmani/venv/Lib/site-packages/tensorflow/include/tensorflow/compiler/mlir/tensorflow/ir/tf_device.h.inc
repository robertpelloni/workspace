/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: tf_device_ops.td                                                     *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::tf_device {

/// The `tf_device.cluster_func` launches a function containing the body of a
/// cluster.
/// This op is used for outlining a cluster.
class ClusterFuncOp;

} // namespace mlir::tf_device
namespace mlir::tf_device {

/// The `tf_device.cluster` op wraps containing operations in a region.
/// This op can be used to group operations, and captures all needed live-in values.
/// 
/// Optional policy attribute allows to tag clusters with a policy name that was
/// used to form the cluster.
class ClusterOp;

} // namespace mlir::tf_device
namespace mlir::tf_device {

/// The `tf_device.launch_func` launches a function on target device.
class LaunchFuncOp;

} // namespace mlir::tf_device
namespace mlir::tf_device {

/// The `tf_device.launch` op launches containing operations on target device.
/// This op captures all needed live-in values.
class LaunchOp;

} // namespace mlir::tf_device
namespace mlir::tf_device {

/// ParallelExecute op concurrently executes variadic number of regions. Regions
///     must represent separate sets of instructions to execute concurrently. In
///     order to represent concurrently executed regions with dependencies, multiple
///     ParallelExecute ops can be used instead. As so, regions within
///     ParallelExecute op must not have control/data dependencies.
/// 
///     While explicit dependencies between regions are disallowed, ParallelExecute
///     op does not prevent implicit communication between regions (e.g.
///     communication via send/recvs). In this case, users of ParallelExecute op
///     must provide correct control dependencies between regions to guarantee
///     correctness. Regions in ParallelExecute may include Resource ops.
/// 
///     In the case where different regions include ops access the same resource,
///     the users of the ParallelExecute op must provide mechanism (via send/recvs
///     or via control dependencies) to guarantee correct ordering. Sequential
///     ordering of ops within a region is guaranteed. Also, sequential ordering of
///     ops before/after ParallelExecute ops are guaranteed. That is, execution of
///     regions inside ParallelExecute op is blocked until all inputs to all regions
///     are materialized and ops following ParallelExecute op are blocked until all
///     regions are executed.
class ParallelExecuteOp;

} // namespace mlir::tf_device
namespace mlir::tf_device {

/// Rceive a value from a host.
/// Receive a value from the given host with the given rendezvous key.
class ReceiveOp;

} // namespace mlir::tf_device
namespace mlir::tf_device {

/// The `tf_device.remote_run` op launches the containing operations on a specific
/// host.
/// This op captures all needed live-in values.
class RemoteRunOp;

} // namespace mlir::tf_device
namespace mlir::tf_device {

/// Wraps an N-way replicated computation.
/// The region held by this operation represents a computation that is replicated
/// across multiple devices. The number of replications is based on the `n`
/// attribute. Explicit devices can be populated in the `devices` attribute, and it
/// must be a mapping of device alias to list of explicit or aliased device names
/// from the outer scope. The device name map specifies devices on which replicated
/// ops inside tf_device.replicate will be executed.
/// 
/// A tf_device.parallel_execute inside the tf_device.replicate op region may be
/// used to represent computations across a larger set of devices. In that case, the
/// device alias can be used to specify device assignment and replication of each
/// concurrent execution (i.e. region) defined by tf_device.parallel_execute op.
/// The size of each value list in the device name map must match `n`. Within a
/// replica, the execution semantics follow standard sequential behavior. Ops in the
/// tf_device.replicate wrapped with a tf_device.launch will have its device set to
/// the associated replicated device from `devices` if the tf_device.launch refers
/// to an aliased device name. Otherwise the device already set in tf_device.launch
/// is used instead.
/// 
/// Operands are replicated inputs and packed inputs.
/// 
/// replicated_inputs: each group of `n` inputs corresponds to an input for a single
/// individual replica and is mapped to a single region argument. Inside one group
/// the operands are matching in order the `devices` attribute. Each replicated
/// input must have compatible shapes and types.
/// packed_inputs: each input corresponds to an input broadcasted across all
/// replicas and is mapped to a single region argument.
/// 
/// Operands not replicated can be implicitly captured by ops in the region. Results
/// are replicated each from the regions terminator.
/// 
/// For example:
/// ```
/// %0 = "tf.opA"() : () -> tensor<i32>
/// %1 = "tf.opB"() : () -> tensor<i32>
/// %2 = "tf.opC"() : () -> tensor<f32>
/// %3 = "tf.opD"() : () -> tensor<f32>
/// %4 = "tf.opE"() : () -> tensor<!tf_type.resource>
/// %5 = "tf.opF"() : () -> tensor<!tf_type.resource>
/// %6 = "tf.opG"() : () -> tensor<!tf_type.string>
/// %7 = "tf.opH"() : () -> tensor<!tf_type.string>
/// %8 = "tf.opI"() : () -> tensor<!tf_type.variant>
/// %9 = "tf.opJ"() : () -> tensor<i1>
/// %output:8 = tf_device.replicate([%0, %1] as %input_0: tensor<i32>,
///                                 [%2, %3] as %input_1: tensor<f32>,
///                                 [%4, %5] as %input_2: tensor<!tf_type.resource>,
///                                 [%6, %7] as %input_3: tensor<!tf_type.string>,
///                                 %8 as %input_4: tensor<!tf_type.variant>)
///                 {n = 2 : i32,
///                  devices = {DEVICE_ALIAS_0 = ["/DEVICE:0", "/DEVICE:1"],
///                             DEVICE_ALIAS_1 = ["/DEVICE:2", "/DEVICE:3"]}} {
///   // Inside the region, %0, %2, %4, and %6 corresponds to
///   // "/DEVICE:0"/"/DEVICE:2" and %1, %3, %5, and %7 corresponds to
///   // "/DEVICE:1"/"/DEVICE:3", depending on which device alias is used.
///   %k = "tf_device.launch"() ( {
///     %9 = "tf.opK"(%input_0, %input_4, %9) :
///       (tensor<i32>, tensor<!tf_type.variant>, tensor<i1>) -> tensor<i32>
///     tf_device.return %9 : tensor<i32>
///   }) {device = "DEVICE_ALIAS_0"} : () -> tensor<i32>
///   %l = "tf_device.launch"() ( {
///     %10 = "tf.opL"(%input_1, %input_4, %9) :
///       (tensor<f32>, tensor<!tf_type.variant>, tensor<i1>) -> tensor<f32>
///     tf_device.return %10 : tensor<f32>
///   }) {device = "DEVICE_ALIAS_1"} : () -> tensor<f32>
///   %m = "tf_device.launch"() ( {
///     %11 = "tf.opM"(%input_2, %input_4, %9) :
///       (tensor<!tf_type.resource>, tensor<!tf_type.variant>, tensor<i1>)
///         -> tensor<!tf_type.resource>
///     tf_device.return %11 : tensor<!tf_type.resource>
///   }) {device = "/DEVICE:4"} : () -> tensor<f32>
///   %n = "tf.opN"(%input_3, %input_4, %9) :
///     (tensor<!tf_type.string>, tensor<!tf_type.variant>, tensor<i1>)
///       -> tensor<!tf_type.string>
///   tf_device.return %k, %l, %m, %n :
///     tensor<i32>, tensor<f32>, tensor<!tf_type.resource>, tensor<!tf_type.string>
/// }
/// // %output#0 corresponds to %k returned from "/DEVICE:0"
/// // %output#1 corresponds to %k returned from "/DEVICE:1"
/// // %output#2 corresponds to %l returned from "/DEVICE:2"
/// // %output#3 corresponds to %l returned from "/DEVICE:3"
/// // %output#4, %output#5 corresponds to %m and will be returned from "/DEVICE:4"
/// // %output#6, %output#7 corresponds to %n and will have no device set
/// ```
class ReplicateOp;

} // namespace mlir::tf_device
namespace mlir::tf_device {

/// The `tf_device.return` operation terminates and returns values from a
/// `tf_device` dialect operation.
class ReturnOp;

} // namespace mlir::tf_device
namespace mlir::tf_device {

/// Send a value to a host.
/// Send the value to the given host with the given rendezvous key.
class SendOp;

} // namespace mlir::tf_device
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::tf_device {


//===----------------------------------------------------------------------===//
// ::mlir::tf_device::ClusterFuncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClusterFuncOpGenericAdaptorBase {
public:
  struct Properties {
    using funcTy = ::mlir::FlatSymbolRefAttr;
    funcTy func;

    auto getFunc() const {
      auto &propStorage = this->func;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setFunc(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->func = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.func == this->func &&
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
  ClusterFuncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_device.cluster_func", odsAttrs.getContext());
  }

  ClusterFuncOpGenericAdaptorBase(ClusterFuncOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getFuncAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().func);
    return attr;
  }

  ::llvm::StringRef getFunc();
};

} // namespace detail
template <typename RangeT>
class ClusterFuncOpGenericAdaptor : public detail::ClusterFuncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClusterFuncOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  ClusterFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClusterFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ClusterFuncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClusterFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClusterFuncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClusterFuncOpGenericAdaptor(RangeT values, const ClusterFuncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClusterFuncOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClusterFuncOp>>>
  ClusterFuncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ClusterFuncOpAdaptor : public ClusterFuncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClusterFuncOpGenericAdaptor::ClusterFuncOpGenericAdaptor;
  ClusterFuncOpAdaptor(ClusterFuncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClusterFuncOp : public ::mlir::Op<ClusterFuncOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClusterFuncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClusterFuncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_args = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("func")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFuncAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFuncAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_device.cluster_func");
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
  ::mlir::FlatSymbolRefAttr getFuncAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().func);
  }

  ::llvm::StringRef getFunc();
  void setFuncAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().func = attr;
  }

  void setFunc(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr func, ::mlir::ValueRange args);
  static ClusterFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr func, ::mlir::ValueRange args);
  static ClusterFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr func, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef func, ::mlir::ValueRange args);
  static ClusterFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef func, ::mlir::ValueRange args);
  static ClusterFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef func, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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
  // Gets the argument operands to the called function.
  operand_range getArgOperands() { return getArgs(); }
  MutableOperandRange getArgOperandsMutable() {
    return getArgsMutable();
  }
  // returns the function that this operation will launch.
  func::FuncOp getFuncOp() {
    return SymbolTable::lookupNearestSymbolFrom<func::FuncOp>(*this, getFuncAttr());
  }
  CallInterfaceCallable getCallableForCallee() {
    return getFuncAttr();
  }
  void setCalleeFromCallable(::mlir::CallInterfaceCallable callee);
  Attribute removeArgAttrsAttr() { return nullptr; }
  Attribute removeResAttrsAttr() { return nullptr; }
  ArrayAttr getArgAttrsAttr() { return nullptr; }
  ArrayAttr getResAttrsAttr() { return nullptr; }
  void setArgAttrsAttr(ArrayAttr) { return; }
  void setResAttrsAttr(ArrayAttr) { return; }
};

} // namespace mlir::tf_device
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_device::ClusterFuncOp)

namespace mlir::tf_device {


//===----------------------------------------------------------------------===//
// ::mlir::tf_device::ClusterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClusterOpGenericAdaptorBase {
public:
  struct Properties {
    using policyTy = ::mlir::StringAttr;
    policyTy policy;

    auto getPolicy() const {
      auto &propStorage = this->policy;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setPolicy(const ::mlir::StringAttr &propValue) {
      this->policy = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.policy == this->policy &&
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
  ClusterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_device.cluster", odsAttrs.getContext());
  }

  ClusterOpGenericAdaptorBase(ClusterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getPolicyAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().policy);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getPolicy();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ClusterOpGenericAdaptor : public detail::ClusterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClusterOpGenericAdaptorBase;
public:
  ClusterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClusterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ClusterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClusterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClusterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClusterOpGenericAdaptor(RangeT values, const ClusterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClusterOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClusterOp>>>
  ClusterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ClusterOpAdaptor : public ClusterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClusterOpGenericAdaptor::ClusterOpGenericAdaptor;
  ClusterOpAdaptor(ClusterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClusterOp : public ::mlir::Op<ClusterOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<ReturnOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClusterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClusterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("policy")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPolicyAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPolicyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_device.cluster");
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
  ::mlir::StringAttr getPolicyAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().policy);
  }

  ::std::optional< ::llvm::StringRef > getPolicy();
  void setPolicyAttr(::mlir::StringAttr attr) {
    getProperties().policy = attr;
  }

  void setPolicy(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removePolicyAttr() {
      auto attr = getProperties().policy;
      getProperties().policy = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes);
  static ClusterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes);
  static ClusterOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, /*optional*/::mlir::StringAttr policy);
  static ClusterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, /*optional*/::mlir::StringAttr policy);
  static ClusterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, /*optional*/::mlir::StringAttr policy);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  Block &GetBody() { return getOperation()->getRegion(0).front(); }
};

} // namespace mlir::tf_device
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_device::ClusterOp)

namespace mlir::tf_device {


//===----------------------------------------------------------------------===//
// ::mlir::tf_device::LaunchFuncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LaunchFuncOpGenericAdaptorBase {
public:
  struct Properties {
    using deviceTy = ::mlir::StringAttr;
    deviceTy device;

    auto getDevice() const {
      auto &propStorage = this->device;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setDevice(const ::mlir::StringAttr &propValue) {
      this->device = propValue;
    }
    using funcTy = ::mlir::FlatSymbolRefAttr;
    funcTy func;

    auto getFunc() const {
      auto &propStorage = this->func;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setFunc(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->func = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.device == this->device &&
        rhs.func == this->func &&
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
  LaunchFuncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_device.launch_func", odsAttrs.getContext());
  }

  LaunchFuncOpGenericAdaptorBase(LaunchFuncOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getDeviceAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().device);
    return attr;
  }

  ::llvm::StringRef getDevice();
  ::mlir::FlatSymbolRefAttr getFuncAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().func);
    return attr;
  }

  ::llvm::StringRef getFunc();
};

} // namespace detail
template <typename RangeT>
class LaunchFuncOpGenericAdaptor : public detail::LaunchFuncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LaunchFuncOpGenericAdaptorBase;
public:
  LaunchFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LaunchFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LaunchFuncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LaunchFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LaunchFuncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LaunchFuncOpGenericAdaptor(RangeT values, const LaunchFuncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LaunchFuncOp, typename = std::enable_if_t<std::is_same_v<LateInst, LaunchFuncOp>>>
  LaunchFuncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class LaunchFuncOpAdaptor : public LaunchFuncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LaunchFuncOpGenericAdaptor::LaunchFuncOpGenericAdaptor;
  LaunchFuncOpAdaptor(LaunchFuncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LaunchFuncOp : public ::mlir::Op<LaunchFuncOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LaunchFuncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LaunchFuncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("device"), ::llvm::StringRef("func")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDeviceAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDeviceAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFuncAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFuncAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_device.launch_func");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
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
  ::mlir::StringAttr getDeviceAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().device);
  }

  ::llvm::StringRef getDevice();
  ::mlir::FlatSymbolRefAttr getFuncAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().func);
  }

  ::llvm::StringRef getFunc();
  void setDeviceAttr(::mlir::StringAttr attr) {
    getProperties().device = attr;
  }

  void setDevice(::llvm::StringRef attrValue);
  void setFuncAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().func = attr;
  }

  void setFunc(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr device, ::mlir::FlatSymbolRefAttr func, ::mlir::ValueRange odsArg_0);
  static LaunchFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr device, ::mlir::FlatSymbolRefAttr func, ::mlir::ValueRange odsArg_0);
  static LaunchFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr device, ::mlir::FlatSymbolRefAttr func, ::mlir::ValueRange odsArg_0);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef device, ::llvm::StringRef func, ::mlir::ValueRange odsArg_0);
  static LaunchFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef device, ::llvm::StringRef func, ::mlir::ValueRange odsArg_0);
  static LaunchFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef device, ::llvm::StringRef func, ::mlir::ValueRange odsArg_0);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LaunchFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LaunchFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LaunchFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LaunchFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::tf_device
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_device::LaunchFuncOp)

namespace mlir::tf_device {


//===----------------------------------------------------------------------===//
// ::mlir::tf_device::LaunchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LaunchOpGenericAdaptorBase {
public:
  struct Properties {
    using deviceTy = ::mlir::StringAttr;
    deviceTy device;

    auto getDevice() const {
      auto &propStorage = this->device;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setDevice(const ::mlir::StringAttr &propValue) {
      this->device = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.device == this->device &&
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
  LaunchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_device.launch", odsAttrs.getContext());
  }

  LaunchOpGenericAdaptorBase(LaunchOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getDeviceAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().device);
    return attr;
  }

  ::llvm::StringRef getDevice();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class LaunchOpGenericAdaptor : public detail::LaunchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LaunchOpGenericAdaptorBase;
public:
  LaunchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LaunchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LaunchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LaunchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LaunchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LaunchOpGenericAdaptor(RangeT values, const LaunchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LaunchOp, typename = std::enable_if_t<std::is_same_v<LateInst, LaunchOp>>>
  LaunchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class LaunchOpAdaptor : public LaunchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LaunchOpGenericAdaptor::LaunchOpGenericAdaptor;
  LaunchOpAdaptor(LaunchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LaunchOp : public ::mlir::Op<LaunchOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<ReturnOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LaunchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LaunchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("device")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDeviceAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDeviceAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_device.launch");
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
  ::mlir::StringAttr getDeviceAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().device);
  }

  ::llvm::StringRef getDevice();
  void setDeviceAttr(::mlir::StringAttr attr) {
    getProperties().device = attr;
  }

  void setDevice(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr device, TypeRange result_types);
  static LaunchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr device, TypeRange result_types);
  static LaunchOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr device, TypeRange result_types);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr device);
  static LaunchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr device);
  static LaunchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr device);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef device);
  static LaunchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef device);
  static LaunchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef device);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LaunchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LaunchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LaunchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LaunchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  Block &GetBody() { return getOperation()->getRegion(0).front(); }
  bool WrapsSingleOp();
};

} // namespace mlir::tf_device
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_device::LaunchOp)

namespace mlir::tf_device {


//===----------------------------------------------------------------------===//
// ::mlir::tf_device::ParallelExecuteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ParallelExecuteOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ParallelExecuteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_device.parallel_execute", odsAttrs.getContext());
  }

  ParallelExecuteOpGenericAdaptorBase(ParallelExecuteOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions.drop_front(0);
  }

};

} // namespace detail
template <typename RangeT>
class ParallelExecuteOpGenericAdaptor : public detail::ParallelExecuteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ParallelExecuteOpGenericAdaptorBase;
public:
  ParallelExecuteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ParallelExecuteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ParallelExecuteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ParallelExecuteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ParallelExecuteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ParallelExecuteOpGenericAdaptor(RangeT values, const ParallelExecuteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ParallelExecuteOp, typename = std::enable_if_t<std::is_same_v<LateInst, ParallelExecuteOp>>>
  ParallelExecuteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ParallelExecuteOpAdaptor : public ParallelExecuteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ParallelExecuteOpGenericAdaptor::ParallelExecuteOpGenericAdaptor;
  ParallelExecuteOpAdaptor(ParallelExecuteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ParallelExecuteOp : public ::mlir::Op<ParallelExecuteOp, ::mlir::OpTrait::VariadicRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<ReturnOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ParallelExecuteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ParallelExecuteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_device.parallel_execute");
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

  ::mlir::Operation::result_range getExecuteOutputs() {
    return getODSResults(0);
  }

  ::mlir::MutableArrayRef<::mlir::Region> getRegions() {
    return (*this)->getRegions().drop_front(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, int num_regions, TypeRange output_types);
  static ParallelExecuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, int num_regions, TypeRange output_types);
  static ParallelExecuteOp create(::mlir::ImplicitLocOpBuilder &builder, int num_regions, TypeRange output_types);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange execute_outputs, unsigned regionsCount);
  static ParallelExecuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange execute_outputs, unsigned regionsCount);
  static ParallelExecuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange execute_outputs, unsigned regionsCount);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static ParallelExecuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static ParallelExecuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  static ParallelExecuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  static ParallelExecuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
  Block& GetRegionBlockWithIndex(unsigned index);
  Operation::result_range GetRegionOutputs(unsigned region_index);

  // Checks if a tf_device.parallel_execute index'th region block wraps a
  // single operation and the single operation results are perfectly forwarded
  // to the region block's return.
  bool RegionWrapsSingleOp(unsigned index);
};

} // namespace mlir::tf_device
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_device::ParallelExecuteOp)

namespace mlir::tf_device {


//===----------------------------------------------------------------------===//
// ::mlir::tf_device::ReceiveOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReceiveOpGenericAdaptorBase {
public:
  struct Properties {
    using keyTy = ::mlir::StringAttr;
    keyTy key;

    auto getKey() const {
      auto &propStorage = this->key;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setKey(const ::mlir::StringAttr &propValue) {
      this->key = propValue;
    }
    using src_hostTy = ::mlir::StringAttr;
    src_hostTy src_host;

    auto getSrcHost() const {
      auto &propStorage = this->src_host;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSrcHost(const ::mlir::StringAttr &propValue) {
      this->src_host = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.key == this->key &&
        rhs.src_host == this->src_host &&
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
  ReceiveOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_device.receive", odsAttrs.getContext());
  }

  ReceiveOpGenericAdaptorBase(ReceiveOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getKeyAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().key);
    return attr;
  }

  ::llvm::StringRef getKey();
  ::mlir::StringAttr getSrcHostAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().src_host);
    return attr;
  }

  ::llvm::StringRef getSrcHost();
};

} // namespace detail
template <typename RangeT>
class ReceiveOpGenericAdaptor : public detail::ReceiveOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReceiveOpGenericAdaptorBase;
public:
  ReceiveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReceiveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReceiveOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReceiveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReceiveOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReceiveOpGenericAdaptor(RangeT values, const ReceiveOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReceiveOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReceiveOp>>>
  ReceiveOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ReceiveOpAdaptor : public ReceiveOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReceiveOpGenericAdaptor::ReceiveOpGenericAdaptor;
  ReceiveOpAdaptor(ReceiveOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReceiveOp : public ::mlir::Op<ReceiveOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReceiveOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReceiveOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("key"), ::llvm::StringRef("src_host")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getKeyAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getKeyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSrcHostAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSrcHostAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_device.receive");
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
  ::mlir::StringAttr getKeyAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().key);
  }

  ::llvm::StringRef getKey();
  ::mlir::StringAttr getSrcHostAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().src_host);
  }

  ::llvm::StringRef getSrcHost();
  void setKeyAttr(::mlir::StringAttr attr) {
    getProperties().key = attr;
  }

  void setKey(::llvm::StringRef attrValue);
  void setSrcHostAttr(::mlir::StringAttr attr) {
    getProperties().src_host = attr;
  }

  void setSrcHost(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::StringAttr key, ::mlir::StringAttr src_host);
  static ReceiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::StringAttr key, ::mlir::StringAttr src_host);
  static ReceiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::StringAttr key, ::mlir::StringAttr src_host);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr key, ::mlir::StringAttr src_host);
  static ReceiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr key, ::mlir::StringAttr src_host);
  static ReceiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr key, ::mlir::StringAttr src_host);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef key, ::llvm::StringRef src_host);
  static ReceiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef key, ::llvm::StringRef src_host);
  static ReceiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef key, ::llvm::StringRef src_host);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef key, ::llvm::StringRef src_host);
  static ReceiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef key, ::llvm::StringRef src_host);
  static ReceiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef key, ::llvm::StringRef src_host);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReceiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReceiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReceiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReceiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace mlir::tf_device
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_device::ReceiveOp)

namespace mlir::tf_device {


//===----------------------------------------------------------------------===//
// ::mlir::tf_device::RemoteRunOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RemoteRunOpGenericAdaptorBase {
public:
  struct Properties {
    using calleeTy = ::mlir::FlatSymbolRefAttr;
    calleeTy callee;

    auto getCallee() const {
      auto &propStorage = this->callee;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setCallee(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->callee = propValue;
    }
    using hostTy = ::mlir::StringAttr;
    hostTy host;

    auto getHost() const {
      auto &propStorage = this->host;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setHost(const ::mlir::StringAttr &propValue) {
      this->host = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.callee == this->callee &&
        rhs.host == this->host &&
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
  RemoteRunOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_device.remote_run", odsAttrs.getContext());
  }

  RemoteRunOpGenericAdaptorBase(RemoteRunOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getHostAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().host);
    return attr;
  }

  ::llvm::StringRef getHost();
  ::mlir::FlatSymbolRefAttr getCalleeAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().callee);
    return attr;
  }

  ::llvm::StringRef getCallee();
};

} // namespace detail
template <typename RangeT>
class RemoteRunOpGenericAdaptor : public detail::RemoteRunOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RemoteRunOpGenericAdaptorBase;
  static constexpr int odsIndex_callee_args = 0;
public:
  RemoteRunOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RemoteRunOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : RemoteRunOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RemoteRunOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RemoteRunOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RemoteRunOpGenericAdaptor(RangeT values, const RemoteRunOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RemoteRunOp, typename = std::enable_if_t<std::is_same_v<LateInst, RemoteRunOp>>>
  RemoteRunOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getCalleeArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RemoteRunOpAdaptor : public RemoteRunOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RemoteRunOpGenericAdaptor::RemoteRunOpGenericAdaptor;
  RemoteRunOpAdaptor(RemoteRunOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RemoteRunOp : public ::mlir::Op<RemoteRunOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<ReturnOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RemoteRunOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RemoteRunOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_callee_args = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("callee"), ::llvm::StringRef("host")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCalleeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCalleeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getHostAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getHostAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_device.remote_run");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getCalleeArgs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getCalleeArgsMutable();
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
  ::mlir::StringAttr getHostAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().host);
  }

  ::llvm::StringRef getHost();
  ::mlir::FlatSymbolRefAttr getCalleeAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().callee);
  }

  ::llvm::StringRef getCallee();
  void setHostAttr(::mlir::StringAttr attr) {
    getProperties().host = attr;
  }

  void setHost(::llvm::StringRef attrValue);
  void setCalleeAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().callee = attr;
  }

  void setCallee(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr host, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange callee_args);
  static RemoteRunOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr host, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange callee_args);
  static RemoteRunOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr host, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange callee_args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef host, ::llvm::StringRef callee, ::mlir::ValueRange callee_args);
  static RemoteRunOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef host, ::llvm::StringRef callee, ::mlir::ValueRange callee_args);
  static RemoteRunOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef host, ::llvm::StringRef callee, ::mlir::ValueRange callee_args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RemoteRunOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RemoteRunOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RemoteRunOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RemoteRunOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace mlir::tf_device
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_device::RemoteRunOp)

namespace mlir::tf_device {


//===----------------------------------------------------------------------===//
// ::mlir::tf_device::ReplicateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReplicateOpGenericAdaptorBase {
public:
  struct Properties {
    using devicesTy = ::mlir::DictionaryAttr;
    devicesTy devices;

    auto getDevices() const {
      auto &propStorage = this->devices;
      return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(propStorage);
    }
    void setDevices(const ::mlir::DictionaryAttr &propValue) {
      this->devices = propValue;
    }
    using nTy = ::mlir::IntegerAttr;
    nTy n;

    auto getN() const {
      auto &propStorage = this->n;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setN(const ::mlir::IntegerAttr &propValue) {
      this->n = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 2>;
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
        rhs.devices == this->devices &&
        rhs.n == this->n &&
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
  ReplicateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_device.replicate", odsAttrs.getContext());
  }

  ReplicateOpGenericAdaptorBase(ReplicateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getNAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().n);
    return attr;
  }

  uint32_t getN();
  ::mlir::DictionaryAttr getDevicesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().devices);
    return attr;
  }

  ::std::optional< ::mlir::DictionaryAttr > getDevices();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ReplicateOpGenericAdaptor : public detail::ReplicateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReplicateOpGenericAdaptorBase;
  static constexpr int odsIndex_replicated_inputs = 0;
  static constexpr int odsIndex_packed_inputs = 1;
public:
  ReplicateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReplicateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReplicateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReplicateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ReplicateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReplicateOpGenericAdaptor(RangeT values, const ReplicateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReplicateOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReplicateOp>>>
  ReplicateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getReplicatedInputs() {
    return getODSOperands(0);
  }

  RangeT getPackedInputs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReplicateOpAdaptor : public ReplicateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReplicateOpGenericAdaptor::ReplicateOpGenericAdaptor;
  ReplicateOpAdaptor(ReplicateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReplicateOp : public ::mlir::Op<ReplicateOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<ReturnOp>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReplicateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReplicateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_replicated_inputs = 0;
  static constexpr int odsIndex_packed_inputs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("devices"), ::llvm::StringRef("n"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDevicesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDevicesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_device.replicate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getReplicatedInputs() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getPackedInputs() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getReplicatedInputsMutable();
  ::mlir::MutableOperandRange getPackedInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getReplicatedOutputs() {
    return getODSResults(0);
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
  ::mlir::IntegerAttr getNAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().n);
  }

  uint32_t getN();
  ::mlir::DictionaryAttr getDevicesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().devices);
  }

  ::std::optional< ::mlir::DictionaryAttr > getDevices();
  void setNAttr(::mlir::IntegerAttr attr) {
    getProperties().n = attr;
  }

  void setN(uint32_t attrValue);
  void setDevicesAttr(::mlir::DictionaryAttr attr) {
    getProperties().devices = attr;
  }

  ::mlir::Attribute removeDevicesAttr() {
      auto attr = getProperties().devices;
      getProperties().devices = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, int n, const llvm::SmallDenseMap<StringRef, llvm::SmallVector<StringRef, 4>>&devices, llvm::ArrayRef<std::pair<ValueRange, Type>> replicated_inputs, ValueRange packed_inputs, TypeRange replica_output_types);
  static ReplicateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, int n, const llvm::SmallDenseMap<StringRef, llvm::SmallVector<StringRef, 4>>&devices, llvm::ArrayRef<std::pair<ValueRange, Type>> replicated_inputs, ValueRange packed_inputs, TypeRange replica_output_types);
  static ReplicateOp create(::mlir::ImplicitLocOpBuilder &builder, int n, const llvm::SmallDenseMap<StringRef, llvm::SmallVector<StringRef, 4>>&devices, llvm::ArrayRef<std::pair<ValueRange, Type>> replicated_inputs, ValueRange packed_inputs, TypeRange replica_output_types);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, int n, std::optional<DictionaryAttr> devices, llvm::ArrayRef<std::pair<ValueRange, Type>> replicated_inputs, ValueRange packed_inputs, TypeRange replica_output_types);
  static ReplicateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, int n, std::optional<DictionaryAttr> devices, llvm::ArrayRef<std::pair<ValueRange, Type>> replicated_inputs, ValueRange packed_inputs, TypeRange replica_output_types);
  static ReplicateOp create(::mlir::ImplicitLocOpBuilder &builder, int n, std::optional<DictionaryAttr> devices, llvm::ArrayRef<std::pair<ValueRange, Type>> replicated_inputs, ValueRange packed_inputs, TypeRange replica_output_types);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange replicated_outputs, ::mlir::ValueRange replicated_inputs, ::mlir::ValueRange packed_inputs, ::mlir::IntegerAttr n, /*optional*/::mlir::DictionaryAttr devices);
  static ReplicateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange replicated_outputs, ::mlir::ValueRange replicated_inputs, ::mlir::ValueRange packed_inputs, ::mlir::IntegerAttr n, /*optional*/::mlir::DictionaryAttr devices);
  static ReplicateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange replicated_outputs, ::mlir::ValueRange replicated_inputs, ::mlir::ValueRange packed_inputs, ::mlir::IntegerAttr n, /*optional*/::mlir::DictionaryAttr devices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange replicated_outputs, ::mlir::ValueRange replicated_inputs, ::mlir::ValueRange packed_inputs, uint32_t n, /*optional*/::mlir::DictionaryAttr devices);
  static ReplicateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange replicated_outputs, ::mlir::ValueRange replicated_inputs, ::mlir::ValueRange packed_inputs, uint32_t n, /*optional*/::mlir::DictionaryAttr devices);
  static ReplicateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange replicated_outputs, ::mlir::ValueRange replicated_inputs, ::mlir::ValueRange packed_inputs, uint32_t n, /*optional*/::mlir::DictionaryAttr devices);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplicateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplicateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplicateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplicateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  Block &GetBody() { return getOperation()->getRegion(0).front(); }
  unsigned GetNumReplicatedBlockArguments();
  unsigned GetNumPackedBlockArguments();
  llvm::ArrayRef<BlockArgument> GetPackedBlockArguments();
  llvm::ArrayRef<BlockArgument> GetReplicatedBlockArguments();
  bool IsReplicatedBlockArgument(BlockArgument block_arg);
  bool IsPackedBlockArgument(BlockArgument block_arg);
  unsigned GetReplicaOperandIndexForBlockArgument(BlockArgument block_arg, unsigned replica);
  Value GetReplicaOperandForBlockArgument(BlockArgument block_arg, unsigned replica);
  MutableArrayRef<OpOperand> GetOperandsForBlockArgument(BlockArgument block_arg);
  bool WrapsSingleOp();
};

} // namespace mlir::tf_device
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_device::ReplicateOp)

namespace mlir::tf_device {


//===----------------------------------------------------------------------===//
// ::mlir::tf_device::ReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_device.return", odsAttrs.getContext());
  }

  ReturnOpGenericAdaptorBase(ReturnOp op);

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
class ReturnOpGenericAdaptor : public detail::ReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReturnOpGenericAdaptorBase;
  static constexpr int odsIndex_results = 0;
public:
  ReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReturnOpGenericAdaptor(RangeT values, const ReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReturnOp>>>
  ReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getResults() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReturnOpAdaptor : public ReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReturnOpGenericAdaptor::ReturnOpGenericAdaptor;
  ReturnOpAdaptor(ReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReturnOp : public ::mlir::Op<ReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_results = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<ReturnOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_device.return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getResults() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getResultsMutable();
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
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange results);
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange results);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange results);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::tf_device
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_device::ReturnOp)

namespace mlir::tf_device {


//===----------------------------------------------------------------------===//
// ::mlir::tf_device::SendOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SendOpGenericAdaptorBase {
public:
  struct Properties {
    using dst_hostTy = ::mlir::StringAttr;
    dst_hostTy dst_host;

    auto getDstHost() const {
      auto &propStorage = this->dst_host;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setDstHost(const ::mlir::StringAttr &propValue) {
      this->dst_host = propValue;
    }
    using keyTy = ::mlir::StringAttr;
    keyTy key;

    auto getKey() const {
      auto &propStorage = this->key;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setKey(const ::mlir::StringAttr &propValue) {
      this->key = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dst_host == this->dst_host &&
        rhs.key == this->key &&
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
  SendOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_device.send", odsAttrs.getContext());
  }

  SendOpGenericAdaptorBase(SendOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getKeyAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().key);
    return attr;
  }

  ::llvm::StringRef getKey();
  ::mlir::StringAttr getDstHostAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().dst_host);
    return attr;
  }

  ::llvm::StringRef getDstHost();
};

} // namespace detail
template <typename RangeT>
class SendOpGenericAdaptor : public detail::SendOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SendOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  SendOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SendOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SendOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SendOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SendOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SendOpGenericAdaptor(RangeT values, const SendOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SendOp, typename = std::enable_if_t<std::is_same_v<LateInst, SendOp>>>
  SendOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SendOpAdaptor : public SendOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SendOpGenericAdaptor::SendOpGenericAdaptor;
  SendOpAdaptor(SendOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SendOp : public ::mlir::Op<SendOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SendOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SendOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dst_host"), ::llvm::StringRef("key")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDstHostAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDstHostAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getKeyAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getKeyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_device.send");
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

  ::mlir::OpOperand &getValueMutable() {
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
  ::mlir::StringAttr getKeyAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().key);
  }

  ::llvm::StringRef getKey();
  ::mlir::StringAttr getDstHostAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().dst_host);
  }

  ::llvm::StringRef getDstHost();
  void setKeyAttr(::mlir::StringAttr attr) {
    getProperties().key = attr;
  }

  void setKey(::llvm::StringRef attrValue);
  void setDstHostAttr(::mlir::StringAttr attr) {
    getProperties().dst_host = attr;
  }

  void setDstHost(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::StringAttr key, ::mlir::StringAttr dst_host);
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::StringAttr key, ::mlir::StringAttr dst_host);
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::StringAttr key, ::mlir::StringAttr dst_host);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::StringAttr key, ::mlir::StringAttr dst_host);
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::StringAttr key, ::mlir::StringAttr dst_host);
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::StringAttr key, ::mlir::StringAttr dst_host);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::llvm::StringRef key, ::llvm::StringRef dst_host);
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::llvm::StringRef key, ::llvm::StringRef dst_host);
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::llvm::StringRef key, ::llvm::StringRef dst_host);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::llvm::StringRef key, ::llvm::StringRef dst_host);
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::llvm::StringRef key, ::llvm::StringRef dst_host);
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::llvm::StringRef key, ::llvm::StringRef dst_host);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace mlir::tf_device
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_device::SendOp)


#endif // GET_OP_CLASSES

