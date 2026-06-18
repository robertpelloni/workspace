/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: TransformOps.td                                                      *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::transform {

/// Attempts sequences of transforms until one succeeds
/// This op may have an arbitrary number of regions, each of which represents a
///     sequence of transform operations to be applied to the same payload IR. The
///     regions are visited in order of appearance, and transforms in them are
///     applied in their respective order of appearance. If one of these transforms
///     fails to apply, the remaining ops in the same region are skipped an the next
///     region is attempted. If all transformations in a region succeed, the
///     remaining regions are skipped and the entire "alternatives" transformation
///     succeeds. If all regions contained a failing transformation, the entire
///     "alternatives" transformation fails.
/// 
///     It is up to the nested operations to define which errors are "recoverable"
///     (or "silenceable") and allow another alternatives to be attempted, and which
///     errors should be propagated without attempting the other alternatives.
/// 
///     The single operand of this operation is the scope in which the alternative
///     transformation sequences are attempted, that is, an operation in the payload
///     IR that contains all the other operations that may be modified by the
///     transformations. The scope operation must be isolated from above. There is
///     no check that the transforms are indeed scoped as their "apply" methods can
///     be arbitrarily complex. Therefore it is the responsibility of the user to
///     ensure that the transforms are scoped correctly, or to produce an
///     irrecoverable error and thus abort the execution without attempting the
///     remaining alternatives. Note that the payload IR outside of the given scope
///     is not necessarily in the valid state, or even accessible to the
///     transformation.
/// 
///     The changes to the IR within the scope performed by transforms in the failed
///     alternative region are reverted before attempting the next region.
///     Practically, this is achieved by cloning the scope. Therefore it is advised
///     to limit the scope as much as possible and place the most likely
///     alternatives early in the region list. The operation is also isolated from
///     above and requires rediscovering the operations within the given scope to
///     avoid additional handle invalidation. The latter restriction may be lifted
///     in the future.
/// 
///     Each of the regions may yield transform IR handles. The handles of the first
///     successful alternative region are returned as the results of the
///     "alternatives" op. Therefore, each alternative region must yield the same
///     number of results, which should also match the number and the types of the
///     "alternatives" op results.
/// 
///     Remark: this op allows one to implement a simple "try" construct as follows:
/// 
///     ```mlir
///     %result = transform.alternatives %scope {
///     ^bb0(%arg0: !transform.any_op):
///       // Try a fallible transformation.
///       %0 = transform.fallible %arg0 // ...
///       // If succeeded, yield the the result of the transformation.
///       transform.yield %0 : !transform.any_op
///     }, {
///     ^bb0(%arg0: !transform.any_op):
///       // Otherwise, the second alternative is tried and it always succeeds by
///       // returning the original handle.
///       transform.yield %arg0 : !transform.any_op
///     }
///     ```
class AlternativesOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Annotates the target operation with an attribute by name
/// Adds an attribute with the given `name` to the `target` operation. An
///     optional `param` handle can be provided to give the attribute a specific
///     value, else a UnitAttr is added. A single attribute will be broadcasted to
///     all target operations, otherwise the attributes will be mapped 1:1 based on
///     the order within the handles.
/// 
///     Produces a silenceable failure if the length of the parameter payload does
///     not match the length of the target payload. Does not consume the provided
///     handles.
class AnnotateOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Populates canonicalization patterns
/// This op populates all canonicalization patterns of all loaded dialects in
///     an `apply_patterns` transform.
class ApplyCanonicalizationPatternsOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Eliminate common subexpressions in the body of the target op
/// This transform applies common subexpression elimination (CSE) to the body
///     of the targeted op.
/// 
///     This transform reads the target handle and modifies the payload. Existing
///     handles to operations inside of the targeted op are retained and updated if
///     necessary. Note that this can lead to situations where a handle, that was
///     previously mapped to multiple distinct (but equivalent) operations, is now
///     mapped to the same operation multiple times.
class ApplyCommonSubexpressionEliminationOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Applies conversion patterns to the body of the targeted op
/// This transform applies the specified conversion patterns to the targeted op
///     and all nested ops. By default, this transform applies a "full" dialect
///     conversion. If the `partial_conversion` unit attribute is present, this
///     transform applies a partial dialect conversion.
/// 
///     The patterns that should be applied are specified in the first graph region
///     of this op. They must implement the
///     `ConversionPatternDescriptorOpInterface`. The order in which patterns are
///     applied is unspecified; i.e., the ordering of ops in the region of this op
///     is irrelevant.
/// 
///     The second, optional graph region contains exactly one op that specifies
///     default type converter that should be used with this dialect conversion. If
///     provided, this op must implement the `TypeConverterBuilderOpInterface`.
///     Type converters are a property of conversion patterns: each conversion
///     pattern stores the type converter that should be used in its C++ class. Each
///     conversion pattern descriptor can optionally specify a type converter in its
///     `getTypeConverter` interface method. If no type converter is specified in
///     this method, the default type converter of the dialect conversion is used.
///     Default type converters are useful if the same type converter should be used
///     for multiple sets of conversion patterns. (Patterns that should not use this
///     default type converter specify their own type converter.)
/// 
///     The `legal_ops`, `illegal_ops`, `legal_dialects`, `illegal_dialects`
///     attributes specify the conversion target.
/// 
///     This transform modifies the payload. By default, it consumes the `target`
///     handle. It does not produce any handles.
/// 
///     If the `preserve_handles` attribute is set, this transform does not consume
///     the `target` handle and instead updates handles based on notifications from
///     a tracking listener that is attached to the dialect conversion, similar to
///     `transform.apply_patterns`. Only replacements via `RewriterBase::replaceOp`
///     or `replaceOpWithNewOp` are considered "payload op replacements". In
///     contrast to `transform.apply_patterns`, we allow replacement ops even if the
///     op name has changed. This is because conversion patterns are expected to
///     lower ops to different ops (from a different dialect). More details can be
///     found at the documentation site of `TrackingListener`.
/// 
///     This transform produces a silenceable failure if the dialect conversion was
///     unsuccessful or the tracking listener failed to find a replacement op.
class ApplyConversionPatternsOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Eliminate dead operations in the body of the target op
/// This transform applies dead code elimination (DCE) to the body of the
///     targeted op.
/// 
///     Note: "transform.apply_patterns" with an empty region can also be used to
///     remove dead ops. However, that op applies additional simplifications such as
///     op folding and region simplification.
/// 
///     This transform reads the target handle and modifies the payload. Note that
///     this transform may silently remove payload ops from handles.
class ApplyDeadCodeEliminationOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Move loop-invariant code out of a loop-like op
/// This transform moves side-effect free, loop invariant code out of the
///     targeted loop-like op. The targeted op must implement the
///     `LoopLikeOpInterface`.
/// 
///     Note: To move invariant ops from a loop nest, this transform must be applied
///     to each loop of the loop nest, starting with the inner-most loop.
/// 
///     This transform reads the target handle and modifies the payload.
class ApplyLoopInvariantCodeMotionOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Greedily applies patterns to the body of the targeted op
/// This transform greedily applies the specified patterns to the body of the
///     targeted op until a fixpoint was reached. Patterns are not applied to the
///     targeted op itself.
/// 
///     The patterns that should be applied are specified in the graph region of
///     this op. They must implement the `PatternDescriptorOpInterface`. The order
///     in which patterns are applied is unspecified; i.e., the ordering of ops in
///     the region of this op is irrelevant.
/// 
///     If `apple_cse` is set, the greedy pattern rewrite is interleaved with
///     common subexpression elimination (CSE): both are repeated until a fixpoint
///     is reached.
/// 
///     This transform only reads the target handle and modifies the payload. If a
///     pattern erases or replaces a tracked op, the mapping is updated accordingly.
/// 
///     Only replacements via `RewriterBase::replaceOp` or `replaceOpWithNewOp` are
///     considered "payload op replacements". Furthermore, only if the replacement
///     values are defined by the same op and that op has the same type as the
///     original op, the mapping is updated. Otherwise, this transform produces a
///     silenceable failure. More details can be found at the documentation site of
///     `TrackingListener`.
/// 
///     This transform also produces a silenceable failure if the pattern
///     application did not converge within the default number of
///     iterations/rewrites of the greedy pattern rewrite driver.
class ApplyPatternsOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Applies the specified registered pass or pass pipeline
/// This transform applies the specified pass or pass pipeline to the targeted
///     ops. The name of the pass/pipeline is specified as a string attribute, as
///     set during pass/pipeline registration.
/// 
///     Optionally, pass options may be specified via a DictionaryAttr. This
///     dictionary is converted to a string -- formatted `key=value ...` -- which
///     is expected to be in the exact format used by the pass on the commandline.
///     Values are either attributes or (SSA-values of) Transform Dialect params.
///     For example:
/// 
///     ```mlir
///     transform.apply_registered_pass "canonicalize"
///         with options = { "top-down" = false,
///                          "max-iterations" = %max_iter,
///                          "test-convergence" = true,
///                          "max-num-rewrites" = %max_rewrites }
///         to %module
///     : (!transform.any_param, !transform.any_param, !transform.any_op) -> !transform.any_op
///     ```
/// 
///     Options' values which are `ArrayAttr`s are converted to comma-separated
///     lists of options. Likewise for params which associate multiple values.
/// 
///     This op first looks for a pass pipeline with the specified name. If no such
///     pipeline exists, it looks for a pass with the specified name. If no such
///     pass exists either, this op fails definitely.
/// 
///     This transform consumes the target handle and produces a new handle that is
///     mapped to the same op. Passes are not allowed to remove/modify the operation
///     that they operate on, so the target op is guaranteed to still exist. The
///     target handle is invalidated because a pass may arbitrarily modify the body
///     of targeted ops.
class ApplyRegisteredPassOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Collects patterns that convert ops from the specified dialect to LLVM
///     dialect ops. These patterns require an "LLVMTypeConverter".
/// 
///     Note: Only dialects that implement the `ConvertToLLVMPatternInterface` are
///     supported. Any conversion target modifications by interface implementations
///     are currently ignored. The conversion target is fully specified by the
///     enclosing "apply_conversion_patterns" op.
class ApplyToLLVMConversionPatternsOp;

} // namespace mlir::transform
namespace mlir::transform {

class CastOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Collects all payload ops that match the given named matcher
/// Collects operations or other payload IR objects nested under `root`
///     (inclusive) that match the given matcher expressed as a named sequence. The
///     matcher sequence must accept exactly one argument that it is not allowed to
///     modify. It must yield as many values as this op has results. Each of the
///     yielded values must be associated with exactly one payload object. If any
///     operation in the matcher sequence produces a silenceable failure, the
///     matcher advances to the next payload operation in the walk order without
///     finishing the sequence.
/// 
///     The i-th result of this operation is constructed by concatenating the i-th
///     yielded payload IR objects of all successful matcher sequence applications.
///     All results are guaranteed to be mapped to the same number of payload IR
///     objects.
/// 
///     The operation succeeds unless the matcher sequence produced a definite
///     failure for any invocation.
class CollectMatchingOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Applies named sequences when a named matcher succeeds
/// Given a pair of co-indexed lists of transform dialect symbols (such as
///     `transform.named_sequence`), walks the payload IR associated with the root
///     handle and interprets the symbols as matcher/action pairs by applying the
///     body of the corresponding symbol definition. The symbol from the first list
///     is the matcher part: if it results in a silenceable error, the error is
///     silenced and the next matcher is attempted. Definite failures from any
///     matcher stop the application immediately and are propagated unconditionally.
///     If none of the matchers succeeds, the next payload operation in walk order
///     (post-order at the moment of writing, double check `Operation::walk`) is
///     matched. If a matcher succeeds, the co-indexed action symbol is applied and
///     the following matchers are not applied to the same payload operation. If the
///     action succeeds, the next payload operation in walk order is matched. If it
///     fails, both silenceable and definite errors are propagated as the result of
///     this op; propagation of silenceable errors is postponed until the end of the
///     walk.
/// 
///     The matcher symbol must take at least one operand of a type that implements
///     the same transform dialect interface as the `root` operand (a check is
///     performed at application time to see if the associated payload satisfies the
///     constraints of the actual type), and may take additional operands with a
///     similar type requirement. It must not consume operands as multiple matchers
///     may be applied. The matcher may produce any number of results. The action
///     symbol paired with the matcher must take the same number of arguments as the
///     matcher has results, and these arguments must implement the same transform
///     dialect interfaces, but not necessarily have the exact same type (again, a
///     check is performed at application time to see if the associated payload
///     satisfies the constraints of actual types on both sides).
/// 
///     The action symbol may have results that are accumulated from all actions and
///     returned from the `foreach_match` operation on success. Unless the
///     `flatten_results` attribute is present, each action result must be
///     associated with exactly one payload entity. The actions are expected to only
///     modify payload operations nested in the `root` payload operations associated
///     with the operand of this transform operation. Furthermore, the actions may
///     not modify operations outside of the currently matched payload operation,
///     e.g., they may not modify sibling or parent operations. If such behavior is
///     desired, the parent must be matched first and the nested operations obtained
///     by traversing the IR from the parent. This is due to the matching being
///     performed as a post-order IR walk.
/// 
///     This operation consumes the operand and produces a new handle associated
///     with the same payload. This is necessary to trigger invalidation of handles
///     to any of the payload operations nested in the payload operations associated
///     with the operand, as those are likely to be modified by actions.
/// 
///     By default, the root payload operation associated with the operand is not
///     matched. This is to support the conservative case where applied actions may
///     invalidate the root payload operation. If the optional `restrict_root`
///     attribute is set, the root operand is guaranteed to not be invalidated by any
///     of the applied actions. In such cases, the root payload operation is also
///     matched. This is useful because matching the root payload operation is a
///     common idiom, when e.g. matching a func.func directly and operations nested
///     under it.
/// 
///     The operation succeeds if none of the matchers produced a definite failure
///     during application and if all of the applied actions produced success. Note
///     that it also succeeds if all the matchers failed on all payload operations,
///     i.e. failure to apply is not an error. The operation produces a silenceable
///     failure if any applied action produced a silenceable failure. In this case,
///     the resulting handle is associated with an empty payload. The operation
///     produces a definite failure if any of the applied matchers or actions
///     produced a definite failure.
class ForeachMatchOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Executes the body for each element of the payload
/// Execute the op's body - its single region block - exactly once per
///     element of the payload associated to a target handle. The body's
///     transformations are applied in order of appearance until reaching the
///     (implicit) YieldOp terminator.
/// 
///     Each iteration gets executed by co-indexing the payloads of the arguments
///     and mapping the body's arguments to these tuples, as though iterating over
///     the zipped together `targets`. As such, in each iteration, the size of the
///     payload of each of the body's block arguments is exactly one. The attribute
///     `zip_shortest` can be used if the targets vary in their number of payloads;
///     this will limit the iterations to only the number of payloads found in the
///     shortest target.
/// 
///     This op always reads the target handles. Furthermore, it consumes a handle
///     if there is a transform op in the body that consumes the corresponding
///     block argument. Handles can point to ops, values, or parameters.
/// 
///     #### Return Modes
/// 
///     This op produces as many result handles as the body's terminating YieldOp
///     has operands. For each result, the payloads of the corresponding YieldOp
///     operand are merged and mapped to the same resulting handle.
/// 
///     If the target handles do not associate payloads of the same size, a
///     silencable failure will be generated.
/// 
///     During application, if any transformation in the sequence fails, the entire
///     sequence fails immediately with the same failure, leaving the payload IR in
///     a potentially invalid state, i.e., this operation offers no transformation
///     rollback capabilities.
class ForeachOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Get handle to the consumers of this operation's result number
/// The handle defined by this Transform op corresponds to all operations that
///     consume the SSA value defined by the `target` and `result_number`
///     arguments.
///     This operation applies to a single payload operation, otherwise it produces
///     a definite failure.
///     The return handle points to the consuming operations operations, which can
///     be empty.
class GetConsumersOfResult;

} // namespace mlir::transform
namespace mlir::transform {

/// Get handle to the defining op of a value
/// The handle defined by this Transform op corresponds to the defining op of
///     the targeted value.
/// 
///     This transform produces a silenceable failure if the targeted value is a
///     block argument.
class GetDefiningOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Get a handle to the operand(s) of the targeted op
/// The handle defined by this Transform op corresponds to the operands of the
///     given `target` operation specified by the given set of positions. There are
///     three possible modes:
/// 
///      - Position list directly, i.e. `%target[0, 1, 2]`. This will return the
///        operands at the specified positions.
///      - Inverted position list, i.e. `%target[except(0, 1, 2)]`. This will return
///        all operands except those at the given positions.
///      - All, i.e. `%target[all]`. This will return all operands of the operation.
///     
///     This transform produces a silenceable failure if any of the operand indices
///     exceeds the number of operands in the target. It reads the target handle and
///     produces the result handle.
class GetOperandOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Gets handles to the closest parent ops
/// The handle defined by this Transform op corresponds to the parents of the
///     targeted payload ops (in the same order).
/// 
///     Requirements that parent ops must fulfill can be optionally specified. In
///     that case for each target op, the closest parent op that fulfills all
///     requirements, is returned.
///     - `isolated_from_above`: the parent op must be isolated from above
///     - `allow_empty_results`: get_parent_op is allowed to return an empty list
///       and still succeeds. In such a case, if `get_parent_op` fails for any
///       operation in the list, the entire transform returns an empty handle.
///     - `op_name`: the parent op must have the specified name
///     - `nth_parent`: get the n-th parent of that satisfies the above requirements
/// 
///     If `deduplicate` is set, the result handle does not contain any duplicate
///     ops. For example, given the list
///     "(childof(A), childof(B), childof(B), childof(A), childof(B))", the
///     resulting list will be just "(A, B)". Note that no other semantic ordering
///     is applied, e.g., "B" may itself be a parent of "A". This may have an impact
///     on the further transformation applied to the handle produced here.
/// 
///     If any of the given Payload IR ops has no such suitable parent, then:
///       - if `allow_empty_results` is set, the result handle is empty
///       - otherwise, the transformation produces a silenceable failure.
class GetParentOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Get handle to the producer of this operation's operand number
/// The handle defined by this Transform op corresponds to operation that
///     produces the SSA value defined by the `target` and `operand_number`
///     arguments. If the origin of the SSA value is not an operations (i.e. it is
///     a block argument), the transform produces a silenceable failure.
///     The return handle points to only the subset of successfully produced
///     computational operations, which can be empty.
class GetProducerOfOperand;

} // namespace mlir::transform
namespace mlir::transform {

/// Get a handle to the result(s) of the targeted op
/// The handle defined by this Transform op correspond to the OpResults of the
///     given `target` operation. Optionally `result_number` can be specified to
///     select a specific result.
///     
///     This transform fails silently if the targeted operation does not have enough
///     results. It reads the target handle and produces the result handle.
/// 
///     The handle defined by this Transform op corresponds to the results of the
///     given `target` operation specified by the given set of positions. There are
///     three possible modes:
/// 
///      - Position list directly, i.e. `%target[0, 1, 2]`. This will return the
///        results at the specified positions.
///      - Inverted position list, i.e. `%target[except(0, 1, 2)]`. This will return
///        all results except those at the given positions.
///      - All, i.e. `%target[all]`. This will return all results of the operation.
///     
///     This transform produces a silenceable failure if any of the result indices
///     exceeds the number of results returned by the target. It reads the target
///     handle and produces the result handle.
class GetResultOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Get a parameter containing the type of the given value
/// This operation creates a new Transform parameter containing the
///     type(s) of the value(s) associated with the operand handle.
/// 
///     This transform never fails.
class GetTypeOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Includes a named transform sequence
/// The application of this transform operation is equivalent to applying the
///     operations contained in the named transform sequence with operands being
///     remapped to block arguments. The behavior of the operation when a
///     transformation in the included named sequence produces a silenceable error
///     is controlled by the `failure_propagation_mode` attribute. When set to
///     `propagate`, the failure of any nested transformation in the sequence
///     implies immediate failure of the entire sequence with a silenceable error,
///     and no further transformation is attempted. When set to `suppress`,
///     silenceable errors in nested operations are ignored and further
///     transformations are applied. Beware that even silenceable errors may leave
///     the payload IR in a state unsuitable for further transformations. It is the
///     responsibility of the user to ensure the following transformations are
///     robust enough when errors are suppressed. Definite errors are propagated
///     immediately regardless of the mode. The objects associated with the results
///     of this operation are the same as those associated with the operands of the
///     `transform.yield` in the referenced named sequence.
class IncludeOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Matches if the handle is not associated to any op
/// Succeeds if the handle is not associated to any op.
class MatchOperationEmptyOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Matches a single operation of one of the given kinds
/// Succeeds if the operation associated with the operand handle has one of the
///     given operation names. Produces a silenceable failure otherwise.
/// 
///     If more than one payload operation is associated with the operand handle,
///     produces a definite failure.
class MatchOperationNameOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Matches if two parameter lists are associated with the same value
/// Succeeds if all of the co-indexed values associated with the given
///     parameters relate as specified by the predicate (greater than, less than,
///     equal to, or their combinations). Comparison treats all values as signed.
///     Produces a silenceable failure otherwise.
class MatchParamCmpIOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Merges handles into one pointing to the union of payload ops
/// Creates a new Transform IR handle value that points to the same Payload IR
///     operations/values/parameters as the operand handles. The Payload IR elements
///     are listed in the same order as they are in the operand handles, grouped by
///     operand handle, e.g., all Payload IR associated with the first handle comes
///     first, then all Payload IR associated with the second handle and so on. If
///     `deduplicate` is set, do not add the given Payload IR operation, value, or
///     parameter more than once to the final list regardless of it coming from the
///     same or different handles. Consumes the operands and produces a new handle.
class MergeHandlesOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Named transform sequence that can be included elsewhere
/// Defines a named (callable, function-like) sequence of other Transform
///     dialect operations that can be included using `transform.include` as part of
///     another Transform dialect construct. This sequence is not processed
///     immediately but rather dispatched to when the inclusion is processed. The
///     arguments and results can be used to communicate a subset of mapping into
///     the named sequence. The sequence must consist of a single block and end with
///     a `transform.yield` terminator. The operands of the terminator become the
///     results of the `transform.include`.
/// 
///     When dispatched to, the operations in the named sequence are executed one by
///     one, similarly to the regular unnamed sequence. The failure propagation mode
///     is specified on the `transform.include`. Different inclusions may use
///     different failure propagation modes. This transform operation always
///     succeeds by itself, but the inclusion may fail if any of the operations
///     fail.
/// 
///     Named sequences can only appear at the top-level of the Transform dialect
///     nesting structure. That is, they cannot be nested in other Transform dialect
///     operations. Furthermore, one of the ancestors must have the `SymbolTable`
///     trait and have the `transform.with_named_sequence` attribute attached.
/// 
///     Named sequences may include other named sequences via `transform.include`,
///     but recursion is *not* allowed.
class NamedSequenceOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Returns the number of payload objects associated with the argument
/// Given an argument, handle or parameter, returns a new parameter associated
///     with a single 64-bit number that corresponds to the number of payload
///     objects (operations or values for a handle, attributes for a parameter)
///     associated with the argument.
/// 
///     Always succeeds.
class NumAssociationsOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Produces a new transform dialect parameter value associated with the given attribute
/// Produces a new transform dialect parameter associated with the singleton
///     list containing the given attribute. The operation itself always succeeds,
///     but the general association check may fail if the parameter type does not
///     accept the given kind of attribute as valid.
class ParamConstantOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Dump each payload op
/// Prints each payload op that is associated with the `target` operand to
///     `stdout`. It also prints the `name` string attribute. If no target is
///     specified, the top-level op is dumped.
/// 
///     This op is useful for printf-style debugging.
/// 
///     Supported printing flag attributes:
///     * `assume_verified` -- skips verification when the unit attribute is
///       specified. This improves performace but may lead to crashes and
///       unexpected behavior when the printed payload op is invalid.
///     * `use_local_scope` -- prints in local scope when the unit attribute is
///       specified. This improves performance but may not be identical to
///       printing within the full module.
///     * `skip_regions` -- does not print regions of operations when the unit
///       attribute is specified.
class PrintOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Lists payload ops multiple times in the new handle
/// Produces a new handle associated with a list of payload IR ops that is
///     computed by repeating the list of payload IR ops associated with the
///     operand handle as many times as the "pattern" handle has associated
///     operations. For example, if pattern is associated with [op1, op2] and the
///     operand handle is associated with [op3, op4, op5], the resulting handle
///     will be associated with [op3, op4, op5, op3, op4, op5].
/// 
///     This transformation is useful to "align" the sizes of payload IR lists
///     before a transformation that expects, e.g., identically-sized lists. For
///     example, a transformation may be parameterized by same notional per-target
///     size computed at runtime and supplied as another handle, the replication
///     allows this size to be computed only once and used for every target instead
///     of replicating the computation itself.
/// 
///     Note that it is undesirable to pass a handle with duplicate operations to
///     an operation that consumes the handle. Handle consumption often indicates
///     that the associated payload IR ops are destroyed, so having the same op
///     listed more than once will lead to double-free. Single-operand
///     MergeHandlesOp may be used to deduplicate the associated list of payload IR
///     ops when necessary. Furthermore, a combination of ReplicateOp and
///     MergeHandlesOp can be used to construct arbitrary lists with repetitions.
class ReplicateOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Select payload ops by name
/// The handle defined by this Transform op corresponds to all operations among
///     `target` that have the specified properties. Currently the following
///     properties are supported:
/// 
///     - `op_name`: The op must have the specified name.
/// 
///     The result payload ops are in the same relative order as the targeted ops.
///     This transform op reads the `target` handle and produces the `result`
///     handle. It reads the payload, but does not modify it.
class SelectOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Contains a sequence of other transform ops to apply
/// The transformations indicated by the sequence are applied in order of their
///     appearance. Each value produced by a transformation within the sequence
///     corresponds to a group of operations or values in the payload IR, or to a
///     group of parameters, depending on the type of the value. The behavior of the
///     operation when a nested transformation produces a silenceable error is
///     controlled by the `failure_propagation_mode` attribute. When set to
///     `propagate`, the failure of any nested transformation in the sequence
///     implies immediate failure of the entire sequence with a silenceable error,
///     and no further transformation is attempted. When set to `suppress`,
///     silenceable errors in nested operations are ignored and further
///     transformations are applied. Beware that even silenceable errors may leave
///     the payload IR in a state unsuitable for further transformations. It is the
///     responsibility of the caller to ensure the following transformations are
///     robust enough when errors are suppressed. Definite errors reported by nested
///     transformations abort the sequence regardless of the propagation mode. The
///     set of modes may be extended in the future, e.g., to collect silenceable
///     errors and report them after attempting all transformations in the sequence.
/// 
///     The entry block of this operation has a single argument that maps to either
///     the operand if provided or the top-level container operation of the payload
///     IR, typically the root operation of the pass interpreting the transform
///     dialect. Operand omission is only allowed for sequences not contained in
///     another sequence.
/// 
///     The type of the block argument must match the type of the operand. If the
///     sequence is a top-level transform (without an operand), it can be used for
///     matching operations if the specified type within the top-level container
///     payload IR (including the container op itself). E.g.:
/// 
///     ```mlir
///     transform.sequence failures(propagate) {
///     ^bb1(%arg1: !transform.any_op):
///       // %arg1 is mapped to the top-level container of the payload IR, which is
///       // typically a module
///     }
/// 
///     transform.sequence failures(propagate) {
///     ^bb1(%arg1: !transform.op<"func.func>"):
///       // %arg1 is mapped to all "func.func" ops within and including the
///       // top-level container of the payload IR. Nested operations that have the
///       // specified op type are not included.
///     }
///     ```
/// 
///     The body of the sequence terminates with an implicit or explicit
///     `transform.yield` op. The operands of the terminator are returned as the
///     results of the sequence op.
class SequenceOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Splits a handle or parameter into multiple values
/// Splits `handle` into one or multiple handles, as specified by the number
///     of results of this operation. `handle` should be mapped to as many payload
///     ops, values or parameteres as there are results. Otherwise, this transform
///     will fail producing a silenceable failure by default. Each result handle
///     is mapped to exactly one payload unless specified otherwise by attributes
///     described below. The order of the payloads is preserved,  i.e., the i-th
///     payload is mapped to the i-th result handle.
/// 
///     This operation is useful for ensuring a statically known number of
///     payloads are tracked by the source `handle` and to extract them into
///     individual handles that can be further manipulated in isolation.
/// 
///     If there are more payloads than results, the remaining payloads are mapped to
///     the result with index `overflow_result`. If no `overflow_result` is
///     specified, the transform produces a silenceable failure.
/// 
///     If there are fewer payload ops than results, the transform produces a
///     silenceable failure if `fail_on_payload_too_small` is set to "true".
///     Otherwise, it succeeds and the remaining result handles are not mapped to
///     anything. It also succeeds if `handle` is empty and
///     `pass_through_empty_handle` is set to "true", regardless of
///     `fail_on_payload_too_small`.
class SplitHandleOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Verifies the targeted ops
/// This transform verifies the targeted ops. If at least one op fails to
///     verify, the transform produces a definite failure.
/// 
///     Note: This op was designed for debugging purposes and should be used like an
///     assertion. It is intentional that this op produces a definite failure and
///     not a silenceable one. Correctness of the program should not depend on this
///     op.
/// 
///     This transform reads the target handle.
class VerifyOp;

} // namespace mlir::transform
namespace mlir::transform {

/// Yields operation handles from a transform IR region
/// This terminator operation yields operation handles from regions of the
///     transform IR ops back to the containing op. It is not itself associated with
///     any transformation on the payload IR and is used for flow purposes only.
class YieldOp;

} // namespace mlir::transform
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::AlternativesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AlternativesOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AlternativesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.alternatives", odsAttrs.getContext());
  }

  AlternativesOpGenericAdaptorBase(AlternativesOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::RegionRange getAlternatives() {
    return odsRegions.drop_front(0);
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class AlternativesOpGenericAdaptor : public detail::AlternativesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AlternativesOpGenericAdaptorBase;
  static constexpr int odsIndex_scope = 0;
public:
  AlternativesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AlternativesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AlternativesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AlternativesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AlternativesOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AlternativesOpGenericAdaptor(RangeT values, const AlternativesOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AlternativesOp, typename = std::enable_if_t<std::is_same_v<LateInst, AlternativesOp>>>
  AlternativesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getScope() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AlternativesOpAdaptor : public AlternativesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AlternativesOpGenericAdaptor::AlternativesOpGenericAdaptor;
  AlternativesOpAdaptor(AlternativesOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AlternativesOp : public ::mlir::Op<AlternativesOp, ::mlir::OpTrait::VariadicRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<::mlir::transform::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::RegionBranchOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::transform::PossibleTopLevelTransformOpTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AlternativesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AlternativesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_scope = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchOpInterface::Trait<AlternativesOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<AlternativesOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<AlternativesOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<AlternativesOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<AlternativesOp>::areTypesCompatible;
  using ::mlir::transform::TransformOpInterface::Trait<AlternativesOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.alternatives");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getScope() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>{} : ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getScopeMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
  }

  ::mlir::MutableArrayRef<::mlir::Region> getAlternatives() {
    return (*this)->getRegions().drop_front(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, /*optional*/::mlir::Value scope, unsigned alternativesCount);
  static AlternativesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, /*optional*/::mlir::Value scope, unsigned alternativesCount);
  static AlternativesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, /*optional*/::mlir::Value scope, unsigned alternativesCount);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static AlternativesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static AlternativesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  static AlternativesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  static AlternativesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OperandRange getEntrySuccessorOperands(::mlir::RegionSuccessor successor);
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);
  void getRegionInvocationBounds(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> &invocationBounds);
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::AlternativesOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::AnnotateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AnnotateOpGenericAdaptorBase {
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
  AnnotateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.annotate", odsAttrs.getContext());
  }

  AnnotateOpGenericAdaptorBase(AnnotateOp op);

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
class AnnotateOpGenericAdaptor : public detail::AnnotateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AnnotateOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
  static constexpr int odsIndex_param = 1;
public:
  AnnotateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AnnotateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AnnotateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AnnotateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AnnotateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AnnotateOpGenericAdaptor(RangeT values, const AnnotateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AnnotateOp, typename = std::enable_if_t<std::is_same_v<LateInst, AnnotateOp>>>
  AnnotateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  ValueT getParam() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AnnotateOpAdaptor : public AnnotateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AnnotateOpGenericAdaptor::AnnotateOpGenericAdaptor;
  AnnotateOpAdaptor(AnnotateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AnnotateOp : public ::mlir::Op<AnnotateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AnnotateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AnnotateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  static constexpr int odsIndex_param = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<AnnotateOp>::allowsRepeatedHandleOperands;
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
    return ::llvm::StringLiteral("transform.annotate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface> getParam() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface>{} : ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface>>(*operands.begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getParamMutable();
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value target, ::mlir::StringAttr name, /*optional*/::mlir::Value param);
  static AnnotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value target, ::mlir::StringAttr name, /*optional*/::mlir::Value param);
  static AnnotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value target, ::mlir::StringAttr name, /*optional*/::mlir::Value param);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::StringAttr name, /*optional*/::mlir::Value param);
  static AnnotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::StringAttr name, /*optional*/::mlir::Value param);
  static AnnotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::StringAttr name, /*optional*/::mlir::Value param);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value target, ::llvm::StringRef name, /*optional*/::mlir::Value param);
  static AnnotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value target, ::llvm::StringRef name, /*optional*/::mlir::Value param);
  static AnnotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value target, ::llvm::StringRef name, /*optional*/::mlir::Value param);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::StringRef name, /*optional*/::mlir::Value param);
  static AnnotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::StringRef name, /*optional*/::mlir::Value param);
  static AnnotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::StringRef name, /*optional*/::mlir::Value param);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AnnotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AnnotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AnnotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AnnotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::AnnotateOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ApplyCanonicalizationPatternsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyCanonicalizationPatternsOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ApplyCanonicalizationPatternsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.apply_patterns.canonicalization", odsAttrs.getContext());
  }

  ApplyCanonicalizationPatternsOpGenericAdaptorBase(ApplyCanonicalizationPatternsOp op);

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
class ApplyCanonicalizationPatternsOpGenericAdaptor : public detail::ApplyCanonicalizationPatternsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyCanonicalizationPatternsOpGenericAdaptorBase;
public:
  ApplyCanonicalizationPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyCanonicalizationPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyCanonicalizationPatternsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyCanonicalizationPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyCanonicalizationPatternsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyCanonicalizationPatternsOpGenericAdaptor(RangeT values, const ApplyCanonicalizationPatternsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyCanonicalizationPatternsOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyCanonicalizationPatternsOp>>>
  ApplyCanonicalizationPatternsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ApplyCanonicalizationPatternsOpAdaptor : public ApplyCanonicalizationPatternsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyCanonicalizationPatternsOpGenericAdaptor::ApplyCanonicalizationPatternsOpGenericAdaptor;
  ApplyCanonicalizationPatternsOpAdaptor(ApplyCanonicalizationPatternsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyCanonicalizationPatternsOp : public ::mlir::Op<ApplyCanonicalizationPatternsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::transform::PatternDescriptorOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyCanonicalizationPatternsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyCanonicalizationPatternsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::PatternDescriptorOpInterface::Trait<ApplyCanonicalizationPatternsOp>::populatePatternsWithState;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.apply_patterns.canonicalization");
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
  static ApplyCanonicalizationPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static ApplyCanonicalizationPatternsOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static ApplyCanonicalizationPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static ApplyCanonicalizationPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyCanonicalizationPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyCanonicalizationPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyCanonicalizationPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyCanonicalizationPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void populatePatterns(::mlir::RewritePatternSet &patterns);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ApplyCanonicalizationPatternsOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ApplyCommonSubexpressionEliminationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyCommonSubexpressionEliminationOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ApplyCommonSubexpressionEliminationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.apply_cse", odsAttrs.getContext());
  }

  ApplyCommonSubexpressionEliminationOpGenericAdaptorBase(ApplyCommonSubexpressionEliminationOp op);

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
class ApplyCommonSubexpressionEliminationOpGenericAdaptor : public detail::ApplyCommonSubexpressionEliminationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyCommonSubexpressionEliminationOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  ApplyCommonSubexpressionEliminationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyCommonSubexpressionEliminationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyCommonSubexpressionEliminationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyCommonSubexpressionEliminationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyCommonSubexpressionEliminationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyCommonSubexpressionEliminationOpGenericAdaptor(RangeT values, const ApplyCommonSubexpressionEliminationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyCommonSubexpressionEliminationOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyCommonSubexpressionEliminationOp>>>
  ApplyCommonSubexpressionEliminationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ApplyCommonSubexpressionEliminationOpAdaptor : public ApplyCommonSubexpressionEliminationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyCommonSubexpressionEliminationOpGenericAdaptor::ApplyCommonSubexpressionEliminationOpGenericAdaptor;
  ApplyCommonSubexpressionEliminationOpAdaptor(ApplyCommonSubexpressionEliminationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyCommonSubexpressionEliminationOp : public ::mlir::Op<ApplyCommonSubexpressionEliminationOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::TransformEachOpTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::ReportTrackingListenerFailuresOpTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyCommonSubexpressionEliminationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyCommonSubexpressionEliminationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.apply_cse");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value target);
  static ApplyCommonSubexpressionEliminationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value target);
  static ApplyCommonSubexpressionEliminationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value target);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static ApplyCommonSubexpressionEliminationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static ApplyCommonSubexpressionEliminationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyCommonSubexpressionEliminationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyCommonSubexpressionEliminationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyCommonSubexpressionEliminationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyCommonSubexpressionEliminationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  ::mlir::DiagnosedSilenceableFailure applyToOne(
    ::mlir::transform::TransformRewriter &rewriter,
    ::mlir::Operation *target,
    ::mlir::transform::ApplyToEachResultList &results,
    ::mlir::transform::TransformState &state);
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ApplyCommonSubexpressionEliminationOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ApplyConversionPatternsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyConversionPatternsOpGenericAdaptorBase {
public:
  struct Properties {
    using illegal_dialectsTy = ::mlir::ArrayAttr;
    illegal_dialectsTy illegal_dialects;

    auto getIllegalDialects() const {
      auto &propStorage = this->illegal_dialects;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setIllegalDialects(const ::mlir::ArrayAttr &propValue) {
      this->illegal_dialects = propValue;
    }
    using illegal_opsTy = ::mlir::ArrayAttr;
    illegal_opsTy illegal_ops;

    auto getIllegalOps() const {
      auto &propStorage = this->illegal_ops;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setIllegalOps(const ::mlir::ArrayAttr &propValue) {
      this->illegal_ops = propValue;
    }
    using legal_dialectsTy = ::mlir::ArrayAttr;
    legal_dialectsTy legal_dialects;

    auto getLegalDialects() const {
      auto &propStorage = this->legal_dialects;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setLegalDialects(const ::mlir::ArrayAttr &propValue) {
      this->legal_dialects = propValue;
    }
    using legal_opsTy = ::mlir::ArrayAttr;
    legal_opsTy legal_ops;

    auto getLegalOps() const {
      auto &propStorage = this->legal_ops;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setLegalOps(const ::mlir::ArrayAttr &propValue) {
      this->legal_ops = propValue;
    }
    using partial_conversionTy = ::mlir::UnitAttr;
    partial_conversionTy partial_conversion;

    auto getPartialConversion() const {
      auto &propStorage = this->partial_conversion;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPartialConversion(const ::mlir::UnitAttr &propValue) {
      this->partial_conversion = propValue;
    }
    using preserve_handlesTy = ::mlir::UnitAttr;
    preserve_handlesTy preserve_handles;

    auto getPreserveHandles() const {
      auto &propStorage = this->preserve_handles;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPreserveHandles(const ::mlir::UnitAttr &propValue) {
      this->preserve_handles = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.illegal_dialects == this->illegal_dialects &&
        rhs.illegal_ops == this->illegal_ops &&
        rhs.legal_dialects == this->legal_dialects &&
        rhs.legal_ops == this->legal_ops &&
        rhs.partial_conversion == this->partial_conversion &&
        rhs.preserve_handles == this->preserve_handles &&
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
  ApplyConversionPatternsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.apply_conversion_patterns", odsAttrs.getContext());
  }

  ApplyConversionPatternsOpGenericAdaptorBase(ApplyConversionPatternsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getLegalOpsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().legal_ops);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getLegalOps();
  ::mlir::ArrayAttr getIllegalOpsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().illegal_ops);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getIllegalOps();
  ::mlir::ArrayAttr getLegalDialectsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().legal_dialects);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getLegalDialects();
  ::mlir::ArrayAttr getIllegalDialectsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().illegal_dialects);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getIllegalDialects();
  ::mlir::UnitAttr getPartialConversionAttr();
  bool getPartialConversion();
  ::mlir::UnitAttr getPreserveHandlesAttr();
  bool getPreserveHandles();
  ::mlir::Region &getPatterns() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getDefaultTypeConverterRegion() {
    return odsRegions.drop_front(1);
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ApplyConversionPatternsOpGenericAdaptor : public detail::ApplyConversionPatternsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyConversionPatternsOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  ApplyConversionPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyConversionPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyConversionPatternsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyConversionPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyConversionPatternsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyConversionPatternsOpGenericAdaptor(RangeT values, const ApplyConversionPatternsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyConversionPatternsOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyConversionPatternsOp>>>
  ApplyConversionPatternsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ApplyConversionPatternsOpAdaptor : public ApplyConversionPatternsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyConversionPatternsOpGenericAdaptor::ApplyConversionPatternsOpGenericAdaptor;
  ApplyConversionPatternsOpAdaptor(ApplyConversionPatternsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyConversionPatternsOp : public ::mlir::Op<ApplyConversionPatternsOp, ::mlir::OpTrait::AtLeastNRegions<1>::Impl, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::ReportTrackingListenerFailuresOpTrait, ::mlir::RegionKindInterface::Trait, ::mlir::OpTrait::HasOnlyGraphRegion> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyConversionPatternsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyConversionPatternsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<ApplyConversionPatternsOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("illegal_dialects"), ::llvm::StringRef("illegal_ops"), ::llvm::StringRef("legal_dialects"), ::llvm::StringRef("legal_ops"), ::llvm::StringRef("partial_conversion"), ::llvm::StringRef("preserve_handles")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIllegalDialectsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIllegalDialectsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIllegalOpsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIllegalOpsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getLegalDialectsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getLegalDialectsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getLegalOpsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getLegalOpsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getPartialConversionAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getPartialConversionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getPreserveHandlesAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getPreserveHandlesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.apply_conversion_patterns");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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

  ::mlir::Region &getPatterns() {
    return (*this)->getRegion(0);
  }

  ::mlir::MutableArrayRef<::mlir::Region> getDefaultTypeConverterRegion() {
    return (*this)->getRegions().drop_front(1);
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
  ::mlir::ArrayAttr getLegalOpsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().legal_ops);
  }

  ::std::optional< ::mlir::ArrayAttr > getLegalOps();
  ::mlir::ArrayAttr getIllegalOpsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().illegal_ops);
  }

  ::std::optional< ::mlir::ArrayAttr > getIllegalOps();
  ::mlir::ArrayAttr getLegalDialectsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().legal_dialects);
  }

  ::std::optional< ::mlir::ArrayAttr > getLegalDialects();
  ::mlir::ArrayAttr getIllegalDialectsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().illegal_dialects);
  }

  ::std::optional< ::mlir::ArrayAttr > getIllegalDialects();
  ::mlir::UnitAttr getPartialConversionAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().partial_conversion);
  }

  bool getPartialConversion();
  ::mlir::UnitAttr getPreserveHandlesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().preserve_handles);
  }

  bool getPreserveHandles();
  void setLegalOpsAttr(::mlir::ArrayAttr attr) {
    getProperties().legal_ops = attr;
  }

  void setIllegalOpsAttr(::mlir::ArrayAttr attr) {
    getProperties().illegal_ops = attr;
  }

  void setLegalDialectsAttr(::mlir::ArrayAttr attr) {
    getProperties().legal_dialects = attr;
  }

  void setIllegalDialectsAttr(::mlir::ArrayAttr attr) {
    getProperties().illegal_dialects = attr;
  }

  void setPartialConversionAttr(::mlir::UnitAttr attr) {
    getProperties().partial_conversion = attr;
  }

  void setPartialConversion(bool attrValue);
  void setPreserveHandlesAttr(::mlir::UnitAttr attr) {
    getProperties().preserve_handles = attr;
  }

  void setPreserveHandles(bool attrValue);
  ::mlir::Attribute removeLegalOpsAttr() {
      auto attr = getProperties().legal_ops;
      getProperties().legal_ops = {};
      return attr;
  }

  ::mlir::Attribute removeIllegalOpsAttr() {
      auto attr = getProperties().illegal_ops;
      getProperties().illegal_ops = {};
      return attr;
  }

  ::mlir::Attribute removeLegalDialectsAttr() {
      auto attr = getProperties().legal_dialects;
      getProperties().legal_dialects = {};
      return attr;
  }

  ::mlir::Attribute removeIllegalDialectsAttr() {
      auto attr = getProperties().illegal_dialects;
      getProperties().illegal_dialects = {};
      return attr;
  }

  ::mlir::Attribute removePartialConversionAttr() {
      auto attr = getProperties().partial_conversion;
      getProperties().partial_conversion = {};
      return attr;
  }

  ::mlir::Attribute removePreserveHandlesAttr() {
      auto attr = getProperties().preserve_handles;
      getProperties().preserve_handles = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value target, function_ref<void(OpBuilder &, Location)> patternsBodyBuilder = nullptr, function_ref<void(OpBuilder &, Location)> typeConverterBodyBuilder = nullptr);
  static ApplyConversionPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value target, function_ref<void(OpBuilder &, Location)> patternsBodyBuilder = nullptr, function_ref<void(OpBuilder &, Location)> typeConverterBodyBuilder = nullptr);
  static ApplyConversionPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, Value target, function_ref<void(OpBuilder &, Location)> patternsBodyBuilder = nullptr, function_ref<void(OpBuilder &, Location)> typeConverterBodyBuilder = nullptr);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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
  ::mlir::transform::TypeConverterBuilderOpInterface getDefaultTypeConverter() {
    if (getDefaultTypeConverterRegion().size() == 0)
      return {};
    return ::llvm::cast<::mlir::transform::TypeConverterBuilderOpInterface>(
        &getDefaultTypeConverterRegion()[0].front().front());
  }
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ApplyConversionPatternsOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ApplyDeadCodeEliminationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyDeadCodeEliminationOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ApplyDeadCodeEliminationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.apply_dce", odsAttrs.getContext());
  }

  ApplyDeadCodeEliminationOpGenericAdaptorBase(ApplyDeadCodeEliminationOp op);

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
class ApplyDeadCodeEliminationOpGenericAdaptor : public detail::ApplyDeadCodeEliminationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyDeadCodeEliminationOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  ApplyDeadCodeEliminationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyDeadCodeEliminationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyDeadCodeEliminationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyDeadCodeEliminationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyDeadCodeEliminationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyDeadCodeEliminationOpGenericAdaptor(RangeT values, const ApplyDeadCodeEliminationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyDeadCodeEliminationOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyDeadCodeEliminationOp>>>
  ApplyDeadCodeEliminationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ApplyDeadCodeEliminationOpAdaptor : public ApplyDeadCodeEliminationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyDeadCodeEliminationOpGenericAdaptor::ApplyDeadCodeEliminationOpGenericAdaptor;
  ApplyDeadCodeEliminationOpAdaptor(ApplyDeadCodeEliminationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyDeadCodeEliminationOp : public ::mlir::Op<ApplyDeadCodeEliminationOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::TransformEachOpTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::ReportTrackingListenerFailuresOpTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyDeadCodeEliminationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyDeadCodeEliminationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.apply_dce");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value target);
  static ApplyDeadCodeEliminationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value target);
  static ApplyDeadCodeEliminationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value target);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static ApplyDeadCodeEliminationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static ApplyDeadCodeEliminationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyDeadCodeEliminationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyDeadCodeEliminationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyDeadCodeEliminationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyDeadCodeEliminationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  ::mlir::DiagnosedSilenceableFailure applyToOne(
    ::mlir::transform::TransformRewriter &rewriter,
    ::mlir::Operation *target,
    ::mlir::transform::ApplyToEachResultList &results,
    ::mlir::transform::TransformState &state);
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ApplyDeadCodeEliminationOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ApplyLoopInvariantCodeMotionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyLoopInvariantCodeMotionOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ApplyLoopInvariantCodeMotionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.apply_licm", odsAttrs.getContext());
  }

  ApplyLoopInvariantCodeMotionOpGenericAdaptorBase(ApplyLoopInvariantCodeMotionOp op);

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
class ApplyLoopInvariantCodeMotionOpGenericAdaptor : public detail::ApplyLoopInvariantCodeMotionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyLoopInvariantCodeMotionOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  ApplyLoopInvariantCodeMotionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyLoopInvariantCodeMotionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyLoopInvariantCodeMotionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyLoopInvariantCodeMotionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyLoopInvariantCodeMotionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyLoopInvariantCodeMotionOpGenericAdaptor(RangeT values, const ApplyLoopInvariantCodeMotionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyLoopInvariantCodeMotionOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyLoopInvariantCodeMotionOp>>>
  ApplyLoopInvariantCodeMotionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ApplyLoopInvariantCodeMotionOpAdaptor : public ApplyLoopInvariantCodeMotionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyLoopInvariantCodeMotionOpGenericAdaptor::ApplyLoopInvariantCodeMotionOpGenericAdaptor;
  ApplyLoopInvariantCodeMotionOpAdaptor(ApplyLoopInvariantCodeMotionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyLoopInvariantCodeMotionOp : public ::mlir::Op<ApplyLoopInvariantCodeMotionOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::TransformEachOpTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::ReportTrackingListenerFailuresOpTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyLoopInvariantCodeMotionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyLoopInvariantCodeMotionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.apply_licm");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value target);
  static ApplyLoopInvariantCodeMotionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value target);
  static ApplyLoopInvariantCodeMotionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value target);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static ApplyLoopInvariantCodeMotionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static ApplyLoopInvariantCodeMotionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyLoopInvariantCodeMotionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyLoopInvariantCodeMotionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyLoopInvariantCodeMotionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyLoopInvariantCodeMotionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  ::mlir::DiagnosedSilenceableFailure applyToOne(
    ::mlir::transform::TransformRewriter &rewriter,
    ::mlir::LoopLikeOpInterface target,
    ::mlir::transform::ApplyToEachResultList &results,
    ::mlir::transform::TransformState &state);
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ApplyLoopInvariantCodeMotionOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ApplyPatternsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyPatternsOpGenericAdaptorBase {
public:
  struct Properties {
    using apply_cseTy = ::mlir::UnitAttr;
    apply_cseTy apply_cse;

    auto getApplyCse() const {
      auto &propStorage = this->apply_cse;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setApplyCse(const ::mlir::UnitAttr &propValue) {
      this->apply_cse = propValue;
    }
    using max_iterationsTy = ::mlir::IntegerAttr;
    max_iterationsTy max_iterations;

    auto getMaxIterations() const {
      auto &propStorage = this->max_iterations;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setMaxIterations(const ::mlir::IntegerAttr &propValue) {
      this->max_iterations = propValue;
    }
    using max_num_rewritesTy = ::mlir::IntegerAttr;
    max_num_rewritesTy max_num_rewrites;

    auto getMaxNumRewrites() const {
      auto &propStorage = this->max_num_rewrites;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setMaxNumRewrites(const ::mlir::IntegerAttr &propValue) {
      this->max_num_rewrites = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.apply_cse == this->apply_cse &&
        rhs.max_iterations == this->max_iterations &&
        rhs.max_num_rewrites == this->max_num_rewrites &&
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
  ApplyPatternsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.apply_patterns", odsAttrs.getContext());
  }

  ApplyPatternsOpGenericAdaptorBase(ApplyPatternsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getApplyCseAttr();
  bool getApplyCse();
  ::mlir::IntegerAttr getMaxIterationsAttr();
  uint64_t getMaxIterations();
  ::mlir::IntegerAttr getMaxNumRewritesAttr();
  uint64_t getMaxNumRewrites();
  ::mlir::Region &getPatterns() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ApplyPatternsOpGenericAdaptor : public detail::ApplyPatternsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyPatternsOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  ApplyPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyPatternsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyPatternsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyPatternsOpGenericAdaptor(RangeT values, const ApplyPatternsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyPatternsOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyPatternsOp>>>
  ApplyPatternsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ApplyPatternsOpAdaptor : public ApplyPatternsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyPatternsOpGenericAdaptor::ApplyPatternsOpGenericAdaptor;
  ApplyPatternsOpAdaptor(ApplyPatternsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyPatternsOp : public ::mlir::Op<ApplyPatternsOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::TransformEachOpTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::ReportTrackingListenerFailuresOpTrait, ::mlir::RegionKindInterface::Trait, ::mlir::OpTrait::HasOnlyGraphRegion> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyPatternsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyPatternsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("apply_cse"), ::llvm::StringRef("max_iterations"), ::llvm::StringRef("max_num_rewrites")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getApplyCseAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getApplyCseAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getMaxIterationsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getMaxIterationsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getMaxNumRewritesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getMaxNumRewritesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.apply_patterns");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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

  ::mlir::Region &getPatterns() {
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
  ::mlir::UnitAttr getApplyCseAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().apply_cse);
  }

  bool getApplyCse();
  ::mlir::IntegerAttr getMaxIterationsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().max_iterations);
  }

  uint64_t getMaxIterations();
  ::mlir::IntegerAttr getMaxNumRewritesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().max_num_rewrites);
  }

  uint64_t getMaxNumRewrites();
  void setApplyCseAttr(::mlir::UnitAttr attr) {
    getProperties().apply_cse = attr;
  }

  void setApplyCse(bool attrValue);
  void setMaxIterationsAttr(::mlir::IntegerAttr attr) {
    getProperties().max_iterations = attr;
  }

  void setMaxIterations(uint64_t attrValue);
  void setMaxNumRewritesAttr(::mlir::IntegerAttr attr) {
    getProperties().max_num_rewrites = attr;
  }

  void setMaxNumRewrites(uint64_t attrValue);
  ::mlir::Attribute removeApplyCseAttr() {
      auto attr = getProperties().apply_cse;
      getProperties().apply_cse = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value target, function_ref<void(OpBuilder &, Location)> bodyBuilder = nullptr);
  static ApplyPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value target, function_ref<void(OpBuilder &, Location)> bodyBuilder = nullptr);
  static ApplyPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, Value target, function_ref<void(OpBuilder &, Location)> bodyBuilder = nullptr);
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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
  ::mlir::DiagnosedSilenceableFailure applyToOne(
    ::mlir::transform::TransformRewriter &rewriter,
    ::mlir::Operation *target,
    ::mlir::transform::ApplyToEachResultList &results,
    ::mlir::transform::TransformState &state);
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ApplyPatternsOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ApplyRegisteredPassOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyRegisteredPassOpGenericAdaptorBase {
public:
  struct Properties {
    using optionsTy = ::mlir::DictionaryAttr;
    optionsTy options;

    auto getOptions() const {
      auto &propStorage = this->options;
      return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(propStorage);
    }
    void setOptions(const ::mlir::DictionaryAttr &propValue) {
      this->options = propValue;
    }
    using pass_nameTy = ::mlir::StringAttr;
    pass_nameTy pass_name;

    auto getPassName() const {
      auto &propStorage = this->pass_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setPassName(const ::mlir::StringAttr &propValue) {
      this->pass_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.options == this->options &&
        rhs.pass_name == this->pass_name &&
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
  ApplyRegisteredPassOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.apply_registered_pass", odsAttrs.getContext());
  }

  ApplyRegisteredPassOpGenericAdaptorBase(ApplyRegisteredPassOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getPassNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().pass_name);
    return attr;
  }

  ::llvm::StringRef getPassName();
  ::mlir::DictionaryAttr getOptionsAttr();
  ::mlir::DictionaryAttr getOptions();
};

} // namespace detail
template <typename RangeT>
class ApplyRegisteredPassOpGenericAdaptor : public detail::ApplyRegisteredPassOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyRegisteredPassOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
  static constexpr int odsIndex_dynamic_options = 1;
public:
  ApplyRegisteredPassOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyRegisteredPassOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyRegisteredPassOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyRegisteredPassOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyRegisteredPassOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyRegisteredPassOpGenericAdaptor(RangeT values, const ApplyRegisteredPassOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyRegisteredPassOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyRegisteredPassOp>>>
  ApplyRegisteredPassOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getDynamicOptions() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ApplyRegisteredPassOpAdaptor : public ApplyRegisteredPassOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyRegisteredPassOpGenericAdaptor::ApplyRegisteredPassOpGenericAdaptor;
  ApplyRegisteredPassOpAdaptor(ApplyRegisteredPassOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyRegisteredPassOp : public ::mlir::Op<ApplyRegisteredPassOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformHandleTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyRegisteredPassOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyRegisteredPassOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  static constexpr int odsIndex_dynamic_options = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<ApplyRegisteredPassOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("options"), ::llvm::StringRef("pass_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOptionsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOptionsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPassNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPassNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.apply_registered_pass");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getDynamicOptions() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getTargetMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDynamicOptionsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSResults(0).begin());
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
  ::mlir::StringAttr getPassNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().pass_name);
  }

  ::llvm::StringRef getPassName();
  ::mlir::DictionaryAttr getOptionsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().options);
  }

  ::mlir::DictionaryAttr getOptions();
  void setPassNameAttr(::mlir::StringAttr attr) {
    getProperties().pass_name = attr;
  }

  void setPassName(::llvm::StringRef attrValue);
  void setOptionsAttr(::mlir::DictionaryAttr attr) {
    getProperties().options = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value target, ::mlir::StringAttr pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static ApplyRegisteredPassOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value target, ::mlir::StringAttr pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static ApplyRegisteredPassOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value target, ::mlir::StringAttr pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::StringAttr pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static ApplyRegisteredPassOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::StringAttr pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static ApplyRegisteredPassOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::StringAttr pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value target, ::llvm::StringRef pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static ApplyRegisteredPassOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value target, ::llvm::StringRef pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static ApplyRegisteredPassOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value target, ::llvm::StringRef pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::StringRef pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static ApplyRegisteredPassOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::StringRef pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static ApplyRegisteredPassOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::StringRef pass_name, ::mlir::DictionaryAttr options, ::mlir::ValueRange dynamic_options);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyRegisteredPassOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyRegisteredPassOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyRegisteredPassOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyRegisteredPassOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ApplyRegisteredPassOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ApplyToLLVMConversionPatternsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ApplyToLLVMConversionPatternsOpGenericAdaptorBase {
public:
  struct Properties {
    using dialect_nameTy = ::mlir::StringAttr;
    dialect_nameTy dialect_name;

    auto getDialectName() const {
      auto &propStorage = this->dialect_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setDialectName(const ::mlir::StringAttr &propValue) {
      this->dialect_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dialect_name == this->dialect_name &&
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
  ApplyToLLVMConversionPatternsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.apply_conversion_patterns.dialect_to_llvm", odsAttrs.getContext());
  }

  ApplyToLLVMConversionPatternsOpGenericAdaptorBase(ApplyToLLVMConversionPatternsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getDialectNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().dialect_name);
    return attr;
  }

  ::llvm::StringRef getDialectName();
};

} // namespace detail
template <typename RangeT>
class ApplyToLLVMConversionPatternsOpGenericAdaptor : public detail::ApplyToLLVMConversionPatternsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ApplyToLLVMConversionPatternsOpGenericAdaptorBase;
public:
  ApplyToLLVMConversionPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ApplyToLLVMConversionPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ApplyToLLVMConversionPatternsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ApplyToLLVMConversionPatternsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ApplyToLLVMConversionPatternsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ApplyToLLVMConversionPatternsOpGenericAdaptor(RangeT values, const ApplyToLLVMConversionPatternsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ApplyToLLVMConversionPatternsOp, typename = std::enable_if_t<std::is_same_v<LateInst, ApplyToLLVMConversionPatternsOp>>>
  ApplyToLLVMConversionPatternsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ApplyToLLVMConversionPatternsOpAdaptor : public ApplyToLLVMConversionPatternsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ApplyToLLVMConversionPatternsOpGenericAdaptor::ApplyToLLVMConversionPatternsOpGenericAdaptor;
  ApplyToLLVMConversionPatternsOpAdaptor(ApplyToLLVMConversionPatternsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ApplyToLLVMConversionPatternsOp : public ::mlir::Op<ApplyToLLVMConversionPatternsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::ConversionPatternDescriptorOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ApplyToLLVMConversionPatternsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ApplyToLLVMConversionPatternsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::ConversionPatternDescriptorOpInterface::Trait<ApplyToLLVMConversionPatternsOp>::populateConversionTargetRules;
  using ::mlir::transform::ConversionPatternDescriptorOpInterface::Trait<ApplyToLLVMConversionPatternsOp>::getTypeConverter;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dialect_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDialectNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDialectNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.apply_conversion_patterns.dialect_to_llvm");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getDialectNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().dialect_name);
  }

  ::llvm::StringRef getDialectName();
  void setDialectNameAttr(::mlir::StringAttr attr) {
    getProperties().dialect_name = attr;
  }

  void setDialectName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr dialect_name);
  static ApplyToLLVMConversionPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr dialect_name);
  static ApplyToLLVMConversionPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr dialect_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr dialect_name);
  static ApplyToLLVMConversionPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr dialect_name);
  static ApplyToLLVMConversionPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr dialect_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef dialect_name);
  static ApplyToLLVMConversionPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef dialect_name);
  static ApplyToLLVMConversionPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef dialect_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef dialect_name);
  static ApplyToLLVMConversionPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef dialect_name);
  static ApplyToLLVMConversionPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef dialect_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyToLLVMConversionPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ApplyToLLVMConversionPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyToLLVMConversionPatternsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ApplyToLLVMConversionPatternsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void populatePatterns(::mlir::TypeConverter &typeConverter, ::mlir::RewritePatternSet &patterns);
  ::llvm::LogicalResult verifyTypeConverter(TypeConverterBuilderOpInterface builder);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ApplyToLLVMConversionPatternsOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::CastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.cast", odsAttrs.getContext());
  }

  CastOpGenericAdaptorBase(CastOp op);

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
class CastOpGenericAdaptor : public detail::CastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CastOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  CastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CastOpGenericAdaptor(RangeT values, const CastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CastOp, typename = std::enable_if_t<std::is_same_v<LateInst, CastOp>>>
  CastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CastOpAdaptor : public CastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CastOpGenericAdaptor::CastOpGenericAdaptor;
  CastOpAdaptor(CastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CastOp : public ::mlir::Op<CastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformHandleTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::TransformEachOpTrait, ::mlir::CastOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.cast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
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

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input);
  static CastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input);
  static CastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static CastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static CastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static bool areCastCompatible(::mlir::TypeRange inputs, ::mlir::TypeRange outputs);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  ::mlir::DiagnosedSilenceableFailure applyToOne(
    ::mlir::transform::TransformRewriter &rewriter,
    ::mlir::Operation *target,
    ::mlir::transform::ApplyToEachResultList &results,
    ::mlir::transform::TransformState &state);
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::CastOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::CollectMatchingOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CollectMatchingOpGenericAdaptorBase {
public:
  struct Properties {
    using matcherTy = ::mlir::SymbolRefAttr;
    matcherTy matcher;

    auto getMatcher() const {
      auto &propStorage = this->matcher;
      return ::llvm::cast<::mlir::SymbolRefAttr>(propStorage);
    }
    void setMatcher(const ::mlir::SymbolRefAttr &propValue) {
      this->matcher = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.matcher == this->matcher &&
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
  CollectMatchingOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.collect_matching", odsAttrs.getContext());
  }

  CollectMatchingOpGenericAdaptorBase(CollectMatchingOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::SymbolRefAttr getMatcherAttr() {
    auto attr = ::llvm::cast<::mlir::SymbolRefAttr>(getProperties().matcher);
    return attr;
  }

  ::mlir::SymbolRefAttr getMatcher();
};

} // namespace detail
template <typename RangeT>
class CollectMatchingOpGenericAdaptor : public detail::CollectMatchingOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CollectMatchingOpGenericAdaptorBase;
  static constexpr int odsIndex_root = 0;
public:
  CollectMatchingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CollectMatchingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CollectMatchingOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CollectMatchingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CollectMatchingOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CollectMatchingOpGenericAdaptor(RangeT values, const CollectMatchingOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CollectMatchingOp, typename = std::enable_if_t<std::is_same_v<LateInst, CollectMatchingOp>>>
  CollectMatchingOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRoot() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CollectMatchingOpAdaptor : public CollectMatchingOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CollectMatchingOpGenericAdaptor::CollectMatchingOpGenericAdaptor;
  CollectMatchingOpAdaptor(CollectMatchingOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CollectMatchingOp : public ::mlir::Op<CollectMatchingOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CollectMatchingOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CollectMatchingOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_root = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<CollectMatchingOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("matcher")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMatcherAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMatcherAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.collect_matching");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getRoot() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getRootMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
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
  ::mlir::SymbolRefAttr getMatcherAttr() {
    return ::llvm::cast<::mlir::SymbolRefAttr>(getProperties().matcher);
  }

  ::mlir::SymbolRefAttr getMatcher();
  void setMatcherAttr(::mlir::SymbolRefAttr attr) {
    getProperties().matcher = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value root, ::mlir::SymbolRefAttr matcher);
  static CollectMatchingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value root, ::mlir::SymbolRefAttr matcher);
  static CollectMatchingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value root, ::mlir::SymbolRefAttr matcher);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CollectMatchingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CollectMatchingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CollectMatchingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CollectMatchingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::CollectMatchingOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ForeachMatchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ForeachMatchOpGenericAdaptorBase {
public:
  struct Properties {
    using actionsTy = ::mlir::ArrayAttr;
    actionsTy actions;

    auto getActions() const {
      auto &propStorage = this->actions;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setActions(const ::mlir::ArrayAttr &propValue) {
      this->actions = propValue;
    }
    using flatten_resultsTy = ::mlir::UnitAttr;
    flatten_resultsTy flatten_results;

    auto getFlattenResults() const {
      auto &propStorage = this->flatten_results;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setFlattenResults(const ::mlir::UnitAttr &propValue) {
      this->flatten_results = propValue;
    }
    using matchersTy = ::mlir::ArrayAttr;
    matchersTy matchers;

    auto getMatchers() const {
      auto &propStorage = this->matchers;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setMatchers(const ::mlir::ArrayAttr &propValue) {
      this->matchers = propValue;
    }
    using restrict_rootTy = ::mlir::UnitAttr;
    restrict_rootTy restrict_root;

    auto getRestrictRoot() const {
      auto &propStorage = this->restrict_root;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setRestrictRoot(const ::mlir::UnitAttr &propValue) {
      this->restrict_root = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.actions == this->actions &&
        rhs.flatten_results == this->flatten_results &&
        rhs.matchers == this->matchers &&
        rhs.restrict_root == this->restrict_root &&
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
  ForeachMatchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.foreach_match", odsAttrs.getContext());
  }

  ForeachMatchOpGenericAdaptorBase(ForeachMatchOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getRestrictRootAttr();
  bool getRestrictRoot();
  ::mlir::UnitAttr getFlattenResultsAttr();
  bool getFlattenResults();
  ::mlir::ArrayAttr getMatchersAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().matchers);
    return attr;
  }

  ::mlir::ArrayAttr getMatchers();
  ::mlir::ArrayAttr getActionsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().actions);
    return attr;
  }

  ::mlir::ArrayAttr getActions();
};

} // namespace detail
template <typename RangeT>
class ForeachMatchOpGenericAdaptor : public detail::ForeachMatchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ForeachMatchOpGenericAdaptorBase;
  static constexpr int odsIndex_root = 0;
  static constexpr int odsIndex_forwarded_inputs = 1;
public:
  ForeachMatchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ForeachMatchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ForeachMatchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ForeachMatchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ForeachMatchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ForeachMatchOpGenericAdaptor(RangeT values, const ForeachMatchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ForeachMatchOp, typename = std::enable_if_t<std::is_same_v<LateInst, ForeachMatchOp>>>
  ForeachMatchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRoot() {
    return (*getODSOperands(0).begin());
  }

  RangeT getForwardedInputs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ForeachMatchOpAdaptor : public ForeachMatchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ForeachMatchOpGenericAdaptor::ForeachMatchOpGenericAdaptor;
  ForeachMatchOpAdaptor(ForeachMatchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ForeachMatchOp : public ::mlir::Op<ForeachMatchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ForeachMatchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ForeachMatchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_root = 0;
  static constexpr int odsIndex_forwarded_inputs = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ForeachMatchOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ForeachMatchOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ForeachMatchOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("actions"), ::llvm::StringRef("flatten_results"), ::llvm::StringRef("matchers"), ::llvm::StringRef("restrict_root")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getActionsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getActionsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFlattenResultsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFlattenResultsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getMatchersAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getMatchersAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getRestrictRootAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getRestrictRootAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.foreach_match");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getRoot() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getForwardedInputs() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getRootMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getForwardedInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getUpdated() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSResults(0).begin());
  }

  ::mlir::Operation::result_range getForwardedOutputs() {
    return getODSResults(1);
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
  ::mlir::UnitAttr getRestrictRootAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().restrict_root);
  }

  bool getRestrictRoot();
  ::mlir::UnitAttr getFlattenResultsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().flatten_results);
  }

  bool getFlattenResults();
  ::mlir::ArrayAttr getMatchersAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().matchers);
  }

  ::mlir::ArrayAttr getMatchers();
  ::mlir::ArrayAttr getActionsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().actions);
  }

  ::mlir::ArrayAttr getActions();
  void setRestrictRootAttr(::mlir::UnitAttr attr) {
    getProperties().restrict_root = attr;
  }

  void setRestrictRoot(bool attrValue);
  void setFlattenResultsAttr(::mlir::UnitAttr attr) {
    getProperties().flatten_results = attr;
  }

  void setFlattenResults(bool attrValue);
  void setMatchersAttr(::mlir::ArrayAttr attr) {
    getProperties().matchers = attr;
  }

  void setActionsAttr(::mlir::ArrayAttr attr) {
    getProperties().actions = attr;
  }

  ::mlir::Attribute removeRestrictRootAttr() {
      auto attr = getProperties().restrict_root;
      getProperties().restrict_root = {};
      return attr;
  }

  ::mlir::Attribute removeFlattenResultsAttr() {
      auto attr = getProperties().flatten_results;
      getProperties().flatten_results = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type updated, ::mlir::TypeRange forwarded_outputs, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/::mlir::UnitAttr restrict_root, /*optional*/::mlir::UnitAttr flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static ForeachMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type updated, ::mlir::TypeRange forwarded_outputs, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/::mlir::UnitAttr restrict_root, /*optional*/::mlir::UnitAttr flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static ForeachMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type updated, ::mlir::TypeRange forwarded_outputs, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/::mlir::UnitAttr restrict_root, /*optional*/::mlir::UnitAttr flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/::mlir::UnitAttr restrict_root, /*optional*/::mlir::UnitAttr flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static ForeachMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/::mlir::UnitAttr restrict_root, /*optional*/::mlir::UnitAttr flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static ForeachMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/::mlir::UnitAttr restrict_root, /*optional*/::mlir::UnitAttr flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type updated, ::mlir::TypeRange forwarded_outputs, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/bool restrict_root, /*optional*/bool flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static ForeachMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type updated, ::mlir::TypeRange forwarded_outputs, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/bool restrict_root, /*optional*/bool flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static ForeachMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type updated, ::mlir::TypeRange forwarded_outputs, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/bool restrict_root, /*optional*/bool flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/bool restrict_root, /*optional*/bool flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static ForeachMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/bool restrict_root, /*optional*/bool flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static ForeachMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value root, ::mlir::ValueRange forwarded_inputs, /*optional*/bool restrict_root, /*optional*/bool flatten_results, ::mlir::ArrayAttr matchers, ::mlir::ArrayAttr actions);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ForeachMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ForeachMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ForeachMatchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ForeachMatchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  bool allowsRepeatedHandleOperands();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ForeachMatchOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ForeachOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ForeachOpGenericAdaptorBase {
public:
  struct Properties {
    using with_zip_shortestTy = ::mlir::UnitAttr;
    with_zip_shortestTy with_zip_shortest;

    auto getWithZipShortest() const {
      auto &propStorage = this->with_zip_shortest;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setWithZipShortest(const ::mlir::UnitAttr &propValue) {
      this->with_zip_shortest = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.with_zip_shortest == this->with_zip_shortest &&
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
  ForeachOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.foreach", odsAttrs.getContext());
  }

  ForeachOpGenericAdaptorBase(ForeachOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getWithZipShortestAttr();
  bool getWithZipShortest();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ForeachOpGenericAdaptor : public detail::ForeachOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ForeachOpGenericAdaptorBase;
  static constexpr int odsIndex_targets = 0;
public:
  ForeachOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ForeachOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ForeachOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ForeachOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ForeachOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ForeachOpGenericAdaptor(RangeT values, const ForeachOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ForeachOp, typename = std::enable_if_t<std::is_same_v<LateInst, ForeachOp>>>
  ForeachOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getTargets() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ForeachOpAdaptor : public ForeachOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ForeachOpGenericAdaptor::ForeachOpGenericAdaptor;
  ForeachOpAdaptor(ForeachOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ForeachOp : public ::mlir::Op<ForeachOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<::mlir::transform::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ForeachOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ForeachOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_targets = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<ForeachOp>::allowsRepeatedHandleOperands;
  using ::mlir::RegionBranchOpInterface::Trait<ForeachOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<ForeachOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<ForeachOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<ForeachOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<ForeachOp>::getRegionInvocationBounds;
  using ::mlir::RegionBranchOpInterface::Trait<ForeachOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("with_zip_shortest")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getWithZipShortestAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getWithZipShortestAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.foreach");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getTargets() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getTargetsMutable();
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
  ::mlir::UnitAttr getWithZipShortestAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().with_zip_shortest);
  }

  bool getWithZipShortest();
  void setWithZipShortestAttr(::mlir::UnitAttr attr) {
    getProperties().with_zip_shortest = attr;
  }

  void setWithZipShortest(bool attrValue);
  ::mlir::Attribute removeWithZipShortestAttr() {
      auto attr = getProperties().with_zip_shortest;
      getProperties().with_zip_shortest = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ValueRange targets, /*optional*/::mlir::UnitAttr with_zip_shortest);
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ValueRange targets, /*optional*/::mlir::UnitAttr with_zip_shortest);
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ValueRange targets, /*optional*/::mlir::UnitAttr with_zip_shortest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ValueRange targets, /*optional*/bool with_zip_shortest = false);
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ValueRange targets, /*optional*/bool with_zip_shortest = false);
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ValueRange targets, /*optional*/bool with_zip_shortest = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  ::mlir::OperandRange getEntrySuccessorOperands(::mlir::RegionSuccessor successor);
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);
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
  /// Allow the dialect prefix to be omitted.
  static StringRef getDefaultDialect() { return "transform"; }

  transform::YieldOp getYieldOp();
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ForeachOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::GetConsumersOfResult declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetConsumersOfResultGenericAdaptorBase {
public:
  struct Properties {
    using result_numberTy = ::mlir::IntegerAttr;
    result_numberTy result_number;

    auto getResultNumber() const {
      auto &propStorage = this->result_number;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setResultNumber(const ::mlir::IntegerAttr &propValue) {
      this->result_number = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.result_number == this->result_number &&
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
  GetConsumersOfResultGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.get_consumers_of_result", odsAttrs.getContext());
  }

  GetConsumersOfResultGenericAdaptorBase(GetConsumersOfResult op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getResultNumberAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().result_number);
    return attr;
  }

  uint64_t getResultNumber();
};

} // namespace detail
template <typename RangeT>
class GetConsumersOfResultGenericAdaptor : public detail::GetConsumersOfResultGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetConsumersOfResultGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  GetConsumersOfResultGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetConsumersOfResultGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetConsumersOfResultGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetConsumersOfResultGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetConsumersOfResultGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetConsumersOfResultGenericAdaptor(RangeT values, const GetConsumersOfResultGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetConsumersOfResult, typename = std::enable_if_t<std::is_same_v<LateInst, GetConsumersOfResult>>>
  GetConsumersOfResultGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetConsumersOfResultAdaptor : public GetConsumersOfResultGenericAdaptor<::mlir::ValueRange> {
public:
  using GetConsumersOfResultGenericAdaptor::GetConsumersOfResultGenericAdaptor;
  GetConsumersOfResultAdaptor(GetConsumersOfResult op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetConsumersOfResult : public ::mlir::Op<GetConsumersOfResult, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformHandleTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::NavigationTransformOpTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetConsumersOfResultAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetConsumersOfResultGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<GetConsumersOfResult>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("result_number")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getResultNumberAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getResultNumberAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.get_consumers_of_result");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getConsumers() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getResultNumberAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().result_number);
  }

  uint64_t getResultNumber();
  void setResultNumberAttr(::mlir::IntegerAttr attr) {
    getProperties().result_number = attr;
  }

  void setResultNumber(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type consumers, ::mlir::Value target, ::mlir::IntegerAttr result_number);
  static GetConsumersOfResult create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type consumers, ::mlir::Value target, ::mlir::IntegerAttr result_number);
  static GetConsumersOfResult create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type consumers, ::mlir::Value target, ::mlir::IntegerAttr result_number);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::IntegerAttr result_number);
  static GetConsumersOfResult create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::IntegerAttr result_number);
  static GetConsumersOfResult create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::IntegerAttr result_number);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type consumers, ::mlir::Value target, uint64_t result_number);
  static GetConsumersOfResult create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type consumers, ::mlir::Value target, uint64_t result_number);
  static GetConsumersOfResult create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type consumers, ::mlir::Value target, uint64_t result_number);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, uint64_t result_number);
  static GetConsumersOfResult create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, uint64_t result_number);
  static GetConsumersOfResult create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, uint64_t result_number);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetConsumersOfResult create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetConsumersOfResult create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetConsumersOfResult create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetConsumersOfResult create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::GetConsumersOfResult)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::GetDefiningOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetDefiningOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GetDefiningOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.get_defining_op", odsAttrs.getContext());
  }

  GetDefiningOpGenericAdaptorBase(GetDefiningOp op);

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
class GetDefiningOpGenericAdaptor : public detail::GetDefiningOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetDefiningOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  GetDefiningOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetDefiningOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetDefiningOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetDefiningOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetDefiningOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetDefiningOpGenericAdaptor(RangeT values, const GetDefiningOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetDefiningOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetDefiningOp>>>
  GetDefiningOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetDefiningOpAdaptor : public GetDefiningOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetDefiningOpGenericAdaptor::GetDefiningOpGenericAdaptor;
  GetDefiningOpAdaptor(GetDefiningOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetDefiningOp : public ::mlir::Op<GetDefiningOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformHandleTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::transform::NavigationTransformOpTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetDefiningOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetDefiningOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<GetDefiningOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.get_defining_op");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformValueHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformValueHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value target);
  static GetDefiningOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value target);
  static GetDefiningOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value target);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static GetDefiningOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static GetDefiningOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetDefiningOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetDefiningOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetDefiningOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetDefiningOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::GetDefiningOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::GetOperandOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetOperandOpGenericAdaptorBase {
public:
  struct Properties {
    using is_allTy = ::mlir::UnitAttr;
    is_allTy is_all;

    auto getIsAll() const {
      auto &propStorage = this->is_all;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsAll(const ::mlir::UnitAttr &propValue) {
      this->is_all = propValue;
    }
    using is_invertedTy = ::mlir::UnitAttr;
    is_invertedTy is_inverted;

    auto getIsInverted() const {
      auto &propStorage = this->is_inverted;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsInverted(const ::mlir::UnitAttr &propValue) {
      this->is_inverted = propValue;
    }
    using raw_position_listTy = ::mlir::DenseI64ArrayAttr;
    raw_position_listTy raw_position_list;

    auto getRawPositionList() const {
      auto &propStorage = this->raw_position_list;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setRawPositionList(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->raw_position_list = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.is_all == this->is_all &&
        rhs.is_inverted == this->is_inverted &&
        rhs.raw_position_list == this->raw_position_list &&
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
      odsOpName.emplace("transform.get_operand", odsAttrs.getContext());
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

  ::mlir::DenseI64ArrayAttr getRawPositionListAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().raw_position_list);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getRawPositionList();
  ::mlir::UnitAttr getIsInvertedAttr();
  bool getIsInverted();
  ::mlir::UnitAttr getIsAllAttr();
  bool getIsAll();
};

} // namespace detail
template <typename RangeT>
class GetOperandOpGenericAdaptor : public detail::GetOperandOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetOperandOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
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

  ValueT getTarget() {
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
class GetOperandOp : public ::mlir::Op<GetOperandOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformValueHandleTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::NavigationTransformOpTrait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetOperandOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetOperandOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<GetOperandOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("is_all"), ::llvm::StringRef("is_inverted"), ::llvm::StringRef("raw_position_list")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIsAllAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIsAllAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIsInvertedAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIsInvertedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getRawPositionListAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getRawPositionListAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.get_operand");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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

  ::mlir::TypedValue<::mlir::transform::TransformValueHandleTypeInterface> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformValueHandleTypeInterface>>(*getODSResults(0).begin());
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
  ::mlir::DenseI64ArrayAttr getRawPositionListAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().raw_position_list);
  }

  ::llvm::ArrayRef<int64_t> getRawPositionList();
  ::mlir::UnitAttr getIsInvertedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().is_inverted);
  }

  bool getIsInverted();
  ::mlir::UnitAttr getIsAllAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().is_all);
  }

  bool getIsAll();
  void setRawPositionListAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().raw_position_list = attr;
  }

  void setRawPositionList(::llvm::ArrayRef<int64_t> attrValue);
  void setIsInvertedAttr(::mlir::UnitAttr attr) {
    getProperties().is_inverted = attr;
  }

  void setIsInverted(bool attrValue);
  void setIsAllAttr(::mlir::UnitAttr attr) {
    getProperties().is_all = attr;
  }

  void setIsAll(bool attrValue);
  ::mlir::Attribute removeIsInvertedAttr() {
      auto attr = getProperties().is_inverted;
      getProperties().is_inverted = {};
      return attr;
  }

  ::mlir::Attribute removeIsAllAttr() {
      auto attr = getProperties().is_all;
      getProperties().is_all = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetOperandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetOperandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::GetOperandOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::GetParentOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetParentOpGenericAdaptorBase {
public:
  struct Properties {
    using allow_empty_resultsTy = ::mlir::UnitAttr;
    allow_empty_resultsTy allow_empty_results;

    auto getAllowEmptyResults() const {
      auto &propStorage = this->allow_empty_results;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setAllowEmptyResults(const ::mlir::UnitAttr &propValue) {
      this->allow_empty_results = propValue;
    }
    using deduplicateTy = ::mlir::UnitAttr;
    deduplicateTy deduplicate;

    auto getDeduplicate() const {
      auto &propStorage = this->deduplicate;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setDeduplicate(const ::mlir::UnitAttr &propValue) {
      this->deduplicate = propValue;
    }
    using isolated_from_aboveTy = ::mlir::UnitAttr;
    isolated_from_aboveTy isolated_from_above;

    auto getIsolatedFromAbove() const {
      auto &propStorage = this->isolated_from_above;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsolatedFromAbove(const ::mlir::UnitAttr &propValue) {
      this->isolated_from_above = propValue;
    }
    using nth_parentTy = ::mlir::IntegerAttr;
    nth_parentTy nth_parent;

    auto getNthParent() const {
      auto &propStorage = this->nth_parent;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setNthParent(const ::mlir::IntegerAttr &propValue) {
      this->nth_parent = propValue;
    }
    using op_nameTy = ::mlir::StringAttr;
    op_nameTy op_name;

    auto getOpName() const {
      auto &propStorage = this->op_name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setOpName(const ::mlir::StringAttr &propValue) {
      this->op_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.allow_empty_results == this->allow_empty_results &&
        rhs.deduplicate == this->deduplicate &&
        rhs.isolated_from_above == this->isolated_from_above &&
        rhs.nth_parent == this->nth_parent &&
        rhs.op_name == this->op_name &&
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
  GetParentOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.get_parent_op", odsAttrs.getContext());
  }

  GetParentOpGenericAdaptorBase(GetParentOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getIsolatedFromAboveAttr();
  bool getIsolatedFromAbove();
  ::mlir::UnitAttr getAllowEmptyResultsAttr();
  bool getAllowEmptyResults();
  ::mlir::StringAttr getOpNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().op_name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getOpName();
  ::mlir::UnitAttr getDeduplicateAttr();
  bool getDeduplicate();
  ::mlir::IntegerAttr getNthParentAttr();
  uint64_t getNthParent();
};

} // namespace detail
template <typename RangeT>
class GetParentOpGenericAdaptor : public detail::GetParentOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetParentOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  GetParentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetParentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetParentOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetParentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetParentOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetParentOpGenericAdaptor(RangeT values, const GetParentOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetParentOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetParentOp>>>
  GetParentOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetParentOpAdaptor : public GetParentOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetParentOpGenericAdaptor::GetParentOpGenericAdaptor;
  GetParentOpAdaptor(GetParentOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetParentOp : public ::mlir::Op<GetParentOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformHandleTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::transform::NavigationTransformOpTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetParentOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetParentOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<GetParentOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("allow_empty_results"), ::llvm::StringRef("deduplicate"), ::llvm::StringRef("isolated_from_above"), ::llvm::StringRef("nth_parent"), ::llvm::StringRef("op_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAllowEmptyResultsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAllowEmptyResultsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getDeduplicateAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getDeduplicateAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getIsolatedFromAboveAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getIsolatedFromAboveAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getNthParentAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getNthParentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getOpNameAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getOpNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.get_parent_op");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getParent() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSResults(0).begin());
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
  ::mlir::UnitAttr getIsolatedFromAboveAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().isolated_from_above);
  }

  bool getIsolatedFromAbove();
  ::mlir::UnitAttr getAllowEmptyResultsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().allow_empty_results);
  }

  bool getAllowEmptyResults();
  ::mlir::StringAttr getOpNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().op_name);
  }

  ::std::optional< ::llvm::StringRef > getOpName();
  ::mlir::UnitAttr getDeduplicateAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().deduplicate);
  }

  bool getDeduplicate();
  ::mlir::IntegerAttr getNthParentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().nth_parent);
  }

  uint64_t getNthParent();
  void setIsolatedFromAboveAttr(::mlir::UnitAttr attr) {
    getProperties().isolated_from_above = attr;
  }

  void setIsolatedFromAbove(bool attrValue);
  void setAllowEmptyResultsAttr(::mlir::UnitAttr attr) {
    getProperties().allow_empty_results = attr;
  }

  void setAllowEmptyResults(bool attrValue);
  void setOpNameAttr(::mlir::StringAttr attr) {
    getProperties().op_name = attr;
  }

  void setOpName(::std::optional<::llvm::StringRef> attrValue);
  void setDeduplicateAttr(::mlir::UnitAttr attr) {
    getProperties().deduplicate = attr;
  }

  void setDeduplicate(bool attrValue);
  void setNthParentAttr(::mlir::IntegerAttr attr) {
    getProperties().nth_parent = attr;
  }

  void setNthParent(uint64_t attrValue);
  ::mlir::Attribute removeIsolatedFromAboveAttr() {
      auto attr = getProperties().isolated_from_above;
      getProperties().isolated_from_above = {};
      return attr;
  }

  ::mlir::Attribute removeAllowEmptyResultsAttr() {
      auto attr = getProperties().allow_empty_results;
      getProperties().allow_empty_results = {};
      return attr;
  }

  ::mlir::Attribute removeOpNameAttr() {
      auto attr = getProperties().op_name;
      getProperties().op_name = {};
      return attr;
  }

  ::mlir::Attribute removeDeduplicateAttr() {
      auto attr = getProperties().deduplicate;
      getProperties().deduplicate = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type parent, ::mlir::Value target, /*optional*/::mlir::UnitAttr isolated_from_above, /*optional*/::mlir::UnitAttr allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/::mlir::UnitAttr deduplicate, ::mlir::IntegerAttr nth_parent = nullptr);
  static GetParentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type parent, ::mlir::Value target, /*optional*/::mlir::UnitAttr isolated_from_above, /*optional*/::mlir::UnitAttr allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/::mlir::UnitAttr deduplicate, ::mlir::IntegerAttr nth_parent = nullptr);
  static GetParentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type parent, ::mlir::Value target, /*optional*/::mlir::UnitAttr isolated_from_above, /*optional*/::mlir::UnitAttr allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/::mlir::UnitAttr deduplicate, ::mlir::IntegerAttr nth_parent = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, /*optional*/::mlir::UnitAttr isolated_from_above, /*optional*/::mlir::UnitAttr allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/::mlir::UnitAttr deduplicate, ::mlir::IntegerAttr nth_parent = nullptr);
  static GetParentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, /*optional*/::mlir::UnitAttr isolated_from_above, /*optional*/::mlir::UnitAttr allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/::mlir::UnitAttr deduplicate, ::mlir::IntegerAttr nth_parent = nullptr);
  static GetParentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, /*optional*/::mlir::UnitAttr isolated_from_above, /*optional*/::mlir::UnitAttr allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/::mlir::UnitAttr deduplicate, ::mlir::IntegerAttr nth_parent = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type parent, ::mlir::Value target, /*optional*/bool isolated_from_above, /*optional*/bool allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/bool deduplicate = false, uint64_t nth_parent = 1);
  static GetParentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type parent, ::mlir::Value target, /*optional*/bool isolated_from_above, /*optional*/bool allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/bool deduplicate = false, uint64_t nth_parent = 1);
  static GetParentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type parent, ::mlir::Value target, /*optional*/bool isolated_from_above, /*optional*/bool allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/bool deduplicate = false, uint64_t nth_parent = 1);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, /*optional*/bool isolated_from_above, /*optional*/bool allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/bool deduplicate = false, uint64_t nth_parent = 1);
  static GetParentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, /*optional*/bool isolated_from_above, /*optional*/bool allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/bool deduplicate = false, uint64_t nth_parent = 1);
  static GetParentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, /*optional*/bool isolated_from_above, /*optional*/bool allow_empty_results, /*optional*/::mlir::StringAttr op_name, /*optional*/bool deduplicate = false, uint64_t nth_parent = 1);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetParentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetParentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetParentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetParentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::GetParentOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::GetProducerOfOperand declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetProducerOfOperandGenericAdaptorBase {
public:
  struct Properties {
    using operand_numberTy = ::mlir::IntegerAttr;
    operand_numberTy operand_number;

    auto getOperandNumber() const {
      auto &propStorage = this->operand_number;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setOperandNumber(const ::mlir::IntegerAttr &propValue) {
      this->operand_number = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.operand_number == this->operand_number &&
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
  GetProducerOfOperandGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.get_producer_of_operand", odsAttrs.getContext());
  }

  GetProducerOfOperandGenericAdaptorBase(GetProducerOfOperand op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getOperandNumberAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().operand_number);
    return attr;
  }

  uint64_t getOperandNumber();
};

} // namespace detail
template <typename RangeT>
class GetProducerOfOperandGenericAdaptor : public detail::GetProducerOfOperandGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetProducerOfOperandGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  GetProducerOfOperandGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetProducerOfOperandGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetProducerOfOperandGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetProducerOfOperandGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetProducerOfOperandGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetProducerOfOperandGenericAdaptor(RangeT values, const GetProducerOfOperandGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetProducerOfOperand, typename = std::enable_if_t<std::is_same_v<LateInst, GetProducerOfOperand>>>
  GetProducerOfOperandGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetProducerOfOperandAdaptor : public GetProducerOfOperandGenericAdaptor<::mlir::ValueRange> {
public:
  using GetProducerOfOperandGenericAdaptor::GetProducerOfOperandGenericAdaptor;
  GetProducerOfOperandAdaptor(GetProducerOfOperand op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetProducerOfOperand : public ::mlir::Op<GetProducerOfOperand, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformHandleTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::NavigationTransformOpTrait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetProducerOfOperandAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetProducerOfOperandGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<GetProducerOfOperand>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("operand_number")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOperandNumberAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOperandNumberAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.get_producer_of_operand");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getProducer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getOperandNumberAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().operand_number);
  }

  uint64_t getOperandNumber();
  void setOperandNumberAttr(::mlir::IntegerAttr attr) {
    getProperties().operand_number = attr;
  }

  void setOperandNumber(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type producer, ::mlir::Value target, ::mlir::IntegerAttr operand_number);
  static GetProducerOfOperand create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type producer, ::mlir::Value target, ::mlir::IntegerAttr operand_number);
  static GetProducerOfOperand create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type producer, ::mlir::Value target, ::mlir::IntegerAttr operand_number);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::IntegerAttr operand_number);
  static GetProducerOfOperand create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::IntegerAttr operand_number);
  static GetProducerOfOperand create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::IntegerAttr operand_number);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type producer, ::mlir::Value target, uint64_t operand_number);
  static GetProducerOfOperand create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type producer, ::mlir::Value target, uint64_t operand_number);
  static GetProducerOfOperand create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type producer, ::mlir::Value target, uint64_t operand_number);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, uint64_t operand_number);
  static GetProducerOfOperand create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, uint64_t operand_number);
  static GetProducerOfOperand create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, uint64_t operand_number);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetProducerOfOperand create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetProducerOfOperand create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetProducerOfOperand create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetProducerOfOperand create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::GetProducerOfOperand)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::GetResultOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetResultOpGenericAdaptorBase {
public:
  struct Properties {
    using is_allTy = ::mlir::UnitAttr;
    is_allTy is_all;

    auto getIsAll() const {
      auto &propStorage = this->is_all;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsAll(const ::mlir::UnitAttr &propValue) {
      this->is_all = propValue;
    }
    using is_invertedTy = ::mlir::UnitAttr;
    is_invertedTy is_inverted;

    auto getIsInverted() const {
      auto &propStorage = this->is_inverted;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsInverted(const ::mlir::UnitAttr &propValue) {
      this->is_inverted = propValue;
    }
    using raw_position_listTy = ::mlir::DenseI64ArrayAttr;
    raw_position_listTy raw_position_list;

    auto getRawPositionList() const {
      auto &propStorage = this->raw_position_list;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setRawPositionList(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->raw_position_list = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.is_all == this->is_all &&
        rhs.is_inverted == this->is_inverted &&
        rhs.raw_position_list == this->raw_position_list &&
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
      odsOpName.emplace("transform.get_result", odsAttrs.getContext());
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

  ::mlir::DenseI64ArrayAttr getRawPositionListAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().raw_position_list);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getRawPositionList();
  ::mlir::UnitAttr getIsInvertedAttr();
  bool getIsInverted();
  ::mlir::UnitAttr getIsAllAttr();
  bool getIsAll();
};

} // namespace detail
template <typename RangeT>
class GetResultOpGenericAdaptor : public detail::GetResultOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetResultOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
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

  ValueT getTarget() {
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
class GetResultOp : public ::mlir::Op<GetResultOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformValueHandleTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::NavigationTransformOpTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetResultOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetResultOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<GetResultOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("is_all"), ::llvm::StringRef("is_inverted"), ::llvm::StringRef("raw_position_list")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIsAllAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIsAllAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIsInvertedAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIsInvertedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getRawPositionListAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getRawPositionListAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.get_result");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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

  ::mlir::TypedValue<::mlir::transform::TransformValueHandleTypeInterface> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformValueHandleTypeInterface>>(*getODSResults(0).begin());
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
  ::mlir::DenseI64ArrayAttr getRawPositionListAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().raw_position_list);
  }

  ::llvm::ArrayRef<int64_t> getRawPositionList();
  ::mlir::UnitAttr getIsInvertedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().is_inverted);
  }

  bool getIsInverted();
  ::mlir::UnitAttr getIsAllAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().is_all);
  }

  bool getIsAll();
  void setRawPositionListAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().raw_position_list = attr;
  }

  void setRawPositionList(::llvm::ArrayRef<int64_t> attrValue);
  void setIsInvertedAttr(::mlir::UnitAttr attr) {
    getProperties().is_inverted = attr;
  }

  void setIsInverted(bool attrValue);
  void setIsAllAttr(::mlir::UnitAttr attr) {
    getProperties().is_all = attr;
  }

  void setIsAll(bool attrValue);
  ::mlir::Attribute removeIsInvertedAttr() {
      auto attr = getProperties().is_inverted;
      getProperties().is_inverted = {};
      return attr;
  }

  ::mlir::Attribute removeIsAllAttr() {
      auto attr = getProperties().is_all;
      getProperties().is_all = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::DenseI64ArrayAttr raw_position_list, /*optional*/::mlir::UnitAttr is_inverted = nullptr, /*optional*/::mlir::UnitAttr is_all = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::ArrayRef<int64_t> raw_position_list, /*optional*/bool is_inverted = false, /*optional*/bool is_all = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetResultOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetResultOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::GetResultOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::GetTypeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetTypeOpGenericAdaptorBase {
public:
  struct Properties {
    using elementalTy = ::mlir::UnitAttr;
    elementalTy elemental;

    auto getElemental() const {
      auto &propStorage = this->elemental;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setElemental(const ::mlir::UnitAttr &propValue) {
      this->elemental = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.elemental == this->elemental &&
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
  GetTypeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.get_type", odsAttrs.getContext());
  }

  GetTypeOpGenericAdaptorBase(GetTypeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getElementalAttr();
  bool getElemental();
};

} // namespace detail
template <typename RangeT>
class GetTypeOpGenericAdaptor : public detail::GetTypeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetTypeOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  GetTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetTypeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetTypeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetTypeOpGenericAdaptor(RangeT values, const GetTypeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetTypeOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetTypeOp>>>
  GetTypeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GetTypeOpAdaptor : public GetTypeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetTypeOpGenericAdaptor::GetTypeOpGenericAdaptor;
  GetTypeOpAdaptor(GetTypeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetTypeOp : public ::mlir::Op<GetTypeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformParamTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetTypeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetTypeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<GetTypeOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("elemental")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getElementalAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getElementalAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.get_type");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformValueHandleTypeInterface> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformValueHandleTypeInterface>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface> getTypeParam() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface>>(*getODSResults(0).begin());
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
  ::mlir::UnitAttr getElementalAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().elemental);
  }

  bool getElemental();
  void setElementalAttr(::mlir::UnitAttr attr) {
    getProperties().elemental = attr;
  }

  void setElemental(bool attrValue);
  ::mlir::Attribute removeElementalAttr() {
      auto attr = getProperties().elemental;
      getProperties().elemental = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type type_param, ::mlir::Value value, /*optional*/::mlir::UnitAttr elemental);
  static GetTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type type_param, ::mlir::Value value, /*optional*/::mlir::UnitAttr elemental);
  static GetTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type type_param, ::mlir::Value value, /*optional*/::mlir::UnitAttr elemental);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::UnitAttr elemental);
  static GetTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::UnitAttr elemental);
  static GetTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::UnitAttr elemental);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type type_param, ::mlir::Value value, /*optional*/bool elemental = false);
  static GetTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type type_param, ::mlir::Value value, /*optional*/bool elemental = false);
  static GetTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type type_param, ::mlir::Value value, /*optional*/bool elemental = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/bool elemental = false);
  static GetTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/bool elemental = false);
  static GetTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/bool elemental = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::GetTypeOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::IncludeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IncludeOpGenericAdaptorBase {
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
    using failure_propagation_modeTy = ::mlir::transform::FailurePropagationModeAttr;
    failure_propagation_modeTy failure_propagation_mode;

    auto getFailurePropagationMode() const {
      auto &propStorage = this->failure_propagation_mode;
      return ::llvm::cast<::mlir::transform::FailurePropagationModeAttr>(propStorage);
    }
    void setFailurePropagationMode(const ::mlir::transform::FailurePropagationModeAttr &propValue) {
      this->failure_propagation_mode = propValue;
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
    using targetTy = ::mlir::SymbolRefAttr;
    targetTy target;

    auto getTarget() const {
      auto &propStorage = this->target;
      return ::llvm::cast<::mlir::SymbolRefAttr>(propStorage);
    }
    void setTarget(const ::mlir::SymbolRefAttr &propValue) {
      this->target = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.arg_attrs == this->arg_attrs &&
        rhs.failure_propagation_mode == this->failure_propagation_mode &&
        rhs.res_attrs == this->res_attrs &&
        rhs.target == this->target &&
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
  IncludeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.include", odsAttrs.getContext());
  }

  IncludeOpGenericAdaptorBase(IncludeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::SymbolRefAttr getTargetAttr() {
    auto attr = ::llvm::cast<::mlir::SymbolRefAttr>(getProperties().target);
    return attr;
  }

  ::mlir::SymbolRefAttr getTarget();
  ::mlir::transform::FailurePropagationModeAttr getFailurePropagationModeAttr() {
    auto attr = ::llvm::cast<::mlir::transform::FailurePropagationModeAttr>(getProperties().failure_propagation_mode);
    return attr;
  }

  ::mlir::transform::FailurePropagationMode getFailurePropagationMode();
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
};

} // namespace detail
template <typename RangeT>
class IncludeOpGenericAdaptor : public detail::IncludeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IncludeOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  IncludeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IncludeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IncludeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IncludeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IncludeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IncludeOpGenericAdaptor(RangeT values, const IncludeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IncludeOp, typename = std::enable_if_t<std::is_same_v<LateInst, IncludeOp>>>
  IncludeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return getODSOperands(0);
  }

private:
  RangeT odsOperands;
};
class IncludeOpAdaptor : public IncludeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IncludeOpGenericAdaptor::IncludeOpGenericAdaptor;
  IncludeOpAdaptor(IncludeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IncludeOp : public ::mlir::Op<IncludeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IncludeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IncludeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<IncludeOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("failure_propagation_mode"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("target")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgAttrsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFailurePropagationModeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFailurePropagationModeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getTargetAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getTargetAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.include");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getOperandsMutable();
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
  ::mlir::SymbolRefAttr getTargetAttr() {
    return ::llvm::cast<::mlir::SymbolRefAttr>(getProperties().target);
  }

  ::mlir::SymbolRefAttr getTarget();
  ::mlir::transform::FailurePropagationModeAttr getFailurePropagationModeAttr() {
    return ::llvm::cast<::mlir::transform::FailurePropagationModeAttr>(getProperties().failure_propagation_mode);
  }

  ::mlir::transform::FailurePropagationMode getFailurePropagationMode();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  void setTargetAttr(::mlir::SymbolRefAttr attr) {
    getProperties().target = attr;
  }

  void setFailurePropagationModeAttr(::mlir::transform::FailurePropagationModeAttr attr) {
    getProperties().failure_propagation_mode = attr;
  }

  void setFailurePropagationMode(::mlir::transform::FailurePropagationMode attrValue);
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::SymbolRefAttr target, ::mlir::transform::FailurePropagationModeAttr failure_propagation_mode, ::mlir::ValueRange operands, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static IncludeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::SymbolRefAttr target, ::mlir::transform::FailurePropagationModeAttr failure_propagation_mode, ::mlir::ValueRange operands, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static IncludeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::SymbolRefAttr target, ::mlir::transform::FailurePropagationModeAttr failure_propagation_mode, ::mlir::ValueRange operands, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::SymbolRefAttr target, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::ValueRange operands, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static IncludeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::SymbolRefAttr target, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::ValueRange operands, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static IncludeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::SymbolRefAttr target, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::ValueRange operands, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IncludeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IncludeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IncludeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IncludeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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
  ::mlir::CallInterfaceCallable getCallableForCallee() {
    return getTarget();
  }

  void setCalleeFromCallable(::mlir::CallInterfaceCallable callee) {
    setTargetAttr(cast<SymbolRefAttr>(callee));
  }

  ::mlir::Operation::operand_range getArgOperands() {
    return getOperands();
  }

  ::mlir::MutableOperandRange getArgOperandsMutable() {
    return getOperandsMutable();
  }
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::IncludeOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::MatchOperationEmptyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MatchOperationEmptyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MatchOperationEmptyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.match.operation_empty", odsAttrs.getContext());
  }

  MatchOperationEmptyOpGenericAdaptorBase(MatchOperationEmptyOp op);

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
class MatchOperationEmptyOpGenericAdaptor : public detail::MatchOperationEmptyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MatchOperationEmptyOpGenericAdaptorBase;
  static constexpr int odsIndex_operand_handle = 0;
public:
  MatchOperationEmptyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MatchOperationEmptyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MatchOperationEmptyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MatchOperationEmptyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MatchOperationEmptyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MatchOperationEmptyOpGenericAdaptor(RangeT values, const MatchOperationEmptyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MatchOperationEmptyOp, typename = std::enable_if_t<std::is_same_v<LateInst, MatchOperationEmptyOp>>>
  MatchOperationEmptyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getOperandHandle() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MatchOperationEmptyOpAdaptor : public MatchOperationEmptyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MatchOperationEmptyOpGenericAdaptor::MatchOperationEmptyOpGenericAdaptor;
  MatchOperationEmptyOpAdaptor(MatchOperationEmptyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MatchOperationEmptyOp : public ::mlir::Op<MatchOperationEmptyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::transform::AtMostOneOpMatcherOpTrait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MatchOperationEmptyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MatchOperationEmptyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operand_handle = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.match.operation_empty");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getOperandHandle() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getOperandHandleMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value operand_handle);
  static MatchOperationEmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value operand_handle);
  static MatchOperationEmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value operand_handle);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value operand_handle);
  static MatchOperationEmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value operand_handle);
  static MatchOperationEmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value operand_handle);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MatchOperationEmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MatchOperationEmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MatchOperationEmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MatchOperationEmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  ::mlir::DiagnosedSilenceableFailure matchOperation(
        ::std::optional<::mlir::Operation *> maybeCurrent,
        ::mlir::transform::TransformResults &results,
        ::mlir::transform::TransformState &state);
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::MatchOperationEmptyOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::MatchOperationNameOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MatchOperationNameOpGenericAdaptorBase {
public:
  struct Properties {
    using op_namesTy = ::mlir::ArrayAttr;
    op_namesTy op_names;

    auto getOpNames() const {
      auto &propStorage = this->op_names;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setOpNames(const ::mlir::ArrayAttr &propValue) {
      this->op_names = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.op_names == this->op_names &&
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
  MatchOperationNameOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.match.operation_name", odsAttrs.getContext());
  }

  MatchOperationNameOpGenericAdaptorBase(MatchOperationNameOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getOpNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().op_names);
    return attr;
  }

  ::mlir::ArrayAttr getOpNames();
};

} // namespace detail
template <typename RangeT>
class MatchOperationNameOpGenericAdaptor : public detail::MatchOperationNameOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MatchOperationNameOpGenericAdaptorBase;
  static constexpr int odsIndex_operand_handle = 0;
