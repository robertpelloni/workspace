/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// This interface provides hooks to interact with the AsmPrinter and AsmParser
///     classes.
class OpAsmAttrInterface;

} // namespace mlir
namespace mlir {

/// This interface provides hooks to interact with the AsmPrinter and AsmParser
///     classes.
namespace detail {
struct OpAsmAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::OpAsmAliasResult (*getAlias)(const Concept *impl, ::mlir::Attribute , ::llvm::raw_ostream&);
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::OpAsmAttrInterface;
    Model() : Concept{getAlias} {}

    static inline ::mlir::OpAsmAliasResult getAlias(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::llvm::raw_ostream& os);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::OpAsmAttrInterface;
    FallbackModel() : Concept{getAlias} {}

    static inline ::mlir::OpAsmAliasResult getAlias(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::llvm::raw_ostream& os);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
    ::mlir::OpAsmAliasResult getAlias(::mlir::Attribute tablegen_opaque_val, ::llvm::raw_ostream&os) const;
  };
};
template <typename ConcreteAttr>
struct OpAsmAttrInterfaceTrait;

} // namespace detail
class OpAsmAttrInterface : public ::mlir::AttributeInterface<OpAsmAttrInterface, detail::OpAsmAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<OpAsmAttrInterface, detail::OpAsmAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::OpAsmAttrInterfaceTrait<ConcreteAttr> {};

  /// Get a name to use when generating an alias for this attribute.
  ::mlir::OpAsmAliasResult getAlias(::llvm::raw_ostream& os) const;
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteAttr>
  struct OpAsmAttrInterfaceTrait : public ::mlir::AttributeInterface<OpAsmAttrInterface, detail::OpAsmAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {

    /// Get a name to use when generating an alias for this attribute.
    ::mlir::OpAsmAliasResult getAlias(::llvm::raw_ostream& os) const {
      return ::mlir::OpAsmAliasResult::NoAlias;
    }
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteAttr>
::mlir::OpAsmAliasResult detail::OpAsmAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getAlias(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::llvm::raw_ostream& os) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getAlias(os);
}
template<typename ConcreteAttr>
::mlir::OpAsmAliasResult detail::OpAsmAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getAlias(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::llvm::raw_ostream& os) {
  return static_cast<const ConcreteAttr *>(impl)->getAlias(tablegen_opaque_val, os);
}
template<typename ConcreteModel, typename ConcreteAttr>
::mlir::OpAsmAliasResult detail::OpAsmAttrInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteAttr>::getAlias(::mlir::Attribute tablegen_opaque_val, ::llvm::raw_ostream&os) const {
return ::mlir::OpAsmAliasResult::NoAlias;
}

} // namespace mlir
