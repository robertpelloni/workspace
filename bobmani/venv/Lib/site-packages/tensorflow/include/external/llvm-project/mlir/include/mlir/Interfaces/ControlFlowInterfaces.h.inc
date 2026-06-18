/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// This interface provides information for branching terminator operations,
///     i.e. terminator operations with successors.
/// 
///     This interface is meant to model well-defined cases of control-flow of
///     value propagation, where what occurs along control-flow edges is assumed to
///     be side-effect free. For example, corresponding successor operands and
///     successor block arguments may have different types. In such cases,
///     `areTypesCompatible` can be implemented to compare types along control-flow
///     edges. By default, type equality is used.
class BranchOpInterface;

} // namespace mlir
namespace mlir {

/// This interface provides information for region-holding operations that
///     exhibit branching behavior between held regions. I.e., this interface allows
///     for expressing control flow information for region holding operations.
/// 
///     This interface is meant to model well-defined cases of control-flow and
///     value propagation, where what occurs along control-flow edges is assumed to
///     be side-effect free.
/// 
///     A "region branch point" indicates a point from which a branch originates. It
///     can indicate:
///     1. A `RegionBranchTerminatorOpInterface` terminator in any of the
///        immediately nested regions of this op.
///     2. `RegionBranchPoint::parent()`: the branch originates from outside of the
///        op, i.e., when first executing this op.
/// 
///     When branching from a region branch point to a region successor, the
///     "successor operands" to be forwarded from the region branch point can be
///     specified with `getEntrySuccessorOperands` /
///     `RegionBranchTerminatorOpInterface::getSuccessorOperands`.
/// 
///     A "region successor" indicates the target of a branch. It can indicate:
///     1. A region of this op.
///     2. `RegionSuccessor::parent()`, i.e., the control flow leaves this op.
/// 
///     The SSA values to which successor operands are forwarded are called
///     "successor inputs".
/// 
///     By default, successor operands and successor block arguments/successor
///     results must have the same type. `areTypesCompatible` can be implemented to
///     allow non-equal types.
/// 
/// 
///     Note: This interface works in conjunction with
///     `RegionBranchTerminatorOpInterface`. All immediately nested block
///     terminators that model branching between regions must implement the
///     `RegionBranchTerminatorOpInterface`. Otherwise, analyses/transformations
///     may miss control flow edges and produce incorrect results. Not every block
///     terminator is necessarily a region branch terminator: e.g., in the presence
///     of unstructured control flow, a block terminator could indicate a branch to
///     a different block within the same region.
/// 
///     Example:
/// 
///     ```
///     %r = scf.for %iv = %lb to %ub step %step iter_args(%a = %b)
///         -> tensor<5xf32> {
///       ...
///       scf.yield %c : tensor<5xf32>
///     }
///     ```
/// 
///     `scf.for` has one region. There are two region branch points with two
///     identical region successors:
///     * parent => parent(%r), region0(%a)
///     * `scf.yield` => parent(%r), region0(%a)
/// 
///     `%a` and %r are successor inputs. `%b` is an entry successor operand. `%c`
///     is a successor operand.
class RegionBranchOpInterface;

} // namespace mlir
namespace mlir {

/// This interface provides information for branching terminator operations
///     in the presence of a parent `RegionBranchOpInterface` implementation. It
///     acts as a marker for valid region branch points and specifies which
///     operands are passed to which region successor.
/// 
///     Note: If an operation does not implement the
///     `RegionBranchTerminatorOpInterface`, then that op has no region successors.
///     (However, there may be other block terminators in the same region that
///     implement the `RegionBranchTerminatorOpInterface`, so the enclosing region
///     may have region successors.)
class RegionBranchTerminatorOpInterface;

} // namespace mlir
namespace mlir {

/// This interface provides information for select-like operations, i.e.,
///     operations that forward specific operands to the output, depending on a
///     binary condition.
/// 
///     If the value of the condition is 1, then the `true` operand is returned,
///     and the third operand is ignored, even if it was poison.
/// 
///     If the value of the condition is 0, then the `false` operand is returned,
///     and the second operand is ignored, even if it was poison.
/// 
///     If the condition is poison, then poison is returned.
/// 
///     Implementing operations can also accept shaped conditions, in which case
///     the operation works element-wise.
class SelectLikeOpInterface;

} // namespace mlir
namespace mlir {

/// This interface provides weight information for branching terminator
///     operations, i.e. terminator operations with successors.
/// 
///     This interface provides methods for getting/setting integer weights of each
///     branch. The probability of executing a branch is computed as the ratio
///     between the branch's weight and the total sum of the weights (which cannot
///     be zero). The weights are optional. If they are provided, then their number
///     must match the number of successors of the operation.
/// 
///     Note that the branch weight use an i32 representation but they are to be
///     interpreted as unsigned integers.
/// 
///     The default implementations of the methods expect the operation
///     to have an attribute of type DenseI32ArrayAttr named branch_weights.
class WeightedBranchOpInterface;

} // namespace mlir
namespace mlir {

/// This interface provides weight information for region operations
///     that exhibit branching behavior between held regions.
/// 
///     This interface provides methods for getting/setting integer weights of each
///     branch. The probability of executing a region is computed as the ratio
///     between the region branch's weight and the total sum of the weights (which
///     cannot be zero). The weights are optional. If they are provided, then their
///     number must match the number of regions held by the operation (including
///     empty regions).
/// 
///     The weights specify the probability of branching to a particular
///     region when first executing the operation.
///     For example, for loop-like operations with a single region
///     the weight specifies the probability of entering the loop.
/// 
///     Note that the branch weight use an i32 representation but they are to be
///     interpreted as unsigned integers.
/// 
///     The default implementations of the methods expect the operation
///     to have an attribute of type DenseI32ArrayAttr named branch_weights.
class WeightedRegionBranchOpInterface;

} // namespace mlir
namespace mlir {

/// This interface provides information for branching terminator operations,
///     i.e. terminator operations with successors.
/// 
///     This interface is meant to model well-defined cases of control-flow of
///     value propagation, where what occurs along control-flow edges is assumed to
///     be side-effect free. For example, corresponding successor operands and
///     successor block arguments may have different types. In such cases,
///     `areTypesCompatible` can be implemented to compare types along control-flow
///     edges. By default, type equality is used.
namespace detail {
struct BranchOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::SuccessorOperands (*getSuccessorOperands)(const Concept *impl, ::mlir::Operation *, unsigned);
    ::std::optional<::mlir::BlockArgument> (*getSuccessorBlockArgument)(const Concept *impl, ::mlir::Operation *, unsigned);
    ::mlir::Block *(*getSuccessorForOperands)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<::mlir::Attribute>);
    bool (*areTypesCompatible)(const Concept *impl, ::mlir::Operation *, ::mlir::Type, ::mlir::Type);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::BranchOpInterface;
    Model() : Concept{getSuccessorOperands, getSuccessorBlockArgument, getSuccessorForOperands, areTypesCompatible} {}

