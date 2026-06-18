/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SparseTensorOps.td                                                   *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::sparse_tensor {

/// Extracts an iteration space from a sparse tensor between certain levels
/// Extracts a `!sparse_tensor.iter_space` from a sparse tensor between
///       certain (consecutive) levels. For sparse levels, it is usually done by
///       loading a postion range from the underlying sparse tensor storage.
///       E.g., for a compressed level, the iteration space is extracted by
///       [pos[i], pos[i+1]) supposing the the parent iterator points at `i`.
/// 
///       `tensor`: the input sparse tensor that defines the iteration space.
///       `parentIter`: the iterator for the previous level, at which the iteration space
///       at the current levels will be extracted.
///       `loLvl`, `hiLvl`: the level range between [loLvl, hiLvl) in the input tensor that
///       the returned iteration space covers. `hiLvl - loLvl` defines the dimension of the
///       iteration space.
/// 
///       The type of returned the value is must be
///       `!sparse_tensor.iter_space<#INPUT_ENCODING, lvls = $loLvl to $hiLvl>`.
///       The returned iteration space can then be iterated over by
///       `sparse_tensor.iterate` operations to visit every stored element
///       (usually nonzeros) in the input sparse tensor.
/// 
///       Example:
///       ```mlir
///       // Extracts a 1-D iteration space from a COO tensor at level 1.
///       %space = sparse_tensor.iteration.extract_space %sp at %it1 lvls = 1
///         : tensor<4x8xf32, #COO>, !sparse_tensor.iterator<#COO, lvls = 0>
///        ->!sparse_tensor.iter_space<#COO, lvls = 1>
///       ```
class ExtractIterSpaceOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Extracts a value from a sparse tensor using an iterator.
/// The `sparse_tensor.extract_value` operation extracts the value
///       pointed to by a sparse iterator from a sparse tensor.
/// 
///       Example:
/// 
///       ```mlir
///       %val = sparse_tensor.extract_value %sp at %it
///            : tensor<?x?xf32, #CSR>, !sparse_tensor.iterator<#CSR, lvl = 1>
///       ```
class ExtractValOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Iterates over a sparse iteration space
/// The `sparse_tensor.iterate` operation represents a loop (nest) over
///       the provided iteration space extracted from a specific sparse tensor.
///       The operation defines an SSA value for a sparse iterator that points
///       to the current stored element in the sparse tensor and SSA values
///       for coordinates of the stored element. The coordinates are always
///       converted to `index` type despite of the underlying sparse tensor
///       storage. When coordinates are not used, the SSA values can be skipped
///       by `_` symbols, which usually leads to simpler generated code after
///       sparsification. For example:
/// 
///       ```mlir
///       // The coordinate for level 0 is not used when iterating over a 2-D
///       // iteration space.
///       %sparse_tensor.iterate %iterator in %space at(_, %crd_1)
///         : !sparse_tensor.iter_space<#CSR, lvls = 0 to 2>
///       ```
/// 
///       `sparse_tensor.iterate` can also operate on loop-carried variables.
///       It returns the final values after loop termination.
///       The initial values of the variables are passed as additional SSA operands
///       to the iterator SSA value and used coordinate SSA values mentioned
///       above. The operation region has an argument for the iterator, variadic
///       arguments for specified (used) coordiates and followed by one argument
///       for each loop-carried variable, representing the value of the variable
///       at the current iteration.
///       The body region must contain exactly one block that terminates with
///       `sparse_tensor.yield`.
/// 
///       The results of an `sparse_tensor.iterate` hold the final values after
///       the last iteration. If the `sparse_tensor.iterate` defines any values,
///       a yield must be explicitly present.
///       The number and types of the `sparse_tensor.iterate` results must match
///       the initial values in the iter_args binding and the yield operands.
/// 
/// 
///       A nested `sparse_tensor.iterate` example that prints all the coordinates
///       stored in the sparse input:
/// 
///       ```mlir
///       func.func @nested_iterate(%sp : tensor<4x8xf32, #COO>) {
///         // Iterates over the first level of %sp
///         %l1 = sparse_tensor.extract_iteration_space %sp lvls = 0
///             : tensor<4x8xf32, #COO> -> !sparse_tensor.iter_space<#COO, lvls = 0 to 1>
///         %r1 = sparse_tensor.iterate %it1 in %l1 at (%coord0)
///             : !sparse_tensor.iter_space<#COO, lvls = 0 to 1>  {
///           // Iterates over the second level of %sp
///           %l2 = sparse_tensor.extract_iteration_space %sp at %it1 lvls = 1
///               : tensor<4x8xf32, #COO>, !sparse_tensor.iterator<#COO, lvls = 0 to 1>
///              -> !sparse_tensor.iter_space<#COO, lvls = 1 to 2>
///           %r2 = sparse_tensor.iterate %it2 in %l2 at (coord1)
///               : !sparse_tensor.iter_space<#COO, lvls = 1 to 2>  {
///              vector.print %coord0 : index
///              vector.print %coord1 : index
///           }
///         }
///       }
/// 
///       ```
class IterateOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Returns a sparse tensor assembled from the given levels and values
/// Assembles the per-level position and coordinate arrays together with
///     the values arrays into a sparse tensor. The order and types of the
///     provided levels must be consistent with the actual storage layout of
///     the returned sparse tensor described below.
/// 
///     - `levels: [tensor<? x iType>, ...]`
///       supplies the sparse tensor position and coordinate arrays
///       of the sparse tensor for the corresponding level as specifed by
///       `sparse_tensor::StorageLayout`.
///     - `values : tensor<? x V>`
///       supplies the values array for the stored elements in the sparse tensor.
/// 
///     This operation can be used to assemble a sparse tensor from an
///     external source; e.g., by passing numpy arrays from Python. It
///     is the user's responsibility to provide input that can be correctly
///     interpreted by the sparsifier, which does not perform any sanity
///     test to verify data integrity.
/// 
///     Example:
/// 
///     ```mlir
///     %pos    = arith.constant dense<[0, 3]>                : tensor<2xindex>
///     %index  = arith.constant dense<[[0,0], [1,2], [1,3]]> : tensor<3x2xindex>
///     %values = arith.constant dense<[ 1.1,   2.2,   3.3 ]> : tensor<3xf64>
///     %s = sparse_tensor.assemble (%pos, %index), %values
///        : (tensor<2xindex>, tensor<3x2xindex>), tensor<3xf64> to tensor<3x4xf64, #COO>
///     // yields COO format |1.1, 0.0, 0.0, 0.0|
///     //     of 3x4 matrix |0.0, 0.0, 2.2, 3.3|
///     //                   |0.0, 0.0, 0.0, 0.0|
///     ```
class AssembleOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Binary set operation utilized within linalg.generic
/// Defines a computation within a `linalg.generic` operation that takes two
///       operands and executes one of the regions depending on whether both operands
///       or either operand is nonzero (i.e. stored explicitly in the sparse storage
///       format).
/// 
///       Three regions are defined for the operation and must appear in this order:
///       - overlap (elements present in both sparse tensors)
///       - left (elements only present in the left sparse tensor)
///       - right (element only present in the right sparse tensor)
/// 
///       Each region contains a single block describing the computation and result.
///       Every non-empty block must end with a sparse_tensor.yield and the return
///       type must match the type of `output`. The primary region's block has two
///       arguments, while the left and right region's block has only one argument.
/// 
///       A region may also be declared empty (i.e. `left={}`), indicating that the
///       region does not contribute to the output. For example, setting both
///       `left={}` and `right={}` is equivalent to the intersection of the two
///       inputs as only the overlap region will contribute values to the output.
/// 
///       As a convenience, there is also a special token `identity` which can be
///       used in place of the left or right region. This token indicates that
///       the return value is the input value (i.e. func(%x) => return %x).
///       As a practical example, setting `left=identity` and `right=identity`
///       would be equivalent to a union operation where non-overlapping values
///       in the inputs are copied to the output unchanged.
/// 
///       Due to the possibility of empty regions, i.e. lack of a value for certain
///       cases, the result of this operation may only feed directly into the output
///       of the `linalg.generic` operation or into into a custom reduction
///       `sparse_tensor.reduce` operation that follows in the same region.
/// 
///       Example of isEqual applied to intersecting elements only:
/// 
///       ```mlir
///       %C = tensor.empty(...)
///       %0 = linalg.generic #trait
///         ins(%A: tensor<?xf64, #SparseVector>,
///             %B: tensor<?xf64, #SparseVector>)
///         outs(%C: tensor<?xi8, #SparseVector>) {
///         ^bb0(%a: f64, %b: f64, %c: i8) :
///           %result = sparse_tensor.binary %a, %b : f64, f64 to i8
///             overlap={
///               ^bb0(%arg0: f64, %arg1: f64):
///                 %cmp = arith.cmpf "oeq", %arg0, %arg1 : f64
///                 %ret_i8 = arith.extui %cmp : i1 to i8
///                 sparse_tensor.yield %ret_i8 : i8
///             }
///             left={}
///             right={}
///           linalg.yield %result : i8
///       } -> tensor<?xi8, #SparseVector>
///       ```
/// 
///       Example of A+B in upper triangle, A-B in lower triangle:
/// 
///       ```mlir
///       %C = tensor.empty(...)
///       %1 = linalg.generic #trait
///         ins(%A: tensor<?x?xf64, #CSR>, %B: tensor<?x?xf64, #CSR>
///         outs(%C: tensor<?x?xf64, #CSR> {
///         ^bb0(%a: f64, %b: f64, %c: f64) :
///           %row = linalg.index 0 : index
///           %col = linalg.index 1 : index
///           %result = sparse_tensor.binary %a, %b : f64, f64 to f64
///             overlap={
///               ^bb0(%x: f64, %y: f64):
///                 %cmp = arith.cmpi "uge", %col, %row : index
///                 %upperTriangleResult = arith.addf %x, %y : f64
///                 %lowerTriangleResult = arith.subf %x, %y : f64
///                 %ret = arith.select %cmp, %upperTriangleResult, %lowerTriangleResult : f64
///                 sparse_tensor.yield %ret : f64
///             }
///             left=identity
///             right={
///               ^bb0(%y: f64):
///                 %cmp = arith.cmpi "uge", %col, %row : index
///                 %lowerTriangleResult = arith.negf %y : f64
///                 %ret = arith.select %cmp, %y, %lowerTriangleResult : f64
///                 sparse_tensor.yield %ret : f64
///             }
///           linalg.yield %result : f64
///       } -> tensor<?x?xf64, #CSR>
///       ```
/// 
///       Example of set difference. Returns a copy of A where its sparse structure
///       is *not* overlapped by B. The element type of B can be different than A
///       because we never use its values, only its sparse structure:
/// 
///       ```mlir
///       %C = tensor.empty(...)
///       %2 = linalg.generic #trait
///         ins(%A: tensor<?x?xf64, #CSR>, %B: tensor<?x?xi32, #CSR>
///         outs(%C: tensor<?x?xf64, #CSR> {
///         ^bb0(%a: f64, %b: i32, %c: f64) :
///           %result = sparse_tensor.binary %a, %b : f64, i32 to f64
///             overlap={}
///             left=identity
///             right={}
///           linalg.yield %result : f64
///       } -> tensor<?x?xf64, #CSR>
///       ```
class BinaryOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Co-iterates over a set of sparse iteration spaces
/// The `sparse_tensor.coiterate` operation represents a loop (nest) over
///       a set of iteration spaces. The operation can have multiple regions,
///       with each of them defining a case to compute a result at the current iterations.
///       The case condition is defined solely based on the pattern of specified iterators.
///       For example:
///       ```mlir
///       %ret = sparse_tensor.coiterate (%sp1, %sp2) at(%coord) iter_args(%arg = %init)
///            : (!sparse_tensor.iter_space<#CSR, lvls = 0>,
///               !sparse_tensor.iter_space<#COO, lvls = 0>)
///            -> index
///       case %it1, _ {
///         // %coord is specifed in space %sp1 but *NOT* specified in space %sp2.
///       }
///       case %it1, %it2 {
///         // %coord is specifed in *BOTH* spaces %sp1 and %sp2.
///       }
///       ```
/// 
///       `sparse_tensor.coiterate` can also operate on loop-carried variables.
///       It returns the final value for each loop-carried variable after loop termination.
///       The initial values of the variables are passed as additional SSA operands
///       to the iterator SSA value and used coordinate SSA values.
///       Each operation region has variadic arguments for specified (used), one argument
///       for each loop-carried variable, representing the value of the variable
///       at the current iteration, followed by a list of arguments for iterators.
///       The body region must contain exactly one block that terminates with
///       `sparse_tensor.yield`.
/// 
///       The results of an `sparse_tensor.coiterate` hold the final values after
///       the last iteration. If the `sparse_tensor.coiterate` defines any values,
///       a yield must be explicitly present in every region defined in the operation.
///       The number and types of the `sparse_tensor.coiterate` results must match
///       the initial values in the iter_args binding and the yield operands.
/// 
/// 
///       A `sparse_tensor.coiterate` example that does elementwise addition between two
///       sparse vectors.
/// 
/// 
///       ```mlir
///       %ret = sparse_tensor.coiterate (%sp1, %sp2) at(%coord) iter_args(%arg = %init)
///            : (!sparse_tensor.iter_space<#CSR, lvls = 0>,
///               !sparse_tensor.iter_space<#CSR, lvls = 0>)
///            -> tensor<?xindex, #CSR>
///       case %it1, _ {
///          // v = v1 + 0 = v1
///          %v1 = sparse_tensor.extract_value %t1 at %it1 : index
///          %yield = sparse_tensor.insert %v1 into %arg[%coord]
///          sparse_tensor.yield %yield
///       }
///       case _, %it2 {
///          // v = v2 + 0 = v2
///          %v2 = sparse_tensor.extract_value %t2 at %it2 : index
///          %yield = sparse_tensor.insert %v1 into %arg[%coord]
///          sparse_tensor.yield %yield
///       }
///       case %it1, %it2 {
///          // v = v1 + v2
///          %v1 = sparse_tensor.extract_value %t1 at %it1 : index
///          %v2 = sparse_tensor.extract_value %t2 at %it2 : index
///          %v = arith.addi %v1, %v2 : index
///          %yield = sparse_tensor.insert %v into %arg[%coord]
///          sparse_tensor.yield %yield
///       }
///       ```
class CoIterateOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Compressed an access pattern for insertion
/// Finishes a single access pattern expansion by moving inserted elements
///     into the sparse storage scheme of the given tensor with the given
///     level-coordinates.  The arity of `lvlCoords` is one less than the
///     level-rank of the tensor, with the coordinate of the innermost
///     level defined through the `added` array.  The `values` and `filled`
///     arrays are reset in a *sparse* fashion by only iterating over set
///     elements through an indirection using the `added` array, so that
///     the operations are kept proportional to the number of nonzeros.
///     See the `sparse_tensor.expand` operation for more details.
/// 
///     Note that this operation is "impure" in the sense that even though
///     the result is modeled through an SSA value, the insertion is eventually
///     done "in place", and referencing the old SSA value is undefined behavior.
/// 
///     Example:
/// 
///     ```mlir
///     %result = sparse_tensor.compress %values, %filled, %added, %count into %tensor[%i]
///       : memref<?xf64>, memref<?xi1>, memref<?xindex>, tensor<4x4xf64, #CSR>
///     ```
class CompressOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Concatenates a list of tensors into a single tensor.
/// Concatenates a list input tensors and the output tensor with the same
///      dimension-rank.  The concatenation happens on the specified `dimension`
///      (0 <= dimension < dimRank).  The resulting `dimension` size is the
///      sum of all the input sizes for that dimension, while all the other
///      dimensions should have the same size in the input and output tensors.
/// 
///      Only statically-sized input tensors are accepted, while the output tensor
///      can be dynamically-sized.
/// 
///      Example:
/// 
///      ```mlir
///      %0 = sparse_tensor.concatenate %1, %2 { dimension = 0 : index }
///        : tensor<64x64xf64, #CSR>, tensor<64x64xf64, #CSR> to tensor<128x64xf64, #CSR>
///      ```
class ConcatenateOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Converts between different tensor types
/// Converts one sparse or dense tensor type to another tensor type. The rank
///     of the source and destination types must match exactly, and the dimension
///     sizes must either match exactly or relax from a static to a dynamic size.
///     The sparse encoding of the two types can obviously be completely different.
///     The name `convert` was preferred over `cast`, since the operation may incur
///     a non-trivial cost.
/// 
///     When converting between two different sparse tensor types, only explicitly
///     stored values are moved from one underlying sparse storage format to
///     the other. When converting from an unannotated dense tensor type to a
///     sparse tensor type, an explicit test for nonzero values is used. When
///     converting to an unannotated dense tensor type, implicit zeroes in the
///     sparse storage format are made explicit. Note that the conversions can have
///     non-trivial costs associated with them, since they may involve elaborate
///     data structure transformations. Also, conversions from sparse tensor types
///     into dense tensor types may be infeasible in terms of storage requirements.
/// 
///     Trivial dense-to-dense convert will be removed by canonicalization while
///     trivial sparse-to-sparse convert will be removed by the sparse codegen. This
///     is because we use trivial sparse-to-sparse convert to tell bufferization
///     that the sparse codegen will expand the tensor buffer into sparse tensor
///     storage.
/// 
///     Examples:
/// 
///     ```mlir
///     %0 = sparse_tensor.convert %a : tensor<32x32xf32> to tensor<32x32xf32, #CSR>
///     %1 = sparse_tensor.convert %a : tensor<32x32xf32> to tensor<?x?xf32, #CSR>
///     %2 = sparse_tensor.convert %b : tensor<8x8xi32, #CSC> to tensor<8x8xi32, #CSR>
///     %3 = sparse_tensor.convert %c : tensor<4x8xf64, #CSR> to tensor<4x?xf64, #CSC>
/// 
///     // The following conversion is not allowed (since it would require a
///     // runtime assertion that the source's dimension size is actually 100).
///     %4 = sparse_tensor.convert %d : tensor<?xf64> to tensor<100xf64, #SV>
///     ```
class ConvertOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Performs coordinate translation between level and dimension coordinate space.
/// Performs coordinate translation between level and dimension coordinate space according
///     to the affine maps defined by $encoder.
/// 
///     Example:
/// 
///     ```mlir
///     %l0, %l1, %l2, %l3 = sparse_tensor.crd_translate dim_to_lvl [%d0, %d1] as #BSR
///                        : index, index, index, index
///     ```
class CrdTranslateOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Copies the levels and values of the given sparse tensor
/// The disassemble operation is the inverse of `sparse_tensor::assemble`.
///     It copies the per-level position and coordinate arrays together with
///     the values array of the given sparse tensor into the user-supplied buffers
///     along with the actual length of the memory used in each returned buffer.
/// 
///     This operation can be used for returning a disassembled MLIR sparse tensor;
///     e.g., copying the sparse tensor contents into pre-allocated numpy arrays
///     back to Python. It is the user's responsibility to allocate large enough
///     buffers of the appropriate types to hold the sparse tensor contents.
///     The sparsifier simply copies all fields of the sparse tensor into the
///     user-supplied buffers without any sanity test to verify data integrity.
/// 
///     Example:
/// 
///     ```mlir
///     // input COO format |1.1, 0.0, 0.0, 0.0|
///     //    of 3x4 matrix |0.0, 0.0, 2.2, 3.3|
///     //                  |0.0, 0.0, 0.0, 0.0|
///     %p, %c, %v, %p_len, %c_len, %v_len =
///       sparse_tensor.disassemble %s : tensor<3x4xf64, #COO>
///          out_lvls(%op, %oi : tensor<2xindex>, tensor<3x2xindex>)
///          out_vals(%od : tensor<3xf64>) ->
///            (tensor<2xindex>, tensor<3x2xindex>), tensor<3xf64>, (index, index), index
///     // %p = arith.constant dense<[ 0,              3 ]> : tensor<2xindex>
///     // %c = arith.constant dense<[[0,0], [1,2], [1,3]]> : tensor<3x2xindex>
///     // %v = arith.constant dense<[ 1.1,   2.2,   3.3 ]> : tensor<3xf64>
///     // %p_len = 2
///     // %c_len = 6 (3x2)
///     // %v_len = 3
///     ```
class DisassembleOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Expands an access pattern for insertion
/// Performs an access pattern expansion for the innermost levels of the
///     given tensor. This operation is useful to implement kernels in which a
///     sparse tensor appears as output. This technique is known under several
///     different names and using several alternative implementations,
///     for example, phase counter [Gustavson72], expanded or switch array
///     [Pissanetzky84], in phase scan [Duff90], access pattern expansion [Bik96],
///     and workspaces [Kjolstad19].
/// 
///     The `values` and `filled` arrays must have lengths equal to the
///     level-size of the innermost level (i.e., as if the innermost level
///     were *dense*).  The `added` array and `count` are used to store new
///     level-coordinates when a false value is encountered in the `filled`
///     array.  All arrays should be allocated before the loop (possibly even
///     shared between loops in a future optimization) so that their *dense*
///     initialization can be amortized over many iterations.  Setting and
///     resetting the dense arrays in the loop nest itself is kept *sparse*
///     by only iterating over set elements through an indirection using
///     the added array, so that the operations are kept proportional to
///     the number of nonzeros.
/// 
///     Note that this operation is "impure" in the sense that even though the
///     results are modeled through SSA values, the operation relies on a proper
///     side-effecting context that sets and resets the expanded arrays.
/// 
///     Example:
/// 
///     ```mlir
///     %values, %filled, %added, %count = sparse_tensor.expand %tensor
///       : tensor<4x4xf64, #CSR> to memref<?xf64>, memref<?xi1>, memref<?xindex>
///     ```
class ExpandOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Iterates over elements in a tensor
/// Iterates over stored elements in a tensor (which are typically, but not always,
///      non-zero for sparse tensors) and executes the block.
/// 
///      `tensor`: the input tensor to iterate over.
///      `initArgs`: the initial loop argument to carry and update during each iteration.
///      `order`: an optional permutation affine map that specifies the order in which
///      the dimensions are visited (e.g., row first or column first). This is only
///      applicable when the input tensor is a non-annotated dense tensor.
/// 
///      For an input tensor with dim-rank `n`, the block must take `n + 1`
///      arguments (plus additional loop-carried variables as described below).
///      The first `n` arguments provide the dimension-coordinates of the element
///      being visited, and must all have `index` type.  The `(n+1)`-th argument
///      provides the element's value, and must have the tensor's element type.
/// 
///      `sparse_tensor.foreach` can also operate on loop-carried variables and returns
///      the final values after loop termination. The initial values of the variables are
///      passed as additional SSA operands to the "sparse_tensor.foreach" following the n + 1
///      SSA values mentioned above (n coordinates and 1 value).
/// 
///      The region must terminate with a "sparse_tensor.yield" that passes the current
///      values of all loop-carried variables to the next iteration, or to the
///      result, if at the last iteration. The number and static types of loop-carried
///      variables may not change with iterations.
/// 
///      For example:
///      ```mlir
///      %c0 = arith.constant 0 : i32
///      %ret = sparse_tensor.foreach in %0 init(%c0): tensor<?x?xi32, #DCSR>, i32 -> i32 do {
///       ^bb0(%arg1: index, %arg2: index, %arg3: i32, %iter: i32):
///         %sum = arith.add %iter, %arg3
///         sparse_tensor.yield %sum
///      }
///      ```
/// 
///      It is important to note that the generated loop iterates over
///      elements in their storage order.  However, regardless of the
///      storage scheme used by the tensor, the block is always given
///      the dimension-coordinates.
/// 
///      For example:
///      ```mlir
///      #COL_MAJOR = #sparse_tensor.encoding<{
///        map = (d0, d1) -> (d1 : compressed, d0 : compressed)
///      }>
/// 
///      // foreach on a column-major sparse tensor
///      sparse_tensor.foreach in %0 : tensor<2x3xf64, #COL_MAJOR> do {
///       ^bb0(%row: index, %col: index, %arg3: f64):
///          // [%row, %col] -> [0, 0], [1, 0], [2, 0], [0, 1], [1, 1], [2, 1]
///      }
/// 
///      #ROW_MAJOR = #sparse_tensor.encoding<{
///        map = (d0, d1) -> (d0 : compressed, d1 : compressed)
///      }>
/// 
///      // foreach on a row-major sparse tensor
///      sparse_tensor.foreach in %0 : tensor<2x3xf64, #ROW_MAJOR> do {
///       ^bb0(%row: index, %col: index, %arg3: f64):
///          // [%row, %col] -> [0, 0], [0, 1], [1, 0], [1, 1], [2, 0], [2, 1]
///      }
/// 
///      // foreach on a row-major dense tensor but visit column first
///      sparse_tensor.foreach in %0 {order=affine_map<(i,j)->(j,i)>}: tensor<2x3xf64> do {
///       ^bb0(%row: index, %col: index, %arg3: f64):
///          // [%row, %col] -> [0, 0], [1, 0], [2, 0], [0, 1], [1, 1], [2, 1]
///      }
/// 
///      ```
class ForeachOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Returns the requested field of the given storage_specifier.
/// 
///     Example of querying the size of the coordinates array for level 0:
/// 
///     ```mlir
///     %0 = sparse_tensor.storage_specifier.get %arg0 crd_mem_sz at 0
///          : !sparse_tensor.storage_specifier<#COO>
///     ```
class GetStorageSpecifierOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Indicates whether running in runtime/codegen mode
/// Returns a boolean value that indicates whether the sparsifier runs in
///     runtime library mode or not. For testing only! This operation is useful
///     for writing test cases that require different code depending on
///     runtime/codegen mode.
/// 
///     Example:
/// 
///     ```mlir
///     %has_runtime = sparse_tensor.has_runtime_library
///     scf.if %has_runtime {
///       ...
///     }
///     ```
class HasRuntimeLibraryOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Rematerializes tensor from underlying sparse storage format
/// Rematerializes a tensor from the underlying sparse storage format of the
///     given tensor. This is similar to the `bufferization.to_tensor` operation
///     in the sense that it provides a bridge between a bufferized world view
///     and a tensor world view. Unlike the `bufferization.to_tensor` operation,
///     however, this sparse operation is used only temporarily to maintain a
///     correctly typed intermediate representation during progressive
///     bufferization.
/// 
///     The `hasInserts` attribute denote whether insertions to the underlying
///     sparse storage format may have occurred, in which case the underlying
///     sparse storage format needs to be finalized. Otherwise, the operation
///     simply folds away.
/// 
///     Note that this operation is "impure" in the sense that even though
///     the result is modeled through an SSA value, the operation relies on
///     a proper context of materializing and inserting the tensor value.
/// 
///     Examples:
/// 
///     ```mlir
///     %result = sparse_tensor.load %tensor : tensor<8xf64, #SV>
/// 
///     %1 = sparse_tensor.load %0 hasInserts : tensor<16x32xf32, #CSR>
///     ```
class LoadOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// level index operation
/// The `sparse_tensor.lvl` behaves similar to `tensor.dim` operation.
///     It takes a sparse tensor and a level operand of type `index` and returns
///     the size of the requested level of the given sparse tensor.
///     If the sparse tensor has an identity dimension to level mapping, it returns
///     the same result as `tensor.dim`.
///     If the level index is out of bounds, the behavior is undefined.
/// 
///     Example:
/// 
///     ```mlir
///     #BSR = #sparse_tensor.encoding<{
///       map = ( i, j ) ->
///         ( i floordiv 2 : dense,
///           j floordiv 3 : compressed,
///           i mod 2      : dense,
///           j mod 3      : dense
///         )
///     }>
/// 
///     // Always returns 2 (4 floordiv 2), can be constant folded:
///     %c0 = arith.constant 0 : index
///     %x = sparse_tensor.lvl %A, %c0 : tensor<4x?xf32, #BSR>
/// 
///     // Return the dynamic dimension of %A computed by %j mod 3.
///     %c1 = arith.constant 1 : index
///     %y = sparse_tensor.lvl %A, %c1 : tensor<4x?xf32, #BSR>
/// 
///     // Always return 3 (since j mod 3 < 3), can be constant fold
///     %c3 = arith.constant 3 : index
///     %y = sparse_tensor.lvl %A, %c3 : tensor<4x?xf32, #BSR>
///     ```
class LvlOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Materializes a new sparse tensor from given source
/// Materializes a sparse tensor with contents taken from an opaque pointer
///     provided by `source`. For targets that have access to a file system,
///     for example, this pointer may be a filename (or file) of a sparse
///     tensor in a particular external storage format. The form of the operation
///     is kept deliberately very general to allow for alternative implementations
///     in the future, such as pointers to buffers or runnable initialization
///     code. The operation is provided as an anchor that materializes a properly
///     typed sparse tensor with inital contents into a computation.
/// 
///     Reading in a symmetric matrix will result in just the lower/upper triangular
///     part of the matrix (so that only relevant information is stored). Proper
///     symmetry support for operating on symmetric matrices is still TBD.
/// 
///     Example:
/// 
///     ```mlir
///     sparse_tensor.new %source : !Source to tensor<1024x1024xf64, #CSR>
///     ```
class NewOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Returns the number of entries that are stored in the tensor.
/// Returns the number of entries that are stored in the given sparse tensor.
///     Note that this is typically the number of nonzero elements in the tensor,
///     but since explicit zeros may appear in the storage formats, the more
///     accurate nomenclature is used.
/// 
///     Example:
/// 
///     ```mlir
///     %noe = sparse_tensor.number_of_entries %tensor : tensor<64x64xf64, #CSR>
///     ```
class NumberOfEntriesOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Outputs a sparse tensor to the given destination
/// Outputs the contents of a sparse tensor to the destination defined by an
///     opaque pointer provided by `dest`. For targets that have access to a file
///     system, for example, this pointer may specify a filename (or file) for output.
///     The form of the operation is kept deliberately very general to allow for
///     alternative implementations in the future, such as sending the contents to
///     a buffer defined by a pointer.
/// 
///     Note that this operation is "impure" in the sense that its behavior
///     is solely defined by side-effects and not SSA values.
/// 
///     Example:
/// 
///     ```mlir
///     sparse_tensor.out %t, %dest : tensor<1024x1024xf64, #CSR>, !Dest
///     ```
class OutOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Prints a sparse tensor (for testing and debugging)
/// Prints the individual components of a sparse tensors (the positions,
///     coordinates, and values components) to stdout for testing and debugging
///     purposes. This operation lowers to just a few primitives in a light-weight
///     runtime support to simplify supporting this operation on new platforms.
/// 
///     Example:
/// 
///     ```mlir
///     sparse_tensor.print %tensor : tensor<1024x1024xf64, #CSR>
///     ```
class PrintOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Pushes a value to the back of a given buffer
/// Pushes `value` to the end of the given sparse tensor storage buffer
///     `inBuffer` as indicated by the value of `curSize` and returns the
///     new size of the buffer in `newSize` (`newSize = curSize + n`).
///     The capacity of the buffer is recorded in the memref type of `inBuffer`.
///     If the current buffer is full, then `inBuffer.realloc` is called before
///     pushing the data to the buffer. This is similar to std::vector push_back.
/// 
///     The optional input `n` specifies the number of times to repeately push
///     the value to the back of the tensor. When `n` is a compile-time constant,
///     its value can't be less than 1. If `n` is a runtime value that is less
///     than 1, the behavior is undefined. Although using input `n` is semantically
///     equivalent to calling push_back n times, it gives compiler more chances to
///     to optimize the memory reallocation and the filling of the memory with the
///     same value.
/// 
///     The `inbounds` attribute tells the compiler that the insertion won't go
///     beyond the current storage buffer. This allows the compiler to not generate
///     the code for capacity check and reallocation. The typical usage will be for
///     "dynamic" sparse tensors for which a capacity can be set beforehand.
/// 
///     Note that this operation is "impure" in the sense that even though
///     the result is modeled through an SSA value, referencing the memref
///     through the old SSA value after this operation is undefined behavior.
/// 
///     Example:
/// 
///     ```mlir
///     %buf, %newSize = sparse_tensor.push_back %curSize, %buffer, %val
///        : index, memref<?xf64>, f64
///     ```
/// 
///     ```mlir
///     %buf, %newSize = sparse_tensor.push_back inbounds %curSize, %buffer, %val
///        : xindex, memref<?xf64>, f64
///     ```
/// 
///     ```mlir
///     %buf, %newSize = sparse_tensor.push_back inbounds %curSize, %buffer, %val, %n
///        : xindex, memref<?xf64>, f64
///     ```
class PushBackOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Custom reduction operation utilized within linalg.generic
/// Defines a computation with a `linalg.generic` operation that takes two
///       operands and an identity value and reduces all stored values down to a
///       single result based on the computation in the region.
/// 
///       The region must contain exactly one block taking two arguments. The block
///       must end with a sparse_tensor.yield and the output must match the input
///       argument types.
/// 
///       Note that this operation is only required for custom reductions beyond
///       the standard reduction operations (add, sub, or, xor) that can be
///       sparsified by merely reducing the stored values. More elaborate reduction
///       operations (mul, and, min, max, etc.) would need to account for implicit
///       zeros as well. They can still be handled using this custom reduction
///       operation. The `linalg.generic` `iterator_types` defines which indices
///       are being reduced. When the associated operands are used in an operation,
///       a reduction will occur. The use of this explicit `reduce` operation
///       is not required in most cases.
/// 
///       Example of Matrix->Vector reduction using max(product(x_i), 100):
/// 
///       ```mlir
///       %cf1 = arith.constant 1.0 : f64
///       %cf100 = arith.constant 100.0 : f64
///       %C = tensor.empty(...)
///       %0 = linalg.generic #trait
///          ins(%A: tensor<?x?xf64, #SparseMatrix>)
///         outs(%C: tensor<?xf64, #SparseVector>) {
///         ^bb0(%a: f64, %c: f64) :
///           %result = sparse_tensor.reduce %c, %a, %cf1 : f64 {
///               ^bb0(%arg0: f64, %arg1: f64):
///                 %0 = arith.mulf %arg0, %arg1 : f64
///                 %cmp = arith.cmpf "ogt", %0, %cf100 : f64
///                 %ret = arith.select %cmp, %cf100, %0 : f64
///                 sparse_tensor.yield %ret : f64
///             }
///           linalg.yield %result : f64
///       } -> tensor<?xf64, #SparseVector>
///       ```
class ReduceOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Reinterprets the dimension/level maps of the source tensor
/// Reinterprets the dimension-to-level and level-to-dimension map specified in
///     `source` according to the type of `dest`.
///     `reinterpret_map` is a no-op and is introduced merely to resolve type conflicts.
///     It does not make any modification to the source tensor and source/dest tensors
///     are considered to be aliases.
/// 
///     `source` and `dest` tensors are "reinterpretable" if and only if they have
///     the exactly same storage at a low level.
///     That is, both `source` and `dest` has the same number of levels and level types,
///     and their shape is consistent before and after `reinterpret_map`.
/// 
///     Example:
///     ```mlir
///     #CSC = #sparse_tensor.encoding<{
///       map = (d0, d1) -> (d1: dense, d0: compressed)
///     }>
///     #CSR = #sparse_tensor.encoding<{
///       map = (d0, d1) -> (d0: dense, d1: compressed)
///     }>
///     %t1 = sparse_tensor.reinterpret_map %t0 : tensor<3x4xi32, #CSC> to tensor<4x3xi32, #CSR>
/// 
///     #BSR = #sparse_tensor.encoding<{
///       map = ( i, j ) -> ( i floordiv 2 : dense,
///                           j floordiv 3 : compressed,
///                           i mod 2      : dense,
///                           j mod 3      : dense
///       )
///     }>
///     #DSDD = #sparse_tensor.encoding<{
///       map = (i, j, k, l) -> (i: dense, j: compressed, k: dense, l: dense)
///     }>
///     %t1 = sparse_tensor.reinterpret_map %t0 : tensor<6x12xi32, #BSR> to tensor<3x4x2x3xi32, #DSDD>
///     ```
class ReinterpretMapOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Reorder the input COO such that it has the the same order as the output COO
/// Reorders the input COO to the same order as specified by the output format.
///     E.g., reorder an unordered COO into an ordered one.
/// 
///     The input and result COO tensor must have the same element type, position type and
///     coordinate type. At the moment, the operation also only supports ordering
///     input and result COO with the same dim2lvl map.
/// 
///     Example:
/// 
///     ```mlir
///     %res = sparse_tensor.reorder_coo quick_sort %coo : tensor<?x?xf64 : #Unordered_COO> to
///                                                        tensor<?x?xf64 : #Ordered_COO>
/// 
///     ```
class ReorderCOOOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Select operation utilized within linalg.generic
/// Defines an evaluation within a `linalg.generic` operation that takes a single
///       operand and decides whether or not to keep that operand in the output.
/// 
///       A single region must contain exactly one block taking one argument. The block
///       must end with a sparse_tensor.yield and the output type must be boolean.
/// 
///       Value threshold is an obvious usage of the select operation. However, by using
///       `linalg.index`, other useful selection can be achieved, such as selecting the
///       upper triangle of a matrix.
/// 
///       Example of selecting A >= 4.0:
/// 
///       ```mlir
///       %C = tensor.empty(...)
///       %0 = linalg.generic #trait
///          ins(%A: tensor<?xf64, #SparseVector>)
///         outs(%C: tensor<?xf64, #SparseVector>) {
///         ^bb0(%a: f64, %c: f64) :
///           %result = sparse_tensor.select %a : f64 {
///               ^bb0(%arg0: f64):
///                 %cf4 = arith.constant 4.0 : f64
///                 %keep = arith.cmpf "uge", %arg0, %cf4 : f64
///                 sparse_tensor.yield %keep : i1
///             }
///           linalg.yield %result : f64
///       } -> tensor<?xf64, #SparseVector>
///       ```
/// 
///       Example of selecting lower triangle of a matrix:
/// 
///       ```mlir
///       %C = tensor.empty(...)
///       %1 = linalg.generic #trait
///          ins(%A: tensor<?x?xf64, #CSR>)
///         outs(%C: tensor<?x?xf64, #CSR>) {
///         ^bb0(%a: f64, %c: f64) :
///           %row = linalg.index 0 : index
///           %col = linalg.index 1 : index
///           %result = sparse_tensor.select %a : f64 {
///               ^bb0(%arg0: f64):
///                 %keep = arith.cmpf "olt", %col, %row : f64
///                 sparse_tensor.yield %keep : i1
///             }
///           linalg.yield %result : f64
///       } -> tensor<?x?xf64, #CSR>
///       ```
class SelectOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Set the field of the storage specifier to the given input value. Returns
///     the updated storage_specifier as a new SSA value.
/// 
///     Example of updating the sizes of the coordinates array for level 0:
/// 
///     ```mlir
///     %0 = sparse_tensor.storage_specifier.set %arg0 crd_mem_sz at 0 with %new_sz
///        : !sparse_tensor.storage_specifier<#COO>
///     ```
class SetStorageSpecifierOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Sorts the arrays in xs and ys lexicographically on the integral values found in the xs list
/// Sorts the `xs` values along with some `ys` values that are put in a single linear
///     buffer `xy`.  The affine map attribute `perm_map` specifies the permutation to be
///     applied on the `xs` before comparison, the rank of the permutation map
///     also specifies the number of `xs` values in `xy`.
///     The optional index attribute `ny` provides the number of `ys` values in `xy`.
///     When `ny` is not explicitly specified, its value is 0.
///     This instruction supports a more efficient way to store the COO definition
///     in sparse tensor type.
/// 
///     The buffer xy should have a dimension not less than n * (rank(perm_map) + ny) while the
///     buffers in `ys` should have a dimension not less than `n`. The behavior of
///     the operator is undefined if this condition is not met.
/// 
///     Example:
/// 
///     ```mlir
///     sparse_tensor.sort insertion_sort_stable %n, %x { perm_map = affine_map<(i,j) -> (j,i)> }
///       : memref<?xindex>
///     ```
class SortOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Returns an initial storage specifier value.  A storage specifier
///     value holds the level-sizes, position arrays, coordinate arrays,
///     and the value array.
///     If this is a specifier for slices, it also holds the extra strides/offsets
///     for each tensor dimension.
/// 
///     TODO: The sparse tensor slice support is currently in a unstable state, and
///     is subject to change in the future.
/// 
///     Example:
/// 
///     ```mlir
///     #CSR = #sparse_tensor.encoding<{
///       map = (i, j) -> (i : dense, j : compressed)
///     }>
///     #CSR_SLICE = #sparse_tensor.encoding<{
///       map = (d0 : #sparse_tensor<slice(1, 4, 1)>,
///              d1 : #sparse_tensor<slice(1, 4, 2)>) ->
///             (d0 : dense, d1 : compressed)
///     }>
/// 
///     %0 = sparse_tensor.storage_specifier.init :  !sparse_tensor.storage_specifier<#CSR>
///     %1 = sparse_tensor.storage_specifier.init with %src
///          : !sparse_tensor.storage_specifier<#CSR> to
///            !sparse_tensor.storage_specifier<#CSR_SLICE>
///     ```
class StorageSpecifierInitOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Extracts the linear coordinates array from a tensor
/// Returns the linear coordinates array for a sparse tensor with
///     a trailing COO region with at least two levels.  It is an error
///     if the tensor doesn't contain such a COO region.  This is similar
///     to the `bufferization.to_buffer` operation in the sense that it
///     provides a bridge between a tensor world view and a bufferized
///     world view.  Unlike the `bufferization.to_buffer` operation,
///     however, this operation actually lowers into code that extracts
///     the linear coordinates array from the sparse storage scheme that
///     stores the coordinates for the COO region as an array of structures.
///     For example, a 2D COO sparse tensor with two non-zero elements at
///     coordinates (1, 3) and (4, 6) are stored in a linear buffer as
///     (1, 4, 3, 6) instead of two buffer as (1, 4) and (3, 6).
/// 
///     Writing into the result of this operation is undefined behavior.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = sparse_tensor.coordinates_buffer %0
///        : tensor<64x64xf64, #COO> to memref<?xindex>
///     ```
class ToCoordinatesBufferOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Extracts the `level`-th coordinates array of the `tensor`
/// Returns the coordinates array of the tensor's storage at the given
///     level.  This is similar to the `bufferization.to_buffer` operation
///     in the sense that it provides a bridge between a tensor world view
///     and a bufferized world view.  Unlike the `bufferization.to_buffer`
///     operation, however, this sparse operation actually lowers into code
///     that extracts the coordinates array from the sparse storage itself
///     (either by calling a support library or through direct code).
/// 
///     Writing into the result of this operation is undefined behavior.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = sparse_tensor.coordinates %0 { level = 1 : index }
///        : tensor<64x64xf64, #CSR> to memref<?xindex>
///     ```
class ToCoordinatesOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Extracts the `level`-th positions array of the `tensor`
/// Returns the positions array of the tensor's storage at the given
///     level.  This is similar to the `bufferization.to_buffer` operation
///     in the sense that it provides a bridge between a tensor world view
///     and a bufferized world view.  Unlike the `bufferization.to_buffer`
///     operation, however, this sparse operation actually lowers into code
///     that extracts the positions array from the sparse storage itself
///     (either by calling a support library or through direct code).
/// 
///     Writing into the result of this operation is undefined behavior.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = sparse_tensor.positions %0 { level = 1 : index }
///        : tensor<64x64xf64, #CSR> to memref<?xindex>
///     ```
class ToPositionsOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Extracts the offset of the sparse tensor slice at the given dimension
/// Extracts the offset of the sparse tensor slice at the given dimension.
/// 
///     Currently, sparse tensor slices are still a work in progress, and only
///     works when runtime library is disabled (i.e., running the sparsifier
///     with `enable-runtime-library=false`).
/// 
///     Example:
/// 
///     ```mlir
///     %0 = tensor.extract_slice %s[%v1, %v2][64, 64][1, 1] : tensor<128x128xf64, #DCSR>
///                                                         to tensor<64x64xf64, #Slice>
/// 
///     %1 = sparse_tensor.slice.offset %0 at 0 : tensor<64x64xf64, #Slice>
///     %2 = sparse_tensor.slice.offset %0 at 1 : tensor<64x64xf64, #Slice>
///     // %1 = %v1
///     // %2 = %v2
///     ```
class ToSliceOffsetOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Extracts the stride of the sparse tensor slice at the given dimension
/// Extracts the stride of the sparse tensor slice at the given dimension.
/// 
///     Currently, sparse tensor slices are still a work in progress, and only
///     works when runtime library is disabled (i.e., running the sparsifier
///     with `enable-runtime-library=false`).
/// 
///     Example:
/// 
///     ```mlir
///     %0 = tensor.extract_slice %s[%v1, %v2][64, 64][%s1, %s2] : tensor<128x128xf64, #DCSR>
///                                                             to tensor<64x64xf64, #Slice>
/// 
///     %1 = sparse_tensor.slice.stride %0 at 0 : tensor<64x64xf64, #Slice>
///     %2 = sparse_tensor.slice.stride %0 at 1 : tensor<64x64xf64, #Slice>
///     // %1 = %s1
///     // %2 = %s2
/// 
///     ```
class ToSliceStrideOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Extracts numerical values array from a tensor
/// Returns the values array of the sparse storage format for the given
///     sparse tensor, independent of the actual dimension. This is similar to
///     the `bufferization.to_buffer` operation in the sense that it provides a bridge
///     between a tensor world view and a bufferized world view. Unlike the
///     `bufferization.to_buffer` operation, however, this sparse operation actually
///     lowers into code that extracts the values array from the sparse storage
///     scheme (either by calling a support library or through direct code).
/// 
///     Writing into the result of this operation is undefined behavior.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = sparse_tensor.values %0 : tensor<64x64xf64, #CSR> to memref<?xf64>
///     ```
class ToValuesOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Unary set operation utilized within linalg.generic
/// Defines a computation with a `linalg.generic` operation that takes a single
///       operand and executes one of two regions depending on whether the operand is
///       nonzero (i.e. stored explicitly in the sparse storage format).
/// 
///       Two regions are defined for the operation must appear in this order:
///       - present (elements present in the sparse tensor)
///       - absent (elements not present in the sparse tensor)
/// 
///       Each region contains a single block describing the computation and result.
///       A non-empty block must end with a sparse_tensor.yield and the return type
///       must match the type of `output`. The primary region's block has one
///       argument, while the missing region's block has zero arguments. The
///       absent region may only generate constants or values already computed
///       on entry of the `linalg.generic` operation.
/// 
///       A region may also be declared empty (i.e. `absent={}`), indicating that the
///       region does not contribute to the output.
/// 
///       Due to the possibility of empty regions, i.e. lack of a value for certain
///       cases, the result of this operation may only feed directly into the output
///       of the `linalg.generic` operation or into into a custom reduction
///       `sparse_tensor.reduce` operation that follows in the same region.
/// 
///       Example of A+1, restricted to existing elements:
/// 
///       ```mlir
///       %C = tensor.empty(...) : tensor<?xf64, #SparseVector>
///       %0 = linalg.generic #trait
///          ins(%A: tensor<?xf64, #SparseVector>)
///         outs(%C: tensor<?xf64, #SparseVector>) {
///         ^bb0(%a: f64, %c: f64) :
///           %result = sparse_tensor.unary %a : f64 to f64
///             present={
///             ^bb0(%arg0: f64):
///               %cf1 = arith.constant 1.0 : f64
///               %ret = arith.addf %arg0, %cf1 : f64
///               sparse_tensor.yield %ret : f64
///             }
///             absent={}
///           linalg.yield %result : f64
///       } -> tensor<?xf64, #SparseVector>
///       ```
/// 
///       Example returning +1 for existing values and -1 for missing values:
/// 
///       ```mlir
///       %p1 = arith.constant  1 : i32
///       %m1 = arith.constant -1 : i32
///       %C = tensor.empty(...) : tensor<?xi32, #SparseVector>
///       %1 = linalg.generic #trait
///          ins(%A: tensor<?xf64, #SparseVector>)
///         outs(%C: tensor<?xi32, #SparseVector>) {
///         ^bb0(%a: f64, %c: i32) :
///           %result = sparse_tensor.unary %a : f64 to i32
///             present={
///             ^bb0(%x: f64):
///               sparse_tensor.yield %p1 : i32
///             }
///             absent={
///               sparse_tensor.yield %m1 : i32
///             }
///           linalg.yield %result : i32
///       } -> tensor<?xi32, #SparseVector>
///       ```
/// 
///       Example showing a structural inversion (existing values become missing in
///       the output, while missing values are filled with 1):
/// 
///       ```mlir
///       %c1 = arith.constant 1 : i64
///       %C = tensor.empty(...) : tensor<?xi64, #SparseVector>
///       %2 = linalg.generic #trait
///          ins(%A: tensor<?xf64, #SparseVector>)
///         outs(%C: tensor<?xi64, #SparseVector>) {
///         ^bb0(%a: f64, %c: i64) :
///           %result = sparse_tensor.unary %a : f64 to i64
///             present={}
///             absent={
///               sparse_tensor.yield %c1 : i64
///             }
///           linalg.yield %result : i64
///       } -> tensor<?xi64, #SparseVector>
///       ```
class UnaryOp;

} // namespace mlir::sparse_tensor
namespace mlir::sparse_tensor {

/// Yield from sparse_tensor set-like operations
/// Yields a value from within a `binary`, `unary`, `reduce`,
///       `select` or `foreach` block.
/// 
///       Example:
/// 
///       ```mlir
///       %0 = sparse_tensor.unary %a : i64 to i64 {
///         present={
///           ^bb0(%arg0: i64):
///             %cst = arith.constant 1 : i64
///             %ret = arith.addi %arg0, %cst : i64
///             sparse_tensor.yield %ret : i64
///         }
///       }
///       ```
class YieldOp;

} // namespace mlir::sparse_tensor
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ExtractIterSpaceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtractIterSpaceOpGenericAdaptorBase {
public:
  struct Properties {
    using hiLvlTy = ::mlir::IntegerAttr;
    hiLvlTy hiLvl;

    auto getHiLvl() const {
      auto &propStorage = this->hiLvl;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setHiLvl(const ::mlir::IntegerAttr &propValue) {
      this->hiLvl = propValue;
    }
    using loLvlTy = ::mlir::IntegerAttr;
    loLvlTy loLvl;

    auto getLoLvl() const {
      auto &propStorage = this->loLvl;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLoLvl(const ::mlir::IntegerAttr &propValue) {
      this->loLvl = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.hiLvl == this->hiLvl &&
        rhs.loLvl == this->loLvl &&
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
  ExtractIterSpaceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.extract_iteration_space", odsAttrs.getContext());
  }

  ExtractIterSpaceOpGenericAdaptorBase(ExtractIterSpaceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getLoLvlAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().loLvl);
    return attr;
  }

  ::mlir::sparse_tensor::Level getLoLvl();
  ::mlir::IntegerAttr getHiLvlAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().hiLvl);
    return attr;
  }

  ::mlir::sparse_tensor::Level getHiLvl();
};

} // namespace detail
template <typename RangeT>
class ExtractIterSpaceOpGenericAdaptor : public detail::ExtractIterSpaceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtractIterSpaceOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_parentIter = 1;
public:
  ExtractIterSpaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExtractIterSpaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExtractIterSpaceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExtractIterSpaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExtractIterSpaceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExtractIterSpaceOpGenericAdaptor(RangeT values, const ExtractIterSpaceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExtractIterSpaceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExtractIterSpaceOp>>>
  ExtractIterSpaceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getParentIter() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ExtractIterSpaceOpAdaptor : public ExtractIterSpaceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExtractIterSpaceOpGenericAdaptor::ExtractIterSpaceOpGenericAdaptor;
  ExtractIterSpaceOpAdaptor(ExtractIterSpaceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExtractIterSpaceOp : public ::mlir::Op<ExtractIterSpaceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::sparse_tensor::IterSpaceType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtractIterSpaceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtractIterSpaceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_parentIter = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<ExtractIterSpaceOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("hiLvl"), ::llvm::StringRef("loLvl")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getHiLvlAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getHiLvlAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLoLvlAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLoLvlAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.extract_iteration_space");
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

  ::mlir::TypedValue<::mlir::sparse_tensor::IteratorType> getParentIter() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::sparse_tensor::IteratorType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::sparse_tensor::IteratorType>>(*operands.begin());
  }

  ::mlir::OpOperand &getTensorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getParentIterMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::sparse_tensor::IterSpaceType> getExtractedSpace() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::sparse_tensor::IterSpaceType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getLoLvlAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().loLvl);
  }

  ::mlir::sparse_tensor::Level getLoLvl();
  ::mlir::IntegerAttr getHiLvlAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().hiLvl);
  }

  ::mlir::sparse_tensor::Level getHiLvl();
  void setLoLvlAttr(::mlir::IntegerAttr attr) {
    getProperties().loLvl = attr;
  }

  void setLoLvl(::mlir::sparse_tensor::Level attrValue);
  void setHiLvlAttr(::mlir::IntegerAttr attr) {
    getProperties().hiLvl = attr;
  }

  void setHiLvl(::mlir::sparse_tensor::Level attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value tensor, Value parentIter, sparse_tensor::Level loLvl);
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value tensor, Value parentIter, sparse_tensor::Level loLvl);
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, Value tensor, Value parentIter, sparse_tensor::Level loLvl);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value tensor);
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value tensor);
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type extractedSpace, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::IntegerAttr loLvl, ::mlir::IntegerAttr hiLvl);
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type extractedSpace, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::IntegerAttr loLvl, ::mlir::IntegerAttr hiLvl);
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type extractedSpace, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::IntegerAttr loLvl, ::mlir::IntegerAttr hiLvl);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::IntegerAttr loLvl, ::mlir::IntegerAttr hiLvl);
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::IntegerAttr loLvl, ::mlir::IntegerAttr hiLvl);
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::IntegerAttr loLvl, ::mlir::IntegerAttr hiLvl);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::IntegerAttr loLvl, ::mlir::IntegerAttr hiLvl);
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::IntegerAttr loLvl, ::mlir::IntegerAttr hiLvl);
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::IntegerAttr loLvl, ::mlir::IntegerAttr hiLvl);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type extractedSpace, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::sparse_tensor::Level loLvl, ::mlir::sparse_tensor::Level hiLvl);
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type extractedSpace, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::sparse_tensor::Level loLvl, ::mlir::sparse_tensor::Level hiLvl);
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type extractedSpace, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::sparse_tensor::Level loLvl, ::mlir::sparse_tensor::Level hiLvl);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::sparse_tensor::Level loLvl, ::mlir::sparse_tensor::Level hiLvl);
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::sparse_tensor::Level loLvl, ::mlir::sparse_tensor::Level hiLvl);
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::sparse_tensor::Level loLvl, ::mlir::sparse_tensor::Level hiLvl);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::sparse_tensor::Level loLvl, ::mlir::sparse_tensor::Level hiLvl);
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::sparse_tensor::Level loLvl, ::mlir::sparse_tensor::Level hiLvl);
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::Value parentIter, ::mlir::sparse_tensor::Level loLvl, ::mlir::sparse_tensor::Level hiLvl);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractIterSpaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractIterSpaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  std::pair<Level, Level> getLvlRange() {
    return std::make_pair(getLoLvl(), getHiLvl());
  }
  unsigned getSpaceDim() {
    return getHiLvl() - getLoLvl();
  }
  ArrayRef<::mlir::sparse_tensor::LevelType> getSpaceLvlTypes() {
    return getExtractedSpace().getType().getLvlTypes();
  }
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ExtractIterSpaceOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ExtractValOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtractValOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ExtractValOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.extract_value", odsAttrs.getContext());
  }

  ExtractValOpGenericAdaptorBase(ExtractValOp op);

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
class ExtractValOpGenericAdaptor : public detail::ExtractValOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtractValOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_iterator = 1;
public:
  ExtractValOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExtractValOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExtractValOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExtractValOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExtractValOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExtractValOpGenericAdaptor(RangeT values, const ExtractValOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExtractValOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExtractValOp>>>
  ExtractValOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getIterator() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ExtractValOpAdaptor : public ExtractValOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExtractValOpGenericAdaptor::ExtractValOpGenericAdaptor;
  ExtractValOpAdaptor(ExtractValOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExtractValOp : public ::mlir::Op<ExtractValOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtractValOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtractValOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_iterator = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.extract_value");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::sparse_tensor::IteratorType> getIterator() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::sparse_tensor::IteratorType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getTensorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIteratorMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::Value iterator);
  static ExtractValOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::Value iterator);
  static ExtractValOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::Value iterator);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::Value iterator);
  static ExtractValOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::Value iterator);
  static ExtractValOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::Value iterator);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::Value iterator);
  static ExtractValOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::Value iterator);
  static ExtractValOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::Value iterator);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractValOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractValOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractValOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExtractValOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractValOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractValOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractValOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExtractValOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ExtractValOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::IterateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IterateOpGenericAdaptorBase {
public:
  struct Properties {
    using crdUsedLvlsTy = ::mlir::IntegerAttr;
    crdUsedLvlsTy crdUsedLvls;

    auto getCrdUsedLvls() const {
      auto &propStorage = this->crdUsedLvls;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setCrdUsedLvls(const ::mlir::IntegerAttr &propValue) {
      this->crdUsedLvls = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.crdUsedLvls == this->crdUsedLvls &&
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
  IterateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.iterate", odsAttrs.getContext());
  }

  IterateOpGenericAdaptorBase(IterateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getCrdUsedLvlsAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().crdUsedLvls);
    return attr;
  }

  ::mlir::sparse_tensor::I64BitSet getCrdUsedLvls();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class IterateOpGenericAdaptor : public detail::IterateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IterateOpGenericAdaptorBase;
  static constexpr int odsIndex_iterSpace = 0;
  static constexpr int odsIndex_initArgs = 1;
public:
  IterateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IterateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IterateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IterateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IterateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IterateOpGenericAdaptor(RangeT values, const IterateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IterateOp, typename = std::enable_if_t<std::is_same_v<LateInst, IterateOp>>>
  IterateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getIterSpace() {
    return (*getODSOperands(0).begin());
  }

  RangeT getInitArgs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class IterateOpAdaptor : public IterateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IterateOpGenericAdaptor::IterateOpGenericAdaptor;
  IterateOpAdaptor(IterateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IterateOp : public ::mlir::Op<IterateOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<sparse_tensor::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::RecursivelySpeculatableImplTrait, ::mlir::LoopLikeOpInterface::Trait, ::mlir::RegionBranchOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IterateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IterateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_iterSpace = 0;
  static constexpr int odsIndex_initArgs = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::isDefinedOutsideOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::moveOutOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::promoteIfSingleIteration;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::getLoopInductionVars;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::getLoopLowerBounds;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::getLoopSteps;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::getLoopUpperBounds;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::replaceWithAdditionalYields;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::getStaticTripCount;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::isValidInductionVarType;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::setLoopLowerBounds;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::setLoopUpperBounds;
  using ::mlir::LoopLikeOpInterface::Trait<IterateOp>::setLoopSteps;
  using ::mlir::RegionBranchOpInterface::Trait<IterateOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<IterateOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<IterateOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<IterateOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<IterateOp>::getRegionInvocationBounds;
  using ::mlir::RegionBranchOpInterface::Trait<IterateOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("crdUsedLvls")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCrdUsedLvlsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCrdUsedLvlsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.iterate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::sparse_tensor::IterSpaceType> getIterSpace() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::sparse_tensor::IterSpaceType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getInitArgs() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getIterSpaceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getInitArgsMutable();
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
  ::mlir::IntegerAttr getCrdUsedLvlsAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().crdUsedLvls);
  }

  ::mlir::sparse_tensor::I64BitSet getCrdUsedLvls();
  void setCrdUsedLvlsAttr(::mlir::IntegerAttr attr) {
    getProperties().crdUsedLvls = attr;
  }

  void setCrdUsedLvls(::mlir::sparse_tensor::I64BitSet attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value iterSpace, ValueRange initArgs);
  static IterateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value iterSpace, ValueRange initArgs);
  static IterateOp create(::mlir::ImplicitLocOpBuilder &builder, Value iterSpace, ValueRange initArgs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value iterSpace, ValueRange initArgs, I64BitSet crdUsedLvls);
  static IterateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value iterSpace, ValueRange initArgs, I64BitSet crdUsedLvls);
  static IterateOp create(::mlir::ImplicitLocOpBuilder &builder, Value iterSpace, ValueRange initArgs, I64BitSet crdUsedLvls);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::SmallVector<::mlir::Region *> getLoopRegions();
  ::llvm::MutableArrayRef<::mlir::OpOperand> getInitsMutable();
  ::mlir::Block::BlockArgListType getRegionIterArgs();
  ::std::optional<::llvm::MutableArrayRef<::mlir::OpOperand>> getYieldedValuesMutable();
  ::std::optional<::mlir::ResultRange> getLoopResults();
  ::mlir::OperandRange getEntrySuccessorOperands(::mlir::RegionSuccessor successor);
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
  unsigned getSpaceDim() {
    return getIterSpace().getType().getSpaceDim();
  }
  BlockArgument getIterator() {
    return getRegion().getArguments().back();
  }
  std::optional<BlockArgument> getLvlCrd(Level lvl) {
    if (getCrdUsedLvls()[lvl]) {
      uint64_t mask = (static_cast<uint64_t>(0x01u) << lvl) - 1;
      return getCrds()[llvm::popcount(mask & getCrdUsedLvls())];
    }
    return std::nullopt;
  }
  Block::BlockArgListType getCrds() {
    // User-provided iteration arguments -> coords -> iterator.
    return getRegion().getArguments().slice(getNumRegionIterArgs(), getCrdUsedLvls().count());
  }
  unsigned getNumRegionIterArgs() {
    return getRegion().getArguments().size() - 1 - getCrdUsedLvls().count();
  }
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::IterateOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::AssembleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AssembleOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AssembleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.assemble", odsAttrs.getContext());
  }

  AssembleOpGenericAdaptorBase(AssembleOp op);

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
class AssembleOpGenericAdaptor : public detail::AssembleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AssembleOpGenericAdaptorBase;
  static constexpr int odsIndex_levels = 0;
  static constexpr int odsIndex_values = 1;
