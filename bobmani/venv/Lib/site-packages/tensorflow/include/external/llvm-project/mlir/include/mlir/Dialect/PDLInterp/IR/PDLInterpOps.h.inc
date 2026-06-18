/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: PDLInterpOps.td                                                      *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::pdl_interp {

/// Apply a constraint to a set of positional values
/// `pdl_interp.apply_constraint` operations apply a generic constraint, that
///     has been registered with the interpreter, with a given set of positional
///     values.
///     The constraint function may return any number of results.
///     On success, this operation branches to the true destination,
///     otherwise the false destination is taken. This behavior can be reversed
///     by setting the attribute `isNegated` to true.
/// 
///     Example:
/// 
///     ```mlir
///     // Apply `myConstraint` to the entities defined by `input`, `attr`, and
///     // `op`.
///     pdl_interp.apply_constraint "myConstraint"(%input, %attr, %op : !pdl.value, !pdl.attribute, !pdl.operation) -> ^matchDest, ^failureDest
///     ```
class ApplyConstraintOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Invoke and apply an externally registered rewrite method
/// `pdl_interp.apply_rewrite` operations invoke an external rewriter that has
///     been registered with the interpreter to perform the rewrite after a
///     successful match. The rewrite is passed a set of positional arguments. The
///     rewrite function may return any number of results.
/// 
///     Example:
/// 
///     ```mlir
///     // Rewriter operating solely on the root operation.
///     pdl_interp.apply_rewrite "rewriter"(%root : !pdl.operation)
/// 
///     // Rewriter operating solely on the root operation and return an attribute.
///     %attr = pdl_interp.apply_rewrite "rewriter"(%root : !pdl.operation) : !pdl.attribute
/// 
///     // Rewriter operating on the root operation along with additional arguments
///     // from the matcher.
///     pdl_interp.apply_rewrite "rewriter"(%root : !pdl.operation, %value : !pdl.value)
///     ```
class ApplyRewriteOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Check if two positional values or ranges are equivalent
/// `pdl_interp.are_equal` operations compare two positional values for
///     equality. On success, this operation branches to the true destination,
///     otherwise the false destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.are_equal %result1, %result2 : !pdl.value -> ^matchDest, ^failureDest
///     ```
class AreEqualOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// General branch operation
/// `pdl_interp.branch` operations expose general branch functionality to the
///     interpreter, and are generally used to branch from one pattern match
///     sequence to another.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.branch ^dest
///     ```
class BranchOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Check the value of an `Attribute`
/// `pdl_interp.check_attribute` operations compare the value of a given
///     attribute with a constant value. On success, this operation branches to the
///     true destination, otherwise the false destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.check_attribute %attr is 10 -> ^matchDest, ^failureDest
///     ```
class CheckAttributeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Check the number of operands of an `Operation`
/// `pdl_interp.check_operand_count` operations compare the number of operands
///     of a given operation value with a constant. The comparison is either exact
///     or at_least, with the latter used to compare against a minimum number of
///     expected operands. On success, this operation branches to the true
///     destination, otherwise the false destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     // Check for exact equality.
///     pdl_interp.check_operand_count of %op is 2 -> ^matchDest, ^failureDest
/// 
///     // Check for at least N operands.
///     pdl_interp.check_operand_count of %op is at_least 2 -> ^matchDest, ^failureDest
///     ```
class CheckOperandCountOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Check the OperationName of an `Operation`
/// `pdl_interp.check_operation_name` operations compare the name of a given
///     operation with a known name. On success, this operation branches to the true
///     destination, otherwise the false destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.check_operation_name of %op is "foo.op" -> ^matchDest, ^failureDest
///     ```
class CheckOperationNameOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Check the number of results of an `Operation`
/// `pdl_interp.check_result_count` operations compare the number of results
///     of a given operation value with a constant. The comparison is either exact
///     or at_least, with the latter used to compare against a minimum number of
///     expected results. On success, this operation branches to the true
///     destination, otherwise the false destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     // Check for exact equality.
///     pdl_interp.check_result_count of %op is 2 -> ^matchDest, ^failureDest
/// 
///     // Check for at least N results.
///     pdl_interp.check_result_count of %op is at_least 2 -> ^matchDest, ^failureDest
///     ```
class CheckResultCountOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Compare a type to a known value
/// `pdl_interp.check_type` operations compare a type with a statically known
///     type. On success, this operation branches to the true destination, otherwise
///     the false destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.check_type %type is i32 -> ^matchDest, ^failureDest
///     ```
class CheckTypeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Compare a range of types to a range of known values
/// `pdl_interp.check_types` operations compare a range of types with a
///     statically known range of types. On success, this operation branches
///     to the true destination, otherwise the false destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.check_types %type are [i32, i64] -> ^matchDest, ^failureDest
///     ```
class CheckTypesOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Breaks the current iteration
/// `pdl_interp.continue` operation breaks the current iteration within the
///     `pdl_interp.foreach` region and continues with the next iteration from
///     the beginning of the region.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.continue
///     ```
class ContinueOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Create an interpreter handle to a constant `Attribute`
/// `pdl_interp.create_attribute` operations generate a handle within the
///     interpreter for a specific constant attribute value.
/// 
///     Example:
/// 
///     ```mlir
///     %attr = pdl_interp.create_attribute 10 : i64
///     ```
class CreateAttributeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Create an instance of a specific `Operation`
/// `pdl_interp.create_operation` operations create an `Operation` instance with
///     the specified attributes, operands, and result types. See `pdl.operation`
///     for a more detailed description on the general interpretation of the arguments
///     to this operation.
/// 
///     Example:
/// 
///     ```mlir
///     // Create an instance of a `foo.op` operation.
///     %op = pdl_interp.create_operation "foo.op"(%arg0 : !pdl.value) {"attrA" = %attr0} -> (%type : !pdl.type)
/// 
///     // Create an instance of a `foo.op` operation that has inferred result types
///     // (using the InferTypeOpInterface).
///     %op = pdl_interp.create_operation "foo.op"(%arg0 : !pdl.value) {"attrA" = %attr0} -> <inferred>
///     ```
class CreateOperationOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Construct a range of PDL entities
/// `pdl_interp.create_range` operations construct a range from a given set of PDL
///     entities, which all share the same underlying element type. For example, a
///     `!pdl.range<value>` may be constructed from a list of `!pdl.value`
///     or `!pdl.range<value>` entities.
/// 
///     Example:
/// 
///     ```mlir
///     // Construct a range of values.
///     %valueRange = pdl_interp.create_range %inputValue, %inputRange : !pdl.value, !pdl.range<value>
/// 
///     // Construct a range of types.
///     %typeRange = pdl_interp.create_range %inputType, %inputRange : !pdl.type, !pdl.range<type>
/// 
///     // Construct an empty range of types.
///     %valueRange = pdl_interp.create_range : !pdl.range<type>
///     ```
class CreateRangeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Create an interpreter handle to a constant `Type`
/// `pdl_interp.create_type` operations generate a handle within the interpreter
///     for a specific constant type value.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.create_type i64
///     ```
class CreateTypeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Create an interpreter handle to a range of constant `Type`s
/// `pdl_interp.create_types` operations generate a handle within the
///     interpreter for a specific range of constant type values.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.create_types [i64, i64]
///     ```
class CreateTypesOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Mark an operation as `erased`
/// `pdl.erase` operations are used to specify that an operation should be
///     marked as erased. The semantics of this operation correspond with the
///     `eraseOp` method on a `PatternRewriter`.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.erase %root
///     ```
class EraseOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Extract the item at the specified index in a range
/// `pdl_interp.extract` operations are used to extract an item from a range
///     at the specified index. If the index is out of range, returns null.
/// 
///     Example:
/// 
///     ```mlir
///     // Extract the value at index 1 from a range of values.
///     %ops = pdl_interp.extract 1 of %values : !pdl.value
///     ```
class ExtractOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Finalize a pattern match or rewrite sequence
/// `pdl_interp.finalize` is used to denote the termination of a match or
///     rewrite sequence.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.finalize
///     ```
class FinalizeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Iterates over a range of values or ranges
/// `pdl_interp.foreach` iteratively selects an element from a range of values
///     and executes the region until pdl.continue is reached.
/// 
///     In the bytecode interpreter, this operation is implemented by looping over
///     the values and, for each selection, running the bytecode until we reach
///     pdl.continue. This may result in multiple matches being reported. Note
///     that the input range is mutated (popped from).
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.foreach %op : !pdl.operation in %ops {
///       pdl_interp.continue
///     } -> ^next
///     ```
class ForEachOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// PDL Interpreter Function Operation
/// `pdl_interp.func` operations act as interpreter functions. These are
///     callable SSA-region operations that contain other interpreter operations.
///     Interpreter functions are used for both the matching and the rewriting
///     portion of the interpreter.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.func @rewriter(%root: !pdl.operation) {
///       %op = pdl_interp.create_operation "foo.new_operation"
///       pdl_interp.erase %root
///       pdl_interp.finalize
///     }
///     ```
class FuncOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Get a specified attribute value from an `Operation`
/// `pdl_interp.get_attribute` operations try to get a specific attribute from
///     an operation. If the operation does not have that attribute, a null value is
///     returned.
/// 
///     Example:
/// 
///     ```mlir
///     %attr = pdl_interp.get_attribute "attr" of %op
///     ```
class GetAttributeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Get the result type of a specified `Attribute`
/// `pdl_interp.get_attribute_type` operations get the resulting type of a
///     specific attribute.
/// 
///     Example:
/// 
///     ```mlir
///     %type = pdl_interp.get_attribute_type of %attr
///     ```
class GetAttributeTypeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Get the defining operation of a `Value`
/// `pdl_interp.get_defining_op` operations try to get the defining operation
///     of a specific value or range of values. In the case of range, the defining
///     op of the first value is returned. If the value is not an operation result
///     or range of operand results, null is returned.
/// 
///     Example:
/// 
///     ```mlir
///     %op = pdl_interp.get_defining_op of %value : !pdl.value
///     ```
class GetDefiningOpOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Get a specified operand from an `Operation`
/// `pdl_interp.get_operand` operations try to get a specific operand from an
///     operation If the operation does not have an operand for the given index, a
///     null value is returned.
/// 
///     Example:
/// 
///     ```mlir
///     %operand = pdl_interp.get_operand 1 of %op
///     ```
class GetOperandOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Get a specified operand group from an `Operation`
/// `pdl_interp.get_operands` operations try to get a specific operand
///     group from an operation. If the expected result is a single Value, null is
///     returned if the operand group is not of size 1. If a range is expected,
///     null is returned if the operand group is invalid. If no index is provided,
///     the returned operand group corresponds to all operands of the operation.
/// 
///     Example:
/// 
///     ```mlir
///     // Get the first group of operands from an operation, and expect a single
///     // element.
///     %operand = pdl_interp.get_operands 0 of %op : !pdl.value
/// 
///     // Get the first group of operands from an operation.
///     %operands = pdl_interp.get_operands 0 of %op : !pdl.range<value>
/// 
///     // Get all of the operands from an operation.
///     %operands = pdl_interp.get_operands of %op : !pdl.range<value>
///     ```
class GetOperandsOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Get a specified result from an `Operation`
/// `pdl_interp.get_result` operations try to get a specific result from an
///     operation. If the operation does not have a result for the given index, a
///     null value is returned.
/// 
///     Example:
/// 
///     ```mlir
///     %result = pdl_interp.get_result 1 of %op
///     ```
class GetResultOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Get a specified result group from an `Operation`
/// `pdl_interp.get_results` operations try to get a specific result group
///     from an operation. If the expected result is a single Value, null is
///     returned if the result group is not of size 1. If a range is expected,
///     null is returned if the result group is invalid. If no index is provided,
///     the returned operand group corresponds to all results of the operation.
/// 
///     Example:
/// 
///     ```mlir
///     // Get the first group of results from an operation, and expect a single
///     // element.
///     %result = pdl_interp.get_results 0 of %op : !pdl.value
/// 
///     // Get the first group of results from an operation.
///     %results = pdl_interp.get_results 0 of %op : !pdl.range<value>
/// 
///     // Get all of the results from an operation.
///     %results = pdl_interp.get_results of %op : !pdl.range<value>
///     ```
class GetResultsOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Get the users of a `Value`
/// `pdl_interp.get_users` extracts the users that accept this value. In the
///     case of a range, the union of users of the all the values are returned,
///     similarly to ResultRange::getUsers.
/// 
///     Example:
/// 
///     ```mlir
///     // Get all the users of a single value.
///     %ops = pdl_interp.get_users of %value : !pdl.value
/// 
///     // Get all the users of the first value in a range.
///     %ops = pdl_interp.get_users of %values : !pdl.range<value>
///     ```
class GetUsersOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Get the result type of a specified `Value`
/// `pdl_interp.get_value_type` operations get the resulting type of a specific
///     value or range thereof.
/// 
///     Example:
/// 
///     ```mlir
///     // Get the type of a single value.
///     %type = pdl_interp.get_value_type of %value : !pdl.type
/// 
///     // Get the types of a value range.
///     %type = pdl_interp.get_value_type of %values : !pdl.range<type>
///     ```
class GetValueTypeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Check if a positional value is non-null
/// `pdl_interp.is_not_null` operations check that a positional value or range
///     exists. For ranges, this does not mean that the range was simply empty. On
///     success, this operation branches to the true destination. Otherwise, the
///     false destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.is_not_null %value : !pdl.value -> ^matchDest, ^failureDest
///     ```
class IsNotNullOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Record the metadata for a successful pattern match
/// `pdl_interp.record_match` operations record a successful pattern match with
///     the interpreter and branch to the next part of the matcher. The metadata
///     recorded by these operations correspond to a specific `pdl.pattern`, as well
///     as what values were used during that match that should be propagated to the
///     rewriter.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.record_match @rewriters::myRewriter(%root : !pdl.operation) : benefit(1), loc([%root, %op1]), root("foo.op") -> ^nextDest
///     ```
class RecordMatchOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Mark an operation as `replace`d
/// `pdl_interp.replaced` operations are used to specify that an operation
///     should be marked as replaced. The semantics of this operation correspond
///     with the `replaceOp` method on a `PatternRewriter`. The set of replacement
///     values must match the number of results specified by the operation.
/// 
///     Example:
/// 
///     ```mlir
///     // Replace root node with 2 values:
///     pdl_interp.replace %root with (%val0, %val1 : !pdl.type, !pdl.type)
///     ```
class ReplaceOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Switch on the value of an `Attribute`
/// `pdl_interp.switch_attribute` operations compare the value of a given
///     attribute with a set of constant attributes. If the value matches one of the
///     provided case values the destination for that case value is taken, otherwise
///     the default destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.switch_attribute %attr to [10, true](^10Dest, ^trueDest) -> ^defaultDest
///     ```
class SwitchAttributeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Switch on the operand count of an `Operation`
/// `pdl_interp.switch_operand_count` operations compare the operand count of a
///     given operation with a set of potential counts. If the value matches one of
///     the provided case values the destination for that case value is taken,
///     otherwise the default destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.switch_operand_count of %op to [10, 2] -> ^10Dest, ^2Dest, ^defaultDest
///     ```
class SwitchOperandCountOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Switch on the OperationName of an `Operation`
/// `pdl_interp.switch_operation_name` operations compare the name of a given
///     operation with a set of known names. If the value matches one of the
///     provided case values the destination for that case value is taken, otherwise
///     the default destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.switch_operation_name of %op to ["foo.op", "bar.op"](^fooDest, ^barDest) -> ^defaultDest
///     ```
class SwitchOperationNameOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Switch on the result count of an `Operation`
/// `pdl_interp.switch_result_count` operations compare the result count of a
///     given operation with a set of potential counts. If the value matches one of
///     the provided case values the destination for that case value is taken,
///     otherwise the default destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.switch_result_count of %op to [0, 2](^0Dest, ^2Dest) -> ^defaultDest
///     ```
class SwitchResultCountOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Switch on a `Type` value
/// `pdl_interp.switch_type` operations compare a type with a set of statically
///     known types. If the value matches one of the provided case values the
///     destination for that case value is taken, otherwise the default destination
///     is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.switch_type %type to [i32, i64] -> ^i32Dest, ^i64Dest, ^defaultDest
///     ```
class SwitchTypeOp;

} // namespace mlir::pdl_interp
namespace mlir::pdl_interp {

/// Switch on a range of `Type` values
/// `pdl_interp.switch_types` operations compare a range of types with a set of
///     statically known ranges. If the value matches one of the provided case
///     values the destination for that case value is taken, otherwise the default
///     destination is taken.
/// 
///     Example:
/// 
///     ```mlir
///     pdl_interp.switch_types %type is [[i32], [i64, i64]] -> ^i32Dest, ^i64Dest, ^defaultDest
///     ```
class SwitchTypesOp;

} // namespace mlir::pdl_interp
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::ApplyConstraintOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyConstraintOpGenericAdaptorBase {
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
  ApplyConstraintOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.apply_constraint", odsAttrs.getContext());
  }

  ApplyConstraintOpGenericAdaptorBase(ApplyConstraintOp op);

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
class ApplyConstraintOpGenericAdaptor : public detail::ApplyConstraintOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyConstraintOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  ApplyConstraintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyConstraintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyConstraintOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyConstraintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyConstraintOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyConstraintOpGenericAdaptor(RangeT values, const ApplyConstraintOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyConstraintOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyConstraintOp>>>
  ApplyConstraintOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ApplyConstraintOpAdaptor : public ApplyConstraintOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyConstraintOpGenericAdaptor::ApplyConstraintOpGenericAdaptor;
  ApplyConstraintOpAdaptor(ApplyConstraintOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyConstraintOp : public ::mlir::Op<ApplyConstraintOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::NSuccessors<2>::Impl, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyConstraintOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyConstraintOpGenericAdaptor<RangeT>;
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
    return ::llvm::StringLiteral("pdl_interp.apply_constraint");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args, ::mlir::BoolAttr isNegated, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static ApplyConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args, ::mlir::BoolAttr isNegated, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static ApplyConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args, ::mlir::BoolAttr isNegated, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args, bool isNegated, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static ApplyConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args, bool isNegated, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static ApplyConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args, bool isNegated, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyConstraintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyConstraintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::ApplyConstraintOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::ApplyRewriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyRewriteOpGenericAdaptorBase {
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
  ApplyRewriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.apply_rewrite", odsAttrs.getContext());
  }

  ApplyRewriteOpGenericAdaptorBase(ApplyRewriteOp op);

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
class ApplyRewriteOpGenericAdaptor : public detail::ApplyRewriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyRewriteOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  ApplyRewriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyRewriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyRewriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyRewriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyRewriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyRewriteOpGenericAdaptor(RangeT values, const ApplyRewriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyRewriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyRewriteOp>>>
  ApplyRewriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ApplyRewriteOpAdaptor : public ApplyRewriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyRewriteOpGenericAdaptor::ApplyRewriteOpGenericAdaptor;
  ApplyRewriteOpAdaptor(ApplyRewriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyRewriteOp : public ::mlir::Op<ApplyRewriteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyRewriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyRewriteOpGenericAdaptor<RangeT>;
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
    return ::llvm::StringLiteral("pdl_interp.apply_rewrite");
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
  static ApplyRewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args);
  static ApplyRewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr name, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args);
  static ApplyRewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args);
  static ApplyRewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef name, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyRewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyRewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyRewriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyRewriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::ApplyRewriteOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::AreEqualOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AreEqualOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AreEqualOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.are_equal", odsAttrs.getContext());
  }

  AreEqualOpGenericAdaptorBase(AreEqualOp op);

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
class AreEqualOpGenericAdaptor : public detail::AreEqualOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AreEqualOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
public:
  AreEqualOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AreEqualOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AreEqualOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AreEqualOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AreEqualOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AreEqualOpGenericAdaptor(RangeT values, const AreEqualOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AreEqualOp, typename = std::enable_if_t<std::is_same_v<LateInst, AreEqualOp>>>
  AreEqualOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AreEqualOpAdaptor : public AreEqualOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AreEqualOpGenericAdaptor::AreEqualOpGenericAdaptor;
  AreEqualOpAdaptor(AreEqualOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AreEqualOp : public ::mlir::Op<AreEqualOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::NSuccessors<2>::Impl, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameTypeOperands> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AreEqualOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AreEqualOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.are_equal");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::PDLType> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::PDLType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::pdl::PDLType> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::PDLType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static AreEqualOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static AreEqualOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static AreEqualOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static AreEqualOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AreEqualOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AreEqualOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AreEqualOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AreEqualOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::AreEqualOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::BranchOp declarations
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
      odsOpName.emplace("pdl_interp.branch", odsAttrs.getContext());
  }

  BranchOpGenericAdaptorBase(BranchOp op);

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
class BranchOpGenericAdaptor : public detail::BranchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BranchOpGenericAdaptorBase;
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
class BranchOp : public ::mlir::Op<BranchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::OneSuccessor, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BranchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BranchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.branch");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Block *dest);
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Block *dest);
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Block *dest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Block *dest);
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Block *dest);
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Block *dest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::BranchOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CheckAttributeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CheckAttributeOpGenericAdaptorBase {
public:
  struct Properties {
    using constantValueTy = ::mlir::Attribute;
    constantValueTy constantValue;

    auto getConstantValue() const {
      auto &propStorage = this->constantValue;
      return ::llvm::cast<::mlir::Attribute>(propStorage);
    }
    void setConstantValue(const ::mlir::Attribute &propValue) {
      this->constantValue = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.constantValue == this->constantValue &&
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
  CheckAttributeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.check_attribute", odsAttrs.getContext());
  }

  CheckAttributeOpGenericAdaptorBase(CheckAttributeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Attribute getConstantValueAttr() {
    auto attr = ::llvm::cast<::mlir::Attribute>(getProperties().constantValue);
    return attr;
  }

  ::mlir::Attribute getConstantValue();
};

} // namespace detail
template <typename RangeT>
class CheckAttributeOpGenericAdaptor : public detail::CheckAttributeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CheckAttributeOpGenericAdaptorBase;
  static constexpr int odsIndex_attribute = 0;
public:
  CheckAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CheckAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CheckAttributeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CheckAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CheckAttributeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CheckAttributeOpGenericAdaptor(RangeT values, const CheckAttributeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CheckAttributeOp, typename = std::enable_if_t<std::is_same_v<LateInst, CheckAttributeOp>>>
  CheckAttributeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getAttribute() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CheckAttributeOpAdaptor : public CheckAttributeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CheckAttributeOpGenericAdaptor::CheckAttributeOpGenericAdaptor;
  CheckAttributeOpAdaptor(CheckAttributeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CheckAttributeOp : public ::mlir::Op<CheckAttributeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::NSuccessors<2>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CheckAttributeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CheckAttributeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_attribute = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("constantValue")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getConstantValueAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getConstantValueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.check_attribute");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::AttributeType> getAttribute() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::AttributeType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getAttributeMutable() {
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
  ::mlir::Attribute getConstantValueAttr() {
    return ::llvm::cast<::mlir::Attribute>(getProperties().constantValue);
  }

  ::mlir::Attribute getConstantValue();
  void setConstantValueAttr(::mlir::Attribute attr) {
    getProperties().constantValue = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value attribute, ::mlir::Attribute constantValue, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value attribute, ::mlir::Attribute constantValue, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value attribute, ::mlir::Attribute constantValue, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value attribute, ::mlir::Attribute constantValue, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value attribute, ::mlir::Attribute constantValue, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value attribute, ::mlir::Attribute constantValue, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CheckAttributeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CheckOperandCountOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CheckOperandCountOpGenericAdaptorBase {
public:
  struct Properties {
    using compareAtLeastTy = ::mlir::UnitAttr;
    compareAtLeastTy compareAtLeast;

    auto getCompareAtLeast() const {
      auto &propStorage = this->compareAtLeast;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setCompareAtLeast(const ::mlir::UnitAttr &propValue) {
      this->compareAtLeast = propValue;
    }
    using countTy = ::mlir::IntegerAttr;
    countTy count;

    auto getCount() const {
      auto &propStorage = this->count;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setCount(const ::mlir::IntegerAttr &propValue) {
      this->count = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.compareAtLeast == this->compareAtLeast &&
        rhs.count == this->count &&
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
  CheckOperandCountOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.check_operand_count", odsAttrs.getContext());
  }

  CheckOperandCountOpGenericAdaptorBase(CheckOperandCountOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getCountAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().count);
    return attr;
  }

  uint32_t getCount();
  ::mlir::UnitAttr getCompareAtLeastAttr();
  bool getCompareAtLeast();
};

} // namespace detail
template <typename RangeT>
class CheckOperandCountOpGenericAdaptor : public detail::CheckOperandCountOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CheckOperandCountOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  CheckOperandCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CheckOperandCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CheckOperandCountOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CheckOperandCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CheckOperandCountOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CheckOperandCountOpGenericAdaptor(RangeT values, const CheckOperandCountOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CheckOperandCountOp, typename = std::enable_if_t<std::is_same_v<LateInst, CheckOperandCountOp>>>
  CheckOperandCountOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CheckOperandCountOpAdaptor : public CheckOperandCountOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CheckOperandCountOpGenericAdaptor::CheckOperandCountOpGenericAdaptor;
  CheckOperandCountOpAdaptor(CheckOperandCountOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CheckOperandCountOp : public ::mlir::Op<CheckOperandCountOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::NSuccessors<2>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CheckOperandCountOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CheckOperandCountOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("compareAtLeast"), ::llvm::StringRef("count")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCompareAtLeastAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCompareAtLeastAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getCountAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getCountAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.check_operand_count");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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
  ::mlir::IntegerAttr getCountAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().count);
  }

  uint32_t getCount();
  ::mlir::UnitAttr getCompareAtLeastAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().compareAtLeast);
  }

  bool getCompareAtLeast();
  void setCountAttr(::mlir::IntegerAttr attr) {
    getProperties().count = attr;
  }

  void setCount(uint32_t attrValue);
  void setCompareAtLeastAttr(::mlir::UnitAttr attr) {
    getProperties().compareAtLeast = attr;
  }

  void setCompareAtLeast(bool attrValue);
  ::mlir::Attribute removeCompareAtLeastAttr() {
      auto attr = getProperties().compareAtLeast;
      getProperties().compareAtLeast = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CheckOperandCountOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CheckOperationNameOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CheckOperationNameOpGenericAdaptorBase {
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
  CheckOperationNameOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.check_operation_name", odsAttrs.getContext());
  }

  CheckOperationNameOpGenericAdaptorBase(CheckOperationNameOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

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
class CheckOperationNameOpGenericAdaptor : public detail::CheckOperationNameOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CheckOperationNameOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  CheckOperationNameOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CheckOperationNameOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CheckOperationNameOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CheckOperationNameOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CheckOperationNameOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CheckOperationNameOpGenericAdaptor(RangeT values, const CheckOperationNameOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CheckOperationNameOp, typename = std::enable_if_t<std::is_same_v<LateInst, CheckOperationNameOp>>>
  CheckOperationNameOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CheckOperationNameOpAdaptor : public CheckOperationNameOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CheckOperationNameOpGenericAdaptor::CheckOperationNameOpGenericAdaptor;
  CheckOperationNameOpAdaptor(CheckOperationNameOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CheckOperationNameOp : public ::mlir::Op<CheckOperationNameOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::NSuccessors<2>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CheckOperationNameOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CheckOperationNameOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
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
    return ::llvm::StringLiteral("pdl_interp.check_operation_name");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp, ::mlir::StringAttr name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp, ::mlir::StringAttr name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp, ::mlir::StringAttr name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::StringAttr name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::StringAttr name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::StringAttr name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp, ::llvm::StringRef name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp, ::llvm::StringRef name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp, ::llvm::StringRef name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::llvm::StringRef name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::llvm::StringRef name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::llvm::StringRef name, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CheckOperationNameOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CheckResultCountOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CheckResultCountOpGenericAdaptorBase {
public:
  struct Properties {
    using compareAtLeastTy = ::mlir::UnitAttr;
    compareAtLeastTy compareAtLeast;

    auto getCompareAtLeast() const {
      auto &propStorage = this->compareAtLeast;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setCompareAtLeast(const ::mlir::UnitAttr &propValue) {
      this->compareAtLeast = propValue;
    }
    using countTy = ::mlir::IntegerAttr;
    countTy count;

    auto getCount() const {
      auto &propStorage = this->count;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setCount(const ::mlir::IntegerAttr &propValue) {
      this->count = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.compareAtLeast == this->compareAtLeast &&
        rhs.count == this->count &&
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
  CheckResultCountOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.check_result_count", odsAttrs.getContext());
  }

  CheckResultCountOpGenericAdaptorBase(CheckResultCountOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getCountAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().count);
    return attr;
  }

  uint32_t getCount();
  ::mlir::UnitAttr getCompareAtLeastAttr();
  bool getCompareAtLeast();
};

} // namespace detail
template <typename RangeT>
class CheckResultCountOpGenericAdaptor : public detail::CheckResultCountOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CheckResultCountOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  CheckResultCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CheckResultCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CheckResultCountOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CheckResultCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CheckResultCountOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CheckResultCountOpGenericAdaptor(RangeT values, const CheckResultCountOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CheckResultCountOp, typename = std::enable_if_t<std::is_same_v<LateInst, CheckResultCountOp>>>
  CheckResultCountOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CheckResultCountOpAdaptor : public CheckResultCountOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CheckResultCountOpGenericAdaptor::CheckResultCountOpGenericAdaptor;
  CheckResultCountOpAdaptor(CheckResultCountOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CheckResultCountOp : public ::mlir::Op<CheckResultCountOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::NSuccessors<2>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CheckResultCountOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CheckResultCountOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("compareAtLeast"), ::llvm::StringRef("count")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCompareAtLeastAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCompareAtLeastAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getCountAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getCountAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.check_result_count");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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
  ::mlir::IntegerAttr getCountAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().count);
  }

  uint32_t getCount();
  ::mlir::UnitAttr getCompareAtLeastAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().compareAtLeast);
  }

  bool getCompareAtLeast();
  void setCountAttr(::mlir::IntegerAttr attr) {
    getProperties().count = attr;
  }

  void setCount(uint32_t attrValue);
  void setCompareAtLeastAttr(::mlir::UnitAttr attr) {
    getProperties().compareAtLeast = attr;
  }

  void setCompareAtLeast(bool attrValue);
  ::mlir::Attribute removeCompareAtLeastAttr() {
      auto attr = getProperties().compareAtLeast;
      getProperties().compareAtLeast = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr count, /*optional*/::mlir::UnitAttr compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t count, /*optional*/bool compareAtLeast, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CheckResultCountOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CheckTypeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CheckTypeOpGenericAdaptorBase {
public:
  struct Properties {
    using typeTy = ::mlir::TypeAttr;
    typeTy type;

    auto getType() const {
      auto &propStorage = this->type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setType(const ::mlir::TypeAttr &propValue) {
      this->type = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.type == this->type &&
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
  CheckTypeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.check_type", odsAttrs.getContext());
  }

  CheckTypeOpGenericAdaptorBase(CheckTypeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
    return attr;
  }

  ::mlir::Type getType();
};

} // namespace detail
template <typename RangeT>
class CheckTypeOpGenericAdaptor : public detail::CheckTypeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CheckTypeOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  CheckTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CheckTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CheckTypeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CheckTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CheckTypeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CheckTypeOpGenericAdaptor(RangeT values, const CheckTypeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CheckTypeOp, typename = std::enable_if_t<std::is_same_v<LateInst, CheckTypeOp>>>
  CheckTypeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CheckTypeOpAdaptor : public CheckTypeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CheckTypeOpGenericAdaptor::CheckTypeOpGenericAdaptor;
  CheckTypeOpAdaptor(CheckTypeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CheckTypeOp : public ::mlir::Op<CheckTypeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::NSuccessors<2>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CheckTypeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CheckTypeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("type")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.check_type");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::TypeType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::TypeType>>(*getODSOperands(0).begin());
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
  ::mlir::TypeAttr getTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
  }

  ::mlir::Type getType();
  void setTypeAttr(::mlir::TypeAttr attr) {
    getProperties().type = attr;
  }

  void setType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::TypeAttr type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::TypeAttr type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::TypeAttr type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::TypeAttr type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::TypeAttr type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::TypeAttr type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Type type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Type type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Type type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Type type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Type type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Type type, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CheckTypeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CheckTypesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CheckTypesOpGenericAdaptorBase {
public:
  struct Properties {
    using typesTy = ::mlir::ArrayAttr;
    typesTy types;

    auto getTypes() const {
      auto &propStorage = this->types;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setTypes(const ::mlir::ArrayAttr &propValue) {
      this->types = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.types == this->types &&
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
  CheckTypesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.check_types", odsAttrs.getContext());
  }

  CheckTypesOpGenericAdaptorBase(CheckTypesOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getTypesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().types);
    return attr;
  }

  ::mlir::ArrayAttr getTypes();
};

} // namespace detail
template <typename RangeT>
class CheckTypesOpGenericAdaptor : public detail::CheckTypesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CheckTypesOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  CheckTypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CheckTypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CheckTypesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CheckTypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CheckTypesOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CheckTypesOpGenericAdaptor(RangeT values, const CheckTypesOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CheckTypesOp, typename = std::enable_if_t<std::is_same_v<LateInst, CheckTypesOp>>>
  CheckTypesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CheckTypesOpAdaptor : public CheckTypesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CheckTypesOpGenericAdaptor::CheckTypesOpGenericAdaptor;
  CheckTypesOpAdaptor(CheckTypesOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CheckTypesOp : public ::mlir::Op<CheckTypesOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::NSuccessors<2>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CheckTypesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CheckTypesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("types")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTypesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTypesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.check_types");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::RangeType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::RangeType>>(*getODSOperands(0).begin());
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
  ::mlir::ArrayAttr getTypesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().types);
  }

  ::mlir::ArrayAttr getTypes();
  void setTypesAttr(::mlir::ArrayAttr attr) {
    getProperties().types = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::ArrayAttr types, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::ArrayAttr types, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::ArrayAttr types, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr types, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr types, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static CheckTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr types, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CheckTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CheckTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CheckTypesOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::ContinueOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ContinueOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ContinueOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.continue", odsAttrs.getContext());
  }

  ContinueOpGenericAdaptorBase(ContinueOp op);

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
class ContinueOpGenericAdaptor : public detail::ContinueOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ContinueOpGenericAdaptorBase;
public:
  ContinueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ContinueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ContinueOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ContinueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ContinueOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ContinueOpGenericAdaptor(RangeT values, const ContinueOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ContinueOp, typename = std::enable_if_t<std::is_same_v<LateInst, ContinueOp>>>
  ContinueOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ContinueOpAdaptor : public ContinueOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ContinueOpGenericAdaptor::ContinueOpGenericAdaptor;
  ContinueOpAdaptor(ContinueOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ContinueOp : public ::mlir::Op<ContinueOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ForEachOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ContinueOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ContinueOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.continue");
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
  static ContinueOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static ContinueOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static ContinueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static ContinueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ContinueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ContinueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ContinueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ContinueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::ContinueOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CreateAttributeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateAttributeOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::mlir::Attribute;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::Attribute>(propStorage);
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
  CreateAttributeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.create_attribute", odsAttrs.getContext());
  }

  CreateAttributeOpGenericAdaptorBase(CreateAttributeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Attribute getValueAttr() {
    auto attr = ::llvm::cast<::mlir::Attribute>(getProperties().value);
    return attr;
  }

  ::mlir::Attribute getValue();
};

} // namespace detail
template <typename RangeT>
class CreateAttributeOpGenericAdaptor : public detail::CreateAttributeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateAttributeOpGenericAdaptorBase;
public:
  CreateAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateAttributeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CreateAttributeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateAttributeOpGenericAdaptor(RangeT values, const CreateAttributeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateAttributeOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateAttributeOp>>>
  CreateAttributeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CreateAttributeOpAdaptor : public CreateAttributeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateAttributeOpGenericAdaptor::CreateAttributeOpGenericAdaptor;
  CreateAttributeOpAdaptor(CreateAttributeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateAttributeOp : public ::mlir::Op<CreateAttributeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::AttributeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateAttributeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateAttributeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
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
    return ::llvm::StringLiteral("pdl_interp.create_attribute");
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

  ::mlir::TypedValue<::mlir::pdl::AttributeType> getAttribute() {
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
    return ::llvm::cast<::mlir::Attribute>(getProperties().value);
  }

  ::mlir::Attribute getValue();
  void setValueAttr(::mlir::Attribute attr) {
    getProperties().value = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Attribute value);
  static CreateAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Attribute value);
  static CreateAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, Attribute value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type attribute, ::mlir::Attribute value);
  static CreateAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type attribute, ::mlir::Attribute value);
  static CreateAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type attribute, ::mlir::Attribute value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static CreateAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static CreateAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CreateAttributeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CreateOperationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateOperationOpGenericAdaptorBase {
public:
  struct Properties {
    using inferredResultTypesTy = ::mlir::UnitAttr;
    inferredResultTypesTy inferredResultTypes;

    auto getInferredResultTypes() const {
      auto &propStorage = this->inferredResultTypes;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setInferredResultTypes(const ::mlir::UnitAttr &propValue) {
      this->inferredResultTypes = propValue;
    }
    using inputAttributeNamesTy = ::mlir::ArrayAttr;
    inputAttributeNamesTy inputAttributeNames;

    auto getInputAttributeNames() const {
      auto &propStorage = this->inputAttributeNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setInputAttributeNames(const ::mlir::ArrayAttr &propValue) {
      this->inputAttributeNames = propValue;
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
        rhs.inferredResultTypes == this->inferredResultTypes &&
        rhs.inputAttributeNames == this->inputAttributeNames &&
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
  CreateOperationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.create_operation", odsAttrs.getContext());
  }

  CreateOperationOpGenericAdaptorBase(CreateOperationOp op);

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
  ::mlir::ArrayAttr getInputAttributeNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().inputAttributeNames);
    return attr;
  }

  ::mlir::ArrayAttr getInputAttributeNames();
  ::mlir::UnitAttr getInferredResultTypesAttr();
  bool getInferredResultTypes();
};

} // namespace detail
template <typename RangeT>
class CreateOperationOpGenericAdaptor : public detail::CreateOperationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateOperationOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOperands = 0;
  static constexpr int odsIndex_inputAttributes = 1;
  static constexpr int odsIndex_inputResultTypes = 2;
public:
  CreateOperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateOperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateOperationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateOperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : CreateOperationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateOperationOpGenericAdaptor(RangeT values, const CreateOperationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateOperationOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateOperationOp>>>
  CreateOperationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputOperands() {
    return getODSOperands(0);
  }

  RangeT getInputAttributes() {
    return getODSOperands(1);
  }

  RangeT getInputResultTypes() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CreateOperationOpAdaptor : public CreateOperationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateOperationOpGenericAdaptor::CreateOperationOpGenericAdaptor;
  CreateOperationOpAdaptor(CreateOperationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateOperationOp : public ::mlir::Op<CreateOperationOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::OperationType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateOperationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateOperationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOperands = 0;
  static constexpr int odsIndex_inputAttributes = 1;
  static constexpr int odsIndex_inputResultTypes = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inferredResultTypes"), ::llvm::StringRef("inputAttributeNames"), ::llvm::StringRef("name"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInferredResultTypesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInferredResultTypesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInputAttributeNamesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInputAttributeNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.create_operation");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputOperands() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getInputAttributes() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getInputResultTypes() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getInputOperandsMutable();
  ::mlir::MutableOperandRange getInputAttributesMutable();
  ::mlir::MutableOperandRange getInputResultTypesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getResultOp() {
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  ::mlir::ArrayAttr getInputAttributeNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().inputAttributeNames);
  }

  ::mlir::ArrayAttr getInputAttributeNames();
  ::mlir::UnitAttr getInferredResultTypesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().inferredResultTypes);
  }

  bool getInferredResultTypes();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setInputAttributeNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().inputAttributeNames = attr;
  }

  void setInferredResultTypesAttr(::mlir::UnitAttr attr) {
    getProperties().inferredResultTypes = attr;
  }

  void setInferredResultTypes(bool attrValue);
  ::mlir::Attribute removeInferredResultTypesAttr() {
      auto attr = getProperties().inferredResultTypes;
      getProperties().inferredResultTypes = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name, ValueRange types, bool inferredResultTypes, ValueRange operands, ValueRange attributes, ArrayAttr attributeNames);
  static CreateOperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, ValueRange types, bool inferredResultTypes, ValueRange operands, ValueRange attributes, ArrayAttr attributeNames);
  static CreateOperationOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, ValueRange types, bool inferredResultTypes, ValueRange operands, ValueRange attributes, ArrayAttr attributeNames);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultOp, ::mlir::StringAttr name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/::mlir::UnitAttr inferredResultTypes = nullptr);
  static CreateOperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultOp, ::mlir::StringAttr name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/::mlir::UnitAttr inferredResultTypes = nullptr);
  static CreateOperationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultOp, ::mlir::StringAttr name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/::mlir::UnitAttr inferredResultTypes = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/::mlir::UnitAttr inferredResultTypes = nullptr);
  static CreateOperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/::mlir::UnitAttr inferredResultTypes = nullptr);
  static CreateOperationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/::mlir::UnitAttr inferredResultTypes = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultOp, ::llvm::StringRef name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/bool inferredResultTypes = false);
  static CreateOperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultOp, ::llvm::StringRef name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/bool inferredResultTypes = false);
  static CreateOperationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultOp, ::llvm::StringRef name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/bool inferredResultTypes = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/bool inferredResultTypes = false);
  static CreateOperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/bool inferredResultTypes = false);
  static CreateOperationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::ValueRange inputOperands, ::mlir::ValueRange inputAttributes, ::mlir::ArrayAttr inputAttributeNames, ::mlir::ValueRange inputResultTypes, /*optional*/bool inferredResultTypes = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateOperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateOperationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateOperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateOperationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CreateOperationOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CreateRangeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateRangeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CreateRangeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.create_range", odsAttrs.getContext());
  }

  CreateRangeOpGenericAdaptorBase(CreateRangeOp op);

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
class CreateRangeOpGenericAdaptor : public detail::CreateRangeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateRangeOpGenericAdaptorBase;
  static constexpr int odsIndex_arguments = 0;
