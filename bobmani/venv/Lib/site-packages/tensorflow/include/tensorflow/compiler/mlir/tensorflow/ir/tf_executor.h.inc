/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: tf_executor_ops.td                                                   *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::tf_executor {

/// The `tf_executor.ControlTrigger` operation is similar to a no-op except that
///     it always produces a valid output even when inputs are dead.
/// Its primary use so far is in the scheduling of recvs, where we add
///     ControlTrigger nodes and use them to trigger recvs. We allow ControlTrigger
///     nodes to be enabled by dead nodes.
class ControlTriggerOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The "tf_executor.Enter" operation forwards its input to Tensorflow while
///     loop.
/// More details can be found in Tensorflow Control Flow white paper:
///     https://storage.googleapis.com/download.tensorflow.org/paper/white_paper_tf_control_flow_implementation_2017_11_1.pdf
/// 
///     Each tensor needs its own tf_executor.Enter to be made available inside a
///     while loop.
/// 
///     This is defined in Tensorflow as:
/// 
///     REGISTER_OP("Enter")
///        .Input("data: T")
///        .Output("output: T")
///        .Attr("T: type")
///        .Attr("frame_name: string")
///        .Attr("is_constant: bool = false")
///        .Attr("parallel_iterations: int = 10")
/// 
///     For example:
///        %res:2 = tf_executor.Enter %arg0 frame "some/frame" parallel_iterations 42 constant : tensor<*xf32>
/// 
///     Note: Additional result corresponds to the control output.
class EnterOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The "tf_executor.Exit" operation forwards a value from an while loop to its
///     consumer outside of loop. Each returned tensor needs its own
///     tf_executor.Exit.
/// More details can be found in Tensorflow Control Flow white paper:
///     https://storage.googleapis.com/download.tensorflow.org/paper/white_paper_tf_control_flow_implementation_2017_11_1.pdf
/// 
///     This is defined in Tensorflow as:
/// 
///     REGISTER_OP("Exit")
///        .Input("data: T")
///        .Output("output: T")
///        .Attr("T: type")
/// 
///     For example:
///      %1:2 = tf_executor.Exit %0#0 : tensor<*xi32> {T: "tfdtype$DT_INT32"}
/// 
///     Note: Additional result corresponds to the control output.
class ExitOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The `tf_executor.fetch` operation terminates the graph and returns values;
/// The non-control operands of the fetch operation are returned outside of the
///     graph and must match the return type of the graph.
class FetchOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The `tf_executor.graph` operation contains a region with a
///     single block that lists the operations in a TensorFlow graph.
/// The operations are topologically sorted in-order (no cycles are allowed in
///     the values). The execution model for operations in this block follows the
///     TensorFlow executor semantics:
///       1. Operations that don’t have any transitive dependencies through the
///          def/use chains may be executed in parallel
///          (`tf_executor.NextIteration.Source` is the exception).
///       2. SSA values in this block can be implicitly dead. This means that every
///          SSA value defined in a `tf_executor.graph` can be considered implicitly
///          wrapped in a conceptual `dead_or<T>` structure, and includes a runtime
///          flag indicating if the value is dead or present.
///       3. Operations may have special case handling of dead values.
/// 
///     The `tf_executor.graph` op only allows specific `tf_executor` dialect
///     operations in its body: the `tf_executor.graph` verifier will reject any
///     unknown operation. In order to execute standard `tf` dialect operations
///     (like `tf.Add`) they must be wrapped in the `tf_executor.island` operation.
/// 
///     The `tf_executor.graph` operation does not accept any operands, inputs are
///     implicitly captured by the region, representing the feeds to the graph.
/// 
///     The region attached to `tf_executor.graph` is terminated by a
///     `tf_executor.fetch` operation. The operands of the terminator correspond to
///     the result values (or fetches) of the `tf_executor.graph` operation. The
///     behavior is undefined if any of the operands of the `tf_executor.fetch` is
///     dead.
class GraphOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The `tf_executor.island` operation is a wrapper for operations in other
///     dialects to be nested in a `tf_executor.graph`.
/// The `tf_executor.graph` operation does not allow `tf` dialect operations to
///     be immediately nested underneath it. The `tf_executor.island` is introduced
///     as a wrapper for `tf` dialect operations: this results in a more consistent
///     representation which makes analysis and transformation simpler.
///     The `tf_executor.island` operation has a single region with a single block
///     attached (only functional control flow is allowed). The block is terminated
///     by a `tf_executor.yield` operation. The operands of the terminator
///     correspond to the result values of the `tf_executor.island` operation. An
///     extra result of type `!tf_executor.control` is always produced by every
///     `tf_executor.island`.
///     Within an island, execution semantics follow standard sequential behavior as
///     expected by TF2 and by compiler analyses and transformations, and values
///     can’t be dead. Other nested `tf_executor.graph` operations can be present in
///     the region to re-enable the TensorFlow executor for a subsection of the
///     code.
///      - Initially the functional control flow operations are calling functions
///        involving graphs, if `tf_executor.graph` weren’t allowed in an island,
///        these operations would need to have an equivalent in the `tf_executor`
///        dialect to be modelled in a graph.
///      - Nesting also allows forming islands without involving inter-procedural
///        analyses: any function call may involve a callee with a graph.
///     The `tf_executor.island` region allows implicit capture. If any value
///     captured by a `tf_executor.island` is dead, the whole region does not
///     execute and every produced value is marked as dead as well.
///     An arbitrary number of `tf_executor.control` operands are accepted by a
///     `tf_executor.island` operation.
///     If any operand or implicitly captured value are dead, the region is not
///     executed and dead values are immediately returned for every result.
class IslandOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The "tf_executor.LoopCond" operation forwards a boolean value as loop
///     condition of Tensorflow while loops.
/// More details can be found in Tensorflow Control Flow white paper:
///     https://storage.googleapis.com/download.tensorflow.org/paper/white_paper_tf_control_flow_implementation_2017_11_1.pdf
/// 
///     This is defined in Tensorflow as:
/// 
///     REGISTER_OP("LoopCond")
///        .Input("input: bool")
///        .Output("output: bool")
/// 
///     For example:
///       %5:2 = tf_executor.LoopCond %4#0 {name: "while/LoopCond"}
/// 
///     Note: Additional result corresponds to the control output.
class LoopCondOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The "tf_executor.Merge" operation takes a list of input operands and returns
///     a value of the operand type along with the index of the first match encountered.
/// More details can be found in Tensorflow Control Flow white paper:
///     https://storage.googleapis.com/download.tensorflow.org/paper/white_paper_tf_control_flow_implementation_2017_11_1.pdf
/// 
///     This is defined in TensorFlow as:
/// 
///     REGISTER_OP("Merge")
///        .Input("inputs: N * T")
///        .Output("output: T")
///        .Output("value_index: int32")
/// 
///     For example:
///       %2 = tf_executor.Merge %0, %1, %2, %3 : tensor<*xf32>
/// 
///     Note: Additional result corresponds to the control output.
class MergeOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The "tf_executor.NextIteration.Sink" is paired with a
///     "tf_executor.NextIteration.source" to represent NextIteration op in
///     Tensorflow.
/// Tensorflow NextIteration operation forwards its input to the next iteration
///     of a while loop. Each loop variable needs its own NextIteration op.
/// 
///     More details can be found in Tensorflow Control Flow white paper:
///     https://storage.googleapis.com/download.tensorflow.org/paper/white_paper_tf_control_flow_implementation_2017_11_1.pdf
/// 
///     In the TF executor dialect, the NextIteration op is broken into
///     tf_executor.NextIteration.sink and tf_executor.NextIteration.source because
///     NextIteration is a back-edge in Tensorflow graph, which would form a data
///     flow cycle if expressed naively in a basic block.
///     tf_executor.NextIteration.source takes no input but returns results while
///     tf_executor.NextIteration.sink takes input but doesn't return anything. When
///     optimizing these ops, they are paired by token and considered as a single
///     op.
/// 
///     This is defined in Tensorflow as:
/// 
///     REGISTER_OP("NextIteration")
///        .Input("data: T")
///        .Output("output: T")
///        .Attr("T: type")
/// 
///     For example:
///       %value, %token, %ctl = tf_executor.NextIteration.Source : tensor<*xi32>
///       tf_executor.NextIteration.sink [%token] (%value) : tensor<*xi32>
/// 
///     Note: Additional result corresponds to the control output.
class NextIterationSinkOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The "tf_executor.NextIteration.Source" is paired with a
///     "tf_executor.NextIteration.sink" to represent NextIteration op in
///     Tensorflow.
/// Tensorflow NextIteration operation forwards its input to the next iteration
///     of a while loop. Each loop variable needs its own NextIteration op.
/// 
///     More details can be found in Tensorflow Control Flow white paper:
///     https://storage.googleapis.com/download.tensorflow.org/paper/white_paper_tf_control_flow_implementation_2017_11_1.pdf
/// 
///     In the TF executor dialect, the NextIteration op is broken into
///     tf_executor.NextIteration.sink and tf_executor.NextIteration.source because
///     NextIteration is a back-edge in Tensorflow graph, which would form a data
///     flow cycle if expressed naively in a basic block.
///     tf_executor.NextIteration.source takes no input but returns results while
///     tf_executor.NextIteration.sink takes input but doesn't return anything. When
///     optimizing these ops, they are paired by token and considered as a single
///     op.
/// 
///     This is defined in Tensorflow as:
/// 
///     REGISTER_OP("NextIteration")
///        .Input("data: T")
///        .Output("output: T")
///        .Attr("T: type")
/// 
///     For example:
///       %value, %token, %ctl = tf_executor.NextIteration.Source : tensor<*xi32>
///       tf_executor.NextIteration.sink [%token] (%value) : tensor<*xi32>
/// 
///     Note: Additional result corresponds to the control output.
class NextIterationSourceOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The "tf_executor._SwitchN" operation takes two inputs, `data` and `index`
///     and an integer attribute `num_outs` indicating the number of outputs. The
///     `data` input is copied to output indicated by the `index` input. The other
///     outputs are marked as dead. If one of the inputs or a control token is
///     dead, then all of the outputs are marked as dead as well.
/// This is defined in TensorFlow as:
/// 
///     REGISTER_OP("_SwitchN")
///         .Input("data: T")
///         .Input("output_index: int32")
///         .Output("outputs: num_outs * T")
///         .Attr("num_outs: int >= 1")
///         .Attr("T: type")
///         .SetShapeFn(SwitchNShape);
/// 
///     For example:
///       %2:6 = tf_executor.SwitchN %0, %1 of 5 : tensor<??xf32>
/// 
///     Note: One additional result corresponds to the control output.
class SwitchNOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The "tf_executor.Switch" operation takes a data operand and a boolean
///     predicate condition, and returns two values matching the type of the data
///     predicate.
/// More details can be found in Tensorflow Control Flow white paper:
///     https://storage.googleapis.com/download.tensorflow.org/paper/white_paper_tf_control_flow_implementation_2017_11_1.pdf
/// 
///     This is defined in TensorFlow as:
/// 
///     REGISTER_OP("Switch")
///        .Input("data: T")
///        .Input("pred: bool")
///        .Output("output_false: T")
///        .Output("output_true: T")
/// 
///     For example:
///       %2 = tf_executor.Switch %0, %1 : tensor<*xf32>
/// 
///     Note: Additional result corresponds to the control output.
class SwitchOp;

} // namespace mlir::tf_executor
namespace mlir::tf_executor {

/// The `tf_executor.yield` operation terminates and returns values for the
///     `tf_executor.island` operation.
class YieldOp;

} // namespace mlir::tf_executor
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::ControlTriggerOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ControlTriggerOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ControlTriggerOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.ControlTrigger", odsAttrs.getContext());
  }

  ControlTriggerOpGenericAdaptorBase(ControlTriggerOp op);

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
class ControlTriggerOpGenericAdaptor : public detail::ControlTriggerOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ControlTriggerOpGenericAdaptorBase;
  static constexpr int odsIndex_controlInputs = 0;
