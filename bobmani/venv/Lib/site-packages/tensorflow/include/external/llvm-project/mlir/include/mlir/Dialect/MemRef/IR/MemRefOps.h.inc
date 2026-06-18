/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: MemRefOps.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::memref {

/// assumption that gives alignment information to the input memref
/// The `assume_alignment` operation takes a memref and an integer alignment
///       value. It returns a new SSA value of the same memref type, but associated
///       with the assumption that the underlying buffer is aligned to the given
///       alignment.
/// 
///       If the buffer isn't aligned to the given alignment, its result is poison.
///       This operation doesn't affect the semantics of a program where the
///       alignment assumption holds true. It is intended for optimization purposes,
///       allowing the compiler to generate more efficient code based on the
///       alignment assumption. The optimization is best-effort.
class AssumeAlignmentOp;

} // namespace mlir::memref
namespace mlir::memref {

/// atomic read-modify-write operation
/// The `memref.atomic_rmw` operation provides a way to perform a read-modify-write
///     sequence that is free from data races. The kind enumeration specifies the
///     modification to perform. The value operand represents the new value to be
///     applied during the modification. The memref operand represents the buffer
///     that the read and write will be performed against, as accessed by the
///     specified indices. The arity of the indices is the rank of the memref. The
///     result represents the latest value that was stored.
/// 
///     Example:
/// 
///     ```mlir
///     %x = memref.atomic_rmw "addf" %value, %I[%i] : (f32, memref<10xf32>) -> f32
///     ```
class AtomicRMWOp;

} // namespace mlir::memref
namespace mlir::memref {

/// yield operation for GenericAtomicRMWOp
/// "memref.atomic_yield" yields an SSA value from a
///     GenericAtomicRMWOp region.
class AtomicYieldOp;

} // namespace mlir::memref
namespace mlir::memref {

/// Copies the data from the source to the destination memref.
/// 
///     Usage:
/// 
///     ```mlir
///     memref.copy %arg0, %arg1 : memref<?xf32> to memref<?xf32>
///     ```
/// 
///     Source and destination are expected to have the same element type and shape.
///     Otherwise, the result is undefined. They may have different layouts.
class CopyOp;

} // namespace mlir::memref
namespace mlir::memref {

/// assumption that acesses to specific memrefs will never alias
/// The `distinct_objects` operation takes a list of memrefs and returns the same
///       memrefs, with the additional assumption that accesses to them will never
///       alias with each other. This means that loads and stores to different
///       memrefs in the list can be safely reordered.
/// 
///       If the memrefs do alias, the load/store behavior is undefined. This
///       operation doesn't affect the semantics of a valid program. It is
///       intended for optimization purposes, allowing the compiler to generate more
///       efficient code based on the non-aliasing assumption. The optimization is
///       best-effort.
/// 
///       Example:
/// 
///       ```mlir
///       %1, %2 = memref.distinct_objects %a, %b : memref<?xf32>, memref<?xf32>
///       ```
class DistinctObjectsOp;

} // namespace mlir::memref
namespace mlir::memref {

/// atomic read-modify-write operation with a region
/// The `memref.generic_atomic_rmw` operation provides a way to perform a
///     read-modify-write sequence that is free from data races. The memref operand
///     represents the buffer that the read and write will be performed against, as
///     accessed by the specified indices. The arity of the indices is the rank of
///     the memref. The result represents the latest value that was stored. The
///     region contains the code for the modification itself. The entry block has
///     a single argument that represents the value stored in `memref[indices]`
///     before the write is performed. No side-effecting ops are allowed in the
///     body of `GenericAtomicRMWOp`.
/// 
///     Example:
/// 
///     ```mlir
///     %x = memref.generic_atomic_rmw %I[%i] : memref<10xf32> {
///       ^bb0(%current_value : f32):
///         %c1 = arith.constant 1.0 : f32
///         %inc = arith.addf %c1, %current_value : f32
///         memref.atomic_yield %inc : f32
///     }
///     ```
class GenericAtomicRMWOp;

} // namespace mlir::memref
namespace mlir::memref {

/// load operation
/// The `load` op reads an element from a memref at the specified indices.
/// 
///     The number of indices must match the rank of the memref. The indices must
///     be in-bounds: `0 <= idx < dim_size`.
/// 
///     Lowerings of `memref.load` may emit attributes, e.g. `inbouds` + `nuw`
///     when converting to LLVM's `llvm.getelementptr`, that would cause undefined
///     behavior if indices are out of bounds or if computing the offset in the
///     memref would cause signed overflow of the `index` type.
/// 
///     The single result of `memref.load` is a value with the same type as the
///     element type of the memref.
/// 
///     A set `nontemporal` attribute indicates that this load is not expected to
///     be reused in the cache. For details, refer to the
///     [LLVM load instruction](https://llvm.org/docs/LangRef.html#load-instruction).
/// 
///     An optional `alignment` attribute allows to specify the byte alignment of the
///     load operation. It must be a positive power of 2. The operation must access
///     memory at an address aligned to this boundary. Violations may lead to
///     architecture-specific faults or performance penalties.
///     A value of 0 indicates no specific alignment requirement.
///     Example:
/// 
///     ```mlir
///     %0 = memref.load %A[%a, %b] : memref<8x?xi32, #layout, memspace0>
///     ```
class LoadOp;

} // namespace mlir::memref
namespace mlir::memref {

/// memory allocation operation
/// The `alloc` operation allocates a region of memory, as specified by its
///     memref type.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = memref.alloc() : memref<8x64xf32, 1>
///     ```
/// 
///     The optional list of dimension operands are bound to the dynamic dimensions
///     specified in its memref type. In the example below, the ssa value '%d' is
///     bound to the second dimension of the memref (which is dynamic).
/// 
///     ```mlir
///     %0 = memref.alloc(%d) : memref<8x?xf32, 1>
///     ```
/// 
///     The optional list of symbol operands are bound to the symbols of the
///     memrefs affine map. In the example below, the ssa value '%s' is bound to
///     the symbol 's0' in the affine map specified in the allocs memref type.
/// 
///     ```mlir
///     %0 = memref.alloc()[%s] : memref<8x64xf32,
///                               affine_map<(d0, d1)[s0] -> ((d0 + s0), d1)>, 1>
///     ```
/// 
///     This operation returns a single ssa value of memref type, which can be used
///     by subsequent load and store operations.
/// 
///     The optional `alignment` attribute may be specified to ensure that the
///     region of memory that will be indexed is aligned at the specified byte
///     boundary.
/// 
///     ```mlir
///     %0 = memref.alloc()[%s] {alignment = 8} :
///       memref<8x64xf32, affine_map<(d0, d1)[s0] -> ((d0 + s0), d1)>, 1>
///     ```
class AllocOp;

} // namespace mlir::memref
namespace mlir::memref {

/// stack memory allocation operation
/// The `alloca` operation allocates memory on the stack, to be automatically
///     released when control transfers back from the region of its closest
///     surrounding operation with an
///     [`AutomaticAllocationScope`](../Traits/#automaticallocationscope) trait.
///     The amount of memory allocated is specified by its memref and additional
///     operands. For example:
/// 
///     ```mlir
///     %0 = memref.alloca() : memref<8x64xf32>
///     ```
/// 
///     The optional list of dimension operands are bound to the dynamic dimensions
///     specified in its memref type. In the example below, the SSA value '%d' is
///     bound to the second dimension of the memref (which is dynamic).
/// 
///     ```mlir
///     %0 = memref.alloca(%d) : memref<8x?xf32>
///     ```
/// 
///     The optional list of symbol operands are bound to the symbols of the
///     memref's affine map. In the example below, the SSA value '%s' is bound to
///     the symbol 's0' in the affine map specified in the allocs memref type.
/// 
///     ```mlir
///     %0 = memref.alloca()[%s] : memref<8x64xf32,
///                                affine_map<(d0, d1)[s0] -> ((d0 + s0), d1)>>
///     ```
/// 
///     This operation returns a single SSA value of memref type, which can be used
///     by subsequent load and store operations. An optional alignment attribute, if
///     specified, guarantees alignment at least to that boundary. If not specified,
///     an alignment on any convenient boundary compatible with the type will be
///     chosen.
class AllocaOp;

} // namespace mlir::memref
namespace mlir::memref {

/// explicitly delimited scope for stack allocation
/// The `memref.alloca_scope` operation represents an explicitly-delimited
///     scope for the alloca allocations. Any `memref.alloca` operations that are
///     used within this scope are going to be cleaned up automatically once
///     the control-flow exits the nested region. For example:
/// 
///     ```mlir
///     memref.alloca_scope {
///       %myalloca = memref.alloca(): memref<4x3xf32>
///       ...
///     }
///     ```
/// 
///     Here, `%myalloca` memref is valid within the explicitly delimited scope
///     and is automatically deallocated at the end of the given region. Conceptually,
///     `memref.alloca_scope` is a passthrough operation with
///     `AutomaticAllocationScope` that spans the body of the region within the operation.
/// 
///     `memref.alloca_scope` may also return results that are defined in the nested
///     region. To return a value, one should use `memref.alloca_scope.return`
///     operation:
/// 
///     ```mlir
///     %result = memref.alloca_scope -> f32 {
///       %value = arith.constant 1.0 : f32
///       ...
///       memref.alloca_scope.return %value : f32
///     }
///     ```
/// 
///     If `memref.alloca_scope` returns no value, the `memref.alloca_scope.return ` can
///     be left out, and will be inserted implicitly.
class AllocaScopeOp;

} // namespace mlir::memref
namespace mlir::memref {

/// terminator for alloca_scope operation
/// `memref.alloca_scope.return` operation returns zero or more SSA values
///     from the region within `memref.alloca_scope`. If no values are returned,
///     the return operation may be omitted. Otherwise, it has to be present
///     to indicate which values are going to be returned. For example:
/// 
///     ```mlir
///     memref.alloca_scope.return %value : f32
///     ```
class AllocaScopeReturnOp;

} // namespace mlir::memref
namespace mlir::memref {

/// memref cast operation
/// The `memref.cast` operation converts a memref from one type to an equivalent
///     type with a compatible shape. The source and destination types are
///     compatible if:
/// 
///     a. Both are ranked memref types with the same element type, address space,
///     and rank and:
///       1. Both have the same layout or both have compatible strided layouts.
///       2. The individual sizes (resp. offset and strides in the case of strided
///          memrefs) may convert constant dimensions to dynamic dimensions and
///          vice-versa.
/// 
///     If the cast converts any dimensions from an unknown to a known size, then it
///     acts as an assertion that fails at runtime if the dynamic dimensions
///     disagree with resultant destination size.
/// 
///     Example:
/// 
///     ```mlir
///     // Assert that the input dynamic shape matches the destination static shape.
///     %2 = memref.cast %1 : memref<?x?xf32> to memref<4x4xf32>
///     // Erase static shape information, replacing it with dynamic information.
///     %3 = memref.cast %1 : memref<4xf32> to memref<?xf32>
/// 
///     // The same holds true for offsets and strides.
/// 
///     // Assert that the input dynamic shape matches the destination static stride.
///     %4 = memref.cast %1 : memref<12x4xf32, strided<[?, ?], offset: ?>> to
///                           memref<12x4xf32, strided<[4, 1], offset: 5>>
///     // Erase static offset and stride information, replacing it with
///     // dynamic information.
///     %5 = memref.cast %1 : memref<12x4xf32, strided<[4, 1], offset: 5>> to
///                           memref<12x4xf32, strided<[?, ?], offset: ?>>
///     ```
/// 
///     b. Either or both memref types are unranked with the same element type, and
///     address space.
/// 
///     Example:
/// 
///     ```mlir
///     // Cast to concrete shape.
///     %4 = memref.cast %1 : memref<*xf32> to memref<4x?xf32>
/// 
///     // Erase rank information.
///     %5 = memref.cast %1 : memref<4x?xf32> to memref<*xf32>
///     ```
class CastOp;

} // namespace mlir::memref
namespace mlir::memref {

/// operation to produce a memref with a smaller rank.
/// The `memref.collapse_shape` op produces a new view with a smaller rank
///     whose sizes are a reassociation of the original `view`. The operation is
///     limited to such reassociations, where subsequent, contiguous dimensions are
///     collapsed into a single dimension. Such reassociations never require
///     additional allocs or copies.
/// 
///     Collapsing non-contiguous dimensions is undefined behavior. When a group of
///     dimensions can be statically proven to be non-contiguous, collapses of such
///     groups are rejected in the verifier on a best-effort basis. In the general
///     case, collapses of dynamically-sized dims with dynamic strides cannot be
///     proven to be contiguous or non-contiguous due to limitations in the memref
///     type.
/// 
///     A reassociation is defined as a continuous grouping of dimensions and is
///     represented with an array of DenseI64ArrayAttr attribute.
/// 
///     Note: Only the dimensions within a reassociation group must be contiguous.
///     The remaining dimensions may be non-contiguous.
/// 
///     The result memref type can be zero-ranked if the source memref type is
///     statically shaped with all dimensions being unit extent. In such a case, the
///     reassociation indices must be empty.
/// 
///     Examples:
/// 
///     ```mlir
///     // Dimension collapse (i, j) -> i' and k -> k'
///     %1 = memref.collapse_shape %0 [[0, 1], [2]] :
///         memref<?x?x?xf32, stride_spec> into memref<?x?xf32, stride_spec_2>
///     ```
/// 
///     For simplicity, this op may not be used to cast dynamicity of dimension
///     sizes and/or strides. I.e., a result dimension must be dynamic if and only
///     if at least one dimension in the corresponding reassociation group is
///     dynamic. Similarly, the stride of a result dimension must be dynamic if and
///     only if the corresponding start dimension in the source type is dynamic.
/// 
///     Note: This op currently assumes that the inner strides are of the
///     source/result layout map are the faster-varying ones.
class CollapseShapeOp;

} // namespace mlir::memref
namespace mlir::memref {

/// memory deallocation operation
/// The `dealloc` operation frees the region of memory referenced by a memref
///     which was originally created by the `alloc` operation.
///     The `dealloc` operation should not be called on memrefs which alias an
///     alloc'd memref (e.g. memrefs returned by `view` operations).
/// 
///     Example:
/// 
///     ```mlir
///     %0 = memref.alloc() : memref<8x64xf32, affine_map<(d0, d1) -> (d0, d1)>, 1>
///     memref.dealloc %0 : memref<8x64xf32,  affine_map<(d0, d1) -> (d0, d1)>, 1>
///     ```
class DeallocOp;

} // namespace mlir::memref
namespace mlir::memref {

/// dimension index operation
/// The `dim` operation takes a memref and a dimension operand of type `index`.
///     It returns the size of the requested dimension of the given memref.
///     If the dimension index is out of bounds the behavior is undefined.
/// 
///     The specified memref type is that of the first operand.
/// 
///     Example:
/// 
///     ```mlir
///     // Always returns 4, can be constant folded:
///     %c0 = arith.constant 0 : index
///     %x = memref.dim %A, %c0 : memref<4 x ? x f32>
/// 
///     // Returns the dynamic dimension of %A.
///     %c1 = arith.constant 1 : index
///     %y = memref.dim %A, %c1 : memref<4 x ? x f32>
/// 
///     // Equivalent generic form:
///     %x = "memref.dim"(%A, %c0) : (memref<4 x ? x f32>, index) -> index
///     %y = "memref.dim"(%A, %c1) : (memref<4 x ? x f32>, index) -> index
///     ```
class DimOp;

} // namespace mlir::memref
namespace mlir::memref {

/// non-blocking DMA operation that starts a transfer
/// Syntax:
/// 
///     ```
///     operation ::= `memref.dma_start` ssa-use`[`ssa-use-list`]` `,`
///                    ssa-use`[`ssa-use-list`]` `,` ssa-use `,`
///                    ssa-use`[`ssa-use-list`]` (`,` ssa-use `,` ssa-use)?
///                   `:` memref-type `,` memref-type `,` memref-type
///     ```
/// 
///     DmaStartOp starts a non-blocking DMA operation that transfers data from a
///     source memref to a destination memref. The source and destination memref
///     need not be of the same dimensionality, but need to have the same elemental
///     type. The operands include the source and destination memref's each followed
///     by its indices, size of the data transfer in terms of the number of elements
///     (of the elemental type of the memref), a tag memref with its indices, and
///     optionally at the end, a stride and a number_of_elements_per_stride
///     arguments. The tag location is used by a DmaWaitOp to check for completion.
///     The indices of the source memref, destination memref, and the tag memref
///     have the same restrictions as any load/store. The optional stride arguments
///     should be of 'index' type, and specify a stride for the slower memory space
///     (memory space with a lower memory space id), transferring chunks of
///     number_of_elements_per_stride every stride until %num_elements are
///     transferred. Either both or no stride arguments should be specified. If the
///     source and destination locations overlap the behavior of this operation is
///     not defined.
/// 
///     For example, a DmaStartOp operation that transfers 256 elements of a memref
///     '%src' in memory space 0 at indices [%i, %j] to memref '%dst' in memory
///     space 1 at indices [%k, %l], would be specified as follows:
/// 
///     ```mlir
///     %num_elements = arith.constant 256 : index
///     %idx = arith.constant 0 : index
///     %tag = memref.alloc() : memref<1 x i32, affine_map<(d0) -> (d0)>, 2>
///     memref.dma_start %src[%i, %j], %dst[%k, %l], %num_elements, %tag[%idx] :
///       memref<40 x 128 x f32, affine_map<(d0, d1) -> (d0, d1)>, 0>,
///       memref<2 x 1024 x f32, affine_map<(d0, d1) -> (d0, d1)>, 1>,
///       memref<1 x i32, affine_map<(d0) -> (d0)>, 2>
///     ```
/// 
///     If %stride and %num_elt_per_stride are specified, the DMA is expected to
///     transfer %num_elt_per_stride elements every %stride elements apart from
///     memory space 0 until %num_elements are transferred.
/// 
///     ```mlir
///     memref.dma_start %src[%i, %j], %dst[%k, %l], %num_elements, %tag[%idx], %stride,
///                      %num_elt_per_stride :
///     ```
/// 
///     * TODO: add additional operands to allow source and destination striding, and
///     multiple stride levels.
///     * TODO: Consider replacing src/dst memref indices with view memrefs.
class DmaStartOp;

} // namespace mlir::memref
namespace mlir::memref {

/// blocking DMA operation that waits for transfer completion
/// DmaWaitOp blocks until the completion of a DMA operation associated with the
///    tag element '%tag[%index]'. %tag is a memref, and %index has to be an index
///    with the same restrictions as any load/store index. %num_elements is the
///    number of elements associated with the DMA operation.
/// 
///    Example:
/// 
///    ```mlir
///     memref.dma_start %src[%i, %j], %dst[%k, %l], %num_elements, %tag[%index] :
///       memref<2048 x f32, affine_map<(d0) -> (d0)>, 0>,
///       memref<256 x f32, affine_map<(d0) -> (d0)>, 1>,
///       memref<1 x i32, affine_map<(d0) -> (d0)>, 2>
///     ...
///     ...
///     dma_wait %tag[%index], %num_elements : memref<1 x i32, affine_map<(d0) -> (d0)>, 2>
///     ```
class DmaWaitOp;

} // namespace mlir::memref
namespace mlir::memref {

/// operation to produce a memref with a higher rank.
/// The `memref.expand_shape` op produces a new view with a higher rank whose
///     sizes are a reassociation of the original `view`. The operation is limited
///     to such reassociations, where a dimension is expanded into one or multiple
///     contiguous dimensions. Such reassociations never require additional allocs
///     or copies.
/// 
///     A reassociation is defined as a grouping of dimensions and is represented
///     with an array of DenseI64ArrayAttr attributes.
/// 
///     Example:
/// 
///     ```mlir
///     %r = memref.expand_shape %0 [[0, 1], [2]] output_shape [%sz0, %sz1, 32]
///         : memref<?x32xf32> into memref<?x?x32xf32>
///     ```
/// 
///     If an op can be statically proven to be invalid (e.g, an expansion from
///     `memref<10xf32>` to `memref<2x6xf32>`), it is rejected by the verifier. If
///     it cannot statically be proven invalid (e.g., the full example above; it is
///     unclear whether the first source dimension is divisible by 5), the op is
///     accepted by the verifier. However, if the op is in fact invalid at runtime,
///     the behavior is undefined.
/// 
///     The source memref can be zero-ranked. In that case, the reassociation
///     indices must be empty and the result shape may only consist of unit
///     dimensions.
/// 
///     For simplicity, this op may not be used to cast dynamicity of dimension
///     sizes and/or strides. I.e., if and only if a source dimension is dynamic,
///     there must be a dynamic result dimension in the corresponding reassociation
///     group. Same for strides.
/// 
///     The representation for the output shape supports a partially-static
///     specification via attributes specified through the `static_output_shape`
///     argument.  A special sentinel value `ShapedType::kDynamic` encodes that the
///     corresponding entry has a dynamic value.  There must be exactly as many SSA
///     inputs in `output_shape` as there are `ShapedType::kDynamic` entries in
///     `static_output_shape`.
/// 
///     Note: This op currently assumes that the inner strides are of the
///     source/result layout map are the faster-varying ones.
class ExpandShapeOp;

} // namespace mlir::memref
namespace mlir::memref {

/// Extracts a memref's underlying aligned pointer as an index
/// Extracts the underlying aligned pointer as an index.
/// 
///     This operation is useful for lowering to lower-level dialects while still
///     avoiding the need to define a pointer type in higher-level dialects such as
///     the memref dialect.
/// 
///     This operation is intended solely as step during lowering, it has no side
///     effects. A reverse operation that creates a memref from an index interpreted
///     as a pointer is explicitly discouraged.
/// 
///     Example:
/// 
///     ```
///       %0 = memref.extract_aligned_pointer_as_index %arg : memref<4x4xf32> -> index
///       %1 = arith.index_cast %0 : index to i64
///       %2 = llvm.inttoptr %1 : i64 to !llvm.ptr
///       call @foo(%2) : (!llvm.ptr) ->()
///     ```
class ExtractAlignedPointerAsIndexOp;

} // namespace mlir::memref
namespace mlir::memref {

/// Extracts a buffer base with offset and strides
/// Extracts a base buffer, offset and strides. This op allows additional layers
///     of transformations and foldings to be added as lowering progresses from
///     higher-level dialect to lower-level dialects such as the LLVM dialect.
/// 
///     The op requires a strided memref source operand. If the source operand is not
///     a strided memref, then verification fails.
/// 
///     This operation is also useful for completeness to the existing memref.dim op.
///     While accessing strides, offsets and the base pointer independently is not
///     available, this is useful for composing with its natural complement op:
///     `memref.reinterpret_cast`.
/// 
///     Intended Use Cases:
/// 
///     The main use case is to expose the logic for manipulate memref metadata at a
///     higher level than the LLVM dialect.
///     This makes lowering more progressive and brings the following benefits:
///       - not all users of MLIR want to lower to LLVM and the information to e.g.
///         lower to library calls---like libxsmm---or to SPIR-V was not available.
///       - foldings and canonicalizations can happen at a higher level in MLIR:
///         before this op existed, lowering to LLVM would create large amounts of
///         LLVMIR. Even when LLVM does a good job at folding the low-level IR from
///         a performance perspective, it is unnecessarily opaque and inefficient to
///         send unkempt IR to LLVM.
/// 
///     Example:
/// 
///     ```mlir
///       %base, %offset, %sizes:2, %strides:2 =
///         memref.extract_strided_metadata %memref : memref<10x?xf32>
///           -> memref<f32>, index, index, index, index, index
/// 
///       // After folding, the type of %m2 can be memref<10x?xf32> and further
///       // folded to %memref.
///       %m2 = memref.reinterpret_cast %base to
///           offset: [%offset],
///           sizes: [%sizes#0, %sizes#1],
///           strides: [%strides#0, %strides#1]
///         : memref<f32> to memref<?x?xf32, strided<[?, ?], offset:?>>
///     ```
class ExtractStridedMetadataOp;

} // namespace mlir::memref
namespace mlir::memref {

/// get the memref pointing to a global variable
/// The `memref.get_global` operation retrieves the memref pointing to a
///      named global variable. If the global variable is marked constant, writing
///      to the result memref (such as through a `memref.store` operation) is
///      undefined.
/// 
///      Example:
/// 
///      ```mlir
///      %x = memref.get_global @foo : memref<2xf32>
///      ```
class GetGlobalOp;

} // namespace mlir::memref
namespace mlir::memref {

/// declare or define a global memref variable
/// The `memref.global` operation declares or defines a named global memref
///     variable. The backing memory for the variable is allocated statically and is
///     described by the type of the variable (which should be a statically shaped
///     memref type). The operation is a declaration if no `initial_value` is
///     specified, else it is a definition. The `initial_value` can either be a unit
///     attribute to represent a definition of an uninitialized global variable, or
///     an elements attribute to represent the definition of a global variable with
///     an initial value. The global variable can also be marked constant using the
///     `constant` unit attribute. Writing to such constant global variables is
///     undefined.
/// 
///     The global variable can be accessed by using the `memref.get_global` to
///     retrieve the memref for the global variable. Note that the memref
///     for such global variable itself is immutable (i.e., memref.get_global for a
///     given global variable will always return the same memref descriptor).
/// 
///     Example:
/// 
///     ```mlir
///     // Private variable with an initial value.
///     memref.global "private" @x : memref<2xf32> = dense<[0.0, 2.0]>
/// 
///     // Private variable with an initial value and an alignment (power of 2).
///     memref.global "private" @x : memref<2xf32> = dense<[0.0, 2.0]> {alignment = 64}
/// 
///     // Declaration of an external variable.
///     memref.global "private" @y : memref<4xi32>
/// 
///     // Uninitialized externally visible variable.
///     memref.global @z : memref<3xf16> = uninitialized
/// 
///     // Externally visible constant variable.
///     memref.global constant @c : memref<2xi32> = dense<[1, 4]>
///     ```
class GlobalOp;

} // namespace mlir::memref
namespace mlir::memref {

/// memref memory space cast operation
/// This operation casts memref values between memory spaces.
///     The input and result will be memrefs of the same types and shape that alias
///     the same underlying memory, though, for some casts on some targets,
///     the underlying values of the pointer stored in the memref may be affected
///     by the cast.
/// 
///     The input and result must have the same shape, element type, rank, and layout.
/// 
///     If the source and target address spaces are the same, this operation is a noop.
/// 
///     Finally, if the target memory-space is the generic/default memory-space,
///     then it is assumed this cast can be bubbled down safely. See the docs of
///     `MemorySpaceCastOpInterface` interface for more details.
/// 
///     Example:
/// 
///     ```mlir
///     // Cast a GPU private memory attribution into a generic pointer
///     %2 = memref.memory_space_cast %1 : memref<?xf32, 5> to memref<?xf32>
///     // Cast a generic pointer to workgroup-local memory
///     %4 = memref.memory_space_cast %3 : memref<5x4xi32> to memref<5x34xi32, 3>
///     // Cast between two non-default memory spaces
///     %6 = memref.memory_space_cast %5
///       : memref<*xmemref<?xf32>, 5> to memref<*xmemref<?xf32>, 3>
///     ```
class MemorySpaceCastOp;

} // namespace mlir::memref
namespace mlir::memref {

/// prefetch operation
/// The "prefetch" op prefetches data from a memref location described with
///     subscript indices similar to memref.load, and with three attributes: a
///     read/write specifier, a locality hint, and a cache type specifier as shown
///     below:
/// 
///     ```mlir
///     memref.prefetch %0[%i, %j], read, locality<3>, data : memref<400x400xi32>
///     ```
/// 
///     The read/write specifier is either 'read' or 'write', the locality hint
///     ranges from locality<0> (no locality) to locality<3> (extremely local keep
///     in cache). The cache type specifier is either 'data' or 'instr'
///     and specifies whether the prefetch is performed on data cache or on
///     instruction cache.
class PrefetchOp;

} // namespace mlir::memref
namespace mlir::memref {

/// rank operation
/// The `memref.rank` operation takes a memref operand and returns its rank.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = memref.rank %arg0 : memref<*xf32>
///     %1 = memref.rank %arg1 : memref<?x?xf32>
///     ```
class RankOp;

} // namespace mlir::memref
namespace mlir::memref {

/// memory reallocation operation
/// The `realloc` operation changes the size of a memory region. The memory
///     region is specified by a 1D source memref and the size of the new memory
///     region is specified by a 1D result memref type and an optional dynamic Value
///     of `Index` type. The source and the result memref must be in the same memory
///     space and have the same element type.
/// 
///     The operation may move the memory region to a new location. In this case,
///     the content of the memory block is preserved up to the lesser of the new
///     and old sizes. If the new size if larger, the value of the extended memory
///     is undefined. This is consistent with the ISO C realloc.
/// 
///     The operation returns an SSA value for the memref.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = memref.realloc %src : memref<64xf32> to memref<124xf32>
///     ```
/// 
///     The source memref may have a dynamic shape, in which case, the compiler will
///     generate code to extract its size from the runtime data structure for the
///     memref.
/// 
///     ```mlir
///     %1 = memref.realloc %src : memref<?xf32> to memref<124xf32>
///     ```
/// 
///     If the result memref has a dynamic shape, a result dimension operand is
///     needed to spefify its dynamic dimension. In the example below, the ssa value
///     '%d' specifies the unknown dimension of the result memref.
/// 
///     ```mlir
///     %2 = memref.realloc %src(%d) : memref<?xf32> to memref<?xf32>
///     ```
/// 
///     An optional `alignment` attribute may be specified to ensure that the
///     region of memory that will be indexed is aligned at the specified byte
///     boundary.  This is consistent with the fact that memref.alloc supports such
///     an optional alignment attribute. Note that in ISO C standard, neither alloc
///     nor realloc supports alignment, though there is aligned_alloc but not
///     aligned_realloc.
/// 
///     ```mlir
///     %3 = memref.realloc %src {alignment = 8} : memref<64xf32> to memref<124xf32>
///     ```
/// 
///     Referencing the memref through the old SSA value after realloc is undefined
///     behavior.
/// 
///     ```mlir
///     %new = memref.realloc %old : memref<64xf32> to memref<124xf32>
///     %4 = memref.load %new[%index] : memref<124xf32> // ok
///     %5 = memref.load %old[%index] : memref<64xf32>  // undefined behavior
///     ```
class ReallocOp;

} // namespace mlir::memref
namespace mlir::memref {

/// memref reinterpret cast operation
/// Modify offset, sizes and strides of an unranked/ranked memref.
/// 
///     Example 1:
/// 
///     Consecutive `reinterpret_cast` operations on memref's with static
///     dimensions.
/// 
///     We distinguish between *underlying memory* — the sequence of elements as
///     they appear in the contiguous memory of the memref — and the
///     *strided memref*, which refers to the underlying memory interpreted
///     according to specified offsets, sizes, and strides.
/// 
///     ```mlir
///     %result1 = memref.reinterpret_cast %arg0 to
///       offset: [9],
///       sizes: [4, 4],
///       strides: [16, 2]
///     : memref<8x8xf32, strided<[8, 1], offset: 0>> to
///       memref<4x4xf32, strided<[16, 2], offset: 9>>
/// 
///     %result2 = memref.reinterpret_cast %result1 to
///       offset: [0],
///       sizes: [2, 2],
///       strides: [4, 2]
///     : memref<4x4xf32, strided<[16, 2], offset: 9>> to
///       memref<2x2xf32, strided<[4, 2], offset: 0>>
///     ```
/// 
///     The underlying memory of `%arg0` consists of a linear sequence of integers
///     from 1 to 64. Its memref has the following 8x8 elements:
/// 
///     ```mlir
///     [[1,  2,  3,  4,  5,  6,  7,  8],
///     [9,  10, 11, 12, 13, 14, 15, 16],
///     [17, 18, 19, 20, 21, 22, 23, 24],
///     [25, 26, 27, 28, 29, 30, 31, 32],
///     [33, 34, 35, 36, 37, 38, 39, 40],
///     [41, 42, 43, 44, 45, 46, 47, 48],
///     [49, 50, 51, 52, 53, 54, 55, 56],
///     [57, 58, 59, 60, 61, 62, 63, 64]]
///     ```
/// 
///     Following the first `reinterpret_cast`, the strided memref elements
///     of `%result1` are:
/// 
///     ```mlir
///     [[10, 12, 14, 16],
///     [26, 28, 30, 32],
///     [42, 44, 46, 48],
///     [58, 60, 62, 64]]
///     ```
/// 
///     Note: The offset and strides are relative to the underlying memory of
///     `%arg0`.
/// 
///     The second `reinterpret_cast` results in the following strided memref
///     for `%result2`:
/// 
///     ```mlir
///     [[1, 3],
///     [5, 7]]
///     ```
/// 
///     Notice that it does not matter if you use %result1 or %arg0 as a source
///     for the second `reinterpret_cast` operation. Only the underlying memory
///     pointers will be reused.
/// 
///     The offset and stride are relative to the base underlying memory of the
///     memref, starting at 1, not at 10 as seen in the output of `%result1`.
///     This behavior contrasts with the `subview` operator, where values are
///     relative to the strided memref (refer to `subview` examples).
///     Consequently, the second `reinterpret_cast` behaves as if `%arg0` were
///     passed directly as its argument.
/// 
///     Example 2:
///     ```mlir
///     memref.reinterpret_cast %ranked to
///       offset: [0],
///       sizes: [%size0, 10],
///       strides: [1, %stride1]
///     : memref<?x?xf32> to memref<?x10xf32, strided<[1, ?], offset: 0>>
/// 
///     memref.reinterpret_cast %unranked to
///       offset: [%offset],
///       sizes: [%size0, %size1],
///       strides: [%stride0, %stride1]
///     : memref<*xf32> to memref<?x?xf32, strided<[?, ?], offset: ?>>
///     ```
/// 
///     This operation creates a new memref descriptor using the base of the
///     source and applying the input arguments to the other metadata.
///     In other words:
///     ```mlir
///     %dst = memref.reinterpret_cast %src to
///       offset: [%offset],
///       sizes: [%sizes],
///       strides: [%strides] :
///       memref<*xf32> to memref<?x?xf32, strided<[?, ?], offset: ?>>
///     ```
///     means that `%dst`'s descriptor will be:
///     ```mlir
///     %dst.base = %src.base
///     %dst.aligned = %src.aligned
///     %dst.offset = %offset
///     %dst.sizes = %sizes
///     %dst.strides = %strides
///     ```
class ReinterpretCastOp;

} // namespace mlir::memref
namespace mlir::memref {

/// memref reshape operation
/// The `reshape` operation converts a memref from one type to an
///     equivalent type with a provided shape. The data is never copied or
///     modified. The source and destination types are compatible if both have the
///     same element type, same number of elements, address space and identity
///     layout map. The following combinations are possible:
/// 
///     a. Source type is ranked or unranked. Shape argument has static size.
///     Result type is ranked.
/// 
///     ```mlir
///     // Reshape statically-shaped memref.
///     %dst = memref.reshape %src(%shape)
///              : (memref<4x1xf32>, memref<1xi32>) -> memref<4xf32>
///     %dst0 = memref.reshape %src(%shape0)
///              : (memref<4x1xf32>, memref<2xi32>) -> memref<2x2xf32>
///     // Flatten unranked memref.
///     %dst = memref.reshape %src(%shape)
///              : (memref<*xf32>, memref<1xi32>) -> memref<?xf32>
///     ```
/// 
///     b. Source type is ranked or unranked. Shape argument has dynamic size.
///     Result type is unranked.
/// 
///     ```mlir
///     // Reshape dynamically-shaped 1D memref.
///     %dst = memref.reshape %src(%shape)
///              : (memref<?xf32>, memref<?xi32>) -> memref<*xf32>
///     // Reshape unranked memref.
///     %dst = memref.reshape %src(%shape)
///              : (memref<*xf32>, memref<?xi32>) -> memref<*xf32>
///     ```
class ReshapeOp;

} // namespace mlir::memref
namespace mlir::memref {

/// store operation
/// The `store` op stores an element into a memref at the specified indices.
/// 
///     The number of indices must match the rank of the memref. The indices must
///     be in-bounds: `0 <= idx < dim_size`.
/// 
///     Lowerings of `memref.store` may emit attributes, e.g. `inbouds` + `nuw`
///     when converting to LLVM's `llvm.getelementptr`, that would cause undefined
///     behavior if indices are out of bounds or if computing the offset in the
///     memref would cause signed overflow of the `index` type.
/// 
///     A set `nontemporal` attribute indicates that this store is not expected to
///     be reused in the cache. For details, refer to the
///     [LLVM store instruction](https://llvm.org/docs/LangRef.html#store-instruction).
/// 
///     An optional `alignment` attribute allows to specify the byte alignment of the
///     store operation. It must be a positive power of 2. The operation must access
///     memory at an address aligned to this boundary. Violations may lead to
///     architecture-specific faults or performance penalties.
///     A value of 0 indicates no specific alignment requirement.
///     Example:
/// 
///     ```mlir
///     memref.store %val, %A[%a, %b] : memref<8x?xi32, #layout, memspace0>
///     ```
class StoreOp;

} // namespace mlir::memref
namespace mlir::memref {

/// `transpose` produces a new strided memref (metadata-only)
/// The `transpose` op produces a strided memref whose sizes and strides
///     are a permutation of the original `in` memref. This is purely a metadata
///     transformation.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = memref.transpose %0 (i, j) -> (j, i) : memref<?x?xf32> to memref<?x?xf32, affine_map<(d0, d1)[s0] -> (d1 * s0 + d0)>>
///     ```
class TransposeOp;

} // namespace mlir::memref
namespace mlir::memref {

/// memref view operation
/// The "view" operation extracts an N-D contiguous memref with empty layout map
///     with arbitrary element type from a 1-D contiguous memref with empty layout
///     map of i8 element  type. The ViewOp supports the following arguments:
/// 
///     * A single dynamic byte-shift operand must be specified which represents a
///       a shift of the base 1-D memref pointer from which to create the resulting
///       contiguous memref view with identity layout.
///     * A dynamic size operand that must be specified for each dynamic dimension
///       in the resulting view memref type.
/// 
///     The "view" operation gives a structured indexing form to a flat 1-D buffer.
///     Unlike "subview" it can perform a type change. The type change behavior
///     requires the op to have special semantics because, e.g. a byte shift of 3
///     cannot be represented as an offset on f64.
///     For now, a "view" op:
/// 
///     1. Only takes a contiguous source memref with 0 offset and empty layout.
///     2. Must specify a byte_shift operand (in the future, a special integer
///        attribute may be added to support the folded case).
///     3. Returns a contiguous memref with 0 offset and empty layout.
/// 
///     Example:
/// 
///     ```mlir
///     // Allocate a flat 1D/i8 memref.
///     %0 = memref.alloc() : memref<2048xi8>
/// 
///     // ViewOp with dynamic offset and static sizes.
///     %1 = memref.view %0[%offset_1024][] : memref<2048xi8> to memref<64x4xf32>
/// 
///     // ViewOp with dynamic offset and two dynamic size.
///     %2 = memref.view %0[%offset_1024][%size0, %size1] :
///       memref<2048xi8> to memref<?x4x?xf32>
///     ```
class ViewOp;

} // namespace mlir::memref
namespace mlir::memref {

/// memref subview operation
/// The `subview` operation converts a memref type to a memref type which
///     represents a reduced-size view of the original memref as specified by the
///     operation's offsets, sizes and strides arguments.
/// 
///     The `subview` operation supports the following arguments:
/// 
///     * source: the "base" memref on which to create a "view" memref.
///     * offsets: memref-rank number of offsets into the "base" memref at which to
///                create the "view" memref.
///     * sizes: memref-rank number of sizes which specify the sizes of the result
///              "view" memref type.
///     * strides: memref-rank number of strides that compose multiplicatively with
///                the base memref strides in each dimension.
/// 
///     The representation based on offsets, sizes and strides support a
///     partially-static specification via attributes specified through the
///     `static_offsets`, `static_sizes` and `static_strides` arguments. A special
///     sentinel value `ShapedType::kDynamic` encodes that the corresponding entry
///     has a dynamic value.
/// 
///     A `subview` operation may additionally reduce the rank of the resulting
///     view by removing dimensions that are statically known to be of size 1.
/// 
///     In the absence of rank reductions, the resulting memref type is computed
///     as follows:
///     ```
///     result_sizes[i] = size_operands[i]
///     result_strides[i] = src_strides[i] * stride_operands[i]
///     result_offset = src_offset + dot_product(offset_operands, src_strides)
///     ```
/// 
///     The offset, size and stride operands must be in-bounds with respect to the
///     source memref. When possible, the static operation verifier will detect
///     out-of-bounds subviews. Subviews that cannot be confirmed to be in-bounds
///     or out-of-bounds based on compile-time information are valid. However,
///     performing an out-of-bounds subview at runtime is undefined behavior.
/// 
///     Example 1:
/// 
///     Consecutive `subview` operations on memref's with static dimensions.
/// 
///     We distinguish between *underlying memory* — the sequence of elements as
///     they appear in the contiguous memory of the memref — and the
///     *strided memref*, which refers to the underlying memory interpreted
///     according to specified offsets, sizes, and strides.
/// 
///     ```mlir
///     %result1 = memref.subview %arg0[1, 1][4, 4][2, 2]
///     : memref<8x8xf32, strided<[8, 1], offset: 0>> to
///       memref<4x4xf32, strided<[16, 2], offset: 9>>
/// 
///     %result2 = memref.subview %result1[1, 1][2, 2][2, 2]
///     : memref<4x4xf32, strided<[16, 2], offset: 9>> to
///       memref<2x2xf32, strided<[32, 4], offset: 27>>
///     ```
/// 
///     The underlying memory of `%arg0` consists of a linear sequence of integers
///     from 1 to 64. Its memref has the following 8x8 elements:
/// 
///     ```mlir
///     [[1,  2,  3,  4,  5,  6,  7,  8],
///     [9,  10, 11, 12, 13, 14, 15, 16],
///     [17, 18, 19, 20, 21, 22, 23, 24],
///     [25, 26, 27, 28, 29, 30, 31, 32],
///     [33, 34, 35, 36, 37, 38, 39, 40],
///     [41, 42, 43, 44, 45, 46, 47, 48],
///     [49, 50, 51, 52, 53, 54, 55, 56],
///     [57, 58, 59, 60, 61, 62, 63, 64]]
///     ```
/// 
///     Following the first `subview`, the strided memref elements of `%result1`
///     are:
/// 
///     ```mlir
///     [[10, 12, 14, 16],
///     [26, 28, 30, 32],
///     [42, 44, 46, 48],
///     [58, 60, 62, 64]]
///     ```
/// 
///     Note: The offset and strides are relative to the strided memref of `%arg0`
///     (compare to the corresponding `reinterpret_cast` example).
/// 
///     The second `subview` results in the following strided memref for
///     `%result2`:
/// 
///     ```mlir
///     [[28, 32],
///     [60, 64]]
///     ```
/// 
///     Unlike the `reinterpret_cast`, the values are relative to the strided
///     memref of the input (`%result1` in this case) and not its
///     underlying memory.
/// 
///     Example 2:
/// 
///     ```mlir
///     // Subview of static memref with strided layout at static offsets, sizes
///     // and strides.
///     %1 = memref.subview %0[4, 2][8, 2][3, 2]
///         : memref<64x4xf32, strided<[7, 9], offset: 91>> to
///           memref<8x2xf32, strided<[21, 18], offset: 137>>
///     ```
/// 
///     Example 3:
/// 
///     ```mlir
///     // Subview of static memref with identity layout at dynamic offsets, sizes
///     // and strides.
///     %1 = memref.subview %0[%off0, %off1][%sz0, %sz1][%str0, %str1]
///         : memref<64x4xf32> to memref<?x?xf32, strided<[?, ?], offset: ?>>
///     ```
/// 
///     Example 4:
/// 
///     ```mlir
///     // Subview of dynamic memref with strided layout at dynamic offsets and
///     // strides, but static sizes.
///     %1 = memref.subview %0[%off0, %off1][4, 4][%str0, %str1]
///         : memref<?x?xf32, strided<[?, ?], offset: ?>> to
///           memref<4x4xf32, strided<[?, ?], offset: ?>>
///     ```
/// 
///     Example 5:
/// 
///     ```mlir
///     // Rank-reducing subviews.
///     %1 = memref.subview %0[0, 0, 0][1, 16, 4][1, 1, 1]
///         : memref<8x16x4xf32> to memref<16x4xf32>
///     %3 = memref.subview %2[3, 4, 2][1, 6, 3][1, 1, 1]
///         : memref<8x16x4xf32> to memref<6x3xf32, strided<[4, 1], offset: 210>>
///     ```
/// 
///     Example 6:
/// 
///     ```mlir
///     // Identity subview. The subview is the full source memref.
///     %1 = memref.subview %0[0, 0, 0] [8, 16, 4] [1, 1, 1]
///         : memref<8x16x4xf32> to memref<8x16x4xf32>
///     ```
class SubViewOp;

} // namespace mlir::memref
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::AssumeAlignmentOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AssumeAlignmentOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentTy = ::mlir::IntegerAttr;
    alignmentTy alignment;

    auto getAlignment() const {
      auto &propStorage = this->alignment;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
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
  AssumeAlignmentOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.assume_alignment", odsAttrs.getContext());
  }

  AssumeAlignmentOpGenericAdaptorBase(AssumeAlignmentOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getAlignmentAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().alignment);
    return attr;
  }

  uint32_t getAlignment();
};

} // namespace detail
template <typename RangeT>
class AssumeAlignmentOpGenericAdaptor : public detail::AssumeAlignmentOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AssumeAlignmentOpGenericAdaptorBase;
  static constexpr int odsIndex_memref = 0;
