/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: AffineOps.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::affine {

/// affine apply operation
/// The `affine.apply` operation applies an [affine mapping](#affine-maps)
///     to a list of SSA values, yielding a single SSA value. The number of
///     dimension and symbol operands to `affine.apply` must be equal to the
///     respective number of dimensional and symbolic inputs to the affine mapping;
///     the affine mapping has to be one-dimensional, and so the `affine.apply`
///     operation always returns one value. The input operands and result must all
///     have ‘index’ type.
/// 
///     An operand that is a valid dimension as per the [rules on valid affine
///     dimensions and symbols](#restrictions-on-dimensions-and-symbols)
///     cannot be used as a symbolic operand.
/// 
///     Example:
/// 
///     ```mlir
///     #map = affine_map<(d0, d1) -> (d0 floordiv 8 + d1 floordiv 128)>
///     ...
///     %1 = affine.apply #map (%s, %t)
/// 
///     // Inline example.
///     %2 = affine.apply affine_map<(i)[s0] -> (i + s0)> (%42)[%n]
///     ```
class AffineApplyOp;

} // namespace mlir::affine
namespace mlir::affine {

/// delinearize an index
/// The `affine.delinearize_index` operation takes a single index value and
///     calculates the multi-index according to the given basis.
/// 
///     Example:
/// 
///     ```
///     %indices:3 = affine.delinearize_index %linear_index into (%c16, %c224, %c224) : index, index, index
///     ```
/// 
///     In the above example, `%indices:3` conceptually holds the following:
/// 
///     ```
///     #map0 = affine_map<()[s0] -> (s0 floordiv 50176)>
///     #map1 = affine_map<()[s0] -> ((s0 mod 50176) floordiv 224)>
///     #map2 = affine_map<()[s0] -> (s0 mod 224)>
///     %indices_0 = affine.apply #map0()[%linear_index]
///     %indices_1 = affine.apply #map1()[%linear_index]
///     %indices_2 = affine.apply #map2()[%linear_index]
///     ```
/// 
///     In other words, `%0:3 = affine.delinearize_index %x into (B, C)` produces
///     `%0 = {%x / (B * C), (%x mod (B * C)) / C, %x mod C}`.
/// 
///     The basis may either contain `N` or `N-1` elements, where `N` is the number of results.
///     If there are N basis elements, the first one will not be used during computations,
///     but may be used during analysis and canonicalization to eliminate terms from
///     the `affine.delinearize_index` or to enable conclusions about the total size of
///     `%linear_index`.
/// 
///     If the basis is fully provided, the delinearize_index operation is said to "have
///     an outer bound". The builders assume that an `affine.delinearize_index` has
///     an outer bound by default, as this is how the operation was initially defined.
/// 
///     That is, the example above could also have been written
///     ```mlir
///     %0:3 = affine.delinearize_index %linear_index into (244, 244) : index, index
///     ```
/// 
///     Note that, for symmetry with `getPaddedBasis()`, if `hasOuterBound` is `true`
///     when one of the `OpFoldResult` builders is called but the first element of the
///     basis is `nullptr`, that first element is ignored and the builder proceeds as if
///     there was no outer bound.
/// 
///     Due to the constraints of affine maps, all the basis elements must
///     be strictly positive. A dynamic basis element being 0 or negative causes
///     undefined behavior.
/// 
///     As with other affine operations, lowerings of delinearize_index may assume
///     that the underlying computations do not overflow the index type in a signed sense
///     - that is, the product of all basis elements is positive as an `index` as well.
class AffineDelinearizeIndexOp;

} // namespace mlir::affine
namespace mlir::affine {

/// for operation
/// Syntax:
/// 
///     ```
///     operation   ::= `affine.for` ssa-id `=` lower-bound `to` upper-bound
///                     (`step` integer-literal)? `{` op* `}`
/// 
///     lower-bound ::= `max`? affine-map-attribute dim-and-symbol-use-list | shorthand-bound
///     upper-bound ::= `min`? affine-map-attribute dim-and-symbol-use-list | shorthand-bound
///     shorthand-bound ::= ssa-id | `-`? integer-literal
///     ```
/// 
///     The `affine.for` operation represents an affine loop nest. It has one region
///     containing its body. This region must contain one block that terminates with
///     [`affine.yield`](#affineyield-mliraffineyieldop). *Note:* when
///     `affine.for` is printed in custom format, the terminator is omitted. The
///     block has one argument of [`index`](Builtin.md/#indextype) type that
///     represents the induction variable of the loop.
/// 
///     The `affine.for` operation executes its body a number of times iterating
///     from a lower bound to an upper bound by a stride. The stride, represented by
///     `step`, is a positive constant integer which defaults to "1" if not present.
///     The lower and upper bounds specify a half-open range: the range includes the
///     lower bound but does not include the upper bound.
/// 
///     The lower and upper bounds of a `affine.for` operation are represented as an
///     application of an affine mapping to a list of SSA values passed to the map.
///     The [same restrictions](#restrictions-on-dimensions-and-symbols) hold for
///     these SSA values as for all bindings of SSA values to dimensions and
///     symbols.
/// 
///     The affine mappings for the bounds may return multiple results, in which
///     case the `max`/`min` keywords are required (for the lower/upper bound
///     respectively), and the bound is the maximum/minimum of the returned values.
///     There is no semantic ambiguity, but MLIR syntax requires the use of these
///     keywords to make things more obvious to human readers.
/// 
///     Many upper and lower bounds are simple, so MLIR accepts two custom form
///     syntaxes: the form that accepts a single 'ssa-id' (e.g. `%N`) is shorthand
///     for applying that SSA value to a function that maps a single symbol to
///     itself, e.g., `()[s]->(s)()[%N]`. The integer literal form (e.g. `-42`) is
///     shorthand for a nullary mapping function that returns the constant value
///     (e.g. `()->(-42)()`).
/// 
///     Example showing reverse iteration of the inner loop:
/// 
///     ```mlir
///     #map57 = affine_map<(d0)[s0] -> (s0 - d0 - 1)>
/// 
///     func.func @simple_example(%A: memref<?x?xf32>, %B: memref<?x?xf32>) {
///       %N = dim %A, 0 : memref<?x?xf32>
///       affine.for %i = 0 to %N step 1 {
///         affine.for %j = 0 to %N {   // implicitly steps by 1
///           %0 = affine.apply #map57(%j)[%N]
///           %tmp = call @F1(%A, %i, %0) : (memref<?x?xf32>, index, index)->(f32)
///           call @F2(%tmp, %B, %i, %0) : (f32, memref<?x?xf32>, index, index)->()
///         }
///       }
///       return
///     }
///     ```
///     `affine.for` can also operate on loop-carried variables (`iter_args`) and
///     return the final values after loop termination. The initial values of the
///     variables are passed as additional SSA operands to the `affine.for`
///     following the operands for the loop's lower and upper bounds. The
///     operation's region has equivalent arguments for each variable representing
///     the value of the variable at the current iteration.
/// 
///     The region must terminate with an `affine.yield` that passes all the current
///     iteration variables to the next iteration, or to the `affine.for`'s results
///     if at the last iteration. For `affine.for`'s that execute zero iterations, the
///     initial values of the loop-carried variables (corresponding to the SSA
///     operands) will be the op's results.
/// 
///     For example, to sum-reduce a memref:
/// 
///      ```mlir
///     func.func @reduce(%buffer: memref<1024xf32>) -> (f32) {
///       // Initial sum set to 0.
///       %sum_0 = arith.constant 0.0 : f32
///       // iter_args binds initial values to the loop's region arguments.
///       %sum = affine.for %i = 0 to 10 step 2
///           iter_args(%sum_iter = %sum_0) -> (f32) {
///         %t = affine.load %buffer[%i] : memref<1024xf32>
///         %sum_next = arith.addf %sum_iter, %t : f32
///         // Yield current iteration sum to next iteration %sum_iter or to %sum
///         // if final iteration.
///         affine.yield %sum_next : f32
///       }
///       return %sum : f32
///     }
///     ```
/// 
///     ```mlir
///     %res:2 = affine.for %i = 0 to 128 iter_args(%arg0 = %init0, %arg1 = %init1)
///                -> (index, index) {
///       %y0 = arith.addi %arg0, %c1 : index
///       %y1 = arith.addi %arg1, %c2 : index
///       affine.yield %y0, %y1 : index, index
///     }
///     ```
///     If the `affine.for` defines any values, a yield terminator must be
///     explicitly present. The number and types of the "affine.for" results must
///     match the initial values in the `iter_args` binding and the yield operands.
class AffineForOp;

} // namespace mlir::affine
namespace mlir::affine {

/// if-then-else operation
/// Syntax:
/// 
///     ```
///     operation  ::= `affine.if` if-op-cond `{` op* `}` (`else` `{` op* `}`)?
///     if-op-cond ::= integer-set-attr dim-and-symbol-use-list
///     ```
/// 
///     The `affine.if` operation restricts execution to a subset of the loop
///     iteration space defined by an integer set (a conjunction of affine
///     constraints). A single `affine.if` may end with an optional `else` clause.
/// 
///     The condition of the `affine.if` is represented by an
///     [integer set](#integer-sets) (a conjunction of affine constraints),
///     and the SSA values bound to the dimensions and symbols in the integer set.
///     The [same restrictions](#restrictions-on-dimensions-and-symbols) hold for
///     these SSA values as for all bindings of SSA values to dimensions and
///     symbols.
/// 
///     The `affine.if` operation contains two regions for the "then" and "else"
///     clauses.  `affine.if` may return results that are defined in its regions.
///     The values defined are determined by which execution path is taken.  Each
///     region of the `affine.if` must contain a single block with no arguments,
///     and be terminated by `affine.yield`.  If `affine.if` defines no values,
///     the `affine.yield` can be left out, and will be inserted implicitly.
///     Otherwise, it must be explicit.  If no values are defined, the else block
///     may be empty (i.e. contain no blocks).
/// 
///     Example:
/// 
///     ```mlir
///     #set = affine_set<(d0, d1)[s0]: (d0 - 10 >= 0, s0 - d0 - 9 >= 0,
///                                      d1 - 10 >= 0, s0 - d1 - 9 >= 0)>
///     func.func @reduced_domain_example(%A, %X, %N) : (memref<10xi32>, i32, i32) {
///       affine.for %i = 0 to %N {
///          affine.for %j = 0 to %N {
///            %0 = affine.apply #map42(%j)
///            %tmp = call @S1(%X, %i, %0)
///            affine.if #set(%i, %j)[%N] {
///               %1 = affine.apply #map43(%i, %j)
///               call @S2(%tmp, %A, %i, %1)
///            }
///         }
///       }
///       return
///     }
///     ```
/// 
///     Example with an explicit yield (initialization with edge padding):
/// 
///     ```mlir
///     #interior = affine_set<(i, j) : (i - 1 >= 0, j - 1 >= 0,  10 - i >= 0, 10 - j >= 0)> (%i, %j)
///     func.func @pad_edges(%I : memref<10x10xf32>) -> (memref<12x12xf32) {
///       %O = alloc memref<12x12xf32>
///       affine.parallel (%i, %j) = (0, 0) to (12, 12) {
///         %1 = affine.if #interior (%i, %j) {
///           %2 = load %I[%i - 1, %j - 1] : memref<10x10xf32>
///           affine.yield %2
///         } else {
///           %2 = arith.constant 0.0 : f32
///           affine.yield %2 : f32
///         }
///         affine.store %1, %O[%i, %j] : memref<12x12xf32>
///       }
///       return %O
///     }
///     ```
class AffineIfOp;

} // namespace mlir::affine
namespace mlir::affine {

/// linearize an index
/// The `affine.linearize_index` operation takes a sequence of index values and a
///     basis of the same length and linearizes the indices using that basis.
/// 
///     That is, for indices `%idx_0` to `%idx_{N-1}` and basis elements `b_0`
///     (or `b_1`) up to `b_{N-1}` it computes
/// 
///     ```
///     sum(i = 0 to N-1) %idx_i * product(j = i + 1 to N-1) B_j
///     ```
/// 
///     In other words, `%0 = affine.linearize_index [%z, %y, %x] by (Z, Y, X)`
///     gives `%0 = %x + %y * X + %z * X * Y`, or `%0 = %x + X * (%y + Y * (%z))`.
/// 
///     The basis may either have `N` or `N-1` elements, where `N` is the number of
///     inputs to linearize_index. If `N` inputs are provided, the first one is not used
///     in computation, but may be used during analysis or canonicalization as a bound
///     on `%idx_0`.
/// 
///     If all `N` basis elements are provided, the linearize_index operation is said to
///     "have an outer bound".
/// 
///     As a convenience, and for symmetry with `getPaddedBasis()`, if the first
///     element of a set of `OpFoldResult`s passed to the builders of this operation is
///     `nullptr`, that element is ignored.
/// 
///     If the `disjoint` property is present, this is an optimization hint that,
///     for all `i`, `0 <= %idx_i < B_i` - that is, no index affects any other index,
///     except that `%idx_0` may be negative to make the index as a whole negative.
///     In addition, `disjoint` is an assertion that all bases elements are non-negative.
/// 
///     Note that the outputs of `affine.delinearize_index` are, by definition, `disjoint`.
/// 
///     As with other affine ops, undefined behavior occurs if the linearization
///     computation overflows in the signed sense.
/// 
///     Example:
/// 
///     ```mlir
///     %linear_index = affine.linearize_index [%index_0, %index_1, %index_2] by (2, 3, 5) : index
///     // Same effect
///     %linear_index = affine.linearize_index [%index_0, %index_1, %index_2] by (3, 5) : index
///     ```
/// 
///     In the above example, `%linear_index` conceptually holds the following:
/// 
///     ```mlir
///     #map = affine_map<()[s0, s1, s2] -> (s0 * 15 + s1 * 5 + s2)>
///     %linear_index = affine.apply #map()[%index_0, %index_1, %index_2]
///     ```
class AffineLinearizeIndexOp;

} // namespace mlir::affine
namespace mlir::affine {

/// affine load operation
/// Syntax:
/// 
///     ```
///     operation ::= ssa-id `=` `affine.load` ssa-use `[` multi-dim-affine-map-of-ssa-ids `]` `:` memref-type
///     ```
/// 
///     The `affine.load` op reads an element from a memref, where the index
///     for each memref dimension is an affine expression of loop induction
///     variables and symbols. The output of `affine.load` is a new value with the
///     same type as the elements of the memref. An affine expression of loop IVs
///     and symbols must be specified for each dimension of the memref. The keyword
///     `symbol` can be used to indicate SSA identifiers which are symbolic.
/// 
///     Example 1:
/// 
///     ```mlir
///     %1 = affine.load %0[%i0 + 3, %i1 + 7] : memref<100x100xf32>
///     ```
/// 
///     Example 2: Uses `symbol` keyword for symbols `%n` and `%m`.
/// 
///     ```mlir
///     %1 = affine.load %0[%i0 + symbol(%n), %i1 + symbol(%m)] : memref<100x100xf32>
///     ```
class AffineLoadOp;

} // namespace mlir::affine
namespace mlir::affine {

/// max operation
/// The `affine.max` operation computes the maximum value result from a multi-result
///     affine map.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = affine.max (d0) -> (1000, d0 + 512) (%i0) : index
///     ```
class AffineMaxOp;

} // namespace mlir::affine
namespace mlir::affine {

/// min operation
/// Syntax:
/// 
///     ```
///     operation ::= ssa-id `=` `affine.min` affine-map-attribute dim-and-symbol-use-list
///     ```
/// 
///     The `affine.min` operation applies an [affine mapping](#affine-expressions)
///     to a list of SSA values, and returns the minimum value of all result
///     expressions. The number of dimension and symbol arguments to `affine.min`
///     must be equal to the respective number of dimensional and symbolic inputs to
///     the affine mapping; the `affine.min` operation always returns one value. The
///     input operands and result must all have 'index' type.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = affine.min affine_map<(d0)[s0] -> (1000, d0 + 512, s0)> (%arg0)[%arg1]
///     ```
class AffineMinOp;

} // namespace mlir::affine
namespace mlir::affine {

/// multi-index parallel band operation
/// The `affine.parallel` operation represents a hyper-rectangular affine
///     parallel band, defining zero or more SSA values for its induction variables.
///     It has one region capturing the parallel band body. The induction variables
///     are represented as arguments of this region. These SSA values always have
///     type index, which is the size of the machine word. The strides, represented
///     by steps, are positive constant integers which defaults to "1" if not
///     present. The lower and upper bounds specify a half-open range: the range
///     includes the lower bound but does not include the upper bound. The body
///     region must contain exactly one block that terminates with `affine.yield`.
/// 
///     The lower and upper bounds of a parallel operation are represented as an
///     application of an affine mapping to a list of SSA values passed to the map.
///     The same restrictions hold for these SSA values as for all bindings of SSA
///     values to dimensions and symbols. The list of expressions in each map is
///     interpreted according to the respective bounds group attribute. If a single
///     expression belongs to the group, then the result of this expression is taken
///     as a lower(upper) bound of the corresponding loop induction variable. If
///     multiple expressions belong to the group, then the lower(upper) bound is the
///     max(min) of these values obtained from these expressions. The loop band has
///     as many loops as elements in the group bounds attributes.
/// 
///     Each value yielded by `affine.yield` will be accumulated/reduced via one of
///     the reduction methods defined in the AtomicRMWKind enum.  The order of
///     reduction is unspecified, and lowering may produce any valid ordering.
///     Loops with a 0 trip count will produce as a result the identity value
///     associated with each reduction (i.e. 0.0 for addf, 1.0 for mulf).  Assign
///     reductions for loops with a trip count != 1 produces undefined results.
/// 
///     Note: Calling `AffineParallelOp::build` will create the required region and
///     block, and insert the required terminator if it is trivial (i.e. no values
///     are yielded).  Parsing will also create the required region, block, and
///     terminator, even when they are missing from the textual representation.
/// 
///     Example (3x3 valid convolution):
/// 
///     ```mlir
///     func.func @conv_2d(%D : memref<100x100xf32>, %K : memref<3x3xf32>) -> (memref<98x98xf32>) {
///       %O = memref.alloc() : memref<98x98xf32>
///       affine.parallel (%x, %y) = (0, 0) to (98, 98) {
///         %0 = affine.parallel (%kx, %ky) = (0, 0) to (2, 2) reduce ("addf") -> f32 {
///           %1 = affine.load %D[%x + %kx, %y + %ky] : memref<100x100xf32>
///           %2 = affine.load %K[%kx, %ky] : memref<3x3xf32>
///           %3 = arith.mulf %1, %2 : f32
///           affine.yield %3 : f32
///         }
///         affine.store %0, %O[%x, %y] : memref<98x98xf32>
///       }
///       return %O : memref<98x98xf32>
///     }
///     ```
/// 
///     Example (tiling by potentially imperfectly dividing sizes):
/// 
///     ```mlir
///     affine.parallel (%ii, %jj) = (0, 0) to (%N, %M) step (32, 32) {
///       affine.parallel (%i, %j) = (%ii, %jj)
///                               to (min(%ii + 32, %N), min(%jj + 32, %M)) {
///         call @f(%i, %j) : (index, index) -> ()
///       }
///     }
///     ```
class AffineParallelOp;

} // namespace mlir::affine
namespace mlir::affine {

/// affine prefetch operation
/// The `affine.prefetch` op prefetches data from a memref location described
///     with an affine subscript similar to affine.load, and has three attributes:
///     a read/write specifier, a locality hint, and a cache type specifier as shown
///     below:
/// 
///     ```mlir
///     affine.prefetch %0[%i, %j + 5], read, locality<3>, data : memref<400x400xi32>
///     ```
/// 
///     The read/write specifier is either 'read' or 'write', the locality hint
///     specifier ranges from locality<0> (no locality) to locality<3> (extremely
///     local keep in cache). The cache type specifier is either 'data' or 'instr'
///     and specifies whether the prefetch is performed on data cache or on
///     instruction cache.
class AffinePrefetchOp;

} // namespace mlir::affine
namespace mlir::affine {

/// affine store operation
/// Syntax:
/// 
///     ```
///     operation ::= `affine.store` ssa-use, ssa-use `[` multi-dim-affine-map-of-ssa-ids `]` `:` memref-type
///     ```
/// 
///     The `affine.store` op writes an element to a memref, where the index
///     for each memref dimension is an affine expression of loop induction
///     variables and symbols. The `affine.store` op stores a new value which is the
///     same type as the elements of the memref. An affine expression of loop IVs
///     and symbols must be specified for each dimension of the memref. The keyword
///     `symbol` can be used to indicate SSA identifiers which are symbolic.
/// 
///     Example 1:
/// 
///     ```mlir
///     affine.store %v0, %0[%i0 + 3, %i1 + 7] : memref<100x100xf32>
///     ```
/// 
///     Example 2: Uses `symbol` keyword for symbols `%n` and `%m`.
/// 
///     ```mlir
///     affine.store %v0, %0[%i0 + symbol(%n), %i1 + symbol(%m)] : memref<100x100xf32>
///     ```
class AffineStoreOp;

} // namespace mlir::affine
namespace mlir::affine {

/// affine vector load operation
/// The `affine.vector_load` is the vector counterpart of
///     [affine.load](#affineload-mliraffineloadop). It reads a slice from a
///     [MemRef](Builtin.md/#memreftype), supplied as its first operand,
///     into a [vector](Builtin.md/#vectortype) of the same base elemental type.
///     The index for each memref dimension is an affine expression of loop induction
///     variables and symbols. These indices determine the start position of the read
///     within the memref. The shape of the return vector type determines the shape of
///     the slice read from the memref. This slice is contiguous along the respective
///     dimensions of the shape. Strided vector loads will be supported in the future.
///     An affine expression of loop IVs and symbols must be specified for each
///     dimension of the memref. The keyword `symbol` can be used to indicate SSA
///     identifiers which are symbolic.
/// 
///     Example 1: 8-wide f32 vector load.
/// 
///     ```mlir
///     %1 = affine.vector_load %0[%i0 + 3, %i1 + 7] : memref<100x100xf32>, vector<8xf32>
///     ```
/// 
///     Example 2: 4-wide f32 vector load. Uses `symbol` keyword for symbols `%n` and `%m`.
/// 
///     ```mlir
///     %1 = affine.vector_load %0[%i0 + symbol(%n), %i1 + symbol(%m)] : memref<100x100xf32>, vector<4xf32>
///     ```
/// 
///     Example 3: 2-dim f32 vector load.
/// 
///     ```mlir
///     %1 = affine.vector_load %0[%i0, %i1] : memref<100x100xf32>, vector<2x8xf32>
///     ```
/// 
///     TODOs:
///     * Add support for strided vector loads.
///     * Consider adding a permutation map to permute the slice that is read from memory
///     (see [vector.transfer_read](../Vector/#vectortransfer_read-mlirvectortransferreadop)).
class AffineVectorLoadOp;

} // namespace mlir::affine
namespace mlir::affine {

/// affine vector store operation
/// The `affine.vector_store` is the vector counterpart of
///     [affine.store](#affinestore-mliraffinestoreop). It writes a
///     [vector](Builtin.md/#vectortype), supplied as its first operand,
///     into a slice within a [MemRef](Builtin.md/#memreftype) of the same base
///     elemental type, supplied as its second operand.
///     The index for each memref dimension is an affine expression of loop
///     induction variables and symbols. These indices determine the start position
///     of the write within the memref. The shape of the input vector determines the
///     shape of the slice written to the memref. This slice is contiguous along the
///     respective dimensions of the shape. Strided vector stores will be supported
///     in the future.
///     An affine expression of loop IVs and symbols must be specified for each
///     dimension of the memref. The keyword `symbol` can be used to indicate SSA
///     identifiers which are symbolic.
/// 
///     Example 1: 8-wide f32 vector store.
/// 
///     ```mlir
///     affine.vector_store %v0, %0[%i0 + 3, %i1 + 7] : memref<100x100xf32>, vector<8xf32>
///     ```
/// 
///     Example 2: 4-wide f32 vector store. Uses `symbol` keyword for symbols `%n` and `%m`.
/// 
///     ```mlir
///     affine.vector_store %v0, %0[%i0 + symbol(%n), %i1 + symbol(%m)] : memref<100x100xf32>, vector<4xf32>
///     ```
/// 
///     Example 3: 2-dim f32 vector store.
/// 
///     ```mlir
///     affine.vector_store %v0, %0[%i0, %i1] : memref<100x100xf32>, vector<2x8xf32>
///     ```
/// 
///     TODOs:
///     * Add support for strided vector stores.
///     * Consider adding a permutation map to permute the slice that is written to memory
///     (see [vector.transfer_write](../Vector/#vectortransfer_write-mlirvectortransferwriteop)).
class AffineVectorStoreOp;

} // namespace mlir::affine
namespace mlir::affine {

/// Yield values to parent operation
/// The `affine.yield` yields zero or more SSA values from an affine op region and
///     terminates the region. The semantics of how the values yielded are used
///     is defined by the parent operation.
///     If `affine.yield` has any operands, the operands must match the parent
///     operation's results.
///     If the parent operation defines no values, then the `affine.yield` may be
///     left out in the custom syntax and the builders will insert one implicitly.
///     Otherwise, it has to be present in the syntax to indicate which values are
///     yielded.
class AffineYieldOp;

} // namespace mlir::affine
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineApplyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineApplyOpGenericAdaptorBase {
public:
  struct Properties {
    using mapTy = ::mlir::AffineMapAttr;
    mapTy map;

    auto getMap() const {
      auto &propStorage = this->map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setMap(const ::mlir::AffineMapAttr &propValue) {
      this->map = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.map == this->map &&
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
  AffineApplyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.apply", odsAttrs.getContext());
  }

  AffineApplyOpGenericAdaptorBase(AffineApplyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
    return attr;
  }

  ::mlir::AffineMap getMap();
};

} // namespace detail
template <typename RangeT>
class AffineApplyOpGenericAdaptor : public detail::AffineApplyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineApplyOpGenericAdaptorBase;
  static constexpr int odsIndex_mapOperands = 0;
public:
  AffineApplyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineApplyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineApplyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineApplyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineApplyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineApplyOpGenericAdaptor(RangeT values, const AffineApplyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineApplyOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineApplyOp>>>
  AffineApplyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getMapOperands() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AffineApplyOpAdaptor : public AffineApplyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineApplyOpGenericAdaptor::AffineApplyOpGenericAdaptor;
  AffineApplyOpAdaptor(AffineApplyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineApplyOp : public ::mlir::Op<AffineApplyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineApplyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineApplyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_mapOperands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<AffineApplyOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("map")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMapAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.apply");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getMapOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getMapOperandsMutable();
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
  ::mlir::AffineMapAttr getMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
  }

  ::mlir::AffineMap getMap();
  void setMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().map = attr;
  }

  void setMap(::mlir::AffineMap attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<AffineExpr>  exprList, ValueRange mapOperands);
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<AffineExpr>  exprList, ValueRange mapOperands);
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<AffineExpr>  exprList, ValueRange mapOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::AffineMapAttr map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::AffineMapAttr map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::AffineMapAttr map, ::mlir::ValueRange mapOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::AffineMapAttr map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::AffineMapAttr map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::AffineMapAttr map, ::mlir::ValueRange mapOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::AffineMapAttr map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::AffineMapAttr map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::AffineMapAttr map, ::mlir::ValueRange mapOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::AffineMap map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::AffineMap map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::AffineMap map, ::mlir::ValueRange mapOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::AffineMap map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::AffineMap map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::AffineMap map, ::mlir::ValueRange mapOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::AffineMap map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::AffineMap map, ::mlir::ValueRange mapOperands);
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::AffineMap map, ::mlir::ValueRange mapOperands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineApplyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineApplyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
  /// Returns the affine map to be applied by this operation.
  AffineMap getAffineMap() { return getMap(); }

  /// Returns the affine value map computed from this operation.
  AffineValueMap getAffineValueMap();

  /// Returns true if the result of this operation can be used as dimension id
  /// in the region of the closest surrounding op with trait AffineScope.
  bool isValidDim();

  /// Returns true if the result of this operation can be used as dimension id
  /// within 'region', i.e., for all its uses with `region`.
  bool isValidDim(Region *region);

  /// Returns true if the result of this operation is a symbol in the region
  /// of the closest surrounding op that has the trait AffineScope.
  bool isValidSymbol();

  /// Returns true if the result of this operation is a symbol for all its
  /// uses in `region`.
  bool isValidSymbol(Region *region);

  /// Returns all dimension operands.
  ValueRange getDimOperands() {
    return OperandRange{getOperands().begin(),
                        getOperands().begin() + getMap().getNumDims()};
  }

  /// Returns all symbol operands.
  ValueRange getSymbolOperands() {
    return OperandRange{getOperands().begin() + getMap().getNumDims(),
                        getOperands().end()};
  }
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineApplyOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineDelinearizeIndexOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineDelinearizeIndexOpGenericAdaptorBase {
public:
  struct Properties {
    using static_basisTy = ::mlir::DenseI64ArrayAttr;
    static_basisTy static_basis;

    auto getStaticBasis() const {
      auto &propStorage = this->static_basis;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticBasis(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_basis = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.static_basis == this->static_basis &&
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
  AffineDelinearizeIndexOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.delinearize_index", odsAttrs.getContext());
  }

  AffineDelinearizeIndexOpGenericAdaptorBase(AffineDelinearizeIndexOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getStaticBasisAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_basis);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticBasis();
};

} // namespace detail
template <typename RangeT>
class AffineDelinearizeIndexOpGenericAdaptor : public detail::AffineDelinearizeIndexOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineDelinearizeIndexOpGenericAdaptorBase;
  static constexpr int odsIndex_linear_index = 0;
  static constexpr int odsIndex_dynamic_basis = 1;
public:
  AffineDelinearizeIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineDelinearizeIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineDelinearizeIndexOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineDelinearizeIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineDelinearizeIndexOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineDelinearizeIndexOpGenericAdaptor(RangeT values, const AffineDelinearizeIndexOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineDelinearizeIndexOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineDelinearizeIndexOp>>>
  AffineDelinearizeIndexOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLinearIndex() {
    return (*getODSOperands(0).begin());
  }

  RangeT getDynamicBasis() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AffineDelinearizeIndexOpAdaptor : public AffineDelinearizeIndexOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineDelinearizeIndexOpGenericAdaptor::AffineDelinearizeIndexOpGenericAdaptor;
  AffineDelinearizeIndexOpAdaptor(AffineDelinearizeIndexOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineDelinearizeIndexOp : public ::mlir::Op<AffineDelinearizeIndexOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineDelinearizeIndexOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineDelinearizeIndexOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_linear_index = 0;
  static constexpr int odsIndex_dynamic_basis = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("static_basis")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getStaticBasisAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getStaticBasisAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.delinearize_index");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getLinearIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getDynamicBasis() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getLinearIndexMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDynamicBasisMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getMultiIndex() {
    return getODSResults(0);
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
  ::mlir::DenseI64ArrayAttr getStaticBasisAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_basis);
  }

  ::llvm::ArrayRef<int64_t> getStaticBasis();
  void setStaticBasisAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_basis = attr;
  }

  void setStaticBasis(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value linear_index, ValueRange dynamic_basis, ArrayRef<int64_t> static_basis, bool hasOuterBound = true);
  static AffineDelinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value linear_index, ValueRange dynamic_basis, ArrayRef<int64_t> static_basis, bool hasOuterBound = true);
  static AffineDelinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, Value linear_index, ValueRange dynamic_basis, ArrayRef<int64_t> static_basis, bool hasOuterBound = true);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value linear_index, ValueRange basis, bool hasOuterBound = true);
  static AffineDelinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value linear_index, ValueRange basis, bool hasOuterBound = true);
  static AffineDelinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, Value linear_index, ValueRange basis, bool hasOuterBound = true);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value linear_index, ArrayRef<OpFoldResult> basis, bool hasOuterBound = true);
  static AffineDelinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value linear_index, ArrayRef<OpFoldResult> basis, bool hasOuterBound = true);
  static AffineDelinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, Value linear_index, ArrayRef<OpFoldResult> basis, bool hasOuterBound = true);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value linear_index, ArrayRef<int64_t> basis, bool hasOuterBound = true);
  static AffineDelinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value linear_index, ArrayRef<int64_t> basis, bool hasOuterBound = true);
  static AffineDelinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, Value linear_index, ArrayRef<int64_t> basis, bool hasOuterBound = true);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange multi_index, ::mlir::Value linear_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis);
  static AffineDelinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange multi_index, ::mlir::Value linear_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis);
  static AffineDelinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange multi_index, ::mlir::Value linear_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange multi_index, ::mlir::Value linear_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis);
  static AffineDelinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange multi_index, ::mlir::Value linear_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis);
  static AffineDelinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange multi_index, ::mlir::Value linear_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineDelinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineDelinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineDelinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineDelinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
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
  /// Return true if the basis includes a bound on the first index input.
  bool hasOuterBound() {
    return getMultiIndex().size() == getStaticBasis().size();
  }

  /// Returns a vector with all the static and dynamic basis values.
  SmallVector<OpFoldResult> getMixedBasis() {
    OpBuilder builder(getContext());
    return ::mlir::getMixedValues(getStaticBasis(), getDynamicBasis(), builder);
  }

  /// Return a vector that contains the basis of the operation, removing
  /// the outer bound if one is present.
  SmallVector<OpFoldResult> getEffectiveBasis();

  /// Return the vector with one basis element per result of the operation. If
  /// there is no outer bound specified, the leading entry of this result will be
  /// nullptr.
  SmallVector<OpFoldResult> getPaddedBasis();
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineDelinearizeIndexOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineForOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineForOpGenericAdaptorBase {
public:
  struct Properties {
    using lowerBoundMapTy = ::mlir::AffineMapAttr;
    lowerBoundMapTy lowerBoundMap;

    auto getLowerBoundMap() const {
      auto &propStorage = this->lowerBoundMap;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setLowerBoundMap(const ::mlir::AffineMapAttr &propValue) {
      this->lowerBoundMap = propValue;
    }
    using stepTy = ::mlir::IntegerAttr;
    stepTy step;

    auto getStep() const {
      auto &propStorage = this->step;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setStep(const ::mlir::IntegerAttr &propValue) {
      this->step = propValue;
    }
    using upperBoundMapTy = ::mlir::AffineMapAttr;
    upperBoundMapTy upperBoundMap;

    auto getUpperBoundMap() const {
      auto &propStorage = this->upperBoundMap;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setUpperBoundMap(const ::mlir::AffineMapAttr &propValue) {
      this->upperBoundMap = propValue;
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
        rhs.lowerBoundMap == this->lowerBoundMap &&
        rhs.step == this->step &&
        rhs.upperBoundMap == this->upperBoundMap &&
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
  AffineForOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.for", odsAttrs.getContext());
  }

  AffineForOpGenericAdaptorBase(AffineForOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getLowerBoundMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().lowerBoundMap);
    return attr;
  }

  ::mlir::AffineMap getLowerBoundMap();
  ::mlir::AffineMapAttr getUpperBoundMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().upperBoundMap);
    return attr;
  }

  ::mlir::AffineMap getUpperBoundMap();
  ::mlir::IntegerAttr getStepAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().step);
    return attr;
  }

  ::llvm::APInt getStep();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class AffineForOpGenericAdaptor : public detail::AffineForOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineForOpGenericAdaptorBase;
  static constexpr int odsIndex_lowerBoundOperands = 0;
  static constexpr int odsIndex_upperBoundOperands = 1;
  static constexpr int odsIndex_inits = 2;