public:
  MatchOperationNameOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MatchOperationNameOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MatchOperationNameOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MatchOperationNameOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MatchOperationNameOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MatchOperationNameOpGenericAdaptor(RangeT values, const MatchOperationNameOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MatchOperationNameOp, typename = std::enable_if_t<std::is_same_v<LateInst, MatchOperationNameOp>>>
  MatchOperationNameOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getOperandHandle() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MatchOperationNameOpAdaptor : public MatchOperationNameOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MatchOperationNameOpGenericAdaptor::MatchOperationNameOpGenericAdaptor;
  MatchOperationNameOpAdaptor(MatchOperationNameOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MatchOperationNameOp : public ::mlir::Op<MatchOperationNameOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::SingleOpMatcherOpTrait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MatchOperationNameOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MatchOperationNameOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operand_handle = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("op_names")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOpNamesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOpNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.match.operation_name");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getOperandHandle() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getOperandHandleMutable() {
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
  ::mlir::ArrayAttr getOpNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().op_names);
  }

  ::mlir::ArrayAttr getOpNames();
  void setOpNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().op_names = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value operand_handle, ::mlir::ArrayAttr op_names);
  static MatchOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value operand_handle, ::mlir::ArrayAttr op_names);
  static MatchOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value operand_handle, ::mlir::ArrayAttr op_names);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value operand_handle, ::mlir::ArrayAttr op_names);
  static MatchOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value operand_handle, ::mlir::ArrayAttr op_names);
  static MatchOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value operand_handle, ::mlir::ArrayAttr op_names);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MatchOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MatchOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MatchOperationNameOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MatchOperationNameOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  ::mlir::DiagnosedSilenceableFailure matchOperation(
        ::mlir::Operation *current,
        ::mlir::transform::TransformResults &results,
        ::mlir::transform::TransformState &state);
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::MatchOperationNameOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::MatchParamCmpIOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MatchParamCmpIOpGenericAdaptorBase {
public:
  struct Properties {
    using predicateTy = ::mlir::transform::MatchCmpIPredicateAttr;
    predicateTy predicate;

    auto getPredicate() const {
      auto &propStorage = this->predicate;
      return ::llvm::cast<::mlir::transform::MatchCmpIPredicateAttr>(propStorage);
    }
    void setPredicate(const ::mlir::transform::MatchCmpIPredicateAttr &propValue) {
      this->predicate = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.predicate == this->predicate &&
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
  MatchParamCmpIOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.match.param.cmpi", odsAttrs.getContext());
  }

  MatchParamCmpIOpGenericAdaptorBase(MatchParamCmpIOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::transform::MatchCmpIPredicateAttr getPredicateAttr() {
    auto attr = ::llvm::cast<::mlir::transform::MatchCmpIPredicateAttr>(getProperties().predicate);
    return attr;
  }

  ::mlir::transform::MatchCmpIPredicate getPredicate();
};

} // namespace detail
template <typename RangeT>
class MatchParamCmpIOpGenericAdaptor : public detail::MatchParamCmpIOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MatchParamCmpIOpGenericAdaptorBase;
  static constexpr int odsIndex_param = 0;
  static constexpr int odsIndex_reference = 1;
public:
  MatchParamCmpIOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MatchParamCmpIOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MatchParamCmpIOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MatchParamCmpIOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MatchParamCmpIOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MatchParamCmpIOpGenericAdaptor(RangeT values, const MatchParamCmpIOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MatchParamCmpIOp, typename = std::enable_if_t<std::is_same_v<LateInst, MatchParamCmpIOp>>>
  MatchParamCmpIOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getParam() {
    return (*getODSOperands(0).begin());
  }

  ValueT getReference() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MatchParamCmpIOpAdaptor : public MatchParamCmpIOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MatchParamCmpIOpGenericAdaptor::MatchParamCmpIOpGenericAdaptor;
  MatchParamCmpIOpAdaptor(MatchParamCmpIOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MatchParamCmpIOp : public ::mlir::Op<MatchParamCmpIOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameTypeOperands> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MatchParamCmpIOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MatchParamCmpIOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_param = 0;
  static constexpr int odsIndex_reference = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<MatchParamCmpIOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("predicate")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPredicateAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPredicateAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.match.param.cmpi");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface> getParam() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface> getReference() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getParamMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getReferenceMutable() {
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
  ::mlir::transform::MatchCmpIPredicateAttr getPredicateAttr() {
    return ::llvm::cast<::mlir::transform::MatchCmpIPredicateAttr>(getProperties().predicate);
  }

  ::mlir::transform::MatchCmpIPredicate getPredicate();
  void setPredicateAttr(::mlir::transform::MatchCmpIPredicateAttr attr) {
    getProperties().predicate = attr;
  }

  void setPredicate(::mlir::transform::MatchCmpIPredicate attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicateAttr predicate);
  static MatchParamCmpIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicateAttr predicate);
  static MatchParamCmpIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicateAttr predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicateAttr predicate);
  static MatchParamCmpIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicateAttr predicate);
  static MatchParamCmpIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicateAttr predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicate predicate);
  static MatchParamCmpIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicate predicate);
  static MatchParamCmpIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicate predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicate predicate);
  static MatchParamCmpIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicate predicate);
  static MatchParamCmpIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value param, ::mlir::Value reference, ::mlir::transform::MatchCmpIPredicate predicate);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MatchParamCmpIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MatchParamCmpIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MatchParamCmpIOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MatchParamCmpIOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::MatchParamCmpIOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::MergeHandlesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MergeHandlesOpGenericAdaptorBase {
public:
  struct Properties {
    using deduplicateTy = ::mlir::UnitAttr;
    deduplicateTy deduplicate;

    auto getDeduplicate() const {
      auto &propStorage = this->deduplicate;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setDeduplicate(const ::mlir::UnitAttr &propValue) {
      this->deduplicate = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.deduplicate == this->deduplicate &&
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
  MergeHandlesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.merge_handles", odsAttrs.getContext());
  }

  MergeHandlesOpGenericAdaptorBase(MergeHandlesOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getDeduplicateAttr();
  bool getDeduplicate();
};

} // namespace detail
template <typename RangeT>
class MergeHandlesOpGenericAdaptor : public detail::MergeHandlesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MergeHandlesOpGenericAdaptorBase;
  static constexpr int odsIndex_handles = 0;
public:
  MergeHandlesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MergeHandlesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MergeHandlesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MergeHandlesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MergeHandlesOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MergeHandlesOpGenericAdaptor(RangeT values, const MergeHandlesOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MergeHandlesOp, typename = std::enable_if_t<std::is_same_v<LateInst, MergeHandlesOp>>>
  MergeHandlesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getHandles() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MergeHandlesOpAdaptor : public MergeHandlesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MergeHandlesOpGenericAdaptor::MergeHandlesOpGenericAdaptor;
  MergeHandlesOpAdaptor(MergeHandlesOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MergeHandlesOp : public ::mlir::Op<MergeHandlesOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MergeHandlesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MergeHandlesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_handles = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("deduplicate")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDeduplicateAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDeduplicateAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.merge_handles");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getHandles() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getHandlesMutable();
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
  ::mlir::UnitAttr getDeduplicateAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().deduplicate);
  }

  bool getDeduplicate();
  void setDeduplicateAttr(::mlir::UnitAttr attr) {
    getProperties().deduplicate = attr;
  }

  void setDeduplicate(bool attrValue);
  ::mlir::Attribute removeDeduplicateAttr() {
      auto attr = getProperties().deduplicate;
      getProperties().deduplicate = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange handles, /*optional*/::mlir::UnitAttr deduplicate);
  static MergeHandlesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange handles, /*optional*/::mlir::UnitAttr deduplicate);
  static MergeHandlesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange handles, /*optional*/::mlir::UnitAttr deduplicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange handles, /*optional*/::mlir::UnitAttr deduplicate);
  static MergeHandlesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange handles, /*optional*/::mlir::UnitAttr deduplicate);
  static MergeHandlesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange handles, /*optional*/::mlir::UnitAttr deduplicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange handles, /*optional*/bool deduplicate = false);
  static MergeHandlesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange handles, /*optional*/bool deduplicate = false);
  static MergeHandlesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange handles, /*optional*/bool deduplicate = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange handles, /*optional*/bool deduplicate = false);
  static MergeHandlesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange handles, /*optional*/bool deduplicate = false);
  static MergeHandlesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange handles, /*optional*/bool deduplicate = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MergeHandlesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MergeHandlesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MergeHandlesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MergeHandlesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange handles, /*optional*/::mlir::UnitAttr deduplicate);
  static MergeHandlesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange handles, /*optional*/::mlir::UnitAttr deduplicate);
  static MergeHandlesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange handles, /*optional*/::mlir::UnitAttr deduplicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange handles, /*optional*/bool deduplicate = false);
  static MergeHandlesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange handles, /*optional*/bool deduplicate = false);
  static MergeHandlesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange handles, /*optional*/bool deduplicate = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MergeHandlesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MergeHandlesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MergeHandlesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MergeHandlesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  bool allowsRepeatedHandleOperands();
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::MergeHandlesOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::NamedSequenceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NamedSequenceOpGenericAdaptorBase {
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
    using sym_visibilityTy = ::mlir::StringAttr;
    sym_visibilityTy sym_visibility;

    auto getSymVisibility() const {
      auto &propStorage = this->sym_visibility;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSymVisibility(const ::mlir::StringAttr &propValue) {
      this->sym_visibility = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.res_attrs == this->res_attrs &&
        rhs.sym_name == this->sym_name &&
        rhs.sym_visibility == this->sym_visibility &&
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
  NamedSequenceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.named_sequence", odsAttrs.getContext());
  }

  NamedSequenceOpGenericAdaptorBase(NamedSequenceOp op);

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
  ::mlir::StringAttr getSymVisibilityAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_visibility);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSymVisibility();
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
class NamedSequenceOpGenericAdaptor : public detail::NamedSequenceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NamedSequenceOpGenericAdaptorBase;
public:
  NamedSequenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NamedSequenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : NamedSequenceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NamedSequenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NamedSequenceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NamedSequenceOpGenericAdaptor(RangeT values, const NamedSequenceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NamedSequenceOp, typename = std::enable_if_t<std::is_same_v<LateInst, NamedSequenceOp>>>
  NamedSequenceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class NamedSequenceOpAdaptor : public NamedSequenceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NamedSequenceOpGenericAdaptor::NamedSequenceOpGenericAdaptor;
  NamedSequenceOpAdaptor(NamedSequenceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NamedSequenceOp : public ::mlir::Op<NamedSequenceOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NamedSequenceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NamedSequenceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<NamedSequenceOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("sym_visibility")};
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

  ::mlir::StringAttr getSymVisibilityAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getSymVisibilityAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.named_sequence");
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
  ::mlir::StringAttr getSymVisibilityAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_visibility);
  }

  ::std::optional< ::llvm::StringRef > getSymVisibility();
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

  void setSymVisibilityAttr(::mlir::StringAttr attr) {
    getProperties().sym_visibility = attr;
  }

  void setSymVisibility(::std::optional<::llvm::StringRef> attrValue);
  void setArgAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().arg_attrs = attr;
  }

  void setResAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().res_attrs = attr;
  }

  ::mlir::Attribute removeSymVisibilityAttr() {
      auto attr = getProperties().sym_visibility;
      getProperties().sym_visibility = {};
      return attr;
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef symName, Type rootType, TypeRange resultType, SequenceBodyBuilderFn bodyBuilder, ArrayRef<NamedAttribute> attrs = {}, ArrayRef<DictionaryAttr> argAttrs = {});
  static NamedSequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef symName, Type rootType, TypeRange resultType, SequenceBodyBuilderFn bodyBuilder, ArrayRef<NamedAttribute> attrs = {}, ArrayRef<DictionaryAttr> argAttrs = {});
  static NamedSequenceOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef symName, Type rootType, TypeRange resultType, SequenceBodyBuilderFn bodyBuilder, ArrayRef<NamedAttribute> attrs = {}, ArrayRef<DictionaryAttr> argAttrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static NamedSequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static NamedSequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static NamedSequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static NamedSequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static NamedSequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static NamedSequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static NamedSequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static NamedSequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::StringAttr sym_visibility, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NamedSequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NamedSequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NamedSequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NamedSequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  ::llvm::ArrayRef<::mlir::Type> getArgumentTypes() {
    return getFunctionType().getInputs();
  }
  ::llvm::ArrayRef<::mlir::Type> getResultTypes() {
    return getFunctionType().getResults();
  }
  ::mlir::Region *getCallableRegion() {
    return &getBody();
  }
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::NamedSequenceOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::NumAssociationsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NumAssociationsOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  NumAssociationsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.num_associations", odsAttrs.getContext());
  }

  NumAssociationsOpGenericAdaptorBase(NumAssociationsOp op);

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
class NumAssociationsOpGenericAdaptor : public detail::NumAssociationsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NumAssociationsOpGenericAdaptorBase;
  static constexpr int odsIndex_handle = 0;