public:
  AssumeAlignmentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AssumeAlignmentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AssumeAlignmentOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AssumeAlignmentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AssumeAlignmentOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AssumeAlignmentOpGenericAdaptor(RangeT values, const AssumeAlignmentOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AssumeAlignmentOp, typename = std::enable_if_t<std::is_same_v<LateInst, AssumeAlignmentOp>>>
  AssumeAlignmentOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AssumeAlignmentOpAdaptor : public AssumeAlignmentOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AssumeAlignmentOpGenericAdaptor::AssumeAlignmentOpGenericAdaptor;
  AssumeAlignmentOpAdaptor(AssumeAlignmentOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AssumeAlignmentOp : public ::mlir::Op<AssumeAlignmentOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ViewLikeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AssumeAlignmentOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AssumeAlignmentOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<AssumeAlignmentOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<AssumeAlignmentOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<AssumeAlignmentOp>::getDefaultDialect;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<AssumeAlignmentOp>::reifyResultShapes;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<AssumeAlignmentOp>::reifyShapeOfResult;
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
    return ::llvm::StringLiteral("memref.assume_alignment");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getAlignmentAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().alignment);
  }

  uint32_t getAlignment();
  void setAlignmentAttr(::mlir::IntegerAttr attr) {
    getProperties().alignment = attr;
  }

  void setAlignment(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value memref, ::mlir::IntegerAttr alignment);
  static AssumeAlignmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value memref, ::mlir::IntegerAttr alignment);
  static AssumeAlignmentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value memref, ::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memref, ::mlir::IntegerAttr alignment);
  static AssumeAlignmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memref, ::mlir::IntegerAttr alignment);
  static AssumeAlignmentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memref, ::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::IntegerAttr alignment);
  static AssumeAlignmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::IntegerAttr alignment);
  static AssumeAlignmentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value memref, uint32_t alignment);
  static AssumeAlignmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value memref, uint32_t alignment);
  static AssumeAlignmentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value memref, uint32_t alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memref, uint32_t alignment);
  static AssumeAlignmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memref, uint32_t alignment);
  static AssumeAlignmentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memref, uint32_t alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, uint32_t alignment);
  static AssumeAlignmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, uint32_t alignment);
  static AssumeAlignmentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, uint32_t alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssumeAlignmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssumeAlignmentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssumeAlignmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssumeAlignmentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssumeAlignmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssumeAlignmentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssumeAlignmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssumeAlignmentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  ::llvm::FailureOr<::mlir::OpFoldResult> reifyDimOfResult(::mlir::OpBuilder &builder, int resultIndex, int dim);
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
  MemRefType getType() { return ::llvm::cast<MemRefType>(getResult().getType()); }

  Value getViewSource() { return getMemref(); }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::AssumeAlignmentOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::AtomicRMWOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AtomicRMWOpGenericAdaptorBase {
public:
  struct Properties {
    using kindTy = ::mlir::arith::AtomicRMWKindAttr;
    kindTy kind;

    auto getKind() const {
      auto &propStorage = this->kind;
      return ::llvm::cast<::mlir::arith::AtomicRMWKindAttr>(propStorage);
    }
    void setKind(const ::mlir::arith::AtomicRMWKindAttr &propValue) {
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
  AtomicRMWOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.atomic_rmw", odsAttrs.getContext());
  }

  AtomicRMWOpGenericAdaptorBase(AtomicRMWOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::arith::AtomicRMWKindAttr getKindAttr() {
    auto attr = ::llvm::cast<::mlir::arith::AtomicRMWKindAttr>(getProperties().kind);
    return attr;
  }

  ::mlir::arith::AtomicRMWKind getKind();
};

} // namespace detail
template <typename RangeT>
class AtomicRMWOpGenericAdaptor : public detail::AtomicRMWOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AtomicRMWOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_memref = 1;
  static constexpr int odsIndex_indices = 2;
public:
  AtomicRMWOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AtomicRMWOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AtomicRMWOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AtomicRMWOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AtomicRMWOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AtomicRMWOpGenericAdaptor(RangeT values, const AtomicRMWOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AtomicRMWOp, typename = std::enable_if_t<std::is_same_v<LateInst, AtomicRMWOp>>>
  AtomicRMWOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getMemref() {
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
class AtomicRMWOpAdaptor : public AtomicRMWOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AtomicRMWOpGenericAdaptor::AtomicRMWOpGenericAdaptor;
  AtomicRMWOpAdaptor(AtomicRMWOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AtomicRMWOp : public ::mlir::Op<AtomicRMWOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AtomicRMWOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AtomicRMWOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_memref = 1;
  static constexpr int odsIndex_indices = 2;
  using Properties = FoldAdaptor::Properties;
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
    return ::llvm::StringLiteral("memref.atomic_rmw");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMemrefMutable() {
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
  ::mlir::arith::AtomicRMWKindAttr getKindAttr() {
    return ::llvm::cast<::mlir::arith::AtomicRMWKindAttr>(getProperties().kind);
  }

  ::mlir::arith::AtomicRMWKind getKind();
  void setKindAttr(::mlir::arith::AtomicRMWKindAttr attr) {
    getProperties().kind = attr;
  }

  void setKind(::mlir::arith::AtomicRMWKind attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::arith::AtomicRMWKindAttr kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::arith::AtomicRMWKindAttr kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::arith::AtomicRMWKindAttr kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::arith::AtomicRMWKindAttr kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::arith::AtomicRMWKindAttr kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::arith::AtomicRMWKindAttr kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::arith::AtomicRMWKindAttr kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::arith::AtomicRMWKindAttr kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::arith::AtomicRMWKindAttr kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::arith::AtomicRMWKind kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::arith::AtomicRMWKind kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::arith::AtomicRMWKind kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::arith::AtomicRMWKind kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::arith::AtomicRMWKind kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::arith::AtomicRMWKind kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::arith::AtomicRMWKind kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::arith::AtomicRMWKind kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static AtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::arith::AtomicRMWKind kind, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
    return ::llvm::cast<MemRefType>(getMemref().getType());
  }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::AtomicRMWOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::AtomicYieldOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AtomicYieldOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AtomicYieldOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.atomic_yield", odsAttrs.getContext());
  }

  AtomicYieldOpGenericAdaptorBase(AtomicYieldOp op);

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
class AtomicYieldOpGenericAdaptor : public detail::AtomicYieldOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AtomicYieldOpGenericAdaptorBase;
  static constexpr int odsIndex_result = 0;
public:
  AtomicYieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AtomicYieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AtomicYieldOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AtomicYieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AtomicYieldOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AtomicYieldOpGenericAdaptor(RangeT values, const AtomicYieldOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AtomicYieldOp, typename = std::enable_if_t<std::is_same_v<LateInst, AtomicYieldOp>>>
  AtomicYieldOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getResult() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AtomicYieldOpAdaptor : public AtomicYieldOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AtomicYieldOpGenericAdaptor::AtomicYieldOpGenericAdaptor;
  AtomicYieldOpAdaptor(AtomicYieldOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AtomicYieldOp : public ::mlir::Op<AtomicYieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParent<GenericAtomicRMWOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AtomicYieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AtomicYieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_result = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<AtomicYieldOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.atomic_yield");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getResultMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value result);
  static AtomicYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value result);
  static AtomicYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value result);
  static AtomicYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value result);
  static AtomicYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value result);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::AtomicYieldOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::CopyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CopyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CopyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.copy", odsAttrs.getContext());
  }

  CopyOpGenericAdaptorBase(CopyOp op);

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
class CopyOpGenericAdaptor : public detail::CopyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CopyOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_target = 1;
public:
  CopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CopyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CopyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CopyOpGenericAdaptor(RangeT values, const CopyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CopyOp, typename = std::enable_if_t<std::is_same_v<LateInst, CopyOp>>>
  CopyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getTarget() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CopyOpAdaptor : public CopyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CopyOpGenericAdaptor::CopyOpGenericAdaptor;
  CopyOpAdaptor(CopyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CopyOp : public ::mlir::Op<CopyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::SameOperandsElementType, ::mlir::OpTrait::SameOperandsShape, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CopyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CopyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_target = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.copy");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::BaseMemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::BaseMemRefType> getTarget() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTargetMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::Value target);
  static CopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::Value target);
  static CopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::Value target);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value target);
  static CopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value target);
  static CopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value target);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::CopyOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::DistinctObjectsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DistinctObjectsOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DistinctObjectsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.distinct_objects", odsAttrs.getContext());
  }

  DistinctObjectsOpGenericAdaptorBase(DistinctObjectsOp op);

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
class DistinctObjectsOpGenericAdaptor : public detail::DistinctObjectsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DistinctObjectsOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  DistinctObjectsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DistinctObjectsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DistinctObjectsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DistinctObjectsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DistinctObjectsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DistinctObjectsOpGenericAdaptor(RangeT values, const DistinctObjectsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DistinctObjectsOp, typename = std::enable_if_t<std::is_same_v<LateInst, DistinctObjectsOp>>>
  DistinctObjectsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DistinctObjectsOpAdaptor : public DistinctObjectsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DistinctObjectsOpGenericAdaptor::DistinctObjectsOpGenericAdaptor;
  DistinctObjectsOpAdaptor(DistinctObjectsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DistinctObjectsOp : public ::mlir::Op<DistinctObjectsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::DistinctObjectsTrait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DistinctObjectsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DistinctObjectsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<DistinctObjectsOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.distinct_objects");
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
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DistinctObjectsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DistinctObjectsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DistinctObjectsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DistinctObjectsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DistinctObjectsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DistinctObjectsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DistinctObjectsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DistinctObjectsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::DistinctObjectsOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::GenericAtomicRMWOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GenericAtomicRMWOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GenericAtomicRMWOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.generic_atomic_rmw", odsAttrs.getContext());
  }

  GenericAtomicRMWOpGenericAdaptorBase(GenericAtomicRMWOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getAtomicBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class GenericAtomicRMWOpGenericAdaptor : public detail::GenericAtomicRMWOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GenericAtomicRMWOpGenericAdaptorBase;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_indices = 1;
public:
  GenericAtomicRMWOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GenericAtomicRMWOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GenericAtomicRMWOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GenericAtomicRMWOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GenericAtomicRMWOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GenericAtomicRMWOpGenericAdaptor(RangeT values, const GenericAtomicRMWOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GenericAtomicRMWOp, typename = std::enable_if_t<std::is_same_v<LateInst, GenericAtomicRMWOp>>>
  GenericAtomicRMWOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getIndices() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GenericAtomicRMWOpAdaptor : public GenericAtomicRMWOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GenericAtomicRMWOpGenericAdaptor::GenericAtomicRMWOpGenericAdaptor;
  GenericAtomicRMWOpAdaptor(GenericAtomicRMWOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GenericAtomicRMWOp : public ::mlir::Op<GenericAtomicRMWOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<AtomicYieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GenericAtomicRMWOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GenericAtomicRMWOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.generic_atomic_rmw");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getMemrefMutable() {
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

  ::mlir::Region &getAtomicBody() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value memref, ValueRange ivs);
  static GenericAtomicRMWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value memref, ValueRange ivs);
  static GenericAtomicRMWOp create(::mlir::ImplicitLocOpBuilder &builder, Value memref, ValueRange ivs);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  // TODO: remove post migrating callers.
  Region &body() { return getRegion(); }

  // The value stored in memref[ivs].
  Value getCurrentValue() {
    return getRegion().getArgument(0);
  }
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getMemref().getType());
  }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::GenericAtomicRMWOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::LoadOp declarations
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
      odsOpName.emplace("memref.load", odsAttrs.getContext());
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
  static constexpr int odsIndex_memref = 0;
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

  ValueT getMemref() {
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
class LoadOp : public ::mlir::Op<LoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::PromotableMemOpInterface::Trait, ::mlir::DestructurableAccessorOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
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
    return ::llvm::StringLiteral("memref.load");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getMemrefMutable() {
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type resultType, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type resultType, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, Type resultType, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  bool loadsFrom(const ::mlir::MemorySlot &slot);
  bool storesTo(const ::mlir::MemorySlot &slot);
  ::mlir::Value getStored(const ::mlir::MemorySlot &slot, ::mlir::OpBuilder &builder, ::mlir::Value reachingDef, const ::mlir::DataLayout &dataLayout);
  bool canUsesBeRemoved(const ::mlir::MemorySlot &slot, const ::llvm::SmallPtrSetImpl<::mlir::OpOperand *> &blockingUses, ::llvm::SmallVectorImpl<::mlir::OpOperand *> &newBlockingUses, const ::mlir::DataLayout &datalayout);
  ::mlir::DeletionKind removeBlockingUses(const ::mlir::MemorySlot &slot, const ::llvm::SmallPtrSetImpl<mlir::OpOperand *> &blockingUses, ::mlir::OpBuilder &builder, ::mlir::Value reachingDefinition, const ::mlir::DataLayout &dataLayout);
  bool canRewire(const ::mlir::DestructurableMemorySlot &slot, ::llvm::SmallPtrSetImpl<::mlir::Attribute> &usedIndices, ::mlir::SmallVectorImpl<::mlir::MemorySlot> &mustBeSafelyUsed, const ::mlir::DataLayout &dataLayout);
  ::mlir::DeletionKind rewire(const ::mlir::DestructurableMemorySlot &slot, ::llvm::DenseMap<::mlir::Attribute, ::mlir::MemorySlot> &subslots, ::mlir::OpBuilder &builder, const ::mlir::DataLayout &dataLayout);
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
  Value getMemRef() { return getOperand(0); }
  void setMemRef(Value value) { setOperand(0, value); }
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getMemRef().getType());
  }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::LoadOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::AllocOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllocOpGenericAdaptorBase {
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
    using operandSegmentSizesTy = std::array<int32_t, 2>;
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
        rhs.alignment == this->alignment &&
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
  AllocOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.alloc", odsAttrs.getContext());
  }

  AllocOpGenericAdaptorBase(AllocOp op);

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
class AllocOpGenericAdaptor : public detail::AllocOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllocOpGenericAdaptorBase;
  static constexpr int odsIndex_dynamicSizes = 0;
  static constexpr int odsIndex_symbolOperands = 1;