public:
  CreateRangeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateRangeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateRangeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateRangeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CreateRangeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateRangeOpGenericAdaptor(RangeT values, const CreateRangeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateRangeOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateRangeOp>>>
  CreateRangeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CreateRangeOpAdaptor : public CreateRangeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateRangeOpGenericAdaptor::CreateRangeOpGenericAdaptor;
  CreateRangeOpAdaptor(CreateRangeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateRangeOp : public ::mlir::Op<CreateRangeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::RangeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateRangeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateRangeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_arguments = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.create_range");
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
  static CreateRangeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange arguments);
  static CreateRangeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange arguments);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateRangeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateRangeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateRangeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateRangeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CreateRangeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CreateTypeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateTypeOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::mlir::TypeAttr;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setValue(const ::mlir::TypeAttr &propValue) {
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
  CreateTypeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.create_type", odsAttrs.getContext());
  }

  CreateTypeOpGenericAdaptorBase(CreateTypeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getValueAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().value);
    return attr;
  }

  ::mlir::Type getValue();
};

} // namespace detail
template <typename RangeT>
class CreateTypeOpGenericAdaptor : public detail::CreateTypeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateTypeOpGenericAdaptorBase;
public:
  CreateTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateTypeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CreateTypeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateTypeOpGenericAdaptor(RangeT values, const CreateTypeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateTypeOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateTypeOp>>>
  CreateTypeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CreateTypeOpAdaptor : public CreateTypeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateTypeOpGenericAdaptor::CreateTypeOpGenericAdaptor;
  CreateTypeOpAdaptor(CreateTypeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateTypeOp : public ::mlir::Op<CreateTypeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::TypeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateTypeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateTypeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
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
    return ::llvm::StringLiteral("pdl_interp.create_type");
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
  ::mlir::TypeAttr getValueAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().value);
  }

  ::mlir::Type getValue();
  void setValueAttr(::mlir::TypeAttr attr) {
    getProperties().value = attr;
  }

  void setValue(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeAttr type);
  static CreateTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeAttr type);
  static CreateTypeOp create(::mlir::ImplicitLocOpBuilder &builder, TypeAttr type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::TypeAttr value);
  static CreateTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::TypeAttr value);
  static CreateTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::TypeAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr value);
  static CreateTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr value);
  static CreateTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Type value);
  static CreateTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Type value);
  static CreateTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Type value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Type value);
  static CreateTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Type value);
  static CreateTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Type value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CreateTypeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::CreateTypesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateTypesOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::mlir::ArrayAttr;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setValue(const ::mlir::ArrayAttr &propValue) {
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
  CreateTypesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.create_types", odsAttrs.getContext());
  }

  CreateTypesOpGenericAdaptorBase(CreateTypesOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getValueAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().value);
    return attr;
  }

  ::mlir::ArrayAttr getValue();
};

} // namespace detail
template <typename RangeT>
class CreateTypesOpGenericAdaptor : public detail::CreateTypesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateTypesOpGenericAdaptorBase;
public:
  CreateTypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateTypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateTypesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateTypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CreateTypesOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateTypesOpGenericAdaptor(RangeT values, const CreateTypesOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateTypesOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateTypesOp>>>
  CreateTypesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CreateTypesOpAdaptor : public CreateTypesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateTypesOpGenericAdaptor::CreateTypesOpGenericAdaptor;
  CreateTypesOpAdaptor(CreateTypesOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateTypesOp : public ::mlir::Op<CreateTypesOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::RangeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateTypesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateTypesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
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
    return ::llvm::StringLiteral("pdl_interp.create_types");
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
  ::mlir::ArrayAttr getValueAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().value);
  }

  ::mlir::ArrayAttr getValue();
  void setValueAttr(::mlir::ArrayAttr attr) {
    getProperties().value = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayAttr type);
  static CreateTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayAttr type);
  static CreateTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayAttr type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ArrayAttr value);
  static CreateTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ArrayAttr value);
  static CreateTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ArrayAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr value);
  static CreateTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr value);
  static CreateTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::CreateTypesOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::EraseOp declarations
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
      odsOpName.emplace("pdl_interp.erase", odsAttrs.getContext());
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
  static constexpr int odsIndex_inputOp = 0;
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

  ValueT getInputOp() {
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
class EraseOp : public ::mlir::Op<EraseOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EraseOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EraseOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.erase");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp);
  static EraseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp);
  static EraseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp);
  static EraseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp);
  static EraseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp);
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::EraseOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::ExtractOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtractOpGenericAdaptorBase {
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
  ExtractOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.extract", odsAttrs.getContext());
  }

  ExtractOpGenericAdaptorBase(ExtractOp op);

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
class ExtractOpGenericAdaptor : public detail::ExtractOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtractOpGenericAdaptorBase;
  static constexpr int odsIndex_range = 0;