public:
  AssembleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AssembleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AssembleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AssembleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AssembleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AssembleOpGenericAdaptor(RangeT values, const AssembleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AssembleOp, typename = std::enable_if_t<std::is_same_v<LateInst, AssembleOp>>>
  AssembleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getLevels() {
    return getODSOperands(0);
  }

  ValueT getValues() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AssembleOpAdaptor : public AssembleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AssembleOpGenericAdaptor::AssembleOpGenericAdaptor;
  AssembleOpAdaptor(AssembleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AssembleOp : public ::mlir::Op<AssembleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AssembleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AssembleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_levels = 0;
  static constexpr int odsIndex_values = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.assemble");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getLevels() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(1).begin());
  }

  ::mlir::MutableOperandRange getLevelsMutable();
  ::mlir::OpOperand &getValuesMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange levels, ::mlir::Value values);
  static AssembleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange levels, ::mlir::Value values);
  static AssembleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange levels, ::mlir::Value values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange levels, ::mlir::Value values);
  static AssembleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange levels, ::mlir::Value values);
  static AssembleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange levels, ::mlir::Value values);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssembleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssembleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssembleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssembleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::AssembleOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::BinaryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BinaryOpGenericAdaptorBase {
public:
  struct Properties {
    using left_identityTy = ::mlir::UnitAttr;
    left_identityTy left_identity;

    auto getLeftIdentity() const {
      auto &propStorage = this->left_identity;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setLeftIdentity(const ::mlir::UnitAttr &propValue) {
      this->left_identity = propValue;
    }
    using right_identityTy = ::mlir::UnitAttr;
    right_identityTy right_identity;

    auto getRightIdentity() const {
      auto &propStorage = this->right_identity;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setRightIdentity(const ::mlir::UnitAttr &propValue) {
      this->right_identity = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.left_identity == this->left_identity &&
        rhs.right_identity == this->right_identity &&
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
  BinaryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.binary", odsAttrs.getContext());
  }

  BinaryOpGenericAdaptorBase(BinaryOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getLeftIdentityAttr();
  bool getLeftIdentity();
  ::mlir::UnitAttr getRightIdentityAttr();
  bool getRightIdentity();
  ::mlir::Region &getOverlapRegion() {
    return *odsRegions[0];
  }

  ::mlir::Region &getLeftRegion() {
    return *odsRegions[1];
  }

  ::mlir::Region &getRightRegion() {
    return *odsRegions[2];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class BinaryOpGenericAdaptor : public detail::BinaryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BinaryOpGenericAdaptorBase;
  static constexpr int odsIndex_x = 0;
  static constexpr int odsIndex_y = 1;
public:
  BinaryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BinaryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : BinaryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BinaryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BinaryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BinaryOpGenericAdaptor(RangeT values, const BinaryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BinaryOp, typename = std::enable_if_t<std::is_same_v<LateInst, BinaryOp>>>
  BinaryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getX() {
    return (*getODSOperands(0).begin());
  }

  ValueT getY() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BinaryOpAdaptor : public BinaryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BinaryOpGenericAdaptor::BinaryOpGenericAdaptor;
  BinaryOpAdaptor(BinaryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BinaryOp : public ::mlir::Op<BinaryOp, ::mlir::OpTrait::NRegions<3>::Impl, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BinaryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BinaryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_x = 0;
  static constexpr int odsIndex_y = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("left_identity"), ::llvm::StringRef("right_identity")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLeftIdentityAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLeftIdentityAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getRightIdentityAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getRightIdentityAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.binary");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getY() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getXMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getYMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::Region &getOverlapRegion() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getLeftRegion() {
    return (*this)->getRegion(1);
  }

  ::mlir::Region &getRightRegion() {
    return (*this)->getRegion(2);
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
  ::mlir::UnitAttr getLeftIdentityAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().left_identity);
  }

  bool getLeftIdentity();
  ::mlir::UnitAttr getRightIdentityAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().right_identity);
  }

  bool getRightIdentity();
  void setLeftIdentityAttr(::mlir::UnitAttr attr) {
    getProperties().left_identity = attr;
  }

  void setLeftIdentity(bool attrValue);
  void setRightIdentityAttr(::mlir::UnitAttr attr) {
    getProperties().right_identity = attr;
  }

  void setRightIdentity(bool attrValue);
  ::mlir::Attribute removeLeftIdentityAttr() {
      auto attr = getProperties().left_identity;
      getProperties().left_identity = {};
      return attr;
  }

  ::mlir::Attribute removeRightIdentityAttr() {
      auto attr = getProperties().right_identity;
      getProperties().right_identity = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value x, ::mlir::Value y, /*optional*/::mlir::UnitAttr left_identity, /*optional*/::mlir::UnitAttr right_identity = nullptr);
  static BinaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value x, ::mlir::Value y, /*optional*/::mlir::UnitAttr left_identity, /*optional*/::mlir::UnitAttr right_identity = nullptr);
  static BinaryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value x, ::mlir::Value y, /*optional*/::mlir::UnitAttr left_identity, /*optional*/::mlir::UnitAttr right_identity = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value y, /*optional*/::mlir::UnitAttr left_identity, /*optional*/::mlir::UnitAttr right_identity = nullptr);
  static BinaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value y, /*optional*/::mlir::UnitAttr left_identity, /*optional*/::mlir::UnitAttr right_identity = nullptr);
  static BinaryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value y, /*optional*/::mlir::UnitAttr left_identity, /*optional*/::mlir::UnitAttr right_identity = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value x, ::mlir::Value y, /*optional*/bool left_identity = false, /*optional*/bool right_identity = false);
  static BinaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value x, ::mlir::Value y, /*optional*/bool left_identity = false, /*optional*/bool right_identity = false);
  static BinaryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value x, ::mlir::Value y, /*optional*/bool left_identity = false, /*optional*/bool right_identity = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value y, /*optional*/bool left_identity = false, /*optional*/bool right_identity = false);
  static BinaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value y, /*optional*/bool left_identity = false, /*optional*/bool right_identity = false);
  static BinaryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value y, /*optional*/bool left_identity = false, /*optional*/bool right_identity = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BinaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BinaryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BinaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BinaryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::BinaryOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::CoIterateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoIterateOpGenericAdaptorBase {
public:
  struct Properties {
    using casesTy = ::mlir::ArrayAttr;
    casesTy cases;

    auto getCases() const {
      auto &propStorage = this->cases;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setCases(const ::mlir::ArrayAttr &propValue) {
      this->cases = propValue;
    }
    using crdUsedLvlsTy = ::mlir::IntegerAttr;
    crdUsedLvlsTy crdUsedLvls;

    auto getCrdUsedLvls() const {
      auto &propStorage = this->crdUsedLvls;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setCrdUsedLvls(const ::mlir::IntegerAttr &propValue) {
      this->crdUsedLvls = propValue;
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
        rhs.cases == this->cases &&
        rhs.crdUsedLvls == this->crdUsedLvls &&
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
  CoIterateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.coiterate", odsAttrs.getContext());
  }

  CoIterateOpGenericAdaptorBase(CoIterateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getCrdUsedLvlsAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().crdUsedLvls);
    return attr;
  }

  ::mlir::sparse_tensor::I64BitSet getCrdUsedLvls();
  ::mlir::ArrayAttr getCasesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().cases);
    return attr;
  }

  ::mlir::ArrayAttr getCases();
  ::mlir::RegionRange getCaseRegions() {
    return odsRegions.drop_front(0);
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class CoIterateOpGenericAdaptor : public detail::CoIterateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoIterateOpGenericAdaptorBase;
  static constexpr int odsIndex_iterSpaces = 0;
  static constexpr int odsIndex_initArgs = 1;
public:
  CoIterateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoIterateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CoIterateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoIterateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : CoIterateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoIterateOpGenericAdaptor(RangeT values, const CoIterateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoIterateOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoIterateOp>>>
  CoIterateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getIterSpaces() {
    return getODSOperands(0);
  }

  RangeT getInitArgs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CoIterateOpAdaptor : public CoIterateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoIterateOpGenericAdaptor::CoIterateOpGenericAdaptor;
  CoIterateOpAdaptor(CoIterateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoIterateOp : public ::mlir::Op<CoIterateOp, ::mlir::OpTrait::VariadicRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<sparse_tensor::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoIterateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoIterateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_iterSpaces = 0;
  static constexpr int odsIndex_initArgs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("cases"), ::llvm::StringRef("crdUsedLvls"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCasesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCasesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getCrdUsedLvlsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getCrdUsedLvlsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.coiterate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getIterSpaces() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getInitArgs() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getIterSpacesMutable();
  ::mlir::MutableOperandRange getInitArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
  }

  ::mlir::MutableArrayRef<::mlir::Region> getCaseRegions() {
    return (*this)->getRegions().drop_front(0);
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
  ::mlir::IntegerAttr getCrdUsedLvlsAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().crdUsedLvls);
  }

  ::mlir::sparse_tensor::I64BitSet getCrdUsedLvls();
  ::mlir::ArrayAttr getCasesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().cases);
  }

  ::mlir::ArrayAttr getCases();
  void setCrdUsedLvlsAttr(::mlir::IntegerAttr attr) {
    getProperties().crdUsedLvls = attr;
  }

  void setCrdUsedLvls(::mlir::sparse_tensor::I64BitSet attrValue);
  void setCasesAttr(::mlir::ArrayAttr attr) {
    getProperties().cases = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange iterSpace, ValueRange initArgs, unsigned numCases);
  static CoIterateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange iterSpace, ValueRange initArgs, unsigned numCases);
  static CoIterateOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange iterSpace, ValueRange initArgs, unsigned numCases);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ValueRange iterSpaces, ::mlir::ValueRange initArgs, ::mlir::IntegerAttr crdUsedLvls, ::mlir::ArrayAttr cases, unsigned caseRegionsCount);
  static CoIterateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ValueRange iterSpaces, ::mlir::ValueRange initArgs, ::mlir::IntegerAttr crdUsedLvls, ::mlir::ArrayAttr cases, unsigned caseRegionsCount);
  static CoIterateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ValueRange iterSpaces, ::mlir::ValueRange initArgs, ::mlir::IntegerAttr crdUsedLvls, ::mlir::ArrayAttr cases, unsigned caseRegionsCount);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::ValueRange iterSpaces, ::mlir::ValueRange initArgs, ::mlir::sparse_tensor::I64BitSet crdUsedLvls, ::mlir::ArrayAttr cases, unsigned caseRegionsCount);
  static CoIterateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::ValueRange iterSpaces, ::mlir::ValueRange initArgs, ::mlir::sparse_tensor::I64BitSet crdUsedLvls, ::mlir::ArrayAttr cases, unsigned caseRegionsCount);
  static CoIterateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::ValueRange iterSpaces, ::mlir::ValueRange initArgs, ::mlir::sparse_tensor::I64BitSet crdUsedLvls, ::mlir::ArrayAttr cases, unsigned caseRegionsCount);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static CoIterateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static CoIterateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  static CoIterateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  static CoIterateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
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
  unsigned getSpaceDim() {
    return llvm::cast<::mlir::sparse_tensor::IterSpaceType>(
               getIterSpaces().front().getType())
        .getSpaceDim();
  }
  I64BitSet getRegionDefinedSpace(unsigned regionIdx) {
    return I64BitSet(llvm::cast<IntegerAttr>(getCases()[regionIdx])
                         .getValue().getZExtValue());
  }
  auto getRegionDefinedSpaces() {
    return llvm::map_range(getCases().getValue(), [](Attribute attr) {
      return I64BitSet(llvm::cast<IntegerAttr>(attr).getValue().getZExtValue());
    });
  }

  // The block arguments starts with user-provided iteration arguments,
  // follows by referenced coordinates and ends with iterators.
  Block::BlockArgListType getCrds(unsigned regionIdx) {
    return getRegion(regionIdx).getArguments()
        .slice(getNumRegionIterArgs(), getCrdUsedLvls().count());
  }
  unsigned getNumRegionIterArgs() {
    return getInitArgs().size();
  }
  Block::BlockArgListType getRegionIterArgs(unsigned regionIdx) {
    return getRegion(regionIdx).getArguments()
        .take_front(getNumRegionIterArgs());
  }
  Block::BlockArgListType getRegionIterators(unsigned regionIdx) {
    return getRegion(regionIdx).getArguments()
        .take_back(getRegionDefinedSpace(regionIdx).count());
  }
  ValueRange getYieldedValues(unsigned regionIdx);

  // Returns a vector of regions that are the `sub-cases` of the given case region.
  // E.g., `case %it1, _, %it3` is a subcase of `case %it1, %it2, %it3`.
  SmallVector<Region *> getSubCasesOf(unsigned regionIdx);
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::CoIterateOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::CompressOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CompressOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CompressOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.compress", odsAttrs.getContext());
  }

  CompressOpGenericAdaptorBase(CompressOp op);

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
class CompressOpGenericAdaptor : public detail::CompressOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CompressOpGenericAdaptorBase;
  static constexpr int odsIndex_values = 0;
  static constexpr int odsIndex_filled = 1;
  static constexpr int odsIndex_added = 2;
  static constexpr int odsIndex_count = 3;
  static constexpr int odsIndex_tensor = 4;
  static constexpr int odsIndex_lvlCoords = 5;