    static inline ::mlir::SuccessorOperands getSuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index);
    static inline ::std::optional<::mlir::BlockArgument> getSuccessorBlockArgument(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned operandIndex);
    static inline ::mlir::Block *getSuccessorForOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands);
    static inline bool areTypesCompatible(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::BranchOpInterface;
    FallbackModel() : Concept{getSuccessorOperands, getSuccessorBlockArgument, getSuccessorForOperands, areTypesCompatible} {}

    static inline ::mlir::SuccessorOperands getSuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index);
    static inline ::std::optional<::mlir::BlockArgument> getSuccessorBlockArgument(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned operandIndex);
    static inline ::mlir::Block *getSuccessorForOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands);
    static inline bool areTypesCompatible(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::mlir::Block *getSuccessorForOperands(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands) const;
    bool areTypesCompatible(::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs) const;
  };
};
template <typename ConcreteOp>
struct BranchOpInterfaceTrait;

} // namespace detail
class BranchOpInterface : public ::mlir::OpInterface<BranchOpInterface, detail::BranchOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<BranchOpInterface, detail::BranchOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::BranchOpInterfaceTrait<ConcreteOp> {};

  /// Returns the operands that correspond to the arguments of the successor
  /// at the given index. It consists of a number of operands that are
  /// internally produced by the operation, followed by a range of operands
  /// that are forwarded. An example operation making use of produced
  /// operands would be:
  /// 
  /// ```mlir
  /// invoke %function(%0)
  ///     label ^success ^error(%1 : i32)
  /// 
  /// ^error(%e: !error, %arg0: i32):
  ///     ...
  /// ```
  /// 
  /// The operand that would map to the `^error`s `%e` operand is produced
  /// by the `invoke` operation, while `%1` is a forwarded operand that maps
  /// to `%arg0` in the successor.
  /// 
  /// Produced operands always map to the first few block arguments of the
  /// successor, followed by the forwarded operands. Mapping them in any
  /// other order is not supported by the interface.
  /// 
  /// By having the forwarded operands last allows users of the interface
  /// to append more forwarded operands to the branch operation without
  /// interfering with other successor operands.
  ::mlir::SuccessorOperands getSuccessorOperands(unsigned index);

  /// Returns the `BlockArgument` corresponding to operand `operandIndex` in
  /// some successor, or std::nullopt if `operandIndex` isn't a successor operand
  /// index.
  ::std::optional<::mlir::BlockArgument> getSuccessorBlockArgument(unsigned operandIndex);

  /// Returns the successor that would be chosen with the given constant
  /// operands. Returns nullptr if a single successor could not be chosen.
  ::mlir::Block *getSuccessorForOperands(::llvm::ArrayRef<::mlir::Attribute> operands);

  /// This method is called to compare types along control-flow edges. By
  /// default, the types are checked as equal.
  bool areTypesCompatible(::mlir::Type lhs, ::mlir::Type rhs);
};

} // namespace mlir
namespace mlir {

/// This interface provides information for region-holding operations that
///     exhibit branching behavior between held regions. I.e., this interface allows
///     for expressing control flow information for region holding operations.
/// 
///     This interface is meant to model well-defined cases of control-flow and
///     value propagation, where what occurs along control-flow edges is assumed to
///     be side-effect free.
/// 
///     A "region branch point" indicates a point from which a branch originates. It
///     can indicate:
///     1. A `RegionBranchTerminatorOpInterface` terminator in any of the
///        immediately nested regions of this op.
///     2. `RegionBranchPoint::parent()`: the branch originates from outside of the
///        op, i.e., when first executing this op.
/// 
///     When branching from a region branch point to a region successor, the
///     "successor operands" to be forwarded from the region branch point can be
///     specified with `getEntrySuccessorOperands` /
///     `RegionBranchTerminatorOpInterface::getSuccessorOperands`.
/// 
///     A "region successor" indicates the target of a branch. It can indicate:
///     1. A region of this op.
///     2. `RegionSuccessor::parent()`, i.e., the control flow leaves this op.
/// 
///     The SSA values to which successor operands are forwarded are called
///     "successor inputs".
/// 
///     By default, successor operands and successor block arguments/successor
///     results must have the same type. `areTypesCompatible` can be implemented to
///     allow non-equal types.
/// 
/// 
///     Note: This interface works in conjunction with
///     `RegionBranchTerminatorOpInterface`. All immediately nested block
///     terminators that model branching between regions must implement the
///     `RegionBranchTerminatorOpInterface`. Otherwise, analyses/transformations
///     may miss control flow edges and produce incorrect results. Not every block
///     terminator is necessarily a region branch terminator: e.g., in the presence
///     of unstructured control flow, a block terminator could indicate a branch to
///     a different block within the same region.
/// 
///     Example:
/// 
///     ```
///     %r = scf.for %iv = %lb to %ub step %step iter_args(%a = %b)
///         -> tensor<5xf32> {
///       ...
///       scf.yield %c : tensor<5xf32>
///     }
///     ```
/// 
///     `scf.for` has one region. There are two region branch points with two
///     identical region successors:
///     * parent => parent(%r), region0(%a)
///     * `scf.yield` => parent(%r), region0(%a)
/// 
///     `%a` and %r are successor inputs. `%b` is an entry successor operand. `%c`
///     is a successor operand.
namespace detail {
struct RegionBranchOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::OperandRange (*getEntrySuccessorOperands)(const Concept *impl, ::mlir::Operation *, ::mlir::RegionSuccessor);
    void (*getEntrySuccessorRegions)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<::mlir::Attribute>, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &);
    void (*getSuccessorRegions)(const Concept *impl, ::mlir::Operation *, ::mlir::RegionBranchPoint, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &);
    void (*getSuccessorRegions_3)(const Concept *impl, ::mlir::Operation *, ::mlir::Region&, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &);
    ::mlir::ValueRange (*getSuccessorInputs)(const Concept *impl, ::mlir::Operation *, ::mlir::RegionSuccessor);
    void (*getPredecessors)(const Concept *impl, ::mlir::Operation *, ::mlir::RegionSuccessor, ::llvm::SmallVectorImpl<::mlir::RegionBranchPoint> &);
    void (*getPredecessorValues)(const Concept *impl, ::mlir::Operation *, ::mlir::RegionSuccessor, int, ::llvm::SmallVectorImpl<::mlir::Value> &);
    void (*getRegionInvocationBounds)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<::mlir::Attribute>, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> &);
    bool (*areTypesCompatible)(const Concept *impl, ::mlir::Operation *, ::mlir::Type, ::mlir::Type);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::RegionBranchOpInterface;
    Model() : Concept{getEntrySuccessorOperands, getEntrySuccessorRegions, getSuccessorRegions, getSuccessorRegions_3, getSuccessorInputs, getPredecessors, getPredecessorValues, getRegionInvocationBounds, areTypesCompatible} {}

    static inline ::mlir::OperandRange getEntrySuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor);
    static inline void getEntrySuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);
    static inline void getSuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);
    static inline void getSuccessorRegions_3(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Region& region, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);
    static inline ::mlir::ValueRange getSuccessorInputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor);
    static inline void getPredecessors(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, ::llvm::SmallVectorImpl<::mlir::RegionBranchPoint> & predecessors);
    static inline void getPredecessorValues(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, int index, ::llvm::SmallVectorImpl<::mlir::Value> & predecessorValues);
    static inline void getRegionInvocationBounds(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> & invocationBounds);
    static inline bool areTypesCompatible(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::RegionBranchOpInterface;
    FallbackModel() : Concept{getEntrySuccessorOperands, getEntrySuccessorRegions, getSuccessorRegions, getSuccessorRegions_3, getSuccessorInputs, getPredecessors, getPredecessorValues, getRegionInvocationBounds, areTypesCompatible} {}

    static inline ::mlir::OperandRange getEntrySuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor);
    static inline void getEntrySuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);
    static inline void getSuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);
    static inline void getSuccessorRegions_3(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Region& region, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);
    static inline ::mlir::ValueRange getSuccessorInputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor);
    static inline void getPredecessors(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, ::llvm::SmallVectorImpl<::mlir::RegionBranchPoint> & predecessors);
    static inline void getPredecessorValues(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, int index, ::llvm::SmallVectorImpl<::mlir::Value> & predecessorValues);
    static inline void getRegionInvocationBounds(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> & invocationBounds);
    static inline bool areTypesCompatible(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::mlir::OperandRange getEntrySuccessorOperands(::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor) const;
    void getEntrySuccessorRegions(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions) const;
    void getSuccessorRegions_3(::mlir::Operation *tablegen_opaque_val, ::mlir::Region&region, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions) const;
    ::mlir::ValueRange getSuccessorInputs(::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor) const;
    void getPredecessors(::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, ::llvm::SmallVectorImpl<::mlir::RegionBranchPoint> &predecessors) const;
    void getPredecessorValues(::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, int index, ::llvm::SmallVectorImpl<::mlir::Value> &predecessorValues) const;
    void getRegionInvocationBounds(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> &invocationBounds) const;
    bool areTypesCompatible(::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs) const;
  };
};
template <typename ConcreteOp>
struct RegionBranchOpInterfaceTrait;

} // namespace detail
class RegionBranchOpInterface : public ::mlir::OpInterface<RegionBranchOpInterface, detail::RegionBranchOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<RegionBranchOpInterface, detail::RegionBranchOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::RegionBranchOpInterfaceTrait<ConcreteOp> {};

  /// Returns the operands of this operation that are forwarded to the
  /// successor inputs when branching to `successor`. `successor` is
  /// guaranteed to be among the successors that are returned by
  /// `getEntrySuccessorRegions`/`getSuccessorRegions(parent())`.
  /// 
  /// Example: In the above example, this method returns the operand %b of the
  /// `scf.for` op, regardless of the value of `successor`. I.e., this op always
  /// forwards the same operands, regardless of whether the loop has 0 or more
  /// iterations.
  ::mlir::OperandRange getEntrySuccessorOperands(::mlir::RegionSuccessor successor);

  /// Returns the potential region successors when first executing the op.
  /// 
  /// Unlike `getSuccessorRegions`, this method also passes along the
  /// constant operands of this op. Based on these, the implementation may
  /// filter out certain successors. By default, simply dispatches to
  /// `getSuccessorRegions`. `operands` contains an entry for every
  /// operand of this op, with a null attribute if the operand has no constant
  /// value.
  /// 
  /// Note: The control flow does not necessarily have to enter any region of
  /// this op.
  /// 
  /// Example: In the above example, this method may return two region
  /// region successors: the single region of the `scf.for` op and the
  /// `scf.for` operation (that implements this interface). If %lb, %ub, %step
  /// are constants and it can be determined the loop does not have any
  /// iterations, this method may choose to return only this operation.
  /// Similarly, if it can be determined that the loop has at least one
  /// iteration, this method may choose to return only the region of the loop.
  void getEntrySuccessorRegions(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);

  /// Returns all potential region successors when branching from `point`.
  /// These are the regions that may be selected during the flow of control.
  /// 
  /// When `point = RegionBranchPoint::parent()`, this method returns the
  /// region successors when entering the operation. Otherwise, this method
  /// returns the successor regions when branching from the region indicated
  /// by `point`.
  /// 
  /// Example: In the above example, this method returns the region of the
  /// `scf.for` and `parent` for either region branch point. An implementation
  /// may choose to filter out region successors when it is statically known
  /// (e.g., by examining the operands of this op) that those successors are
  /// not branched to.
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);

  /// Returns the potential region successors when branching from any
  /// terminator in `region`.
  void getSuccessorRegions(::mlir::Region& region, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);

  /// Return all successor inputs for the given region successor. If the
  /// given region successor is a region, then the returned values are block
  /// arguments. Otherwise, if the given region successor is the "parent",
  /// the returned values are op results.
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);

  /// Returns the potential branching points (predecessors) for a given
  /// region successor.
  void getPredecessors(::mlir::RegionSuccessor successor, ::llvm::SmallVectorImpl<::mlir::RegionBranchPoint> & predecessors);

  /// Returns the potential values across all (predecessors) for a given successor
  /// input, modeled by its index (its position in the list of values).
  void getPredecessorValues(::mlir::RegionSuccessor successor, int index, ::llvm::SmallVectorImpl<::mlir::Value> & predecessorValues);

  /// Populates `invocationBounds` with the minimum and maximum number of
  /// times this operation will invoke the attached regions (assuming the
  /// regions yield normally, i.e. do not abort or invoke an infinite loop).
  /// The minimum number of invocations is at least 0. If the maximum number
  /// of invocations cannot be statically determined, then it will be set to
  /// `InvocationBounds::getUnknown()`.
  /// 
  /// This method also passes along the constant operands of this op.
  /// `operands` contains an entry for every operand of this op, with a null
  /// attribute if the operand has no constant value.
  /// 
  /// This method may be called speculatively on operations where the provided
  /// operands are not necessarily the same as the operation's current
  /// operands. This may occur in analyses that wish to determine "what would
  /// be the region invocations if these were the operands?"
  void getRegionInvocationBounds(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> & invocationBounds);

  /// This method is called to compare types along control-flow edges. By
  /// default, the types are checked as equal.
  bool areTypesCompatible(::mlir::Type lhs, ::mlir::Type rhs);

    /// Return `true` if control flow originating from the given region may
    /// eventually branch back to the same region. (Maybe after passing through
    /// other regions.)
    bool isRepetitiveRegion(unsigned index);

    /// Return `true` if there is a loop in the region branching graph. Only
    /// reachable regions (starting from the entry regions) are considered.
    bool hasLoop();

    /// Return the successor operands from the source branch point to the
    /// destination region successor.
    ///
    /// If the branch point is the parent op, this function returns entry
    /// successor operands of this op. Otherwise, it returns successor operands
    /// of the respective terminator.
    ::mlir::OperandRange getSuccessorOperands(
        ::mlir::RegionBranchPoint src, ::mlir::RegionSuccessor dest);

    /// Return all successor inputs for the given region successor.
    ///
    /// If the "successor" is a region, it will return non-forwarded arguments,
    /// if it is a "parent", it will return non-forwarded results.
    ::llvm::SmallVector<Value> getNonSuccessorInputs(
        ::mlir::RegionSuccessor successor);

    /// Build a mapping from successor operands to successor input. Each
    /// successor operand could be forwarded to multiple successor inputs.
    /// Operands that are not forwarded are not added to the map. Unless a
    /// specific region branch point is specified, this function takes into
    /// account all possible region branch points.
    void getSuccessorOperandInputMapping(
        ::mlir::RegionBranchSuccessorMapping &mapping,
        std::optional<::mlir::RegionBranchPoint> src = std::nullopt);

    /// Build a mapping from successor inputs to successor operands. This is
    /// the same as "getSuccessorOperandInputMapping", but inverted.
    void getSuccessorInputOperandMapping(
        ::mlir::RegionBranchInverseSuccessorMapping &mapping);

    /// Return all possible region branch points: the region branch op itself
    /// and all region branch terminators.
    ::llvm::SmallVector<::mlir::RegionBranchPoint> getAllRegionBranchPoints();
};

} // namespace mlir
namespace mlir {

/// This interface provides information for branching terminator operations
///     in the presence of a parent `RegionBranchOpInterface` implementation. It
///     acts as a marker for valid region branch points and specifies which
///     operands are passed to which region successor.
/// 
///     Note: If an operation does not implement the
///     `RegionBranchTerminatorOpInterface`, then that op has no region successors.
///     (However, there may be other block terminators in the same region that
///     implement the `RegionBranchTerminatorOpInterface`, so the enclosing region
///     may have region successors.)
namespace detail {
struct RegionBranchTerminatorOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::MutableOperandRange (*getMutableSuccessorOperands)(const Concept *impl, ::mlir::Operation *, ::mlir::RegionSuccessor);
    void (*getSuccessorRegions)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<::mlir::Attribute>, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::RegionBranchTerminatorOpInterface;
    Model() : Concept{getMutableSuccessorOperands, getSuccessorRegions} {}

