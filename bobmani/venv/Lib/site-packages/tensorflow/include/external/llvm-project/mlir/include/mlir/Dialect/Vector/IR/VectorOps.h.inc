/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: VectorOps.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::vector {

/// Load vector scale size
/// The `vscale` op returns the scale of the scalable vectors, a positive
///     integer value that is constant at runtime but unknown at compile-time.
///     The scale of the vector indicates the multiplicity of the vectors and
///     vector operations. For example, a `vector<[4]xi32>` is equivalent to
///     `vscale` consecutive `vector<4xi32>`; and an operation on a
///     `vector<[4]xi32>` is equivalent to performing that operation `vscale`
///     times, once on each `<4xi32>` segment of the scalable vector. The `vscale`
///     op can be used to calculate the step in vector-length agnostic (VLA) loops.
///     Right now we only support one contiguous set of scalable dimensions, all of
///     them grouped and scaled with the value returned by 'vscale'.
class VectorScaleOp;

} // namespace mlir::vector
namespace mlir::vector {

/// bitcast casts between vectors
/// The bitcast operation casts between vectors of the same rank, the minor 1-D
///     vector size is casted to a vector with a different element type but same
///     bitwidth. In case of 0-D vectors, the bitwidth of element types must be
///     equal.
/// 
///     Example:
/// 
///     ```mlir
///     // Example casting to a smaller element type.
///     %1 = vector.bitcast %0 : vector<5x1x4x3xf32> to vector<5x1x4x6xi16>
/// 
///     // Example casting to a bigger element type.
///     %3 = vector.bitcast %2 : vector<10x12x8xi8> to vector<10x12x2xi32>
/// 
///     // Example casting to an element type of the same size.
///     %5 = vector.bitcast %4 : vector<5x1x4x3xf32> to vector<5x1x4x3xi32>
/// 
///     // Example casting of 0-D vectors.
///     %7 = vector.bitcast %6 : vector<f32> to vector<i32>
///     ```
class BitCastOp;

} // namespace mlir::vector
namespace mlir::vector {

/// broadcast operation
/// Broadcasts the scalar or k-D vector value in the source operand
///     to a n-D result vector such that the broadcast makes sense, i.e.,
///     the source operand is duplicated to match the given rank and sizes
///     in the result vector. The legality rules are:
///     * the source operand must have the same element type as the result type
///     * a k-D vector <s_1 x .. x s_k x type> can be broadcast to
///       a n-D vector <t_1 x .. x t_n x type> if
///        * k <= n, and
///        * the sizes in the trailing dimensions n-k < i <= n with j=i+k-n
///           match exactly as s_j = t_i or s_j = 1:
///        ```
///            t_1 x   ..  t_n-k x t_n-k+1 x .. x t_i x .. x t_n
///                                s_1     x .. x s_j x .. x s_k
///                <duplication>         <potential stretch>
///        ```
///        * in addition, any scalable unit dimension, `[1]`, must match exactly.
/// 
///     The source operand is duplicated over all the missing leading dimensions
///     and stretched over the trailing dimensions where the source has a non-equal
///     dimension of 1 (stretching a trailing dimension is also referred to as
///     "dim-1" broadcasting). These rules imply that any scalar broadcast (k=0) to
///     any shaped vector with the same element type is always legal.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = arith.constant 0.0 : f32
///     %1 = vector.broadcast %0 : f32 to vector<16xf32>
///     %2 = vector.broadcast %1 : vector<16xf32> to vector<4x16xf32>
///     ```
class BroadcastOp;

} // namespace mlir::vector
namespace mlir::vector {

/// writes elements selectively from a vector as defined by a mask
/// The compress store operation writes elements from a vector into memory as
///     defined by a base with indices and a mask vector. Compression only applies
///     to the innermost dimension. When the mask is set, the corresponding element
///     from the vector is written next to memory.  Otherwise, no action is taken
///     for the element. Informally the semantics are:
/// 
///     ```
///     index = i
///     if (mask[0]) base[index++] = value[0]
///     if (mask[1]) base[index++] = value[1]
///     etc.
///     ```
/// 
///     Note that the index increment is done conditionally.
/// 
///     If a mask bit is set and the corresponding index is out-of-bounds for the
///     given base, the behavior is undefined. If a mask bit is not set, no value
///     is stored regardless of the index, and the index is allowed to be
///     out-of-bounds.
/// 
///     The compress store can be used directly where applicable, or can be used
///     during progressively lowering to bring other memory operations closer to
///     hardware ISA support for a compress. The semantics of the operation closely
///     correspond to those of the `llvm.masked.compressstore`
///     [intrinsic](https://llvm.org/docs/LangRef.html#llvm-masked-compressstore-intrinsics).
/// 
///     An optional `alignment` attribute allows to specify the byte alignment of the
///     store operation. It must be a positive power of 2. The operation must access
///     memory at an address aligned to this boundary. Violating this requirement
///     triggers immediate undefined behavior.
/// 
///     Note, at the moment this Op is only available for fixed-width vectors.
/// 
///     Examples:
/// 
///     ```mlir
///     vector.compressstore %base[%i], %mask, %value
///       : memref<?xf32>, vector<8xi1>, vector<8xf32>
/// 
///     vector.compressstore %base[%i, %j], %mask, %value
///       : memref<?x?xf32>, vector<16xi1>, vector<16xf32>
///     ```
class CompressStoreOp;

} // namespace mlir::vector
namespace mlir::vector {

/// creates a constant vector mask
/// Creates and returns a vector mask where elements of the result vector
///     are set to '0' or '1', based on whether the element indices are contained
///     within a hyper-rectangular region specified by the 'mask_dim_sizes'
///     array attribute argument. Each element of the 'mask_dim_sizes' array,
///     specifies an exclusive upper bound [0, mask-dim-size-element-value)
///     for a unique dimension in the vector result. The conjunction of the ranges
///     define a hyper-rectangular region within which elements values are set to 1
///     (otherwise element values are set to 0). Each value of 'mask_dim_sizes' must
///     be non-negative and not greater than the size of the corresponding vector
///     dimension (as opposed to vector.create_mask which allows this). Sizes that
///     correspond to scalable dimensions are implicitly multiplied by vscale,
///     though currently only zero (none set) or the size of the dim/vscale
///     (all set) are supported.
/// 
///     Example:
/// 
///     ```mlir
///     // create a constant vector mask of size 4x3xi1 with elements in range
///     // 0 <= row <= 2 and 0 <= col <= 1 are set to 1 (others to 0).
///     %1 = vector.constant_mask [3, 2] : vector<4x3xi1>
/// 
///     print %1
///                   columns
///                 0    1    2
///               |------------
///             0 | 1    1    0
///       rows  1 | 1    1    0
///             2 | 1    1    0
///             3 | 0    0    0
///     ```
class ConstantMaskOp;

} // namespace mlir::vector
namespace mlir::vector {

/// vector contraction operation
/// Computes the sum of products of vector elements along contracting
///     dimension pairs from 2 vectors of rank M and N respectively, adds this
///     intermediate result to the accumulator argument of rank K, and returns a
///     vector result of rank K (where K = num_lhs_free_dims + num_rhs_free_dims +
///     num_batch_dims (see dimension type descriptions below)). For K = 0 (no
///     free or batch dimensions), the accumulator and output are a scalar.
/// 
///     If operands and the result have types of different bitwidths, operands are
///     promoted to have the same bitwidth as the result before performing the
///     contraction. For integer types, only signless integer types are supported,
///     and the promotion happens via sign extension.
/// 
///     An iterator type attribute list must be specified, where each element of
///     the list represents an iterator with one of the following types:
/// 
///     *   "reduction": reduction dimensions are present in the lhs and rhs
///         arguments but not in the output (and accumulator
///         argument). These are the dimensions along which the vector
///         contraction op computes the sum of products, and
///         contracting dimension pair dimension sizes must match
///         between lhs/rhs.
/// 
///     *   "parallel": Batch dimensions are iterator type "parallel", and
///         are non-contracting dimensions present in the lhs, rhs and
///         output. The lhs/rhs co-iterate along the batch dimensions,
///         which should be expressed in their indexing maps.
/// 
///         Free dimensions are iterator type "parallel", and are
///         non-contraction, non-batch dimensions accessed by either the
///         lhs or rhs (but not both). The lhs and rhs free dimensions
///         are unrelated to each other and do not co-iterate, which
///         should be expressed in their indexing maps.
/// 
///     An indexing map attribute list must be specified with an entry for lhs, rhs
///     and acc arguments. An indexing map attribute specifies a mapping from each
///     iterator in the iterator type list, to each dimension of an N-D vector.
/// 
///     An optional kind attribute may be used to specify the combining function
///     between the intermediate result and accumulator argument of rank K. This
///     attribute can take the values `add`/`mul`/`minsi`/`minui`/`maxsi`/`maxui`
///     /`and`/`or`/`xor` for integers, and `add`/`mul`/`minnumf`/`maxnumf`
///     /`minimumf`/`maximumf` for floats. The default is `add`.
/// 
///     Example:
/// 
///     ```mlir
///     // Simple DOT product (K = 0).
///     #contraction_accesses = [
///      affine_map<(i) -> (i)>,
///      affine_map<(i) -> (i)>,
///      affine_map<(i) -> ()>
///     ]
///     #contraction_trait = {
///       indexing_maps = #contraction_accesses,
///       iterator_types = ["reduction"]
///     }
///     %3 = vector.contract #contraction_trait %0, %1, %2
///       : vector<10xf32>, vector<10xf32> into f32
/// 
///     // 2D vector contraction with one contracting dimension (matmul, K = 2).
///     #contraction_accesses = [
///       affine_map<(i, j, k) -> (i, k)>,
///       affine_map<(i, j, k) -> (k, j)>,
///       affine_map<(i, j, k) -> (i, j)>
///     ]
///     #contraction_trait = {
///       indexing_maps = #contraction_accesses,
///       iterator_types = ["parallel", "parallel", "reduction"]
///     }
/// 
///     %3 = vector.contract #contraction_trait %0, %1, %2
///       : vector<4x3xf32>, vector<3x7xf32> into vector<4x7xf32>
/// 
///     // 4D to 3D vector contraction with two contracting dimensions and
///     // one batch dimension (K = 3).
///     #contraction_accesses = [
///       affine_map<(b0, f0, f1, c0, c1) -> (c0, b0, c1, f0)>,
///       affine_map<(b0, f0, f1, c0, c1) -> (b0, c1, c0, f1)>,
///       affine_map<(b0, f0, f1, c0, c1) -> (b0, f0, f1)>
///     ]
///     #contraction_trait = {
///       indexing_maps = #contraction_accesses,
///       iterator_types = ["parallel", "parallel", "parallel",
///                         "reduction", "reduction"]
///     }
/// 
///     %4 = vector.contract #contraction_trait %0, %1, %2
///         : vector<7x8x16x15xf32>, vector<8x16x7x5xf32> into vector<8x15x5xf32>
/// 
///     // Vector contraction with mixed typed. lhs/rhs have different element
///     // types than accumulator/result.
///     %5 = vector.contract #contraction_trait %0, %1, %2
///       : vector<10xf16>, vector<10xf16> into f32
/// 
///     // Contract with max (K = 0).
///     #contraction_accesses = [
///      affine_map<(i) -> (i)>,
///      affine_map<(i) -> (i)>,
///      affine_map<(i) -> ()>
///     ]
///     #contraction_trait = {
///       indexing_maps = #contraction_accesses,
///       iterator_types = ["reduction"],
///       kind = #vector.kind<maxnumf>
///     }
///     %6 = vector.contract #contraction_trait %0, %1, %2
///       : vector<10xf32>, vector<10xf32> into f32
///     ```
class ContractionOp;

} // namespace mlir::vector
namespace mlir::vector {

/// creates a vector mask
/// Creates and returns a vector mask where elements of the result vector
///     are set to '0' or '1', based on whether the element indices are contained
///     within a hyper-rectangular region specified by the operands. Specifically,
///     each operand specifies a range [0, operand-value) for a unique dimension in
///     the vector result. The conjunction of the operand ranges define a
///     hyper-rectangular region within which elements values are set to 1
///     (otherwise element values are set to 0). If operand-value is negative, it is
///     treated as if it were zero, and if it is greater than the corresponding
///     dimension size, it is treated as if it were equal to the dimension size.
/// 
///     Example:
/// 
///     ```mlir
///     // create a vector mask of size 4x3xi1 where elements in range
///     // 0 <= row <= 2 and 0 <= col <= 1 are set to 1 (others to 0).
///     %1 = vector.create_mask %c3, %c2 : vector<4x3xi1>
/// 
///     print %1
///                   columns
///                 0    1    2
///               |------------
///             0 | 1    1    0
///       rows  1 | 1    1    0
///             2 | 1    1    0
///             3 | 0    0    0
///     ```
class CreateMaskOp;

} // namespace mlir::vector
namespace mlir::vector {

/// constructs two vectors by deinterleaving an input vector
/// The deinterleave operation constructs two vectors from a single input
///         vector. The first result vector contains the elements from even indexes
///         of the input, and the second contains elements from odd indexes. This is
///         the inverse of a `vector.interleave` operation.
/// 
///         Each output's trailing dimension is half of the size of the input
///         vector's trailing dimension. This operation requires the input vector
///         to have a rank > 0 and an even number of elements in its trailing
///         dimension.
/// 
///         The operation supports scalable vectors.
/// 
///         Example:
///         ```mlir
///         %0, %1 = vector.deinterleave %a
///                    : vector<8xi8> -> vector<4xi8>
///         %2, %3 = vector.deinterleave %b
///                    : vector<2x8xi8> -> vector<2x4xi8>
///         %4, %5 = vector.deinterleave %c
///                    : vector<2x8x4xi8> -> vector<2x8x2xi8>
///         %6, %7 = vector.deinterleave %d
///                    : vector<[8]xf32> -> vector<[4]xf32>
///         %8, %9 = vector.deinterleave %e
///                    : vector<2x[6]xf64> -> vector<2x[3]xf64>
///         %10, %11 = vector.deinterleave %f
///                    : vector<2x4x[6]xf64> -> vector<2x4x[3]xf64>
///         ```
class DeinterleaveOp;

} // namespace mlir::vector
namespace mlir::vector {

/// reads elements from memory and spreads them into a vector as defined by a mask
/// The expand load reads elements from memory into a vector as defined by a
///     base with indices and a mask vector. Expansion only applies to the innermost
///     dimension. When the mask is set, the next element is read from memory.
///     Otherwise, the corresponding element is taken from a pass-through vector.
///     Informally the semantics are:
/// 
///     ```
///     index = i
///     result[0] := if mask[0] then base[index++] else pass_thru[0]
///     result[1] := if mask[1] then base[index++] else pass_thru[1]
///     etc.
///     ```
/// 
///     Note that the index increment is done conditionally.
/// 
///     If a mask bit is set and the corresponding index is out-of-bounds for the
///     given base, the behavior is undefined. If a mask bit is not set, the value
///     comes from the pass-through vector regardless of the index, and the index is
///     allowed to be out-of-bounds.
/// 
///     The expand load can be used directly where applicable, or can be used
///     during progressively lowering to bring other memory operations closer to
///     hardware ISA support for an expand. The semantics of the operation closely
///     correspond to those of the `llvm.masked.expandload`
///     [intrinsic](https://llvm.org/docs/LangRef.html#llvm-masked-expandload-intrinsics).
/// 
///     An optional `alignment` attribute allows to specify the byte alignment of the
///     load operation. It must be a positive power of 2. The operation must access
///     memory at an address aligned to this boundary. Violating this requirement
///     triggers immediate undefined behavior.
/// 
///     Note, at the moment this Op is only available for fixed-width vectors.
/// 
///     Examples:
/// 
///     ```mlir
///     %0 = vector.expandload %base[%i], %mask, %pass_thru
///        : memref<?xf32>, vector<8xi1>, vector<8xf32> into vector<8xf32>
/// 
///     %1 = vector.expandload %base[%i, %j], %mask, %pass_thru
///        : memref<?x?xf32>, vector<16xi1>, vector<16xf32> into vector<16xf32>
///     ```
class ExpandLoadOp;

} // namespace mlir::vector
namespace mlir::vector {

/// extract operation
/// Extracts an (n − k)-D result sub-vector from an n-D source vector at a
///     specified k-D position. When n = k, the result degenerates to a scalar
///     element.
/// 
///     Static and dynamic indices must be greater or equal to zero and less than
///     the size of the corresponding dimension. The result is undefined if any
///     index is out-of-bounds. The value `-1` represents a poison index, which
///     specifies that the extracted element is poison.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = vector.extract %0[3]: vector<8x16xf32> from vector<4x8x16xf32>
///     %2 = vector.extract %0[2, 1, 3]: f32 from vector<4x8x16xf32>
///     %4 = vector.extract %0[%a, %b, %c]: f32 from vector<4x8x16xf32>
///     %5 = vector.extract %0[2, %b]: vector<16xf32> from vector<4x8x16xf32>
///     %6 = vector.extract %10[-1, %c]: f32 from vector<4x16xf32>
///     ```
class ExtractOp;

} // namespace mlir::vector
namespace mlir::vector {

/// extract_strided_slice operation
/// Takes an n-D vector, k-D `offsets` integer array attribute, a k-sized
///     `sizes` integer array attribute, a k-sized `strides` integer array
///     attribute and extracts the n-D subvector at the proper offset.
/// 
///     At the moment strides must contain only 1s.
/// 
///     Returns an n-D vector where the first k-D dimensions match the `sizes`
///     attribute. The returned subvector contains the elements starting at offset
///     `offsets` and ending at `offsets + sizes`.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = vector.extract_strided_slice %0
///         {offsets = [0, 2], sizes = [2, 4], strides = [1, 1]}:
///       vector<4x8x16xf32> to vector<2x4x16xf32>
/// 
///     // TODO: Evolve to a range form syntax similar to:
///     %1 = vector.extract_strided_slice %0[0:2:1][2:4:1]
///       vector<4x8x16xf32> to vector<2x4x16xf32>
///     ```
/// 
///     TODO: Implement support for poison indices.
class ExtractStridedSliceOp;

} // namespace mlir::vector
namespace mlir::vector {

/// vector fused multiply-add
/// Multiply-add expressions operate on n-D vectors and compute a fused
///     pointwise multiply-and-accumulate: `$result = $lhs * $rhs + $acc`.
///     All operands and result have the same vector type. The semantics
///     of the operation correspond to those of the `llvm.fma`
///     [intrinsic](https://llvm.org/docs/LangRef.html#int-fma). In the
///     particular case of lowering to LLVM, this is guaranteed to lower
///     to the `llvm.fma.*` intrinsic.
/// 
///     Example:
/// 
///     ```mlir
///     %3 = vector.fma %0, %1, %2: vector<8x16xf32>
///     ```
class FMAOp;

} // namespace mlir::vector
namespace mlir::vector {

/// operation that defines a vector from scalar elements
/// This operation defines a vector from one or multiple scalar elements. The
///     scalar elements are arranged in row-major within the vector. The number of
///     elements must match the number of elements in the result type. All elements
///     must have the same type, which must match the element type of the result
///     vector type. Scalable vectors are not supported.
/// 
///     Examples:
/// 
///     ```mlir
///     // Define a 0-D vector.
///     %0 = vector.from_elements %f1 : vector<f32>
///     // [%f1]
/// 
///     // Define a 1-D vector.
///     %1 = vector.from_elements %f1, %f2 : vector<2xf32>
///     // [%f1, %f2]
/// 
///     // Define a 2-D vector.
///     %2 = vector.from_elements %f1, %f2, %f3, %f4, %f5, %f6 : vector<2x3xf32>
///     // [[%f1, %f2, %f3], [%f4, %f5, %f6]]
/// 
///     // Define a 3-D vector.
///     %3 = vector.from_elements %f1, %f2, %f3, %f4, %f5, %f6 : vector<3x1x2xf32>
///     // [[[%f1, %f2]], [[%f3, %f4]], [[%f5, %f6]]]
///     ```
class FromElementsOp;

} // namespace mlir::vector
namespace mlir::vector {

/// Gathers elements from memory or ranked tensor into a vector as defined by an
///     index vector and a mask vector.
/// The gather operation returns an n-D vector whose elements are either loaded
///     from a k-D memref or tensor, or taken from an n-D pass-through vector, depending
///     on the values of an n-D mask vector.
/// 
///     If a mask bit is set, the corresponding result element is taken from `base`
///     at an index defined by k indices and n-D `index_vec`. Otherwise, the element
///     is taken from the pass-through vector. As an example, suppose that `base` is
///     3-D and the result is 2-D:
/// 
///     ```mlir
///     func.func @gather_3D_to_2D(
///         %base: memref<?x10x?xf32>, %ofs_0: index, %ofs_1: index, %ofs_2: index,
///         %indices: vector<2x3xi32>, %mask: vector<2x3xi1>,
///         %fall_thru: vector<2x3xf32>) -> vector<2x3xf32> {
///             %result = vector.gather %base[%ofs_0, %ofs_1, %ofs_2]
///                                    [%indices], %mask, %fall_thru : [...]
///             return %result : vector<2x3xf32>
///     }
///     ```
/// 
///     The indexing semantics are then,
/// 
///     ```
///     result[i,j] := if mask[i,j] then base[i0, i1, i2 + indices[i,j]]
///                    else pass_thru[i,j]
///     ```
///     The index into `base` only varies in the innermost ((k-1)-th) dimension.
/// 
///     If a mask bit is set and the corresponding index is out-of-bounds for the
///     given base, the behavior is undefined. If a mask bit is not set, the value
///     comes from the pass-through vector regardless of the index, and the index is
///     allowed to be out-of-bounds.
/// 
///     The gather operation can be used directly where applicable, or can be used
///     during progressively lowering to bring other memory operations closer to
///     hardware ISA support for a gather.
/// 
///     An optional `alignment` attribute allows to specify the byte alignment of the
///     gather operation. It must be a positive power of 2. The operation must access
///     memory at an address aligned to this boundary. Violating this requirement
///     triggers immediate undefined behavior.
/// 
///     Examples:
/// 
///     ```mlir
///     // 1-D memref gathered to 2-D vector.
///     %0 = vector.gather %base[%c0][%v], %mask, %pass_thru
///        : memref<?xf32>, vector<2x16xi32>, vector<2x16xi1>, vector<2x16xf32> into vector<2x16xf32>
/// 
///     // 2-D memref gathered to 1-D vector.
///     %1 = vector.gather %base[%i, %j][%v], %mask, %pass_thru
///        : memref<16x16xf32>, vector<16xi32>, vector<16xi1>, vector<16xf32> into vector<16xf32>
///     ```
class GatherOp;

} // namespace mlir::vector
namespace mlir::vector {

/// insert operation
/// Inserts an (n - k)-D sub-vector (value-to-store) into an n-D destination
///     vector at a specified k-D position. When n = 0, value-to-store degenerates
///     to a scalar element inserted into the n-D destination vector.
/// 
///     Static and dynamic indices must be greater or equal to zero and less than
///     the size of the corresponding dimension. The result is undefined if any
///     index is out-of-bounds. The value `-1` represents a poison index, which
///     specifies that the resulting vector is poison.
/// 
///     Example:
/// 
///     ```mlir
///     %2 = vector.insert %0, %1[3] : vector<8x16xf32> into vector<4x8x16xf32>
///     %5 = vector.insert %3, %4[2, 1, 3] : f32 into vector<4x8x16xf32>
///     %11 = vector.insert %9, %10[%a, %b, %c] : f32 into vector<4x8x16xf32>
///     %12 = vector.insert %4, %10[2, %b] : vector<16xf32> into vector<4x8x16xf32>
///     %13 = vector.insert %20, %1[-1, %c] : f32 into vector<4x16xf32>
///     ```
class InsertOp;

} // namespace mlir::vector
namespace mlir::vector {

/// strided_slice operation
/// Takes a k-D valueToStore vector, an n-D destination vector (n >= k), n-sized
///     `offsets` integer array attribute, a k-sized `strides` integer array attribute
///     and inserts the k-D valueToStore vector as a strided subvector at the proper offset
///     into the n-D destination vector.
/// 
///     At the moment strides must contain only 1s.
/// 
///     Returns an n-D vector that is a copy of the n-D destination vector in which
///     the last k-D dimensions contain the k-D valueToStore vector elements strided at
///     the proper location as specified by the offsets.
/// 
///     Example:
/// 
///     ```mlir
///     %2 = vector.insert_strided_slice %0, %1
///         {offsets = [0, 0, 2], strides = [1, 1]}:
///       vector<2x4xf32> into vector<16x4x8xf32>
///     ```
class InsertStridedSliceOp;

} // namespace mlir::vector
namespace mlir::vector {

/// constructs a vector by interleaving two input vectors
/// The interleave operation constructs a new vector by interleaving the
///     elements from the trailing (or final) dimension of two input vectors,
///     returning a new vector where the trailing dimension is twice the size.
/// 
///     Note that for the n-D case this differs from the interleaving possible with
///     `vector.shuffle`, which would only operate on the leading dimension.
/// 
///     Another key difference is this operation supports scalable vectors, though
///     currently a general LLVM lowering is limited to the case where only the
///     trailing dimension is scalable.
/// 
///     Example:
///     ```mlir
///     %a = arith.constant dense<[0, 1]> : vector<2xi32>
///     %b = arith.constant dense<[2, 3]> : vector<2xi32>
///     // The value of `%0` is `[0, 2, 1, 3]`.
///     %0 = vector.interleave %a, %b : vector<2xi32> -> vector<4xi32>
/// 
///     // Examples showing allowed input and result types.
///     %1 = vector.interleave %c, %d : vector<f16> -> vector<2xf16>
///     %2 = vector.interleave %e, %f : vector<6x3xf32> -> vector<6x6xf32>
///     %3 = vector.interleave %g, %h : vector<[4]xi32> -> vector<[8]xi32>
///     %4 = vector.interleave %i, %j : vector<2x4x[2]xf64> -> vector<2x4x[4]xf64>
///     ```
class InterleaveOp;

} // namespace mlir::vector
namespace mlir::vector {

/// reads an n-D slice of memory into an n-D vector
/// The 'vector.load' operation reads an n-D slice of memory into an n-D
///     vector. It takes a 'base' memref, an index for each memref dimension and a
///     result vector type as arguments. It returns a value of the result vector
///     type. The 'base' memref and indices determine the start memory address from
///     which to read. Each index provides an offset for each memref dimension
///     based on the element type of the memref. The shape of the result vector
///     type determines the shape of the slice read from the start memory address.
///     The elements along each dimension of the slice are strided by the memref
///     strides. When loading more than 1 element, only unit strides are allowed
///     along the most minor memref dimension. These constraints guarantee that
///     elements read along the first dimension of the slice are contiguous in
///     memory.
/// 
///     The memref element type can be a scalar or a vector type. If the memref
///     element type is a scalar, it should match the element type of the result
///     vector. If the memref element type is vector, it should match the result
///     vector type.
/// 
///     Example: 0-D vector load on a scalar memref.
///     ```mlir
///     %result = vector.load %base[%i, %j] : memref<100x100xf32>, vector<f32>
///     ```
/// 
///     Example: 1-D vector load on a scalar memref.
///     ```mlir
///     %result = vector.load %base[%i, %j] : memref<100x100xf32>, vector<8xf32>
///     ```
/// 
///     Example: 1-D vector load on a vector memref.
///     ```mlir
///     %result = vector.load %memref[%i, %j] : memref<200x100xvector<8xf32>>, vector<8xf32>
///     ```
/// 
///     Example:  2-D vector load on a scalar memref.
///     ```mlir
///     %result = vector.load %memref[%i, %j] : memref<200x100xf32>, vector<4x8xf32>
///     ```
/// 
///     Example:  2-D vector load on a vector memref.
///     ```mlir
///     %result = vector.load %memref[%i, %j] : memref<200x100xvector<4x8xf32>>, vector<4x8xf32>
///     ```
/// 
///     Representation-wise, the 'vector.load' operation permits out-of-bounds
///     reads. Support and implementation of out-of-bounds vector loads is
///     target-specific. No assumptions should be made on the value of elements
///     loaded out of bounds. Not all targets may support out-of-bounds vector
///     loads.
/// 
///     Example:  Potential out-of-bound vector load.
///     ```mlir
///     %result = vector.load %memref[%index] : memref<?xf32>, vector<8xf32>
///     ```
/// 
///     Example:  Explicit out-of-bound vector load.
///     ```mlir
///     %result = vector.load %memref[%c0] : memref<7xf32>, vector<8xf32>
///     ```
/// 
///     An optional `alignment` attribute allows to specify the byte alignment of the
///     load operation. It must be a positive power of 2. The operation must access
///     memory at an address aligned to this boundary. Violating this requirement
///     triggers immediate undefined behavior.
class LoadOp;

} // namespace mlir::vector
namespace mlir::vector {

/// Predicates a maskable vector operation
/// The `vector.mask` is a `MaskingOpInterface` operation that predicates the
///     execution of another operation. It takes an `i1` vector mask and an
///     optional passthru vector as arguments.
/// 
///     A implicitly `vector.yield`-terminated region encloses the operation to be
///     masked. Values used within the region are captured from above. Only one
///     *maskable* operation can be masked with a `vector.mask` operation at a time.
///     An operation is *maskable* if it implements the `MaskableOpInterface`. The
///     terminator yields all results from the maskable operation to the result of
///     this operation. No other values are allowed to be yielded.
/// 
///     An empty `vector.mask` operation is currently legal to enable optimizations
///     across the `vector.mask` region. However, this might change in the future
///     once vector transformations gain better support for `vector.mask`.
///     TODO: Consider making empty `vector.mask` illegal.
/// 
///     The vector mask argument holds a bit for each vector lane and determines
///     which vector lanes should execute the maskable operation and which ones
///     should not. The `vector.mask` operation returns the value produced by the
///     masked execution of the nested operation, if any. The masked-off lanes in
///     the result vector are taken from the corresponding lanes of the pass-thru
///     argument, if provided, or left unmodified, otherwise. At this point, 0-D
///     vectors are not supported by `vector.mask`. They may be supported in the
///     future.
/// 
///     The `vector.mask` operation does not prescribe how a maskable operation
///     should be masked or how a masked operation should be lowered. Masking
///     constraints and some semantic details are provided by each maskable
///     operation through the `MaskableOpInterface`. Lowering of masked operations
///     is implementation defined. For instance, scalarizing the masked operation
///     or executing the operation for the masked-off lanes are valid lowerings as
///     long as the execution of masked-off lanes does not change the observable
///     behavior of the program.
/// 
///     Examples:
/// 
///     ```
///       %0 = vector.mask %mask { vector.reduction <add>, %a : vector<8xi32> into i32 } : vector<8xi1> -> i32
///     ```
/// 
///     ```
///       %0 = vector.mask %mask, %passthru { arith.divsi %a, %b : vector<8xi32> } : vector<8xi1> -> vector<8xi32>
///     ```
/// 
///     ```
///       vector.mask %mask { vector.transfer_write %val, %t0[%idx] : vector<16xf32>, memref<?xf32> } : vector<16xi1>
///     ```
/// 
///     ```
///       vector.mask %mask { vector.transfer_write %val, %t0[%idx] : vector<16xf32>, tensor<?xf32> } : vector<16xi1> -> tensor<?xf32>
///     ```
class MaskOp;

} // namespace mlir::vector
namespace mlir::vector {

/// loads elements from memory into a vector as defined by a mask vector
/// The masked load reads elements from memory into a vector as defined
///     by a base with indices and a mask vector. When the mask is set, the
///     element is read from memory. Otherwise, the corresponding element is taken
///     from a pass-through vector. Informally the semantics are:
///     ```
///     result[0] := if mask[0] then base[i + 0] else pass_thru[0]
///     result[1] := if mask[1] then base[i + 1] else pass_thru[1]
///     etc.
///     ```
/// 
///     If a mask bit is set and the corresponding index is out-of-bounds for the
///     given base, the behavior is undefined. If a mask bit is not set, the value
///     comes from the pass-through vector regardless of the index, and the index is
///     allowed to be out-of-bounds.
/// 
///     The masked load can be used directly where applicable, or can be used
///     during progressively lowering to bring other memory operations closer to
///     hardware ISA support for a masked load. The semantics of the operation
///     closely correspond to those of the `llvm.masked.load`
///     [intrinsic](https://llvm.org/docs/LangRef.html#llvm-masked-load-intrinsics).
/// 
///     Examples:
/// 
///     ```mlir
///     %0 = vector.maskedload %base[%i], %mask, %pass_thru
///        : memref<?xf32>, vector<8xi1>, vector<8xf32> into vector<8xf32>
/// 
///     %1 = vector.maskedload %base[%i, %j], %mask, %pass_thru
///        : memref<?x?xf32>, vector<16xi1>, vector<16xf32> into vector<16xf32>
///     ```
/// 
///     An optional `alignment` attribute allows to specify the byte alignment of the
///     load operation. It must be a positive power of 2. The operation must access
///     memory at an address aligned to this boundary. Violating this requirement
///     triggers immediate undefined behavior.
class MaskedLoadOp;

} // namespace mlir::vector
namespace mlir::vector {

/// stores elements from a vector into memory as defined by a mask vector
/// The masked store operation writes elements from a vector into memory
///     as defined by a base with indices and a mask vector. When the mask is
///     set, the corresponding element from the vector is written to memory. Otherwise,
///     no action is taken for the element. Informally the semantics are:
///     ```
///     if (mask[0]) base[i+0] = value[0]
///     if (mask[1]) base[i+1] = value[1]
///     etc.
///     ```
/// 
///     If a mask bit is set and the corresponding index is out-of-bounds for the
///     given base, the behavior is undefined. If a mask bit is not set, no value
///     is stored regardless of the index, and the index is allowed to be
///     out-of-bounds.
/// 
///     The masked store can be used directly where applicable, or can be used
///     during progressively lowering to bring other memory operations closer to
///     hardware ISA support for a masked store. The semantics of the operation
///     closely correspond to those of the `llvm.masked.store`
///     [intrinsic](https://llvm.org/docs/LangRef.html#llvm-masked-store-intrinsics).
/// 
///     Examples:
/// 
///     ```mlir
///     vector.maskedstore %base[%i], %mask, %value
///       : memref<?xf32>, vector<8xi1>, vector<8xf32>
/// 
///     vector.maskedstore %base[%i, %j], %mask, %value
///       : memref<?x?xf32>, vector<16xi1>, vector<16xf32>
///     ```
/// 
///     An optional `alignment` attribute allows to specify the byte alignment of the
///     store operation. It must be a positive power of 2. The operation must access
///     memory at an address aligned to this boundary. Violating this requirement
///     triggers immediate undefined behavior.
class MaskedStoreOp;

} // namespace mlir::vector
namespace mlir::vector {

/// Multi-dimensional reduction operation
/// Reduces an n-D vector into an (n-k)-D vector (or a scalar when k == n)
///     using the given operation: `add`/`mul`/`minsi`/`minui`/`maxsi`/`maxui`
///     /`and`/`or`/`xor` for integers, and `add`/`mul`/`minnumf`/`maxnumf`/`minimumf`
///     /`maximumf` for floats.
///     Takes an initial accumulator operand.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = vector.multi_reduction <add>, %0, %acc0 [1, 3] :
///       vector<4x8x16x32xf32> to vector<4x16xf32>
///     %2 = vector.multi_reduction <add>, %1, %acc1 [0, 1] :
///       vector<4x16xf32> to f32
///     ```
class MultiDimReductionOp;

} // namespace mlir::vector
namespace mlir::vector {

/// vector outerproduct with optional fused add
/// Takes 2 1-D vectors and returns the 2-D vector containing the outer-product,
///     as illustrated below:
///     ```
///      outer |   [c, d]
///      ------+------------
///        [a, | [ [a*c, a*d],
///         b] |   [b*c, b*d] ]
///     ```
///     This operation also accepts a 1-D vector lhs and a scalar rhs. In this
///     case a simple AXPY operation is performed, which returns a 1-D vector.
///     ```
///         [a, b] * c = [a*c, b*c]
///     ```
/// 
///     An optional extra vector argument with the same shape as the output
///     vector may be specified in which case the operation returns the sum of
///     the outer-product and the extra vector. In this multiply-accumulate
///     scenario for floating-point arguments, the rounding mode is enforced
///     by guaranteeing that a fused-multiply add operation is emitted. When
///     lowered to the LLVMIR dialect, this form emits `llvm.intr.fma`, which
///     is guaranteed to lower to actual `fma` instructions on x86.
/// 
///     An optional kind attribute may be specified to be: `add`/`mul`/`minsi`
///     /`minui`/`maxsi`/`maxui`/`and`/`or`/`xor` for integers, and `add`/`mul`
///     /`minnumf`/`maxnumf`/`minimumf`/`maximumf` for floats. The default is
///     `add`.
/// 
///     Example:
/// 
///     ```
///     %2 = vector.outerproduct %0, %1: vector<4xf32>, vector<8xf32>
///     return %2: vector<4x8xf32>
/// 
///     %3 = vector.outerproduct %0, %1, %2:
///       vector<4xf32>, vector<8xf32>, vector<4x8xf32>
///     return %3: vector<4x8xf32>
/// 
///     %4 = vector.outerproduct %0, %1, %2 {kind = #vector.kind<maxnumf>}:
///       vector<4xf32>, vector<8xf32>, vector<4x8xf32>
///     return %3: vector<4x8xf32>
/// 
///     %6 = vector.outerproduct %4, %5: vector<10xf32>, f32
///     return %6: vector<10xf32>
/// 
///     ```
class OuterProductOp;

} // namespace mlir::vector
namespace mlir::vector {

/// print operation (for testing and debugging)
/// Prints the source vector (or scalar) to stdout in a human-readable format
///     (for testing and debugging). No return value.
/// 
///     Example:
/// 
///     ```mlir
///     %v = arith.constant dense<0.0> : vector<4xf32>
///     vector.print %v : vector<4xf32>
///     ```
/// 
///     When lowered to LLVM, the vector print is decomposed into elementary
///     printing method calls that at runtime will yield:
/// 
///     ```
///     ( 0.0, 0.0, 0.0, 0.0 )
///     ```
/// 
///     This is printed to stdout via a small runtime support library, which only
///     needs to provide a few printing methods (single value for all data
///     types, opening/closing bracket, comma, newline).
/// 
///     By default `vector.print` adds a newline after the vector, but this can be
///     controlled by the `punctuation` attribute. For example, to print a comma
///     after instead do:
/// 
///     ```mlir
///     vector.print %v : vector<4xf32> punctuation <comma>
///     ```
/// 
///     Note that it is possible to use the punctuation attribute alone. The
///     following will print a single newline:
/// 
///     ```mlir
///     vector.print punctuation <newline>
///     ```
/// 
///     Additionally, to aid with debugging and testing `vector.print` can also
///     print constant strings:
/// 
///     ```mlir
///     vector.print str "Hello, World!"
///     ```
class PrintOp;

} // namespace mlir::vector
namespace mlir::vector {

/// reduction operation
/// Reduces an 1-D vector "horizontally" into a scalar using the given
///     operation: `add`/`mul`/`minsi`/`minui`/`maxsi`/`maxui`/`and`/`or`/`xor` for
///     integers, and `add`/`mul`/`minnumf`/`maxnumf`/`minimumf`/`maximumf` for
///     floats. Reductions also allow an optional fused accumulator.
/// 
///     Note that these operations are restricted to 1-D vectors to remain
///     close to the corresponding LLVM intrinsics:
/// 
///     http://llvm.org/docs/LangRef.html#vector-reduction-intrinsics
/// 
///     Example:
/// 
///     ```mlir
///     %1 = vector.reduction <add>, %0 : vector<16xf32> into f32
/// 
///     %3 = vector.reduction <xor>, %2 : vector<4xi32> into i32
/// 
///     %4 = vector.reduction <mul>, %0, %1 : vector<16xf32> into f32
///     ```
class ReductionOp;

} // namespace mlir::vector
namespace mlir::vector {

/// extract subvector from scalable vector operation
/// Takes rank-1 source vector and a position `pos` within the source
///     vector, and extracts a subvector starting from that position.
/// 
///     The extraction position must be a multiple of the minimum size of the result
///     vector. For the operation to be well defined, the destination vector must
///     fit within the source vector from the specified position. Since the source
///     vector is scalable and its runtime length is unknown, the validity of the
///     operation can't be verified nor guaranteed at compile time.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = vector.scalable.extract %0[8] : vector<4xf32> from vector<[8]xf32>
///     %3 = vector.scalable.extract %2[0] : vector<[4]xf32> from vector<[8]xf32>
///     ```
/// 
///     Invalid example:
///     ```mlir
///     %1 = vector.scalable.extract %0[5] : vector<4xf32> from vector<[16]xf32>
///     ```
class ScalableExtractOp;

} // namespace mlir::vector
namespace mlir::vector {

/// insert subvector into scalable vector operation
/// This operations takes a rank-1 fixed-length or scalable subvector and
///     inserts it within the destination scalable vector starting from the
///     position specificed by `pos`. If the source vector is scalable, the
///     insertion position will be scaled by the runtime scaling factor of the
///     source subvector.
/// 
///     The insertion position must be a multiple of the minimum size of the source
///     vector. For the operation to be well defined, the source vector must fit in
///     the destination vector from the specified position. Since the destination
///     vector is scalable and its runtime length is unknown, the validity of the
///     operation can't be verified nor guaranteed at compile time.
/// 
///     Example:
/// 
///     ```mlir
///     %2 = vector.scalable.insert %0, %1[8] : vector<4xf32> into vector<[16]xf32>
///     %5 = vector.scalable.insert %3, %4[0] : vector<8xf32> into vector<[4]xf32>
///     %8 = vector.scalable.insert %6, %7[0] : vector<[4]xf32> into vector<[8]xf32>
///     ```
/// 
///     Invalid example:
///     ```mlir
///     %2 = vector.scalable.insert %0, %1[5] : vector<4xf32> into vector<[16]xf32>
///     ```
class ScalableInsertOp;

} // namespace mlir::vector
namespace mlir::vector {

/// Scan operation
/// Performs an inclusive/exclusive scan on an n-D vector along a single
///     dimension returning an n-D result vector using the given
///     operation (`add`/`mul`/`minsi`/`minui`/`maxsi`/`maxui`/`and`/`or`/`xor` for
///     integers, and `add`/`mul`/`minnumf`/`maxnumf`/`minimumf`/`maximumf` for
///     floats), and a specified value for the initial value. The operator returns
///     the result of scan as well as the result of the last reduction in the scan.
/// 
///     Example:
/// 
///     ```mlir
///     %1:2 = vector.scan <add>, %0, %acc {inclusive = false, reduction_dim = 1 : i64} :
///       vector<4x8x16x32xf32>, vector<4x16x32xf32>
///     ```
class ScanOp;

} // namespace mlir::vector
namespace mlir::vector {

/// scatters elements from a vector into memory or ranked tensor as defined by an index vector
///     and a mask vector
/// The scatter operation stores elements from a n-D vector into memory or ranked tensor as
///     defined by a base with indices and an additional n-D index vector, but
///     only if the corresponding bit in a n-D mask vector is set. Otherwise, no
///     action is taken for that element. Informally the semantics are:
///     ```
///     if (mask[0]) base[index[0]] = value[0]
///     if (mask[1]) base[index[1]] = value[1]
///     etc.
///     ```
/// 
///     If a mask bit is set and the corresponding index is out-of-bounds for the
///     given base, the behavior is undefined. If a mask bit is not set, no value
///     is stored regardless of the index, and the index is allowed to be
///     out-of-bounds.
/// 
///     If the index vector contains two or more duplicate indices, the behavior is
///     undefined. Underlying implementation may enforce strict sequential
///     semantics.
///     TODO: always enforce strict sequential semantics?
/// 
///     The scatter operation can be used directly where applicable, or can be used
///     during progressively lowering to bring other memory operations closer to
///     hardware ISA support for a scatter. The semantics of the operation closely
///     correspond to those of the `llvm.masked.scatter`
///     [intrinsic](https://llvm.org/docs/LangRef.html#llvm-masked-scatter-intrinsics).
/// 
///     An optional `alignment` attribute allows to specify the byte alignment of the
///     scatter operation. It must be a positive power of 2. The operation must access
///     memory at an address aligned to this boundary. Violating this requirement
///     triggers immediate undefined behavior.
/// 
///     Examples:
/// 
///     ```mlir
///     vector.scatter %base[%c0][%v], %mask, %value
///         : memref<?xf32>, vector<16xi32>, vector<16xi1>, vector<16xf32>
/// 
///     vector.scatter %base[%i, %j][%v], %mask, %value
///         : memref<16x16xf32>, vector<16xi32>, vector<16xi1>, vector<16xf32>
///     ```
class ScatterOp;

} // namespace mlir::vector
namespace mlir::vector {

/// shape_cast casts between vector shapes
/// Casts to a vector with the same number of elements, element type, and
///     number of scalable dimensions.
/// 
///     It is currently assumed that this operation does not require moving data,
///     and that it will be folded away before lowering vector operations.
/// 
///     There is an exception to the folding expectation when targeting
///     llvm.intr.matrix operations. We need a type conversion back and forth from a
///     2-D MLIR vector to a 1-D flattened LLVM vector.shape_cast lowering to LLVM
///     is supported in that particular case, for now.
/// 
///     Examples:
/// 
///     ```mlir
///     %1 = vector.shape_cast %0 : vector<4x3xf32> to vector<3x2x2xf32>
/// 
///     // with 2 scalable dimensions (number of which must be preserved).
///     %3 = vector.shape_cast %2 : vector<[2]x3x[4]xi8> to vector<3x[1]x[8]xi8>
///     ```
class ShapeCastOp;

} // namespace mlir::vector
namespace mlir::vector {

/// shuffle operation
/// The shuffle operation constructs a permutation (or duplication) of elements
///     from two input vectors, returning a vector with the same element type as
///     the input and a length that is the same as the shuffle mask. The two input
///     vectors must have the same element type, same rank, and trailing dimension
///     sizes and shuffles their values in the leading dimension (which may differ
///     in size) according to the given mask. The legality rules are:
///     * the two operands must have the same element type as the result
///       - Either, the two operands and the result must have the same
///         rank and trailing dimension sizes, viz. given two k-D operands
///                 v1 : <s_1 x s_2 x .. x s_k x type> and
///                 v2 : <t_1 x t_2 x .. x t_k x type>
///         we have s_i = t_i for all 1 < i <= k
///       - Or, the two operands must be 0-D vectors and the result is a 1-D vector.
///     * the mask length equals the leading dimension size of the result
///     * numbering the input vector indices left to right across the operands, all
///       mask values must be within range, viz. given two k-D operands v1 and v2
///       above, all mask values are in the range [0,s_1+t_1). The value `-1`
///       represents a poison mask value, which specifies that the selected element
///       is poison.
/// 
///     Note, scalable vectors are not supported.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = vector.shuffle %a, %b[0, 3]
///                : vector<2xf32>, vector<2xf32>       ; yields vector<2xf32>
///     %1 = vector.shuffle %c, %b[0, 1, 2]
///                : vector<2x16xf32>, vector<1x16xf32> ; yields vector<3x16xf32>
///     %2 = vector.shuffle %a, %b[3, 2, 1, 0]
///                : vector<2xf32>, vector<2xf32>       ; yields vector<4xf32>
///     %3 = vector.shuffle %a, %b[0, 1]
///                : vector<f32>, vector<f32>           ; yields vector<2xf32>
///     %4 = vector.shuffle %a, %b[0, 4, -1, -1, -1, -1]
///                : vector<4xf32>, vector<4xf32>       ; yields vector<6xf32>
///     ```
class ShuffleOp;

} // namespace mlir::vector
namespace mlir::vector {

/// A linear sequence of values from 0 to N
/// A `step` operation produces an index vector, i.e. a 1-D vector of values of
///     index type that represents a linear sequence from 0 to N-1, where N is the
///     number of elements in the `result` vector.
/// 
///     Supports fixed-width and scalable vectors.
/// 
///     Examples:
/// 
///     ```mlir
///     %0 = vector.step : vector<4xindex> ; [0, 1, 2, 3]
///     %1 = vector.step : vector<[4]xindex> ; [0, 1, .., <vscale * 4 - 1>]
///     ```
class StepOp;

} // namespace mlir::vector
namespace mlir::vector {

/// writes an n-D vector to an n-D slice of memory
/// The 'vector.store' operation writes an n-D vector to an n-D slice of memory.
///     It takes the vector value to be stored, a 'base' memref and an index for
///     each memref dimension. The 'base' memref and indices determine the start
///     memory address from which to write. Each index provides an offset for each
///     memref dimension based on the element type of the memref. The shape of the
///     vector value to store determines the shape of the slice written from the
///     start memory address. The elements along each dimension of the slice are
///     strided by the memref strides. When storing more than 1 element, only unit
///     strides are allowed along the most minor memref dimension. These constraints
///     guarantee that elements written along the first dimension of the slice are
///     contiguous in memory.
/// 
///     The memref element type can be a scalar or a vector type. If the memref
///     element type is a scalar, it should match the element type of the value
///     to store. If the memref element type is vector, it should match the type
///     of the value to store.
/// 
///     Example: 0-D vector store on a scalar memref.
///     ```mlir
///     vector.store %valueToStore, %memref[%i, %j] : memref<200x100xf32>, vector<f32>
///     ```
/// 
///     Example: 1-D vector store on a scalar memref.
///     ```mlir
///     vector.store %valueToStore, %memref[%i, %j] : memref<200x100xf32>, vector<8xf32>
///     ```
/// 
///     Example: 1-D vector store on a vector memref.
///     ```mlir
///     vector.store %valueToStore, %memref[%i, %j] : memref<200x100xvector<8xf32>>, vector<8xf32>
///     ```
/// 
///     Example:  2-D vector store on a scalar memref.
///     ```mlir
///     vector.store %valueToStore, %memref[%i, %j] : memref<200x100xf32>, vector<4x8xf32>
///     ```
/// 
///     Example:  2-D vector store on a vector memref.
///     ```mlir
///     vector.store %valueToStore, %memref[%i, %j] : memref<200x100xvector<4x8xf32>>, vector<4x8xf32>
///     ```
/// 
///     Representation-wise, the 'vector.store' operation permits out-of-bounds
///     writes. Support and implementation of out-of-bounds vector stores are
///     target-specific. No assumptions should be made on the memory written out of
///     bounds. Not all targets may support out-of-bounds vector stores.
/// 
///     Example:  Potential out-of-bounds vector store.
///     ```mlir
///     vector.store %valueToStore, %memref[%index] : memref<?xf32>, vector<8xf32>
///     ```
/// 
///     Example:  Explicit out-of-bounds vector store.
///     ```mlir
///     vector.store %valueToStore, %memref[%c0] : memref<7xf32>, vector<8xf32>
///     ```
/// 
///     An optional `alignment` attribute allows to specify the byte alignment of the
///     store operation. It must be a positive power of 2. The operation must access
///     memory at an address aligned to this boundary. Violating this requirement
///     triggers immediate undefined behavior.
class StoreOp;

} // namespace mlir::vector
namespace mlir::vector {

/// operation that decomposes a vector into all its scalar elements
/// This operation decomposes all the scalar elements from a vector. The
///     decomposed scalar elements are returned in row-major order. The number of
///     scalar results must match the number of elements in the input vector type.
///     All the result elements have the same result type, which must match the
///     element type of the input vector. Scalable vectors are not supported.
/// 
///     Examples:
/// 
///     ```mlir
///     // Decompose a 0-D vector.
///     %0 = vector.to_elements %v0 : vector<f32>
///     // %0 = %v0[0]
/// 
///     // Decompose a 1-D vector.
///     %0:2 = vector.to_elements %v1 : vector<2xf32>
///     // %0#0 = %v1[0]
///     // %0#1 = %v1[1]
/// 
///     // Decompose a 2-D.
///     %0:6 = vector.to_elements %v2 : vector<2x3xf32>
///     // %0#0 = %v2[0, 0]
///     // %0#1 = %v2[0, 1]
///     // %0#2 = %v2[0, 2]
///     // %0#3 = %v2[1, 0]
///     // %0#4 = %v2[1, 1]
///     // %0#5 = %v2[1, 2]
/// 
///     // Decompose a 3-D vector.
///     %0:6 = vector.to_elements %v3 : vector<3x1x2xf32>
///     // %0#0 = %v3[0, 0, 0]
///     // %0#1 = %v3[0, 0, 1]
///     // %0#2 = %v3[1, 0, 0]
///     // %0#3 = %v3[1, 0, 1]
///     // %0#4 = %v3[2, 0, 0]
///     // %0#5 = %v3[2, 0, 1]
///     ```
class ToElementsOp;

} // namespace mlir::vector
namespace mlir::vector {

/// Reads a supervector from memory into an SSA vector value.
/// The `vector.transfer_read` op performs a read from a slice within a
///     [MemRef](../LangRef.md#memref-type) or a Ranked
///     [Tensor](../LangRef.md#tensor-type) supplied as its first operand
///     into a [vector](../LangRef.md#vector-type) of the same base elemental type.
/// 
///     A memref/tensor operand with vector element type, must have its vector
///     element type match a suffix (shape and element type) of the vector (e.g.
///     memref<3x2x6x4x3xf32>, vector<1x1x4x3xf32>).
/// 
///     The slice is further defined by a full-rank index within the MemRef/Tensor,
///     supplied as the operands `[1 .. 1 + rank(memref/tensor))` that defines the
///     starting point of the transfer (e.g. `%A[%i0, %i1, %i2]`).
/// 
///     The permutation_map [attribute](../LangRef.md#attributes) is an
///     [affine-map](Affine.md#affine-maps) which specifies the transposition on the
///     slice to match the vector shape. The permutation map may be implicit and
///     omitted from parsing and printing if it is the canonical minor identity map
///     (i.e. if it does not permute or broadcast any dimension).
/// 
///     The size of the slice is specified by the size of the vector, given as the
///     return type.
/// 
///     An SSA value `padding` of the same elemental type as the MemRef/Tensor is
///     provided to specify a fallback value in the case of out-of-bounds accesses
///     and/or masking.
/// 
///     An optional SSA value `mask` may be specified to mask out elements read from
///     the MemRef/Tensor. The `mask` type is an `i1` vector with a shape that
///     matches how elements are read from the MemRef/Tensor, *before* any
///     permutation or broadcasting. Elements whose corresponding mask element is
///     `0` are masked out and replaced with `padding`.
/// 
///     For every vector dimension, the boolean array attribute `in_bounds`
///     specifies if the transfer is guaranteed to be within the source bounds. If
///     set to "false", accesses (including the starting point) may run
///     out-of-bounds along the respective vector dimension as the index increases.
///     Non-vector dimensions *must* always be in-bounds. The `in_bounds` array
///     length has to be equal to the vector rank. This attribute has a default
///     value: `false` (i.e. "out-of-bounds"). When skipped in the textual IR, the
///     default value is assumed. Similarly, the OP printer will omit this
///     attribute when all dimensions are out-of-bounds (i.e. the default value is
///     used).
/// 
///     A `vector.transfer_read` can be lowered to a simple load if all dimensions
///     are specified to be within bounds and no `mask` was specified.
/// 
///     This operation is called 'read' by opposition to 'load' because the
///     super-vector granularity is generally not representable with a single
///     hardware register. A `vector.transfer_read` is thus a mid-level abstraction
///     that supports super-vectorization with non-effecting padding for full-tile
///     only operations.
/// 
///     More precisely, let's dive deeper into the permutation_map for the following
///     MLIR:
/// 
///     ```mlir
///     vector.transfer_read %A[%expr1, %expr2, %expr3, %expr4]
///       { permutation_map : (d0,d1,d2,d3) -> (d2,0,d0) } :
///       memref<?x?x?x?xf32>, vector<3x4x5xf32>
///     ```
/// 
///     This operation always reads a slice starting at `%A[%expr1, %expr2, %expr3,
///     %expr4]`. The size of the slice can be inferred from the resulting vector
///     shape and walking back through the permutation map: 3 along d2 and 5 along
///     d0, so the slice is: `%A[%expr1 : %expr1 + 5, %expr2, %expr3:%expr3 + 3, %expr4]`
/// 
///     That slice needs to be read into a `vector<3x4x5xf32>`. Since the
///     permutation map is not full rank, there must be a broadcast along vector
///     dimension `1`.
/// 
///     A notional lowering of vector.transfer_read could generate code resembling:
/// 
///     ```mlir
///     // %expr1, %expr2, %expr3, %expr4 defined before this point
///     // alloc a temporary buffer for performing the "gather" of the slice.
///     %tmp = memref.alloc() : memref<vector<3x4x5xf32>>
///     for %i = 0 to 3 {
///       affine.for %j = 0 to 4 {
///         affine.for %k = 0 to 5 {
///           // Note that this load does not involve %j.
///           %a = load %A[%expr1 + %k, %expr2, %expr3 + %i, %expr4] : memref<?x?x?x?xf32>
///           // Update the temporary gathered slice with the individual element
///           %slice = memref.load %tmp : memref<vector<3x4x5xf32>> -> vector<3x4x5xf32>
///           %updated = vector.insert %a, %slice[%i, %j, %k] : f32 into vector<3x4x5xf32>
///           memref.store %updated, %tmp : memref<vector<3x4x5xf32>>
///     }}}
///     // At this point we gathered the elements from the original
///     // memref into the desired vector layout, stored in the `%tmp` allocation.
///     %vec = memref.load %tmp : memref<vector<3x4x5xf32>> -> vector<3x4x5xf32>
///     ```
/// 
///     On a GPU one could then map `i`, `j`, `k` to blocks and threads. Notice that
///     the temporary storage footprint could conceptually be only `3 * 5` values but
///     `3 * 4 * 5` values are actually transferred between `%A` and `%tmp`.
/// 
///     Alternatively, if a notional vector broadcast operation were available, we
///     could avoid the loop on `%j` and the lowered code would resemble:
/// 
///     ```mlir
///     // %expr1, %expr2, %expr3, %expr4 defined before this point
///     %tmp = memref.alloc() : memref<vector<3x4x5xf32>>
///     for %i = 0 to 3 {
///       affine.for %k = 0 to 5 {
///         %a = load %A[%expr1 + %k, %expr2, %expr3 + %i, %expr4] : memref<?x?x?x?xf32>
///         %slice = memref.load %tmp : memref<vector<3x4x5xf32>> -> vector<3x4x5xf32>
///         // Here we only store to the first element in dimension one
///         %updated = vector.insert %a, %slice[%i, 0, %k] : f32 into vector<3x4x5xf32>
///         memref.store %updated, %tmp : memref<vector<3x4x5xf32>>
///     }}
///     // At this point we gathered the elements from the original
///     // memref into the desired vector layout, stored in the `%tmp` allocation.
///     // However we haven't replicated them alongside the first dimension, we need
///     // to broadcast now.
///     %partialVec = load %tmp : memref<vector<3x4x5xf32>> -> vector<3x4x5xf32>
///     %vec = broadcast %tmpvec, 1 : vector<3x4x5xf32>
///     ```
/// 
///     where `broadcast` broadcasts from element 0 to all others along the
///     specified dimension. This time, the number of loaded element is `3 * 5`
///     values.
///     An additional `1` broadcast is required. On a GPU this broadcast could be
///     implemented using a warp-shuffle if loop `j` were mapped to `threadIdx.x`.
/// 
///     Syntax
///     ```
///     operation ::= ssa-id `=` `vector.transfer_read` ssa-use-list
///       `{` attribute-entry `} :` memref-type `,` vector-type
///     ```
/// 
///     Example:
/// 
///     ```mlir
///     // Read the slice `%A[%i0, %i1:%i1+256, %i2:%i2+32]` into vector<32x256xf32>
///     // and pad with %f0 to handle the boundary case:
///     %f0 = arith.constant 0.0f : f32
///     affine.for %i0 = 0 to %0 {
///       affine.for %i1 = 0 to %1 step 256 {
///         affine.for %i2 = 0 to %2 step 32 {
///           %v = vector.transfer_read %A[%i0, %i1, %i2], (%f0)
///                {permutation_map: (d0, d1, d2) -> (d2, d1)} :
///                memref<?x?x?xf32>, vector<32x256xf32>
///     }}}
/// 
///     // or equivalently (rewrite with vector.transpose)
///     %f0 = arith.constant 0.0f : f32
///     affine.for %i0 = 0 to %0 {
///       affine.for %i1 = 0 to %1 step 256 {
///         affine.for %i2 = 0 to %2 step 32 {
///           %v0 = vector.transfer_read %A[%i0, %i1, %i2], (%f0)
///                {permutation_map: (d0, d1, d2) -> (d1, d2)} :
///                memref<?x?x?xf32>, vector<256x32xf32>
///           %v = vector.transpose %v0, [1, 0] :
///               vector<256x32xf32> to vector<32x256f32>
///     }}}
/// 
///     // Read the slice `%A[%i0, %i1]` (i.e. the element `%A[%i0, %i1]`) into
///     // vector<128xf32>. The underlying implementation will require a 1-D vector
///     // broadcast:
///     affine.for %i0 = 0 to %0 {
///       affine.for %i1 = 0 to %1 {
///         %3 = vector.transfer_read %A[%i0, %i1]
///              {permutation_map: (d0, d1) -> (0)} :
///              memref<?x?xf32>, vector<128xf32>
///       }
///     }
/// 
///     // Read from a memref with vector element type.
///     %4 = vector.transfer_read %arg1[%c3, %c3], %vf0
///       {permutation_map = (d0, d1)->(d0, d1)}
///         : memref<?x?xvector<4x3xf32>>, vector<1x1x4x3xf32>
/// 
///     // Read from a tensor with vector element type.
///     %4 = vector.transfer_read %arg1[%c3, %c3], %vf0
///       {permutation_map = (d0, d1)->(d0, d1)}
///         : tensor<?x?xvector<4x3xf32>>, vector<1x1x4x3xf32>
/// 
///     // Special encoding for 0-d transfer with 0-d tensor/memref, vector shape
///     // {1} and permutation_map () -> (0).
///     %0 = vector.transfer_read %arg0[], %f0 {permutation_map = affine_map<()->(0)>} :
///       tensor<f32>, vector<1xf32>
///     ```
class TransferReadOp;

} // namespace mlir::vector
namespace mlir::vector {

/// The vector.transfer_write op writes a supervector to memory.
/// The `vector.transfer_write` op performs a write from a
///     [vector](../LangRef.md#vector-type), supplied as its first operand, into a
///     slice within a [MemRef](../LangRef.md#memref-type) or a Ranked
///     [Tensor](../LangRef.md#tensor-type) of the same base elemental type,
///     supplied as its second operand.
/// 
///     A vector memref/tensor operand must have its vector element type match a
///     suffix (shape and element type) of the vector (e.g. memref<3x2x6x4x3xf32>,
///     vector<1x1x4x3xf32>). If the operand is a tensor, the operation returns a
///     new tensor of the same type.
/// 
///     The slice is further defined by a full-rank index within the MemRef/Tensor,
///     supplied as the operands `[2 .. 2 + rank(memref/tensor))` that defines the
///     starting point of the transfer (e.g. `%A[%i0, %i1, %i2, %i3]`).
/// 
///     The permutation_map [attribute](../LangRef.md#attributes) is an
///     [affine-map](Affine.md#affine-maps) which specifies the transposition on the
///     slice to match the vector shape. The permutation map may be implicit and
///     omitted from parsing and printing if it is the canonical minor identity map
///     (i.e. if it does not permute any dimension). In contrast to `transfer_read`,
///     write ops cannot have broadcast dimensions.
/// 
///     The size of the slice is specified by the size of the vector.
/// 
///     An optional SSA value `mask` may be specified to mask out elements written
///     to the MemRef/Tensor. The `mask` type is an `i1` vector with a shape that
///     matches how elements are written into the MemRef/Tensor, *after* applying
///     any permutation. Elements whose corresponding mask element is `0` are
///     masked out.
/// 
///     For every vector dimension, the boolean array attribute `in_bounds`
///     specifies if the transfer is guaranteed to be within the source bounds. If
///     set to "false", accesses (including the starting point) may run
///     out-of-bounds along the respective vector dimension as the index increases.
///     Non-vector dimensions *must* always be in-bounds. The `in_bounds` array
///     length has to be equal to the vector rank. This attribute has a default
///     value: `false` (i.e. "out-of-bounds"). When skipped in the textual IR, the
///     default value is assumed. Similarly, the OP printer will omit this
///     attribute when all dimensions are out-of-bounds (i.e. the default value is
///     used).
/// 
///      A `vector.transfer_write` can be lowered to a simple store if all
///      dimensions are specified to be within bounds and no `mask` was specified.
/// 
///     This operation is called 'write' by opposition to 'store' because the
///     super-vector granularity is generally not representable with a single
///     hardware register. A `vector.transfer_write` is thus a
///     mid-level abstraction that supports super-vectorization with non-effecting
///     padding for full-tile-only code. It is the responsibility of
///     `vector.transfer_write`'s implementation to ensure the memory writes are
///     valid. Different lowerings may be pertinent depending on the hardware
///     support.
/// 
///     Example:
/// 
///     ```mlir
///     // write vector<16x32x64xf32> into the slice
///     //   `%A[%i0, %i1:%i1+32, %i2:%i2+64, %i3:%i3+16]`:
///     for %i0 = 0 to %0 {
///       affine.for %i1 = 0 to %1 step 32 {
///         affine.for %i2 = 0 to %2 step 64 {
///           affine.for %i3 = 0 to %3 step 16 {
///             %val = `ssa-value` : vector<16x32x64xf32>
///             vector.transfer_write %val, %A[%i0, %i1, %i2, %i3]
///               {permutation_map: (d0, d1, d2, d3) -> (d3, d1, d2)} :
///               vector<16x32x64xf32>, memref<?x?x?x?xf32>
///     }}}}
/// 
///     // or equivalently (rewrite with vector.transpose)
///     for %i0 = 0 to %0 {
///       affine.for %i1 = 0 to %1 step 32 {
///         affine.for %i2 = 0 to %2 step 64 {
///           affine.for %i3 = 0 to %3 step 16 {
///             %val = `ssa-value` : vector<16x32x64xf32>
///             %valt = vector.transpose %val, [1, 2, 0] :
///                   vector<16x32x64xf32> -> vector<32x64x16xf32>
///             vector.transfer_write %valt, %A[%i0, %i1, %i2, %i3]
///               {permutation_map: (d0, d1, d2, d3) -> (d1, d2, d3)} :
///               vector<32x64x16xf32>, memref<?x?x?x?xf32>
///     }}}}
/// 
///     // write to a memref with vector element type.
///     vector.transfer_write %4, %arg1[%c3, %c3]
///       {permutation_map = (d0, d1)->(d0, d1)}
///         : vector<1x1x4x3xf32>, memref<?x?xvector<4x3xf32>>
/// 
///     // return a tensor where the vector is inserted into the source tensor.
///     %5 = vector.transfer_write %4, %arg1[%c3, %c3]
///       {permutation_map = (d0, d1)->(d0, d1)}
///         : vector<1x1x4x3xf32>, tensor<?x?xvector<4x3xf32>>
/// 
///     // Special encoding for 0-d transfer with 0-d tensor/memref, vector shape
///     // {1} and permutation_map () -> (0).
///     %1 = vector.transfer_write %0, %arg0[] {permutation_map = affine_map<()->(0)>} :
///       vector<1xf32>, tensor<f32>
///     ```
class TransferWriteOp;

} // namespace mlir::vector
namespace mlir::vector {

/// vector transpose operation
/// Takes a n-D vector and returns the transposed n-D vector defined by
///     the permutation of ranks in the n-sized integer array attribute (in case
///     of 0-D vectors the array attribute must be empty).
/// 
///     In the operation
/// 
///     ```mlir
///     %1 = vector.transpose %0, [i_1, .., i_n]
///       : vector<d_1 x .. x d_n x f32>
///       to vector<d_trans[0] x .. x d_trans[n-1] x f32>
///     ```
/// 
///     the `permutation` array [i_1, .., i_n] must be a permutation of [0, .., n-1].
/// 
///     Example:
/// 
///     ```mlir
///     %1 = vector.transpose %0, [1, 0] : vector<2x3xf32> to vector<3x2xf32>
/// 
///      [ [a, b, c],       [ [a, d],
///        [d, e, f] ]  ->    [b, e],
///                           [c, f] ]
///     ```
class TransposeOp;

} // namespace mlir::vector
namespace mlir::vector {

/// type_cast op converts a scalar memref to a vector memref
/// Performs a conversion from a memref with scalar element to a memref with a
///     *single* vector element, copying the shape of the memref to the vector. This
///     is the minimal viable operation that is required to makeke
///     super-vectorization operational. It can be seen as a special case of the
///     `view` operation but scoped in the super-vectorization context.
/// 
///     Example:
/// 
///     ```mlir
///     %A  = memref.alloc() : memref<5x4x3xf32>
///     %VA = vector.type_cast %A : memref<5x4x3xf32> to memref<vector<5x4x3xf32>>
///     ```
class TypeCastOp;

} // namespace mlir::vector
namespace mlir::vector {

/// Terminates and yields values from vector regions.
/// "vector.yield" yields an SSA value from the Vector dialect op region and
///     terminates the regions. The semantics of how the values are yielded is
///     defined by the parent operation.
///     If "vector.yield" has any operands, the operands must correspond to the
///     parent operation's results.
///     If the parent operation defines no value the vector.yield may be omitted
///     when printing the region.
class YieldOp;

} // namespace mlir::vector
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::VectorScaleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class VectorScaleOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  VectorScaleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.vscale", odsAttrs.getContext());
  }

  VectorScaleOpGenericAdaptorBase(VectorScaleOp op);

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
class VectorScaleOpGenericAdaptor : public detail::VectorScaleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::VectorScaleOpGenericAdaptorBase;
public:
  VectorScaleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  VectorScaleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : VectorScaleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  VectorScaleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : VectorScaleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  VectorScaleOpGenericAdaptor(RangeT values, const VectorScaleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = VectorScaleOp, typename = std::enable_if_t<std::is_same_v<LateInst, VectorScaleOp>>>
  VectorScaleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class VectorScaleOpAdaptor : public VectorScaleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using VectorScaleOpGenericAdaptor::VectorScaleOpGenericAdaptor;
  VectorScaleOpAdaptor(VectorScaleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class VectorScaleOp : public ::mlir::Op<VectorScaleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = VectorScaleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = VectorScaleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<VectorScaleOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<VectorScaleOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<VectorScaleOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.vscale");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res);
  static VectorScaleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res);
  static VectorScaleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static VectorScaleOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static VectorScaleOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static VectorScaleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static VectorScaleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VectorScaleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VectorScaleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VectorScaleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VectorScaleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VectorScaleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VectorScaleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VectorScaleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VectorScaleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::VectorScaleOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::BitCastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BitCastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BitCastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.bitcast", odsAttrs.getContext());
  }

  BitCastOpGenericAdaptorBase(BitCastOp op);

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
class BitCastOpGenericAdaptor : public detail::BitCastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BitCastOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  BitCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BitCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : BitCastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BitCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BitCastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BitCastOpGenericAdaptor(RangeT values, const BitCastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BitCastOp, typename = std::enable_if_t<std::is_same_v<LateInst, BitCastOp>>>
  BitCastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class BitCastOpAdaptor : public BitCastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BitCastOpGenericAdaptor::BitCastOpGenericAdaptor;
  BitCastOpAdaptor(BitCastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BitCastOp : public ::mlir::Op<BitCastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BitCastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BitCastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.bitcast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source);
  static BitCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source);
  static BitCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static BitCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static BitCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BitCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BitCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BitCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BitCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getSource().getType());
  }
  VectorType getResultVectorType() {
    return ::llvm::cast<VectorType>(getResult().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::BitCastOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::BroadcastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BroadcastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BroadcastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.broadcast", odsAttrs.getContext());
  }

  BroadcastOpGenericAdaptorBase(BroadcastOp op);

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
class BroadcastOpGenericAdaptor : public detail::BroadcastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BroadcastOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  BroadcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BroadcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : BroadcastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BroadcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BroadcastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BroadcastOpGenericAdaptor(RangeT values, const BroadcastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BroadcastOp, typename = std::enable_if_t<std::is_same_v<LateInst, BroadcastOp>>>
  BroadcastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class BroadcastOpAdaptor : public BroadcastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BroadcastOpGenericAdaptor::BroadcastOpGenericAdaptor;
  BroadcastOpAdaptor(BroadcastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BroadcastOp : public ::mlir::Op<BroadcastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BroadcastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BroadcastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<BroadcastOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.broadcast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::VectorType> getVector() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type vector, ::mlir::Value source);
  static BroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type vector, ::mlir::Value source);
  static BroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type vector, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static BroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static BroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  Type getSourceType() { return getSource().getType(); }
  VectorType getResultVectorType() {
    return ::llvm::cast<VectorType>(getVector().getType());
  }

  /// Return the dimensions of the result vector that were formerly ones in the
  /// source tensor and thus correspond to "dim-1" broadcasting.
  llvm::SetVector<int64_t> computeBroadcastedUnitDims();

  /// Broadcast `value` to a vector of `dstShape`, knowing that exactly the
  /// `broadcastedDims` dimensions in the dstShape are broadcasted.
  /// This requires (and asserts) that the broadcast is free of "dim-1"
  /// broadcasting.
  /// Since vector.broadcast only allows expanding leading dimensions, an extra
  /// vector.transpose may be inserted to make the broadcast possible.
  /// `value`, `dstShape` and `broadcastedDims` must be properly specified or
  /// the helper will assert. This means:
  ///   1. `dstShape` must not be empty.
  ///   2. `broadcastedDims` must be confined to [0 .. rank(value.getResultVectorType)]
  ///   2. `dstShape` trimmed of the dimensions specified in `broadcastedDims`
  //       must match the `value` shape.
  static Value createOrFoldBroadcastOp(
    OpBuilder &b, Value value,
    ArrayRef<int64_t> dstShape,
    const llvm::SetVector<int64_t> &broadcastedDims);
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::BroadcastOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::CompressStoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CompressStoreOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = ::mlir::IntegerAttr;
    alignmentTy alignment;

    auto getAlignment() const {
      auto &propStorage = this->alignment;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlignment(const ::mlir::IntegerAttr &propValue) {
      this->alignment = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
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
  CompressStoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.compressstore", odsAttrs.getContext());
  }

  CompressStoreOpGenericAdaptorBase(CompressStoreOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getAlignmentAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
    return attr;
  }

  ::std::optional<uint64_t> getAlignment();
};

} // namespace detail
template <typename RangeT>
class CompressStoreOpGenericAdaptor : public detail::CompressStoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CompressStoreOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_mask = 2;
  static constexpr int odsIndex_valueToStore = 3;