public:
  AffineForOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineForOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineForOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineForOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : AffineForOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineForOpGenericAdaptor(RangeT values, const AffineForOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineForOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineForOp>>>
  AffineForOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getLowerBoundOperands() {
    return getODSOperands(0);
  }

  RangeT getUpperBoundOperands() {
    return getODSOperands(1);
  }

  RangeT getInits() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AffineForOpAdaptor : public AffineForOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineForOpGenericAdaptor::AffineForOpGenericAdaptor;
  AffineForOpAdaptor(AffineForOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineForOp : public ::mlir::Op<AffineForOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<AffineYieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::LoopLikeOpInterface::Trait, ::mlir::RegionBranchOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineForOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineForOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lowerBoundOperands = 0;
  static constexpr int odsIndex_upperBoundOperands = 1;
  static constexpr int odsIndex_inits = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::isDefinedOutsideOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::moveOutOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::promoteIfSingleIteration;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::getInitsMutable;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::getRegionIterArgs;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::getLoopResults;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::getStaticTripCount;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::isValidInductionVarType;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::setLoopLowerBounds;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::setLoopUpperBounds;
  using ::mlir::LoopLikeOpInterface::Trait<AffineForOp>::setLoopSteps;
  using ::mlir::RegionBranchOpInterface::Trait<AffineForOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<AffineForOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<AffineForOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<AffineForOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<AffineForOp>::getRegionInvocationBounds;
  using ::mlir::RegionBranchOpInterface::Trait<AffineForOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("lowerBoundMap"), ::llvm::StringRef("step"), ::llvm::StringRef("upperBoundMap"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLowerBoundMapAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLowerBoundMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStepAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStepAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getUpperBoundMapAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getUpperBoundMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.for");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getLowerBoundOperands() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getUpperBoundOperands() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getInits() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getLowerBoundOperandsMutable();
  ::mlir::MutableOperandRange getUpperBoundOperandsMutable();
  ::mlir::MutableOperandRange getInitsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
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
  ::mlir::AffineMapAttr getLowerBoundMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().lowerBoundMap);
  }

  ::mlir::AffineMap getLowerBoundMap();
  ::mlir::AffineMapAttr getUpperBoundMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().upperBoundMap);
  }

  ::mlir::AffineMap getUpperBoundMap();
  ::mlir::IntegerAttr getStepAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().step);
  }

  ::llvm::APInt getStep();
  void setLowerBoundMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().lowerBoundMap = attr;
  }

  void setLowerBoundMap(::mlir::AffineMap attrValue);
  void setUpperBoundMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().upperBoundMap = attr;
  }

  void setUpperBoundMap(::mlir::AffineMap attrValue);
  void setStepAttr(::mlir::IntegerAttr attr) {
    getProperties().step = attr;
  }

  void setStep(::llvm::APInt attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, int64_t lowerBound, int64_t upperBound, int64_t step = 1, ValueRange iterArgs = {}, function_ref<void(OpBuilder &, Location, Value, ValueRange)> bodyBuilder = nullptr);
  static AffineForOp create(::mlir::OpBuilder &builder, ::mlir::Location location, int64_t lowerBound, int64_t upperBound, int64_t step = 1, ValueRange iterArgs = {}, function_ref<void(OpBuilder &, Location, Value, ValueRange)> bodyBuilder = nullptr);
  static AffineForOp create(::mlir::ImplicitLocOpBuilder &builder, int64_t lowerBound, int64_t upperBound, int64_t step = 1, ValueRange iterArgs = {}, function_ref<void(OpBuilder &, Location, Value, ValueRange)> bodyBuilder = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange lbOperands, AffineMap lbMap, ValueRange ubOperands, AffineMap ubMap, int64_t step = 1, ValueRange iterArgs = {}, function_ref<void(OpBuilder &, Location, Value, ValueRange)> bodyBuilder = nullptr);
  static AffineForOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange lbOperands, AffineMap lbMap, ValueRange ubOperands, AffineMap ubMap, int64_t step = 1, ValueRange iterArgs = {}, function_ref<void(OpBuilder &, Location, Value, ValueRange)> bodyBuilder = nullptr);
  static AffineForOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange lbOperands, AffineMap lbMap, ValueRange ubOperands, AffineMap ubMap, int64_t step = 1, ValueRange iterArgs = {}, function_ref<void(OpBuilder &, Location, Value, ValueRange)> bodyBuilder = nullptr);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  ::llvm::SmallVector<::mlir::Region *> getLoopRegions();
  ::std::optional<::llvm::SmallVector<::mlir::Value>> getLoopInductionVars();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopLowerBounds();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopSteps();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopUpperBounds();
  ::std::optional<::llvm::MutableArrayRef<::mlir::OpOperand>> getYieldedValuesMutable();
  ::mlir::FailureOr<::mlir::LoopLikeOpInterface> replaceWithAdditionalYields(::mlir::RewriterBase &rewriter, ::mlir::ValueRange newInitOperands, bool replaceInitOperandUsesInLoop, const ::mlir::NewYieldValuesFn &newYieldValuesFn);
  ::mlir::OperandRange getEntrySuccessorOperands(::mlir::RegionSuccessor successor);
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  /// Defining the function type we use for building the body of affine.for.
  using BodyBuilderFn =
      function_ref<void(OpBuilder &, Location, Value, ValueRange)>;

  BlockArgument getInductionVar() { return getBody()->getArgument(0); }
  Block::BlockArgListType getRegionIterArgs() {
    return getBody()->getArguments().drop_front();
  }

  /// Returns operands for the lower and upper bound maps with the operands
  /// for the lower bound map in front of those for the upper bound map.
  operand_range getControlOperands();

  /// Returns information about the lower bound as a single object.
  AffineBound getLowerBound();

  /// Returns information about the upper bound as a single object.
  AffineBound getUpperBound();

  /// Returns loop step.
  int64_t getStepAsInt() { return getStep().getSExtValue(); }

  /// Set lower bound. The new bound must have the same number of operands as
  /// the current bound map. Otherwise, 'replaceForLowerBound' should be used.
  void setLowerBound(ValueRange operands, AffineMap map);
  /// Set upper bound. The new bound must not have more operands than the
  /// current bound map. Otherwise, 'replaceForUpperBound' should be used.
  void setUpperBound(ValueRange operands, AffineMap map);

  /// Set loop step.
  void setStep(int64_t step) {
    assert(step > 0 && "step has to be a positive integer constant");
    setStep(APInt(/*numBits=*/64, step, /*isSigned=*/true));
  }

  /// Returns number of region arguments for loop-carried values.
  unsigned getNumRegionIterArgs() {
    return getBody()->getNumArguments() - 1;
  }

  /// Number of operands controlling the loop: lb and ub.
  unsigned getNumControlOperands() {
    return getOperation()->getNumOperands() - getNumIterOperands();
  }

  /// Get the number of loop-carried values.
  unsigned getNumIterOperands();

  /// Returns true if the lower bound is constant.
  bool hasConstantLowerBound();
  /// Returns true if the upper bound is constant.
  bool hasConstantUpperBound();
  /// Returns true if both bounds are constant.
  bool hasConstantBounds() {
    return hasConstantLowerBound() && hasConstantUpperBound();
  }
  /// Returns the value of the constant lower bound.
  /// Fails assertion if the bound is non-constant.
  int64_t getConstantLowerBound();
  /// Returns the value of the constant upper bound. The upper bound is
  /// exclusive. Fails assertion if the bound is non-constant.
  int64_t getConstantUpperBound();
  /// Sets the lower bound to the given constant value.
  void setConstantLowerBound(int64_t value);
  /// Sets the upper bound to the given constant value.
  void setConstantUpperBound(int64_t value);

  /// Returns true if both the lower and upper bound have the same operand
  /// lists (same operands in the same order).
  bool matchingBoundOperandList();

  /// Interface method for ConditionallySpeculatable.
  Speculation::Speculatability getSpeculatability();
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineForOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineIfOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineIfOpGenericAdaptorBase {
public:
  struct Properties {
    using conditionTy = ::mlir::IntegerSetAttr;
    conditionTy condition;

    auto getCondition() const {
      auto &propStorage = this->condition;
      return ::llvm::cast<::mlir::IntegerSetAttr>(propStorage);
    }
    void setCondition(const ::mlir::IntegerSetAttr &propValue) {
      this->condition = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.condition == this->condition &&
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
  AffineIfOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.if", odsAttrs.getContext());
  }

  AffineIfOpGenericAdaptorBase(AffineIfOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerSetAttr getConditionAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerSetAttr>(getProperties().condition);
    return attr;
  }

  ::mlir::IntegerSet getCondition();
  ::mlir::Region &getThenRegion() {
    return *odsRegions[0];
  }

  ::mlir::Region &getElseRegion() {
    return *odsRegions[1];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class AffineIfOpGenericAdaptor : public detail::AffineIfOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineIfOpGenericAdaptorBase;
public:
  AffineIfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineIfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineIfOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineIfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineIfOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineIfOpGenericAdaptor(RangeT values, const AffineIfOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineIfOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineIfOp>>>
  AffineIfOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AffineIfOpAdaptor : public AffineIfOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineIfOpGenericAdaptor::AffineIfOpGenericAdaptor;
  AffineIfOpAdaptor(AffineIfOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineIfOp : public ::mlir::Op<AffineIfOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<AffineYieldOp>::Impl, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::RecursivelySpeculatableImplTrait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::RegionBranchOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineIfOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineIfOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchOpInterface::Trait<AffineIfOp>::getEntrySuccessorOperands;
  using ::mlir::RegionBranchOpInterface::Trait<AffineIfOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<AffineIfOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<AffineIfOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<AffineIfOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<AffineIfOp>::getRegionInvocationBounds;
  using ::mlir::RegionBranchOpInterface::Trait<AffineIfOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("condition")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getConditionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getConditionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.if");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
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

  ::mlir::Region &getThenRegion() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getElseRegion() {
    return (*this)->getRegion(1);
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
  ::mlir::IntegerSetAttr getConditionAttr() {
    return ::llvm::cast<::mlir::IntegerSetAttr>(getProperties().condition);
  }

  ::mlir::IntegerSet getCondition();
  void setConditionAttr(::mlir::IntegerSetAttr attr) {
    getProperties().condition = attr;
  }

  void setCondition(::mlir::IntegerSet attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, IntegerSet set, ValueRange args, bool withElseRegion);
  static AffineIfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, IntegerSet set, ValueRange args, bool withElseRegion);
  static AffineIfOp create(::mlir::ImplicitLocOpBuilder &builder, IntegerSet set, ValueRange args, bool withElseRegion);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, IntegerSet set, ValueRange args, bool withElseRegion);
  static AffineIfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, IntegerSet set, ValueRange args, bool withElseRegion);
  static AffineIfOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, IntegerSet set, ValueRange args, bool withElseRegion);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  static StringRef getConditionAttrStrName() { return "condition"; }

  IntegerSet getIntegerSet();
  void setIntegerSet(IntegerSet newSet);

  /// Sets the integer set with its operands.
  void setConditional(IntegerSet set, ValueRange operands);

  /// Returns true if an else block exists.
  bool hasElse() { return !getElseRegion().empty(); }

  Block *getThenBlock() {
    assert(!getThenRegion().empty() && "Unexpected empty 'then' region.");
    return &getThenRegion().front();
  }

  Block *getElseBlock() {
    assert(hasElse() && "Empty 'else' region.");
    return &getElseRegion().front();
  }

  OpBuilder getThenBodyBuilder() {
    assert(!getThenRegion().empty() && "Unexpected empty 'then' region.");
    Block &body = getThenRegion().front();
    return OpBuilder(&body, std::prev(body.end()));
  }
  OpBuilder getElseBodyBuilder() {
    assert(hasElse() && "No 'else' block");
    Block &body = getElseRegion().front();
    return OpBuilder(&body, std::prev(body.end()));
  }
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineIfOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineLinearizeIndexOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineLinearizeIndexOpGenericAdaptorBase {
public:
  struct Properties {
    using static_basisTy = ::mlir::DenseI64ArrayAttr;
    static_basisTy static_basis;

    auto getStaticBasis() const {
      auto &propStorage = this->static_basis;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticBasis(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_basis = propValue;
    }
    using disjointTy = bool;
    disjointTy disjoint = false;
    bool getDisjoint() const {
      auto &propStorage = this->disjoint;
      return propStorage;
    }
    void setDisjoint(bool propValue) {
      auto &propStorage = this->disjoint;
      propStorage = propValue;
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
        rhs.static_basis == this->static_basis &&
        rhs.disjoint == this->disjoint &&
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
  AffineLinearizeIndexOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.linearize_index", odsAttrs.getContext());
  }

  AffineLinearizeIndexOpGenericAdaptorBase(AffineLinearizeIndexOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  bool getDisjoint() {
    return getProperties().getDisjoint();
  }

  ::mlir::DenseI64ArrayAttr getStaticBasisAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_basis);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticBasis();
};

} // namespace detail
template <typename RangeT>
class AffineLinearizeIndexOpGenericAdaptor : public detail::AffineLinearizeIndexOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineLinearizeIndexOpGenericAdaptorBase;
  static constexpr int odsIndex_multi_index = 0;
  static constexpr int odsIndex_dynamic_basis = 1;
public:
  AffineLinearizeIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineLinearizeIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineLinearizeIndexOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineLinearizeIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : AffineLinearizeIndexOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineLinearizeIndexOpGenericAdaptor(RangeT values, const AffineLinearizeIndexOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineLinearizeIndexOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineLinearizeIndexOp>>>
  AffineLinearizeIndexOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getMultiIndex() {
    return getODSOperands(0);
  }

  RangeT getDynamicBasis() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AffineLinearizeIndexOpAdaptor : public AffineLinearizeIndexOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineLinearizeIndexOpGenericAdaptor::AffineLinearizeIndexOpGenericAdaptor;
  AffineLinearizeIndexOpAdaptor(AffineLinearizeIndexOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineLinearizeIndexOp : public ::mlir::Op<AffineLinearizeIndexOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineLinearizeIndexOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineLinearizeIndexOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_multi_index = 0;
  static constexpr int odsIndex_dynamic_basis = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("static_basis"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getStaticBasisAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getStaticBasisAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.linearize_index");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getMultiIndex() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getDynamicBasis() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getMultiIndexMutable();
  ::mlir::MutableOperandRange getDynamicBasisMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getLinearIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
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
  bool getDisjoint() {
    return getProperties().getDisjoint();
  }

  void setDisjoint(bool newDisjoint) {
    getProperties().setDisjoint(newDisjoint);
  }

  ::mlir::DenseI64ArrayAttr getStaticBasisAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().static_basis);
  }

  ::llvm::ArrayRef<int64_t> getStaticBasis();
  void setStaticBasisAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_basis = attr;
  }

  void setStaticBasis(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange multi_index, ValueRange basis, bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange multi_index, ValueRange basis, bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange multi_index, ValueRange basis, bool disjoint = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange multi_index, ArrayRef<OpFoldResult> basis, bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange multi_index, ArrayRef<OpFoldResult> basis, bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange multi_index, ArrayRef<OpFoldResult> basis, bool disjoint = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange multi_index, ArrayRef<int64_t> basis, bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange multi_index, ArrayRef<int64_t> basis, bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange multi_index, ArrayRef<int64_t> basis, bool disjoint = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type linear_index, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type linear_index, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type linear_index, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis, /*optional*/bool disjoint = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis, /*optional*/bool disjoint = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::mlir::DenseI64ArrayAttr static_basis, /*optional*/bool disjoint = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type linear_index, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type linear_index, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type linear_index, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis, /*optional*/bool disjoint = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis, /*optional*/bool disjoint = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis, /*optional*/bool disjoint = false);
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange multi_index, ::mlir::ValueRange dynamic_basis, ::llvm::ArrayRef<int64_t> static_basis, /*optional*/bool disjoint = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineLinearizeIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineLinearizeIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  /// Return true if the basis includes a bound on the first index input.
  bool hasOuterBound() {
    return getMultiIndex().size() == getStaticBasis().size();
  }

  /// Return a vector with all the static and dynamic basis values.
  SmallVector<OpFoldResult> getMixedBasis() {
    OpBuilder builder(getContext());
    return ::mlir::getMixedValues(getStaticBasis(), getDynamicBasis(), builder);
  }

  /// Return a vector that contains the basis of the operation, removing
  /// the outer bound if one is present.
  SmallVector<OpFoldResult> getEffectiveBasis();

  /// Return the vector with one basis element per index operand of the operation.
  /// If there is no outer bound specified, the leading entry of this basis will be
  /// nullptr.
  SmallVector<OpFoldResult> getPaddedBasis();
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineLinearizeIndexOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineLoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineLoadOpGenericAdaptorBase {
public:
  struct Properties {
    using mapTy = ::mlir::AffineMapAttr;
    mapTy map;

    auto getMap() const {
      auto &propStorage = this->map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setMap(const ::mlir::AffineMapAttr &propValue) {
      this->map = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.map == this->map &&
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
  AffineLoadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.load", odsAttrs.getContext());
  }

  AffineLoadOpGenericAdaptorBase(AffineLoadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
    return attr;
  }

  ::mlir::AffineMap getMap();
};

} // namespace detail
template <typename RangeT>
class AffineLoadOpGenericAdaptor : public detail::AffineLoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineLoadOpGenericAdaptorBase;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_indices = 1;
public:
  AffineLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineLoadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineLoadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineLoadOpGenericAdaptor(RangeT values, const AffineLoadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineLoadOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineLoadOp>>>
  AffineLoadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AffineLoadOpAdaptor : public AffineLoadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineLoadOpGenericAdaptor::AffineLoadOpGenericAdaptor;
  AffineLoadOpAdaptor(AffineLoadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineLoadOp : public ::mlir::Op<AffineLoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::affine::AffineReadOpInterface::Trait, ::mlir::affine::AffineMapAccessInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineLoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineLoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::affine::AffineReadOpInterface::Trait<AffineLoadOp>::getMemRef;
  using ::mlir::affine::AffineReadOpInterface::Trait<AffineLoadOp>::getMemRefType;
  using ::mlir::affine::AffineReadOpInterface::Trait<AffineLoadOp>::getMapOperands;
  using ::mlir::affine::AffineReadOpInterface::Trait<AffineLoadOp>::getAffineMap;
  using ::mlir::affine::AffineReadOpInterface::Trait<AffineLoadOp>::getValue;
  using ::mlir::affine::AffineMapAccessInterface::Trait<AffineLoadOp>::getAffineMapAttrForMemRef;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("map")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMapAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.load");
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
  ::mlir::AffineMapAttr getMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
  }

  ::mlir::AffineMap getMap();
  void setMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().map = attr;
  }

  void setMap(::mlir::AffineMap attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, AffineMap map, ValueRange operands);
  static AffineLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, AffineMap map, ValueRange operands);
  static AffineLoadOp create(::mlir::ImplicitLocOpBuilder &builder, AffineMap map, ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value memref, ValueRange indices = {});
  static AffineLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value memref, ValueRange indices = {});
  static AffineLoadOp create(::mlir::ImplicitLocOpBuilder &builder, Value memref, ValueRange indices = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value memref, AffineMap map, ValueRange mapOperands);
  static AffineLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value memref, AffineMap map, ValueRange mapOperands);
  static AffineLoadOp create(::mlir::ImplicitLocOpBuilder &builder, Value memref, AffineMap map, ValueRange mapOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static AffineLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static AffineLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static AffineLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static AffineLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static AffineLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static AffineLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static AffineLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static AffineLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
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
  /// Returns the operand index of the memref.
  unsigned getMemRefOperandIndex() { return 0; }

  void setMemRef(Value value) { setOperand(getMemRefOperandIndex(), value); }

  /// Returns the affine map used to index the memref for this operation.
  AffineMapAttr getAffineMapAttr() {
    return getProperties().map;
  }

  static StringRef getMapAttrStrName() { return "map"; }
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineLoadOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineMaxOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineMaxOpGenericAdaptorBase {
public:
  struct Properties {
    using mapTy = ::mlir::AffineMapAttr;
    mapTy map;

    auto getMap() const {
      auto &propStorage = this->map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setMap(const ::mlir::AffineMapAttr &propValue) {
      this->map = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.map == this->map &&
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
  AffineMaxOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.max", odsAttrs.getContext());
  }

  AffineMaxOpGenericAdaptorBase(AffineMaxOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
    return attr;
  }

  ::mlir::AffineMap getMap();
};

} // namespace detail
template <typename RangeT>
class AffineMaxOpGenericAdaptor : public detail::AffineMaxOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineMaxOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  AffineMaxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineMaxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineMaxOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineMaxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineMaxOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineMaxOpGenericAdaptor(RangeT values, const AffineMaxOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineMaxOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineMaxOp>>>
  AffineMaxOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AffineMaxOpAdaptor : public AffineMaxOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineMaxOpGenericAdaptor::AffineMaxOpGenericAdaptor;
  AffineMaxOpAdaptor(AffineMaxOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineMaxOp : public ::mlir::Op<AffineMaxOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineMaxOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineMaxOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("map")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMapAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.max");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::AffineMapAttr getMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
  }

  ::mlir::AffineMap getMap();
  void setMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().map = attr;
  }

  void setMap(::mlir::AffineMap attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineMaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineMaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineMaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineMaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineMaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineMaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineMaxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineMaxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
  static StringRef getMapAttrStrName() { return "map"; }
  AffineMap getAffineMap() { return getMap(); }
  ValueRange getMapOperands() { return getOperands(); }
  ValueRange getDimOperands() {
    return OperandRange{getOperands().begin(),
                        getOperands().begin() + getMap().getNumDims()};
  }
  ValueRange getSymbolOperands() {
    return OperandRange{getOperands().begin() + getMap().getNumDims(),
                        getOperands().end()};
  }
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineMaxOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineMinOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineMinOpGenericAdaptorBase {
public:
  struct Properties {
    using mapTy = ::mlir::AffineMapAttr;
    mapTy map;

    auto getMap() const {
      auto &propStorage = this->map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setMap(const ::mlir::AffineMapAttr &propValue) {
      this->map = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.map == this->map &&
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
  AffineMinOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.min", odsAttrs.getContext());
  }

  AffineMinOpGenericAdaptorBase(AffineMinOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
    return attr;
  }

  ::mlir::AffineMap getMap();
};

} // namespace detail
template <typename RangeT>
class AffineMinOpGenericAdaptor : public detail::AffineMinOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineMinOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  AffineMinOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineMinOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineMinOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineMinOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineMinOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineMinOpGenericAdaptor(RangeT values, const AffineMinOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineMinOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineMinOp>>>
  AffineMinOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AffineMinOpAdaptor : public AffineMinOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineMinOpGenericAdaptor::AffineMinOpGenericAdaptor;
  AffineMinOpAdaptor(AffineMinOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineMinOp : public ::mlir::Op<AffineMinOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineMinOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineMinOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("map")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMapAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.min");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::AffineMapAttr getMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
  }

  ::mlir::AffineMap getMap();
  void setMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().map = attr;
  }

  void setMap(::mlir::AffineMap attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::AffineMapAttr map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static AffineMinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::AffineMap map, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineMinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineMinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineMinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineMinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineMinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineMinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineMinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineMinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
  static StringRef getMapAttrStrName() { return "map"; }
  AffineMap getAffineMap() { return getMap(); }
  ValueRange getMapOperands() { return getOperands(); }
  ValueRange getDimOperands() {
    return OperandRange{getOperands().begin(),
                        getOperands().begin() + getMap().getNumDims()};
  }
  ValueRange getSymbolOperands() {
    return OperandRange{getOperands().begin() + getMap().getNumDims(),
                        getOperands().end()};
  }
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineMinOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineParallelOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineParallelOpGenericAdaptorBase {
public:
  struct Properties {
    using lowerBoundsGroupsTy = ::mlir::DenseIntElementsAttr;
    lowerBoundsGroupsTy lowerBoundsGroups;

    auto getLowerBoundsGroups() const {
      auto &propStorage = this->lowerBoundsGroups;
      return ::llvm::cast<::mlir::DenseIntElementsAttr>(propStorage);
    }
    void setLowerBoundsGroups(const ::mlir::DenseIntElementsAttr &propValue) {
      this->lowerBoundsGroups = propValue;
    }
    using lowerBoundsMapTy = ::mlir::AffineMapAttr;
    lowerBoundsMapTy lowerBoundsMap;

    auto getLowerBoundsMap() const {
      auto &propStorage = this->lowerBoundsMap;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setLowerBoundsMap(const ::mlir::AffineMapAttr &propValue) {
      this->lowerBoundsMap = propValue;
    }
    using reductionsTy = ::mlir::ArrayAttr;
    reductionsTy reductions;

    auto getReductions() const {
      auto &propStorage = this->reductions;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setReductions(const ::mlir::ArrayAttr &propValue) {
      this->reductions = propValue;
    }
    using stepsTy = ::mlir::ArrayAttr;
    stepsTy steps;

    auto getSteps() const {
      auto &propStorage = this->steps;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setSteps(const ::mlir::ArrayAttr &propValue) {
      this->steps = propValue;
    }
    using upperBoundsGroupsTy = ::mlir::DenseIntElementsAttr;
    upperBoundsGroupsTy upperBoundsGroups;

    auto getUpperBoundsGroups() const {
      auto &propStorage = this->upperBoundsGroups;
      return ::llvm::cast<::mlir::DenseIntElementsAttr>(propStorage);
    }
    void setUpperBoundsGroups(const ::mlir::DenseIntElementsAttr &propValue) {
      this->upperBoundsGroups = propValue;
    }
    using upperBoundsMapTy = ::mlir::AffineMapAttr;
    upperBoundsMapTy upperBoundsMap;

    auto getUpperBoundsMap() const {
      auto &propStorage = this->upperBoundsMap;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setUpperBoundsMap(const ::mlir::AffineMapAttr &propValue) {
      this->upperBoundsMap = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.lowerBoundsGroups == this->lowerBoundsGroups &&
        rhs.lowerBoundsMap == this->lowerBoundsMap &&
        rhs.reductions == this->reductions &&
        rhs.steps == this->steps &&
        rhs.upperBoundsGroups == this->upperBoundsGroups &&
        rhs.upperBoundsMap == this->upperBoundsMap &&
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
  AffineParallelOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.parallel", odsAttrs.getContext());
  }

  AffineParallelOpGenericAdaptorBase(AffineParallelOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getReductionsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().reductions);
    return attr;
  }

  ::mlir::ArrayAttr getReductions();
  ::mlir::AffineMapAttr getLowerBoundsMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().lowerBoundsMap);
    return attr;
  }

  ::mlir::AffineMap getLowerBoundsMap();
  ::mlir::DenseIntElementsAttr getLowerBoundsGroupsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseIntElementsAttr>(getProperties().lowerBoundsGroups);
    return attr;
  }

  ::mlir::DenseIntElementsAttr getLowerBoundsGroups();
  ::mlir::AffineMapAttr getUpperBoundsMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().upperBoundsMap);
    return attr;
  }

  ::mlir::AffineMap getUpperBoundsMap();
  ::mlir::DenseIntElementsAttr getUpperBoundsGroupsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseIntElementsAttr>(getProperties().upperBoundsGroups);
    return attr;
  }

  ::mlir::DenseIntElementsAttr getUpperBoundsGroups();
  ::mlir::ArrayAttr getStepsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().steps);
    return attr;
  }

  ::llvm::SmallVector<int64_t, 8> getSteps();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class AffineParallelOpGenericAdaptor : public detail::AffineParallelOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineParallelOpGenericAdaptorBase;
  static constexpr int odsIndex_mapOperands = 0;
public:
  AffineParallelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineParallelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineParallelOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineParallelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineParallelOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineParallelOpGenericAdaptor(RangeT values, const AffineParallelOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineParallelOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineParallelOp>>>
  AffineParallelOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getMapOperands() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AffineParallelOpAdaptor : public AffineParallelOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineParallelOpGenericAdaptor::AffineParallelOpGenericAdaptor;
  AffineParallelOpAdaptor(AffineParallelOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineParallelOp : public ::mlir::Op<AffineParallelOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<AffineYieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::RecursivelySpeculatableImplTrait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::LoopLikeOpInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineParallelOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineParallelOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_mapOperands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::isDefinedOutsideOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::moveOutOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::promoteIfSingleIteration;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::getLoopInductionVars;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::getLoopLowerBounds;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::getLoopSteps;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::getLoopUpperBounds;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::getInitsMutable;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::getRegionIterArgs;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::getYieldedValuesMutable;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::getLoopResults;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::replaceWithAdditionalYields;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::getStaticTripCount;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::isValidInductionVarType;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::setLoopLowerBounds;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::setLoopUpperBounds;
  using ::mlir::LoopLikeOpInterface::Trait<AffineParallelOp>::setLoopSteps;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("lowerBoundsGroups"), ::llvm::StringRef("lowerBoundsMap"), ::llvm::StringRef("reductions"), ::llvm::StringRef("steps"), ::llvm::StringRef("upperBoundsGroups"), ::llvm::StringRef("upperBoundsMap")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLowerBoundsGroupsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLowerBoundsGroupsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLowerBoundsMapAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLowerBoundsMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getReductionsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getReductionsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getStepsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getStepsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getUpperBoundsGroupsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getUpperBoundsGroupsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getUpperBoundsMapAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getUpperBoundsMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.parallel");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getMapOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getMapOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
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
  ::mlir::ArrayAttr getReductionsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().reductions);
  }

  ::mlir::ArrayAttr getReductions();
  ::mlir::AffineMapAttr getLowerBoundsMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().lowerBoundsMap);
  }

  ::mlir::AffineMap getLowerBoundsMap();
  ::mlir::DenseIntElementsAttr getLowerBoundsGroupsAttr() {
    return ::llvm::cast<::mlir::DenseIntElementsAttr>(getProperties().lowerBoundsGroups);
  }

  ::mlir::DenseIntElementsAttr getLowerBoundsGroups();
  ::mlir::AffineMapAttr getUpperBoundsMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().upperBoundsMap);
  }

  ::mlir::AffineMap getUpperBoundsMap();
  ::mlir::DenseIntElementsAttr getUpperBoundsGroupsAttr() {
    return ::llvm::cast<::mlir::DenseIntElementsAttr>(getProperties().upperBoundsGroups);
  }

  ::mlir::DenseIntElementsAttr getUpperBoundsGroups();
  ::mlir::ArrayAttr getStepsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().steps);
  }

  ::llvm::SmallVector<int64_t, 8> getSteps();
  void setReductionsAttr(::mlir::ArrayAttr attr) {
    getProperties().reductions = attr;
  }

  void setLowerBoundsMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().lowerBoundsMap = attr;
  }

  void setLowerBoundsMap(::mlir::AffineMap attrValue);
  void setLowerBoundsGroupsAttr(::mlir::DenseIntElementsAttr attr) {
    getProperties().lowerBoundsGroups = attr;
  }

  void setUpperBoundsMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().upperBoundsMap = attr;
  }

  void setUpperBoundsMap(::mlir::AffineMap attrValue);
  void setUpperBoundsGroupsAttr(::mlir::DenseIntElementsAttr attr) {
    getProperties().upperBoundsGroups = attr;
  }

  void setStepsAttr(::mlir::ArrayAttr attr) {
    getProperties().steps = attr;
  }

  void setSteps(::llvm::SmallVector<int64_t, 8> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, ArrayRef<arith::AtomicRMWKind> reductions, ArrayRef<int64_t> ranges);
  static AffineParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, ArrayRef<arith::AtomicRMWKind> reductions, ArrayRef<int64_t> ranges);
  static AffineParallelOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, ArrayRef<arith::AtomicRMWKind> reductions, ArrayRef<int64_t> ranges);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, ArrayRef<arith::AtomicRMWKind> reductions, ArrayRef<AffineMap> lbMaps, ValueRange lbArgs, ArrayRef<AffineMap> ubMaps, ValueRange ubArgs, ArrayRef<int64_t> steps);
  static AffineParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, ArrayRef<arith::AtomicRMWKind> reductions, ArrayRef<AffineMap> lbMaps, ValueRange lbArgs, ArrayRef<AffineMap> ubMaps, ValueRange ubArgs, ArrayRef<int64_t> steps);
  static AffineParallelOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, ArrayRef<arith::AtomicRMWKind> reductions, ArrayRef<AffineMap> lbMaps, ValueRange lbArgs, ArrayRef<AffineMap> ubMaps, ValueRange ubArgs, ArrayRef<int64_t> steps);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ArrayAttr reductions, ::mlir::AffineMapAttr lowerBoundsMap, ::mlir::DenseIntElementsAttr lowerBoundsGroups, ::mlir::AffineMapAttr upperBoundsMap, ::mlir::DenseIntElementsAttr upperBoundsGroups, ::mlir::ArrayAttr steps, ::mlir::ValueRange mapOperands);
  static AffineParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ArrayAttr reductions, ::mlir::AffineMapAttr lowerBoundsMap, ::mlir::DenseIntElementsAttr lowerBoundsGroups, ::mlir::AffineMapAttr upperBoundsMap, ::mlir::DenseIntElementsAttr upperBoundsGroups, ::mlir::ArrayAttr steps, ::mlir::ValueRange mapOperands);
  static AffineParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ArrayAttr reductions, ::mlir::AffineMapAttr lowerBoundsMap, ::mlir::DenseIntElementsAttr lowerBoundsGroups, ::mlir::AffineMapAttr upperBoundsMap, ::mlir::DenseIntElementsAttr upperBoundsGroups, ::mlir::ArrayAttr steps, ::mlir::ValueRange mapOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ArrayAttr reductions, ::mlir::AffineMap lowerBoundsMap, ::mlir::DenseIntElementsAttr lowerBoundsGroups, ::mlir::AffineMap upperBoundsMap, ::mlir::DenseIntElementsAttr upperBoundsGroups, ::llvm::SmallVector<int64_t, 8> steps, ::mlir::ValueRange mapOperands);
  static AffineParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ArrayAttr reductions, ::mlir::AffineMap lowerBoundsMap, ::mlir::DenseIntElementsAttr lowerBoundsGroups, ::mlir::AffineMap upperBoundsMap, ::mlir::DenseIntElementsAttr upperBoundsGroups, ::llvm::SmallVector<int64_t, 8> steps, ::mlir::ValueRange mapOperands);
  static AffineParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ArrayAttr reductions, ::mlir::AffineMap lowerBoundsMap, ::mlir::DenseIntElementsAttr lowerBoundsGroups, ::mlir::AffineMap upperBoundsMap, ::mlir::DenseIntElementsAttr upperBoundsGroups, ::llvm::SmallVector<int64_t, 8> steps, ::mlir::ValueRange mapOperands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  ::llvm::SmallVector<::mlir::Region *> getLoopRegions();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  /// Get the number of dimensions.
  unsigned getNumDims();

  /// Get ranges as constants, may fail in dynamic case.
  std::optional<SmallVector<int64_t, 8>> getConstantRanges();

  Block *getBody();
  OpBuilder getBodyBuilder();
  MutableArrayRef<BlockArgument> getIVs() {
    return getBody()->getArguments();
  }

  /// Returns elements of the loop lower bound.
  AffineMap getLowerBoundMap(unsigned pos);
  operand_range getLowerBoundsOperands();
  AffineValueMap getLowerBoundsValueMap();

  /// Sets elements of the loop lower bound.
  void setLowerBounds(ValueRange operands, AffineMap map);

  /// Returns elements of the loop upper bound.
  AffineMap getUpperBoundMap(unsigned pos);
  operand_range getUpperBoundsOperands();
  AffineValueMap getUpperBoundsValueMap();

  /// Sets elements of the loop upper bound.
  void setUpperBounds(ValueRange operands, AffineMap map);

  void setSteps(ArrayRef<int64_t> newSteps);

  /// Returns attribute names to use in op construction. Not expected to be
  /// used directly.
  static StringRef getReductionsAttrStrName() { return "reductions"; }
  static StringRef getLowerBoundsMapAttrStrName() { return "lowerBoundsMap"; }
  static StringRef getLowerBoundsGroupsAttrStrName() {
    return "lowerBoundsGroups";
  }
  static StringRef getUpperBoundsMapAttrStrName() { return "upperBoundsMap"; }
  static StringRef getUpperBoundsGroupsAttrStrName() {
    return "upperBoundsGroups";
  }
  static StringRef getStepsAttrStrName() { return "steps"; }

  /// Returns `true` if the loop bounds have min/max expressions.
  bool hasMinMaxBounds() {
    return getLowerBoundsMap().getNumResults() != getNumDims() ||
           getUpperBoundsMap().getNumResults() != getNumDims();
  }
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineParallelOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffinePrefetchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffinePrefetchOpGenericAdaptorBase {
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
    using mapTy = ::mlir::AffineMapAttr;
    mapTy map;

    auto getMap() const {
      auto &propStorage = this->map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setMap(const ::mlir::AffineMapAttr &propValue) {
      this->map = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.isDataCache == this->isDataCache &&
        rhs.isWrite == this->isWrite &&
        rhs.localityHint == this->localityHint &&
        rhs.map == this->map &&
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
  AffinePrefetchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.prefetch", odsAttrs.getContext());
  }

  AffinePrefetchOpGenericAdaptorBase(AffinePrefetchOp op);

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
  ::mlir::AffineMapAttr getMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
    return attr;
  }

  ::mlir::AffineMap getMap();
};

} // namespace detail
template <typename RangeT>
class AffinePrefetchOpGenericAdaptor : public detail::AffinePrefetchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffinePrefetchOpGenericAdaptorBase;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_indices = 1;
public:
  AffinePrefetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffinePrefetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffinePrefetchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffinePrefetchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffinePrefetchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffinePrefetchOpGenericAdaptor(RangeT values, const AffinePrefetchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffinePrefetchOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffinePrefetchOp>>>
  AffinePrefetchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AffinePrefetchOpAdaptor : public AffinePrefetchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffinePrefetchOpGenericAdaptor::AffinePrefetchOpGenericAdaptor;
  AffinePrefetchOpAdaptor(AffinePrefetchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffinePrefetchOp : public ::mlir::Op<AffinePrefetchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::affine::AffineMapAccessInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffinePrefetchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffinePrefetchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::affine::AffineMapAccessInterface::Trait<AffinePrefetchOp>::getAffineMapAttrForMemRef;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("isDataCache"), ::llvm::StringRef("isWrite"), ::llvm::StringRef("localityHint"), ::llvm::StringRef("map")};
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

  ::mlir::StringAttr getMapAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.prefetch");
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
  ::mlir::AffineMapAttr getMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
  }

  ::mlir::AffineMap getMap();
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
  void setMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().map = attr;
  }

  void setMap(::mlir::AffineMap attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value memref, AffineMap map, ArrayRef<Value> mapOperands, bool isWrite, unsigned localityHint, bool isDataCache);
  static AffinePrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value memref, AffineMap map, ArrayRef<Value> mapOperands, bool isWrite, unsigned localityHint, bool isDataCache);
  static AffinePrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, Value memref, AffineMap map, ArrayRef<Value> mapOperands, bool isWrite, unsigned localityHint, bool isDataCache);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache, ::mlir::AffineMapAttr map);
  static AffinePrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache, ::mlir::AffineMapAttr map);
  static AffinePrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache, ::mlir::AffineMapAttr map);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache, ::mlir::AffineMapAttr map);
  static AffinePrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache, ::mlir::AffineMapAttr map);
  static AffinePrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::BoolAttr isWrite, ::mlir::IntegerAttr localityHint, ::mlir::BoolAttr isDataCache, ::mlir::AffineMapAttr map);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache, ::mlir::AffineMap map);
  static AffinePrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache, ::mlir::AffineMap map);
  static AffinePrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache, ::mlir::AffineMap map);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache, ::mlir::AffineMap map);
  static AffinePrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache, ::mlir::AffineMap map);
  static AffinePrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, bool isWrite, uint32_t localityHint, bool isDataCache, ::mlir::AffineMap map);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffinePrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffinePrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffinePrefetchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffinePrefetchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  MemRefType getMemRefType() {
    return ::llvm::cast<MemRefType>(getMemref().getType());
  }

  /// Returns the affine map used to index the memref for this operation.
  AffineMap getAffineMap() { return getAffineMapAttr().getValue(); }
  AffineMapAttr getAffineMapAttr() {
    return getProperties().map;
  }

  /// Implements the AffineMapAccessInterface.
  /// Returns the AffineMapAttr associated with 'memref'.
  NamedAttribute getAffineMapAttrForMemRef(Value mref) {
    assert(mref == getMemref() &&
           "Expected mref argument to match memref operand");
    return {StringAttr::get(getContext(), getMapAttrStrName()),
      getAffineMapAttr()};
  }

  /// Get affine map operands.
  operand_range getMapOperands() {
    return {operand_begin() + 1, operand_end()};
  }

  static StringRef getMapAttrStrName() { return "map"; }
  static StringRef getLocalityHintAttrStrName() { return "localityHint"; }
  static StringRef getIsWriteAttrStrName() { return "isWrite"; }
  static StringRef getIsDataCacheAttrStrName() { return "isDataCache"; }
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffinePrefetchOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineStoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineStoreOpGenericAdaptorBase {
public:
  struct Properties {
    using mapTy = ::mlir::AffineMapAttr;
    mapTy map;

    auto getMap() const {
      auto &propStorage = this->map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setMap(const ::mlir::AffineMapAttr &propValue) {
      this->map = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.map == this->map &&
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
  AffineStoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.store", odsAttrs.getContext());
  }

  AffineStoreOpGenericAdaptorBase(AffineStoreOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
    return attr;
  }

  ::mlir::AffineMap getMap();
};

} // namespace detail
template <typename RangeT>
class AffineStoreOpGenericAdaptor : public detail::AffineStoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineStoreOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_memref = 1;
  static constexpr int odsIndex_indices = 2;
public:
  AffineStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineStoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineStoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineStoreOpGenericAdaptor(RangeT values, const AffineStoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineStoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineStoreOp>>>
  AffineStoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AffineStoreOpAdaptor : public AffineStoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineStoreOpGenericAdaptor::AffineStoreOpGenericAdaptor;
  AffineStoreOpAdaptor(AffineStoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineStoreOp : public ::mlir::Op<AffineStoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::affine::AffineWriteOpInterface::Trait, ::mlir::affine::AffineMapAccessInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineStoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineStoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_memref = 1;
  static constexpr int odsIndex_indices = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineStoreOp>::getMemRef;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineStoreOp>::getMemRefType;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineStoreOp>::getMapOperands;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineStoreOp>::getAffineMap;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineStoreOp>::getValueToStore;
  using ::mlir::affine::AffineMapAccessInterface::Trait<AffineStoreOp>::getAffineMapAttrForMemRef;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("map")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMapAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.store");
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
  ::mlir::AffineMapAttr getMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
  }

  ::mlir::AffineMap getMap();
  void setMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().map = attr;
  }

  void setMap(::mlir::AffineMap attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value memref, ValueRange indices);
  static AffineStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value memref, ValueRange indices);
  static AffineStoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value memref, ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value memref, AffineMap map, ValueRange mapOperands);
  static AffineStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value memref, AffineMap map, ValueRange mapOperands);
  static AffineStoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value memref, AffineMap map, ValueRange mapOperands);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
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
  /// Returns the operand index of the value to be stored.
  unsigned getStoredValOperandIndex() { return 0; }

  /// Returns the operand index of the memref.
  unsigned getMemRefOperandIndex() { return 1; }

  void setMemRef(Value value) { setOperand(getMemRefOperandIndex(), value); }

  /// Returns the affine map used to index the memref for this operation.
  AffineMapAttr getAffineMapAttr() {
    return getProperties().map;
  }

  static StringRef getMapAttrStrName() { return "map"; }
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineStoreOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineVectorLoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineVectorLoadOpGenericAdaptorBase {
public:
  struct Properties {
    using mapTy = ::mlir::AffineMapAttr;
    mapTy map;

    auto getMap() const {
      auto &propStorage = this->map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setMap(const ::mlir::AffineMapAttr &propValue) {
      this->map = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.map == this->map &&
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
  AffineVectorLoadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.vector_load", odsAttrs.getContext());
  }

  AffineVectorLoadOpGenericAdaptorBase(AffineVectorLoadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
    return attr;
  }

  ::mlir::AffineMap getMap();
};

} // namespace detail
template <typename RangeT>
class AffineVectorLoadOpGenericAdaptor : public detail::AffineVectorLoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineVectorLoadOpGenericAdaptorBase;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_indices = 1;
public:
  AffineVectorLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineVectorLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineVectorLoadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineVectorLoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineVectorLoadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineVectorLoadOpGenericAdaptor(RangeT values, const AffineVectorLoadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineVectorLoadOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineVectorLoadOp>>>
  AffineVectorLoadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AffineVectorLoadOpAdaptor : public AffineVectorLoadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineVectorLoadOpGenericAdaptor::AffineVectorLoadOpGenericAdaptor;
  AffineVectorLoadOpAdaptor(AffineVectorLoadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineVectorLoadOp : public ::mlir::Op<AffineVectorLoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::VectorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::affine::AffineReadOpInterface::Trait, ::mlir::affine::AffineMapAccessInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineVectorLoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineVectorLoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::affine::AffineReadOpInterface::Trait<AffineVectorLoadOp>::getMemRef;
  using ::mlir::affine::AffineReadOpInterface::Trait<AffineVectorLoadOp>::getMemRefType;
  using ::mlir::affine::AffineReadOpInterface::Trait<AffineVectorLoadOp>::getMapOperands;
  using ::mlir::affine::AffineReadOpInterface::Trait<AffineVectorLoadOp>::getAffineMap;
  using ::mlir::affine::AffineReadOpInterface::Trait<AffineVectorLoadOp>::getValue;
  using ::mlir::affine::AffineMapAccessInterface::Trait<AffineVectorLoadOp>::getAffineMapAttrForMemRef;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("map")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMapAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.vector_load");
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
  ::mlir::AffineMapAttr getMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
  }

  ::mlir::AffineMap getMap();
  void setMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().map = attr;
  }

  void setMap(::mlir::AffineMap attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType resultType, AffineMap map, ValueRange operands);
  static AffineVectorLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType resultType, AffineMap map, ValueRange operands);
  static AffineVectorLoadOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType resultType, AffineMap map, ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType resultType, Value memref, ValueRange indices = {});
  static AffineVectorLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType resultType, Value memref, ValueRange indices = {});
  static AffineVectorLoadOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType resultType, Value memref, ValueRange indices = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, VectorType resultType, Value memref, AffineMap map, ValueRange mapOperands);
  static AffineVectorLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, VectorType resultType, Value memref, AffineMap map, ValueRange mapOperands);
  static AffineVectorLoadOp create(::mlir::ImplicitLocOpBuilder &builder, VectorType resultType, Value memref, AffineMap map, ValueRange mapOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static AffineVectorLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static AffineVectorLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static AffineVectorLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static AffineVectorLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMapAttr map);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static AffineVectorLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static AffineVectorLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static AffineVectorLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static AffineVectorLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memref, ::mlir::ValueRange indices, ::mlir::AffineMap map);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineVectorLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineVectorLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineVectorLoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineVectorLoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  /// Returns the operand index of the memref.
  unsigned getMemRefOperandIndex() { return 0; }

  void setMemRef(Value value) { setOperand(getMemRefOperandIndex(), value); }

  /// Returns the affine map used to index the memref for this operation.
  AffineMapAttr getAffineMapAttr() {
    return getProperties().map;
  }

  static StringRef getMapAttrStrName() { return "map"; }

  VectorType getVectorType() {
    return ::llvm::cast<VectorType>(getResult().getType());
  }
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineVectorLoadOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineVectorStoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineVectorStoreOpGenericAdaptorBase {
public:
  struct Properties {
    using mapTy = ::mlir::AffineMapAttr;
    mapTy map;

    auto getMap() const {
      auto &propStorage = this->map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setMap(const ::mlir::AffineMapAttr &propValue) {
      this->map = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.map == this->map &&
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
  AffineVectorStoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.vector_store", odsAttrs.getContext());
  }

  AffineVectorStoreOpGenericAdaptorBase(AffineVectorStoreOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
    return attr;
  }

  ::mlir::AffineMap getMap();
};

} // namespace detail
template <typename RangeT>
class AffineVectorStoreOpGenericAdaptor : public detail::AffineVectorStoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineVectorStoreOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_memref = 1;
  static constexpr int odsIndex_indices = 2;
public:
  AffineVectorStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineVectorStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineVectorStoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineVectorStoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineVectorStoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineVectorStoreOpGenericAdaptor(RangeT values, const AffineVectorStoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineVectorStoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineVectorStoreOp>>>
  AffineVectorStoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AffineVectorStoreOpAdaptor : public AffineVectorStoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineVectorStoreOpGenericAdaptor::AffineVectorStoreOpGenericAdaptor;
  AffineVectorStoreOpAdaptor(AffineVectorStoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineVectorStoreOp : public ::mlir::Op<AffineVectorStoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::affine::AffineWriteOpInterface::Trait, ::mlir::affine::AffineMapAccessInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineVectorStoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineVectorStoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_memref = 1;
  static constexpr int odsIndex_indices = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineVectorStoreOp>::getMemRef;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineVectorStoreOp>::getMemRefType;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineVectorStoreOp>::getMapOperands;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineVectorStoreOp>::getAffineMap;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineVectorStoreOp>::getValueToStore;
  using ::mlir::affine::AffineMapAccessInterface::Trait<AffineVectorStoreOp>::getAffineMapAttrForMemRef;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("map")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMapAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.vector_store");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::VectorType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::VectorType>>(*getODSOperands(0).begin());
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
  ::mlir::AffineMapAttr getMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
  }

  ::mlir::AffineMap getMap();
  void setMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().map = attr;
  }

  void setMap(::mlir::AffineMap attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value memref, ValueRange indices);
  static AffineVectorStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value memref, ValueRange indices);
  static AffineVectorStoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value memref, ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, Value memref, AffineMap map, ValueRange mapOperands);
  static AffineVectorStoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, Value memref, AffineMap map, ValueRange mapOperands);
  static AffineVectorStoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, Value memref, AffineMap map, ValueRange mapOperands);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  /// Returns the operand index of the value to be stored.
  unsigned getStoredValOperandIndex() { return 0; }

  /// Returns the operand index of the memref.
  unsigned getMemRefOperandIndex() { return 1; }

  void setMemRef(Value value) { setOperand(getMemRefOperandIndex(), value); }

  /// Returns the affine map used to index the memref for this operation.
  AffineMapAttr getAffineMapAttr() {
    return getProperties().map;
  }

  static StringRef getMapAttrStrName() { return "map"; }

  VectorType getVectorType() {
    return ::llvm::cast<VectorType>(getValue().getType());
  }
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineVectorStoreOp)

namespace mlir::affine {


//===----------------------------------------------------------------------===//
// ::mlir::affine::AffineYieldOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineYieldOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AffineYieldOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("affine.yield", odsAttrs.getContext());
  }

  AffineYieldOpGenericAdaptorBase(AffineYieldOp op);

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
class AffineYieldOpGenericAdaptor : public detail::AffineYieldOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineYieldOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  AffineYieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineYieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AffineYieldOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineYieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AffineYieldOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineYieldOpGenericAdaptor(RangeT values, const AffineYieldOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineYieldOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineYieldOp>>>
  AffineYieldOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AffineYieldOpAdaptor : public AffineYieldOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineYieldOpGenericAdaptor::AffineYieldOpGenericAdaptor;
  AffineYieldOpAdaptor(AffineYieldOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineYieldOp : public ::mlir::Op<AffineYieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::MemRefsNormalizable> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineYieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineYieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<AffineYieldOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("affine.yield");
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
  static AffineYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static AffineYieldOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static AffineYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands);
  static AffineYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::affine
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::affine::AffineYieldOp)


#endif // GET_OP_CLASSES

