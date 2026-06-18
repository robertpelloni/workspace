/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns the alignment encoded on the operation as an `llvm::MaybeAlign`.
/// Operations providing a differently named accessor can override the
/// default implementation.
::llvm::MaybeAlign mlir::AlignmentAttrOpInterface::getMaybeAlign() {
      return getImpl()->getMaybeAlign(getImpl(), getOperation());
  }
