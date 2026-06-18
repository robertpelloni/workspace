/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// This interface describes an attribute that may use a `Symbol`. This
///     interface allows for users of symbols to hook into verification and other
///     symbol related utilities that are either costly or otherwise disallowed
///     within an operation (e.g., recreating symbol users per op verified rather
///     than per symbol table, or querying symbols usage of sibblings).
class SymbolUserAttrInterface;

} // namespace mlir
namespace mlir {

/// This interface describes an attribute that may use a `Symbol`. This
///     interface allows for users of symbols to hook into verification and other
///     symbol related utilities that are either costly or otherwise disallowed
///     within an operation (e.g., recreating symbol users per op verified rather
///     than per symbol table, or querying symbols usage of sibblings).
namespace detail {
struct SymbolUserAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::LogicalResult (*verifySymbolUses)(const Concept *impl, ::mlir::Attribute , ::mlir::Operation *, ::mlir::SymbolTableCollection &);
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::SymbolUserAttrInterface;
    Model() : Concept{verifySymbolUses} {}

    static inline ::llvm::LogicalResult verifySymbolUses(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Operation * op, ::mlir::SymbolTableCollection & symbolTable);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::SymbolUserAttrInterface;
    FallbackModel() : Concept{verifySymbolUses} {}

    static inline ::llvm::LogicalResult verifySymbolUses(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Operation * op, ::mlir::SymbolTableCollection & symbolTable);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct SymbolUserAttrInterfaceTrait;

} // namespace detail
class SymbolUserAttrInterface : public ::mlir::AttributeInterface<SymbolUserAttrInterface, detail::SymbolUserAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<SymbolUserAttrInterface, detail::SymbolUserAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::SymbolUserAttrInterfaceTrait<ConcreteAttr> {};

  /// Verify the symbol uses held by this attribute of this operation.
  ::llvm::LogicalResult verifySymbolUses(::mlir::Operation * op, ::mlir::SymbolTableCollection & symbolTable) const;
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteAttr>
  struct SymbolUserAttrInterfaceTrait : public ::mlir::AttributeInterface<SymbolUserAttrInterface, detail::SymbolUserAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteAttr>
::llvm::LogicalResult detail::SymbolUserAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::verifySymbolUses(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Operation * op, ::mlir::SymbolTableCollection & symbolTable) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).verifySymbolUses(op, symbolTable);
}
template<typename ConcreteAttr>
::llvm::LogicalResult detail::SymbolUserAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::verifySymbolUses(const Concept *impl, ::mlir::Attribute tablegen_opaque_val, ::mlir::Operation * op, ::mlir::SymbolTableCollection & symbolTable) {
  return static_cast<const ConcreteAttr *>(impl)->verifySymbolUses(tablegen_opaque_val, op, symbolTable);
}

} // namespace mlir