public:
  AllocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllocOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : AllocOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllocOpGenericAdaptor(RangeT values, const AllocOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllocOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllocOp>>>
  AllocOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getSymbolOperands() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllocOpAdaptor : public AllocOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllocOpGenericAdaptor::AllocOpGenericAdaptor;
  AllocOpAdaptor(AllocOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllocOp : public ::mlir::Op<AllocOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllocOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllocOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dynamicSizes = 0;
  static constexpr int odsIndex_symbolOperands = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<AllocOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<AllocOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<AllocOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.alloc");
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

  ::mlir::Operation::operand_range getSymbolOperands() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getDynamicSizesMutable();
  ::mlir::MutableOperandRange getSymbolOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSResults(0).begin());
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType memrefType, IntegerAttr alignment = IntegerAttr());
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType memrefType, IntegerAttr alignment = IntegerAttr());
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType memrefType, IntegerAttr alignment = IntegerAttr());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType memrefType, ValueRange dynamicSizes, IntegerAttr alignment = IntegerAttr());
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType memrefType, ValueRange dynamicSizes, IntegerAttr alignment = IntegerAttr());
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType memrefType, ValueRange dynamicSizes, IntegerAttr alignment = IntegerAttr());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType memrefType, ValueRange dynamicSizes, ValueRange symbolOperands, IntegerAttr alignment = {});
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType memrefType, ValueRange dynamicSizes, ValueRange symbolOperands, IntegerAttr alignment = {});
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType memrefType, ValueRange dynamicSizes, ValueRange symbolOperands, IntegerAttr alignment = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<OpFoldResult> sizes, Type elementType, Attribute memorySpace = {});
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<OpFoldResult> sizes, Type elementType, Attribute memorySpace = {});
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<OpFoldResult> sizes, Type elementType, Attribute memorySpace = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type memref, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type memref, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type memref, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  static StringRef getAlignmentAttrStrName() { return "alignment"; }

  MemRefType getType() { return ::llvm::cast<MemRefType>(getResult().getType()); }

  SmallVector<OpFoldResult> getMixedSizes() {
    SmallVector<OpFoldResult> result;
    unsigned ctr = 0;
    OpBuilder b(getContext());
    for (int64_t i = 0, e = getType().getRank(); i < e; ++i) {
      if (getType().isDynamicDim(i)) {
        result.push_back(getDynamicSizes()[ctr++]);
      } else {
        result.push_back(b.getIndexAttr(getType().getShape()[i]));
      }
    }
    return result;
  }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::AllocOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::AllocaOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllocaOpGenericAdaptorBase {
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
    using operandSegmentSizesTy = std::array<int32_t, 2>;
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
        rhs.alignment == this->alignment &&
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
  AllocaOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.alloca", odsAttrs.getContext());
  }

  AllocaOpGenericAdaptorBase(AllocaOp op);

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
class AllocaOpGenericAdaptor : public detail::AllocaOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllocaOpGenericAdaptorBase;
  static constexpr int odsIndex_dynamicSizes = 0;
  static constexpr int odsIndex_symbolOperands = 1;
