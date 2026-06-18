/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: PDLOps.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::pdl {

/// Apply a native constraint to a set of provided entities
/// `pdl.apply_native_constraint` operations apply a native C++ constraint, that
///     has been registered externally with the consumer of PDL, to a given set of
///     entities and optionally return a number of values.
/// 
///     Example:
/// 
///     ```mlir
///     // Apply `myConstraint` to the entities defined by `input`, `attr`, and `op`.
///     pdl.apply_native_constraint "myConstraint"(%input, %attr, %op : !pdl.value, !pdl.attribute, !pdl.operation)
///     // Apply constraint `with_result` to `root`. This constraint returns an attribute.
///     %attr = pdl.apply_native_constraint "with_result"(%root : !pdl.operation) : !pdl.attribute
///     ```
class ApplyNativeConstraintOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Apply a native rewrite method inside of pdl.rewrite region
/// `pdl.apply_native_rewrite` operations apply a native C++ function, that has
///     been registered externally with the consumer of PDL, to perform a rewrite
///     and optionally return a number of values. The native function may accept any
///     number of arguments. This operation is used within a pdl.rewrite region to enable
///     the interleaving of native rewrite methods with other pdl constructs.
/// 
///     Example:
/// 
///     ```mlir
///     // Apply a native rewrite method that returns an attribute.
///     %ret = pdl.apply_native_rewrite "myNativeFunc"(%arg0, %attr1) : !pdl.attribute
///     ```
/// 
///     ```c++
///     // The native rewrite as defined in C++:
///     static Attribute myNativeFunc(PatternRewriter &rewriter, Value arg0, Attribute arg1) {
///       // Just return the second arg.
///       return arg1;
///     }
/// 
///     void registerNativeRewrite(PDLPatternModule &pdlModule) {
///       pdlModule.registerRewriteFunction("myNativeFunc", myNativeFunc);
///     }
///     ```
class ApplyNativeRewriteOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Define an input attribute in a pattern
/// `pdl.attribute` operations capture named attribute edges into an operation.
///     Instances of this operation define, and partially constrain, attributes of a
///     given operation. A `pdl.attribute` may partially constrain the input by
///     specifying an expected attribute value type (via a `pdl.type` operation), or
///     a constant value for the attribute (via `val`). Only one of these may be set
///     for a given input, as the type of the constant value provides the type. When
///     defined within a `pdl.rewrite` region, the constant value must be specified.
/// 
///     Example:
/// 
///     ```mlir
///     // Define an attribute:
///     %attr = pdl.attribute
/// 
///     // Define an attribute with an expected type:
///     %type = pdl.type : i32
///     %attr = pdl.attribute : %type
/// 
///     // Define an attribute with a constant value:
///     %attr = pdl.attribute = "hello"
///     ```
class AttributeOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Mark an input operation as `erased`
/// `pdl.erase` operations are used within `pdl.rewrite` regions to specify that
///     an input operation should be marked as erased. The semantics of this
///     operation correspond with the `eraseOp` method on a `PatternRewriter`.
/// 
///     Example:
/// 
///     ```mlir
///     pdl.erase %root
///     ```
class EraseOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Define an external input operand in a pattern
/// `pdl.operand` operations capture external operand edges into an operation
///     node that originate from operations or block arguments not otherwise
///     specified within the pattern (i.e. via `pdl.result` or `pdl.results`). These
///     operations define individual operands of a given operation. A `pdl.operand`
///     may partially constrain an operand by specifying an expected value type
///     (via a `pdl.type` operation).
/// 
///     Example:
/// 
///     ```mlir
///     // Define an external operand:
///     %operand = pdl.operand
/// 
///     // Define an external operand with an expected type:
///     %type = pdl.type : i32
///     %operand = pdl.operand : %type
///     ```
class OperandOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Define a range of input operands in a pattern
/// `pdl.operands` operations capture external operand range edges into an
///     operation node that originate from operations or block arguments not
///     otherwise specified within the pattern (i.e. via `pdl.result` or
///     `pdl.results`). These operations define groups of input operands into a
///     given operation. A `pdl.operands` may partially constrain a set of input
///     operands by specifying expected value types (via `pdl.types` operations).
/// 
///     Example:
/// 
///     ```mlir
///     // Define a range of input operands:
///     %operands = pdl.operands
/// 
///     // Define a range of input operands with expected types:
///     %types = pdl.types : [i32, i64, i32]
///     %typed_operands = pdl.operands : %types
///     ```
class OperandsOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Define an operation within a pattern
/// `pdl.operation` operations define operation nodes within a pattern. Within
///     a match sequence, i.e. when directly nested within a `pdl.pattern`, these
///     operations correspond to input operations, or those that already existing
///     within the MLIR module. Inside of a `pdl.rewrite`, these operations
///     correspond to operations that should be created as part of the replacement
///     sequence.
/// 
///     `pdl.operation`s are composed of a name, and a set of attribute, operand,
///     and result type values, that map to what those that would be on a
///     constructed instance of that operation. The results of a `pdl.operation` are
///     a handle to the operation itself. Handles to the results of the operation
///     can be extracted via `pdl.result`.
/// 
///     Example:
/// 
///     ```mlir
///     // Define an instance of a `foo.op` operation.
///     %op = pdl.operation "foo.op"(%arg0, %arg1 : !pdl.value, !pdl.value)
///       {"attrA" = %attr0} -> (%type, %type : !pdl.type, !pdl.type)
///     ```
/// 
///     When used within a matching context, the name of the operation may be
///     omitted.
/// 
///     When used within a rewriting context, i.e. when defined within a
///     `pdl.rewrite`, all of the result types must be "inferable". This means that
///     the type must be attributable to either a constant type value or the result
///     type of another entity, such as an attribute, the result of a
///     `apply_native_rewrite`, or the result type of another operation. If the
///     result type value does not meet any of these criteria, the operation must
///     override the `InferTypeOpInterface` to ensure that the result types can be
///     inferred.
/// 
///     The operands of the operation are interpreted in the following ways:
/// 
///     1) A single !pdl.range<value>:
/// 
///     In this case, the single range is treated as all of the operands of the
///     operation.
/// 
///     ```mlir
///     // Define an instance with single range of operands.
///     %op = pdl.operation "func.return"(%allArgs : !pdl.range<value>)
///     ```
/// 
///     2) A variadic number of either !pdl.value or !pdl.range<value>:
/// 
///     In this case, the inputs are expected to correspond with the operand groups
///     defined on the operation in ODS.
/// 
///     ```tablgen
///     // Given the following operation definition in ODS:
///     def MyIndirectCallOp {
///       let results = (outs FunctionType:$call, Variadic<AnyType>:$args);
///     }
///     ```
/// 
///     ```mlir
///     // We can match the operands as so:
///     %op = pdl.operation "my.indirect_call"(%call, %args : !pdl.value, !pdl.range<value>)
///     ```
/// 
///     The results of the operation are interpreted in the following ways:
/// 
///     1) A single !pdl.range<type>:
/// 
///     In this case, the single range is treated as all of the result types of the
///     operation.
/// 
///     ```mlir
///     // Define an instance with single range of types.
///     %allResultTypes = pdl.types
///     %op = pdl.operation "builtin.unrealized_conversion_cast" -> (%allResultTypes : !pdl.types)
///     ```
/// 
///     2) A variadic number of either !pdl.type or !pdl.range<type>:
/// 
///     In this case, the inputs are expected to correspond with the result groups
///     defined on the operation in ODS.
/// 
///     ```tablgen
///     // Given the following operation definition in ODS:
///     def MyOp {
///       let results = (outs SomeType:$result, Variadic<SomeType>:$otherResults);
///     }
///     ```
/// 
///     ```mlir
///     // We can match the results as so:
///     %result = pdl.type
///     %otherResults = pdl.types
///     %op = pdl.operation "foo.op" -> (%result, %otherResults : !pdl.type, !pdl.range<type>)
///     ```
class OperationOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Define a rewrite pattern
/// `pdl.pattern` operations provide a transformable representation for a
///     `RewritePattern`. The attributes on this operation correspond to the various
///     metadata on a `RewritePattern`, such as the benefit. The match section of
///     the pattern is specified within the region body, with the rewrite provided
///     by a terminating `pdl.rewrite`.
/// 
///     Example:
/// 
///     ```mlir
///     // Provide a pattern matching "foo.op" that replaces the root with its
///     // operand.
///     pdl.pattern : benefit(1) {
///       %resultType = pdl.type
///       %inputOperand = pdl.operand
///       %root = pdl.operation "foo.op"(%inputOperand) -> (%resultType)
///       pdl.rewrite %root {
///         pdl.replace %root with (%inputOperand)
///       }
///     }
///     ```
class PatternOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Construct a range of pdl entities
/// `pdl.range` operations construct a range from a given set of PDL entities,
///     which all share the same underlying element type. For example, a
///     `!pdl.range<value>` may be constructed from a list of `!pdl.value`
///     or `!pdl.range<value>` entities.
/// 
///     Example:
/// 
///     ```mlir
///     // Construct a range of values.
///     %valueRange = pdl.range %inputValue, %inputRange : !pdl.value, !pdl.range<value>
/// 
///     // Construct a range of types.
///     %typeRange = pdl.range %inputType, %inputRange : !pdl.type, !pdl.range<type>
/// 
///     // Construct an empty range of types.
///     %valueRange = pdl.range : !pdl.range<type>
///     ```
/// 
///     TODO: Range construction is currently limited to rewrites, but it could
///     be extended to constraints under certain circustances; i.e., if we can
///     determine how to extract the underlying elements. If we can't, e.g. if
///     there are multiple sub ranges used for construction, we won't be able
///     to determine their sizes during constraint time.
class RangeOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Mark an input operation as `replaced`
/// `pdl.replace` operations are used within `pdl.rewrite` regions to specify
///     that an input operation should be marked as replaced. The semantics of this
///     operation correspond with the `replaceOp` method on a `PatternRewriter`. The
///     set of replacement values can be either:
///     * a single `Operation` (`replOperation` should be populated)
///       - The operation will be replaced with the results of this operation.
///     * a set of `Value`s (`replValues` should be populated)
///       - The operation will be replaced with these values.
/// 
///     Example:
/// 
///     ```mlir
///     // Replace root node with 2 values:
///     pdl.replace %root with (%val0, %val1 : !pdl.value, !pdl.value)
/// 
///     // Replace root node with a range of values:
///     pdl.replace %root with (%vals : !pdl.range<value>)
/// 
///     // Replace root with another operation:
///     pdl.replace %root with %otherOp
///     ```
class ReplaceOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Extract a result from an operation
/// `pdl.result` operations extract result edges from an operation node within
///     a pattern or rewrite region. The provided index is zero-based, and
///     represents the concrete result to extract, i.e. this is not the result index
///     as defined by the ODS definition of the operation.
/// 
///     Example:
/// 
///     ```mlir
///     // Extract a result:
///     %operation = pdl.operation ...
///     %pdl_result = pdl.result 1 of %operation
/// 
///     // Imagine the following IR being matched:
///     %result_0, %result_1 = foo.op ...
/// 
///     // If the example pattern snippet above were matching against `foo.op` in
///     // the IR snippet, `%pdl_result` would correspond to `%result_1`.
///     ```
class ResultOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Extract a result group from an operation
/// `pdl.results` operations extract a result group from an operation within a
///     pattern or rewrite region. If an index is provided, this operation extracts
///     a result group as defined by the ODS definition of the operation. In this
///     case the result of this operation may be either a single `pdl.value` or
///     a `pdl.range<value>`, depending on the constraint of the result in ODS. If
///     no index is provided, this operation extracts the full result range of the
///     operation.
/// 
///     Example:
/// 
///     ```mlir
///     // Extract all of the results of an operation:
///     %operation = pdl.operation ...
///     %results = pdl.results of %operation
/// 
///     // Extract the results in the first result group of an operation, which is
///     // variadic:
///     %operation = pdl.operation ...
///     %results = pdl.results 0 of %operation -> !pdl.range<value>
/// 
///     // Extract the results in the second result group of an operation, which is
///     // not variadic:
///     %operation = pdl.operation ...
///     %results = pdl.results 1 of %operation -> !pdl.value
///     ```
class ResultsOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Specify the rewrite of a matched pattern
/// `pdl.rewrite` operations terminate the region of a `pdl.pattern` and specify
///     the main rewrite of a `pdl.pattern`, on the optional root operation. The
///     rewrite is specified either via a string name (`name`) to a native
///     rewrite function, or via the region body. The rewrite region, if specified,
///     must contain a single block. If the rewrite is external it functions
///     similarly to `pdl.apply_native_rewrite`, and takes a set of additional
///     positional values defined within the matcher as arguments. If the rewrite is
///     external, the root operation is passed to the native function as the leading
///     arguments. The root operation, if provided, specifies the starting point in
///     the pattern for the subgraph isomorphism search. Pattern matching will proceed
///     from this node downward (towards the defining operation) or upward
///     (towards the users) until all the operations in the pattern have been matched.
///     If the root is omitted, the pdl_interp lowering will automatically select
///     the best root of the pdl.rewrite among all the operations in the pattern.
/// 
///     Example:
/// 
///     ```mlir
///     // Specify an external rewrite function:
///     pdl.rewrite %root with "myExternalRewriter"(%value : !pdl.value)
/// 
///     // Specify a rewrite inline using PDL with the given root:
///     pdl.rewrite %root {
///       %op = pdl.operation "foo.op"(%arg0, %arg1)
///       pdl.replace %root with %op
///     }
/// 
///     // Specify a rewrite inline using PDL, automatically selecting root:
///     pdl.rewrite {
///       %op1 = pdl.operation "foo.op"(%arg0, %arg1)
///       %op2 = pdl.operation "bar.op"(%arg0, %arg1)
///       pdl.replace %root1 with %op1
///       pdl.replace %root2 with %op2
///     }
///     ```
class RewriteOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Define a type handle within a pattern
/// `pdl.type` operations capture result type constraints of `Attributes`,
///     `Values`, and `Operations`. Instances of this operation define, and
///     partially constrain, results types of a given entity. A `pdl.type` may
///     partially constrain the result by specifying a constant `Type`.
/// 
///     Example:
/// 
///     ```mlir
///     // Define a type:
///     %type = pdl.type
/// 
///     // Define a type with a constant value:
///     %type = pdl.type : i32
///     ```
class TypeOp;

} // namespace mlir::pdl
namespace mlir::pdl {

/// Define a range of type handles within a pattern
/// `pdl.types` operations capture result type constraints of `Value`s, and
///     `Operation`s. Instances of this operation define results types of a given
///     entity. A `pdl.types` may partially constrain the results by specifying
///     an array of `Type`s.
/// 
///     Example:
/// 
///     ```mlir
///     // Define a range of types:
///     %types = pdl.types
/// 
///     // Define a range of types with a range of constant values:
///     %types = pdl.types : [i32, i64, i32]
///     ```
class TypesOp;

} // namespace mlir::pdl
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::ApplyNativeConstraintOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyNativeConstraintOpGenericAdaptorBase {
public:
  struct Properties {
    using isNegatedTy = ::mlir::BoolAttr;
    isNegatedTy isNegated;

    auto getIsNegated() const {
      auto &propStorage = this->isNegated;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setIsNegated(const ::mlir::BoolAttr &propValue) {
      this->isNegated = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.isNegated == this->isNegated &&
        rhs.name == this->name &&
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
  ApplyNativeConstraintOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.apply_native_constraint", odsAttrs.getContext());
  }

  ApplyNativeConstraintOpGenericAdaptorBase(ApplyNativeConstraintOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
  ::mlir::BoolAttr getIsNegatedAttr();
  bool getIsNegated();
};

} // namespace detail
template <typename RangeT>
class ApplyNativeConstraintOpGenericAdaptor : public detail::ApplyNativeConstraintOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyNativeConstraintOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  ApplyNativeConstraintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyNativeConstraintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyNativeConstraintOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyNativeConstraintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyNativeConstraintOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyNativeConstraintOpGenericAdaptor(RangeT values, const ApplyNativeConstraintOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyNativeConstraintOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyNativeConstraintOp>>>
  ApplyNativeConstraintOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ApplyNativeConstraintOpAdaptor : public ApplyNativeConstraintOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyNativeConstraintOpGenericAdaptor::ApplyNativeConstraintOpGenericAdaptor;
  ApplyNativeConstraintOpAdaptor(ApplyNativeConstraintOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyNativeConstraintOp : public ::mlir::Op<ApplyNativeConstraintOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<pdl::PatternOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyNativeConstraintOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyNativeConstraintOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_args = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("isNegated"), ::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIsNegatedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIsNegatedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.apply_native_constraint");
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  ::mlir::BoolAttr getIsNegatedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().isNegated);
  }

  bool getIsNegated();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setIsNegatedAttr(::mlir::BoolAttr attr) {
    getProperties().isNegated = attr;
  }

  void setIsNegated(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args, ::mlir::BoolAttr isNegated = nullptr);
  static ApplyNativeConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args, ::mlir::BoolAttr isNegated = nullptr);
  static ApplyNativeConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args, ::mlir::BoolAttr isNegated = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args, bool isNegated = false);
  static ApplyNativeConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args, bool isNegated = false);
  static ApplyNativeConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args, bool isNegated = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyNativeConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyNativeConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyNativeConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyNativeConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::ApplyNativeConstraintOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::ApplyNativeRewriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyNativeRewriteOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.name == this->name &&
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
  ApplyNativeRewriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.apply_native_rewrite", odsAttrs.getContext());
  }

  ApplyNativeRewriteOpGenericAdaptorBase(ApplyNativeRewriteOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
};

} // namespace detail
template <typename RangeT>
class ApplyNativeRewriteOpGenericAdaptor : public detail::ApplyNativeRewriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyNativeRewriteOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  ApplyNativeRewriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyNativeRewriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyNativeRewriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyNativeRewriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyNativeRewriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyNativeRewriteOpGenericAdaptor(RangeT values, const ApplyNativeRewriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyNativeRewriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyNativeRewriteOp>>>
  ApplyNativeRewriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ApplyNativeRewriteOpAdaptor : public ApplyNativeRewriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyNativeRewriteOpGenericAdaptor::ApplyNativeRewriteOpGenericAdaptor;
  ApplyNativeRewriteOpAdaptor(ApplyNativeRewriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyNativeRewriteOp : public ::mlir::Op<ApplyNativeRewriteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<pdl::RewriteOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyNativeRewriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyNativeRewriteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_args = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.apply_native_rewrite");
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args);
  static ApplyNativeRewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args);
  static ApplyNativeRewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args);
  static ApplyNativeRewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args);
  static ApplyNativeRewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyNativeRewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyNativeRewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyNativeRewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyNativeRewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::ApplyNativeRewriteOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::AttributeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AttributeOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::mlir::Attribute;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::dyn_cast_or_null<::mlir::Attribute>(propStorage);
    }
    void setValue(const ::mlir::Attribute &propValue) {
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
  AttributeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.attribute", odsAttrs.getContext());
  }

  AttributeOpGenericAdaptorBase(AttributeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Attribute getValueAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().value);
    return attr;
  }

  ::std::optional<::mlir::Attribute> getValue();
};

} // namespace detail
template <typename RangeT>
class AttributeOpGenericAdaptor : public detail::AttributeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AttributeOpGenericAdaptorBase;
  static constexpr int odsIndex_valueType = 0;
