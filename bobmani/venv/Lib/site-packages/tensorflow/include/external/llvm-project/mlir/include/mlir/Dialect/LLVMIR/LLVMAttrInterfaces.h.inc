/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::LLVM {

/// This attribute represents a DITypeAttr that is recursive. Only DITypeAttrs
///     that translate to LLVM DITypes that support mutation should implement this
///     interface.
/// 
///     There are two modes for conforming attributes:
/// 
///     1. "rec-decl":
///       - This attr is a recursive declaration identified by a recId.
/// 
///     2. "rec-self":
///       - This attr is considered a recursive self reference.
///       - This attr itself is a placeholder type that should be conceptually
///         replaced with the closest parent attr of the same type with the same
///         recId.
/// 
///     For example, to represent a linked list struct:
/// 
///       #rec_self = di_composite_type<recId = 0>
///       #ptr = di_derived_type<baseType: #rec_self, ...>
///       #field = di_derived_type<name = "next", baseType: #ptr, ...>
///       #rec = di_composite_type<recId = 0, name = "Node", elements: #field, ...>
///       #var = di_local_variable<type = #rec, ...>
/// 
///     Note that a rec-self without an outer rec-decl with the same recId is
///     conceptually the same as an "unbound" variable. The context needs to provide
///     meaning to the rec-self.
class DIRecursiveTypeAttrInterface;

} // namespace mlir::LLVM
namespace mlir::LLVM {

/// An interface for attributes that represent LLVM address spaces.
///     Implementing attributes should provide access to the address space value
///     as an unsigned integer.
class LLVMAddrSpaceAttrInterface;

} // namespace mlir::LLVM
namespace mlir::LLVM {

/// Interface for attributes that describe LLVM targets.
/// 
///     These attributes should be able to return the specified target `triple`,
///     `chip` and `features`.
/// 
///     Implementing attributes should provide a `DLTIQueryInterface::query()`
///     implementation which responds to keys `"triple"`, `"chip"` and `"features"`
///     by returning appropriate `StringAttr`s.
class TargetAttrInterface;

} // namespace mlir::LLVM
namespace mlir::LLVM {

/// This attribute represents a DITypeAttr that is recursive. Only DITypeAttrs
///     that translate to LLVM DITypes that support mutation should implement this
///     interface.
/// 
///     There are two modes for conforming attributes:
/// 
///     1. "rec-decl":
///       - This attr is a recursive declaration identified by a recId.
/// 
///     2. "rec-self":
///       - This attr is considered a recursive self reference.
///       - This attr itself is a placeholder type that should be conceptually
///         replaced with the closest parent attr of the same type with the same
///         recId.
/// 
///     For example, to represent a linked list struct:
/// 
///       #rec_self = di_composite_type<recId = 0>
///       #ptr = di_derived_type<baseType: #rec_self, ...>
///       #field = di_derived_type<name = "next", baseType: #ptr, ...>
///       #rec = di_composite_type<recId = 0, name = "Node", elements: #field, ...>
///       #var = di_local_variable<type = #rec, ...>
/// 
///     Note that a rec-self without an outer rec-decl with the same recId is
///     conceptually the same as an "unbound" variable. The context needs to provide
///     meaning to the rec-self.
namespace detail {
struct DIRecursiveTypeAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*getIsRecSelf)(const Concept *impl, ::mlir::Attribute );
    DistinctAttr (*getRecId)(const Concept *impl, ::mlir::Attribute );
    DIRecursiveTypeAttrInterface (*withRecId)(const Concept *impl, ::mlir::Attribute , DistinctAttr);
    DIRecursiveTypeAttrInterface (*getRecSelf)(DistinctAttr);
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::LLVM::DIRecursiveTypeAttrInterface;
    Model() : Concept{getIsRecSelf, getRecId, withRecId, getRecSelf} {}

    static inline bool getIsRecSelf(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline DistinctAttr getRecId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline DIRecursiveTypeAttrInterface withRecId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, DistinctAttr recId);
    static inline DIRecursiveTypeAttrInterface getRecSelf(DistinctAttr recId);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::LLVM::DIRecursiveTypeAttrInterface;
    FallbackModel() : Concept{getIsRecSelf, getRecId, withRecId, getRecSelf} {}

