/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::NVVM {

class RequiresSMInterface;

} // namespace mlir::NVVM
namespace mlir::NVVM {

namespace detail {
struct RequiresSMInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    const mlir::NVVM::NVVMCheckSMVersion (*getRequiredMinSMVersion)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::NVVM::RequiresSMInterface;
    Model() : Concept{getRequiredMinSMVersion} {}

    static inline const mlir::NVVM::NVVMCheckSMVersion getRequiredMinSMVersion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::NVVM::RequiresSMInterface;
    FallbackModel() : Concept{getRequiredMinSMVersion} {}

    static inline const mlir::NVVM::NVVMCheckSMVersion getRequiredMinSMVersion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct RequiresSMInterfaceTrait;

} // namespace detail
class RequiresSMInterface : public ::mlir::OpInterface<RequiresSMInterface, detail::RequiresSMInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<RequiresSMInterface, detail::RequiresSMInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::RequiresSMInterfaceTrait<ConcreteOp> {};

  /// Get the SM version required by the op from the trait
  const mlir::NVVM::NVVMCheckSMVersion getRequiredMinSMVersion();
};

} // namespace mlir::NVVM
namespace mlir::NVVM::detail {

  template <typename ConcreteOp>
  struct RequiresSMInterfaceTrait : public ::mlir::OpInterface<RequiresSMInterface, detail::RequiresSMInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::NVVM::detail
namespace mlir::NVVM {

template<typename ConcreteOp>
const mlir::NVVM::NVVMCheckSMVersion detail::RequiresSMInterfaceInterfaceTraits::Model<ConcreteOp>::getRequiredMinSMVersion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getRequiredMinSMVersion();
}
template<typename ConcreteOp>
const mlir::NVVM::NVVMCheckSMVersion detail::RequiresSMInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getRequiredMinSMVersion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getRequiredMinSMVersion(tablegen_opaque_val);
}

} // namespace mlir::NVVM
