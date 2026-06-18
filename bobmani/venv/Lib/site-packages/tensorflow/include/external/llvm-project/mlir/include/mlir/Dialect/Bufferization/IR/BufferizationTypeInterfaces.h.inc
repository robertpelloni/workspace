/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::bufferization {

/// Indicates that this type is a tensor type (similarly to a MLIR builtin
///     tensor) for bufferization purposes.
class TensorLikeType;

} // namespace mlir::bufferization
namespace mlir::bufferization {

/// Indicates that this type is a buffer type (similarly to a MLIR builtin
///     memref) for bufferization purposes.
/// 
///     The interface currently has no methods as it is used by types to opt into
///     being supported by the bufferization procedures.
class BufferLikeType;

} // namespace mlir::bufferization
namespace mlir::bufferization {

/// Indicates that this type is a tensor type (similarly to a MLIR builtin
///     tensor) for bufferization purposes.
namespace detail {
struct TensorLikeTypeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::FailureOr<::mlir::bufferization::BufferLikeType> (*getBufferType)(const Concept *impl, ::mlir::Type , const ::mlir::bufferization::BufferizationOptions &, ::llvm::function_ref<::mlir::InFlightDiagnostic()>);
    ::mlir::LogicalResult (*verifyCompatibleBufferType)(const Concept *impl, ::mlir::Type , ::mlir::bufferization::BufferLikeType, ::llvm::function_ref<::mlir::InFlightDiagnostic()>);
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::bufferization::TensorLikeType;
    Model() : Concept{getBufferType, verifyCompatibleBufferType} {}

    static inline ::mlir::FailureOr<::mlir::bufferization::BufferLikeType> getBufferType(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::bufferization::BufferizationOptions & options, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline ::mlir::LogicalResult verifyCompatibleBufferType(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::bufferization::BufferLikeType bufferType, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::bufferization::TensorLikeType;
    FallbackModel() : Concept{getBufferType, verifyCompatibleBufferType} {}

    static inline ::mlir::FailureOr<::mlir::bufferization::BufferLikeType> getBufferType(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::bufferization::BufferizationOptions & options, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
    static inline ::mlir::LogicalResult verifyCompatibleBufferType(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::bufferization::BufferLikeType bufferType, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct TensorLikeTypeTrait;

} // namespace detail
class TensorLikeType : public ::mlir::TypeInterface<TensorLikeType, detail::TensorLikeTypeInterfaceTraits> {
public:
  using ::mlir::TypeInterface<TensorLikeType, detail::TensorLikeTypeInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::TensorLikeTypeTrait<ConcreteType> {};

  /// Returns a BufferLike type for this TensorLike type.
  ::mlir::FailureOr<::mlir::bufferization::BufferLikeType> getBufferType(const ::mlir::bufferization::BufferizationOptions & options, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;

  /// Returns whether a BufferLike type is compatible to this TensorLike type.
  /// The BufferLike type is assumed to be created by getBufferType().
  ::mlir::LogicalResult verifyCompatibleBufferType(::mlir::bufferization::BufferLikeType bufferType, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
};

} // namespace mlir::bufferization
namespace mlir::bufferization {

/// Indicates that this type is a buffer type (similarly to a MLIR builtin
///     memref) for bufferization purposes.
/// 
///     The interface currently has no methods as it is used by types to opt into
///     being supported by the bufferization procedures.
namespace detail {
struct BufferLikeTypeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::bufferization::BufferLikeType;
    Model() : Concept{} {}

  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::bufferization::BufferLikeType;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct BufferLikeTypeTrait;

} // namespace detail
class BufferLikeType : public ::mlir::TypeInterface<BufferLikeType, detail::BufferLikeTypeInterfaceTraits> {
public:
  using ::mlir::TypeInterface<BufferLikeType, detail::BufferLikeTypeInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::BufferLikeTypeTrait<ConcreteType> {};
};

} // namespace mlir::bufferization
namespace mlir::bufferization::detail {

  template <typename ConcreteType>
  struct TensorLikeTypeTrait : public ::mlir::TypeInterface<TensorLikeType, detail::TensorLikeTypeInterfaceTraits>::Trait<ConcreteType> {
  };

} // namespace mlir::bufferization::detail
namespace mlir::bufferization::detail {

  template <typename ConcreteType>
  struct BufferLikeTypeTrait : public ::mlir::TypeInterface<BufferLikeType, detail::BufferLikeTypeInterfaceTraits>::Trait<ConcreteType> {
  };

} // namespace mlir::bufferization::detail
namespace mlir::bufferization {

template<typename ConcreteType>
::mlir::FailureOr<::mlir::bufferization::BufferLikeType> detail::TensorLikeTypeInterfaceTraits::Model<ConcreteType>::getBufferType(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::bufferization::BufferizationOptions & options, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getBufferType(options, emitError);
}
template<typename ConcreteType>
::mlir::LogicalResult detail::TensorLikeTypeInterfaceTraits::Model<ConcreteType>::verifyCompatibleBufferType(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::bufferization::BufferLikeType bufferType, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).verifyCompatibleBufferType(bufferType, emitError);
}
template<typename ConcreteType>
::mlir::FailureOr<::mlir::bufferization::BufferLikeType> detail::TensorLikeTypeInterfaceTraits::FallbackModel<ConcreteType>::getBufferType(const Concept *impl, ::mlir::Type tablegen_opaque_val, const ::mlir::bufferization::BufferizationOptions & options, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return static_cast<const ConcreteType *>(impl)->getBufferType(tablegen_opaque_val, options, emitError);
}
template<typename ConcreteType>
::mlir::LogicalResult detail::TensorLikeTypeInterfaceTraits::FallbackModel<ConcreteType>::verifyCompatibleBufferType(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::bufferization::BufferLikeType bufferType, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return static_cast<const ConcreteType *>(impl)->verifyCompatibleBufferType(tablegen_opaque_val, bufferType, emitError);
}

} // namespace mlir::bufferization
namespace mlir::bufferization {


} // namespace mlir::bufferization