public:
  CompressStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CompressStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CompressStoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CompressStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CompressStoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CompressStoreOpGenericAdaptor(RangeT values, const CompressStoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CompressStoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, CompressStoreOp>>>
  CompressStoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBase() {
    return (*getODSOperands(0).begin());
  }

  RangeT getIndices() {
    return getODSOperands(1);
  }

  ValueT getMask() {
    return (*getODSOperands(2).begin());
  }

  ValueT getValueToStore() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CompressStoreOpAdaptor : public CompressStoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CompressStoreOpGenericAdaptor::CompressStoreOpGenericAdaptor;
  CompressStoreOpAdaptor(CompressStoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CompressStoreOp : public ::mlir::Op<CompressStoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CompressStoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CompressStoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_mask = 2;
  static constexpr int odsIndex_valueToStore = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.compressstore");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::VectorType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getValueToStore() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(3).begin());
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  ::mlir::OpOperand &getMaskMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValueToStoreMutable() {
    auto range = getODSOperandIndexAndLength(3);
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getAlignmentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
  }

  ::std::optional<uint64_t> getAlignment();
  void setAlignmentAttr(::mlir::IntegerAttr attr) {
    getProperties().alignment = attr;
  }

  void setAlignment(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeAlignmentAttr() {
      auto attr = getProperties().alignment;
      getProperties().alignment = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value base, ValueRange indices, Value mask, Value valueToStore, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static CompressStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value base, ValueRange indices, Value mask, Value valueToStore, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static CompressStoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value base, ValueRange indices, Value mask, Value valueToStore, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static CompressStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static CompressStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static CompressStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static CompressStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompressStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompressStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompressStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompressStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
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
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getBase().getType());
  }
  VectorType getMaskVectorType() {
    return ::llvm::cast<VectorType>(getMask().getType());
  }
  VectorType getVectorType() {
    return ::llvm::cast<VectorType>(getValueToStore().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::CompressStoreOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ConstantMaskOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConstantMaskOpGenericAdaptorBase {
public:
  struct Properties {
    using mask_dim_sizesTy = ::mlir::DenseI64ArrayAttr;
    mask_dim_sizesTy mask_dim_sizes;

    auto getMaskDimSizes() const {
      auto &propStorage = this->mask_dim_sizes;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setMaskDimSizes(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->mask_dim_sizes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.mask_dim_sizes == this->mask_dim_sizes &&
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
  ConstantMaskOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.constant_mask", odsAttrs.getContext());
  }

  ConstantMaskOpGenericAdaptorBase(ConstantMaskOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getMaskDimSizesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().mask_dim_sizes);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getMaskDimSizes();
};

} // namespace detail
template <typename RangeT>
class ConstantMaskOpGenericAdaptor : public detail::ConstantMaskOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConstantMaskOpGenericAdaptorBase;
public:
  ConstantMaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConstantMaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ConstantMaskOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConstantMaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConstantMaskOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConstantMaskOpGenericAdaptor(RangeT values, const ConstantMaskOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConstantMaskOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConstantMaskOp>>>
  ConstantMaskOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ConstantMaskOpAdaptor : public ConstantMaskOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConstantMaskOpGenericAdaptor::ConstantMaskOpGenericAdaptor;
  ConstantMaskOpAdaptor(ConstantMaskOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConstantMaskOp : public ::mlir::Op<ConstantMaskOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConstantMaskOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConstantMaskOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::VectorUnrollOpInterface::Trait<ConstantMaskOp>::getShapeForUnroll;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("mask_dim_sizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMaskDimSizesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMaskDimSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.constant_mask");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::DenseI64ArrayAttr getMaskDimSizesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().mask_dim_sizes);
  }

  ::llvm::ArrayRef<int64_t> getMaskDimSizes();
  void setMaskDimSizesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().mask_dim_sizes = attr;
  }

  void setMaskDimSizes(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType type, ConstantMaskKind kind);
  static ConstantMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType type, ConstantMaskKind kind);
  static ConstantMaskOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType type, ConstantMaskKind kind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::DenseI64ArrayAttr mask_dim_sizes);
  static ConstantMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::DenseI64ArrayAttr mask_dim_sizes);
  static ConstantMaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::DenseI64ArrayAttr mask_dim_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::DenseI64ArrayAttr mask_dim_sizes);
  static ConstantMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::DenseI64ArrayAttr mask_dim_sizes);
  static ConstantMaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::DenseI64ArrayAttr mask_dim_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::llvm::ArrayRef<int64_t> mask_dim_sizes);
  static ConstantMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::llvm::ArrayRef<int64_t> mask_dim_sizes);
  static ConstantMaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::llvm::ArrayRef<int64_t> mask_dim_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::ArrayRef<int64_t> mask_dim_sizes);
  static ConstantMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::ArrayRef<int64_t> mask_dim_sizes);
  static ConstantMaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::ArrayRef<int64_t> mask_dim_sizes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantMaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantMaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
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
  /// Return the result type of this op.
  VectorType getVectorType() {
    return cast<VectorType>(getOperation()->getResultTypes()[0]);
  }

  /// Return whether the mask is a uniform vector of `1`s.
  bool isAllOnesMask();
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ConstantMaskOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ContractionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ContractionOpGenericAdaptorBase {
public:
  struct Properties {
    using indexing_mapsTy = ::mlir::ArrayAttr;
    indexing_mapsTy indexing_maps;

    auto getIndexingMaps() const {
      auto &propStorage = this->indexing_maps;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setIndexingMaps(const ::mlir::ArrayAttr &propValue) {
      this->indexing_maps = propValue;
    }
    using iterator_typesTy = ::mlir::ArrayAttr;
    iterator_typesTy iterator_types;

    auto getIteratorTypes() const {
      auto &propStorage = this->iterator_types;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setIteratorTypes(const ::mlir::ArrayAttr &propValue) {
      this->iterator_types = propValue;
    }
    using kindTy = ::mlir::vector::CombiningKindAttr;
    kindTy kind;

    auto getKind() const {
      auto &propStorage = this->kind;
      return ::llvm::dyn_cast_or_null<::mlir::vector::CombiningKindAttr>(propStorage);
    }
    void setKind(const ::mlir::vector::CombiningKindAttr &propValue) {
      this->kind = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.indexing_maps == this->indexing_maps &&
        rhs.iterator_types == this->iterator_types &&
        rhs.kind == this->kind &&
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
  ContractionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.contract", odsAttrs.getContext());
  }

  ContractionOpGenericAdaptorBase(ContractionOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getIndexingMapsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().indexing_maps);
    return attr;
  }

  ::mlir::ArrayAttr getIndexingMaps();
  ::mlir::ArrayAttr getIteratorTypesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().iterator_types);
    return attr;
  }

  ::mlir::ArrayAttr getIteratorTypes();
  ::mlir::vector::CombiningKindAttr getKindAttr();
  ::mlir::vector::CombiningKind getKind();
};

} // namespace detail
template <typename RangeT>
class ContractionOpGenericAdaptor : public detail::ContractionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ContractionOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_acc = 2;
public:
  ContractionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ContractionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ContractionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ContractionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ContractionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ContractionOpGenericAdaptor(RangeT values, const ContractionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ContractionOp, typename = std::enable_if_t<std::is_same_v<LateInst, ContractionOp>>>
  ContractionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLhs() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRhs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getAcc() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ContractionOpAdaptor : public ContractionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ContractionOpGenericAdaptor::ContractionOpGenericAdaptor;
  ContractionOpAdaptor(ContractionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ContractionOp : public ::mlir::Op<ContractionOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::IndexingMapOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::vector::MaskableOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ContractionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ContractionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_acc = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::vector::MaskableOpInterface::Trait<ContractionOp>::isMasked;
  using ::mlir::vector::MaskableOpInterface::Trait<ContractionOp>::getMaskingOp;
  using ::mlir::vector::MaskableOpInterface::Trait<ContractionOp>::supportsPassthru;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("indexing_maps"), ::llvm::StringRef("iterator_types"), ::llvm::StringRef("kind")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIndexingMapsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIndexingMapsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIteratorTypesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIteratorTypesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getKindAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.contract");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAcc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAccMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getIndexingMapsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().indexing_maps);
  }

  ::mlir::ArrayAttr getIndexingMaps();
  ::mlir::ArrayAttr getIteratorTypesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().iterator_types);
  }

  ::mlir::ArrayAttr getIteratorTypes();
  ::mlir::vector::CombiningKindAttr getKindAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::vector::CombiningKindAttr>(getProperties().kind);
  }

  ::mlir::vector::CombiningKind getKind();
  void setIndexingMapsAttr(::mlir::ArrayAttr attr) {
    getProperties().indexing_maps = attr;
  }

  void setIteratorTypesAttr(::mlir::ArrayAttr attr) {
    getProperties().iterator_types = attr;
  }

  void setKindAttr(::mlir::vector::CombiningKindAttr attr) {
    getProperties().kind = attr;
  }

  void setKind(::mlir::vector::CombiningKind attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, Value acc, ArrayAttr indexingMaps, ArrayAttr iteratorTypes);
  static ContractionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, Value acc, ArrayAttr indexingMaps, ArrayAttr iteratorTypes);
  static ContractionOp create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, Value acc, ArrayAttr indexingMaps, ArrayAttr iteratorTypes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, Value acc, ArrayRef<ArrayRef<AffineExpr>> indexingExprs, ArrayRef<IteratorType> iteratorTypes);
  static ContractionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, Value acc, ArrayRef<ArrayRef<AffineExpr>> indexingExprs, ArrayRef<IteratorType> iteratorTypes);
  static ContractionOp create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, Value acc, ArrayRef<ArrayRef<AffineExpr>> indexingExprs, ArrayRef<IteratorType> iteratorTypes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, Value acc, ArrayAttr indexingMaps, ArrayAttr iteratorTypes, CombiningKind kind);
  static ContractionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, Value acc, ArrayAttr indexingMaps, ArrayAttr iteratorTypes, CombiningKind kind);
  static ContractionOp create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, Value acc, ArrayAttr indexingMaps, ArrayAttr iteratorTypes, CombiningKind kind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKindAttr kind);
  static ContractionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKindAttr kind);
  static ContractionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKindAttr kind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKindAttr kind);
  static ContractionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKindAttr kind);
  static ContractionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKindAttr kind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static ContractionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static ContractionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static ContractionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static ContractionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc, ::mlir::ArrayAttr indexing_maps, ::mlir::ArrayAttr iterator_types, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ContractionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ContractionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ContractionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ContractionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  mlir::Type getExpectedMaskType();
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  VectorType getLhsType() {
    return ::llvm::cast<VectorType>(getLhs().getType());
  }
  VectorType getRhsType() {
    return ::llvm::cast<VectorType>(getRhs().getType());
  }
  Type getAccType() { return getAcc().getType(); }
  Type getResultType() { return getResult().getType(); }
  SmallVector<StringRef> getTraitAttrNames();
  static unsigned getAccOperandIndex() { return 2; }

  llvm::SmallVector<::mlir::AffineMap, 4> getIndexingMapsArray() {
    return llvm::to_vector<4>(getIndexingMaps().getAsValueRange<::mlir::AffineMapAttr>());
  }

  // Returns the bounds of each dimension in the iteration space spanned
  // by the iterator types of this operation.
  void getIterationBounds(SmallVectorImpl<int64_t> &iterationBounds);

  // Returns a list of index maps, where there is a list entry for each
  // op indexing map attribute (i.e. one for each input and output, with
  // the output listed last). Each index map, maps from this operations
  // iteration space, to vector dimensions of the maps input/output.
  void getIterationIndexMap(
    std::vector<DenseMap<int64_t, int64_t>> &iterationIndexMap);

  std::vector<std::pair<int64_t, int64_t>> getContractingDimMap();
  std::vector<std::pair<int64_t, int64_t>> getBatchDimMap();

  static CombiningKind getDefaultKind() {
    return CombiningKind::ADD;
  }

  SmallVector<IteratorType> getIteratorTypesArray() {
    auto range =
        getIteratorTypes()
            .template getAsValueRange<IteratorTypeAttr, IteratorType>();
    return {range.begin(), range.end()};
  }

  //===------------------------------------------------------------------===//
  // IndexingMapOpInterface interface methods implementation.
  //===------------------------------------------------------------------===//
  ArrayRef<int64_t> getShape(OpOperand * opOperand) {
    Type t = opOperand->get().getType();
    if (auto vt = dyn_cast<VectorType>(t))
      return vt.getShape();
    return {};
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ContractionOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::CreateMaskOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateMaskOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CreateMaskOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.create_mask", odsAttrs.getContext());
  }

  CreateMaskOpGenericAdaptorBase(CreateMaskOp op);

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
class CreateMaskOpGenericAdaptor : public detail::CreateMaskOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateMaskOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  CreateMaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateMaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateMaskOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateMaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CreateMaskOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateMaskOpGenericAdaptor(RangeT values, const CreateMaskOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateMaskOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateMaskOp>>>
  CreateMaskOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return getODSOperands(0);
  }

