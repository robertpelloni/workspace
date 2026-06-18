/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::hlo {

/// This interface is used for attributes that carry bounds for dimension sizes
///     of an accompanying shaped type, e.g. when the attribute represents a
///     RankedTensorType::getEncoding.
///     The number of bounds is expected to be the same as the number of dimensions
///     in the accompanying shaped type.
///     For a static dimension, the corresponding bound is ShapedType::kDynamic.
///     For a dynamic dimension, the corresponding bound is either known and is
///     a non-negative number or unknown and is ShapedType::kDynamic.
class BoundedAttrInterface;

} // namespace mlir::hlo
namespace mlir::hlo {

/// This interface is used for attributes that carry bounds for dimension sizes
///     of an accompanying shaped type, e.g. when the attribute represents a
///     RankedTensorType::getEncoding.
///     The number of bounds is expected to be the same as the number of dimensions
///     in the accompanying shaped type.
///     For a static dimension, the corresponding bound is ShapedType::kDynamic.
///     For a dynamic dimension, the corresponding bound is either known and is
///     a non-negative number or unknown and is ShapedType::kDynamic.
namespace detail {
struct BoundedAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::ArrayRef<int64_t> (*getBounds)(const Concept *impl, ::mlir::Attribute );
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::mlir::hlo::BoundedAttrInterface;
    Model() : Concept{getBounds} {}

    static inline ::llvm::ArrayRef<int64_t> getBounds(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::hlo::BoundedAttrInterface;
    FallbackModel() : Concept{getBounds} {}

    static inline ::llvm::ArrayRef<int64_t> getBounds(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct BoundedAttrInterfaceTrait;

} // namespace detail
class BoundedAttrInterface : public ::mlir::AttributeInterface<BoundedAttrInterface, detail::BoundedAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<BoundedAttrInterface, detail::BoundedAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::BoundedAttrInterfaceTrait<ConcreteAttr> {};

  /// Get the attribute's bounds
  ::llvm::ArrayRef<int64_t> getBounds() const;
};

} // namespace mlir::hlo
namespace mlir::hlo::detail {

  template <typename ConcreteAttr>
  struct BoundedAttrInterfaceTrait : public ::mlir::AttributeInterface<BoundedAttrInterface, detail::BoundedAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace mlir::hlo::detail
namespace mlir::hlo {

template<typename ConcreteAttr>
::llvm::ArrayRef<int64_t> detail::BoundedAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getBounds(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getBounds();
}
template<typename ConcreteAttr>
::llvm::ArrayRef<int64_t> detail::BoundedAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getBounds(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getBounds(tablegen_opaque_val);
}

} // namespace mlir::hlo
