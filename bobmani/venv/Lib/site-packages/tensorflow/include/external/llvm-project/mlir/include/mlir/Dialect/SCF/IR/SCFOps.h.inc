/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SCFOps.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::scf {

/// loop continuation condition
/// This operation accepts the continuation (i.e., inverse of exit) condition
///     of the `scf.while` construct. If its first argument is true, the "after"
///     region of `scf.while` is executed, with the remaining arguments forwarded
///     to the entry block of the region. Otherwise, the loop terminates.
class ConditionOp;

} // namespace mlir::scf
namespace mlir::scf {

/// operation that executes its region exactly once
/// The `scf.execute_region` operation is used to allow multiple blocks within SCF
///     and other operations which can hold only one block.  The `scf.execute_region`
///     operation executes the region held exactly once and cannot have any operands.
///     As such, its region has no arguments. All SSA values that dominate the op can
///     be accessed inside the op. The op's region can have multiple blocks and the
///     blocks can have multiple distinct terminators. Values returned from this op's
///     region define the op's results.
///     The optional 'no_inline' flag can be set to request the ExecuteRegionOp to be
///     preserved as much as possible and not being inlined in the parent block until
///     an explicit lowering step.
/// 
///     Example:
/// 
///     ```mlir
///     scf.for %i = 0 to 128 step %c1 {
///       %y = scf.execute_region -> i32 {
///         %x = load %A[%i] : memref<128xi32>
///         scf.yield %x : i32
///       }
///     }
/// 
///     // the same as above but with no_inline attribute
///     scf.for %i = 0 to 128 step %c1 {
///       %y = scf.execute_region -> i32 no_inline {
///         %x = load %A[%i] : memref<128xi32>
///         scf.yield %x : i32
///       }
///     }
/// 
///     affine.for %i = 0 to 100 {
///       "foo"() : () -> ()
///       %v = scf.execute_region -> i64 {
///         cf.cond_br %cond, ^bb1, ^bb2
/// 
///       ^bb1:
///         %c1 = arith.constant 1 : i64
///         cf.br ^bb3(%c1 : i64)
/// 
///       ^bb2:
///         %c2 = arith.constant 2 : i64
///         cf.br ^bb3(%c2 : i64)
/// 
///       ^bb3(%x : i64):
///         scf.yield %x : i64
///       }
///       "bar"(%v) : (i64) -> ()
///     }
///     ```
class ExecuteRegionOp;

} // namespace mlir::scf
namespace mlir::scf {

/// for operation
/// The `scf.for` operation represents a loop taking 3 SSA value as operands
///     that represent the lower bound, upper bound and step respectively. The
///     operation defines an SSA value for its induction variable. It has one
///     region capturing the loop body. The induction variable is represented as an
///     argument of this region. This SSA value is a signless integer or index.
///     The step is a value of same type but required to be positive, the lower and
///     upper bounds can be also negative or zero. The lower and upper bounds
///     specify a half-open range: the iteration is executed iff the comparison of
///     induction variable value is less than the upper bound and bigger or equal
///     to the lower bound.
/// 
///     By default, the integer comparison is signed. If the `unsignedCmp` unit
///     attribute is specified, the integer comparison is unsigned.
/// 
///     The body region must contain exactly one block that terminates with
///     `scf.yield`. Calling ForOp::build will create such a region and insert
///     the terminator implicitly if none is defined, so will the parsing even in
///     cases when it is absent from the custom format. For example:
/// 
///     ```mlir
///     // Index case.
///     scf.for %iv = %lb to %ub step %step {
///       ... // body
///     }
///     ...
///     // Unsigned integer case.
///     scf.for unsigned %iv_32 = %lb_32 to %ub_32 step %step_32 : i32 {
///       ... // body
///     }
///     ```
/// 
///     `scf.for` can also operate on loop-carried variables and returns the final
///     values after loop termination. The initial values of the variables are
///     passed as additional SSA operands to the `scf.for` following the 3 loop
///     control SSA values mentioned above (lower bound, upper bound and step). The
///     operation region has an argument for the induction variable, followed by
///     one argument for each loop-carried variable, representing the value of the
///     variable at the current iteration.
/// 
///     The region must terminate with a `scf.yield` that passes the current
///     values of all loop-carried variables to the next iteration, or to the
///     `scf.for` result, if at the last iteration. The static type of a
///     loop-carried variable may not change with iterations; its runtime type is
///     allowed to change. Note, that when the loop-carried variables are present,
///     calling ForOp::build will not insert the terminator implicitly. The caller
///     must insert `scf.yield` in that case.
/// 
///     `scf.for` results hold the final values after the last iteration.
///     For example, to sum-reduce a memref:
/// 
///     ```mlir
///     func.func @reduce(%buffer: memref<1024xf32>, %lb: index,
///                       %ub: index, %step: index) -> (f32) {
///       // Initial sum set to 0.
///       %sum_0 = arith.constant 0.0 : f32
///       // iter_args binds initial values to the loop's region arguments.
///       %sum = scf.for %iv = %lb to %ub step %step
///           iter_args(%sum_iter = %sum_0) -> (f32) {
///         %t = load %buffer[%iv] : memref<1024xf32>
///         %sum_next = arith.addf %sum_iter, %t : f32
///         // Yield current iteration sum to next iteration %sum_iter or to %sum
///         // if final iteration.
///         scf.yield %sum_next : f32
///       }
///       return %sum : f32
///     }
///     ```
/// 
///     If the `scf.for` defines any values, a yield must be explicitly present.
///     The number and types of the `scf.for` results must match the initial
///     values in the `iter_args` binding and the yield operands.
/// 
///     Another example with a nested `scf.if` (see `scf.if` for details) to
///     perform conditional reduction:
/// 
///     ```mlir
///     func.func @conditional_reduce(%buffer: memref<1024xf32>, %lb: index,
///                                   %ub: index, %step: index) -> (f32) {
///       %sum_0 = arith.constant 0.0 : f32
///       %c0 = arith.constant 0.0 : f32
///       %sum = scf.for %iv = %lb to %ub step %step
///           iter_args(%sum_iter = %sum_0) -> (f32) {
///         %t = load %buffer[%iv] : memref<1024xf32>
///         %cond = arith.cmpf "ugt", %t, %c0 : f32
///         %sum_next = scf.if %cond -> (f32) {
///           %new_sum = arith.addf %sum_iter, %t : f32
///           scf.yield %new_sum : f32
///         } else {
///           scf.yield %sum_iter : f32
///         }
///         scf.yield %sum_next : f32
///       }
///       return %sum : f32
///     }
///     ```
class ForOp;

} // namespace mlir::scf
namespace mlir::scf {

/// evaluate a block multiple times in parallel
/// `scf.forall` is a target-independent multi-dimensional parallel
///     region application operation. It has exactly one block that represents the
///     parallel body and it takes index operands that specify lower bounds, upper
///     bounds and steps.
/// 
///     The op also takes a variadic number of tensor operands (`shared_outs`).
///     The future buffers corresponding to these tensors are shared among all
///     threads. Shared tensors should be accessed via their corresponding block
///     arguments. If multiple threads write to a shared buffer in a racy
///     fashion, these writes will execute in some unspecified order. Tensors that
///     are not shared can be used inside the body (i.e., the op is not isolated
///     from above); however, if a use of such a tensor bufferizes to a memory
///     write, the tensor is privatized, i.e., a thread-local copy of the tensor is
///     used. This ensures that memory side effects of a thread are not visible to
///     other threads (or in the parent body), apart from explicitly shared tensors.
/// 
///     The name "thread" conveys the fact that the parallel execution is mapped
///     (i.e. distributed) to a set of virtual threads of execution, one function
///     application per thread. Further lowerings are responsible for specifying
///     how this is materialized on concrete hardware resources.
/// 
///     An optional `mapping` is an attribute array that specifies processing units
///     with their dimension, how it remaps 1-1 to a set of concrete processing
///     element resources (e.g. a CUDA grid dimension or a level of concrete nested
///     async parallelism). It is expressed via any attribute that implements the
///     device mapping interface. It is the reponsibility of the lowering mechanism
///     to interpret the `mapping` attributes in the context of the concrete target
///     the op is lowered to, or to ignore it when the specification is ill-formed
///     or unsupported for a particular target.
/// 
///     The only allowed terminator is `scf.forall.in_parallel`.
///     `scf.forall` returns one value per `shared_out` operand. The
///     actions of the `scf.forall.in_parallel` terminators specify how to combine the
///     partial results of all parallel invocations into a full value, in some
///     unspecified order. The "destination" of each such op must be a `shared_out`
///     block argument of the `scf.forall` op.
/// 
///     The actions involved in constructing the return values are further described
///     by `tensor.parallel_insert_slice`.
/// 
///     `scf.forall` acts as an implicit synchronization point.
/// 
///     When the parallel function body has side effects, their order is unspecified
///     across threads.
/// 
///     `scf.forall` can be printed in two different ways depending on
///     whether the loop is normalized or not. The loop is 'normalized' when all
///     lower bounds are equal to zero and steps are equal to one. In that case,
///     `lowerBound` and `step` operands will be omitted during printing.
/// 
///     Normalized loop example:
/// 
///     ```mlir
///     //
///     // Sequential context.
///     //
///     %matmul_and_pointwise:2 = scf.forall (%thread_id_1, %thread_id_2) in
///         (%num_threads_1, %numthread_id_2) shared_outs(%o1 = %C, %o2 = %pointwise)
///       -> (tensor<?x?xT>, tensor<?xT>) {
///       //
///       // Parallel context, each thread with id = (%thread_id_1, %thread_id_2)
///       // runs its version of the code.
///       //
///       %sA = tensor.extract_slice %A[f((%thread_id_1, %thread_id_2))]:
///         tensor<?x?xT> to tensor<?x?xT>
///       %sB = tensor.extract_slice %B[g((%thread_id_1, %thread_id_2))]:
///         tensor<?x?xT> to tensor<?x?xT>
///       %sC = tensor.extract_slice %o1[h((%thread_id_1, %thread_id_2))]:
///         tensor<?x?xT> to tensor<?x?xT>
///       %sD = linalg.matmul
///         ins(%sA, %sB : tensor<?x?xT>, tensor<?x?xT>)
///         outs(%sC : tensor<?x?xT>)
/// 
///       %spointwise = subtensor %o2[i((%thread_id_1, %thread_id_2))]:
///         tensor<?xT> to tensor<?xT>
///       %sE = linalg.add ins(%spointwise : tensor<?xT>) outs(%sD : tensor<?xT>)
/// 
///       scf.forall.in_parallel {
///         tensor.parallel_insert_slice %sD into %o1[h((%thread_id_1, %thread_id_2))]:
///           tensor<?x?xT> into tensor<?x?xT>
/// 
///         tensor.parallel_insert_slice %spointwise into %o2[i((%thread_id_1, %thread_id_2))]:
///           tensor<?xT> into tensor<?xT>
///       }
///     }
///     // Implicit synchronization point.
///     // Sequential context.
///     //
///     ```
/// 
///     Loop with loop bounds example:
/// 
///     ```mlir
///     //
///     // Sequential context.
///     //
///     %pointwise = scf.forall (%i, %j) = (0, 0) to (%dim1, %dim2)
///       step (%tileSize1, %tileSize2) shared_outs(%o1 = %out)
///       -> (tensor<?x?xT>, tensor<?xT>) {
///       //
///       // Parallel context.
///       //
///       %sA = tensor.extract_slice %A[%i, %j][%tileSize1, %tileSize2][1, 1]
///         : tensor<?x?xT> to tensor<?x?xT>
///       %sB = tensor.extract_slice %B[%i, %j][%tileSize1, %tileSize2][1, 1]
///         : tensor<?x?xT> to tensor<?x?xT>
///       %sC = tensor.extract_slice %o[%i, %j][%tileSize1, %tileSize2][1, 1]
///         : tensor<?x?xT> to tensor<?x?xT>
/// 
///       %add = linalg.map {"arith.addf"}
///         ins(%sA, %sB : tensor<?x?xT>, tensor<?x?xT>)
///         outs(%sC : tensor<?x?xT>)
/// 
///       scf.forall.in_parallel {
///         tensor.parallel_insert_slice %add into
///           %o[%i, %j][%tileSize1, %tileSize2][1, 1]
///           : tensor<?x?xT> into tensor<?x?xT>
///       }
///     }
///     // Implicit synchronization point.
///     // Sequential context.
///     //
///     ```
/// 
///     Example with mapping attribute:
/// 
///     ```mlir
///     //
///     // Sequential context. Here `mapping` is expressed as GPU thread mapping
///     // attributes
///     //
///     %matmul_and_pointwise:2 = scf.forall (%thread_id_1, %thread_id_2) in
///         (%num_threads_1, %numthread_id_2) shared_outs(...)
///       -> (tensor<?x?xT>, tensor<?xT>) {
///       //
///       // Parallel context, each thread with id = **(%thread_id_2, %thread_id_1)**
///       // runs its version of the code.
///       //
///        scf.forall.in_parallel {
///          ...
///       }
///     } { mapping = [#gpu.thread<y>, #gpu.thread<x>] }
///     // Implicit synchronization point.
///     // Sequential context.
///     //
///     ```
/// 
///     Example with privatized tensors:
/// 
///     ```mlir
///     %t0 = ...
///     %t1 = ...
///     %r = scf.forall ... shared_outs(%o = t0) -> tensor<?xf32> {
///       // %t0 and %t1 are privatized. %t0 is definitely copied for each thread
///       // because the scf.forall op's %t0 use bufferizes to a memory
///       // write. In the absence of other conflicts, %t1 is copied only if there
///       // are uses of %t1 in the body that bufferize to a memory read and to a
///       // memory write.
///       "some_use"(%t0)
///       "some_use"(%t1)
///     }
///     ```
class ForallOp;

} // namespace mlir::scf
namespace mlir::scf {

/// if-then-else operation
/// The `scf.if` operation represents an if-then-else construct for
///     conditionally executing two regions of code. The operand to an if operation
///     is a boolean value. For example:
/// 
///     ```mlir
///     scf.if %b  {
///       ...
///     } else {
///       ...
///     }
///     ```
/// 
///     `scf.if` may also produce results. Which values are returned depends on
///     which execution path is taken.
/// 
///     Example:
/// 
///     ```mlir
///     %x, %y = scf.if %b -> (f32, f32) {
///       %x_true = ...
///       %y_true = ...
///       scf.yield %x_true, %y_true : f32, f32
///     } else {
///       %x_false = ...
///       %y_false = ...
///       scf.yield %x_false, %y_false : f32, f32
///     }
///     ```
/// 
///     The "then" region has exactly 1 block. The "else" region may have 0 or 1
///     block. In case the `scf.if` produces results, the "else" region must also
///     have exactly 1 block.
/// 
///     The blocks are always terminated with `scf.yield`. If `scf.if` defines no
///     values, the `scf.yield` can be left out, and will be inserted implicitly.
///     Otherwise, it must be explicit.
/// 
///     Example:
/// 
///     ```mlir
///     scf.if %b  {
///       ...
///     }
///     ```
/// 
///     The types of the yielded values must match the result types of the
///     `scf.if`.
class IfOp;

} // namespace mlir::scf
namespace mlir::scf {

/// terminates a `forall` block
/// The `scf.forall.in_parallel` is a designated terminator for
///     the `scf.forall` operation.
/// 
///     It has a single region with a single block that contains a flat list of ops.
///     Each such op participates in the aggregate formation of a single result of
///     the enclosing `scf.forall`.
///     The result number corresponds to the position of the op in the terminator.
class InParallelOp;

} // namespace mlir::scf
namespace mlir::scf {

/// switch-case operation on an index argument
/// The `scf.index_switch` is a control-flow operation that branches to one of
///     the given regions based on the values of the argument and the cases. The
///     argument is always of type `index`.
/// 
///     The operation always has a "default" region and any number of case regions
///     denoted by integer constants. Control-flow transfers to the case region
///     whose constant value equals the value of the argument. If the argument does
///     not equal any of the case values, control-flow transfer to the "default"
///     region.
/// 
///     Example:
/// 
///     ```mlir
///     %0 = scf.index_switch %arg0 : index -> i32
///     case 2 {
///       %1 = arith.constant 10 : i32
///       scf.yield %1 : i32
///     }
///     case 5 {
///       %2 = arith.constant 20 : i32
///       scf.yield %2 : i32
///     }
///     default {
///       %3 = arith.constant 30 : i32
///       scf.yield %3 : i32
///     }
///     ```
class IndexSwitchOp;

} // namespace mlir::scf
namespace mlir::scf {

/// parallel for operation
/// The `scf.parallel` operation represents a loop nest taking 4 groups of SSA
///     values as operands that represent the lower bounds, upper bounds, steps and
///     initial values, respectively. The operation defines a variadic number of
///     SSA values for its induction variables. It has one region capturing the
///     loop body. The induction variables are represented as an argument of this
///     region. These SSA values always have type index, which is the size of the
///     machine word. The steps are values of type index, required to be positive.
///     The lower and upper bounds specify a half-open range: the range includes
///     the lower bound but does not include the upper bound. The initial values
///     have the same types as results of `scf.parallel`. If there are no results,
///     the keyword `init` can be omitted.
/// 
///     Semantically we require that the iteration space can be iterated in any
///     order, and the loop body can be executed in parallel. If there are data
///     races, the behavior is undefined.
/// 
///     The parallel loop operation supports reduction of values produced by
///     individual iterations into a single result. This is modeled using the
///     `scf.reduce` terminator operation (see `scf.reduce` for details). The i-th
///     result of an `scf.parallel` operation is associated with the i-th initial
///     value operand, the i-th operand of the `scf.reduce` operation (the value to
///     be reduced) and the i-th region of the `scf.reduce` operation (the reduction
///     function). Consequently, we require that the number of results of an
///     `scf.parallel` op matches the number of initial values and the the number of
///     reductions in the `scf.reduce` terminator.
/// 
///     The body region must contain exactly one block that terminates with a
///     `scf.reduce` operation. If an `scf.parallel` op has no reductions, the
///     terminator has no operands and no regions. The `scf.parallel` parser will
///     automatically insert the terminator for ops that have no reductions if it is
///     absent.
/// 
///     Example:
/// 
///     ```mlir
///     %init = arith.constant 0.0 : f32
///     %r:2 = scf.parallel (%iv) = (%lb) to (%ub) step (%step) init (%init, %init)
///         -> f32, f32 {
///       %elem_to_reduce1 = load %buffer1[%iv] : memref<100xf32>
///       %elem_to_reduce2 = load %buffer2[%iv] : memref<100xf32>
///       scf.reduce(%elem_to_reduce1, %elem_to_reduce2 : f32, f32) {
///         ^bb0(%lhs : f32, %rhs: f32):
///           %res = arith.addf %lhs, %rhs : f32
///           scf.reduce.return %res : f32
///       }, {
///         ^bb0(%lhs : f32, %rhs: f32):
///           %res = arith.mulf %lhs, %rhs : f32
///           scf.reduce.return %res : f32
///       }
///     }
///     ```
class ParallelOp;

} // namespace mlir::scf
namespace mlir::scf {

/// reduce operation for scf.parallel
/// The `scf.reduce` operation is the terminator for `scf.parallel` operations. It can model
///     an arbitrary number of reductions. It has one region per reduction. Each
///     region has one block with two arguments which have the same type as the
///     corresponding operand of `scf.reduce`. The operands of the op are the values
///     that should be reduce; one value per reduction.
/// 
///     The i-th reduction (i.e., the i-th region and the i-th operand) corresponds
///     the i-th initial value and the i-th result of the enclosing `scf.parallel`
///     op.
/// 
///     The `scf.reduce` operation contains regions whose entry blocks expect two
///     arguments of the same type as the corresponding operand. As the iteration
///     order of the enclosing parallel loop and hence reduction order is
///     unspecified, the results of the reductions may be non-deterministic unless
///     the reductions are associative and commutative.
/// 
///     The result of a reduction region (`scf.reduce.return` operand) must have the
///     same type as the corresponding `scf.reduce` operand and the corresponding
///     `scf.parallel` initial value.
/// 
///     Example:
/// 
///     ```mlir
///     %operand = arith.constant 1.0 : f32
///     scf.reduce(%operand : f32) {
///       ^bb0(%lhs : f32, %rhs: f32):
///         %res = arith.addf %lhs, %rhs : f32
///         scf.reduce.return %res : f32
///     }
///     ```
class ReduceOp;

} // namespace mlir::scf
namespace mlir::scf {

/// terminator for reduce operation
/// The `scf.reduce.return` operation is a special terminator operation for the block inside
///     `scf.reduce` regions. It terminates the region. It should have the same
///     operand type as the corresponding operand of the enclosing `scf.reduce` op.
/// 
///     Example:
/// 
///     ```mlir
///     scf.reduce.return %res : f32
///     ```
class ReduceReturnOp;

} // namespace mlir::scf
namespace mlir::scf {

/// a generic 'while' loop
/// This operation represents a generic "while"/"do-while" loop that keeps
///     iterating as long as a condition is satisfied. There is no restriction on
///     the complexity of the condition. It consists of two regions (with single
///     block each): "before" region and "after" region. The names of regions
///     indicates whether they execute before or after the condition check.
///     Therefore, if the main loop payload is located in the "before" region, the
///     operation is a "do-while" loop. Otherwise, it is a "while" loop.
/// 
///     The "before" region terminates with a special operation, `scf.condition`,
///     that accepts as its first operand an `i1` value indicating whether to
///     proceed to the "after" region (value is `true`) or not. The two regions
///     communicate by means of region arguments. Initially, the "before" region
///     accepts as arguments the operands of the `scf.while` operation and uses them
///     to evaluate the condition. It forwards the trailing, non-condition operands
///     of the `scf.condition` terminator either to the "after" region if the
///     control flow is transferred there or to results of the `scf.while` operation
///     otherwise. The "after" region takes as arguments the values produced by the
///     "before" region and uses `scf.yield` to supply new arguments for the
///     "before" region, into which it transfers the control flow unconditionally.
/// 
///     A simple "while" loop can be represented as follows.
/// 
///     ```mlir
///     %res = scf.while (%arg1 = %init1) : (f32) -> f32 {
///       // "Before" region.
///       // In a "while" loop, this region computes the condition.
///       %condition = call @evaluate_condition(%arg1) : (f32) -> i1
/// 
///       // Forward the argument (as result or "after" region argument).
///       scf.condition(%condition) %arg1 : f32
/// 
///     } do {
///     ^bb0(%arg2: f32):
///       // "After" region.
///       // In a "while" loop, this region is the loop body.
///       %next = call @payload(%arg2) : (f32) -> f32
/// 
///       // Forward the new value to the "before" region.
///       // The operand types must match the types of the `scf.while` operands.
///       scf.yield %next : f32
///     }
///     ```
/// 
///     A simple "do-while" loop can be represented by reducing the "after" block
///     to a simple forwarder.
/// 
///     ```mlir
///     %res = scf.while (%arg1 = %init1) : (f32) -> f32 {
///       // "Before" region.
///       // In a "do-while" loop, this region contains the loop body.
///       %next = call @payload(%arg1) : (f32) -> f32
/// 
///       // And also evaluates the condition.
///       %condition = call @evaluate_condition(%arg1) : (f32) -> i1
/// 
///       // Loop through the "after" region.
///       scf.condition(%condition) %next : f32
/// 
///     } do {
///     ^bb0(%arg2: f32):
///       // "After" region.
///       // Forwards the values back to "before" region unmodified.
///       scf.yield %arg2 : f32
///     }
///     ```
/// 
///     Note that the types of region arguments need not to match with each other.
///     The op expects the operand types to match with argument types of the
///     "before" region; the result types to match with the trailing operand types
///     of the terminator of the "before" region, and with the argument types of the
///     "after" region. The following scheme can be used to share the results of
///     some operations executed in the "before" region with the "after" region,
///     avoiding the need to recompute them.
/// 
///     ```mlir
///     %res = scf.while (%arg1 = %init1) : (f32) -> i64 {
///       // One can perform some computations, e.g., necessary to evaluate the
///       // condition, in the "before" region and forward their results to the
///       // "after" region.
///       %shared = call @shared_compute(%arg1) : (f32) -> i64
/// 
///       // Evaluate the condition.
///       %condition = call @evaluate_condition(%arg1, %shared) : (f32, i64) -> i1
/// 
///       // Forward the result of the shared computation to the "after" region.
///       // The types must match the arguments of the "after" region as well as
///       // those of the `scf.while` results.
///       scf.condition(%condition) %shared : i64
/// 
///     } do {
///     ^bb0(%arg2: i64) {
///       // Use the partial result to compute the rest of the payload in the
///       // "after" region.
///       %res = call @payload(%arg2) : (i64) -> f32
/// 
///       // Forward the new value to the "before" region.
///       // The operand types must match the types of the `scf.while` operands.
///       scf.yield %res : f32
///     }
///     ```
/// 
///     The custom syntax for this operation is as follows.
/// 
///     ```
///     op ::= `scf.while` assignments `:` function-type region `do` region
///            `attributes` attribute-dict
///     initializer ::= /* empty */ | `(` assignment-list `)`
///     assignment-list ::= assignment | assignment `,` assignment-list
///     assignment ::= ssa-value `=` ssa-value
///     ```
class WhileOp;

} // namespace mlir::scf
namespace mlir::scf {

/// loop yield and termination operation
/// The `scf.yield` operation yields an SSA value from the SCF dialect op region and
///     terminates the regions. The semantics of how the values are yielded is
///     defined by the parent operation.
///     If `scf.yield` has any operands, the operands must match the parent
///     operation's results.
///     If the parent operation defines no values, then the `scf.yield` may be
///     left out in the custom syntax and the builders will insert one implicitly.
///     Otherwise, it has to be present in the syntax to indicate which values are
///     yielded.
class YieldOp;

} // namespace mlir::scf
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::ConditionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConditionOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ConditionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("scf.condition", odsAttrs.getContext());
  }

  ConditionOpGenericAdaptorBase(ConditionOp op);

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
class ConditionOpGenericAdaptor : public detail::ConditionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConditionOpGenericAdaptorBase;
  static constexpr int odsIndex_condition = 0;
  static constexpr int odsIndex_args = 1;