public:
  AllocaOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllocaOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllocaOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllocaOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : AllocaOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllocaOpGenericAdaptor(RangeT values, const AllocaOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllocaOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllocaOp>>>
  AllocaOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getSymbolOperands() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllocaOpAdaptor : public AllocaOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllocaOpGenericAdaptor::AllocaOpGenericAdaptor;
  AllocaOpAdaptor(AllocaOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllocaOp : public ::mlir::Op<AllocaOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::PromotableAllocationOpInterface::Trait, ::mlir::DestructurableAllocationOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllocaOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllocaOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dynamicSizes = 0;
  static constexpr int odsIndex_symbolOperands = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<AllocaOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<AllocaOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<AllocaOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.alloca");
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

  ::mlir::Operation::operand_range getSymbolOperands() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getDynamicSizesMutable();
  ::mlir::MutableOperandRange getSymbolOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSResults(0).begin());
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType memrefType, IntegerAttr alignment = IntegerAttr());
  static AllocaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType memrefType, IntegerAttr alignment = IntegerAttr());
  static AllocaOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType memrefType, IntegerAttr alignment = IntegerAttr());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType memrefType, ValueRange dynamicSizes, IntegerAttr alignment = IntegerAttr());
  static AllocaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType memrefType, ValueRange dynamicSizes, IntegerAttr alignment = IntegerAttr());
  static AllocaOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType memrefType, ValueRange dynamicSizes, IntegerAttr alignment = IntegerAttr());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType memrefType, ValueRange dynamicSizes, ValueRange symbolOperands, IntegerAttr alignment = {});
  static AllocaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType memrefType, ValueRange dynamicSizes, ValueRange symbolOperands, IntegerAttr alignment = {});
  static AllocaOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType memrefType, ValueRange dynamicSizes, ValueRange symbolOperands, IntegerAttr alignment = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<OpFoldResult> sizes, Type elementType, Attribute memorySpace = {});
  static AllocaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<OpFoldResult> sizes, Type elementType, Attribute memorySpace = {});
  static AllocaOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<OpFoldResult> sizes, Type elementType, Attribute memorySpace = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type memref, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static AllocaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type memref, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static AllocaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type memref, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static AllocaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static AllocaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::SmallVector<::mlir::MemorySlot> getPromotableSlots();
  ::mlir::Value getDefaultValue(const ::mlir::MemorySlot &slot, ::mlir::OpBuilder &builder);
  void handleBlockArgument(const ::mlir::MemorySlot &slot, ::mlir::BlockArgument argument, ::mlir::OpBuilder &builder);
  ::std::optional<::mlir::PromotableAllocationOpInterface> handlePromotionComplete(const ::mlir::MemorySlot &slot, ::mlir::Value defaultValue, ::mlir::OpBuilder &builder);
  ::llvm::SmallVector<::mlir::DestructurableMemorySlot> getDestructurableSlots();
  ::llvm::DenseMap<::mlir::Attribute, ::mlir::MemorySlot> destructure(const ::mlir::DestructurableMemorySlot &slot, const ::llvm::SmallPtrSetImpl<::mlir::Attribute> &usedIndices, ::mlir::OpBuilder &builder, ::mlir::SmallVectorImpl<::mlir::DestructurableAllocationOpInterface> &newAllocators);
  ::std::optional<::mlir::DestructurableAllocationOpInterface> handleDestructuringComplete(const ::mlir::DestructurableMemorySlot &slot, ::mlir::OpBuilder &builder);
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
  static StringRef getAlignmentAttrStrName() { return "alignment"; }

  MemRefType getType() { return ::llvm::cast<MemRefType>(getResult().getType()); }

  SmallVector<OpFoldResult> getMixedSizes() {
    SmallVector<OpFoldResult> result;
    unsigned ctr = 0;
    OpBuilder b(getContext());
    for (int64_t i = 0, e = getType().getRank(); i < e; ++i) {
      if (getType().isDynamicDim(i)) {
        result.push_back(getDynamicSizes()[ctr++]);
      } else {
        result.push_back(b.getIndexAttr(getType().getShape()[i]));
      }
    }
    return result;
  }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::AllocaOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::AllocaScopeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllocaScopeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AllocaScopeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.alloca_scope", odsAttrs.getContext());
  }

  AllocaScopeOpGenericAdaptorBase(AllocaScopeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBodyRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class AllocaScopeOpGenericAdaptor : public detail::AllocaScopeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllocaScopeOpGenericAdaptorBase;
public:
  AllocaScopeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllocaScopeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllocaScopeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllocaScopeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AllocaScopeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllocaScopeOpGenericAdaptor(RangeT values, const AllocaScopeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllocaScopeOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllocaScopeOp>>>
  AllocaScopeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AllocaScopeOpAdaptor : public AllocaScopeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllocaScopeOpGenericAdaptor::AllocaScopeOpGenericAdaptor;
  AllocaScopeOpAdaptor(AllocaScopeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllocaScopeOp : public ::mlir::Op<AllocaScopeOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<AllocaScopeReturnOp>::Impl, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::RegionBranchOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllocaScopeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllocaScopeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchOpInterface::Trait<AllocaScopeOp>::getEntrySuccessorOperands;
  using ::mlir::RegionBranchOpInterface::Trait<AllocaScopeOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<AllocaScopeOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<AllocaScopeOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<AllocaScopeOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<AllocaScopeOp>::getRegionInvocationBounds;
  using ::mlir::RegionBranchOpInterface::Trait<AllocaScopeOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.alloca_scope");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
  }

  ::mlir::Region &getBodyRegion() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results);
  static AllocaScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results);
  static AllocaScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocaScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocaScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocaScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocaScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::AllocaScopeOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::AllocaScopeReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllocaScopeReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AllocaScopeReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.alloca_scope.return", odsAttrs.getContext());
  }

  AllocaScopeReturnOpGenericAdaptorBase(AllocaScopeReturnOp op);

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
class AllocaScopeReturnOpGenericAdaptor : public detail::AllocaScopeReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllocaScopeReturnOpGenericAdaptorBase;
  static constexpr int odsIndex_results = 0;
