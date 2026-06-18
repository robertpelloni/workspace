/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::linalg {

/// A Linalg relayout-op is either linalg.pack or linalg.unpack.
/// 
///     While we could extend this interface with methods from Linalg_RelayoutOp,
///     this is currently not needed and left as a TODO.
class RelayoutOpInterface;

} // namespace mlir::linalg
namespace mlir::linalg {

/// A Linalg relayout-op is either linalg.pack or linalg.unpack.
/// 
///     While we could extend this interface with methods from Linalg_RelayoutOp,
///     this is currently not needed and left as a TODO.
namespace detail {
struct RelayoutOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::linalg::RelayoutOpInterface;
    Model() : Concept{} {}

  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::linalg::RelayoutOpInterface;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct RelayoutOpInterfaceTrait;

} // namespace detail
class RelayoutOpInterface : public ::mlir::OpInterface<RelayoutOpInterface, detail::RelayoutOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<RelayoutOpInterface, detail::RelayoutOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::RelayoutOpInterfaceTrait<ConcreteOp> {};
};

} // namespace mlir::linalg
namespace mlir::linalg::detail {

  template <typename ConcreteOp>
  struct RelayoutOpInterfaceTrait : public ::mlir::OpInterface<RelayoutOpInterface, detail::RelayoutOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::linalg::detail
namespace mlir::linalg {


} // namespace mlir::linalg