public:
  ExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExtractOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExtractOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExtractOpGenericAdaptor(RangeT values, const ExtractOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExtractOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExtractOp>>>
  ExtractOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRange() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ExtractOpAdaptor : public ExtractOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExtractOpGenericAdaptor::ExtractOpGenericAdaptor;
  ExtractOpAdaptor(ExtractOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExtractOp : public ::mlir::Op<ExtractOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::PDLType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtractOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtractOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_range = 0;
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
    return ::llvm::StringLiteral("pdl_interp.extract");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::RangeType> getRange() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::RangeType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getRangeMutable() {
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

  ::mlir::TypedValue<::mlir::pdl::PDLType> getResult() {
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
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().index);
  }

  uint32_t getIndex();
  void setIndexAttr(::mlir::IntegerAttr attr) {
    getProperties().index = attr;
  }

  void setIndex(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value range, unsigned index);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value range, unsigned index);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value range, unsigned index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value range, ::mlir::IntegerAttr index);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value range, ::mlir::IntegerAttr index);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value range, ::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value range, ::mlir::IntegerAttr index);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value range, ::mlir::IntegerAttr index);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value range, ::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value range, uint32_t index);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value range, uint32_t index);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value range, uint32_t index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value range, uint32_t index);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value range, uint32_t index);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value range, uint32_t index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::ExtractOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::FinalizeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FinalizeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FinalizeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.finalize", odsAttrs.getContext());
  }

  FinalizeOpGenericAdaptorBase(FinalizeOp op);

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
class FinalizeOpGenericAdaptor : public detail::FinalizeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FinalizeOpGenericAdaptorBase;
public:
  FinalizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FinalizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : FinalizeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FinalizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FinalizeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FinalizeOpGenericAdaptor(RangeT values, const FinalizeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FinalizeOp, typename = std::enable_if_t<std::is_same_v<LateInst, FinalizeOp>>>
  FinalizeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FinalizeOpAdaptor : public FinalizeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FinalizeOpGenericAdaptor::FinalizeOpGenericAdaptor;
  FinalizeOpAdaptor(FinalizeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FinalizeOp : public ::mlir::Op<FinalizeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FinalizeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FinalizeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.finalize");
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
  static FinalizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static FinalizeOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static FinalizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static FinalizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FinalizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FinalizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FinalizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FinalizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::FinalizeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::ForEachOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ForEachOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ForEachOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.foreach", odsAttrs.getContext());
  }

  ForEachOpGenericAdaptorBase(ForEachOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ForEachOpGenericAdaptor : public detail::ForEachOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ForEachOpGenericAdaptorBase;
  static constexpr int odsIndex_values = 0;
public:
  ForEachOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ForEachOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ForEachOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ForEachOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ForEachOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ForEachOpGenericAdaptor(RangeT values, const ForEachOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ForEachOp, typename = std::enable_if_t<std::is_same_v<LateInst, ForEachOp>>>
  ForEachOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValues() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ForEachOpAdaptor : public ForEachOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ForEachOpGenericAdaptor::ForEachOpGenericAdaptor;
  ForEachOpAdaptor(ForEachOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ForEachOp : public ::mlir::Op<ForEachOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::OneSuccessor, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ForEachOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ForEachOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_values = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.foreach");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::RangeType> getValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::RangeType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getValuesMutable() {
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

  ::mlir::Region &getRegion() {
    return (*this)->getRegion(0);
  }

  ::mlir::Block *getSuccessor() {
    return (*this)->getSuccessor(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value range, Block *successor, bool initLoop);
  static ForEachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value range, Block *successor, bool initLoop);
  static ForEachOp create(::mlir::ImplicitLocOpBuilder &builder, Value range, Block *successor, bool initLoop);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value values, ::mlir::Block *successor);
  static ForEachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value values, ::mlir::Block *successor);
  static ForEachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value values, ::mlir::Block *successor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value values, ::mlir::Block *successor);
  static ForEachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value values, ::mlir::Block *successor);
  static ForEachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value values, ::mlir::Block *successor);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ForEachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ForEachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ForEachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ForEachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
  /// Returns the loop variable.
  BlockArgument getLoopVariable() { return getRegion().getArgument(0); }
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::ForEachOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::FuncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FuncOpGenericAdaptorBase {
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
    bool operator==(const Properties &rhs) const {
      return 
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.res_attrs == this->res_attrs &&
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
  FuncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.func", odsAttrs.getContext());
  }

  FuncOpGenericAdaptorBase(FuncOp op);

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
  ::mlir::ArrayAttr getResAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class FuncOpGenericAdaptor : public detail::FuncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FuncOpGenericAdaptorBase;
public:
  FuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : FuncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FuncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FuncOpGenericAdaptor(RangeT values, const FuncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FuncOp, typename = std::enable_if_t<std::is_same_v<LateInst, FuncOp>>>
  FuncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FuncOpAdaptor : public FuncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FuncOpGenericAdaptor::FuncOpGenericAdaptor;
  FuncOpAdaptor(FuncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FuncOp : public ::mlir::Op<FuncOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FuncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FuncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("sym_name")};
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

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.func");
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
  ::mlir::ArrayAttr getResAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
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

  void setResAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().res_attrs = attr;
  }

  ::mlir::Attribute removeArgAttrsAttr() {
      auto attr = getProperties().arg_attrs;
      getProperties().arg_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeResAttrsAttr() {
      auto attr = getProperties().res_attrs;
      getProperties().res_attrs = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name, FunctionType type, ArrayRef<NamedAttribute> attrs = {});
  static FuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, FunctionType type, ArrayRef<NamedAttribute> attrs = {});
  static FuncOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, FunctionType type, ArrayRef<NamedAttribute> attrs = {});
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
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  //===------------------------------------------------------------------===//
  // FunctionOpInterface Methods
  //===------------------------------------------------------------------===//

  /// Returns the argument types of this function.
  ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

  /// Returns the result types of this function.
  ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

  Region *getCallableRegion() { return &getBody(); }
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::FuncOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::GetAttributeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetAttributeOpGenericAdaptorBase {
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
  GetAttributeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.get_attribute", odsAttrs.getContext());
  }

  GetAttributeOpGenericAdaptorBase(GetAttributeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

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
class GetAttributeOpGenericAdaptor : public detail::GetAttributeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetAttributeOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  GetAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetAttributeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetAttributeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetAttributeOpGenericAdaptor(RangeT values, const GetAttributeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetAttributeOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetAttributeOp>>>
  GetAttributeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetAttributeOpAdaptor : public GetAttributeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetAttributeOpGenericAdaptor::GetAttributeOpGenericAdaptor;
  GetAttributeOpAdaptor(GetAttributeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetAttributeOp : public ::mlir::Op<GetAttributeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::AttributeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetAttributeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetAttributeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
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
    return ::llvm::StringLiteral("pdl_interp.get_attribute");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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

  ::mlir::TypedValue<::mlir::pdl::AttributeType> getAttribute() {
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type attribute, ::mlir::Value inputOp, ::mlir::StringAttr name);
  static GetAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type attribute, ::mlir::Value inputOp, ::mlir::StringAttr name);
  static GetAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type attribute, ::mlir::Value inputOp, ::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::StringAttr name);
  static GetAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::StringAttr name);
  static GetAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type attribute, ::mlir::Value inputOp, ::llvm::StringRef name);
  static GetAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type attribute, ::mlir::Value inputOp, ::llvm::StringRef name);
  static GetAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type attribute, ::mlir::Value inputOp, ::llvm::StringRef name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::llvm::StringRef name);
  static GetAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::llvm::StringRef name);
  static GetAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::llvm::StringRef name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::GetAttributeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::GetAttributeTypeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetAttributeTypeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GetAttributeTypeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.get_attribute_type", odsAttrs.getContext());
  }

  GetAttributeTypeOpGenericAdaptorBase(GetAttributeTypeOp op);

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
class GetAttributeTypeOpGenericAdaptor : public detail::GetAttributeTypeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetAttributeTypeOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  GetAttributeTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetAttributeTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetAttributeTypeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetAttributeTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetAttributeTypeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetAttributeTypeOpGenericAdaptor(RangeT values, const GetAttributeTypeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetAttributeTypeOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetAttributeTypeOp>>>
  GetAttributeTypeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GetAttributeTypeOpAdaptor : public GetAttributeTypeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetAttributeTypeOpGenericAdaptor::GetAttributeTypeOpGenericAdaptor;
  GetAttributeTypeOpAdaptor(GetAttributeTypeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetAttributeTypeOp : public ::mlir::Op<GetAttributeTypeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::TypeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetAttributeTypeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetAttributeTypeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.get_attribute_type");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::AttributeType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::AttributeType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value);
  static GetAttributeTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value);
  static GetAttributeTypeOp create(::mlir::ImplicitLocOpBuilder &builder, Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value);
  static GetAttributeTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value);
  static GetAttributeTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static GetAttributeTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static GetAttributeTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetAttributeTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetAttributeTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetAttributeTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetAttributeTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::GetAttributeTypeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::GetDefiningOpOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetDefiningOpOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GetDefiningOpOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.get_defining_op", odsAttrs.getContext());
  }

  GetDefiningOpOpGenericAdaptorBase(GetDefiningOpOp op);

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
class GetDefiningOpOpGenericAdaptor : public detail::GetDefiningOpOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetDefiningOpOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  GetDefiningOpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetDefiningOpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetDefiningOpOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetDefiningOpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetDefiningOpOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetDefiningOpOpGenericAdaptor(RangeT values, const GetDefiningOpOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetDefiningOpOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetDefiningOpOp>>>
  GetDefiningOpOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GetDefiningOpOpAdaptor : public GetDefiningOpOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetDefiningOpOpGenericAdaptor::GetDefiningOpOpGenericAdaptor;
  GetDefiningOpOpAdaptor(GetDefiningOpOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetDefiningOpOp : public ::mlir::Op<GetDefiningOpOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::OperationType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetDefiningOpOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetDefiningOpOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.get_defining_op");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::PDLType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::PDLType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type inputOp, ::mlir::Value value);
  static GetDefiningOpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type inputOp, ::mlir::Value value);
  static GetDefiningOpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type inputOp, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static GetDefiningOpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static GetDefiningOpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetDefiningOpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetDefiningOpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetDefiningOpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetDefiningOpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::GetDefiningOpOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::GetOperandOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetOperandOpGenericAdaptorBase {
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
  GetOperandOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.get_operand", odsAttrs.getContext());
  }

  GetOperandOpGenericAdaptorBase(GetOperandOp op);

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
class GetOperandOpGenericAdaptor : public detail::GetOperandOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetOperandOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  GetOperandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetOperandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetOperandOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetOperandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetOperandOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetOperandOpGenericAdaptor(RangeT values, const GetOperandOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetOperandOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetOperandOp>>>
  GetOperandOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetOperandOpAdaptor : public GetOperandOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetOperandOpGenericAdaptor::GetOperandOpGenericAdaptor;
  GetOperandOpAdaptor(GetOperandOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetOperandOp : public ::mlir::Op<GetOperandOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::ValueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetOperandOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetOperandOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
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
    return ::llvm::StringLiteral("pdl_interp.get_operand");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value inputOp, uint32_t index);
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value inputOp, uint32_t index);
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value inputOp, uint32_t index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t index);
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t index);
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::GetOperandOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::GetOperandsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetOperandsOpGenericAdaptorBase {
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
  GetOperandsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.get_operands", odsAttrs.getContext());
  }

  GetOperandsOpGenericAdaptorBase(GetOperandsOp op);

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
class GetOperandsOpGenericAdaptor : public detail::GetOperandsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetOperandsOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  GetOperandsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetOperandsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetOperandsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetOperandsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetOperandsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetOperandsOpGenericAdaptor(RangeT values, const GetOperandsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetOperandsOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetOperandsOp>>>
  GetOperandsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetOperandsOpAdaptor : public GetOperandsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetOperandsOpGenericAdaptor::GetOperandsOpGenericAdaptor;
  GetOperandsOpAdaptor(GetOperandsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetOperandsOp : public ::mlir::Op<GetOperandsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::PDLType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetOperandsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetOperandsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
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
    return ::llvm::StringLiteral("pdl_interp.get_operands");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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

  ::mlir::TypedValue<::mlir::pdl::PDLType> getValue() {
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value inputOp, std::optional<unsigned> index);
  static GetOperandsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value inputOp, std::optional<unsigned> index);
  static GetOperandsOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value inputOp, std::optional<unsigned> index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static GetOperandsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static GetOperandsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static GetOperandsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static GetOperandsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetOperandsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetOperandsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetOperandsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetOperandsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::GetOperandsOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::GetResultOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetResultOpGenericAdaptorBase {
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
  GetResultOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.get_result", odsAttrs.getContext());
  }

  GetResultOpGenericAdaptorBase(GetResultOp op);

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
class GetResultOpGenericAdaptor : public detail::GetResultOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetResultOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  GetResultOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetResultOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetResultOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetResultOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetResultOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetResultOpGenericAdaptor(RangeT values, const GetResultOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetResultOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetResultOp>>>
  GetResultOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetResultOpAdaptor : public GetResultOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetResultOpGenericAdaptor::GetResultOpGenericAdaptor;
  GetResultOpAdaptor(GetResultOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetResultOp : public ::mlir::Op<GetResultOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::ValueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetResultOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetResultOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
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
    return ::llvm::StringLiteral("pdl_interp.get_result");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value inputOp, uint32_t index);
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value inputOp, uint32_t index);
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value inputOp, uint32_t index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t index);
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t index);
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, uint32_t index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::GetResultOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::GetResultsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetResultsOpGenericAdaptorBase {
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
  GetResultsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.get_results", odsAttrs.getContext());
  }

  GetResultsOpGenericAdaptorBase(GetResultsOp op);

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
class GetResultsOpGenericAdaptor : public detail::GetResultsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetResultsOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  GetResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetResultsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetResultsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetResultsOpGenericAdaptor(RangeT values, const GetResultsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetResultsOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetResultsOp>>>
  GetResultsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetResultsOpAdaptor : public GetResultsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetResultsOpGenericAdaptor::GetResultsOpGenericAdaptor;
  GetResultsOpAdaptor(GetResultsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetResultsOp : public ::mlir::Op<GetResultsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::PDLType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetResultsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetResultsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
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
    return ::llvm::StringLiteral("pdl_interp.get_results");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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

  ::mlir::TypedValue<::mlir::pdl::PDLType> getValue() {
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value inputOp, std::optional<unsigned> index);
  static GetResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value inputOp, std::optional<unsigned> index);
  static GetResultsOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value inputOp, std::optional<unsigned> index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value inputOp);
  static GetResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value inputOp);
  static GetResultsOp create(::mlir::ImplicitLocOpBuilder &builder, Value inputOp);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static GetResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static GetResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static GetResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static GetResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, /*optional*/::mlir::IntegerAttr index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetResultsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetResultsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::GetResultsOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::GetUsersOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetUsersOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GetUsersOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.get_users", odsAttrs.getContext());
  }

  GetUsersOpGenericAdaptorBase(GetUsersOp op);

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
class GetUsersOpGenericAdaptor : public detail::GetUsersOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetUsersOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  GetUsersOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetUsersOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetUsersOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetUsersOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetUsersOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetUsersOpGenericAdaptor(RangeT values, const GetUsersOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetUsersOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetUsersOp>>>
  GetUsersOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GetUsersOpAdaptor : public GetUsersOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetUsersOpGenericAdaptor::GetUsersOpGenericAdaptor;
  GetUsersOpAdaptor(GetUsersOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetUsersOp : public ::mlir::Op<GetUsersOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::RangeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetUsersOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetUsersOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.get_users");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::PDLType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::PDLType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::pdl::RangeType> getOperations() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::RangeType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value);
  static GetUsersOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value);
  static GetUsersOp create(::mlir::ImplicitLocOpBuilder &builder, Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type operations, ::mlir::Value value);
  static GetUsersOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type operations, ::mlir::Value value);
  static GetUsersOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type operations, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static GetUsersOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static GetUsersOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetUsersOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetUsersOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetUsersOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetUsersOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::GetUsersOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::GetValueTypeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetValueTypeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GetValueTypeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.get_value_type", odsAttrs.getContext());
  }

  GetValueTypeOpGenericAdaptorBase(GetValueTypeOp op);

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
class GetValueTypeOpGenericAdaptor : public detail::GetValueTypeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetValueTypeOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  GetValueTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetValueTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetValueTypeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetValueTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetValueTypeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetValueTypeOpGenericAdaptor(RangeT values, const GetValueTypeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetValueTypeOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetValueTypeOp>>>
  GetValueTypeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GetValueTypeOpAdaptor : public GetValueTypeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetValueTypeOpGenericAdaptor::GetValueTypeOpGenericAdaptor;
  GetValueTypeOpAdaptor(GetValueTypeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetValueTypeOp : public ::mlir::Op<GetValueTypeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::pdl::PDLType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetValueTypeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetValueTypeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.get_value_type");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::PDLType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::PDLType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::pdl::PDLType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::PDLType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value);
  static GetValueTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value);
  static GetValueTypeOp create(::mlir::ImplicitLocOpBuilder &builder, Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value);
  static GetValueTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value);
  static GetValueTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static GetValueTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static GetValueTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetValueTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetValueTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetValueTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetValueTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::GetValueTypeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::IsNotNullOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IsNotNullOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  IsNotNullOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.is_not_null", odsAttrs.getContext());
  }

  IsNotNullOpGenericAdaptorBase(IsNotNullOp op);

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
class IsNotNullOpGenericAdaptor : public detail::IsNotNullOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IsNotNullOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  IsNotNullOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IsNotNullOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IsNotNullOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IsNotNullOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IsNotNullOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IsNotNullOpGenericAdaptor(RangeT values, const IsNotNullOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IsNotNullOp, typename = std::enable_if_t<std::is_same_v<LateInst, IsNotNullOp>>>
  IsNotNullOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class IsNotNullOpAdaptor : public IsNotNullOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IsNotNullOpGenericAdaptor::IsNotNullOpGenericAdaptor;
  IsNotNullOpAdaptor(IsNotNullOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IsNotNullOp : public ::mlir::Op<IsNotNullOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::NSuccessors<2>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IsNotNullOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IsNotNullOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.is_not_null");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::PDLType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::PDLType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static IsNotNullOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static IsNotNullOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static IsNotNullOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static IsNotNullOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Block *trueDest, ::mlir::Block *falseDest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IsNotNullOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IsNotNullOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IsNotNullOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IsNotNullOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::IsNotNullOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::RecordMatchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RecordMatchOpGenericAdaptorBase {
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
    using generatedOpsTy = ::mlir::ArrayAttr;
    generatedOpsTy generatedOps;

    auto getGeneratedOps() const {
      auto &propStorage = this->generatedOps;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setGeneratedOps(const ::mlir::ArrayAttr &propValue) {
      this->generatedOps = propValue;
    }
    using rewriterTy = ::mlir::SymbolRefAttr;
    rewriterTy rewriter;

    auto getRewriter() const {
      auto &propStorage = this->rewriter;
      return ::llvm::cast<::mlir::SymbolRefAttr>(propStorage);
    }
    void setRewriter(const ::mlir::SymbolRefAttr &propValue) {
      this->rewriter = propValue;
    }
    using rootKindTy = ::mlir::StringAttr;
    rootKindTy rootKind;

    auto getRootKind() const {
      auto &propStorage = this->rootKind;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setRootKind(const ::mlir::StringAttr &propValue) {
      this->rootKind = propValue;
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
        rhs.benefit == this->benefit &&
        rhs.generatedOps == this->generatedOps &&
        rhs.rewriter == this->rewriter &&
        rhs.rootKind == this->rootKind &&
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
  RecordMatchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.record_match", odsAttrs.getContext());
  }

  RecordMatchOpGenericAdaptorBase(RecordMatchOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::SymbolRefAttr getRewriterAttr() {
    auto attr = ::llvm::cast<::mlir::SymbolRefAttr>(getProperties().rewriter);
    return attr;
  }

  ::mlir::SymbolRefAttr getRewriter();
  ::mlir::StringAttr getRootKindAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().rootKind);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getRootKind();
  ::mlir::ArrayAttr getGeneratedOpsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().generatedOps);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getGeneratedOps();
  ::mlir::IntegerAttr getBenefitAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().benefit);
    return attr;
  }

  uint16_t getBenefit();
};

} // namespace detail
template <typename RangeT>
class RecordMatchOpGenericAdaptor : public detail::RecordMatchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RecordMatchOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
  static constexpr int odsIndex_matchedOps = 1;
