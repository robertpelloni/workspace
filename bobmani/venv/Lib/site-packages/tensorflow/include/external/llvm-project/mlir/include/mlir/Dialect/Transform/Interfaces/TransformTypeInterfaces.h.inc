/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::transform {

/// Types that can be used for the Transform dialect operation handle values.
///     Such types define the properties of Payload IR operations associated with
///     the handle. A user of such a handle can assume that these properties have
///     been verified for any Payload IR operation associated with it.
class TransformHandleTypeInterface;

} // namespace mlir::transform
namespace mlir::transform {

/// Types that can be used for the Transform dialect parameter values. Such types
///     define the structure of the parameters associated with the value, e.g., their
///     underlying type. A user of the value can assume that the parameter has been
///     verified.
class TransformParamTypeInterface;

} // namespace mlir::transform
namespace mlir::transform {

/// Types that can be used for the Transform dialect handle values pointing to
///     Payload IR values. Such types define the properties of Payload IR values
///     associated with the handle. Users of such a handle can assume that these
///     properties have been verified for any Payload IR value associated with it.
class TransformValueHandleTypeInterface;

} // namespace mlir::transform
namespace mlir::transform {

/// Types that can be used for the Transform dialect operation handle values.
///     Such types define the properties of Payload IR operations associated with
///     the handle. A user of such a handle can assume that these properties have
///     been verified for any Payload IR operation associated with it.
namespace detail {
struct TransformHandleTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::DiagnosedSilenceableFailure (*checkPayload)(const Concept *impl, ::mlir::Type , ::mlir::Location, ::mlir::ArrayRef<::mlir::Operation *>);
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::transform::TransformHandleTypeInterface;
    Model() : Concept{checkPayload} {}

    static inline ::mlir::DiagnosedSilenceableFailure checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Operation *> payload);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::transform::TransformHandleTypeInterface;
    FallbackModel() : Concept{checkPayload} {}

    static inline ::mlir::DiagnosedSilenceableFailure checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Operation *> payload);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct TransformHandleTypeInterfaceTrait;

} // namespace detail
class TransformHandleTypeInterface : public ::mlir::TypeInterface<TransformHandleTypeInterface, detail::TransformHandleTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<TransformHandleTypeInterface, detail::TransformHandleTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::TransformHandleTypeInterfaceTrait<ConcreteType> {};

  /// Checks if the given associated objects (Payload IR operations or attributes)
  /// satisfy the conditions defined by this type. If not, produces a silenceable
  /// error at the specified location.
  ::mlir::DiagnosedSilenceableFailure checkPayload(::mlir::Location loc, ::mlir::ArrayRef<::mlir::Operation *> payload) const;

    DiagnosedSilenceableFailure emitSilenceableError(Location loc) const {
      Diagnostic diag(loc, DiagnosticSeverity::Error);
      return DiagnosedSilenceableFailure::silenceableFailure(std::move(diag));
    }
};

} // namespace mlir::transform
namespace mlir::transform {

/// Types that can be used for the Transform dialect parameter values. Such types
///     define the structure of the parameters associated with the value, e.g., their
///     underlying type. A user of the value can assume that the parameter has been
///     verified.
namespace detail {
struct TransformParamTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::DiagnosedSilenceableFailure (*checkPayload)(const Concept *impl, ::mlir::Type , ::mlir::Location, ::mlir::ArrayRef<::mlir::Attribute>);
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::transform::TransformParamTypeInterface;
    Model() : Concept{checkPayload} {}

    static inline ::mlir::DiagnosedSilenceableFailure checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Attribute> payload);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::transform::TransformParamTypeInterface;
    FallbackModel() : Concept{checkPayload} {}

    static inline ::mlir::DiagnosedSilenceableFailure checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Attribute> payload);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct TransformParamTypeInterfaceTrait;

} // namespace detail
class TransformParamTypeInterface : public ::mlir::TypeInterface<TransformParamTypeInterface, detail::TransformParamTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<TransformParamTypeInterface, detail::TransformParamTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::TransformParamTypeInterfaceTrait<ConcreteType> {};

  /// Checks if the given associated objects (Payload IR operations or attributes)
  /// satisfy the conditions defined by this type. If not, produces a silenceable
  /// error at the specified location.
  ::mlir::DiagnosedSilenceableFailure checkPayload(::mlir::Location loc, ::mlir::ArrayRef<::mlir::Attribute> payload) const;

    DiagnosedSilenceableFailure emitSilenceableError(Location loc) const {
      Diagnostic diag(loc, DiagnosticSeverity::Error);
      return DiagnosedSilenceableFailure::silenceableFailure(std::move(diag));
    }
};

} // namespace mlir::transform
namespace mlir::transform {

/// Types that can be used for the Transform dialect handle values pointing to
///     Payload IR values. Such types define the properties of Payload IR values
///     associated with the handle. Users of such a handle can assume that these
///     properties have been verified for any Payload IR value associated with it.
namespace detail {
struct TransformValueHandleTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::DiagnosedSilenceableFailure (*checkPayload)(const Concept *impl, ::mlir::Type , ::mlir::Location, ::mlir::ArrayRef<::mlir::Value>);
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::transform::TransformValueHandleTypeInterface;
    Model() : Concept{checkPayload} {}

