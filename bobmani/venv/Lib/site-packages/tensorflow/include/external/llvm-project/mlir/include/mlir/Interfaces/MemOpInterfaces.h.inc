/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// An interface for operations that can consume memory-space cast-like
///     operations.
/// 
///     This interface can be used to bubble-down memory-space cast operations,
///     see the `bubble-down-memory-space-casts` pass for an example.
class MemorySpaceCastConsumerOpInterface;

} // namespace mlir
namespace mlir {

/// An interface for operations that perform memory-space casts. This
///     interface assumes that the cast operation is `pure`.
/// 
///     These operations expect to have a well-defined ptr-like operand, and
///     a well-defined target ptr-like result.
/// 
///     This interface also allows to determine whether a cast can be bubbled-down
///     by the `MemorySpaceCastConsumerOpInterface`, allowing control over which
///     casts can be bubbled-down or not.
class MemorySpaceCastOpInterface;

} // namespace mlir
namespace mlir {

/// An interface for operations that can consume memory-space cast-like
///     operations.
/// 
///     This interface can be used to bubble-down memory-space cast operations,
///     see the `bubble-down-memory-space-casts` pass for an example.
namespace detail {
struct MemorySpaceCastConsumerOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> (*bubbleDownCasts)(const Concept *impl, ::mlir::Operation *, ::mlir::OpBuilder &);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::MemorySpaceCastConsumerOpInterface;
    Model() : Concept{bubbleDownCasts} {}

    static inline ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::MemorySpaceCastConsumerOpInterface;
    FallbackModel() : Concept{bubbleDownCasts} {}

    static inline ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct MemorySpaceCastConsumerOpInterfaceTrait;

} // namespace detail
class MemorySpaceCastConsumerOpInterface : public ::mlir::OpInterface<MemorySpaceCastConsumerOpInterface, detail::MemorySpaceCastConsumerOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<MemorySpaceCastConsumerOpInterface, detail::MemorySpaceCastConsumerOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::MemorySpaceCastConsumerOpInterfaceTrait<ConcreteOp> {};

  /// Attempt to bubble-down the incoming cast-like operands. On success
  /// returns a `std::optional<SmallVector<Value>>`, otherwise it returns
  /// failure. If the optional is `std::nullopt` then the cast was performed
  /// in place, otherwise the method returns a list of replacement values.
  /// If new results are produced, these must be compatible with the original
  /// operation results.
  /// 
  /// If the operation was not modified in place, then the interface
  /// guarantees it is valid to erase the original operation.
  /// If the operation was modified in place, then the interface must
  /// guarantee no operations were created by the method, and that no further
  /// IR modification is necessary.
  /// 
  /// Any implementations of this method must not erase/replace the original
  /// operation, instead it is the caller responsibility to erase or replace
  /// the op with the results provided by the method.
  /// 
  /// Finally, any implementations of this method have to guarantee that the
  /// IR remains valid at all times.
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder & builder);
};

} // namespace mlir
namespace mlir {

/// An interface for operations that perform memory-space casts. This
///     interface assumes that the cast operation is `pure`.
/// 
///     These operations expect to have a well-defined ptr-like operand, and
///     a well-defined target ptr-like result.
/// 
///     This interface also allows to determine whether a cast can be bubbled-down
///     by the `MemorySpaceCastConsumerOpInterface`, allowing control over which
///     casts can be bubbled-down or not.
namespace detail {
struct MemorySpaceCastOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> (*getSourcePtr)(const Concept *impl, ::mlir::Operation *);
    ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> (*getTargetPtr)(const Concept *impl, ::mlir::Operation *);
    bool (*isValidMemorySpaceCast)(const Concept *impl, ::mlir::Operation *, ::mlir::PtrLikeTypeInterface, ::mlir::PtrLikeTypeInterface);
    ::mlir::MemorySpaceCastOpInterface (*cloneMemorySpaceCastOp)(const Concept *impl, ::mlir::Operation *, ::mlir::OpBuilder &, ::mlir::PtrLikeTypeInterface, ::mlir::TypedValue<::mlir::PtrLikeTypeInterface>);
    bool (*isSourcePromotable)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::MemorySpaceCastOpInterface;
    Model() : Concept{getSourcePtr, getTargetPtr, isValidMemorySpaceCast, cloneMemorySpaceCastOp, isSourcePromotable} {}

    static inline ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> getSourcePtr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> getTargetPtr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool isValidMemorySpaceCast(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::PtrLikeTypeInterface tgt, ::mlir::PtrLikeTypeInterface src);
    static inline ::mlir::MemorySpaceCastOpInterface cloneMemorySpaceCastOp(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder, ::mlir::PtrLikeTypeInterface tgt, ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> src);
    static inline bool isSourcePromotable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::MemorySpaceCastOpInterface;
    FallbackModel() : Concept{getSourcePtr, getTargetPtr, isValidMemorySpaceCast, cloneMemorySpaceCastOp, isSourcePromotable} {}

    static inline ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> getSourcePtr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> getTargetPtr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool isValidMemorySpaceCast(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::PtrLikeTypeInterface tgt, ::mlir::PtrLikeTypeInterface src);
    static inline ::mlir::MemorySpaceCastOpInterface cloneMemorySpaceCastOp(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder, ::mlir::PtrLikeTypeInterface tgt, ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> src);
    static inline bool isSourcePromotable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct MemorySpaceCastOpInterfaceTrait;

} // namespace detail
class MemorySpaceCastOpInterface : public ::mlir::OpInterface<MemorySpaceCastOpInterface, detail::MemorySpaceCastOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<MemorySpaceCastOpInterface, detail::MemorySpaceCastOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::MemorySpaceCastOpInterfaceTrait<ConcreteOp> {};