public:
  RecordMatchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RecordMatchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : RecordMatchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RecordMatchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : RecordMatchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RecordMatchOpGenericAdaptor(RangeT values, const RecordMatchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RecordMatchOp, typename = std::enable_if_t<std::is_same_v<LateInst, RecordMatchOp>>>
  RecordMatchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputs() {
    return getODSOperands(0);
  }

  RangeT getMatchedOps() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RecordMatchOpAdaptor : public RecordMatchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RecordMatchOpGenericAdaptor::RecordMatchOpGenericAdaptor;
  RecordMatchOpAdaptor(RecordMatchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RecordMatchOp : public ::mlir::Op<RecordMatchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::OneSuccessor, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RecordMatchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RecordMatchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  static constexpr int odsIndex_matchedOps = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("benefit"), ::llvm::StringRef("generatedOps"), ::llvm::StringRef("rewriter"), ::llvm::StringRef("rootKind"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBenefitAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBenefitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGeneratedOpsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGeneratedOpsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getRewriterAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getRewriterAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getRootKindAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getRootKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.record_match");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getMatchedOps() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getInputsMutable();
  ::mlir::MutableOperandRange getMatchedOpsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::SymbolRefAttr getRewriterAttr() {
    return ::llvm::cast<::mlir::SymbolRefAttr>(getProperties().rewriter);
  }

  ::mlir::SymbolRefAttr getRewriter();
  ::mlir::StringAttr getRootKindAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().rootKind);
  }

  ::std::optional< ::llvm::StringRef > getRootKind();
  ::mlir::ArrayAttr getGeneratedOpsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().generatedOps);
  }

  ::std::optional< ::mlir::ArrayAttr > getGeneratedOps();
  ::mlir::IntegerAttr getBenefitAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().benefit);
  }

  uint16_t getBenefit();
  void setRewriterAttr(::mlir::SymbolRefAttr attr) {
    getProperties().rewriter = attr;
  }

  void setRootKindAttr(::mlir::StringAttr attr) {
    getProperties().rootKind = attr;
  }

  void setRootKind(::std::optional<::llvm::StringRef> attrValue);
  void setGeneratedOpsAttr(::mlir::ArrayAttr attr) {
    getProperties().generatedOps = attr;
  }

  void setBenefitAttr(::mlir::IntegerAttr attr) {
    getProperties().benefit = attr;
  }

  void setBenefit(uint16_t attrValue);
  ::mlir::Attribute removeRootKindAttr() {
      auto attr = getProperties().rootKind;
      getProperties().rootKind = {};
      return attr;
  }

  ::mlir::Attribute removeGeneratedOpsAttr() {
      auto attr = getProperties().generatedOps;
      getProperties().generatedOps = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, ::mlir::IntegerAttr benefit, ::mlir::Block *dest);
  static RecordMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, ::mlir::IntegerAttr benefit, ::mlir::Block *dest);
  static RecordMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, ::mlir::IntegerAttr benefit, ::mlir::Block *dest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, ::mlir::IntegerAttr benefit, ::mlir::Block *dest);
  static RecordMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, ::mlir::IntegerAttr benefit, ::mlir::Block *dest);
  static RecordMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, ::mlir::IntegerAttr benefit, ::mlir::Block *dest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, uint16_t benefit, ::mlir::Block *dest);
  static RecordMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, uint16_t benefit, ::mlir::Block *dest);
  static RecordMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, uint16_t benefit, ::mlir::Block *dest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, uint16_t benefit, ::mlir::Block *dest);
  static RecordMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, uint16_t benefit, ::mlir::Block *dest);
  static RecordMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::ValueRange matchedOps, ::mlir::SymbolRefAttr rewriter, /*optional*/::mlir::StringAttr rootKind, /*optional*/::mlir::ArrayAttr generatedOps, uint16_t benefit, ::mlir::Block *dest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RecordMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RecordMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RecordMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RecordMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::RecordMatchOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::ReplaceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReplaceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ReplaceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.replace", odsAttrs.getContext());
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
  static constexpr int odsIndex_inputOp = 0;
  static constexpr int odsIndex_replValues = 1;
