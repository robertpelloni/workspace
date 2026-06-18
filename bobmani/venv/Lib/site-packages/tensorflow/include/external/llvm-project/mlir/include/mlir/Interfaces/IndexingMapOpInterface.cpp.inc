/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Return the indexing maps attribute within the current operation.
ArrayAttr mlir::IndexingMapOpInterface::getIndexingMaps() {
      return getImpl()->getIndexingMaps(getImpl(), getOperation());
  }

/// Return the indexing maps within the current operation.
SmallVector<AffineMap> mlir::IndexingMapOpInterface::getIndexingMapsArray() {
      return getImpl()->getIndexingMapsArray(getImpl(), getOperation());
  }

/// Return the input or output indexing map for `opOperand`.
AffineMap mlir::IndexingMapOpInterface::getMatchingIndexingMap(OpOperand* opOperand) {
      return getImpl()->getMatchingIndexingMap(getImpl(), getOperation(), opOperand);
  }

/// Hook to provide a custom AffineMap used to compute all the operand
/// subshapes given loop bounds. This is used to answer the question: "given
/// an iteration space over the codomain, what are the subshapes of the
/// operands involved in the computation".
/// The default behavior is to just concatenate all the indexing maps.
/// A custom AffineMap allows providing a map that can be used to
/// compute subshapes even in cases where the concatenation of indexing maps
/// (i.e. the data traversal order) is not a simple permutation of the loop
/// traversal order. It is then possible to define ops with skewed data
/// traversal order for which we can still easily compute hyperrectangular
/// loop bounds and subviews.
AffineMap mlir::IndexingMapOpInterface::getLoopsToShapesMap() {
      return getImpl()->getLoopsToShapesMap(getImpl(), getOperation());
  }

/// Hook to provide a custom AffineMap used to construct the
/// hyperrectangular loop iteration space given all the operand subshapes.
/// This is used to answer the question:
/// "Given a list of operand ranges, what is the subportion of the iteration
/// space involved in the computation".
/// This is the inverse problem of `getLoopsToShapesMap`.
/// Return the empty AffineMap when such an AffineMap cannot be constructed.
/// The default behavior is based on a very simple inference procedure that
/// only works with permutation affine maps.
/// A more advanced Tensor-Comprehension like inference is possible but has
/// proven to be ambiguous in unfavorable case.
/// A safer and more robust alternative is to allow each op to define
/// its own AffineMap.
AffineMap mlir::IndexingMapOpInterface::getShapesToLoopsMap() {
      return getImpl()->getShapesToLoopsMap(getImpl(), getOperation());
  }

/// Returns the static shape of the underlying operand (note this is
/// op-specific behavior).
/// Returns ShapedType::kDynamic for non-statically-known loop ranges.
SmallVector<int64_t> mlir::IndexingMapOpInterface::getStaticOperandShape(OpOperand* opOperand) {
      return getImpl()->getStaticOperandShape(getImpl(), getOperation(), opOperand);
  }

/// Returns loop ranges by composing `getShapesToLoopsMap()` with the
/// flattened list of operand shapes.
/// Returns ShapedType::kDynamic for non-statically-known loop ranges.
SmallVector<int64_t> mlir::IndexingMapOpInterface::getStaticLoopRanges() {
      return getImpl()->getStaticLoopRanges(getImpl(), getOperation());
  }