public:
  CompressOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CompressOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CompressOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CompressOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CompressOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CompressOpGenericAdaptor(RangeT values, const CompressOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CompressOp, typename = std::enable_if_t<std::is_same_v<LateInst, CompressOp>>>
  CompressOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValues() {
    return (*getODSOperands(0).begin());
  }

  ValueT getFilled() {
    return (*getODSOperands(1).begin());
  }

  ValueT getAdded() {
    return (*getODSOperands(2).begin());
  }

  ValueT getCount() {
    return (*getODSOperands(3).begin());
  }

  ValueT getTensor() {
    return (*getODSOperands(4).begin());
  }

  RangeT getLvlCoords() {
    return getODSOperands(5);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CompressOpAdaptor : public CompressOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CompressOpGenericAdaptor::CompressOpGenericAdaptor;
  CompressOpAdaptor(CompressOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CompressOp : public ::mlir::Op<CompressOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<5>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CompressOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CompressOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_values = 0;
  static constexpr int odsIndex_filled = 1;
  static constexpr int odsIndex_added = 2;
  static constexpr int odsIndex_count = 3;
  static constexpr int odsIndex_tensor = 4;
  static constexpr int odsIndex_lvlCoords = 5;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.compress");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getFilled() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getAdded() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCount() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(4).begin());
  }

  ::mlir::Operation::operand_range getLvlCoords() {
    return getODSOperands(5);
  }

  ::mlir::OpOperand &getValuesMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getFilledMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAddedMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getCountMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTensorMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getLvlCoordsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value values, ::mlir::Value filled, ::mlir::Value added, ::mlir::Value count, ::mlir::Value tensor, ::mlir::ValueRange lvlCoords);
  static CompressOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value values, ::mlir::Value filled, ::mlir::Value added, ::mlir::Value count, ::mlir::Value tensor, ::mlir::ValueRange lvlCoords);
  static CompressOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value values, ::mlir::Value filled, ::mlir::Value added, ::mlir::Value count, ::mlir::Value tensor, ::mlir::ValueRange lvlCoords);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value values, ::mlir::Value filled, ::mlir::Value added, ::mlir::Value count, ::mlir::Value tensor, ::mlir::ValueRange lvlCoords);
  static CompressOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value values, ::mlir::Value filled, ::mlir::Value added, ::mlir::Value count, ::mlir::Value tensor, ::mlir::ValueRange lvlCoords);
  static CompressOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value values, ::mlir::Value filled, ::mlir::Value added, ::mlir::Value count, ::mlir::Value tensor, ::mlir::ValueRange lvlCoords);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value values, ::mlir::Value filled, ::mlir::Value added, ::mlir::Value count, ::mlir::Value tensor, ::mlir::ValueRange lvlCoords);
  static CompressOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value values, ::mlir::Value filled, ::mlir::Value added, ::mlir::Value count, ::mlir::Value tensor, ::mlir::ValueRange lvlCoords);
  static CompressOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value values, ::mlir::Value filled, ::mlir::Value added, ::mlir::Value count, ::mlir::Value tensor, ::mlir::ValueRange lvlCoords);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompressOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompressOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompressOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompressOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompressOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompressOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompressOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompressOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::CompressOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ConcatenateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConcatenateOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::IntegerAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setDimension(const ::mlir::IntegerAttr &propValue) {
      this->dimension = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
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
  ConcatenateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.concatenate", odsAttrs.getContext());
  }

  ConcatenateOpGenericAdaptorBase(ConcatenateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().dimension);
    return attr;
  }

  ::mlir::sparse_tensor::Dimension getDimension();
};

} // namespace detail
template <typename RangeT>
class ConcatenateOpGenericAdaptor : public detail::ConcatenateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConcatenateOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  ConcatenateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConcatenateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ConcatenateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConcatenateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConcatenateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConcatenateOpGenericAdaptor(RangeT values, const ConcatenateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConcatenateOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConcatenateOp>>>
  ConcatenateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ConcatenateOpAdaptor : public ConcatenateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConcatenateOpGenericAdaptor::ConcatenateOpGenericAdaptor;
  ConcatenateOpAdaptor(ConcatenateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConcatenateOp : public ::mlir::Op<ConcatenateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::sparse_tensor::StageWithSortSparseOp::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConcatenateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConcatenateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.concatenate");
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
  ::mlir::IntegerAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().dimension);
  }

  ::mlir::sparse_tensor::Dimension getDimension();
  void setDimensionAttr(::mlir::IntegerAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(::mlir::sparse_tensor::Dimension attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::IntegerAttr dimension);
  static ConcatenateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::IntegerAttr dimension);
  static ConcatenateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::IntegerAttr dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::IntegerAttr dimension);
  static ConcatenateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::IntegerAttr dimension);
  static ConcatenateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::IntegerAttr dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::sparse_tensor::Dimension dimension);
  static ConcatenateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::sparse_tensor::Dimension dimension);
  static ConcatenateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::sparse_tensor::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::sparse_tensor::Dimension dimension);
  static ConcatenateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::sparse_tensor::Dimension dimension);
  static ConcatenateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::sparse_tensor::Dimension dimension);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConcatenateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConcatenateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConcatenateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConcatenateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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
  // Whether the concatenate can be done by a single step or it would require
  // an extra sort. Inherited from StageWithSortSparseOpInterface.
  bool needsExtraSort();
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ConcatenateOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ConvertOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConvertOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ConvertOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.convert", odsAttrs.getContext());
  }

  ConvertOpGenericAdaptorBase(ConvertOp op);

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
class ConvertOpGenericAdaptor : public detail::ConvertOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConvertOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  ConvertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConvertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ConvertOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConvertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConvertOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConvertOpGenericAdaptor(RangeT values, const ConvertOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConvertOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConvertOp>>>
  ConvertOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ConvertOpAdaptor : public ConvertOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConvertOpGenericAdaptor::ConvertOpGenericAdaptor;
  ConvertOpAdaptor(ConvertOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConvertOp : public ::mlir::Op<ConvertOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::sparse_tensor::StageWithSortSparseOp::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConvertOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConvertOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.convert");
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

  ::mlir::TypedValue<::mlir::RankedTensorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::Value source);
  static ConvertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::Value source);
  static ConvertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static ConvertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static ConvertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConvertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConvertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConvertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConvertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  // Whether the convert can be done by a single step or it would require
  // an extra sort. Inherited from StageWithSortSparseOpInterface.
  bool needsExtraSort();
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ConvertOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::CrdTranslateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CrdTranslateOpGenericAdaptorBase {
public:
  struct Properties {
    using directionTy = ::mlir::sparse_tensor::CrdTransDirectionKindAttr;
    directionTy direction;

    auto getDirection() const {
      auto &propStorage = this->direction;
      return ::llvm::cast<::mlir::sparse_tensor::CrdTransDirectionKindAttr>(propStorage);
    }
    void setDirection(const ::mlir::sparse_tensor::CrdTransDirectionKindAttr &propValue) {
      this->direction = propValue;
    }
    using encoderTy = ::mlir::sparse_tensor::SparseTensorEncodingAttr;
    encoderTy encoder;

    auto getEncoder() const {
      auto &propStorage = this->encoder;
      return ::llvm::cast<::mlir::sparse_tensor::SparseTensorEncodingAttr>(propStorage);
    }
    void setEncoder(const ::mlir::sparse_tensor::SparseTensorEncodingAttr &propValue) {
      this->encoder = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.direction == this->direction &&
        rhs.encoder == this->encoder &&
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
  CrdTranslateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.crd_translate", odsAttrs.getContext());
  }

  CrdTranslateOpGenericAdaptorBase(CrdTranslateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sparse_tensor::CrdTransDirectionKindAttr getDirectionAttr() {
    auto attr = ::llvm::cast<::mlir::sparse_tensor::CrdTransDirectionKindAttr>(getProperties().direction);
    return attr;
  }

  ::mlir::sparse_tensor::CrdTransDirectionKind getDirection();
  ::mlir::sparse_tensor::SparseTensorEncodingAttr getEncoderAttr() {
    auto attr = ::llvm::cast<::mlir::sparse_tensor::SparseTensorEncodingAttr>(getProperties().encoder);
    return attr;
  }

  ::mlir::sparse_tensor::SparseTensorEncodingAttr getEncoder();
};

} // namespace detail
template <typename RangeT>
class CrdTranslateOpGenericAdaptor : public detail::CrdTranslateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CrdTranslateOpGenericAdaptorBase;
  static constexpr int odsIndex_in_crds = 0;
public:
  CrdTranslateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CrdTranslateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CrdTranslateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CrdTranslateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CrdTranslateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CrdTranslateOpGenericAdaptor(RangeT values, const CrdTranslateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CrdTranslateOp, typename = std::enable_if_t<std::is_same_v<LateInst, CrdTranslateOp>>>
  CrdTranslateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInCrds() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CrdTranslateOpAdaptor : public CrdTranslateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CrdTranslateOpGenericAdaptor::CrdTranslateOpGenericAdaptor;
  CrdTranslateOpAdaptor(CrdTranslateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CrdTranslateOp : public ::mlir::Op<CrdTranslateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CrdTranslateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CrdTranslateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_in_crds = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("direction"), ::llvm::StringRef("encoder")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDirectionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDirectionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getEncoderAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getEncoderAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.crd_translate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInCrds() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getInCrdsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getOutCrds() {
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
  ::mlir::sparse_tensor::CrdTransDirectionKindAttr getDirectionAttr() {
    return ::llvm::cast<::mlir::sparse_tensor::CrdTransDirectionKindAttr>(getProperties().direction);
  }

  ::mlir::sparse_tensor::CrdTransDirectionKind getDirection();
  ::mlir::sparse_tensor::SparseTensorEncodingAttr getEncoderAttr() {
    return ::llvm::cast<::mlir::sparse_tensor::SparseTensorEncodingAttr>(getProperties().encoder);
  }

  ::mlir::sparse_tensor::SparseTensorEncodingAttr getEncoder();
  void setDirectionAttr(::mlir::sparse_tensor::CrdTransDirectionKindAttr attr) {
    getProperties().direction = attr;
  }

  void setDirection(::mlir::sparse_tensor::CrdTransDirectionKind attrValue);
  void setEncoderAttr(::mlir::sparse_tensor::SparseTensorEncodingAttr attr) {
    getProperties().encoder = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange out_crds, ::mlir::ValueRange in_crds, ::mlir::sparse_tensor::CrdTransDirectionKindAttr direction, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoder);
  static CrdTranslateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange out_crds, ::mlir::ValueRange in_crds, ::mlir::sparse_tensor::CrdTransDirectionKindAttr direction, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoder);
  static CrdTranslateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange out_crds, ::mlir::ValueRange in_crds, ::mlir::sparse_tensor::CrdTransDirectionKindAttr direction, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange out_crds, ::mlir::ValueRange in_crds, ::mlir::sparse_tensor::CrdTransDirectionKind direction, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoder);
  static CrdTranslateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange out_crds, ::mlir::ValueRange in_crds, ::mlir::sparse_tensor::CrdTransDirectionKind direction, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoder);
  static CrdTranslateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange out_crds, ::mlir::ValueRange in_crds, ::mlir::sparse_tensor::CrdTransDirectionKind direction, ::mlir::sparse_tensor::SparseTensorEncodingAttr encoder);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CrdTranslateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CrdTranslateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CrdTranslateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CrdTranslateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
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
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::CrdTranslateOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::DisassembleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DisassembleOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DisassembleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.disassemble", odsAttrs.getContext());
  }

  DisassembleOpGenericAdaptorBase(DisassembleOp op);

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
class DisassembleOpGenericAdaptor : public detail::DisassembleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DisassembleOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_out_levels = 1;
  static constexpr int odsIndex_out_values = 2;