public:
  AttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AttributeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AttributeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AttributeOpGenericAdaptor(RangeT values, const AttributeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AttributeOp, typename = std::enable_if_t<std::is_same_v<LateInst, AttributeOp>>>
  AttributeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValueType() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AttributeOpAdaptor : public AttributeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AttributeOpGenericAdaptor::AttributeOpGenericAdaptor;
  AttributeOpAdaptor(AttributeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AttributeOp : public ::mlir::Op<AttributeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::AttributeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AttributeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AttributeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_valueType = 0;
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
    return ::llvm::StringLiteral("pdl.attribute");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::TypeType> getValueType() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::pdl::TypeType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::pdl::TypeType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getValueTypeMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::AttributeType> getAttr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::AttributeType>>(*getODSResults(0).begin());
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
  ::mlir::Attribute getValueAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().value);
  }

  ::std::optional<::mlir::Attribute> getValue();
  void setValueAttr(::mlir::Attribute attr) {
    getProperties().value = attr;
  }

  ::mlir::Attribute removeValueAttr() {
      auto attr = getProperties().value;
      getProperties().value = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value type = Value());
  static AttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value type = Value());
  static AttributeOp create(::mlir::ImplicitLocOpBuilder &builder, Value type = Value());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Attribute attr);
  static AttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Attribute attr);
  static AttributeOp create(::mlir::ImplicitLocOpBuilder &builder, Attribute attr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type attr, /*optional*/::mlir::Value valueType, /*optional*/::mlir::Attribute value);
  static AttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type attr, /*optional*/::mlir::Value valueType, /*optional*/::mlir::Attribute value);
  static AttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type attr, /*optional*/::mlir::Value valueType, /*optional*/::mlir::Attribute value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value valueType, /*optional*/::mlir::Attribute value);
  static AttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value valueType, /*optional*/::mlir::Attribute value);
  static AttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value valueType, /*optional*/::mlir::Attribute value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::AttributeOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::EraseOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EraseOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  EraseOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.erase", odsAttrs.getContext());
  }

  EraseOpGenericAdaptorBase(EraseOp op);

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
class EraseOpGenericAdaptor : public detail::EraseOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EraseOpGenericAdaptorBase;
  static constexpr int odsIndex_opValue = 0;
