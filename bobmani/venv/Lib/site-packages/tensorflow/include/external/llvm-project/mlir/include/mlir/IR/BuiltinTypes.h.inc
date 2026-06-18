/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace mlir {

/// Complex number with a parameterized element type
/// Syntax:
/// 
///     ```
///     complex-type ::= `complex` `<` type `>`
///     ```
/// 
///     The value of `complex` type represents a complex number with a parameterized
///     element type, which is composed of a real and imaginary value of that
///     element type. The element must be a floating point or integer scalar type.
/// 
///     #### Example:
/// 
///     ```mlir
///     complex<f32>
///     complex<i32>
///     ```
class ComplexType;
/// 8-bit floating point with 2 bit mantissa
/// An 8-bit floating point type with 1 sign bit, 5 bits exponent and 2 bits
///     mantissa. This is not a standard type as defined by IEEE-754, but it
///     follows similar conventions with the following characteristics:
/// 
///       * bit encoding: S1E5M2
///       * exponent bias: 15
///       * infinities: supported with exponent set to all 1s and mantissa 0s
///       * NaNs: supported with exponent bits set to all 1s and mantissa of
///         (01, 10, or 11)
///       * denormals when exponent is 0
/// 
///     Described in: https://arxiv.org/abs/2209.05433
class Float8E5M2Type;
/// 8-bit floating point with 3 bit mantissa
/// An 8-bit floating point type with 1 sign bit, 4 bits exponent and 3 bits
///     mantissa. This is not a standard type as defined by IEEE-754, but it
///     follows similar conventions with the following characteristics:
/// 
///       * bit encoding: S1E4M3
///       * exponent bias: 7
///       * infinities: supported with exponent set to all 1s and mantissa 0s
///       * NaNs: supported with exponent bits set to all 1s and mantissa of
///         (001, 010, 011, 100, 101, 110, 111)
///       * denormals when exponent is 0
class Float8E4M3Type;
/// 8-bit floating point with 3 bit mantissa
/// An 8-bit floating point type with 1 sign bit, 4 bits exponent and 3 bits
///     mantissa. This is not a standard type as defined by IEEE-754, but it follows
///     similar conventions, with the exception that there are no infinity values
///     and only two NaN representations. This type has the following
///     characteristics:
/// 
///       * bit encoding: S1E4M3
///       * exponent bias: 7
///       * infinities: Not supported
///       * NaNs: supported with exponent bits and mantissa bits set to all 1s
///       * denormals when exponent is 0
/// 
///     Described in: https://arxiv.org/abs/2209.05433
class Float8E4M3FNType;
/// 8-bit floating point with 2 bit mantissa
/// An 8-bit floating point type with 1 sign bit, 5 bits exponent and 2 bits
///     mantissa. This is not a standard type as defined by IEEE-754, but it follows
///     similar conventions, with the exception that there are no infinity values,
///     no negative zero, and only one NaN representation. This type has the
///     following characteristics:
/// 
///       * bit encoding: S1E5M2
///       * exponent bias: 16
///       * infinities: Not supported
///       * NaNs: Supported with sign bit set to 1, exponent bits and mantissa bits set to all 0s
///       * denormals when exponent is 0
/// 
///     Described in: https://arxiv.org/abs/2206.02915
class Float8E5M2FNUZType;
/// 8-bit floating point with 3 bit mantissa
/// An 8-bit floating point type with 1 sign bit, 4 bits exponent and 3 bits
///     mantissa. This is not a standard type as defined by IEEE-754, but it follows
///     similar conventions, with the exception that there are no infinity values,
///     no negative zero, and only one NaN representation. This type has the
///     following characteristics:
/// 
///       * bit encoding: S1E4M3
///       * exponent bias: 8
///       * infinities: Not supported
///       * NaNs: Supported with sign bit set to 1, exponent bits and mantissa bits set to all 0s
///       * denormals when exponent is 0
/// 
///     Described in: https://arxiv.org/abs/2209.05433
class Float8E4M3FNUZType;
/// 8-bit floating point with 3 bit mantissa
/// An 8-bit floating point type with 1 sign bit, 4 bits exponent and 3 bits
///     mantissa. This is not a standard type as defined by IEEE-754, but it follows
///     similar conventions, with the exception that there are no infinity values,
///     no negative zero, and only one NaN representation. This type has the
///     following characteristics:
/// 
///       * bit encoding: S1E4M3
///       * exponent bias: 11
///       * infinities: Not supported
///       * NaNs: Supported with sign bit set to 1, exponent bits and mantissa bits set to all 0s
///       * denormals when exponent is 0
/// 
///     Related to: https://dl.acm.org/doi/10.5555/3454287.3454728
class Float8E4M3B11FNUZType;
/// 8-bit floating point with 3 bits exponent and 4 bit mantissa
/// An 8-bit floating point type with 1 sign bit, 3 bits exponent and 4 bits
///     mantissa. This is not a standard type as defined by IEEE-754, but it
///     follows similar conventions with the following characteristics:
/// 
///       * bit encoding: S1E3M4
///       * exponent bias: 3
///       * infinities: supported with exponent set to all 1s and mantissa 0s
///       * NaNs: supported with exponent bits set to all 1s and mantissa values of
///         {0,1}⁴ except S.111.0000
///       * denormals when exponent is 0
class Float8E3M4Type;
/// 4-bit floating point with 2-bit exponent and 1-bit mantissa
/// An 4-bit floating point type with 1 sign bit, 2 bits exponent and 1 bit
///     mantissa. This is not a standard type as defined by IEEE-754, but it
///     follows similar conventions with the following characteristics:
/// 
///       * bit encoding: S1E2M1
///       * exponent bias: 1
///       * infinities: Not supported
///       * NaNs: Not supported
///       * denormals when exponent is 0
/// 
///     Open Compute Project (OCP) microscaling formats (MX) specification:
///     https://www.opencompute.org/documents/ocp-microscaling-formats-mx-v1-0-spec-final-pdf
class Float4E2M1FNType;
/// 6-bit floating point with 2-bit exponent and 3-bit mantissa
/// An 6-bit floating point type with 1 sign bit, 2 bits exponent and 3 bits
///     mantissa. This is not a standard type as defined by IEEE-754, but it
///     follows similar conventions with the following characteristics:
/// 
///       * bit encoding: S1E2M3
///       * exponent bias: 1
///       * infinities: Not supported
///       * NaNs: Not supported
///       * denormals when exponent is 0
/// 
///     Open Compute Project (OCP) microscaling formats (MX) specification:
///     https://www.opencompute.org/documents/ocp-microscaling-formats-mx-v1-0-spec-final-pdf
class Float6E2M3FNType;
/// 6-bit floating point with 3-bit exponent and 2-bit mantissa
/// An 6-bit floating point type with 1 sign bit, 3 bits exponent and 2 bits
///     mantissa. This is not a standard type as defined by IEEE-754, but it
///     follows similar conventions with the following characteristics:
/// 
///       * bit encoding: S1E3M2
///       * exponent bias: 3
///       * infinities: Not supported
///       * NaNs: Not supported
///       * denormals when exponent is 0
/// 
///     Open Compute Project (OCP) microscaling formats (MX) specification:
///     https://www.opencompute.org/documents/ocp-microscaling-formats-mx-v1-0-spec-final-pdf
class Float6E3M2FNType;
/// 8-bit floating point with 8-bit exponent, no mantissa or sign
/// An 8-bit floating point type with no sign bit, 8 bits exponent and no
///     mantissa. This is not a standard type as defined by IEEE-754; it is intended
///     to be used for representing scaling factors, so it cannot represent zeros
///     and negative numbers. The values it can represent are powers of two in the
///     range [-127,127] and NaN.
/// 
///       * bit encoding: S0E8M0
///       * exponent bias: 127
///       * infinities: Not supported
///       * NaNs: Supported with all bits set to 1
///       * denormals: Not supported
/// 
///     Open Compute Project (OCP) microscaling formats (MX) specification:
///     https://www.opencompute.org/documents/ocp-microscaling-formats-mx-v1-0-spec-final-pdf
class Float8E8M0FNUType;
/// bfloat16 floating-point type
class BFloat16Type;
/// 16-bit floating-point type
class Float16Type;
/// TF32 floating-point type
class FloatTF32Type;
/// 32-bit floating-point type
class Float32Type;
/// 64-bit floating-point type
class Float64Type;
/// 80-bit floating-point type
class Float80Type;
/// 128-bit floating-point type
class Float128Type;
/// Map from a list of inputs to a list of results
/// Syntax:
/// 
///     ```
///     // Function types may have multiple results.
///     function-result-type ::= type-list-parens | non-function-type
///     function-type ::= type-list-parens `->` function-result-type
///     ```
/// 
///     The function type can be thought of as a function signature. It consists of
///     a list of formal parameter types and a list of formal result types.
/// 
///     #### Example:
/// 
///     ```mlir
///     func.func @add_one(%arg0 : i64) -> i64 {
///       %c1 = arith.constant 1 : i64
///       %0 = arith.addi %arg0, %c1 : i64
///       return %0 : i64
///     }
///     ```
class FunctionType;
/// Map from a list of inputs to a list of results
/// Syntax:
/// 
///     ```
///     // Function types may have multiple results.
///     function-result-type ::= type-list-parens | non-function-type
///     function-type ::= type-list-parens `->` function-result-type
///     ```
/// 
///     The function type can be thought of as a function signature. It consists of
///     a list of formal parameter types and a list of formal result types.
/// 
///     #### Example:
/// 
///     ```mlir
///     func.func @add_one(%arg0 : i64) -> i64 {
///       %c1 = arith.constant 1 : i64
///       %0 = arith.addi %arg0, %c1 : i64
///       return %0 : i64
///     }
///     ```
class GraphType;
/// Integer-like type with unknown platform-dependent bit width
/// Syntax:
/// 
///     ```
///     // Target word-sized integer.
///     index-type ::= `index`
///     ```
/// 
///     The index type is a signless integer whose size is equal to the natural
///     machine word of the target ( [rationale](../../Rationale/Rationale/#integer-signedness-semantics) )
///     and is used by the affine constructs in MLIR.
/// 
///     **Rationale:** integers of platform-specific bit widths are practical to
///     express sizes, dimensionalities and subscripts.
class IndexType;
/// Integer type with arbitrary precision up to a fixed limit
/// Syntax:
/// 
///     ```
///     // Sized integers like i1, i4, i8, i16, i32.
///     signed-integer-type ::= `si` [1-9][0-9]*
///     unsigned-integer-type ::= `ui` [1-9][0-9]*
///     signless-integer-type ::= `i` [1-9][0-9]*
///     integer-type ::= signed-integer-type |
///                      unsigned-integer-type |
///                      signless-integer-type
///     ```
/// 
///     Integer types have a designated bit width and may optionally have signedness
///     semantics.
/// 
///     **Rationale:** low precision integers (like `i2`, `i4` etc) are useful for
///     low-precision inference chips, and arbitrary precision integers are useful
///     for hardware synthesis (where a 13 bit multiplier is a lot cheaper/smaller
///     than a 16 bit one).
class IntegerType;
/// Shaped reference to a region of memory
/// Syntax:
/// 
///     ```
///     layout-specification ::= attribute-value
///     memory-space ::= attribute-value
///     memref-type ::= `memref` `<` dimension-list-ranked type
///                     (`,` layout-specification)? (`,` memory-space)? `>`
///     ```
/// 
///     A `memref` type is a reference to a region of memory (similar to a buffer
///     pointer, but more powerful). The buffer pointed to by a memref can be
///     allocated, aliased and deallocated. A memref can be used to read and write
///     data from/to the memory region which it references. Memref types use the
///     same shape specifier as tensor types. Note that `memref<f32>`,
///     `memref<0 x f32>`, `memref<1 x 0 x f32>`, and `memref<0 x 1 x f32>` are all
///     different types.
/// 
///     A `memref` is allowed to have an unknown rank (e.g. `memref<*xf32>`). The
///     purpose of unranked memrefs is to allow external library functions to
///     receive memref arguments of any rank without versioning the functions based
///     on the rank. Other uses of this type are disallowed or will have undefined
///     behavior.
/// 
///     Are accepted as elements:
/// 
///     - built-in integer types;
///     - built-in index type;
///     - built-in floating point types;
///     - built-in vector types with elements of the above types;
///     - another memref type;
///     - any other type implementing `MemRefElementTypeInterface`.
/// 
///     ##### Layout
/// 
///     A memref may optionally have a layout that indicates how indices are
///     transformed from the multi-dimensional form into a linear address. The
///     layout must avoid internal aliasing, i.e., two distinct tuples of
///     _in-bounds_ indices must be pointing to different elements in memory. The
///     layout is an attribute that implements `MemRefLayoutAttrInterface`. The
///     bulitin dialect offers two kinds of layouts: strided and affine map, each
///     of which is available as an attribute. Other attributes may be used to
///     represent the layout as long as they can be converted to a
///     [semi-affine map](Affine.md/#semi-affine-maps) and implement the required
///     interface. Users of memref are expected to fallback to the affine
///     representation when handling unknown memref layouts. Multi-dimensional
///     affine forms are interpreted in _row-major_ fashion.
/// 
///     In absence of an explicit layout, a memref is considered to have a
///     multi-dimensional identity affine map layout.  Identity layout maps do not
///     contribute to the MemRef type identification and are discarded on
///     construction. That is, a type with an explicit identity map is
///     `memref<?x?xf32, (i,j)->(i,j)>` is strictly the same as the one without a
///     layout, `memref<?x?xf32>`.
/// 
///     ##### Affine Map Layout
/// 
///     The layout may be represented directly as an affine map from the index space
///     to the storage space. For example, the following figure shows an index map
///     which maps a 2-dimensional index from a 2x2 index space to a 3x3 index
///     space, using symbols `S0` and `S1` as offsets.
/// 
///     ![Index Map Example](/includes/img/index-map.svg)
/// 
///     Semi-affine maps are sufficiently flexible to represent a wide variety of
///     dense storage layouts, including row- and column-major and tiled:
/// 
///     ```mlir
///     // MxN matrix stored in row major layout in memory:
///     #layout_map_row_major = (i, j) -> (i, j)
/// 
///     // MxN matrix stored in column major layout in memory:
///     #layout_map_col_major = (i, j) -> (j, i)
/// 
///     // MxN matrix stored in a 2-d blocked/tiled layout with 64x64 tiles.
///     #layout_tiled = (i, j) -> (i floordiv 64, j floordiv 64, i mod 64, j mod 64)
///     ```
/// 
///     ##### Strided Layout
/// 
///     Memref layout can be expressed using strides to encode the distance, in
///     number of elements, in (linear) memory between successive entries along a
///     particular dimension. For example, a row-major strided layout for
///     `memref<2x3x4xf32>` is `strided<[12, 4, 1]>`, where the last dimension is
///     contiguous as indicated by the unit stride and the remaining strides are
///     products of the sizes of faster-variying dimensions. Strided layout can also
///     express non-contiguity, e.g., `memref<2x3, strided<[6, 2]>>` only accesses
///     even elements of the dense consecutive storage along the innermost
///     dimension.
/// 
///     The strided layout supports an optional _offset_ that indicates the
///     distance, in the number of elements, between the beginning of the memref
///     and the first accessed element. When omitted, the offset is considered to
///     be zero. That is, `memref<2, strided<[2], offset: 0>>` and
///     `memref<2, strided<[2]>>` are strictly the same type.
/// 
///     Both offsets and strides may be _dynamic_, that is, unknown at compile time.
///     This is represented by using a question mark (`?`) instead of the value in
///     the textual form of the IR.
/// 
///     The strided layout converts into the following canonical one-dimensional
///     affine form through explicit linearization:
/// 
///     ```mlir
///     affine_map<(d0, ... dN)[offset, stride0, ... strideN] ->
///                 (offset + d0 * stride0 + ... dN * strideN)>
///     ```
/// 
///     Therefore, it is never subject to the implicit row-major layout
///     interpretation.
/// 
///     ##### Codegen of Unranked Memref
/// 
///     Using unranked memref in codegen besides the case mentioned above is highly
///     discouraged. Codegen is concerned with generating loop nests and specialized
///     instructions for high-performance, unranked memref is concerned with hiding
///     the rank and thus, the number of enclosing loops required to iterate over
///     the data. However, if there is a need to code-gen unranked memref, one
///     possible path is to cast into a static ranked type based on the dynamic
///     rank. Another possible path is to emit a single while loop conditioned on a
///     linear index and perform delinearization of the linear index to a dynamic
///     array containing the (unranked) indices. While this is possible, it is
///     expected to not be a good idea to perform this during codegen as the cost
///     of the translations is expected to be prohibitive and optimizations at this
///     level are not expected to be worthwhile. If expressiveness is the main
///     concern, irrespective of performance, passing unranked memrefs to an
///     external C++ library and implementing rank-agnostic logic there is expected
///     to be significantly simpler.
/// 
///     Unranked memrefs may provide expressiveness gains in the future and help
///     bridge the gap with unranked tensors. Unranked memrefs will not be expected
///     to be exposed to codegen but one may query the rank of an unranked memref
///     (a special op will be needed for this purpose) and perform a switch and cast
///     to a ranked memref as a prerequisite to codegen.
/// 
///     Example:
/// 
///     ```mlir
///     // With static ranks, we need a function for each possible argument type
///     %A = alloc() : memref<16x32xf32>
///     %B = alloc() : memref<16x32x64xf32>
///     call @helper_2D(%A) : (memref<16x32xf32>)->()
///     call @helper_3D(%B) : (memref<16x32x64xf32>)->()
/// 
///     // With unknown rank, the functions can be unified under one unranked type
///     %A = alloc() : memref<16x32xf32>
///     %B = alloc() : memref<16x32x64xf32>
///     // Remove rank info
///     %A_u = memref_cast %A : memref<16x32xf32> -> memref<*xf32>
///     %B_u = memref_cast %B : memref<16x32x64xf32> -> memref<*xf32>
///     // call same function with dynamic ranks
///     call @helper(%A_u) : (memref<*xf32>)->()
///     call @helper(%B_u) : (memref<*xf32>)->()
///     ```
/// 
///     The core syntax and representation of a layout specification is a
///     [semi-affine map](Affine.md/#semi-affine-maps). Additionally,
///     syntactic sugar is supported to make certain layout specifications more
///     intuitive to read. For the moment, a `memref` supports parsing a strided
///     form which is converted to a semi-affine map automatically.
/// 
///     The memory space of a memref is specified by a target-specific attribute.
///     It might be an integer value, string, dictionary or custom dialect attribute.
///     The empty memory space (attribute is None) is target specific.
/// 
///     The notionally dynamic value of a memref value includes the address of the
///     buffer allocated, as well as the symbols referred to by the shape, layout
///     map, and index maps.
/// 
///     Examples of memref static type
/// 
///     ```mlir
///     // Identity index/layout map
///     #identity = affine_map<(d0, d1) -> (d0, d1)>
/// 
///     // Column major layout.
///     #col_major = affine_map<(d0, d1, d2) -> (d2, d1, d0)>
/// 
///     // A 2-d tiled layout with tiles of size 128 x 256.
///     #tiled_2d_128x256 = affine_map<(d0, d1) -> (d0 div 128, d1 div 256, d0 mod 128, d1 mod 256)>
/// 
///     // A tiled data layout with non-constant tile sizes.
///     #tiled_dynamic = affine_map<(d0, d1)[s0, s1] -> (d0 floordiv s0, d1 floordiv s1,
///                                  d0 mod s0, d1 mod s1)>
/// 
///     // A layout that yields a padding on two at either end of the minor dimension.
///     #padded = affine_map<(d0, d1) -> (d0, (d1 + 2) floordiv 2, (d1 + 2) mod 2)>
/// 
/// 
///     // The dimension list "16x32" defines the following 2D index space:
///     //
///     //   { (i, j) : 0 <= i < 16, 0 <= j < 32 }
///     //
///     memref<16x32xf32, #identity>
/// 
///     // The dimension list "16x4x?" defines the following 3D index space:
///     //
///     //   { (i, j, k) : 0 <= i < 16, 0 <= j < 4, 0 <= k < N }
///     //
///     // where N is a symbol which represents the runtime value of the size of
///     // the third dimension.
///     //
///     // %N here binds to the size of the third dimension.
///     %A = alloc(%N) : memref<16x4x?xf32, #col_major>
/// 
///     // A 2-d dynamic shaped memref that also has a dynamically sized tiled
///     // layout. The memref index space is of size %M x %N, while %B1 and %B2
///     // bind to the symbols s0, s1 respectively of the layout map #tiled_dynamic.
///     // Data tiles of size %B1 x %B2 in the logical space will be stored
///     // contiguously in memory. The allocation size will be
///     // (%M ceildiv %B1) * %B1 * (%N ceildiv %B2) * %B2 f32 elements.
///     %T = alloc(%M, %N) [%B1, %B2] : memref<?x?xf32, #tiled_dynamic>
/// 
///     // A memref that has a two-element padding at either end. The allocation
///     // size will fit 16 * 64 float elements of data.
///     %P = alloc() : memref<16x64xf32, #padded>
/// 
///     // Affine map with symbol 's0' used as offset for the first dimension.
///     #imapS = affine_map<(d0, d1) [s0] -> (d0 + s0, d1)>
///     // Allocate memref and bind the following symbols:
///     // '%n' is bound to the dynamic second dimension of the memref type.
///     // '%o' is bound to the symbol 's0' in the affine map of the memref type.
///     %n = ...
///     %o = ...
///     %A = alloc (%n)[%o] : <16x?xf32, #imapS>
///     ```
class MemRefType;
/// A unit type
/// Syntax:
/// 
///     ```
///     none-type ::= `none`
///     ```
/// 
///     NoneType is a unit type, i.e. a type with exactly one possible value, where
///     its value does not have a defined dynamic representation.
/// 
///     #### Example:
/// 
///     ```mlir
///     func.func @none_type() {
///       %none_val = "foo.unknown_op"() : () -> none
///       return
///     }
///     ```
class NoneType;
/// Type of a non-registered dialect
/// Syntax:
/// 
///     ```
///     opaque-type ::= `opaque` `<` type `>`
///     ```
/// 
///     Opaque types represent types of non-registered dialects. These are types
///     represented in their raw string form, and can only usefully be tested for
///     type equality.
/// 
///     #### Example:
/// 
///     ```mlir
///     opaque<"llvm", "struct<(i32, float)>">
///     opaque<"pdl", "value">
///     ```
class OpaqueType;
/// Multi-dimensional array with a fixed number of dimensions
/// Syntax:
/// 
///     ```
///     tensor-type ::= `tensor` `<` dimension-list type (`,` encoding)? `>`
///     dimension-list ::= (dimension `x`)*
///     dimension ::= `?` | decimal-literal
///     encoding ::= attribute-value
///     ```
/// 
///     Values with tensor type represents aggregate N-dimensional data values, and
///     have a known element type and a fixed rank with a list of dimensions. Each
///     dimension may be a static non-negative decimal constant or be dynamically
///     determined (indicated by `?`).
/// 
///     The runtime representation of the MLIR tensor type is intentionally
///     abstracted - you cannot control layout or get a pointer to the data. For
///     low level buffer access, MLIR has a [`memref` type](#memreftype). This
///     abstracted runtime representation holds both the tensor data values as well
///     as information about the (potentially dynamic) shape of the tensor. The
///     [`dim` operation](MemRef.md/#memrefdim-mlirmemrefdimop) returns the size of a
///     dimension from a value of tensor type.
/// 
///     The `encoding` attribute provides additional information on the tensor.
///     An empty attribute denotes a straightforward tensor without any specific
///     structure. But particular properties, like sparsity or other specific
///     characteristics of the data of the tensor can be encoded through this
///     attribute. The semantics are defined by a type and attribute interface
///     and must be respected by all passes that operate on tensor types.
///     TODO: provide this interface, and document it further.
/// 
///     Note: hexadecimal integer literals are not allowed in tensor type
///     declarations to avoid confusion between `0xf32` and `0 x f32`. Zero sizes
///     are allowed in tensors and treated as other sizes, e.g.,
///     `tensor<0 x 1 x i32>` and `tensor<1 x 0 x i32>` are different types. Since
///     zero sizes are not allowed in some other types, such tensors should be
///     optimized away before lowering tensors to vectors.
/// 
///     #### Example:
/// 
///     ```mlir
///     // Known rank but unknown dimensions.
///     tensor<? x ? x ? x ? x f32>
/// 
///     // Partially known dimensions.
///     tensor<? x ? x 13 x ? x f32>
/// 
///     // Full static shape.
///     tensor<17 x 4 x 13 x 4 x f32>
/// 
///     // Tensor with rank zero. Represents a scalar.
///     tensor<f32>
/// 
///     // Zero-element dimensions are allowed.
///     tensor<0 x 42 x f32>
/// 
///     // Zero-element tensor of f32 type (hexadecimal literals not allowed here).
///     tensor<0xf32>
/// 
///     // Tensor with an encoding attribute (where #ENCODING is a named alias).
///     tensor<?x?xf64, #ENCODING>
///     ```
class RankedTensorType;
/// Fixed-sized collection of other types
/// Syntax:
/// 
///     ```
///     tuple-type ::= `tuple` `<` (type ( `,` type)*)? `>`
///     ```
/// 
///     The value of `tuple` type represents a fixed-size collection of elements,
///     where each element may be of a different type.
/// 
///     **Rationale:** Though this type is first class in the type system, MLIR
///     provides no standard operations for operating on `tuple` types
///     ([rationale](../../Rationale/Rationale/#tuple-types)).
/// 
///     #### Example:
/// 
///     ```mlir
///     // Empty tuple.
///     tuple<>
/// 
///     // Single element
///     tuple<f32>
/// 
///     // Many elements.
///     tuple<i32, f32, tensor<i1>, i5>
///     ```
class TupleType;
/// Shaped reference, with unknown rank, to a region of memory
/// Syntax:
/// 
///     ```
///     unranked-memref-type ::= `memref` `<*x` type (`,` memory-space)? `>`
///     memory-space ::= attribute-value
///     ```
/// 
///     A `memref` type with an unknown rank (e.g. `memref<*xf32>`). The purpose of
///     unranked memrefs is to allow external library functions to receive memref
///     arguments of any rank without versioning the functions based on the rank.
///     Other uses of this type are disallowed or will have undefined behavior.
/// 
///     See [MemRefType](#memreftype) for more information on
///     memref types.
/// 
///     #### Examples:
/// 
///     ```mlir
///     memref<*f32>
/// 
///     // An unranked memref with a memory space of 10.
///     memref<*f32, 10>
///     ```
class UnrankedMemRefType;
/// Multi-dimensional array with unknown dimensions
/// Syntax:
/// 
///     ```
///     tensor-type ::= `tensor` `<` `*` `x` type `>`
///     ```
/// 
///     An unranked tensor is a type of tensor in which the set of dimensions have
///     unknown rank. See [RankedTensorType](#rankedtensortype)
///     for more information on tensor types.
/// 
///     #### Examples:
/// 
///     ```mlir
///     tensor<*xf32>
///     ```
class UnrankedTensorType;
/// Multi-dimensional SIMD vector type
/// Syntax:
/// 
///     ```
///     vector-type ::= `vector` `<` vector-dim-list vector-element-type `>`
///     vector-element-type ::= float-type | integer-type | index-type
///     vector-dim-list := (static-dim-list `x`)?
///     static-dim-list ::= static-dim (`x` static-dim)*
///     static-dim ::= (decimal-literal | `[` decimal-literal `]`)
///     ```
/// 
///     The vector type represents a SIMD style vector used by target-specific
///     operation sets like AVX or SVE. While the most common use is for 1D
///     vectors (e.g. vector<16 x f32>) we also support multidimensional registers
///     on targets that support them (like TPUs). The dimensions of a vector type
///     can be fixed-length, scalable, or a combination of the two. The scalable
///     dimensions in a vector are indicated between square brackets ([ ]).
/// 
///     Vector shapes must be positive decimal integers. 0D vectors are allowed by
///     omitting the dimension: `vector<f32>`.
/// 
///     Note: hexadecimal integer literals are not allowed in vector type
///     declarations, `vector<0x42xi32>` is invalid because it is interpreted as a
///     2D vector with shape `(0, 42)` and zero shapes are not allowed.
/// 
///     #### Examples:
/// 
///     ```mlir
///     // A 2D fixed-length vector of 3x42 i32 elements.
///     vector<3x42xi32>
/// 
///     // A 1D scalable-length vector that contains a multiple of 4 f32 elements.
///     vector<[4]xf32>
/// 
///     // A 2D scalable-length vector that contains a multiple of 2x8 f32 elements.
///     vector<[2]x[8]xf32>
/// 
///     // A 2D mixed fixed/scalable vector that contains 4 scalable vectors of 4 f32 elements.
///     vector<4x[4]xf32>
/// 
///     // A 3D mixed fixed/scalable vector in which only the inner dimension is
///     // scalable.
///     vector<2x[4]x8xf32>
///     ```
class VectorType;
namespace detail {

struct ComplexTypeStorage;

} // namespace detail
class ComplexType : public ::mlir::Type::TypeBase<ComplexType, ::mlir::Type, detail::ComplexTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.complex";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static ComplexType get(Type elementType);
  static ComplexType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType);
  Type getElementType() const;
};
class Float8E5M2Type : public ::mlir::Type::TypeBase<Float8E5M2Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f8E5M2";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float8E5M2Type>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float8E4M3Type : public ::mlir::Type::TypeBase<Float8E4M3Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f8E4M3";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float8E4M3Type>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float8E4M3FNType : public ::mlir::Type::TypeBase<Float8E4M3FNType, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f8E4M3FN";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float8E4M3FNType>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float8E5M2FNUZType : public ::mlir::Type::TypeBase<Float8E5M2FNUZType, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f8E5M2FNUZ";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float8E5M2FNUZType>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float8E4M3FNUZType : public ::mlir::Type::TypeBase<Float8E4M3FNUZType, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f8E4M3FNUZ";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float8E4M3FNUZType>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float8E4M3B11FNUZType : public ::mlir::Type::TypeBase<Float8E4M3B11FNUZType, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f8E4M3B11FNUZ";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float8E4M3B11FNUZType>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float8E3M4Type : public ::mlir::Type::TypeBase<Float8E3M4Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f8E3M4";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float8E3M4Type>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float4E2M1FNType : public ::mlir::Type::TypeBase<Float4E2M1FNType, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f4E2M1FN";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float4E2M1FNType>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float6E2M3FNType : public ::mlir::Type::TypeBase<Float6E2M3FNType, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f6E2M3FN";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float6E2M3FNType>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float6E3M2FNType : public ::mlir::Type::TypeBase<Float6E3M2FNType, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f6E3M2FN";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float6E3M2FNType>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float8E8M0FNUType : public ::mlir::Type::TypeBase<Float8E8M0FNUType, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.f8E8M0FNU";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float8E8M0FNUType>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class BFloat16Type : public ::mlir::Type::TypeBase<BFloat16Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static BFloat16Type get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "builtin.bf16";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  const ::llvm::fltSemantics &getFloatSemantics() const;
  ::mlir::FloatType scaleElementBitwidth(unsigned scale) const;
};
class Float16Type : public ::mlir::Type::TypeBase<Float16Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static Float16Type get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "builtin.f16";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  const ::llvm::fltSemantics &getFloatSemantics() const;
  ::mlir::FloatType scaleElementBitwidth(unsigned scale) const;
};
class FloatTF32Type : public ::mlir::Type::TypeBase<FloatTF32Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static FloatTF32Type get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "builtin.tf32";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<FloatTF32Type>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float32Type : public ::mlir::Type::TypeBase<Float32Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static Float32Type get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "builtin.f32";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  const ::llvm::fltSemantics &getFloatSemantics() const;
  ::mlir::FloatType scaleElementBitwidth(unsigned scale) const;
};
class Float64Type : public ::mlir::Type::TypeBase<Float64Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static Float64Type get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "builtin.f64";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float64Type>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float80Type : public ::mlir::Type::TypeBase<Float80Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static Float80Type get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "builtin.f80";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float80Type>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class Float128Type : public ::mlir::Type::TypeBase<Float128Type, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait, ::mlir::FloatType::Trait> {
public:
  using Base::Base;
  static Float128Type get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "builtin.f128";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using ::mlir::FloatType::Trait<Float128Type>::scaleElementBitwidth;
  const ::llvm::fltSemantics &getFloatSemantics() const;
};
class FunctionType : public ::mlir::Type::TypeBase<FunctionType, ::mlir::Type, detail::FunctionTypeStorage> {
public:
  using Base::Base;
  /// Input types.
  unsigned getNumInputs() const;
  Type getInput(unsigned i) const { return getInputs()[i]; }

