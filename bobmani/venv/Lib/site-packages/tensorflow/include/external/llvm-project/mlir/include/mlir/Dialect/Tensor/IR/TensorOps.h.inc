/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: TensorOps.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::tensor {

/// tensor bitcast operation
/// Bitcast a tensor from one type to another type of equivalent element width.
///     If both are ranked, then the rank should be the same and static dimensions
///     should match.
/// 
///     Example:
/// 
///     ```mlir
///     // Bitcast from unsigned to signed or signless integer.
///     %2 = tensor.bitcast %1 : tensor<4xui32> to tensor<4xi32>
///     ```
class BitcastOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// tensor cast operation
/// Convert a tensor from one type to an equivalent type without changing any
///     data elements. The source and destination types must both be tensor types
///     with the same element type. If both are ranked, then the rank should be the
///     same and static dimensions should match. The operation is invalid if
///     converting to a mismatching constant dimension.
/// 
///     Example:
/// 
///     ```mlir
///     // Convert from unknown rank to rank 2 with unknown dimension sizes.
///     %2 = tensor.cast %1 : tensor<*xf32> to tensor<?x?xf32>
/// 
///     // Convert to a type with more known dimensions.
///     %3 = tensor.cast %2 : tensor<?x?xf32> to tensor<4x?xf32>
/// 
///     // Discard static dimension and rank information.
///     %4 = tensor.cast %3 : tensor<4x?xf32> to tensor<?x?xf32>
///     %5 = tensor.cast %4 : tensor<?x?xf32> to tensor<*xf32>
///     ```
class CastOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// operation to produce a tensor with a smaller rank
/// The `tensor.collapse_shape` op produces a new tensor of lower (or equal)
///     rank whose dimension sizes are a reassociation of the original `src` dimensions.
/// 
///     A reassociation is defined as a continuous grouping of dimensions and is
///     represented by an array of DenseI64ArrayAttr attribute. The reassociation
///     maps are applied to the operand shape to obtain the result shape.
/// 
/// 
///     Example:
/// 
///     ```mlir
///     // Dimension collapse (i, j) -> i' and k -> k'
///     %b = tensor.collapse_shape %a [[0, 1], [2]]
///         : tensor<?x?x?xf32> into tensor<?x?xf32>
///     ```
class CollapseShapeOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// tensor concatenation operation
/// The "concat" operation constructs a tensor out of a variadic list of input
///     tensors, concatenated along a static dimension number. All inputs and the
///     result type must share the same rank.
/// 
///     `dim` specifies the dimension along which to concatenate. The size of the
///     concatenated dimension in the result must be equal to the sum of the sizes
///     of the inputs along that dimension. All other dimensions in both the inputs
///     and result must be the same size.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = tensor.concat dim(0) %0, %1, %2 :
///         (tensor<3x6xf32>, tensor<3x6xf32>, tensor<1x6xf32) -> tensor<7x6xf32>
/// 
///     // Dynamic + dynamic -> static
///     %0 = tensor.concat dim(1) %0, %1, %2 :
///         (tensor<3x?xf32>, tensor<3x2xf32>, tensor<3x?xf32) -> tensor<3x10xf32>
///     ```
class ConcatOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// dimension index operation
/// The `tensor.dim` operation takes a tensor and a dimension operand of type
///     `index`. It returns the size of the requested dimension of the given
///     tensor. If the dimension index is out of bounds, the behavior is undefined.
/// 
///     The specified tensor type is that of the first operand.
/// 
///     Example:
/// 
///     ```mlir
///     // Always returns 4, can be constant folded:
///     %c0 = arith.constant 0 : index
///     %x = tensor.dim %A, %c0 : tensor<4x?xf32>
/// 
///     // Return the dynamic dimension of %A.
///     %c1 = arith.constant 1 : index
///     %y = tensor.dim %A, %c1 : tensor<4x?xf32>
/// 
///     // Equivalent generic form:
///     %x = "tensor.dim"(%A, %c0) : (tensor<4x?xf32>, index) -> index
///     %y = "tensor.dim"(%A, %c1) : (tensor<4x?xf32>, index) -> index
///     ```
class DimOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// empty tensor operation
/// `tensor.empty` is an operation that defines a tensor of a particular shape.
///     The shape could be dynamic or static. The contents of the tensor are
///     unspecified and the only purpose of the op result is to materialize the
///     specified shape in IR and make it available to other transformations.
/// 
///     `tensor.empty` is useful in transformations that expect destination style
///     ops. I.e., ops that implement `DestinationStyleOpInterface`. Ops that are
///     not in destination style can be made compatible with such transformations
///     with a `tensor.empty` destination.
/// 
///     Note: This op can be lowered to a `bufferization.alloc_tensor`, at which
///     point it turns into an explicit buffer allocation.
class EmptyOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// operation to produce a tensor with a higher rank
/// The `tensor.expand_shape` op produces a tensor of higher (or equal)
///     rank than the operand `src` whose dimension sizes are a reassociation of
///     `src`.
/// 
///     A reassociation is defined as a continuous grouping of dimensions and is
///     represented with an array of DenseI64ArrayAttr attribute.  The reassociation
///     maps applied to the result tensor with the higher rank must result in the
///     operand tensor with the smaller rank.
/// 
///     The representation for the output shape supports a partially-static
///     specification via attributes specified through the `static_output_shape`
///     argument.  A special sentinel value `ShapedType::kDynamic` encodes that the
///     corresponding entry has a dynamic value.  There must be exactly as many SSA
///     inputs in `output_shape` as there are `ShapedType::kDynamic` entries in
///     `static_output_shape`.
/// 
///     Example:
/// 
///     ```mlir
///     // Dimension expansion i -> (i', j') and (k) -> (k')
///     %b = tensor.expand_shape %a [[0, 1], [2]] output_shape [%sz0, %sz1, 32]
///         : tensor<?x32xf32> into tensor<?x?x32xf32>
///     ```
class ExpandShapeOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// element extraction operation
/// The `tensor.extract` op reads a ranked tensor and returns one element as
///     specified by the given indices. The result of the op is a value with the
///     same type as the elements of the tensor. The arity of indices must match
///     the rank of the accessed value. All indices should all be of `index` type.
/// 
///     Example:
/// 
///     ```mlir
///     %4 = tensor.extract %t[%1, %2] : tensor<4x4xi32>
///     %5 = tensor.extract %rt[%1, %2] : tensor<?x?xi32>
///     ```
class ExtractOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// extract slice operation
/// The "extract_slice" operation extract a tensor from another tensor as
///     specified by the operation's offsets, sizes and strides arguments.
/// 
///     The extract_slice operation supports the following arguments:
/// 
///     * source: the "base" tensor from which to extract a slice.
///     * offsets: tensor-rank number of offsets into the "base" tensor from which
///                to extract the slice.
///     * sizes: tensor-rank number of sizes which specify the sizes of the result
///              tensor type.
///     * strides: tensor-rank number of strides specifying subsampling in each
///                dimension.
/// 
///     The representation based on offsets, sizes and strides support a
///     partially-static specification via attributes specified through the
///     `static_offsets`, `static_sizes` and `static_strides` arguments. A special
///     sentinel value ShapedType::kDynamic encodes that the corresponding entry has
///     a dynamic value.
/// 
///     After buffer allocation, the "extract_slice" op is expected to lower into a
///     memref.subview op.
/// 
///     An extract_slice operation may additionally reduce the rank of the resulting
///     tensor by removing dimensions that are statically known to be of size 1.
///     This rank-reduction behavior is not required by the op semantics: this
///     flexibility allows to progressively drop unit dimensions while lowering
///     between different flavors of ops on that operate on tensors.
/// 
///     #### Verification vs Inference in the rank-reduced case
/// 
///     Note that there may be multiple ways to infer a resulting rank-reduced type.
///       e.g. 1x6x1 could potentially rank-reduce to either 1x6 or 6x1 2-D shapes.
/// 
///     To disambiguate, the inference helpers `inferCanonicalRankReducedResultType`
///     only drop the first unit dimensions, in order:
///       e.g. 1x6x1 rank-reduced to 2-D will infer the 6x1 2-D shape, but not 1x6.
/// 
///     Verification however has access to result type and does not need to infer.
///     The verifier calls `isRankReducedType(getSource(), getResult())` to
///     determine whether the result type is rank-reduced from the source type.
///     This computes a so-called rank-reduction mask, consisting of dropped unit
///     dims, to map the rank-reduced type to the source type by dropping ones:
///       e.g. 1x6 is a rank-reduced version of 1x6x1 by mask {2}
///            6x1 is a rank-reduced version of 1x6x1 by mask {0}
///            1x2x1x4 is a rank-reduced version of 1x1x2x1x1x4x1 by mask {1, 4, 6}
///              (remaining common 1 dimensions are matched eagerly)
/// 
///     Example:
/// 
///     ```mlir
///     // Rank-reducing extract_slice.
///     %1 = tensor.extract_slice %0[0, 0, 0][1, 16, 4][1, 1, 1] :
///       tensor<8x16x4xf32> to tensor<16x4xf32>
///     %3 = tensor.extract_slice %2[%o0, 4, %o2][1, %sz1, 1][1, %st1, 1] :
///       tensor<8x16x4xf32> to tensor<1x?xf32>
///     ```
class ExtractSliceOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// tensor from elements operation.
/// Create a N-D tensor from a range of same-type arguments. The number of
///     provided `elements` should equal to the number of the elements in the
///     result type. The `elements` correspond to a flattened tensor.
/// 
///     Example:
/// 
///     ```mlir
///     tensor.from_elements %a, %b, %c, %d, %e, %f :  tensor<2x3xindex>
///     ```
/// 
///     will result in a tensor
/// 
///     [[%a, %b, %c]
///      [%d, %e, %f]]
class FromElementsOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// gather a subset of a tensor at specified indices
/// The `gather` operation extracts a subset of the elements from a `source`
///     tensor at the given indices.
/// 
///     In its most general form, the tensor of indices specifies all the coordinates
///     of every element to extract (i.e. COO format, without the payload).
///     The indices are expected to be confined to coordinate values that fit the
///     range of the `source` tensor, otherwise the behavior is undefined.
/// 
///     The leading dimensions of the index tensor give the result tensor its leading
///     dimensions. The trailing dimensions of the result tensor are obtained from
///     the source tensor by omitting the dimensions specified in `gather_dims`
///     (rank-reducing semantics) or setting them to `1` (rank-preserving semantics)
///     (see examples).
///     The trailing dimension of the index tensor contains the coordinates and is
///     expected to have its size equal to the number of dimensions being gathered.
///     This convention allows an idiomatic specification and lowering of "gathering
///     multiple N-D slices from the source tensor".
/// 
///     Note: in the examples below, we separate out the indexing part of the tensor
///     type by a whitespace for readability purposes.
/// 
///     Example:
/// 
///     ```mlir
///         // For each 1x2 triple of coordinates in %indices, extract the
///         // element (i.e. 0-D subset) at the coordinates triple in %source.
///         //
///         %out = tensor.gather %source[%indices] gather_dims([0, 1, 2]) :
///           (tensor<4x4x4xf32>, tensor<1x2x 3xindex>) -> tensor<1x2x 1x1x1xf32>
/// 
///         // Note: result type may be further rank-reduced to tensor<1x2x f32>.
///     ```
/// 
///     A slice variant is provided to allow specifying whole slices of the source
///     tensor.
/// 
///     Example:
/// 
///     ```mlir
///         // For each 5x6 singleton of coordinates in %indices, extract the 2-D
///         // slice %source[*, %indices[...]:%indices[...] + 1, *] with the indices
///         // corresponding to the `gather_dims` attribute specified by %indices.
///         //
///         %out = tensor.gather %source[%indices] gather_dims([1]) :
///           (tensor<3x4x5xf32>, tensor<6x7x 1xindex>) -> tensor<6x7x 3x1x5xf32>
/// 
///         // Note: result type may be further rank-reduced to tensor<6x7x 3x5xf32>.
///     ```
/// 
///     The dimensions specified in the gather_dims attribute are ones for which the
///     result tensor has size `1`.
///     I.e. if the source type is `axbxcxd` and the coordinates are [1, 3], then
///     the shape suffix is `ax1xcx1`.
///     Gather also allows rank-reducing semantics where the shape `ax1xcx1` can be
///     further simplified to `axc`.
/// 
///     The elemental type of the indices tensor can be any integer type.
///     In the absence of target-specific or problem specific information the default
///     type one should use is `index`.
/// 
///     This operation does not support unranked tensors.
/// 
///     An optional `unique` unit attribute may be specified to indicate that the
///     coordinates in `indices` are statically guaranteed to be unique at runtime.
///     Incorrectly setting the `unique` attribute when the coordinates are not truly
///     unique is undefined behavior.
/// 
///     Only full slices are meant to be supported by this op, if one desires
///     partial slices (e.g. strided windows) one should compose this op with other
///     tensor ops (e.g. tensor.extract_slice). This is to avoid a slippery slope of
///     complexity that would make the op unusable in practice.
/// 
///     At the tensor-level, the index tensor is specified in an AoS form (i.e.
///     coordinate tuple is the most minor). It is the responsibility of further
///     lowerings and bufferization to implement various concrete layouts.
/// 
///     Note: As currently specified, the operation must lower to an abstraction that
///     performs copies to the output tensor. This is because the buffer type system
///     is currently not rich enough to allow multiple non-contiguous views in the
///     same type. This is visible more clearly in a notional buffer version of the
///     op:
/// 
///     ```mlir
///         // memref<?x4x1xf32> is a contiguous buffer of ?x4x1 elements.
///         // gather from random source slices must copy to the contiguous output.
///         %out = memref.gather %source[%indices] gather_dims([1]) :
///           (memref<4x4xf32>, memref<?x 1xindex>) -> memref<?x 4x1xf32>
/// 
///         // Nested buffer support would allow gather to directly index into the
///         // source buffer (i.e. represent a jagged view into the source).
///         %out = memref.gather %source[%indices] gather_dims([1]) :
///           (memref<4x4xf32>, memref<?x 1xindex>) -> memref<? x memref<4x1xf32>>
///     ```
class GatherOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// Creates a dynamically sized tensor from elements
/// This operation creates a dynamically sized tensor with elements of any type.
///     It expects one index operand per dynamic extent of the result tensor.
/// 
///     The body region defines the tensor's elements. It takes index operands as
///     its region arguments that span the index space. The element at the given
///     position is yielded with the `yield` operation (see `YieldOp`). There is
///     no defined ordering to the invocations of the body. It is conceptually
///     a "parallel map" operation.
/// 
///     Example:
/// 
///     ```mlir
///       %tnsr = tensor.generate %m, %n {
///       ^bb0(%i : index, %j : index, %k : index):
///         ...
///         yield %elem : f32
///       } : tensor<?x3x?f32>
///     ```
class GenerateOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// element insertion operation
/// The `tensor.insert` op inserts a scalar into a ranked tensor `dest` as
///     specified by the operation's indices.
/// 
///     It returns a copy of `dest` with the indexed position updated to the value
///     of `scalar`.
/// 
///     The arity of `indices `must match the rank of the tensor `dest`. All
///     indices should be of `index` type.
/// 
///     Example:
/// 
///     ```mlir
///     %4 = tensor.insert %t into %dest[%1, %2] : tensor<4x4xi32>
///     %5 = tensor.insert %rt into %dest[%1, %2] : tensor<?x?xi32>
///     ```
class InsertOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// insert_slice operation
/// The "insert_slice" operation insert a tensor `source` into another
///     tensor `dest` as specified by the operation's offsets, sizes and strides
///     arguments.
/// 
///     It returns a copy of `dest` with the proper slice updated with the value
///     of `source`.
/// 
///     The insert_slice operation supports the following arguments:
/// 
///     * source: the tensor that is inserted.
///     * dest: the tensor into which the source tensor is inserted.
///     * offsets: tensor-rank number of offsets into the `dest` tensor into which
///                the slice is inserted.
///     * sizes: tensor-rank number of sizes which specify the sizes of the source
///              tensor type.
///     * strides: tensor-rank number of strides that specify subsampling in each
///                dimension.
/// 
///     The representation based on offsets, sizes and strides support a
///     partially-static specification via attributes specified through the
///     `static_offsets`, `static_sizes` and `static_strides` arguments. A special
///     sentinel value ShapedType::kDynamic encodes that the corresponding entry has
///     a dynamic value.
/// 
///     After buffer allocation, the "insert_slice" op is expected to lower into a
///     memref.subview op.
/// 
///     An insert_slice operation may additionally specify insertion into a tensor
///     of higher rank than the source tensor, along dimensions that are statically
///     known to be of size 1.
///     This rank-altering behavior is not required by the op semantics: this
///     flexibility allows to progressively drop unit dimensions while lowering
///     between different flavors of ops on that operate on tensors.
///     The rank-altering behavior of tensor.insert_slice matches the rank-reducing
///     behavior of tensor.extract_slice.
/// 
///     #### Verification in the rank-reduced case
/// 
///     The same verification discussion and mechanisms apply as for ExtractSliceOp.
///     Unlike ExtractSliceOp however, there is no need for a specific inference.
/// 
///     Example:
/// 
///     ```mlir
///     // Rank-altering insert_slice.
///     %1 = tensor.insert_slice %t into %0[0, 0, 0][1, 16, 4][1, 1, 1] :
///       tensor<16x4xf32> into tensor<8x16x4xf32>
///     %3 = tensor.insert_slice %tt into %2[%o0, 4, %o2][1, %sz1, 1][1, %st1, 1] :
///       tensor<1x?xf32> into tensor<8x16x4xf32>
///     ```
class InsertSliceOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// tensor pad operation
/// `tensor.pad` is an operation that pads the `source` tensor
///     with given `low` and `high` padding config.
/// 
///     The PadOp operation supports the following arguments:
/// 
///     * source: the "base" tensor on which to pad.
///     * low: A list contains the padding along the start of each
///            dimension, i.e., how many padded values are prepended
///            to the beginning of the tensor in each dimension.
///     * high: A list contains the padding along the end of each
///             dimension, i.e., how many padded values are appended
///             to the end of the tensor in each dimension.
///     * nofold: indicates that the operation should not be folded when source and
///               result types are equal.
/// 
///     The result tensor dimensions are `low[i]` + `dim[i]` + `high[i]` for each
///     dimension `i`. The number of elements of `low` and `high` must match the
///     rank of the input tensor. They can be either a constant or a dynamic value.
/// 
///     The region of the `tensor.pad` operation returns the value to use
///     for the padding. The arguments of the region represent the index
///     of the source being accessed. There should be as many arguments as
///     the rank of the `source` tensor. The value `yield`-ed by the
///     region is used as the value of the view at the given position.
/// 
///     If `nofold` is set, the padding operation will not be folded away even
///     if the source type and the padded type have the same static shape. This can
///     be used, e.g., for packing or promotion to faster memory.
/// 
///     Example 1: add 3 zeros to the beginning and 5 zeros to the end of a 1D
///     tensor.
/// 
///     ```mlir
///       %arg0 = ... : tensor<10xi32>
///       %c0_i32 = arith.constant 0 : i32
///       %padded = tensor.pad %arg0 low[3] high[5] {
///       ^bb0(%arg1: index):
///         tensor.yield %c0_i32 : i32
///       } : tensor<10xi32> to tensor<18xi32>
///     ```
/// 
///     Example 2: add 1 value to the beginning of dimension 0, 2 values to the end
///     of dimension 0, 2 values to the start of dimension 1, and 3 values to the
///     end of dimension 1.
/// 
///     ```mlir
///       %pad_value = ... : f32
///       %0 = tensor.pad %0 low[1, 2] high[2, 3] {
///       ^bb0(%arg0 : index, %arg1 : index):
///         tensor.yield %pad_value : f32
///       } : tensor<?x?xf32> to tensor<?x?xf32>
///     ```
/// 
///     Example 3:
/// 
///     ```mlir
///       %pad_value = ... : f32
///       %0 = tensor.pad %arg0 low[2, %arg1, 3, 3] high[3, 3, %arg1, 2] {
///       ^bb0(%arg2: index, %arg3: index, %arg4: index, %arg5: index):
///           tensor.yield %pad_value : f32
///       } : tensor<1x2x2x?xf32> to tensor<6x?x?x?xf32>
///     ```
/// 
///     Example 4:
/// 
///     ```mlir
///       %pad_value = ... : f32
///       %0 = tensor.pad %arg0 low[0, 0] high[%ub0, %ub1] {
///       ^bb0(%arg1: index, %arg2: index):
///         tensor.yield %pad_value : f32
///       } : tensor<2x3xf32> to tensor<?x?xf32>
///     ```
/// 
///     Example 5: Force a padded value to be always exist with `nofold`, even
///     though the padding config specifies that no new elements will be added to
///     the tensor.
/// 
///     ```mlir
///       %pad_value = ... : f32
///       %0 = tensor.pad %arg0 nofold low[0, 0] high[0, 0] {
///       ^bb0(%arg1: index, %arg2: index):
///         tensor.yield %pad_value : f32
///       } : tensor<2x3xf32> to tensor<2x3xf32>
///     ```
class PadOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// Specify the tensor slice update of a single thread of a parent
///     InParallelOpInterface op.
/// The `parallel_insert_slice` yields a subset tensor value to its parent
///     InParallelOpInterface. These subset tensor values are aggregated to
///     in some unspecified order into a full tensor value returned by the parent
///     parallel iterating op.
///     The `parallel_insert_slice` is one such op allowed in the
///     InParallelOpInterface op.
/// 
///     Conflicting writes result in undefined semantics, in that the indices written
///     to by multiple parallel updates might contain data from any of the updates,
///     or even a malformed bit pattern.
/// 
///     If an index is updated exactly once, the value contained at that index
///     in the resulting tensor will be equal to the value at a corresponding index
///     of a slice that was used for the updated. If an index is not updated at all,
///     its value will be equal to the one in the original tensor.
/// 
///     This op does not create a new value, which allows maintaining a clean
///     separation between the subset and full tensor.
/// 
///     Note that we cannot mark this operation as pure (Pures), even
///     though it has no side effects, because it will get DCEd during
///     canonicalization.
/// 
///     The parallel_insert_slice operation supports the following arguments:
/// 
///     * source: the tensor that is inserted.
///     * dest: the tensor into which the source tensor is inserted.
///     * offsets: tensor-rank number of offsets into the `dest` tensor into which
///                the slice is inserted.
///     * sizes: tensor-rank number of sizes which specify the sizes of the source
///              tensor type.
///     * strides: tensor-rank number of strides that specify subsampling in each
///                dimension.
/// 
///     The representation based on offsets, sizes and strides support a
///     partially-static specification via attributes specified through the
///     `static_offsets`, `static_sizes` and `static_strides` arguments. A special
///     sentinel value ShapedType::kDynamic encodes that the corresponding entry has
///     a dynamic value.
/// 
///     After buffer allocation, the "parallel_insert_slice" op is expected to lower
///     into a memref.subview op.
/// 
///     A parallel_insert_slice operation may additionally specify insertion into a
///     tensor of higher rank than the source tensor, along dimensions that are
///     statically known to be of size 1.
///     This rank-altering behavior is not required by the op semantics: this
///     flexibility allows to progressively drop unit dimensions while lowering
///     between different flavors of ops on that operate on tensors.
///     The rank-altering behavior of tensor.parallel_insert_slice matches the
///     rank-reducing behavior of tensor.insert_slice and tensor.extract_slice.
/// 
///     #### Verification in the rank-reduced case
/// 
///     The same verification discussion and mechanisms apply as for ExtractSliceOp.
///     Unlike ExtractSliceOp however, there is no need for a specific inference.
class ParallelInsertSliceOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// rank operation
/// The `tensor.rank` operation takes a tensor operand and returns its rank.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = tensor.rank %arg0 : tensor<*xf32>
///     %1 = tensor.rank %arg1 : tensor<?x?xf32>
///     ```
class RankOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// tensor reshape operation
/// The `reshape` operation converts a tensor from one type to an equivalent
///     type with a provided shape. The source and destination types are compatible
///     if both have the same element type, same number of elements. The following
///     combinations are possible:
/// 
///     a. Source type is ranked or unranked. Shape argument has static size.
///     Result type is ranked.
/// 
///     ```mlir
///     // Reshape statically-shaped tensor.
///     %dst = tensor.reshape %src(%shape)
///              : (tensor<4x1xf32>, tensor<1xi32>) -> tensor<4xf32>
///     %dst0 = tensor.reshape %src(%shape0)
///              : (tensor<4x1xf32>, tensor<2xi32>) -> tensor<2x2xf32>
///     // Flatten unranked tensor.
///     %dst = tensor.reshape %src(%shape)
///              : (tensor<*xf32>, tensor<1xi32>) -> tensor<?xf32>
///     ```
/// 
///     b. Source type is ranked or unranked. Shape argument has dynamic size.
///     Result type is unranked.
/// 
///     ```mlir
///     // Reshape dynamically-shaped 1D tensor.
///     %dst = tensor.reshape %src(%shape)
///              : (tensor<?xf32>, tensor<?xi32>) -> tensor<*xf32>
///     // Reshape unranked tensor.
///     %dst = tensor.reshape %src(%shape)
///              : (tensor<*xf32>, tensor<?xi32>) -> tensor<*xf32>
///     ```
class ReshapeOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// scatter a tensor into a destination tensor at specified indices
/// The `scatter` operation inserts a `source` tensor into a `dest` tensor at
///     the given indices.
/// 
///     In its most general form, the tensor of indices specifies all the coordinates
///     of every element to insert (i.e. COO format, without the payload).
///     The indices are expected to be confined to coordinate values that fit the
///     range of the `dest` tensor, otherwise the behavior is undefined.
/// 
///     The leading dimensions of the index tensor must match that of the dest
///     tensor. The trailing dimensions of the dest tensor must match those of the
///     source tensor by omitting the dimensions specified in scatter_dims
///     (rank-reducing semantics) or setting them to `1` (rank-preserving semantics)
///     (see examples).
///     This convention allows an idiomatic specification and lowering of
///     "scattering multiple N-D slices into the dest tensor".
///     The result type must match the type of the dest tensor.
/// 
///     Note: in the examples below, we separate out the indexing part of the tensor
///     type by a whitespace for readability purposes.
/// 
///     Example:
/// 
///     ```mlir
///         // For each 1x2 triple of coordinates in %indices, insert the
///         // element (i.e. 0-D subset) at the coordinates triple in %dest.
///         //
///         %out = tensor.scatter %source into %dest[%indices]
///             scatter_dims([0, 1, 2]) unique :
///           (tensor<1x2x 1x1x1xf32>, tensor<4x4x4xf32>, tensor<1x2x 3xindex>)
///             -> tensor<4x4x4xf32>
/// 
///         // Note: source type may be further rank-reduced to tensor<1x2x f32>.
///     ```
/// 
///     A slice variant is provided to allow specifying insertion of whole tensor
///     slices into the `dest` tensor.
/// 
///     Example:
/// 
///     ```mlir
///         // For each 3 singleton of coordinates in %indices, insert the 2-D
///         // slice into %dest[*, %indices[...]:%indices[...] + 1, *] with the
///         // indices corresponding to the scatter_dims attribute specified by
///         // %indices.
///         //
///         %out = tensor.scatter %source into %dest[%indices] scatter_dims([1]) unique :
///           (tensor<3x 4x1x6xf32>, tensor<4x5x6xf32>, tensor<3x 1xindex>)
///             -> tensor<4x5x6xf32>
///     ```
/// 
///     The dimensions specified in the scatter_dims attribute are ones for which the
///     source tensor has size `1`.
///     I.e. if the dest type is `axbxcxd` and the coordinates are [1, 3], then
///     the source type suffix is `ax1xcx1`.
///     Scatter also allows rank-reducing semantics where the shape `ax1xcx1` can be
///     further simplified to `axc`.
/// 
///     The elemental type of the indices tensor can be any integer type.
///     In the absence of target-specific or problem specific information the default
///     type one should use is `index`.
/// 
///     This operation does not support unranked tensors.
/// 
///     A `unique` unit attribute must be be specified to indicate that the
///     coordinates are statically guaranteed to be unique at runtime. If coordinates
///     are not truly unique at runtime, the behavior is undefined.
/// 
///     Only full slices are meant to be supported by this op, if one desires
///     partial slices (e.g. strided windows) one should compose this op with other
///     tensor ops (e.g. tensor.insert_slice). This is to avoid a slippery slope of
///     complexity that would make the op unusable in practice.
/// 
///     At the tensor-level, the index tensor is specified in an AoS form (i.e.
///     coordinate tuple is the most minor). It is the responsibility of further
///     lowerings and bufferization to implement various concrete layouts.
/// 
///     Note: As currently specified, the operation must lower to an abstraction that
///     performs copies to the output tensor. This is because the buffer type system
///     is currently not rich enough to allow multiple non-contiguous views in the
///     same type. This is visible more clearly in a notional buffer version of the
///     op:
/// 
///     ```mlir
///         // memref<?x 4xf32> is a contiguous buffer of ?x4 elements, scatter into
///         // random dest slices must copy to the contiguous dest.
///         //
///         some_side_effecting_op_writing_into %source, ...: memref<3x 4xf32>
///         memref.scatter %source into %dest[%indices] scatter_dims([1]) unique :
///           (memref<3x 4xf32>, memref<?x 4xf32>, memref<?x 1xindex>)
/// 
///         // Nested buffer support in the producing op would allow writing directly
///         // into the dest buffer.
///         %v = some_nested_buffer_view_op %dest[%indices] scatter_dims([1]) unique :
///           memref<? x memref<4xf32>>
///         some_side_effecting_op_writing_into %v, ...: memref<? x memref<4xf32>>
///     ```
class ScatterOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// tensor splat or broadcast operation
/// Broadcast the operand to all elements of the result tensor.
/// 
///     An additional argument of type `index` must be provided for each dynamic
///     dimension present in the result type.
/// 
///     Example for a statically shaped tensor:
/// 
///     ```mlir
///     %s = arith.constant 1.0 : f32
///     %t = tensor.splat %s : tensor<8x16xf32>
///     ```
/// 
///     Example for a tensor containing dynamic dimensions:
/// 
///     ```mlir
///     // Broadcasts %s to a 3D dynamically shaped tensor, with %m and %n binding
///     // to dimensions 0 and 2 of the resulting tensor, respectively.
///     %m = arith.constant 10 : index
///     %n = arith.constant 30 : index
///     %t = tensor.splat %s[%m, %n] : tensor<?x20x?xf32>
///     ```
class SplatOp;

} // namespace mlir::tensor
namespace mlir::tensor {

/// Yield a value from a region
/// This operation is used to yield a single value from a within a region. It
///      is used to create dynamically sized tensors
///      (see `tensor.generate` and `tensor.pad` ops).
class YieldOp;

} // namespace mlir::tensor
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::BitcastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BitcastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BitcastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.bitcast", odsAttrs.getContext());
  }

  BitcastOpGenericAdaptorBase(BitcastOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class BitcastOpGenericAdaptor : public detail::BitcastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BitcastOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  BitcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BitcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : BitcastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BitcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BitcastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BitcastOpGenericAdaptor(RangeT values, const BitcastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BitcastOp, typename = std::enable_if_t<std::is_same_v<LateInst, BitcastOp>>>
  BitcastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BitcastOpAdaptor : public BitcastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BitcastOpGenericAdaptor::BitcastOpGenericAdaptor;
  BitcastOpAdaptor(BitcastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BitcastOp : public ::mlir::Op<BitcastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::CastOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BitcastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BitcastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.bitcast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::Value source);
  static BitcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::Value source);
  static BitcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static BitcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static BitcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BitcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BitcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BitcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BitcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static bool areCastCompatible(::mlir::TypeRange inputs, ::mlir::TypeRange outputs);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::BitcastOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::CastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.cast", odsAttrs.getContext());
  }

  CastOpGenericAdaptorBase(CastOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class CastOpGenericAdaptor : public detail::CastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CastOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  CastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CastOpGenericAdaptor(RangeT values, const CastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CastOp, typename = std::enable_if_t<std::is_same_v<LateInst, CastOp>>>
  CastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CastOpAdaptor : public CastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CastOpGenericAdaptor::CastOpGenericAdaptor;
  CastOpAdaptor(CastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CastOp : public ::mlir::Op<CastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::CastOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<CastOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<CastOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<CastOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.cast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::Value source);
  static CastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::Value source);
  static CastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static CastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static CastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static bool areCastCompatible(::mlir::TypeRange inputs, ::mlir::TypeRange outputs);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::CastOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::CollapseShapeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CollapseShapeOpGenericAdaptorBase {
public:
  struct Properties {
    using reassociationTy = ::mlir::ArrayAttr;
    reassociationTy reassociation;

    auto getReassociation() const {
      auto &propStorage = this->reassociation;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setReassociation(const ::mlir::ArrayAttr &propValue) {
      this->reassociation = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.reassociation == this->reassociation &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CollapseShapeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.collapse_shape", odsAttrs.getContext());
  }

  CollapseShapeOpGenericAdaptorBase(CollapseShapeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getReassociationAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().reassociation);
    return attr;
  }

  ::mlir::ArrayAttr getReassociation();
};

} // namespace detail
template <typename RangeT>
class CollapseShapeOpGenericAdaptor : public detail::CollapseShapeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CollapseShapeOpGenericAdaptorBase;
  static constexpr int odsIndex_src = 0;
public:
  CollapseShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CollapseShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CollapseShapeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CollapseShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CollapseShapeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CollapseShapeOpGenericAdaptor(RangeT values, const CollapseShapeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CollapseShapeOp, typename = std::enable_if_t<std::is_same_v<LateInst, CollapseShapeOp>>>
  CollapseShapeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSrc() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CollapseShapeOpAdaptor : public CollapseShapeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CollapseShapeOpGenericAdaptor::CollapseShapeOpGenericAdaptor;
  CollapseShapeOpAdaptor(CollapseShapeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CollapseShapeOp : public ::mlir::Op<CollapseShapeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CollapseShapeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CollapseShapeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_src = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<CollapseShapeOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<CollapseShapeOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<CollapseShapeOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("reassociation")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getReassociationAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getReassociationAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.collapse_shape");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getReassociationAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().reassociation);
  }

  ::mlir::ArrayAttr getReassociation();
  void setReassociationAttr(::mlir::ArrayAttr attr) {
    getProperties().reassociation = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static CollapseShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static CollapseShapeOp create(::mlir::ImplicitLocOpBuilder &builder, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value src, ArrayRef<ReassociationExprs> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static CollapseShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value src, ArrayRef<ReassociationExprs> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static CollapseShapeOp create(::mlir::ImplicitLocOpBuilder &builder, Value src, ArrayRef<ReassociationExprs> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static CollapseShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static CollapseShapeOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value src, ArrayRef<ReassociationExprs> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static CollapseShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value src, ArrayRef<ReassociationExprs> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static CollapseShapeOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value src, ArrayRef<ReassociationExprs> reassociation, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value src, ::mlir::ArrayAttr reassociation);
  static CollapseShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value src, ::mlir::ArrayAttr reassociation);
  static CollapseShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value src, ::mlir::ArrayAttr reassociation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::ArrayAttr reassociation);
  static CollapseShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::ArrayAttr reassociation);
  static CollapseShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::ArrayAttr reassociation);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CollapseShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CollapseShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CollapseShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CollapseShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  static StringRef getReassociationAttrStrName() { return "reassociation"; }
  SmallVector<AffineMap, 4> getReassociationMaps();
  SmallVector<ReassociationExprs, 4> getReassociationExprs();
  SmallVector<ReassociationIndices, 4> getReassociationIndices() {
    SmallVector<ReassociationIndices, 4> reassociationIndices;
    for (auto attr : getReassociation())
      reassociationIndices.push_back(llvm::to_vector<2>(
          llvm::map_range(::llvm::cast<ArrayAttr>(attr), [&](Attribute indexAttr) {
            return ::llvm::cast<IntegerAttr>(indexAttr).getInt();
          })));
    return reassociationIndices;
  }
  RankedTensorType getSrcType() {
    return ::llvm::cast<RankedTensorType>(getSrc().getType());
  }
  RankedTensorType getResultType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }

  static RankedTensorType
  inferCollapsedType(RankedTensorType type, ArrayRef<AffineMap> reassociation);
  static RankedTensorType
  inferCollapsedType(RankedTensorType type,
                     ArrayRef<ReassociationIndices> reassociation);
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::CollapseShapeOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::ConcatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConcatOpGenericAdaptorBase {
public:
  struct Properties {
    using dimTy = ::mlir::IntegerAttr;
    dimTy dim;

    auto getDim() const {
      auto &propStorage = this->dim;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setDim(const ::mlir::IntegerAttr &propValue) {
      this->dim = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dim == this->dim &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ConcatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.concat", odsAttrs.getContext());
  }

  ConcatOpGenericAdaptorBase(ConcatOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getDimAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().dim);
    return attr;
  }

  uint64_t getDim();
};

} // namespace detail
template <typename RangeT>
class ConcatOpGenericAdaptor : public detail::ConcatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConcatOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  ConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ConcatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConcatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConcatOpGenericAdaptor(RangeT values, const ConcatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConcatOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConcatOp>>>
  ConcatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ConcatOpAdaptor : public ConcatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConcatOpGenericAdaptor::ConcatOpGenericAdaptor;
  ConcatOpAdaptor(ConcatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConcatOp : public ::mlir::Op<ConcatOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConcatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConcatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ConcatOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ConcatOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ConcatOp>::getDefaultDialect;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<ConcatOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<ConcatOp>::reifyDimOfResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dim")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.concat");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getDimAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().dim);
  }

  uint64_t getDim();
  void setDimAttr(::mlir::IntegerAttr attr) {
    getProperties().dim = attr;
  }

  void setDim(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, int64_t dim, ValueRange inputs);
  static ConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, int64_t dim, ValueRange inputs);
  static ConcatOp create(::mlir::ImplicitLocOpBuilder &builder, int64_t dim, ValueRange inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::IntegerAttr dim, ::mlir::ValueRange inputs);
  static ConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::IntegerAttr dim, ::mlir::ValueRange inputs);
  static ConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::IntegerAttr dim, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr dim, ::mlir::ValueRange inputs);
  static ConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr dim, ::mlir::ValueRange inputs);
  static ConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr dim, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, uint64_t dim, ::mlir::ValueRange inputs);
  static ConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, uint64_t dim, ::mlir::ValueRange inputs);
  static ConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, uint64_t dim, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint64_t dim, ::mlir::ValueRange inputs);
  static ConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint64_t dim, ::mlir::ValueRange inputs);
  static ConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint64_t dim, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Helper to infer the concatenated result type for the given list of input
  // types, being concatenated along `dim`. Because concatenation can specify
  // more static information than can automatically be inferred,
  // InferTypeOpInterface is not used.
  static RankedTensorType inferResultType(int64_t dim, TypeRange inputTypes);

  RankedTensorType getResultType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }

  int64_t getRank() {
    return ::llvm::cast<RankedTensorType>(getResult().getType()).getRank();
  }

  // Method to decompose the operation into a sequence of insert_slices.
  FailureOr<SmallVector<Value>> decomposeOperation(OpBuilder &builder);
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::ConcatOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::DimOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DimOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DimOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.dim", odsAttrs.getContext());
  }

  DimOpGenericAdaptorBase(DimOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class DimOpGenericAdaptor : public detail::DimOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DimOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_index = 1;
public:
  DimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DimOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DimOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DimOpGenericAdaptor(RangeT values, const DimOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DimOp, typename = std::enable_if_t<std::is_same_v<LateInst, DimOp>>>
  DimOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  ValueT getIndex() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DimOpAdaptor : public DimOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DimOpGenericAdaptor::DimOpGenericAdaptor;
  DimOpAdaptor(DimOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DimOp : public ::mlir::Op<DimOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ShapedDimOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DimOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DimOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_index = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<DimOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<DimOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<DimOp>::getDefaultDialect;
  using ::mlir::InferIntRangeInterface::Trait<DimOp>::inferResultRanges;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.dim");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIndexMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, int64_t index);
  static DimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, int64_t index);
  static DimOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, int64_t index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::Value index);
  static DimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::Value index);
  static DimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::Value index);
  static DimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::Value index);
  static DimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value index);
  static DimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value index);
  static DimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  void inferResultRangesFromOptional(::llvm::ArrayRef<::mlir::IntegerValueRange> argRanges, ::mlir::SetIntLatticeFn setResultRanges);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// Helper function to get the index as a simple integer if it is constant.
  std::optional<int64_t> getConstantIndex();

  /// Interface method of ShapedDimOpInterface: Return the source tensor.
  Value getShapedValue() { return getSource(); }

  /// Interface method of ShapedDimOpInterface: Return the dimension.
  OpFoldResult getDimension() { return getIndex(); }

  /// Interface method for ConditionallySpeculatable.
  Speculation::Speculatability getSpeculatability();
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::DimOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::EmptyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EmptyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  EmptyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.empty", odsAttrs.getContext());
  }

  EmptyOpGenericAdaptorBase(EmptyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class EmptyOpGenericAdaptor : public detail::EmptyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EmptyOpGenericAdaptorBase;
  static constexpr int odsIndex_dynamicSizes = 0;
public:
  EmptyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EmptyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : EmptyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EmptyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EmptyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EmptyOpGenericAdaptor(RangeT values, const EmptyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EmptyOp, typename = std::enable_if_t<std::is_same_v<LateInst, EmptyOp>>>
  EmptyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDynamicSizes() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class EmptyOpAdaptor : public EmptyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EmptyOpGenericAdaptor::EmptyOpGenericAdaptor;
  EmptyOpAdaptor(EmptyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EmptyOp : public ::mlir::Op<EmptyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EmptyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EmptyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dynamicSizes = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<EmptyOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<EmptyOp>::reifyDimOfResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.empty");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDynamicSizes() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getDynamicSizesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<int64_t> staticShape, Type elementType, Attribute encoding = {});
  static EmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<int64_t> staticShape, Type elementType, Attribute encoding = {});
  static EmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<int64_t> staticShape, Type elementType, Attribute encoding = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<int64_t> staticShape, Type elementType, ValueRange dynamicSizes, Attribute encoding = {});
  static EmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<int64_t> staticShape, Type elementType, ValueRange dynamicSizes, Attribute encoding = {});
  static EmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<int64_t> staticShape, Type elementType, ValueRange dynamicSizes, Attribute encoding = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<OpFoldResult> sizes, Type elementType, Attribute encoding = {});
  static EmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<OpFoldResult> sizes, Type elementType, Attribute encoding = {});
  static EmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<OpFoldResult> sizes, Type elementType, Attribute encoding = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange dynamicSizes);
  static EmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange dynamicSizes);
  static EmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange dynamicSizes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  RankedTensorType getType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }

  // Return both static and dynamic sizes as a list of `OpFoldResult`.
  SmallVector<OpFoldResult> getMixedSizes();

  // Return the Value of the dynamic size of the tensor at dimension `idx`.
  // Asserts that the shape is dynamic at that `idx`.
  Value getDynamicSize(unsigned idx);
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::EmptyOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::ExpandShapeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExpandShapeOpGenericAdaptorBase {
public:
  struct Properties {
    using reassociationTy = ::mlir::ArrayAttr;
    reassociationTy reassociation;

    auto getReassociation() const {
      auto &propStorage = this->reassociation;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setReassociation(const ::mlir::ArrayAttr &propValue) {
      this->reassociation = propValue;
    }
    using static_output_shapeTy = ::mlir::DenseI64ArrayAttr;
    static_output_shapeTy static_output_shape;

    auto getStaticOutputShape() const {
      auto &propStorage = this->static_output_shape;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticOutputShape(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_output_shape = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.reassociation == this->reassociation &&
        rhs.static_output_shape == this->static_output_shape &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ExpandShapeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.expand_shape", odsAttrs.getContext());
  }

  ExpandShapeOpGenericAdaptorBase(ExpandShapeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getReassociationAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().reassociation);
    return attr;
  }

  ::mlir::ArrayAttr getReassociation();
  ::mlir::DenseI64ArrayAttr getStaticOutputShapeAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_output_shape);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticOutputShape();
};

} // namespace detail
template <typename RangeT>
class ExpandShapeOpGenericAdaptor : public detail::ExpandShapeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExpandShapeOpGenericAdaptorBase;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_output_shape = 1;
public:
  ExpandShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExpandShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExpandShapeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExpandShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExpandShapeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExpandShapeOpGenericAdaptor(RangeT values, const ExpandShapeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExpandShapeOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExpandShapeOp>>>
  ExpandShapeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSrc() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOutputShape() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ExpandShapeOpAdaptor : public ExpandShapeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExpandShapeOpGenericAdaptor::ExpandShapeOpGenericAdaptor;
  ExpandShapeOpAdaptor(ExpandShapeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExpandShapeOp : public ::mlir::Op<ExpandShapeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExpandShapeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExpandShapeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_output_shape = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ExpandShapeOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ExpandShapeOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ExpandShapeOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("reassociation"), ::llvm::StringRef("static_output_shape")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getReassociationAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getReassociationAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStaticOutputShapeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStaticOutputShapeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.expand_shape");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getOutputShape() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getOutputShapeMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getReassociationAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().reassociation);
  }

  ::mlir::ArrayAttr getReassociation();
  ::mlir::DenseI64ArrayAttr getStaticOutputShapeAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_output_shape);
  }

  ::llvm::ArrayRef<int64_t> getStaticOutputShape();
  void setReassociationAttr(::mlir::ArrayAttr attr) {
    getProperties().reassociation = attr;
  }

  void setStaticOutputShapeAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_output_shape = attr;
  }

  void setStaticOutputShape(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<OpFoldResult> outputShape);
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<OpFoldResult> outputShape);
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<OpFoldResult> outputShape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value src, ArrayRef<ReassociationIndices> reassociation);
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value src, ArrayRef<ReassociationIndices> reassociation);
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value src, ArrayRef<ReassociationIndices> reassociation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value src, ArrayRef<ReassociationExprs> reassociation);
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value src, ArrayRef<ReassociationExprs> reassociation);
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value src, ArrayRef<ReassociationExprs> reassociation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value src, ArrayRef<ReassociationExprs> reassociation, ArrayRef<OpFoldResult> outputShape);
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value src, ArrayRef<ReassociationExprs> reassociation, ArrayRef<OpFoldResult> outputShape);
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value src, ArrayRef<ReassociationExprs> reassociation, ArrayRef<OpFoldResult> outputShape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::mlir::DenseI64ArrayAttr static_output_shape);
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::mlir::DenseI64ArrayAttr static_output_shape);
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::mlir::DenseI64ArrayAttr static_output_shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::mlir::DenseI64ArrayAttr static_output_shape);
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::mlir::DenseI64ArrayAttr static_output_shape);
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::mlir::DenseI64ArrayAttr static_output_shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::llvm::ArrayRef<int64_t> static_output_shape);
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::llvm::ArrayRef<int64_t> static_output_shape);
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::llvm::ArrayRef<int64_t> static_output_shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::llvm::ArrayRef<int64_t> static_output_shape);
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::llvm::ArrayRef<int64_t> static_output_shape);
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::ArrayAttr reassociation, ::mlir::ValueRange output_shape, ::llvm::ArrayRef<int64_t> static_output_shape);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  static StringRef getReassociationAttrStrName() { return "reassociation"; }
  SmallVector<AffineMap, 4> getReassociationMaps();
  SmallVector<ReassociationExprs, 4> getReassociationExprs();
  SmallVector<ReassociationIndices, 4> getReassociationIndices() {
    SmallVector<ReassociationIndices, 4> reassociationIndices;
    for (auto attr : getReassociation())
      reassociationIndices.push_back(llvm::to_vector<2>(
          llvm::map_range(::llvm::cast<ArrayAttr>(attr), [&](Attribute indexAttr) {
            return ::llvm::cast<IntegerAttr>(indexAttr).getInt();
          })));
    return reassociationIndices;
  }
  RankedTensorType getSrcType() {
    return ::llvm::cast<RankedTensorType>(getSrc().getType());
  }
  RankedTensorType getResultType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }

  int64_t getCorrespondingSourceDim(int64_t resultDim);

  // Return output shape as mixes static/dynamic shapes.
  SmallVector<OpFoldResult> getMixedOutputShape();

  // Infer the output shape for a tensor.expand_shape when it is possible
  // to do so.
  static FailureOr<SmallVector<OpFoldResult>> inferOutputShape(
      OpBuilder &b, Location loc, RankedTensorType expandedType,
      ArrayRef<ReassociationIndices> reassociation,
      ArrayRef<OpFoldResult> inputShape);
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::ExpandShapeOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::ExtractOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtractOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ExtractOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.extract", odsAttrs.getContext());
  }

  ExtractOpGenericAdaptorBase(ExtractOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class ExtractOpGenericAdaptor : public detail::ExtractOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtractOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_indices = 1;
public:
  ExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExtractOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExtractOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExtractOpGenericAdaptor(RangeT values, const ExtractOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExtractOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExtractOp>>>
  ExtractOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTensor() {
    return (*getODSOperands(0).begin());
  }

  RangeT getIndices() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ExtractOpAdaptor : public ExtractOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExtractOpGenericAdaptor::ExtractOpGenericAdaptor;
  ExtractOpAdaptor(ExtractOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExtractOp : public ::mlir::Op<ExtractOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtractOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtractOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ExtractOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ExtractOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ExtractOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.extract");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getTensorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::ValueRange indices);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::ValueRange indices);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::ValueRange indices);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::ValueRange indices);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::ValueRange indices);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::ValueRange indices);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::ExtractOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::ExtractSliceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtractSliceOpGenericAdaptorBase {
public:
  struct Properties {
    using static_offsetsTy = ::mlir::DenseI64ArrayAttr;
    static_offsetsTy static_offsets;

    auto getStaticOffsets() const {
      auto &propStorage = this->static_offsets;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticOffsets(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_offsets = propValue;
    }
    using static_sizesTy = ::mlir::DenseI64ArrayAttr;
    static_sizesTy static_sizes;

    auto getStaticSizes() const {
      auto &propStorage = this->static_sizes;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticSizes(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_sizes = propValue;
    }
    using static_stridesTy = ::mlir::DenseI64ArrayAttr;
    static_stridesTy static_strides;

    auto getStaticStrides() const {
      auto &propStorage = this->static_strides;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticStrides(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_strides = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 4>;
    operandSegmentSizesTy operandSegmentSizes;
    ::llvm::ArrayRef<int32_t> getOperandSegmentSizes() const {
      auto &propStorage = this->operandSegmentSizes;
      return propStorage;
    }
    void setOperandSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->operandSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.static_offsets == this->static_offsets &&
        rhs.static_sizes == this->static_sizes &&
        rhs.static_strides == this->static_strides &&
        rhs.operandSegmentSizes == this->operandSegmentSizes &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ExtractSliceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.extract_slice", odsAttrs.getContext());
  }

  ExtractSliceOpGenericAdaptorBase(ExtractSliceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getStaticOffsetsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_offsets);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticOffsets();
  ::mlir::DenseI64ArrayAttr getStaticSizesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_sizes);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticSizes();
  ::mlir::DenseI64ArrayAttr getStaticStridesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_strides);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticStrides();
};

} // namespace detail
template <typename RangeT>
class ExtractSliceOpGenericAdaptor : public detail::ExtractSliceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtractSliceOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_offsets = 1;
  static constexpr int odsIndex_sizes = 2;
  static constexpr int odsIndex_strides = 3;
public:
  ExtractSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExtractSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExtractSliceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExtractSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ExtractSliceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExtractSliceOpGenericAdaptor(RangeT values, const ExtractSliceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExtractSliceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExtractSliceOp>>>
  ExtractSliceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOffsets() {
    return getODSOperands(1);
  }

  RangeT getSizes() {
    return getODSOperands(2);
  }

  RangeT getStrides() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ExtractSliceOpAdaptor : public ExtractSliceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExtractSliceOpGenericAdaptor::ExtractSliceOpGenericAdaptor;
  ExtractSliceOpAdaptor(ExtractSliceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExtractSliceOp : public ::mlir::Op<ExtractSliceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OffsetSizeAndStrideOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtractSliceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtractSliceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_offsets = 1;
  static constexpr int odsIndex_sizes = 2;
  static constexpr int odsIndex_strides = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ExtractSliceOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ExtractSliceOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ExtractSliceOp>::getDefaultDialect;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<ExtractSliceOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<ExtractSliceOp>::reifyDimOfResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("static_offsets"), ::llvm::StringRef("static_sizes"), ::llvm::StringRef("static_strides"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getStaticOffsetsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getStaticOffsetsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStaticSizesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStaticSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStaticStridesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStaticStridesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.extract_slice");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getOffsets() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getSizes() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getStrides() {
    return getODSOperands(3);
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getOffsetsMutable();
  ::mlir::MutableOperandRange getSizesMutable();
  ::mlir::MutableOperandRange getStridesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::DenseI64ArrayAttr getStaticOffsetsAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_offsets);
  }

  ::llvm::ArrayRef<int64_t> getStaticOffsets();
  ::mlir::DenseI64ArrayAttr getStaticSizesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_sizes);
  }

  ::llvm::ArrayRef<int64_t> getStaticSizes();
  ::mlir::DenseI64ArrayAttr getStaticStridesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_strides);
  }

  ::llvm::ArrayRef<int64_t> getStaticStrides();
  void setStaticOffsetsAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_offsets = attr;
  }

  void setStaticOffsets(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticSizesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_sizes = attr;
  }

  void setStaticSizes(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticStridesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_strides = attr;
  }

  void setStaticStrides(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, RankedTensorType resultType, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, RankedTensorType resultType, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, RankedTensorType resultType, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, RankedTensorType resultType, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, RankedTensorType resultType, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, RankedTensorType resultType, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, ArrayRef<Range> ranges, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, ArrayRef<Range> ranges, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, ArrayRef<Range> ranges, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, RankedTensorType resultType, Value source, ArrayRef<OpFoldResult> sizes, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, RankedTensorType resultType, Value source, ArrayRef<OpFoldResult> sizes, ArrayRef<NamedAttribute> attrs = {});
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, RankedTensorType resultType, Value source, ArrayRef<OpFoldResult> sizes, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Return the type of the base tensor operand.
  ::mlir::RankedTensorType getSourceType() {
    return ::llvm::cast<RankedTensorType>(getSource().getType());
  }

  /// Return the type of the result tensor.
  ::mlir::RankedTensorType getResultType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }

  /// Return the dynamic sizes for this subview operation if specified.
  ::mlir::Operation::operand_range getDynamicSizes() { return getSizes(); }

  /// Return the list of Range (i.e. offset, size, stride). Each
  /// Range entry contains either the dynamic value or a ConstantIndexOp
  /// constructed with `b` at location `loc`.
  ::mlir::SmallVector<::mlir::Range, 8> getOrCreateRanges(
      ::mlir::OpBuilder &b, ::mlir::Location loc) {
    return ::mlir::getOrCreateRanges(*this, b, loc);
  }

  /// The result of an extract_slice is always a tensor.
  // TODO: deprecate
  RankedTensorType getType() {
    return getResultType();
  }

  /// Compute the rank-reduction mask that can be applied to map the source
  /// tensor type to the result tensor type by dropping unit dims.
  std::optional<llvm::SmallDenseSet<unsigned>>
  computeRankReductionMask() {
    return ::mlir::computeRankReductionMask(getSourceType().getShape(),
                                            getType().getShape());
  };

  /// An extract_slice result type can be inferred, when it is not
  /// rank-reduced, from the source type and the static representation of
  /// sizes. Special sentinels encode the dynamic case.
  static RankedTensorType inferResultType(
    RankedTensorType sourceTensorType,
    ArrayRef<int64_t> staticSizes);
  static RankedTensorType inferResultType(
    RankedTensorType sourceTensorType,
    ArrayRef<OpFoldResult> staticSizes);

  /// If the rank is reduced (i.e. the desiredResultRank is smaller than the
  /// number of sizes), drop as many size 1 as needed to produce an inferred type
  /// with the desired rank.
  ///
  /// Note that there may be multiple ways to compute this rank-reduced type:
  ///   e.g. 1x6x1 can rank-reduce to either 1x6 or 6x1 2-D tensors.
  ///
  /// To disambiguate, this function always drops the first 1 sizes occurrences.
  static RankedTensorType inferCanonicalRankReducedResultType(
    unsigned resultRank,
    RankedTensorType sourceRankedTensorType,
    ArrayRef<int64_t> staticSizes);
  static RankedTensorType inferCanonicalRankReducedResultType(
    unsigned resultRank,
    RankedTensorType sourceRankedTensorType,
    ArrayRef<OpFoldResult> staticSizes);

  /// Return the expected rank of each of the`static_offsets`, `static_sizes`
  /// and `static_strides` attributes.
  std::array<unsigned, 3> getArrayAttrMaxRanks() {
    unsigned rank = getSourceType().getRank();
    return {rank, rank, rank};
  }

  /// Return the number of leading operands before the `offsets`, `sizes` and
  /// and `strides` operands.
  static unsigned getOffsetSizeAndStrideStartOperandIndex() { return 1; }

  /// Return the dimensions of the source that are dropped in the
  /// result when the result is rank-reduced.
  llvm::SmallBitVector getDroppedDims();

  /// Given a `value`, asserted to be of RankedTensorType, build an
  /// ExtractSliceOp that results in a rank-reducing extract to the desired
  /// tensor shape and return the new value created.
  /// If the shape of `value` is already the `desiredShape`, just return
  /// `value`.
  /// If the shape of `value` cannot be rank-reduced to `desiredShape`, fail.
  static FailureOr<Value> rankReduceIfNeeded(
    OpBuilder &b, Location loc, Value value, ArrayRef<int64_t> desiredShape);
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::ExtractSliceOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::FromElementsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FromElementsOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FromElementsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.from_elements", odsAttrs.getContext());
  }

  FromElementsOpGenericAdaptorBase(FromElementsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class FromElementsOpGenericAdaptor : public detail::FromElementsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FromElementsOpGenericAdaptorBase;
  static constexpr int odsIndex_elements = 0;
public:
  FromElementsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FromElementsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : FromElementsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FromElementsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FromElementsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FromElementsOpGenericAdaptor(RangeT values, const FromElementsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FromElementsOp, typename = std::enable_if_t<std::is_same_v<LateInst, FromElementsOp>>>
  FromElementsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getElements() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FromElementsOpAdaptor : public FromElementsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FromElementsOpGenericAdaptor::FromElementsOpGenericAdaptor;
  FromElementsOpAdaptor(FromElementsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FromElementsOp : public ::mlir::Op<FromElementsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FromElementsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FromElementsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_elements = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<FromElementsOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<FromElementsOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<FromElementsOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.from_elements");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getElements() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getElementsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange elements);
  static FromElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange elements);
  static FromElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange elements);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange elements);
  static FromElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange elements);
  static FromElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange elements);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FromElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FromElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FromElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FromElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::FromElementsOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::GatherOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GatherOpGenericAdaptorBase {
public:
  struct Properties {
    using gather_dimsTy = ::mlir::DenseI64ArrayAttr;
    gather_dimsTy gather_dims;

    auto getGatherDims() const {
      auto &propStorage = this->gather_dims;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setGatherDims(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->gather_dims = propValue;
    }
    using uniqueTy = ::mlir::UnitAttr;
    uniqueTy unique;

    auto getUnique() const {
      auto &propStorage = this->unique;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setUnique(const ::mlir::UnitAttr &propValue) {
      this->unique = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.gather_dims == this->gather_dims &&
        rhs.unique == this->unique &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GatherOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.gather", odsAttrs.getContext());
  }

  GatherOpGenericAdaptorBase(GatherOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getGatherDimsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().gather_dims);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getGatherDims();
  ::mlir::UnitAttr getUniqueAttr();
  bool getUnique();
};

} // namespace detail
template <typename RangeT>
class GatherOpGenericAdaptor : public detail::GatherOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GatherOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_indices = 1;
public:
  GatherOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GatherOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GatherOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GatherOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GatherOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GatherOpGenericAdaptor(RangeT values, const GatherOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GatherOp, typename = std::enable_if_t<std::is_same_v<LateInst, GatherOp>>>
  GatherOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  ValueT getIndices() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GatherOpAdaptor : public GatherOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GatherOpGenericAdaptor::GatherOpGenericAdaptor;
  GatherOpAdaptor(GatherOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GatherOp : public ::mlir::Op<GatherOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GatherOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GatherOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<GatherOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GatherOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GatherOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("gather_dims"), ::llvm::StringRef("unique")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGatherDimsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGatherDimsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUniqueAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUniqueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.gather");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getIndices() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIndicesMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::DenseI64ArrayAttr getGatherDimsAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().gather_dims);
  }

  ::llvm::ArrayRef<int64_t> getGatherDims();
  ::mlir::UnitAttr getUniqueAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().unique);
  }

  bool getUnique();
  void setGatherDimsAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().gather_dims = attr;
  }

  void setGatherDims(::llvm::ArrayRef<int64_t> attrValue);
  void setUniqueAttr(::mlir::UnitAttr attr) {
    getProperties().unique = attr;
  }

  void setUnique(bool attrValue);
  ::mlir::Attribute removeUniqueAttr() {
      auto attr = getProperties().unique;
      getProperties().unique = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr gather_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr gather_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr gather_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr gather_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr gather_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr gather_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> gather_dims, /*optional*/bool unique = false);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> gather_dims, /*optional*/bool unique = false);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> gather_dims, /*optional*/bool unique = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> gather_dims, /*optional*/bool unique = false);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> gather_dims, /*optional*/bool unique = false);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> gather_dims, /*optional*/bool unique = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // TODO: InferTypeOpInterface once enough confidence is built with
  // tensor<tensor> and its lowering to memref<memref>.
  static RankedTensorType inferResultType(RankedTensorType sourceType,
                                          RankedTensorType indicesType,
                                          ArrayRef<int64_t> gatherDims,
                                          bool rankReduced);
  RankedTensorType getIndicesType() {
    return ::llvm::cast<RankedTensorType>(getIndices().getType());
  }
  RankedTensorType getSourceType() {
    return ::llvm::cast<RankedTensorType>(getSource().getType());
  }
  RankedTensorType getResultType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::GatherOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::GenerateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GenerateOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GenerateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.generate", odsAttrs.getContext());
  }

  GenerateOpGenericAdaptorBase(GenerateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class GenerateOpGenericAdaptor : public detail::GenerateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GenerateOpGenericAdaptorBase;
  static constexpr int odsIndex_dynamicExtents = 0;
public:
  GenerateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GenerateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GenerateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GenerateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GenerateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GenerateOpGenericAdaptor(RangeT values, const GenerateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GenerateOp, typename = std::enable_if_t<std::is_same_v<LateInst, GenerateOp>>>
  GenerateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDynamicExtents() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GenerateOpAdaptor : public GenerateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GenerateOpGenericAdaptor::GenerateOpGenericAdaptor;
  GenerateOpAdaptor(GenerateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GenerateOp : public ::mlir::Op<GenerateOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<mlir::tensor::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::ReifyRankedShapedTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GenerateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GenerateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dynamicExtents = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<GenerateOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GenerateOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GenerateOp>::getDefaultDialect;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<GenerateOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<GenerateOp>::reifyDimOfResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.generate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDynamicExtents() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getDynamicExtentsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  ::mlir::Region &getBody() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultTy, ValueRange dynamicExtents, function_ref<void(OpBuilder &, Location, ValueRange)> odsArg2);
  static GenerateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultTy, ValueRange dynamicExtents, function_ref<void(OpBuilder &, Location, ValueRange)> odsArg2);
  static GenerateOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultTy, ValueRange dynamicExtents, function_ref<void(OpBuilder &, Location, ValueRange)> odsArg2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange dynamicExtents);
  static GenerateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange dynamicExtents);
  static GenerateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange dynamicExtents);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GenerateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GenerateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GenerateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GenerateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::GenerateOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::InsertOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InsertOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  InsertOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.insert", odsAttrs.getContext());
  }

  InsertOpGenericAdaptorBase(InsertOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class InsertOpGenericAdaptor : public detail::InsertOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InsertOpGenericAdaptorBase;
  static constexpr int odsIndex_scalar = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_indices = 2;
public:
  InsertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InsertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : InsertOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InsertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InsertOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InsertOpGenericAdaptor(RangeT values, const InsertOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InsertOp, typename = std::enable_if_t<std::is_same_v<LateInst, InsertOp>>>
  InsertOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getScalar() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDest() {
    return (*getODSOperands(1).begin());
  }

  RangeT getIndices() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class InsertOpAdaptor : public InsertOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InsertOpGenericAdaptor::InsertOpGenericAdaptor;
  InsertOpAdaptor(InsertOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InsertOp : public ::mlir::Op<InsertOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InsertOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InsertOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_scalar = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_indices = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<InsertOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<InsertOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<InsertOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.insert");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getScalar() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getScalarMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value scalar, ::mlir::Value dest, ::mlir::ValueRange indices);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value scalar, ::mlir::Value dest, ::mlir::ValueRange indices);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value scalar, ::mlir::Value dest, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value scalar, ::mlir::Value dest, ::mlir::ValueRange indices);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value scalar, ::mlir::Value dest, ::mlir::ValueRange indices);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value scalar, ::mlir::Value dest, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value scalar, ::mlir::Value dest, ::mlir::ValueRange indices);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value scalar, ::mlir::Value dest, ::mlir::ValueRange indices);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value scalar, ::mlir::Value dest, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  MutableOperandRange getDpsInitsMutable() { return getDestMutable(); }
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::InsertOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::InsertSliceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InsertSliceOpGenericAdaptorBase {
public:
  struct Properties {
    using static_offsetsTy = ::mlir::DenseI64ArrayAttr;
    static_offsetsTy static_offsets;

    auto getStaticOffsets() const {
      auto &propStorage = this->static_offsets;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticOffsets(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_offsets = propValue;
    }
    using static_sizesTy = ::mlir::DenseI64ArrayAttr;
    static_sizesTy static_sizes;

    auto getStaticSizes() const {
      auto &propStorage = this->static_sizes;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticSizes(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_sizes = propValue;
    }
    using static_stridesTy = ::mlir::DenseI64ArrayAttr;
    static_stridesTy static_strides;

    auto getStaticStrides() const {
      auto &propStorage = this->static_strides;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticStrides(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_strides = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 5>;
    operandSegmentSizesTy operandSegmentSizes;
    ::llvm::ArrayRef<int32_t> getOperandSegmentSizes() const {
      auto &propStorage = this->operandSegmentSizes;
      return propStorage;
    }
    void setOperandSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->operandSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.static_offsets == this->static_offsets &&
        rhs.static_sizes == this->static_sizes &&
        rhs.static_strides == this->static_strides &&
        rhs.operandSegmentSizes == this->operandSegmentSizes &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  InsertSliceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.insert_slice", odsAttrs.getContext());
  }

  InsertSliceOpGenericAdaptorBase(InsertSliceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getStaticOffsetsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_offsets);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticOffsets();
  ::mlir::DenseI64ArrayAttr getStaticSizesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_sizes);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticSizes();
  ::mlir::DenseI64ArrayAttr getStaticStridesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_strides);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticStrides();
};

} // namespace detail
template <typename RangeT>
class InsertSliceOpGenericAdaptor : public detail::InsertSliceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InsertSliceOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_offsets = 2;
  static constexpr int odsIndex_sizes = 3;
  static constexpr int odsIndex_strides = 4;
public:
  InsertSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InsertSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : InsertSliceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InsertSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : InsertSliceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InsertSliceOpGenericAdaptor(RangeT values, const InsertSliceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InsertSliceOp, typename = std::enable_if_t<std::is_same_v<LateInst, InsertSliceOp>>>
  InsertSliceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDest() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOffsets() {
    return getODSOperands(2);
  }

  RangeT getSizes() {
    return getODSOperands(3);
  }

  RangeT getStrides() {
    return getODSOperands(4);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class InsertSliceOpAdaptor : public InsertSliceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InsertSliceOpGenericAdaptor::InsertSliceOpGenericAdaptor;
  InsertSliceOpAdaptor(InsertSliceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InsertSliceOp : public ::mlir::Op<InsertSliceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OffsetSizeAndStrideOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InsertSliceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InsertSliceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_offsets = 2;
  static constexpr int odsIndex_sizes = 3;
  static constexpr int odsIndex_strides = 4;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<InsertSliceOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<InsertSliceOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<InsertSliceOp>::getDefaultDialect;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<InsertSliceOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<InsertSliceOp>::reifyDimOfResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("static_offsets"), ::llvm::StringRef("static_sizes"), ::llvm::StringRef("static_strides"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getStaticOffsetsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getStaticOffsetsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStaticSizesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStaticSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStaticStridesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStaticStridesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.insert_slice");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getOffsets() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getSizes() {
    return getODSOperands(3);
  }

  ::mlir::Operation::operand_range getStrides() {
    return getODSOperands(4);
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getOffsetsMutable();
  ::mlir::MutableOperandRange getSizesMutable();
  ::mlir::MutableOperandRange getStridesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::DenseI64ArrayAttr getStaticOffsetsAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_offsets);
  }

  ::llvm::ArrayRef<int64_t> getStaticOffsets();
  ::mlir::DenseI64ArrayAttr getStaticSizesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_sizes);
  }

  ::llvm::ArrayRef<int64_t> getStaticSizes();
  ::mlir::DenseI64ArrayAttr getStaticStridesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_strides);
  }

  ::llvm::ArrayRef<int64_t> getStaticStrides();
  void setStaticOffsetsAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_offsets = attr;
  }

  void setStaticOffsets(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticSizesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_sizes = attr;
  }

  void setStaticSizes(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticStridesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_strides = attr;
  }

  void setStaticStrides(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value dest, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value dest, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value dest, ArrayRef<Range> ranges, ArrayRef<NamedAttribute> attrs = {});
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ArrayRef<Range> ranges, ArrayRef<NamedAttribute> attrs = {});
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ArrayRef<Range> ranges, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value dest, ArrayRef<OpFoldResult> sizes, ArrayRef<NamedAttribute> attrs = {});
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ArrayRef<OpFoldResult> sizes, ArrayRef<NamedAttribute> attrs = {});
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ArrayRef<OpFoldResult> sizes, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Return the type of the base tensor operand.
  ::mlir::RankedTensorType getSourceType() {
    return ::llvm::cast<RankedTensorType>(getSource().getType());
  }

  /// Return the type of the result tensor.
  ::mlir::RankedTensorType getResultType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }

  /// Return the dynamic sizes for this subview operation if specified.
  ::mlir::Operation::operand_range getDynamicSizes() { return getSizes(); }

  /// Return the list of Range (i.e. offset, size, stride). Each
  /// Range entry contains either the dynamic value or a ConstantIndexOp
  /// constructed with `b` at location `loc`.
  ::mlir::SmallVector<::mlir::Range, 8> getOrCreateRanges(
      ::mlir::OpBuilder &b, ::mlir::Location loc) {
    return ::mlir::getOrCreateRanges(*this, b, loc);
  }

  /// The result of a insert_slice is always a tensor.
  // TODO: Deprecate this method.
  RankedTensorType getType() {
    return getResultType();
  }

  /// The `dest` type is the same as the result type.
  RankedTensorType getDestType() {
    return getResultType();
  }

  /// Return the expected rank of each of the`static_offsets`, `static_sizes`
  /// and `static_strides` attributes.
  std::array<unsigned, 3> getArrayAttrMaxRanks() {
    unsigned rank = getResultType().getRank();
    return {rank, rank, rank};
  }

  /// Return the dimensions of the dest that are omitted to insert a source
  /// when the result is rank-extended.
  llvm::SmallBitVector getDroppedDims();

  /// Return the number of leading operands before the `offsets`, `sizes` and
  /// and `strides` operands.
  static unsigned getOffsetSizeAndStrideStartOperandIndex() { return 2; }

  MutableOperandRange getDpsInitsMutable() { return getDestMutable(); }
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::InsertSliceOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::PadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PadOpGenericAdaptorBase {
public:
  struct Properties {
    using nofoldTy = ::mlir::UnitAttr;
    nofoldTy nofold;

    auto getNofold() const {
      auto &propStorage = this->nofold;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNofold(const ::mlir::UnitAttr &propValue) {
      this->nofold = propValue;
    }
    using static_highTy = ::mlir::DenseI64ArrayAttr;
    static_highTy static_high;

    auto getStaticHigh() const {
      auto &propStorage = this->static_high;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticHigh(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_high = propValue;
    }
    using static_lowTy = ::mlir::DenseI64ArrayAttr;
    static_lowTy static_low;

    auto getStaticLow() const {
      auto &propStorage = this->static_low;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticLow(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_low = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 3>;
    operandSegmentSizesTy operandSegmentSizes;
    ::llvm::ArrayRef<int32_t> getOperandSegmentSizes() const {
      auto &propStorage = this->operandSegmentSizes;
      return propStorage;
    }
    void setOperandSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->operandSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.nofold == this->nofold &&
        rhs.static_high == this->static_high &&
        rhs.static_low == this->static_low &&
        rhs.operandSegmentSizes == this->operandSegmentSizes &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.pad", odsAttrs.getContext());
  }

  PadOpGenericAdaptorBase(PadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getStaticLowAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_low);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticLow();
  ::mlir::DenseI64ArrayAttr getStaticHighAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_high);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticHigh();
  ::mlir::UnitAttr getNofoldAttr();
  bool getNofold();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class PadOpGenericAdaptor : public detail::PadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PadOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_low = 1;
  static constexpr int odsIndex_high = 2;
public:
  PadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : PadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PadOpGenericAdaptor(RangeT values, const PadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PadOp, typename = std::enable_if_t<std::is_same_v<LateInst, PadOp>>>
  PadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  RangeT getLow() {
    return getODSOperands(1);
  }

  RangeT getHigh() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PadOpAdaptor : public PadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PadOpGenericAdaptor::PadOpGenericAdaptor;
  PadOpAdaptor(PadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PadOp : public ::mlir::Op<PadOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<mlir::tensor::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_low = 1;
  static constexpr int odsIndex_high = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<PadOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<PadOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<PadOp>::getDefaultDialect;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<PadOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<PadOp>::reifyDimOfResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("nofold"), ::llvm::StringRef("static_high"), ::llvm::StringRef("static_low"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNofoldAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNofoldAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStaticHighAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStaticHighAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStaticLowAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStaticLowAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.pad");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getLow() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getHigh() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getLowMutable();
  ::mlir::MutableOperandRange getHighMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  ::mlir::Region &getRegion() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::DenseI64ArrayAttr getStaticLowAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_low);
  }

  ::llvm::ArrayRef<int64_t> getStaticLow();
  ::mlir::DenseI64ArrayAttr getStaticHighAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_high);
  }

  ::llvm::ArrayRef<int64_t> getStaticHigh();
  ::mlir::UnitAttr getNofoldAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nofold);
  }

  bool getNofold();
  void setStaticLowAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_low = attr;
  }

  void setStaticLow(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticHighAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_high = attr;
  }

  void setStaticHigh(::llvm::ArrayRef<int64_t> attrValue);
  void setNofoldAttr(::mlir::UnitAttr attr) {
    getProperties().nofold = attr;
  }

  void setNofold(bool attrValue);
  ::mlir::Attribute removeNofoldAttr() {
      auto attr = getProperties().nofold;
      getProperties().nofold = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value source, ArrayRef<int64_t> staticLow, ArrayRef<int64_t> staticHigh, ValueRange low, ValueRange high, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static PadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value source, ArrayRef<int64_t> staticLow, ArrayRef<int64_t> staticHigh, ValueRange low, ValueRange high, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static PadOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value source, ArrayRef<int64_t> staticLow, ArrayRef<int64_t> staticHigh, ValueRange low, ValueRange high, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value source, ValueRange low, ValueRange high, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static PadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value source, ValueRange low, ValueRange high, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static PadOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value source, ValueRange low, ValueRange high, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value source, ArrayRef<OpFoldResult> low, ArrayRef<OpFoldResult> high, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static PadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value source, ArrayRef<OpFoldResult> low, ArrayRef<OpFoldResult> high, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static PadOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value source, ArrayRef<OpFoldResult> low, ArrayRef<OpFoldResult> high, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value source, ArrayRef<OpFoldResult> low, ArrayRef<OpFoldResult> high, Value constantPadValue, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static PadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value source, ArrayRef<OpFoldResult> low, ArrayRef<OpFoldResult> high, Value constantPadValue, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static PadOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value source, ArrayRef<OpFoldResult> low, ArrayRef<OpFoldResult> high, Value constantPadValue, bool nofold = false, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::mlir::DenseI64ArrayAttr static_low, ::mlir::DenseI64ArrayAttr static_high, /*optional*/::mlir::UnitAttr nofold = nullptr);
  static PadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::mlir::DenseI64ArrayAttr static_low, ::mlir::DenseI64ArrayAttr static_high, /*optional*/::mlir::UnitAttr nofold = nullptr);
  static PadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::mlir::DenseI64ArrayAttr static_low, ::mlir::DenseI64ArrayAttr static_high, /*optional*/::mlir::UnitAttr nofold = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::mlir::DenseI64ArrayAttr static_low, ::mlir::DenseI64ArrayAttr static_high, /*optional*/::mlir::UnitAttr nofold = nullptr);
  static PadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::mlir::DenseI64ArrayAttr static_low, ::mlir::DenseI64ArrayAttr static_high, /*optional*/::mlir::UnitAttr nofold = nullptr);
  static PadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::mlir::DenseI64ArrayAttr static_low, ::mlir::DenseI64ArrayAttr static_high, /*optional*/::mlir::UnitAttr nofold = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::llvm::ArrayRef<int64_t> static_low, ::llvm::ArrayRef<int64_t> static_high, /*optional*/bool nofold = false);
  static PadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::llvm::ArrayRef<int64_t> static_low, ::llvm::ArrayRef<int64_t> static_high, /*optional*/bool nofold = false);
  static PadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::llvm::ArrayRef<int64_t> static_low, ::llvm::ArrayRef<int64_t> static_high, /*optional*/bool nofold = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::llvm::ArrayRef<int64_t> static_low, ::llvm::ArrayRef<int64_t> static_high, /*optional*/bool nofold = false);
  static PadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::llvm::ArrayRef<int64_t> static_low, ::llvm::ArrayRef<int64_t> static_high, /*optional*/bool nofold = false);
  static PadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange low, ::mlir::ValueRange high, ::llvm::ArrayRef<int64_t> static_low, ::llvm::ArrayRef<int64_t> static_high, /*optional*/bool nofold = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  static StringRef getStaticLowAttrStrName() {
    return "static_low";
  }

  static StringRef getStaticHighAttrStrName() {
    return "static_high";
  }

  RankedTensorType getSourceType() {
    return ::llvm::cast<RankedTensorType>(getSource().getType());
  }
  RankedTensorType getResultType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }

  // Infer the shape of the result tensor given the type of the source tensor
  // and paddings. Known result dimensions that cannot necessarily be inferred
  // from low/high padding sizes can be optionally specified. Those will be
  // considered when computing the result type.
  static RankedTensorType inferResultType(
                              RankedTensorType sourceType,
                              ArrayRef<int64_t> staticLow,
                              ArrayRef<int64_t> staticHigh,
                              ArrayRef<int64_t> resultShape = {});

  // Return the pad value if it is a constant. Return null value otherwise.
  Value getConstantPaddingValue();

  // Return a vector of all the static or dynamic values (low/high padding) of
  // the op.
  inline SmallVector<OpFoldResult> getMixedPadImpl(ArrayRef<int64_t> staticAttrs,
                                                   ValueRange values) {
    Builder builder(*this);
    SmallVector<OpFoldResult> res;
    unsigned numDynamic = 0;
    unsigned count = staticAttrs.size();
    for (unsigned idx = 0; idx < count; ++idx) {
      if (ShapedType::isDynamic(staticAttrs[idx]))
        res.push_back(getAsOpFoldResult(values[numDynamic++]));
      else
        res.push_back(builder.getI64IntegerAttr(staticAttrs[idx]));
    }
    return res;
  }
  SmallVector<OpFoldResult> getMixedLowPad() {
    return getMixedPadImpl(getStaticLow(), getLow());
  }
  SmallVector<OpFoldResult> getMixedHighPad() {
    return getMixedPadImpl(getStaticHigh(), getHigh());
  }
  // Return true if low padding is guaranteed to be 0.
  bool hasZeroLowPad() {
    return llvm::all_of(getMixedLowPad(), [](OpFoldResult ofr) {
      return getConstantIntValue(ofr) == static_cast<int64_t>(0);
    });
  }
  // Return true if high padding is guaranteed to be 0.
  bool hasZeroHighPad() {
    return llvm::all_of(getMixedHighPad(), [](OpFoldResult ofr) {
      return getConstantIntValue(ofr) == static_cast<int64_t>(0);
    });
  }
  /// Return the dimensions with a non-zero low or high padding.
  llvm::SmallBitVector getPaddedDims();
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::PadOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::ParallelInsertSliceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ParallelInsertSliceOpGenericAdaptorBase {
public:
  struct Properties {
    using static_offsetsTy = ::mlir::DenseI64ArrayAttr;
    static_offsetsTy static_offsets;

    auto getStaticOffsets() const {
      auto &propStorage = this->static_offsets;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticOffsets(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_offsets = propValue;
    }
    using static_sizesTy = ::mlir::DenseI64ArrayAttr;
    static_sizesTy static_sizes;

    auto getStaticSizes() const {
      auto &propStorage = this->static_sizes;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticSizes(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_sizes = propValue;
    }
    using static_stridesTy = ::mlir::DenseI64ArrayAttr;
    static_stridesTy static_strides;

    auto getStaticStrides() const {
      auto &propStorage = this->static_strides;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticStrides(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_strides = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 5>;
    operandSegmentSizesTy operandSegmentSizes;
    ::llvm::ArrayRef<int32_t> getOperandSegmentSizes() const {
      auto &propStorage = this->operandSegmentSizes;
      return propStorage;
    }
    void setOperandSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->operandSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.static_offsets == this->static_offsets &&
        rhs.static_sizes == this->static_sizes &&
        rhs.static_strides == this->static_strides &&
        rhs.operandSegmentSizes == this->operandSegmentSizes &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ParallelInsertSliceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.parallel_insert_slice", odsAttrs.getContext());
  }

  ParallelInsertSliceOpGenericAdaptorBase(ParallelInsertSliceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getStaticOffsetsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_offsets);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticOffsets();
  ::mlir::DenseI64ArrayAttr getStaticSizesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_sizes);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticSizes();
  ::mlir::DenseI64ArrayAttr getStaticStridesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_strides);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticStrides();
};

} // namespace detail
template <typename RangeT>
class ParallelInsertSliceOpGenericAdaptor : public detail::ParallelInsertSliceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ParallelInsertSliceOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_offsets = 2;
  static constexpr int odsIndex_sizes = 3;
  static constexpr int odsIndex_strides = 4;
public:
  ParallelInsertSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ParallelInsertSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ParallelInsertSliceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ParallelInsertSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ParallelInsertSliceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ParallelInsertSliceOpGenericAdaptor(RangeT values, const ParallelInsertSliceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ParallelInsertSliceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ParallelInsertSliceOp>>>
  ParallelInsertSliceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDest() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOffsets() {
    return getODSOperands(2);
  }

  RangeT getSizes() {
    return getODSOperands(3);
  }

  RangeT getStrides() {
    return getODSOperands(4);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ParallelInsertSliceOpAdaptor : public ParallelInsertSliceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ParallelInsertSliceOpGenericAdaptor::ParallelInsertSliceOpGenericAdaptor;
  ParallelInsertSliceOpAdaptor(ParallelInsertSliceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ParallelInsertSliceOp : public ::mlir::Op<ParallelInsertSliceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OffsetSizeAndStrideOpInterface::Trait, ::mlir::ParallelCombiningOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ParallelInsertSliceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ParallelInsertSliceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_offsets = 2;
  static constexpr int odsIndex_sizes = 3;
  static constexpr int odsIndex_strides = 4;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("static_offsets"), ::llvm::StringRef("static_sizes"), ::llvm::StringRef("static_strides"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getStaticOffsetsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getStaticOffsetsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStaticSizesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStaticSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStaticStridesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStaticStridesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.parallel_insert_slice");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getOffsets() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getSizes() {
    return getODSOperands(3);
  }

  ::mlir::Operation::operand_range getStrides() {
    return getODSOperands(4);
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getOffsetsMutable();
  ::mlir::MutableOperandRange getSizesMutable();
  ::mlir::MutableOperandRange getStridesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::DenseI64ArrayAttr getStaticOffsetsAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_offsets);
  }

  ::llvm::ArrayRef<int64_t> getStaticOffsets();
  ::mlir::DenseI64ArrayAttr getStaticSizesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_sizes);
  }

  ::llvm::ArrayRef<int64_t> getStaticSizes();
  ::mlir::DenseI64ArrayAttr getStaticStridesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_strides);
  }

  ::llvm::ArrayRef<int64_t> getStaticStrides();
  void setStaticOffsetsAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_offsets = attr;
  }

  void setStaticOffsets(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticSizesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_sizes = attr;
  }

  void setStaticSizes(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticStridesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_strides = attr;
  }

  void setStaticStrides(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value dest, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static ParallelInsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static ParallelInsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value dest, ArrayRef<Range> ranges, ArrayRef<NamedAttribute> attrs = {});
  static ParallelInsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ArrayRef<Range> ranges, ArrayRef<NamedAttribute> attrs = {});
  static ParallelInsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ArrayRef<Range> ranges, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value dest, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static ParallelInsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value dest, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static ParallelInsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value dest, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ParallelInsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ParallelInsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ParallelInsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ParallelInsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ParallelInsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ParallelInsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ParallelInsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ParallelInsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ParallelInsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ParallelInsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ParallelInsertSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ParallelInsertSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::MutableOperandRange getUpdatedDestinations();
  ::mlir::Operation*getIteratingParent();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  Type yieldedType() { return getDest().getType(); }

  RankedTensorType getSourceType() {
    return ::llvm::cast<RankedTensorType>(getSource().getType());
  }

  RankedTensorType getDestType() {
    return ::llvm::cast<RankedTensorType>(getDest().getType());
  }

  InParallelOpInterface getParallelCombiningParent() {
    return dyn_cast<InParallelOpInterface>(
      getOperation()->getParentOp());
  }

  /// Return the expected rank of each of the `static_offsets`, `static_sizes`
  /// and `static_strides` attributes.
  std::array<unsigned, 3> getArrayAttrMaxRanks() {
    unsigned rank = getDestType().getRank();
    return {rank, rank, rank};
  }

  /// Return the number of leading operands before `offsets`, `sizes` and
  /// `strides` operands.
  static unsigned getOffsetSizeAndStrideStartOperandIndex() { return 1; }

  /// Return the OpResult of the enclosing ForallOp that is
  /// corresponding to this ParallelInsertSliceOp.
  OpResult getTiedOpResult();

  /// Return the dimensions of the dest that are omitted to insert a source
  /// when the result is rank-extended.
  llvm::SmallBitVector getDroppedDims();
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::ParallelInsertSliceOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::RankOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RankOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  RankOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.rank", odsAttrs.getContext());
  }

  RankOpGenericAdaptorBase(RankOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class RankOpGenericAdaptor : public detail::RankOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RankOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  RankOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RankOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : RankOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RankOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RankOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RankOpGenericAdaptor(RangeT values, const RankOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RankOp, typename = std::enable_if_t<std::is_same_v<LateInst, RankOp>>>
  RankOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTensor() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RankOpAdaptor : public RankOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RankOpGenericAdaptor::RankOpGenericAdaptor;
  RankOpAdaptor(RankOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RankOp : public ::mlir::Op<RankOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RankOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RankOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<RankOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<RankOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<RankOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.rank");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getTensorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value tensor);
  static RankOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value tensor);
  static RankOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor);
  static RankOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor);
  static RankOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static RankOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static RankOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RankOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RankOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RankOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RankOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RankOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RankOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RankOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RankOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::RankOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::ReshapeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReshapeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ReshapeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.reshape", odsAttrs.getContext());
  }

  ReshapeOpGenericAdaptorBase(ReshapeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class ReshapeOpGenericAdaptor : public detail::ReshapeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReshapeOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_shape = 1;
public:
  ReshapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReshapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReshapeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReshapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReshapeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReshapeOpGenericAdaptor(RangeT values, const ReshapeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReshapeOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReshapeOp>>>
  ReshapeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  ValueT getShape() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReshapeOpAdaptor : public ReshapeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReshapeOpGenericAdaptor::ReshapeOpGenericAdaptor;
  ReshapeOpAdaptor(ReshapeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReshapeOp : public ::mlir::Op<ReshapeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReshapeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReshapeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_shape = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ReshapeOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ReshapeOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ReshapeOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.reshape");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getShape() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getShapeMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TensorType resultType, Value operand, Value shape);
  static ReshapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TensorType resultType, Value operand, Value shape);
  static ReshapeOp create(::mlir::ImplicitLocOpBuilder &builder, TensorType resultType, Value operand, Value shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::Value shape);
  static ReshapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::Value shape);
  static ReshapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::Value shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value shape);
  static ReshapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value shape);
  static ReshapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value shape);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReshapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReshapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReshapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReshapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  TensorType getResultType() { return ::llvm::cast<TensorType>(getResult().getType()); }
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::ReshapeOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::ScatterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ScatterOpGenericAdaptorBase {
public:
  struct Properties {
    using scatter_dimsTy = ::mlir::DenseI64ArrayAttr;
    scatter_dimsTy scatter_dims;

    auto getScatterDims() const {
      auto &propStorage = this->scatter_dims;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setScatterDims(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->scatter_dims = propValue;
    }
    using uniqueTy = ::mlir::UnitAttr;
    uniqueTy unique;

    auto getUnique() const {
      auto &propStorage = this->unique;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setUnique(const ::mlir::UnitAttr &propValue) {
      this->unique = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.scatter_dims == this->scatter_dims &&
        rhs.unique == this->unique &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ScatterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.scatter", odsAttrs.getContext());
  }

  ScatterOpGenericAdaptorBase(ScatterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getScatterDimsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().scatter_dims);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getScatterDims();
  ::mlir::UnitAttr getUniqueAttr();
  bool getUnique();
};

} // namespace detail
template <typename RangeT>
class ScatterOpGenericAdaptor : public detail::ScatterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ScatterOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_indices = 2;
public:
  ScatterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ScatterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ScatterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ScatterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ScatterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ScatterOpGenericAdaptor(RangeT values, const ScatterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ScatterOp, typename = std::enable_if_t<std::is_same_v<LateInst, ScatterOp>>>
  ScatterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDest() {
    return (*getODSOperands(1).begin());
  }

  ValueT getIndices() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ScatterOpAdaptor : public ScatterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ScatterOpGenericAdaptor::ScatterOpGenericAdaptor;
  ScatterOpAdaptor(ScatterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ScatterOp : public ::mlir::Op<ScatterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ScatterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ScatterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_indices = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ScatterOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ScatterOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ScatterOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("scatter_dims"), ::llvm::StringRef("unique")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getScatterDimsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getScatterDimsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUniqueAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUniqueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.scatter");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getIndices() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIndicesMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::DenseI64ArrayAttr getScatterDimsAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().scatter_dims);
  }

  ::llvm::ArrayRef<int64_t> getScatterDims();
  ::mlir::UnitAttr getUniqueAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().unique);
  }

  bool getUnique();
  void setScatterDimsAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().scatter_dims = attr;
  }

  void setScatterDims(::llvm::ArrayRef<int64_t> attrValue);
  void setUniqueAttr(::mlir::UnitAttr attr) {
    getProperties().unique = attr;
  }

  void setUnique(bool attrValue);
  ::mlir::Attribute removeUniqueAttr() {
      auto attr = getProperties().unique;
      getProperties().unique = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr scatter_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr scatter_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr scatter_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr scatter_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr scatter_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::mlir::DenseI64ArrayAttr scatter_dims, /*optional*/::mlir::UnitAttr unique = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> scatter_dims, /*optional*/bool unique = false);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> scatter_dims, /*optional*/bool unique = false);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> scatter_dims, /*optional*/bool unique = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> scatter_dims, /*optional*/bool unique = false);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> scatter_dims, /*optional*/bool unique = false);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value dest, ::mlir::Value indices, ::llvm::ArrayRef<int64_t> scatter_dims, /*optional*/bool unique = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  RankedTensorType getDestType() {
    return ::llvm::cast<RankedTensorType>(getDest().getType());
  }
  RankedTensorType getIndicesType() {
    return ::llvm::cast<RankedTensorType>(getIndices().getType());
  }
  RankedTensorType getSourceType() {
    return ::llvm::cast<RankedTensorType>(getSource().getType());
  }
  RankedTensorType getResultType() {
    return ::llvm::cast<RankedTensorType>(getResult().getType());
  }
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::ScatterOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::SplatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SplatOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SplatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.splat", odsAttrs.getContext());
  }

  SplatOpGenericAdaptorBase(SplatOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class SplatOpGenericAdaptor : public detail::SplatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SplatOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_dynamicSizes = 1;
public:
  SplatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SplatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SplatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SplatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SplatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SplatOpGenericAdaptor(RangeT values, const SplatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SplatOp, typename = std::enable_if_t<std::is_same_v<LateInst, SplatOp>>>
  SplatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getDynamicSizes() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SplatOpAdaptor : public SplatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SplatOpGenericAdaptor::SplatOpGenericAdaptor;
  SplatOpAdaptor(SplatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SplatOp : public ::mlir::Op<SplatOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SplatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SplatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_dynamicSizes = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<SplatOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SplatOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SplatOp>::getDefaultDialect;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<SplatOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<SplatOp>::reifyDimOfResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.splat");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getDynamicSizes() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDynamicSizesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getAggregate() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value element, Type aggregateType, ValueRange dynamicSizes = {});
  static SplatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value element, Type aggregateType, ValueRange dynamicSizes = {});
  static SplatOp create(::mlir::ImplicitLocOpBuilder &builder, Value element, Type aggregateType, ValueRange dynamicSizes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value element, ArrayRef<int64_t> staticShape, ValueRange dynamicSizes = {});
  static SplatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value element, ArrayRef<int64_t> staticShape, ValueRange dynamicSizes = {});
  static SplatOp create(::mlir::ImplicitLocOpBuilder &builder, Value element, ArrayRef<int64_t> staticShape, ValueRange dynamicSizes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value element, ArrayRef<OpFoldResult> sizes);
  static SplatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value element, ArrayRef<OpFoldResult> sizes);
  static SplatOp create(::mlir::ImplicitLocOpBuilder &builder, Value element, ArrayRef<OpFoldResult> sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type aggregate, ::mlir::Value input, ::mlir::ValueRange dynamicSizes);
  static SplatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type aggregate, ::mlir::Value input, ::mlir::ValueRange dynamicSizes);
  static SplatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type aggregate, ::mlir::Value input, ::mlir::ValueRange dynamicSizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::ValueRange dynamicSizes);
  static SplatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::ValueRange dynamicSizes);
  static SplatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::ValueRange dynamicSizes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SplatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SplatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SplatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SplatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::SplatOp)

namespace mlir::tensor {


//===----------------------------------------------------------------------===//
// ::mlir::tensor::YieldOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class YieldOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  YieldOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tensor.yield", odsAttrs.getContext());
  }

  YieldOpGenericAdaptorBase(YieldOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class YieldOpGenericAdaptor : public detail::YieldOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::YieldOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  YieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  YieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : YieldOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  YieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : YieldOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  YieldOpGenericAdaptor(RangeT values, const YieldOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = YieldOp, typename = std::enable_if_t<std::is_same_v<LateInst, YieldOp>>>
  YieldOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class YieldOpAdaptor : public YieldOpGenericAdaptor<::mlir::ValueRange> {
public:
  using YieldOpGenericAdaptor::YieldOpGenericAdaptor;
  YieldOpAdaptor(YieldOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParent<::mlir::tensor::GenerateOp, ::mlir::tensor::PadOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = YieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = YieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<YieldOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tensor.yield");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tensor::YieldOp)


#endif // GET_OP_CLASSES