public:
  EraseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EraseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : EraseOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EraseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EraseOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EraseOpGenericAdaptor(RangeT values, const EraseOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EraseOp, typename = std::enable_if_t<std::is_same_v<LateInst, EraseOp>>>
  EraseOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getOpValue() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class EraseOpAdaptor : public EraseOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EraseOpGenericAdaptor::EraseOpGenericAdaptor;
  EraseOpAdaptor(EraseOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EraseOp : public ::mlir::Op<EraseOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParent<pdl::RewriteOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EraseOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EraseOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_opValue = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.erase");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getOpValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getOpValueMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value opValue);
  static EraseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value opValue);
  static EraseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value opValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value opValue);
  static EraseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value opValue);
  static EraseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value opValue);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EraseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EraseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EraseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EraseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::EraseOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::OperandOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OperandOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  OperandOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.operand", odsAttrs.getContext());
  }

  OperandOpGenericAdaptorBase(OperandOp op);

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
class OperandOpGenericAdaptor : public detail::OperandOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OperandOpGenericAdaptorBase;
  static constexpr int odsIndex_valueType = 0;
public:
  OperandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OperandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : OperandOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OperandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OperandOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OperandOpGenericAdaptor(RangeT values, const OperandOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OperandOp, typename = std::enable_if_t<std::is_same_v<LateInst, OperandOp>>>
  OperandOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValueType() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class OperandOpAdaptor : public OperandOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OperandOpGenericAdaptor::OperandOpGenericAdaptor;
  OperandOpAdaptor(OperandOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OperandOp : public ::mlir::Op<OperandOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::ValueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<pdl::PatternOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OperandOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OperandOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_valueType = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.operand");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::TypeType> getValueType() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::pdl::TypeType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::pdl::TypeType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getValueTypeMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::ValueType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::ValueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static OperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static OperandOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, /*optional*/::mlir::Value valueType);
  static OperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, /*optional*/::mlir::Value valueType);
  static OperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, /*optional*/::mlir::Value valueType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value valueType);
  static OperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value valueType);
  static OperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value valueType);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::OperandOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::OperandsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OperandsOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  OperandsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.operands", odsAttrs.getContext());
  }

  OperandsOpGenericAdaptorBase(OperandsOp op);

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
class OperandsOpGenericAdaptor : public detail::OperandsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OperandsOpGenericAdaptorBase;
  static constexpr int odsIndex_valueType = 0;
