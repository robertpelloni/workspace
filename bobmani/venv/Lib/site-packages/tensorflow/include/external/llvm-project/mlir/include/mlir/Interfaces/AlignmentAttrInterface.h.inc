/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// An interface for operations that carry an optional alignment attribute and
///     want to expose it as an `llvm::MaybeAlign` helper.
class AlignmentAttrOpInterface;

} // namespace mlir
namespace mlir {

/// An interface for operations that carry an optional alignment attribute and
///     want to expose it as an `llvm::MaybeAlign` helper.
namespace detail {
struct AlignmentAttrOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::MaybeAlign (*getMaybeAlign)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::AlignmentAttrOpInterface;
    Model() : Concept{getMaybeAlign} {}

    static inline ::llvm::MaybeAlign getMaybeAlign(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::AlignmentAttrOpInterface;
    FallbackModel() : Concept{getMaybeAlign} {}

    static inline ::llvm::MaybeAlign getMaybeAlign(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct AlignmentAttrOpInterfaceTrait;

} // namespace detail
class AlignmentAttrOpInterface : public ::mlir::OpInterface<AlignmentAttrOpInterface, detail::AlignmentAttrOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<AlignmentAttrOpInterface, detail::AlignmentAttrOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::AlignmentAttrOpInterfaceTrait<ConcreteOp> {};

  /// Returns the alignment encoded on the operation as an `llvm::MaybeAlign`.
  /// Operations providing a differently named accessor can override the
  /// default implementation.
  ::llvm::MaybeAlign getMaybeAlign();
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteOp>
  struct AlignmentAttrOpInterfaceTrait : public ::mlir::OpInterface<AlignmentAttrOpInterface, detail::AlignmentAttrOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    ::llvm::MaybeAlign getMaybeAlign() {
      // Defensive: trait implementations are expected to validate power-of-two
      // alignments, but we still guard against accidental misuse.
      auto alignmentOpt = (*static_cast<ConcreteOp *>(this)).getAlignment();
      if (!alignmentOpt || *alignmentOpt <= 0)
        return ::llvm::MaybeAlign();
      uint64_t value = static_cast<uint64_t>(*alignmentOpt);
      if (!::llvm::isPowerOf2_64(value))
        return ::llvm::MaybeAlign();
      return ::llvm::MaybeAlign(value);
    }
  
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteOp>
::llvm::MaybeAlign detail::AlignmentAttrOpInterfaceInterfaceTraits::Model<ConcreteOp>::getMaybeAlign(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  // Defensive: trait implementations are expected to validate power-of-two
        // alignments, but we still guard against accidental misuse.
        auto alignmentOpt = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getAlignment();
        if (!alignmentOpt || *alignmentOpt <= 0)
          return ::llvm::MaybeAlign();
        uint64_t value = static_cast<uint64_t>(*alignmentOpt);
        if (!::llvm::isPowerOf2_64(value))
          return ::llvm::MaybeAlign();
        return ::llvm::MaybeAlign(value);
}
template<typename ConcreteOp>
::llvm::MaybeAlign detail::AlignmentAttrOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getMaybeAlign(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getMaybeAlign(tablegen_opaque_val);
}

} // namespace mlir