public:
  NumAssociationsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NumAssociationsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : NumAssociationsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NumAssociationsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NumAssociationsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NumAssociationsOpGenericAdaptor(RangeT values, const NumAssociationsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NumAssociationsOp, typename = std::enable_if_t<std::is_same_v<LateInst, NumAssociationsOp>>>
  NumAssociationsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getHandle() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class NumAssociationsOpAdaptor : public NumAssociationsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NumAssociationsOpGenericAdaptor::NumAssociationsOpGenericAdaptor;
  NumAssociationsOpAdaptor(NumAssociationsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NumAssociationsOp : public ::mlir::Op<NumAssociationsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformParamTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::ParamProducerTransformOpTrait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NumAssociationsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NumAssociationsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_handle = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<NumAssociationsOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.num_associations");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getHandle() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getHandleMutable() {
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

  ::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface> getNum() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type num, ::mlir::Value handle);
  static NumAssociationsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type num, ::mlir::Value handle);
  static NumAssociationsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type num, ::mlir::Value handle);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value handle);
  static NumAssociationsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value handle);
  static NumAssociationsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value handle);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NumAssociationsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NumAssociationsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NumAssociationsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NumAssociationsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::NumAssociationsOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ParamConstantOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ParamConstantOpGenericAdaptorBase {
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
  ParamConstantOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.param.constant", odsAttrs.getContext());
  }

  ParamConstantOpGenericAdaptorBase(ParamConstantOp op);

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
class ParamConstantOpGenericAdaptor : public detail::ParamConstantOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ParamConstantOpGenericAdaptorBase;
public:
  ParamConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ParamConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ParamConstantOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ParamConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ParamConstantOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ParamConstantOpGenericAdaptor(RangeT values, const ParamConstantOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ParamConstantOp, typename = std::enable_if_t<std::is_same_v<LateInst, ParamConstantOp>>>
  ParamConstantOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ParamConstantOpAdaptor : public ParamConstantOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ParamConstantOpGenericAdaptor::ParamConstantOpGenericAdaptor;
  ParamConstantOpAdaptor(ParamConstantOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ParamConstantOp : public ::mlir::Op<ParamConstantOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformParamTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::ParamProducerTransformOpTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ParamConstantOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ParamConstantOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<ParamConstantOp>::allowsRepeatedHandleOperands;
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
    return ::llvm::StringLiteral("transform.param.constant");
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

  ::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface> getParam() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformParamTypeInterface>>(*getODSResults(0).begin());
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type param, ::mlir::Attribute value);
  static ParamConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type param, ::mlir::Attribute value);
  static ParamConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type param, ::mlir::Attribute value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static ParamConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static ParamConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ParamConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ParamConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ParamConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ParamConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ParamConstantOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::PrintOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PrintOpGenericAdaptorBase {
public:
  struct Properties {
    using assume_verifiedTy = ::mlir::UnitAttr;
    assume_verifiedTy assume_verified;

    auto getAssumeVerified() const {
      auto &propStorage = this->assume_verified;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setAssumeVerified(const ::mlir::UnitAttr &propValue) {
      this->assume_verified = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using skip_regionsTy = ::mlir::UnitAttr;
    skip_regionsTy skip_regions;

    auto getSkipRegions() const {
      auto &propStorage = this->skip_regions;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setSkipRegions(const ::mlir::UnitAttr &propValue) {
      this->skip_regions = propValue;
    }
    using use_local_scopeTy = ::mlir::UnitAttr;
    use_local_scopeTy use_local_scope;

    auto getUseLocalScope() const {
      auto &propStorage = this->use_local_scope;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setUseLocalScope(const ::mlir::UnitAttr &propValue) {
      this->use_local_scope = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.assume_verified == this->assume_verified &&
        rhs.name == this->name &&
        rhs.skip_regions == this->skip_regions &&
        rhs.use_local_scope == this->use_local_scope &&
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
  PrintOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.print", odsAttrs.getContext());
  }

  PrintOpGenericAdaptorBase(PrintOp op);

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
  ::mlir::UnitAttr getAssumeVerifiedAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().assume_verified);
    return attr;
  }

  ::std::optional<bool> getAssumeVerified();
  ::mlir::UnitAttr getUseLocalScopeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().use_local_scope);
    return attr;
  }

  ::std::optional<bool> getUseLocalScope();
  ::mlir::UnitAttr getSkipRegionsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().skip_regions);
    return attr;
  }

  ::std::optional<bool> getSkipRegions();
};

} // namespace detail
template <typename RangeT>
class PrintOpGenericAdaptor : public detail::PrintOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PrintOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  PrintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PrintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PrintOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PrintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PrintOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PrintOpGenericAdaptor(RangeT values, const PrintOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PrintOp, typename = std::enable_if_t<std::is_same_v<LateInst, PrintOp>>>
  PrintOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PrintOpAdaptor : public PrintOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PrintOpGenericAdaptor::PrintOpGenericAdaptor;
  PrintOpAdaptor(PrintOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PrintOp : public ::mlir::Op<PrintOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PrintOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PrintOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<PrintOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("assume_verified"), ::llvm::StringRef("name"), ::llvm::StringRef("skip_regions"), ::llvm::StringRef("use_local_scope")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAssumeVerifiedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAssumeVerifiedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSkipRegionsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSkipRegionsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getUseLocalScopeAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getUseLocalScopeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.print");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>{} : ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getTargetMutable();
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::UnitAttr getAssumeVerifiedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().assume_verified);
  }

  ::std::optional<bool> getAssumeVerified();
  ::mlir::UnitAttr getUseLocalScopeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().use_local_scope);
  }

  ::std::optional<bool> getUseLocalScope();
  ::mlir::UnitAttr getSkipRegionsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().skip_regions);
  }

  ::std::optional<bool> getSkipRegions();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  void setAssumeVerifiedAttr(::mlir::UnitAttr attr) {
    getProperties().assume_verified = attr;
  }

  void setAssumeVerified(bool attrValue);
  void setUseLocalScopeAttr(::mlir::UnitAttr attr) {
    getProperties().use_local_scope = attr;
  }

  void setUseLocalScope(bool attrValue);
  void setSkipRegionsAttr(::mlir::UnitAttr attr) {
    getProperties().skip_regions = attr;
  }

  void setSkipRegions(bool attrValue);
  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  ::mlir::Attribute removeAssumeVerifiedAttr() {
      auto attr = getProperties().assume_verified;
      getProperties().assume_verified = {};
      return attr;
  }

  ::mlir::Attribute removeUseLocalScopeAttr() {
      auto attr = getProperties().use_local_scope;
      getProperties().use_local_scope = {};
      return attr;
  }

  ::mlir::Attribute removeSkipRegionsAttr() {
      auto attr = getProperties().skip_regions;
      getProperties().skip_regions = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name = StringRef());
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name = StringRef());
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name = StringRef());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value target, StringRef name = StringRef());
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value target, StringRef name = StringRef());
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, Value target, StringRef name = StringRef());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Value target, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::UnitAttr assume_verified, /*optional*/::mlir::UnitAttr use_local_scope, /*optional*/::mlir::UnitAttr skip_regions);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Value target, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::UnitAttr assume_verified, /*optional*/::mlir::UnitAttr use_local_scope, /*optional*/::mlir::UnitAttr skip_regions);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Value target, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::UnitAttr assume_verified, /*optional*/::mlir::UnitAttr use_local_scope, /*optional*/::mlir::UnitAttr skip_regions);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value target, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::UnitAttr assume_verified, /*optional*/::mlir::UnitAttr use_local_scope, /*optional*/::mlir::UnitAttr skip_regions);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value target, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::UnitAttr assume_verified, /*optional*/::mlir::UnitAttr use_local_scope, /*optional*/::mlir::UnitAttr skip_regions);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value target, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::UnitAttr assume_verified, /*optional*/::mlir::UnitAttr use_local_scope, /*optional*/::mlir::UnitAttr skip_regions);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::PrintOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::ReplicateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReplicateOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ReplicateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.replicate", odsAttrs.getContext());
  }

  ReplicateOpGenericAdaptorBase(ReplicateOp op);

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
class ReplicateOpGenericAdaptor : public detail::ReplicateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReplicateOpGenericAdaptorBase;
  static constexpr int odsIndex_pattern = 0;
  static constexpr int odsIndex_handles = 1;
