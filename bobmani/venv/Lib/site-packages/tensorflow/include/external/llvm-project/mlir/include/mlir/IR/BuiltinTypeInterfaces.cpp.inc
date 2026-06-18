/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns the APFloat semantics for this floating-point type.
const ::llvm::fltSemantics &mlir::FloatType::getFloatSemantics() const {
      return getImpl()->getFloatSemantics(getImpl(), *this);
  }

/// Returns a float type with bitwidth scaled by `scale`. Returns a "null"
/// float type if the scaled element type cannot be represented.
::mlir::FloatType mlir::FloatType::scaleElementBitwidth(unsigned scale) const {
      return getImpl()->scaleElementBitwidth(getImpl(), *this, scale);
  }

/// Returns the memory space of this ptr-like type.
::mlir::Attribute mlir::PtrLikeTypeInterface::getMemorySpace() const {
      return getImpl()->getMemorySpace(getImpl(), *this);
  }

/// Returns the element type of this ptr-like type. Note: this method can
/// return `::mlir::Type()`, in which case the pointer is considered opaque.
::mlir::Type mlir::PtrLikeTypeInterface::getElementType() const {
      return getImpl()->getElementType(getImpl(), *this);
  }

/// Returns whether this ptr-like type has non-empty metadata.
bool mlir::PtrLikeTypeInterface::hasPtrMetadata() const {
      return getImpl()->hasPtrMetadata(getImpl(), *this);
  }

/// Returns a clone of this type with the given memory space and element type,
/// or `failure` if the type cannot be cloned with the specified arguments.
/// If the pointer is opaque and `elementType` is not `std::nullopt` the
/// method will return `failure`.
/// 
/// If no `elementType` is provided and ptr is not opaque, the `elementType`
/// of this type is used.
::llvm::FailureOr<::mlir::PtrLikeTypeInterface> mlir::PtrLikeTypeInterface::clonePtrWith(::mlir::Attribute memorySpace, ::std::optional<::mlir::Type> elementType) const {
      return getImpl()->clonePtrWith(getImpl(), *this, memorySpace, elementType);
  }

/// Returns a clone of this type with the given shape and element type.
/// 
/// If no shape is provided, the shape of this type is used. In that case, if
/// this type is unranked, so is the resulting type.
/// 
/// If a shape is provided, the resulting type is always ranked, even if this
/// type is unranked.
::mlir::ShapedType mlir::ShapedType::cloneWith(::std::optional<::llvm::ArrayRef<int64_t>> shape, ::mlir::Type elementType) const {
      return getImpl()->cloneWith(getImpl(), *this, shape, elementType);
  }

/// Returns the element type of this shaped type.
::mlir::Type mlir::ShapedType::getElementType() const {
      return getImpl()->getElementType(getImpl(), *this);
  }

/// Returns if this type is ranked, i.e. it has a known number of dimensions.
bool mlir::ShapedType::hasRank() const {
      return getImpl()->hasRank(getImpl(), *this);
  }

/// Returns the shape of this type if it is ranked, otherwise asserts.
::llvm::ArrayRef<int64_t> mlir::ShapedType::getShape() const {
      return getImpl()->getShape(getImpl(), *this);
  }