private:
  RangeT odsOperands;
};
class CreateMaskOpAdaptor : public CreateMaskOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateMaskOpGenericAdaptor::CreateMaskOpGenericAdaptor;
  CreateMaskOpAdaptor(CreateMaskOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateMaskOp : public ::mlir::Op<CreateMaskOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateMaskOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateMaskOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::VectorUnrollOpInterface::Trait<CreateMaskOp>::getShapeForUnroll;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.create_mask");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getOperandsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType type, ArrayRef<OpFoldResult> mixedOperands);
  static CreateMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType type, ArrayRef<OpFoldResult> mixedOperands);
  static CreateMaskOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType type, ArrayRef<OpFoldResult> mixedOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::ValueRange operands);
  static CreateMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::ValueRange operands);
  static CreateMaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateMaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateMaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateMaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// Return the result type of this op.
  VectorType getVectorType() {
    return cast<VectorType>(getOperation()->getResultTypes()[0]);
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::CreateMaskOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::DeinterleaveOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeinterleaveOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DeinterleaveOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.deinterleave", odsAttrs.getContext());
  }

  DeinterleaveOpGenericAdaptorBase(DeinterleaveOp op);

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
class DeinterleaveOpGenericAdaptor : public detail::DeinterleaveOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeinterleaveOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  DeinterleaveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeinterleaveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeinterleaveOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeinterleaveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DeinterleaveOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeinterleaveOpGenericAdaptor(RangeT values, const DeinterleaveOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeinterleaveOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeinterleaveOp>>>
  DeinterleaveOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DeinterleaveOpAdaptor : public DeinterleaveOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeinterleaveOpGenericAdaptor::DeinterleaveOpGenericAdaptor;
  DeinterleaveOpAdaptor(DeinterleaveOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeinterleaveOp : public ::mlir::Op<DeinterleaveOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeinterleaveOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeinterleaveOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.deinterleave");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::VectorType> getRes1() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getRes2() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res1, ::mlir::Type res2, ::mlir::Value source);
  static DeinterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res1, ::mlir::Type res2, ::mlir::Value source);
  static DeinterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res1, ::mlir::Type res2, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source);
  static DeinterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source);
  static DeinterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static DeinterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static DeinterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeinterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeinterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeinterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeinterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeinterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeinterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeinterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeinterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getSource().getType());
  }
  VectorType getResultVectorType() {
    return ::llvm::cast<VectorType>(getRes1().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::DeinterleaveOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ExpandLoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExpandLoadOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = ::mlir::IntegerAttr;
    alignmentTy alignment;

    auto getAlignment() const {
      auto &propStorage = this->alignment;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlignment(const ::mlir::IntegerAttr &propValue) {
      this->alignment = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
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
  ExpandLoadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.expandload", odsAttrs.getContext());
  }

  ExpandLoadOpGenericAdaptorBase(ExpandLoadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getAlignmentAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
    return attr;
  }

  ::std::optional<uint64_t> getAlignment();
};

} // namespace detail
template <typename RangeT>
class ExpandLoadOpGenericAdaptor : public detail::ExpandLoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExpandLoadOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_mask = 2;
  static constexpr int odsIndex_pass_thru = 3;
public:
  ExpandLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExpandLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExpandLoadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExpandLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExpandLoadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExpandLoadOpGenericAdaptor(RangeT values, const ExpandLoadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExpandLoadOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExpandLoadOp>>>
  ExpandLoadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBase() {
    return (*getODSOperands(0).begin());
  }

  RangeT getIndices() {
    return getODSOperands(1);
  }

  ValueT getMask() {
    return (*getODSOperands(2).begin());
  }

  ValueT getPassThru() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ExpandLoadOpAdaptor : public ExpandLoadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExpandLoadOpGenericAdaptor::ExpandLoadOpGenericAdaptor;
  ExpandLoadOpAdaptor(ExpandLoadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExpandLoadOp : public ::mlir::Op<ExpandLoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExpandLoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExpandLoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_mask = 2;
  static constexpr int odsIndex_pass_thru = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.expandload");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::VectorType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getPassThru() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(3).begin());
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  ::mlir::OpOperand &getMaskMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPassThruMutable() {
    auto range = getODSOperandIndexAndLength(3);
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getAlignmentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
  }

  ::std::optional<uint64_t> getAlignment();
  void setAlignmentAttr(::mlir::IntegerAttr attr) {
    getProperties().alignment = attr;
  }

  void setAlignment(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeAlignmentAttr() {
      auto attr = getProperties().alignment;
      getProperties().alignment = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType resultType, Value base, ValueRange indices, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static ExpandLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType resultType, Value base, ValueRange indices, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static ExpandLoadOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType resultType, Value base, ValueRange indices, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static ExpandLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static ExpandLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static ExpandLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static ExpandLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExpandLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExpandLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExpandLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExpandLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
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
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getBase().getType());
  }
  VectorType getMaskVectorType() {
    return ::llvm::cast<VectorType>(getMask().getType());
  }
  VectorType getPassThruVectorType() {
    return ::llvm::cast<VectorType>(getPassThru().getType());
  }
  VectorType getVectorType() {
    return ::llvm::cast<VectorType>(getResult().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ExpandLoadOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ExtractOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtractOpGenericAdaptorBase {
public:
  struct Properties {
    using static_positionTy = ::mlir::DenseI64ArrayAttr;
    static_positionTy static_position;

    auto getStaticPosition() const {
      auto &propStorage = this->static_position;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticPosition(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_position = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.static_position == this->static_position &&
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
  ExtractOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.extract", odsAttrs.getContext());
  }

  ExtractOpGenericAdaptorBase(ExtractOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getStaticPositionAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_position);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticPosition();
};

} // namespace detail
template <typename RangeT>
class ExtractOpGenericAdaptor : public detail::ExtractOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtractOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dynamic_position = 1;
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

  ValueT getSource() {
    return (*getODSOperands(0).begin());
  }

  RangeT getDynamicPosition() {
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
class ExtractOp : public ::mlir::Op<ExtractOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpTrait::InferTypeOpAdaptor> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtractOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtractOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dynamic_position = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<ExtractOp>::inferResultRangesFromOptional;
  using ::mlir::InferTypeOpInterface::Trait<ExtractOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("static_position")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getStaticPositionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getStaticPositionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.extract");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getDynamicPosition() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDynamicPositionMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::DenseI64ArrayAttr getStaticPositionAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_position);
  }

  ::llvm::ArrayRef<int64_t> getStaticPosition();
  void setStaticPositionAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_position = attr;
  }

  void setStaticPosition(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, int64_t position);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, int64_t position);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, int64_t position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, OpFoldResult position);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, OpFoldResult position);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, OpFoldResult position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, ArrayRef<int64_t> position);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, ArrayRef<int64_t> position);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, ArrayRef<int64_t> position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, ArrayRef<OpFoldResult> position);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, ArrayRef<OpFoldResult> position);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, ArrayRef<OpFoldResult> position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static ExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static ExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
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
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
      static ::llvm::LogicalResult
      inferReturnTypes(::mlir::MLIRContext *context,
                              std::optional<::mlir::Location> location,
                              Adaptor adaptor,
                              ::llvm::SmallVectorImpl<::mlir::Type> &inferredReturnTypes);

  static bool isCompatibleReturnTypes(::mlir::TypeRange l, ::mlir::TypeRange r);


  // Integer to represent a poison index within a static and positive integer
  // range.
  static constexpr int64_t kPoisonIndex = -1;

  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getSource().getType());
  }

  /// Return a vector with all the static and dynamic position indices.
  SmallVector<OpFoldResult> getMixedPosition() {
    OpBuilder builder(getContext());
    return getMixedValues(getStaticPosition(), getDynamicPosition(), builder);
  }

  unsigned getNumIndices() {
    return getStaticPosition().size();
  }

  /// Return "true" if the op has at least one dynamic position.
  bool hasDynamicPosition() {
    return !getDynamicPosition().empty();
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ExtractOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ExtractStridedSliceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtractStridedSliceOpGenericAdaptorBase {
public:
  struct Properties {
    using offsetsTy = ::mlir::ArrayAttr;
    offsetsTy offsets;

    auto getOffsets() const {
      auto &propStorage = this->offsets;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setOffsets(const ::mlir::ArrayAttr &propValue) {
      this->offsets = propValue;
    }
    using sizesTy = ::mlir::ArrayAttr;
    sizesTy sizes;

    auto getSizes() const {
      auto &propStorage = this->sizes;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setSizes(const ::mlir::ArrayAttr &propValue) {
      this->sizes = propValue;
    }
    using stridesTy = ::mlir::ArrayAttr;
    stridesTy strides;

    auto getStrides() const {
      auto &propStorage = this->strides;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setStrides(const ::mlir::ArrayAttr &propValue) {
      this->strides = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.offsets == this->offsets &&
        rhs.sizes == this->sizes &&
        rhs.strides == this->strides &&
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
  ExtractStridedSliceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.extract_strided_slice", odsAttrs.getContext());
  }

  ExtractStridedSliceOpGenericAdaptorBase(ExtractStridedSliceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getOffsetsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().offsets);
    return attr;
  }

  ::mlir::ArrayAttr getOffsets();
  ::mlir::ArrayAttr getSizesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().sizes);
    return attr;
  }

  ::mlir::ArrayAttr getSizes();
  ::mlir::ArrayAttr getStridesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().strides);
    return attr;
  }

  ::mlir::ArrayAttr getStrides();
};

} // namespace detail
template <typename RangeT>
class ExtractStridedSliceOpGenericAdaptor : public detail::ExtractStridedSliceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtractStridedSliceOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  ExtractStridedSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExtractStridedSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExtractStridedSliceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExtractStridedSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExtractStridedSliceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExtractStridedSliceOpGenericAdaptor(RangeT values, const ExtractStridedSliceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExtractStridedSliceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExtractStridedSliceOp>>>
  ExtractStridedSliceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ExtractStridedSliceOpAdaptor : public ExtractStridedSliceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExtractStridedSliceOpGenericAdaptor::ExtractStridedSliceOpGenericAdaptor;
  ExtractStridedSliceOpAdaptor(ExtractStridedSliceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExtractStridedSliceOp : public ::mlir::Op<ExtractStridedSliceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtractStridedSliceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtractStridedSliceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("offsets"), ::llvm::StringRef("sizes"), ::llvm::StringRef("strides")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOffsetsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOffsetsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSizesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStridesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStridesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.extract_strided_slice");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getOffsetsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().offsets);
  }

  ::mlir::ArrayAttr getOffsets();
  ::mlir::ArrayAttr getSizesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().sizes);
  }

  ::mlir::ArrayAttr getSizes();
  ::mlir::ArrayAttr getStridesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().strides);
  }

  ::mlir::ArrayAttr getStrides();
  void setOffsetsAttr(::mlir::ArrayAttr attr) {
    getProperties().offsets = attr;
  }

  void setSizesAttr(::mlir::ArrayAttr attr) {
    getProperties().sizes = attr;
  }

  void setStridesAttr(::mlir::ArrayAttr attr) {
    getProperties().strides = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, ArrayRef<int64_t> offsets, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides);
  static ExtractStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, ArrayRef<int64_t> offsets, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides);
  static ExtractStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, ArrayRef<int64_t> offsets, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value source, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr sizes, ::mlir::ArrayAttr strides);
  static ExtractStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value source, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr sizes, ::mlir::ArrayAttr strides);
  static ExtractStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value source, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr sizes, ::mlir::ArrayAttr strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr sizes, ::mlir::ArrayAttr strides);
  static ExtractStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr sizes, ::mlir::ArrayAttr strides);
  static ExtractStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr sizes, ::mlir::ArrayAttr strides);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
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
  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getSource().getType());
  }
  void getOffsets(SmallVectorImpl<int64_t> &results);
  bool hasNonUnitStrides() {
    return llvm::any_of(getStrides(), [](Attribute attr) {
      return ::llvm::cast<IntegerAttr>(attr).getInt() != 1;
    });
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ExtractStridedSliceOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::FMAOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FMAOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FMAOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.fma", odsAttrs.getContext());
  }

  FMAOpGenericAdaptorBase(FMAOp op);

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
class FMAOpGenericAdaptor : public detail::FMAOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FMAOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_acc = 2;
public:
  FMAOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FMAOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : FMAOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FMAOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FMAOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FMAOpGenericAdaptor(RangeT values, const FMAOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FMAOp, typename = std::enable_if_t<std::is_same_v<LateInst, FMAOp>>>
  FMAOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLhs() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRhs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getAcc() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FMAOpAdaptor : public FMAOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FMAOpGenericAdaptor::FMAOpGenericAdaptor;
  FMAOpAdaptor(FMAOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FMAOp : public ::mlir::Op<FMAOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait, ::mlir::OpTrait::Elementwise, ::mlir::OpTrait::Scalarizable, ::mlir::OpTrait::Vectorizable, ::mlir::OpTrait::Tensorizable, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FMAOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FMAOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_acc = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.fma");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getAcc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAccMutable() {
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static FMAOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static FMAOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static FMAOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static FMAOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static FMAOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static FMAOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value acc);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FMAOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FMAOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FMAOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FMAOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FMAOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FMAOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FMAOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FMAOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  VectorType getVectorType() { return ::llvm::cast<VectorType>(getLhs().getType()); }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::FMAOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::FromElementsOp declarations
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
      odsOpName.emplace("vector.from_elements", odsAttrs.getContext());
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
class FromElementsOp : public ::mlir::Op<FromElementsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FromElementsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FromElementsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_elements = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.from_elements");
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

  ::mlir::TypedValue<::mlir::VectorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::ValueRange elements);
  static FromElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::ValueRange elements);
  static FromElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::ValueRange elements);
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
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::FromElementsOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::GatherOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GatherOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = ::mlir::IntegerAttr;
    alignmentTy alignment;

    auto getAlignment() const {
      auto &propStorage = this->alignment;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlignment(const ::mlir::IntegerAttr &propValue) {
      this->alignment = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
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
      odsOpName.emplace("vector.gather", odsAttrs.getContext());
  }

  GatherOpGenericAdaptorBase(GatherOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getAlignmentAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
    return attr;
  }

  ::std::optional<uint64_t> getAlignment();
};

} // namespace detail
template <typename RangeT>
class GatherOpGenericAdaptor : public detail::GatherOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GatherOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_offsets = 1;
  static constexpr int odsIndex_indices = 2;
  static constexpr int odsIndex_mask = 3;
  static constexpr int odsIndex_pass_thru = 4;
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

  ValueT getBase() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOffsets() {
    return getODSOperands(1);
  }

  ValueT getIndices() {
    return (*getODSOperands(2).begin());
  }

  ValueT getMask() {
    return (*getODSOperands(3).begin());
  }

  ValueT getPassThru() {
    return (*getODSOperands(4).begin());
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
class GatherOp : public ::mlir::Op<GatherOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<4>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::vector::MaskableOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GatherOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GatherOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_offsets = 1;
  static constexpr int odsIndex_indices = 2;
  static constexpr int odsIndex_mask = 3;
  static constexpr int odsIndex_pass_thru = 4;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::vector::MaskableOpInterface::Trait<GatherOp>::isMasked;
  using ::mlir::vector::MaskableOpInterface::Trait<GatherOp>::getMaskingOp;
  using ::mlir::vector::MaskableOpInterface::Trait<GatherOp>::supportsPassthru;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.gather");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getOffsets() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::VectorType> getIndices() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getPassThru() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(4).begin());
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getOffsetsMutable();
  ::mlir::OpOperand &getIndicesMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMaskMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPassThruMutable() {
    auto range = getODSOperandIndexAndLength(4);
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getAlignmentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
  }

  ::std::optional<uint64_t> getAlignment();
  void setAlignmentAttr(::mlir::IntegerAttr attr) {
    getProperties().alignment = attr;
  }

  void setAlignment(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeAlignmentAttr() {
      auto attr = getProperties().alignment;
      getProperties().alignment = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType resultType, Value base, ValueRange indices, Value index_vec, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType resultType, Value base, ValueRange indices, Value index_vec, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType resultType, Value base, ValueRange indices, Value index_vec, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  mlir::Type getExpectedMaskType();
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
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
  ShapedType getBaseType() { return getBase().getType(); }
  VectorType getIndexVectorType() { return getIndices().getType(); }
  VectorType getMaskVectorType() { return getMask().getType(); }
  VectorType getPassThruVectorType() { return getPassThru().getType(); }
  VectorType getVectorType() { return getResult().getType(); }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::GatherOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::InsertOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InsertOpGenericAdaptorBase {
public:
  struct Properties {
    using static_positionTy = ::mlir::DenseI64ArrayAttr;
    static_positionTy static_position;

    auto getStaticPosition() const {
      auto &propStorage = this->static_position;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticPosition(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_position = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.static_position == this->static_position &&
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
  InsertOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.insert", odsAttrs.getContext());
  }

  InsertOpGenericAdaptorBase(InsertOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getStaticPositionAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_position);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticPosition();
};

} // namespace detail
template <typename RangeT>
class InsertOpGenericAdaptor : public detail::InsertOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InsertOpGenericAdaptorBase;
  static constexpr int odsIndex_valueToStore = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_dynamic_position = 2;
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

  ValueT getValueToStore() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDest() {
    return (*getODSOperands(1).begin());
  }

  RangeT getDynamicPosition() {
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
class InsertOp : public ::mlir::Op<InsertOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InsertOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InsertOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_valueToStore = 0;
  static constexpr int odsIndex_dest = 1;
  static constexpr int odsIndex_dynamic_position = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<InsertOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("static_position")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getStaticPositionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getStaticPositionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.insert");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValueToStore() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getDynamicPosition() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getValueToStoreMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDynamicPositionMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::DenseI64ArrayAttr getStaticPositionAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_position);
  }

  ::llvm::ArrayRef<int64_t> getStaticPosition();
  void setStaticPositionAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_position = attr;
  }

  void setStaticPosition(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value dest);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value dest);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value dest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value dest, int64_t position);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value dest, int64_t position);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value dest, int64_t position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value dest, OpFoldResult position);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value dest, OpFoldResult position);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value dest, OpFoldResult position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value dest, ArrayRef<int64_t> position);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value dest, ArrayRef<int64_t> position);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value dest, ArrayRef<int64_t> position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value dest, ArrayRef<OpFoldResult> position);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value dest, ArrayRef<OpFoldResult> position);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value dest, ArrayRef<OpFoldResult> position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::mlir::DenseI64ArrayAttr static_position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static InsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
  static InsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ValueRange dynamic_position, ::llvm::ArrayRef<int64_t> static_position);
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
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
  // Integer to represent a poison index within a static and positive integer
  // range.
  static constexpr int64_t kPoisonIndex = -1;

  Type getValueToStoreType() { return getValueToStore().getType(); }
  VectorType getDestVectorType() {
    return ::llvm::cast<VectorType>(getDest().getType());
  }

  /// Return a vector with all the static and dynamic position indices.
  SmallVector<OpFoldResult> getMixedPosition() {
    OpBuilder builder(getContext());
    return getMixedValues(getStaticPosition(), getDynamicPosition(), builder);
  }

  unsigned getNumIndices() {
    return getStaticPosition().size();
  }

  bool hasDynamicPosition() {
    return llvm::any_of(getDynamicPosition(),
                        [](Value operand) { return operand != nullptr; });
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::InsertOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::InsertStridedSliceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InsertStridedSliceOpGenericAdaptorBase {
public:
  struct Properties {
    using offsetsTy = ::mlir::ArrayAttr;
    offsetsTy offsets;

    auto getOffsets() const {
      auto &propStorage = this->offsets;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setOffsets(const ::mlir::ArrayAttr &propValue) {
      this->offsets = propValue;
    }
    using stridesTy = ::mlir::ArrayAttr;
    stridesTy strides;

    auto getStrides() const {
      auto &propStorage = this->strides;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setStrides(const ::mlir::ArrayAttr &propValue) {
      this->strides = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.offsets == this->offsets &&
        rhs.strides == this->strides &&
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
  InsertStridedSliceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.insert_strided_slice", odsAttrs.getContext());
  }

  InsertStridedSliceOpGenericAdaptorBase(InsertStridedSliceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getOffsetsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().offsets);
    return attr;
  }

  ::mlir::ArrayAttr getOffsets();
  ::mlir::ArrayAttr getStridesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().strides);
    return attr;
  }

  ::mlir::ArrayAttr getStrides();
};

} // namespace detail
template <typename RangeT>
class InsertStridedSliceOpGenericAdaptor : public detail::InsertStridedSliceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InsertStridedSliceOpGenericAdaptorBase;
  static constexpr int odsIndex_valueToStore = 0;
  static constexpr int odsIndex_dest = 1;
