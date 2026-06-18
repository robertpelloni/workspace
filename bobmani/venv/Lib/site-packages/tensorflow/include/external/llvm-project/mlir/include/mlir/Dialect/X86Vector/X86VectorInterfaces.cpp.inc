/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns mangled LLVM intrinsic function name matching the operation
/// variant.
std::string mlir::x86vector::X86IntrinsicOp::getIntrinsicName() {
      return getImpl()->implOneToOneIntrinsicOpInterface->getIntrinsicName(getImpl()->implOneToOneIntrinsicOpInterface, getOperation());
  }

/// Returns operands for a corresponding LLVM intrinsic.
/// 
/// Additional operations may be created to facilitate mapping
/// between the source operands and the target intrinsic.
SmallVector<Value> mlir::x86vector::X86IntrinsicOp::getIntrinsicOperands(::mlir::ArrayRef<Value> operands, const ::mlir::LLVMTypeConverter & typeConverter, ::mlir::RewriterBase & rewriter) {
      return getImpl()->implOneToOneIntrinsicOpInterface->getIntrinsicOperands(getImpl()->implOneToOneIntrinsicOpInterface, getOperation(), operands, typeConverter, rewriter);
  }