public:
  DisassembleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DisassembleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DisassembleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DisassembleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DisassembleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DisassembleOpGenericAdaptor(RangeT values, const DisassembleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DisassembleOp, typename = std::enable_if_t<std::is_same_v<LateInst, DisassembleOp>>>
  DisassembleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOutLevels() {
    return getODSOperands(1);
  }

  ValueT getOutValues() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DisassembleOpAdaptor : public DisassembleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DisassembleOpGenericAdaptor::DisassembleOpGenericAdaptor;
  DisassembleOpAdaptor(DisassembleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DisassembleOp : public ::mlir::Op<DisassembleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DisassembleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DisassembleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_out_levels = 1;
  static constexpr int odsIndex_out_values = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.disassemble");
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

  ::mlir::Operation::operand_range getOutLevels() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getOutValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getTensorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getOutLevelsMutable();
  ::mlir::OpOperand &getOutValuesMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getRetLevels() {
    return getODSResults(0);
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getRetValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(1).begin());
  }

  ::mlir::Operation::result_range getLvlLens() {
    return getODSResults(2);
  }

  ::mlir::TypedValue<::mlir::Type> getValLen() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(3).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange ret_levels, ::mlir::Type ret_values, ::mlir::TypeRange lvl_lens, ::mlir::Type val_len, ::mlir::Value tensor, ::mlir::ValueRange out_levels, ::mlir::Value out_values);
  static DisassembleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange ret_levels, ::mlir::Type ret_values, ::mlir::TypeRange lvl_lens, ::mlir::Type val_len, ::mlir::Value tensor, ::mlir::ValueRange out_levels, ::mlir::Value out_values);
  static DisassembleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange ret_levels, ::mlir::Type ret_values, ::mlir::TypeRange lvl_lens, ::mlir::Type val_len, ::mlir::Value tensor, ::mlir::ValueRange out_levels, ::mlir::Value out_values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::ValueRange out_levels, ::mlir::Value out_values);
  static DisassembleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::ValueRange out_levels, ::mlir::Value out_values);
  static DisassembleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::ValueRange out_levels, ::mlir::Value out_values);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DisassembleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DisassembleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DisassembleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DisassembleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::DisassembleOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ExpandOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExpandOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ExpandOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.expand", odsAttrs.getContext());
  }

  ExpandOpGenericAdaptorBase(ExpandOp op);

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
class ExpandOpGenericAdaptor : public detail::ExpandOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExpandOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  ExpandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExpandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExpandOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExpandOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExpandOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExpandOpGenericAdaptor(RangeT values, const ExpandOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExpandOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExpandOp>>>
  ExpandOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ExpandOpAdaptor : public ExpandOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExpandOpGenericAdaptor::ExpandOpGenericAdaptor;
  ExpandOpAdaptor(ExpandOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExpandOp : public ::mlir::Op<ExpandOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<4>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExpandOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExpandOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.expand");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::Type> getValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getFilled() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getAdded() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCount() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(3).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type values, ::mlir::Type filled, ::mlir::Type added, ::mlir::Type count, ::mlir::Value tensor);
  static ExpandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type values, ::mlir::Type filled, ::mlir::Type added, ::mlir::Type count, ::mlir::Value tensor);
  static ExpandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type values, ::mlir::Type filled, ::mlir::Type added, ::mlir::Type count, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static ExpandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static ExpandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExpandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExpandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExpandOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExpandOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ExpandOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ForeachOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ForeachOpGenericAdaptorBase {
public:
  struct Properties {
    using orderTy = ::mlir::AffineMapAttr;
    orderTy order;

    auto getOrder() const {
      auto &propStorage = this->order;
      return ::llvm::dyn_cast_or_null<::mlir::AffineMapAttr>(propStorage);
    }
    void setOrder(const ::mlir::AffineMapAttr &propValue) {
      this->order = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.order == this->order &&
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
  ForeachOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.foreach", odsAttrs.getContext());
  }

  ForeachOpGenericAdaptorBase(ForeachOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getOrderAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::AffineMapAttr>(getProperties().order);
    return attr;
  }

  ::std::optional< ::mlir::AffineMap > getOrder();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ForeachOpGenericAdaptor : public detail::ForeachOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ForeachOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_initArgs = 1;
public:
  ForeachOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ForeachOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ForeachOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ForeachOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ForeachOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ForeachOpGenericAdaptor(RangeT values, const ForeachOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ForeachOp, typename = std::enable_if_t<std::is_same_v<LateInst, ForeachOp>>>
  ForeachOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getInitArgs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ForeachOpAdaptor : public ForeachOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ForeachOpGenericAdaptor::ForeachOpGenericAdaptor;
  ForeachOpAdaptor(ForeachOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ForeachOp : public ::mlir::Op<ForeachOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ForeachOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ForeachOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_initArgs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("order")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOrderAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOrderAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.foreach");
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

  ::mlir::Operation::operand_range getInitArgs() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getTensorMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getInitArgsMutable();
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
  ::mlir::AffineMapAttr getOrderAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::AffineMapAttr>(getProperties().order);
  }

  ::std::optional< ::mlir::AffineMap > getOrder();
  void setOrderAttr(::mlir::AffineMapAttr attr) {
    getProperties().order = attr;
  }

  void setOrder(::std::optional<::mlir::AffineMap> attrValue);
  ::mlir::Attribute removeOrderAttr() {
      auto attr = getProperties().order;
      getProperties().order = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value tensor, ValueRange iterArgs, AffineMapAttr order, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> odsArg3);
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value tensor, ValueRange iterArgs, AffineMapAttr order, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> odsArg3);
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, Value tensor, ValueRange iterArgs, AffineMapAttr order, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> odsArg3);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value tensor, AffineMapAttr order, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> bodyBuilder);
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value tensor, AffineMapAttr order, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> bodyBuilder);
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, Value tensor, AffineMapAttr order, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> bodyBuilder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value tensor, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> bodyBuilder);
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value tensor, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> bodyBuilder);
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, Value tensor, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> bodyBuilder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value tensor, ValueRange iterArgs, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> bodyBuilder);
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value tensor, ValueRange iterArgs, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> bodyBuilder);
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, Value tensor, ValueRange iterArgs, function_ref<void(OpBuilder &, Location, ValueRange, Value, ValueRange)> bodyBuilder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value tensor, ::mlir::ValueRange initArgs, /*optional*/::mlir::AffineMapAttr order);
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value tensor, ::mlir::ValueRange initArgs, /*optional*/::mlir::AffineMapAttr order);
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value tensor, ::mlir::ValueRange initArgs, /*optional*/::mlir::AffineMapAttr order);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ForeachOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ForeachOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ForeachOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::GetStorageSpecifierOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetStorageSpecifierOpGenericAdaptorBase {
public:
  struct Properties {
    using levelTy = ::mlir::IntegerAttr;
    levelTy level;

    auto getLevel() const {
      auto &propStorage = this->level;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setLevel(const ::mlir::IntegerAttr &propValue) {
      this->level = propValue;
    }
    using specifierKindTy = ::mlir::sparse_tensor::StorageSpecifierKindAttr;
    specifierKindTy specifierKind;

    auto getSpecifierKind() const {
      auto &propStorage = this->specifierKind;
      return ::llvm::cast<::mlir::sparse_tensor::StorageSpecifierKindAttr>(propStorage);
    }
    void setSpecifierKind(const ::mlir::sparse_tensor::StorageSpecifierKindAttr &propValue) {
      this->specifierKind = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.level == this->level &&
        rhs.specifierKind == this->specifierKind &&
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
  GetStorageSpecifierOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.storage_specifier.get", odsAttrs.getContext());
  }

  GetStorageSpecifierOpGenericAdaptorBase(GetStorageSpecifierOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sparse_tensor::StorageSpecifierKindAttr getSpecifierKindAttr() {
    auto attr = ::llvm::cast<::mlir::sparse_tensor::StorageSpecifierKindAttr>(getProperties().specifierKind);
    return attr;
  }

  ::mlir::sparse_tensor::StorageSpecifierKind getSpecifierKind();
  ::mlir::IntegerAttr getLevelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().level);
    return attr;
  }

  ::std::optional<::mlir::sparse_tensor::Level> getLevel();
};

} // namespace detail
template <typename RangeT>
class GetStorageSpecifierOpGenericAdaptor : public detail::GetStorageSpecifierOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetStorageSpecifierOpGenericAdaptorBase;
  static constexpr int odsIndex_specifier = 0;