public:
  ControlTriggerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ControlTriggerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ControlTriggerOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ControlTriggerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ControlTriggerOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ControlTriggerOpGenericAdaptor(RangeT values, const ControlTriggerOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ControlTriggerOp, typename = std::enable_if_t<std::is_same_v<LateInst, ControlTriggerOp>>>
  ControlTriggerOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getControlInputs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ControlTriggerOpAdaptor : public ControlTriggerOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ControlTriggerOpGenericAdaptor::ControlTriggerOpGenericAdaptor;
  ControlTriggerOpAdaptor(ControlTriggerOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ControlTriggerOp : public ::mlir::Op<ControlTriggerOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ControlTriggerOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ControlTriggerOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_controlInputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.ControlTrigger");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getControlInputs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getControlInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<Value> operands, ArrayRef<NamedAttribute> attributes = {});
  static ControlTriggerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<Value> operands, ArrayRef<NamedAttribute> attributes = {});
  static ControlTriggerOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<Value> operands, ArrayRef<NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type control, ::mlir::ValueRange controlInputs);
  static ControlTriggerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type control, ::mlir::ValueRange controlInputs);
  static ControlTriggerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type control, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ControlTriggerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ControlTriggerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ControlTriggerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ControlTriggerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ControlTriggerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ControlTriggerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ControlTriggerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ControlTriggerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::ControlTriggerOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::EnterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EnterOpGenericAdaptorBase {
public:
  struct Properties {
    using frame_nameTy = ::mlir::StringAttr;
    frame_nameTy frame_name;

    auto getFrameName() const {
      auto &propStorage = this->frame_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setFrameName(const ::mlir::StringAttr &propValue) {
      this->frame_name = propValue;
    }
    using is_constantTy = ::mlir::BoolAttr;
    is_constantTy is_constant;

    auto getIsConstant() const {
      auto &propStorage = this->is_constant;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setIsConstant(const ::mlir::BoolAttr &propValue) {
      this->is_constant = propValue;
    }
    using parallel_iterationsTy = ::mlir::IntegerAttr;
    parallel_iterationsTy parallel_iterations;

    auto getParallelIterations() const {
      auto &propStorage = this->parallel_iterations;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setParallelIterations(const ::mlir::IntegerAttr &propValue) {
      this->parallel_iterations = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.frame_name == this->frame_name &&
        rhs.is_constant == this->is_constant &&
        rhs.parallel_iterations == this->parallel_iterations &&
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
  EnterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.Enter", odsAttrs.getContext());
  }

  EnterOpGenericAdaptorBase(EnterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getFrameNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().frame_name);
    return attr;
  }

  ::llvm::StringRef getFrameName();
  ::mlir::BoolAttr getIsConstantAttr();
  bool getIsConstant();
  ::mlir::IntegerAttr getParallelIterationsAttr();
  uint64_t getParallelIterations();
};

} // namespace detail
template <typename RangeT>
class EnterOpGenericAdaptor : public detail::EnterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EnterOpGenericAdaptorBase;
  static constexpr int odsIndex_data = 0;
  static constexpr int odsIndex_controlInputs = 1;
public:
  EnterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EnterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : EnterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EnterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EnterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EnterOpGenericAdaptor(RangeT values, const EnterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EnterOp, typename = std::enable_if_t<std::is_same_v<LateInst, EnterOp>>>
  EnterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getData() {
    return (*getODSOperands(0).begin());
  }

  RangeT getControlInputs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class EnterOpAdaptor : public EnterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EnterOpGenericAdaptor::EnterOpGenericAdaptor;
  EnterOpAdaptor(EnterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EnterOp : public ::mlir::Op<EnterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EnterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EnterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_data = 0;
  static constexpr int odsIndex_controlInputs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("frame_name"), ::llvm::StringRef("is_constant"), ::llvm::StringRef("parallel_iterations")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFrameNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFrameNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIsConstantAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIsConstantAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getParallelIterationsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getParallelIterationsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.Enter");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getControlInputs() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getDataMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getControlInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
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
  ::mlir::StringAttr getFrameNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().frame_name);
  }

  ::llvm::StringRef getFrameName();
  ::mlir::BoolAttr getIsConstantAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().is_constant);
  }

  bool getIsConstant();
  ::mlir::IntegerAttr getParallelIterationsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().parallel_iterations);
  }

  uint64_t getParallelIterations();
  void setFrameNameAttr(::mlir::StringAttr attr) {
    getProperties().frame_name = attr;
  }

  void setFrameName(::llvm::StringRef attrValue);
  void setIsConstantAttr(::mlir::BoolAttr attr) {
    getProperties().is_constant = attr;
  }

  void setIsConstant(::std::optional<bool> attrValue);
  void setParallelIterationsAttr(::mlir::IntegerAttr attr) {
    getProperties().parallel_iterations = attr;
  }

  void setParallelIterations(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeIsConstantAttr() {
      auto attr = getProperties().is_constant;
      getProperties().is_constant = {};
      return attr;
  }

  ::mlir::Attribute removeParallelIterationsAttr() {
      auto attr = getProperties().parallel_iterations;
      getProperties().parallel_iterations = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Type control, ::mlir::Value data, ::mlir::StringAttr frame_name, /*optional*/::mlir::BoolAttr is_constant, /*optional*/::mlir::IntegerAttr parallel_iterations, ::mlir::ValueRange controlInputs);
  static EnterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Type control, ::mlir::Value data, ::mlir::StringAttr frame_name, /*optional*/::mlir::BoolAttr is_constant, /*optional*/::mlir::IntegerAttr parallel_iterations, ::mlir::ValueRange controlInputs);
  static EnterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Type control, ::mlir::Value data, ::mlir::StringAttr frame_name, /*optional*/::mlir::BoolAttr is_constant, /*optional*/::mlir::IntegerAttr parallel_iterations, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::StringAttr frame_name, /*optional*/::mlir::BoolAttr is_constant, /*optional*/::mlir::IntegerAttr parallel_iterations, ::mlir::ValueRange controlInputs);
  static EnterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::StringAttr frame_name, /*optional*/::mlir::BoolAttr is_constant, /*optional*/::mlir::IntegerAttr parallel_iterations, ::mlir::ValueRange controlInputs);
  static EnterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::StringAttr frame_name, /*optional*/::mlir::BoolAttr is_constant, /*optional*/::mlir::IntegerAttr parallel_iterations, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Type control, ::mlir::Value data, ::llvm::StringRef frame_name, /*optional*/bool is_constant, /*optional*/uint64_t parallel_iterations, ::mlir::ValueRange controlInputs);
  static EnterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Type control, ::mlir::Value data, ::llvm::StringRef frame_name, /*optional*/bool is_constant, /*optional*/uint64_t parallel_iterations, ::mlir::ValueRange controlInputs);
  static EnterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Type control, ::mlir::Value data, ::llvm::StringRef frame_name, /*optional*/bool is_constant, /*optional*/uint64_t parallel_iterations, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::llvm::StringRef frame_name, /*optional*/bool is_constant, /*optional*/uint64_t parallel_iterations, ::mlir::ValueRange controlInputs);
  static EnterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::llvm::StringRef frame_name, /*optional*/bool is_constant, /*optional*/uint64_t parallel_iterations, ::mlir::ValueRange controlInputs);
  static EnterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::llvm::StringRef frame_name, /*optional*/bool is_constant, /*optional*/uint64_t parallel_iterations, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::EnterOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::ExitOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExitOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ExitOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.Exit", odsAttrs.getContext());
  }

  ExitOpGenericAdaptorBase(ExitOp op);

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
class ExitOpGenericAdaptor : public detail::ExitOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExitOpGenericAdaptorBase;
  static constexpr int odsIndex_data = 0;
  static constexpr int odsIndex_controlInputs = 1;
