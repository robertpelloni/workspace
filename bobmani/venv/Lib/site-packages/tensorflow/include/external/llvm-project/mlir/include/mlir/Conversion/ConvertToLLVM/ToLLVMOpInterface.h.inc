/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// Interface for collecting all convert to LLVM attributes stored in an
///     operation. See `ConvertToLLVMAttrInterface` for more information on these
///     attributes.
class ConvertToLLVMOpInterface;

} // namespace mlir
namespace mlir {

/// Interface for collecting all convert to LLVM attributes stored in an
///     operation. See `ConvertToLLVMAttrInterface` for more information on these
///     attributes.
namespace detail {
struct ConvertToLLVMOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    void (*getConvertToLLVMConversionAttrs)(const Concept *impl, ::mlir::Operation *, ::llvm::SmallVectorImpl<::mlir::ConvertToLLVMAttrInterface>&);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::ConvertToLLVMOpInterface;
    Model() : Concept{getConvertToLLVMConversionAttrs} {}

    static inline void getConvertToLLVMConversionAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::SmallVectorImpl<::mlir::ConvertToLLVMAttrInterface>& attrs);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::ConvertToLLVMOpInterface;
    FallbackModel() : Concept{getConvertToLLVMConversionAttrs} {}

    static inline void getConvertToLLVMConversionAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::SmallVectorImpl<::mlir::ConvertToLLVMAttrInterface>& attrs);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct ConvertToLLVMOpInterfaceTrait;

} // namespace detail
class ConvertToLLVMOpInterface : public ::mlir::OpInterface<ConvertToLLVMOpInterface, detail::ConvertToLLVMOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ConvertToLLVMOpInterface, detail::ConvertToLLVMOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ConvertToLLVMOpInterfaceTrait<ConcreteOp> {};

  /// Populate the provided vector with a list of convert to LLVM attributes
  /// to apply.
  void getConvertToLLVMConversionAttrs(::llvm::SmallVectorImpl<::mlir::ConvertToLLVMAttrInterface>& attrs);
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteOp>
  struct ConvertToLLVMOpInterfaceTrait : public ::mlir::OpInterface<ConvertToLLVMOpInterface, detail::ConvertToLLVMOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::detail
namespace mlir {

template<typename ConcreteOp>
void detail::ConvertToLLVMOpInterfaceInterfaceTraits::Model<ConcreteOp>::getConvertToLLVMConversionAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::SmallVectorImpl<::mlir::ConvertToLLVMAttrInterface>& attrs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getConvertToLLVMConversionAttrs(attrs);
}
template<typename ConcreteOp>
void detail::ConvertToLLVMOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getConvertToLLVMConversionAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::SmallVectorImpl<::mlir::ConvertToLLVMAttrInterface>& attrs) {
  return static_cast<const ConcreteOp *>(impl)->getConvertToLLVMConversionAttrs(tablegen_opaque_val, attrs);
}

} // namespace mlir