  /// Returns the source ptr-like value.
  ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> getSourcePtr();

  /// Returns the target ptr-like value.
  ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> getTargetPtr();

  /// Returns whether the memory space cast specified by `tgt` and `src`
  /// is supported.
  bool isValidMemorySpaceCast(::mlir::PtrLikeTypeInterface tgt, ::mlir::PtrLikeTypeInterface src);

  /// Clones the memory space cast op with the given source and target type.
  ::mlir::MemorySpaceCastOpInterface cloneMemorySpaceCastOp(::mlir::OpBuilder & builder, ::mlir::PtrLikeTypeInterface tgt, ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> src);

  /// Returns whether the source pointer of the memory-space cast can be used
  /// by the `MemorySpaceCastConsumerOpInterface::bubbleDownCasts` method to
  /// promote the source pointer and bubble down the cast.
  /// 
  /// For example, a cast operation might decide that all casts to the generic
  /// memory-space can be promoted. 
  bool isSourcePromotable();

    /// Returns the underlying `MemorySpaceCastOpInterface` op if `value`
    /// is produced by a `MemorySpaceCastOpInterface` op, and
    /// `isSourcePromotable` returns true, otherwise it returns null.
    static ::mlir::MemorySpaceCastOpInterface
    getIfPromotableCast(::mlir::Value value) {
      auto op = ::llvm::dyn_cast_or_null<::mlir::MemorySpaceCastOpInterface>(
        value.getDefiningOp());
      if (!op || !op.isSourcePromotable())
        return nullptr;
      return op;
    }
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteOp>
  struct MemorySpaceCastConsumerOpInterfaceTrait : public ::mlir::OpInterface<MemorySpaceCastConsumerOpInterface, detail::MemorySpaceCastConsumerOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteOp>
  struct MemorySpaceCastOpInterfaceTrait : public ::mlir::OpInterface<MemorySpaceCastOpInterface, detail::MemorySpaceCastOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return ::mlir::detail::verifyMemorySpaceCastOpInterface(op);
    }
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteOp>
::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> detail::MemorySpaceCastConsumerOpInterfaceInterfaceTraits::Model<ConcreteOp>::bubbleDownCasts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).bubbleDownCasts(builder);
}
template<typename ConcreteOp>
::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> detail::MemorySpaceCastConsumerOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::bubbleDownCasts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder) {
  return static_cast<const ConcreteOp *>(impl)->bubbleDownCasts(tablegen_opaque_val, builder);
}

} // namespace mlir
namespace mlir {

template<typename ConcreteOp>
::mlir::TypedValue<::mlir::PtrLikeTypeInterface> detail::MemorySpaceCastOpInterfaceInterfaceTraits::Model<ConcreteOp>::getSourcePtr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSourcePtr();
}
template<typename ConcreteOp>
::mlir::TypedValue<::mlir::PtrLikeTypeInterface> detail::MemorySpaceCastOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTargetPtr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getTargetPtr();
}
template<typename ConcreteOp>
bool detail::MemorySpaceCastOpInterfaceInterfaceTraits::Model<ConcreteOp>::isValidMemorySpaceCast(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::PtrLikeTypeInterface tgt, ::mlir::PtrLikeTypeInterface src) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isValidMemorySpaceCast(tgt, src);
}
template<typename ConcreteOp>
::mlir::MemorySpaceCastOpInterface detail::MemorySpaceCastOpInterfaceInterfaceTraits::Model<ConcreteOp>::cloneMemorySpaceCastOp(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder, ::mlir::PtrLikeTypeInterface tgt, ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> src) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).cloneMemorySpaceCastOp(builder, tgt, src);
}
template<typename ConcreteOp>
bool detail::MemorySpaceCastOpInterfaceInterfaceTraits::Model<ConcreteOp>::isSourcePromotable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isSourcePromotable();
}
template<typename ConcreteOp>
::mlir::TypedValue<::mlir::PtrLikeTypeInterface> detail::MemorySpaceCastOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getSourcePtr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getSourcePtr(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::TypedValue<::mlir::PtrLikeTypeInterface> detail::MemorySpaceCastOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTargetPtr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getTargetPtr(tablegen_opaque_val);
}
template<typename ConcreteOp>
bool detail::MemorySpaceCastOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isValidMemorySpaceCast(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::PtrLikeTypeInterface tgt, ::mlir::PtrLikeTypeInterface src) {
  return static_cast<const ConcreteOp *>(impl)->isValidMemorySpaceCast(tablegen_opaque_val, tgt, src);
}
template<typename ConcreteOp>
::mlir::MemorySpaceCastOpInterface detail::MemorySpaceCastOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::cloneMemorySpaceCastOp(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder, ::mlir::PtrLikeTypeInterface tgt, ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> src) {
  return static_cast<const ConcreteOp *>(impl)->cloneMemorySpaceCastOp(tablegen_opaque_val, builder, tgt, src);
}
template<typename ConcreteOp>
bool detail::MemorySpaceCastOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isSourcePromotable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->isSourcePromotable(tablegen_opaque_val);
}

} // namespace mlir