public:
  ExitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExitOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExitOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExitOpGenericAdaptor(RangeT values, const ExitOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExitOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExitOp>>>
  ExitOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getData() {
    return (*getODSOperands(0).begin());
  }

  RangeT getControlInputs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ExitOpAdaptor : public ExitOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExitOpGenericAdaptor::ExitOpGenericAdaptor;
  ExitOpAdaptor(ExitOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExitOp : public ::mlir::Op<ExitOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExitOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExitOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_data = 0;
  static constexpr int odsIndex_controlInputs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.Exit");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getControlInputs() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getDataMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getControlInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Type control, ::mlir::Value data, ::mlir::ValueRange controlInputs);
  static ExitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Type control, ::mlir::Value data, ::mlir::ValueRange controlInputs);
  static ExitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Type control, ::mlir::Value data, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::ValueRange controlInputs);
  static ExitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::ValueRange controlInputs);
  static ExitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::ExitOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::FetchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FetchOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FetchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.fetch", odsAttrs.getContext());
  }

  FetchOpGenericAdaptorBase(FetchOp op);

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
class FetchOpGenericAdaptor : public detail::FetchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FetchOpGenericAdaptorBase;
  static constexpr int odsIndex_fetches = 0;
public:
  FetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : FetchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FetchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FetchOpGenericAdaptor(RangeT values, const FetchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FetchOp, typename = std::enable_if_t<std::is_same_v<LateInst, FetchOp>>>
  FetchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getFetches() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FetchOpAdaptor : public FetchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FetchOpGenericAdaptor::FetchOpGenericAdaptor;
  FetchOpAdaptor(FetchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FetchOp : public ::mlir::Op<FetchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FetchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FetchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_fetches = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.fetch");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getFetches() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getFetchesMutable();
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
  static FetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static FetchOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange fetches);
  static FetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange fetches);
  static FetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange fetches);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::FetchOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::GraphOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GraphOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GraphOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.graph", odsAttrs.getContext());
  }

  GraphOpGenericAdaptorBase(GraphOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class GraphOpGenericAdaptor : public detail::GraphOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GraphOpGenericAdaptorBase;
public:
  GraphOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GraphOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GraphOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GraphOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GraphOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GraphOpGenericAdaptor(RangeT values, const GraphOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GraphOp, typename = std::enable_if_t<std::is_same_v<LateInst, GraphOp>>>
  GraphOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GraphOpAdaptor : public GraphOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GraphOpGenericAdaptor::GraphOpGenericAdaptor;
  GraphOpAdaptor(GraphOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GraphOp : public ::mlir::Op<GraphOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<FetchOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GraphOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GraphOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.graph");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results);
  static GraphOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results);
  static GraphOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GraphOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GraphOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GraphOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GraphOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
  Block &GetBody() { return getOperation()->getRegion(0).front(); }
  FetchOp GetFetch();
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::GraphOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::IslandOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IslandOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  IslandOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.island", odsAttrs.getContext());
  }

  IslandOpGenericAdaptorBase(IslandOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class IslandOpGenericAdaptor : public detail::IslandOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IslandOpGenericAdaptorBase;
  static constexpr int odsIndex_controlInputs = 0;
public:
  IslandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IslandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IslandOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IslandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IslandOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IslandOpGenericAdaptor(RangeT values, const IslandOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IslandOp, typename = std::enable_if_t<std::is_same_v<LateInst, IslandOp>>>
  IslandOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getControlInputs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class IslandOpAdaptor : public IslandOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IslandOpGenericAdaptor::IslandOpGenericAdaptor;
  IslandOpAdaptor(IslandOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IslandOp : public ::mlir::Op<IslandOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IslandOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IslandOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_controlInputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.island");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getControlInputs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getControlInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getOutputs() {
    return getODSResults(0);
  }

  ::mlir::TypedValue<::mlir::Type> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::mlir::Type control, ::mlir::ValueRange controlInputs);
  static IslandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::mlir::Type control, ::mlir::ValueRange controlInputs);
  static IslandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::mlir::Type control, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IslandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IslandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IslandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IslandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
  Block &GetBody() { return getOperation()->getRegion(0).front(); }
  YieldOp GetYield();
  bool WrapsSingleOp();
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::IslandOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::LoopCondOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoopCondOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LoopCondOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.LoopCond", odsAttrs.getContext());
  }

  LoopCondOpGenericAdaptorBase(LoopCondOp op);

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
class LoopCondOpGenericAdaptor : public detail::LoopCondOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoopCondOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_controlInputs = 1;
public:
  LoopCondOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LoopCondOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LoopCondOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LoopCondOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LoopCondOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LoopCondOpGenericAdaptor(RangeT values, const LoopCondOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LoopCondOp, typename = std::enable_if_t<std::is_same_v<LateInst, LoopCondOp>>>
  LoopCondOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getControlInputs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LoopCondOpAdaptor : public LoopCondOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LoopCondOpGenericAdaptor::LoopCondOpGenericAdaptor;
  LoopCondOpAdaptor(LoopCondOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LoopCondOp : public ::mlir::Op<LoopCondOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoopCondOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoopCondOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_controlInputs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.LoopCond");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getControlInputs() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getControlInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Type control, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static LoopCondOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Type control, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static LoopCondOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Type control, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static LoopCondOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static LoopCondOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoopCondOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoopCondOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoopCondOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoopCondOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::LoopCondOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::MergeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MergeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MergeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.Merge", odsAttrs.getContext());
  }

  MergeOpGenericAdaptorBase(MergeOp op);

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
class MergeOpGenericAdaptor : public detail::MergeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MergeOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs_and_control = 0;
public:
  MergeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MergeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MergeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MergeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MergeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MergeOpGenericAdaptor(RangeT values, const MergeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MergeOp, typename = std::enable_if_t<std::is_same_v<LateInst, MergeOp>>>
  MergeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputsAndControl() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MergeOpAdaptor : public MergeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MergeOpGenericAdaptor::MergeOpGenericAdaptor;
  MergeOpAdaptor(MergeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MergeOp : public ::mlir::Op<MergeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MergeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MergeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs_and_control = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.Merge");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputsAndControl() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getInputsAndControlMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::TensorType> getValueIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Type value_index, ::mlir::Type control, ::mlir::ValueRange inputs_and_control);
  static MergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Type value_index, ::mlir::Type control, ::mlir::ValueRange inputs_and_control);
  static MergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Type value_index, ::mlir::Type control, ::mlir::ValueRange inputs_and_control);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::MergeOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::NextIterationSinkOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NextIterationSinkOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  NextIterationSinkOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.NextIteration.Sink", odsAttrs.getContext());
  }

  NextIterationSinkOpGenericAdaptorBase(NextIterationSinkOp op);

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
class NextIterationSinkOpGenericAdaptor : public detail::NextIterationSinkOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NextIterationSinkOpGenericAdaptorBase;
  static constexpr int odsIndex_token = 0;
  static constexpr int odsIndex_input = 1;
  static constexpr int odsIndex_controlInputs = 2;