    static inline ::mlir::DiagnosedSilenceableFailure checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Value> payload);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::transform::TransformValueHandleTypeInterface;
    FallbackModel() : Concept{checkPayload} {}

    static inline ::mlir::DiagnosedSilenceableFailure checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Value> payload);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct TransformValueHandleTypeInterfaceTrait;

} // namespace detail
class TransformValueHandleTypeInterface : public ::mlir::TypeInterface<TransformValueHandleTypeInterface, detail::TransformValueHandleTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<TransformValueHandleTypeInterface, detail::TransformValueHandleTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::TransformValueHandleTypeInterfaceTrait<ConcreteType> {};

  /// Checks if the given associated objects (Payload IR operations or attributes)
  /// satisfy the conditions defined by this type. If not, produces a silenceable
  /// error at the specified location.
  ::mlir::DiagnosedSilenceableFailure checkPayload(::mlir::Location loc, ::mlir::ArrayRef<::mlir::Value> payload) const;

    DiagnosedSilenceableFailure emitSilenceableError(Location loc) const {
      Diagnostic diag(loc, DiagnosticSeverity::Error);
      return DiagnosedSilenceableFailure::silenceableFailure(std::move(diag));
    }
};

} // namespace mlir::transform
namespace mlir::transform::detail {

  template <typename ConcreteType>
  struct TransformHandleTypeInterfaceTrait : public ::mlir::TypeInterface<TransformHandleTypeInterface, detail::TransformHandleTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {

    DiagnosedSilenceableFailure emitSilenceableError(Location loc) const {
      Diagnostic diag(loc, DiagnosticSeverity::Error);
      return DiagnosedSilenceableFailure::silenceableFailure(std::move(diag));
    }
  
  };

} // namespace mlir::transform::detail
namespace mlir::transform::detail {

  template <typename ConcreteType>
  struct TransformParamTypeInterfaceTrait : public ::mlir::TypeInterface<TransformParamTypeInterface, detail::TransformParamTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {

    DiagnosedSilenceableFailure emitSilenceableError(Location loc) const {
      Diagnostic diag(loc, DiagnosticSeverity::Error);
      return DiagnosedSilenceableFailure::silenceableFailure(std::move(diag));
    }
  
  };

} // namespace mlir::transform::detail
namespace mlir::transform::detail {

  template <typename ConcreteType>
  struct TransformValueHandleTypeInterfaceTrait : public ::mlir::TypeInterface<TransformValueHandleTypeInterface, detail::TransformValueHandleTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {

    DiagnosedSilenceableFailure emitSilenceableError(Location loc) const {
      Diagnostic diag(loc, DiagnosticSeverity::Error);
      return DiagnosedSilenceableFailure::silenceableFailure(std::move(diag));
    }
  
  };

} // namespace mlir::transform::detail
namespace mlir::transform {

template<typename ConcreteType>
::mlir::DiagnosedSilenceableFailure detail::TransformHandleTypeInterfaceInterfaceTraits::Model<ConcreteType>::checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Operation *> payload) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).checkPayload(loc, payload);
}
template<typename ConcreteType>
::mlir::DiagnosedSilenceableFailure detail::TransformHandleTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Operation *> payload) {
  return static_cast<const ConcreteType *>(impl)->checkPayload(tablegen_opaque_val, loc, payload);
}

} // namespace mlir::transform
namespace mlir::transform {

template<typename ConcreteType>
::mlir::DiagnosedSilenceableFailure detail::TransformParamTypeInterfaceInterfaceTraits::Model<ConcreteType>::checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Attribute> payload) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).checkPayload(loc, payload);
}
template<typename ConcreteType>
::mlir::DiagnosedSilenceableFailure detail::TransformParamTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Attribute> payload) {
  return static_cast<const ConcreteType *>(impl)->checkPayload(tablegen_opaque_val, loc, payload);
}

} // namespace mlir::transform
namespace mlir::transform {

template<typename ConcreteType>
::mlir::DiagnosedSilenceableFailure detail::TransformValueHandleTypeInterfaceInterfaceTraits::Model<ConcreteType>::checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Value> payload) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).checkPayload(loc, payload);
}
template<typename ConcreteType>
::mlir::DiagnosedSilenceableFailure detail::TransformValueHandleTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::checkPayload(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Location loc, ::mlir::ArrayRef<::mlir::Value> payload) {
  return static_cast<const ConcreteType *>(impl)->checkPayload(tablegen_opaque_val, loc, payload);
}

} // namespace mlir::transform