  /// Result types.
  unsigned getNumResults() const;
  Type getResult(unsigned i) const { return getResults()[i]; }

  /// Returns a clone of this function-like type with the given argument
  /// and result types.
  FunctionType clone(TypeRange inputs, TypeRange results) const;

  /// Returns a new function-like type with the specified arguments and results
  /// inserted.
  FunctionType getWithArgsAndResults(ArrayRef<unsigned> argIndices,
                                     TypeRange argTypes,
                                     ArrayRef<unsigned> resultIndices,
                                     TypeRange resultTypes);

  /// Returns a new function-like type without the specified arguments and results.
  FunctionType getWithoutArgsAndResults(const BitVector &argIndices,
                                        const BitVector &resultIndices);
  static constexpr ::llvm::StringLiteral name = "builtin.function";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static FunctionType get(::mlir::MLIRContext *context, TypeRange inputs, TypeRange results);
  ArrayRef<Type> getInputs() const;
  ArrayRef<Type> getResults() const;
};
class GraphType : public ::mlir::Type::TypeBase<GraphType, ::mlir::Type, detail::FunctionTypeStorage> {
public:
  using Base::Base;
  /// Input types.
  unsigned getNumInputs() const;
  Type getInput(unsigned i) const { return getInputs()[i]; }

  /// Result types.
  unsigned getNumResults() const;
  Type getResult(unsigned i) const { return getResults()[i]; }

