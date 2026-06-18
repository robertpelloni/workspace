/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {

/// Implementing this interface establishes a contract between this type and the
///     vector type, indicating that this type can be used as element of vectors.
/// 
///     Vector element types are treated as a bag of bits without any assumed
///     structure. The size of an element type must be a compile-time constant.
///     However, the bit-width may remain opaque or unavailable during
///     transformations that do not depend on the element type.
/// 
///     Note: This type interface is still evolving. It currently has no methods
///     and is just used as marker to allow types to opt into being vector elements.
///     This may change in the future, for example, to require types to provide
///     their size or alignment given a data layout. Please post an RFC before
///     adding this interface to additional types. Implementing this interface on
///     downstream types is discouraged, until we specified the exact properties of
///     a vector element type in more detail.
class VectorElementTypeInterface;

} // namespace mlir
namespace mlir {

/// This type interface should be implemented by all floating-point types. It
///     defines the LLVM APFloat semantics and provides a few helper functions.
class FloatType;

} // namespace mlir
namespace mlir {

/// Indication that this type can be used as element in memref types.
/// 
///     Implementing this interface establishes a contract between this type and the
///     memref type indicating that this type can be used as element of ranked or
///     unranked memrefs. The type is expected to:
/// 
///       - model an entity stored in memory;
///       - have non-zero size.
/// 
///     For example, scalar values such as integers can implement this interface,
///     but indicator types such as `void` or `unit` should not.
/// 
///     The interface currently has no methods and is used by types to opt into
///     being memref elements. This may change in the future, in particular to
///     require types to provide their size or alignment given a data layout.
class MemRefElementTypeInterface;

} // namespace mlir
namespace mlir {

/// A ptr-like type represents an object storing a memory address. This object
///     is constituted by:
///     - A memory address called the base pointer. This pointer is treated as a
///       bag of bits without any assumed structure. The bit-width of the base
///       pointer must be a compile-time constant. However, the bit-width may remain
///       opaque or unavailable during transformations that do not depend on the
///       base pointer. Finally, it is considered indivisible in the sense that as
///       a `PtrLikeTypeInterface` value, it has no metadata.
///     - Optional metadata about the pointer. For example, the size of the  memory
///       region associated with the pointer.
/// 
///     Furthermore, all ptr-like types have two properties:
///     - The memory space associated with the address held by the pointer.
///     - An optional element type. If the element type is not specified, the
///       pointer is considered opaque.
class PtrLikeTypeInterface;

} // namespace mlir
namespace mlir {

/// This interface provides a common API for interacting with multi-dimensional
///     container types. These types contain a shape and an element type.
/// 
///     A shape is a list of sizes corresponding to the dimensions of the container.
///     If the number of dimensions in the shape is unknown, the shape is "unranked".
///     If the number of dimensions is known, the shape "ranked". The sizes of the
///     dimensions of the shape must be positive, or kDynamic (in which case the
///     size of the dimension is dynamic, or not statically known).
class ShapedType;

} // namespace mlir
namespace mlir {

/// Implementing this interface establishes a contract between this type and the
///     vector type, indicating that this type can be used as element of vectors.
/// 
///     Vector element types are treated as a bag of bits without any assumed
///     structure. The size of an element type must be a compile-time constant.
///     However, the bit-width may remain opaque or unavailable during
///     transformations that do not depend on the element type.
/// 
///     Note: This type interface is still evolving. It currently has no methods
///     and is just used as marker to allow types to opt into being vector elements.
///     This may change in the future, for example, to require types to provide
///     their size or alignment given a data layout. Please post an RFC before
///     adding this interface to additional types. Implementing this interface on
///     downstream types is discouraged, until we specified the exact properties of
///     a vector element type in more detail.
namespace detail {
struct VectorElementTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::VectorElementTypeInterface;
    Model() : Concept{} {}

  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::VectorElementTypeInterface;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct VectorElementTypeInterfaceTrait;

} // namespace detail
class VectorElementTypeInterface : public ::mlir::TypeInterface<VectorElementTypeInterface, detail::VectorElementTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<VectorElementTypeInterface, detail::VectorElementTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::VectorElementTypeInterfaceTrait<ConcreteType> {};
};

} // namespace mlir
namespace mlir {

/// This type interface should be implemented by all floating-point types. It
///     defines the LLVM APFloat semantics and provides a few helper functions.
namespace detail {
struct FloatTypeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    const ::llvm::fltSemantics &(*getFloatSemantics)(const Concept *impl, ::mlir::Type );
    ::mlir::FloatType (*scaleElementBitwidth)(const Concept *impl, ::mlir::Type , unsigned);
    /// The base classes of this interface.
    const ::mlir::VectorElementTypeInterface::Concept *implVectorElementTypeInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implVectorElementTypeInterface = interfaceMap.lookup<::mlir::VectorElementTypeInterface>();
      assert(implVectorElementTypeInterface && "`::mlir::FloatType` expected its base interface `::mlir::VectorElementTypeInterface` to be registered");
    }
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::FloatType;
    Model() : Concept{getFloatSemantics, scaleElementBitwidth} {}

