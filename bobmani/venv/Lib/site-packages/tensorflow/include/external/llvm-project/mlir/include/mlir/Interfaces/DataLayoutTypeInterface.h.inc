/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// Interface for types subject to data layout.
/// 
///     Types willing to be supported by the data layout subsystem should implement
///     this interface by providing implementations of functions querying their
///     size, required and preferred alignment. Each of these functions accepts as
///     arguments a data layout object that can be used to perform recursive queries
///     in the same scope, and a list of data layout entries relevant to this type.
///     Specifically, the entries are those that have as key _any instance_ of the
///     same type class as the current type. For example, if IntegerType had
///     implemented this interface, it would have received the entries with keys i1,
///     i2, i8, etc. regardless of the bitwidth of this type. This mechanism allows
///     types to "interpolate" the results in a type-specific way instead of listing
///     all possible types in the specification.
/// 
///     The list of entries may be empty, in which case the type must provide a
///     reasonable default value. The entries in the list are known to have passed
///     the spec and the entry verifiers, as well as the type-specified verifier if
///     provided.
/// 
///     In case of nested layout specs or spec changes, the type can override a hook
///     indicating whether the outer (old) and the inner (new) spec are compatible.
class DataLayoutTypeInterface;

} // namespace mlir
namespace mlir {

/// Interface for types subject to data layout.
/// 
///     Types willing to be supported by the data layout subsystem should implement
///     this interface by providing implementations of functions querying their
///     size, required and preferred alignment. Each of these functions accepts as
///     arguments a data layout object that can be used to perform recursive queries
///     in the same scope, and a list of data layout entries relevant to this type.
///     Specifically, the entries are those that have as key _any instance_ of the
///     same type class as the current type. For example, if IntegerType had
///     implemented this interface, it would have received the entries with keys i1,
///     i2, i8, etc. regardless of the bitwidth of this type. This mechanism allows
///     types to "interpolate" the results in a type-specific way instead of listing
///     all possible types in the specification.
/// 
///     The list of entries may be empty, in which case the type must provide a
///     reasonable default value. The entries in the list are known to have passed
///     the spec and the entry verifiers, as well as the type-specified verifier if
///     provided.
/// 
///     In case of nested layout specs or spec changes, the type can override a hook
///     indicating whether the outer (old) and the inner (new) spec are compatible.
namespace detail {
struct DataLayoutTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::TypeSize (*getTypeSize)(const Concept *impl, ::mlir::Type , const ::mlir::DataLayout &, ::mlir::DataLayoutEntryListRef);
    ::llvm::TypeSize (*getTypeSizeInBits)(const Concept *impl, ::mlir::Type , const ::mlir::DataLayout &, ::mlir::DataLayoutEntryListRef);
    uint64_t (*getABIAlignment)(const Concept *impl, ::mlir::Type , const ::mlir::DataLayout &, ::mlir::DataLayoutEntryListRef);
    uint64_t (*getPreferredAlignment)(const Concept *impl, ::mlir::Type , const ::mlir::DataLayout &, ::mlir::DataLayoutEntryListRef);
    std::optional<uint64_t> (*getIndexBitwidth)(const Concept *impl, ::mlir::Type , const ::mlir::DataLayout &, ::mlir::DataLayoutEntryListRef);
    bool (*areCompatible)(const Concept *impl, ::mlir::Type , ::mlir::DataLayoutEntryListRef, ::mlir::DataLayoutEntryListRef, ::mlir::DataLayoutSpecInterface, const ::mlir::DataLayoutIdentifiedEntryMap&);
    ::llvm::LogicalResult (*verifyEntries)(const Concept *impl, ::mlir::Type , ::mlir::DataLayoutEntryListRef, ::mlir::Location);
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::DataLayoutTypeInterface;
    Model() : Concept{getTypeSize, getTypeSizeInBits, getABIAlignment, getPreferredAlignment, getIndexBitwidth, areCompatible, verifyEntries} {}