public:
  InsertStridedSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InsertStridedSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : InsertStridedSliceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InsertStridedSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InsertStridedSliceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InsertStridedSliceOpGenericAdaptor(RangeT values, const InsertStridedSliceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InsertStridedSliceOp, typename = std::enable_if_t<std::is_same_v<LateInst, InsertStridedSliceOp>>>
  InsertStridedSliceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValueToStore() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDest() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class InsertStridedSliceOpAdaptor : public InsertStridedSliceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InsertStridedSliceOpGenericAdaptor::InsertStridedSliceOpGenericAdaptor;
  InsertStridedSliceOpAdaptor(InsertStridedSliceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InsertStridedSliceOp : public ::mlir::Op<InsertStridedSliceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InsertStridedSliceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InsertStridedSliceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_valueToStore = 0;
  static constexpr int odsIndex_dest = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("offsets"), ::llvm::StringRef("strides")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOffsetsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOffsetsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStridesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStridesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.insert_strided_slice");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getValueToStore() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getValueToStoreMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestMutable() {
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::ArrayAttr getOffsetsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().offsets);
  }

  ::mlir::ArrayAttr getOffsets();
  ::mlir::ArrayAttr getStridesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().strides);
  }

  ::mlir::ArrayAttr getStrides();
  void setOffsetsAttr(::mlir::ArrayAttr attr) {
    getProperties().offsets = attr;
  }

  void setStridesAttr(::mlir::ArrayAttr attr) {
    getProperties().strides = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value dest, ArrayRef<int64_t> offsets, ArrayRef<int64_t> strides);
  static InsertStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value dest, ArrayRef<int64_t> offsets, ArrayRef<int64_t> strides);
  static InsertStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value dest, ArrayRef<int64_t> offsets, ArrayRef<int64_t> strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr strides);
  static InsertStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr strides);
  static InsertStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr strides);
  static InsertStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr strides);
  static InsertStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr strides);
  static InsertStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr strides);
  static InsertStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::ArrayAttr offsets, ::mlir::ArrayAttr strides);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InsertStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertStridedSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InsertStridedSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
  // TODO: Rename
  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getValueToStore().getType());
  }
  VectorType getDestVectorType() {
    return ::llvm::cast<VectorType>(getDest().getType());
  }
  bool hasNonUnitStrides() {
    return llvm::any_of(getStrides(), [](Attribute attr) {
      return ::llvm::cast<IntegerAttr>(attr).getInt() != 1;
    });
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::InsertStridedSliceOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::InterleaveOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InterleaveOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  InterleaveOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.interleave", odsAttrs.getContext());
  }

  InterleaveOpGenericAdaptorBase(InterleaveOp op);

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
class InterleaveOpGenericAdaptor : public detail::InterleaveOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InterleaveOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
public:
  InterleaveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InterleaveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : InterleaveOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InterleaveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InterleaveOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InterleaveOpGenericAdaptor(RangeT values, const InterleaveOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InterleaveOp, typename = std::enable_if_t<std::is_same_v<LateInst, InterleaveOp>>>
  InterleaveOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLhs() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRhs() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class InterleaveOpAdaptor : public InterleaveOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InterleaveOpGenericAdaptor::InterleaveOpGenericAdaptor;
  InterleaveOpAdaptor(InterleaveOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InterleaveOp : public ::mlir::Op<InterleaveOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InterleaveOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InterleaveOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.interleave");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs);
  static InterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs);
  static InterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs);
  static InterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs);
  static InterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs);
  static InterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs);
  static InterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InterleaveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InterleaveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getLhs().getType());
  }
  VectorType getResultVectorType() {
    return ::llvm::cast<VectorType>(getResult().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::InterleaveOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::LoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoadOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = ::mlir::IntegerAttr;
    alignmentTy alignment;

    auto getAlignment() const {
      auto &propStorage = this->alignment;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlignment(const ::mlir::IntegerAttr &propValue) {
      this->alignment = propValue;
    }
    using nontemporalTy = ::mlir::BoolAttr;
    nontemporalTy nontemporal;

    auto getNontemporal() const {
      auto &propStorage = this->nontemporal;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setNontemporal(const ::mlir::BoolAttr &propValue) {
      this->nontemporal = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
        rhs.nontemporal == this->nontemporal &&
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
  LoadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.load", odsAttrs.getContext());
  }

  LoadOpGenericAdaptorBase(LoadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getNontemporalAttr();
  bool getNontemporal();
  ::mlir::IntegerAttr getAlignmentAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
    return attr;
  }

  ::std::optional<uint64_t> getAlignment();
};

} // namespace detail
template <typename RangeT>
class LoadOpGenericAdaptor : public detail::LoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoadOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
public:
  LoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LoadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LoadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LoadOpGenericAdaptor(RangeT values, const LoadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LoadOp, typename = std::enable_if_t<std::is_same_v<LateInst, LoadOp>>>
  LoadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBase() {
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
class LoadOpAdaptor : public LoadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LoadOpGenericAdaptor::LoadOpGenericAdaptor;
  LoadOpAdaptor(LoadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LoadOp : public ::mlir::Op<LoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment"), ::llvm::StringRef("nontemporal")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNontemporalAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNontemporalAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.load");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getBaseMutable() {
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::BoolAttr getNontemporalAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().nontemporal);
  }

  bool getNontemporal();
  ::mlir::IntegerAttr getAlignmentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
  }

  ::std::optional<uint64_t> getAlignment();
  void setNontemporalAttr(::mlir::BoolAttr attr) {
    getProperties().nontemporal = attr;
  }

  void setNontemporal(::std::optional<bool> attrValue);
  void setAlignmentAttr(::mlir::IntegerAttr attr) {
    getProperties().alignment = attr;
  }

  void setAlignment(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeNontemporalAttr() {
      auto attr = getProperties().nontemporal;
      getProperties().nontemporal = {};
      return attr;
  }

  ::mlir::Attribute removeAlignmentAttr() {
      auto attr = getProperties().alignment;
      getProperties().alignment = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType resultType, Value base, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType resultType, Value base, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType resultType, Value base, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, Value base, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, Value base, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, Value base, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
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
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getBase().getType());
  }

  VectorType getVectorType() {
    return ::llvm::cast<VectorType>(getResult().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::LoadOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::MaskOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MaskOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MaskOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.mask", odsAttrs.getContext());
  }

  MaskOpGenericAdaptorBase(MaskOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getMaskRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class MaskOpGenericAdaptor : public detail::MaskOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MaskOpGenericAdaptorBase;
  static constexpr int odsIndex_mask = 0;
  static constexpr int odsIndex_passthru = 1;
public:
  MaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MaskOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MaskOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MaskOpGenericAdaptor(RangeT values, const MaskOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MaskOp, typename = std::enable_if_t<std::is_same_v<LateInst, MaskOp>>>
  MaskOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMask() {
    return (*getODSOperands(0).begin());
  }

  ValueT getPassthru() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MaskOpAdaptor : public MaskOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MaskOpGenericAdaptor::MaskOpGenericAdaptor;
  MaskOpAdaptor(MaskOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MaskOp : public ::mlir::Op<MaskOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<vector::YieldOp>::Impl, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::OpInvariants, ::mlir::vector::MaskingOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MaskOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MaskOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_mask = 0;
  static constexpr int odsIndex_passthru = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.mask");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getPassthru() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::OpOperand &getMaskMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getPassthruMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
  }

  ::mlir::Region &getMaskRegion() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value mask, Operation *maskableOp, function_ref<void(OpBuilder &, Operation *)> maskRegion);
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value mask, Operation *maskableOp, function_ref<void(OpBuilder &, Operation *)> maskRegion);
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, Value mask, Operation *maskableOp, function_ref<void(OpBuilder &, Operation *)> maskRegion);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, Value mask, Operation *maskableOp, function_ref<void(OpBuilder &, Operation *)> maskRegion);
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, Value mask, Operation *maskableOp, function_ref<void(OpBuilder &, Operation *)> maskRegion);
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, Value mask, Operation *maskableOp, function_ref<void(OpBuilder &, Operation *)> maskRegion);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, Value mask, Value passthru, Operation *maskableOp, function_ref<void(OpBuilder &, Operation *)> maskRegion);
  static MaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, Value mask, Value passthru, Operation *maskableOp, function_ref<void(OpBuilder &, Operation *)> maskRegion);
  static MaskOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, Value mask, Value passthru, Operation *maskableOp, function_ref<void(OpBuilder &, Operation *)> maskRegion);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  Operation *getMaskableOp();
  bool hasPassthru();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
  Block *getMaskBlock() { return &getMaskRegion().front(); }

  /// Returns true if mask op is not masking any operation.
  bool isEmpty() {
    Block *block = getMaskBlock();
    if (block->getOperations().size() > 1)
      return false;
    return true;
  }

  static void ensureTerminator(Region &region, Builder &builder,
                               Location loc);
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::MaskOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::MaskedLoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MaskedLoadOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = ::mlir::IntegerAttr;
    alignmentTy alignment;

    auto getAlignment() const {
      auto &propStorage = this->alignment;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlignment(const ::mlir::IntegerAttr &propValue) {
      this->alignment = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
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
  MaskedLoadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.maskedload", odsAttrs.getContext());
  }

  MaskedLoadOpGenericAdaptorBase(MaskedLoadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getAlignmentAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
    return attr;
  }

  ::std::optional<uint64_t> getAlignment();
};

} // namespace detail
template <typename RangeT>
class MaskedLoadOpGenericAdaptor : public detail::MaskedLoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MaskedLoadOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_mask = 2;
  static constexpr int odsIndex_pass_thru = 3;