    static inline ::mlir::MutableOperandRange getMutableSuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor point);
    static inline void getSuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::RegionBranchTerminatorOpInterface;
    FallbackModel() : Concept{getMutableSuccessorOperands, getSuccessorRegions} {}

    static inline ::mlir::MutableOperandRange getMutableSuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor point);
    static inline void getSuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    void getSuccessorRegions(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions) const;
  };
};
template <typename ConcreteOp>
struct RegionBranchTerminatorOpInterfaceTrait;

} // namespace detail
class RegionBranchTerminatorOpInterface : public ::mlir::OpInterface<RegionBranchTerminatorOpInterface, detail::RegionBranchTerminatorOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<RegionBranchTerminatorOpInterface, detail::RegionBranchTerminatorOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::RegionBranchTerminatorOpInterfaceTrait<ConcreteOp> {};

  /// Returns a mutable range of operands that are semantically "returned" by
  /// passing them to the region successor indicated by `point`.
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);

  /// Returns the potential region successors that are branched to after this
  /// terminator based on the given constant operands.
  /// 
  /// This method also passes along the constant operands of this op.
  /// `operands` contains an entry for every operand of this op, with a null
  /// attribute if the operand has no constant value.
  /// 
  /// The default implementation simply dispatches to the parent
  /// `RegionBranchOpInterface`'s `getSuccessorRegions` implementation.
  void getSuccessorRegions(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions);

    // Returns a range of operands that are semantically "returned" by passing
    // them to the region successor given by `index`.  If `index` is None, this
    // function returns the operands that are passed as a result to the parent
    // operation.
    ::mlir::OperandRange getSuccessorOperands(::mlir::RegionSuccessor successor) {
      return getMutableSuccessorOperands(successor);
    }
};

} // namespace mlir
namespace mlir {

/// This interface provides information for select-like operations, i.e.,
///     operations that forward specific operands to the output, depending on a
///     binary condition.
/// 
///     If the value of the condition is 1, then the `true` operand is returned,
///     and the third operand is ignored, even if it was poison.
/// 
///     If the value of the condition is 0, then the `false` operand is returned,
///     and the second operand is ignored, even if it was poison.
/// 
///     If the condition is poison, then poison is returned.
/// 
///     Implementing operations can also accept shaped conditions, in which case
///     the operation works element-wise.
namespace detail {
struct SelectLikeOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::Value (*getFalseValue)(const Concept *impl, ::mlir::Operation *);
    ::mlir::Value (*getTrueValue)(const Concept *impl, ::mlir::Operation *);
    ::mlir::Value (*getCondition)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::SelectLikeOpInterface;
    Model() : Concept{getFalseValue, getTrueValue, getCondition} {}