  /// Returns a clone of this function-like type with the given argument
  /// and result types.
  GraphType clone(TypeRange inputs, TypeRange results) const;

  /// Returns a new function-like type with the specified arguments and results
  /// inserted.
  GraphType getWithArgsAndResults(ArrayRef<unsigned> argIndices,
                                     TypeRange argTypes,
                                     ArrayRef<unsigned> resultIndices,
                                     TypeRange resultTypes);

  /// Returns a new function-like type without the specified arguments and results.
  GraphType getWithoutArgsAndResults(const BitVector &argIndices,
                                        const BitVector &resultIndices);
  static constexpr ::llvm::StringLiteral name = "builtin.graph";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static GraphType get(::mlir::MLIRContext *context, TypeRange inputs, TypeRange results);
  ArrayRef<Type> getInputs() const;
  ArrayRef<Type> getResults() const;
};
class IndexType : public ::mlir::Type::TypeBase<IndexType, ::mlir::Type, ::mlir::TypeStorage, ::mlir::VectorElementTypeInterface::Trait> {
public:
  using Base::Base;
  static IndexType get(MLIRContext *context);

  /// Storage bit width used for IndexType by internal compiler data
  /// structures.
  static constexpr unsigned kInternalStorageBitWidth = 64;
  static constexpr ::llvm::StringLiteral name = "builtin.index";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
};
class IntegerType : public ::mlir::Type::TypeBase<IntegerType, ::mlir::Type, detail::IntegerTypeStorage, ::mlir::VectorElementTypeInterface::Trait> {
public:
  using Base::Base;
  /// Signedness semantics.
  enum SignednessSemantics : uint32_t {
    Signless, /// No signedness semantics
    Signed,   /// Signed integer
    Unsigned, /// Unsigned integer
  };