    static inline ::llvm::TypeSize getTypeSize(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline ::llvm::TypeSize getTypeSizeInBits(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline uint64_t getABIAlignment(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline uint64_t getPreferredAlignment(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline std::optional<uint64_t> getIndexBitwidth(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline bool areCompatible(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap& identified);
    static inline ::llvm::LogicalResult verifyEntries(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::DataLayoutTypeInterface;
    FallbackModel() : Concept{getTypeSize, getTypeSizeInBits, getABIAlignment, getPreferredAlignment, getIndexBitwidth, areCompatible, verifyEntries} {}

    static inline ::llvm::TypeSize getTypeSize(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline ::llvm::TypeSize getTypeSizeInBits(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline uint64_t getABIAlignment(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline uint64_t getPreferredAlignment(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline std::optional<uint64_t> getIndexBitwidth(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params);
    static inline bool areCompatible(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap& identified);
    static inline ::llvm::LogicalResult verifyEntries(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
    ::llvm::TypeSize getTypeSize(::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
    uint64_t getPreferredAlignment(::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
    std::optional<uint64_t> getIndexBitwidth(::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const;
    bool areCompatible(::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap&identified) const;
    ::llvm::LogicalResult verifyEntries(::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc) const;
  };
};
template <typename ConcreteType>
struct DataLayoutTypeInterfaceTrait;

} // namespace detail
class DataLayoutTypeInterface : public ::mlir::TypeInterface<DataLayoutTypeInterface, detail::DataLayoutTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<DataLayoutTypeInterface, detail::DataLayoutTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::DataLayoutTypeInterfaceTrait<ConcreteType> {};

  /// Returns the size of this type in bytes.
  ::llvm::TypeSize getTypeSize(const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) const;

  /// Returns the size of this type in bits.
  ::llvm::TypeSize getTypeSizeInBits(const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) const;

  /// Returns the ABI-required alignment for this type, in bytes
  uint64_t getABIAlignment(const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) const;

  /// Returns the preferred alignment for this type, in bytes.
  uint64_t getPreferredAlignment(const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) const;

  /// Returns the bitwidth that should be used when performing index computations for the given pointer-like type. If the type is not a pointer-like type, returns std::nullopt.
  std::optional<uint64_t> getIndexBitwidth(const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) const;

  /// Returns true if the two lists of entries are compatible, that is, that `newLayout` spec entries can be nested in an op with `oldLayout` spec entries. `newSpec` and `identified` areprovided to further query data from the combined spec, e.g.,the default address space. TODO: Revisit this method oncehttps://github.com/llvm/llvm-project/issues/130321 gets solved
  bool areCompatible(::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap& identified) const;

  /// Verifies that the given list of entries is valid for this type.
  ::llvm::LogicalResult verifyEntries(::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc) const;
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteType>
  struct DataLayoutTypeInterfaceTrait : public ::mlir::TypeInterface<DataLayoutTypeInterface, detail::DataLayoutTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {

    /// Returns the size of this type in bytes.
    ::llvm::TypeSize getTypeSize(const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) const {
      ::llvm::TypeSize bits = (*static_cast<const ConcreteType *>(this)).getTypeSizeInBits(dataLayout, params);
        return ::mlir::detail::divideCeil(bits, 8u);
    }

    /// Returns the preferred alignment for this type, in bytes.
    uint64_t getPreferredAlignment(const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) const {
      return (*static_cast<const ConcreteType *>(this)).getABIAlignment(dataLayout, params);
    }

    /// Returns the bitwidth that should be used when performing index computations for the given pointer-like type. If the type is not a pointer-like type, returns std::nullopt.
    std::optional<uint64_t> getIndexBitwidth(const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) const {
      return std::nullopt;
    }

    /// Returns true if the two lists of entries are compatible, that is, that `newLayout` spec entries can be nested in an op with `oldLayout` spec entries. `newSpec` and `identified` areprovided to further query data from the combined spec, e.g.,the default address space. TODO: Revisit this method oncehttps://github.com/llvm/llvm-project/issues/130321 gets solved
    bool areCompatible(::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap& identified) const {
      return true;
    }

    /// Verifies that the given list of entries is valid for this type.
    ::llvm::LogicalResult verifyEntries(::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc) const {
      return ::mlir::success();
    }
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteType>
::llvm::TypeSize detail::DataLayoutTypeInterfaceInterfaceTraits::Model<ConcreteType>::getTypeSize(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getTypeSize(dataLayout, params);
}
template<typename ConcreteType>
::llvm::TypeSize detail::DataLayoutTypeInterfaceInterfaceTraits::Model<ConcreteType>::getTypeSizeInBits(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getTypeSizeInBits(dataLayout, params);
}
template<typename ConcreteType>
uint64_t detail::DataLayoutTypeInterfaceInterfaceTraits::Model<ConcreteType>::getABIAlignment(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getABIAlignment(dataLayout, params);
}
template<typename ConcreteType>
uint64_t detail::DataLayoutTypeInterfaceInterfaceTraits::Model<ConcreteType>::getPreferredAlignment(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getPreferredAlignment(dataLayout, params);
}
template<typename ConcreteType>
std::optional<uint64_t> detail::DataLayoutTypeInterfaceInterfaceTraits::Model<ConcreteType>::getIndexBitwidth(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getIndexBitwidth(dataLayout, params);
}
template<typename ConcreteType>
bool detail::DataLayoutTypeInterfaceInterfaceTraits::Model<ConcreteType>::areCompatible(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap& identified) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).areCompatible(oldLayout, newLayout, newSpec, identified);
}
template<typename ConcreteType>
::llvm::LogicalResult detail::DataLayoutTypeInterfaceInterfaceTraits::Model<ConcreteType>::verifyEntries(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).verifyEntries(entries, loc);
}
template<typename ConcreteType>
::llvm::TypeSize detail::DataLayoutTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getTypeSize(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return static_cast<const ConcreteType *>(impl)->getTypeSize(tablegen_opaque_val, dataLayout, params);
}
template<typename ConcreteType>
::llvm::TypeSize detail::DataLayoutTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getTypeSizeInBits(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return static_cast<const ConcreteType *>(impl)->getTypeSizeInBits(tablegen_opaque_val, dataLayout, params);
}
template<typename ConcreteType>
uint64_t detail::DataLayoutTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getABIAlignment(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return static_cast<const ConcreteType *>(impl)->getABIAlignment(tablegen_opaque_val, dataLayout, params);
}
template<typename ConcreteType>
uint64_t detail::DataLayoutTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getPreferredAlignment(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return static_cast<const ConcreteType *>(impl)->getPreferredAlignment(tablegen_opaque_val, dataLayout, params);
}
template<typename ConcreteType>
std::optional<uint64_t> detail::DataLayoutTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getIndexBitwidth(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout & dataLayout, ::mlir::DataLayoutEntryListRef params) {
  return static_cast<const ConcreteType *>(impl)->getIndexBitwidth(tablegen_opaque_val, dataLayout, params);
}
template<typename ConcreteType>
bool detail::DataLayoutTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::areCompatible(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap& identified) {
  return static_cast<const ConcreteType *>(impl)->areCompatible(tablegen_opaque_val, oldLayout, newLayout, newSpec, identified);
}
template<typename ConcreteType>
::llvm::LogicalResult detail::DataLayoutTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::verifyEntries(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc) {
  return static_cast<const ConcreteType *>(impl)->verifyEntries(tablegen_opaque_val, entries, loc);
}
template<typename ConcreteModel, typename ConcreteType>
::llvm::TypeSize detail::DataLayoutTypeInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteType>::getTypeSize(::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const {
::llvm::TypeSize bits = (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getTypeSizeInBits(dataLayout, params);
        return ::mlir::detail::divideCeil(bits, 8u);
}
template<typename ConcreteModel, typename ConcreteType>
uint64_t detail::DataLayoutTypeInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteType>::getPreferredAlignment(::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const {
return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getABIAlignment(dataLayout, params);
}
template<typename ConcreteModel, typename ConcreteType>
std::optional<uint64_t> detail::DataLayoutTypeInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteType>::getIndexBitwidth(::mlir::Type tablegen_opaque_val, const ::mlir::DataLayout &dataLayout, ::mlir::DataLayoutEntryListRef params) const {
return std::nullopt;
}
template<typename ConcreteModel, typename ConcreteType>
bool detail::DataLayoutTypeInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteType>::areCompatible(::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef oldLayout, ::mlir::DataLayoutEntryListRef newLayout, ::mlir::DataLayoutSpecInterface newSpec, const ::mlir::DataLayoutIdentifiedEntryMap&identified) const {
return true;
}
template<typename ConcreteModel, typename ConcreteType>
::llvm::LogicalResult detail::DataLayoutTypeInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteType>::verifyEntries(::mlir::Type tablegen_opaque_val, ::mlir::DataLayoutEntryListRef entries, ::mlir::Location loc) const {
return ::mlir::success();
}

} // namespace mlir