public:
  NextIterationSinkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NextIterationSinkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : NextIterationSinkOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NextIterationSinkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NextIterationSinkOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NextIterationSinkOpGenericAdaptor(RangeT values, const NextIterationSinkOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NextIterationSinkOp, typename = std::enable_if_t<std::is_same_v<LateInst, NextIterationSinkOp>>>
  NextIterationSinkOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getToken() {
    return (*getODSOperands(0).begin());
  }

  ValueT getInput() {
    return (*getODSOperands(1).begin());
  }

  RangeT getControlInputs() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class NextIterationSinkOpAdaptor : public NextIterationSinkOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NextIterationSinkOpGenericAdaptor::NextIterationSinkOpGenericAdaptor;
  NextIterationSinkOpAdaptor(NextIterationSinkOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NextIterationSinkOp : public ::mlir::Op<NextIterationSinkOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NextIterationSinkOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NextIterationSinkOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_token = 0;
  static constexpr int odsIndex_input = 1;
  static constexpr int odsIndex_controlInputs = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.NextIteration.Sink");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getToken() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getControlInputs() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getTokenMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getControlInputsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value token, ArrayRef<Value> operands, ArrayRef<NamedAttribute> attributes = {});
  static NextIterationSinkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value token, ArrayRef<Value> operands, ArrayRef<NamedAttribute> attributes = {});
  static NextIterationSinkOp create(::mlir::ImplicitLocOpBuilder &builder, Value token, ArrayRef<Value> operands, ArrayRef<NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value token, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static NextIterationSinkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value token, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static NextIterationSinkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value token, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value token, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static NextIterationSinkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value token, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static NextIterationSinkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value token, ::mlir::Value input, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NextIterationSinkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NextIterationSinkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NextIterationSinkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NextIterationSinkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  NextIterationSourceOp GetSource();
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::NextIterationSinkOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::NextIterationSourceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NextIterationSourceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  NextIterationSourceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.NextIteration.Source", odsAttrs.getContext());
  }

  NextIterationSourceOpGenericAdaptorBase(NextIterationSourceOp op);

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
class NextIterationSourceOpGenericAdaptor : public detail::NextIterationSourceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NextIterationSourceOpGenericAdaptorBase;
public:
  NextIterationSourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NextIterationSourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : NextIterationSourceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NextIterationSourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NextIterationSourceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NextIterationSourceOpGenericAdaptor(RangeT values, const NextIterationSourceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NextIterationSourceOp, typename = std::enable_if_t<std::is_same_v<LateInst, NextIterationSourceOp>>>
  NextIterationSourceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class NextIterationSourceOpAdaptor : public NextIterationSourceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NextIterationSourceOpGenericAdaptor::NextIterationSourceOpGenericAdaptor;
  NextIterationSourceOpAdaptor(NextIterationSourceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NextIterationSourceOp : public ::mlir::Op<NextIterationSourceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NextIterationSourceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NextIterationSourceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.NextIteration.Source");
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

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getToken() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type result_type, ArrayRef<NamedAttribute> attributes = {});
  static NextIterationSourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type result_type, ArrayRef<NamedAttribute> attributes = {});
  static NextIterationSourceOp create(::mlir::ImplicitLocOpBuilder &builder, Type result_type, ArrayRef<NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Type token, ::mlir::Type control);
  static NextIterationSourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Type token, ::mlir::Type control);
  static NextIterationSourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Type token, ::mlir::Type control);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static NextIterationSourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static NextIterationSourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NextIterationSourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NextIterationSourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NextIterationSourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NextIterationSourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  NextIterationSinkOp GetSink() {
    return cast<NextIterationSinkOp>(*getToken().user_begin());
  }
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::NextIterationSourceOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::SwitchNOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SwitchNOpGenericAdaptorBase {
public:
  struct Properties {
    using num_outsTy = ::mlir::IntegerAttr;
    num_outsTy num_outs;

    auto getNumOuts() const {
      auto &propStorage = this->num_outs;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setNumOuts(const ::mlir::IntegerAttr &propValue) {
      this->num_outs = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.num_outs == this->num_outs &&
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
  SwitchNOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor._SwitchN", odsAttrs.getContext());
  }

  SwitchNOpGenericAdaptorBase(SwitchNOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getNumOutsAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().num_outs);
    return attr;
  }

  uint64_t getNumOuts();
};

} // namespace detail
template <typename RangeT>
class SwitchNOpGenericAdaptor : public detail::SwitchNOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SwitchNOpGenericAdaptorBase;
  static constexpr int odsIndex_data = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_controlInputs = 2;
