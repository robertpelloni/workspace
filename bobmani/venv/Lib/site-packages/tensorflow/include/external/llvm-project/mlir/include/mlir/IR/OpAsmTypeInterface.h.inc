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
class OpAsmTypeInterface;

} // namespace mlir
namespace mlir {

/// This interface provides hooks to interact with the AsmPrinter and AsmParser
///     classes.
namespace detail {
struct OpAsmTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    void (*getAsmName)(const Concept *impl, ::mlir::Type , ::mlir::OpAsmSetNameFn);
    ::mlir::OpAsmAliasResult (*getAlias)(const Concept *impl, ::mlir::Type , ::llvm::raw_ostream&);
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::OpAsmTypeInterface;
    Model() : Concept{getAsmName, getAlias} {}

    static inline void getAsmName(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::OpAsmSetNameFn setNameFn);
    static inline ::mlir::OpAsmAliasResult getAlias(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::llvm::raw_ostream& os);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::OpAsmTypeInterface;
    FallbackModel() : Concept{getAsmName, getAlias} {}

    static inline void getAsmName(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::OpAsmSetNameFn setNameFn);
    static inline ::mlir::OpAsmAliasResult getAlias(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::llvm::raw_ostream& os);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
    void getAsmName(::mlir::Type tablegen_opaque_val, ::mlir::OpAsmSetNameFn setNameFn) const;
    ::mlir::OpAsmAliasResult getAlias(::mlir::Type tablegen_opaque_val, ::llvm::raw_ostream&os) const;
  };
};
template <typename ConcreteType>
struct OpAsmTypeInterfaceTrait;

} // namespace detail
class OpAsmTypeInterface : public ::mlir::TypeInterface<OpAsmTypeInterface, detail::OpAsmTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<OpAsmTypeInterface, detail::OpAsmTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::OpAsmTypeInterfaceTrait<ConcreteType> {};

  /// Get a name to use when printing a value of this type.
  void getAsmName(::mlir::OpAsmSetNameFn setNameFn) const;

  /// Get a name to use when generating an alias for this type.
  ::mlir::OpAsmAliasResult getAlias(::llvm::raw_ostream& os) const;
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteType>
  struct OpAsmTypeInterfaceTrait : public ::mlir::TypeInterface<OpAsmTypeInterface, detail::OpAsmTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {

    /// Get a name to use when printing a value of this type.
    void getAsmName(::mlir::OpAsmSetNameFn setNameFn) const {
      ;
    }

    /// Get a name to use when generating an alias for this type.
    ::mlir::OpAsmAliasResult getAlias(::llvm::raw_ostream& os) const {
      return ::mlir::OpAsmAliasResult::NoAlias;
    }
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteType>
void detail::OpAsmTypeInterfaceInterfaceTraits::Model<ConcreteType>::getAsmName(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::OpAsmSetNameFn setNameFn) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getAsmName(setNameFn);
}
template<typename ConcreteType>
::mlir::OpAsmAliasResult detail::OpAsmTypeInterfaceInterfaceTraits::Model<ConcreteType>::getAlias(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::llvm::raw_ostream& os) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getAlias(os);
}
template<typename ConcreteType>
void detail::OpAsmTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getAsmName(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::OpAsmSetNameFn setNameFn) {
  return static_cast<const ConcreteType *>(impl)->getAsmName(tablegen_opaque_val, setNameFn);
}
template<typename ConcreteType>
::mlir::OpAsmAliasResult detail::OpAsmTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getAlias(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::llvm::raw_ostream& os) {
  return static_cast<const ConcreteType *>(impl)->getAlias(tablegen_opaque_val, os);
}
template<typename ConcreteModel, typename ConcreteType>
void detail::OpAsmTypeInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteType>::getAsmName(::mlir::Type tablegen_opaque_val, ::mlir::OpAsmSetNameFn setNameFn) const {
;
}
template<typename ConcreteModel, typename ConcreteType>
::mlir::OpAsmAliasResult detail::OpAsmTypeInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteType>::getAlias(::mlir::Type tablegen_opaque_val, ::llvm::raw_ostream&os) const {
return ::mlir::OpAsmAliasResult::NoAlias;
}

} // namespace mlir