    static inline const ::llvm::fltSemantics &getFloatSemantics(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline ::mlir::FloatType scaleElementBitwidth(const Concept *impl, ::mlir::Type tablegen_opaque_val, unsigned scale);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::FloatType;
    FallbackModel() : Concept{getFloatSemantics, scaleElementBitwidth} {}

    static inline const ::llvm::fltSemantics &getFloatSemantics(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline ::mlir::FloatType scaleElementBitwidth(const Concept *impl, ::mlir::Type tablegen_opaque_val, unsigned scale);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
    ::mlir::FloatType scaleElementBitwidth(::mlir::Type tablegen_opaque_val, unsigned scale) const;
  };
};
template <typename ConcreteType>
struct FloatTypeTrait;

} // namespace detail
class FloatType : public ::mlir::TypeInterface<FloatType, detail::FloatTypeInterfaceTraits> {
public:
  using ::mlir::TypeInterface<FloatType, detail::FloatTypeInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::FloatTypeTrait<ConcreteType> {};

  /// Returns the APFloat semantics for this floating-point type.
  const ::llvm::fltSemantics &getFloatSemantics() const;

  /// Returns a float type with bitwidth scaled by `scale`. Returns a "null"
  /// float type if the scaled element type cannot be represented.
  ::mlir::FloatType scaleElementBitwidth(unsigned scale) const;

    /// Return the bitwidth of this float type.
    unsigned getWidth();

    /// Return the width of the mantissa of this type.
    /// The width includes the integer bit.
    unsigned getFPMantissaWidth();
  //===----------------------------------------------------------------===//
  // Inherited from ::mlir::VectorElementTypeInterface
  //===----------------------------------------------------------------===//

  operator ::mlir::VectorElementTypeInterface () const {
    if (!*this) return nullptr;
    return ::mlir::VectorElementTypeInterface(*this, getImpl()->implVectorElementTypeInterface);
  }

};

} // namespace mlir
namespace mlir {

/// Indication that this type can be used as element in memref types.
/// 
///     Implementing this interface establishes a contract between this type and the
///     memref type indicating that this type can be used as element of ranked or
///     unranked memrefs. The type is expected to:
/// 
///       - model an entity stored in memory;
///       - have non-zero size.
/// 
///     For example, scalar values such as integers can implement this interface,
///     but indicator types such as `void` or `unit` should not.
/// 
///     The interface currently has no methods and is used by types to opt into
///     being memref elements. This may change in the future, in particular to
///     require types to provide their size or alignment given a data layout.
namespace detail {
struct MemRefElementTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::MemRefElementTypeInterface;
    Model() : Concept{} {}

  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::MemRefElementTypeInterface;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct MemRefElementTypeInterfaceTrait;

} // namespace detail
class MemRefElementTypeInterface : public ::mlir::TypeInterface<MemRefElementTypeInterface, detail::MemRefElementTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<MemRefElementTypeInterface, detail::MemRefElementTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::MemRefElementTypeInterfaceTrait<ConcreteType> {};
};

} // namespace mlir
namespace mlir {

/// A ptr-like type represents an object storing a memory address. This object
///     is constituted by:
///     - A memory address called the base pointer. This pointer is treated as a
///       bag of bits without any assumed structure. The bit-width of the base
///       pointer must be a compile-time constant. However, the bit-width may remain
///       opaque or unavailable during transformations that do not depend on the
///       base pointer. Finally, it is considered indivisible in the sense that as
///       a `PtrLikeTypeInterface` value, it has no metadata.
///     - Optional metadata about the pointer. For example, the size of the  memory
///       region associated with the pointer.
/// 
///     Furthermore, all ptr-like types have two properties:
///     - The memory space associated with the address held by the pointer.
///     - An optional element type. If the element type is not specified, the
///       pointer is considered opaque.
namespace detail {
struct PtrLikeTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::Attribute (*getMemorySpace)(const Concept *impl, ::mlir::Type );
    ::mlir::Type (*getElementType)(const Concept *impl, ::mlir::Type );
    bool (*hasPtrMetadata)(const Concept *impl, ::mlir::Type );
    ::llvm::FailureOr<::mlir::PtrLikeTypeInterface> (*clonePtrWith)(const Concept *impl, ::mlir::Type , ::mlir::Attribute, ::std::optional<::mlir::Type>);
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::PtrLikeTypeInterface;
    Model() : Concept{getMemorySpace, getElementType, hasPtrMetadata, clonePtrWith} {}