    static inline bool getIsRecSelf(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline DistinctAttr getRecId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline DIRecursiveTypeAttrInterface withRecId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, DistinctAttr recId);
    static inline DIRecursiveTypeAttrInterface getRecSelf(DistinctAttr recId);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct DIRecursiveTypeAttrInterfaceTrait;

} // namespace detail
class DIRecursiveTypeAttrInterface : public ::mlir::AttributeInterface<DIRecursiveTypeAttrInterface, detail::DIRecursiveTypeAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<DIRecursiveTypeAttrInterface, detail::DIRecursiveTypeAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::DIRecursiveTypeAttrInterfaceTrait<ConcreteAttr> {};

  /// Get whether this attr describes a recursive self reference.
  bool getIsRecSelf() const;

  /// Get the recursive ID used for matching "rec-decl" with "rec-self".
  /// If this attr instance is not recursive, return a null attribute.
  DistinctAttr getRecId() const;

  /// Get a copy of this type attr but with the recursive ID set to `recId`.
  DIRecursiveTypeAttrInterface withRecId(DistinctAttr recId) const;

  /// Build a rec-self instance using the provided `recId`.
  DIRecursiveTypeAttrInterface getRecSelf(DistinctAttr recId) const;
};

} // namespace mlir::LLVM
namespace mlir::LLVM {

/// An interface for attributes that represent LLVM address spaces.
///     Implementing attributes should provide access to the address space value
///     as an unsigned integer.
namespace detail {
struct LLVMAddrSpaceAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    unsigned (*getAddressSpace)(const Concept *impl, ::mlir::Attribute );
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::LLVM::LLVMAddrSpaceAttrInterface;
    Model() : Concept{getAddressSpace} {}

    static inline unsigned getAddressSpace(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::LLVM::LLVMAddrSpaceAttrInterface;
    FallbackModel() : Concept{getAddressSpace} {}

    static inline unsigned getAddressSpace(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct LLVMAddrSpaceAttrInterfaceTrait;

} // namespace detail
class LLVMAddrSpaceAttrInterface : public ::mlir::AttributeInterface<LLVMAddrSpaceAttrInterface, detail::LLVMAddrSpaceAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<LLVMAddrSpaceAttrInterface, detail::LLVMAddrSpaceAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::LLVMAddrSpaceAttrInterfaceTrait<ConcreteAttr> {};

  /// Returns the address space as an unsigned integer.
  unsigned getAddressSpace() const;
};

} // namespace mlir::LLVM
namespace mlir::LLVM {

/// Interface for attributes that describe LLVM targets.
/// 
///     These attributes should be able to return the specified target `triple`,
///     `chip` and `features`.
/// 
///     Implementing attributes should provide a `DLTIQueryInterface::query()`
///     implementation which responds to keys `"triple"`, `"chip"` and `"features"`
///     by returning appropriate `StringAttr`s.
namespace detail {
struct TargetAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    StringAttr (*getTriple)(const Concept *impl, ::mlir::Attribute );
    StringAttr (*getChip)(const Concept *impl, ::mlir::Attribute );
    Attribute (*getFeatures)(const Concept *impl, ::mlir::Attribute );
    /// The base classes of this interface.
    const ::mlir::DLTIQueryInterface::Concept *implDLTIQueryInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implDLTIQueryInterface = interfaceMap.lookup<::mlir::DLTIQueryInterface>();
      assert(implDLTIQueryInterface && "`::mlir::LLVM::TargetAttrInterface` expected its base interface `::mlir::DLTIQueryInterface` to be registered");
    }
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::LLVM::TargetAttrInterface;
    Model() : Concept{getTriple, getChip, getFeatures} {}