  /// Return true if this is a signless integer type.
  bool isSignless() const { return getSignedness() == Signless; }
  /// Return true if this is a signed integer type.
  bool isSigned() const { return getSignedness() == Signed; }
  /// Return true if this is an unsigned integer type.
  bool isUnsigned() const { return getSignedness() == Unsigned; }

  /// Get or create a new IntegerType with the same signedness as `this` and a
  /// bitwidth scaled by `scale`.
  /// Return null if the scaled element type cannot be represented.
  IntegerType scaleElementBitwidth(unsigned scale);

  /// Integer representation maximal bitwidth.
  /// Note: This is aligned with the maximum width of llvm::IntegerType.
  static constexpr unsigned kMaxWidth = (1 << 24) - 1;
  static constexpr ::llvm::StringLiteral name = "builtin.integer";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static IntegerType get(::mlir::MLIRContext *context, unsigned width, SignednessSemantics signedness = Signless);
  static IntegerType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, unsigned width, SignednessSemantics signedness = Signless);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, unsigned width, SignednessSemantics signedness);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, unsigned width, SignednessSemantics signedness);
  unsigned getWidth() const;
  SignednessSemantics getSignedness() const;
};
namespace detail {

struct MemRefTypeStorage;

} // namespace detail
class MemRefType : public ::mlir::Type::TypeBase<MemRefType, BaseMemRefType, detail::MemRefTypeStorage, ::mlir::PtrLikeTypeInterface::Trait, ::mlir::ShapedType::Trait> {
public:
  using Base::Base;
  using BaseMemRefType::clone;
  using ShapedType::Trait<MemRefType>::getElementTypeBitWidth;
  using ShapedType::Trait<MemRefType>::getRank;
  using ShapedType::Trait<MemRefType>::getNumElements;
  using ShapedType::Trait<MemRefType>::isDynamicDim;
  using ShapedType::Trait<MemRefType>::hasStaticShape;
  using ShapedType::Trait<MemRefType>::getNumDynamicDims;
  using ShapedType::Trait<MemRefType>::getDimSize;
  using ShapedType::Trait<MemRefType>::getDynamicDimIndex;