public:
  GetStorageSpecifierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetStorageSpecifierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetStorageSpecifierOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetStorageSpecifierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetStorageSpecifierOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetStorageSpecifierOpGenericAdaptor(RangeT values, const GetStorageSpecifierOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetStorageSpecifierOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetStorageSpecifierOp>>>
  GetStorageSpecifierOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSpecifier() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetStorageSpecifierOpAdaptor : public GetStorageSpecifierOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetStorageSpecifierOpGenericAdaptor::GetStorageSpecifierOpGenericAdaptor;
  GetStorageSpecifierOpAdaptor(GetStorageSpecifierOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetStorageSpecifierOp : public ::mlir::Op<GetStorageSpecifierOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetStorageSpecifierOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetStorageSpecifierOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_specifier = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("level"), ::llvm::StringRef("specifierKind")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLevelAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLevelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSpecifierKindAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSpecifierKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.storage_specifier.get");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType> getSpecifier() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getSpecifierMutable() {
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::sparse_tensor::StorageSpecifierKindAttr getSpecifierKindAttr() {
    return ::llvm::cast<::mlir::sparse_tensor::StorageSpecifierKindAttr>(getProperties().specifierKind);
  }

  ::mlir::sparse_tensor::StorageSpecifierKind getSpecifierKind();
  ::mlir::IntegerAttr getLevelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().level);
  }

  ::std::optional<::mlir::sparse_tensor::Level> getLevel();
  void setSpecifierKindAttr(::mlir::sparse_tensor::StorageSpecifierKindAttr attr) {
    getProperties().specifierKind = attr;
  }

  void setSpecifierKind(::mlir::sparse_tensor::StorageSpecifierKind attrValue);
  void setLevelAttr(::mlir::IntegerAttr attr) {
    getProperties().level = attr;
  }

  void setLevel(::std::optional<::mlir::sparse_tensor::Level> attrValue);
  ::mlir::Attribute removeLevelAttr() {
      auto attr = getProperties().level;
      getProperties().level = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level);
  static GetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::GetStorageSpecifierOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::HasRuntimeLibraryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HasRuntimeLibraryOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  HasRuntimeLibraryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.has_runtime_library", odsAttrs.getContext());
  }

  HasRuntimeLibraryOpGenericAdaptorBase(HasRuntimeLibraryOp op);

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
class HasRuntimeLibraryOpGenericAdaptor : public detail::HasRuntimeLibraryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HasRuntimeLibraryOpGenericAdaptorBase;
public:
  HasRuntimeLibraryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HasRuntimeLibraryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : HasRuntimeLibraryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HasRuntimeLibraryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HasRuntimeLibraryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HasRuntimeLibraryOpGenericAdaptor(RangeT values, const HasRuntimeLibraryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HasRuntimeLibraryOp, typename = std::enable_if_t<std::is_same_v<LateInst, HasRuntimeLibraryOp>>>
  HasRuntimeLibraryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class HasRuntimeLibraryOpAdaptor : public HasRuntimeLibraryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HasRuntimeLibraryOpGenericAdaptor::HasRuntimeLibraryOpGenericAdaptor;
  HasRuntimeLibraryOpAdaptor(HasRuntimeLibraryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HasRuntimeLibraryOp : public ::mlir::Op<HasRuntimeLibraryOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HasRuntimeLibraryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HasRuntimeLibraryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.has_runtime_library");
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

  ::mlir::TypedValue<::mlir::IntegerType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result);
  static HasRuntimeLibraryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result);
  static HasRuntimeLibraryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static HasRuntimeLibraryOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static HasRuntimeLibraryOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static HasRuntimeLibraryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static HasRuntimeLibraryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HasRuntimeLibraryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HasRuntimeLibraryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HasRuntimeLibraryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HasRuntimeLibraryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HasRuntimeLibraryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HasRuntimeLibraryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HasRuntimeLibraryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HasRuntimeLibraryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::HasRuntimeLibraryOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::LoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoadOpGenericAdaptorBase {
public:
  struct Properties {
    using hasInsertsTy = ::mlir::UnitAttr;
    hasInsertsTy hasInserts;

    auto getHasInserts() const {
      auto &propStorage = this->hasInserts;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setHasInserts(const ::mlir::UnitAttr &propValue) {
      this->hasInserts = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.hasInserts == this->hasInserts &&
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
      odsOpName.emplace("sparse_tensor.load", odsAttrs.getContext());
  }

  LoadOpGenericAdaptorBase(LoadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getHasInsertsAttr();
  bool getHasInserts();
};

} // namespace detail
template <typename RangeT>
class LoadOpGenericAdaptor : public detail::LoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoadOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
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

  ValueT getTensor() {
    return (*getODSOperands(0).begin());
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
class LoadOp : public ::mlir::Op<LoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("hasInserts")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getHasInsertsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getHasInsertsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.load");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
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
  ::mlir::UnitAttr getHasInsertsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().hasInserts);
  }

  bool getHasInserts();
  void setHasInsertsAttr(::mlir::UnitAttr attr) {
    getProperties().hasInserts = attr;
  }

  void setHasInserts(bool attrValue);
  ::mlir::Attribute removeHasInsertsAttr() {
      auto attr = getProperties().hasInserts;
      getProperties().hasInserts = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr hasInserts);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr hasInserts);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr hasInserts);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr hasInserts);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr hasInserts);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr hasInserts);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr hasInserts);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr hasInserts);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/::mlir::UnitAttr hasInserts);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, /*optional*/bool hasInserts = false);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, /*optional*/bool hasInserts = false);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, /*optional*/bool hasInserts = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, /*optional*/bool hasInserts = false);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, /*optional*/bool hasInserts = false);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, /*optional*/bool hasInserts = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/bool hasInserts = false);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/bool hasInserts = false);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, /*optional*/bool hasInserts = false);
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
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::LoadOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::LvlOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LvlOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LvlOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.lvl", odsAttrs.getContext());
  }

  LvlOpGenericAdaptorBase(LvlOp op);

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
class LvlOpGenericAdaptor : public detail::LvlOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LvlOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_index = 1;
public:
  LvlOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LvlOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LvlOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LvlOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LvlOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LvlOpGenericAdaptor(RangeT values, const LvlOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LvlOp, typename = std::enable_if_t<std::is_same_v<LateInst, LvlOp>>>
  LvlOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class LvlOpAdaptor : public LvlOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LvlOpGenericAdaptor::LvlOpGenericAdaptor;
  LvlOpAdaptor(LvlOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LvlOp : public ::mlir::Op<LvlOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LvlOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LvlOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  static constexpr int odsIndex_index = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.lvl");
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
  static LvlOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value source, int64_t index);
  static LvlOp create(::mlir::ImplicitLocOpBuilder &builder, Value source, int64_t index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source, ::mlir::Value index);
  static LvlOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source, ::mlir::Value index);
  static LvlOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source, ::mlir::Value index);
  static LvlOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source, ::mlir::Value index);
  static LvlOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value index);
  static LvlOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value index);
  static LvlOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source, ::mlir::Value index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LvlOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LvlOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LvlOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LvlOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LvlOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LvlOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LvlOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LvlOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// Helper function to get the index as a simple integer if it is constant.
  std::optional<uint64_t> getConstantLvlIndex();

  /// Interface method for ConditionallySpeculatable.
  Speculation::Speculatability getSpeculatability();
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::LvlOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::NewOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NewOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  NewOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.new", odsAttrs.getContext());
  }

  NewOpGenericAdaptorBase(NewOp op);

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
class NewOpGenericAdaptor : public detail::NewOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NewOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  NewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : NewOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NewOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NewOpGenericAdaptor(RangeT values, const NewOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NewOp, typename = std::enable_if_t<std::is_same_v<LateInst, NewOp>>>
  NewOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class NewOpAdaptor : public NewOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NewOpGenericAdaptor::NewOpGenericAdaptor;
  NewOpAdaptor(NewOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NewOp : public ::mlir::Op<NewOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NewOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NewOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.new");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source);
  static NewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source);
  static NewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static NewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static NewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::NewOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::NumberOfEntriesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NumberOfEntriesOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  NumberOfEntriesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.number_of_entries", odsAttrs.getContext());
  }

  NumberOfEntriesOpGenericAdaptorBase(NumberOfEntriesOp op);

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
class NumberOfEntriesOpGenericAdaptor : public detail::NumberOfEntriesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NumberOfEntriesOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  NumberOfEntriesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NumberOfEntriesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : NumberOfEntriesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NumberOfEntriesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NumberOfEntriesOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NumberOfEntriesOpGenericAdaptor(RangeT values, const NumberOfEntriesOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NumberOfEntriesOp, typename = std::enable_if_t<std::is_same_v<LateInst, NumberOfEntriesOp>>>
  NumberOfEntriesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class NumberOfEntriesOpAdaptor : public NumberOfEntriesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NumberOfEntriesOpGenericAdaptor::NumberOfEntriesOpGenericAdaptor;
  NumberOfEntriesOpAdaptor(NumberOfEntriesOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NumberOfEntriesOp : public ::mlir::Op<NumberOfEntriesOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NumberOfEntriesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NumberOfEntriesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.number_of_entries");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor);
  static NumberOfEntriesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor);
  static NumberOfEntriesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor);
  static NumberOfEntriesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor);
  static NumberOfEntriesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static NumberOfEntriesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static NumberOfEntriesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NumberOfEntriesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NumberOfEntriesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NumberOfEntriesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NumberOfEntriesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NumberOfEntriesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NumberOfEntriesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NumberOfEntriesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NumberOfEntriesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::NumberOfEntriesOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::OutOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OutOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  OutOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.out", odsAttrs.getContext());
  }

  OutOpGenericAdaptorBase(OutOp op);

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
class OutOpGenericAdaptor : public detail::OutOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OutOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_dest = 1;
public:
  OutOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OutOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : OutOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OutOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OutOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OutOpGenericAdaptor(RangeT values, const OutOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OutOp, typename = std::enable_if_t<std::is_same_v<LateInst, OutOp>>>
  OutOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getDest() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class OutOpAdaptor : public OutOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OutOpGenericAdaptor::OutOpGenericAdaptor;
  OutOpAdaptor(OutOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OutOp : public ::mlir::Op<OutOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OutOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OutOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  static constexpr int odsIndex_dest = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.out");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getTensorMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::Value dest);
  static OutOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::Value dest);
  static OutOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::Value dest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::Value dest);
  static OutOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::Value dest);
  static OutOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::Value dest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::OutOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::PrintOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PrintOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PrintOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.print", odsAttrs.getContext());
  }

  PrintOpGenericAdaptorBase(PrintOp op);

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
class PrintOpGenericAdaptor : public detail::PrintOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PrintOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
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

  ValueT getTensor() {
    return (*getODSOperands(0).begin());
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
class PrintOp : public ::mlir::Op<PrintOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PrintOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PrintOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.print");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::PrintOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::PushBackOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PushBackOpGenericAdaptorBase {
public:
  struct Properties {
    using inboundsTy = ::mlir::UnitAttr;
    inboundsTy inbounds;

    auto getInbounds() const {
      auto &propStorage = this->inbounds;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setInbounds(const ::mlir::UnitAttr &propValue) {
      this->inbounds = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inbounds == this->inbounds &&
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
  PushBackOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.push_back", odsAttrs.getContext());
  }

  PushBackOpGenericAdaptorBase(PushBackOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getInboundsAttr();
  bool getInbounds();
};

} // namespace detail
template <typename RangeT>
class PushBackOpGenericAdaptor : public detail::PushBackOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PushBackOpGenericAdaptorBase;
  static constexpr int odsIndex_curSize = 0;
  static constexpr int odsIndex_inBuffer = 1;
  static constexpr int odsIndex_value = 2;
  static constexpr int odsIndex_n = 3;
public:
  PushBackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PushBackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PushBackOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PushBackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PushBackOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PushBackOpGenericAdaptor(RangeT values, const PushBackOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PushBackOp, typename = std::enable_if_t<std::is_same_v<LateInst, PushBackOp>>>
  PushBackOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getCurSize() {
    return (*getODSOperands(0).begin());
  }

  ValueT getInBuffer() {
    return (*getODSOperands(1).begin());
  }

  ValueT getValue() {
    return (*getODSOperands(2).begin());
  }

  ValueT getN() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PushBackOpAdaptor : public PushBackOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PushBackOpGenericAdaptor::PushBackOpGenericAdaptor;
  PushBackOpAdaptor(PushBackOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PushBackOp : public ::mlir::Op<PushBackOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PushBackOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PushBackOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_curSize = 0;
  static constexpr int odsIndex_inBuffer = 1;
  static constexpr int odsIndex_value = 2;
  static constexpr int odsIndex_n = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inbounds")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInboundsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInboundsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.push_back");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getCurSize() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getInBuffer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getN() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IndexType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*operands.begin());
  }

  ::mlir::OpOperand &getCurSizeMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getInBufferMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getNMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getOutBuffer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getNewSize() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(1).begin());
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
  ::mlir::UnitAttr getInboundsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().inbounds);
  }

  bool getInbounds();
  void setInboundsAttr(::mlir::UnitAttr attr) {
    getProperties().inbounds = attr;
  }

  void setInbounds(bool attrValue);
  ::mlir::Attribute removeInboundsAttr() {
      auto attr = getProperties().inbounds;
      getProperties().inbounds = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value curSize, Value inBuffer, Value value);
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value curSize, Value inBuffer, Value value);
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, Value curSize, Value inBuffer, Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type outBuffer, ::mlir::Type newSize, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/::mlir::UnitAttr inbounds);
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type outBuffer, ::mlir::Type newSize, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/::mlir::UnitAttr inbounds);
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type outBuffer, ::mlir::Type newSize, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/::mlir::UnitAttr inbounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/::mlir::UnitAttr inbounds);
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/::mlir::UnitAttr inbounds);
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/::mlir::UnitAttr inbounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/::mlir::UnitAttr inbounds);
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/::mlir::UnitAttr inbounds);
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/::mlir::UnitAttr inbounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type outBuffer, ::mlir::Type newSize, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/bool inbounds = false);
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type outBuffer, ::mlir::Type newSize, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/bool inbounds = false);
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type outBuffer, ::mlir::Type newSize, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/bool inbounds = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/bool inbounds = false);
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/bool inbounds = false);
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/bool inbounds = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/bool inbounds = false);
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/bool inbounds = false);
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value curSize, ::mlir::Value inBuffer, ::mlir::Value value, /*optional*/::mlir::Value n, /*optional*/bool inbounds = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::PushBackOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ReduceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReduceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ReduceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.reduce", odsAttrs.getContext());
  }

  ReduceOpGenericAdaptorBase(ReduceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ReduceOpGenericAdaptor : public detail::ReduceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReduceOpGenericAdaptorBase;
  static constexpr int odsIndex_x = 0;
  static constexpr int odsIndex_y = 1;
  static constexpr int odsIndex_identity = 2;
public:
  ReduceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReduceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReduceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReduceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReduceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReduceOpGenericAdaptor(RangeT values, const ReduceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReduceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReduceOp>>>
  ReduceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getX() {
    return (*getODSOperands(0).begin());
  }

  ValueT getY() {
    return (*getODSOperands(1).begin());
  }

  ValueT getIdentity() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReduceOpAdaptor : public ReduceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReduceOpGenericAdaptor::ReduceOpGenericAdaptor;
  ReduceOpAdaptor(ReduceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReduceOp : public ::mlir::Op<ReduceOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReduceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReduceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_x = 0;
  static constexpr int odsIndex_y = 1;
  static constexpr int odsIndex_identity = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.reduce");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getY() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getIdentity() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getXMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getYMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIdentityMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value x, ::mlir::Value y, ::mlir::Value identity);
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value x, ::mlir::Value y, ::mlir::Value identity);
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value x, ::mlir::Value y, ::mlir::Value identity);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value x, ::mlir::Value y, ::mlir::Value identity);
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value x, ::mlir::Value y, ::mlir::Value identity);
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value x, ::mlir::Value y, ::mlir::Value identity);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value y, ::mlir::Value identity);
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value y, ::mlir::Value identity);
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value y, ::mlir::Value identity);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ReduceOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ReinterpretMapOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReinterpretMapOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ReinterpretMapOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.reinterpret_map", odsAttrs.getContext());
  }

  ReinterpretMapOpGenericAdaptorBase(ReinterpretMapOp op);

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
class ReinterpretMapOpGenericAdaptor : public detail::ReinterpretMapOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReinterpretMapOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  ReinterpretMapOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReinterpretMapOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReinterpretMapOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReinterpretMapOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReinterpretMapOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReinterpretMapOpGenericAdaptor(RangeT values, const ReinterpretMapOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReinterpretMapOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReinterpretMapOp>>>
  ReinterpretMapOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ReinterpretMapOpAdaptor : public ReinterpretMapOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReinterpretMapOpGenericAdaptor::ReinterpretMapOpGenericAdaptor;
  ReinterpretMapOpAdaptor(ReinterpretMapOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReinterpretMapOp : public ::mlir::Op<ReinterpretMapOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReinterpretMapOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReinterpretMapOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.reinterpret_map");
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

  ::mlir::TypedValue<::mlir::RankedTensorType> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, SparseTensorEncodingAttr dstEnc, Value source);
  static ReinterpretMapOp create(::mlir::OpBuilder &builder, ::mlir::Location location, SparseTensorEncodingAttr dstEnc, Value source);
  static ReinterpretMapOp create(::mlir::ImplicitLocOpBuilder &builder, SparseTensorEncodingAttr dstEnc, Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dest, ::mlir::Value source);
  static ReinterpretMapOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dest, ::mlir::Value source);
  static ReinterpretMapOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dest, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static ReinterpretMapOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static ReinterpretMapOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReinterpretMapOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReinterpretMapOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReinterpretMapOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReinterpretMapOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ReinterpretMapOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ReorderCOOOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReorderCOOOpGenericAdaptorBase {
public:
  struct Properties {
    using algorithmTy = ::mlir::sparse_tensor::SparseTensorSortKindAttr;
    algorithmTy algorithm;

    auto getAlgorithm() const {
      auto &propStorage = this->algorithm;
      return ::llvm::cast<::mlir::sparse_tensor::SparseTensorSortKindAttr>(propStorage);
    }
    void setAlgorithm(const ::mlir::sparse_tensor::SparseTensorSortKindAttr &propValue) {
      this->algorithm = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.algorithm == this->algorithm &&
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
  ReorderCOOOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.reorder_coo", odsAttrs.getContext());
  }

  ReorderCOOOpGenericAdaptorBase(ReorderCOOOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sparse_tensor::SparseTensorSortKindAttr getAlgorithmAttr() {
    auto attr = ::llvm::cast<::mlir::sparse_tensor::SparseTensorSortKindAttr>(getProperties().algorithm);
    return attr;
  }

  ::mlir::sparse_tensor::SparseTensorSortKind getAlgorithm();
};

} // namespace detail
template <typename RangeT>
class ReorderCOOOpGenericAdaptor : public detail::ReorderCOOOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReorderCOOOpGenericAdaptorBase;
  static constexpr int odsIndex_input_coo = 0;
public:
  ReorderCOOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReorderCOOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReorderCOOOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReorderCOOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReorderCOOOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReorderCOOOpGenericAdaptor(RangeT values, const ReorderCOOOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReorderCOOOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReorderCOOOp>>>
  ReorderCOOOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInputCoo() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReorderCOOOpAdaptor : public ReorderCOOOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReorderCOOOpGenericAdaptor::ReorderCOOOpGenericAdaptor;
  ReorderCOOOpAdaptor(ReorderCOOOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReorderCOOOp : public ::mlir::Op<ReorderCOOOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReorderCOOOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReorderCOOOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input_coo = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("algorithm")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlgorithmAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlgorithmAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.reorder_coo");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getInputCoo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputCooMutable() {
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

  ::mlir::TypedValue<::mlir::RankedTensorType> getResultCoo() {
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
  ::mlir::sparse_tensor::SparseTensorSortKindAttr getAlgorithmAttr() {
    return ::llvm::cast<::mlir::sparse_tensor::SparseTensorSortKindAttr>(getProperties().algorithm);
  }

  ::mlir::sparse_tensor::SparseTensorSortKind getAlgorithm();
  void setAlgorithmAttr(::mlir::sparse_tensor::SparseTensorSortKindAttr attr) {
    getProperties().algorithm = attr;
  }

  void setAlgorithm(::mlir::sparse_tensor::SparseTensorSortKind attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result_coo, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static ReorderCOOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result_coo, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static ReorderCOOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result_coo, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static ReorderCOOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static ReorderCOOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result_coo, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static ReorderCOOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result_coo, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static ReorderCOOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result_coo, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static ReorderCOOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static ReorderCOOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input_coo, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReorderCOOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReorderCOOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReorderCOOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReorderCOOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ReorderCOOOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::SelectOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SelectOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SelectOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.select", odsAttrs.getContext());
  }

  SelectOpGenericAdaptorBase(SelectOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SelectOpGenericAdaptor : public detail::SelectOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SelectOpGenericAdaptorBase;
  static constexpr int odsIndex_x = 0;
public:
  SelectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SelectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SelectOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SelectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SelectOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SelectOpGenericAdaptor(RangeT values, const SelectOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SelectOp, typename = std::enable_if_t<std::is_same_v<LateInst, SelectOp>>>
  SelectOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getX() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SelectOpAdaptor : public SelectOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SelectOpGenericAdaptor::SelectOpGenericAdaptor;
  SelectOpAdaptor(SelectOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SelectOp : public ::mlir::Op<SelectOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SelectOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SelectOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_x = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.select");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getXMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value x);
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value x);
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value x);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value x);
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value x);
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value x);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x);
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x);
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SelectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SelectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::SelectOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::SetStorageSpecifierOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SetStorageSpecifierOpGenericAdaptorBase {
public:
  struct Properties {
    using levelTy = ::mlir::IntegerAttr;
    levelTy level;

    auto getLevel() const {
      auto &propStorage = this->level;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setLevel(const ::mlir::IntegerAttr &propValue) {
      this->level = propValue;
    }
    using specifierKindTy = ::mlir::sparse_tensor::StorageSpecifierKindAttr;
    specifierKindTy specifierKind;

    auto getSpecifierKind() const {
      auto &propStorage = this->specifierKind;
      return ::llvm::cast<::mlir::sparse_tensor::StorageSpecifierKindAttr>(propStorage);
    }
    void setSpecifierKind(const ::mlir::sparse_tensor::StorageSpecifierKindAttr &propValue) {
      this->specifierKind = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.level == this->level &&
        rhs.specifierKind == this->specifierKind &&
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
  SetStorageSpecifierOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.storage_specifier.set", odsAttrs.getContext());
  }

  SetStorageSpecifierOpGenericAdaptorBase(SetStorageSpecifierOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::sparse_tensor::StorageSpecifierKindAttr getSpecifierKindAttr() {
    auto attr = ::llvm::cast<::mlir::sparse_tensor::StorageSpecifierKindAttr>(getProperties().specifierKind);
    return attr;
  }

  ::mlir::sparse_tensor::StorageSpecifierKind getSpecifierKind();
  ::mlir::IntegerAttr getLevelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().level);
    return attr;
  }

  ::std::optional<::mlir::sparse_tensor::Level> getLevel();
};

} // namespace detail
template <typename RangeT>
class SetStorageSpecifierOpGenericAdaptor : public detail::SetStorageSpecifierOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SetStorageSpecifierOpGenericAdaptorBase;
  static constexpr int odsIndex_specifier = 0;
  static constexpr int odsIndex_value = 1;