public:
  ReplicateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReplicateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReplicateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReplicateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReplicateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

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

  ValueT getPattern() {
    return (*getODSOperands(0).begin());
  }

  RangeT getHandles() {
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
class ReplicateOp : public ::mlir::Op<ReplicateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::transform::TransformOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReplicateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReplicateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_pattern = 0;
  static constexpr int odsIndex_handles = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<ReplicateOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.replicate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getPattern() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getHandles() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getPatternMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getHandlesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getReplicated() {
    return getODSResults(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange replicated, ::mlir::Value pattern, ::mlir::ValueRange handles);
  static ReplicateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange replicated, ::mlir::Value pattern, ::mlir::ValueRange handles);
  static ReplicateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange replicated, ::mlir::Value pattern, ::mlir::ValueRange handles);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplicateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReplicateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplicateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReplicateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::ReplicateOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::SelectOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SelectOpGenericAdaptorBase {
public:
  struct Properties {
    using op_nameTy = ::mlir::StringAttr;
    op_nameTy op_name;

    auto getOpName() const {
      auto &propStorage = this->op_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setOpName(const ::mlir::StringAttr &propValue) {
      this->op_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.op_name == this->op_name &&
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
  SelectOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.select", odsAttrs.getContext());
  }

  SelectOpGenericAdaptorBase(SelectOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getOpNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().op_name);
    return attr;
  }

  ::llvm::StringRef getOpName();
};

} // namespace detail
template <typename RangeT>
class SelectOpGenericAdaptor : public detail::SelectOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SelectOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  SelectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SelectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SelectOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SelectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SelectOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SelectOpGenericAdaptor(RangeT values, const SelectOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SelectOp, typename = std::enable_if_t<std::is_same_v<LateInst, SelectOp>>>
  SelectOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SelectOpAdaptor : public SelectOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SelectOpGenericAdaptor::SelectOpGenericAdaptor;
  SelectOpAdaptor(SelectOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SelectOp : public ::mlir::Op<SelectOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::transform::TransformHandleTypeInterface>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::NavigationTransformOpTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SelectOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SelectOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<SelectOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("op_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOpNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOpNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.select");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSResults(0).begin());
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
    return ::llvm::cast<::mlir::StringAttr>(getProperties().op_name);
  }

  ::llvm::StringRef getOpName();
  void setOpNameAttr(::mlir::StringAttr attr) {
    getProperties().op_name = attr;
  }

  void setOpName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value target, ::mlir::StringAttr op_name);
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value target, ::mlir::StringAttr op_name);
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value target, ::mlir::StringAttr op_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::StringAttr op_name);
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::StringAttr op_name);
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::mlir::StringAttr op_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value target, ::llvm::StringRef op_name);
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value target, ::llvm::StringRef op_name);
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value target, ::llvm::StringRef op_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::StringRef op_name);
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::StringRef op_name);
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target, ::llvm::StringRef op_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::SelectOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::SequenceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SequenceOpGenericAdaptorBase {
public:
  struct Properties {
    using failure_propagation_modeTy = ::mlir::transform::FailurePropagationModeAttr;
    failure_propagation_modeTy failure_propagation_mode;

    auto getFailurePropagationMode() const {
      auto &propStorage = this->failure_propagation_mode;
      return ::llvm::cast<::mlir::transform::FailurePropagationModeAttr>(propStorage);
    }
    void setFailurePropagationMode(const ::mlir::transform::FailurePropagationModeAttr &propValue) {
      this->failure_propagation_mode = propValue;
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
        rhs.failure_propagation_mode == this->failure_propagation_mode &&
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
  SequenceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.sequence", odsAttrs.getContext());
  }

  SequenceOpGenericAdaptorBase(SequenceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::transform::FailurePropagationModeAttr getFailurePropagationModeAttr() {
    auto attr = ::llvm::cast<::mlir::transform::FailurePropagationModeAttr>(getProperties().failure_propagation_mode);
    return attr;
  }

  ::mlir::transform::FailurePropagationMode getFailurePropagationMode();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SequenceOpGenericAdaptor : public detail::SequenceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SequenceOpGenericAdaptorBase;
  static constexpr int odsIndex_root = 0;
  static constexpr int odsIndex_extra_bindings = 1;
public:
  SequenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SequenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SequenceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SequenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : SequenceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SequenceOpGenericAdaptor(RangeT values, const SequenceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SequenceOp, typename = std::enable_if_t<std::is_same_v<LateInst, SequenceOp>>>
  SequenceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getExtraBindings() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SequenceOpAdaptor : public SequenceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SequenceOpGenericAdaptor::SequenceOpGenericAdaptor;
  SequenceOpAdaptor(SequenceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SequenceOp : public ::mlir::Op<SequenceOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<::mlir::transform::YieldOp>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::RegionBranchOpInterface::Trait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::MatchOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::transform::PossibleTopLevelTransformOpTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SequenceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SequenceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_root = 0;
  static constexpr int odsIndex_extra_bindings = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchOpInterface::Trait<SequenceOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<SequenceOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<SequenceOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<SequenceOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<SequenceOp>::areTypesCompatible;
  using ::mlir::transform::TransformOpInterface::Trait<SequenceOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("failure_propagation_mode"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFailurePropagationModeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFailurePropagationModeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.sequence");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getRoot() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>{} : ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getExtraBindings() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getRootMutable();
  ::mlir::MutableOperandRange getExtraBindingsMutable();
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
  ::mlir::transform::FailurePropagationModeAttr getFailurePropagationModeAttr() {
    return ::llvm::cast<::mlir::transform::FailurePropagationModeAttr>(getProperties().failure_propagation_mode);
  }

  ::mlir::transform::FailurePropagationMode getFailurePropagationMode();
  void setFailurePropagationModeAttr(::mlir::transform::FailurePropagationModeAttr attr) {
    getProperties().failure_propagation_mode = attr;
  }

  void setFailurePropagationMode(::mlir::transform::FailurePropagationMode attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Value root, SequenceBodyBuilderFn bodyBuilder);
  static SequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Value root, SequenceBodyBuilderFn bodyBuilder);
  static SequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Value root, SequenceBodyBuilderFn bodyBuilder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Value root, ::mlir::ValueRange extraBindings, SequenceBodyBuilderArgsFn bodyBuilder);
  static SequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Value root, ::mlir::ValueRange extraBindings, SequenceBodyBuilderArgsFn bodyBuilder);
  static SequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Value root, ::mlir::ValueRange extraBindings, SequenceBodyBuilderArgsFn bodyBuilder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Type bbArgType, SequenceBodyBuilderFn bodyBuilder);
  static SequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Type bbArgType, SequenceBodyBuilderFn bodyBuilder);
  static SequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Type bbArgType, SequenceBodyBuilderFn bodyBuilder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Type bbArgType, ::mlir::TypeRange extraBindingTypes, SequenceBodyBuilderArgsFn bodyBuilder);
  static SequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Type bbArgType, ::mlir::TypeRange extraBindingTypes, SequenceBodyBuilderArgsFn bodyBuilder);
  static SequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::transform::FailurePropagationMode failure_propagation_mode, ::mlir::Type bbArgType, ::mlir::TypeRange extraBindingTypes, SequenceBodyBuilderArgsFn bodyBuilder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::transform::FailurePropagationModeAttr failure_propagation_mode, /*optional*/::mlir::Value root, ::mlir::ValueRange extra_bindings);
  static SequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::transform::FailurePropagationModeAttr failure_propagation_mode, /*optional*/::mlir::Value root, ::mlir::ValueRange extra_bindings);
  static SequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::transform::FailurePropagationModeAttr failure_propagation_mode, /*optional*/::mlir::Value root, ::mlir::ValueRange extra_bindings);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::transform::FailurePropagationMode failure_propagation_mode, /*optional*/::mlir::Value root, ::mlir::ValueRange extra_bindings);
  static SequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::transform::FailurePropagationMode failure_propagation_mode, /*optional*/::mlir::Value root, ::mlir::ValueRange extra_bindings);
  static SequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::transform::FailurePropagationMode failure_propagation_mode, /*optional*/::mlir::Value root, ::mlir::ValueRange extra_bindings);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SequenceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SequenceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OperandRange getEntrySuccessorOperands(::mlir::RegionSuccessor successor);
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);
  void getRegionInvocationBounds(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> &invocationBounds);
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
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
  /// Allow the dialect prefix to be omitted.
  static StringRef getDefaultDialect() { return "transform"; }
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::SequenceOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::SplitHandleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SplitHandleOpGenericAdaptorBase {
public:
  struct Properties {
    using fail_on_payload_too_smallTy = ::mlir::BoolAttr;
    fail_on_payload_too_smallTy fail_on_payload_too_small;

    auto getFailOnPayloadTooSmall() const {
      auto &propStorage = this->fail_on_payload_too_small;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setFailOnPayloadTooSmall(const ::mlir::BoolAttr &propValue) {
      this->fail_on_payload_too_small = propValue;
    }
    using overflow_resultTy = ::mlir::IntegerAttr;
    overflow_resultTy overflow_result;

    auto getOverflowResult() const {
      auto &propStorage = this->overflow_result;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setOverflowResult(const ::mlir::IntegerAttr &propValue) {
      this->overflow_result = propValue;
    }
    using pass_through_empty_handleTy = ::mlir::BoolAttr;
    pass_through_empty_handleTy pass_through_empty_handle;

    auto getPassThroughEmptyHandle() const {
      auto &propStorage = this->pass_through_empty_handle;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setPassThroughEmptyHandle(const ::mlir::BoolAttr &propValue) {
      this->pass_through_empty_handle = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fail_on_payload_too_small == this->fail_on_payload_too_small &&
        rhs.overflow_result == this->overflow_result &&
        rhs.pass_through_empty_handle == this->pass_through_empty_handle &&
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
  SplitHandleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.split_handle", odsAttrs.getContext());
  }

  SplitHandleOpGenericAdaptorBase(SplitHandleOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getPassThroughEmptyHandleAttr();
  bool getPassThroughEmptyHandle();
  ::mlir::BoolAttr getFailOnPayloadTooSmallAttr();
  bool getFailOnPayloadTooSmall();
  ::mlir::IntegerAttr getOverflowResultAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().overflow_result);
    return attr;
  }

  ::std::optional<uint64_t> getOverflowResult();
};

} // namespace detail
template <typename RangeT>
class SplitHandleOpGenericAdaptor : public detail::SplitHandleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SplitHandleOpGenericAdaptorBase;
  static constexpr int odsIndex_handle = 0;
public:
  SplitHandleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SplitHandleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SplitHandleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SplitHandleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SplitHandleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SplitHandleOpGenericAdaptor(RangeT values, const SplitHandleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SplitHandleOp, typename = std::enable_if_t<std::is_same_v<LateInst, SplitHandleOp>>>
  SplitHandleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getHandle() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SplitHandleOpAdaptor : public SplitHandleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SplitHandleOpGenericAdaptor::SplitHandleOpGenericAdaptor;
  SplitHandleOpAdaptor(SplitHandleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SplitHandleOp : public ::mlir::Op<SplitHandleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::transform::FunctionalStyleTransformOpTrait, ::mlir::transform::TransformOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SplitHandleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SplitHandleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_handle = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::transform::TransformOpInterface::Trait<SplitHandleOp>::allowsRepeatedHandleOperands;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fail_on_payload_too_small"), ::llvm::StringRef("overflow_result"), ::llvm::StringRef("pass_through_empty_handle")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFailOnPayloadTooSmallAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFailOnPayloadTooSmallAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOverflowResultAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getOverflowResultAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPassThroughEmptyHandleAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPassThroughEmptyHandleAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.split_handle");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getHandle() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getHandleMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
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
  ::mlir::BoolAttr getPassThroughEmptyHandleAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().pass_through_empty_handle);
  }

  bool getPassThroughEmptyHandle();
  ::mlir::BoolAttr getFailOnPayloadTooSmallAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().fail_on_payload_too_small);
  }

  bool getFailOnPayloadTooSmall();
  ::mlir::IntegerAttr getOverflowResultAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().overflow_result);
  }

  ::std::optional<uint64_t> getOverflowResult();
  void setPassThroughEmptyHandleAttr(::mlir::BoolAttr attr) {
    getProperties().pass_through_empty_handle = attr;
  }

  void setPassThroughEmptyHandle(bool attrValue);
  void setFailOnPayloadTooSmallAttr(::mlir::BoolAttr attr) {
    getProperties().fail_on_payload_too_small = attr;
  }

  void setFailOnPayloadTooSmall(bool attrValue);
  void setOverflowResultAttr(::mlir::IntegerAttr attr) {
    getProperties().overflow_result = attr;
  }

  void setOverflowResult(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeOverflowResultAttr() {
      auto attr = getProperties().overflow_result;
      getProperties().overflow_result = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value handle, int64_t numResultHandles);
  static SplitHandleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value handle, int64_t numResultHandles);
  static SplitHandleOp create(::mlir::ImplicitLocOpBuilder &builder, Value handle, int64_t numResultHandles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value handle, ::mlir::BoolAttr pass_through_empty_handle, ::mlir::BoolAttr fail_on_payload_too_small, /*optional*/::mlir::IntegerAttr overflow_result);
  static SplitHandleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value handle, ::mlir::BoolAttr pass_through_empty_handle, ::mlir::BoolAttr fail_on_payload_too_small, /*optional*/::mlir::IntegerAttr overflow_result);
  static SplitHandleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value handle, ::mlir::BoolAttr pass_through_empty_handle, ::mlir::BoolAttr fail_on_payload_too_small, /*optional*/::mlir::IntegerAttr overflow_result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value handle, bool pass_through_empty_handle, bool fail_on_payload_too_small, /*optional*/::mlir::IntegerAttr overflow_result);
  static SplitHandleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value handle, bool pass_through_empty_handle, bool fail_on_payload_too_small, /*optional*/::mlir::IntegerAttr overflow_result);
  static SplitHandleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value handle, bool pass_through_empty_handle, bool fail_on_payload_too_small, /*optional*/::mlir::IntegerAttr overflow_result);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SplitHandleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SplitHandleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SplitHandleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SplitHandleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::DiagnosedSilenceableFailure apply(::mlir::transform::TransformRewriter &rewriter, ::mlir::transform::TransformResults &transformResults, ::mlir::transform::TransformState &state);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::SplitHandleOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::VerifyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class VerifyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  VerifyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("transform.verify", odsAttrs.getContext());
  }

  VerifyOpGenericAdaptorBase(VerifyOp op);

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
class VerifyOpGenericAdaptor : public detail::VerifyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::VerifyOpGenericAdaptorBase;
  static constexpr int odsIndex_target = 0;