public:
  ReplaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReplaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReplaceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReplaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReplaceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

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

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getReplValues() {
    return getODSOperands(1);
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
class ReplaceOp : public ::mlir::Op<ReplaceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReplaceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReplaceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
  static constexpr int odsIndex_replValues = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.replace");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getReplValues() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getInputOpMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp, ::mlir::ValueRange replValues);
  static ReplaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp, ::mlir::ValueRange replValues);
  static ReplaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp, ::mlir::ValueRange replValues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::ValueRange replValues);
  static ReplaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::ValueRange replValues);
  static ReplaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::ValueRange replValues);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::ReplaceOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::SwitchAttributeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SwitchAttributeOpGenericAdaptorBase {
public:
  struct Properties {
    using caseValuesTy = ::mlir::ArrayAttr;
    caseValuesTy caseValues;

    auto getCaseValues() const {
      auto &propStorage = this->caseValues;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setCaseValues(const ::mlir::ArrayAttr &propValue) {
      this->caseValues = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.caseValues == this->caseValues &&
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
  SwitchAttributeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.switch_attribute", odsAttrs.getContext());
  }

  SwitchAttributeOpGenericAdaptorBase(SwitchAttributeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getCaseValuesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().caseValues);
    return attr;
  }

  ::mlir::ArrayAttr getCaseValues();
};

} // namespace detail
template <typename RangeT>
class SwitchAttributeOpGenericAdaptor : public detail::SwitchAttributeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SwitchAttributeOpGenericAdaptorBase;
  static constexpr int odsIndex_attribute = 0;
