/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Return `idx`^th result of the parent operation.
::mlir::OpResult mlir::InParallelOpInterface::getParentResult(int64_t idx) {
      return getImpl()->getParentResult(getImpl(), getOperation(), idx);
  }

/// Return the contained ops that yield subvalues that this op combines to
/// yield to its parent.
::llvm::iterator_range<Block::iterator> mlir::InParallelOpInterface::getYieldingOps() {
      return getImpl()->getYieldingOps(getImpl(), getOperation());
  }

/// Returns the list of destination values this op contributes to.
::mlir::MutableOperandRange mlir::ParallelCombiningOpInterface::getUpdatedDestinations() {
      return getImpl()->getUpdatedDestinations(getImpl(), getOperation());
  }

/// Returns the iterating parent for this op.
::mlir::Operation*mlir::ParallelCombiningOpInterface::getIteratingParent() {
      return getImpl()->getIteratingParent(getImpl(), getOperation());
  }