public:
  AllocaScopeReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllocaScopeReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllocaScopeReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllocaScopeReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AllocaScopeReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllocaScopeReturnOpGenericAdaptor(RangeT values, const AllocaScopeReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllocaScopeReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllocaScopeReturnOp>>>
  AllocaScopeReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getResults() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllocaScopeReturnOpAdaptor : public AllocaScopeReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllocaScopeReturnOpGenericAdaptor::AllocaScopeReturnOpGenericAdaptor;
  AllocaScopeReturnOpAdaptor(AllocaScopeReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllocaScopeReturnOp : public ::mlir::Op<AllocaScopeReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<AllocaScopeOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllocaScopeReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllocaScopeReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_results = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<AllocaScopeReturnOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.alloca_scope.return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getResults() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getResultsMutable();
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
  static AllocaScopeReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static AllocaScopeReturnOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange results);
  static AllocaScopeReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange results);
  static AllocaScopeReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange results);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocaScopeReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocaScopeReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocaScopeReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocaScopeReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::AllocaScopeReturnOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::CastOp declarations
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
      odsOpName.emplace("memref.cast", odsAttrs.getContext());
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
class CastOp : public ::mlir::Op<CastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::BaseMemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::CastOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultShape, ::mlir::ViewLikeOpInterface::Trait> {
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
    return ::llvm::StringLiteral("memref.cast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::BaseMemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::BaseMemRefType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSResults(0).begin());
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
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static bool areCastCompatible(::mlir::TypeRange inputs, ::mlir::TypeRange outputs);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// Fold the given CastOp into consumer op.
  static bool canFoldIntoConsumerOp(CastOp castOp);

  Value getViewSource() { return getSource(); }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::CastOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::CollapseShapeOp declarations
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
      odsOpName.emplace("memref.collapse_shape", odsAttrs.getContext());
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
class CollapseShapeOp : public ::mlir::Op<CollapseShapeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ViewLikeOpInterface::Trait> {
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
    return ::llvm::StringLiteral("memref.collapse_shape");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
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
  };

  MemRefType getSrcType() { return ::llvm::cast<MemRefType>(getSrc().getType()); }

  MemRefType getResultType() { return ::llvm::cast<MemRefType>(getResult().getType()); }

  Value getViewSource() { return getSrc(); }

  /// Return `true` if this source MemRef type is guaranteed to be collapsible
  /// according to the given reassociation indices. In the presence of dynamic
  /// strides this is usually not the case.
  static bool isGuaranteedCollapsible(
      MemRefType srcType, ArrayRef<ReassociationIndices> reassociation);

  static MemRefType computeCollapsedType(
      MemRefType srcType, ArrayRef<ReassociationIndices> reassociation);
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::CollapseShapeOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::DeallocOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeallocOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DeallocOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.dealloc", odsAttrs.getContext());
  }

  DeallocOpGenericAdaptorBase(DeallocOp op);

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
class DeallocOpGenericAdaptor : public detail::DeallocOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeallocOpGenericAdaptorBase;
  static constexpr int odsIndex_memref = 0;
public:
  DeallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeallocOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DeallocOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeallocOpGenericAdaptor(RangeT values, const DeallocOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeallocOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeallocOp>>>
  DeallocOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DeallocOpAdaptor : public DeallocOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeallocOpGenericAdaptor::DeallocOpGenericAdaptor;
  DeallocOpAdaptor(DeallocOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeallocOp : public ::mlir::Op<DeallocOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeallocOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeallocOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.dealloc");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::BaseMemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSOperands(0).begin());
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memref);
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memref);
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref);
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref);
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::DeallocOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::DimOp declarations
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
      odsOpName.emplace("memref.dim", odsAttrs.getContext());
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
class DimOp : public ::mlir::Op<DimOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::ConditionallySpeculatable::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ShapedDimOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
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
    return ::llvm::StringLiteral("memref.dim");
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

  /// Interface method of ShapedDimOpInterface: Return the source memref.
  Value getShapedValue() { return getSource(); }

  /// Interface method of ShapedDimOpInterface: Return the dimension.
  OpFoldResult getDimension() { return getIndex(); }

  /// Interface method for ConditionallySpeculatable.
  Speculation::Speculatability getSpeculatability();
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::DimOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::DmaStartOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DmaStartOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DmaStartOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.dma_start", odsAttrs.getContext());
  }

  DmaStartOpGenericAdaptorBase(DmaStartOp op);

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
class DmaStartOpGenericAdaptor : public detail::DmaStartOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DmaStartOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  DmaStartOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DmaStartOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DmaStartOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DmaStartOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DmaStartOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DmaStartOpGenericAdaptor(RangeT values, const DmaStartOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DmaStartOp, typename = std::enable_if_t<std::is_same_v<LateInst, DmaStartOp>>>
  DmaStartOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DmaStartOpAdaptor : public DmaStartOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DmaStartOpGenericAdaptor::DmaStartOpGenericAdaptor;
  DmaStartOpAdaptor(DmaStartOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DmaStartOp : public ::mlir::Op<DmaStartOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DmaStartOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DmaStartOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.dma_start");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value srcMemRef, ValueRange srcIndices, Value destMemRef, ValueRange destIndices, Value numElements, Value tagMemRef, ValueRange tagIndices, Value stride = {}, Value elementsPerStride = {});
  static DmaStartOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value srcMemRef, ValueRange srcIndices, Value destMemRef, ValueRange destIndices, Value numElements, Value tagMemRef, ValueRange tagIndices, Value stride = {}, Value elementsPerStride = {});
  static DmaStartOp create(::mlir::ImplicitLocOpBuilder &builder, Value srcMemRef, ValueRange srcIndices, Value destMemRef, ValueRange destIndices, Value numElements, Value tagMemRef, ValueRange tagIndices, Value stride = {}, Value elementsPerStride = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static DmaStartOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands);
  static DmaStartOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DmaStartOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DmaStartOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DmaStartOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DmaStartOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
  // Returns the source MemRefType for this DMA operation.
  Value getSrcMemRef() { return getOperand(0); }
  OpOperand &getSrcMemRefMutable() { return getOperation()->getOpOperand(0); }
  // Returns the rank (number of indices) of the source MemRefType.
  unsigned getSrcMemRefRank() {
    return ::llvm::cast<MemRefType>(getSrcMemRef().getType()).getRank();
  }
  // Returns the source memref indices for this DMA operation.
  operand_range getSrcIndices() {
    return {(*this)->operand_begin() + 1,
            (*this)->operand_begin() + 1 + getSrcMemRefRank()};
  }

  // Returns the destination MemRefType for this DMA operations.
  Value getDstMemRef() { return getOperand(1 + getSrcMemRefRank()); }
  OpOperand &getDstMemRefMutable() { return getOperation()->getOpOperand(1 + getSrcMemRefRank()); }
  // Returns the rank (number of indices) of the destination MemRefType.
  unsigned getDstMemRefRank() {
    return ::llvm::cast<MemRefType>(getDstMemRef().getType()).getRank();
  }
  unsigned getSrcMemorySpace() {
    return ::llvm::cast<MemRefType>(getSrcMemRef().getType()).getMemorySpaceAsInt();
  }
  unsigned getDstMemorySpace() {
    return ::llvm::cast<MemRefType>(getDstMemRef().getType()).getMemorySpaceAsInt();
  }

  // Returns the destination memref indices for this DMA operation.
  operand_range getDstIndices() {
    return {(*this)->operand_begin() + 1 + getSrcMemRefRank() + 1,
            (*this)->operand_begin() + 1 + getSrcMemRefRank() + 1 +
                getDstMemRefRank()};
  }

  // Returns the number of elements being transferred by this DMA operation.
  Value getNumElements() {
    return getOperand(1 + getSrcMemRefRank() + 1 + getDstMemRefRank());
  }

  // Returns the Tag MemRef for this DMA operation.
  Value getTagMemRef() {
    return getOperand(1 + getSrcMemRefRank() + 1 + getDstMemRefRank() + 1);
  }
  OpOperand &getTagMemRefMutable() {
    return getOperation()->getOpOperand(1 + getSrcMemRefRank() + 1 + getDstMemRefRank() + 1);
  }

  // Returns the rank (number of indices) of the tag MemRefType.
  unsigned getTagMemRefRank() {
    return ::llvm::cast<MemRefType>(getTagMemRef().getType()).getRank();
  }

  // Returns the tag memref index for this DMA operation.
  operand_range getTagIndices() {
    unsigned tagIndexStartPos =
        1 + getSrcMemRefRank() + 1 + getDstMemRefRank() + 1 + 1;
    return {(*this)->operand_begin() + tagIndexStartPos,
            (*this)->operand_begin() + tagIndexStartPos + getTagMemRefRank()};
  }

  /// Returns true if this is a DMA from a faster memory space to a slower
  /// one.
  bool isDestMemorySpaceFaster() {
    return (getSrcMemorySpace() < getDstMemorySpace());
  }

  /// Returns true if this is a DMA from a slower memory space to a faster
  /// one.
  bool isSrcMemorySpaceFaster() {
    // Assumes that a lower number is for a slower memory space.
    return (getDstMemorySpace() < getSrcMemorySpace());
  }

  /// Given a DMA start operation, returns the operand position of either the
  /// source or destination memref depending on the one that is at the higher
  /// level of the memory hierarchy. Asserts failure if neither is true.
  unsigned getFasterMemPos() {
    assert(isSrcMemorySpaceFaster() || isDestMemorySpaceFaster());
    return isSrcMemorySpaceFaster() ? 0 : getSrcMemRefRank() + 1;
  }

  bool isStrided() {
    return getNumOperands() != 1 + getSrcMemRefRank() + 1 +
                               getDstMemRefRank() + 1 + 1 +
                               getTagMemRefRank();
  }

  Value getStride() {
    if (!isStrided())
      return nullptr;
    return getOperand(getNumOperands() - 1 - 1);
  }

  Value getNumElementsPerStride() {
    if (!isStrided())
      return nullptr;
    return getOperand(getNumOperands() - 1);
  }

  void getEffects(
      SmallVectorImpl<SideEffects::EffectInstance<MemoryEffects::Effect>> &
      effects) {
    effects.emplace_back(MemoryEffects::Read::get(), &getSrcMemRefMutable(),
                         SideEffects::DefaultResource::get());
    effects.emplace_back(MemoryEffects::Write::get(), &getDstMemRefMutable(),
                         SideEffects::DefaultResource::get());
    effects.emplace_back(MemoryEffects::Read::get(), &getTagMemRefMutable(),
                         SideEffects::DefaultResource::get());
  }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::DmaStartOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::DmaWaitOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DmaWaitOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DmaWaitOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.dma_wait", odsAttrs.getContext());
  }

  DmaWaitOpGenericAdaptorBase(DmaWaitOp op);

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
class DmaWaitOpGenericAdaptor : public detail::DmaWaitOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DmaWaitOpGenericAdaptorBase;
  static constexpr int odsIndex_tagMemRef = 0;
  static constexpr int odsIndex_tagIndices = 1;
  static constexpr int odsIndex_numElements = 2;
