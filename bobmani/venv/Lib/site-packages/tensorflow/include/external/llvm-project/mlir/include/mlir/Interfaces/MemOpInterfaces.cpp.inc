/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Attempt to bubble-down the incoming cast-like operands. On success
/// returns a `std::optional<SmallVector<Value>>`, otherwise it returns
/// failure. If the optional is `std::nullopt` then the cast was performed
/// in place, otherwise the method returns a list of replacement values.
/// If new results are produced, these must be compatible with the original
/// operation results.
/// 
/// If the operation was not modified in place, then the interface
/// guarantees it is valid to erase the original operation.
/// If the operation was modified in place, then the interface must
/// guarantee no operations were created by the method, and that no further
/// IR modification is necessary.
/// 
/// Any implementations of this method must not erase/replace the original
/// operation, instead it is the caller responsibility to erase or replace
/// the op with the results provided by the method.
/// 
/// Finally, any implementations of this method have to guarantee that the
/// IR remains valid at all times.
::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> mlir::MemorySpaceCastConsumerOpInterface::bubbleDownCasts(::mlir::OpBuilder & builder) {
      return getImpl()->bubbleDownCasts(getImpl(), getOperation(), builder);
  }

/// Returns the source ptr-like value.
::mlir::TypedValue<::mlir::PtrLikeTypeInterface> mlir::MemorySpaceCastOpInterface::getSourcePtr() {
      return getImpl()->getSourcePtr(getImpl(), getOperation());
  }

/// Returns the target ptr-like value.
::mlir::TypedValue<::mlir::PtrLikeTypeInterface> mlir::MemorySpaceCastOpInterface::getTargetPtr() {
      return getImpl()->getTargetPtr(getImpl(), getOperation());
  }

/// Returns whether the memory space cast specified by `tgt` and `src`
/// is supported.
bool mlir::MemorySpaceCastOpInterface::isValidMemorySpaceCast(::mlir::PtrLikeTypeInterface tgt, ::mlir::PtrLikeTypeInterface src) {
      return getImpl()->isValidMemorySpaceCast(getImpl(), getOperation(), tgt, src);
  }

/// Clones the memory space cast op with the given source and target type.
::mlir::MemorySpaceCastOpInterface mlir::MemorySpaceCastOpInterface::cloneMemorySpaceCastOp(::mlir::OpBuilder & builder, ::mlir::PtrLikeTypeInterface tgt, ::mlir::TypedValue<::mlir::PtrLikeTypeInterface> src) {
      return getImpl()->cloneMemorySpaceCastOp(getImpl(), getOperation(), builder, tgt, src);
  }

/// Returns whether the source pointer of the memory-space cast can be used
/// by the `MemorySpaceCastConsumerOpInterface::bubbleDownCasts` method to
/// promote the source pointer and bubble down the cast.
/// 
/// For example, a cast operation might decide that all casts to the generic
/// memory-space can be promoted. 
bool mlir::MemorySpaceCastOpInterface::isSourcePromotable() {
      return getImpl()->isSourcePromotable(getImpl(), getOperation());
  }