  /// This is a builder type that keeps local references to arguments.
  /// Arguments that are passed into the builder must outlive the builder.
  class Builder;

  /// Return "true" if the last N dimensions are contiguous.
  ///
  /// Examples:
  ///   - memref<5x4x3x2xi8, strided<[24, 6, 2, 1]> is contiguous when
  ///   considering both _all_ and _only_ the trailing 3 dims,
  ///   - memref<5x4x3x2xi8, strided<[48, 6, 2, 1]> is _only_ contiguous when
  ///   considering the trailing 3 dims.
  ///
  bool areTrailingDimsContiguous(int64_t n);

  /// Return the number of trailing dimensions that are contiguous.
  ///
  /// Examples:
  ///   - memref<5x3x2xi8, strided<[6,2,1]>>, the number of collapsable
  ///     trailing dimensions is 3
  ///   - memref<5x3x2xi8, strided<[12,2,1]>>, the number of collapsable
  ///     trailing dimensions is 2 (dimension 0 is non-contiguous)
  ///   - memref<5x3x2xi8, strided<[12,4,1]>>, the number of collapsable
  ///     trailing dimensions is 1 (dimension 1 is non-contiguous)
  ///   - memref<5x3x2xi8, strided<[12,4,2]>>, the number of collapsable
  ///     trailing dimensions is 0 (dimension 2 is non-contiguous)
  ///   - memref<?x3x2xi8, strided<[6,2,1]>>, the number of collapsable
  ///     trailing dimensions is 3
  ///   - memref<?x3x2xi8, strided<[12,2,1]>>, the number of collapsable
  ///     trailing dimensions is 2 (dimension 0 is non-contiguous)
  ///   - memref<5x?x2xi8, strided<[?,2,1]>>, the number of collapsable
  ///     trailing dimensions is 2 (stride 0 is dynamic)
  int64_t getNumContiguousTrailingDims();