public:
  SwitchAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SwitchAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SwitchAttributeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SwitchAttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SwitchAttributeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SwitchAttributeOpGenericAdaptor(RangeT values, const SwitchAttributeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SwitchAttributeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SwitchAttributeOp>>>
  SwitchAttributeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getAttribute() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SwitchAttributeOpAdaptor : public SwitchAttributeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SwitchAttributeOpGenericAdaptor::SwitchAttributeOpGenericAdaptor;
  SwitchAttributeOpAdaptor(SwitchAttributeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SwitchAttributeOp : public ::mlir::Op<SwitchAttributeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::AtLeastNSuccessors<1>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SwitchAttributeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SwitchAttributeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_attribute = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("caseValues")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCaseValuesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCaseValuesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.switch_attribute");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::AttributeType> getAttribute() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::AttributeType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getAttributeMutable() {
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

  ::mlir::Block *getDefaultDest() {
    return (*this)->getSuccessor(0);
  }

  ::mlir::SuccessorRange getCases() {
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
  ::mlir::ArrayAttr getCaseValuesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().caseValues);
  }

  ::mlir::ArrayAttr getCaseValues();
  void setCaseValuesAttr(::mlir::ArrayAttr attr) {
    getProperties().caseValues = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value attribute, ArrayRef<Attribute> caseValues, Block *defaultDest, BlockRange dests);
  static SwitchAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value attribute, ArrayRef<Attribute> caseValues, Block *defaultDest, BlockRange dests);
  static SwitchAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, Value attribute, ArrayRef<Attribute> caseValues, Block *defaultDest, BlockRange dests);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value attribute, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value attribute, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value attribute, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value attribute, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value attribute, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value attribute, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchAttributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchAttributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::SwitchAttributeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::SwitchOperandCountOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SwitchOperandCountOpGenericAdaptorBase {
public:
  struct Properties {
    using caseValuesTy = ::mlir::DenseIntElementsAttr;
    caseValuesTy caseValues;

    auto getCaseValues() const {
      auto &propStorage = this->caseValues;
      return ::llvm::cast<::mlir::DenseIntElementsAttr>(propStorage);
    }
    void setCaseValues(const ::mlir::DenseIntElementsAttr &propValue) {
      this->caseValues = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.caseValues == this->caseValues &&
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
  SwitchOperandCountOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.switch_operand_count", odsAttrs.getContext());
  }

  SwitchOperandCountOpGenericAdaptorBase(SwitchOperandCountOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseIntElementsAttr getCaseValuesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseIntElementsAttr>(getProperties().caseValues);
    return attr;
  }

  ::mlir::DenseIntElementsAttr getCaseValues();
};

} // namespace detail
template <typename RangeT>
class SwitchOperandCountOpGenericAdaptor : public detail::SwitchOperandCountOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SwitchOperandCountOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  SwitchOperandCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SwitchOperandCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SwitchOperandCountOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SwitchOperandCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SwitchOperandCountOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SwitchOperandCountOpGenericAdaptor(RangeT values, const SwitchOperandCountOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SwitchOperandCountOp, typename = std::enable_if_t<std::is_same_v<LateInst, SwitchOperandCountOp>>>
  SwitchOperandCountOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SwitchOperandCountOpAdaptor : public SwitchOperandCountOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SwitchOperandCountOpGenericAdaptor::SwitchOperandCountOpGenericAdaptor;
  SwitchOperandCountOpAdaptor(SwitchOperandCountOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SwitchOperandCountOp : public ::mlir::Op<SwitchOperandCountOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::AtLeastNSuccessors<1>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SwitchOperandCountOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SwitchOperandCountOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("caseValues")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCaseValuesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCaseValuesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.switch_operand_count");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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

  ::mlir::Block *getDefaultDest() {
    return (*this)->getSuccessor(0);
  }

  ::mlir::SuccessorRange getCases() {
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
    return ::llvm::cast<::mlir::DenseIntElementsAttr>(getProperties().caseValues);
  }

  ::mlir::DenseIntElementsAttr getCaseValues();
  void setCaseValuesAttr(::mlir::DenseIntElementsAttr attr) {
    getProperties().caseValues = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value inputOp, ArrayRef<int32_t> counts, Block *defaultDest, BlockRange dests);
  static SwitchOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value inputOp, ArrayRef<int32_t> counts, Block *defaultDest, BlockRange dests);
  static SwitchOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, Value inputOp, ArrayRef<int32_t> counts, Block *defaultDest, BlockRange dests);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchOperandCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchOperandCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::SwitchOperandCountOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::SwitchOperationNameOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SwitchOperationNameOpGenericAdaptorBase {
public:
  struct Properties {
    using caseValuesTy = ::mlir::ArrayAttr;
    caseValuesTy caseValues;

    auto getCaseValues() const {
      auto &propStorage = this->caseValues;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setCaseValues(const ::mlir::ArrayAttr &propValue) {
      this->caseValues = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.caseValues == this->caseValues &&
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
  SwitchOperationNameOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.switch_operation_name", odsAttrs.getContext());
  }

  SwitchOperationNameOpGenericAdaptorBase(SwitchOperationNameOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getCaseValuesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().caseValues);
    return attr;
  }

  ::mlir::ArrayAttr getCaseValues();
};

} // namespace detail
template <typename RangeT>
class SwitchOperationNameOpGenericAdaptor : public detail::SwitchOperationNameOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SwitchOperationNameOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  SwitchOperationNameOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SwitchOperationNameOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SwitchOperationNameOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SwitchOperationNameOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SwitchOperationNameOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SwitchOperationNameOpGenericAdaptor(RangeT values, const SwitchOperationNameOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SwitchOperationNameOp, typename = std::enable_if_t<std::is_same_v<LateInst, SwitchOperationNameOp>>>
  SwitchOperationNameOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SwitchOperationNameOpAdaptor : public SwitchOperationNameOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SwitchOperationNameOpGenericAdaptor::SwitchOperationNameOpGenericAdaptor;
  SwitchOperationNameOpAdaptor(SwitchOperationNameOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SwitchOperationNameOp : public ::mlir::Op<SwitchOperationNameOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::AtLeastNSuccessors<1>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SwitchOperationNameOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SwitchOperationNameOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("caseValues")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCaseValuesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCaseValuesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.switch_operation_name");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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

  ::mlir::Block *getDefaultDest() {
    return (*this)->getSuccessor(0);
  }

  ::mlir::SuccessorRange getCases() {
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
  ::mlir::ArrayAttr getCaseValuesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().caseValues);
  }

  ::mlir::ArrayAttr getCaseValues();
  void setCaseValuesAttr(::mlir::ArrayAttr attr) {
    getProperties().caseValues = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value inputOp, ArrayRef<OperationName> names, Block *defaultDest, BlockRange dests);
  static SwitchOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value inputOp, ArrayRef<OperationName> names, Block *defaultDest, BlockRange dests);
  static SwitchOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, Value inputOp, ArrayRef<OperationName> names, Block *defaultDest, BlockRange dests);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::SwitchOperationNameOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::SwitchResultCountOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SwitchResultCountOpGenericAdaptorBase {
public:
  struct Properties {
    using caseValuesTy = ::mlir::DenseIntElementsAttr;
    caseValuesTy caseValues;

    auto getCaseValues() const {
      auto &propStorage = this->caseValues;
      return ::llvm::cast<::mlir::DenseIntElementsAttr>(propStorage);
    }
    void setCaseValues(const ::mlir::DenseIntElementsAttr &propValue) {
      this->caseValues = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.caseValues == this->caseValues &&
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
  SwitchResultCountOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.switch_result_count", odsAttrs.getContext());
  }

  SwitchResultCountOpGenericAdaptorBase(SwitchResultCountOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseIntElementsAttr getCaseValuesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseIntElementsAttr>(getProperties().caseValues);
    return attr;
  }

  ::mlir::DenseIntElementsAttr getCaseValues();
};

} // namespace detail
template <typename RangeT>
class SwitchResultCountOpGenericAdaptor : public detail::SwitchResultCountOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SwitchResultCountOpGenericAdaptorBase;
  static constexpr int odsIndex_inputOp = 0;