public:
  ConditionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConditionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ConditionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConditionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConditionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConditionOpGenericAdaptor(RangeT values, const ConditionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConditionOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConditionOp>>>
  ConditionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getCondition() {
    return (*getODSOperands(0).begin());
  }

  RangeT getArgs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ConditionOpAdaptor : public ConditionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConditionOpGenericAdaptor::ConditionOpGenericAdaptor;
  ConditionOpAdaptor(ConditionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConditionOp : public ::mlir::Op<ConditionOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::HasParent<WhileOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConditionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConditionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_condition = 0;
  static constexpr int odsIndex_args = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.condition");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCondition() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getArgs() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getConditionMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getArgsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value condition, ::mlir::ValueRange args);
  static ConditionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value condition, ::mlir::ValueRange args);
  static ConditionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value condition, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value condition, ::mlir::ValueRange args);
  static ConditionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value condition, ::mlir::ValueRange args);
  static ConditionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value condition, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConditionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConditionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConditionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConditionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  void getSuccessorRegions(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::ConditionOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::ExecuteRegionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExecuteRegionOpGenericAdaptorBase {
public:
  struct Properties {
    using no_inlineTy = ::mlir::UnitAttr;
    no_inlineTy no_inline;

    auto getNoInline() const {
      auto &propStorage = this->no_inline;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNoInline(const ::mlir::UnitAttr &propValue) {
      this->no_inline = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.no_inline == this->no_inline &&
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
  ExecuteRegionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("scf.execute_region", odsAttrs.getContext());
  }

  ExecuteRegionOpGenericAdaptorBase(ExecuteRegionOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getNoInlineAttr();
  bool getNoInline();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ExecuteRegionOpGenericAdaptor : public detail::ExecuteRegionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExecuteRegionOpGenericAdaptorBase;
public:
  ExecuteRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExecuteRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ExecuteRegionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExecuteRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExecuteRegionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExecuteRegionOpGenericAdaptor(RangeT values, const ExecuteRegionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExecuteRegionOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExecuteRegionOp>>>
  ExecuteRegionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ExecuteRegionOpAdaptor : public ExecuteRegionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExecuteRegionOpGenericAdaptor::ExecuteRegionOpGenericAdaptor;
  ExecuteRegionOpAdaptor(ExecuteRegionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExecuteRegionOp : public ::mlir::Op<ExecuteRegionOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::RegionBranchOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExecuteRegionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExecuteRegionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchOpInterface::Trait<ExecuteRegionOp>::getEntrySuccessorOperands;
  using ::mlir::RegionBranchOpInterface::Trait<ExecuteRegionOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<ExecuteRegionOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<ExecuteRegionOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<ExecuteRegionOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<ExecuteRegionOp>::getRegionInvocationBounds;
  using ::mlir::RegionBranchOpInterface::Trait<ExecuteRegionOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("no_inline")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNoInlineAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNoInlineAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.execute_region");
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
  ::mlir::UnitAttr getNoInlineAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().no_inline);
  }

  bool getNoInline();
  void setNoInlineAttr(::mlir::UnitAttr attr) {
    getProperties().no_inline = attr;
  }

  void setNoInline(bool attrValue);
  ::mlir::Attribute removeNoInlineAttr() {
      auto attr = getProperties().no_inline;
      getProperties().no_inline = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, /*optional*/::mlir::UnitAttr no_inline);
  static ExecuteRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, /*optional*/::mlir::UnitAttr no_inline);
  static ExecuteRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, /*optional*/::mlir::UnitAttr no_inline);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, /*optional*/bool no_inline = false);
  static ExecuteRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, /*optional*/bool no_inline = false);
  static ExecuteRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, /*optional*/bool no_inline = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExecuteRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExecuteRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExecuteRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExecuteRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::ExecuteRegionOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::ForOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ForOpGenericAdaptorBase {
public:
  struct Properties {
    using unsignedCmpTy = ::mlir::UnitAttr;
    unsignedCmpTy unsignedCmp;

    auto getUnsignedCmp() const {
      auto &propStorage = this->unsignedCmp;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setUnsignedCmp(const ::mlir::UnitAttr &propValue) {
      this->unsignedCmp = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.unsignedCmp == this->unsignedCmp &&
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
  ForOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("scf.for", odsAttrs.getContext());
  }

  ForOpGenericAdaptorBase(ForOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getUnsignedCmpAttr();
  bool getUnsignedCmp();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ForOpGenericAdaptor : public detail::ForOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ForOpGenericAdaptorBase;
  static constexpr int odsIndex_lowerBound = 0;
  static constexpr int odsIndex_upperBound = 1;
  static constexpr int odsIndex_step = 2;
  static constexpr int odsIndex_initArgs = 3;
public:
  ForOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ForOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ForOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ForOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ForOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ForOpGenericAdaptor(RangeT values, const ForOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ForOp, typename = std::enable_if_t<std::is_same_v<LateInst, ForOp>>>
  ForOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLowerBound() {
    return (*getODSOperands(0).begin());
  }

  ValueT getUpperBound() {
    return (*getODSOperands(1).begin());
  }

  ValueT getStep() {
    return (*getODSOperands(2).begin());
  }

  RangeT getInitArgs() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ForOpAdaptor : public ForOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ForOpGenericAdaptor::ForOpGenericAdaptor;
  ForOpAdaptor(ForOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ForOp : public ::mlir::Op<ForOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<scf::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::LoopLikeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::RegionBranchOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ForOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ForOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lowerBound = 0;
  static constexpr int odsIndex_upperBound = 1;
  static constexpr int odsIndex_step = 2;
  static constexpr int odsIndex_initArgs = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::LoopLikeOpInterface::Trait<ForOp>::isDefinedOutsideOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<ForOp>::moveOutOfLoop;
  using ::mlir::RegionBranchOpInterface::Trait<ForOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<ForOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<ForOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<ForOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<ForOp>::getRegionInvocationBounds;
  using ::mlir::RegionBranchOpInterface::Trait<ForOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("unsignedCmp")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getUnsignedCmpAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getUnsignedCmpAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.for");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getLowerBound() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getUpperBound() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getStep() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::Operation::operand_range getInitArgs() {
    return getODSOperands(3);
  }

  ::mlir::OpOperand &getLowerBoundMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getUpperBoundMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getStepMutable() {
    auto range = getODSOperandIndexAndLength(2);
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
  ::mlir::UnitAttr getUnsignedCmpAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().unsignedCmp);
  }

  bool getUnsignedCmp();
  void setUnsignedCmpAttr(::mlir::UnitAttr attr) {
    getProperties().unsignedCmp = attr;
  }

  void setUnsignedCmp(bool attrValue);
  ::mlir::Attribute removeUnsignedCmpAttr() {
      auto attr = getProperties().unsignedCmp;
      getProperties().unsignedCmp = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lowerBound, Value upperBound, Value step, ValueRange initArgs = {}, function_ref<void(OpBuilder &, Location, Value, ValueRange)> odsArg4 = nullptr, bool unsignedCmp = false);
  static ForOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lowerBound, Value upperBound, Value step, ValueRange initArgs = {}, function_ref<void(OpBuilder &, Location, Value, ValueRange)> odsArg4 = nullptr, bool unsignedCmp = false);
  static ForOp create(::mlir::ImplicitLocOpBuilder &builder, Value lowerBound, Value upperBound, Value step, ValueRange initArgs = {}, function_ref<void(OpBuilder &, Location, Value, ValueRange)> odsArg4 = nullptr, bool unsignedCmp = false);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::SmallVector<::mlir::Region *> getLoopRegions();
  ::llvm::LogicalResult promoteIfSingleIteration(::mlir::RewriterBase &rewriter);
  ::std::optional<::llvm::SmallVector<::mlir::Value>> getLoopInductionVars();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopLowerBounds();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopSteps();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopUpperBounds();
  ::llvm::MutableArrayRef<::mlir::OpOperand> getInitsMutable();
  ::mlir::Block::BlockArgListType getRegionIterArgs();
  ::std::optional<::llvm::MutableArrayRef<::mlir::OpOperand>> getYieldedValuesMutable();
  ::std::optional<::mlir::ResultRange> getLoopResults();
  ::mlir::FailureOr<::mlir::LoopLikeOpInterface> replaceWithAdditionalYields(::mlir::RewriterBase &rewriter, ::mlir::ValueRange newInitOperands, bool replaceInitOperandUsesInLoop, const ::mlir::NewYieldValuesFn &newYieldValuesFn);
  ::std::optional<::llvm::APInt> getStaticTripCount();
  bool isValidInductionVarType(::mlir::Type type);
  ::mlir::LogicalResult setLoopLowerBounds(::llvm::ArrayRef<::mlir::OpFoldResult> bounds);
  ::mlir::LogicalResult setLoopUpperBounds(::llvm::ArrayRef<::mlir::OpFoldResult> bounds);
  ::mlir::LogicalResult setLoopSteps(::llvm::ArrayRef<::mlir::OpFoldResult> steps);
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
  using BodyBuilderFn =
      function_ref<void(OpBuilder &, Location, Value, ValueRange)>;

  Value getInductionVar() { return getBody()->getArgument(0); }

  /// Return the `index`-th region iteration argument.
  BlockArgument getRegionIterArg(unsigned index) {
    assert(index < getNumRegionIterArgs() &&
      "expected an index less than the number of region iter args");
    return getBody()->getArguments().drop_front(getNumInductionVars())[index];
  }

  void setLowerBound(Value bound) { getOperation()->setOperand(0, bound); }
  void setUpperBound(Value bound) { getOperation()->setOperand(1, bound); }
  void setStep(Value step) { getOperation()->setOperand(2, step); }

  /// Number of induction variables, always 1 for scf::ForOp.
  unsigned getNumInductionVars() { return 1; }
  /// Number of region arguments for loop-carried values
  unsigned getNumRegionIterArgs() {
    return getBody()->getNumArguments() - getNumInductionVars();
  }
  /// Number of operands controlling the loop: lb, ub, step
  unsigned getNumControlOperands() { return 3; }

  /// Returns the step as an `APInt` if it is constant.
  std::optional<APInt> getConstantStep();

  /// Interface method for ConditionallySpeculatable.
  Speculation::Speculatability getSpeculatability();
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::ForOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::ForallOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ForallOpGenericAdaptorBase {
public:
  struct Properties {
    using mappingTy = ::mlir::ArrayAttr;
    mappingTy mapping;

    auto getMapping() const {
      auto &propStorage = this->mapping;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setMapping(const ::mlir::ArrayAttr &propValue) {
      this->mapping = propValue;
    }
    using staticLowerBoundTy = ::mlir::DenseI64ArrayAttr;
    staticLowerBoundTy staticLowerBound;

    auto getStaticLowerBound() const {
      auto &propStorage = this->staticLowerBound;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticLowerBound(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->staticLowerBound = propValue;
    }
    using staticStepTy = ::mlir::DenseI64ArrayAttr;
    staticStepTy staticStep;

    auto getStaticStep() const {
      auto &propStorage = this->staticStep;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticStep(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->staticStep = propValue;
    }
    using staticUpperBoundTy = ::mlir::DenseI64ArrayAttr;
    staticUpperBoundTy staticUpperBound;

    auto getStaticUpperBound() const {
      auto &propStorage = this->staticUpperBound;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticUpperBound(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->staticUpperBound = propValue;
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
        rhs.mapping == this->mapping &&
        rhs.staticLowerBound == this->staticLowerBound &&
        rhs.staticStep == this->staticStep &&
        rhs.staticUpperBound == this->staticUpperBound &&
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
  ForallOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("scf.forall", odsAttrs.getContext());
  }

  ForallOpGenericAdaptorBase(ForallOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getStaticLowerBoundAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().staticLowerBound);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticLowerBound();
  ::mlir::DenseI64ArrayAttr getStaticUpperBoundAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().staticUpperBound);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticUpperBound();
  ::mlir::DenseI64ArrayAttr getStaticStepAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().staticStep);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getStaticStep();
  ::mlir::ArrayAttr getMappingAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().mapping);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getMapping();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ForallOpGenericAdaptor : public detail::ForallOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ForallOpGenericAdaptorBase;
  static constexpr int odsIndex_dynamicLowerBound = 0;
  static constexpr int odsIndex_dynamicUpperBound = 1;
  static constexpr int odsIndex_dynamicStep = 2;
  static constexpr int odsIndex_outputs = 3;
public:
  ForallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ForallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ForallOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ForallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ForallOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ForallOpGenericAdaptor(RangeT values, const ForallOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ForallOp, typename = std::enable_if_t<std::is_same_v<LateInst, ForallOp>>>
  ForallOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDynamicLowerBound() {
    return getODSOperands(0);
  }

  RangeT getDynamicUpperBound() {
    return getODSOperands(1);
  }

  RangeT getDynamicStep() {
    return getODSOperands(2);
  }

  RangeT getOutputs() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ForallOpAdaptor : public ForallOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ForallOpGenericAdaptor::ForallOpGenericAdaptor;
  ForallOpAdaptor(ForallOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ForallOp : public ::mlir::Op<ForallOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<scf::InParallelOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::LoopLikeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::RegionBranchOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::OpTrait::HasParallelRegion> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ForallOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ForallOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dynamicLowerBound = 0;
  static constexpr int odsIndex_dynamicUpperBound = 1;
  static constexpr int odsIndex_dynamicStep = 2;
  static constexpr int odsIndex_outputs = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::LoopLikeOpInterface::Trait<ForallOp>::isDefinedOutsideOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<ForallOp>::moveOutOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<ForallOp>::getYieldedValuesMutable;
  using ::mlir::LoopLikeOpInterface::Trait<ForallOp>::getLoopResults;
  using ::mlir::LoopLikeOpInterface::Trait<ForallOp>::replaceWithAdditionalYields;
  using ::mlir::LoopLikeOpInterface::Trait<ForallOp>::getStaticTripCount;
  using ::mlir::LoopLikeOpInterface::Trait<ForallOp>::isValidInductionVarType;
  using ::mlir::LoopLikeOpInterface::Trait<ForallOp>::setLoopLowerBounds;
  using ::mlir::LoopLikeOpInterface::Trait<ForallOp>::setLoopUpperBounds;
  using ::mlir::LoopLikeOpInterface::Trait<ForallOp>::setLoopSteps;
  using ::mlir::RegionBranchOpInterface::Trait<ForallOp>::getEntrySuccessorOperands;
  using ::mlir::RegionBranchOpInterface::Trait<ForallOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<ForallOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<ForallOp>::getSuccessorInputs;
  using ::mlir::RegionBranchOpInterface::Trait<ForallOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<ForallOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<ForallOp>::getRegionInvocationBounds;
  using ::mlir::RegionBranchOpInterface::Trait<ForallOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("mapping"), ::llvm::StringRef("staticLowerBound"), ::llvm::StringRef("staticStep"), ::llvm::StringRef("staticUpperBound"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMappingAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMappingAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStaticLowerBoundAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStaticLowerBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStaticStepAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStaticStepAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getStaticUpperBoundAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getStaticUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.forall");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDynamicLowerBound() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getDynamicUpperBound() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getDynamicStep() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getOutputs() {
    return getODSOperands(3);
  }

  ::mlir::MutableOperandRange getDynamicLowerBoundMutable();
  ::mlir::MutableOperandRange getDynamicUpperBoundMutable();
  ::mlir::MutableOperandRange getDynamicStepMutable();
  ::mlir::MutableOperandRange getOutputsMutable();
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
  ::mlir::DenseI64ArrayAttr getStaticLowerBoundAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().staticLowerBound);
  }

  ::llvm::ArrayRef<int64_t> getStaticLowerBound();
  ::mlir::DenseI64ArrayAttr getStaticUpperBoundAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().staticUpperBound);
  }

  ::llvm::ArrayRef<int64_t> getStaticUpperBound();
  ::mlir::DenseI64ArrayAttr getStaticStepAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().staticStep);
  }

  ::llvm::ArrayRef<int64_t> getStaticStep();
  ::mlir::ArrayAttr getMappingAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().mapping);
  }

  ::std::optional< ::mlir::ArrayAttr > getMapping();
  void setStaticLowerBoundAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().staticLowerBound = attr;
  }

  void setStaticLowerBound(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticUpperBoundAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().staticUpperBound = attr;
  }

  void setStaticUpperBound(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticStepAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().staticStep = attr;
  }

  void setStaticStep(::llvm::ArrayRef<int64_t> attrValue);
  void setMappingAttr(::mlir::ArrayAttr attr) {
    getProperties().mapping = attr;
  }

  ::mlir::Attribute removeMappingAttr() {
      auto attr = getProperties().mapping;
      getProperties().mapping = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<OpFoldResult> lbs, ArrayRef<OpFoldResult> ubs, ArrayRef<OpFoldResult> steps, ValueRange outputs, std::optional<ArrayAttr> mapping, function_ref<void(OpBuilder &, Location, ValueRange)> bodyBuilderFn = nullptr);
  static ForallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<OpFoldResult> lbs, ArrayRef<OpFoldResult> ubs, ArrayRef<OpFoldResult> steps, ValueRange outputs, std::optional<ArrayAttr> mapping, function_ref<void(OpBuilder &, Location, ValueRange)> bodyBuilderFn = nullptr);
  static ForallOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<OpFoldResult> lbs, ArrayRef<OpFoldResult> ubs, ArrayRef<OpFoldResult> steps, ValueRange outputs, std::optional<ArrayAttr> mapping, function_ref<void(OpBuilder &, Location, ValueRange)> bodyBuilderFn = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<OpFoldResult> ubs, ValueRange outputs, std::optional<ArrayAttr> mapping, function_ref<void(OpBuilder &, Location, ValueRange)> bodyBuilderFn = nullptr);
  static ForallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<OpFoldResult> ubs, ValueRange outputs, std::optional<ArrayAttr> mapping, function_ref<void(OpBuilder &, Location, ValueRange)> bodyBuilderFn = nullptr);
  static ForallOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<OpFoldResult> ubs, ValueRange outputs, std::optional<ArrayAttr> mapping, function_ref<void(OpBuilder &, Location, ValueRange)> bodyBuilderFn = nullptr);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::SmallVector<::mlir::Region *> getLoopRegions();
  ::llvm::LogicalResult promoteIfSingleIteration(::mlir::RewriterBase &rewriter);
  ::std::optional<::llvm::SmallVector<::mlir::Value>> getLoopInductionVars();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopLowerBounds();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopSteps();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopUpperBounds();
  ::llvm::MutableArrayRef<::mlir::OpOperand> getInitsMutable();
  ::mlir::Block::BlockArgListType getRegionIterArgs();
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
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
  /// Get induction variables.
  SmallVector<Value> getInductionVars() {
    std::optional<SmallVector<Value>> maybeInductionVars = getLoopInductionVars();
    assert(maybeInductionVars.has_value() && "expected values");
    return *maybeInductionVars;
  }
  /// Get lower bounds as OpFoldResult.
  SmallVector<OpFoldResult> getMixedLowerBound() {
    std::optional<SmallVector<OpFoldResult>> maybeLowerBounds = getLoopLowerBounds();
    assert(maybeLowerBounds.has_value() && "expected values");
    return *maybeLowerBounds;
  }

  /// Get upper bounds as OpFoldResult.
  SmallVector<OpFoldResult> getMixedUpperBound() {
    std::optional<SmallVector<OpFoldResult>> maybeUpperBounds = getLoopUpperBounds();
    assert(maybeUpperBounds.has_value() && "expected values");
    return *maybeUpperBounds;
  }

  /// Get steps as OpFoldResult.
  SmallVector<OpFoldResult> getMixedStep() {
    std::optional<SmallVector<OpFoldResult>> maybeSteps = getLoopSteps();
    assert(maybeSteps.has_value() && "expected values");
    return *maybeSteps;
  }

  /// Get lower bounds as values.
  SmallVector<Value> getLowerBound(OpBuilder &b) {
    return getValueOrCreateConstantIndexOp(b, getLoc(), getMixedLowerBound());
  }

  /// Get upper bounds as values.
  SmallVector<Value> getUpperBound(OpBuilder &b) {
    return getValueOrCreateConstantIndexOp(b, getLoc(), getMixedUpperBound());
  }

  /// Get steps as values.
  SmallVector<Value> getStep(OpBuilder &b) {
    return getValueOrCreateConstantIndexOp(b, getLoc(), getMixedStep());
  }

  int64_t getRank() { return getStaticLowerBound().size(); }

  /// Number of operands controlling the loop: lbs, ubs, steps
  unsigned getNumControlOperands() { return 3 * getRank(); }

  /// Number of dynamic operands controlling the loop: lbs, ubs, steps
  unsigned getNumDynamicControlOperands() {
    return getODSOperandIndexAndLength(3).first;
  }

  OpResult getTiedOpResult(OpOperand *opOperand) {
    assert(opOperand->getOperandNumber() >= getNumDynamicControlOperands() &&
           "invalid operand");
    return getOperation()->getOpResult(
        opOperand->getOperandNumber() - getNumDynamicControlOperands());
  }

  /// Return the num_threads operand that is tied to the given thread id
  /// block argument.
  OpOperand *getTiedOpOperand(BlockArgument bbArg) {
    assert(bbArg.getArgNumber() >= getRank() && "invalid bbArg");

    return &getOperation()->getOpOperand(getNumDynamicControlOperands() +
                                         bbArg.getArgNumber() - getRank());
  }

  /// Return the shared_outs operand that is tied to the given OpResult.
  OpOperand *getTiedOpOperand(OpResult opResult) {
    assert(opResult.getDefiningOp() == getOperation() && "invalid OpResult");
    return &getOperation()->getOpOperand(getNumDynamicControlOperands() +
                                         opResult.getResultNumber());
  }

  BlockArgument getTiedBlockArgument(OpOperand *opOperand) {
    assert(opOperand->getOperandNumber() >= getNumDynamicControlOperands() &&
           "invalid operand");

    return getBody()->getArgument(opOperand->getOperandNumber() -
                                  getNumDynamicControlOperands() + getRank());
  }

  BlockArgument getTiedBlockArgument(OpResult opResult) {
    assert(opResult.getDefiningOp() == getOperation()  && "invalid OpResult");
    return getBody()->getArgument(getRank() + opResult.getResultNumber());
  }

  ::mlir::Value getInductionVar(int64_t idx) {
    return getInductionVars()[idx];
  }

  ::mlir::Block::BlockArgListType getRegionOutArgs() {
    return getBody()->getArguments().drop_front(getRank());
  }

  /// Checks if the lbs are zeros and steps are ones.
  bool isNormalized();

  InParallelOp getTerminator();

  // Declare the shared_outs as inits/outs to DestinationStyleOpInterface.
  MutableOperandRange getDpsInitsMutable() { return getOutputsMutable(); }

  /// Returns operations within scf.forall.in_parallel whose destination
  /// operand is the block argument `bbArg`.
  SmallVector<Operation*> getCombiningOps(BlockArgument bbArg);

  /// Returns the subset of DeviceMappingArrayAttrs of type
  /// DeviceMappingAttrInterface.
  SmallVector<DeviceMappingAttrInterface> getDeviceMappingAttrs();

  /// Returns the at most one DeviceMaskingAttrInterface in the mapping.
  /// If more than one DeviceMaskingAttrInterface is specified, returns
  /// failure. If no mapping is present, returns nullptr.
  FailureOr<DeviceMaskingAttrInterface> getDeviceMaskingAttr();

  /// Returns true if the mapping specified for this forall op is linear.
  bool usesLinearMapping();
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::ForallOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::IfOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IfOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  IfOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("scf.if", odsAttrs.getContext());
  }

  IfOpGenericAdaptorBase(IfOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

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
class IfOpGenericAdaptor : public detail::IfOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IfOpGenericAdaptorBase;
  static constexpr int odsIndex_condition = 0;
public:
  IfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IfOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IfOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IfOpGenericAdaptor(RangeT values, const IfOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IfOp, typename = std::enable_if_t<std::is_same_v<LateInst, IfOp>>>
  IfOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getCondition() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class IfOpAdaptor : public IfOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IfOpGenericAdaptor::IfOpGenericAdaptor;
  IfOpAdaptor(IfOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IfOp : public ::mlir::Op<IfOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<scf::YieldOp>::Impl, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::OpInvariants, ::mlir::RegionBranchOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpTrait::InferTypeOpAdaptor, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::RecursivelySpeculatableImplTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IfOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IfOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_condition = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchOpInterface::Trait<IfOp>::getEntrySuccessorOperands;
  using ::mlir::RegionBranchOpInterface::Trait<IfOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<IfOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<IfOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<IfOp>::areTypesCompatible;
  using ::mlir::InferTypeOpInterface::Trait<IfOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.if");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCondition() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getConditionMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, Value cond);
  static IfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, Value cond);
  static IfOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, Value cond);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, Value cond, bool addThenBlock, bool addElseBlock);
  static IfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, Value cond, bool addThenBlock, bool addElseBlock);
  static IfOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, Value cond, bool addThenBlock, bool addElseBlock);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value cond, bool withElseRegion);
  static IfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value cond, bool withElseRegion);
  static IfOp create(::mlir::ImplicitLocOpBuilder &builder, Value cond, bool withElseRegion);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, Value cond, bool withElseRegion);
  static IfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, Value cond, bool withElseRegion);
  static IfOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, Value cond, bool withElseRegion);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value cond, function_ref<void(OpBuilder &, Location)> thenBuilder = buildTerminatedBody, function_ref<void(OpBuilder &, Location)> elseBuilder = nullptr);
  static IfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value cond, function_ref<void(OpBuilder &, Location)> thenBuilder = buildTerminatedBody, function_ref<void(OpBuilder &, Location)> elseBuilder = nullptr);
  static IfOp create(::mlir::ImplicitLocOpBuilder &builder, Value cond, function_ref<void(OpBuilder &, Location)> thenBuilder = buildTerminatedBody, function_ref<void(OpBuilder &, Location)> elseBuilder = nullptr);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  void getEntrySuccessorRegions(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);
  void getRegionInvocationBounds(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> &invocationBounds);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
      static ::llvm::LogicalResult
      inferReturnTypes(::mlir::MLIRContext *context,
                              std::optional<::mlir::Location> location,
                              Adaptor adaptor,
                              ::llvm::SmallVectorImpl<::mlir::Type> &inferredReturnTypes);


  OpBuilder getThenBodyBuilder(OpBuilder::Listener *listener = nullptr) {
    Block* body = getBody(0);
    return getResults().empty() ? OpBuilder::atBlockTerminator(body, listener)
                                : OpBuilder::atBlockEnd(body, listener);
  }
  OpBuilder getElseBodyBuilder(OpBuilder::Listener *listener = nullptr) {
    Block* body = getBody(1);
    return getResults().empty() ? OpBuilder::atBlockTerminator(body, listener)
                                : OpBuilder::atBlockEnd(body, listener);
  }
  Block* thenBlock();
  YieldOp thenYield();
  Block* elseBlock();
  YieldOp elseYield();
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::IfOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::InParallelOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InParallelOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  InParallelOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("scf.forall.in_parallel", odsAttrs.getContext());
  }

  InParallelOpGenericAdaptorBase(InParallelOp op);

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
class InParallelOpGenericAdaptor : public detail::InParallelOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InParallelOpGenericAdaptorBase;
public:
  InParallelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InParallelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : InParallelOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InParallelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InParallelOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InParallelOpGenericAdaptor(RangeT values, const InParallelOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InParallelOp, typename = std::enable_if_t<std::is_same_v<LateInst, InParallelOp>>>
  InParallelOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InParallelOpAdaptor : public InParallelOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InParallelOpGenericAdaptor::InParallelOpGenericAdaptor;
  InParallelOpAdaptor(InParallelOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InParallelOp : public ::mlir::Op<InParallelOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ForallOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator, ::mlir::InParallelOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::RegionKindInterface::Trait, ::mlir::OpTrait::HasOnlyGraphRegion> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InParallelOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InParallelOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<InParallelOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.forall.in_parallel");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static InParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static InParallelOp create(::mlir::ImplicitLocOpBuilder &builder);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  ::llvm::SmallVector<::mlir::BlockArgument> getDests();
  ::llvm::iterator_range<::mlir::Block::iterator> getYieldingOps();
  ::mlir::OpResult getParentResult(int64_t idx);
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::InParallelOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::IndexSwitchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IndexSwitchOpGenericAdaptorBase {
public:
  struct Properties {
    using casesTy = ::mlir::DenseI64ArrayAttr;
    casesTy cases;

    auto getCases() const {
      auto &propStorage = this->cases;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setCases(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->cases = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.cases == this->cases &&
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
  IndexSwitchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("scf.index_switch", odsAttrs.getContext());
  }

  IndexSwitchOpGenericAdaptorBase(IndexSwitchOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getCasesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().cases);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getCases();
  ::mlir::Region &getDefaultRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getCaseRegions() {
    return odsRegions.drop_front(1);
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class IndexSwitchOpGenericAdaptor : public detail::IndexSwitchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IndexSwitchOpGenericAdaptorBase;
  static constexpr int odsIndex_arg = 0;
public:
  IndexSwitchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IndexSwitchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IndexSwitchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IndexSwitchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IndexSwitchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IndexSwitchOpGenericAdaptor(RangeT values, const IndexSwitchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IndexSwitchOp, typename = std::enable_if_t<std::is_same_v<LateInst, IndexSwitchOp>>>
  IndexSwitchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getArg() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class IndexSwitchOpAdaptor : public IndexSwitchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IndexSwitchOpGenericAdaptor::IndexSwitchOpGenericAdaptor;
  IndexSwitchOpAdaptor(IndexSwitchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IndexSwitchOp : public ::mlir::Op<IndexSwitchOp, ::mlir::OpTrait::AtLeastNRegions<1>::Impl, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<scf::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::RegionBranchOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IndexSwitchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IndexSwitchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_arg = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchOpInterface::Trait<IndexSwitchOp>::getEntrySuccessorOperands;
  using ::mlir::RegionBranchOpInterface::Trait<IndexSwitchOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<IndexSwitchOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<IndexSwitchOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<IndexSwitchOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("cases")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCasesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCasesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.index_switch");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getArg() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getArgMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
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

  ::mlir::Region &getDefaultRegion() {
    return (*this)->getRegion(0);
  }

  ::mlir::MutableArrayRef<::mlir::Region> getCaseRegions() {
    return (*this)->getRegions().drop_front(1);
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
  ::mlir::DenseI64ArrayAttr getCasesAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().cases);
  }

  ::llvm::ArrayRef<int64_t> getCases();
  void setCasesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().cases = attr;
  }

  void setCases(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value arg, ::mlir::DenseI64ArrayAttr cases, unsigned caseRegionsCount);
  static IndexSwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value arg, ::mlir::DenseI64ArrayAttr cases, unsigned caseRegionsCount);
  static IndexSwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value arg, ::mlir::DenseI64ArrayAttr cases, unsigned caseRegionsCount);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value arg, ::llvm::ArrayRef<int64_t> cases, unsigned caseRegionsCount);
  static IndexSwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value arg, ::llvm::ArrayRef<int64_t> cases, unsigned caseRegionsCount);
  static IndexSwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value arg, ::llvm::ArrayRef<int64_t> cases, unsigned caseRegionsCount);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static IndexSwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static IndexSwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes, unsigned numRegions);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  static IndexSwitchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  static IndexSwitchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes, unsigned numRegions);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  void getEntrySuccessorRegions(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);
  void getRegionInvocationBounds(::llvm::ArrayRef<::mlir::Attribute> operands, ::llvm::SmallVectorImpl<::mlir::InvocationBounds> &invocationBounds);
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
  /// Get the number of cases.
  unsigned getNumCases();

  /// Get the default region body.
  Block &getDefaultBlock();

  /// Get the body of a case region.
  Block &getCaseBlock(unsigned idx);
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::IndexSwitchOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::ParallelOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ParallelOpGenericAdaptorBase {
public:
  struct Properties {
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
  ParallelOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("scf.parallel", odsAttrs.getContext());
  }

  ParallelOpGenericAdaptorBase(ParallelOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
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
class ParallelOpGenericAdaptor : public detail::ParallelOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ParallelOpGenericAdaptorBase;
  static constexpr int odsIndex_lowerBound = 0;
  static constexpr int odsIndex_upperBound = 1;
  static constexpr int odsIndex_step = 2;
  static constexpr int odsIndex_initVals = 3;
public:
  ParallelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ParallelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ParallelOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ParallelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ParallelOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ParallelOpGenericAdaptor(RangeT values, const ParallelOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ParallelOp, typename = std::enable_if_t<std::is_same_v<LateInst, ParallelOp>>>
  ParallelOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getLowerBound() {
    return getODSOperands(0);
  }

  RangeT getUpperBound() {
    return getODSOperands(1);
  }

  RangeT getStep() {
    return getODSOperands(2);
  }

  RangeT getInitVals() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ParallelOpAdaptor : public ParallelOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ParallelOpGenericAdaptor::ParallelOpGenericAdaptor;
  ParallelOpAdaptor(ParallelOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ParallelOp : public ::mlir::Op<ParallelOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<scf::ReduceOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::LoopLikeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::RegionBranchOpInterface::Trait, ::mlir::OpTrait::HasParallelRegion> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ParallelOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ParallelOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lowerBound = 0;
  static constexpr int odsIndex_upperBound = 1;
  static constexpr int odsIndex_step = 2;
  static constexpr int odsIndex_initVals = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::isDefinedOutsideOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::moveOutOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::promoteIfSingleIteration;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::getInitsMutable;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::getRegionIterArgs;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::getYieldedValuesMutable;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::getLoopResults;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::replaceWithAdditionalYields;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::getStaticTripCount;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::isValidInductionVarType;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::setLoopLowerBounds;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::setLoopUpperBounds;
  using ::mlir::LoopLikeOpInterface::Trait<ParallelOp>::setLoopSteps;
  using ::mlir::RegionBranchOpInterface::Trait<ParallelOp>::getEntrySuccessorOperands;
  using ::mlir::RegionBranchOpInterface::Trait<ParallelOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<ParallelOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<ParallelOp>::getSuccessorInputs;
  using ::mlir::RegionBranchOpInterface::Trait<ParallelOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<ParallelOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<ParallelOp>::getRegionInvocationBounds;
  using ::mlir::RegionBranchOpInterface::Trait<ParallelOp>::areTypesCompatible;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.parallel");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getLowerBound() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getUpperBound() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getStep() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getInitVals() {
    return getODSOperands(3);
  }

  ::mlir::MutableOperandRange getLowerBoundMutable();
  ::mlir::MutableOperandRange getUpperBoundMutable();
  ::mlir::MutableOperandRange getStepMutable();
  ::mlir::MutableOperandRange getInitValsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange lowerBounds, ValueRange upperBounds, ValueRange steps, ValueRange initVals, function_ref<void (OpBuilder &, Location, ValueRange, ValueRange)> bodyBuilderFn = nullptr);
  static ParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange lowerBounds, ValueRange upperBounds, ValueRange steps, ValueRange initVals, function_ref<void (OpBuilder &, Location, ValueRange, ValueRange)> bodyBuilderFn = nullptr);
  static ParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange lowerBounds, ValueRange upperBounds, ValueRange steps, ValueRange initVals, function_ref<void (OpBuilder &, Location, ValueRange, ValueRange)> bodyBuilderFn = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange lowerBounds, ValueRange upperBounds, ValueRange steps, function_ref<void (OpBuilder &, Location, ValueRange)> bodyBuilderFn = nullptr);
  static ParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange lowerBounds, ValueRange upperBounds, ValueRange steps, function_ref<void (OpBuilder &, Location, ValueRange)> bodyBuilderFn = nullptr);
  static ParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange lowerBounds, ValueRange upperBounds, ValueRange steps, function_ref<void (OpBuilder &, Location, ValueRange)> bodyBuilderFn = nullptr);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::SmallVector<::mlir::Region *> getLoopRegions();
  ::std::optional<::llvm::SmallVector<::mlir::Value>> getLoopInductionVars();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopLowerBounds();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopSteps();
  ::std::optional<::llvm::SmallVector<::mlir::OpFoldResult>> getLoopUpperBounds();
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    return {};
  }