public:
  DmaWaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DmaWaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DmaWaitOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DmaWaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DmaWaitOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DmaWaitOpGenericAdaptor(RangeT values, const DmaWaitOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DmaWaitOp, typename = std::enable_if_t<std::is_same_v<LateInst, DmaWaitOp>>>
  DmaWaitOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTagMemRef() {
    return (*getODSOperands(0).begin());
  }

  RangeT getTagIndices() {
    return getODSOperands(1);
  }

  ValueT getNumElements() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DmaWaitOpAdaptor : public DmaWaitOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DmaWaitOpGenericAdaptor::DmaWaitOpGenericAdaptor;
  DmaWaitOpAdaptor(DmaWaitOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DmaWaitOp : public ::mlir::Op<DmaWaitOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DmaWaitOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DmaWaitOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tagMemRef = 0;
  static constexpr int odsIndex_tagIndices = 1;
  static constexpr int odsIndex_numElements = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.dma_wait");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getTagMemRef() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getTagIndices() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::IndexType> getNumElements() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getTagMemRefMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getTagIndicesMutable();
  ::mlir::OpOperand &getNumElementsMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tagMemRef, ::mlir::ValueRange tagIndices, ::mlir::Value numElements);
  static DmaWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tagMemRef, ::mlir::ValueRange tagIndices, ::mlir::Value numElements);
  static DmaWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tagMemRef, ::mlir::ValueRange tagIndices, ::mlir::Value numElements);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tagMemRef, ::mlir::ValueRange tagIndices, ::mlir::Value numElements);
  static DmaWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tagMemRef, ::mlir::ValueRange tagIndices, ::mlir::Value numElements);
  static DmaWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tagMemRef, ::mlir::ValueRange tagIndices, ::mlir::Value numElements);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DmaWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DmaWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DmaWaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DmaWaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Returns the rank (number of indices) of the tag memref.
  unsigned getTagMemRefRank() {
    return ::llvm::cast<MemRefType>(getTagMemRef().getType()).getRank();
  }
  void getEffects(
      SmallVectorImpl<SideEffects::EffectInstance<MemoryEffects::Effect>> &
      effects) {
    effects.emplace_back(MemoryEffects::Read::get(), &getTagMemRefMutable(),
                         SideEffects::DefaultResource::get());
  }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::DmaWaitOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::ExpandShapeOp declarations
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
      odsOpName.emplace("memref.expand_shape", odsAttrs.getContext());
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
class ExpandShapeOp : public ::mlir::Op<ExpandShapeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::ReifyRankedShapedTypeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ViewLikeOpInterface::Trait> {
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
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<ExpandShapeOp>::reifyShapeOfResult;
  using ::mlir::ReifyRankedShapedTypeOpInterface::Trait<ExpandShapeOp>::reifyDimOfResult;
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
    return ::llvm::StringLiteral("memref.expand_shape");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<int64_t> resultShape, Value src, ArrayRef<ReassociationIndices> reassociation);
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<int64_t> resultShape, Value src, ArrayRef<ReassociationIndices> reassociation);
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<int64_t> resultShape, Value src, ArrayRef<ReassociationIndices> reassociation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<int64_t> resultShape, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<OpFoldResult> outputShape);
  static ExpandShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<int64_t> resultShape, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<OpFoldResult> outputShape);
  static ExpandShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<int64_t> resultShape, Value src, ArrayRef<ReassociationIndices> reassociation, ArrayRef<OpFoldResult> outputShape);
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
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  ::llvm::LogicalResult reifyResultShapes(::mlir::OpBuilder &builder, ::mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);
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
  };

  MemRefType getSrcType() { return ::llvm::cast<MemRefType>(getSrc().getType()); }

  MemRefType getResultType() { return ::llvm::cast<MemRefType>(getResult().getType()); }

  Value getViewSource() { return getSrc(); }

  static FailureOr<MemRefType> computeExpandedType(
      MemRefType srcType, ArrayRef<int64_t> resultShape,
      ArrayRef<ReassociationIndices> reassociation);

  // Infer the output shape for a memref.expand_shape when it is possible
  // to do so.
  static FailureOr<SmallVector<OpFoldResult>> inferOutputShape(
      OpBuilder &b, Location loc, MemRefType expandedType,
      ArrayRef<ReassociationIndices> reassociation,
      ArrayRef<OpFoldResult> inputShape);

  // Return a vector with all the static and dynamic values in the output shape.
  SmallVector<OpFoldResult> getMixedOutputShape() {
    OpBuilder builder(getContext());
    return ::mlir::getMixedValues(getStaticOutputShape(), getOutputShape(), builder);
  }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::ExpandShapeOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::ExtractAlignedPointerAsIndexOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtractAlignedPointerAsIndexOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ExtractAlignedPointerAsIndexOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.extract_aligned_pointer_as_index", odsAttrs.getContext());
  }

  ExtractAlignedPointerAsIndexOpGenericAdaptorBase(ExtractAlignedPointerAsIndexOp op);

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
class ExtractAlignedPointerAsIndexOpGenericAdaptor : public detail::ExtractAlignedPointerAsIndexOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtractAlignedPointerAsIndexOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  ExtractAlignedPointerAsIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExtractAlignedPointerAsIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExtractAlignedPointerAsIndexOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExtractAlignedPointerAsIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExtractAlignedPointerAsIndexOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExtractAlignedPointerAsIndexOpGenericAdaptor(RangeT values, const ExtractAlignedPointerAsIndexOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExtractAlignedPointerAsIndexOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExtractAlignedPointerAsIndexOp>>>
  ExtractAlignedPointerAsIndexOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ExtractAlignedPointerAsIndexOpAdaptor : public ExtractAlignedPointerAsIndexOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExtractAlignedPointerAsIndexOpGenericAdaptor::ExtractAlignedPointerAsIndexOpGenericAdaptor;
  ExtractAlignedPointerAsIndexOpAdaptor(ExtractAlignedPointerAsIndexOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExtractAlignedPointerAsIndexOp : public ::mlir::Op<ExtractAlignedPointerAsIndexOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtractAlignedPointerAsIndexOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtractAlignedPointerAsIndexOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ExtractAlignedPointerAsIndexOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ExtractAlignedPointerAsIndexOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ExtractAlignedPointerAsIndexOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.extract_aligned_pointer_as_index");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::BaseMemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::IndexType> getAlignedPointer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type aligned_pointer, ::mlir::Value source);
  static ExtractAlignedPointerAsIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type aligned_pointer, ::mlir::Value source);
  static ExtractAlignedPointerAsIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type aligned_pointer, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source);
  static ExtractAlignedPointerAsIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source);
  static ExtractAlignedPointerAsIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static ExtractAlignedPointerAsIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static ExtractAlignedPointerAsIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractAlignedPointerAsIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractAlignedPointerAsIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractAlignedPointerAsIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractAlignedPointerAsIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractAlignedPointerAsIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractAlignedPointerAsIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractAlignedPointerAsIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractAlignedPointerAsIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::ExtractAlignedPointerAsIndexOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::ExtractStridedMetadataOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtractStridedMetadataOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ExtractStridedMetadataOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.extract_strided_metadata", odsAttrs.getContext());
  }

  ExtractStridedMetadataOpGenericAdaptorBase(ExtractStridedMetadataOp op);

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
class ExtractStridedMetadataOpGenericAdaptor : public detail::ExtractStridedMetadataOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtractStridedMetadataOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  ExtractStridedMetadataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExtractStridedMetadataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExtractStridedMetadataOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExtractStridedMetadataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExtractStridedMetadataOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExtractStridedMetadataOpGenericAdaptor(RangeT values, const ExtractStridedMetadataOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExtractStridedMetadataOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExtractStridedMetadataOp>>>
  ExtractStridedMetadataOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ExtractStridedMetadataOpAdaptor : public ExtractStridedMetadataOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExtractStridedMetadataOpGenericAdaptor::ExtractStridedMetadataOpGenericAdaptor;
  ExtractStridedMetadataOpAdaptor(ExtractStridedMetadataOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExtractStridedMetadataOp : public ::mlir::Op<ExtractStridedMetadataOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ViewLikeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpTrait::InferTypeOpAdaptor> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtractStridedMetadataOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtractStridedMetadataOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ExtractStridedMetadataOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ExtractStridedMetadataOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ExtractStridedMetadataOp>::getDefaultDialect;
  using ::mlir::InferTypeOpInterface::Trait<ExtractStridedMetadataOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.extract_strided_metadata");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::Type> getBaseBuffer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getOffset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(1).begin());
  }

  ::mlir::Operation::result_range getSizes() {
    return getODSResults(2);
  }

  ::mlir::Operation::result_range getStrides() {
    return getODSResults(3);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type base_buffer, ::mlir::Type offset, ::mlir::TypeRange sizes, ::mlir::TypeRange strides, ::mlir::Value source);
  static ExtractStridedMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type base_buffer, ::mlir::Type offset, ::mlir::TypeRange sizes, ::mlir::TypeRange strides, ::mlir::Value source);
  static ExtractStridedMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type base_buffer, ::mlir::Type offset, ::mlir::TypeRange sizes, ::mlir::TypeRange strides, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source);
  static ExtractStridedMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source);
  static ExtractStridedMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static ExtractStridedMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static ExtractStridedMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractStridedMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractStridedMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractStridedMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractStridedMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractStridedMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractStridedMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractStridedMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractStridedMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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


  /// Return a vector of all the static or dynamic sizes of the op, while
  /// statically inferring the sizes of the dynamic sizes, when possible.
  /// This is best effort.
  /// E.g., if `getSizes` returns `[%dyn_size0, %dyn_size1]`, but the
  /// source memref type is `memref<2x8xi16>`, this method will
  /// return `[2, 8]`.
  /// Similarly if the resulting memref type is `memref<2x?xi16>`, but
  /// `%dyn_size1` can statically be pinned to a constant value, this
  /// constant value is returned instead of `%dyn_size`.
  SmallVector<OpFoldResult> getConstifiedMixedSizes();
  /// Similar to `getConstifiedMixedSizes` but for strides.
  SmallVector<OpFoldResult> getConstifiedMixedStrides();
  /// Similar to `getConstifiedMixedSizes` but for the offset.
  OpFoldResult getConstifiedMixedOffset();

  ::mlir::Value getViewSource() { return getSource(); }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::ExtractStridedMetadataOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::GetGlobalOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetGlobalOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::FlatSymbolRefAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setName(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.name == this->name &&
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
  GetGlobalOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.get_global", odsAttrs.getContext());
  }

  GetGlobalOpGenericAdaptorBase(GetGlobalOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
};

} // namespace detail
template <typename RangeT>
class GetGlobalOpGenericAdaptor : public detail::GetGlobalOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetGlobalOpGenericAdaptorBase;
public:
  GetGlobalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetGlobalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetGlobalOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetGlobalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetGlobalOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetGlobalOpGenericAdaptor(RangeT values, const GetGlobalOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetGlobalOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetGlobalOp>>>
  GetGlobalOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GetGlobalOpAdaptor : public GetGlobalOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetGlobalOpGenericAdaptor::GetGlobalOpGenericAdaptor;
  GetGlobalOpAdaptor(GetGlobalOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetGlobalOp : public ::mlir::Op<GetGlobalOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetGlobalOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetGlobalOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.get_global");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::FlatSymbolRefAttr getNameAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr name);
  static GetGlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr name);
  static GetGlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr name);
  static GetGlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr name);
  static GetGlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef name);
  static GetGlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef name);
  static GetGlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name);
  static GetGlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name);
  static GetGlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetGlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetGlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetGlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetGlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::GetGlobalOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::GlobalOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GlobalOpGenericAdaptorBase {
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
    using constantTy = ::mlir::UnitAttr;
    constantTy constant;

    auto getConstant() const {
      auto &propStorage = this->constant;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setConstant(const ::mlir::UnitAttr &propValue) {
      this->constant = propValue;
    }
    using initial_valueTy = ::mlir::Attribute;
    initial_valueTy initial_value;

    auto getInitialValue() const {
      auto &propStorage = this->initial_value;
      return ::llvm::dyn_cast_or_null<::mlir::Attribute>(propStorage);
    }
    void setInitialValue(const ::mlir::Attribute &propValue) {
      this->initial_value = propValue;
    }
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    using sym_visibilityTy = ::mlir::StringAttr;
    sym_visibilityTy sym_visibility;

    auto getSymVisibility() const {
      auto &propStorage = this->sym_visibility;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSymVisibility(const ::mlir::StringAttr &propValue) {
      this->sym_visibility = propValue;
    }
    using typeTy = ::mlir::TypeAttr;
    typeTy type;

    auto getType() const {
      auto &propStorage = this->type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setType(const ::mlir::TypeAttr &propValue) {
      this->type = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.alignment == this->alignment &&
        rhs.constant == this->constant &&
        rhs.initial_value == this->initial_value &&
        rhs.sym_name == this->sym_name &&
        rhs.sym_visibility == this->sym_visibility &&
        rhs.type == this->type &&
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
  GlobalOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.global", odsAttrs.getContext());
  }

  GlobalOpGenericAdaptorBase(GlobalOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
  ::mlir::StringAttr getSymVisibilityAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_visibility);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSymVisibility();
  ::mlir::TypeAttr getTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
    return attr;
  }

  ::mlir::MemRefType getType();
  ::mlir::Attribute getInitialValueAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().initial_value);
    return attr;
  }

  ::std::optional<::mlir::Attribute> getInitialValue();
  ::mlir::UnitAttr getConstantAttr();
  bool getConstant();
  ::mlir::IntegerAttr getAlignmentAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
    return attr;
  }

  ::std::optional<uint64_t> getAlignment();
};

} // namespace detail
template <typename RangeT>
class GlobalOpGenericAdaptor : public detail::GlobalOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GlobalOpGenericAdaptorBase;
public:
  GlobalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GlobalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GlobalOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GlobalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GlobalOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GlobalOpGenericAdaptor(RangeT values, const GlobalOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GlobalOp, typename = std::enable_if_t<std::is_same_v<LateInst, GlobalOp>>>
  GlobalOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GlobalOpAdaptor : public GlobalOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GlobalOpGenericAdaptor::GlobalOpGenericAdaptor;
  GlobalOpAdaptor(GlobalOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GlobalOp : public ::mlir::Op<GlobalOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GlobalOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GlobalOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignment"), ::llvm::StringRef("constant"), ::llvm::StringRef("initial_value"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("sym_visibility"), ::llvm::StringRef("type")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getConstantAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getConstantAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getInitialValueAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getInitialValueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getSymVisibilityAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getSymVisibilityAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getTypeAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.global");
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  ::mlir::StringAttr getSymVisibilityAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_visibility);
  }

  ::std::optional< ::llvm::StringRef > getSymVisibility();
  ::mlir::TypeAttr getTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
  }

  ::mlir::MemRefType getType();
  ::mlir::Attribute getInitialValueAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().initial_value);
  }

  ::std::optional<::mlir::Attribute> getInitialValue();
  ::mlir::UnitAttr getConstantAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().constant);
  }

  bool getConstant();
  ::mlir::IntegerAttr getAlignmentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().alignment);
  }

  ::std::optional<uint64_t> getAlignment();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setSymVisibilityAttr(::mlir::StringAttr attr) {
    getProperties().sym_visibility = attr;
  }

  void setSymVisibility(::std::optional<::llvm::StringRef> attrValue);
  void setTypeAttr(::mlir::TypeAttr attr) {
    getProperties().type = attr;
  }

  void setType(::mlir::MemRefType attrValue);
  void setInitialValueAttr(::mlir::Attribute attr) {
    getProperties().initial_value = attr;
  }

  void setConstantAttr(::mlir::UnitAttr attr) {
    getProperties().constant = attr;
  }

  void setConstant(bool attrValue);
  void setAlignmentAttr(::mlir::IntegerAttr attr) {
    getProperties().alignment = attr;
  }

  void setAlignment(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeSymVisibilityAttr() {
      auto attr = getProperties().sym_visibility;
      getProperties().sym_visibility = {};
      return attr;
  }

  ::mlir::Attribute removeInitialValueAttr() {
      auto attr = getProperties().initial_value;
      getProperties().initial_value = {};
      return attr;
  }

  ::mlir::Attribute removeConstantAttr() {
      auto attr = getProperties().constant;
      getProperties().constant = {};
      return attr;
  }

  ::mlir::Attribute removeAlignmentAttr() {
      auto attr = getProperties().alignment;
      getProperties().alignment = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::TypeAttr type, /*optional*/::mlir::Attribute initial_value, /*optional*/::mlir::UnitAttr constant, /*optional*/::mlir::IntegerAttr alignment);
  static GlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::TypeAttr type, /*optional*/::mlir::Attribute initial_value, /*optional*/::mlir::UnitAttr constant, /*optional*/::mlir::IntegerAttr alignment);
  static GlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::TypeAttr type, /*optional*/::mlir::Attribute initial_value, /*optional*/::mlir::UnitAttr constant, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::TypeAttr type, /*optional*/::mlir::Attribute initial_value, /*optional*/::mlir::UnitAttr constant, /*optional*/::mlir::IntegerAttr alignment);
  static GlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::TypeAttr type, /*optional*/::mlir::Attribute initial_value, /*optional*/::mlir::UnitAttr constant, /*optional*/::mlir::IntegerAttr alignment);
  static GlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::TypeAttr type, /*optional*/::mlir::Attribute initial_value, /*optional*/::mlir::UnitAttr constant, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::MemRefType type, /*optional*/::mlir::Attribute initial_value, /*optional*/bool constant, /*optional*/::mlir::IntegerAttr alignment);
  static GlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::MemRefType type, /*optional*/::mlir::Attribute initial_value, /*optional*/bool constant, /*optional*/::mlir::IntegerAttr alignment);
  static GlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::MemRefType type, /*optional*/::mlir::Attribute initial_value, /*optional*/bool constant, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::MemRefType type, /*optional*/::mlir::Attribute initial_value, /*optional*/bool constant, /*optional*/::mlir::IntegerAttr alignment);
  static GlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::MemRefType type, /*optional*/::mlir::Attribute initial_value, /*optional*/bool constant, /*optional*/::mlir::IntegerAttr alignment);
  static GlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::StringAttr sym_visibility, ::mlir::MemRefType type, /*optional*/::mlir::Attribute initial_value, /*optional*/bool constant, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GlobalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GlobalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 6 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  bool isExternal() { return !getInitialValue(); }
  bool isUninitialized() {
    return !isExternal() && ::llvm::isa<UnitAttr>(*getInitialValue());
  }
  /// Returns the constant initial value if the memref.global is a constant,
  /// or null otherwise.
  ElementsAttr getConstantInitValue();
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::GlobalOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::MemorySpaceCastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemorySpaceCastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MemorySpaceCastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.memory_space_cast", odsAttrs.getContext());
  }

  MemorySpaceCastOpGenericAdaptorBase(MemorySpaceCastOp op);

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
class MemorySpaceCastOpGenericAdaptor : public detail::MemorySpaceCastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemorySpaceCastOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  MemorySpaceCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemorySpaceCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MemorySpaceCastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemorySpaceCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemorySpaceCastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemorySpaceCastOpGenericAdaptor(RangeT values, const MemorySpaceCastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemorySpaceCastOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemorySpaceCastOp>>>
  MemorySpaceCastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MemorySpaceCastOpAdaptor : public MemorySpaceCastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemorySpaceCastOpGenericAdaptor::MemorySpaceCastOpGenericAdaptor;
  MemorySpaceCastOpAdaptor(MemorySpaceCastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemorySpaceCastOp : public ::mlir::Op<MemorySpaceCastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::BaseMemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::CastOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemorySpaceCastOpInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultElementType, ::mlir::OpTrait::SameOperandsAndResultShape, ::mlir::ViewLikeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemorySpaceCastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemorySpaceCastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<MemorySpaceCastOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<MemorySpaceCastOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<MemorySpaceCastOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.memory_space_cast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::BaseMemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::BaseMemRefType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::Value source);
  static MemorySpaceCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::Value source);
  static MemorySpaceCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static MemorySpaceCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static MemorySpaceCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemorySpaceCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemorySpaceCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemorySpaceCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemorySpaceCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static bool areCastCompatible(::mlir::TypeRange inputs, ::mlir::TypeRange outputs);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  Value getViewSource() { return getSource(); }

  //===------------------------------------------------------------------===//
  // MemorySpaceCastConsumerOpInterface
  //===------------------------------------------------------------------===//
  /// Returns the `source` memref.
  TypedValue<PtrLikeTypeInterface> getSourcePtr();
  /// Returns the `dest` memref.
  TypedValue<PtrLikeTypeInterface> getTargetPtr();
  /// Returns whether the memory-space cast is valid. Only casts between
  /// memrefs are considered valid. Further, the `tgt` and `src` should only
  /// differ on the memory-space parameter of the memref type.
  bool isValidMemorySpaceCast(PtrLikeTypeInterface tgt,
                              PtrLikeTypeInterface src);
  /// Clones the operation using a new target type and source value.
  MemorySpaceCastOpInterface cloneMemorySpaceCastOp(
      OpBuilder &b, PtrLikeTypeInterface tgt,
      TypedValue<PtrLikeTypeInterface> src);
  /// Returns whether the `source` value can be promoted by the
  /// `MemorySpaceCastConsumerOpInterface::bubbleDownCasts` method. The only
  /// casts the op recognizes as promotable are to the generic memory-space.
  bool isSourcePromotable();
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::MemorySpaceCastOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::PrefetchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PrefetchOpGenericAdaptorBase {
public:
  struct Properties {
    using isDataCacheTy = ::mlir::BoolAttr;
    isDataCacheTy isDataCache;

    auto getIsDataCache() const {
      auto &propStorage = this->isDataCache;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setIsDataCache(const ::mlir::BoolAttr &propValue) {
      this->isDataCache = propValue;
    }
    using isWriteTy = ::mlir::BoolAttr;
    isWriteTy isWrite;

    auto getIsWrite() const {
      auto &propStorage = this->isWrite;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setIsWrite(const ::mlir::BoolAttr &propValue) {
      this->isWrite = propValue;
    }
    using localityHintTy = ::mlir::IntegerAttr;
    localityHintTy localityHint;

    auto getLocalityHint() const {
      auto &propStorage = this->localityHint;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLocalityHint(const ::mlir::IntegerAttr &propValue) {
      this->localityHint = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.isDataCache == this->isDataCache &&
        rhs.isWrite == this->isWrite &&
        rhs.localityHint == this->localityHint &&
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
  PrefetchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.prefetch", odsAttrs.getContext());
  }

  PrefetchOpGenericAdaptorBase(PrefetchOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getIsWriteAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().isWrite);
    return attr;
  }

  bool getIsWrite();
  ::mlir::IntegerAttr getLocalityHintAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().localityHint);
    return attr;
  }

  uint32_t getLocalityHint();
  ::mlir::BoolAttr getIsDataCacheAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().isDataCache);
    return attr;
  }

  bool getIsDataCache();
};

} // namespace detail
template <typename RangeT>
class PrefetchOpGenericAdaptor : public detail::PrefetchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PrefetchOpGenericAdaptorBase;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_indices = 1;
public:
  PrefetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PrefetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PrefetchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PrefetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PrefetchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PrefetchOpGenericAdaptor(RangeT values, const PrefetchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PrefetchOp, typename = std::enable_if_t<std::is_same_v<LateInst, PrefetchOp>>>
  PrefetchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getIndices() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PrefetchOpAdaptor : public PrefetchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PrefetchOpGenericAdaptor::PrefetchOpGenericAdaptor;
  PrefetchOpAdaptor(PrefetchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PrefetchOp : public ::mlir::Op<PrefetchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PrefetchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PrefetchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("isDataCache"), ::llvm::StringRef("isWrite"), ::llvm::StringRef("localityHint")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIsDataCacheAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIsDataCacheAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIsWriteAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIsWriteAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getLocalityHintAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getLocalityHintAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.prefetch");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getMemrefMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::BoolAttr getIsWriteAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().isWrite);
  }

  bool getIsWrite();
  ::mlir::IntegerAttr getLocalityHintAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().localityHint);
  }

  uint32_t getLocalityHint();
  ::mlir::BoolAttr getIsDataCacheAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().isDataCache);
  }

  bool getIsDataCache();
  void setIsWriteAttr(::mlir::BoolAttr attr) {
    getProperties().isWrite = attr;
  }

  void setIsWrite(bool attrValue);
  void setLocalityHintAttr(::mlir::IntegerAttr attr) {
    getProperties().localityHint = attr;
  }

  void setLocalityHint(uint32_t attrValue);
  void setIsDataCacheAttr(::mlir::BoolAttr attr) {
    getProperties().isDataCache = attr;
  }

  void setIsDataCache(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache);
  static PrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache);
  static PrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache);
  static PrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache);
  static PrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache);
  static PrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache);
  static PrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache);
  static PrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache);
  static PrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
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
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getMemref().getType());
  }
  static StringRef getLocalityHintAttrStrName() { return "localityHint"; }
  static StringRef getIsWriteAttrStrName() { return "isWrite"; }
  static StringRef getIsDataCacheAttrStrName() { return "isDataCache"; }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::PrefetchOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::RankOp declarations
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
      odsOpName.emplace("memref.rank", odsAttrs.getContext());
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
  static constexpr int odsIndex_memref = 0;
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

  ValueT getMemref() {
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
class RankOp : public ::mlir::Op<RankOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RankOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RankOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.rank");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::BaseMemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSOperands(0).begin());
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value memref);
  static RankOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value memref);
  static RankOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memref);
  static RankOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memref);
  static RankOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref);
  static RankOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref);
  static RankOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref);
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
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::RankOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::ReallocOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReallocOpGenericAdaptorBase {
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
  ReallocOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.realloc", odsAttrs.getContext());
  }

  ReallocOpGenericAdaptorBase(ReallocOp op);

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
class ReallocOpGenericAdaptor : public detail::ReallocOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReallocOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dynamicResultSize = 1;
public:
  ReallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReallocOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReallocOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReallocOpGenericAdaptor(RangeT values, const ReallocOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReallocOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReallocOp>>>
  ReallocOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getDynamicResultSize() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReallocOpAdaptor : public ReallocOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReallocOpGenericAdaptor::ReallocOpGenericAdaptor;
  ReallocOpAdaptor(ReallocOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReallocOp : public ::mlir::Op<ReallocOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReallocOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReallocOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_dynamicResultSize = 1;
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
    return ::llvm::StringLiteral("memref.realloc");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getDynamicResultSize() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IndexType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*operands.begin());
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDynamicResultSizeMutable();
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType resultType, Value source, Value dynamicResultSize = Value());
  static ReallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType resultType, Value source, Value dynamicResultSize = Value());
  static ReallocOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType resultType, Value source, Value dynamicResultSize = Value());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value source, /*optional*/::mlir::Value dynamicResultSize, /*optional*/::mlir::IntegerAttr alignment);
  static ReallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value source, /*optional*/::mlir::Value dynamicResultSize, /*optional*/::mlir::IntegerAttr alignment);
  static ReallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value source, /*optional*/::mlir::Value dynamicResultSize, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, /*optional*/::mlir::Value dynamicResultSize, /*optional*/::mlir::IntegerAttr alignment);
  static ReallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, /*optional*/::mlir::Value dynamicResultSize, /*optional*/::mlir::IntegerAttr alignment);
  static ReallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, /*optional*/::mlir::Value dynamicResultSize, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  /// The result of a realloc is always a memref.
  MemRefType getType() { return ::llvm::cast<MemRefType>(getResult().getType()); }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::ReallocOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::ReinterpretCastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReinterpretCastOpGenericAdaptorBase {
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
  ReinterpretCastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.reinterpret_cast", odsAttrs.getContext());
  }

  ReinterpretCastOpGenericAdaptorBase(ReinterpretCastOp op);

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
class ReinterpretCastOpGenericAdaptor : public detail::ReinterpretCastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReinterpretCastOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_offsets = 1;
  static constexpr int odsIndex_sizes = 2;
  static constexpr int odsIndex_strides = 3;
