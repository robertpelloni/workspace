/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::ptr {

/// This interface defines a common API for interacting with the memory model of
///     a memory space and the operations in the pointer dialect.
/// 
///     Furthermore, this interface allows concepts such as read-only memory to be
///     adequately modeled and enforced.
class MemorySpaceAttrInterface;

} // namespace mlir::ptr
namespace mlir::ptr {

/// This interface defines a common API for interacting with the memory model of
///     a memory space and the operations in the pointer dialect.
/// 
///     Furthermore, this interface allows concepts such as read-only memory to be
///     adequately modeled and enforced.
namespace detail {
struct MemorySpaceAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*isValidLoad)(const Concept *impl, ::mlir::Attribute , ::mlir::Type, ::mlir::ptr::AtomicOrdering, std::optional<int64_t>, const ::mlir::DataLayout *, ::llvm::function_ref<::mlir::InFlightDiagnostic()>);
    bool (*isValidStore)(const Concept *impl, ::mlir::Attribute , ::mlir::Type, ::mlir::ptr::AtomicOrdering, std::optional<int64_t>, const ::mlir::DataLayout *, ::llvm::function_ref<::mlir::InFlightDiagnostic()>);
    bool (*isValidAtomicOp)(const Concept *impl, ::mlir::Attribute , ::mlir::ptr::AtomicBinOp, ::mlir::Type, ::mlir::ptr::AtomicOrdering, std::optional<int64_t>, const ::mlir::DataLayout *, ::llvm::function_ref<::mlir::InFlightDiagnostic()>);
    bool (*isValidAtomicXchg)(const Concept *impl, ::mlir::Attribute , ::mlir::Type, ::mlir::ptr::AtomicOrdering, ::mlir::ptr::AtomicOrdering, std::optional<int64_t>, const ::mlir::DataLayout *, ::llvm::function_ref<::mlir::InFlightDiagnostic()>);
    bool (*isValidAddrSpaceCast)(const Concept *impl, ::mlir::Attribute , ::mlir::Type, ::mlir::Type, ::llvm::function_ref<::mlir::InFlightDiagnostic()>);
    bool (*isValidPtrIntCast)(const Concept *impl, ::mlir::Attribute , ::mlir::Type, ::mlir::Type, ::llvm::function_ref<::mlir::InFlightDiagnostic()>);
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::ptr::MemorySpaceAttrInterface;
    Model() : Concept{isValidLoad, isValidStore, isValidAtomicOp, isValidAtomicXchg, isValidAddrSpaceCast, isValidPtrIntCast} {}