public:
  SetStorageSpecifierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SetStorageSpecifierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SetStorageSpecifierOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SetStorageSpecifierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SetStorageSpecifierOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SetStorageSpecifierOpGenericAdaptor(RangeT values, const SetStorageSpecifierOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SetStorageSpecifierOp, typename = std::enable_if_t<std::is_same_v<LateInst, SetStorageSpecifierOp>>>
  SetStorageSpecifierOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSpecifier() {
    return (*getODSOperands(0).begin());
  }

  ValueT getValue() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SetStorageSpecifierOpAdaptor : public SetStorageSpecifierOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SetStorageSpecifierOpGenericAdaptor::SetStorageSpecifierOpGenericAdaptor;
  SetStorageSpecifierOpAdaptor(SetStorageSpecifierOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SetStorageSpecifierOp : public ::mlir::Op<SetStorageSpecifierOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::sparse_tensor::StorageSpecifierType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SetStorageSpecifierOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SetStorageSpecifierOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_specifier = 0;
  static constexpr int odsIndex_value = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("level"), ::llvm::StringRef("specifierKind")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLevelAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLevelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSpecifierKindAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSpecifierKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.storage_specifier.set");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType> getSpecifier() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getSpecifierMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValueMutable() {
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

  ::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType>>(*getODSResults(0).begin());
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
  ::mlir::sparse_tensor::StorageSpecifierKindAttr getSpecifierKindAttr() {
    return ::llvm::cast<::mlir::sparse_tensor::StorageSpecifierKindAttr>(getProperties().specifierKind);
  }

  ::mlir::sparse_tensor::StorageSpecifierKind getSpecifierKind();
  ::mlir::IntegerAttr getLevelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().level);
  }

  ::std::optional<::mlir::sparse_tensor::Level> getLevel();
  void setSpecifierKindAttr(::mlir::sparse_tensor::StorageSpecifierKindAttr attr) {
    getProperties().specifierKind = attr;
  }

  void setSpecifierKind(::mlir::sparse_tensor::StorageSpecifierKind attrValue);
  void setLevelAttr(::mlir::IntegerAttr attr) {
    getProperties().level = attr;
  }

  void setLevel(::std::optional<::mlir::sparse_tensor::Level> attrValue);
  ::mlir::Attribute removeLevelAttr() {
      auto attr = getProperties().level;
      getProperties().level = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKindAttr specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static SetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value specifier, ::mlir::sparse_tensor::StorageSpecifierKind specifierKind, /*optional*/::mlir::IntegerAttr level, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SetStorageSpecifierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SetStorageSpecifierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::SetStorageSpecifierOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::SortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SortOpGenericAdaptorBase {
public:
  struct Properties {
    using algorithmTy = ::mlir::sparse_tensor::SparseTensorSortKindAttr;
    algorithmTy algorithm;

    auto getAlgorithm() const {
      auto &propStorage = this->algorithm;
      return ::llvm::cast<::mlir::sparse_tensor::SparseTensorSortKindAttr>(propStorage);
    }
    void setAlgorithm(const ::mlir::sparse_tensor::SparseTensorSortKindAttr &propValue) {
      this->algorithm = propValue;
    }
    using nyTy = ::mlir::IntegerAttr;
    nyTy ny;

    auto getNy() const {
      auto &propStorage = this->ny;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setNy(const ::mlir::IntegerAttr &propValue) {
      this->ny = propValue;
    }
    using perm_mapTy = ::mlir::AffineMapAttr;
    perm_mapTy perm_map;

    auto getPermMap() const {
      auto &propStorage = this->perm_map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setPermMap(const ::mlir::AffineMapAttr &propValue) {
      this->perm_map = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.algorithm == this->algorithm &&
        rhs.ny == this->ny &&
        rhs.perm_map == this->perm_map &&
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
  SortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.sort", odsAttrs.getContext());
  }

  SortOpGenericAdaptorBase(SortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getPermMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().perm_map);
    return attr;
  }

  ::mlir::AffineMap getPermMap();
  ::mlir::IntegerAttr getNyAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().ny);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getNy();
  ::mlir::sparse_tensor::SparseTensorSortKindAttr getAlgorithmAttr() {
    auto attr = ::llvm::cast<::mlir::sparse_tensor::SparseTensorSortKindAttr>(getProperties().algorithm);
    return attr;
  }

  ::mlir::sparse_tensor::SparseTensorSortKind getAlgorithm();
};

} // namespace detail
template <typename RangeT>
class SortOpGenericAdaptor : public detail::SortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SortOpGenericAdaptorBase;
  static constexpr int odsIndex_n = 0;
  static constexpr int odsIndex_xy = 1;
  static constexpr int odsIndex_ys = 2;
public:
  SortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SortOpGenericAdaptor(RangeT values, const SortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SortOp, typename = std::enable_if_t<std::is_same_v<LateInst, SortOp>>>
  SortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getN() {
    return (*getODSOperands(0).begin());
  }

  ValueT getXy() {
    return (*getODSOperands(1).begin());
  }

  RangeT getYs() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SortOpAdaptor : public SortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SortOpGenericAdaptor::SortOpGenericAdaptor;
  SortOpAdaptor(SortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SortOp : public ::mlir::Op<SortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_n = 0;
  static constexpr int odsIndex_xy = 1;
  static constexpr int odsIndex_ys = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("algorithm"), ::llvm::StringRef("ny"), ::llvm::StringRef("perm_map")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlgorithmAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlgorithmAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNyAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPermMapAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPermMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.sort");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getN() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getXy() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getYs() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getNMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getXyMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getYsMutable();
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
  ::mlir::AffineMapAttr getPermMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().perm_map);
  }

  ::mlir::AffineMap getPermMap();
  ::mlir::IntegerAttr getNyAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().ny);
  }

  ::std::optional< ::llvm::APInt > getNy();
  ::mlir::sparse_tensor::SparseTensorSortKindAttr getAlgorithmAttr() {
    return ::llvm::cast<::mlir::sparse_tensor::SparseTensorSortKindAttr>(getProperties().algorithm);
  }

  ::mlir::sparse_tensor::SparseTensorSortKind getAlgorithm();
  void setPermMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().perm_map = attr;
  }

  void setPermMap(::mlir::AffineMap attrValue);
  void setNyAttr(::mlir::IntegerAttr attr) {
    getProperties().ny = attr;
  }

  void setNy(::std::optional<::llvm::APInt> attrValue);
  void setAlgorithmAttr(::mlir::sparse_tensor::SparseTensorSortKindAttr attr) {
    getProperties().algorithm = attr;
  }

  void setAlgorithm(::mlir::sparse_tensor::SparseTensorSortKind attrValue);
  ::mlir::Attribute removeNyAttr() {
      auto attr = getProperties().ny;
      getProperties().ny = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMapAttr perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static SortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMapAttr perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static SortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMapAttr perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMapAttr perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static SortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMapAttr perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static SortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMapAttr perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKindAttr algorithm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMap perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static SortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMap perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static SortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMap perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMap perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static SortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMap perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static SortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value n, ::mlir::Value xy, ::mlir::ValueRange ys, ::mlir::AffineMap perm_map, /*optional*/::mlir::IntegerAttr ny, ::mlir::sparse_tensor::SparseTensorSortKind algorithm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::SortOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::StorageSpecifierInitOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StorageSpecifierInitOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StorageSpecifierInitOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.storage_specifier.init", odsAttrs.getContext());
  }

  StorageSpecifierInitOpGenericAdaptorBase(StorageSpecifierInitOp op);

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
class StorageSpecifierInitOpGenericAdaptor : public detail::StorageSpecifierInitOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StorageSpecifierInitOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  StorageSpecifierInitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StorageSpecifierInitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : StorageSpecifierInitOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StorageSpecifierInitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StorageSpecifierInitOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StorageSpecifierInitOpGenericAdaptor(RangeT values, const StorageSpecifierInitOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StorageSpecifierInitOp, typename = std::enable_if_t<std::is_same_v<LateInst, StorageSpecifierInitOp>>>
  StorageSpecifierInitOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StorageSpecifierInitOpAdaptor : public StorageSpecifierInitOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StorageSpecifierInitOpGenericAdaptor::StorageSpecifierInitOpGenericAdaptor;
  StorageSpecifierInitOpAdaptor(StorageSpecifierInitOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StorageSpecifierInitOp : public ::mlir::Op<StorageSpecifierInitOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::sparse_tensor::StorageSpecifierType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StorageSpecifierInitOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StorageSpecifierInitOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.storage_specifier.init");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType> getSource() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType>>(*operands.begin());
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

  ::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::sparse_tensor::StorageSpecifierType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type result);
  static StorageSpecifierInitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type result);
  static StorageSpecifierInitOp create(::mlir::ImplicitLocOpBuilder &builder, Type result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::Value source);
  static StorageSpecifierInitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::Value source);
  static StorageSpecifierInitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value source);
  static StorageSpecifierInitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value source);
  static StorageSpecifierInitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StorageSpecifierInitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StorageSpecifierInitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StorageSpecifierInitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StorageSpecifierInitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::StorageSpecifierInitOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ToCoordinatesBufferOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToCoordinatesBufferOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ToCoordinatesBufferOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.coordinates_buffer", odsAttrs.getContext());
  }

  ToCoordinatesBufferOpGenericAdaptorBase(ToCoordinatesBufferOp op);

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
class ToCoordinatesBufferOpGenericAdaptor : public detail::ToCoordinatesBufferOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToCoordinatesBufferOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  ToCoordinatesBufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToCoordinatesBufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ToCoordinatesBufferOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToCoordinatesBufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToCoordinatesBufferOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToCoordinatesBufferOpGenericAdaptor(RangeT values, const ToCoordinatesBufferOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToCoordinatesBufferOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToCoordinatesBufferOp>>>
  ToCoordinatesBufferOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ToCoordinatesBufferOpAdaptor : public ToCoordinatesBufferOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToCoordinatesBufferOpGenericAdaptor::ToCoordinatesBufferOpGenericAdaptor;
  ToCoordinatesBufferOpAdaptor(ToCoordinatesBufferOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToCoordinatesBufferOp : public ::mlir::Op<ToCoordinatesBufferOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToCoordinatesBufferOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToCoordinatesBufferOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<ToCoordinatesBufferOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.coordinates_buffer");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor);
  static ToCoordinatesBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor);
  static ToCoordinatesBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor);
  static ToCoordinatesBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor);
  static ToCoordinatesBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static ToCoordinatesBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static ToCoordinatesBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToCoordinatesBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToCoordinatesBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToCoordinatesBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToCoordinatesBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToCoordinatesBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToCoordinatesBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToCoordinatesBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToCoordinatesBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ToCoordinatesBufferOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ToCoordinatesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToCoordinatesOpGenericAdaptorBase {
public:
  struct Properties {
    using levelTy = ::mlir::IntegerAttr;
    levelTy level;

    auto getLevel() const {
      auto &propStorage = this->level;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLevel(const ::mlir::IntegerAttr &propValue) {
      this->level = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.level == this->level &&
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
  ToCoordinatesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.coordinates", odsAttrs.getContext());
  }

  ToCoordinatesOpGenericAdaptorBase(ToCoordinatesOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getLevelAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().level);
    return attr;
  }

  ::mlir::sparse_tensor::Level getLevel();
};

} // namespace detail
template <typename RangeT>
class ToCoordinatesOpGenericAdaptor : public detail::ToCoordinatesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToCoordinatesOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  ToCoordinatesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToCoordinatesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ToCoordinatesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToCoordinatesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToCoordinatesOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToCoordinatesOpGenericAdaptor(RangeT values, const ToCoordinatesOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToCoordinatesOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToCoordinatesOp>>>
  ToCoordinatesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ToCoordinatesOpAdaptor : public ToCoordinatesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToCoordinatesOpGenericAdaptor::ToCoordinatesOpGenericAdaptor;
  ToCoordinatesOpAdaptor(ToCoordinatesOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToCoordinatesOp : public ::mlir::Op<ToCoordinatesOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToCoordinatesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToCoordinatesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<ToCoordinatesOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("level")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLevelAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLevelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.coordinates");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
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
  ::mlir::IntegerAttr getLevelAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().level);
  }

  ::mlir::sparse_tensor::Level getLevel();
  void setLevelAttr(::mlir::IntegerAttr attr) {
    getProperties().level = attr;
  }

  void setLevel(::mlir::sparse_tensor::Level attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToCoordinatesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToCoordinatesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToCoordinatesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToCoordinatesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToCoordinatesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToCoordinatesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToCoordinatesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToCoordinatesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToCoordinatesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToCoordinatesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToCoordinatesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToCoordinatesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToCoordinatesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToCoordinatesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToCoordinatesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToCoordinatesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToCoordinatesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToCoordinatesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToCoordinatesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToCoordinatesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ToCoordinatesOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ToPositionsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToPositionsOpGenericAdaptorBase {
public:
  struct Properties {
    using levelTy = ::mlir::IntegerAttr;
    levelTy level;

    auto getLevel() const {
      auto &propStorage = this->level;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLevel(const ::mlir::IntegerAttr &propValue) {
      this->level = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.level == this->level &&
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
  ToPositionsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.positions", odsAttrs.getContext());
  }

  ToPositionsOpGenericAdaptorBase(ToPositionsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getLevelAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().level);
    return attr;
  }

  ::mlir::sparse_tensor::Level getLevel();
};

} // namespace detail
template <typename RangeT>
class ToPositionsOpGenericAdaptor : public detail::ToPositionsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToPositionsOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  ToPositionsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToPositionsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ToPositionsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToPositionsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToPositionsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToPositionsOpGenericAdaptor(RangeT values, const ToPositionsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToPositionsOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToPositionsOp>>>
  ToPositionsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ToPositionsOpAdaptor : public ToPositionsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToPositionsOpGenericAdaptor::ToPositionsOpGenericAdaptor;
  ToPositionsOpAdaptor(ToPositionsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToPositionsOp : public ::mlir::Op<ToPositionsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToPositionsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToPositionsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<ToPositionsOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("level")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLevelAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLevelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.positions");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
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
  ::mlir::IntegerAttr getLevelAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().level);
  }

  ::mlir::sparse_tensor::Level getLevel();
  void setLevelAttr(::mlir::IntegerAttr attr) {
    getProperties().level = attr;
  }

  void setLevel(::mlir::sparse_tensor::Level attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToPositionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToPositionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToPositionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToPositionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToPositionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static ToPositionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::IntegerAttr level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToPositionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToPositionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToPositionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToPositionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToPositionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static ToPositionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor, ::mlir::sparse_tensor::Level level);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToPositionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToPositionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToPositionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToPositionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToPositionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToPositionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToPositionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToPositionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ToPositionsOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ToSliceOffsetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToSliceOffsetOpGenericAdaptorBase {
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
  ToSliceOffsetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.slice.offset", odsAttrs.getContext());
  }

  ToSliceOffsetOpGenericAdaptorBase(ToSliceOffsetOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

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

  ::llvm::APInt getDim();
};

} // namespace detail
template <typename RangeT>
class ToSliceOffsetOpGenericAdaptor : public detail::ToSliceOffsetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToSliceOffsetOpGenericAdaptorBase;
  static constexpr int odsIndex_slice = 0;
