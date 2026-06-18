/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Generate IR to verify this op at runtime, aborting runtime execution if
/// verification fails.
void mlir::RuntimeVerifiableOpInterface::generateRuntimeVerification(::mlir::OpBuilder & builder, ::mlir::Location loc, function_ref<std::string(Operation *, StringRef)> generateErrorMessage) {
      return getImpl()->generateRuntimeVerification(getImpl(), getOperation(), builder, loc, generateErrorMessage);
  }