    static inline StringAttr getTriple(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline StringAttr getChip(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline Attribute getFeatures(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::LLVM::TargetAttrInterface;
    FallbackModel() : Concept{getTriple, getChip, getFeatures} {}

    static inline StringAttr getTriple(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline StringAttr getChip(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline Attribute getFeatures(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct TargetAttrInterfaceTrait;

} // namespace detail
class TargetAttrInterface : public ::mlir::AttributeInterface<TargetAttrInterface, detail::TargetAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<TargetAttrInterface, detail::TargetAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::TargetAttrInterfaceTrait<ConcreteAttr> {};

  /// Returns the target triple identifier.
  StringAttr getTriple() const;

  /// Returns the target chip (i.e. "cpu") identifier.
  StringAttr getChip() const;

  /// Returns the target features as a TargetFeaturesAttr.
  Attribute getFeatures() const;
  //===----------------------------------------------------------------===//
  // Inherited from ::mlir::DLTIQueryInterface
  //===----------------------------------------------------------------===//

  operator ::mlir::DLTIQueryInterface () const {
    if (!*this) return nullptr;
    return ::mlir::DLTIQueryInterface(*this, getImpl()->implDLTIQueryInterface);
  }


  /// Returns the attribute associated with the key.
  ::mlir::FailureOr<::mlir::Attribute> query(::mlir::DataLayoutEntryKey key) const;
};

} // namespace mlir::LLVM
namespace mlir::LLVM::detail {

  template <typename ConcreteAttr>
  struct DIRecursiveTypeAttrInterfaceTrait : public ::mlir::AttributeInterface<DIRecursiveTypeAttrInterface, detail::DIRecursiveTypeAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace mlir::LLVM::detail
namespace mlir::LLVM::detail {

  template <typename ConcreteAttr>
  struct LLVMAddrSpaceAttrInterfaceTrait : public ::mlir::AttributeInterface<LLVMAddrSpaceAttrInterface, detail::LLVMAddrSpaceAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace mlir::LLVM::detail
namespace mlir::LLVM::detail {

  template <typename ConcreteAttr>
  struct TargetAttrInterfaceTrait : public ::mlir::AttributeInterface<TargetAttrInterface, detail::TargetAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace mlir::LLVM::detail
namespace mlir::LLVM {

template<typename ConcreteAttr>
bool detail::DIRecursiveTypeAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getIsRecSelf(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getIsRecSelf();
}
template<typename ConcreteAttr>
DistinctAttr detail::DIRecursiveTypeAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getRecId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getRecId();
}
template<typename ConcreteAttr>
DIRecursiveTypeAttrInterface detail::DIRecursiveTypeAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::withRecId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, DistinctAttr recId) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).withRecId(recId);
}
template<typename ConcreteAttr>
DIRecursiveTypeAttrInterface detail::DIRecursiveTypeAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getRecSelf(DistinctAttr recId) {
  return ConcreteAttr::getRecSelf(recId);
}
template<typename ConcreteAttr>
bool detail::DIRecursiveTypeAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getIsRecSelf(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getIsRecSelf(tablegen_opaque_val);
}
template<typename ConcreteAttr>
DistinctAttr detail::DIRecursiveTypeAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getRecId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getRecId(tablegen_opaque_val);
}
template<typename ConcreteAttr>
DIRecursiveTypeAttrInterface detail::DIRecursiveTypeAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::withRecId(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, DistinctAttr recId) {
  return static_cast<const ConcreteAttr *>(impl)->withRecId(tablegen_opaque_val, recId);
}
template<typename ConcreteAttr>
DIRecursiveTypeAttrInterface detail::DIRecursiveTypeAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getRecSelf(DistinctAttr recId) {
  return ConcreteAttr::getRecSelf(recId);
}

} // namespace mlir::LLVM
namespace mlir::LLVM {

template<typename ConcreteAttr>
unsigned detail::LLVMAddrSpaceAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getAddressSpace(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getAddressSpace();
}
template<typename ConcreteAttr>
unsigned detail::LLVMAddrSpaceAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getAddressSpace(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getAddressSpace(tablegen_opaque_val);
}

} // namespace mlir::LLVM
namespace mlir::LLVM {

template<typename ConcreteAttr>
StringAttr detail::TargetAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getTriple(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getTriple();
}
template<typename ConcreteAttr>
StringAttr detail::TargetAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getChip(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getChip();
}
template<typename ConcreteAttr>
Attribute detail::TargetAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getFeatures(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getFeatures();
}
template<typename ConcreteAttr>
StringAttr detail::TargetAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getTriple(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getTriple(tablegen_opaque_val);
}
template<typename ConcreteAttr>
StringAttr detail::TargetAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getChip(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getChip(tablegen_opaque_val);
}
template<typename ConcreteAttr>
Attribute detail::TargetAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getFeatures(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getFeatures(tablegen_opaque_val);
}

} // namespace mlir::LLVM