public:
  VerifyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  VerifyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : VerifyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  VerifyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : VerifyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  VerifyOpGenericAdaptor(RangeT values, const VerifyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = VerifyOp, typename = std::enable_if_t<std::is_same_v<LateInst, VerifyOp>>>
  VerifyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTarget() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class VerifyOpAdaptor : public VerifyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using VerifyOpGenericAdaptor::VerifyOpGenericAdaptor;
  VerifyOpAdaptor(VerifyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class VerifyOp : public ::mlir::Op<VerifyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::transform::TransformOpInterface::Trait, ::mlir::transform::TransformEachOpTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::transform::ReportTrackingListenerFailuresOpTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = VerifyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = VerifyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_target = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.verify");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::transform::TransformHandleTypeInterface>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTargetMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value target);
  static VerifyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value target);
  static VerifyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value target);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static VerifyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static VerifyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value target);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VerifyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VerifyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VerifyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VerifyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  ::mlir::DiagnosedSilenceableFailure applyToOne(
    ::mlir::transform::TransformRewriter &rewriter,
    ::mlir::Operation *target,
    ::mlir::transform::ApplyToEachResultList &results,
    ::mlir::transform::TransformState &state);
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::VerifyOp)

namespace mlir::transform {


//===----------------------------------------------------------------------===//
// ::mlir::transform::YieldOp declarations
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
      odsOpName.emplace("transform.yield", odsAttrs.getContext());
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
  static constexpr int odsIndex_operands = 0;
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

  RangeT getOperands() {
    return getODSOperands(0);
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
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = YieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = YieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("transform.yield");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getOperandsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::transform
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::transform::YieldOp)


#endif // GET_OP_CLASSES