public:
  OperandsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OperandsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : OperandsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OperandsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OperandsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OperandsOpGenericAdaptor(RangeT values, const OperandsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OperandsOp, typename = std::enable_if_t<std::is_same_v<LateInst, OperandsOp>>>
  OperandsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValueType() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class OperandsOpAdaptor : public OperandsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OperandsOpGenericAdaptor::OperandsOpGenericAdaptor;
  OperandsOpAdaptor(OperandsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OperandsOp : public ::mlir::Op<OperandsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::RangeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<pdl::PatternOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OperandsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OperandsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_valueType = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.operands");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::RangeType> getValueType() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::pdl::RangeType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::pdl::RangeType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getValueTypeMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::RangeType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::RangeType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static OperandsOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static OperandsOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, /*optional*/::mlir::Value valueType);
  static OperandsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, /*optional*/::mlir::Value valueType);
  static OperandsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, /*optional*/::mlir::Value valueType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value valueType);
  static OperandsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value valueType);
  static OperandsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value valueType);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OperandsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OperandsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OperandsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OperandsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::OperandsOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::OperationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OperationOpGenericAdaptorBase {
public:
  struct Properties {
    using attributeValueNamesTy = ::mlir::ArrayAttr;
    attributeValueNamesTy attributeValueNames;

    auto getAttributeValueNames() const {
      auto &propStorage = this->attributeValueNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setAttributeValueNames(const ::mlir::ArrayAttr &propValue) {
      this->attributeValueNames = propValue;
    }
    using opNameTy = ::mlir::StringAttr;
    opNameTy opName;

    auto getOpName() const {
      auto &propStorage = this->opName;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setOpName(const ::mlir::StringAttr &propValue) {
      this->opName = propValue;
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
        rhs.attributeValueNames == this->attributeValueNames &&
        rhs.opName == this->opName &&
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
  OperationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.operation", odsAttrs.getContext());
  }

  OperationOpGenericAdaptorBase(OperationOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getOpNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().opName);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getOpName();
  ::mlir::ArrayAttr getAttributeValueNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().attributeValueNames);
    return attr;
  }

  ::mlir::ArrayAttr getAttributeValueNames();
};

} // namespace detail
template <typename RangeT>
class OperationOpGenericAdaptor : public detail::OperationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OperationOpGenericAdaptorBase;
  static constexpr int odsIndex_operandValues = 0;
  static constexpr int odsIndex_attributeValues = 1;
  static constexpr int odsIndex_typeValues = 2;