  /// Return a version of this type with identity layout if it can be
  /// determined statically that the layout is the canonical contiguous
  /// strided layout. Otherwise pass the layout into `simplifyAffineMap`
  /// and return a copy of this type with simplified layout.
  MemRefType canonicalizeStridedLayout();

  /// [deprecated] Returns the memory space in old raw integer representation.
  /// New `Attribute getMemorySpace()` method should be used instead.
  unsigned getMemorySpaceAsInt() const;

  /// Returns the strides of the MemRef if the layout map is in strided form.
  /// MemRefs with a layout map in strided form include:
  ///   1. empty or identity layout map, in which case the stride information
  ///      is the canonical form computed from sizes;
  ///   2. a StridedLayoutAttr layout;
  ///   3. any other layout that be converted into a single affine map layout
  ///      of the form `K + k0 * d0 + ... kn * dn`, where K and ki's are
  ///      constants or symbols.
  ///
  /// A stride specification is a list of integer values that are either
  /// static or dynamic (encoded with ShapedType::kDynamic). Strides encode
  /// the distance in the number of elements between successive entries along
  /// a particular dimension.
  LogicalResult getStridesAndOffset(SmallVectorImpl<int64_t> &strides,
                                    int64_t &offset) const;

  /// Wrapper around getStridesAndOffset(SmallVectorImpl<int64_t>, int64_t)
  /// that will assert if the logical result is not succeeded.
  std::pair<SmallVector<int64_t>, int64_t> getStridesAndOffset() const;