public:
  /// Get induction variables.
  SmallVector<Value> getInductionVars() {
    std::optional<SmallVector<Value>> maybeInductionVars = getLoopInductionVars();;
    assert(maybeInductionVars.has_value() && "expected values");
    return *maybeInductionVars;
  }
  unsigned getNumLoops() { return getStep().size(); }
  unsigned getNumReductions() { return getInitVals().size(); }
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::ParallelOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::ReduceOp declarations
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
      odsOpName.emplace("scf.reduce", odsAttrs.getContext());
  }

  ReduceOpGenericAdaptorBase(ReduceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::RegionRange getReductions() {
    return odsRegions.drop_front(0);
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
  static constexpr int odsIndex_operands = 0;
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

  RangeT getOperands() {
    return getODSOperands(0);
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
class ReduceOp : public ::mlir::Op<ReduceOp, ::mlir::OpTrait::VariadicRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<ParallelOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::RegionBranchTerminatorOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReduceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReduceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<ReduceOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.reduce");
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

  ::mlir::MutableArrayRef<::mlir::Region> getReductions() {
    return (*this)->getRegions().drop_front(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange operands);
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange operands);
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::ReduceOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::ReduceReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReduceReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ReduceReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("scf.reduce.return", odsAttrs.getContext());
  }

  ReduceReturnOpGenericAdaptorBase(ReduceReturnOp op);

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
class ReduceReturnOpGenericAdaptor : public detail::ReduceReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReduceReturnOpGenericAdaptorBase;
  static constexpr int odsIndex_result = 0;
public:
  ReduceReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReduceReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReduceReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReduceReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReduceReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReduceReturnOpGenericAdaptor(RangeT values, const ReduceReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReduceReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReduceReturnOp>>>
  ReduceReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ReduceReturnOpAdaptor : public ReduceReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReduceReturnOpGenericAdaptor::ReduceReturnOpGenericAdaptor;
  ReduceReturnOpAdaptor(ReduceReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReduceReturnOp : public ::mlir::Op<ReduceReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParent<ReduceOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReduceReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReduceReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_result = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.reduce.return");
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
  static ReduceReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value result);
  static ReduceReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value result);
  static ReduceReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value result);
  static ReduceReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value result);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::ReduceReturnOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::WhileOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WhileOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WhileOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("scf.while", odsAttrs.getContext());
  }

  WhileOpGenericAdaptorBase(WhileOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBefore() {
    return *odsRegions[0];
  }

  ::mlir::Region &getAfter() {
    return *odsRegions[1];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class WhileOpGenericAdaptor : public detail::WhileOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WhileOpGenericAdaptorBase;
  static constexpr int odsIndex_inits = 0;
public:
  WhileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WhileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WhileOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WhileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WhileOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WhileOpGenericAdaptor(RangeT values, const WhileOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WhileOp, typename = std::enable_if_t<std::is_same_v<LateInst, WhileOp>>>
  WhileOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInits() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WhileOpAdaptor : public WhileOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WhileOpGenericAdaptor::WhileOpGenericAdaptor;
  WhileOpAdaptor(WhileOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WhileOp : public ::mlir::Op<WhileOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::RegionBranchOpInterface::Trait, ::mlir::LoopLikeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WhileOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WhileOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inits = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchOpInterface::Trait<WhileOp>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<WhileOp>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<WhileOp>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<WhileOp>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<WhileOp>::getRegionInvocationBounds;
  using ::mlir::RegionBranchOpInterface::Trait<WhileOp>::areTypesCompatible;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::isDefinedOutsideOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::moveOutOfLoop;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::promoteIfSingleIteration;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::getLoopInductionVars;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::getLoopLowerBounds;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::getLoopSteps;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::getLoopUpperBounds;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::getInitsMutable;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::getLoopResults;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::replaceWithAdditionalYields;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::getStaticTripCount;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::isValidInductionVarType;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::setLoopLowerBounds;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::setLoopUpperBounds;
  using ::mlir::LoopLikeOpInterface::Trait<WhileOp>::setLoopSteps;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.while");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInits() {
    return getODSOperands(0);
  }

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

  ::mlir::Region &getBefore() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getAfter() {
    return (*this)->getRegion(1);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, ValueRange inits, function_ref<void(OpBuilder &, Location, ValueRange)> beforeBuilder, function_ref<void(OpBuilder &, Location, ValueRange)> afterBuilder);
  static WhileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, ValueRange inits, function_ref<void(OpBuilder &, Location, ValueRange)> beforeBuilder, function_ref<void(OpBuilder &, Location, ValueRange)> afterBuilder);
  static WhileOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, ValueRange inits, function_ref<void(OpBuilder &, Location, ValueRange)> beforeBuilder, function_ref<void(OpBuilder &, Location, ValueRange)> afterBuilder);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WhileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WhileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WhileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WhileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OperandRange getEntrySuccessorOperands(::mlir::RegionSuccessor successor);
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);
  ::llvm::SmallVector<::mlir::Region *> getLoopRegions();
  ::mlir::Block::BlockArgListType getRegionIterArgs();
  ::std::optional<::llvm::MutableArrayRef<::mlir::OpOperand>> getYieldedValuesMutable();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
  using BodyBuilderFn =
      function_ref<void(OpBuilder &, Location, ValueRange)>;

  ConditionOp getConditionOp();
  YieldOp getYieldOp();

  Block::BlockArgListType getBeforeArguments();
  Block::BlockArgListType getAfterArguments();
  Block *getBeforeBody() { return &getBefore().front(); }
  Block *getAfterBody() { return &getAfter().front(); }
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::WhileOp)

namespace mlir::scf {


//===----------------------------------------------------------------------===//
// ::mlir::scf::YieldOp declarations
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
      odsOpName.emplace("scf.yield", odsAttrs.getContext());
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
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<ExecuteRegionOp, ForOp, IfOp, IndexSwitchOp, WhileOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = YieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = YieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_results = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<YieldOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("scf.yield");
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
  ::mlir::MutableOperandRange getMutableSuccessorOperands(::mlir::RegionSuccessor point);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::scf
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::scf::YieldOp)


#endif // GET_OP_CLASSES