public:
  MaskedLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MaskedLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MaskedLoadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MaskedLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MaskedLoadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MaskedLoadOpGenericAdaptor(RangeT values, const MaskedLoadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MaskedLoadOp, typename = std::enable_if_t<std::is_same_v<LateInst, MaskedLoadOp>>>
  MaskedLoadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBase() {
    return (*getODSOperands(0).begin());
  }

  RangeT getIndices() {
    return getODSOperands(1);
  }

  ValueT getMask() {
    return (*getODSOperands(2).begin());
  }

  ValueT getPassThru() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MaskedLoadOpAdaptor : public MaskedLoadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MaskedLoadOpGenericAdaptor::MaskedLoadOpGenericAdaptor;
  MaskedLoadOpAdaptor(MaskedLoadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MaskedLoadOp : public ::mlir::Op<MaskedLoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MaskedLoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MaskedLoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_mask = 2;
  static constexpr int odsIndex_pass_thru = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.maskedload");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::VectorType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getPassThru() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(3).begin());
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  ::mlir::OpOperand &getMaskMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPassThruMutable() {
    auto range = getODSOperandIndexAndLength(3);
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getAlignmentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
  }

  ::std::optional<uint64_t> getAlignment();
  void setAlignmentAttr(::mlir::IntegerAttr attr) {
    getProperties().alignment = attr;
  }

  void setAlignment(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeAlignmentAttr() {
      auto attr = getProperties().alignment;
      getProperties().alignment = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType resultType, Value base, ValueRange indices, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType resultType, Value base, ValueRange indices, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType resultType, Value base, ValueRange indices, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, Value base, ValueRange indices, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, Value base, ValueRange indices, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, Value base, ValueRange indices, Value mask, Value passthrough, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value pass_thru, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
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
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getBase().getType());
  }
  VectorType getMaskVectorType() {
    return ::llvm::cast<VectorType>(getMask().getType());
  }
  VectorType getPassThruVectorType() {
    return ::llvm::cast<VectorType>(getPassThru().getType());
  }
  VectorType getVectorType() {
    return ::llvm::cast<VectorType>(getResult().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::MaskedLoadOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::MaskedStoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MaskedStoreOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = ::mlir::IntegerAttr;
    alignmentTy alignment;

    auto getAlignment() const {
      auto &propStorage = this->alignment;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlignment(const ::mlir::IntegerAttr &propValue) {
      this->alignment = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
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
  MaskedStoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.maskedstore", odsAttrs.getContext());
  }

  MaskedStoreOpGenericAdaptorBase(MaskedStoreOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getAlignmentAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
    return attr;
  }

  ::std::optional<uint64_t> getAlignment();
};

} // namespace detail
template <typename RangeT>
class MaskedStoreOpGenericAdaptor : public detail::MaskedStoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MaskedStoreOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_mask = 2;
  static constexpr int odsIndex_valueToStore = 3;
public:
  MaskedStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MaskedStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MaskedStoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MaskedStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MaskedStoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MaskedStoreOpGenericAdaptor(RangeT values, const MaskedStoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MaskedStoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, MaskedStoreOp>>>
  MaskedStoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBase() {
    return (*getODSOperands(0).begin());
  }

  RangeT getIndices() {
    return getODSOperands(1);
  }

  ValueT getMask() {
    return (*getODSOperands(2).begin());
  }

  ValueT getValueToStore() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MaskedStoreOpAdaptor : public MaskedStoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MaskedStoreOpGenericAdaptor::MaskedStoreOpGenericAdaptor;
  MaskedStoreOpAdaptor(MaskedStoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MaskedStoreOp : public ::mlir::Op<MaskedStoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MaskedStoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MaskedStoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_mask = 2;
  static constexpr int odsIndex_valueToStore = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.maskedstore");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::VectorType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getValueToStore() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(3).begin());
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  ::mlir::OpOperand &getMaskMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValueToStoreMutable() {
    auto range = getODSOperandIndexAndLength(3);
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getAlignmentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
  }

  ::std::optional<uint64_t> getAlignment();
  void setAlignmentAttr(::mlir::IntegerAttr attr) {
    getProperties().alignment = attr;
  }

  void setAlignment(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeAlignmentAttr() {
      auto attr = getProperties().alignment;
      getProperties().alignment = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value base, ValueRange indices, Value mask, Value valueToStore, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static MaskedStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value base, ValueRange indices, Value mask, Value valueToStore, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static MaskedStoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value base, ValueRange indices, Value mask, Value valueToStore, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static MaskedStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static MaskedStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static MaskedStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static MaskedStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedStoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
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
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getBase().getType());
  }
  VectorType getMaskVectorType() {
    return ::llvm::cast<VectorType>(getMask().getType());
  }
  VectorType getVectorType() {
    return ::llvm::cast<VectorType>(getValueToStore().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::MaskedStoreOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::MultiDimReductionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MultiDimReductionOpGenericAdaptorBase {
public:
  struct Properties {
    using kindTy = ::mlir::vector::CombiningKindAttr;
    kindTy kind;

    auto getKind() const {
      auto &propStorage = this->kind;
      return ::llvm::cast<::mlir::vector::CombiningKindAttr>(propStorage);
    }
    void setKind(const ::mlir::vector::CombiningKindAttr &propValue) {
      this->kind = propValue;
    }
    using reduction_dimsTy = ::mlir::DenseI64ArrayAttr;
    reduction_dimsTy reduction_dims;

    auto getReductionDims() const {
      auto &propStorage = this->reduction_dims;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setReductionDims(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->reduction_dims = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.kind == this->kind &&
        rhs.reduction_dims == this->reduction_dims &&
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
  MultiDimReductionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.multi_reduction", odsAttrs.getContext());
  }

  MultiDimReductionOpGenericAdaptorBase(MultiDimReductionOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::vector::CombiningKindAttr getKindAttr() {
    auto attr = ::llvm::cast<::mlir::vector::CombiningKindAttr>(getProperties().kind);
    return attr;
  }

  ::mlir::vector::CombiningKind getKind();
  ::mlir::DenseI64ArrayAttr getReductionDimsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().reduction_dims);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getReductionDims();
};

} // namespace detail
template <typename RangeT>
class MultiDimReductionOpGenericAdaptor : public detail::MultiDimReductionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MultiDimReductionOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_acc = 1;
public:
  MultiDimReductionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MultiDimReductionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MultiDimReductionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MultiDimReductionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MultiDimReductionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MultiDimReductionOpGenericAdaptor(RangeT values, const MultiDimReductionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MultiDimReductionOp, typename = std::enable_if_t<std::is_same_v<LateInst, MultiDimReductionOp>>>
  MultiDimReductionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getAcc() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MultiDimReductionOpAdaptor : public MultiDimReductionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MultiDimReductionOpGenericAdaptor::MultiDimReductionOpGenericAdaptor;
  MultiDimReductionOpAdaptor(MultiDimReductionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MultiDimReductionOp : public ::mlir::Op<MultiDimReductionOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::vector::MaskableOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MultiDimReductionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MultiDimReductionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_acc = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<MultiDimReductionOp>::refineReturnTypes;
  using ::mlir::vector::MaskableOpInterface::Trait<MultiDimReductionOp>::isMasked;
  using ::mlir::vector::MaskableOpInterface::Trait<MultiDimReductionOp>::getMaskingOp;
  using ::mlir::vector::MaskableOpInterface::Trait<MultiDimReductionOp>::supportsPassthru;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("kind"), ::llvm::StringRef("reduction_dims")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getKindAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getReductionDimsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getReductionDimsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.multi_reduction");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAcc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAccMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  ::mlir::vector::CombiningKindAttr getKindAttr() {
    return ::llvm::cast<::mlir::vector::CombiningKindAttr>(getProperties().kind);
  }

  ::mlir::vector::CombiningKind getKind();
  ::mlir::DenseI64ArrayAttr getReductionDimsAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().reduction_dims);
  }

  ::llvm::ArrayRef<int64_t> getReductionDims();
  void setKindAttr(::mlir::vector::CombiningKindAttr attr) {
    getProperties().kind = attr;
  }

  void setKind(::mlir::vector::CombiningKind attrValue);
  void setReductionDimsAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().reduction_dims = attr;
  }

  void setReductionDims(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, Value acc, ArrayRef<bool> reductionMask, CombiningKind kind);
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, Value acc, ArrayRef<bool> reductionMask, CombiningKind kind);
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, Value acc, ArrayRef<bool> reductionMask, CombiningKind kind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value acc, ::mlir::DenseI64ArrayAttr reduction_dims);
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value acc, ::mlir::DenseI64ArrayAttr reduction_dims);
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value acc, ::mlir::DenseI64ArrayAttr reduction_dims);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value acc, ::mlir::DenseI64ArrayAttr reduction_dims);
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value acc, ::mlir::DenseI64ArrayAttr reduction_dims);
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value acc, ::mlir::DenseI64ArrayAttr reduction_dims);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value acc, ::mlir::DenseI64ArrayAttr reduction_dims);
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value acc, ::mlir::DenseI64ArrayAttr reduction_dims);
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value acc, ::mlir::DenseI64ArrayAttr reduction_dims);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value acc, ::llvm::ArrayRef<int64_t> reduction_dims);
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value acc, ::llvm::ArrayRef<int64_t> reduction_dims);
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value acc, ::llvm::ArrayRef<int64_t> reduction_dims);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value acc, ::llvm::ArrayRef<int64_t> reduction_dims);
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value acc, ::llvm::ArrayRef<int64_t> reduction_dims);
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value acc, ::llvm::ArrayRef<int64_t> reduction_dims);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value acc, ::llvm::ArrayRef<int64_t> reduction_dims);
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value acc, ::llvm::ArrayRef<int64_t> reduction_dims);
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value acc, ::llvm::ArrayRef<int64_t> reduction_dims);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MultiDimReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MultiDimReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  mlir::Type getExpectedMaskType();
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
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
  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getSource().getType());
  }
  Type getDestType() {
    return getDest().getType();
  }

  bool isReducedDim(int64_t d) {
    assert(d >= 0 && d < static_cast<int64_t>(getReductionMask().size()) &&
      "d overflows the number of dims");
    return getReductionMask()[d];
  }

  SmallVector<bool> getReductionMask() {
    SmallVector<bool> res(getSourceVectorType().getRank(), false);
    for (int64_t dim : getReductionDims())
      res[dim] = true;
    return res;
  }
  static SmallVector<bool> getReductionMask(
      ArrayRef<int64_t> reductionDims, unsigned sourceRank) {
    SmallVector<bool> res(sourceRank, false);
    for (auto idx : reductionDims)
      res[idx] = true;
    return res;
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::MultiDimReductionOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::OuterProductOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OuterProductOpGenericAdaptorBase {
public:
  struct Properties {
    using kindTy = ::mlir::vector::CombiningKindAttr;
    kindTy kind;

    auto getKind() const {
      auto &propStorage = this->kind;
      return ::llvm::dyn_cast_or_null<::mlir::vector::CombiningKindAttr>(propStorage);
    }
    void setKind(const ::mlir::vector::CombiningKindAttr &propValue) {
      this->kind = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.kind == this->kind &&
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
  OuterProductOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.outerproduct", odsAttrs.getContext());
  }

  OuterProductOpGenericAdaptorBase(OuterProductOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::vector::CombiningKindAttr getKindAttr();
  ::mlir::vector::CombiningKind getKind();
};

} // namespace detail
template <typename RangeT>
class OuterProductOpGenericAdaptor : public detail::OuterProductOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OuterProductOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_acc = 2;
public:
  OuterProductOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OuterProductOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : OuterProductOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OuterProductOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OuterProductOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OuterProductOpGenericAdaptor(RangeT values, const OuterProductOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OuterProductOp, typename = std::enable_if_t<std::is_same_v<LateInst, OuterProductOp>>>
  OuterProductOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLhs() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRhs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getAcc() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class OuterProductOpAdaptor : public OuterProductOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OuterProductOpGenericAdaptor::OuterProductOpGenericAdaptor;
  OuterProductOpAdaptor(OuterProductOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OuterProductOp : public ::mlir::Op<OuterProductOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::vector::MaskableOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OuterProductOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OuterProductOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_acc = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::vector::MaskableOpInterface::Trait<OuterProductOp>::isMasked;
  using ::mlir::vector::MaskableOpInterface::Trait<OuterProductOp>::getMaskingOp;
  using ::mlir::vector::MaskableOpInterface::Trait<OuterProductOp>::supportsPassthru;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("kind")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getKindAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.outerproduct");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getAcc() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::VectorType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*operands.begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getAccMutable();
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
  ::mlir::vector::CombiningKindAttr getKindAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::vector::CombiningKindAttr>(getProperties().kind);
  }

  ::mlir::vector::CombiningKind getKind();
  void setKindAttr(::mlir::vector::CombiningKindAttr attr) {
    getProperties().kind = attr;
  }

  void setKind(::mlir::vector::CombiningKind attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, Value acc);
  static OuterProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, Value acc);
  static OuterProductOp create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, Value acc);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKindAttr kind);
  static OuterProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKindAttr kind);
  static OuterProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKindAttr kind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKindAttr kind);
  static OuterProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKindAttr kind);
  static OuterProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKindAttr kind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static OuterProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static OuterProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static OuterProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static OuterProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::Value acc, ::mlir::vector::CombiningKind kind = CombiningKind::ADD);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OuterProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OuterProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OuterProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OuterProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  mlir::Type getExpectedMaskType();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  VectorType getOperandVectorTypeLHS() {
    return ::llvm::cast<VectorType>(getLhs().getType());
  }
  Type getOperandTypeRHS() {
    return getRhs().getType();
  }
  VectorType getOperandVectorTypeACC() {
    return getAcc()
      ? ::llvm::cast<VectorType>(getAcc().getType())
      : VectorType();
  }
  VectorType getResultVectorType() {
    return ::llvm::cast<VectorType>(getResult().getType());
  }
  static CombiningKind getDefaultKind() {
    return CombiningKind::ADD;
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::OuterProductOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::PrintOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PrintOpGenericAdaptorBase {
public:
  struct Properties {
    using punctuationTy = ::mlir::vector::PrintPunctuationAttr;
    punctuationTy punctuation;

    auto getPunctuation() const {
      auto &propStorage = this->punctuation;
      return ::llvm::dyn_cast_or_null<::mlir::vector::PrintPunctuationAttr>(propStorage);
    }
    void setPunctuation(const ::mlir::vector::PrintPunctuationAttr &propValue) {
      this->punctuation = propValue;
    }
    using stringLiteralTy = ::mlir::StringAttr;
    stringLiteralTy stringLiteral;

    auto getStringLiteral() const {
      auto &propStorage = this->stringLiteral;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setStringLiteral(const ::mlir::StringAttr &propValue) {
      this->stringLiteral = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.punctuation == this->punctuation &&
        rhs.stringLiteral == this->stringLiteral &&
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
  PrintOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.print", odsAttrs.getContext());
  }

  PrintOpGenericAdaptorBase(PrintOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::vector::PrintPunctuationAttr getPunctuationAttr();
  ::mlir::vector::PrintPunctuation getPunctuation();
  ::mlir::StringAttr getStringLiteralAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().stringLiteral);
    return attr;
  }

  ::std::optional<::mlir::StringAttr> getStringLiteral();
};

} // namespace detail
template <typename RangeT>
class PrintOpGenericAdaptor : public detail::PrintOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PrintOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  PrintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PrintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PrintOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PrintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PrintOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PrintOpGenericAdaptor(RangeT values, const PrintOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PrintOp, typename = std::enable_if_t<std::is_same_v<LateInst, PrintOp>>>
  PrintOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSource() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PrintOpAdaptor : public PrintOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PrintOpGenericAdaptor::PrintOpGenericAdaptor;
  PrintOpAdaptor(PrintOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PrintOp : public ::mlir::Op<PrintOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PrintOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PrintOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("punctuation"), ::llvm::StringRef("stringLiteral")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPunctuationAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPunctuationAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStringLiteralAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStringLiteralAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.print");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getSource() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getSourceMutable();
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
  ::mlir::vector::PrintPunctuationAttr getPunctuationAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::vector::PrintPunctuationAttr>(getProperties().punctuation);
  }

  ::mlir::vector::PrintPunctuation getPunctuation();
  ::mlir::StringAttr getStringLiteralAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().stringLiteral);
  }

  ::std::optional<::mlir::StringAttr> getStringLiteral();
  void setPunctuationAttr(::mlir::vector::PrintPunctuationAttr attr) {
    getProperties().punctuation = attr;
  }

  void setPunctuation(::mlir::vector::PrintPunctuation attrValue);
  void setStringLiteralAttr(::mlir::StringAttr attr) {
    getProperties().stringLiteral = attr;
  }

  ::mlir::Attribute removeStringLiteralAttr() {
      auto attr = getProperties().stringLiteral;
      getProperties().stringLiteral = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, PrintPunctuation punctuation);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, PrintPunctuation punctuation);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, PrintPunctuation punctuation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, PrintPunctuation punctuation);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, PrintPunctuation punctuation);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, PrintPunctuation punctuation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef string);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef string);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef string);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuationAttr punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuationAttr punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuationAttr punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuationAttr punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuationAttr punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuationAttr punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuation punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuation punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuation punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuation punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuation punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value source, ::mlir::vector::PrintPunctuation punctuation, /*optional*/::mlir::StringAttr stringLiteral);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
  Type getPrintType() {
    return getSource().getType();
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::PrintOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ReductionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReductionOpGenericAdaptorBase {
public:
  struct Properties {
    using fastmathTy = ::mlir::arith::FastMathFlagsAttr;
    fastmathTy fastmath;

    auto getFastmath() const {
      auto &propStorage = this->fastmath;
      return ::llvm::dyn_cast_or_null<::mlir::arith::FastMathFlagsAttr>(propStorage);
    }
    void setFastmath(const ::mlir::arith::FastMathFlagsAttr &propValue) {
      this->fastmath = propValue;
    }
    using kindTy = ::mlir::vector::CombiningKindAttr;
    kindTy kind;

    auto getKind() const {
      auto &propStorage = this->kind;
      return ::llvm::cast<::mlir::vector::CombiningKindAttr>(propStorage);
    }
    void setKind(const ::mlir::vector::CombiningKindAttr &propValue) {
      this->kind = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fastmath == this->fastmath &&
        rhs.kind == this->kind &&
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
  ReductionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.reduction", odsAttrs.getContext());
  }

  ReductionOpGenericAdaptorBase(ReductionOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::vector::CombiningKindAttr getKindAttr() {
    auto attr = ::llvm::cast<::mlir::vector::CombiningKindAttr>(getProperties().kind);
    return attr;
  }

  ::mlir::vector::CombiningKind getKind();
  ::mlir::arith::FastMathFlagsAttr getFastmathAttr();
  ::mlir::arith::FastMathFlags getFastmath();
};

} // namespace detail
template <typename RangeT>
class ReductionOpGenericAdaptor : public detail::ReductionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReductionOpGenericAdaptorBase;
  static constexpr int odsIndex_vector = 0;
  static constexpr int odsIndex_acc = 1;
public:
  ReductionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReductionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReductionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReductionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReductionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReductionOpGenericAdaptor(RangeT values, const ReductionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReductionOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReductionOp>>>
  ReductionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getVector() {
    return (*getODSOperands(0).begin());
  }

  ValueT getAcc() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReductionOpAdaptor : public ReductionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReductionOpGenericAdaptor::ReductionOpGenericAdaptor;
  ReductionOpAdaptor(ReductionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReductionOp : public ::mlir::Op<ReductionOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::arith::ArithFastMathInterface::Trait, ::mlir::vector::MaskableOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReductionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReductionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_vector = 0;
  static constexpr int odsIndex_acc = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::arith::ArithFastMathInterface::Trait<ReductionOp>::getFastMathFlagsAttr;
  using ::mlir::arith::ArithFastMathInterface::Trait<ReductionOp>::getFastMathAttrName;
  using ::mlir::vector::MaskableOpInterface::Trait<ReductionOp>::isMasked;
  using ::mlir::vector::MaskableOpInterface::Trait<ReductionOp>::getMaskingOp;
  using ::mlir::vector::MaskableOpInterface::Trait<ReductionOp>::supportsPassthru;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fastmath"), ::llvm::StringRef("kind")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFastmathAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFastmathAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getKindAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.reduction");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getVector() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAcc() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::OpOperand &getVectorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getAccMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  ::mlir::vector::CombiningKindAttr getKindAttr() {
    return ::llvm::cast<::mlir::vector::CombiningKindAttr>(getProperties().kind);
  }

  ::mlir::vector::CombiningKind getKind();
  ::mlir::arith::FastMathFlagsAttr getFastmathAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::arith::FastMathFlagsAttr>(getProperties().fastmath);
  }

  ::mlir::arith::FastMathFlags getFastmath();
  void setKindAttr(::mlir::vector::CombiningKindAttr attr) {
    getProperties().kind = attr;
  }

  void setKind(::mlir::vector::CombiningKind attrValue);
  void setFastmathAttr(::mlir::arith::FastMathFlagsAttr attr) {
    getProperties().fastmath = attr;
  }

  void setFastmath(::mlir::arith::FastMathFlags attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, CombiningKind kind, Value vector, Value acc, ::mlir::arith::FastMathFlags fastMathFlags = ::mlir::arith::FastMathFlags::none);
  static ReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, CombiningKind kind, Value vector, Value acc, ::mlir::arith::FastMathFlags fastMathFlags = ::mlir::arith::FastMathFlags::none);
  static ReductionOp create(::mlir::ImplicitLocOpBuilder &builder, CombiningKind kind, Value vector, Value acc, ::mlir::arith::FastMathFlags fastMathFlags = ::mlir::arith::FastMathFlags::none);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, CombiningKind kind, Value vector, ::mlir::arith::FastMathFlags fastMathFlags = ::mlir::arith::FastMathFlags::none);
  static ReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, CombiningKind kind, Value vector, ::mlir::arith::FastMathFlags fastMathFlags = ::mlir::arith::FastMathFlags::none);
  static ReductionOp create(::mlir::ImplicitLocOpBuilder &builder, CombiningKind kind, Value vector, ::mlir::arith::FastMathFlags fastMathFlags = ::mlir::arith::FastMathFlags::none);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlagsAttr fastmath = nullptr);
  static ReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlagsAttr fastmath = nullptr);
  static ReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlagsAttr fastmath = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlagsAttr fastmath = nullptr);
  static ReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlagsAttr fastmath = nullptr);
  static ReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlagsAttr fastmath = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::vector::CombiningKind kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlags fastmath = ::mlir::arith::FastMathFlags::none);
  static ReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::vector::CombiningKind kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlags fastmath = ::mlir::arith::FastMathFlags::none);
  static ReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::vector::CombiningKind kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlags fastmath = ::mlir::arith::FastMathFlags::none);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKind kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlags fastmath = ::mlir::arith::FastMathFlags::none);
  static ReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKind kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlags fastmath = ::mlir::arith::FastMathFlags::none);
  static ReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKind kind, ::mlir::Value vector, /*optional*/::mlir::Value acc, ::mlir::arith::FastMathFlags fastmath = ::mlir::arith::FastMathFlags::none);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  mlir::Type getExpectedMaskType();
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
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
  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getVector().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ReductionOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ScalableExtractOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ScalableExtractOpGenericAdaptorBase {
public:
  struct Properties {
    using posTy = ::mlir::IntegerAttr;
    posTy pos;

    auto getPos() const {
      auto &propStorage = this->pos;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setPos(const ::mlir::IntegerAttr &propValue) {
      this->pos = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.pos == this->pos &&
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
  ScalableExtractOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.scalable.extract", odsAttrs.getContext());
  }

  ScalableExtractOpGenericAdaptorBase(ScalableExtractOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getPosAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().pos);
    return attr;
  }

  uint64_t getPos();
};

} // namespace detail
template <typename RangeT>
class ScalableExtractOpGenericAdaptor : public detail::ScalableExtractOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ScalableExtractOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  ScalableExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ScalableExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ScalableExtractOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ScalableExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ScalableExtractOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ScalableExtractOpGenericAdaptor(RangeT values, const ScalableExtractOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ScalableExtractOp, typename = std::enable_if_t<std::is_same_v<LateInst, ScalableExtractOp>>>
  ScalableExtractOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ScalableExtractOpAdaptor : public ScalableExtractOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ScalableExtractOpGenericAdaptor::ScalableExtractOpGenericAdaptor;
  ScalableExtractOpAdaptor(ScalableExtractOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ScalableExtractOp : public ::mlir::Op<ScalableExtractOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ScalableExtractOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ScalableExtractOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("pos")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPosAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPosAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.scalable.extract");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getPosAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().pos);
  }

  uint64_t getPos();
  void setPosAttr(::mlir::IntegerAttr attr) {
    getProperties().pos = attr;
  }

  void setPos(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::IntegerAttr pos);
  static ScalableExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::IntegerAttr pos);
  static ScalableExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::IntegerAttr pos);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::IntegerAttr pos);
  static ScalableExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::IntegerAttr pos);
  static ScalableExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::IntegerAttr pos);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, uint64_t pos);
  static ScalableExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, uint64_t pos);
  static ScalableExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, uint64_t pos);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, uint64_t pos);
  static ScalableExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, uint64_t pos);
  static ScalableExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, uint64_t pos);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScalableExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScalableExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScalableExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScalableExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
  // Integer to represent a poison index within a static and positive integer
  // range.
  static constexpr int64_t kPoisonIndex = -1;

  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getSource().getType());
  }
  VectorType getResultVectorType() {
    return ::llvm::cast<VectorType>(getResult().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ScalableExtractOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ScalableInsertOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ScalableInsertOpGenericAdaptorBase {
public:
  struct Properties {
    using posTy = ::mlir::IntegerAttr;
    posTy pos;

    auto getPos() const {
      auto &propStorage = this->pos;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setPos(const ::mlir::IntegerAttr &propValue) {
      this->pos = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.pos == this->pos &&
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
  ScalableInsertOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.scalable.insert", odsAttrs.getContext());
  }

  ScalableInsertOpGenericAdaptorBase(ScalableInsertOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getPosAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().pos);
    return attr;
  }

  uint64_t getPos();
};

} // namespace detail
template <typename RangeT>
class ScalableInsertOpGenericAdaptor : public detail::ScalableInsertOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ScalableInsertOpGenericAdaptorBase;
  static constexpr int odsIndex_valueToStore = 0;
  static constexpr int odsIndex_dest = 1;
public:
  ScalableInsertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ScalableInsertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ScalableInsertOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ScalableInsertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ScalableInsertOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ScalableInsertOpGenericAdaptor(RangeT values, const ScalableInsertOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ScalableInsertOp, typename = std::enable_if_t<std::is_same_v<LateInst, ScalableInsertOp>>>
  ScalableInsertOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValueToStore() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDest() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ScalableInsertOpAdaptor : public ScalableInsertOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ScalableInsertOpGenericAdaptor::ScalableInsertOpGenericAdaptor;
  ScalableInsertOpAdaptor(ScalableInsertOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ScalableInsertOp : public ::mlir::Op<ScalableInsertOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ScalableInsertOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ScalableInsertOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_valueToStore = 0;
  static constexpr int odsIndex_dest = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("pos")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPosAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPosAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.scalable.insert");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getValueToStore() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getValueToStoreMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDestMutable() {
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getPosAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().pos);
  }

  uint64_t getPos();
  void setPosAttr(::mlir::IntegerAttr attr) {
    getProperties().pos = attr;
  }

  void setPos(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::IntegerAttr pos);
  static ScalableInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::IntegerAttr pos);
  static ScalableInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::IntegerAttr pos);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::IntegerAttr pos);
  static ScalableInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::IntegerAttr pos);
  static ScalableInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::IntegerAttr pos);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::IntegerAttr pos);
  static ScalableInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::IntegerAttr pos);
  static ScalableInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, ::mlir::IntegerAttr pos);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, uint64_t pos);
  static ScalableInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, uint64_t pos);
  static ScalableInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value dest, uint64_t pos);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value valueToStore, ::mlir::Value dest, uint64_t pos);
  static ScalableInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value valueToStore, ::mlir::Value dest, uint64_t pos);
  static ScalableInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value valueToStore, ::mlir::Value dest, uint64_t pos);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, uint64_t pos);
  static ScalableInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, uint64_t pos);
  static ScalableInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value dest, uint64_t pos);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScalableInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScalableInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScalableInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScalableInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScalableInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScalableInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScalableInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScalableInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
  // Integer to represent a poison index within a static and positive integer
  // range.
  static constexpr int64_t kPoisonIndex = -1;

  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getValueToStore().getType());
  }
  VectorType getDestVectorType() {
    return ::llvm::cast<VectorType>(getDest().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ScalableInsertOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ScanOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ScanOpGenericAdaptorBase {
public:
  struct Properties {
    using inclusiveTy = ::mlir::BoolAttr;
    inclusiveTy inclusive;

    auto getInclusive() const {
      auto &propStorage = this->inclusive;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setInclusive(const ::mlir::BoolAttr &propValue) {
      this->inclusive = propValue;
    }
    using kindTy = ::mlir::vector::CombiningKindAttr;
    kindTy kind;

    auto getKind() const {
      auto &propStorage = this->kind;
      return ::llvm::cast<::mlir::vector::CombiningKindAttr>(propStorage);
    }
    void setKind(const ::mlir::vector::CombiningKindAttr &propValue) {
      this->kind = propValue;
    }
    using reduction_dimTy = ::mlir::IntegerAttr;
    reduction_dimTy reduction_dim;

    auto getReductionDim() const {
      auto &propStorage = this->reduction_dim;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setReductionDim(const ::mlir::IntegerAttr &propValue) {
      this->reduction_dim = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inclusive == this->inclusive &&
        rhs.kind == this->kind &&
        rhs.reduction_dim == this->reduction_dim &&
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
  ScanOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.scan", odsAttrs.getContext());
  }

  ScanOpGenericAdaptorBase(ScanOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::vector::CombiningKindAttr getKindAttr() {
    auto attr = ::llvm::cast<::mlir::vector::CombiningKindAttr>(getProperties().kind);
    return attr;
  }

  ::mlir::vector::CombiningKind getKind();
  ::mlir::IntegerAttr getReductionDimAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().reduction_dim);
    return attr;
  }

  uint64_t getReductionDim();
  ::mlir::BoolAttr getInclusiveAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().inclusive);
    return attr;
  }

  bool getInclusive();
};

} // namespace detail
template <typename RangeT>
class ScanOpGenericAdaptor : public detail::ScanOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ScanOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_initial_value = 1;
public:
  ScanOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ScanOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ScanOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ScanOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ScanOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ScanOpGenericAdaptor(RangeT values, const ScanOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ScanOp, typename = std::enable_if_t<std::is_same_v<LateInst, ScanOp>>>
  ScanOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getInitialValue() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ScanOpAdaptor : public ScanOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ScanOpGenericAdaptor::ScanOpGenericAdaptor;
  ScanOpAdaptor(ScanOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ScanOp : public ::mlir::Op<ScanOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ScanOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ScanOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_initial_value = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inclusive"), ::llvm::StringRef("kind"), ::llvm::StringRef("reduction_dim")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInclusiveAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInclusiveAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getKindAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getReductionDimAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getReductionDimAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.scan");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getInitialValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getInitialValueMutable() {
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

  ::mlir::TypedValue<::mlir::VectorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getAccumulatedValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(1).begin());
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
  ::mlir::vector::CombiningKindAttr getKindAttr() {
    return ::llvm::cast<::mlir::vector::CombiningKindAttr>(getProperties().kind);
  }

  ::mlir::vector::CombiningKind getKind();
  ::mlir::IntegerAttr getReductionDimAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().reduction_dim);
  }

  uint64_t getReductionDim();
  ::mlir::BoolAttr getInclusiveAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().inclusive);
  }

  bool getInclusive();
  void setKindAttr(::mlir::vector::CombiningKindAttr attr) {
    getProperties().kind = attr;
  }

  void setKind(::mlir::vector::CombiningKind attrValue);
  void setReductionDimAttr(::mlir::IntegerAttr attr) {
    getProperties().reduction_dim = attr;
  }

  void setReductionDim(uint64_t attrValue);
  void setInclusiveAttr(::mlir::BoolAttr attr) {
    getProperties().inclusive = attr;
  }

  void setInclusive(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::Type accumulated_value, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value initial_value, ::mlir::IntegerAttr reduction_dim, ::mlir::BoolAttr inclusive);
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::Type accumulated_value, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value initial_value, ::mlir::IntegerAttr reduction_dim, ::mlir::BoolAttr inclusive);
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::Type accumulated_value, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value initial_value, ::mlir::IntegerAttr reduction_dim, ::mlir::BoolAttr inclusive);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value initial_value, ::mlir::IntegerAttr reduction_dim, ::mlir::BoolAttr inclusive);
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value initial_value, ::mlir::IntegerAttr reduction_dim, ::mlir::BoolAttr inclusive);
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value initial_value, ::mlir::IntegerAttr reduction_dim, ::mlir::BoolAttr inclusive);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value initial_value, ::mlir::IntegerAttr reduction_dim, ::mlir::BoolAttr inclusive);
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value initial_value, ::mlir::IntegerAttr reduction_dim, ::mlir::BoolAttr inclusive);
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKindAttr kind, ::mlir::Value source, ::mlir::Value initial_value, ::mlir::IntegerAttr reduction_dim, ::mlir::BoolAttr inclusive);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::Type accumulated_value, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value initial_value, uint64_t reduction_dim, bool inclusive);
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::Type accumulated_value, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value initial_value, uint64_t reduction_dim, bool inclusive);
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::Type accumulated_value, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value initial_value, uint64_t reduction_dim, bool inclusive);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value initial_value, uint64_t reduction_dim, bool inclusive);
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value initial_value, uint64_t reduction_dim, bool inclusive);
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value initial_value, uint64_t reduction_dim, bool inclusive);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value initial_value, uint64_t reduction_dim, bool inclusive);
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value initial_value, uint64_t reduction_dim, bool inclusive);
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::vector::CombiningKind kind, ::mlir::Value source, ::mlir::Value initial_value, uint64_t reduction_dim, bool inclusive);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
  VectorType getSourceType() {
    return ::llvm::cast<VectorType>(getSource().getType());
  }
  VectorType getDestType() {
    return ::llvm::cast<VectorType>(getDest().getType());
  }
  VectorType getAccumulatorType() {
    return ::llvm::cast<VectorType>(getAccumulatedValue().getType());
  }
  VectorType getInitialValueType() {
    return ::llvm::cast<VectorType>(getInitialValue().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ScanOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ScatterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ScatterOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = ::mlir::IntegerAttr;
    alignmentTy alignment;

    auto getAlignment() const {
      auto &propStorage = this->alignment;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlignment(const ::mlir::IntegerAttr &propValue) {
      this->alignment = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
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
      odsOpName.emplace("vector.scatter", odsAttrs.getContext());
  }

  ScatterOpGenericAdaptorBase(ScatterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getAlignmentAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
    return attr;
  }

  ::std::optional<uint64_t> getAlignment();
};

} // namespace detail
template <typename RangeT>
class ScatterOpGenericAdaptor : public detail::ScatterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ScatterOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_offsets = 1;
  static constexpr int odsIndex_indices = 2;
  static constexpr int odsIndex_mask = 3;
  static constexpr int odsIndex_valueToStore = 4;
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

  ValueT getBase() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOffsets() {
    return getODSOperands(1);
  }

  ValueT getIndices() {
    return (*getODSOperands(2).begin());
  }

  ValueT getMask() {
    return (*getODSOperands(3).begin());
  }

  ValueT getValueToStore() {
    return (*getODSOperands(4).begin());
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
class ScatterOp : public ::mlir::Op<ScatterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<4>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ScatterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ScatterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_offsets = 1;
  static constexpr int odsIndex_indices = 2;
  static constexpr int odsIndex_mask = 3;
  static constexpr int odsIndex_valueToStore = 4;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.scatter");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getOffsets() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::VectorType> getIndices() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getMask() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getValueToStore() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(4).begin());
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getOffsetsMutable();
  ::mlir::OpOperand &getIndicesMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMaskMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValueToStoreMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::RankedTensorType>() : ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*results.begin());
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
  ::mlir::IntegerAttr getAlignmentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
  }

  ::std::optional<uint64_t> getAlignment();
  void setAlignmentAttr(::mlir::IntegerAttr attr) {
    getProperties().alignment = attr;
  }

  void setAlignment(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeAlignmentAttr() {
      auto attr = getProperties().alignment;
      getProperties().alignment = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value base, ValueRange indices, Value index_vec, Value mask, Value valueToStore, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value base, ValueRange indices, Value index_vec, Value mask, Value valueToStore, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value base, ValueRange indices, Value index_vec, Value mask, Value valueToStore, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange offsets, ::mlir::Value indices, ::mlir::Value mask, ::mlir::Value valueToStore, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
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
  ShapedType getBaseType() { return getBase().getType(); }
  VectorType getIndexVectorType() { return getIndices().getType(); }
  VectorType getMaskVectorType() { return getMask().getType(); }
  VectorType getVectorType() { return getValueToStore().getType(); }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ScatterOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ShapeCastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShapeCastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ShapeCastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.shape_cast", odsAttrs.getContext());
  }

  ShapeCastOpGenericAdaptorBase(ShapeCastOp op);

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
class ShapeCastOpGenericAdaptor : public detail::ShapeCastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShapeCastOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  ShapeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShapeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ShapeCastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShapeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ShapeCastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShapeCastOpGenericAdaptor(RangeT values, const ShapeCastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShapeCastOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShapeCastOp>>>
  ShapeCastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ShapeCastOpAdaptor : public ShapeCastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShapeCastOpGenericAdaptor::ShapeCastOpGenericAdaptor;
  ShapeCastOpAdaptor(ShapeCastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShapeCastOp : public ::mlir::Op<ShapeCastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShapeCastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShapeCastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<ShapeCastOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.shape_cast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source);
  static ShapeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source);
  static ShapeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static ShapeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static ShapeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShapeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShapeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShapeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShapeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getSource().getType());
  }
  VectorType getResultVectorType() {
    return ::llvm::cast<VectorType>(getResult().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ShapeCastOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ShuffleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShuffleOpGenericAdaptorBase {
public:
  struct Properties {
    using maskTy = ::mlir::DenseI64ArrayAttr;
    maskTy mask;

    auto getMask() const {
      auto &propStorage = this->mask;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setMask(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->mask = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.mask == this->mask &&
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
  ShuffleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.shuffle", odsAttrs.getContext());
  }

  ShuffleOpGenericAdaptorBase(ShuffleOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getMaskAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().mask);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getMask();
};

} // namespace detail
template <typename RangeT>
class ShuffleOpGenericAdaptor : public detail::ShuffleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShuffleOpGenericAdaptorBase;
  static constexpr int odsIndex_v1 = 0;
  static constexpr int odsIndex_v2 = 1;
public:
  ShuffleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShuffleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ShuffleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShuffleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ShuffleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShuffleOpGenericAdaptor(RangeT values, const ShuffleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShuffleOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShuffleOp>>>
  ShuffleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getV1() {
    return (*getODSOperands(0).begin());
  }

  ValueT getV2() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ShuffleOpAdaptor : public ShuffleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShuffleOpGenericAdaptor::ShuffleOpGenericAdaptor;
  ShuffleOpAdaptor(ShuffleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShuffleOp : public ::mlir::Op<ShuffleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpTrait::InferTypeOpAdaptor> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShuffleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShuffleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_v1 = 0;
  static constexpr int odsIndex_v2 = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<ShuffleOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("mask")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMaskAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMaskAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.shuffle");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getV1() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getV2() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getV1Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getV2Mutable() {
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

  ::mlir::TypedValue<::mlir::VectorType> getVector() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::DenseI64ArrayAttr getMaskAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().mask);
  }

  ::llvm::ArrayRef<int64_t> getMask();
  void setMaskAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().mask = attr;
  }

  void setMask(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type vector, ::mlir::Value v1, ::mlir::Value v2, ::mlir::DenseI64ArrayAttr mask);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type vector, ::mlir::Value v1, ::mlir::Value v2, ::mlir::DenseI64ArrayAttr mask);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type vector, ::mlir::Value v1, ::mlir::Value v2, ::mlir::DenseI64ArrayAttr mask);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value v1, ::mlir::Value v2, ::mlir::DenseI64ArrayAttr mask);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value v1, ::mlir::Value v2, ::mlir::DenseI64ArrayAttr mask);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value v1, ::mlir::Value v2, ::mlir::DenseI64ArrayAttr mask);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value v1, ::mlir::Value v2, ::mlir::DenseI64ArrayAttr mask);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value v1, ::mlir::Value v2, ::mlir::DenseI64ArrayAttr mask);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value v1, ::mlir::Value v2, ::mlir::DenseI64ArrayAttr mask);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type vector, ::mlir::Value v1, ::mlir::Value v2, ::llvm::ArrayRef<int64_t> mask);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type vector, ::mlir::Value v1, ::mlir::Value v2, ::llvm::ArrayRef<int64_t> mask);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type vector, ::mlir::Value v1, ::mlir::Value v2, ::llvm::ArrayRef<int64_t> mask);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value v1, ::mlir::Value v2, ::llvm::ArrayRef<int64_t> mask);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value v1, ::mlir::Value v2, ::llvm::ArrayRef<int64_t> mask);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value v1, ::mlir::Value v2, ::llvm::ArrayRef<int64_t> mask);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value v1, ::mlir::Value v2, ::llvm::ArrayRef<int64_t> mask);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value v1, ::mlir::Value v2, ::llvm::ArrayRef<int64_t> mask);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value v1, ::mlir::Value v2, ::llvm::ArrayRef<int64_t> mask);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
      static ::llvm::LogicalResult
      inferReturnTypes(::mlir::MLIRContext *context,
                              std::optional<::mlir::Location> location,
                              Adaptor adaptor,
                              ::llvm::SmallVectorImpl<::mlir::Type> &inferredReturnTypes);


  // Integer to represent a poison index within a static and positive integer
  // range.
  static constexpr int64_t kPoisonIndex = -1;

  VectorType getV1VectorType() {
    return ::llvm::cast<VectorType>(getV1().getType());
  }
  VectorType getV2VectorType() {
    return ::llvm::cast<VectorType>(getV2().getType());
  }
  VectorType getResultVectorType() {
    return ::llvm::cast<VectorType>(getVector().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ShuffleOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::StepOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StepOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StepOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.step", odsAttrs.getContext());
  }

  StepOpGenericAdaptorBase(StepOp op);

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
class StepOpGenericAdaptor : public detail::StepOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StepOpGenericAdaptorBase;
public:
  StepOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StepOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : StepOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StepOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StepOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StepOpGenericAdaptor(RangeT values, const StepOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StepOp, typename = std::enable_if_t<std::is_same_v<LateInst, StepOp>>>
  StepOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StepOpAdaptor : public StepOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StepOpGenericAdaptor::StepOpGenericAdaptor;
  StepOpAdaptor(StepOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StepOp : public ::mlir::Op<StepOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StepOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StepOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::VectorUnrollOpInterface::Trait<StepOp>::getShapeForUnroll;
  using ::mlir::InferIntRangeInterface::Trait<StepOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.step");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result);
  static StepOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result);
  static StepOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static StepOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static StepOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StepOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StepOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StepOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StepOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::StepOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::StoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StoreOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = ::mlir::IntegerAttr;
    alignmentTy alignment;

    auto getAlignment() const {
      auto &propStorage = this->alignment;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlignment(const ::mlir::IntegerAttr &propValue) {
      this->alignment = propValue;
    }
    using nontemporalTy = ::mlir::BoolAttr;
    nontemporalTy nontemporal;

    auto getNontemporal() const {
      auto &propStorage = this->nontemporal;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setNontemporal(const ::mlir::BoolAttr &propValue) {
      this->nontemporal = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
        rhs.nontemporal == this->nontemporal &&
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
  StoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.store", odsAttrs.getContext());
  }

  StoreOpGenericAdaptorBase(StoreOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getNontemporalAttr();
  bool getNontemporal();
  ::mlir::IntegerAttr getAlignmentAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
    return attr;
  }

  ::std::optional<uint64_t> getAlignment();
};

} // namespace detail
template <typename RangeT>
class StoreOpGenericAdaptor : public detail::StoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StoreOpGenericAdaptorBase;
  static constexpr int odsIndex_valueToStore = 0;
  static constexpr int odsIndex_base = 1;
  static constexpr int odsIndex_indices = 2;
public:
  StoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : StoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StoreOpGenericAdaptor(RangeT values, const StoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, StoreOp>>>
  StoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValueToStore() {
    return (*getODSOperands(0).begin());
  }

  ValueT getBase() {
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
class StoreOpAdaptor : public StoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StoreOpGenericAdaptor::StoreOpGenericAdaptor;
  StoreOpAdaptor(StoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StoreOp : public ::mlir::Op<StoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_valueToStore = 0;
  static constexpr int odsIndex_base = 1;
  static constexpr int odsIndex_indices = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment"), ::llvm::StringRef("nontemporal")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNontemporalAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNontemporalAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.store");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getValueToStore() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getValueToStoreMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBaseMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::BoolAttr getNontemporalAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().nontemporal);
  }

  bool getNontemporal();
  ::mlir::IntegerAttr getAlignmentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
  }

  ::std::optional<uint64_t> getAlignment();
  void setNontemporalAttr(::mlir::BoolAttr attr) {
    getProperties().nontemporal = attr;
  }

  void setNontemporal(::std::optional<bool> attrValue);
  void setAlignmentAttr(::mlir::IntegerAttr attr) {
    getProperties().alignment = attr;
  }

  void setAlignment(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeNontemporalAttr() {
      auto attr = getProperties().nontemporal;
      getProperties().nontemporal = {};
      return attr;
  }

  ::mlir::Attribute removeAlignmentAttr() {
      auto attr = getProperties().alignment;
      getProperties().alignment = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value base, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value base, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value base, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
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
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getBase().getType());
  }

  VectorType getVectorType() {
    return ::llvm::cast<VectorType>(getValueToStore().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::StoreOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::ToElementsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToElementsOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ToElementsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.to_elements", odsAttrs.getContext());
  }

  ToElementsOpGenericAdaptorBase(ToElementsOp op);

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
class ToElementsOpGenericAdaptor : public detail::ToElementsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToElementsOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  ToElementsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToElementsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ToElementsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToElementsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToElementsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToElementsOpGenericAdaptor(RangeT values, const ToElementsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToElementsOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToElementsOp>>>
  ToElementsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ToElementsOpAdaptor : public ToElementsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToElementsOpGenericAdaptor::ToElementsOpGenericAdaptor;
  ToElementsOpAdaptor(ToElementsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToElementsOp : public ::mlir::Op<ToElementsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpTrait::InferTypeOpAdaptor, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToElementsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToElementsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<ToElementsOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.to_elements");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getElements() {
    return getODSResults(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange elements, ::mlir::Value source);
  static ToElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange elements, ::mlir::Value source);
  static ToElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange elements, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source);
  static ToElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source);
  static ToElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToElementsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToElementsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  static ::llvm::LogicalResult
  inferReturnTypes(::mlir::MLIRContext *context,
                          std::optional<::mlir::Location> location,
                          Adaptor adaptor,
                          ::llvm::SmallVectorImpl<::mlir::Type> &inferredReturnTypes);

};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::ToElementsOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::TransferReadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TransferReadOpGenericAdaptorBase {
public:
  struct Properties {
    using in_boundsTy = ::mlir::ArrayAttr;
    in_boundsTy in_bounds;

    auto getInBounds() const {
      auto &propStorage = this->in_bounds;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setInBounds(const ::mlir::ArrayAttr &propValue) {
      this->in_bounds = propValue;
    }
    using permutation_mapTy = ::mlir::AffineMapAttr;
    permutation_mapTy permutation_map;

    auto getPermutationMap() const {
      auto &propStorage = this->permutation_map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setPermutationMap(const ::mlir::AffineMapAttr &propValue) {
      this->permutation_map = propValue;
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
        rhs.in_bounds == this->in_bounds &&
        rhs.permutation_map == this->permutation_map &&
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
  TransferReadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.transfer_read", odsAttrs.getContext());
  }

  TransferReadOpGenericAdaptorBase(TransferReadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getPermutationMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().permutation_map);
    return attr;
  }

  ::mlir::AffineMap getPermutationMap();
  ::mlir::ArrayAttr getInBoundsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().in_bounds);
    return attr;
  }

  ::mlir::ArrayAttr getInBounds();
};

} // namespace detail
template <typename RangeT>
class TransferReadOpGenericAdaptor : public detail::TransferReadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TransferReadOpGenericAdaptorBase;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_padding = 2;
  static constexpr int odsIndex_mask = 3;
