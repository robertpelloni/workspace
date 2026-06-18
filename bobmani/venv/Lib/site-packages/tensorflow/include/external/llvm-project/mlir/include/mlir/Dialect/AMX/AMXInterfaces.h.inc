/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::amx {

/// A wrapper interface for operations representing AMX LLVM intrinsics.
class AMXIntrinsicOp;

} // namespace mlir::amx
namespace mlir::amx {

/// A wrapper interface for operations representing AMX LLVM intrinsics.
namespace detail {
struct AMXIntrinsicOpInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    /// The base classes of this interface.
    const ::mlir::LLVM::OneToOneIntrinsicOpInterface::Concept *implOneToOneIntrinsicOpInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implOneToOneIntrinsicOpInterface = interfaceMap.lookup<::mlir::LLVM::OneToOneIntrinsicOpInterface>();
      assert(implOneToOneIntrinsicOpInterface && "`::mlir::amx::AMXIntrinsicOp` expected its base interface `::mlir::LLVM::OneToOneIntrinsicOpInterface` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::amx::AMXIntrinsicOp;
    Model() : Concept{} {}

  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::amx::AMXIntrinsicOp;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct AMXIntrinsicOpTrait;

} // namespace detail
class AMXIntrinsicOp : public ::mlir::OpInterface<AMXIntrinsicOp, detail::AMXIntrinsicOpInterfaceTraits> {
public:
  using ::mlir::OpInterface<AMXIntrinsicOp, detail::AMXIntrinsicOpInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::AMXIntrinsicOpTrait<ConcreteOp> {};
  //===----------------------------------------------------------------===//
  // Inherited from ::mlir::LLVM::OneToOneIntrinsicOpInterface
  //===----------------------------------------------------------------===//

  operator ::mlir::LLVM::OneToOneIntrinsicOpInterface () const {
    if (!*this) return nullptr;
    return ::mlir::LLVM::OneToOneIntrinsicOpInterface(*this, getImpl()->implOneToOneIntrinsicOpInterface);
  }


  /// Returns mangled LLVM intrinsic function name matching the operation
  /// variant.
  std::string getIntrinsicName();

  /// Returns operands for a corresponding LLVM intrinsic.
  /// 
  /// Additional operations may be created to facilitate mapping
  /// between the source operands and the target intrinsic.
  SmallVector<Value> getIntrinsicOperands(::mlir::ArrayRef<Value> operands, const ::mlir::LLVMTypeConverter & typeConverter, ::mlir::RewriterBase & rewriter);
};

} // namespace mlir::amx
namespace mlir::amx::detail {

  template <typename ConcreteOp>
  struct AMXIntrinsicOpTrait : public ::mlir::OpInterface<AMXIntrinsicOp, detail::AMXIntrinsicOpInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::amx::detail
namespace mlir::amx {


} // namespace mlir::amx
