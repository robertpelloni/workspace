/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Infer the strided metadata bounds on the results of this op given
/// the bounds on its operands.
/// For each result value or block argument of interest, the method should
/// call `setMetadata` with that `Value` as an argument.
/// The `operands` parameter contains the strided metadata ranges for all the
/// operands of the operation in order.
/// The `getIntRange` callback is provided for obtaining the int-range
/// analysis result for a given value.
void mlir::InferStridedMetadataOpInterface::inferStridedMetadataRanges(::llvm::ArrayRef<::mlir::StridedMetadataRange> operands, ::mlir::GetIntRangeFn getIntRange, ::mlir::SetStridedMetadataRangeFn setMetadata, int32_t indexBitwidth) {
      return getImpl()->inferStridedMetadataRanges(getImpl(), getOperation(), operands, getIntRange, setMetadata, indexBitwidth);
  }