public:
  ReinterpretCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReinterpretCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReinterpretCastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReinterpretCastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ReinterpretCastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReinterpretCastOpGenericAdaptor(RangeT values, const ReinterpretCastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReinterpretCastOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReinterpretCastOp>>>
  ReinterpretCastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ReinterpretCastOpAdaptor : public ReinterpretCastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReinterpretCastOpGenericAdaptor::ReinterpretCastOpGenericAdaptor;
  ReinterpretCastOpAdaptor(ReinterpretCastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReinterpretCastOp : public ::mlir::Op<ReinterpretCastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OffsetSizeAndStrideOpInterface::Trait, ::mlir::ViewLikeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReinterpretCastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReinterpretCastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_offsets = 1;
  static constexpr int odsIndex_sizes = 2;
  static constexpr int odsIndex_strides = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ReinterpretCastOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ReinterpretCastOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ReinterpretCastOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("memref.reinterpret_cast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::BaseMemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType resultType, Value source, OpFoldResult offset, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static ReinterpretCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType resultType, Value source, OpFoldResult offset, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static ReinterpretCastOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType resultType, Value source, OpFoldResult offset, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, OpFoldResult offset, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static ReinterpretCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, OpFoldResult offset, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static ReinterpretCastOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, OpFoldResult offset, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType resultType, Value source, int64_t offset, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides, ArrayRef<NamedAttribute> attrs = {});
  static ReinterpretCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType resultType, Value source, int64_t offset, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides, ArrayRef<NamedAttribute> attrs = {});
  static ReinterpretCastOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType resultType, Value source, int64_t offset, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType resultType, Value source, Value offset, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static ReinterpretCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType resultType, Value source, Value offset, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static ReinterpretCastOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType resultType, Value source, Value offset, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ReinterpretCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ReinterpretCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ReinterpretCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static ReinterpretCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ReinterpretCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ReinterpretCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ReinterpretCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static ReinterpretCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReinterpretCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReinterpretCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReinterpretCastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReinterpretCastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
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
  /// Returns the dynamic sizes for this subview operation if specified.
  ::mlir::Operation::operand_range getDynamicSizes() { return getSizes(); }

  /// Return the list of Range (i.e. offset, size, stride). Each
  /// Range entry contains either the dynamic value or a ConstantIndexOp
  /// constructed with `b` at location `loc`.
  ::mlir::SmallVector<::mlir::Range, 8> getOrCreateRanges(
      ::mlir::OpBuilder &b, ::mlir::Location loc) {
    return ::mlir::getOrCreateRanges(*this, b, loc);
  }

  // The result of the op is always a ranked memref.
  MemRefType getType() { return getResult().getType(); }
  Value getViewSource() { return getSource(); }

  /// Return the rank of the result type.
  unsigned getResultRank() { return getType().getRank(); }

  /// Return the expected rank of each of the`static_offsets`, `static_sizes`
  /// and `static_strides` attributes.
  std::array<unsigned, 3> getArrayAttrMaxRanks() {
    unsigned resultRank = getType().getRank();
    return {1, resultRank, resultRank};
  }

  /// Return the number of leading operands before the `offsets`, `sizes` and
  /// and `strides` operands.
  static unsigned getOffsetSizeAndStrideStartOperandIndex() { return 1; }

  /// Return a vector of all the static or dynamic sizes of the op, while
  /// statically inferring the sizes of the dynamic sizes, when possible.
  /// This is best effort.
  /// E.g., if `getMixedSizes` returns `[2, %dyn_size]`, but the resulting
  /// memref type is `memref<2x8xi16>`, this method will return `[2, 8]`.
  /// Similarly if the resulting memref type is `memref<2x?xi16>`, but
  /// `%dyn_size` can statically be pinned to a constant value, this
  /// constant value is returned instead of `%dyn_size`.
  SmallVector<OpFoldResult> getConstifiedMixedSizes();
  /// Similar to `getConstifiedMixedSizes` but for strides.
  SmallVector<OpFoldResult> getConstifiedMixedStrides();
  /// Similar to `getConstifiedMixedSizes` but for the offset.
  OpFoldResult getConstifiedMixedOffset();
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::ReinterpretCastOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::ReshapeOp declarations
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
      odsOpName.emplace("memref.reshape", odsAttrs.getContext());
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
class ReshapeOp : public ::mlir::Op<ReshapeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::BaseMemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ViewLikeOpInterface::Trait> {
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
    return ::llvm::StringLiteral("memref.reshape");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::BaseMemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getShape() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
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

  ::mlir::TypedValue<::mlir::BaseMemRefType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::BaseMemRefType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType resultType, Value operand, Value shape);
  static ReshapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType resultType, Value operand, Value shape);
  static ReshapeOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType resultType, Value operand, Value shape);
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
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  MemRefType getType() { return ::llvm::cast<MemRefType>(getResult().getType()); }
  Value getViewSource() { return getSource(); }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::ReshapeOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::StoreOp declarations
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
      odsOpName.emplace("memref.store", odsAttrs.getContext());
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
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_memref = 1;
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

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMemref() {
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
class StoreOp : public ::mlir::Op<StoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::AlignmentAttrOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::PromotableMemOpInterface::Trait, ::mlir::DestructurableAccessorOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_memref = 1;
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
    return ::llvm::StringLiteral("memref.store");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMemrefMutable() {
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value memref, ValueRange indices, bool nontemporal = false, llvm::MaybeAlign alignment = llvm::MaybeAlign());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value memref);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value memref);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value memref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/::mlir::BoolAttr nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange indices, /*optional*/bool nontemporal, /*optional*/::mlir::IntegerAttr alignment);
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
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  bool loadsFrom(const ::mlir::MemorySlot &slot);
  bool storesTo(const ::mlir::MemorySlot &slot);
  ::mlir::Value getStored(const ::mlir::MemorySlot &slot, ::mlir::OpBuilder &builder, ::mlir::Value reachingDef, const ::mlir::DataLayout &dataLayout);
  bool canUsesBeRemoved(const ::mlir::MemorySlot &slot, const ::llvm::SmallPtrSetImpl<::mlir::OpOperand *> &blockingUses, ::llvm::SmallVectorImpl<::mlir::OpOperand *> &newBlockingUses, const ::mlir::DataLayout &datalayout);
  ::mlir::DeletionKind removeBlockingUses(const ::mlir::MemorySlot &slot, const ::llvm::SmallPtrSetImpl<mlir::OpOperand *> &blockingUses, ::mlir::OpBuilder &builder, ::mlir::Value reachingDefinition, const ::mlir::DataLayout &dataLayout);
  bool canRewire(const ::mlir::DestructurableMemorySlot &slot, ::llvm::SmallPtrSetImpl<::mlir::Attribute> &usedIndices, ::mlir::SmallVectorImpl<::mlir::MemorySlot> &mustBeSafelyUsed, const ::mlir::DataLayout &dataLayout);
  ::mlir::DeletionKind rewire(const ::mlir::DestructurableMemorySlot &slot, ::llvm::DenseMap<::mlir::Attribute, ::mlir::MemorySlot> &subslots, ::mlir::OpBuilder &builder, const ::mlir::DataLayout &dataLayout);
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
  Value getValueToStore() { return getOperand(0); }

  Value getMemRef() { return getOperand(1); }
  void setMemRef(Value value) { setOperand(1, value); }
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getMemRef().getType());
  }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::StoreOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::TransposeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TransposeOpGenericAdaptorBase {
public:
  struct Properties {
    using permutationTy = ::mlir::AffineMapAttr;
    permutationTy permutation;

    auto getPermutation() const {
      auto &propStorage = this->permutation;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setPermutation(const ::mlir::AffineMapAttr &propValue) {
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
      odsOpName.emplace("memref.transpose", odsAttrs.getContext());
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

  ::mlir::AffineMapAttr getPermutationAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().permutation);
    return attr;
  }

  ::mlir::AffineMap getPermutation();
};

} // namespace detail
template <typename RangeT>
class TransposeOpGenericAdaptor : public detail::TransposeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TransposeOpGenericAdaptorBase;
  static constexpr int odsIndex_in = 0;
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

  ValueT getIn() {
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
class TransposeOp : public ::mlir::Op<TransposeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TransposeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TransposeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_in = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<TransposeOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<TransposeOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<TransposeOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("memref.transpose");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInMutable() {
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
  ::mlir::AffineMapAttr getPermutationAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().permutation);
  }

  ::mlir::AffineMap getPermutation();
  void setPermutationAttr(::mlir::AffineMapAttr attr) {
    getProperties().permutation = attr;
  }

  void setPermutation(::mlir::AffineMap attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value in, AffineMapAttr permutation, ArrayRef<NamedAttribute> attrs = {});
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value in, AffineMapAttr permutation, ArrayRef<NamedAttribute> attrs = {});
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, Value in, AffineMapAttr permutation, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value in, ::mlir::AffineMapAttr permutation);
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value in, ::mlir::AffineMapAttr permutation);
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value in, ::mlir::AffineMapAttr permutation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::AffineMapAttr permutation);
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::AffineMapAttr permutation);
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::AffineMapAttr permutation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value in, ::mlir::AffineMap permutation);
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value in, ::mlir::AffineMap permutation);
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value in, ::mlir::AffineMap permutation);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::AffineMap permutation);
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::AffineMap permutation);
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value in, ::mlir::AffineMap permutation);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TransposeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TransposeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
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
  static StringRef getPermutationAttrStrName() { return "permutation"; }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::TransposeOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::ViewOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ViewOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ViewOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.view", odsAttrs.getContext());
  }

  ViewOpGenericAdaptorBase(ViewOp op);

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
class ViewOpGenericAdaptor : public detail::ViewOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ViewOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_byte_shift = 1;
  static constexpr int odsIndex_sizes = 2;