  /// Return "true" if the layout is compatible with strided semantics.
  bool isStrided();

  /// Return "true" if the last dimension has a static unit stride. Also
  /// return "true" for types with no strides.
  bool isLastDimUnitStride();
  static constexpr ::llvm::StringLiteral name = "builtin.memref";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static MemRefType get(ArrayRef<int64_t> shape, Type elementType, MemRefLayoutAttrInterface layout = {}, Attribute memorySpace = {});
  static MemRefType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<int64_t> shape, Type elementType, MemRefLayoutAttrInterface layout = {}, Attribute memorySpace = {});
  static MemRefType get(ArrayRef<int64_t> shape, Type elementType, AffineMap map, Attribute memorySpace = {});
  static MemRefType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<int64_t> shape, Type elementType, AffineMap map, Attribute memorySpace = {});
  static MemRefType get(ArrayRef<int64_t> shape, Type elementType, AffineMap map, unsigned memorySpaceInd);
  static MemRefType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<int64_t> shape, Type elementType, AffineMap map, unsigned memorySpaceInd);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<int64_t> shape, Type elementType, MemRefLayoutAttrInterface layout, Attribute memorySpace);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<int64_t> shape, Type elementType, MemRefLayoutAttrInterface layout, Attribute memorySpace);
  ::llvm::ArrayRef<int64_t> getShape() const;
  Type getElementType() const;
  MemRefLayoutAttrInterface getLayout() const;
  Attribute getMemorySpace() const;
};
class NoneType : public ::mlir::Type::TypeBase<NoneType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static NoneType get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "builtin.none";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
};
namespace detail {

struct OpaqueTypeStorage;

} // namespace detail
class OpaqueType : public ::mlir::Type::TypeBase<OpaqueType, ::mlir::Type, detail::OpaqueTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "builtin.opaque";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static OpaqueType get(StringAttr dialectNamespace, StringRef typeData = {});
  static OpaqueType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr dialectNamespace, StringRef typeData = {});
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr dialectNamespace, ::llvm::StringRef typeData);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr dialectNamespace, ::llvm::StringRef typeData);
  StringAttr getDialectNamespace() const;
  ::llvm::StringRef getTypeData() const;
};
namespace detail {

struct RankedTensorTypeStorage;

} // namespace detail
class RankedTensorType : public ::mlir::Type::TypeBase<RankedTensorType, TensorType, detail::RankedTensorTypeStorage, ::mlir::ShapedType::Trait, ::mlir::ValueSemantics> {
public:
  using Base::Base;
  using TensorType::clone;
  using ShapedType::Trait<RankedTensorType>::getElementTypeBitWidth;
  using ShapedType::Trait<RankedTensorType>::getRank;
  using ShapedType::Trait<RankedTensorType>::getNumElements;
  using ShapedType::Trait<RankedTensorType>::isDynamicDim;
  using ShapedType::Trait<RankedTensorType>::hasStaticShape;
  using ShapedType::Trait<RankedTensorType>::getNumDynamicDims;
  using ShapedType::Trait<RankedTensorType>::getDimSize;
  using ShapedType::Trait<RankedTensorType>::getDynamicDimIndex;

  /// This is a builder type that keeps local references to arguments.
  /// Arguments that are passed into the builder must outlive the builder.
  class Builder;

  /// Return a clone of this type with the given new element type and the same
  /// shape as this type.
  RankedTensorType clone(::mlir::Type elementType) {
    return ::llvm::cast<RankedTensorType>(cloneWith(getShape(), elementType));
  }

  /// Return a clone of this type without the encoding.
  RankedTensorType dropEncoding() {
    return RankedTensorType::get(getShape(), getElementType());
  }

  /// Return a clone of this type with the given new encoding and the same
  /// shape and element type as this type.
  RankedTensorType cloneWithEncoding(::mlir::Attribute encoding) {
    return RankedTensorType::get(getShape(), getElementType(), encoding);
  }
  static constexpr ::llvm::StringLiteral name = "builtin.tensor";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static RankedTensorType get(ArrayRef<int64_t> shape, Type elementType, Attribute encoding = {});
  static RankedTensorType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<int64_t> shape, Type elementType, Attribute encoding = {});
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<int64_t> shape, Type elementType, Attribute encoding);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<int64_t> shape, Type elementType, Attribute encoding);
  ::llvm::ArrayRef<int64_t> getShape() const;
  Type getElementType() const;
  Attribute getEncoding() const;
};
class TupleType : public ::mlir::Type::TypeBase<TupleType, ::mlir::Type, detail::TupleTypeStorage> {
public:
  using Base::Base;
  /// Accumulate the types contained in this tuple and tuples nested within
  /// it. Note that this only flattens nested tuples, not any other container
  /// type, e.g. a tuple<i32, tensor<i32>, tuple<f32, tuple<i64>>> is
  /// flattened to (i32, tensor<i32>, f32, i64)
  void getFlattenedTypes(SmallVectorImpl<Type> &types);

  /// Return the number of held types.
  size_t size() const;

  /// Iterate over the held elements.
  using iterator = ArrayRef<Type>::iterator;
  iterator begin() const { return getTypes().begin(); }
  iterator end() const { return getTypes().end(); }