public:
  ToSliceOffsetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToSliceOffsetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ToSliceOffsetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToSliceOffsetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToSliceOffsetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToSliceOffsetOpGenericAdaptor(RangeT values, const ToSliceOffsetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToSliceOffsetOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToSliceOffsetOp>>>
  ToSliceOffsetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSlice() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ToSliceOffsetOpAdaptor : public ToSliceOffsetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToSliceOffsetOpGenericAdaptor::ToSliceOffsetOpGenericAdaptor;
  ToSliceOffsetOpAdaptor(ToSliceOffsetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToSliceOffsetOp : public ::mlir::Op<ToSliceOffsetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToSliceOffsetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToSliceOffsetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_slice = 0;
  using Properties = FoldAdaptor::Properties;
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
    return ::llvm::StringLiteral("sparse_tensor.slice.offset");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSlice() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getSliceMutable() {
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

  ::mlir::TypedValue<::mlir::IndexType> getOffset() {
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
  ::mlir::IntegerAttr getDimAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().dim);
  }

  ::llvm::APInt getDim();
  void setDimAttr(::mlir::IntegerAttr attr) {
    getProperties().dim = attr;
  }

  void setDim(::llvm::APInt attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type offset, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type offset, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type offset, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type offset, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type offset, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type offset, ::mlir::Value slice, ::llvm::APInt dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value slice, ::llvm::APInt dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::llvm::APInt dim);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToSliceOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToSliceOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToSliceOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToSliceOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToSliceOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToSliceOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToSliceOffsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToSliceOffsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ToSliceOffsetOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ToSliceStrideOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToSliceStrideOpGenericAdaptorBase {
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
  ToSliceStrideOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.slice.stride", odsAttrs.getContext());
  }

  ToSliceStrideOpGenericAdaptorBase(ToSliceStrideOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

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

  ::llvm::APInt getDim();
};

} // namespace detail
template <typename RangeT>
class ToSliceStrideOpGenericAdaptor : public detail::ToSliceStrideOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToSliceStrideOpGenericAdaptorBase;
  static constexpr int odsIndex_slice = 0;
public:
  ToSliceStrideOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToSliceStrideOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ToSliceStrideOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToSliceStrideOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToSliceStrideOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToSliceStrideOpGenericAdaptor(RangeT values, const ToSliceStrideOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToSliceStrideOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToSliceStrideOp>>>
  ToSliceStrideOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSlice() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ToSliceStrideOpAdaptor : public ToSliceStrideOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToSliceStrideOpGenericAdaptor::ToSliceStrideOpGenericAdaptor;
  ToSliceStrideOpAdaptor(ToSliceStrideOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToSliceStrideOp : public ::mlir::Op<ToSliceStrideOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToSliceStrideOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToSliceStrideOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_slice = 0;
  using Properties = FoldAdaptor::Properties;
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
    return ::llvm::StringLiteral("sparse_tensor.slice.stride");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSlice() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getSliceMutable() {
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

  ::mlir::TypedValue<::mlir::IndexType> getStride() {
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
  ::mlir::IntegerAttr getDimAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().dim);
  }

  ::llvm::APInt getDim();
  void setDimAttr(::mlir::IntegerAttr attr) {
    getProperties().dim = attr;
  }

  void setDim(::llvm::APInt attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type stride, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceStrideOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type stride, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceStrideOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type stride, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceStrideOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceStrideOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceStrideOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static ToSliceStrideOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::mlir::IntegerAttr dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type stride, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceStrideOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type stride, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceStrideOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type stride, ::mlir::Value slice, ::llvm::APInt dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceStrideOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceStrideOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value slice, ::llvm::APInt dim);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceStrideOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::llvm::APInt dim);
  static ToSliceStrideOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value slice, ::llvm::APInt dim);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToSliceStrideOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToSliceStrideOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToSliceStrideOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToSliceStrideOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToSliceStrideOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToSliceStrideOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToSliceStrideOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToSliceStrideOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ToSliceStrideOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::ToValuesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToValuesOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ToValuesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.values", odsAttrs.getContext());
  }

  ToValuesOpGenericAdaptorBase(ToValuesOp op);

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
class ToValuesOpGenericAdaptor : public detail::ToValuesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToValuesOpGenericAdaptorBase;
  static constexpr int odsIndex_tensor = 0;