    static inline ::mlir::Value getFalseValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Value getTrueValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Value getCondition(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::SelectLikeOpInterface;
    FallbackModel() : Concept{getFalseValue, getTrueValue, getCondition} {}

    static inline ::mlir::Value getFalseValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Value getTrueValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Value getCondition(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct SelectLikeOpInterfaceTrait;

} // namespace detail
class SelectLikeOpInterface : public ::mlir::OpInterface<SelectLikeOpInterface, detail::SelectLikeOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<SelectLikeOpInterface, detail::SelectLikeOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::SelectLikeOpInterfaceTrait<ConcreteOp> {};

  /// Returns the operand that would be chosen for a false condition.
  ::mlir::Value getFalseValue();

  /// Returns the operand that would be chosen for a true condition.
  ::mlir::Value getTrueValue();

  /// Returns the condition operand.
  ::mlir::Value getCondition();
};

} // namespace mlir
namespace mlir {

/// This interface provides weight information for branching terminator
///     operations, i.e. terminator operations with successors.
/// 
///     This interface provides methods for getting/setting integer weights of each
///     branch. The probability of executing a branch is computed as the ratio
///     between the branch's weight and the total sum of the weights (which cannot
///     be zero). The weights are optional. If they are provided, then their number
///     must match the number of successors of the operation.
/// 
///     Note that the branch weight use an i32 representation but they are to be
///     interpreted as unsigned integers.
/// 
///     The default implementations of the methods expect the operation
///     to have an attribute of type DenseI32ArrayAttr named branch_weights.
namespace detail {
struct WeightedBranchOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::ArrayRef<int32_t> (*getWeights)(const Concept *impl, ::mlir::Operation *);
    void (*setWeights)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<int32_t>);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::WeightedBranchOpInterface;
    Model() : Concept{getWeights, setWeights} {}