    static inline bool isValidLoad(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline bool isValidStore(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline bool isValidAtomicOp(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::ptr::AtomicBinOp op, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline bool isValidAtomicXchg(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering successOrdering, ::mlir::ptr::AtomicOrdering failureOrdering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline bool isValidAddrSpaceCast(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type tgt, ::mlir::Type src, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline bool isValidPtrIntCast(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type intLikeTy, ::mlir::Type ptrLikeTy, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::ptr::MemorySpaceAttrInterface;
    FallbackModel() : Concept{isValidLoad, isValidStore, isValidAtomicOp, isValidAtomicXchg, isValidAddrSpaceCast, isValidPtrIntCast} {}

    static inline bool isValidLoad(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline bool isValidStore(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline bool isValidAtomicOp(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::ptr::AtomicBinOp op, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline bool isValidAtomicXchg(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering successOrdering, ::mlir::ptr::AtomicOrdering failureOrdering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline bool isValidAddrSpaceCast(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type tgt, ::mlir::Type src, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline bool isValidPtrIntCast(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type intLikeTy, ::mlir::Type ptrLikeTy, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct MemorySpaceAttrInterfaceTrait;

} // namespace detail
class MemorySpaceAttrInterface : public ::mlir::AttributeInterface<MemorySpaceAttrInterface, detail::MemorySpaceAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<MemorySpaceAttrInterface, detail::MemorySpaceAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::MemorySpaceAttrInterfaceTrait<ConcreteAttr> {};

  /// This method checks if it's valid to load a value from the memory space
  /// with a specific type, alignment, and atomic ordering.
  /// If `emitError` is non-null then the method is allowed to emit errors.
  /// Furthermore, if `emitError` is non-null and the result is `false` an
  /// error must have been emitted.
  bool isValidLoad(::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;

  /// This method checks if it's valid to store a value in the memory space
  /// with a specific type, alignment, and atomic ordering.
  /// If `emitError` is non-null then the method is allowed to emit errors.
  /// Furthermore, if `emitError` is non-null and the result is `false` an
  /// error must have been emitted.
  bool isValidStore(::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;

  /// This method checks if it's valid to perform an atomic operation in the
  /// memory space with a specific type, alignment, and atomic ordering.
  /// If `emitError` is non-null then the method is allowed to emit errors.
  /// Furthermore, if `emitError` is non-null and the result is `false` an
  /// error must have been emitted.
  bool isValidAtomicOp(::mlir::ptr::AtomicBinOp op, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;

  /// This method checks if it's valid to perform an atomic exchange operation
  /// in the memory space with a specific type, alignment, and atomic
  /// orderings.
  /// If `emitError` is non-null then the method is allowed to emit errors.
  /// Furthermore, if `emitError` is non-null and the result is `false` an
  /// error must have been emitted.
  bool isValidAtomicXchg(::mlir::Type type, ::mlir::ptr::AtomicOrdering successOrdering, ::mlir::ptr::AtomicOrdering failureOrdering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;

  /// This method checks if it's valid to perform an `addrspacecast` op
  /// in the memory space.
  /// If `emitError` is non-null then the method is allowed to emit errors.
  /// Furthermore, if `emitError` is non-null and the result is `false` an
  /// error must have been emitted.
  bool isValidAddrSpaceCast(::mlir::Type tgt, ::mlir::Type src, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;

  /// This method checks if it's valid to perform a `ptrtoint` or `inttoptr`
  /// op in the memory space.
  /// The first type is expected to be integer-like, while the second must be
  /// a ptr-like type.
  /// If `emitError` is non-null then the method is allowed to emit errors.
  /// Furthermore, if `emitError` is non-null and the result is `false` an
  /// error must have been emitted.
  bool isValidPtrIntCast(::mlir::Type intLikeTy, ::mlir::Type ptrLikeTy, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
};

} // namespace mlir::ptr
namespace mlir::ptr::detail {

  template <typename ConcreteAttr>
  struct MemorySpaceAttrInterfaceTrait : public ::mlir::AttributeInterface<MemorySpaceAttrInterface, detail::MemorySpaceAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace mlir::ptr::detail
namespace mlir::ptr {

template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::isValidLoad(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).isValidLoad(type, ordering, alignment, dataLayout, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::isValidStore(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).isValidStore(type, ordering, alignment, dataLayout, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::isValidAtomicOp(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::ptr::AtomicBinOp op, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).isValidAtomicOp(op, type, ordering, alignment, dataLayout, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::isValidAtomicXchg(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering successOrdering, ::mlir::ptr::AtomicOrdering failureOrdering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).isValidAtomicXchg(type, successOrdering, failureOrdering, alignment, dataLayout, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::isValidAddrSpaceCast(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type tgt, ::mlir::Type src, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).isValidAddrSpaceCast(tgt, src, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::isValidPtrIntCast(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type intLikeTy, ::mlir::Type ptrLikeTy, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).isValidPtrIntCast(intLikeTy, ptrLikeTy, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::isValidLoad(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return static_cast<const ConcreteAttr *>(impl)->isValidLoad(tablegen_opaque_val, type, ordering, alignment, dataLayout, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::isValidStore(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return static_cast<const ConcreteAttr *>(impl)->isValidStore(tablegen_opaque_val, type, ordering, alignment, dataLayout, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::isValidAtomicOp(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::ptr::AtomicBinOp op, ::mlir::Type type, ::mlir::ptr::AtomicOrdering ordering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return static_cast<const ConcreteAttr *>(impl)->isValidAtomicOp(tablegen_opaque_val, op, type, ordering, alignment, dataLayout, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::isValidAtomicXchg(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type type, ::mlir::ptr::AtomicOrdering successOrdering, ::mlir::ptr::AtomicOrdering failureOrdering, std::optional<int64_t> alignment, const ::mlir::DataLayout * dataLayout, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return static_cast<const ConcreteAttr *>(impl)->isValidAtomicXchg(tablegen_opaque_val, type, successOrdering, failureOrdering, alignment, dataLayout, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::isValidAddrSpaceCast(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type tgt, ::mlir::Type src, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return static_cast<const ConcreteAttr *>(impl)->isValidAddrSpaceCast(tablegen_opaque_val, tgt, src, emitError);
}
template<typename ConcreteAttr>
bool detail::MemorySpaceAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::isValidPtrIntCast(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Type intLikeTy, ::mlir::Type ptrLikeTy, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return static_cast<const ConcreteAttr *>(impl)->isValidPtrIntCast(tablegen_opaque_val, intLikeTy, ptrLikeTy, emitError);
}

} // namespace mlir::ptr