public:
  TransferReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TransferReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TransferReadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TransferReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TransferReadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TransferReadOpGenericAdaptor(RangeT values, const TransferReadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TransferReadOp, typename = std::enable_if_t<std::is_same_v<LateInst, TransferReadOp>>>
  TransferReadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBase() {
    return (*getODSOperands(0).begin());
  }

  RangeT getIndices() {
    return getODSOperands(1);
  }

  ValueT getPadding() {
    return (*getODSOperands(2).begin());
  }

  ValueT getMask() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TransferReadOpAdaptor : public TransferReadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TransferReadOpGenericAdaptor::TransferReadOpGenericAdaptor;
  TransferReadOpAdaptor(TransferReadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TransferReadOp : public ::mlir::Op<TransferReadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::VectorTransferOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait, ::mlir::vector::MaskableOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TransferReadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TransferReadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_base = 0;
  static constexpr int odsIndex_indices = 1;
  static constexpr int odsIndex_padding = 2;
  static constexpr int odsIndex_mask = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::vector::MaskableOpInterface::Trait<TransferReadOp>::isMasked;
  using ::mlir::vector::MaskableOpInterface::Trait<TransferReadOp>::getMaskingOp;
  using ::mlir::vector::MaskableOpInterface::Trait<TransferReadOp>::supportsPassthru;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("in_bounds"), ::llvm::StringRef("permutation_map"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInBoundsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInBoundsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPermutationMapAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPermutationMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.transfer_read");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::ShapedType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::Type> getPadding() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::VectorType> getMask() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::VectorType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*operands.begin());
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  ::mlir::OpOperand &getPaddingMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getMaskMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getVector() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::AffineMapAttr getPermutationMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().permutation_map);
  }

  ::mlir::AffineMap getPermutationMap();
  ::mlir::ArrayAttr getInBoundsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().in_bounds);
  }

  ::mlir::ArrayAttr getInBounds();
  void setPermutationMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().permutation_map = attr;
  }

  void setPermutationMap(::mlir::AffineMap attrValue);
  void setInBoundsAttr(::mlir::ArrayAttr attr) {
    getProperties().in_bounds = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType vectorType, Value source, ValueRange indices, std::optional<Value> padding, AffineMapAttr permutationMapAttr, ArrayAttr inBoundsAttr);
  static TransferReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType vectorType, Value source, ValueRange indices, std::optional<Value> padding, AffineMapAttr permutationMapAttr, ArrayAttr inBoundsAttr);
  static TransferReadOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType vectorType, Value source, ValueRange indices, std::optional<Value> padding, AffineMapAttr permutationMapAttr, ArrayAttr inBoundsAttr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType vectorType, Value source, ValueRange indices, std::optional<Value> padding, AffineMap permutationMap, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static TransferReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType vectorType, Value source, ValueRange indices, std::optional<Value> padding, AffineMap permutationMap, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static TransferReadOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType vectorType, Value source, ValueRange indices, std::optional<Value> padding, AffineMap permutationMap, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType vectorType, Value source, ValueRange indices, std::optional<Value> padding, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static TransferReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType vectorType, Value source, ValueRange indices, std::optional<Value> padding, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static TransferReadOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType vectorType, Value source, ValueRange indices, std::optional<Value> padding, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type vector, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type vector, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type vector, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type vector, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type vector, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type vector, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, ::mlir::Value padding, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TransferReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TransferReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TransferReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TransferReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  ::mlir::VectorType getVectorType();
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
  mlir::Type getExpectedMaskType();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  ::mlir::Speculation::Speculatability getSpeculatability();
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  // MaskableOpInterface methods.
  bool supportsPassthru() { return true; }

  MutableOperandRange getDpsInitsMutable() {
    return MutableOperandRange(getOperation(), /*start=*/0, /*length=*/0);
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::TransferReadOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::TransferWriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TransferWriteOpGenericAdaptorBase {
public:
  struct Properties {
    using in_boundsTy = ::mlir::ArrayAttr;
    in_boundsTy in_bounds;

    auto getInBounds() const {
      auto &propStorage = this->in_bounds;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setInBounds(const ::mlir::ArrayAttr &propValue) {
      this->in_bounds = propValue;
    }
    using permutation_mapTy = ::mlir::AffineMapAttr;
    permutation_mapTy permutation_map;

    auto getPermutationMap() const {
      auto &propStorage = this->permutation_map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setPermutationMap(const ::mlir::AffineMapAttr &propValue) {
      this->permutation_map = propValue;
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
        rhs.in_bounds == this->in_bounds &&
        rhs.permutation_map == this->permutation_map &&
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
  TransferWriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.transfer_write", odsAttrs.getContext());
  }

  TransferWriteOpGenericAdaptorBase(TransferWriteOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getPermutationMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().permutation_map);
    return attr;
  }

  ::mlir::AffineMap getPermutationMap();
  ::mlir::ArrayAttr getInBoundsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().in_bounds);
    return attr;
  }

  ::mlir::ArrayAttr getInBounds();
};

} // namespace detail
template <typename RangeT>
class TransferWriteOpGenericAdaptor : public detail::TransferWriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TransferWriteOpGenericAdaptorBase;
  static constexpr int odsIndex_valueToStore = 0;
  static constexpr int odsIndex_base = 1;
  static constexpr int odsIndex_indices = 2;
  static constexpr int odsIndex_mask = 3;