public:
  OperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : OperationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : OperationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OperationOpGenericAdaptor(RangeT values, const OperationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OperationOp, typename = std::enable_if_t<std::is_same_v<LateInst, OperationOp>>>
  OperationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperandValues() {
    return getODSOperands(0);
  }

  RangeT getAttributeValues() {
    return getODSOperands(1);
  }

  RangeT getTypeValues() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class OperationOpAdaptor : public OperationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OperationOpGenericAdaptor::OperationOpGenericAdaptor;
  OperationOpAdaptor(OperationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OperationOp : public ::mlir::Op<OperationOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::OperationType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OperationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OperationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operandValues = 0;
  static constexpr int odsIndex_attributeValues = 1;
  static constexpr int odsIndex_typeValues = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("attributeValueNames"), ::llvm::StringRef("opName"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAttributeValueNamesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAttributeValueNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOpNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getOpNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.operation");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getOperandValues() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAttributeValues() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getTypeValues() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getOperandValuesMutable();
  ::mlir::MutableOperandRange getAttributeValuesMutable();
  ::mlir::MutableOperandRange getTypeValuesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSResults(0).begin());
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
  ::mlir::StringAttr getOpNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().opName);
  }

  ::std::optional< ::llvm::StringRef > getOpName();
  ::mlir::ArrayAttr getAttributeValueNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().attributeValueNames);
  }

  ::mlir::ArrayAttr getAttributeValueNames();
  void setOpNameAttr(::mlir::StringAttr attr) {
    getProperties().opName = attr;
  }

  void setOpName(::std::optional<::llvm::StringRef> attrValue);
  void setAttributeValueNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().attributeValueNames = attr;
  }

  ::mlir::Attribute removeOpNameAttr() {
      auto attr = getProperties().opName;
      getProperties().opName = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, std::optional<StringRef> name = std::nullopt, ValueRange operandValues = {}, ArrayRef<StringRef> attrNames = {}, ValueRange attrValues = {}, ValueRange resultTypes = {});
  static OperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, std::optional<StringRef> name = std::nullopt, ValueRange operandValues = {}, ArrayRef<StringRef> attrNames = {}, ValueRange attrValues = {}, ValueRange resultTypes = {});
  static OperationOp create(::mlir::ImplicitLocOpBuilder &builder, std::optional<StringRef> name = std::nullopt, ValueRange operandValues = {}, ArrayRef<StringRef> attrNames = {}, ValueRange attrValues = {}, ValueRange resultTypes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type op, /*optional*/::mlir::StringAttr opName, ::mlir::ValueRange operandValues, ::mlir::ValueRange attributeValues, ::mlir::ArrayAttr attributeValueNames, ::mlir::ValueRange typeValues);
  static OperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type op, /*optional*/::mlir::StringAttr opName, ::mlir::ValueRange operandValues, ::mlir::ValueRange attributeValues, ::mlir::ArrayAttr attributeValueNames, ::mlir::ValueRange typeValues);
  static OperationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type op, /*optional*/::mlir::StringAttr opName, ::mlir::ValueRange operandValues, ::mlir::ValueRange attributeValues, ::mlir::ArrayAttr attributeValueNames, ::mlir::ValueRange typeValues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::StringAttr opName, ::mlir::ValueRange operandValues, ::mlir::ValueRange attributeValues, ::mlir::ArrayAttr attributeValueNames, ::mlir::ValueRange typeValues);
  static OperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::StringAttr opName, ::mlir::ValueRange operandValues, ::mlir::ValueRange attributeValues, ::mlir::ArrayAttr attributeValueNames, ::mlir::ValueRange typeValues);
  static OperationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::StringAttr opName, ::mlir::ValueRange operandValues, ::mlir::ValueRange attributeValues, ::mlir::ArrayAttr attributeValueNames, ::mlir::ValueRange typeValues);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OperationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OperationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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
  /// Returns true if the operation type referenced supports result type
  /// inference.
  bool hasTypeInference();

  /// Returns true if the operation type referenced might support result type
  /// inference, i.e. it supports type reference or is currently not
  /// registered in the context. Returns false if the root operation name
  /// has not been set.
  bool mightHaveTypeInference();
};

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::OperationOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::PatternOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PatternOpGenericAdaptorBase {
public:
  struct Properties {
    using benefitTy = ::mlir::IntegerAttr;
    benefitTy benefit;

    auto getBenefit() const {
      auto &propStorage = this->benefit;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setBenefit(const ::mlir::IntegerAttr &propValue) {
      this->benefit = propValue;
    }
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.benefit == this->benefit &&
        rhs.sym_name == this->sym_name &&
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
  PatternOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.pattern", odsAttrs.getContext());
  }

  PatternOpGenericAdaptorBase(PatternOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getBenefitAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().benefit);
    return attr;
  }

  uint16_t getBenefit();
  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  ::mlir::Region &getBodyRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class PatternOpGenericAdaptor : public detail::PatternOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PatternOpGenericAdaptorBase;
public:
  PatternOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PatternOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PatternOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PatternOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PatternOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PatternOpGenericAdaptor(RangeT values, const PatternOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PatternOp, typename = std::enable_if_t<std::is_same_v<LateInst, PatternOp>>>
  PatternOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PatternOpAdaptor : public PatternOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PatternOpGenericAdaptor::PatternOpGenericAdaptor;
  PatternOpAdaptor(PatternOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PatternOp : public ::mlir::Op<PatternOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::SymbolOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PatternOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PatternOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<PatternOp>::getAsmResultNames;
  using ::mlir::OpAsmOpInterface::Trait<PatternOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<PatternOp>::getAsmBlockNames;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("benefit"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBenefitAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBenefitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.pattern");
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

  ::mlir::Region &getBodyRegion() {
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
  ::mlir::IntegerAttr getBenefitAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().benefit);
  }

  uint16_t getBenefit();
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  void setBenefitAttr(::mlir::IntegerAttr attr) {
    getProperties().benefit = attr;
  }

  void setBenefit(uint16_t attrValue);
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeSymNameAttr() {
      auto attr = getProperties().sym_name;
      getProperties().sym_name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, std::optional<uint16_t> benefit = 1, std::optional<StringRef> name = std::nullopt);
  static PatternOp create(::mlir::OpBuilder &builder, ::mlir::Location location, std::optional<uint16_t> benefit = 1, std::optional<StringRef> name = std::nullopt);
  static PatternOp create(::mlir::ImplicitLocOpBuilder &builder, std::optional<uint16_t> benefit = 1, std::optional<StringRef> name = std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::IntegerAttr benefit, /*optional*/::mlir::StringAttr sym_name);
  static PatternOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::IntegerAttr benefit, /*optional*/::mlir::StringAttr sym_name);
  static PatternOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::IntegerAttr benefit, /*optional*/::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr benefit, /*optional*/::mlir::StringAttr sym_name);
  static PatternOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr benefit, /*optional*/::mlir::StringAttr sym_name);
  static PatternOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr benefit, /*optional*/::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint16_t benefit, /*optional*/::mlir::StringAttr sym_name);
  static PatternOp create(::mlir::OpBuilder &builder, ::mlir::Location location, uint16_t benefit, /*optional*/::mlir::StringAttr sym_name);
  static PatternOp create(::mlir::ImplicitLocOpBuilder &builder, uint16_t benefit, /*optional*/::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint16_t benefit, /*optional*/::mlir::StringAttr sym_name);
  static PatternOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint16_t benefit, /*optional*/::mlir::StringAttr sym_name);
  static PatternOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint16_t benefit, /*optional*/::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PatternOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PatternOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PatternOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PatternOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  static ::llvm::StringRef getDefaultDialect();
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
  //===------------------------------------------------------------------===//
  // SymbolOpInterface Methods
  //===------------------------------------------------------------------===//

  /// A PatternOp may optionally define a symbol.
  bool isOptionalSymbol() { return true; }

  /// Returns the rewrite operation of this pattern.
  RewriteOp getRewriter();
};

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::PatternOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::RangeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RangeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  RangeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.range", odsAttrs.getContext());
  }

  RangeOpGenericAdaptorBase(RangeOp op);

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
class RangeOpGenericAdaptor : public detail::RangeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RangeOpGenericAdaptorBase;
  static constexpr int odsIndex_arguments = 0;