    static inline ::llvm::ArrayRef<int32_t> getWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::WeightedBranchOpInterface;
    FallbackModel() : Concept{getWeights, setWeights} {}

    static inline ::llvm::ArrayRef<int32_t> getWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::llvm::ArrayRef<int32_t> getWeights(::mlir::Operation *tablegen_opaque_val) const;
    void setWeights(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights) const;
  };
};
template <typename ConcreteOp>
struct WeightedBranchOpInterfaceTrait;

} // namespace detail
class WeightedBranchOpInterface : public ::mlir::OpInterface<WeightedBranchOpInterface, detail::WeightedBranchOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<WeightedBranchOpInterface, detail::WeightedBranchOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::WeightedBranchOpInterfaceTrait<ConcreteOp> {};

  /// Returns the branch weights
  ::llvm::ArrayRef<int32_t> getWeights();

  /// Sets the branch weights
  void setWeights(::llvm::ArrayRef<int32_t> weights);
};

} // namespace mlir
namespace mlir {

/// This interface provides weight information for region operations
///     that exhibit branching behavior between held regions.
/// 
///     This interface provides methods for getting/setting integer weights of each
///     branch. The probability of executing a region is computed as the ratio
///     between the region branch's weight and the total sum of the weights (which
///     cannot be zero). The weights are optional. If they are provided, then their
///     number must match the number of regions held by the operation (including
///     empty regions).
/// 
///     The weights specify the probability of branching to a particular
///     region when first executing the operation.
///     For example, for loop-like operations with a single region
///     the weight specifies the probability of entering the loop.
/// 
///     Note that the branch weight use an i32 representation but they are to be
///     interpreted as unsigned integers.
/// 
///     The default implementations of the methods expect the operation
///     to have an attribute of type DenseI32ArrayAttr named branch_weights.
namespace detail {
struct WeightedRegionBranchOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::ArrayRef<int32_t> (*getWeights)(const Concept *impl, ::mlir::Operation *);
    void (*setWeights)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<int32_t>);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::WeightedRegionBranchOpInterface;
    Model() : Concept{getWeights, setWeights} {}

    static inline ::llvm::ArrayRef<int32_t> getWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::WeightedRegionBranchOpInterface;
    FallbackModel() : Concept{getWeights, setWeights} {}

