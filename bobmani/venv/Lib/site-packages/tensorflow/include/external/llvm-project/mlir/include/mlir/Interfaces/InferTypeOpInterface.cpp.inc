/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Infer the components of return type of shape containter.
/// 
///       The method takes an optional location which, if set, will be used to
///       report errors on. The operands and attributes correspond to those with
///       which an Operation would be created (e.g., as used in Operation::create)
///       and the regions of the op.
/// 
///       Unknown (e.g., unranked) shape and nullptrs for element type and attribute
///       may be returned by this function while returning success. E.g., partial
///       population of components is not error condition.
/// 
///       Because this method can be called from within different stages of IR
///       verification, implementations should not assume the arguments to
///       represent fully valid IR and are responsible for checking inputs for
///       validity to the degree necessary to perform the return type inference.
::llvm::LogicalResult mlir::InferShapedTypeOpInterface::inferReturnTypeComponents(::mlir::MLIRContext* context, ::std::optional<::mlir::Location> location, ::mlir::ValueShapeRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::ShapedTypeComponents>& inferredReturnShapes) {
      return getImpl()->inferReturnTypeComponents(context, location, operands, attributes, properties, regions, inferredReturnShapes);
  }

/// Reify the shape computation for the operation.
/// 
///       Insert operations using the given OpBuilder that computes the
///       result shape. This interface is supposed to be workable during dialect
///       conversion (e.g. convert from tensor world to buffer world),
///       where `getOperand` may be invalid. For example, some ops (e.g.
///       dynamic_reshape(input, target_shape)) may depend on their operands
///       to calculate the result shape. When the `matchAndRewrite ` method
///       of a conversion pattern is called, the operands of the op to convert
///       may have been converted into other types, which makes it invalid to
///       call the `getOperand` method of such op directly inside the
///       conversion pattern.  To solve this problem, this interface follows
///       the design of the conversion pattern, that is, accepting passed in
///       operands to avoid calling `getOperand` directly inside the interface
///       implementation.
::llvm::LogicalResult mlir::InferShapedTypeOpInterface::reifyReturnTypeShapes(::mlir::OpBuilder& builder, ::mlir::ValueRange operands, ::llvm::SmallVectorImpl<::mlir::Value> & reifiedReturnShapes) {
      return getImpl()->reifyReturnTypeShapes(getImpl(), getOperation(), builder, operands, reifiedReturnShapes);
  }

/// Infer the return types that an op would generate.
/// 
///       The method takes an optional location which, if set, will be used to
///       report errors on. The operands and attributes correspond to those with
///       which an Operation would be created (e.g., as used in Operation::create)
///       and the regions of the op. Be aware that this method is supposed to be
///       called with valid arguments, e.g., operands are verified, or it may result
///       in an undefined behavior.
/// 
///       The inferred result types may be less precise than what may be specified
///       directly or produced by refinement, but are required to be compatible
///       (as defined by the op's compatibility function).
::llvm::LogicalResult mlir::InferTypeOpInterface::inferReturnTypes(::mlir::MLIRContext * context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>& inferredReturnTypes) {
      return getImpl()->inferReturnTypes(context, location, operands, attributes, properties, regions, inferredReturnTypes);
  }

/// Refine the return types that an op would generate.
/// 
///       This method computes the return types as `inferReturnTypes` does but
///       additionally takes the existing result types as input. The existing
///       result types can be checked as part of inference to provide more
///       op-specific error messages as well as part of inference to merge
///       additional information, attributes, during inference. It is called during
///       verification for ops implementing this trait with default behavior
///       reporting mismatch with current and inferred types printed.
/// 
///       The operands and attributes correspond to those with which an Operation
///       would be created (e.g., as used in Operation::create) and the regions of
///       the op. The method takes an optional location which, if set, will be used
///       to report errors on.
/// 
///       The return types may be elided or specific elements be null for elements
///       that should just be returned but not verified.
/// 
///       This method may be called from within different stages of IR verification,
///       implementations should not assume the arguments to represent fully valid
///       IR and are responsible for checking inputs for validity to the degree
///       necessary to perform the return type inference.
::llvm::LogicalResult mlir::InferTypeOpInterface::refineReturnTypes(::mlir::MLIRContext * context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>& returnTypes) {
      return getImpl()->refineReturnTypes(context, location, operands, attributes, properties, regions, returnTypes);
  }

/// Returns whether two type ranges are compatible result types.
bool mlir::InferTypeOpInterface::isCompatibleReturnTypes(::mlir::TypeRange lhs, ::mlir::TypeRange rhs) {
      return getImpl()->isCompatibleReturnTypes(lhs, rhs);
  }

/// Reify the shapes of all the result of an operation (typically in terms 
/// of the shape of its operands).
/// 
/// `reifiedReturnShapes` is populated with one vector per op result. Each
/// of those vectors contains an OpFoldResult for each dimension of the
/// shaped type. The given builder may be used to insert ops that compute
/// result shapes.
/// 
/// If the shape of a particular result cannot be computed it in terms of
/// its operands it must be left empty. If any dimension of the result cannot
/// be computed it must be set to OpFoldResult().
::llvm::LogicalResult mlir::ReifyRankedShapedTypeOpInterface::reifyResultShapes(::mlir::OpBuilder & builder, ::mlir::ReifiedRankedShapedTypeDims & reifiedReturnShapes) {
      return getImpl()->reifyResultShapes(getImpl(), getOperation(), builder, reifiedReturnShapes);
  }

/// Reify the shape of a single result of an operation (typically in terms 
/// of the shape of its operands).
/// 
/// Returns the shape of a single result of the operation as a
/// `SmallVector<OpFoldResult>`, one per dimension of the shaped type. The
/// given builder may be used to insert ops that compute result shapes.
/// 
/// If any dimension of the result cannot be computed it must be set to
/// OpFoldResult().
::llvm::FailureOr<::llvm::SmallVector<::mlir::OpFoldResult>> mlir::ReifyRankedShapedTypeOpInterface::reifyShapeOfResult(::mlir::OpBuilder & builder, int resultIndex) {
      return getImpl()->reifyShapeOfResult(getImpl(), getOperation(), builder, resultIndex);
  }

/// Reify the shape of a dimension of a given result of an operation
/// (typically in terms of the shape of its operands).
/// 
/// Returns the shape of a specific dimension of a result of the operation as
/// an OpFoldResult. The given builder may be used to insert ops that compute
/// the shapes.
/// 
/// If the dimension of the result cannot be computed the method must return
/// `failure()`.
::llvm::FailureOr<::mlir::OpFoldResult> mlir::ReifyRankedShapedTypeOpInterface::reifyDimOfResult(::mlir::OpBuilder & builder, int resultIndex, int dim) {
      return getImpl()->reifyDimOfResult(getImpl(), getOperation(), builder, resultIndex, dim);
  }