public:
  SwitchResultCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SwitchResultCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SwitchResultCountOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SwitchResultCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SwitchResultCountOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SwitchResultCountOpGenericAdaptor(RangeT values, const SwitchResultCountOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SwitchResultCountOp, typename = std::enable_if_t<std::is_same_v<LateInst, SwitchResultCountOp>>>
  SwitchResultCountOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputOp() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SwitchResultCountOpAdaptor : public SwitchResultCountOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SwitchResultCountOpGenericAdaptor::SwitchResultCountOpGenericAdaptor;
  SwitchResultCountOpAdaptor(SwitchResultCountOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SwitchResultCountOp : public ::mlir::Op<SwitchResultCountOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::AtLeastNSuccessors<1>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SwitchResultCountOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SwitchResultCountOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputOp = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("caseValues")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCaseValuesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCaseValuesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.switch_result_count");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::OperationType> getInputOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::OperationType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputOpMutable() {
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

  ::mlir::Block *getDefaultDest() {
    return (*this)->getSuccessor(0);
  }

  ::mlir::SuccessorRange getCases() {
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
    return ::llvm::cast<::mlir::DenseIntElementsAttr>(getProperties().caseValues);
  }

  ::mlir::DenseIntElementsAttr getCaseValues();
  void setCaseValuesAttr(::mlir::DenseIntElementsAttr attr) {
    getProperties().caseValues = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value inputOp, ArrayRef<int32_t> counts, Block *defaultDest, BlockRange dests);
  static SwitchResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value inputOp, ArrayRef<int32_t> counts, Block *defaultDest, BlockRange dests);
  static SwitchResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, Value inputOp, ArrayRef<int32_t> counts, Block *defaultDest, BlockRange dests);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value inputOp, ::mlir::DenseIntElementsAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchResultCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchResultCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::SwitchResultCountOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::SwitchTypeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SwitchTypeOpGenericAdaptorBase {
public:
  struct Properties {
    using caseValuesTy = ::mlir::ArrayAttr;
    caseValuesTy caseValues;

    auto getCaseValues() const {
      auto &propStorage = this->caseValues;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setCaseValues(const ::mlir::ArrayAttr &propValue) {
      this->caseValues = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.caseValues == this->caseValues &&
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
  SwitchTypeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.switch_type", odsAttrs.getContext());
  }

  SwitchTypeOpGenericAdaptorBase(SwitchTypeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getCaseValuesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().caseValues);
    return attr;
  }

  ::mlir::ArrayAttr getCaseValues();
};

} // namespace detail
template <typename RangeT>
class SwitchTypeOpGenericAdaptor : public detail::SwitchTypeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SwitchTypeOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  SwitchTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SwitchTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SwitchTypeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SwitchTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SwitchTypeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SwitchTypeOpGenericAdaptor(RangeT values, const SwitchTypeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SwitchTypeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SwitchTypeOp>>>
  SwitchTypeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SwitchTypeOpAdaptor : public SwitchTypeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SwitchTypeOpGenericAdaptor::SwitchTypeOpGenericAdaptor;
  SwitchTypeOpAdaptor(SwitchTypeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SwitchTypeOp : public ::mlir::Op<SwitchTypeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::AtLeastNSuccessors<1>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SwitchTypeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SwitchTypeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("caseValues")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCaseValuesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCaseValuesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.switch_type");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::TypeType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::TypeType>>(*getODSOperands(0).begin());
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

  ::mlir::Block *getDefaultDest() {
    return (*this)->getSuccessor(0);
  }

  ::mlir::SuccessorRange getCases() {
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
  ::mlir::ArrayAttr getCaseValuesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().caseValues);
  }

  ::mlir::ArrayAttr getCaseValues();
  void setCaseValuesAttr(::mlir::ArrayAttr attr) {
    getProperties().caseValues = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value edge, ArrayRef<Attribute> types, Block *defaultDest, BlockRange dests);
  static SwitchTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value edge, ArrayRef<Attribute> types, Block *defaultDest, BlockRange dests);
  static SwitchTypeOp create(::mlir::ImplicitLocOpBuilder &builder, Value edge, ArrayRef<Attribute> types, Block *defaultDest, BlockRange dests);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  auto getCaseTypes() { return getCaseValues().getAsValueRange<TypeAttr>(); }
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::SwitchTypeOp)

