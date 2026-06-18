/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::x86vector {

/// A wrapper interface for operations representing x86 LLVM intrinsics.
class X86IntrinsicOp;

} // namespace mlir::x86vector
namespace mlir::x86vector {

/// A wrapper interface for operations representing x86 LLVM intrinsics.
namespace detail {
struct X86IntrinsicOpInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    /// The base classes of this interface.
    const ::mlir::LLVM::OneToOneIntrinsicOpInterface::Concept *implOneToOneIntrinsicOpInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implOneToOneIntrinsicOpInterface = interfaceMap.lookup<::mlir::LLVM::OneToOneIntrinsicOpInterface>();
      assert(implOneToOneIntrinsicOpInterface && "`::mlir::x86vector::X86IntrinsicOp` expected its base interface `::mlir::LLVM::OneToOneIntrinsicOpInterface` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::x86vector::X86IntrinsicOp;
    Model() : Concept{} {}

  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::x86vector::X86IntrinsicOp;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct X86IntrinsicOpTrait;

} // namespace detail
class X86IntrinsicOp : public ::mlir::OpInterface<X86IntrinsicOp, detail::X86IntrinsicOpInterfaceTraits> {
public:
  using ::mlir::OpInterface<X86IntrinsicOp, detail::X86IntrinsicOpInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::X86IntrinsicOpTrait<ConcreteOp> {};
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

} // namespace mlir::x86vector
namespace mlir::x86vector::detail {

  template <typename ConcreteOp>
  struct X86IntrinsicOpTrait : public ::mlir::OpInterface<X86IntrinsicOp, detail::X86IntrinsicOpInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace mlir::x86vector::detail
namespace mlir::x86vector {


} // namespace mlir::x86vector