public:
  TransferWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TransferWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TransferWriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TransferWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TransferWriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TransferWriteOpGenericAdaptor(RangeT values, const TransferWriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TransferWriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, TransferWriteOp>>>
  TransferWriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValueToStore() {
    return (*getODSOperands(0).begin());
  }

  ValueT getBase() {
    return (*getODSOperands(1).begin());
  }

  RangeT getIndices() {
    return getODSOperands(2);
  }

  ValueT getMask() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TransferWriteOpAdaptor : public TransferWriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TransferWriteOpGenericAdaptor::TransferWriteOpGenericAdaptor;
  TransferWriteOpAdaptor(TransferWriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TransferWriteOp : public ::mlir::Op<TransferWriteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::VectorTransferOpInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait, ::mlir::vector::MaskableOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TransferWriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TransferWriteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_valueToStore = 0;
  static constexpr int odsIndex_base = 1;
  static constexpr int odsIndex_indices = 2;
  static constexpr int odsIndex_mask = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::vector::MaskableOpInterface::Trait<TransferWriteOp>::isMasked;
  using ::mlir::vector::MaskableOpInterface::Trait<TransferWriteOp>::getMaskingOp;
  using ::mlir::vector::MaskableOpInterface::Trait<TransferWriteOp>::supportsPassthru;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("in_bounds"), ::llvm::StringRef("permutation_map"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInBoundsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInBoundsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPermutationMapAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPermutationMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.transfer_write");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getValueToStore() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::ShapedType> getBase() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::ShapedType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(2);
  }

  ::mlir::TypedValue<::mlir::VectorType> getMask() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::VectorType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*operands.begin());
  }

  ::mlir::OpOperand &getValueToStoreMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBaseMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
  ::mlir::MutableOperandRange getMaskMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getResult() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::RankedTensorType>() : ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*results.begin());
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
  ::mlir::AffineMapAttr getPermutationMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().permutation_map);
  }

  ::mlir::AffineMap getPermutationMap();
  ::mlir::ArrayAttr getInBoundsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().in_bounds);
  }

  ::mlir::ArrayAttr getInBounds();
  void setPermutationMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().permutation_map = attr;
  }

  void setPermutationMap(::mlir::AffineMap attrValue);
  void setInBoundsAttr(::mlir::ArrayAttr attr) {
    getProperties().in_bounds = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value vector, Value dest, ValueRange indices, AffineMapAttr permutationMapAttr, Value mask, ArrayAttr inBoundsAttr);
  static TransferWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value vector, Value dest, ValueRange indices, AffineMapAttr permutationMapAttr, Value mask, ArrayAttr inBoundsAttr);
  static TransferWriteOp create(::mlir::ImplicitLocOpBuilder &builder, Value vector, Value dest, ValueRange indices, AffineMapAttr permutationMapAttr, Value mask, ArrayAttr inBoundsAttr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value vector, Value dest, ValueRange indices, AffineMapAttr permutationMapAttr, ArrayAttr inBoundsAttr);
  static TransferWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value vector, Value dest, ValueRange indices, AffineMapAttr permutationMapAttr, ArrayAttr inBoundsAttr);
  static TransferWriteOp create(::mlir::ImplicitLocOpBuilder &builder, Value vector, Value dest, ValueRange indices, AffineMapAttr permutationMapAttr, ArrayAttr inBoundsAttr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value vector, Value dest, ValueRange indices, AffineMap permutationMap, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static TransferWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value vector, Value dest, ValueRange indices, AffineMap permutationMap, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static TransferWriteOp create(::mlir::ImplicitLocOpBuilder &builder, Value vector, Value dest, ValueRange indices, AffineMap permutationMap, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value vector, Value dest, ValueRange indices, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static TransferWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value vector, Value dest, ValueRange indices, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static TransferWriteOp create(::mlir::ImplicitLocOpBuilder &builder, Value vector, Value dest, ValueRange indices, std::optional<ArrayRef<bool>> inBounds = ::std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferWriteOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMapAttr permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferWriteOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type result, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static TransferWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value valueToStore, ::mlir::Value base, ::mlir::ValueRange indices, ::mlir::AffineMap permutation_map, /*optional*/::mlir::Value mask, ::mlir::ArrayAttr in_bounds);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TransferWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TransferWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TransferWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TransferWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  ::mlir::Value getVector();
  ::mlir::VectorType getVectorType();
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
  mlir::Type getExpectedMaskType();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  ::mlir::Speculation::Speculatability getSpeculatability();
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  /// This method is added to maintain uniformity with load/store
  ///  ops of other dialects.
  Value getValue() { return getVector(); }

  MutableOperandRange getDpsInitsMutable() { return getBaseMutable(); }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::TransferWriteOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::TransposeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TransposeOpGenericAdaptorBase {
public:
  struct Properties {
    using permutationTy = ::mlir::DenseI64ArrayAttr;
    permutationTy permutation;

    auto getPermutation() const {
      auto &propStorage = this->permutation;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setPermutation(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->permutation = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.permutation == this->permutation &&
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
  TransposeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.transpose", odsAttrs.getContext());
  }

  TransposeOpGenericAdaptorBase(TransposeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getPermutationAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().permutation);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getPermutation();
};

} // namespace detail
template <typename RangeT>
class TransposeOpGenericAdaptor : public detail::TransposeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TransposeOpGenericAdaptorBase;
  static constexpr int odsIndex_vector = 0;
public:
  TransposeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TransposeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TransposeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TransposeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TransposeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TransposeOpGenericAdaptor(RangeT values, const TransposeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TransposeOp, typename = std::enable_if_t<std::is_same_v<LateInst, TransposeOp>>>
  TransposeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getVector() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TransposeOpAdaptor : public TransposeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TransposeOpGenericAdaptor::TransposeOpGenericAdaptor;
  TransposeOpAdaptor(TransposeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TransposeOp : public ::mlir::Op<TransposeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::VectorUnrollOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TransposeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TransposeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_vector = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<TransposeOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("permutation")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPermutationAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPermutationAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.transpose");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getVector() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getVectorMutable() {
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

  ::mlir::TypedValue<::mlir::VectorType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSResults(0).begin());
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
  ::mlir::DenseI64ArrayAttr getPermutationAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().permutation);
  }

  ::llvm::ArrayRef<int64_t> getPermutation();
  void setPermutationAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().permutation = attr;
  }

  void setPermutation(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value vector, ArrayRef<int64_t> permutation);
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value vector, ArrayRef<int64_t> permutation);
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, Value vector, ArrayRef<int64_t> permutation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value vector, ::mlir::DenseI64ArrayAttr permutation);
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value vector, ::mlir::DenseI64ArrayAttr permutation);
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value vector, ::mlir::DenseI64ArrayAttr permutation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value vector, ::mlir::DenseI64ArrayAttr permutation);
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value vector, ::mlir::DenseI64ArrayAttr permutation);
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value vector, ::mlir::DenseI64ArrayAttr permutation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value vector, ::llvm::ArrayRef<int64_t> permutation);
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value vector, ::llvm::ArrayRef<int64_t> permutation);
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value vector, ::llvm::ArrayRef<int64_t> permutation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value vector, ::llvm::ArrayRef<int64_t> permutation);
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value vector, ::llvm::ArrayRef<int64_t> permutation);
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value vector, ::llvm::ArrayRef<int64_t> permutation);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
  ::std::optional<::llvm::SmallVector<int64_t, 4>> getShapeForUnroll();
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
  VectorType getSourceVectorType() {
    return ::llvm::cast<VectorType>(getVector().getType());
  }
  VectorType getResultVectorType() {
    return ::llvm::cast<VectorType>(getResult().getType());
  }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::TransposeOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::TypeCastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TypeCastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TypeCastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("vector.type_cast", odsAttrs.getContext());
  }

  TypeCastOpGenericAdaptorBase(TypeCastOp op);

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
class TypeCastOpGenericAdaptor : public detail::TypeCastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TypeCastOpGenericAdaptorBase;
  static constexpr int odsIndex_memref = 0;
