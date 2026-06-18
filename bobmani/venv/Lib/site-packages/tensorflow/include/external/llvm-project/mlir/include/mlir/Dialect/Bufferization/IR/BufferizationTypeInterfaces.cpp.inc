/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns a BufferLike type for this TensorLike type.
::mlir::FailureOr<::mlir::bufferization::BufferLikeType> mlir::bufferization::TensorLikeType::getBufferType(const ::mlir::bufferization::BufferizationOptions & options, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const {
      return getImpl()->getBufferType(getImpl(), *this, options, emitError);
  }

/// Returns whether a BufferLike type is compatible to this TensorLike type.
/// The BufferLike type is assumed to be created by getBufferType().
::mlir::LogicalResult mlir::bufferization::TensorLikeType::verifyCompatibleBufferType(::mlir::bufferization::BufferLikeType bufferType, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const {
      return getImpl()->verifyCompatibleBufferType(getImpl(), *this, bufferType, emitError);
  }