public:
  ToValuesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToValuesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ToValuesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToValuesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToValuesOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToValuesOpGenericAdaptor(RangeT values, const ToValuesOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToValuesOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToValuesOp>>>
  ToValuesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ToValuesOpAdaptor : public ToValuesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToValuesOpGenericAdaptor::ToValuesOpGenericAdaptor;
  ToValuesOpAdaptor(ToValuesOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToValuesOp : public ::mlir::Op<ToValuesOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToValuesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToValuesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tensor = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<ToValuesOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.values");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value tensor);
  static ToValuesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value tensor);
  static ToValuesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tensor);
  static ToValuesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tensor);
  static ToValuesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static ToValuesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static ToValuesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tensor);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToValuesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToValuesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToValuesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToValuesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToValuesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToValuesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToValuesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToValuesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::ToValuesOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::UnaryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnaryOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UnaryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sparse_tensor.unary", odsAttrs.getContext());
  }

  UnaryOpGenericAdaptorBase(UnaryOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getPresentRegion() {
    return *odsRegions[0];
  }

  ::mlir::Region &getAbsentRegion() {
    return *odsRegions[1];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class UnaryOpGenericAdaptor : public detail::UnaryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnaryOpGenericAdaptorBase;
  static constexpr int odsIndex_x = 0;
public:
  UnaryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnaryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : UnaryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnaryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnaryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnaryOpGenericAdaptor(RangeT values, const UnaryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnaryOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnaryOp>>>
  UnaryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getX() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UnaryOpAdaptor : public UnaryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnaryOpGenericAdaptor::UnaryOpGenericAdaptor;
  UnaryOpAdaptor(UnaryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnaryOp : public ::mlir::Op<UnaryOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnaryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnaryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_x = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.unary");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getXMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::Region &getPresentRegion() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getAbsentRegion() {
    return (*this)->getRegion(1);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value x);
  static UnaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value x);
  static UnaryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value x);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x);
  static UnaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x);
  static UnaryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnaryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnaryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::UnaryOp)

namespace mlir::sparse_tensor {


//===----------------------------------------------------------------------===//
// ::mlir::sparse_tensor::YieldOp declarations
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
      odsOpName.emplace("sparse_tensor.yield", odsAttrs.getContext());
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
  static constexpr int odsIndex_results = 0;
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

  RangeT getResults() {
    return getODSOperands(0);
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
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<BinaryOp, UnaryOp, ReduceOp, SelectOp, ForeachOp, IterateOp, CoIterateOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = YieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = YieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_results = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sparse_tensor.yield");
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
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value yieldVal);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value yieldVal);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, Value yieldVal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange results);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange results);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange results);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  Value getSingleResult() {
     assert(hasSingleResult());
     return getResults().front();
  }
  bool hasSingleResult() {
     return getResults().size() == 1;
  }
};

} // namespace mlir::sparse_tensor
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::sparse_tensor::YieldOp)


#endif // GET_OP_CLASSES