public:
  RangeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RangeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : RangeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RangeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RangeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RangeOpGenericAdaptor(RangeT values, const RangeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RangeOp, typename = std::enable_if_t<std::is_same_v<LateInst, RangeOp>>>
  RangeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArguments() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RangeOpAdaptor : public RangeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RangeOpGenericAdaptor::RangeOpGenericAdaptor;
  RangeOpAdaptor(RangeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RangeOp : public ::mlir::Op<RangeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::RangeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<pdl::RewriteOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RangeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RangeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_arguments = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.range");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getArguments() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getArgumentsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::RangeType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::RangeType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange arguments);
  static RangeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange arguments);
  static RangeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange arguments);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RangeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RangeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RangeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RangeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::RangeOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::ReplaceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReplaceOpGenericAdaptorBase {
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
  ReplaceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.replace", odsAttrs.getContext());
  }

  ReplaceOpGenericAdaptorBase(ReplaceOp op);

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
class ReplaceOpGenericAdaptor : public detail::ReplaceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReplaceOpGenericAdaptorBase;
  static constexpr int odsIndex_opValue = 0;
  static constexpr int odsIndex_replOperation = 1;
  static constexpr int odsIndex_replValues = 2;
public:
  ReplaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReplaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReplaceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReplaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ReplaceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReplaceOpGenericAdaptor(RangeT values, const ReplaceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReplaceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReplaceOp>>>
  ReplaceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getOpValue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getReplOperation() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getReplValues() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReplaceOpAdaptor : public ReplaceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReplaceOpGenericAdaptor::ReplaceOpGenericAdaptor;
  ReplaceOpAdaptor(ReplaceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReplaceOp : public ::mlir::Op<ReplaceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::HasParent<pdl::RewriteOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReplaceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReplaceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_opValue = 0;
  static constexpr int odsIndex_replOperation = 1;
  static constexpr int odsIndex_replValues = 2;
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
    return ::llvm::StringLiteral("pdl.replace");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getOpValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getReplOperation() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::pdl::OperationType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getReplValues() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getOpValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getReplOperationMutable();
  ::mlir::MutableOperandRange getReplValuesMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value opValue, /*optional*/::mlir::Value replOperation, ::mlir::ValueRange replValues);
  static ReplaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value opValue, /*optional*/::mlir::Value replOperation, ::mlir::ValueRange replValues);
  static ReplaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value opValue, /*optional*/::mlir::Value replOperation, ::mlir::ValueRange replValues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value opValue, /*optional*/::mlir::Value replOperation, ::mlir::ValueRange replValues);
  static ReplaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value opValue, /*optional*/::mlir::Value replOperation, ::mlir::ValueRange replValues);
  static ReplaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value opValue, /*optional*/::mlir::Value replOperation, ::mlir::ValueRange replValues);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    return {};
  }