    static inline ::mlir::Attribute getMemorySpace(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline ::mlir::Type getElementType(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline bool hasPtrMetadata(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline ::llvm::FailureOr<::mlir::PtrLikeTypeInterface> clonePtrWith(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Attribute memorySpace, ::std::optional<::mlir::Type> elementType);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::PtrLikeTypeInterface;
    FallbackModel() : Concept{getMemorySpace, getElementType, hasPtrMetadata, clonePtrWith} {}

    static inline ::mlir::Attribute getMemorySpace(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline ::mlir::Type getElementType(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline bool hasPtrMetadata(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline ::llvm::FailureOr<::mlir::PtrLikeTypeInterface> clonePtrWith(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Attribute memorySpace, ::std::optional<::mlir::Type> elementType);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct PtrLikeTypeInterfaceTrait;

} // namespace detail
class PtrLikeTypeInterface : public ::mlir::TypeInterface<PtrLikeTypeInterface, detail::PtrLikeTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<PtrLikeTypeInterface, detail::PtrLikeTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::PtrLikeTypeInterfaceTrait<ConcreteType> {};

  /// Returns the memory space of this ptr-like type.
  ::mlir::Attribute getMemorySpace() const;

  /// Returns the element type of this ptr-like type. Note: this method can
  /// return `::mlir::Type()`, in which case the pointer is considered opaque.
  ::mlir::Type getElementType() const;

  /// Returns whether this ptr-like type has non-empty metadata.
  bool hasPtrMetadata() const;

  /// Returns a clone of this type with the given memory space and element type,
  /// or `failure` if the type cannot be cloned with the specified arguments.
  /// If the pointer is opaque and `elementType` is not `std::nullopt` the
  /// method will return `failure`.
  /// 
  /// If no `elementType` is provided and ptr is not opaque, the `elementType`
  /// of this type is used.
  ::llvm::FailureOr<::mlir::PtrLikeTypeInterface> clonePtrWith(::mlir::Attribute memorySpace, ::std::optional<::mlir::Type> elementType) const;
};

} // namespace mlir
namespace mlir {

/// This interface provides a common API for interacting with multi-dimensional
///     container types. These types contain a shape and an element type.
/// 
///     A shape is a list of sizes corresponding to the dimensions of the container.
///     If the number of dimensions in the shape is unknown, the shape is "unranked".
///     If the number of dimensions is known, the shape "ranked". The sizes of the
///     dimensions of the shape must be positive, or kDynamic (in which case the
///     size of the dimension is dynamic, or not statically known).
namespace detail {
struct ShapedTypeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::ShapedType (*cloneWith)(const Concept *impl, ::mlir::Type , ::std::optional<::llvm::ArrayRef<int64_t>>, ::mlir::Type);
    ::mlir::Type (*getElementType)(const Concept *impl, ::mlir::Type );
    bool (*hasRank)(const Concept *impl, ::mlir::Type );
    ::llvm::ArrayRef<int64_t> (*getShape)(const Concept *impl, ::mlir::Type );
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::mlir::ShapedType;
    Model() : Concept{cloneWith, getElementType, hasRank, getShape} {}

    static inline ::mlir::ShapedType cloneWith(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::std::optional<::llvm::ArrayRef<int64_t>> shape, ::mlir::Type elementType);
    static inline ::mlir::Type getElementType(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline bool hasRank(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline ::llvm::ArrayRef<int64_t> getShape(const Concept *impl, ::mlir::Type tablegen_opaque_val);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::ShapedType;
    FallbackModel() : Concept{cloneWith, getElementType, hasRank, getShape} {}

    static inline ::mlir::ShapedType cloneWith(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::std::optional<::llvm::ArrayRef<int64_t>> shape, ::mlir::Type elementType);
    static inline ::mlir::Type getElementType(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline bool hasRank(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline ::llvm::ArrayRef<int64_t> getShape(const Concept *impl, ::mlir::Type tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct ShapedTypeTrait;

} // namespace detail
class ShapedType : public ::mlir::TypeInterface<ShapedType, detail::ShapedTypeInterfaceTraits> {
public:
  using ::mlir::TypeInterface<ShapedType, detail::ShapedTypeInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::ShapedTypeTrait<ConcreteType> {};

  /// Returns a clone of this type with the given shape and element type.
  /// 
  /// If no shape is provided, the shape of this type is used. In that case, if
  /// this type is unranked, so is the resulting type.
  /// 
  /// If a shape is provided, the resulting type is always ranked, even if this
  /// type is unranked.
  ::mlir::ShapedType cloneWith(::std::optional<::llvm::ArrayRef<int64_t>> shape, ::mlir::Type elementType) const;

  /// Returns the element type of this shaped type.
  ::mlir::Type getElementType() const;

  /// Returns if this type is ranked, i.e. it has a known number of dimensions.
  bool hasRank() const;

  /// Returns the shape of this type if it is ranked, otherwise asserts.
  ::llvm::ArrayRef<int64_t> getShape() const;

    static constexpr int64_t kDynamic =
        std::numeric_limits<int64_t>::min();

    /// Whether the given dimension size indicates a dynamic dimension.
    static constexpr bool isDynamic(int64_t dValue) {
      return dValue == kDynamic;
    }

    /// Whether the given shape has any size that indicates a dynamic dimension.
    static bool isDynamicShape(ArrayRef<int64_t> dSizes) {
      return llvm::any_of(dSizes, isDynamic);
    }

    /// Whether the given dimension size indicates a statically-sized dimension.
    static constexpr bool isStatic(int64_t dValue) {
      return dValue != kDynamic;
    }

    /// Whether the given shape has static dimensions only.
    static bool isStaticShape(ArrayRef<int64_t> dSizes) {
      return llvm::all_of(dSizes, isStatic);
    }

    /// Return the number of elements present in the given shape.
    static int64_t getNumElements(ArrayRef<int64_t> shape);

    /// Return a clone of this type with the given new shape and element type.
    /// The returned type is ranked, even if this type is unranked.
    auto clone(::llvm::ArrayRef<int64_t> shape, Type elementType) {
      return cloneWith(shape, elementType);
    }

    /// Return a clone of this type with the given new shape. The returned type
    /// is ranked, even if this type is unranked.
    auto clone(::llvm::ArrayRef<int64_t> shape) {
      return cloneWith(shape, getElementType());
    }

    /// Return a clone of this type with the given new element type. The
    /// returned type is ranked if and only if this type is ranked. In that
    /// case, the returned type has the same shape as this type.
    auto clone(::mlir::Type elementType) {
      return (*this).cloneWith(/*shape=*/std::nullopt, elementType);
    }

    /// If an element type is an integer or a float, return its width. Otherwise,
    /// abort.
    unsigned getElementTypeBitWidth() const {
      return (*this).getElementType().getIntOrFloatBitWidth();
    }

    /// If this is a ranked type, return the rank. Otherwise, abort.
    int64_t getRank() const {
      assert((*this).hasRank() && "cannot query rank of unranked shaped type");
      return (*this).getShape().size();
    }

    /// If it has static shape, return the number of elements. Otherwise, abort.
    int64_t getNumElements() const {
      assert(hasStaticShape() && "cannot get element count of dynamic shaped type");
      return ::mlir::ShapedType::getNumElements((*this).getShape());
    }

    /// Returns true if this dimension has a dynamic size (for ranked types);
    /// aborts for unranked types.
    bool isDynamicDim(unsigned idx) const {
      assert(idx < getRank() && "invalid index for shaped type");
      return ::mlir::ShapedType::isDynamic((*this).getShape()[idx]);
    }

    /// Returns true if this dimension has a static size (for ranked types);
    /// aborts for unranked types.
    bool isStaticDim(unsigned idx) const {
      assert(idx < getRank() && "invalid index for shaped type");
      return ::mlir::ShapedType::isStatic((*this).getShape()[idx]);
    }

    /// Returns if this type has a static shape, i.e. if the type is ranked and
    /// all dimensions have known size (>= 0).
    bool hasStaticShape() const {
      return (*this).hasRank() &&
             ::mlir::ShapedType::isStaticShape((*this).getShape());
    }

    /// Returns if this type has a static shape and the shape is equal to
    /// `shape` return true.
    bool hasStaticShape(::llvm::ArrayRef<int64_t> shape) const {
      return hasStaticShape() && (*this).getShape() == shape;
    }

    /// If this is a ranked type, return the number of dimensions with dynamic
    /// size. Otherwise, abort.
    size_t getNumDynamicDims() const {
      return llvm::count_if((*this).getShape(), ::mlir::ShapedType::isDynamic);
    }

    /// If this is ranked type, return the size of the specified dimension.
    /// Otherwise, abort.
    int64_t getDimSize(unsigned idx) const {
      assert(idx < getRank() && "invalid index for shaped type");
      return (*this).getShape()[idx];
    }

    /// Returns the position of the dynamic dimension relative to just the dynamic
    /// dimensions, given its `index` within the shape.
    unsigned getDynamicDimIndex(unsigned index) const {
      assert(index < getRank() && "invalid index");
      assert(::mlir::ShapedType::isDynamic(getDimSize(index)) && "invalid index");
      return llvm::count_if((*this).getShape().take_front(index),
                            ::mlir::ShapedType::isDynamic);
    }
};

} // namespace mlir
namespace mlir::detail {

  template <typename ConcreteType>
  struct VectorElementTypeInterfaceTrait : public ::mlir::TypeInterface<VectorElementTypeInterface, detail::VectorElementTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteType>
  struct FloatTypeTrait : public ::mlir::TypeInterface<FloatType, detail::FloatTypeInterfaceTraits>::Trait<ConcreteType> {

    /// Returns a float type with bitwidth scaled by `scale`. Returns a "null"
    /// float type if the scaled element type cannot be represented.
    ::mlir::FloatType scaleElementBitwidth(unsigned scale) const {
      return ::mlir::FloatType();
    }
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteType>
  struct MemRefElementTypeInterfaceTrait : public ::mlir::TypeInterface<MemRefElementTypeInterface, detail::MemRefElementTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteType>
  struct PtrLikeTypeInterfaceTrait : public ::mlir::TypeInterface<PtrLikeTypeInterface, detail::PtrLikeTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {
  };

} // namespace mlir::detail
namespace mlir::detail {

  template <typename ConcreteType>
  struct ShapedTypeTrait : public ::mlir::TypeInterface<ShapedType, detail::ShapedTypeInterfaceTraits>::Trait<ConcreteType> {

    /// Return a clone of this type with the given new element type. The
    /// returned type is ranked if and only if this type is ranked. In that
    /// case, the returned type has the same shape as this type.
    auto clone(::mlir::Type elementType) {
      return (*static_cast<const ConcreteType *>(this)).cloneWith(/*shape=*/std::nullopt, elementType);
    }

    /// If an element type is an integer or a float, return its width. Otherwise,
    /// abort.
    unsigned getElementTypeBitWidth() const {
      return (*static_cast<const ConcreteType *>(this)).getElementType().getIntOrFloatBitWidth();
    }

    /// If this is a ranked type, return the rank. Otherwise, abort.
    int64_t getRank() const {
      assert((*static_cast<const ConcreteType *>(this)).hasRank() && "cannot query rank of unranked shaped type");
      return (*static_cast<const ConcreteType *>(this)).getShape().size();
    }

    /// If it has static shape, return the number of elements. Otherwise, abort.
    int64_t getNumElements() const {
      assert(hasStaticShape() && "cannot get element count of dynamic shaped type");
      return ::mlir::ShapedType::getNumElements((*static_cast<const ConcreteType *>(this)).getShape());
    }

    /// Returns true if this dimension has a dynamic size (for ranked types);
    /// aborts for unranked types.
    bool isDynamicDim(unsigned idx) const {
      assert(idx < getRank() && "invalid index for shaped type");
      return ::mlir::ShapedType::isDynamic((*static_cast<const ConcreteType *>(this)).getShape()[idx]);
    }

    /// Returns true if this dimension has a static size (for ranked types);
    /// aborts for unranked types.
    bool isStaticDim(unsigned idx) const {
      assert(idx < getRank() && "invalid index for shaped type");
      return ::mlir::ShapedType::isStatic((*static_cast<const ConcreteType *>(this)).getShape()[idx]);
    }

    /// Returns if this type has a static shape, i.e. if the type is ranked and
    /// all dimensions have known size (>= 0).
    bool hasStaticShape() const {
      return (*static_cast<const ConcreteType *>(this)).hasRank() &&
             ::mlir::ShapedType::isStaticShape((*static_cast<const ConcreteType *>(this)).getShape());
    }

    /// Returns if this type has a static shape and the shape is equal to
    /// `shape` return true.
    bool hasStaticShape(::llvm::ArrayRef<int64_t> shape) const {
      return hasStaticShape() && (*static_cast<const ConcreteType *>(this)).getShape() == shape;
    }

    /// If this is a ranked type, return the number of dimensions with dynamic
    /// size. Otherwise, abort.
    size_t getNumDynamicDims() const {
      return llvm::count_if((*static_cast<const ConcreteType *>(this)).getShape(), ::mlir::ShapedType::isDynamic);
    }

    /// If this is ranked type, return the size of the specified dimension.
    /// Otherwise, abort.
    int64_t getDimSize(unsigned idx) const {
      assert(idx < getRank() && "invalid index for shaped type");
      return (*static_cast<const ConcreteType *>(this)).getShape()[idx];
    }

    /// Returns the position of the dynamic dimension relative to just the dynamic
    /// dimensions, given its `index` within the shape.
    unsigned getDynamicDimIndex(unsigned index) const {
      assert(index < getRank() && "invalid index");
      assert(::mlir::ShapedType::isDynamic(getDimSize(index)) && "invalid index");
      return llvm::count_if((*static_cast<const ConcreteType *>(this)).getShape().take_front(index),
                            ::mlir::ShapedType::isDynamic);
    }
  
  };

} // namespace mlir::detail
namespace mlir {


} // namespace mlir
namespace mlir {

template<typename ConcreteType>
const ::llvm::fltSemantics &detail::FloatTypeInterfaceTraits::Model<ConcreteType>::getFloatSemantics(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getFloatSemantics();
}
template<typename ConcreteType>
::mlir::FloatType detail::FloatTypeInterfaceTraits::Model<ConcreteType>::scaleElementBitwidth(const Concept *impl, ::mlir::Type tablegen_opaque_val, unsigned scale) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).scaleElementBitwidth(scale);
}
template<typename ConcreteType>
const ::llvm::fltSemantics &detail::FloatTypeInterfaceTraits::FallbackModel<ConcreteType>::getFloatSemantics(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return static_cast<const ConcreteType *>(impl)->getFloatSemantics(tablegen_opaque_val);
}
template<typename ConcreteType>
::mlir::FloatType detail::FloatTypeInterfaceTraits::FallbackModel<ConcreteType>::scaleElementBitwidth(const Concept *impl, ::mlir::Type tablegen_opaque_val, unsigned scale) {
  return static_cast<const ConcreteType *>(impl)->scaleElementBitwidth(tablegen_opaque_val, scale);
}
template<typename ConcreteModel, typename ConcreteType>
::mlir::FloatType detail::FloatTypeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteType>::scaleElementBitwidth(::mlir::Type tablegen_opaque_val, unsigned scale) const {
return ::mlir::FloatType();
}

} // namespace mlir
namespace mlir {


} // namespace mlir
namespace mlir {

template<typename ConcreteType>
::mlir::Attribute detail::PtrLikeTypeInterfaceInterfaceTraits::Model<ConcreteType>::getMemorySpace(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getMemorySpace();
}
template<typename ConcreteType>
::mlir::Type detail::PtrLikeTypeInterfaceInterfaceTraits::Model<ConcreteType>::getElementType(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getElementType();
}
template<typename ConcreteType>
bool detail::PtrLikeTypeInterfaceInterfaceTraits::Model<ConcreteType>::hasPtrMetadata(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).hasPtrMetadata();
}
template<typename ConcreteType>
::llvm::FailureOr<::mlir::PtrLikeTypeInterface> detail::PtrLikeTypeInterfaceInterfaceTraits::Model<ConcreteType>::clonePtrWith(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Attribute memorySpace, ::std::optional<::mlir::Type> elementType) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).clonePtrWith(memorySpace, elementType);
}
template<typename ConcreteType>
::mlir::Attribute detail::PtrLikeTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getMemorySpace(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return static_cast<const ConcreteType *>(impl)->getMemorySpace(tablegen_opaque_val);
}
template<typename ConcreteType>
::mlir::Type detail::PtrLikeTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getElementType(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return static_cast<const ConcreteType *>(impl)->getElementType(tablegen_opaque_val);
}
template<typename ConcreteType>
bool detail::PtrLikeTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::hasPtrMetadata(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return static_cast<const ConcreteType *>(impl)->hasPtrMetadata(tablegen_opaque_val);
}
template<typename ConcreteType>
::llvm::FailureOr<::mlir::PtrLikeTypeInterface> detail::PtrLikeTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::clonePtrWith(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::mlir::Attribute memorySpace, ::std::optional<::mlir::Type> elementType) {
  return static_cast<const ConcreteType *>(impl)->clonePtrWith(tablegen_opaque_val, memorySpace, elementType);
}

} // namespace mlir
namespace mlir {

template<typename ConcreteType>
::mlir::ShapedType detail::ShapedTypeInterfaceTraits::Model<ConcreteType>::cloneWith(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::std::optional<::llvm::ArrayRef<int64_t>> shape, ::mlir::Type elementType) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).cloneWith(shape, elementType);
}
template<typename ConcreteType>
::mlir::Type detail::ShapedTypeInterfaceTraits::Model<ConcreteType>::getElementType(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getElementType();
}
template<typename ConcreteType>
bool detail::ShapedTypeInterfaceTraits::Model<ConcreteType>::hasRank(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).hasRank();
}
template<typename ConcreteType>
::llvm::ArrayRef<int64_t> detail::ShapedTypeInterfaceTraits::Model<ConcreteType>::getShape(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getShape();
}
template<typename ConcreteType>
::mlir::ShapedType detail::ShapedTypeInterfaceTraits::FallbackModel<ConcreteType>::cloneWith(const Concept *impl, ::mlir::Type tablegen_opaque_val, ::std::optional<::llvm::ArrayRef<int64_t>> shape, ::mlir::Type elementType) {
  return static_cast<const ConcreteType *>(impl)->cloneWith(tablegen_opaque_val, shape, elementType);
}
template<typename ConcreteType>
::mlir::Type detail::ShapedTypeInterfaceTraits::FallbackModel<ConcreteType>::getElementType(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return static_cast<const ConcreteType *>(impl)->getElementType(tablegen_opaque_val);
}
template<typename ConcreteType>
bool detail::ShapedTypeInterfaceTraits::FallbackModel<ConcreteType>::hasRank(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return static_cast<const ConcreteType *>(impl)->hasRank(tablegen_opaque_val);
}
template<typename ConcreteType>
::llvm::ArrayRef<int64_t> detail::ShapedTypeInterfaceTraits::FallbackModel<ConcreteType>::getShape(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return static_cast<const ConcreteType *>(impl)->getShape(tablegen_opaque_val);
}

} // namespace mlir