public:
  SwitchNOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SwitchNOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SwitchNOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SwitchNOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SwitchNOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SwitchNOpGenericAdaptor(RangeT values, const SwitchNOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SwitchNOp, typename = std::enable_if_t<std::is_same_v<LateInst, SwitchNOp>>>
  SwitchNOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getData() {
    return (*getODSOperands(0).begin());
  }

  ValueT getIndex() {
    return (*getODSOperands(1).begin());
  }

  RangeT getControlInputs() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SwitchNOpAdaptor : public SwitchNOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SwitchNOpGenericAdaptor::SwitchNOpGenericAdaptor;
  SwitchNOpAdaptor(SwitchNOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SwitchNOp : public ::mlir::Op<SwitchNOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SwitchNOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SwitchNOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_data = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_controlInputs = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("num_outs")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNumOutsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNumOutsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor._SwitchN");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::TensorType> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getControlInputs() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getDataMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIndexMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getControlInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getOutputs() {
    return getODSResults(0);
  }

  ::mlir::TypedValue<::mlir::Type> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
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
  ::mlir::IntegerAttr getNumOutsAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().num_outs);
  }

  uint64_t getNumOuts();
  void setNumOutsAttr(::mlir::IntegerAttr attr) {
    getProperties().num_outs = attr;
  }

  void setNumOuts(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::mlir::Type control, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, ::mlir::IntegerAttr num_outs);
  static SwitchNOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::mlir::Type control, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, ::mlir::IntegerAttr num_outs);
  static SwitchNOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::mlir::Type control, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, ::mlir::IntegerAttr num_outs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, ::mlir::IntegerAttr num_outs);
  static SwitchNOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, ::mlir::IntegerAttr num_outs);
  static SwitchNOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, ::mlir::IntegerAttr num_outs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::mlir::Type control, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, uint64_t num_outs);
  static SwitchNOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::mlir::Type control, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, uint64_t num_outs);
  static SwitchNOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::mlir::Type control, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, uint64_t num_outs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, uint64_t num_outs);
  static SwitchNOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, uint64_t num_outs);
  static SwitchNOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value index, ::mlir::ValueRange controlInputs, uint64_t num_outs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchNOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchNOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchNOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchNOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::SwitchNOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::SwitchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SwitchOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SwitchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tf_executor.Switch", odsAttrs.getContext());
  }

  SwitchOpGenericAdaptorBase(SwitchOp op);

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
class SwitchOpGenericAdaptor : public detail::SwitchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SwitchOpGenericAdaptorBase;
  static constexpr int odsIndex_data = 0;
  static constexpr int odsIndex_predicate = 1;
  static constexpr int odsIndex_controlInputs = 2;