public:
};

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::ReplaceOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::ResultOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ResultOpGenericAdaptorBase {
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
  ResultOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.result", odsAttrs.getContext());
  }

  ResultOpGenericAdaptorBase(ResultOp op);

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

  uint32_t getIndex();
};

} // namespace detail
template <typename RangeT>
class ResultOpGenericAdaptor : public detail::ResultOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ResultOpGenericAdaptorBase;
  static constexpr int odsIndex_parent = 0;
public:
  ResultOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ResultOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ResultOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ResultOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ResultOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ResultOpGenericAdaptor(RangeT values, const ResultOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ResultOp, typename = std::enable_if_t<std::is_same_v<LateInst, ResultOp>>>
  ResultOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getParent() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ResultOpAdaptor : public ResultOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ResultOpGenericAdaptor::ResultOpGenericAdaptor;
  ResultOpAdaptor(ResultOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ResultOp : public ::mlir::Op<ResultOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::ValueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ResultOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ResultOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_parent = 0;
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
    return ::llvm::StringLiteral("pdl.result");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getParent() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getParentMutable() {
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

  ::mlir::TypedValue<::mlir::pdl::ValueType> getVal() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::ValueType>>(*getODSResults(0).begin());
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

  uint32_t getIndex();
  void setIndexAttr(::mlir::IntegerAttr attr) {
    getProperties().index = attr;
  }

  void setIndex(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type val, ::mlir::Value parent, ::mlir::IntegerAttr index);
  static ResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type val, ::mlir::Value parent, ::mlir::IntegerAttr index);
  static ResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type val, ::mlir::Value parent, ::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value parent, ::mlir::IntegerAttr index);
  static ResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value parent, ::mlir::IntegerAttr index);
  static ResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value parent, ::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type val, ::mlir::Value parent, uint32_t index);
  static ResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type val, ::mlir::Value parent, uint32_t index);
  static ResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type val, ::mlir::Value parent, uint32_t index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value parent, uint32_t index);
  static ResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value parent, uint32_t index);
  static ResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value parent, uint32_t index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
};

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::ResultOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::ResultsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ResultsOpGenericAdaptorBase {
public:
  struct Properties {
    using indexTy = ::mlir::IntegerAttr;
    indexTy index;

    auto getIndex() const {
      auto &propStorage = this->index;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
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
  ResultsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.results", odsAttrs.getContext());
  }

  ResultsOpGenericAdaptorBase(ResultsOp op);

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
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().index);
    return attr;
  }

  ::std::optional<uint32_t> getIndex();
};

} // namespace detail
template <typename RangeT>
class ResultsOpGenericAdaptor : public detail::ResultsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ResultsOpGenericAdaptorBase;
  static constexpr int odsIndex_parent = 0;