namespace mlir::pdl_interp {


//===----------------------------------------------------------------------===//
// ::mlir::pdl_interp::SwitchTypesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SwitchTypesOpGenericAdaptorBase {
public:
  struct Properties {
    using caseValuesTy = ::mlir::ArrayAttr;
    caseValuesTy caseValues;

    auto getCaseValues() const {
      auto &propStorage = this->caseValues;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setCaseValues(const ::mlir::ArrayAttr &propValue) {
      this->caseValues = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.caseValues == this->caseValues &&
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
  SwitchTypesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pdl_interp.switch_types", odsAttrs.getContext());
  }

  SwitchTypesOpGenericAdaptorBase(SwitchTypesOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getCaseValuesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().caseValues);
    return attr;
  }

  ::mlir::ArrayAttr getCaseValues();
};

} // namespace detail
template <typename RangeT>
class SwitchTypesOpGenericAdaptor : public detail::SwitchTypesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SwitchTypesOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  SwitchTypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SwitchTypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SwitchTypesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SwitchTypesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SwitchTypesOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SwitchTypesOpGenericAdaptor(RangeT values, const SwitchTypesOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SwitchTypesOp, typename = std::enable_if_t<std::is_same_v<LateInst, SwitchTypesOp>>>
  SwitchTypesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SwitchTypesOpAdaptor : public SwitchTypesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SwitchTypesOpGenericAdaptor::SwitchTypesOpGenericAdaptor;
  SwitchTypesOpAdaptor(SwitchTypesOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SwitchTypesOp : public ::mlir::Op<SwitchTypesOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::AtLeastNSuccessors<1>::Impl, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SwitchTypesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SwitchTypesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("caseValues")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCaseValuesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCaseValuesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pdl_interp.switch_types");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::pdl::RangeType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::pdl::RangeType>>(*getODSOperands(0).begin());
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

  ::mlir::Block *getDefaultDest() {
    return (*this)->getSuccessor(0);
  }

  ::mlir::SuccessorRange getCases() {
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
  ::mlir::ArrayAttr getCaseValuesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().caseValues);
  }

  ::mlir::ArrayAttr getCaseValues();
  void setCaseValuesAttr(::mlir::ArrayAttr attr) {
    getProperties().caseValues = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value edge, ArrayRef<Attribute> types, Block *defaultDest, BlockRange dests);
  static SwitchTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value edge, ArrayRef<Attribute> types, Block *defaultDest, BlockRange dests);
  static SwitchTypesOp create(::mlir::ImplicitLocOpBuilder &builder, Value edge, ArrayRef<Attribute> types, Block *defaultDest, BlockRange dests);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static SwitchTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr caseValues, ::mlir::Block *defaultDest, ::mlir::BlockRange cases);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SwitchTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchTypesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SwitchTypesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  auto getCaseTypes() { return getCaseValues().getAsRange<ArrayAttr>(); }
};

} // namespace mlir::pdl_interp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::pdl_interp::SwitchTypesOp)


#endif // GET_OP_CLASSES