  /// Return the element type at index 'index'.
  Type getType(size_t index) const {
    assert(index < size() && "invalid index for tuple type");
    return getTypes()[index];
  }
  static constexpr ::llvm::StringLiteral name = "builtin.tuple";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  static TupleType get(::mlir::MLIRContext *context, TypeRange elementTypes);
  static TupleType get(::mlir::MLIRContext *context);
  ArrayRef<Type> getTypes() const;
};
namespace detail {

struct UnrankedMemRefTypeStorage;

} // namespace detail
class UnrankedMemRefType : public ::mlir::Type::TypeBase<UnrankedMemRefType, BaseMemRefType, detail::UnrankedMemRefTypeStorage, ::mlir::PtrLikeTypeInterface::Trait, ::mlir::ShapedType::Trait> {
public:
  using Base::Base;
  using BaseMemRefType::clone;
  using ShapedType::Trait<UnrankedMemRefType>::getElementTypeBitWidth;
  using ShapedType::Trait<UnrankedMemRefType>::getRank;
  using ShapedType::Trait<UnrankedMemRefType>::getNumElements;
  using ShapedType::Trait<UnrankedMemRefType>::isDynamicDim;
  using ShapedType::Trait<UnrankedMemRefType>::hasStaticShape;
  using ShapedType::Trait<UnrankedMemRefType>::getNumDynamicDims;
  using ShapedType::Trait<UnrankedMemRefType>::getDimSize;
  using ShapedType::Trait<UnrankedMemRefType>::getDynamicDimIndex;

  ArrayRef<int64_t> getShape() const { return {}; }

  /// [deprecated] Returns the memory space in old raw integer representation.
  /// New `Attribute getMemorySpace()` method should be used instead.
  unsigned getMemorySpaceAsInt() const;

  /// Return a clone of this type with the given new element type and the same
  /// shape as this type.
  MemRefType clone(::mlir::Type elementType) {
    return ::llvm::cast<MemRefType>(cloneWith(getShape(), elementType));
  }
  static constexpr ::llvm::StringLiteral name = "builtin.unranked_memref";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static UnrankedMemRefType get(Type elementType, Attribute memorySpace);
  static UnrankedMemRefType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, Attribute memorySpace);
  static UnrankedMemRefType get(Type elementType, unsigned memorySpace);
  static UnrankedMemRefType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, unsigned memorySpace);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, Attribute memorySpace);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, Attribute memorySpace);
  Type getElementType() const;
  Attribute getMemorySpace() const;
};
namespace detail {

struct UnrankedTensorTypeStorage;

} // namespace detail
class UnrankedTensorType : public ::mlir::Type::TypeBase<UnrankedTensorType, TensorType, detail::UnrankedTensorTypeStorage, ::mlir::ShapedType::Trait, ::mlir::ValueSemantics> {
public:
  using Base::Base;
  using TensorType::clone;
  using ShapedType::Trait<UnrankedTensorType>::getElementTypeBitWidth;
  using ShapedType::Trait<UnrankedTensorType>::getRank;
  using ShapedType::Trait<UnrankedTensorType>::getNumElements;
  using ShapedType::Trait<UnrankedTensorType>::isDynamicDim;
  using ShapedType::Trait<UnrankedTensorType>::hasStaticShape;
  using ShapedType::Trait<UnrankedTensorType>::getNumDynamicDims;
  using ShapedType::Trait<UnrankedTensorType>::getDimSize;
  using ShapedType::Trait<UnrankedTensorType>::getDynamicDimIndex;

  ArrayRef<int64_t> getShape() const { return {}; }
  static constexpr ::llvm::StringLiteral name = "builtin.unranked_tensor";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static UnrankedTensorType get(Type elementType);
  static UnrankedTensorType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType);
  Type getElementType() const;
};
namespace detail {

struct VectorTypeStorage;

} // namespace detail
class VectorType : public ::mlir::Type::TypeBase<VectorType, Type, detail::VectorTypeStorage, ::mlir::ShapedType::Trait, ::mlir::ValueSemantics> {
public:
  using Base::Base;
  /// This is a builder type that keeps local references to arguments.
  /// Arguments that are passed into the builder must outlive the builder.
  class Builder;

  /// Returns true if the given type can be used as an element of a vector
  /// type. See "Builtin_VectorTypeElementType" for allowed types.
  static bool isValidElementType(Type t);

  /// Returns true if the vector contains scalable dimensions.
  bool isScalable() const {
    return llvm::is_contained(getScalableDims(), true);
  }
  bool allDimsScalable() const {
    // Treat 0-d vectors as fixed size.
    if (getRank() == 0)
      return false;
    return !llvm::is_contained(getScalableDims(), false);
  }

  /// Get the number of scalable dimensions.
  size_t getNumScalableDims() const {
    return llvm::count(getScalableDims(), true);
  }

  /// Get or create a new VectorType with the same shape as `this` and an
  /// element type of bitwidth scaled by `scale`.
  /// Return null if the scaled element type cannot be represented.
  VectorType scaleElementBitwidth(unsigned scale);

  /// Returns if this type is ranked (always true).
  bool hasRank() const { return true; }

  /// Clone this vector type with the given shape and element type. If the
  /// provided shape is `std::nullopt`, the current shape of the type is used.
  VectorType cloneWith(std::optional<ArrayRef<int64_t>> shape,
                       Type elementType) const;
  static constexpr ::llvm::StringLiteral name = "builtin.vector";
  static constexpr ::llvm::StringLiteral dialectName = "builtin";
  using Base::getChecked;
  static VectorType get(ArrayRef<int64_t> shape, Type elementType, ArrayRef<bool> scalableDims = {});
  static VectorType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<int64_t> shape, Type elementType, ArrayRef<bool> scalableDims = {});
  static ::llvm::LogicalResult verifyInvariantsImpl(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<int64_t> shape, ::mlir::Type elementType, ::llvm::ArrayRef<bool> scalableDims);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<int64_t> shape, ::mlir::Type elementType, ::llvm::ArrayRef<bool> scalableDims);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<int64_t> shape, ::mlir::Type elementType, ::llvm::ArrayRef<bool> scalableDims);
  ::llvm::ArrayRef<int64_t> getShape() const;
  ::mlir::Type getElementType() const;
  ::llvm::ArrayRef<bool> getScalableDims() const;
};

} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::ComplexType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float8E5M2Type)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float8E4M3Type)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float8E4M3FNType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float8E5M2FNUZType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float8E4M3FNUZType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float8E4M3B11FNUZType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float8E3M4Type)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float4E2M1FNType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float6E2M3FNType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float6E3M2FNType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float8E8M0FNUType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::BFloat16Type)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float16Type)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::FloatTF32Type)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float32Type)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float64Type)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float80Type)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::Float128Type)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::FunctionType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::GraphType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::IndexType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::IntegerType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::MemRefType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::NoneType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::OpaqueType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::RankedTensorType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::TupleType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::UnrankedMemRefType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::UnrankedTensorType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::VectorType)

#endif // GET_TYPEDEF_CLASSES