public:
  SwitchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SwitchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SwitchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SwitchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SwitchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

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

  ValueT getData() {
    return (*getODSOperands(0).begin());
  }

  ValueT getPredicate() {
    return (*getODSOperands(1).begin());
  }

  RangeT getControlInputs() {
    return getODSOperands(2);
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
class SwitchOp : public ::mlir::Op<SwitchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::HasParent<GraphOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SwitchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SwitchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_data = 0;
  static constexpr int odsIndex_predicate = 1;
  static constexpr int odsIndex_controlInputs = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.Switch");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::TensorType> getPredicate() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getControlInputs() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getDataMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPredicateMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getControlInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getFalseOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getTrueOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type falseOutput, ::mlir::Type trueOutput, ::mlir::Type control, ::mlir::Value data, ::mlir::Value predicate, ::mlir::ValueRange controlInputs);
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type falseOutput, ::mlir::Type trueOutput, ::mlir::Type control, ::mlir::Value data, ::mlir::Value predicate, ::mlir::ValueRange controlInputs);
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type falseOutput, ::mlir::Type trueOutput, ::mlir::Type control, ::mlir::Value data, ::mlir::Value predicate, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value predicate, ::mlir::ValueRange controlInputs);
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value predicate, ::mlir::ValueRange controlInputs);
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value predicate, ::mlir::ValueRange controlInputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::SwitchOp)

namespace mlir::tf_executor {


//===----------------------------------------------------------------------===//
// ::mlir::tf_executor::YieldOp declarations
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
      odsOpName.emplace("tf_executor.yield", odsAttrs.getContext());
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
  static constexpr int odsIndex_fetches = 0;
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

  RangeT getFetches() {
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
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<IslandOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = YieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = YieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_fetches = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tf_executor.yield");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getFetches() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getFetchesMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange fetches);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange fetches);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange fetches);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::tf_executor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tf_executor::YieldOp)


#endif // GET_OP_CLASSES

