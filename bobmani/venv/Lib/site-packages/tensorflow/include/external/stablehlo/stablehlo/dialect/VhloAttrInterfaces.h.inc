/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::vhlo {

class VersionedAttrInterface;

} // namespace mlir::vhlo
namespace mlir::vhlo {

namespace detail {
struct VersionedAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::vhlo::Version (*getMinVersion)(const Concept *impl, ::mlir::Attribute );
    mlir::vhlo::Version (*getMaxVersion)(const Concept *impl, ::mlir::Attribute );
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::vhlo::VersionedAttrInterface;
    Model() : Concept{getMinVersion, getMaxVersion} {}

    static inline mlir::vhlo::Version getMinVersion(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline mlir::vhlo::Version getMaxVersion(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::vhlo::VersionedAttrInterface;
    FallbackModel() : Concept{getMinVersion, getMaxVersion} {}

    static inline mlir::vhlo::Version getMinVersion(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline mlir::vhlo::Version getMaxVersion(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct VersionedAttrInterfaceTrait;

} // namespace detail
class VersionedAttrInterface : public ::mlir::AttributeInterface<VersionedAttrInterface, detail::VersionedAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<VersionedAttrInterface, detail::VersionedAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::VersionedAttrInterfaceTrait<ConcreteAttr> {};

  /// Returns the minimum version of the VHLO dialect an attribute is supported in.
  mlir::vhlo::Version getMinVersion() const;

  /// Returns the maximum version (inclusive) of the VHLO dialect an attribute is supported in.
  mlir::vhlo::Version getMaxVersion() const;
};

} // namespace mlir::vhlo
namespace mlir::vhlo::detail {

  template <typename ConcreteAttr>
  struct VersionedAttrInterfaceTrait : public ::mlir::AttributeInterface<VersionedAttrInterface, detail::VersionedAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace mlir::vhlo::detail
namespace mlir::vhlo {

template<typename ConcreteAttr>
mlir::vhlo::Version detail::VersionedAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getMinVersion(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getMinVersion();
}
template<typename ConcreteAttr>
mlir::vhlo::Version detail::VersionedAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getMaxVersion(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getMaxVersion();
}
template<typename ConcreteAttr>
mlir::vhlo::Version detail::VersionedAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getMinVersion(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getMinVersion(tablegen_opaque_val);
}
template<typename ConcreteAttr>
mlir::vhlo::Version detail::VersionedAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getMaxVersion(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getMaxVersion(tablegen_opaque_val);
}

} // namespace mlir::vhlo