    static inline ::llvm::ArrayRef<int32_t> getWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::llvm::ArrayRef<int32_t> getWeights(::mlir::Operation *tablegen_opaque_val) const;
    void setWeights(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights) const;
  };
};
template <typename ConcreteOp>
struct WeightedRegionBranchOpInterfaceTrait;

} // namespace detail
class WeightedRegionBranchOpInterface : public ::mlir::OpInterface<WeightedRegionBranchOpInterface, detail::WeightedRegionBranchOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<WeightedRegionBranchOpInterface, detail::WeightedRegionBranchOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::WeightedRegionBranchOpInterfaceTrait<ConcreteOp> {};

  /// Returns the region weights
  ::llvm::ArrayRef<int32_t> getWeights();

  /// Sets the region weights
  void setWeights(::llvm::ArrayRef<int32_t> weights);
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteOp>
  struct BranchOpInterfaceTrait : public ::mlir::OpInterface<BranchOpInterface, detail::BranchOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns the successor that would be chosen with the given constant
    /// operands. Returns nullptr if a single successor could not be chosen.
    ::mlir::Block *getSuccessorForOperands(::llvm::ArrayRef<::mlir::Attribute> operands) {
      return nullptr;
    }

    /// This method is called to compare types along control-flow edges. By
    /// default, the types are checked as equal.
    bool areTypesCompatible(::mlir::Type lhs, ::mlir::Type rhs) {
      return lhs == rhs;
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      auto concreteOp = ::mlir::cast<ConcreteOp>(op);
    for (unsigned i = 0, e = op->getNumSuccessors(); i != e; ++i) {
      ::mlir::SuccessorOperands operands = concreteOp.getSuccessorOperands(i);
      if (::mlir::failed(::mlir::detail::verifyBranchSuccessorOperands(op, i, operands)))
        return ::mlir::failure();
    }
    return ::mlir::success();
    }
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteOp>
  struct RegionBranchOpInterfaceTrait : public ::mlir::OpInterface<RegionBranchOpInterface, detail::RegionBranchOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns the operands of this operation that are forwarded to the
    /// successor inputs when branching to `successor`. `successor` is
    /// guaranteed to be among the successors that are returned by
    /// `getEntrySuccessorRegions`/`getSuccessorRegions(parent())`.
    /// 
    /// Example: In the above example, this method returns the operand %b of the
    /// `scf.for` op, regardless of the value of `successor`. I.e., this op always
    /// forwards the same operands, regardless of whether the loop has 0 or more
    /// iterations.
    ::mlir::OperandRange getEntrySuccessorOperands(::mlir::RegionSuccessor successor) {
      auto operandEnd = this->getOperation()->operand_end();
        return ::mlir::OperandRange(operandEnd, operandEnd);
    }

    /// Returns the potential region successors when first executing the op.
    /// 
    /// Unlike `getSuccessorRegions`, this method also passes along the
    /// constant operands of this op. Based on these, the implementation may
    /// filter out certain successors. By default, simply dispatches to
    /// `getSuccessorRegions`. `operands` contains an entry for every
    /// operand of this op, with a null attribute if the operand has no constant
    /// value.
    /// 
    /// Note: The control flow does not necessarily have to enter any region of
    /// this op.
    /// 
    /// Example: In the above example, this method may return two region
    /// region successors: the single region of the `scf.for` op and the
    /// `scf.for` operation (that implements this interface). If %lb, %ub, %step
    /// are constants and it can be determined the loop does not have any
    /// iterations, this method may choose to return only this operation.
    /// Similarly, if it can be determined that the loop has at least one
    /// iteration, this method may choose to return only the region of the loop.
    void getEntrySuccessorRegions(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
      (*static_cast<ConcreteOp *>(this)).getSuccessorRegions(mlir::RegionBranchPoint::parent(), regions);
    }

    /// Returns the potential region successors when branching from any
    /// terminator in `region`.
    void getSuccessorRegions(::mlir::Region& region, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
      for (::mlir::Block &block : region) {
          if (block.empty())
            continue;
          if (auto terminator =
                  dyn_cast<RegionBranchTerminatorOpInterface>(block.back()))
            (*static_cast<ConcreteOp *>(this)).getSuccessorRegions(RegionBranchPoint(terminator),
                                     regions);
        }
    }

    /// Return all successor inputs for the given region successor. If the
    /// given region successor is a region, then the returned values are block
    /// arguments. Otherwise, if the given region successor is the "parent",
    /// the returned values are op results.
    ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor) {
      // Default implementation: No successor inputs.
        return ::mlir::ValueRange();
    }

    /// Returns the potential branching points (predecessors) for a given
    /// region successor.
    void getPredecessors(::mlir::RegionSuccessor successor, ::llvm::SmallVectorImpl<::mlir::RegionBranchPoint> & predecessors) {
      auto op = cast<RegionBranchOpInterface>((*static_cast<ConcreteOp *>(this)).getOperation());
        for (::mlir::RegionBranchPoint point : op.getAllRegionBranchPoints()) {
          ::llvm::SmallVector<::mlir::RegionSuccessor> successors;
          op.getSuccessorRegions(point, successors);
          bool isPred = llvm::any_of(successors, [&] (const auto &succ) {
            return succ.getSuccessor() == successor.getSuccessor() ||
                   (succ.isParent() && successor.isParent());
            });
          if (isPred)
            predecessors.push_back(point);
        }
    }

    /// Returns the potential values across all (predecessors) for a given successor
    /// input, modeled by its index (its position in the list of values).
    void getPredecessorValues(::mlir::RegionSuccessor successor, int index, ::llvm::SmallVectorImpl<::mlir::Value> & predecessorValues) {
      ::llvm::SmallVector<::mlir::RegionBranchPoint> predecessors;
        (*static_cast<ConcreteOp *>(this)).getPredecessors(successor, predecessors);
        for (auto predecessor : predecessors) {
          if (predecessor.isParent()) {
            predecessorValues.push_back((*static_cast<ConcreteOp *>(this)).getEntrySuccessorOperands(successor)[index]);
            continue;
          }
          auto terminator = predecessor.getTerminatorPredecessorOrNull();
          predecessorValues.push_back(terminator.getSuccessorOperands(successor)[index]);
        }
    }

    /// Populates `invocationBounds` with the minimum and maximum number of
    /// times this operation will invoke the attached regions (assuming the
    /// regions yield normally, i.e. do not abort or invoke an infinite loop).
    /// The minimum number of invocations is at least 0. If the maximum number
    /// of invocations cannot be statically determined, then it will be set to
    /// `InvocationBounds::getUnknown()`.
    /// 
    /// This method also passes along the constant operands of this op.
    /// `operands` contains an entry for every operand of this op, with a null
    /// attribute if the operand has no constant value.
    /// 
    /// This method may be called speculatively on operations where the provided
    /// operands are not necessarily the same as the operation's current
    /// operands. This may occur in analyses that wish to determine "what would
    /// be the region invocations if these were the operands?"
    void getRegionInvocationBounds(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> & invocationBounds) {
      invocationBounds.append((*static_cast<ConcreteOp *>(this))->getNumRegions(),
                                ::mlir::InvocationBounds::getUnknown());
    }

    /// This method is called to compare types along control-flow edges. By
    /// default, the types are checked as equal.
    bool areTypesCompatible(::mlir::Type lhs, ::mlir::Type rhs) {
      return lhs == rhs;
    }
    static ::llvm::LogicalResult verifyRegionTrait(::mlir::Operation *op) {
      static_assert(!ConcreteOp::template hasTrait<OpTrait::ZeroRegions>(),
                  "expected operation to have non-zero regions");
    return detail::verifyRegionBranchOpInterface(op);
    }
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteOp>
  struct RegionBranchTerminatorOpInterfaceTrait : public ::mlir::OpInterface<RegionBranchTerminatorOpInterface, detail::RegionBranchTerminatorOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns the potential region successors that are branched to after this
    /// terminator based on the given constant operands.
    /// 
    /// This method also passes along the constant operands of this op.
    /// `operands` contains an entry for every operand of this op, with a null
    /// attribute if the operand has no constant value.
    /// 
    /// The default implementation simply dispatches to the parent
    /// `RegionBranchOpInterface`'s `getSuccessorRegions` implementation.
    void getSuccessorRegions(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
      ::mlir::Operation *op = (*static_cast<ConcreteOp *>(this));
        ::llvm::cast<::mlir::RegionBranchOpInterface>(op->getParentOp())
          .getSuccessorRegions(::llvm::cast<::mlir::RegionBranchTerminatorOpInterface>(op), regions);
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      static_assert(ConcreteOp::template hasTrait<OpTrait::IsTerminator>(),
                  "expected operation to be a terminator");
    static_assert(ConcreteOp::template hasTrait<OpTrait::ZeroResults>(),
                  "expected operation to have zero results");
    static_assert(ConcreteOp::template hasTrait<OpTrait::ZeroSuccessors>(),
                  "expected operation to have zero successors");
    return success();
    }
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteOp>
  struct SelectLikeOpInterfaceTrait : public ::mlir::OpInterface<SelectLikeOpInterface, detail::SelectLikeOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteOp>
  struct WeightedBranchOpInterfaceTrait : public ::mlir::OpInterface<WeightedBranchOpInterface, detail::WeightedBranchOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns the branch weights
    ::llvm::ArrayRef<int32_t> getWeights() {
      auto op = cast<ConcreteOp>(this->getOperation());
        if (auto attr = op.getBranchWeightsAttr())
          return attr.asArrayRef();
        return {};
    }

    /// Sets the branch weights
    void setWeights(::llvm::ArrayRef<int32_t> weights) {
      auto op = cast<ConcreteOp>(this->getOperation());
        op.setBranchWeightsAttr(::mlir::DenseI32ArrayAttr::get(op->getContext(), weights));
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return ::mlir::detail::verifyBranchWeights(op);
    }
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteOp>
  struct WeightedRegionBranchOpInterfaceTrait : public ::mlir::OpInterface<WeightedRegionBranchOpInterface, detail::WeightedRegionBranchOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns the region weights
    ::llvm::ArrayRef<int32_t> getWeights() {
      auto op = cast<ConcreteOp>(this->getOperation());
        if (auto attr = op.getRegionWeightsAttr())
          return attr.asArrayRef();
        return {};
    }

    /// Sets the region weights
    void setWeights(::llvm::ArrayRef<int32_t> weights) {
      auto op = cast<ConcreteOp>(this->getOperation());
        op.setRegionWeightsAttr(::mlir::DenseI32ArrayAttr::get(op->getContext(), weights));
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return ::mlir::detail::verifyRegionBranchWeights(op);
    }
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteOp>
::mlir::SuccessorOperands detail::BranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getSuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSuccessorOperands(index);
}
template<typename ConcreteOp>
::std::optional<::mlir::BlockArgument> detail::BranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getSuccessorBlockArgument(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned operandIndex) {
  ::mlir::Operation *opaqueOp = (llvm::cast<ConcreteOp>(tablegen_opaque_val));
        for (unsigned i = 0, e = opaqueOp->getNumSuccessors(); i != e; ++i) {
          if (::std::optional<::mlir::BlockArgument> arg = ::mlir::detail::getBranchSuccessorArgument(
                (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSuccessorOperands(i), operandIndex,
                opaqueOp->getSuccessor(i)))
            return arg;
        }
        return ::std::nullopt;
}
template<typename ConcreteOp>
::mlir::Block *detail::BranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getSuccessorForOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSuccessorForOperands(operands);
}
template<typename ConcreteOp>
bool detail::BranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::areTypesCompatible(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).areTypesCompatible(lhs, rhs);
}
template<typename ConcreteOp>
::mlir::SuccessorOperands detail::BranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getSuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index) {
  return static_cast<const ConcreteOp *>(impl)->getSuccessorOperands(tablegen_opaque_val, index);
}
template<typename ConcreteOp>
::std::optional<::mlir::BlockArgument> detail::BranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getSuccessorBlockArgument(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned operandIndex) {
  return static_cast<const ConcreteOp *>(impl)->getSuccessorBlockArgument(tablegen_opaque_val, operandIndex);
}
template<typename ConcreteOp>
::mlir::Block *detail::BranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getSuccessorForOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands) {
  return static_cast<const ConcreteOp *>(impl)->getSuccessorForOperands(tablegen_opaque_val, operands);
}
template<typename ConcreteOp>
bool detail::BranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::areTypesCompatible(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs) {
  return static_cast<const ConcreteOp *>(impl)->areTypesCompatible(tablegen_opaque_val, lhs, rhs);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Block *detail::BranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getSuccessorForOperands(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands) const {
return nullptr;
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::BranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::areTypesCompatible(::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs) const {
return lhs == rhs;
}

} // namespace mlir
namespace mlir {

template<typename ConcreteOp>
::mlir::OperandRange detail::RegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getEntrySuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getEntrySuccessorOperands(successor);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getEntrySuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getEntrySuccessorRegions(operands, regions);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getSuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSuccessorRegions(point, regions);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getSuccessorRegions_3(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Region& region, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSuccessorRegions(region, regions);
}
template<typename ConcreteOp>
::mlir::ValueRange detail::RegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getSuccessorInputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSuccessorInputs(successor);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPredecessors(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, ::llvm::SmallVectorImpl<::mlir::RegionBranchPoint> & predecessors) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPredecessors(successor, predecessors);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPredecessorValues(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, int index, ::llvm::SmallVectorImpl<::mlir::Value> & predecessorValues) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPredecessorValues(successor, index, predecessorValues);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getRegionInvocationBounds(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> & invocationBounds) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getRegionInvocationBounds(operands, invocationBounds);
}
template<typename ConcreteOp>
bool detail::RegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::areTypesCompatible(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).areTypesCompatible(lhs, rhs);
}
template<typename ConcreteOp>
::mlir::OperandRange detail::RegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getEntrySuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor) {
  return static_cast<const ConcreteOp *>(impl)->getEntrySuccessorOperands(tablegen_opaque_val, successor);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getEntrySuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
  return static_cast<const ConcreteOp *>(impl)->getEntrySuccessorRegions(tablegen_opaque_val, operands, regions);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getSuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
  return static_cast<const ConcreteOp *>(impl)->getSuccessorRegions(tablegen_opaque_val, point, regions);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getSuccessorRegions_3(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Region& region, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
  return static_cast<const ConcreteOp *>(impl)->getSuccessorRegions_3(tablegen_opaque_val, region, regions);
}
template<typename ConcreteOp>
::mlir::ValueRange detail::RegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getSuccessorInputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor) {
  return static_cast<const ConcreteOp *>(impl)->getSuccessorInputs(tablegen_opaque_val, successor);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPredecessors(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, ::llvm::SmallVectorImpl<::mlir::RegionBranchPoint> & predecessors) {
  return static_cast<const ConcreteOp *>(impl)->getPredecessors(tablegen_opaque_val, successor, predecessors);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPredecessorValues(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, int index, ::llvm::SmallVectorImpl<::mlir::Value> & predecessorValues) {
  return static_cast<const ConcreteOp *>(impl)->getPredecessorValues(tablegen_opaque_val, successor, index, predecessorValues);
}
template<typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getRegionInvocationBounds(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> & invocationBounds) {
  return static_cast<const ConcreteOp *>(impl)->getRegionInvocationBounds(tablegen_opaque_val, operands, invocationBounds);
}
template<typename ConcreteOp>
bool detail::RegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::areTypesCompatible(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs) {
  return static_cast<const ConcreteOp *>(impl)->areTypesCompatible(tablegen_opaque_val, lhs, rhs);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::OperandRange detail::RegionBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getEntrySuccessorOperands(::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor) const {
auto operandEnd = this->getOperation()->operand_end();
        return ::mlir::OperandRange(operandEnd, operandEnd);
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getEntrySuccessorRegions(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSuccessorRegions(mlir::RegionBranchPoint::parent(), regions);
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getSuccessorRegions_3(::mlir::Operation *tablegen_opaque_val, ::mlir::Region&region, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions) const {
for (::mlir::Block &block : region) {
          if (block.empty())
            continue;
          if (auto terminator =
                  dyn_cast<RegionBranchTerminatorOpInterface>(block.back()))
            (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSuccessorRegions(RegionBranchPoint(terminator),
                                     regions);
        }
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::ValueRange detail::RegionBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getSuccessorInputs(::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor) const {
// Default implementation: No successor inputs.
        return ::mlir::ValueRange();
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPredecessors(::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, ::llvm::SmallVectorImpl<::mlir::RegionBranchPoint> &predecessors) const {
auto op = cast<RegionBranchOpInterface>((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getOperation());
        for (::mlir::RegionBranchPoint point : op.getAllRegionBranchPoints()) {
          ::llvm::SmallVector<::mlir::RegionSuccessor> successors;
          op.getSuccessorRegions(point, successors);
          bool isPred = llvm::any_of(successors, [&] (const auto &succ) {
            return succ.getSuccessor() == successor.getSuccessor() ||
                   (succ.isParent() && successor.isParent());
            });
          if (isPred)
            predecessors.push_back(point);
        }
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPredecessorValues(::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor successor, int index, ::llvm::SmallVectorImpl<::mlir::Value> &predecessorValues) const {
::llvm::SmallVector<::mlir::RegionBranchPoint> predecessors;
        (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPredecessors(successor, predecessors);
        for (auto predecessor : predecessors) {
          if (predecessor.isParent()) {
            predecessorValues.push_back((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getEntrySuccessorOperands(successor)[index]);
            continue;
          }
          auto terminator = predecessor.getTerminatorPredecessorOrNull();
          predecessorValues.push_back(terminator.getSuccessorOperands(successor)[index]);
        }
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::RegionBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getRegionInvocationBounds(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> &invocationBounds) const {
invocationBounds.append((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getNumRegions(),
                                ::mlir::InvocationBounds::getUnknown());
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::RegionBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::areTypesCompatible(::mlir::Operation *tablegen_opaque_val, ::mlir::Type lhs, ::mlir::Type rhs) const {
return lhs == rhs;
}

} // namespace mlir
namespace mlir {

template<typename ConcreteOp>
::mlir::MutableOperandRange detail::RegionBranchTerminatorOpInterfaceInterfaceTraits::Model<ConcreteOp>::getMutableSuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor point) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getMutableSuccessorOperands(point);
}
template<typename ConcreteOp>
void detail::RegionBranchTerminatorOpInterfaceInterfaceTraits::Model<ConcreteOp>::getSuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSuccessorRegions(operands, regions);
}
template<typename ConcreteOp>
::mlir::MutableOperandRange detail::RegionBranchTerminatorOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getMutableSuccessorOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::RegionSuccessor point) {
  return static_cast<const ConcreteOp *>(impl)->getMutableSuccessorOperands(tablegen_opaque_val, point);
}
template<typename ConcreteOp>
void detail::RegionBranchTerminatorOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getSuccessorRegions(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> & regions) {
  return static_cast<const ConcreteOp *>(impl)->getSuccessorRegions(tablegen_opaque_val, operands, regions);
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::RegionBranchTerminatorOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getSuccessorRegions(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions) const {
::mlir::Operation *op = (llvm::cast<ConcreteOp>(tablegen_opaque_val));
        ::llvm::cast<::mlir::RegionBranchOpInterface>(op->getParentOp())
          .getSuccessorRegions(::llvm::cast<::mlir::RegionBranchTerminatorOpInterface>(op), regions);
}

} // namespace mlir
namespace mlir {

template<typename ConcreteOp>
::mlir::Value detail::SelectLikeOpInterfaceInterfaceTraits::Model<ConcreteOp>::getFalseValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getFalseValue();
}
template<typename ConcreteOp>
::mlir::Value detail::SelectLikeOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTrueValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getTrueValue();
}
template<typename ConcreteOp>
::mlir::Value detail::SelectLikeOpInterfaceInterfaceTraits::Model<ConcreteOp>::getCondition(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getCondition();
}
template<typename ConcreteOp>
::mlir::Value detail::SelectLikeOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getFalseValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getFalseValue(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::Value detail::SelectLikeOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTrueValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getTrueValue(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::Value detail::SelectLikeOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getCondition(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getCondition(tablegen_opaque_val);
}

} // namespace mlir
namespace mlir {

template<typename ConcreteOp>
::llvm::ArrayRef<int32_t> detail::WeightedBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getWeights();
}
template<typename ConcreteOp>
void detail::WeightedBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::setWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setWeights(weights);
}
template<typename ConcreteOp>
::llvm::ArrayRef<int32_t> detail::WeightedBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getWeights(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::WeightedBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights) {
  return static_cast<const ConcreteOp *>(impl)->setWeights(tablegen_opaque_val, weights);
}
template<typename ConcreteModel, typename ConcreteOp>
::llvm::ArrayRef<int32_t> detail::WeightedBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getWeights(::mlir::Operation *tablegen_opaque_val) const {
auto op = cast<ConcreteOp>(this->getOperation());
        if (auto attr = op.getBranchWeightsAttr())
          return attr.asArrayRef();
        return {};
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::WeightedBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setWeights(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights) const {
auto op = cast<ConcreteOp>(this->getOperation());
        op.setBranchWeightsAttr(::mlir::DenseI32ArrayAttr::get(op->getContext(), weights));
}

} // namespace mlir
namespace mlir {

template<typename ConcreteOp>
::llvm::ArrayRef<int32_t> detail::WeightedRegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::getWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getWeights();
}
template<typename ConcreteOp>
void detail::WeightedRegionBranchOpInterfaceInterfaceTraits::Model<ConcreteOp>::setWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setWeights(weights);
}
template<typename ConcreteOp>
::llvm::ArrayRef<int32_t> detail::WeightedRegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getWeights(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::WeightedRegionBranchOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setWeights(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights) {
  return static_cast<const ConcreteOp *>(impl)->setWeights(tablegen_opaque_val, weights);
}
template<typename ConcreteModel, typename ConcreteOp>
::llvm::ArrayRef<int32_t> detail::WeightedRegionBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getWeights(::mlir::Operation *tablegen_opaque_val) const {
auto op = cast<ConcreteOp>(this->getOperation());
        if (auto attr = op.getRegionWeightsAttr())
          return attr.asArrayRef();
        return {};
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::WeightedRegionBranchOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setWeights(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<int32_t> weights) const {
auto op = cast<ConcreteOp>(this->getOperation());
        op.setRegionWeightsAttr(::mlir::DenseI32ArrayAttr::get(op->getContext(), weights));
}

} // namespace mlir