public:
  TypeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TypeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TypeCastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TypeCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TypeCastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TypeCastOpGenericAdaptor(RangeT values, const TypeCastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TypeCastOp, typename = std::enable_if_t<std::is_same_v<LateInst, TypeCastOp>>>
  TypeCastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMemref() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TypeCastOpAdaptor : public TypeCastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TypeCastOpGenericAdaptor::TypeCastOpGenericAdaptor;
  TypeCastOpAdaptor(TypeCastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TypeCastOp : public ::mlir::Op<TypeCastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ViewLikeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TypeCastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TypeCastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.type_cast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getMemrefMutable() {
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

  ::mlir::TypedValue<::mlir::MemRefType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source);
  static TypeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source);
  static TypeCastOp create(::mlir::ImplicitLocOpBuilder &builder, Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value memref);
  static TypeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value memref);
  static TypeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref);
  static TypeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref);
  static TypeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypeCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypeCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getMemref().getType());
  }
  MemRefType getResultMemRefType() {
    return ::llvm::cast<MemRefType>(getResult().getType());
  }
  // Implement ViewLikeOpInterface.
  Value getViewSource() { return getMemref(); }
};

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::TypeCastOp)

namespace mlir::vector {


//===----------------------------------------------------------------------===//
// ::mlir::vector::YieldOp declarations
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
      odsOpName.emplace("vector.yield", odsAttrs.getContext());
  }

  YieldOpGenericAdaptorBase(YieldOp op);

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
class YieldOpGenericAdaptor : public detail::YieldOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::YieldOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
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

  RangeT getOperands() {
    return getODSOperands(0);
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
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = YieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = YieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<YieldOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vector.yield");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getOperandsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands);
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

} // namespace mlir::vector
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vector::YieldOp)


#endif // GET_OP_CLASSES

