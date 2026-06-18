/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// An in parallel op is an op with a region.
/// 
///     This is useful as a terminator to parallel operations that iterate over
///     some set and return tensors while avoiding tight coupling between the
///     iterating op, the combining op and the individual subtensor producing ops.
class InParallelOpInterface;

} // namespace mlir
namespace mlir {

/// A parallel combining op is an operation that models parallel contributions
///     to result tensors within the context of a parent iterating operation.
///     
///     This interface is designed for operations that need to coordinate parallel
///     insertions or contributions to tensors that are being constructed across
///     multiple parallel iterations. The destination refers to a tensor value that
///     is assembled by aggregating results from parallel computations; each
///     parallel iteration may contribute a slice, element, or region to the final
///     result. No in-place mutation of tensors is implied.
/// 
///     One significant use case for this interface is `tensor.parallel_insert_slice`
///     which allows parallel insertion of slices that are aggregated into a
///     destination tensor. With this interface, other operations that express
///     similar parallel contributions can also be defined.
/// 
///     This op works within an op implementing the `InParallelOpInterface` that
///     specifies how the parallel results are combined.
/// 
///     Key semantics:
///     - The operation identifies destination tensors to which iterations
///       contribute through the `getUpdatedDestinations` method
///     - Each parallel iteration may produce elements or regions that are
///       incorporated into the destination tensor
///     - The parent iterating operation manages the coordination and ensures
///       proper synchronization of these contributions
///   
///     Note: This interface does not verify itself, it is up to the implementing operation
///     to verify the correctness of the op.
class ParallelCombiningOpInterface;

} // namespace mlir
namespace mlir {

/// An in parallel op is an op with a region.
/// 
///     This is useful as a terminator to parallel operations that iterate over
///     some set and return tensors while avoiding tight coupling between the
///     iterating op, the combining op and the individual subtensor producing ops.
namespace detail {
struct InParallelOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::OpResult (*getParentResult)(const Concept *impl, ::mlir::Operation *, int64_t);
    ::llvm::iterator_range<Block::iterator> (*getYieldingOps)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::InParallelOpInterface;
    Model() : Concept{getParentResult, getYieldingOps} {}

    static inline ::mlir::OpResult getParentResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, int64_t idx);
    static inline ::llvm::iterator_range<Block::iterator> getYieldingOps(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::InParallelOpInterface;
    FallbackModel() : Concept{getParentResult, getYieldingOps} {}

    static inline ::mlir::OpResult getParentResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, int64_t idx);
    static inline ::llvm::iterator_range<Block::iterator> getYieldingOps(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct InParallelOpInterfaceTrait;

} // namespace detail
class InParallelOpInterface : public ::mlir::OpInterface<InParallelOpInterface, detail::InParallelOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<InParallelOpInterface, detail::InParallelOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::InParallelOpInterfaceTrait<ConcreteOp> {};

  /// Return `idx`^th result of the parent operation.
  ::mlir::OpResult getParentResult(int64_t idx);

  /// Return the contained ops that yield subvalues that this op combines to
  /// yield to its parent.
  ::llvm::iterator_range<Block::iterator> getYieldingOps();
};

} // namespace mlir
namespace mlir {

/// A parallel combining op is an operation that models parallel contributions
///     to result tensors within the context of a parent iterating operation.
///     
///     This interface is designed for operations that need to coordinate parallel
///     insertions or contributions to tensors that are being constructed across
///     multiple parallel iterations. The destination refers to a tensor value that
///     is assembled by aggregating results from parallel computations; each
///     parallel iteration may contribute a slice, element, or region to the final
///     result. No in-place mutation of tensors is implied.
/// 
///     One significant use case for this interface is `tensor.parallel_insert_slice`
///     which allows parallel insertion of slices that are aggregated into a
///     destination tensor. With this interface, other operations that express
///     similar parallel contributions can also be defined.
/// 
///     This op works within an op implementing the `InParallelOpInterface` that
///     specifies how the parallel results are combined.
/// 
///     Key semantics:
///     - The operation identifies destination tensors to which iterations
///       contribute through the `getUpdatedDestinations` method
///     - Each parallel iteration may produce elements or regions that are
///       incorporated into the destination tensor
///     - The parent iterating operation manages the coordination and ensures
///       proper synchronization of these contributions
///   
///     Note: This interface does not verify itself, it is up to the implementing operation
///     to verify the correctness of the op.
namespace detail {
struct ParallelCombiningOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::MutableOperandRange (*getUpdatedDestinations)(const Concept *impl, ::mlir::Operation *);
    ::mlir::Operation*(*getIteratingParent)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::ParallelCombiningOpInterface;
    Model() : Concept{getUpdatedDestinations, getIteratingParent} {}

    static inline ::mlir::MutableOperandRange getUpdatedDestinations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Operation*getIteratingParent(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::ParallelCombiningOpInterface;
    FallbackModel() : Concept{getUpdatedDestinations, getIteratingParent} {}

    static inline ::mlir::MutableOperandRange getUpdatedDestinations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Operation*getIteratingParent(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct ParallelCombiningOpInterfaceTrait;

} // namespace detail
class ParallelCombiningOpInterface : public ::mlir::OpInterface<ParallelCombiningOpInterface, detail::ParallelCombiningOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ParallelCombiningOpInterface, detail::ParallelCombiningOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ParallelCombiningOpInterfaceTrait<ConcreteOp> {};

  /// Returns the list of destination values this op contributes to.
  ::mlir::MutableOperandRange getUpdatedDestinations();

  /// Returns the iterating parent for this op.
  ::mlir::Operation*getIteratingParent();
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteOp>
  struct InParallelOpInterfaceTrait : public ::mlir::OpInterface<InParallelOpInterface, detail::InParallelOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return verifyInParallelOpInterface(op);
    }
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteOp>
  struct ParallelCombiningOpInterfaceTrait : public ::mlir::OpInterface<ParallelCombiningOpInterface, detail::ParallelCombiningOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteOp>
::mlir::OpResult detail::InParallelOpInterfaceInterfaceTraits::Model<ConcreteOp>::getParentResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, int64_t idx) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getParentResult(idx);
}
template<typename ConcreteOp>
::llvm::iterator_range<Block::iterator> detail::InParallelOpInterfaceInterfaceTraits::Model<ConcreteOp>::getYieldingOps(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getYieldingOps();
}
template<typename ConcreteOp>
::mlir::OpResult detail::InParallelOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getParentResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, int64_t idx) {
  return static_cast<const ConcreteOp *>(impl)->getParentResult(tablegen_opaque_val, idx);
}
template<typename ConcreteOp>
::llvm::iterator_range<Block::iterator> detail::InParallelOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getYieldingOps(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getYieldingOps(tablegen_opaque_val);
}

} // namespace mlir
namespace mlir {

template<typename ConcreteOp>
::mlir::MutableOperandRange detail::ParallelCombiningOpInterfaceInterfaceTraits::Model<ConcreteOp>::getUpdatedDestinations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getUpdatedDestinations();
}
template<typename ConcreteOp>
::mlir::Operation*detail::ParallelCombiningOpInterfaceInterfaceTraits::Model<ConcreteOp>::getIteratingParent(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getIteratingParent();
}
template<typename ConcreteOp>
::mlir::MutableOperandRange detail::ParallelCombiningOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getUpdatedDestinations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getUpdatedDestinations(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::Operation*detail::ParallelCombiningOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getIteratingParent(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getIteratingParent(tablegen_opaque_val);
}

} // namespace mlir