public:
  ViewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ViewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ViewOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ViewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ViewOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ViewOpGenericAdaptor(RangeT values, const ViewOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ViewOp, typename = std::enable_if_t<std::is_same_v<LateInst, ViewOp>>>
  ViewOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getByteShift() {
    return (*getODSOperands(1).begin());
  }

  RangeT getSizes() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ViewOpAdaptor : public ViewOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ViewOpGenericAdaptor::ViewOpGenericAdaptor;
  ViewOpAdaptor(ViewOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ViewOp : public ::mlir::Op<ViewOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::ViewLikeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ViewOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ViewOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_byte_shift = 1;
  static constexpr int odsIndex_sizes = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ViewOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ViewOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ViewOp>::getDefaultDialect;
  using ::mlir::ViewLikeOpInterface::Trait<ViewOp>::getViewDest;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("memref.view");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getByteShift() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getSizes() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getSourceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getByteShiftMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getSizesMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value source, ::mlir::Value byte_shift, ::mlir::ValueRange sizes);
  static ViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value source, ::mlir::Value byte_shift, ::mlir::ValueRange sizes);
  static ViewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value source, ::mlir::Value byte_shift, ::mlir::ValueRange sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value byte_shift, ::mlir::ValueRange sizes);
  static ViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value byte_shift, ::mlir::ValueRange sizes);
  static ViewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value byte_shift, ::mlir::ValueRange sizes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ViewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ViewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  ::mlir::Value getViewSource();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// The result of a view is always a memref.
  MemRefType getType() { return ::llvm::cast<MemRefType>(getResult().getType()); }

  // Return both static and dynamic sizes as a list of `OpFoldResult`.
  SmallVector<OpFoldResult> getMixedSizes();

  /// Returns the dynamic sizes for this view operation. This is redundant
  /// with `sizes` but needed in template implementations. More specifically:
  /// ```
  /// template <typename AnyMemRefDefOp>
  /// bool isMemRefSizeValidSymbol(AnyMemRefDefOp memrefDefOp, unsigned index,
  ///                              Region *region)
  /// ```
  operand_range getDynamicSizes() {
    return {getSizes().begin(), getSizes().end()};
  }
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::ViewOp)

namespace mlir::memref {


//===----------------------------------------------------------------------===//
// ::mlir::memref::SubViewOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubViewOpGenericAdaptorBase {
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
  SubViewOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("memref.subview", odsAttrs.getContext());
  }

  SubViewOpGenericAdaptorBase(SubViewOp op);

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
class SubViewOpGenericAdaptor : public detail::SubViewOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubViewOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_offsets = 1;
  static constexpr int odsIndex_sizes = 2;
  static constexpr int odsIndex_strides = 3;
public:
  SubViewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubViewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubViewOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubViewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : SubViewOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubViewOpGenericAdaptor(RangeT values, const SubViewOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubViewOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubViewOp>>>
  SubViewOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SubViewOpAdaptor : public SubViewOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubViewOpGenericAdaptor::SubViewOpGenericAdaptor;
  SubViewOpAdaptor(SubViewOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubViewOp : public ::mlir::Op<SubViewOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferStridedMetadataOpInterface::Trait, ::mlir::MemorySpaceCastConsumerOpInterface::Trait, ::mlir::ViewLikeOpInterface::Trait, ::mlir::OffsetSizeAndStrideOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubViewOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubViewOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_offsets = 1;
  static constexpr int odsIndex_sizes = 2;
  static constexpr int odsIndex_strides = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<SubViewOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SubViewOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SubViewOp>::getDefaultDialect;
  using ::mlir::ViewLikeOpInterface::Trait<SubViewOp>::getViewDest;
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
    return ::llvm::StringLiteral("memref.subview");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
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
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType resultType, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType resultType, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType resultType, Value source, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, ArrayRef<int64_t> offsets, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, ArrayRef<int64_t> offsets, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, ArrayRef<int64_t> offsets, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType resultType, Value source, ArrayRef<int64_t> offsets, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType resultType, Value source, ArrayRef<int64_t> offsets, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType resultType, Value source, ArrayRef<int64_t> offsets, ArrayRef<int64_t> sizes, ArrayRef<int64_t> strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, MemRefType resultType, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, MemRefType resultType, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, MemRefType resultType, Value source, ValueRange offsets, ValueRange sizes, ValueRange strides, ArrayRef<NamedAttribute> attrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::mlir::DenseI64ArrayAttr static_offsets, ::mlir::DenseI64ArrayAttr static_sizes, ::mlir::DenseI64ArrayAttr static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::ValueRange offsets, ::mlir::ValueRange sizes, ::mlir::ValueRange strides, ::llvm::ArrayRef<int64_t> static_offsets, ::llvm::ArrayRef<int64_t> static_sizes, ::llvm::ArrayRef<int64_t> static_strides);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubViewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubViewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  void inferStridedMetadataRanges(::llvm::ArrayRef<::mlir::StridedMetadataRange> operands, ::mlir::GetIntRangeFn getIntRange, ::mlir::SetStridedMetadataRangeFn setMetadata, int32_t indexBitwidth);
  ::llvm::FailureOr<std::optional<::llvm::SmallVector<::mlir::Value>>> bubbleDownCasts(::mlir::OpBuilder &builder);
  ::mlir::Value getViewSource();
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
  /// Returns the dynamic sizes for this subview operation if specified.
  ::mlir::Operation::operand_range getDynamicSizes() { return getSizes(); }

  /// Return the list of Range (i.e. offset, size, stride). Each
  /// Range entry contains either the dynamic value or a ConstantIndexOp
  /// constructed with `b` at location `loc`.
  ::mlir::SmallVector<::mlir::Range, 8> getOrCreateRanges(
      ::mlir::OpBuilder &b, ::mlir::Location loc) {
    return ::mlir::getOrCreateRanges(*this, b, loc);
  }

  /// Returns the type of the base memref operand.
  MemRefType getSourceType() {
    return ::llvm::cast<MemRefType>(getSource().getType());
  }

  /// The result of a subview is always a memref.
  MemRefType getType() { return ::llvm::cast<MemRefType>(getResult().getType()); }

  /// A subview result type can be fully inferred from the source type and the
  /// static representation of offsets, sizes and strides. Special sentinels
  /// encode the dynamic case.
  static MemRefType inferResultType(MemRefType sourceMemRefType,
                                    ArrayRef<int64_t> staticOffsets,
                                    ArrayRef<int64_t> staticSizes,
                                    ArrayRef<int64_t> staticStrides);
  static MemRefType inferResultType(MemRefType sourceMemRefType,
                                    ArrayRef<OpFoldResult> staticOffsets,
                                    ArrayRef<OpFoldResult> staticSizes,
                                    ArrayRef<OpFoldResult> staticStrides);

  /// A rank-reducing result type can be inferred from the desired result
  /// shape. Only the layout map is inferred.
  ///
  /// Note: The result shape cannot be inferred with just the result rank and
  /// and the desired sizes. In case there are more "ones" among the sizes
  /// than the difference in source/result rank, it is not clear which dims of
  /// size one should be dropped.
  static MemRefType inferRankReducedResultType(
      ArrayRef<int64_t> resultShape, MemRefType sourceMemRefType,
      ArrayRef<int64_t> staticOffsets,
      ArrayRef<int64_t> staticSizes,
      ArrayRef<int64_t> staticStrides);
  static MemRefType inferRankReducedResultType(
      ArrayRef<int64_t> resultShape, MemRefType sourceMemRefType,
      ArrayRef<OpFoldResult> staticOffsets,
      ArrayRef<OpFoldResult> staticSizes,
      ArrayRef<OpFoldResult> staticStrides);

  /// Return the expected rank of each of the`static_offsets`, `static_sizes`
  /// and `static_strides` attributes.
  std::array<unsigned, 3> getArrayAttrMaxRanks() {
    unsigned rank = getSourceType().getRank();
    return {rank, rank, rank};
  }

  /// Return the number of leading operands before the `offsets`, `sizes` and
  /// and `strides` operands.
  static unsigned getOffsetSizeAndStrideStartOperandIndex() { return 1; }

  /// Return the dimensions of the source type that are dropped when
  /// the result is rank-reduced.
  llvm::SmallBitVector getDroppedDims();

  /// Given a `value`, asserted to be of MemRefType, build a SubViewOp that
  /// results in a rank reduction to the desired memref shape and return the
  /// new value created.
  /// If the shape of `value` is already the `desiredShape`, just return
  /// `value`.
  /// If the shape of `value` cannot be rank-reduced to `desiredShape`, fail.
  static FailureOr<Value> rankReduceIfNeeded(
    OpBuilder &b, Location loc, Value value, ArrayRef<int64_t> desiredShape);
};

} // namespace mlir::memref
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::memref::SubViewOp)


#endif // GET_OP_CLASSES