public:
  ResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ResultsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ResultsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ResultsOpGenericAdaptor(RangeT values, const ResultsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ResultsOp, typename = std::enable_if_t<std::is_same_v<LateInst, ResultsOp>>>
  ResultsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getParent() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ResultsOpAdaptor : public ResultsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ResultsOpGenericAdaptor::ResultsOpGenericAdaptor;
  ResultsOpAdaptor(ResultsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ResultsOp : public ::mlir::Op<ResultsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::PDLType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ResultsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ResultsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_parent = 0;
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
    return ::llvm::StringLiteral("pdl.results");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getParent() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getParentMutable() {
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

  ::mlir::TypedValue<::mlir::pdl::PDLType> getVal() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::PDLType>>(*getODSResults(0).begin());
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
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().index);
  }

  ::std::optional<uint32_t> getIndex();
  void setIndexAttr(::mlir::IntegerAttr attr) {
    getProperties().index = attr;
  }

  void setIndex(::std::optional<uint32_t> attrValue);
  ::mlir::Attribute removeIndexAttr() {
      auto attr = getProperties().index;
      getProperties().index = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type val, ::mlir::Value parent, /*optional*/::mlir::IntegerAttr index);
  static ResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type val, ::mlir::Value parent, /*optional*/::mlir::IntegerAttr index);
  static ResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type val, ::mlir::Value parent, /*optional*/::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value parent, /*optional*/::mlir::IntegerAttr index);
  static ResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value parent, /*optional*/::mlir::IntegerAttr index);
  static ResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value parent, /*optional*/::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::ResultsOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::RewriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RewriteOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
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
        rhs.name == this->name &&
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
  RewriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.rewrite", odsAttrs.getContext());
  }

  RewriteOpGenericAdaptorBase(RewriteOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::Region &getBodyRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class RewriteOpGenericAdaptor : public detail::RewriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RewriteOpGenericAdaptorBase;
  static constexpr int odsIndex_root = 0;
  static constexpr int odsIndex_externalArgs = 1;
public:
  RewriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RewriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : RewriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RewriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : RewriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RewriteOpGenericAdaptor(RangeT values, const RewriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RewriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, RewriteOp>>>
  RewriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRoot() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getExternalArgs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RewriteOpAdaptor : public RewriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RewriteOpGenericAdaptor::RewriteOpGenericAdaptor;
  RewriteOpAdaptor(RewriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RewriteOp : public ::mlir::Op<RewriteOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<pdl::PatternOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RewriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RewriteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_root = 0;
  static constexpr int odsIndex_externalArgs = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<RewriteOp>::getAsmResultNames;
  using ::mlir::OpAsmOpInterface::Trait<RewriteOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<RewriteOp>::getAsmBlockNames;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.rewrite");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getRoot() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::pdl::OperationType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getExternalArgs() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getRootMutable();
  ::mlir::MutableOperandRange getExternalArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Region &getBodyRegion() {
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Value root, /*optional*/::mlir::StringAttr name, ::mlir::ValueRange externalArgs);
  static RewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Value root, /*optional*/::mlir::StringAttr name, ::mlir::ValueRange externalArgs);
  static RewriteOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Value root, /*optional*/::mlir::StringAttr name, ::mlir::ValueRange externalArgs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value root, /*optional*/::mlir::StringAttr name, ::mlir::ValueRange externalArgs);
  static RewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value root, /*optional*/::mlir::StringAttr name, ::mlir::ValueRange externalArgs);
  static RewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value root, /*optional*/::mlir::StringAttr name, ::mlir::ValueRange externalArgs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  static ::llvm::StringRef getDefaultDialect();
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

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::RewriteOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::TypeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TypeOpGenericAdaptorBase {
public:
  struct Properties {
    using constantTypeTy = ::mlir::TypeAttr;
    constantTypeTy constantType;

    auto getConstantType() const {
      auto &propStorage = this->constantType;
      return ::llvm::dyn_cast_or_null<::mlir::TypeAttr>(propStorage);
    }
    void setConstantType(const ::mlir::TypeAttr &propValue) {
      this->constantType = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.constantType == this->constantType &&
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
  TypeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.type", odsAttrs.getContext());
  }

  TypeOpGenericAdaptorBase(TypeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getConstantTypeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::TypeAttr>(getProperties().constantType);
    return attr;
  }

  ::std::optional<::mlir::Type> getConstantType();
};

} // namespace detail
template <typename RangeT>
class TypeOpGenericAdaptor : public detail::TypeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TypeOpGenericAdaptorBase;
public:
  TypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TypeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TypeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TypeOpGenericAdaptor(RangeT values, const TypeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TypeOp, typename = std::enable_if_t<std::is_same_v<LateInst, TypeOp>>>
  TypeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class TypeOpAdaptor : public TypeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TypeOpGenericAdaptor::TypeOpGenericAdaptor;
  TypeOpAdaptor(TypeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TypeOp : public ::mlir::Op<TypeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::TypeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TypeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TypeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("constantType")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getConstantTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getConstantTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.type");
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

  ::mlir::TypedValue<::mlir::pdl::TypeType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::TypeType>>(*getODSResults(0).begin());
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
  ::mlir::TypeAttr getConstantTypeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::TypeAttr>(getProperties().constantType);
  }

  ::std::optional<::mlir::Type> getConstantType();
  void setConstantTypeAttr(::mlir::TypeAttr attr) {
    getProperties().constantType = attr;
  }

  void setConstantType(::std::optional<::mlir::Type> attrValue);
  ::mlir::Attribute removeConstantTypeAttr() {
      auto attr = getProperties().constantType;
      getProperties().constantType = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::TypeAttr constantType);
  static TypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::TypeAttr constantType);
  static TypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::TypeAttr constantType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::TypeAttr constantType);
  static TypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::TypeAttr constantType);
  static TypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::TypeAttr constantType);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::TypeOp)

namespace mlir::pdl {


//===----------------------------------------------------------------------===//
// ::mlir::pdl::TypesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TypesOpGenericAdaptorBase {
public:
  struct Properties {
    using constantTypesTy = ::mlir::ArrayAttr;
    constantTypesTy constantTypes;

    auto getConstantTypes() const {
      auto &propStorage = this->constantTypes;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setConstantTypes(const ::mlir::ArrayAttr &propValue) {
      this->constantTypes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.constantTypes == this->constantTypes &&
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
  TypesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl.types", odsAttrs.getContext());
  }

  TypesOpGenericAdaptorBase(TypesOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getConstantTypesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().constantTypes);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getConstantTypes();
};

} // namespace detail
template <typename RangeT>
class TypesOpGenericAdaptor : public detail::TypesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TypesOpGenericAdaptorBase;
public:
  TypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TypesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TypesOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TypesOpGenericAdaptor(RangeT values, const TypesOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TypesOp, typename = std::enable_if_t<std::is_same_v<LateInst, TypesOp>>>
  TypesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class TypesOpAdaptor : public TypesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TypesOpGenericAdaptor::TypesOpGenericAdaptor;
  TypesOpAdaptor(TypesOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TypesOp : public ::mlir::Op<TypesOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::RangeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TypesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TypesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("constantTypes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getConstantTypesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getConstantTypesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl.types");
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

  ::mlir::TypedValue<::mlir::pdl::RangeType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::RangeType>>(*getODSResults(0).begin());
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
  ::mlir::ArrayAttr getConstantTypesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().constantTypes);
  }

  ::std::optional< ::mlir::ArrayAttr > getConstantTypes();
  void setConstantTypesAttr(::mlir::ArrayAttr attr) {
    getProperties().constantTypes = attr;
  }

  ::mlir::Attribute removeConstantTypesAttr() {
      auto attr = getProperties().constantTypes;
      getProperties().constantTypes = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::ArrayAttr constantTypes);
  static TypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::ArrayAttr constantTypes);
  static TypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::ArrayAttr constantTypes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr constantTypes);
  static TypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr constantTypes);
  static TypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr constantTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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

} // namespace mlir::pdl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl::TypesOp)


#endif // GET_OP_CLASSES

