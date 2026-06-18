/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: OpenMPOps.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::omp {

/// allocate directive
/// The storage for each list item that appears in the allocate directive is
///     provided an allocation through the memory allocator.
///   
///     The `align` clause is used to specify the byte alignment to use for
///     allocations associated with the construct on which the clause appears.
///   
///     `allocator` specifies the memory allocator to be used for allocations
///     associated with the construct on which the clause appears.
class AllocateDirOp;

} // namespace mlir::omp
namespace mlir::omp {

/// performs an atomic capture
/// This operation performs an atomic capture.
/// 
///     The region has the following allowed forms:
///     ```
///       omp.atomic.capture {
///         omp.atomic.update ...
///         omp.atomic.read ...
///         omp.terminator
///       }
/// 
///       omp.atomic.capture {
///         omp.atomic.read ...
///         omp.atomic.update ...
///         omp.terminator
///       }
/// 
///       omp.atomic.capture {
///         omp.atomic.read ...
///         omp.atomic.write ...
///         omp.terminator
///       }
///     ```
///   
///     `hint` is the value of hint (as specified in the hint clause). It is a
///     compile time constant. As the name suggests, this is just a hint for
///     optimization.
///   
///     `memory_order` indicates the memory ordering behavior of the construct. It
///     can be one of `seq_cst`, `acq_rel`, `release`, `acquire` or `relaxed`.
class AtomicCaptureOp;

} // namespace mlir::omp
namespace mlir::omp {

/// performs an atomic read
/// This operation performs an atomic read.
/// 
///     The operand `x` is the address from where the value is atomically read.
///     The operand `v` is the address where the value is stored after reading.
///   
///     `hint` is the value of hint (as specified in the hint clause). It is a
///     compile time constant. As the name suggests, this is just a hint for
///     optimization.
///   
///     `memory_order` indicates the memory ordering behavior of the construct. It
///     can be one of `seq_cst`, `acq_rel`, `release`, `acquire` or `relaxed`.
class AtomicReadOp;

} // namespace mlir::omp
namespace mlir::omp {

/// performs an atomic update
/// This operation performs an atomic update.
/// 
///     The operand `x` is exactly the same as the operand `x` in the OpenMP
///     Standard (OpenMP 5.0, section 2.17.7). It is the address of the variable
///     that is being updated. `x` is atomically read/written.
/// 
///     The region describes how to update the value of `x`. It takes the value at
///     `x` as an input and must yield the updated value. Only the update to `x` is
///     atomic. Generally the region must have only one instruction, but can
///     potentially have more than one instructions too. The update is sematically
///     similar to a compare-exchange loop based atomic update.
/// 
///     The syntax of atomic update operation is different from atomic read and
///     atomic write operations. This is because only the host dialect knows how to
///     appropriately update a value. For example, while generating LLVM IR, if
///     there are no special `atomicrmw` instructions for the operation-type
///     combination in atomic update, a compare-exchange loop is generated, where
///     the core update operation is directly translated like regular operations by
///     the host dialect. The front-end must handle semantic checks for allowed
///     operations.
///   
///     `hint` is the value of hint (as specified in the hint clause). It is a
///     compile time constant. As the name suggests, this is just a hint for
///     optimization.
///   
///     `memory_order` indicates the memory ordering behavior of the construct. It
///     can be one of `seq_cst`, `acq_rel`, `release`, `acquire` or `relaxed`.
class AtomicUpdateOp;

} // namespace mlir::omp
namespace mlir::omp {

/// performs an atomic write
/// This operation performs an atomic write.
/// 
///     The operand `x` is the address to where the `expr` is atomically
///     written w.r.t. multiple threads. The evaluation of `expr` need not be
///     atomic w.r.t. the write to address. In general, the type(x) must
///     dereference to type(expr).
///   
///     `hint` is the value of hint (as specified in the hint clause). It is a
///     compile time constant. As the name suggests, this is just a hint for
///     optimization.
///   
///     `memory_order` indicates the memory ordering behavior of the construct. It
///     can be one of `seq_cst`, `acq_rel`, `release`, `acquire` or `relaxed`.
class AtomicWriteOp;

} // namespace mlir::omp
namespace mlir::omp {

/// barrier construct
/// The barrier construct specifies an explicit barrier at the point at which
///     the construct appears.
class BarrierOp;

} // namespace mlir::omp
namespace mlir::omp {

/// cancel directive
/// The cancel construct activates cancellation of the innermost enclosing
///     region of the type specified.
class CancelOp;

} // namespace mlir::omp
namespace mlir::omp {

/// cancellation point directive
/// The cancellation point construct introduces a user-defined cancellation
///     point at which implicit or explicit tasks check if cancellation of the
///     innermost enclosing region of the type specified has been activated.
class CancellationPointOp;

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP Canonical Loop Operation
/// All loops that conform to OpenMP's definition of a canonical loop can be
///     simplified to a CanonicalLoopOp. In particular, there are no loop-carried
///     variables and the number of iterations it will execute is known before the
///     operation. This allows e.g. to determine the number of threads and chunks
///     the iterations space is split into before executing any iteration. More
///     restrictions may apply in cases such as (collapsed) loop nests, doacross
///     loops, etc.
/// 
///     In contrast to other loop operations such as `scf.for`, the number of
///     iterations is determined by only a single variable, the trip-count. The
///     induction variable value is the logical iteration number of that iteration,
///     which OpenMP defines to be between 0 and the trip-count (exclusive).
///     Loop representation having lower-bound, upper-bound, and step-size operands,
///     require passes to do more work than necessary, including handling special
///     cases such as upper-bound smaller than lower-bound, upper-bound equal to
///     the integer type's maximal value, negative step size, etc. This complexity
///     is better only handled once by the front-end and can apply its semantics
///     for such cases while still being able to represent any kind of loop, which
///     kind of the point of a mid-end intermediate representation. User-defined
///     types such as random-access iterators in C++ could not directly be
///     represented anyway.
/// 
///     The induction variable is always of the same type as the tripcount argument.
///     Since it can never be negative, tripcount is always interpreted as an
///     unsigned integer. It is the caller's responsibility to ensure the tripcount
///     is not negative when its interpretation is signed, i.e.
///     `%tripcount = max(0,%tripcount)`.
/// 
///     An optional argument to a omp.canonical_loop that can be passed in
///     is a CanonicalLoopInfo value that can be used to refer to the canonical
///     loop to apply transformations -- such as tiling, unrolling, or
///     work-sharing -- to the loop, similar to the transform dialect but
///     with OpenMP-specific semantics. Because it is optional, it has to be the
///     last of the operands, but appears first in the pretty format printing.
/// 
///     The pretty assembly format is inspired by python syntax, where `range(n)`
///     returns an iterator that runs from $0$ to $n-1$. The pretty assembly syntax
///     is one of:
/// 
///      omp.canonical_loop(%cli) %iv : !type in range(%tripcount)
///      omp.canonical_loop       %iv : !type in range(%tripcount)
/// 
///     A CanonicalLoopOp is lowered to LLVM-IR using
///     `OpenMPIRBuilder::createCanonicalLoop`.
/// 
///     #### Examples
/// 
///     Translation from lower-bound, upper-bound, step-size to trip-count.
///     ```c
///     for (int i = 3; i < 42; i+=2) {
///       B[i] = A[i];
///     }
///     ```
/// 
///     ```mlir
///     %lb = arith.constant 3 : i32
///     %ub = arith.constant 42 : i32
///     %step = arith.constant 2 : i32
///     %range = arith.sub %ub, %lb : i32
///     %tripcount = arith.div %range, %step : i32
///     omp.canonical_loop %iv : i32 in range(%tripcount) {
///       %offset = arith.mul %iv, %step : i32
///       %i = arith.add %offset, %lb : i32
///       %a = load %arrA[%i] : memref<?xf32>
///       store %a, %arrB[%i] : memref<?xf32>
///     }
///     ```
/// 
///     Nested canonical loop with transformation of the inner loop.
///     ```mlir
///     %outer = omp.new_cli : !omp.cli
///     %inner = omp.new_cli : !omp.cli
///     omp.canonical_loop(%outer) %iv1 : i32 in range(%tc1) {
///       omp.canonical_loop(%inner) %iv2 : i32 in range(%tc2) {
///         %a = load %arrA[%iv1, %iv2] : memref<?x?xf32>
///         store %a, %arrB[%iv1, %iv2] : memref<?x?xf32>
///       }
///     }
///     omp.unroll_full(%inner)
///     ```
class CanonicalLoopOp;

} // namespace mlir::omp
namespace mlir::omp {

/// declares a named critical section.
/// Declares a named critical section.
///   
///     The `sym_name` can be used in `omp.critical` constructs in the dialect.
///   
///     `hint` is the value of hint (as specified in the hint clause). It is a
///     compile time constant. As the name suggests, this is just a hint for
///     optimization.
class CriticalDeclareOp;

} // namespace mlir::omp
namespace mlir::omp {

/// critical construct
/// The critical construct imposes a restriction on the associated structured
///     block (region) to be executed by only a single thread at a time.
/// 
///     The optional `name` argument of critical constructs is used to identify
///     them. Unnamed critical constructs behave as though an identical name was
///     specified.
class CriticalOp;

} // namespace mlir::omp
namespace mlir::omp {

/// declare mapper info
/// This Op is used to capture the map information related to it's
///     parent DeclareMapperOp.
///   
///     The optional `map_vars` maps data from the current task's data environment
///     to the device data environment.
class DeclareMapperInfoOp;

} // namespace mlir::omp
namespace mlir::omp {

/// declare mapper directive
/// The declare mapper directive declares a user-defined mapper for a given
///     type, and defines a mapper-identifier that can be used in a map clause.
class DeclareMapperOp;

} // namespace mlir::omp
namespace mlir::omp {

/// declares a reduction kind
/// Declares an OpenMP reduction kind. This requires two mandatory and four
///     optional regions.
/// 
///       1. The optional alloc region specifies how to allocate the thread-local
///          reduction value. This region should not contain control flow and all
///          IR should be suitable for inlining straight into an entry block. In
///          the common case this is expected to contain only allocas. It is
///          expected to `omp.yield` the allocated value on all control paths.
///          If allocation is conditional (e.g. only allocate if the mold is
///          allocated), this should be done in the initilizer region and this
///          region not included. The alloc region is not used for by-value
///          reductions (where allocation is implicit).
///       2. The initializer region specifies how to initialize the thread-local
///          reduction value. This is usually the neutral element of the reduction.
///          For convenience, the region has an argument that contains the value
///          of the reduction accumulator at the start of the reduction. If an alloc
///          region is specified, there is a second block argument containing the
///          address of the allocated memory. The initializer region is expected to
///          `omp.yield` the new value on all control flow paths.
///       3. The reduction region specifies how to combine two values into one, i.e.
///          the reduction operator. It accepts the two values as arguments and is
///          expected to `omp.yield` the combined value on all control flow paths.
///       4. The atomic reduction region is optional and specifies how two values
///          can be combined atomically given local accumulator variables. It is
///          expected to store the combined value in the first accumulator variable.
///       5. The cleanup region is optional and specifies how to clean up any memory
///          allocated by the initializer region. The region has an argument that
///          contains the value of the thread-local reduction accumulator. This will
///          be executed after the reduction has completed.
///       6. The DataPtrPtr region specifies how to access the base address of a
///          descriptor. This is used, in particular, for GPU reductions in order
///          know where partial reduction results are stored in remote lanes.
/// 
///     Note that the MLIR type system does not allow for type-polymorphic
///     reductions. Separate reduction declarations should be created for different
///     element and accumulator types.
/// 
///     For initializer and reduction regions, the operand to `omp.yield` must
///     match the parent operation's results.
/// 
///     * `$byref_element_type`: For by-ref reductions, we want to keep track of the
///       boxed/allocated type.  For example, for a `real, allocatable` variable, 
///       `real` should be stored in this attribute.
class DeclareReductionOp;

} // namespace mlir::omp
namespace mlir::omp {

/// declare simd directive
/// "omp.declare_simd" models the OpenMP `declare simd` directive.
/// 
///     This is a declarative operation (no region) intended to appear inside
///     a function body. It attaches clauses of declare simd to the enclosing
///     function.
/// 
///     Example:
///     ```mlir
///     func.func @add(%a: memref<16xi32>) {
///       omp.declare_simd simdlen(8) aligned(%a : memref<16xi32> -> 64 : i64)
///       ...
///     }
///     ```
///   
///     The `alignments` attribute additionally specifies alignment of each
///     corresponding aligned operand. Note that `aligned_vars` and `alignments`
///     must contain the same number of elements.
///   
///     The `inbranch` clause indicates that the generated SIMD function variant
///     is intended for use in conditional branches.
///   
///     The `linear_step_vars` operand additionally specifies the step for each
///     associated linear operand. Note that the `linear_vars` and
///     `linear_step_vars` variadic lists should contain the same number of
///     elements.
///   
///     The `notinbranch` clause indicates that the generated SIMD function variant
///     is intended for use when not in conditional branches.
///   
///     When a `simdlen` clause is present, the preferred number of iterations to be
///     executed concurrently is the value provided to the `simdlen` clause.
///   
///     The `uniform` clause declares one or more arguments to have an invariant
///     value for all concurrent invocations of the function in the execution of
///     a single SIMD loop.
class DeclareSimdOp;

} // namespace mlir::omp
namespace mlir::omp {

/// distribute construct
/// The distribute construct specifies that the iterations of one or more loops
///     (optionally specified using collapse clause) will be executed by the
///     initial teams in the context of their implicit tasks. The loops that the
///     distribute op is associated with starts with the outermost loop enclosed by
///     the distribute op region and going down the loop nest toward the innermost
///     loop. The iterations are distributed across the initial threads of all
///     initial teams that execute the teams region to which the distribute region
///     binds.
/// 
///     The distribute loop construct specifies that the iterations of the loop(s)
///     will be executed in parallel by threads in the current context. These
///     iterations are spread across threads that already exist in the enclosing
///     region.
/// 
///     The body region can only contain a single block which must contain a single
///     operation. This operation must be another compatible loop wrapper or an
///     `omp.loop_nest`.
/// 
///     ```mlir
///     omp.distribute <clauses> {
///       omp.loop_nest (%i1, %i2) : index = (%c0, %c0) to (%c10, %c10) step (%c1, %c1) {
///         %a = load %arrA[%i1, %i2] : memref<?x?xf32>
///         %b = load %arrB[%i1, %i2] : memref<?x?xf32>
///         %sum = arith.addf %a, %b : f32
///         store %sum, %arrC[%i1, %i2] : memref<?x?xf32>
///         omp.yield
///       }
///     }
///     ```
///   
///     The `allocator_vars` and `allocate_vars` parameters are a variadic list of
///     values that specify the memory allocator to be used to obtain storage for
///     private values.
///   
///     The `dist_schedule_static` attribute specifies the schedule for this loop,
///     determining how the loop is distributed across the various teams. The
///     optional `dist_schedule_chunk_size` associated with this determines further
///     controls this distribution.
///   
///     The optional `order` attribute specifies which order the iterations of the
///     associated loops are executed in. Currently the only option for this
///     attribute is "concurrent".
class DistributeOp;

} // namespace mlir::omp
namespace mlir::omp {

/// flush construct
/// The flush construct executes the OpenMP flush operation. This operation
///     makes a thread's temporary view of memory consistent with memory and
///     enforces an order on the memory operations of the variables explicitly
///     specified or implied.
class FlushOp;

} // namespace mlir::omp
namespace mlir::omp {

/// rectangular loop nest
/// This operation represents a rectangular loop nest which may be collapsed
///     and/or tiled. For each rectangular loop of the nest represented by an
///     instance of this operation, lower and upper bounds, as well as a step
///     variable, must be defined. The collapse clause specifies how many loops
///     that should be collapsed (1 if no collapse is done) after any tiling is
///     performed. The tiling sizes is represented by the tile sizes clause.
/// 
///     The lower and upper bounds specify a half-open range: the range includes the
///     lower bound but does not include the upper bound. If the `loop_inclusive`
///     attribute is specified then the upper bound is also included.
/// 
///     The body region can contain any number of blocks. The region is terminated
///     by an `omp.yield` instruction without operands. The induction variables,
///     represented as entry block arguments to the loop nest operation's single
///     region, match the types of the `loop_lower_bounds`, `loop_upper_bounds` and
///     `loop_steps` arguments.
/// 
///     ```mlir
///     omp.loop_nest (%i1, %i2) : i32 = (%c0, %c0) to (%c10, %c10) step (%c1, %c1) collapse(2) tiles(5,5) {
///       %a = load %arrA[%i1, %i2] : memref<?x?xf32>
///       %b = load %arrB[%i1, %i2] : memref<?x?xf32>
///       %sum = arith.addf %a, %b : f32
///       store %sum, %arrC[%i1, %i2] : memref<?x?xf32>
///       omp.yield
///     }
///     ```
/// 
///     This is a temporary simplified definition of a loop based on existing OpenMP
///     loop operations intended to serve as a stopgap solution until the long-term
///     representation of canonical loops is defined. Specifically, this operation
///     is intended to serve as a unique source for loop information during the
///     transition to making `omp.distribute`, `omp.simd`, `omp.taskloop` and
///     `omp.wsloop` wrapper operations. It is not intended to help with the
///     addition of support for loop transformations, non-rectangular loops and
///     non-perfectly nested loops.
class LoopNestOp;

} // namespace mlir::omp
namespace mlir::omp {

/// loop construct
/// A loop construct specifies that the logical iterations of the associated loops
///     may execute concurrently and permits the encountering threads to execute the
///     loop accordingly. A loop construct can have 3 different types of binding:
///       1. teams: in which case the binding region is the innermost enclosing `teams`
///          region.
///       2. parallel: in which case the binding region is the innermost enclosing `parallel`
///          region.
///       3. thread: in which case the binding region is not defined.
/// 
///     The body region can only contain a single block which must contain a single
///     operation, this operation must be an `omp.loop_nest`.
/// 
///     ```
///     omp.loop <clauses> {
///       omp.loop_nest (%i1, %i2) : index = (%c0, %c0) to (%c10, %c10) step (%c1, %c1) {
///         %a = load %arrA[%i1, %i2] : memref<?x?xf32>
///         %b = load %arrB[%i1, %i2] : memref<?x?xf32>
///         %sum = arith.addf %a, %b : f32
///         store %sum, %arrC[%i1, %i2] : memref<?x?xf32>
///         omp.yield
///       }
///     }
///     ```
///   
///     The `bind` clause specifies the binding region of the construct on which it
///     appears.
///   
///     The optional `order` attribute specifies which order the iterations of the
///     associated loops are executed in. Currently the only option for this
///     attribute is "concurrent".
///   
///     Reductions can be performed by specifying the reduction modifer
///     (`default`, `inscan` or `task`) in `reduction_mod`, reduction accumulator
///     variables in `reduction_vars`, symbols referring to reduction declarations
///     in the `reduction_syms` attribute, and whether the reduction variable
///     should be passed into the reduction region by value or by reference in
///     `reduction_byref`. Each reduction is identified by the accumulator it uses
///     and accumulators must not be repeated in the same reduction. A private
///     variable corresponding to the accumulator is used in place of the
///     accumulator inside the body of the operation. The reduction declaration
///     specifies how to combine the values from each iteration, section, team,
///     thread or simd lane defined by the operation's region into the final value,
///     which is available in the accumulator after they all complete.
class LoopOp;

} // namespace mlir::omp
namespace mlir::omp {

/// Represents normalized bounds information for map clauses.
/// This operation is a variation on the OpenACC dialects DataBoundsOp. Within
///     the OpenMP dialect it stores the bounds/range of data to be mapped to a
///     device specified by map clauses on target directives. Within
///     the OpenMP dialect, the MapBoundsOp is associated with MapInfoOp,
///     helping to store bounds information for the mapped variable.
/// 
///     It is used to support OpenMP array sectioning, Fortran pointer and
///     allocatable mapping and pointer/allocatable member of derived types.
///     In all cases the MapBoundsOp holds information on the section of
///     data to be mapped. Such as the upper bound and lower bound of the
///     section of data to be mapped. This information is currently
///     utilised by the LLVM-IR lowering to help generate instructions to
///     copy data to and from the device when processing target operations.
/// 
///     The example below copys a section of a 10-element array; all except the
///     first element, utilising OpenMP array sectioning syntax where array
///     subscripts are provided to specify the bounds to be mapped to device.
///     To simplify the examples, the constants are used directly, in reality
///     they will be MLIR SSA values.
/// 
///     C++:
///     ```
///     int array[10];
///     #pragma target map(array[1:9])
///     ```
///     =>
///     ```mlir
///     omp.map.bounds lower_bound(1) upper_bound(9) extent(9) start_idx(0)
///     ```
/// 
///     Fortran:
///     ```
///     integer :: array(1:10)
///     !$target map(array(2:10))
///     ```
///     =>
///     ```mlir
///     omp.map.bounds lower_bound(1) upper_bound(9) extent(9) start_idx(1)
///     ```
/// 
///     For Fortran pointers and allocatables (as well as those that are
///     members of derived types) the bounds information is provided by
///     the Fortran compiler and runtime through descriptor information.
/// 
///     A basic pointer example can be found below (constants again
///     provided for simplicity, where in reality SSA values will be
///     used, in this case that point to data yielded by Fortran's
///     descriptors):
/// 
///     Fortran:
///     ```
///     integer, pointer :: ptr(:)
///     allocate(ptr(10))
///     !$target map(ptr)
///     ```
///     =>
///     ```mlir
///     omp.map.bounds lower_bound(0) upper_bound(9) extent(10) start_idx(1)
///     ```
/// 
///     This operation records the bounds information in a normalized fashion
///     (zero-based). This works well with the `PointerLikeType`
///     requirement in data clauses - since a `lower_bound` of 0 means looking
///     at data at the zero offset from pointer.
/// 
///     This operation must have an `upper_bound` or `extent` (or both are allowed -
///     but not checked for consistency). When the source language's arrays are
///     not zero-based, the `start_idx` must specify the zero-position index.
class MapBoundsOp;

} // namespace mlir::omp
namespace mlir::omp {

/// The MapInfoOp captures information relating to individual OpenMP map clauses
///     that are applied to certain OpenMP directives such as Target and Target Data.
/// 
///     For example, the map type modifier; such as from, tofrom and to, the variable
///     being captured or the bounds of an array section being mapped.
/// 
///     It can be used to capture both implicit and explicit map information, where
///     explicit is an argument directly specified to an OpenMP map clause or implicit
///     where a variable is utilised in a target region but is defined externally to
///     the target region.
/// 
///     This map information is later used to aid the lowering of the target operations
///     they are attached to providing argument input and output context for kernels
///     generated or the target data mapping environment.
/// 
///     Example (Fortran):
/// 
///     ```
///     integer :: index
///     !$target map(to: index)
///     ```
///     =>
///     ```mlir
///     omp.map.info var_ptr(%index_ssa) map_type(to) map_capture_type(ByRef)
///       name(index)
///     ```
/// 
///     Description of arguments:
///     - `var_ptr`: The address of variable to copy.
///     - `var_type`: The type of the variable to copy.
///     - 'map_type': OpenMP map type for this map capture, for example: from, to and
///        always. It's a bitfield composed of the OpenMP runtime flags stored in
///        OpenMPOffloadMappingFlags.
///     - 'map_capture_type': Capture type for the variable e.g. this, byref, byvalue, byvla
///        this can affect how the variable is lowered.
///     - `var_ptr_ptr`: Used when the variable copied is a member of a class, structure
///       or derived type and refers to the originating struct.
///     - `members`: Used to indicate mapped child members for the current MapInfoOp,
///        represented as other MapInfoOp's, utilised in cases where a parent structure
///        type and members of the structure type are being mapped at the same time.
///        For example: map(to: parent, parent->member, parent->member2[:10])
///     - `members_index`: Used to indicate the ordering of members within the containing
///        parent (generally a record type such as a structure, class or derived type),
///        e.g. struct {int x, float y, double z}, x would be 0, y would be 1, and z
///        would be 2. This aids the mapping.
///     - `bounds`: Used when copying slices of array's, pointers or pointer members of
///        objects (e.g. derived types or classes), indicates the bounds to be copied
///        of the variable. When it's an array slice it is in rank order where rank 0
///        is the inner-most dimension.
///     - 'mapper_id': OpenMP mapper map type modifier for this map capture. It's used to
///        specify a user defined mapper to be used for mapping.
///     - `name`: Holds the name of variable as specified in user clause (including bounds).
///     - `partial_map`: The record type being mapped will not be mapped in its entirety,
///        it may be used however, in a mapping to bind it's mapped components together.
class MapInfoOp;

} // namespace mlir::omp
namespace mlir::omp {

/// masked construct
/// Masked construct allows to specify a structured block to be executed by a subset of
///     threads of the current team.
///   
///     If `filter` is specified, the masked construct masks the execution of
///     the region to only the thread id filtered. Other threads executing the
///     parallel region are not expected to execute the region specified within
///     the `masked` directive. If `filter` is not specified, master thread is
///     expected to execute the region enclosed within `masked` directive.
class MaskedOp;

} // namespace mlir::omp
namespace mlir::omp {

/// master construct
/// The master construct specifies a structured block that is executed by
///     the master thread of the team.
class MasterOp;

} // namespace mlir::omp
namespace mlir::omp {

/// Create a new Canonical Loop Info value.
/// Create a new CLI that can be passed as an argument to a CanonicalLoopOp
///     and to loop transformation operations to handle dependencies between
///     loop transformation operations.
class NewCliOp;

} // namespace mlir::omp
namespace mlir::omp {

/// ordered construct without region
/// The ordered construct without region is a stand-alone directive that
///     specifies cross-iteration dependencies in a doacross loop nest.
///   
///     The `doacross_depend_type` attribute refers to either the DEPEND(SOURCE)
///     clause or the DEPEND(SINK: vec) clause.
/// 
///     The `doacross_num_loops` attribute specifies the number of loops in the
///     doacross nest.
/// 
///     The `doacross_depend_vars` is a variadic list of operands that specifies the
///     index of the loop iterator in the doacross nest for the DEPEND(SOURCE)
///     clause or the index of the element of "vec" for the DEPEND(SINK: vec)
///     clause. It contains the operands in multiple "vec" when multiple
///     DEPEND(SINK: vec) clauses exist in one ORDERED directive.
class OrderedOp;

} // namespace mlir::omp
namespace mlir::omp {

/// ordered construct with region
/// The ordered construct with region specifies a structured block in a
///     worksharing-loop, SIMD, or worksharing-loop SIMD region that is executed in
///     the order of the loop iterations.
///   
///     The `par_level_simd` attribute corresponds to the simd clause specified. If
///     it is not present, it behaves as if the threads clause is specified or no
///     clause is specified.
class OrderedRegionOp;

} // namespace mlir::omp
namespace mlir::omp {

/// parallel construct
/// The parallel construct includes a region of code which is to be executed
///     by a team of threads.
/// 
///     The optional `if_expr` parameter specifies a boolean result of a conditional
///     check. If this value is 1 or is not provided then the parallel region runs
///     as normal, if it is 0 then the parallel region is executed with one thread.
///   
///     The `allocator_vars` and `allocate_vars` parameters are a variadic list of
///     values that specify the memory allocator to be used to obtain storage for
///     private values.
///   
///     The `num_threads` clause specifies the number of threads.
/// 
///     Multi-dimensional format (dims modifier):
///     - Multiple values can be specified for multi-dimensional thread counts.
///     - The number of dimensions is derived from the number of values.
///     - Values can have different integer types.
///     - Format: `num_threads(%v1, %v2, ... : type1, type2, ...)`
///     - Example: `num_threads(%n, %m : i32, i64)`
/// 
///     Single value format:
///     - A single value specifies the number of threads.
///     - Format: `num_threads(%value : type)`
///     - Example: `num_threads(%n : i32)`
///   
///     The optional `proc_bind_kind` attribute controls the thread affinity for the
///     execution of the parallel region.
///   
///     Reductions can be performed by specifying the reduction modifer
///     (`default`, `inscan` or `task`) in `reduction_mod`, reduction accumulator
///     variables in `reduction_vars`, symbols referring to reduction declarations
///     in the `reduction_syms` attribute, and whether the reduction variable
///     should be passed into the reduction region by value or by reference in
///     `reduction_byref`. Each reduction is identified by the accumulator it uses
///     and accumulators must not be repeated in the same reduction. A private
///     variable corresponding to the accumulator is used in place of the
///     accumulator inside the body of the operation. The reduction declaration
///     specifies how to combine the values from each iteration, section, team,
///     thread or simd lane defined by the operation's region into the final value,
///     which is available in the accumulator after they all complete.
class ParallelOp;

} // namespace mlir::omp
namespace mlir::omp {

/// Provides declaration of [first]private logic.
/// This operation provides a declaration of how to implement the
///     [first]privatization of a variable. The dialect users should provide
///     which type should be allocated for this variable. The allocated (usually by
///     alloca) variable is passed to the initialization region which does everything
///     else (e.g. initialization of Fortran runtime descriptors). Information about
///     how to initialize the copy from the original item should be given in the
///     copy region, and if needed, how to deallocate memory (allocated by the
///     initialization region) in the dealloc region.
/// 
///     Examples:
/// 
///     * `private(x)` would not need any regions because no initialization is
///       required by the standard for i32 variables and this is not firstprivate.
///     ```mlir
///     omp.private {type = private} @x.privatizer : i32
///     ```
/// 
///     * `firstprivate(x)` would be emitted as:
///     ```mlir
///     omp.private {type = firstprivate} @x.privatizer : i32 copy {
///     ^bb0(%arg0: !fir.ref<i32>, %arg1: !fir.ref<i32>):
///     // %arg0 is the original host variable.
///     // %arg1 represents the memory allocated for this private variable.
///     ... copy from host to the privatized clone ....
///     omp.yield(%arg1 : !fir.ref<i32>)
///     }
///     ```
/// 
///     * `private(x)` for "allocatables" would be emitted as:
///     ```mlir
///     omp.private {type = private} @x.privatizer : !some.type init {
///     ^bb0(%arg0: !some.pointer<!some.type>, %arg1: !some.pointer<!some.type>):
///     // initialize %arg1, using %arg0 as a mold for allocations.
///     // For example if %arg0 is a heap allocated array with a runtime determined
///     // length and !some.type is a runtime type descriptor, the init region
///     // will read the array length from %arg0, and heap allocate an array of the
///     // right length and initialize %arg1 to contain the array allocation and
///     // length.
///     omp.yield(%arg1 : !some.pointer<!some.type>)
///     } dealloc {
///     ^bb0(%arg0: !some.pointer<!some.type>):
///     // ... deallocate memory allocated by the init region...
///     // In the example above, this will free the heap allocated array data.
///     omp.yield
///     }
///     ```
/// 
///     There are no restrictions on the body except for:
///     - The `dealloc` regions has a single argument.
///     - The `init` & `copy` regions have 2 arguments.
///     - All three regions are terminated by `omp.yield` ops.
///     The above restrictions and other obvious restrictions (e.g. verifying the
///     type of yielded values) are verified by the custom op verifier. The actual
///     contents of the blocks inside all regions are not verified.
/// 
///     Instances of this op would then be used by ops that model directives that
///     accept data-sharing attribute clauses.
/// 
///     The `sym_name` attribute provides a symbol by which the privatizer op can be
///     referenced by other dialect ops.
/// 
///     The `type` attribute is the type of the value being privatized. This type
///     will be implicitly allocated in MLIR->LLVMIR conversion and passed as the
///     second argument to the init region. Therefore the type of arguments to
///     the regions should be a type which represents a pointer to `type`.
/// 
///     The `data_sharing_type` attribute specifies whether privatizer corresponds
///     to a `private` or a `firstprivate` clause.
class PrivateClauseOp;

} // namespace mlir::omp
namespace mlir::omp {

/// scan directive
/// The scan directive allows to specify scan reductions. It should be
///     enclosed within a parent directive along with which a reduction clause
///     with `inscan` modifier must be specified. The scan directive allows to
///     split code blocks into input phase and scan phase in the region
///     enclosed by the parent.
///   
///     The inclusive clause is used on a separating directive that separates a
///     structured block into two structured block sequences. If it is specified,
///     the input phase includes the preceding structured block sequence and the
///     scan phase includes the following structured block sequence.
/// 
///     The `inclusive_vars` is a variadic list of operands that specifies the
///     scan-reduction accumulator symbols.
///   
///     The exclusive clause is used on a separating directive that separates a
///     structured block into two structured block sequences. If it
///     is specified, the input phase excludes the preceding structured block 
///     sequence and instead includes the following structured block sequence, 
///     while the scan phase includes the preceding structured block sequence.
/// 
///     The `exclusive_vars` is a variadic list of operands that specifies the
///     scan-reduction accumulator symbols.
class ScanOp;

} // namespace mlir::omp
namespace mlir::omp {

/// section directive
/// A section operation encloses a region which represents one section in a
///     sections construct. A section op should always be surrounded by an
///     `omp.sections` operation. The section operation may have block args
///     which corespond to the block arguments of the surrounding `omp.sections`
///     operation. This is done to reflect situations where these block arguments
///     represent variables private to each section.
class SectionOp;

} // namespace mlir::omp
namespace mlir::omp {

/// sections construct
/// The sections construct is a non-iterative worksharing construct that
///     contains `omp.section` operations. The `omp.section` operations are to be
///     distributed among and executed by the threads in a team. Each `omp.section`
///     is executed once by one of the threads in the team in the context of its
///     implicit task.
///     Block arguments for reduction variables should be mirrored in enclosed
///     `omp.section` operations.
///   
///     The `allocator_vars` and `allocate_vars` parameters are a variadic list of
///     values that specify the memory allocator to be used to obtain storage for
///     private values.
///   
///     The optional `nowait` attribute, when present, eliminates the implicit
///     barrier at the end of the construct, so the parent operation can make
///     progress even if the child operation has not completed yet.
///   
///     Reductions can be performed by specifying the reduction modifer
///     (`default`, `inscan` or `task`) in `reduction_mod`, reduction accumulator
///     variables in `reduction_vars`, symbols referring to reduction declarations
///     in the `reduction_syms` attribute, and whether the reduction variable
///     should be passed into the reduction region by value or by reference in
///     `reduction_byref`. Each reduction is identified by the accumulator it uses
///     and accumulators must not be repeated in the same reduction. A private
///     variable corresponding to the accumulator is used in place of the
///     accumulator inside the body of the operation. The reduction declaration
///     specifies how to combine the values from each iteration, section, team,
///     thread or simd lane defined by the operation's region into the final value,
///     which is available in the accumulator after they all complete.
class SectionsOp;

} // namespace mlir::omp
namespace mlir::omp {

/// simd construct
/// The simd construct can be applied to a loop to indicate that the loop can be
///     transformed into a SIMD loop (that is, multiple iterations of the loop can
///     be executed concurrently using SIMD instructions).
/// 
///     The body region can only contain a single block which must contain a single
///     operation. This operation must be another compatible loop wrapper or an
///     `omp.loop_nest`.
/// 
///     ```
///     omp.simd <clauses> {
///       omp.loop_nest (%i1, %i2) : index = (%c0, %c0) to (%c10, %c10) step (%c1, %c1) {
///         %a = load %arrA[%i1, %i2] : memref<?x?xf32>
///         %b = load %arrB[%i1, %i2] : memref<?x?xf32>
///         %sum = arith.addf %a, %b : f32
///         store %sum, %arrC[%i1, %i2] : memref<?x?xf32>
///         omp.yield
///       }
///     }
///     ```
/// 
///     When an if clause is present and evaluates to false, the preferred number of
///     iterations to be executed concurrently is one, regardless of whether
///     a simdlen clause is specified.
///   
///     The `alignments` attribute additionally specifies alignment of each
///     corresponding aligned operand. Note that `aligned_vars` and `alignments`
///     must contain the same number of elements.
///   
///     The `linear_step_vars` operand additionally specifies the step for each
///     associated linear operand. Note that the `linear_vars` and
///     `linear_step_vars` variadic lists should contain the same number of
///     elements.
///   
///     The optional `nontemporal` attribute specifies variables which have low
///     temporal locality across the iterations where they are accessed.
///   
///     The optional `order` attribute specifies which order the iterations of the
///     associated loops are executed in. Currently the only option for this
///     attribute is "concurrent".
///   
///     Reductions can be performed by specifying the reduction modifer
///     (`default`, `inscan` or `task`) in `reduction_mod`, reduction accumulator
///     variables in `reduction_vars`, symbols referring to reduction declarations
///     in the `reduction_syms` attribute, and whether the reduction variable
///     should be passed into the reduction region by value or by reference in
///     `reduction_byref`. Each reduction is identified by the accumulator it uses
///     and accumulators must not be repeated in the same reduction. A private
///     variable corresponding to the accumulator is used in place of the
///     accumulator inside the body of the operation. The reduction declaration
///     specifies how to combine the values from each iteration, section, team,
///     thread or simd lane defined by the operation's region into the final value,
///     which is available in the accumulator after they all complete.
///   
///     The `safelen` clause specifies that no two concurrent iterations within a
///     SIMD chunk can have a distance in the logical iteration space that is
///     greater than or equal to the value given in the clause.
///   
///     When a `simdlen` clause is present, the preferred number of iterations to be
///     executed concurrently is the value provided to the `simdlen` clause.
class SimdOp;

} // namespace mlir::omp
namespace mlir::omp {

/// single directive
/// The single construct specifies that the associated structured block is
///     executed by only one of the threads in the team (not necessarily the
///     master thread), in the context of its implicit task. The other threads
///     in the team, which do not execute the block, wait at an implicit barrier
///     at the end of the single construct.
///   
///     The `allocator_vars` and `allocate_vars` parameters are a variadic list of
///     values that specify the memory allocator to be used to obtain storage for
///     private values.
///   
///     If `copyprivate` variables and functions are specified, then each thread
///     variable is updated with the variable value of the thread that executed
///     the single region, using the specified copy functions.
///   
///     The optional `nowait` attribute, when present, eliminates the implicit
///     barrier at the end of the construct, so the parent operation can make
///     progress even if the child operation has not completed yet.
class SingleOp;

} // namespace mlir::omp
namespace mlir::omp {

/// allocate storage on an openmp device for an object of a given type
/// Allocates memory on the specified OpenMP device for an object of the given type.
///     Returns an integer value representing the device pointer to the allocated memory.
///     The memory is uninitialized after allocation. Operations must be paired with 
///     `omp.target_freemem` to avoid memory leaks.
/// 
///     * `$device`: The integer ID of the OpenMP device where the memory will be allocated.
///     * `$in_type`: The type of the object for which memory is being allocated. 
///       For arrays, this can be a static or dynamic array type.
///     * `$uniq_name`: An optional unique name for the allocated memory.
///     * `$bindc_name`: An optional name used for C interoperability.
///     * `$typeparams`: Runtime type parameters for polymorphic or parameterized types. 
///       These are typically integer values that define aspects of a type not fixed at compile time.
///     * `$shape`: Runtime shape operands for dynamic arrays. 
///       Each operand is an integer value representing the extent of a specific dimension. 
/// 
///   ```mlir
///     // Allocate a static 3x3 integer vector on device 0
///     %device_0 = arith.constant 0 : i32
///     %ptr_static = omp.target_allocmem %device_0 : i32, vector<3x3xi32>
///     // ... use %ptr_static ...
///     omp.target_freemem %device_0, %ptr_static : i32, i64
/// 
///     // Allocate a dynamic 2D Fortran array (fir.array) on device 1
///     %device_1 = arith.constant 1 : i32
///     %rows = arith.constant 10 : index
///     %cols = arith.constant 20 : index
///     %ptr_dynamic = omp.target_allocmem %device_1 : i32, !fir.array<?x?xf32>, %rows, %cols : index, index
///     // ... use %ptr_dynamic ...
///     omp.target_freemem %device_1, %ptr_dynamic : i32, i64
///   ```
class TargetAllocMemOp;

} // namespace mlir::omp
namespace mlir::omp {

/// target data construct
/// Map variables to a device data environment for the extent of the region.
/// 
///     The omp target data directive maps variables to a device data
///     environment, and defines the lexical scope of the data environment
///     that is created. The omp target data directive can reduce data copies
///     to and from the offloading device when multiple target regions are using
///     the same data.
/// 
///     The optional `if_expr` parameter specifies a boolean result of a conditional
///     check. If this value is 1 or is not provided then the target region runs on
///     a device, if it is 0 then the target region is executed on the host device.
///   
///     The optional `device` parameter specifies the device number for the target
///     region.
///   
///     The optional `map_vars` maps data from the current task's data environment
///     to the device data environment.
///   
///     The optional `use_device_addr_vars` specifies the address of the objects in
///     the device data environment.
///   
///     The optional `use_device_ptr_vars` specifies the device pointers to the
///     corresponding list items in the device data environment.
class TargetDataOp;

} // namespace mlir::omp
namespace mlir::omp {

/// target enter data construct
/// The target enter data directive specifies that variables are mapped to
///     a device data environment. The target enter data directive is a
///     stand-alone directive.
/// 
///     The optional `if_expr` parameter specifies a boolean result of a conditional
///     check. If this value is 1 or is not provided then the target region runs on
///     a device, if it is 0 then the target region is executed on the host device.
///   
///     The `depend_kinds` and `depend_vars` arguments are variadic lists of values
///     that specify the dependencies of this particular task in relation to other
///     tasks.
///   
///     The optional `device` parameter specifies the device number for the target
///     region.
///   
///     The optional `map_vars` maps data from the current task's data environment
///     to the device data environment.
///   
///     The optional `nowait` attribute, when present, eliminates the implicit
///     barrier at the end of the construct, so the parent operation can make
///     progress even if the child operation has not completed yet.
class TargetEnterDataOp;

} // namespace mlir::omp
namespace mlir::omp {

/// target exit data construct
/// The target exit data directive specifies that variables are mapped to a
///     device data environment. The target exit data directive is
///     a stand-alone directive.
/// 
///     The optional `if_expr` parameter specifies a boolean result of a conditional
///     check. If this value is 1 or is not provided then the target region runs on
///     a device, if it is 0 then the target region is executed on the host device.
///   
///     The `depend_kinds` and `depend_vars` arguments are variadic lists of values
///     that specify the dependencies of this particular task in relation to other
///     tasks.
///   
///     The optional `device` parameter specifies the device number for the target
///     region.
///   
///     The optional `map_vars` maps data from the current task's data environment
///     to the device data environment.
///   
///     The optional `nowait` attribute, when present, eliminates the implicit
///     barrier at the end of the construct, so the parent operation can make
///     progress even if the child operation has not completed yet.
class TargetExitDataOp;

} // namespace mlir::omp
namespace mlir::omp {

/// free memory on an openmp device
/// Deallocates memory on the specified OpenMP device that was previously
///     allocated by an `omp.target_allocmem` operation. After this operation, the
///     deallocated memory is in an undefined state and should not be accessed.
///     It is crucial to ensure that all accesses to the memory region are completed
///     before `omp.target_freemem` is called to avoid undefined behavior.
/// 
///     * `$device`: The integer ID of the OpenMP device from which the memory will be freed.
///     * `$heapref`: The integer value representing the device pointer to the memory
///       to be deallocated, which was previously returned by `omp.target_allocmem`.
/// 
///     ```mlir
///       // Example of allocating and freeing memory on an OpenMP device
///       %device_id = arith.constant 0 : i32
///       %allocated_ptr = omp.target_allocmem %device_id : i32, vector<3x3xi32>
///       // ... operations using %allocated_ptr on the device ...
///       omp.target_freemem %device_id, %allocated_ptr : i32, i64
///     ```
class TargetFreeMemOp;

} // namespace mlir::omp
namespace mlir::omp {

/// target construct
/// The target construct includes a region of code which is to be executed
///     on a device.
/// 
///     The optional `if_expr` parameter specifies a boolean result of a conditional
///     check. If this value is 1 or is not provided then the target region runs on
///     a device, if it is 0 then the target region is executed on the host device.
/// 
///     The `private_maps` attribute connects `private` operands to their corresponding
///     `map` operands. For `private` operands that require a map, the value of the
///     corresponding element in the attribute is the index of the `map` operand
///     (relative to other `map` operands not the whole operands of the operation). For
///     `private` opernads that do not require a map, this value is -1 (which is omitted
///     from the assembly foramt printing).
///   
///     The `allocator_vars` and `allocate_vars` parameters are a variadic list of
///     values that specify the memory allocator to be used to obtain storage for
///     private values.
///   
///     `ompx_bare` allows `omp target teams` to be executed on a GPU with an
///     explicit number of teams and threads. This clause also allows the teams and
///     threads sizes to have up to 3 dimensions.
///   
///     The `depend_kinds` and `depend_vars` arguments are variadic lists of values
///     that specify the dependencies of this particular task in relation to other
///     tasks.
///   
///     The optional `device` parameter specifies the device number for the target
///     region.
///   
///     The optional `has_device_addr_vars` indicates that list items already have
///     device addresses, so they may be directly accessed from the target device.
///     This includes array sections.
///   
///     The optional `host_eval_vars` holds values defined outside of the region of
///     the `IsolatedFromAbove` operation for which a corresponding entry block
///     argument is defined. The only legal uses for these captured values are the
///     following:
///       - `num_teams` or `thread_limit` clause of an immediately nested
///       `omp.teams` operation.
///       - If the operation is the top-level `omp.target` of a target SPMD kernel:
///         - `num_threads` clause of the nested `omp.parallel` operation.
///         - Bounds and steps of the nested `omp.loop_nest` operation.
///   
///     The optional `is_device_ptr_vars` indicates list items are device pointers.
///   
///     The optional `map_vars` maps data from the current task's data environment
///     to the device data environment.
///   
///     The optional `nowait` attribute, when present, eliminates the implicit
///     barrier at the end of the construct, so the parent operation can make
///     progress even if the child operation has not completed yet.
///   
///     The `thread_limit` clause specifies the limit on the number of threads.
/// 
///     Multi-dimensional format (dims modifier):
///     - Multiple values can be specified for multi-dimensional thread limits.
///     - The number of dimensions is derived from the number of values.
///     - Values can have different integer types.
///     - Format: `thread_limit(%v1, %v2, ... : type1, type2, ...)`
///     - Example: `thread_limit(%n, %m : i32, i64)`
/// 
///     Single value format:
///     - A single value specifies the thread limit.
///     - Format: `thread_limit(%value : type)`
///     - Example: `thread_limit(%n : i32)`
class TargetOp;

} // namespace mlir::omp
namespace mlir::omp {

/// target update construct
/// The target update directive makes the corresponding list items in the device
///     data environment consistent with their original list items, according to the
///     specified motion clauses. The target update construct is a stand-alone
///     directive.
/// 
///     The optional `if_expr` parameter specifies a boolean result of a conditional
///     check. If this value is 1 or is not provided then the target region runs on
///     a device, if it is 0 then the target region is executed on the host device.
/// 
///     We use `MapInfoOp` to model the motion clauses and their modifiers. Even
///     though the spec differentiates between map-types & map-type-modifiers vs.
///     motion-clauses & motion-modifiers, the motion clauses and their modifiers
///     are a subset of map types and their modifiers. The subset relation is
///     handled in during verification to make sure the restrictions for target
///     update are respected.
///   
///     The `depend_kinds` and `depend_vars` arguments are variadic lists of values
///     that specify the dependencies of this particular task in relation to other
///     tasks.
///   
///     The optional `device` parameter specifies the device number for the target
///     region.
///   
///     The optional `map_vars` maps data from the current task's data environment
///     to the device data environment.
///   
///     The optional `nowait` attribute, when present, eliminates the implicit
///     barrier at the end of the construct, so the parent operation can make
///     progress even if the child operation has not completed yet.
class TargetUpdateOp;

} // namespace mlir::omp
namespace mlir::omp {

/// task construct
/// The task construct defines an explicit task.
/// 
///     For definitions of "undeferred task", "included task", "final task" and
///     "mergeable task", please check OpenMP Specification.
/// 
///     When an `if` clause is present on a task construct, and the value of
///     `if_expr` evaluates to `false`, an "undeferred task" is generated, and the
///     encountering thread must suspend the current task region, for which
///     execution cannot be resumed until execution of the structured block that is
///     associated with the generated task is completed.
/// 
///     The `in_reduction` clause specifies that this particular task (among all the
///     tasks in current taskgroup, if any) participates in a reduction.
///     `in_reduction_byref` indicates whether each reduction variable should
///     be passed by value or by reference.
///   
///     The `allocator_vars` and `allocate_vars` parameters are a variadic list of
///     values that specify the memory allocator to be used to obtain storage for
///     private values.
///   
///     The `depend_kinds` and `depend_vars` arguments are variadic lists of values
///     that specify the dependencies of this particular task in relation to other
///     tasks.
///   
///     When a `final` clause is present and the `final` clause expression evaluates
///     to `true`, the generated tasks will be final tasks. All task constructs
///     encountered during execution of a final task will generate final and
///     included tasks. The use of a variable in a `final` clause expression causes
///     an implicit reference to the variable in all enclosing constructs.
///   
///     When the `mergeable` clause is present, the tasks generated by the construct
///     are "mergeable tasks".
///   
///     The `priority` clause is a hint for the priority of the generated tasks.
///     The `priority` is a non-negative integer expression that provides a hint for
///     task execution order. Among all tasks ready to be executed, higher priority
///     tasks (those with a higher numerical value in the priority clause
///     expression) are recommended to execute before lower priority ones. The
///     default priority-value when no priority clause is specified should be
///     assumed to be zero (the lowest priority).
///   
///     If the `untied` clause is present on a task construct, any thread in the
///     team can resume the task region after a suspension. The `untied` clause is
///     ignored if a `final` clause is present on the same task construct and the
///     `final` expression evaluates to `true`, or if a task is an included task.
///   
/// 		The detach clause specifies that the task generated by the construct on which it appears is a
/// 	detachable task. A new allow-completion event is created and connected to the completion of the
/// 	associated task region. The original event-handle is updated to represent that allow-completion
/// 	event before the task data environment is created.
class TaskOp;

} // namespace mlir::omp
namespace mlir::omp {

/// taskgroup construct
/// The taskgroup construct specifies a wait on completion of child tasks of the
///     current task and their descendent tasks.
/// 
///     When a thread encounters a taskgroup construct, it starts executing the
///     region. All child tasks generated in the taskgroup region and all of their
///     descendants that bind to the same parallel region as the taskgroup region
///     are part of the taskgroup set associated with the taskgroup region. There is
///     an implicit task scheduling point at the end of the taskgroup region. The
///     current task is suspended at the task scheduling point until all tasks in
///     the taskgroup set complete execution.
///   
///     The `allocator_vars` and `allocate_vars` parameters are a variadic list of
///     values that specify the memory allocator to be used to obtain storage for
///     private values.
///   
///     The `task_reduction` clause specifies a reduction among tasks. For each list
///     item, the number of copies is unspecified. Any copies associated with the
///     reduction are initialized before they are accessed by the tasks
///     participating in the reduction. After the end of the region, the original
///     list item contains the result of the reduction. Similarly to the `reduction`
///     clause, accumulator variables must be passed in `task_reduction_vars`,
///     symbols referring to reduction declarations in the `task_reduction_syms`
///     attribute, and whether the reduction variable should be passed into the
///     reduction region by value or by reference in `task_reduction_byref`.
class TaskgroupOp;

} // namespace mlir::omp
namespace mlir::omp {

/// taskloop construct
/// The taskloop construct specifies that the iterations of one or more
///     associated loops will be executed in parallel using explicit tasks. The
///     iterations are distributed across tasks generated by the construct and
///     scheduled to be executed.
/// 
///     The body region can only contain a single block which must contain a single
///     operation. This operation must be another compatible loop wrapper or an
///     `omp.loop_nest`.
/// 
///     ```
///     omp.taskloop <clauses> {
///       omp.loop_nest (%i1, %i2) : index = (%c0, %c0) to (%c10, %c10) step (%c1, %c1) {
///         %a = load %arrA[%i1, %i2] : memref<?x?xf32>
///         %b = load %arrB[%i1, %i2] : memref<?x?xf32>
///         %sum = arith.addf %a, %b : f32
///         store %sum, %arrC[%i1, %i2] : memref<?x?xf32>
///         omp.yield
///       }
///     }
///     ```
/// 
///     For definitions of "undeferred task", "included task", "final task" and
///     "mergeable task", please check OpenMP Specification.
/// 
///     When an `if` clause is present on a taskloop construct, and if the `if`
///     clause expression evaluates to `false`, undeferred tasks are generated. The
///     use of a variable in an `if` clause expression of a taskloop construct
///     causes an implicit reference to the variable in all enclosing constructs.
///   
///     The `allocator_vars` and `allocate_vars` parameters are a variadic list of
///     values that specify the memory allocator to be used to obtain storage for
///     private values.
///   
///     When a `final` clause is present and the `final` clause expression evaluates
///     to `true`, the generated tasks will be final tasks. All task constructs
///     encountered during execution of a final task will generate final and
///     included tasks. The use of a variable in a `final` clause expression causes
///     an implicit reference to the variable in all enclosing constructs.
///   
///     If a `grainsize` clause is present, the number of logical loop iterations
///     assigned to each generated task is greater than or equal to the minimum of
///     the value of the grain-size expression and the number of logical loop
///     iterations, but less than two times the value of the grain-size expression.
///   
///     When the `mergeable` clause is present, the tasks generated by the construct
///     are "mergeable tasks".
///   
///     By default, the taskloop construct executes as if it was enclosed in a
///     taskgroup construct with no statements or directives outside of the taskloop
///     construct. Thus, the taskloop construct creates an implicit taskgroup
///     region. If the `nogroup` clause is present, no implicit taskgroup region is
///     created.
///   
///     If `num_tasks` is specified, the taskloop construct creates as many tasks as
///     the minimum of the num-tasks expression and the number of logical loop
///     iterations. Each task must have at least one logical loop iteration.
///   
///     The `priority` clause is a hint for the priority of the generated tasks.
///     The `priority` is a non-negative integer expression that provides a hint for
///     task execution order. Among all tasks ready to be executed, higher priority
///     tasks (those with a higher numerical value in the priority clause
///     expression) are recommended to execute before lower priority ones. The
///     default priority-value when no priority clause is specified should be
///     assumed to be zero (the lowest priority).
///   
///     Reductions can be performed by specifying the reduction modifer
///     (`default`, `inscan` or `task`) in `reduction_mod`, reduction accumulator
///     variables in `reduction_vars`, symbols referring to reduction declarations
///     in the `reduction_syms` attribute, and whether the reduction variable
///     should be passed into the reduction region by value or by reference in
///     `reduction_byref`. Each reduction is identified by the accumulator it uses
///     and accumulators must not be repeated in the same reduction. A private
///     variable corresponding to the accumulator is used in place of the
///     accumulator inside the body of the operation. The reduction declaration
///     specifies how to combine the values from each iteration, section, team,
///     thread or simd lane defined by the operation's region into the final value,
///     which is available in the accumulator after they all complete.
///   
///     If the `untied` clause is present on a task construct, any thread in the
///     team can resume the task region after a suspension. The `untied` clause is
///     ignored if a `final` clause is present on the same task construct and the
///     `final` expression evaluates to `true`, or if a task is an included task.
///   
///     If an `in_reduction` clause is present on the taskloop construct, the
///     behavior is as if each generated task was defined by a task construct on
///     which an `in_reduction` clause with the same reduction operator and list
///     items is present. Thus, the generated tasks are participants of a reduction
///     previously defined by a reduction scoping clause. In this case, accumulator
///     variables are specified in `in_reduction_vars`, symbols referring to
///     reduction declarations in `in_reduction_syms` and `in_reduction_byref`
///     indicate for each reduction variable whether it should be passed by value or
///     by reference.
/// 
///     If a `reduction` clause is present on the taskloop construct, the behavior
///     is as if a `task_reduction` clause with the same reduction operator and list
///     items was applied to the implicit taskgroup construct enclosing the taskloop
///     construct. The taskloop construct executes as if each generated task was
///     defined by a task construct on which an `in_reduction` clause with the same
///     reduction operator and list items is present. Thus, the generated tasks are
///     participants of the reduction defined by the `task_reduction` clause that
///     was applied to the implicit taskgroup construct.
class TaskloopOp;

} // namespace mlir::omp
namespace mlir::omp {

/// taskwait construct
/// The taskwait construct specifies a wait on the completion of child tasks
///     of the current task.
///   
///     The `depend_kinds` and `depend_vars` arguments are variadic lists of values
///     that specify the dependencies of this particular task in relation to other
///     tasks.
///   
///     The optional `nowait` attribute, when present, eliminates the implicit
///     barrier at the end of the construct, so the parent operation can make
///     progress even if the child operation has not completed yet.
class TaskwaitOp;

} // namespace mlir::omp
namespace mlir::omp {

/// taskyield construct
/// The taskyield construct specifies that the current task can be suspended
///     in favor of execution of a different task.
class TaskyieldOp;

} // namespace mlir::omp
namespace mlir::omp {

/// teams construct
/// The teams construct defines a region of code that triggers the creation of a
///     league of teams. Once created, the number of teams remains constant for the
///     duration of its code region.
/// 
///     If the `if_expr` is present and it evaluates to `false`, the number of teams
///     created is one.
///   
///     The `allocator_vars` and `allocate_vars` parameters are a variadic list of
///     values that specify the memory allocator to be used to obtain storage for
///     private values.
///   
///     The `num_teams` clause specifies the bounds on the league space formed by the
///     construct on which it appears.
/// 
///     Multi-dimensional (OpenMP 6.1 dims modifier):
///     - Uses `num_teams_upper_vars` with multiple values (one per dimension)
///     - Values may have different types; they will be cast at LLVM IR translation
///     - Format: `num_teams(to %v0, %v1, ... : type0, type1, ...)`
///     - Example: `num_teams(to %ub0, %ub1, %ub2 : i32, i64, i32)`
///     - The number of dimensions is implicitly `num_teams_upper_vars.size()`
/// 
///     Uni-dimensional (legacy format):
///     - Uses `num_teams_upper_vars` with one value and optional `num_teams_lower`
///     - If lower bound not specified, it defaults to upper bound value
///     - Format: `num_teams(%lb : type to %ub : type)` or `num_teams(to %ub : type)`
///     - Example: `num_teams(%lb : i32 to %ub : i32)` or `num_teams(to %ub : i32)`
///   
///     Reductions can be performed by specifying the reduction modifer
///     (`default`, `inscan` or `task`) in `reduction_mod`, reduction accumulator
///     variables in `reduction_vars`, symbols referring to reduction declarations
///     in the `reduction_syms` attribute, and whether the reduction variable
///     should be passed into the reduction region by value or by reference in
///     `reduction_byref`. Each reduction is identified by the accumulator it uses
///     and accumulators must not be repeated in the same reduction. A private
///     variable corresponding to the accumulator is used in place of the
///     accumulator inside the body of the operation. The reduction declaration
///     specifies how to combine the values from each iteration, section, team,
///     thread or simd lane defined by the operation's region into the final value,
///     which is available in the accumulator after they all complete.
///   
///     The `thread_limit` clause specifies the limit on the number of threads.
/// 
///     Multi-dimensional format (dims modifier):
///     - Multiple values can be specified for multi-dimensional thread limits.
///     - The number of dimensions is derived from the number of values.
///     - Values can have different integer types.
///     - Format: `thread_limit(%v1, %v2, ... : type1, type2, ...)`
///     - Example: `thread_limit(%n, %m : i32, i64)`
/// 
///     Single value format:
///     - A single value specifies the thread limit.
///     - Format: `thread_limit(%value : type)`
///     - Example: `thread_limit(%n : i32)`
class TeamsOp;

} // namespace mlir::omp
namespace mlir::omp {

/// terminator for OpenMP regions
/// A terminator operation for regions that appear in the body of OpenMP
///     operation.  These regions are not expected to return any value so the
///     terminator takes no operands. The terminator op returns control to the
///     enclosing op.
class TerminatorOp;

} // namespace mlir::omp
namespace mlir::omp {

/// threadprivate directive
/// The threadprivate directive specifies that variables are replicated, with
///     each thread having its own copy.
/// 
///     The current implementation uses the OpenMP runtime to provide thread-local
///     storage (TLS). Using the TLS feature of the LLVM IR will be supported in
///     future.
/// 
///     This operation takes in the address of a symbol that represents the original
///     variable and returns the address of its TLS. All occurrences of
///     threadprivate variables in a parallel region should use the TLS returned by
///     this operation.
/// 
///     The `sym_addr` refers to the address of the symbol, which is a pointer to
///     the original variable.
class ThreadprivateOp;

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP tile operation
/// Represents the OpenMP tile directive introduced in OpenMP 5.1.
/// 
///     The construct partitions the logical iteration space of the affected loops
///     into equally-sized tiles, then creates two sets of nested loops. The outer
///     loops, called the grid loops, iterate over all tiles. The inner loops,
///     called the intratile loops, iterate over the logical iterations of a tile.
///     The sizes clause determines the size of a tile.
/// 
///     Currently, the affected loops must be rectangular (the tripcount of the
///     inner loop must not depend on any iv of an surrounding affected loop) and
///     perfectly nested (except for the innermost affected loop, no operations
///     other than the nested loop and the terminator in the loop body).
///   
///     The `sizes` clauses defines the size of a grid over a multi-dimensional
///     logical iteration space. This grid is used for loop transformations such as
///     `tile` and `strip`. The size per dimension can be a variable, but only
///     values that are not at least 2 make sense. It is not specified what happens
///     when smaller values are used, but should still result in a loop nest that
///     executes each logical iteration once.
class TileOp;

} // namespace mlir::omp
namespace mlir::omp {

/// OpenMP heuristic unroll operation
/// Represents a `#pragma omp unroll` construct introduced in OpenMP 5.1.
/// 
///     The operation has one applyee and no generatees. The applyee is unrolled
///     according to implementation-defined heuristics. Implementations may choose
///     to not unroll the loop, partially unroll by a chosen factor, or fully
///     unroll it. Even if the implementation chooses to partially unroll the
///     applyee, the resulting unrolled loop is not accessible as a generatee. Use
///     omp.unroll_partial if a generatee is required.
/// 
///     The lowering is implemented using `OpenMPIRBuilder::unrollLoopHeuristic`,
///     which just attaches `llvm.loop.unroll.enable` metadata to the loop so the
///     unrolling is carried-out by LLVM's LoopUnroll pass. That is, unrolling only
///     actually performed in optimized builds.
/// 
///     Assembly formats:
///       omp.unroll_heuristic(%cli)
///       omp.unroll_heuristic(%cli) -> ()
class UnrollHeuristicOp;

} // namespace mlir::omp
namespace mlir::omp {

/// workdistribute directive
/// workdistribute divides execution of the enclosed structured block into
///     separate units of work, each executed only once by each
///     initial thread in the league.
///     ```
///     !$omp target teams
///         !$omp workdistribute
///         y = a * x + y 
///         !$omp end workdistribute
///     !$omp end target teams
///     ```
class WorkdistributeOp;

} // namespace mlir::omp
namespace mlir::omp {

/// contains loop nests to be parallelized by workshare
/// This operation wraps a loop nest that is marked for dividing into units of
///     work by an encompassing omp.workshare operation.
class WorkshareLoopWrapperOp;

} // namespace mlir::omp
namespace mlir::omp {

/// workshare directive
/// The workshare construct divides the execution of the enclosed structured
///     block into separate units of work, and causes the threads of the team to
///     share the work such that each unit is executed only once by one thread, in
///     the context of its implicit task
/// 
///     This operation is used for the intermediate representation of the workshare
///     block before the work gets divided between the threads. See the flang
///     LowerWorkshare pass for details.
///   
///     The optional `nowait` attribute, when present, eliminates the implicit
///     barrier at the end of the construct, so the parent operation can make
///     progress even if the child operation has not completed yet.
class WorkshareOp;

} // namespace mlir::omp
namespace mlir::omp {

/// worksharing-loop construct
/// The worksharing-loop construct specifies that the iterations of the loop(s)
///     will be executed in parallel by threads in the current context. These
///     iterations are spread across threads that already exist in the enclosing
///     parallel region.
/// 
///     The body region can only contain a single block which must contain a single
///     operation. This operation must be another compatible loop wrapper or an
///     `omp.loop_nest`.
/// 
///     ```
///     omp.wsloop <clauses> {
///       omp.loop_nest (%i1, %i2) : index = (%c0, %c0) to (%c10, %c10) step (%c1, %c1) {
///         %a = load %arrA[%i1, %i2] : memref<?x?xf32>
///         %b = load %arrB[%i1, %i2] : memref<?x?xf32>
///         %sum = arith.addf %a, %b : f32
///         store %sum, %arrC[%i1, %i2] : memref<?x?xf32>
///         omp.yield
///       }
///     }
///     ```
///   
///     The `allocator_vars` and `allocate_vars` parameters are a variadic list of
///     values that specify the memory allocator to be used to obtain storage for
///     private values.
///   
///     The `linear_step_vars` operand additionally specifies the step for each
///     associated linear operand. Note that the `linear_vars` and
///     `linear_step_vars` variadic lists should contain the same number of
///     elements.
///   
///     The optional `nowait` attribute, when present, eliminates the implicit
///     barrier at the end of the construct, so the parent operation can make
///     progress even if the child operation has not completed yet.
///   
///     The optional `order` attribute specifies which order the iterations of the
///     associated loops are executed in. Currently the only option for this
///     attribute is "concurrent".
///   
///     The optional `ordered` attribute specifies how many loops are associated
///     with the worksharing-loop construct. The value of zero refers to the ordered
///     clause specified without parameter.
///   
///     Reductions can be performed by specifying the reduction modifer
///     (`default`, `inscan` or `task`) in `reduction_mod`, reduction accumulator
///     variables in `reduction_vars`, symbols referring to reduction declarations
///     in the `reduction_syms` attribute, and whether the reduction variable
///     should be passed into the reduction region by value or by reference in
///     `reduction_byref`. Each reduction is identified by the accumulator it uses
///     and accumulators must not be repeated in the same reduction. A private
///     variable corresponding to the accumulator is used in place of the
///     accumulator inside the body of the operation. The reduction declaration
///     specifies how to combine the values from each iteration, section, team,
///     thread or simd lane defined by the operation's region into the final value,
///     which is available in the accumulator after they all complete.
///   
///     The optional `schedule_kind` attribute specifies the loop schedule for this
///     loop, determining how the loop is distributed across the parallel threads.
///     The optional `schedule_chunk` associated with this determines further
///     controls this distribution.
class WsloopOp;

} // namespace mlir::omp
namespace mlir::omp {

/// loop yield and termination operation
/// "omp.yield" yields SSA values from the OpenMP dialect op region and
///     terminates the region. The semantics of how the values are yielded is
///     defined by the parent operation.
class YieldOp;

} // namespace mlir::omp
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::AllocateDirOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllocateDirOpGenericAdaptorBase {
public:
  struct Properties {
    using alignTy = ::mlir::IntegerAttr;
    alignTy align;

    auto getAlign() const {
      auto &propStorage = this->align;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlign(const ::mlir::IntegerAttr &propValue) {
      this->align = propValue;
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
        rhs.align == this->align &&
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
  AllocateDirOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.allocate_dir", odsAttrs.getContext());
  }

  AllocateDirOpGenericAdaptorBase(AllocateDirOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getAlignAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().align);
    return attr;
  }

  ::std::optional<uint64_t> getAlign();
};

} // namespace detail
template <typename RangeT>
class AllocateDirOpGenericAdaptor : public detail::AllocateDirOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllocateDirOpGenericAdaptorBase;
  static constexpr int odsIndex_varList = 0;
  static constexpr int odsIndex_allocator = 1;
public:
  AllocateDirOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllocateDirOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllocateDirOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllocateDirOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : AllocateDirOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllocateDirOpGenericAdaptor(RangeT values, const AllocateDirOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllocateDirOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllocateDirOp>>>
  AllocateDirOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getVarList() {
    return getODSOperands(0);
  }

  ValueT getAllocator() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllocateDirOpAdaptor : public AllocateDirOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllocateDirOpGenericAdaptor::AllocateDirOpGenericAdaptor;
  AllocateDirOpAdaptor(AllocateDirOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllocateDirOp : public ::mlir::Op<AllocateDirOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllocateDirOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllocateDirOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_varList = 0;
  static constexpr int odsIndex_allocator = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("align"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.allocate_dir");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getVarList() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getAllocator() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getVarListMutable();
  ::mlir::MutableOperandRange getAllocatorMutable();
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
  ::mlir::IntegerAttr getAlignAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().align);
  }

  ::std::optional<uint64_t> getAlign();
  void setAlignAttr(::mlir::IntegerAttr attr) {
    getProperties().align = attr;
  }

  void setAlign(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeAlignAttr() {
      auto attr = getProperties().align;
      getProperties().align = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange varList, /*optional*/::mlir::IntegerAttr align, /*optional*/::mlir::Value allocator);
  static AllocateDirOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange varList, /*optional*/::mlir::IntegerAttr align, /*optional*/::mlir::Value allocator);
  static AllocateDirOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange varList, /*optional*/::mlir::IntegerAttr align, /*optional*/::mlir::Value allocator);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange varList, /*optional*/::mlir::IntegerAttr align, /*optional*/::mlir::Value allocator);
  static AllocateDirOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange varList, /*optional*/::mlir::IntegerAttr align, /*optional*/::mlir::Value allocator);
  static AllocateDirOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange varList, /*optional*/::mlir::IntegerAttr align, /*optional*/::mlir::Value allocator);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocateDirOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocateDirOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocateDirOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocateDirOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::AllocateDirOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::AtomicCaptureOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AtomicCaptureOpGenericAdaptorBase {
public:
  struct Properties {
    using hintTy = ::mlir::IntegerAttr;
    hintTy hint;

    auto getHint() const {
      auto &propStorage = this->hint;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setHint(const ::mlir::IntegerAttr &propValue) {
      this->hint = propValue;
    }
    using memory_orderTy = ::mlir::omp::ClauseMemoryOrderKindAttr;
    memory_orderTy memory_order;

    auto getMemoryOrder() const {
      auto &propStorage = this->memory_order;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(propStorage);
    }
    void setMemoryOrder(const ::mlir::omp::ClauseMemoryOrderKindAttr &propValue) {
      this->memory_order = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.hint == this->hint &&
        rhs.memory_order == this->memory_order &&
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
  AtomicCaptureOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.atomic.capture", odsAttrs.getContext());
  }

  AtomicCaptureOpGenericAdaptorBase(AtomicCaptureOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getHintAttr();
  uint64_t getHint();
  ::mlir::omp::ClauseMemoryOrderKindAttr getMemoryOrderAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(getProperties().memory_order);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseMemoryOrderKind> getMemoryOrder();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class AtomicCaptureOpGenericAdaptor : public detail::AtomicCaptureOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AtomicCaptureOpGenericAdaptorBase;
public:
  AtomicCaptureOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AtomicCaptureOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AtomicCaptureOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AtomicCaptureOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AtomicCaptureOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AtomicCaptureOpGenericAdaptor(RangeT values, const AtomicCaptureOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AtomicCaptureOp, typename = std::enable_if_t<std::is_same_v<LateInst, AtomicCaptureOp>>>
  AtomicCaptureOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AtomicCaptureOpAdaptor : public AtomicCaptureOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AtomicCaptureOpGenericAdaptor::AtomicCaptureOpGenericAdaptor;
  AtomicCaptureOpAdaptor(AtomicCaptureOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AtomicCaptureOp : public ::mlir::Op<AtomicCaptureOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<TerminatorOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::accomp::AtomicCaptureOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AtomicCaptureOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AtomicCaptureOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("hint"), ::llvm::StringRef("memory_order")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getHintAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getHintAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getMemoryOrderAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getMemoryOrderAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.atomic.capture");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getHintAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().hint);
  }

  uint64_t getHint();
  ::mlir::omp::ClauseMemoryOrderKindAttr getMemoryOrderAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(getProperties().memory_order);
  }

  ::std::optional<::mlir::omp::ClauseMemoryOrderKind> getMemoryOrder();
  void setHintAttr(::mlir::IntegerAttr attr) {
    getProperties().hint = attr;
  }

  void setHint(::std::optional<uint64_t> attrValue);
  void setMemoryOrderAttr(::mlir::omp::ClauseMemoryOrderKindAttr attr) {
    getProperties().memory_order = attr;
  }

  void setMemoryOrder(::std::optional<::mlir::omp::ClauseMemoryOrderKind> attrValue);
  ::mlir::Attribute removeHintAttr() {
      auto attr = getProperties().hint;
      getProperties().hint = {};
      return attr;
  }

  ::mlir::Attribute removeMemoryOrderAttr() {
      auto attr = getProperties().memory_order;
      getProperties().memory_order = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicCaptureOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicCaptureOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicCaptureOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicCaptureOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicCaptureOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicCaptureOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicCaptureOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicCaptureOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicCaptureOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicCaptureOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicCaptureOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicCaptureOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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
  /// Returns the `atomic.read` operation inside the region, if any.
  /// Otherwise, it returns nullptr.
  AtomicReadOp getAtomicReadOp();

  /// Returns the `atomic.write` operation inside the region, if any.
  /// Otherwise, it returns nullptr.
  AtomicWriteOp getAtomicWriteOp();

  /// Returns the `atomic.update` operation inside the region, if any.
  /// Otherwise, it returns nullptr.
  AtomicUpdateOp getAtomicUpdateOp();

};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::AtomicCaptureOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::AtomicReadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AtomicReadOpGenericAdaptorBase {
public:
  struct Properties {
    using element_typeTy = ::mlir::TypeAttr;
    element_typeTy element_type;

    auto getElementType() const {
      auto &propStorage = this->element_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setElementType(const ::mlir::TypeAttr &propValue) {
      this->element_type = propValue;
    }
    using hintTy = ::mlir::IntegerAttr;
    hintTy hint;

    auto getHint() const {
      auto &propStorage = this->hint;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setHint(const ::mlir::IntegerAttr &propValue) {
      this->hint = propValue;
    }
    using memory_orderTy = ::mlir::omp::ClauseMemoryOrderKindAttr;
    memory_orderTy memory_order;

    auto getMemoryOrder() const {
      auto &propStorage = this->memory_order;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(propStorage);
    }
    void setMemoryOrder(const ::mlir::omp::ClauseMemoryOrderKindAttr &propValue) {
      this->memory_order = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.element_type == this->element_type &&
        rhs.hint == this->hint &&
        rhs.memory_order == this->memory_order &&
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
  AtomicReadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.atomic.read", odsAttrs.getContext());
  }

  AtomicReadOpGenericAdaptorBase(AtomicReadOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getElementTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().element_type);
    return attr;
  }

  ::mlir::Type getElementType();
  ::mlir::IntegerAttr getHintAttr();
  uint64_t getHint();
  ::mlir::omp::ClauseMemoryOrderKindAttr getMemoryOrderAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(getProperties().memory_order);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseMemoryOrderKind> getMemoryOrder();
};

} // namespace detail
template <typename RangeT>
class AtomicReadOpGenericAdaptor : public detail::AtomicReadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AtomicReadOpGenericAdaptorBase;
  static constexpr int odsIndex_x = 0;
  static constexpr int odsIndex_v = 1;
public:
  AtomicReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AtomicReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AtomicReadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AtomicReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AtomicReadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AtomicReadOpGenericAdaptor(RangeT values, const AtomicReadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AtomicReadOp, typename = std::enable_if_t<std::is_same_v<LateInst, AtomicReadOp>>>
  AtomicReadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getV() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AtomicReadOpAdaptor : public AtomicReadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AtomicReadOpGenericAdaptor::AtomicReadOpGenericAdaptor;
  AtomicReadOpAdaptor(AtomicReadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AtomicReadOp : public ::mlir::Op<AtomicReadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::accomp::AtomicReadOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AtomicReadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AtomicReadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_x = 0;
  static constexpr int odsIndex_v = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("element_type"), ::llvm::StringRef("hint"), ::llvm::StringRef("memory_order")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getElementTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getElementTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getHintAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getHintAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getMemoryOrderAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getMemoryOrderAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.atomic.read");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::omp::PointerLikeType> getX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::PointerLikeType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::omp::PointerLikeType> getV() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::PointerLikeType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getXMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getVMutable() {
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::TypeAttr getElementTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().element_type);
  }

  ::mlir::Type getElementType();
  ::mlir::IntegerAttr getHintAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().hint);
  }

  uint64_t getHint();
  ::mlir::omp::ClauseMemoryOrderKindAttr getMemoryOrderAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(getProperties().memory_order);
  }

  ::std::optional<::mlir::omp::ClauseMemoryOrderKind> getMemoryOrder();
  void setElementTypeAttr(::mlir::TypeAttr attr) {
    getProperties().element_type = attr;
  }

  void setElementType(::mlir::Type attrValue);
  void setHintAttr(::mlir::IntegerAttr attr) {
    getProperties().hint = attr;
  }

  void setHint(::std::optional<uint64_t> attrValue);
  void setMemoryOrderAttr(::mlir::omp::ClauseMemoryOrderKindAttr attr) {
    getProperties().memory_order = attr;
  }

  void setMemoryOrder(::std::optional<::mlir::omp::ClauseMemoryOrderKind> attrValue);
  ::mlir::Attribute removeHintAttr() {
      auto attr = getProperties().hint;
      getProperties().hint = {};
      return attr;
  }

  ::mlir::Attribute removeMemoryOrderAttr() {
      auto attr = getProperties().memory_order;
      getProperties().memory_order = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value x, ::mlir::Value v, ::mlir::TypeAttr element_type, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value x, ::mlir::Value v, ::mlir::TypeAttr element_type, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value x, ::mlir::Value v, ::mlir::TypeAttr element_type, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value v, ::mlir::TypeAttr element_type, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value v, ::mlir::TypeAttr element_type, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value v, ::mlir::TypeAttr element_type, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value x, ::mlir::Value v, ::mlir::Type element_type, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value x, ::mlir::Value v, ::mlir::Type element_type, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value x, ::mlir::Value v, ::mlir::Type element_type, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value v, ::mlir::Type element_type, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value v, ::mlir::Type element_type, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value v, ::mlir::Type element_type, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::AtomicReadOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::AtomicUpdateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AtomicUpdateOpGenericAdaptorBase {
public:
  struct Properties {
    using atomic_controlTy = ::mlir::omp::AtomicControlAttr;
    atomic_controlTy atomic_control;

    auto getAtomicControl() const {
      auto &propStorage = this->atomic_control;
      return ::llvm::dyn_cast_or_null<::mlir::omp::AtomicControlAttr>(propStorage);
    }
    void setAtomicControl(const ::mlir::omp::AtomicControlAttr &propValue) {
      this->atomic_control = propValue;
    }
    using hintTy = ::mlir::IntegerAttr;
    hintTy hint;

    auto getHint() const {
      auto &propStorage = this->hint;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setHint(const ::mlir::IntegerAttr &propValue) {
      this->hint = propValue;
    }
    using memory_orderTy = ::mlir::omp::ClauseMemoryOrderKindAttr;
    memory_orderTy memory_order;

    auto getMemoryOrder() const {
      auto &propStorage = this->memory_order;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(propStorage);
    }
    void setMemoryOrder(const ::mlir::omp::ClauseMemoryOrderKindAttr &propValue) {
      this->memory_order = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.atomic_control == this->atomic_control &&
        rhs.hint == this->hint &&
        rhs.memory_order == this->memory_order &&
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
  AtomicUpdateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.atomic.update", odsAttrs.getContext());
  }

  AtomicUpdateOpGenericAdaptorBase(AtomicUpdateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::omp::AtomicControlAttr getAtomicControlAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::AtomicControlAttr>(getProperties().atomic_control);
    return attr;
  }

  ::std::optional<::mlir::omp::AtomicControlAttr> getAtomicControl();
  ::mlir::IntegerAttr getHintAttr();
  uint64_t getHint();
  ::mlir::omp::ClauseMemoryOrderKindAttr getMemoryOrderAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(getProperties().memory_order);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseMemoryOrderKind> getMemoryOrder();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class AtomicUpdateOpGenericAdaptor : public detail::AtomicUpdateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AtomicUpdateOpGenericAdaptorBase;
  static constexpr int odsIndex_x = 0;
public:
  AtomicUpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AtomicUpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AtomicUpdateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AtomicUpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AtomicUpdateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AtomicUpdateOpGenericAdaptor(RangeT values, const AtomicUpdateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AtomicUpdateOp, typename = std::enable_if_t<std::is_same_v<LateInst, AtomicUpdateOp>>>
  AtomicUpdateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AtomicUpdateOpAdaptor : public AtomicUpdateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AtomicUpdateOpGenericAdaptor::AtomicUpdateOpGenericAdaptor;
  AtomicUpdateOpAdaptor(AtomicUpdateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AtomicUpdateOp : public ::mlir::Op<AtomicUpdateOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::accomp::AtomicUpdateOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AtomicUpdateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AtomicUpdateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_x = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("atomic_control"), ::llvm::StringRef("hint"), ::llvm::StringRef("memory_order")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAtomicControlAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAtomicControlAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getHintAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getHintAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getMemoryOrderAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getMemoryOrderAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.atomic.update");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::omp::PointerLikeType> getX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::PointerLikeType>>(*getODSOperands(0).begin());
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
  ::mlir::omp::AtomicControlAttr getAtomicControlAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::AtomicControlAttr>(getProperties().atomic_control);
  }

  ::std::optional<::mlir::omp::AtomicControlAttr> getAtomicControl();
  ::mlir::IntegerAttr getHintAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().hint);
  }

  uint64_t getHint();
  ::mlir::omp::ClauseMemoryOrderKindAttr getMemoryOrderAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(getProperties().memory_order);
  }

  ::std::optional<::mlir::omp::ClauseMemoryOrderKind> getMemoryOrder();
  void setAtomicControlAttr(::mlir::omp::AtomicControlAttr attr) {
    getProperties().atomic_control = attr;
  }

  void setHintAttr(::mlir::IntegerAttr attr) {
    getProperties().hint = attr;
  }

  void setHint(::std::optional<uint64_t> attrValue);
  void setMemoryOrderAttr(::mlir::omp::ClauseMemoryOrderKindAttr attr) {
    getProperties().memory_order = attr;
  }

  void setMemoryOrder(::std::optional<::mlir::omp::ClauseMemoryOrderKind> attrValue);
  ::mlir::Attribute removeAtomicControlAttr() {
      auto attr = getProperties().atomic_control;
      getProperties().atomic_control = {};
      return attr;
  }

  ::mlir::Attribute removeHintAttr() {
      auto attr = getProperties().hint;
      getProperties().hint = {};
      return attr;
  }

  ::mlir::Attribute removeMemoryOrderAttr() {
      auto attr = getProperties().memory_order;
      getProperties().memory_order = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x, /*optional*/::mlir::omp::AtomicControlAttr atomic_control, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static ::llvm::LogicalResult canonicalize(AtomicUpdateOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::AtomicUpdateOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::AtomicWriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AtomicWriteOpGenericAdaptorBase {
public:
  struct Properties {
    using hintTy = ::mlir::IntegerAttr;
    hintTy hint;

    auto getHint() const {
      auto &propStorage = this->hint;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setHint(const ::mlir::IntegerAttr &propValue) {
      this->hint = propValue;
    }
    using memory_orderTy = ::mlir::omp::ClauseMemoryOrderKindAttr;
    memory_orderTy memory_order;

    auto getMemoryOrder() const {
      auto &propStorage = this->memory_order;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(propStorage);
    }
    void setMemoryOrder(const ::mlir::omp::ClauseMemoryOrderKindAttr &propValue) {
      this->memory_order = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.hint == this->hint &&
        rhs.memory_order == this->memory_order &&
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
  AtomicWriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.atomic.write", odsAttrs.getContext());
  }

  AtomicWriteOpGenericAdaptorBase(AtomicWriteOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getHintAttr();
  uint64_t getHint();
  ::mlir::omp::ClauseMemoryOrderKindAttr getMemoryOrderAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(getProperties().memory_order);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseMemoryOrderKind> getMemoryOrder();
};

} // namespace detail
template <typename RangeT>
class AtomicWriteOpGenericAdaptor : public detail::AtomicWriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AtomicWriteOpGenericAdaptorBase;
  static constexpr int odsIndex_x = 0;
  static constexpr int odsIndex_expr = 1;
public:
  AtomicWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AtomicWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AtomicWriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AtomicWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AtomicWriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AtomicWriteOpGenericAdaptor(RangeT values, const AtomicWriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AtomicWriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, AtomicWriteOp>>>
  AtomicWriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getExpr() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AtomicWriteOpAdaptor : public AtomicWriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AtomicWriteOpGenericAdaptor::AtomicWriteOpGenericAdaptor;
  AtomicWriteOpAdaptor(AtomicWriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AtomicWriteOp : public ::mlir::Op<AtomicWriteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::accomp::AtomicWriteOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AtomicWriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AtomicWriteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_x = 0;
  static constexpr int odsIndex_expr = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("hint"), ::llvm::StringRef("memory_order")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getHintAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getHintAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getMemoryOrderAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getMemoryOrderAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.atomic.write");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::omp::PointerLikeType> getX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::PointerLikeType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getExpr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getXMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getExprMutable() {
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getHintAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().hint);
  }

  uint64_t getHint();
  ::mlir::omp::ClauseMemoryOrderKindAttr getMemoryOrderAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseMemoryOrderKindAttr>(getProperties().memory_order);
  }

  ::std::optional<::mlir::omp::ClauseMemoryOrderKind> getMemoryOrder();
  void setHintAttr(::mlir::IntegerAttr attr) {
    getProperties().hint = attr;
  }

  void setHint(::std::optional<uint64_t> attrValue);
  void setMemoryOrderAttr(::mlir::omp::ClauseMemoryOrderKindAttr attr) {
    getProperties().memory_order = attr;
  }

  void setMemoryOrder(::std::optional<::mlir::omp::ClauseMemoryOrderKind> attrValue);
  ::mlir::Attribute removeHintAttr() {
      auto attr = getProperties().hint;
      getProperties().hint = {};
      return attr;
  }

  ::mlir::Attribute removeMemoryOrderAttr() {
      auto attr = getProperties().memory_order;
      getProperties().memory_order = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value x, ::mlir::Value expr, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value x, ::mlir::Value expr, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value x, ::mlir::Value expr, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value expr, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value expr, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value expr, /*optional*/::mlir::IntegerAttr hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value x, ::mlir::Value expr, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value x, ::mlir::Value expr, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value x, ::mlir::Value expr, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value expr, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value expr, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static AtomicWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value x, ::mlir::Value expr, /*optional*/uint64_t hint, /*optional*/::mlir::omp::ClauseMemoryOrderKindAttr memory_order);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AtomicWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AtomicWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::AtomicWriteOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::BarrierOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BarrierOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BarrierOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.barrier", odsAttrs.getContext());
  }

  BarrierOpGenericAdaptorBase(BarrierOp op);

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
class BarrierOpGenericAdaptor : public detail::BarrierOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BarrierOpGenericAdaptorBase;
public:
  BarrierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BarrierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : BarrierOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BarrierOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BarrierOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BarrierOpGenericAdaptor(RangeT values, const BarrierOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BarrierOp, typename = std::enable_if_t<std::is_same_v<LateInst, BarrierOp>>>
  BarrierOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class BarrierOpAdaptor : public BarrierOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BarrierOpGenericAdaptor::BarrierOpGenericAdaptor;
  BarrierOpAdaptor(BarrierOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BarrierOp : public ::mlir::Op<BarrierOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BarrierOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BarrierOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.barrier");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static BarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static BarrierOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static BarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static BarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::BarrierOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::CancelOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CancelOpGenericAdaptorBase {
public:
  struct Properties {
    using cancel_directiveTy = ::mlir::omp::ClauseCancellationConstructTypeAttr;
    cancel_directiveTy cancel_directive;

    auto getCancelDirective() const {
      auto &propStorage = this->cancel_directive;
      return ::llvm::cast<::mlir::omp::ClauseCancellationConstructTypeAttr>(propStorage);
    }
    void setCancelDirective(const ::mlir::omp::ClauseCancellationConstructTypeAttr &propValue) {
      this->cancel_directive = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.cancel_directive == this->cancel_directive &&
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
  CancelOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.cancel", odsAttrs.getContext());
  }

  CancelOpGenericAdaptorBase(CancelOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::omp::ClauseCancellationConstructTypeAttr getCancelDirectiveAttr() {
    auto attr = ::llvm::cast<::mlir::omp::ClauseCancellationConstructTypeAttr>(getProperties().cancel_directive);
    return attr;
  }

  ::mlir::omp::ClauseCancellationConstructType getCancelDirective();
};

} // namespace detail
template <typename RangeT>
class CancelOpGenericAdaptor : public detail::CancelOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CancelOpGenericAdaptorBase;
  static constexpr int odsIndex_if_expr = 0;
public:
  CancelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CancelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CancelOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CancelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CancelOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CancelOpGenericAdaptor(RangeT values, const CancelOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CancelOp, typename = std::enable_if_t<std::is_same_v<LateInst, CancelOp>>>
  CancelOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CancelOpAdaptor : public CancelOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CancelOpGenericAdaptor::CancelOpGenericAdaptor;
  CancelOpAdaptor(CancelOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CancelOp : public ::mlir::Op<CancelOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CancelOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CancelOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_if_expr = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("cancel_directive")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCancelDirectiveAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCancelDirectiveAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.cancel");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getIfExprMutable();
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
  ::mlir::omp::ClauseCancellationConstructTypeAttr getCancelDirectiveAttr() {
    return ::llvm::cast<::mlir::omp::ClauseCancellationConstructTypeAttr>(getProperties().cancel_directive);
  }

  ::mlir::omp::ClauseCancellationConstructType getCancelDirective();
  void setCancelDirectiveAttr(::mlir::omp::ClauseCancellationConstructTypeAttr attr) {
    getProperties().cancel_directive = attr;
  }

  void setCancelDirective(::mlir::omp::ClauseCancellationConstructType attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const CancelOperands &clauses);
  static CancelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const CancelOperands &clauses);
  static CancelOp create(::mlir::ImplicitLocOpBuilder &builder, const CancelOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive, /*optional*/::mlir::Value if_expr);
  static CancelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive, /*optional*/::mlir::Value if_expr);
  static CancelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive, /*optional*/::mlir::Value if_expr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive, /*optional*/::mlir::Value if_expr);
  static CancelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive, /*optional*/::mlir::Value if_expr);
  static CancelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive, /*optional*/::mlir::Value if_expr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::omp::ClauseCancellationConstructType cancel_directive, /*optional*/::mlir::Value if_expr);
  static CancelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::omp::ClauseCancellationConstructType cancel_directive, /*optional*/::mlir::Value if_expr);
  static CancelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::omp::ClauseCancellationConstructType cancel_directive, /*optional*/::mlir::Value if_expr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructType cancel_directive, /*optional*/::mlir::Value if_expr);
  static CancelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructType cancel_directive, /*optional*/::mlir::Value if_expr);
  static CancelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructType cancel_directive, /*optional*/::mlir::Value if_expr);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CancelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CancelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CancelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CancelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::CancelOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::CancellationPointOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CancellationPointOpGenericAdaptorBase {
public:
  struct Properties {
    using cancel_directiveTy = ::mlir::omp::ClauseCancellationConstructTypeAttr;
    cancel_directiveTy cancel_directive;

    auto getCancelDirective() const {
      auto &propStorage = this->cancel_directive;
      return ::llvm::cast<::mlir::omp::ClauseCancellationConstructTypeAttr>(propStorage);
    }
    void setCancelDirective(const ::mlir::omp::ClauseCancellationConstructTypeAttr &propValue) {
      this->cancel_directive = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.cancel_directive == this->cancel_directive &&
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
  CancellationPointOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.cancellation_point", odsAttrs.getContext());
  }

  CancellationPointOpGenericAdaptorBase(CancellationPointOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::omp::ClauseCancellationConstructTypeAttr getCancelDirectiveAttr() {
    auto attr = ::llvm::cast<::mlir::omp::ClauseCancellationConstructTypeAttr>(getProperties().cancel_directive);
    return attr;
  }

  ::mlir::omp::ClauseCancellationConstructType getCancelDirective();
};

} // namespace detail
template <typename RangeT>
class CancellationPointOpGenericAdaptor : public detail::CancellationPointOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CancellationPointOpGenericAdaptorBase;
public:
  CancellationPointOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CancellationPointOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CancellationPointOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CancellationPointOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CancellationPointOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CancellationPointOpGenericAdaptor(RangeT values, const CancellationPointOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CancellationPointOp, typename = std::enable_if_t<std::is_same_v<LateInst, CancellationPointOp>>>
  CancellationPointOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CancellationPointOpAdaptor : public CancellationPointOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CancellationPointOpGenericAdaptor::CancellationPointOpGenericAdaptor;
  CancellationPointOpAdaptor(CancellationPointOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CancellationPointOp : public ::mlir::Op<CancellationPointOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CancellationPointOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CancellationPointOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("cancel_directive")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCancelDirectiveAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCancelDirectiveAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.cancellation_point");
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
  ::mlir::omp::ClauseCancellationConstructTypeAttr getCancelDirectiveAttr() {
    return ::llvm::cast<::mlir::omp::ClauseCancellationConstructTypeAttr>(getProperties().cancel_directive);
  }

  ::mlir::omp::ClauseCancellationConstructType getCancelDirective();
  void setCancelDirectiveAttr(::mlir::omp::ClauseCancellationConstructTypeAttr attr) {
    getProperties().cancel_directive = attr;
  }

  void setCancelDirective(::mlir::omp::ClauseCancellationConstructType attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const CancellationPointOperands &clauses);
  static CancellationPointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const CancellationPointOperands &clauses);
  static CancellationPointOp create(::mlir::ImplicitLocOpBuilder &builder, const CancellationPointOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive);
  static CancellationPointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive);
  static CancellationPointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive);
  static CancellationPointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive);
  static CancellationPointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructTypeAttr cancel_directive);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::omp::ClauseCancellationConstructType cancel_directive);
  static CancellationPointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::omp::ClauseCancellationConstructType cancel_directive);
  static CancellationPointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::omp::ClauseCancellationConstructType cancel_directive);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructType cancel_directive);
  static CancellationPointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructType cancel_directive);
  static CancellationPointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::omp::ClauseCancellationConstructType cancel_directive);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CancellationPointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CancellationPointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CancellationPointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CancellationPointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::CancellationPointOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::CanonicalLoopOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CanonicalLoopOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CanonicalLoopOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.canonical_loop", odsAttrs.getContext());
  }

  CanonicalLoopOpGenericAdaptorBase(CanonicalLoopOp op);

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
class CanonicalLoopOpGenericAdaptor : public detail::CanonicalLoopOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CanonicalLoopOpGenericAdaptorBase;
  static constexpr int odsIndex_tripCount = 0;
  static constexpr int odsIndex_cli = 1;
public:
  CanonicalLoopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CanonicalLoopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CanonicalLoopOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CanonicalLoopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CanonicalLoopOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CanonicalLoopOpGenericAdaptor(RangeT values, const CanonicalLoopOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CanonicalLoopOp, typename = std::enable_if_t<std::is_same_v<LateInst, CanonicalLoopOp>>>
  CanonicalLoopOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTripCount() {
    return (*getODSOperands(0).begin());
  }

  ValueT getCli() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CanonicalLoopOpAdaptor : public CanonicalLoopOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CanonicalLoopOpGenericAdaptor::CanonicalLoopOpGenericAdaptor;
  CanonicalLoopOpAdaptor(CanonicalLoopOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CanonicalLoopOp : public ::mlir::Op<CanonicalLoopOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::omp::LoopTransformationInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CanonicalLoopOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CanonicalLoopOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_tripCount = 0;
  static constexpr int odsIndex_cli = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::omp::LoopTransformationInterface::Trait<CanonicalLoopOp>::getNumApplyees;
  using ::mlir::omp::LoopTransformationInterface::Trait<CanonicalLoopOp>::getNumGeneratees;
  using ::mlir::omp::LoopTransformationInterface::Trait<CanonicalLoopOp>::isApplyee;
  using ::mlir::omp::LoopTransformationInterface::Trait<CanonicalLoopOp>::isGeneratee;
  using ::mlir::OpAsmOpInterface::Trait<CanonicalLoopOp>::getAsmResultNames;
  using ::mlir::OpAsmOpInterface::Trait<CanonicalLoopOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.canonical_loop");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getTripCount() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::omp::CanonicalLoopInfoType> getCli() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::omp::CanonicalLoopInfoType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::omp::CanonicalLoopInfoType>>(*operands.begin());
  }

  ::mlir::OpOperand &getTripCountMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getCliMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tripCount);
  static CanonicalLoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tripCount);
  static CanonicalLoopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tripCount);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value tripCount, ::mlir::Value cli);
  static CanonicalLoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value tripCount, ::mlir::Value cli);
  static CanonicalLoopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value tripCount, ::mlir::Value cli);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value tripCount, /*optional*/::mlir::Value cli);
  static CanonicalLoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value tripCount, /*optional*/::mlir::Value cli);
  static CanonicalLoopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value tripCount, /*optional*/::mlir::Value cli);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CanonicalLoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CanonicalLoopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CanonicalLoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CanonicalLoopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  std::pair<unsigned, unsigned> getApplyeesODSOperandIndexAndLength();
  std::pair<unsigned, unsigned> getGenerateesODSOperandIndexAndLength();
  void getAsmBlockArgumentNames(::mlir::Region&region, ::mlir::OpAsmSetValueNameFn setNameFn);
  void getAsmBlockNames(::mlir::OpAsmSetBlockNameFn setNameFn);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
  ::mlir::Value getInductionVar();
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::CanonicalLoopOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::CriticalDeclareOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CriticalDeclareOpGenericAdaptorBase {
public:
  struct Properties {
    using hintTy = ::mlir::IntegerAttr;
    hintTy hint;

    auto getHint() const {
      auto &propStorage = this->hint;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setHint(const ::mlir::IntegerAttr &propValue) {
      this->hint = propValue;
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
    bool operator==(const Properties &rhs) const {
      return 
        rhs.hint == this->hint &&
        rhs.sym_name == this->sym_name &&
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
  CriticalDeclareOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.critical.declare", odsAttrs.getContext());
  }

  CriticalDeclareOpGenericAdaptorBase(CriticalDeclareOp op);

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
  ::mlir::IntegerAttr getHintAttr();
  uint64_t getHint();
};

} // namespace detail
template <typename RangeT>
class CriticalDeclareOpGenericAdaptor : public detail::CriticalDeclareOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CriticalDeclareOpGenericAdaptorBase;
public:
  CriticalDeclareOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CriticalDeclareOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CriticalDeclareOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CriticalDeclareOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CriticalDeclareOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CriticalDeclareOpGenericAdaptor(RangeT values, const CriticalDeclareOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CriticalDeclareOp, typename = std::enable_if_t<std::is_same_v<LateInst, CriticalDeclareOp>>>
  CriticalDeclareOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CriticalDeclareOpAdaptor : public CriticalDeclareOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CriticalDeclareOpGenericAdaptor::CriticalDeclareOpGenericAdaptor;
  CriticalDeclareOpAdaptor(CriticalDeclareOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CriticalDeclareOp : public ::mlir::Op<CriticalDeclareOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CriticalDeclareOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CriticalDeclareOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("hint"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getHintAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getHintAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.critical.declare");
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
  ::mlir::IntegerAttr getHintAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().hint);
  }

  uint64_t getHint();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setHintAttr(::mlir::IntegerAttr attr) {
    getProperties().hint = attr;
  }

  void setHint(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeHintAttr() {
      auto attr = getProperties().hint;
      getProperties().hint = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const CriticalDeclareOperands &clauses);
  static CriticalDeclareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const CriticalDeclareOperands &clauses);
  static CriticalDeclareOp create(::mlir::ImplicitLocOpBuilder &builder, const CriticalDeclareOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, /*optional*/::mlir::IntegerAttr hint = nullptr);
  static CriticalDeclareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, /*optional*/::mlir::IntegerAttr hint = nullptr);
  static CriticalDeclareOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, /*optional*/::mlir::IntegerAttr hint = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::IntegerAttr hint = nullptr);
  static CriticalDeclareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::IntegerAttr hint = nullptr);
  static CriticalDeclareOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::IntegerAttr hint = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, /*optional*/uint64_t hint = 0);
  static CriticalDeclareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, /*optional*/uint64_t hint = 0);
  static CriticalDeclareOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, /*optional*/uint64_t hint = 0);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/uint64_t hint = 0);
  static CriticalDeclareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/uint64_t hint = 0);
  static CriticalDeclareOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/uint64_t hint = 0);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CriticalDeclareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CriticalDeclareOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CriticalDeclareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CriticalDeclareOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::CriticalDeclareOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::CriticalOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CriticalOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::FlatSymbolRefAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
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
  CriticalOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.critical", odsAttrs.getContext());
  }

  CriticalOpGenericAdaptorBase(CriticalOp op);

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
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class CriticalOpGenericAdaptor : public detail::CriticalOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CriticalOpGenericAdaptorBase;
public:
  CriticalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CriticalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CriticalOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CriticalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CriticalOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CriticalOpGenericAdaptor(RangeT values, const CriticalOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CriticalOp, typename = std::enable_if_t<std::is_same_v<LateInst, CriticalOp>>>
  CriticalOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CriticalOpAdaptor : public CriticalOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CriticalOpGenericAdaptor::CriticalOpGenericAdaptor;
  CriticalOpAdaptor(CriticalOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CriticalOp : public ::mlir::Op<CriticalOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CriticalOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CriticalOpGenericAdaptor<RangeT>;
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
    return ::llvm::StringLiteral("omp.critical");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::FlatSymbolRefAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  void setNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::FlatSymbolRefAttr name);
  static CriticalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::FlatSymbolRefAttr name);
  static CriticalOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::FlatSymbolRefAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::FlatSymbolRefAttr name);
  static CriticalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::FlatSymbolRefAttr name);
  static CriticalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::FlatSymbolRefAttr name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CriticalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CriticalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CriticalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CriticalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::CriticalOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::DeclareMapperInfoOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeclareMapperInfoOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DeclareMapperInfoOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.declare_mapper.info", odsAttrs.getContext());
  }

  DeclareMapperInfoOpGenericAdaptorBase(DeclareMapperInfoOp op);

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
class DeclareMapperInfoOpGenericAdaptor : public detail::DeclareMapperInfoOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeclareMapperInfoOpGenericAdaptorBase;
  static constexpr int odsIndex_map_vars = 0;
public:
  DeclareMapperInfoOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeclareMapperInfoOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeclareMapperInfoOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeclareMapperInfoOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DeclareMapperInfoOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeclareMapperInfoOpGenericAdaptor(RangeT values, const DeclareMapperInfoOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeclareMapperInfoOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeclareMapperInfoOp>>>
  DeclareMapperInfoOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getMapVars() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DeclareMapperInfoOpAdaptor : public DeclareMapperInfoOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeclareMapperInfoOpGenericAdaptor::DeclareMapperInfoOpGenericAdaptor;
  DeclareMapperInfoOpAdaptor(DeclareMapperInfoOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeclareMapperInfoOp : public ::mlir::Op<DeclareMapperInfoOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<DeclareMapperOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator, ::mlir::omp::MapClauseOwningOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeclareMapperInfoOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeclareMapperInfoOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_map_vars = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.declare_mapper.info");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getMapVars() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getMapVarsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange map_vars);
  static DeclareMapperInfoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange map_vars);
  static DeclareMapperInfoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange map_vars);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeclareMapperInfoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeclareMapperInfoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeclareMapperInfoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeclareMapperInfoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  // Override BlockArgOpenMPOpInterface method because `map` clauses have no
  // associated entry block arguments in this operation.
  unsigned numMapBlockArgs() {
    return 0;
  }
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::DeclareMapperInfoOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::DeclareMapperOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeclareMapperOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
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
        rhs.sym_name == this->sym_name &&
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
  DeclareMapperOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.declare_mapper", odsAttrs.getContext());
  }

  DeclareMapperOpGenericAdaptorBase(DeclareMapperOp op);

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
  ::mlir::TypeAttr getTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
    return attr;
  }

  ::mlir::Type getType();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class DeclareMapperOpGenericAdaptor : public detail::DeclareMapperOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeclareMapperOpGenericAdaptorBase;
public:
  DeclareMapperOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeclareMapperOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeclareMapperOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeclareMapperOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DeclareMapperOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeclareMapperOpGenericAdaptor(RangeT values, const DeclareMapperOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeclareMapperOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeclareMapperOp>>>
  DeclareMapperOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DeclareMapperOpAdaptor : public DeclareMapperOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeclareMapperOpGenericAdaptor::DeclareMapperOpGenericAdaptor;
  DeclareMapperOpAdaptor(DeclareMapperOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeclareMapperOp : public ::mlir::Op<DeclareMapperOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::accomp::RecipeInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeclareMapperOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeclareMapperOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name"), ::llvm::StringRef("type")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.declare_mapper");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  ::mlir::TypeAttr getTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
  }

  ::mlir::Type getType();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setTypeAttr(::mlir::TypeAttr attr) {
    getProperties().type = attr;
  }

  void setType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type);
  static DeclareMapperOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type);
  static DeclareMapperOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type);
  static DeclareMapperOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type);
  static DeclareMapperOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::Type type);
  static DeclareMapperOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::Type type);
  static DeclareMapperOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::Type type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type);
  static DeclareMapperOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type);
  static DeclareMapperOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeclareMapperOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeclareMapperOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeclareMapperOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeclareMapperOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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
  /// Get DeclareMapperInfoOp.
  DeclareMapperInfoOp getDeclareMapperInfo(){
    return cast<DeclareMapperInfoOp>(getRegion().getBlocks().front().getTerminator());
  }

  /// Get SymVal block argument
  BlockArgument getSymVal(){
    return getRegion().getArgument(0);
  }
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::DeclareMapperOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::DeclareReductionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeclareReductionOpGenericAdaptorBase {
public:
  struct Properties {
    using byref_element_typeTy = ::mlir::TypeAttr;
    byref_element_typeTy byref_element_type;

    auto getByrefElementType() const {
      auto &propStorage = this->byref_element_type;
      return ::llvm::dyn_cast_or_null<::mlir::TypeAttr>(propStorage);
    }
    void setByrefElementType(const ::mlir::TypeAttr &propValue) {
      this->byref_element_type = propValue;
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
        rhs.byref_element_type == this->byref_element_type &&
        rhs.sym_name == this->sym_name &&
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
  DeclareReductionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.declare_reduction", odsAttrs.getContext());
  }

  DeclareReductionOpGenericAdaptorBase(DeclareReductionOp op);

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
  ::mlir::TypeAttr getTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
    return attr;
  }

  ::mlir::Type getType();
  ::mlir::TypeAttr getByrefElementTypeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::TypeAttr>(getProperties().byref_element_type);
    return attr;
  }

  ::std::optional<::mlir::Type> getByrefElementType();
  ::mlir::Region &getAllocRegion() {
    return *odsRegions[0];
  }

  ::mlir::Region &getInitializerRegion() {
    return *odsRegions[1];
  }

  ::mlir::Region &getReductionRegion() {
    return *odsRegions[2];
  }

  ::mlir::Region &getAtomicReductionRegion() {
    return *odsRegions[3];
  }

  ::mlir::Region &getCleanupRegion() {
    return *odsRegions[4];
  }

  ::mlir::Region &getDataPtrPtrRegion() {
    return *odsRegions[5];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class DeclareReductionOpGenericAdaptor : public detail::DeclareReductionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeclareReductionOpGenericAdaptorBase;
public:
  DeclareReductionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeclareReductionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeclareReductionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeclareReductionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DeclareReductionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeclareReductionOpGenericAdaptor(RangeT values, const DeclareReductionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeclareReductionOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeclareReductionOp>>>
  DeclareReductionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DeclareReductionOpAdaptor : public DeclareReductionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeclareReductionOpGenericAdaptor::DeclareReductionOpGenericAdaptor;
  DeclareReductionOpAdaptor(DeclareReductionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeclareReductionOp : public ::mlir::Op<DeclareReductionOp, ::mlir::OpTrait::NRegions<6>::Impl, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::accomp::RecipeInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeclareReductionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeclareReductionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("byref_element_type"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("type")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getByrefElementTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getByrefElementTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getTypeAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.declare_reduction");
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

  ::mlir::Region &getAllocRegion() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getInitializerRegion() {
    return (*this)->getRegion(1);
  }

  ::mlir::Region &getReductionRegion() {
    return (*this)->getRegion(2);
  }

  ::mlir::Region &getAtomicReductionRegion() {
    return (*this)->getRegion(3);
  }

  ::mlir::Region &getCleanupRegion() {
    return (*this)->getRegion(4);
  }

  ::mlir::Region &getDataPtrPtrRegion() {
    return (*this)->getRegion(5);
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
  ::mlir::TypeAttr getTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
  }

  ::mlir::Type getType();
  ::mlir::TypeAttr getByrefElementTypeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::TypeAttr>(getProperties().byref_element_type);
  }

  ::std::optional<::mlir::Type> getByrefElementType();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setTypeAttr(::mlir::TypeAttr attr) {
    getProperties().type = attr;
  }

  void setType(::mlir::Type attrValue);
  void setByrefElementTypeAttr(::mlir::TypeAttr attr) {
    getProperties().byref_element_type = attr;
  }

  void setByrefElementType(::std::optional<::mlir::Type> attrValue);
  ::mlir::Attribute removeByrefElementTypeAttr() {
      auto attr = getProperties().byref_element_type;
      getProperties().byref_element_type = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::TypeAttr byref_element_type);
  static DeclareReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::TypeAttr byref_element_type);
  static DeclareReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::TypeAttr byref_element_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::TypeAttr byref_element_type);
  static DeclareReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::TypeAttr byref_element_type);
  static DeclareReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::TypeAttr byref_element_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::TypeAttr byref_element_type);
  static DeclareReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::TypeAttr byref_element_type);
  static DeclareReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::TypeAttr byref_element_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::TypeAttr byref_element_type);
  static DeclareReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::TypeAttr byref_element_type);
  static DeclareReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::TypeAttr byref_element_type);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeclareReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeclareReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeclareReductionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeclareReductionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
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
  BlockArgument getAllocMoldArg() {
    auto &region = getAllocRegion();
    return region.empty() ? nullptr : region.getArgument(0);
  }
  BlockArgument getInitializerMoldArg() {
    return getInitializerRegion().getArgument(0);
  }
  BlockArgument getInitializerAllocArg() {
    return getAllocRegion().empty() ?
        nullptr : getInitializerRegion().getArgument(1);
  }
  BlockArgument getReductionLhsArg() {
    return getReductionRegion().getArgument(0);
  }
  BlockArgument getReductionRhsArg() {
    return getReductionRegion().getArgument(1);
  }
  BlockArgument getAtomicReductionLhsArg() {
    auto &region = getAtomicReductionRegion();
    return region.empty() ? nullptr : region.getArgument(0);
  }
  BlockArgument getAtomicReductionRhsArg() {
    auto &region = getAtomicReductionRegion();
    return region.empty() ? nullptr : region.getArgument(1);
  }
  BlockArgument getCleanupAllocArg() {
    auto &region = getCleanupRegion();
    return region.empty() ? nullptr : region.getArgument(0);
  }
  BlockArgument getDataPtrPtrRegionArg() {
    auto &region = getDataPtrPtrRegion();
    return region.empty() ? nullptr : region.getArgument(0);
  }

  PointerLikeType getAccumulatorType() {
    if (getAtomicReductionRegion().empty())
      return {};

    return cast<PointerLikeType>(getAtomicReductionLhsArg().getType());
  }
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::DeclareReductionOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::DeclareSimdOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeclareSimdOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentsTy = ::mlir::ArrayAttr;
    alignmentsTy alignments;

    auto getAlignments() const {
      auto &propStorage = this->alignments;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setAlignments(const ::mlir::ArrayAttr &propValue) {
      this->alignments = propValue;
    }
    using inbranchTy = ::mlir::UnitAttr;
    inbranchTy inbranch;

    auto getInbranch() const {
      auto &propStorage = this->inbranch;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setInbranch(const ::mlir::UnitAttr &propValue) {
      this->inbranch = propValue;
    }
    using linear_var_typesTy = ::mlir::ArrayAttr;
    linear_var_typesTy linear_var_types;

    auto getLinearVarTypes() const {
      auto &propStorage = this->linear_var_types;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setLinearVarTypes(const ::mlir::ArrayAttr &propValue) {
      this->linear_var_types = propValue;
    }
    using notinbranchTy = ::mlir::UnitAttr;
    notinbranchTy notinbranch;

    auto getNotinbranch() const {
      auto &propStorage = this->notinbranch;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNotinbranch(const ::mlir::UnitAttr &propValue) {
      this->notinbranch = propValue;
    }
    using simdlenTy = ::mlir::IntegerAttr;
    simdlenTy simdlen;

    auto getSimdlen() const {
      auto &propStorage = this->simdlen;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setSimdlen(const ::mlir::IntegerAttr &propValue) {
      this->simdlen = propValue;
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
        rhs.alignments == this->alignments &&
        rhs.inbranch == this->inbranch &&
        rhs.linear_var_types == this->linear_var_types &&
        rhs.notinbranch == this->notinbranch &&
        rhs.simdlen == this->simdlen &&
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
  DeclareSimdOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.declare_simd", odsAttrs.getContext());
  }

  DeclareSimdOpGenericAdaptorBase(DeclareSimdOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getAlignmentsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().alignments);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getAlignments();
  ::mlir::UnitAttr getInbranchAttr();
  bool getInbranch();
  ::mlir::ArrayAttr getLinearVarTypesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().linear_var_types);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getLinearVarTypes();
  ::mlir::UnitAttr getNotinbranchAttr();
  bool getNotinbranch();
  ::mlir::IntegerAttr getSimdlenAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().simdlen);
    return attr;
  }

  ::std::optional<uint64_t> getSimdlen();
};

} // namespace detail
template <typename RangeT>
class DeclareSimdOpGenericAdaptor : public detail::DeclareSimdOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeclareSimdOpGenericAdaptorBase;
  static constexpr int odsIndex_aligned_vars = 0;
  static constexpr int odsIndex_linear_vars = 1;
  static constexpr int odsIndex_linear_step_vars = 2;
  static constexpr int odsIndex_uniform_vars = 3;
public:
  DeclareSimdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeclareSimdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DeclareSimdOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeclareSimdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : DeclareSimdOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeclareSimdOpGenericAdaptor(RangeT values, const DeclareSimdOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeclareSimdOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeclareSimdOp>>>
  DeclareSimdOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAlignedVars() {
    return getODSOperands(0);
  }

  RangeT getLinearVars() {
    return getODSOperands(1);
  }

  RangeT getLinearStepVars() {
    return getODSOperands(2);
  }

  RangeT getUniformVars() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DeclareSimdOpAdaptor : public DeclareSimdOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeclareSimdOpGenericAdaptor::DeclareSimdOpGenericAdaptor;
  DeclareSimdOpAdaptor(DeclareSimdOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeclareSimdOp : public ::mlir::Op<DeclareSimdOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeclareSimdOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeclareSimdOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_aligned_vars = 0;
  static constexpr int odsIndex_linear_vars = 1;
  static constexpr int odsIndex_linear_step_vars = 2;
  static constexpr int odsIndex_uniform_vars = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignments"), ::llvm::StringRef("inbranch"), ::llvm::StringRef("linear_var_types"), ::llvm::StringRef("notinbranch"), ::llvm::StringRef("simdlen"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInbranchAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInbranchAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getLinearVarTypesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getLinearVarTypesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getNotinbranchAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getNotinbranchAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getSimdlenAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getSimdlenAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.declare_simd");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAlignedVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getLinearVars() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getLinearStepVars() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getUniformVars() {
    return getODSOperands(3);
  }

  ::mlir::MutableOperandRange getAlignedVarsMutable();
  ::mlir::MutableOperandRange getLinearVarsMutable();
  ::mlir::MutableOperandRange getLinearStepVarsMutable();
  ::mlir::MutableOperandRange getUniformVarsMutable();
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
  ::mlir::ArrayAttr getAlignmentsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().alignments);
  }

  ::std::optional< ::mlir::ArrayAttr > getAlignments();
  ::mlir::UnitAttr getInbranchAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().inbranch);
  }

  bool getInbranch();
  ::mlir::ArrayAttr getLinearVarTypesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().linear_var_types);
  }

  ::std::optional< ::mlir::ArrayAttr > getLinearVarTypes();
  ::mlir::UnitAttr getNotinbranchAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().notinbranch);
  }

  bool getNotinbranch();
  ::mlir::IntegerAttr getSimdlenAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().simdlen);
  }

  ::std::optional<uint64_t> getSimdlen();
  void setAlignmentsAttr(::mlir::ArrayAttr attr) {
    getProperties().alignments = attr;
  }

  void setInbranchAttr(::mlir::UnitAttr attr) {
    getProperties().inbranch = attr;
  }

  void setInbranch(bool attrValue);
  void setLinearVarTypesAttr(::mlir::ArrayAttr attr) {
    getProperties().linear_var_types = attr;
  }

  void setNotinbranchAttr(::mlir::UnitAttr attr) {
    getProperties().notinbranch = attr;
  }

  void setNotinbranch(bool attrValue);
  void setSimdlenAttr(::mlir::IntegerAttr attr) {
    getProperties().simdlen = attr;
  }

  void setSimdlen(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeAlignmentsAttr() {
      auto attr = getProperties().alignments;
      getProperties().alignments = {};
      return attr;
  }

  ::mlir::Attribute removeInbranchAttr() {
      auto attr = getProperties().inbranch;
      getProperties().inbranch = {};
      return attr;
  }

  ::mlir::Attribute removeLinearVarTypesAttr() {
      auto attr = getProperties().linear_var_types;
      getProperties().linear_var_types = {};
      return attr;
  }

  ::mlir::Attribute removeNotinbranchAttr() {
      auto attr = getProperties().notinbranch;
      getProperties().notinbranch = {};
      return attr;
  }

  ::mlir::Attribute removeSimdlenAttr() {
      auto attr = getProperties().simdlen;
      getProperties().simdlen = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const DeclareSimdOperands &clauses);
  static DeclareSimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const DeclareSimdOperands &clauses);
  static DeclareSimdOp create(::mlir::ImplicitLocOpBuilder &builder, const DeclareSimdOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::UnitAttr inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static DeclareSimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::UnitAttr inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static DeclareSimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::UnitAttr inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::UnitAttr inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static DeclareSimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::UnitAttr inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static DeclareSimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::UnitAttr inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/bool inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static DeclareSimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/bool inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static DeclareSimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/bool inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/bool inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static DeclareSimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/bool inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static DeclareSimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/bool inbranch, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool notinbranch, /*optional*/::mlir::IntegerAttr simdlen, ::mlir::ValueRange uniform_vars);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeclareSimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeclareSimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeclareSimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeclareSimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::DeclareSimdOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::DistributeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DistributeOpGenericAdaptorBase {
public:
  struct Properties {
    using dist_schedule_staticTy = ::mlir::UnitAttr;
    dist_schedule_staticTy dist_schedule_static;

    auto getDistScheduleStatic() const {
      auto &propStorage = this->dist_schedule_static;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setDistScheduleStatic(const ::mlir::UnitAttr &propValue) {
      this->dist_schedule_static = propValue;
    }
    using orderTy = ::mlir::omp::ClauseOrderKindAttr;
    orderTy order;

    auto getOrder() const {
      auto &propStorage = this->order;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(propStorage);
    }
    void setOrder(const ::mlir::omp::ClauseOrderKindAttr &propValue) {
      this->order = propValue;
    }
    using order_modTy = ::mlir::omp::OrderModifierAttr;
    order_modTy order_mod;

    auto getOrderMod() const {
      auto &propStorage = this->order_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(propStorage);
    }
    void setOrderMod(const ::mlir::omp::OrderModifierAttr &propValue) {
      this->order_mod = propValue;
    }
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
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
        rhs.dist_schedule_static == this->dist_schedule_static &&
        rhs.order == this->order &&
        rhs.order_mod == this->order_mod &&
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
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
  DistributeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.distribute", odsAttrs.getContext());
  }

  DistributeOpGenericAdaptorBase(DistributeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getDistScheduleStaticAttr();
  bool getDistScheduleStatic();
  ::mlir::omp::ClauseOrderKindAttr getOrderAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(getProperties().order);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseOrderKind> getOrder();
  ::mlir::omp::OrderModifierAttr getOrderModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(getProperties().order_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::OrderModifier> getOrderMod();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class DistributeOpGenericAdaptor : public detail::DistributeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DistributeOpGenericAdaptorBase;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_dist_schedule_chunk_size = 2;
  static constexpr int odsIndex_private_vars = 3;
public:
  DistributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DistributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DistributeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DistributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : DistributeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DistributeOpGenericAdaptor(RangeT values, const DistributeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DistributeOp, typename = std::enable_if_t<std::is_same_v<LateInst, DistributeOp>>>
  DistributeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAllocateVars() {
    return getODSOperands(0);
  }

  RangeT getAllocatorVars() {
    return getODSOperands(1);
  }

  ValueT getDistScheduleChunkSize() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getPrivateVars() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DistributeOpAdaptor : public DistributeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DistributeOpGenericAdaptor::DistributeOpGenericAdaptor;
  DistributeOpAdaptor(DistributeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DistributeOp : public ::mlir::Op<DistributeOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::ComposableOpInterface::Trait, ::mlir::omp::LoopWrapperInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DistributeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DistributeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_dist_schedule_chunk_size = 2;
  static constexpr int odsIndex_private_vars = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::omp::ComposableOpInterface::Trait<DistributeOp>::isComposite;
  using ::mlir::omp::ComposableOpInterface::Trait<DistributeOp>::setComposite;
  using ::mlir::omp::LoopWrapperInterface::Trait<DistributeOp>::getNestedWrapper;
  using ::mlir::omp::LoopWrapperInterface::Trait<DistributeOp>::getWrappedLoop;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dist_schedule_static"), ::llvm::StringRef("order"), ::llvm::StringRef("order_mod"), ::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDistScheduleStaticAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDistScheduleStaticAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOrderAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getOrderAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOrderModAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getOrderModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.distribute");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAllocateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAllocatorVars() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::Type> getDistScheduleChunkSize() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(3);
  }

  ::mlir::MutableOperandRange getAllocateVarsMutable();
  ::mlir::MutableOperandRange getAllocatorVarsMutable();
  ::mlir::MutableOperandRange getDistScheduleChunkSizeMutable();
  ::mlir::MutableOperandRange getPrivateVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::UnitAttr getDistScheduleStaticAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().dist_schedule_static);
  }

  bool getDistScheduleStatic();
  ::mlir::omp::ClauseOrderKindAttr getOrderAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(getProperties().order);
  }

  ::std::optional<::mlir::omp::ClauseOrderKind> getOrder();
  ::mlir::omp::OrderModifierAttr getOrderModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(getProperties().order_mod);
  }

  ::std::optional<::mlir::omp::OrderModifier> getOrderMod();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  void setDistScheduleStaticAttr(::mlir::UnitAttr attr) {
    getProperties().dist_schedule_static = attr;
  }

  void setDistScheduleStatic(bool attrValue);
  void setOrderAttr(::mlir::omp::ClauseOrderKindAttr attr) {
    getProperties().order = attr;
  }

  void setOrder(::std::optional<::mlir::omp::ClauseOrderKind> attrValue);
  void setOrderModAttr(::mlir::omp::OrderModifierAttr attr) {
    getProperties().order_mod = attr;
  }

  void setOrderMod(::std::optional<::mlir::omp::OrderModifier> attrValue);
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  ::mlir::Attribute removeDistScheduleStaticAttr() {
      auto attr = getProperties().dist_schedule_static;
      getProperties().dist_schedule_static = {};
      return attr;
  }

  ::mlir::Attribute removeOrderAttr() {
      auto attr = getProperties().order;
      getProperties().order = {};
      return attr;
  }

  ::mlir::Attribute removeOrderModAttr() {
      auto attr = getProperties().order_mod;
      getProperties().order_mod = {};
      return attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const DistributeOperands &clauses);
  static DistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const DistributeOperands &clauses);
  static DistributeOp create(::mlir::ImplicitLocOpBuilder &builder, const DistributeOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static DistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static DistributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static DistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static DistributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static DistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static DistributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static DistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static DistributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool dist_schedule_static, /*optional*/::mlir::Value dist_schedule_chunk_size, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DistributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DistributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  unsigned getNumAllocateVars() { return getAllocateVars().size(); }
  unsigned getNumAllocatorsVars() { return getAllocatorVars().size(); }



};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::DistributeOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::FlushOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FlushOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FlushOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.flush", odsAttrs.getContext());
  }

  FlushOpGenericAdaptorBase(FlushOp op);

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
class FlushOpGenericAdaptor : public detail::FlushOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FlushOpGenericAdaptorBase;
  static constexpr int odsIndex_varList = 0;
public:
  FlushOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FlushOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : FlushOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FlushOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FlushOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FlushOpGenericAdaptor(RangeT values, const FlushOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FlushOp, typename = std::enable_if_t<std::is_same_v<LateInst, FlushOp>>>
  FlushOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getVarList() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FlushOpAdaptor : public FlushOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FlushOpGenericAdaptor::FlushOpGenericAdaptor;
  FlushOpAdaptor(FlushOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FlushOp : public ::mlir::Op<FlushOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FlushOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FlushOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_varList = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.flush");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getVarList() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getVarListMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange varList);
  static FlushOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange varList);
  static FlushOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange varList);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FlushOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FlushOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FlushOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FlushOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::FlushOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::LoopNestOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoopNestOpGenericAdaptorBase {
public:
  struct Properties {
    using collapse_num_loopsTy = ::mlir::IntegerAttr;
    collapse_num_loopsTy collapse_num_loops;

    auto getCollapseNumLoops() const {
      auto &propStorage = this->collapse_num_loops;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setCollapseNumLoops(const ::mlir::IntegerAttr &propValue) {
      this->collapse_num_loops = propValue;
    }
    using loop_inclusiveTy = ::mlir::UnitAttr;
    loop_inclusiveTy loop_inclusive;

    auto getLoopInclusive() const {
      auto &propStorage = this->loop_inclusive;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setLoopInclusive(const ::mlir::UnitAttr &propValue) {
      this->loop_inclusive = propValue;
    }
    using tile_sizesTy = ::mlir::DenseI64ArrayAttr;
    tile_sizesTy tile_sizes;

    auto getTileSizes() const {
      auto &propStorage = this->tile_sizes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setTileSizes(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->tile_sizes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.collapse_num_loops == this->collapse_num_loops &&
        rhs.loop_inclusive == this->loop_inclusive &&
        rhs.tile_sizes == this->tile_sizes &&
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
  LoopNestOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.loop_nest", odsAttrs.getContext());
  }

  LoopNestOpGenericAdaptorBase(LoopNestOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getCollapseNumLoopsAttr();
  uint64_t getCollapseNumLoops();
  ::mlir::UnitAttr getLoopInclusiveAttr();
  bool getLoopInclusive();
  ::mlir::DenseI64ArrayAttr getTileSizesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().tile_sizes);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<int64_t>> getTileSizes();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class LoopNestOpGenericAdaptor : public detail::LoopNestOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoopNestOpGenericAdaptorBase;
  static constexpr int odsIndex_loop_lower_bounds = 0;
  static constexpr int odsIndex_loop_upper_bounds = 1;
  static constexpr int odsIndex_loop_steps = 2;
public:
  LoopNestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LoopNestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LoopNestOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LoopNestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LoopNestOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LoopNestOpGenericAdaptor(RangeT values, const LoopNestOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LoopNestOp, typename = std::enable_if_t<std::is_same_v<LateInst, LoopNestOp>>>
  LoopNestOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getLoopLowerBounds() {
    return getODSOperands(0);
  }

  RangeT getLoopUpperBounds() {
    return getODSOperands(1);
  }

  RangeT getLoopSteps() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LoopNestOpAdaptor : public LoopNestOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LoopNestOpGenericAdaptor::LoopNestOpGenericAdaptor;
  LoopNestOpAdaptor(LoopNestOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LoopNestOp : public ::mlir::Op<LoopNestOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoopNestOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoopNestOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_loop_lower_bounds = 0;
  static constexpr int odsIndex_loop_upper_bounds = 1;
  static constexpr int odsIndex_loop_steps = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("collapse_num_loops"), ::llvm::StringRef("loop_inclusive"), ::llvm::StringRef("tile_sizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCollapseNumLoopsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCollapseNumLoopsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLoopInclusiveAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLoopInclusiveAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getTileSizesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getTileSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.loop_nest");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getLoopLowerBounds() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getLoopUpperBounds() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getLoopSteps() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getLoopLowerBoundsMutable();
  ::mlir::MutableOperandRange getLoopUpperBoundsMutable();
  ::mlir::MutableOperandRange getLoopStepsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getCollapseNumLoopsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().collapse_num_loops);
  }

  uint64_t getCollapseNumLoops();
  ::mlir::UnitAttr getLoopInclusiveAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().loop_inclusive);
  }

  bool getLoopInclusive();
  ::mlir::DenseI64ArrayAttr getTileSizesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().tile_sizes);
  }

  ::std::optional<::llvm::ArrayRef<int64_t>> getTileSizes();
  void setCollapseNumLoopsAttr(::mlir::IntegerAttr attr) {
    getProperties().collapse_num_loops = attr;
  }

  void setCollapseNumLoops(::std::optional<uint64_t> attrValue);
  void setLoopInclusiveAttr(::mlir::UnitAttr attr) {
    getProperties().loop_inclusive = attr;
  }

  void setLoopInclusive(bool attrValue);
  void setTileSizesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().tile_sizes = attr;
  }

  void setTileSizes(::std::optional<::llvm::ArrayRef<int64_t>> attrValue);
  ::mlir::Attribute removeCollapseNumLoopsAttr() {
      auto attr = getProperties().collapse_num_loops;
      getProperties().collapse_num_loops = {};
      return attr;
  }

  ::mlir::Attribute removeLoopInclusiveAttr() {
      auto attr = getProperties().loop_inclusive;
      getProperties().loop_inclusive = {};
      return attr;
  }

  ::mlir::Attribute removeTileSizesAttr() {
      auto attr = getProperties().tile_sizes;
      getProperties().tile_sizes = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const LoopNestOperands &clauses);
  static LoopNestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const LoopNestOperands &clauses);
  static LoopNestOp create(::mlir::ImplicitLocOpBuilder &builder, const LoopNestOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::IntegerAttr collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/::mlir::UnitAttr loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static LoopNestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::IntegerAttr collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/::mlir::UnitAttr loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static LoopNestOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::IntegerAttr collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/::mlir::UnitAttr loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/::mlir::UnitAttr loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static LoopNestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/::mlir::UnitAttr loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static LoopNestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/::mlir::UnitAttr loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/uint64_t collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/bool loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static LoopNestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/uint64_t collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/bool loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static LoopNestOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/uint64_t collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/bool loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/uint64_t collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/bool loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static LoopNestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/uint64_t collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/bool loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static LoopNestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/uint64_t collapse_num_loops, ::mlir::ValueRange loop_lower_bounds, ::mlir::ValueRange loop_upper_bounds, ::mlir::ValueRange loop_steps, /*optional*/bool loop_inclusive, /*optional*/::mlir::DenseI64ArrayAttr tile_sizes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoopNestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoopNestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoopNestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoopNestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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
  /// Returns the induction variables of the loop nest.
  ArrayRef<BlockArgument> getIVs() { return getRegion().getArguments(); }

  /// Fills a list of wrapper operations around this loop nest. Wrappers
  /// in the resulting vector will be sorted from innermost to outermost.
  void gatherWrappers(SmallVectorImpl<LoopWrapperInterface> &wrappers);


  /// Returns the number of loops in the loop nest.
  unsigned getNumLoops() { return getLoopLowerBounds().size(); }

};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::LoopNestOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::LoopOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoopOpGenericAdaptorBase {
public:
  struct Properties {
    using bind_kindTy = ::mlir::omp::ClauseBindKindAttr;
    bind_kindTy bind_kind;

    auto getBindKind() const {
      auto &propStorage = this->bind_kind;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseBindKindAttr>(propStorage);
    }
    void setBindKind(const ::mlir::omp::ClauseBindKindAttr &propValue) {
      this->bind_kind = propValue;
    }
    using orderTy = ::mlir::omp::ClauseOrderKindAttr;
    orderTy order;

    auto getOrder() const {
      auto &propStorage = this->order;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(propStorage);
    }
    void setOrder(const ::mlir::omp::ClauseOrderKindAttr &propValue) {
      this->order = propValue;
    }
    using order_modTy = ::mlir::omp::OrderModifierAttr;
    order_modTy order_mod;

    auto getOrderMod() const {
      auto &propStorage = this->order_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(propStorage);
    }
    void setOrderMod(const ::mlir::omp::OrderModifierAttr &propValue) {
      this->order_mod = propValue;
    }
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
    }
    using reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    reduction_byrefTy reduction_byref;

    auto getReductionByref() const {
      auto &propStorage = this->reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->reduction_byref = propValue;
    }
    using reduction_modTy = ::mlir::omp::ReductionModifierAttr;
    reduction_modTy reduction_mod;

    auto getReductionMod() const {
      auto &propStorage = this->reduction_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(propStorage);
    }
    void setReductionMod(const ::mlir::omp::ReductionModifierAttr &propValue) {
      this->reduction_mod = propValue;
    }
    using reduction_symsTy = ::mlir::ArrayAttr;
    reduction_symsTy reduction_syms;

    auto getReductionSyms() const {
      auto &propStorage = this->reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->reduction_syms = propValue;
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
        rhs.bind_kind == this->bind_kind &&
        rhs.order == this->order &&
        rhs.order_mod == this->order_mod &&
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
        rhs.reduction_byref == this->reduction_byref &&
        rhs.reduction_mod == this->reduction_mod &&
        rhs.reduction_syms == this->reduction_syms &&
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
  LoopOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.loop", odsAttrs.getContext());
  }

  LoopOpGenericAdaptorBase(LoopOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::omp::ClauseBindKindAttr getBindKindAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseBindKindAttr>(getProperties().bind_kind);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseBindKind> getBindKind();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::omp::ClauseOrderKindAttr getOrderAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(getProperties().order);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseOrderKind> getOrder();
  ::mlir::omp::OrderModifierAttr getOrderModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(getProperties().order_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::OrderModifier> getOrderMod();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class LoopOpGenericAdaptor : public detail::LoopOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoopOpGenericAdaptorBase;
  static constexpr int odsIndex_private_vars = 0;
  static constexpr int odsIndex_reduction_vars = 1;
public:
  LoopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LoopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LoopOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LoopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : LoopOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LoopOpGenericAdaptor(RangeT values, const LoopOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LoopOp, typename = std::enable_if_t<std::is_same_v<LateInst, LoopOp>>>
  LoopOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getPrivateVars() {
    return getODSOperands(0);
  }

  RangeT getReductionVars() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LoopOpAdaptor : public LoopOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LoopOpGenericAdaptor::LoopOpGenericAdaptor;
  LoopOpAdaptor(LoopOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LoopOp : public ::mlir::Op<LoopOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::LoopWrapperInterface::Trait, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoopOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoopOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_private_vars = 0;
  static constexpr int odsIndex_reduction_vars = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::omp::LoopWrapperInterface::Trait<LoopOp>::getNestedWrapper;
  using ::mlir::omp::LoopWrapperInterface::Trait<LoopOp>::getWrappedLoop;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("bind_kind"), ::llvm::StringRef("order"), ::llvm::StringRef("order_mod"), ::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("reduction_byref"), ::llvm::StringRef("reduction_mod"), ::llvm::StringRef("reduction_syms"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBindKindAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBindKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOrderAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getOrderAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOrderModAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getOrderModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getReductionByrefAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getReductionModAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getReductionModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  ::mlir::StringAttr getReductionSymsAttrName() {
    return getAttributeNameForIndex(7);
  }

  static ::mlir::StringAttr getReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 7);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.loop");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getReductionVars() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getPrivateVarsMutable();
  ::mlir::MutableOperandRange getReductionVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::omp::ClauseBindKindAttr getBindKindAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseBindKindAttr>(getProperties().bind_kind);
  }

  ::std::optional<::mlir::omp::ClauseBindKind> getBindKind();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  ::mlir::omp::ClauseOrderKindAttr getOrderAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(getProperties().order);
  }

  ::std::optional<::mlir::omp::ClauseOrderKind> getOrder();
  ::mlir::omp::OrderModifierAttr getOrderModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(getProperties().order_mod);
  }

  ::std::optional<::mlir::omp::OrderModifier> getOrderMod();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  void setBindKindAttr(::mlir::omp::ClauseBindKindAttr attr) {
    getProperties().bind_kind = attr;
  }

  void setBindKind(::std::optional<::mlir::omp::ClauseBindKind> attrValue);
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  void setOrderAttr(::mlir::omp::ClauseOrderKindAttr attr) {
    getProperties().order = attr;
  }

  void setOrder(::std::optional<::mlir::omp::ClauseOrderKind> attrValue);
  void setOrderModAttr(::mlir::omp::OrderModifierAttr attr) {
    getProperties().order_mod = attr;
  }

  void setOrderMod(::std::optional<::mlir::omp::OrderModifier> attrValue);
  void setReductionModAttr(::mlir::omp::ReductionModifierAttr attr) {
    getProperties().reduction_mod = attr;
  }

  void setReductionMod(::std::optional<::mlir::omp::ReductionModifier> attrValue);
  void setReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().reduction_byref = attr;
  }

  void setReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().reduction_syms = attr;
  }

  ::mlir::Attribute removeBindKindAttr() {
      auto attr = getProperties().bind_kind;
      getProperties().bind_kind = {};
      return attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  ::mlir::Attribute removeOrderAttr() {
      auto attr = getProperties().order;
      getProperties().order = {};
      return attr;
  }

  ::mlir::Attribute removeOrderModAttr() {
      auto attr = getProperties().order_mod;
      getProperties().order_mod = {};
      return attr;
  }

  ::mlir::Attribute removeReductionModAttr() {
      auto attr = getProperties().reduction_mod;
      getProperties().reduction_mod = {};
      return attr;
  }

  ::mlir::Attribute removeReductionByrefAttr() {
      auto attr = getProperties().reduction_byref;
      getProperties().reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeReductionSymsAttr() {
      auto attr = getProperties().reduction_syms;
      getProperties().reduction_syms = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const LoopOperands &clauses);
  static LoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const LoopOperands &clauses);
  static LoopOp create(::mlir::ImplicitLocOpBuilder &builder, const LoopOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static LoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static LoopOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static LoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static LoopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static LoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static LoopOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static LoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static LoopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::omp::ClauseBindKindAttr bind_kind, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 8 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Returns the number of reduction variables.
  unsigned getNumReductionVars() { return getReductionVars().size(); }
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::LoopOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::MapBoundsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MapBoundsOpGenericAdaptorBase {
public:
  struct Properties {
    using stride_in_bytesTy = ::mlir::BoolAttr;
    stride_in_bytesTy stride_in_bytes;

    auto getStrideInBytes() const {
      auto &propStorage = this->stride_in_bytes;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setStrideInBytes(const ::mlir::BoolAttr &propValue) {
      this->stride_in_bytes = propValue;
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
        rhs.stride_in_bytes == this->stride_in_bytes &&
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
  MapBoundsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.map.bounds", odsAttrs.getContext());
  }

  MapBoundsOpGenericAdaptorBase(MapBoundsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getStrideInBytesAttr();
  bool getStrideInBytes();
};

} // namespace detail
template <typename RangeT>
class MapBoundsOpGenericAdaptor : public detail::MapBoundsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MapBoundsOpGenericAdaptorBase;
  static constexpr int odsIndex_lower_bound = 0;
  static constexpr int odsIndex_upper_bound = 1;
  static constexpr int odsIndex_extent = 2;
  static constexpr int odsIndex_stride = 3;
  static constexpr int odsIndex_start_idx = 4;
public:
  MapBoundsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MapBoundsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MapBoundsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MapBoundsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : MapBoundsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MapBoundsOpGenericAdaptor(RangeT values, const MapBoundsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MapBoundsOp, typename = std::enable_if_t<std::is_same_v<LateInst, MapBoundsOp>>>
  MapBoundsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLowerBound() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getUpperBound() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getExtent() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getStride() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getStartIdx() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MapBoundsOpAdaptor : public MapBoundsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MapBoundsOpGenericAdaptor::MapBoundsOpGenericAdaptor;
  MapBoundsOpAdaptor(MapBoundsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MapBoundsOp : public ::mlir::Op<MapBoundsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::omp::MapBoundsType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MapBoundsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MapBoundsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lower_bound = 0;
  static constexpr int odsIndex_upper_bound = 1;
  static constexpr int odsIndex_extent = 2;
  static constexpr int odsIndex_stride = 3;
  static constexpr int odsIndex_start_idx = 4;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("stride_in_bytes"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getStrideInBytesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getStrideInBytesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.map.bounds");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getLowerBound() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getUpperBound() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getExtent() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getStride() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getStartIdx() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getLowerBoundMutable();
  ::mlir::MutableOperandRange getUpperBoundMutable();
  ::mlir::MutableOperandRange getExtentMutable();
  ::mlir::MutableOperandRange getStrideMutable();
  ::mlir::MutableOperandRange getStartIdxMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::omp::MapBoundsType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::MapBoundsType>>(*getODSResults(0).begin());
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
  ::mlir::BoolAttr getStrideInBytesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().stride_in_bytes);
  }

  bool getStrideInBytes();
  void setStrideInBytesAttr(::mlir::BoolAttr attr) {
    getProperties().stride_in_bytes = attr;
  }

  void setStrideInBytes(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, ::mlir::BoolAttr stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static MapBoundsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, ::mlir::BoolAttr stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static MapBoundsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, ::mlir::BoolAttr stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, ::mlir::BoolAttr stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static MapBoundsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, ::mlir::BoolAttr stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static MapBoundsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, ::mlir::BoolAttr stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, bool stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static MapBoundsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, bool stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static MapBoundsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, bool stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, bool stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static MapBoundsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, bool stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static MapBoundsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value lower_bound, /*optional*/::mlir::Value upper_bound, /*optional*/::mlir::Value extent, /*optional*/::mlir::Value stride, bool stride_in_bytes, /*optional*/::mlir::Value start_idx);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MapBoundsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MapBoundsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MapBoundsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MapBoundsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
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
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::MapBoundsOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::MapInfoOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MapInfoOpGenericAdaptorBase {
public:
  struct Properties {
    using map_capture_typeTy = ::mlir::omp::VariableCaptureKindAttr;
    map_capture_typeTy map_capture_type;

    auto getMapCaptureType() const {
      auto &propStorage = this->map_capture_type;
      return ::llvm::cast<::mlir::omp::VariableCaptureKindAttr>(propStorage);
    }
    void setMapCaptureType(const ::mlir::omp::VariableCaptureKindAttr &propValue) {
      this->map_capture_type = propValue;
    }
    using map_typeTy = ::mlir::omp::ClauseMapFlagsAttr;
    map_typeTy map_type;

    auto getMapType() const {
      auto &propStorage = this->map_type;
      return ::llvm::cast<::mlir::omp::ClauseMapFlagsAttr>(propStorage);
    }
    void setMapType(const ::mlir::omp::ClauseMapFlagsAttr &propValue) {
      this->map_type = propValue;
    }
    using mapper_idTy = ::mlir::FlatSymbolRefAttr;
    mapper_idTy mapper_id;

    auto getMapperId() const {
      auto &propStorage = this->mapper_id;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setMapperId(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->mapper_id = propValue;
    }
    using members_indexTy = ::mlir::ArrayAttr;
    members_indexTy members_index;

    auto getMembersIndex() const {
      auto &propStorage = this->members_index;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setMembersIndex(const ::mlir::ArrayAttr &propValue) {
      this->members_index = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using partial_mapTy = ::mlir::BoolAttr;
    partial_mapTy partial_map;

    auto getPartialMap() const {
      auto &propStorage = this->partial_map;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setPartialMap(const ::mlir::BoolAttr &propValue) {
      this->partial_map = propValue;
    }
    using var_typeTy = ::mlir::TypeAttr;
    var_typeTy var_type;

    auto getVarType() const {
      auto &propStorage = this->var_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setVarType(const ::mlir::TypeAttr &propValue) {
      this->var_type = propValue;
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
        rhs.map_capture_type == this->map_capture_type &&
        rhs.map_type == this->map_type &&
        rhs.mapper_id == this->mapper_id &&
        rhs.members_index == this->members_index &&
        rhs.name == this->name &&
        rhs.partial_map == this->partial_map &&
        rhs.var_type == this->var_type &&
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
  MapInfoOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.map.info", odsAttrs.getContext());
  }

  MapInfoOpGenericAdaptorBase(MapInfoOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getVarTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().var_type);
    return attr;
  }

  ::mlir::Type getVarType();
  ::mlir::omp::ClauseMapFlagsAttr getMapTypeAttr() {
    auto attr = ::llvm::cast<::mlir::omp::ClauseMapFlagsAttr>(getProperties().map_type);
    return attr;
  }

  ::mlir::omp::ClauseMapFlags getMapType();
  ::mlir::omp::VariableCaptureKindAttr getMapCaptureTypeAttr() {
    auto attr = ::llvm::cast<::mlir::omp::VariableCaptureKindAttr>(getProperties().map_capture_type);
    return attr;
  }

  ::mlir::omp::VariableCaptureKind getMapCaptureType();
  ::mlir::ArrayAttr getMembersIndexAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().members_index);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getMembersIndex();
  ::mlir::FlatSymbolRefAttr getMapperIdAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().mapper_id);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getMapperId();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::BoolAttr getPartialMapAttr();
  bool getPartialMap();
};

} // namespace detail
template <typename RangeT>
class MapInfoOpGenericAdaptor : public detail::MapInfoOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MapInfoOpGenericAdaptorBase;
  static constexpr int odsIndex_var_ptr = 0;
  static constexpr int odsIndex_var_ptr_ptr = 1;
  static constexpr int odsIndex_members = 2;
  static constexpr int odsIndex_bounds = 3;
public:
  MapInfoOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MapInfoOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MapInfoOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MapInfoOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : MapInfoOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MapInfoOpGenericAdaptor(RangeT values, const MapInfoOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MapInfoOp, typename = std::enable_if_t<std::is_same_v<LateInst, MapInfoOp>>>
  MapInfoOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getVarPtr() {
    return (*getODSOperands(0).begin());
  }

  ValueT getVarPtrPtr() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getMembers() {
    return getODSOperands(2);
  }

  RangeT getBounds() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MapInfoOpAdaptor : public MapInfoOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MapInfoOpGenericAdaptor::MapInfoOpGenericAdaptor;
  MapInfoOpAdaptor(MapInfoOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MapInfoOp : public ::mlir::Op<MapInfoOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::omp::PointerLikeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MapInfoOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MapInfoOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_var_ptr = 0;
  static constexpr int odsIndex_var_ptr_ptr = 1;
  static constexpr int odsIndex_members = 2;
  static constexpr int odsIndex_bounds = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("map_capture_type"), ::llvm::StringRef("map_type"), ::llvm::StringRef("mapper_id"), ::llvm::StringRef("members_index"), ::llvm::StringRef("name"), ::llvm::StringRef("partial_map"), ::llvm::StringRef("var_type"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMapCaptureTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMapCaptureTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getMapTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getMapTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getMapperIdAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getMapperIdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getMembersIndexAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getMembersIndexAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getPartialMapAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getPartialMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getVarTypeAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getVarTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.map.info");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::omp::PointerLikeType> getVarPtr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::PointerLikeType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::omp::PointerLikeType> getVarPtrPtr() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::omp::PointerLikeType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::omp::PointerLikeType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getMembers() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getBounds() {
    return getODSOperands(3);
  }

  ::mlir::OpOperand &getVarPtrMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getVarPtrPtrMutable();
  ::mlir::MutableOperandRange getMembersMutable();
  ::mlir::MutableOperandRange getBoundsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::omp::PointerLikeType> getOmpPtr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::PointerLikeType>>(*getODSResults(0).begin());
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
  ::mlir::TypeAttr getVarTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().var_type);
  }

  ::mlir::Type getVarType();
  ::mlir::omp::ClauseMapFlagsAttr getMapTypeAttr() {
    return ::llvm::cast<::mlir::omp::ClauseMapFlagsAttr>(getProperties().map_type);
  }

  ::mlir::omp::ClauseMapFlags getMapType();
  ::mlir::omp::VariableCaptureKindAttr getMapCaptureTypeAttr() {
    return ::llvm::cast<::mlir::omp::VariableCaptureKindAttr>(getProperties().map_capture_type);
  }

  ::mlir::omp::VariableCaptureKind getMapCaptureType();
  ::mlir::ArrayAttr getMembersIndexAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().members_index);
  }

  ::std::optional< ::mlir::ArrayAttr > getMembersIndex();
  ::mlir::FlatSymbolRefAttr getMapperIdAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().mapper_id);
  }

  ::std::optional< ::llvm::StringRef > getMapperId();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::BoolAttr getPartialMapAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().partial_map);
  }

  bool getPartialMap();
  void setVarTypeAttr(::mlir::TypeAttr attr) {
    getProperties().var_type = attr;
  }

  void setVarType(::mlir::Type attrValue);
  void setMapTypeAttr(::mlir::omp::ClauseMapFlagsAttr attr) {
    getProperties().map_type = attr;
  }

  void setMapType(::mlir::omp::ClauseMapFlags attrValue);
  void setMapCaptureTypeAttr(::mlir::omp::VariableCaptureKindAttr attr) {
    getProperties().map_capture_type = attr;
  }

  void setMapCaptureType(::mlir::omp::VariableCaptureKind attrValue);
  void setMembersIndexAttr(::mlir::ArrayAttr attr) {
    getProperties().members_index = attr;
  }

  void setMapperIdAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().mapper_id = attr;
  }

  void setMapperId(::std::optional<::llvm::StringRef> attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  void setPartialMapAttr(::mlir::BoolAttr attr) {
    getProperties().partial_map = attr;
  }

  void setPartialMap(bool attrValue);
  ::mlir::Attribute removeMembersIndexAttr() {
      auto attr = getProperties().members_index;
      getProperties().members_index = {};
      return attr;
  }

  ::mlir::Attribute removeMapperIdAttr() {
      auto attr = getProperties().mapper_id;
      getProperties().mapper_id = {};
      return attr;
  }

  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type omp_ptr, ::mlir::Value var_ptr, ::mlir::TypeAttr var_type, ::mlir::omp::ClauseMapFlagsAttr map_type, ::mlir::omp::VariableCaptureKindAttr map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, ::mlir::BoolAttr partial_map = nullptr);
  static MapInfoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type omp_ptr, ::mlir::Value var_ptr, ::mlir::TypeAttr var_type, ::mlir::omp::ClauseMapFlagsAttr map_type, ::mlir::omp::VariableCaptureKindAttr map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, ::mlir::BoolAttr partial_map = nullptr);
  static MapInfoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type omp_ptr, ::mlir::Value var_ptr, ::mlir::TypeAttr var_type, ::mlir::omp::ClauseMapFlagsAttr map_type, ::mlir::omp::VariableCaptureKindAttr map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, ::mlir::BoolAttr partial_map = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value var_ptr, ::mlir::TypeAttr var_type, ::mlir::omp::ClauseMapFlagsAttr map_type, ::mlir::omp::VariableCaptureKindAttr map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, ::mlir::BoolAttr partial_map = nullptr);
  static MapInfoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value var_ptr, ::mlir::TypeAttr var_type, ::mlir::omp::ClauseMapFlagsAttr map_type, ::mlir::omp::VariableCaptureKindAttr map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, ::mlir::BoolAttr partial_map = nullptr);
  static MapInfoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value var_ptr, ::mlir::TypeAttr var_type, ::mlir::omp::ClauseMapFlagsAttr map_type, ::mlir::omp::VariableCaptureKindAttr map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, ::mlir::BoolAttr partial_map = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type omp_ptr, ::mlir::Value var_ptr, ::mlir::Type var_type, ::mlir::omp::ClauseMapFlags map_type, ::mlir::omp::VariableCaptureKind map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, bool partial_map = false);
  static MapInfoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type omp_ptr, ::mlir::Value var_ptr, ::mlir::Type var_type, ::mlir::omp::ClauseMapFlags map_type, ::mlir::omp::VariableCaptureKind map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, bool partial_map = false);
  static MapInfoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type omp_ptr, ::mlir::Value var_ptr, ::mlir::Type var_type, ::mlir::omp::ClauseMapFlags map_type, ::mlir::omp::VariableCaptureKind map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, bool partial_map = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value var_ptr, ::mlir::Type var_type, ::mlir::omp::ClauseMapFlags map_type, ::mlir::omp::VariableCaptureKind map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, bool partial_map = false);
  static MapInfoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value var_ptr, ::mlir::Type var_type, ::mlir::omp::ClauseMapFlags map_type, ::mlir::omp::VariableCaptureKind map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, bool partial_map = false);
  static MapInfoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value var_ptr, ::mlir::Type var_type, ::mlir::omp::ClauseMapFlags map_type, ::mlir::omp::VariableCaptureKind map_capture_type, /*optional*/::mlir::Value var_ptr_ptr, ::mlir::ValueRange members, /*optional*/::mlir::ArrayAttr members_index, ::mlir::ValueRange bounds, /*optional*/::mlir::FlatSymbolRefAttr mapper_id, /*optional*/::mlir::StringAttr name, bool partial_map = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MapInfoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MapInfoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MapInfoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MapInfoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
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
    assert(index < 7 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::MapInfoOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::MaskedOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MaskedOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MaskedOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.masked", odsAttrs.getContext());
  }

  MaskedOpGenericAdaptorBase(MaskedOp op);

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
class MaskedOpGenericAdaptor : public detail::MaskedOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MaskedOpGenericAdaptorBase;
  static constexpr int odsIndex_filtered_thread_id = 0;
public:
  MaskedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MaskedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MaskedOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MaskedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MaskedOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MaskedOpGenericAdaptor(RangeT values, const MaskedOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MaskedOp, typename = std::enable_if_t<std::is_same_v<LateInst, MaskedOp>>>
  MaskedOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getFilteredThreadId() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MaskedOpAdaptor : public MaskedOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MaskedOpGenericAdaptor::MaskedOpGenericAdaptor;
  MaskedOpAdaptor(MaskedOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MaskedOp : public ::mlir::Op<MaskedOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MaskedOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MaskedOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_filtered_thread_id = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.masked");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getFilteredThreadId() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getFilteredThreadIdMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const MaskedOperands &clauses);
  static MaskedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const MaskedOperands &clauses);
  static MaskedOp create(::mlir::ImplicitLocOpBuilder &builder, const MaskedOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Value filtered_thread_id);
  static MaskedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Value filtered_thread_id);
  static MaskedOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Value filtered_thread_id);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value filtered_thread_id);
  static MaskedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value filtered_thread_id);
  static MaskedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value filtered_thread_id);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MaskedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MaskedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::MaskedOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::MasterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MasterOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MasterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.master", odsAttrs.getContext());
  }

  MasterOpGenericAdaptorBase(MasterOp op);

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
class MasterOpGenericAdaptor : public detail::MasterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MasterOpGenericAdaptorBase;
public:
  MasterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MasterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MasterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MasterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MasterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MasterOpGenericAdaptor(RangeT values, const MasterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MasterOp, typename = std::enable_if_t<std::is_same_v<LateInst, MasterOp>>>
  MasterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MasterOpAdaptor : public MasterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MasterOpGenericAdaptor::MasterOpGenericAdaptor;
  MasterOpAdaptor(MasterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MasterOp : public ::mlir::Op<MasterOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MasterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MasterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.master");
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
  static MasterOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static MasterOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static MasterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static MasterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MasterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MasterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MasterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MasterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::MasterOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::NewCliOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NewCliOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  NewCliOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.new_cli", odsAttrs.getContext());
  }

  NewCliOpGenericAdaptorBase(NewCliOp op);

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
class NewCliOpGenericAdaptor : public detail::NewCliOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NewCliOpGenericAdaptorBase;
public:
  NewCliOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NewCliOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : NewCliOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NewCliOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NewCliOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NewCliOpGenericAdaptor(RangeT values, const NewCliOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NewCliOp, typename = std::enable_if_t<std::is_same_v<LateInst, NewCliOp>>>
  NewCliOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class NewCliOpAdaptor : public NewCliOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NewCliOpGenericAdaptor::NewCliOpGenericAdaptor;
  NewCliOpAdaptor(NewCliOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NewCliOp : public ::mlir::Op<NewCliOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::omp::CanonicalLoopInfoType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NewCliOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NewCliOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<NewCliOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<NewCliOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<NewCliOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.new_cli");
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

  ::mlir::TypedValue<::mlir::omp::CanonicalLoopInfoType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::CanonicalLoopInfoType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static NewCliOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static NewCliOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result);
  static NewCliOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result);
  static NewCliOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static NewCliOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static NewCliOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NewCliOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NewCliOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NewCliOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NewCliOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::NewCliOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::OrderedOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OrderedOpGenericAdaptorBase {
public:
  struct Properties {
    using doacross_depend_typeTy = ::mlir::omp::ClauseDependAttr;
    doacross_depend_typeTy doacross_depend_type;

    auto getDoacrossDependType() const {
      auto &propStorage = this->doacross_depend_type;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseDependAttr>(propStorage);
    }
    void setDoacrossDependType(const ::mlir::omp::ClauseDependAttr &propValue) {
      this->doacross_depend_type = propValue;
    }
    using doacross_num_loopsTy = ::mlir::IntegerAttr;
    doacross_num_loopsTy doacross_num_loops;

    auto getDoacrossNumLoops() const {
      auto &propStorage = this->doacross_num_loops;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setDoacrossNumLoops(const ::mlir::IntegerAttr &propValue) {
      this->doacross_num_loops = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.doacross_depend_type == this->doacross_depend_type &&
        rhs.doacross_num_loops == this->doacross_num_loops &&
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
  OrderedOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.ordered", odsAttrs.getContext());
  }

  OrderedOpGenericAdaptorBase(OrderedOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::omp::ClauseDependAttr getDoacrossDependTypeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseDependAttr>(getProperties().doacross_depend_type);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseDepend> getDoacrossDependType();
  ::mlir::IntegerAttr getDoacrossNumLoopsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().doacross_num_loops);
    return attr;
  }

  ::std::optional<uint64_t> getDoacrossNumLoops();
};

} // namespace detail
template <typename RangeT>
class OrderedOpGenericAdaptor : public detail::OrderedOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OrderedOpGenericAdaptorBase;
  static constexpr int odsIndex_doacross_depend_vars = 0;
public:
  OrderedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OrderedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : OrderedOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OrderedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OrderedOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OrderedOpGenericAdaptor(RangeT values, const OrderedOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OrderedOp, typename = std::enable_if_t<std::is_same_v<LateInst, OrderedOp>>>
  OrderedOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDoacrossDependVars() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class OrderedOpAdaptor : public OrderedOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OrderedOpGenericAdaptor::OrderedOpGenericAdaptor;
  OrderedOpAdaptor(OrderedOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OrderedOp : public ::mlir::Op<OrderedOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OrderedOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OrderedOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_doacross_depend_vars = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("doacross_depend_type"), ::llvm::StringRef("doacross_num_loops")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDoacrossDependTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDoacrossDependTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getDoacrossNumLoopsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getDoacrossNumLoopsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.ordered");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDoacrossDependVars() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getDoacrossDependVarsMutable();
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
  ::mlir::omp::ClauseDependAttr getDoacrossDependTypeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseDependAttr>(getProperties().doacross_depend_type);
  }

  ::std::optional<::mlir::omp::ClauseDepend> getDoacrossDependType();
  ::mlir::IntegerAttr getDoacrossNumLoopsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().doacross_num_loops);
  }

  ::std::optional<uint64_t> getDoacrossNumLoops();
  void setDoacrossDependTypeAttr(::mlir::omp::ClauseDependAttr attr) {
    getProperties().doacross_depend_type = attr;
  }

  void setDoacrossDependType(::std::optional<::mlir::omp::ClauseDepend> attrValue);
  void setDoacrossNumLoopsAttr(::mlir::IntegerAttr attr) {
    getProperties().doacross_num_loops = attr;
  }

  void setDoacrossNumLoops(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeDoacrossDependTypeAttr() {
      auto attr = getProperties().doacross_depend_type;
      getProperties().doacross_depend_type = {};
      return attr;
  }

  ::mlir::Attribute removeDoacrossNumLoopsAttr() {
      auto attr = getProperties().doacross_num_loops;
      getProperties().doacross_num_loops = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const OrderedOperands &clauses);
  static OrderedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const OrderedOperands &clauses);
  static OrderedOp create(::mlir::ImplicitLocOpBuilder &builder, const OrderedOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::omp::ClauseDependAttr doacross_depend_type, /*optional*/::mlir::IntegerAttr doacross_num_loops, ::mlir::ValueRange doacross_depend_vars);
  static OrderedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::omp::ClauseDependAttr doacross_depend_type, /*optional*/::mlir::IntegerAttr doacross_num_loops, ::mlir::ValueRange doacross_depend_vars);
  static OrderedOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::omp::ClauseDependAttr doacross_depend_type, /*optional*/::mlir::IntegerAttr doacross_num_loops, ::mlir::ValueRange doacross_depend_vars);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::omp::ClauseDependAttr doacross_depend_type, /*optional*/::mlir::IntegerAttr doacross_num_loops, ::mlir::ValueRange doacross_depend_vars);
  static OrderedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::omp::ClauseDependAttr doacross_depend_type, /*optional*/::mlir::IntegerAttr doacross_num_loops, ::mlir::ValueRange doacross_depend_vars);
  static OrderedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::omp::ClauseDependAttr doacross_depend_type, /*optional*/::mlir::IntegerAttr doacross_num_loops, ::mlir::ValueRange doacross_depend_vars);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OrderedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OrderedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OrderedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OrderedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::OrderedOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::OrderedRegionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OrderedRegionOpGenericAdaptorBase {
public:
  struct Properties {
    using par_level_simdTy = ::mlir::UnitAttr;
    par_level_simdTy par_level_simd;

    auto getParLevelSimd() const {
      auto &propStorage = this->par_level_simd;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setParLevelSimd(const ::mlir::UnitAttr &propValue) {
      this->par_level_simd = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.par_level_simd == this->par_level_simd &&
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
  OrderedRegionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.ordered.region", odsAttrs.getContext());
  }

  OrderedRegionOpGenericAdaptorBase(OrderedRegionOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getParLevelSimdAttr();
  bool getParLevelSimd();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class OrderedRegionOpGenericAdaptor : public detail::OrderedRegionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OrderedRegionOpGenericAdaptorBase;
public:
  OrderedRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OrderedRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : OrderedRegionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OrderedRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OrderedRegionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OrderedRegionOpGenericAdaptor(RangeT values, const OrderedRegionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OrderedRegionOp, typename = std::enable_if_t<std::is_same_v<LateInst, OrderedRegionOp>>>
  OrderedRegionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class OrderedRegionOpAdaptor : public OrderedRegionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OrderedRegionOpGenericAdaptor::OrderedRegionOpGenericAdaptor;
  OrderedRegionOpAdaptor(OrderedRegionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OrderedRegionOp : public ::mlir::Op<OrderedRegionOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OrderedRegionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OrderedRegionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("par_level_simd")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getParLevelSimdAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getParLevelSimdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.ordered.region");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::UnitAttr getParLevelSimdAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().par_level_simd);
  }

  bool getParLevelSimd();
  void setParLevelSimdAttr(::mlir::UnitAttr attr) {
    getProperties().par_level_simd = attr;
  }

  void setParLevelSimd(bool attrValue);
  ::mlir::Attribute removeParLevelSimdAttr() {
      auto attr = getProperties().par_level_simd;
      getProperties().par_level_simd = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const OrderedRegionOperands &clauses);
  static OrderedRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const OrderedRegionOperands &clauses);
  static OrderedRegionOp create(::mlir::ImplicitLocOpBuilder &builder, const OrderedRegionOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::UnitAttr par_level_simd);
  static OrderedRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::UnitAttr par_level_simd);
  static OrderedRegionOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::UnitAttr par_level_simd);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr par_level_simd);
  static OrderedRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr par_level_simd);
  static OrderedRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr par_level_simd);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/bool par_level_simd = false);
  static OrderedRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/bool par_level_simd = false);
  static OrderedRegionOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/bool par_level_simd = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/bool par_level_simd = false);
  static OrderedRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/bool par_level_simd = false);
  static OrderedRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/bool par_level_simd = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OrderedRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OrderedRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OrderedRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OrderedRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::OrderedRegionOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::ParallelOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ParallelOpGenericAdaptorBase {
public:
  struct Properties {
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
    }
    using proc_bind_kindTy = ::mlir::omp::ClauseProcBindKindAttr;
    proc_bind_kindTy proc_bind_kind;

    auto getProcBindKind() const {
      auto &propStorage = this->proc_bind_kind;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseProcBindKindAttr>(propStorage);
    }
    void setProcBindKind(const ::mlir::omp::ClauseProcBindKindAttr &propValue) {
      this->proc_bind_kind = propValue;
    }
    using reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    reduction_byrefTy reduction_byref;

    auto getReductionByref() const {
      auto &propStorage = this->reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->reduction_byref = propValue;
    }
    using reduction_modTy = ::mlir::omp::ReductionModifierAttr;
    reduction_modTy reduction_mod;

    auto getReductionMod() const {
      auto &propStorage = this->reduction_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(propStorage);
    }
    void setReductionMod(const ::mlir::omp::ReductionModifierAttr &propValue) {
      this->reduction_mod = propValue;
    }
    using reduction_symsTy = ::mlir::ArrayAttr;
    reduction_symsTy reduction_syms;

    auto getReductionSyms() const {
      auto &propStorage = this->reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->reduction_syms = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 6>;
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
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
        rhs.proc_bind_kind == this->proc_bind_kind &&
        rhs.reduction_byref == this->reduction_byref &&
        rhs.reduction_mod == this->reduction_mod &&
        rhs.reduction_syms == this->reduction_syms &&
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
      odsOpName.emplace("omp.parallel", odsAttrs.getContext());
  }

  ParallelOpGenericAdaptorBase(ParallelOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::omp::ClauseProcBindKindAttr getProcBindKindAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseProcBindKindAttr>(getProperties().proc_bind_kind);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseProcBindKind> getProcBindKind();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
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
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_if_expr = 2;
  static constexpr int odsIndex_num_threads_vars = 3;
  static constexpr int odsIndex_private_vars = 4;
  static constexpr int odsIndex_reduction_vars = 5;
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

  RangeT getAllocateVars() {
    return getODSOperands(0);
  }

  RangeT getAllocatorVars() {
    return getODSOperands(1);
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getNumThreadsVars() {
    return getODSOperands(3);
  }

  RangeT getPrivateVars() {
    return getODSOperands(4);
  }

  RangeT getReductionVars() {
    return getODSOperands(5);
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
class ParallelOp : public ::mlir::Op<ParallelOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::omp::ComposableOpInterface::Trait, ::mlir::omp::OutlineableOpenMPOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ParallelOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ParallelOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_if_expr = 2;
  static constexpr int odsIndex_num_threads_vars = 3;
  static constexpr int odsIndex_private_vars = 4;
  static constexpr int odsIndex_reduction_vars = 5;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::omp::ComposableOpInterface::Trait<ParallelOp>::isComposite;
  using ::mlir::omp::ComposableOpInterface::Trait<ParallelOp>::setComposite;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("proc_bind_kind"), ::llvm::StringRef("reduction_byref"), ::llvm::StringRef("reduction_mod"), ::llvm::StringRef("reduction_syms"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getProcBindKindAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getProcBindKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getReductionByrefAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getReductionModAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getReductionModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getReductionSymsAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.parallel");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAllocateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAllocatorVars() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getNumThreadsVars() {
    return getODSOperands(3);
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(4);
  }

  ::mlir::Operation::operand_range getReductionVars() {
    return getODSOperands(5);
  }

  ::mlir::MutableOperandRange getAllocateVarsMutable();
  ::mlir::MutableOperandRange getAllocatorVarsMutable();
  ::mlir::MutableOperandRange getIfExprMutable();
  ::mlir::MutableOperandRange getNumThreadsVarsMutable();
  ::mlir::MutableOperandRange getPrivateVarsMutable();
  ::mlir::MutableOperandRange getReductionVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  ::mlir::omp::ClauseProcBindKindAttr getProcBindKindAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseProcBindKindAttr>(getProperties().proc_bind_kind);
  }

  ::std::optional<::mlir::omp::ClauseProcBindKind> getProcBindKind();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  void setProcBindKindAttr(::mlir::omp::ClauseProcBindKindAttr attr) {
    getProperties().proc_bind_kind = attr;
  }

  void setProcBindKind(::std::optional<::mlir::omp::ClauseProcBindKind> attrValue);
  void setReductionModAttr(::mlir::omp::ReductionModifierAttr attr) {
    getProperties().reduction_mod = attr;
  }

  void setReductionMod(::std::optional<::mlir::omp::ReductionModifier> attrValue);
  void setReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().reduction_byref = attr;
  }

  void setReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().reduction_syms = attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  ::mlir::Attribute removeProcBindKindAttr() {
      auto attr = getProperties().proc_bind_kind;
      getProperties().proc_bind_kind = {};
      return attr;
  }

  ::mlir::Attribute removeReductionModAttr() {
      auto attr = getProperties().reduction_mod;
      getProperties().reduction_mod = {};
      return attr;
  }

  ::mlir::Attribute removeReductionByrefAttr() {
      auto attr = getProperties().reduction_byref;
      getProperties().reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeReductionSymsAttr() {
      auto attr = getProperties().reduction_syms;
      getProperties().reduction_syms = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<NamedAttribute> attributes = {});
  static ParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<NamedAttribute> attributes = {});
  static ParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const ParallelOperands &clauses);
  static ParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const ParallelOperands &clauses);
  static ParallelOp create(::mlir::ImplicitLocOpBuilder &builder, const ParallelOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static ParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static ParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static ParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static ParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static ParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static ParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static ParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static ParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange num_threads_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ClauseProcBindKindAttr proc_bind_kind, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ParallelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ParallelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
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
  unsigned getNumAllocateVars() { return getAllocateVars().size(); }
  unsigned getNumAllocatorsVars() { return getAllocatorVars().size(); }



  /// Returns true if using multi-dimensional values (more than one value)
  bool hasNumThreadsMultiDim() {
    return getNumThreadsVars().size() > 1;
  }

  /// Returns the number of dimensions specified for num_threads
  unsigned getNumThreadsDimsCount() {
    return getNumThreadsVars().size();
  }

  /// Returns the value for a specific dimension index
  /// Index must be less than getNumThreadsVars().size()
  ::mlir::Value getNumThreads(unsigned dim = 0) {
    assert(dim < getNumThreadsDimsCount() &&
           "Num threads index out of bounds");
    return getNumThreadsVars()[dim];
  }




  /// Returns the number of reduction variables.
  unsigned getNumReductionVars() { return getReductionVars().size(); }
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::ParallelOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::PrivateClauseOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PrivateClauseOpGenericAdaptorBase {
public:
  struct Properties {
    using data_sharing_typeTy = ::mlir::omp::DataSharingClauseTypeAttr;
    data_sharing_typeTy data_sharing_type;

    auto getDataSharingType() const {
      auto &propStorage = this->data_sharing_type;
      return ::llvm::cast<::mlir::omp::DataSharingClauseTypeAttr>(propStorage);
    }
    void setDataSharingType(const ::mlir::omp::DataSharingClauseTypeAttr &propValue) {
      this->data_sharing_type = propValue;
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
        rhs.data_sharing_type == this->data_sharing_type &&
        rhs.sym_name == this->sym_name &&
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
  PrivateClauseOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.private", odsAttrs.getContext());
  }

  PrivateClauseOpGenericAdaptorBase(PrivateClauseOp op);

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
  ::mlir::TypeAttr getTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
    return attr;
  }

  ::mlir::Type getType();
  ::mlir::omp::DataSharingClauseTypeAttr getDataSharingTypeAttr() {
    auto attr = ::llvm::cast<::mlir::omp::DataSharingClauseTypeAttr>(getProperties().data_sharing_type);
    return attr;
  }

  ::mlir::omp::DataSharingClauseType getDataSharingType();
  ::mlir::Region &getInitRegion() {
    return *odsRegions[0];
  }

  ::mlir::Region &getCopyRegion() {
    return *odsRegions[1];
  }

  ::mlir::Region &getDeallocRegion() {
    return *odsRegions[2];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class PrivateClauseOpGenericAdaptor : public detail::PrivateClauseOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PrivateClauseOpGenericAdaptorBase;
public:
  PrivateClauseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PrivateClauseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PrivateClauseOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PrivateClauseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PrivateClauseOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PrivateClauseOpGenericAdaptor(RangeT values, const PrivateClauseOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PrivateClauseOp, typename = std::enable_if_t<std::is_same_v<LateInst, PrivateClauseOp>>>
  PrivateClauseOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PrivateClauseOpAdaptor : public PrivateClauseOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PrivateClauseOpGenericAdaptor::PrivateClauseOpGenericAdaptor;
  PrivateClauseOpAdaptor(PrivateClauseOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PrivateClauseOp : public ::mlir::Op<PrivateClauseOp, ::mlir::OpTrait::NRegions<3>::Impl, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::accomp::RecipeInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PrivateClauseOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PrivateClauseOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("data_sharing_type"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("type")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDataSharingTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDataSharingTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getTypeAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.private");
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

  ::mlir::Region &getInitRegion() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getCopyRegion() {
    return (*this)->getRegion(1);
  }

  ::mlir::Region &getDeallocRegion() {
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  ::mlir::TypeAttr getTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
  }

  ::mlir::Type getType();
  ::mlir::omp::DataSharingClauseTypeAttr getDataSharingTypeAttr() {
    return ::llvm::cast<::mlir::omp::DataSharingClauseTypeAttr>(getProperties().data_sharing_type);
  }

  ::mlir::omp::DataSharingClauseType getDataSharingType();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setTypeAttr(::mlir::TypeAttr attr) {
    getProperties().type = attr;
  }

  void setType(::mlir::Type attrValue);
  void setDataSharingTypeAttr(::mlir::omp::DataSharingClauseTypeAttr attr) {
    getProperties().data_sharing_type = attr;
  }

  void setDataSharingType(::mlir::omp::DataSharingClauseType attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange result, StringAttr sym_name, TypeAttr type);
  static PrivateClauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange result, StringAttr sym_name, TypeAttr type);
  static PrivateClauseOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange result, StringAttr sym_name, TypeAttr type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, ::mlir::omp::DataSharingClauseTypeAttr data_sharing_type);
  static PrivateClauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, ::mlir::omp::DataSharingClauseTypeAttr data_sharing_type);
  static PrivateClauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, ::mlir::omp::DataSharingClauseTypeAttr data_sharing_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, ::mlir::omp::DataSharingClauseTypeAttr data_sharing_type);
  static PrivateClauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, ::mlir::omp::DataSharingClauseTypeAttr data_sharing_type);
  static PrivateClauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, ::mlir::omp::DataSharingClauseTypeAttr data_sharing_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::Type type, ::mlir::omp::DataSharingClauseType data_sharing_type);
  static PrivateClauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::Type type, ::mlir::omp::DataSharingClauseType data_sharing_type);
  static PrivateClauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::Type type, ::mlir::omp::DataSharingClauseType data_sharing_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, ::mlir::omp::DataSharingClauseType data_sharing_type);
  static PrivateClauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, ::mlir::omp::DataSharingClauseType data_sharing_type);
  static PrivateClauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, ::mlir::omp::DataSharingClauseType data_sharing_type);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrivateClauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrivateClauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrivateClauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrivateClauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
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
  BlockArgument getInitMoldArg() {
    auto &region = getInitRegion();
    return region.empty() ? nullptr : region.getArgument(0);
  }
  BlockArgument getInitPrivateArg() {
    auto &region = getInitRegion();
    return region.empty() ? nullptr : region.getArgument(1);
  }
  BlockArgument getCopyMoldArg() {
    auto &region = getCopyRegion();
    return region.empty() ? nullptr : region.getArgument(0);
  }
  BlockArgument getCopyPrivateArg() {
    auto &region = getCopyRegion();
    return region.empty() ? nullptr : region.getArgument(1);
  }
  BlockArgument getDeallocMoldArg() {
    auto &region = getDeallocRegion();
    return region.empty() ? nullptr : region.getArgument(0);
  }

  /// Returns true if the init region might read from the mold argument
  bool initReadsFromMold() {
    BlockArgument moldArg = getInitMoldArg();
    return moldArg && !moldArg.use_empty();
  }

  /// Returns true if any region of this privatizer might read from the mold
  /// argument
  bool readsFromMold() {
    return initReadsFromMold() || !getCopyRegion().empty();
  }

  /// needsMap returns true if the value being privatized should additionally
  /// be mapped to the target region using a MapInfoOp. This is most common
  /// when an allocatable is privatized. In such cases, the descriptor is used
  /// in privatization and needs to be mapped on to the device. The use of
  /// firstprivate also creates the need to map the host variable to the device.
  bool needsMap() {
    return readsFromMold();
  }

  /// Get the type for arguments to nested regions. This should
  /// generally be either the same as getType() or some pointer
  /// type (pointing to the type allocated by this op).
  /// This method will return Type{nullptr} if there are no nested
  /// regions.
  Type getArgType() {
    for (Region *region : getRegions())
      for (Type ty : region->getArgumentTypes())
        return ty;
    return nullptr;
  }
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::PrivateClauseOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::ScanOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ScanOpGenericAdaptorBase {
public:
  struct Properties {
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
  ScanOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.scan", odsAttrs.getContext());
  }

  ScanOpGenericAdaptorBase(ScanOp op);

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
class ScanOpGenericAdaptor : public detail::ScanOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ScanOpGenericAdaptorBase;
  static constexpr int odsIndex_inclusive_vars = 0;
  static constexpr int odsIndex_exclusive_vars = 1;
public:
  ScanOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ScanOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ScanOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ScanOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ScanOpGenericAdaptor(values, attrs, Properties{}, {}) {}

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

  RangeT getInclusiveVars() {
    return getODSOperands(0);
  }

  RangeT getExclusiveVars() {
    return getODSOperands(1);
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
class ScanOp : public ::mlir::Op<ScanOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ScanOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ScanOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inclusive_vars = 0;
  static constexpr int odsIndex_exclusive_vars = 1;
  using Properties = FoldAdaptor::Properties;
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
    return ::llvm::StringLiteral("omp.scan");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInclusiveVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getExclusiveVars() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getInclusiveVarsMutable();
  ::mlir::MutableOperandRange getExclusiveVarsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const ScanOperands &clauses);
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const ScanOperands &clauses);
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, const ScanOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inclusive_vars, ::mlir::ValueRange exclusive_vars);
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inclusive_vars, ::mlir::ValueRange exclusive_vars);
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inclusive_vars, ::mlir::ValueRange exclusive_vars);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inclusive_vars, ::mlir::ValueRange exclusive_vars);
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inclusive_vars, ::mlir::ValueRange exclusive_vars);
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inclusive_vars, ::mlir::ValueRange exclusive_vars);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScanOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScanOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    return {};
  }

public:
  bool hasInclusiveVars() {
    return !getInclusiveVars().empty();
  }


  bool hasExclusiveVars() {
    return !getExclusiveVars().empty();
  }
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::ScanOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::SectionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SectionOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SectionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.section", odsAttrs.getContext());
  }

  SectionOpGenericAdaptorBase(SectionOp op);

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
class SectionOpGenericAdaptor : public detail::SectionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SectionOpGenericAdaptorBase;
public:
  SectionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SectionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SectionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SectionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SectionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SectionOpGenericAdaptor(RangeT values, const SectionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SectionOp, typename = std::enable_if_t<std::is_same_v<LateInst, SectionOp>>>
  SectionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SectionOpAdaptor : public SectionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SectionOpGenericAdaptor::SectionOpGenericAdaptor;
  SectionOpAdaptor(SectionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SectionOp : public ::mlir::Op<SectionOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<SectionsOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SectionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SectionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.section");
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
  static SectionOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static SectionOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static SectionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static SectionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SectionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SectionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SectionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SectionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  // Override BlockArgOpenMPOpInterface methods based on the parent
  // omp.sections operation. Only forward-declare here because SectionsOp is
  // not completely defined at this point.
  OperandRange getPrivateVars();
  OperandRange getReductionVars();
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::SectionOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::SectionsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SectionsOpGenericAdaptorBase {
public:
  struct Properties {
    using nowaitTy = ::mlir::UnitAttr;
    nowaitTy nowait;

    auto getNowait() const {
      auto &propStorage = this->nowait;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNowait(const ::mlir::UnitAttr &propValue) {
      this->nowait = propValue;
    }
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
    }
    using reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    reduction_byrefTy reduction_byref;

    auto getReductionByref() const {
      auto &propStorage = this->reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->reduction_byref = propValue;
    }
    using reduction_modTy = ::mlir::omp::ReductionModifierAttr;
    reduction_modTy reduction_mod;

    auto getReductionMod() const {
      auto &propStorage = this->reduction_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(propStorage);
    }
    void setReductionMod(const ::mlir::omp::ReductionModifierAttr &propValue) {
      this->reduction_mod = propValue;
    }
    using reduction_symsTy = ::mlir::ArrayAttr;
    reduction_symsTy reduction_syms;

    auto getReductionSyms() const {
      auto &propStorage = this->reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->reduction_syms = propValue;
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
        rhs.nowait == this->nowait &&
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
        rhs.reduction_byref == this->reduction_byref &&
        rhs.reduction_mod == this->reduction_mod &&
        rhs.reduction_syms == this->reduction_syms &&
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
  SectionsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.sections", odsAttrs.getContext());
  }

  SectionsOpGenericAdaptorBase(SectionsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getNowaitAttr();
  bool getNowait();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SectionsOpGenericAdaptor : public detail::SectionsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SectionsOpGenericAdaptorBase;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_private_vars = 2;
  static constexpr int odsIndex_reduction_vars = 3;
public:
  SectionsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SectionsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SectionsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SectionsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : SectionsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SectionsOpGenericAdaptor(RangeT values, const SectionsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SectionsOp, typename = std::enable_if_t<std::is_same_v<LateInst, SectionsOp>>>
  SectionsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAllocateVars() {
    return getODSOperands(0);
  }

  RangeT getAllocatorVars() {
    return getODSOperands(1);
  }

  RangeT getPrivateVars() {
    return getODSOperands(2);
  }

  RangeT getReductionVars() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SectionsOpAdaptor : public SectionsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SectionsOpGenericAdaptor::SectionsOpGenericAdaptor;
  SectionsOpAdaptor(SectionsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SectionsOp : public ::mlir::Op<SectionsOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SectionsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SectionsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_private_vars = 2;
  static constexpr int odsIndex_reduction_vars = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("nowait"), ::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("reduction_byref"), ::llvm::StringRef("reduction_mod"), ::llvm::StringRef("reduction_syms"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNowaitAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNowaitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getReductionByrefAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getReductionModAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getReductionModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getReductionSymsAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.sections");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAllocateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAllocatorVars() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getReductionVars() {
    return getODSOperands(3);
  }

  ::mlir::MutableOperandRange getAllocateVarsMutable();
  ::mlir::MutableOperandRange getAllocatorVarsMutable();
  ::mlir::MutableOperandRange getPrivateVarsMutable();
  ::mlir::MutableOperandRange getReductionVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::UnitAttr getNowaitAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nowait);
  }

  bool getNowait();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  void setNowaitAttr(::mlir::UnitAttr attr) {
    getProperties().nowait = attr;
  }

  void setNowait(bool attrValue);
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  void setReductionModAttr(::mlir::omp::ReductionModifierAttr attr) {
    getProperties().reduction_mod = attr;
  }

  void setReductionMod(::std::optional<::mlir::omp::ReductionModifier> attrValue);
  void setReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().reduction_byref = attr;
  }

  void setReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().reduction_syms = attr;
  }

  ::mlir::Attribute removeNowaitAttr() {
      auto attr = getProperties().nowait;
      getProperties().nowait = {};
      return attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  ::mlir::Attribute removeReductionModAttr() {
      auto attr = getProperties().reduction_mod;
      getProperties().reduction_mod = {};
      return attr;
  }

  ::mlir::Attribute removeReductionByrefAttr() {
      auto attr = getProperties().reduction_byref;
      getProperties().reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeReductionSymsAttr() {
      auto attr = getProperties().reduction_syms;
      getProperties().reduction_syms = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const SectionsOperands &clauses);
  static SectionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const SectionsOperands &clauses);
  static SectionsOp create(::mlir::ImplicitLocOpBuilder &builder, const SectionsOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static SectionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static SectionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static SectionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static SectionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static SectionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static SectionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static SectionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static SectionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SectionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SectionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SectionsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SectionsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
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
  unsigned getNumAllocateVars() { return getAllocateVars().size(); }
  unsigned getNumAllocatorsVars() { return getAllocatorVars().size(); }




  /// Returns the number of reduction variables.
  unsigned getNumReductionVars() { return getReductionVars().size(); }
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::SectionsOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::SimdOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SimdOpGenericAdaptorBase {
public:
  struct Properties {
    using alignmentsTy = ::mlir::ArrayAttr;
    alignmentsTy alignments;

    auto getAlignments() const {
      auto &propStorage = this->alignments;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setAlignments(const ::mlir::ArrayAttr &propValue) {
      this->alignments = propValue;
    }
    using linear_var_typesTy = ::mlir::ArrayAttr;
    linear_var_typesTy linear_var_types;

    auto getLinearVarTypes() const {
      auto &propStorage = this->linear_var_types;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setLinearVarTypes(const ::mlir::ArrayAttr &propValue) {
      this->linear_var_types = propValue;
    }
    using orderTy = ::mlir::omp::ClauseOrderKindAttr;
    orderTy order;

    auto getOrder() const {
      auto &propStorage = this->order;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(propStorage);
    }
    void setOrder(const ::mlir::omp::ClauseOrderKindAttr &propValue) {
      this->order = propValue;
    }
    using order_modTy = ::mlir::omp::OrderModifierAttr;
    order_modTy order_mod;

    auto getOrderMod() const {
      auto &propStorage = this->order_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(propStorage);
    }
    void setOrderMod(const ::mlir::omp::OrderModifierAttr &propValue) {
      this->order_mod = propValue;
    }
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
    }
    using reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    reduction_byrefTy reduction_byref;

    auto getReductionByref() const {
      auto &propStorage = this->reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->reduction_byref = propValue;
    }
    using reduction_modTy = ::mlir::omp::ReductionModifierAttr;
    reduction_modTy reduction_mod;

    auto getReductionMod() const {
      auto &propStorage = this->reduction_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(propStorage);
    }
    void setReductionMod(const ::mlir::omp::ReductionModifierAttr &propValue) {
      this->reduction_mod = propValue;
    }
    using reduction_symsTy = ::mlir::ArrayAttr;
    reduction_symsTy reduction_syms;

    auto getReductionSyms() const {
      auto &propStorage = this->reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->reduction_syms = propValue;
    }
    using safelenTy = ::mlir::IntegerAttr;
    safelenTy safelen;

    auto getSafelen() const {
      auto &propStorage = this->safelen;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setSafelen(const ::mlir::IntegerAttr &propValue) {
      this->safelen = propValue;
    }
    using simdlenTy = ::mlir::IntegerAttr;
    simdlenTy simdlen;

    auto getSimdlen() const {
      auto &propStorage = this->simdlen;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setSimdlen(const ::mlir::IntegerAttr &propValue) {
      this->simdlen = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 7>;
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
        rhs.alignments == this->alignments &&
        rhs.linear_var_types == this->linear_var_types &&
        rhs.order == this->order &&
        rhs.order_mod == this->order_mod &&
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
        rhs.reduction_byref == this->reduction_byref &&
        rhs.reduction_mod == this->reduction_mod &&
        rhs.reduction_syms == this->reduction_syms &&
        rhs.safelen == this->safelen &&
        rhs.simdlen == this->simdlen &&
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
  SimdOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.simd", odsAttrs.getContext());
  }

  SimdOpGenericAdaptorBase(SimdOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getAlignmentsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().alignments);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getAlignments();
  ::mlir::ArrayAttr getLinearVarTypesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().linear_var_types);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getLinearVarTypes();
  ::mlir::omp::ClauseOrderKindAttr getOrderAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(getProperties().order);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseOrderKind> getOrder();
  ::mlir::omp::OrderModifierAttr getOrderModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(getProperties().order_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::OrderModifier> getOrderMod();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  ::mlir::IntegerAttr getSafelenAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().safelen);
    return attr;
  }

  ::std::optional<uint64_t> getSafelen();
  ::mlir::IntegerAttr getSimdlenAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().simdlen);
    return attr;
  }

  ::std::optional<uint64_t> getSimdlen();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SimdOpGenericAdaptor : public detail::SimdOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SimdOpGenericAdaptorBase;
  static constexpr int odsIndex_aligned_vars = 0;
  static constexpr int odsIndex_if_expr = 1;
  static constexpr int odsIndex_linear_vars = 2;
  static constexpr int odsIndex_linear_step_vars = 3;
  static constexpr int odsIndex_nontemporal_vars = 4;
  static constexpr int odsIndex_private_vars = 5;
  static constexpr int odsIndex_reduction_vars = 6;
public:
  SimdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SimdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SimdOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SimdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : SimdOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SimdOpGenericAdaptor(RangeT values, const SimdOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SimdOp, typename = std::enable_if_t<std::is_same_v<LateInst, SimdOp>>>
  SimdOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAlignedVars() {
    return getODSOperands(0);
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getLinearVars() {
    return getODSOperands(2);
  }

  RangeT getLinearStepVars() {
    return getODSOperands(3);
  }

  RangeT getNontemporalVars() {
    return getODSOperands(4);
  }

  RangeT getPrivateVars() {
    return getODSOperands(5);
  }

  RangeT getReductionVars() {
    return getODSOperands(6);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SimdOpAdaptor : public SimdOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SimdOpGenericAdaptor::SimdOpGenericAdaptor;
  SimdOpAdaptor(SimdOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SimdOp : public ::mlir::Op<SimdOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::ComposableOpInterface::Trait, ::mlir::omp::LoopWrapperInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SimdOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SimdOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_aligned_vars = 0;
  static constexpr int odsIndex_if_expr = 1;
  static constexpr int odsIndex_linear_vars = 2;
  static constexpr int odsIndex_linear_step_vars = 3;
  static constexpr int odsIndex_nontemporal_vars = 4;
  static constexpr int odsIndex_private_vars = 5;
  static constexpr int odsIndex_reduction_vars = 6;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::omp::ComposableOpInterface::Trait<SimdOp>::isComposite;
  using ::mlir::omp::ComposableOpInterface::Trait<SimdOp>::setComposite;
  using ::mlir::omp::LoopWrapperInterface::Trait<SimdOp>::getNestedWrapper;
  using ::mlir::omp::LoopWrapperInterface::Trait<SimdOp>::getWrappedLoop;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("alignments"), ::llvm::StringRef("linear_var_types"), ::llvm::StringRef("order"), ::llvm::StringRef("order_mod"), ::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("reduction_byref"), ::llvm::StringRef("reduction_mod"), ::llvm::StringRef("reduction_syms"), ::llvm::StringRef("safelen"), ::llvm::StringRef("simdlen"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlignmentsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlignmentsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLinearVarTypesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLinearVarTypesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOrderAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getOrderAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOrderModAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getOrderModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getReductionByrefAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  ::mlir::StringAttr getReductionModAttrName() {
    return getAttributeNameForIndex(7);
  }

  static ::mlir::StringAttr getReductionModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 7);
  }

  ::mlir::StringAttr getReductionSymsAttrName() {
    return getAttributeNameForIndex(8);
  }

  static ::mlir::StringAttr getReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 8);
  }

  ::mlir::StringAttr getSafelenAttrName() {
    return getAttributeNameForIndex(9);
  }

  static ::mlir::StringAttr getSafelenAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 9);
  }

  ::mlir::StringAttr getSimdlenAttrName() {
    return getAttributeNameForIndex(10);
  }

  static ::mlir::StringAttr getSimdlenAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 10);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.simd");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAlignedVars() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getLinearVars() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getLinearStepVars() {
    return getODSOperands(3);
  }

  ::mlir::Operation::operand_range getNontemporalVars() {
    return getODSOperands(4);
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(5);
  }

  ::mlir::Operation::operand_range getReductionVars() {
    return getODSOperands(6);
  }

  ::mlir::MutableOperandRange getAlignedVarsMutable();
  ::mlir::MutableOperandRange getIfExprMutable();
  ::mlir::MutableOperandRange getLinearVarsMutable();
  ::mlir::MutableOperandRange getLinearStepVarsMutable();
  ::mlir::MutableOperandRange getNontemporalVarsMutable();
  ::mlir::MutableOperandRange getPrivateVarsMutable();
  ::mlir::MutableOperandRange getReductionVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getAlignmentsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().alignments);
  }

  ::std::optional< ::mlir::ArrayAttr > getAlignments();
  ::mlir::ArrayAttr getLinearVarTypesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().linear_var_types);
  }

  ::std::optional< ::mlir::ArrayAttr > getLinearVarTypes();
  ::mlir::omp::ClauseOrderKindAttr getOrderAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(getProperties().order);
  }

  ::std::optional<::mlir::omp::ClauseOrderKind> getOrder();
  ::mlir::omp::OrderModifierAttr getOrderModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(getProperties().order_mod);
  }

  ::std::optional<::mlir::omp::OrderModifier> getOrderMod();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  ::mlir::IntegerAttr getSafelenAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().safelen);
  }

  ::std::optional<uint64_t> getSafelen();
  ::mlir::IntegerAttr getSimdlenAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().simdlen);
  }

  ::std::optional<uint64_t> getSimdlen();
  void setAlignmentsAttr(::mlir::ArrayAttr attr) {
    getProperties().alignments = attr;
  }

  void setLinearVarTypesAttr(::mlir::ArrayAttr attr) {
    getProperties().linear_var_types = attr;
  }

  void setOrderAttr(::mlir::omp::ClauseOrderKindAttr attr) {
    getProperties().order = attr;
  }

  void setOrder(::std::optional<::mlir::omp::ClauseOrderKind> attrValue);
  void setOrderModAttr(::mlir::omp::OrderModifierAttr attr) {
    getProperties().order_mod = attr;
  }

  void setOrderMod(::std::optional<::mlir::omp::OrderModifier> attrValue);
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  void setReductionModAttr(::mlir::omp::ReductionModifierAttr attr) {
    getProperties().reduction_mod = attr;
  }

  void setReductionMod(::std::optional<::mlir::omp::ReductionModifier> attrValue);
  void setReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().reduction_byref = attr;
  }

  void setReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().reduction_syms = attr;
  }

  void setSafelenAttr(::mlir::IntegerAttr attr) {
    getProperties().safelen = attr;
  }

  void setSafelen(::std::optional<uint64_t> attrValue);
  void setSimdlenAttr(::mlir::IntegerAttr attr) {
    getProperties().simdlen = attr;
  }

  void setSimdlen(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeAlignmentsAttr() {
      auto attr = getProperties().alignments;
      getProperties().alignments = {};
      return attr;
  }

  ::mlir::Attribute removeLinearVarTypesAttr() {
      auto attr = getProperties().linear_var_types;
      getProperties().linear_var_types = {};
      return attr;
  }

  ::mlir::Attribute removeOrderAttr() {
      auto attr = getProperties().order;
      getProperties().order = {};
      return attr;
  }

  ::mlir::Attribute removeOrderModAttr() {
      auto attr = getProperties().order_mod;
      getProperties().order_mod = {};
      return attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  ::mlir::Attribute removeReductionModAttr() {
      auto attr = getProperties().reduction_mod;
      getProperties().reduction_mod = {};
      return attr;
  }

  ::mlir::Attribute removeReductionByrefAttr() {
      auto attr = getProperties().reduction_byref;
      getProperties().reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeReductionSymsAttr() {
      auto attr = getProperties().reduction_syms;
      getProperties().reduction_syms = {};
      return attr;
  }

  ::mlir::Attribute removeSafelenAttr() {
      auto attr = getProperties().safelen;
      getProperties().safelen = {};
      return attr;
  }

  ::mlir::Attribute removeSimdlenAttr() {
      auto attr = getProperties().simdlen;
      getProperties().simdlen = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const SimdOperands &clauses);
  static SimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const SimdOperands &clauses);
  static SimdOp create(::mlir::ImplicitLocOpBuilder &builder, const SimdOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static SimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static SimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static SimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static SimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static SimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static SimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static SimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static SimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange aligned_vars, /*optional*/::mlir::ArrayAttr alignments, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, ::mlir::ValueRange nontemporal_vars, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::IntegerAttr safelen, /*optional*/::mlir::IntegerAttr simdlen);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 11 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Returns the number of reduction variables.
  unsigned getNumReductionVars() { return getReductionVars().size(); }


};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::SimdOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::SingleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SingleOpGenericAdaptorBase {
public:
  struct Properties {
    using copyprivate_symsTy = ::mlir::ArrayAttr;
    copyprivate_symsTy copyprivate_syms;

    auto getCopyprivateSyms() const {
      auto &propStorage = this->copyprivate_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setCopyprivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->copyprivate_syms = propValue;
    }
    using nowaitTy = ::mlir::UnitAttr;
    nowaitTy nowait;

    auto getNowait() const {
      auto &propStorage = this->nowait;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNowait(const ::mlir::UnitAttr &propValue) {
      this->nowait = propValue;
    }
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
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
        rhs.copyprivate_syms == this->copyprivate_syms &&
        rhs.nowait == this->nowait &&
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
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
  SingleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.single", odsAttrs.getContext());
  }

  SingleOpGenericAdaptorBase(SingleOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getCopyprivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().copyprivate_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getCopyprivateSyms();
  ::mlir::UnitAttr getNowaitAttr();
  bool getNowait();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SingleOpGenericAdaptor : public detail::SingleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SingleOpGenericAdaptorBase;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_copyprivate_vars = 2;
  static constexpr int odsIndex_private_vars = 3;
public:
  SingleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SingleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SingleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SingleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : SingleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SingleOpGenericAdaptor(RangeT values, const SingleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SingleOp, typename = std::enable_if_t<std::is_same_v<LateInst, SingleOp>>>
  SingleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAllocateVars() {
    return getODSOperands(0);
  }

  RangeT getAllocatorVars() {
    return getODSOperands(1);
  }

  RangeT getCopyprivateVars() {
    return getODSOperands(2);
  }

  RangeT getPrivateVars() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SingleOpAdaptor : public SingleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SingleOpGenericAdaptor::SingleOpGenericAdaptor;
  SingleOpAdaptor(SingleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SingleOp : public ::mlir::Op<SingleOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SingleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SingleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_copyprivate_vars = 2;
  static constexpr int odsIndex_private_vars = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("copyprivate_syms"), ::llvm::StringRef("nowait"), ::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCopyprivateSymsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCopyprivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNowaitAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNowaitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.single");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAllocateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAllocatorVars() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getCopyprivateVars() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(3);
  }

  ::mlir::MutableOperandRange getAllocateVarsMutable();
  ::mlir::MutableOperandRange getAllocatorVarsMutable();
  ::mlir::MutableOperandRange getCopyprivateVarsMutable();
  ::mlir::MutableOperandRange getPrivateVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getCopyprivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().copyprivate_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getCopyprivateSyms();
  ::mlir::UnitAttr getNowaitAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nowait);
  }

  bool getNowait();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  void setCopyprivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().copyprivate_syms = attr;
  }

  void setNowaitAttr(::mlir::UnitAttr attr) {
    getProperties().nowait = attr;
  }

  void setNowait(bool attrValue);
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  ::mlir::Attribute removeCopyprivateSymsAttr() {
      auto attr = getProperties().copyprivate_syms;
      getProperties().copyprivate_syms = {};
      return attr;
  }

  ::mlir::Attribute removeNowaitAttr() {
      auto attr = getProperties().nowait;
      getProperties().nowait = {};
      return attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const SingleOperands &clauses);
  static SingleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const SingleOperands &clauses);
  static SingleOp create(::mlir::ImplicitLocOpBuilder &builder, const SingleOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static SingleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static SingleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static SingleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static SingleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static SingleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static SingleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static SingleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static SingleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange copyprivate_vars, /*optional*/::mlir::ArrayAttr copyprivate_syms, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SingleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SingleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SingleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SingleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  unsigned getNumAllocateVars() { return getAllocateVars().size(); }
  unsigned getNumAllocatorsVars() { return getAllocatorVars().size(); }



};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::SingleOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TargetAllocMemOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TargetAllocMemOpGenericAdaptorBase {
public:
  struct Properties {
    using bindc_nameTy = ::mlir::StringAttr;
    bindc_nameTy bindc_name;

    auto getBindcName() const {
      auto &propStorage = this->bindc_name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setBindcName(const ::mlir::StringAttr &propValue) {
      this->bindc_name = propValue;
    }
    using in_typeTy = ::mlir::TypeAttr;
    in_typeTy in_type;

    auto getInType() const {
      auto &propStorage = this->in_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setInType(const ::mlir::TypeAttr &propValue) {
      this->in_type = propValue;
    }
    using uniq_nameTy = ::mlir::StringAttr;
    uniq_nameTy uniq_name;

    auto getUniqName() const {
      auto &propStorage = this->uniq_name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setUniqName(const ::mlir::StringAttr &propValue) {
      this->uniq_name = propValue;
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
        rhs.bindc_name == this->bindc_name &&
        rhs.in_type == this->in_type &&
        rhs.uniq_name == this->uniq_name &&
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
  TargetAllocMemOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.target_allocmem", odsAttrs.getContext());
  }

  TargetAllocMemOpGenericAdaptorBase(TargetAllocMemOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getInTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().in_type);
    return attr;
  }

  ::mlir::Type getInType();
  ::mlir::StringAttr getUniqNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().uniq_name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getUniqName();
  ::mlir::StringAttr getBindcNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().bindc_name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getBindcName();
};

} // namespace detail
template <typename RangeT>
class TargetAllocMemOpGenericAdaptor : public detail::TargetAllocMemOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TargetAllocMemOpGenericAdaptorBase;
  static constexpr int odsIndex_device = 0;
  static constexpr int odsIndex_typeparams = 1;
  static constexpr int odsIndex_shape = 2;
public:
  TargetAllocMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TargetAllocMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TargetAllocMemOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TargetAllocMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TargetAllocMemOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TargetAllocMemOpGenericAdaptor(RangeT values, const TargetAllocMemOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TargetAllocMemOp, typename = std::enable_if_t<std::is_same_v<LateInst, TargetAllocMemOp>>>
  TargetAllocMemOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDevice() {
    return (*getODSOperands(0).begin());
  }

  RangeT getTypeparams() {
    return getODSOperands(1);
  }

  RangeT getShape() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TargetAllocMemOpAdaptor : public TargetAllocMemOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TargetAllocMemOpGenericAdaptor::TargetAllocMemOpGenericAdaptor;
  TargetAllocMemOpAdaptor(TargetAllocMemOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TargetAllocMemOp : public ::mlir::Op<TargetAllocMemOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TargetAllocMemOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TargetAllocMemOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_device = 0;
  static constexpr int odsIndex_typeparams = 1;
  static constexpr int odsIndex_shape = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("bindc_name"), ::llvm::StringRef("in_type"), ::llvm::StringRef("uniq_name"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBindcNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBindcNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getUniqNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getUniqNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.target_allocmem");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDevice() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getTypeparams() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getShape() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getDeviceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getTypeparamsMutable();
  ::mlir::MutableOperandRange getShapeMutable();
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
  ::mlir::TypeAttr getInTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().in_type);
  }

  ::mlir::Type getInType();
  ::mlir::StringAttr getUniqNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().uniq_name);
  }

  ::std::optional< ::llvm::StringRef > getUniqName();
  ::mlir::StringAttr getBindcNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().bindc_name);
  }

  ::std::optional< ::llvm::StringRef > getBindcName();
  void setInTypeAttr(::mlir::TypeAttr attr) {
    getProperties().in_type = attr;
  }

  void setInType(::mlir::Type attrValue);
  void setUniqNameAttr(::mlir::StringAttr attr) {
    getProperties().uniq_name = attr;
  }

  void setUniqName(::std::optional<::llvm::StringRef> attrValue);
  void setBindcNameAttr(::mlir::StringAttr attr) {
    getProperties().bindc_name = attr;
  }

  void setBindcName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeUniqNameAttr() {
      auto attr = getProperties().uniq_name;
      getProperties().uniq_name = {};
      return attr;
  }

  ::mlir::Attribute removeBindcNameAttr() {
      auto attr = getProperties().bindc_name;
      getProperties().bindc_name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value device, ::mlir::TypeAttr in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static TargetAllocMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value device, ::mlir::TypeAttr in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static TargetAllocMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value device, ::mlir::TypeAttr in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value device, ::mlir::TypeAttr in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static TargetAllocMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value device, ::mlir::TypeAttr in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static TargetAllocMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value device, ::mlir::TypeAttr in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value device, ::mlir::Type in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static TargetAllocMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value device, ::mlir::Type in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static TargetAllocMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value device, ::mlir::Type in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value device, ::mlir::Type in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static TargetAllocMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value device, ::mlir::Type in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static TargetAllocMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value device, ::mlir::Type in_type, /*optional*/::mlir::StringAttr uniq_name, /*optional*/::mlir::StringAttr bindc_name, ::mlir::ValueRange typeparams, ::mlir::ValueRange shape);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetAllocMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetAllocMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetAllocMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetAllocMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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
  mlir::Type getAllocatedType();
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TargetAllocMemOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TargetDataOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TargetDataOpGenericAdaptorBase {
public:
  struct Properties {
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
  TargetDataOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.target_data", odsAttrs.getContext());
  }

  TargetDataOpGenericAdaptorBase(TargetDataOp op);

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
class TargetDataOpGenericAdaptor : public detail::TargetDataOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TargetDataOpGenericAdaptorBase;
  static constexpr int odsIndex_device = 0;
  static constexpr int odsIndex_if_expr = 1;
  static constexpr int odsIndex_map_vars = 2;
  static constexpr int odsIndex_use_device_addr_vars = 3;
  static constexpr int odsIndex_use_device_ptr_vars = 4;
public:
  TargetDataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TargetDataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TargetDataOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TargetDataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TargetDataOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TargetDataOpGenericAdaptor(RangeT values, const TargetDataOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TargetDataOp, typename = std::enable_if_t<std::is_same_v<LateInst, TargetDataOp>>>
  TargetDataOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDevice() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getMapVars() {
    return getODSOperands(2);
  }

  RangeT getUseDeviceAddrVars() {
    return getODSOperands(3);
  }

  RangeT getUseDevicePtrVars() {
    return getODSOperands(4);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TargetDataOpAdaptor : public TargetDataOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TargetDataOpGenericAdaptor::TargetDataOpGenericAdaptor;
  TargetDataOpAdaptor(TargetDataOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TargetDataOp : public ::mlir::Op<TargetDataOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::MapClauseOwningOpInterface::Trait, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TargetDataOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TargetDataOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_device = 0;
  static constexpr int odsIndex_if_expr = 1;
  static constexpr int odsIndex_map_vars = 2;
  static constexpr int odsIndex_use_device_addr_vars = 3;
  static constexpr int odsIndex_use_device_ptr_vars = 4;
  using Properties = FoldAdaptor::Properties;
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
    return ::llvm::StringLiteral("omp.target_data");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDevice() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getMapVars() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getUseDeviceAddrVars() {
    return getODSOperands(3);
  }

  ::mlir::Operation::operand_range getUseDevicePtrVars() {
    return getODSOperands(4);
  }

  ::mlir::MutableOperandRange getDeviceMutable();
  ::mlir::MutableOperandRange getIfExprMutable();
  ::mlir::MutableOperandRange getMapVarsMutable();
  ::mlir::MutableOperandRange getUseDeviceAddrVarsMutable();
  ::mlir::MutableOperandRange getUseDevicePtrVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const TargetDataOperands &clauses);
  static TargetDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const TargetDataOperands &clauses);
  static TargetDataOp create(::mlir::ImplicitLocOpBuilder &builder, const TargetDataOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, ::mlir::ValueRange use_device_addr_vars, ::mlir::ValueRange use_device_ptr_vars);
  static TargetDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, ::mlir::ValueRange use_device_addr_vars, ::mlir::ValueRange use_device_ptr_vars);
  static TargetDataOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, ::mlir::ValueRange use_device_addr_vars, ::mlir::ValueRange use_device_ptr_vars);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, ::mlir::ValueRange use_device_addr_vars, ::mlir::ValueRange use_device_ptr_vars);
  static TargetDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, ::mlir::ValueRange use_device_addr_vars, ::mlir::ValueRange use_device_ptr_vars);
  static TargetDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, ::mlir::ValueRange use_device_addr_vars, ::mlir::ValueRange use_device_ptr_vars);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    return {};
  }

public:
  // Override BlockArgOpenMPOpInterface method because `map` clauses have no
  // associated entry block arguments in this operation.
  unsigned numMapBlockArgs() {
    return 0;
  }




};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TargetDataOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TargetEnterDataOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TargetEnterDataOpGenericAdaptorBase {
public:
  struct Properties {
    using depend_kindsTy = ::mlir::ArrayAttr;
    depend_kindsTy depend_kinds;

    auto getDependKinds() const {
      auto &propStorage = this->depend_kinds;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setDependKinds(const ::mlir::ArrayAttr &propValue) {
      this->depend_kinds = propValue;
    }
    using nowaitTy = ::mlir::UnitAttr;
    nowaitTy nowait;

    auto getNowait() const {
      auto &propStorage = this->nowait;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNowait(const ::mlir::UnitAttr &propValue) {
      this->nowait = propValue;
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
        rhs.depend_kinds == this->depend_kinds &&
        rhs.nowait == this->nowait &&
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
  TargetEnterDataOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.target_enter_data", odsAttrs.getContext());
  }

  TargetEnterDataOpGenericAdaptorBase(TargetEnterDataOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getDependKindsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::UnitAttr getNowaitAttr();
  bool getNowait();
};

} // namespace detail
template <typename RangeT>
class TargetEnterDataOpGenericAdaptor : public detail::TargetEnterDataOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TargetEnterDataOpGenericAdaptorBase;
  static constexpr int odsIndex_depend_vars = 0;
  static constexpr int odsIndex_device = 1;
  static constexpr int odsIndex_if_expr = 2;
  static constexpr int odsIndex_map_vars = 3;
public:
  TargetEnterDataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TargetEnterDataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TargetEnterDataOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TargetEnterDataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TargetEnterDataOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TargetEnterDataOpGenericAdaptor(RangeT values, const TargetEnterDataOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TargetEnterDataOp, typename = std::enable_if_t<std::is_same_v<LateInst, TargetEnterDataOp>>>
  TargetEnterDataOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDependVars() {
    return getODSOperands(0);
  }

  ValueT getDevice() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getMapVars() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TargetEnterDataOpAdaptor : public TargetEnterDataOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TargetEnterDataOpGenericAdaptor::TargetEnterDataOpGenericAdaptor;
  TargetEnterDataOpAdaptor(TargetEnterDataOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TargetEnterDataOp : public ::mlir::Op<TargetEnterDataOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::MapClauseOwningOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TargetEnterDataOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TargetEnterDataOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_depend_vars = 0;
  static constexpr int odsIndex_device = 1;
  static constexpr int odsIndex_if_expr = 2;
  static constexpr int odsIndex_map_vars = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("depend_kinds"), ::llvm::StringRef("nowait"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDependKindsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDependKindsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNowaitAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNowaitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.target_enter_data");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDependVars() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDevice() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getMapVars() {
    return getODSOperands(3);
  }

  ::mlir::MutableOperandRange getDependVarsMutable();
  ::mlir::MutableOperandRange getDeviceMutable();
  ::mlir::MutableOperandRange getIfExprMutable();
  ::mlir::MutableOperandRange getMapVarsMutable();
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
  ::mlir::ArrayAttr getDependKindsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::UnitAttr getNowaitAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nowait);
  }

  bool getNowait();
  void setDependKindsAttr(::mlir::ArrayAttr attr) {
    getProperties().depend_kinds = attr;
  }

  void setNowaitAttr(::mlir::UnitAttr attr) {
    getProperties().nowait = attr;
  }

  void setNowait(bool attrValue);
  ::mlir::Attribute removeDependKindsAttr() {
      auto attr = getProperties().depend_kinds;
      getProperties().depend_kinds = {};
      return attr;
  }

  ::mlir::Attribute removeNowaitAttr() {
      auto attr = getProperties().nowait;
      getProperties().nowait = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const TargetEnterExitUpdateDataOperands &clauses);
  static TargetEnterDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const TargetEnterExitUpdateDataOperands &clauses);
  static TargetEnterDataOp create(::mlir::ImplicitLocOpBuilder &builder, const TargetEnterExitUpdateDataOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetEnterDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetEnterDataOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetEnterDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetEnterDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetEnterDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetEnterDataOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetEnterDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetEnterDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetEnterDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetEnterDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetEnterDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetEnterDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Override BlockArgOpenMPOpInterface method because `map` clauses have no
  // associated entry block arguments in this operation.
  unsigned numMapBlockArgs() {
    return 0;
  }




};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TargetEnterDataOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TargetExitDataOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TargetExitDataOpGenericAdaptorBase {
public:
  struct Properties {
    using depend_kindsTy = ::mlir::ArrayAttr;
    depend_kindsTy depend_kinds;

    auto getDependKinds() const {
      auto &propStorage = this->depend_kinds;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setDependKinds(const ::mlir::ArrayAttr &propValue) {
      this->depend_kinds = propValue;
    }
    using nowaitTy = ::mlir::UnitAttr;
    nowaitTy nowait;

    auto getNowait() const {
      auto &propStorage = this->nowait;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNowait(const ::mlir::UnitAttr &propValue) {
      this->nowait = propValue;
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
        rhs.depend_kinds == this->depend_kinds &&
        rhs.nowait == this->nowait &&
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
  TargetExitDataOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.target_exit_data", odsAttrs.getContext());
  }

  TargetExitDataOpGenericAdaptorBase(TargetExitDataOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getDependKindsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::UnitAttr getNowaitAttr();
  bool getNowait();
};

} // namespace detail
template <typename RangeT>
class TargetExitDataOpGenericAdaptor : public detail::TargetExitDataOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TargetExitDataOpGenericAdaptorBase;
  static constexpr int odsIndex_depend_vars = 0;
  static constexpr int odsIndex_device = 1;
  static constexpr int odsIndex_if_expr = 2;
  static constexpr int odsIndex_map_vars = 3;
public:
  TargetExitDataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TargetExitDataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TargetExitDataOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TargetExitDataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TargetExitDataOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TargetExitDataOpGenericAdaptor(RangeT values, const TargetExitDataOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TargetExitDataOp, typename = std::enable_if_t<std::is_same_v<LateInst, TargetExitDataOp>>>
  TargetExitDataOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDependVars() {
    return getODSOperands(0);
  }

  ValueT getDevice() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getMapVars() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TargetExitDataOpAdaptor : public TargetExitDataOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TargetExitDataOpGenericAdaptor::TargetExitDataOpGenericAdaptor;
  TargetExitDataOpAdaptor(TargetExitDataOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TargetExitDataOp : public ::mlir::Op<TargetExitDataOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::MapClauseOwningOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TargetExitDataOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TargetExitDataOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_depend_vars = 0;
  static constexpr int odsIndex_device = 1;
  static constexpr int odsIndex_if_expr = 2;
  static constexpr int odsIndex_map_vars = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("depend_kinds"), ::llvm::StringRef("nowait"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDependKindsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDependKindsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNowaitAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNowaitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.target_exit_data");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDependVars() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDevice() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getMapVars() {
    return getODSOperands(3);
  }

  ::mlir::MutableOperandRange getDependVarsMutable();
  ::mlir::MutableOperandRange getDeviceMutable();
  ::mlir::MutableOperandRange getIfExprMutable();
  ::mlir::MutableOperandRange getMapVarsMutable();
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
  ::mlir::ArrayAttr getDependKindsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::UnitAttr getNowaitAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nowait);
  }

  bool getNowait();
  void setDependKindsAttr(::mlir::ArrayAttr attr) {
    getProperties().depend_kinds = attr;
  }

  void setNowaitAttr(::mlir::UnitAttr attr) {
    getProperties().nowait = attr;
  }

  void setNowait(bool attrValue);
  ::mlir::Attribute removeDependKindsAttr() {
      auto attr = getProperties().depend_kinds;
      getProperties().depend_kinds = {};
      return attr;
  }

  ::mlir::Attribute removeNowaitAttr() {
      auto attr = getProperties().nowait;
      getProperties().nowait = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const TargetEnterExitUpdateDataOperands &clauses);
  static TargetExitDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const TargetEnterExitUpdateDataOperands &clauses);
  static TargetExitDataOp create(::mlir::ImplicitLocOpBuilder &builder, const TargetEnterExitUpdateDataOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetExitDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetExitDataOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetExitDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetExitDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetExitDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetExitDataOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetExitDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetExitDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetExitDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetExitDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetExitDataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetExitDataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Override BlockArgOpenMPOpInterface method because `map` clauses have no
  // associated entry block arguments in this operation.
  unsigned numMapBlockArgs() {
    return 0;
  }




};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TargetExitDataOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TargetFreeMemOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TargetFreeMemOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TargetFreeMemOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.target_freemem", odsAttrs.getContext());
  }

  TargetFreeMemOpGenericAdaptorBase(TargetFreeMemOp op);

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
class TargetFreeMemOpGenericAdaptor : public detail::TargetFreeMemOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TargetFreeMemOpGenericAdaptorBase;
  static constexpr int odsIndex_device = 0;
  static constexpr int odsIndex_heapref = 1;
public:
  TargetFreeMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TargetFreeMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TargetFreeMemOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TargetFreeMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TargetFreeMemOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TargetFreeMemOpGenericAdaptor(RangeT values, const TargetFreeMemOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TargetFreeMemOp, typename = std::enable_if_t<std::is_same_v<LateInst, TargetFreeMemOp>>>
  TargetFreeMemOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDevice() {
    return (*getODSOperands(0).begin());
  }

  ValueT getHeapref() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TargetFreeMemOpAdaptor : public TargetFreeMemOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TargetFreeMemOpGenericAdaptor::TargetFreeMemOpGenericAdaptor;
  TargetFreeMemOpAdaptor(TargetFreeMemOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TargetFreeMemOp : public ::mlir::Op<TargetFreeMemOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TargetFreeMemOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TargetFreeMemOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_device = 0;
  static constexpr int odsIndex_heapref = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.target_freemem");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDevice() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getHeapref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getDeviceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getHeaprefMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value device, ::mlir::Value heapref);
  static TargetFreeMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value device, ::mlir::Value heapref);
  static TargetFreeMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value device, ::mlir::Value heapref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value device, ::mlir::Value heapref);
  static TargetFreeMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value device, ::mlir::Value heapref);
  static TargetFreeMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value device, ::mlir::Value heapref);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetFreeMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetFreeMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetFreeMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetFreeMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TargetFreeMemOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TargetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TargetOpGenericAdaptorBase {
public:
  struct Properties {
    using bareTy = ::mlir::UnitAttr;
    bareTy bare;

    auto getBare() const {
      auto &propStorage = this->bare;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setBare(const ::mlir::UnitAttr &propValue) {
      this->bare = propValue;
    }
    using depend_kindsTy = ::mlir::ArrayAttr;
    depend_kindsTy depend_kinds;

    auto getDependKinds() const {
      auto &propStorage = this->depend_kinds;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setDependKinds(const ::mlir::ArrayAttr &propValue) {
      this->depend_kinds = propValue;
    }
    using in_reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    in_reduction_byrefTy in_reduction_byref;

    auto getInReductionByref() const {
      auto &propStorage = this->in_reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setInReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->in_reduction_byref = propValue;
    }
    using in_reduction_symsTy = ::mlir::ArrayAttr;
    in_reduction_symsTy in_reduction_syms;

    auto getInReductionSyms() const {
      auto &propStorage = this->in_reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setInReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->in_reduction_syms = propValue;
    }
    using nowaitTy = ::mlir::UnitAttr;
    nowaitTy nowait;

    auto getNowait() const {
      auto &propStorage = this->nowait;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNowait(const ::mlir::UnitAttr &propValue) {
      this->nowait = propValue;
    }
    using private_mapsTy = ::mlir::DenseI64ArrayAttr;
    private_mapsTy private_maps;

    auto getPrivateMaps() const {
      auto &propStorage = this->private_maps;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setPrivateMaps(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->private_maps = propValue;
    }
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 12>;
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
        rhs.bare == this->bare &&
        rhs.depend_kinds == this->depend_kinds &&
        rhs.in_reduction_byref == this->in_reduction_byref &&
        rhs.in_reduction_syms == this->in_reduction_syms &&
        rhs.nowait == this->nowait &&
        rhs.private_maps == this->private_maps &&
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
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
  TargetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.target", odsAttrs.getContext());
  }

  TargetOpGenericAdaptorBase(TargetOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getBareAttr();
  bool getBare();
  ::mlir::ArrayAttr getDependKindsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::DenseBoolArrayAttr getInReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().in_reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getInReductionByref();
  ::mlir::ArrayAttr getInReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().in_reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getInReductionSyms();
  ::mlir::UnitAttr getNowaitAttr();
  bool getNowait();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::DenseI64ArrayAttr getPrivateMapsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().private_maps);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<int64_t>> getPrivateMaps();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class TargetOpGenericAdaptor : public detail::TargetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TargetOpGenericAdaptorBase;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_depend_vars = 2;
  static constexpr int odsIndex_device = 3;
  static constexpr int odsIndex_has_device_addr_vars = 4;
  static constexpr int odsIndex_host_eval_vars = 5;
  static constexpr int odsIndex_if_expr = 6;
  static constexpr int odsIndex_in_reduction_vars = 7;
  static constexpr int odsIndex_is_device_ptr_vars = 8;
  static constexpr int odsIndex_map_vars = 9;
  static constexpr int odsIndex_private_vars = 10;
  static constexpr int odsIndex_thread_limit_vars = 11;
public:
  TargetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TargetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TargetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TargetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TargetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TargetOpGenericAdaptor(RangeT values, const TargetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TargetOp, typename = std::enable_if_t<std::is_same_v<LateInst, TargetOp>>>
  TargetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAllocateVars() {
    return getODSOperands(0);
  }

  RangeT getAllocatorVars() {
    return getODSOperands(1);
  }

  RangeT getDependVars() {
    return getODSOperands(2);
  }

  ValueT getDevice() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getHasDeviceAddrVars() {
    return getODSOperands(4);
  }

  RangeT getHostEvalVars() {
    return getODSOperands(5);
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getInReductionVars() {
    return getODSOperands(7);
  }

  RangeT getIsDevicePtrVars() {
    return getODSOperands(8);
  }

  RangeT getMapVars() {
    return getODSOperands(9);
  }

  RangeT getPrivateVars() {
    return getODSOperands(10);
  }

  RangeT getThreadLimitVars() {
    return getODSOperands(11);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TargetOpAdaptor : public TargetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TargetOpGenericAdaptor::TargetOpGenericAdaptor;
  TargetOpAdaptor(TargetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TargetOp : public ::mlir::Op<TargetOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::BlockArgOpenMPOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::omp::OutlineableOpenMPOpInterface::Trait, ::mlir::omp::MapClauseOwningOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TargetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TargetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_depend_vars = 2;
  static constexpr int odsIndex_device = 3;
  static constexpr int odsIndex_has_device_addr_vars = 4;
  static constexpr int odsIndex_host_eval_vars = 5;
  static constexpr int odsIndex_if_expr = 6;
  static constexpr int odsIndex_in_reduction_vars = 7;
  static constexpr int odsIndex_is_device_ptr_vars = 8;
  static constexpr int odsIndex_map_vars = 9;
  static constexpr int odsIndex_private_vars = 10;
  static constexpr int odsIndex_thread_limit_vars = 11;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("bare"), ::llvm::StringRef("depend_kinds"), ::llvm::StringRef("in_reduction_byref"), ::llvm::StringRef("in_reduction_syms"), ::llvm::StringRef("nowait"), ::llvm::StringRef("private_maps"), ::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBareAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBareAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getDependKindsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getDependKindsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getInReductionByrefAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getInReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getInReductionSymsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getInReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getNowaitAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getNowaitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getPrivateMapsAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getPrivateMapsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(7);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 7);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.target");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAllocateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAllocatorVars() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getDependVars() {
    return getODSOperands(2);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDevice() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getHasDeviceAddrVars() {
    return getODSOperands(4);
  }

  ::mlir::Operation::operand_range getHostEvalVars() {
    return getODSOperands(5);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getInReductionVars() {
    return getODSOperands(7);
  }

  ::mlir::Operation::operand_range getIsDevicePtrVars() {
    return getODSOperands(8);
  }

  ::mlir::Operation::operand_range getMapVars() {
    return getODSOperands(9);
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(10);
  }

  ::mlir::Operation::operand_range getThreadLimitVars() {
    return getODSOperands(11);
  }

  ::mlir::MutableOperandRange getAllocateVarsMutable();
  ::mlir::MutableOperandRange getAllocatorVarsMutable();
  ::mlir::MutableOperandRange getDependVarsMutable();
  ::mlir::MutableOperandRange getDeviceMutable();
  ::mlir::MutableOperandRange getHasDeviceAddrVarsMutable();
  ::mlir::MutableOperandRange getHostEvalVarsMutable();
  ::mlir::MutableOperandRange getIfExprMutable();
  ::mlir::MutableOperandRange getInReductionVarsMutable();
  ::mlir::MutableOperandRange getIsDevicePtrVarsMutable();
  ::mlir::MutableOperandRange getMapVarsMutable();
  ::mlir::MutableOperandRange getPrivateVarsMutable();
  ::mlir::MutableOperandRange getThreadLimitVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::UnitAttr getBareAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().bare);
  }

  bool getBare();
  ::mlir::ArrayAttr getDependKindsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::DenseBoolArrayAttr getInReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().in_reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getInReductionByref();
  ::mlir::ArrayAttr getInReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().in_reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getInReductionSyms();
  ::mlir::UnitAttr getNowaitAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nowait);
  }

  bool getNowait();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  ::mlir::DenseI64ArrayAttr getPrivateMapsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().private_maps);
  }

  ::std::optional<::llvm::ArrayRef<int64_t>> getPrivateMaps();
  void setBareAttr(::mlir::UnitAttr attr) {
    getProperties().bare = attr;
  }

  void setBare(bool attrValue);
  void setDependKindsAttr(::mlir::ArrayAttr attr) {
    getProperties().depend_kinds = attr;
  }

  void setInReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().in_reduction_byref = attr;
  }

  void setInReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setInReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().in_reduction_syms = attr;
  }

  void setNowaitAttr(::mlir::UnitAttr attr) {
    getProperties().nowait = attr;
  }

  void setNowait(bool attrValue);
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  void setPrivateMapsAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().private_maps = attr;
  }

  void setPrivateMaps(::std::optional<::llvm::ArrayRef<int64_t>> attrValue);
  ::mlir::Attribute removeBareAttr() {
      auto attr = getProperties().bare;
      getProperties().bare = {};
      return attr;
  }

  ::mlir::Attribute removeDependKindsAttr() {
      auto attr = getProperties().depend_kinds;
      getProperties().depend_kinds = {};
      return attr;
  }

  ::mlir::Attribute removeInReductionByrefAttr() {
      auto attr = getProperties().in_reduction_byref;
      getProperties().in_reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeInReductionSymsAttr() {
      auto attr = getProperties().in_reduction_syms;
      getProperties().in_reduction_syms = {};
      return attr;
  }

  ::mlir::Attribute removeNowaitAttr() {
      auto attr = getProperties().nowait;
      getProperties().nowait = {};
      return attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  ::mlir::Attribute removePrivateMapsAttr() {
      auto attr = getProperties().private_maps;
      getProperties().private_maps = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const TargetOperands &clauses);
  static TargetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const TargetOperands &clauses);
  static TargetOp create(::mlir::ImplicitLocOpBuilder &builder, const TargetOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static TargetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static TargetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static TargetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static TargetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::UnitAttr bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static TargetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static TargetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static TargetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static TargetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/bool bare, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, ::mlir::ValueRange has_device_addr_vars, ::mlir::ValueRange host_eval_vars, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, ::mlir::ValueRange is_device_ptr_vars, ::mlir::ValueRange map_vars, /*optional*/bool nowait, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, ::mlir::ValueRange thread_limit_vars, /*optional*/::mlir::DenseI64ArrayAttr private_maps);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 8 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  mlir::Value getMappedValueForPrivateVar(unsigned privVarIdx) {
    std::optional<DenseI64ArrayAttr> privateMapIdices = getPrivateMapsAttr();

    if (!privateMapIdices.has_value())
      return {};

    int64_t mapInfoOpIdx = (*privateMapIdices)[privVarIdx];

    if (mapInfoOpIdx == -1)
      return {};

    return getMapVars()[mapInfoOpIdx];
  }

  /// Returns the innermost OpenMP dialect operation captured by this target
  /// construct. For an operation to be detected as captured, it must be
  /// inside a (possibly multi-level) nest of OpenMP dialect operation's
  /// regions where none of these levels contain other operations considered
  /// not-allowed for these purposes (i.e. only terminator operations are
  /// allowed from the OpenMP dialect, and other dialect's operations are
  /// allowed as long as they don't have a memory write effect).
  ///
  /// If there are omp.loop_nest operations in the sequence of nested
  /// operations, the top level one will be the one captured.
  Operation *getInnermostCapturedOmpOp();

  /// Infers the kernel type (Generic, SPMD or Generic-SPMD) based on the
  /// contents of the target region.
  ///
  /// \param capturedOp result of a still valid (no modifications made to any
  /// nested operations) previous call to `getInnermostCapturedOmpOp()`.
  static ::mlir::omp::TargetRegionFlags
  getKernelExecFlags(Operation *capturedOp);

  unsigned getNumAllocateVars() { return getAllocateVars().size(); }
  unsigned getNumAllocatorsVars() { return getAllocatorVars().size(); }













  /// Returns true if using multi-dimensional values (more than one value)
  bool hasThreadLimitMultiDim() {
    return getThreadLimitVars().size() > 1;
  }

  /// Returns the number of dimensions specified for thread_limit
  unsigned getThreadLimitDimsCount() {
    return getThreadLimitVars().size();
  }

  /// Returns the value for a specific dimension
  /// dim must be less than getThreadLimitDimsCount()
  ::mlir::Value getThreadLimit(unsigned dim = 0) {
    assert(dim < getThreadLimitDimsCount() &&
           "Thread limit index out of bounds");
    return getThreadLimitVars()[dim];
  }
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TargetOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TargetUpdateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TargetUpdateOpGenericAdaptorBase {
public:
  struct Properties {
    using depend_kindsTy = ::mlir::ArrayAttr;
    depend_kindsTy depend_kinds;

    auto getDependKinds() const {
      auto &propStorage = this->depend_kinds;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setDependKinds(const ::mlir::ArrayAttr &propValue) {
      this->depend_kinds = propValue;
    }
    using nowaitTy = ::mlir::UnitAttr;
    nowaitTy nowait;

    auto getNowait() const {
      auto &propStorage = this->nowait;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNowait(const ::mlir::UnitAttr &propValue) {
      this->nowait = propValue;
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
        rhs.depend_kinds == this->depend_kinds &&
        rhs.nowait == this->nowait &&
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
  TargetUpdateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.target_update", odsAttrs.getContext());
  }

  TargetUpdateOpGenericAdaptorBase(TargetUpdateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getDependKindsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::UnitAttr getNowaitAttr();
  bool getNowait();
};

} // namespace detail
template <typename RangeT>
class TargetUpdateOpGenericAdaptor : public detail::TargetUpdateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TargetUpdateOpGenericAdaptorBase;
  static constexpr int odsIndex_depend_vars = 0;
  static constexpr int odsIndex_device = 1;
  static constexpr int odsIndex_if_expr = 2;
  static constexpr int odsIndex_map_vars = 3;
public:
  TargetUpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TargetUpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TargetUpdateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TargetUpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TargetUpdateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TargetUpdateOpGenericAdaptor(RangeT values, const TargetUpdateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TargetUpdateOp, typename = std::enable_if_t<std::is_same_v<LateInst, TargetUpdateOp>>>
  TargetUpdateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDependVars() {
    return getODSOperands(0);
  }

  ValueT getDevice() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getMapVars() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TargetUpdateOpAdaptor : public TargetUpdateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TargetUpdateOpGenericAdaptor::TargetUpdateOpGenericAdaptor;
  TargetUpdateOpAdaptor(TargetUpdateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TargetUpdateOp : public ::mlir::Op<TargetUpdateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::MapClauseOwningOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TargetUpdateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TargetUpdateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_depend_vars = 0;
  static constexpr int odsIndex_device = 1;
  static constexpr int odsIndex_if_expr = 2;
  static constexpr int odsIndex_map_vars = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("depend_kinds"), ::llvm::StringRef("nowait"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDependKindsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDependKindsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNowaitAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNowaitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.target_update");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDependVars() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDevice() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getMapVars() {
    return getODSOperands(3);
  }

  ::mlir::MutableOperandRange getDependVarsMutable();
  ::mlir::MutableOperandRange getDeviceMutable();
  ::mlir::MutableOperandRange getIfExprMutable();
  ::mlir::MutableOperandRange getMapVarsMutable();
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
  ::mlir::ArrayAttr getDependKindsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::UnitAttr getNowaitAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nowait);
  }

  bool getNowait();
  void setDependKindsAttr(::mlir::ArrayAttr attr) {
    getProperties().depend_kinds = attr;
  }

  void setNowaitAttr(::mlir::UnitAttr attr) {
    getProperties().nowait = attr;
  }

  void setNowait(bool attrValue);
  ::mlir::Attribute removeDependKindsAttr() {
      auto attr = getProperties().depend_kinds;
      getProperties().depend_kinds = {};
      return attr;
  }

  ::mlir::Attribute removeNowaitAttr() {
      auto attr = getProperties().nowait;
      getProperties().nowait = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const TargetEnterExitUpdateDataOperands &clauses);
  static TargetUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const TargetEnterExitUpdateDataOperands &clauses);
  static TargetUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, const TargetEnterExitUpdateDataOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static TargetUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/::mlir::UnitAttr nowait);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static TargetUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value device, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange map_vars, /*optional*/bool nowait = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TargetUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TargetUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Override BlockArgOpenMPOpInterface method because `map` clauses have no
  // associated entry block arguments in this operation.
  unsigned numMapBlockArgs() {
    return 0;
  }




};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TargetUpdateOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TaskOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TaskOpGenericAdaptorBase {
public:
  struct Properties {
    using depend_kindsTy = ::mlir::ArrayAttr;
    depend_kindsTy depend_kinds;

    auto getDependKinds() const {
      auto &propStorage = this->depend_kinds;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setDependKinds(const ::mlir::ArrayAttr &propValue) {
      this->depend_kinds = propValue;
    }
    using in_reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    in_reduction_byrefTy in_reduction_byref;

    auto getInReductionByref() const {
      auto &propStorage = this->in_reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setInReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->in_reduction_byref = propValue;
    }
    using in_reduction_symsTy = ::mlir::ArrayAttr;
    in_reduction_symsTy in_reduction_syms;

    auto getInReductionSyms() const {
      auto &propStorage = this->in_reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setInReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->in_reduction_syms = propValue;
    }
    using mergeableTy = ::mlir::UnitAttr;
    mergeableTy mergeable;

    auto getMergeable() const {
      auto &propStorage = this->mergeable;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setMergeable(const ::mlir::UnitAttr &propValue) {
      this->mergeable = propValue;
    }
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
    }
    using untiedTy = ::mlir::UnitAttr;
    untiedTy untied;

    auto getUntied() const {
      auto &propStorage = this->untied;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setUntied(const ::mlir::UnitAttr &propValue) {
      this->untied = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 9>;
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
        rhs.depend_kinds == this->depend_kinds &&
        rhs.in_reduction_byref == this->in_reduction_byref &&
        rhs.in_reduction_syms == this->in_reduction_syms &&
        rhs.mergeable == this->mergeable &&
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
        rhs.untied == this->untied &&
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
  TaskOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.task", odsAttrs.getContext());
  }

  TaskOpGenericAdaptorBase(TaskOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getDependKindsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::DenseBoolArrayAttr getInReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().in_reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getInReductionByref();
  ::mlir::ArrayAttr getInReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().in_reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getInReductionSyms();
  ::mlir::UnitAttr getMergeableAttr();
  bool getMergeable();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::UnitAttr getUntiedAttr();
  bool getUntied();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class TaskOpGenericAdaptor : public detail::TaskOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TaskOpGenericAdaptorBase;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_depend_vars = 2;
  static constexpr int odsIndex_final = 3;
  static constexpr int odsIndex_if_expr = 4;
  static constexpr int odsIndex_in_reduction_vars = 5;
  static constexpr int odsIndex_priority = 6;
  static constexpr int odsIndex_private_vars = 7;
  static constexpr int odsIndex_event_handle = 8;
public:
  TaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TaskOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TaskOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TaskOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TaskOpGenericAdaptor(RangeT values, const TaskOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TaskOp, typename = std::enable_if_t<std::is_same_v<LateInst, TaskOp>>>
  TaskOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAllocateVars() {
    return getODSOperands(0);
  }

  RangeT getAllocatorVars() {
    return getODSOperands(1);
  }

  RangeT getDependVars() {
    return getODSOperands(2);
  }

  ValueT getFinal() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getInReductionVars() {
    return getODSOperands(5);
  }

  ValueT getPriority() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getPrivateVars() {
    return getODSOperands(7);
  }

  ValueT getEventHandle() {
    auto operands = getODSOperands(8);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TaskOpAdaptor : public TaskOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TaskOpGenericAdaptor::TaskOpGenericAdaptor;
  TaskOpAdaptor(TaskOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TaskOp : public ::mlir::Op<TaskOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::omp::OutlineableOpenMPOpInterface::Trait, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TaskOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TaskOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_depend_vars = 2;
  static constexpr int odsIndex_final = 3;
  static constexpr int odsIndex_if_expr = 4;
  static constexpr int odsIndex_in_reduction_vars = 5;
  static constexpr int odsIndex_priority = 6;
  static constexpr int odsIndex_private_vars = 7;
  static constexpr int odsIndex_event_handle = 8;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("depend_kinds"), ::llvm::StringRef("in_reduction_byref"), ::llvm::StringRef("in_reduction_syms"), ::llvm::StringRef("mergeable"), ::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("untied"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDependKindsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDependKindsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInReductionByrefAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getInReductionSymsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getInReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getMergeableAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getMergeableAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getUntiedAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getUntiedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.task");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAllocateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAllocatorVars() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getDependVars() {
    return getODSOperands(2);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getFinal() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getInReductionVars() {
    return getODSOperands(5);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getPriority() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(7);
  }

  ::mlir::TypedValue<::mlir::omp::PointerLikeType> getEventHandle() {
    auto operands = getODSOperands(8);
    return operands.empty() ? ::mlir::TypedValue<::mlir::omp::PointerLikeType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::omp::PointerLikeType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getAllocateVarsMutable();
  ::mlir::MutableOperandRange getAllocatorVarsMutable();
  ::mlir::MutableOperandRange getDependVarsMutable();
  ::mlir::MutableOperandRange getFinalMutable();
  ::mlir::MutableOperandRange getIfExprMutable();
  ::mlir::MutableOperandRange getInReductionVarsMutable();
  ::mlir::MutableOperandRange getPriorityMutable();
  ::mlir::MutableOperandRange getPrivateVarsMutable();
  ::mlir::MutableOperandRange getEventHandleMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getDependKindsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::DenseBoolArrayAttr getInReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().in_reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getInReductionByref();
  ::mlir::ArrayAttr getInReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().in_reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getInReductionSyms();
  ::mlir::UnitAttr getMergeableAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().mergeable);
  }

  bool getMergeable();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  ::mlir::UnitAttr getUntiedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().untied);
  }

  bool getUntied();
  void setDependKindsAttr(::mlir::ArrayAttr attr) {
    getProperties().depend_kinds = attr;
  }

  void setInReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().in_reduction_byref = attr;
  }

  void setInReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setInReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().in_reduction_syms = attr;
  }

  void setMergeableAttr(::mlir::UnitAttr attr) {
    getProperties().mergeable = attr;
  }

  void setMergeable(bool attrValue);
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  void setUntiedAttr(::mlir::UnitAttr attr) {
    getProperties().untied = attr;
  }

  void setUntied(bool attrValue);
  ::mlir::Attribute removeDependKindsAttr() {
      auto attr = getProperties().depend_kinds;
      getProperties().depend_kinds = {};
      return attr;
  }

  ::mlir::Attribute removeInReductionByrefAttr() {
      auto attr = getProperties().in_reduction_byref;
      getProperties().in_reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeInReductionSymsAttr() {
      auto attr = getProperties().in_reduction_syms;
      getProperties().in_reduction_syms = {};
      return attr;
  }

  ::mlir::Attribute removeMergeableAttr() {
      auto attr = getProperties().mergeable;
      getProperties().mergeable = {};
      return attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  ::mlir::Attribute removeUntiedAttr() {
      auto attr = getProperties().untied;
      getProperties().untied = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const TaskOperands &clauses);
  static TaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const TaskOperands &clauses);
  static TaskOp create(::mlir::ImplicitLocOpBuilder &builder, const TaskOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::UnitAttr untied, /*optional*/::mlir::Value event_handle);
  static TaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::UnitAttr untied, /*optional*/::mlir::Value event_handle);
  static TaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::UnitAttr untied, /*optional*/::mlir::Value event_handle);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::UnitAttr untied, /*optional*/::mlir::Value event_handle);
  static TaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::UnitAttr untied, /*optional*/::mlir::Value event_handle);
  static TaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::UnitAttr untied, /*optional*/::mlir::Value event_handle);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/bool untied, /*optional*/::mlir::Value event_handle);
  static TaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/bool untied, /*optional*/::mlir::Value event_handle);
  static TaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/bool untied, /*optional*/::mlir::Value event_handle);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/bool untied, /*optional*/::mlir::Value event_handle);
  static TaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/bool untied, /*optional*/::mlir::Value event_handle);
  static TaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/bool untied, /*optional*/::mlir::Value event_handle);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TaskOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TaskOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 7 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  unsigned getNumAllocateVars() { return getAllocateVars().size(); }
  unsigned getNumAllocatorsVars() { return getAllocatorVars().size(); }









};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TaskOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TaskgroupOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TaskgroupOpGenericAdaptorBase {
public:
  struct Properties {
    using task_reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    task_reduction_byrefTy task_reduction_byref;

    auto getTaskReductionByref() const {
      auto &propStorage = this->task_reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setTaskReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->task_reduction_byref = propValue;
    }
    using task_reduction_symsTy = ::mlir::ArrayAttr;
    task_reduction_symsTy task_reduction_syms;

    auto getTaskReductionSyms() const {
      auto &propStorage = this->task_reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setTaskReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->task_reduction_syms = propValue;
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
        rhs.task_reduction_byref == this->task_reduction_byref &&
        rhs.task_reduction_syms == this->task_reduction_syms &&
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
  TaskgroupOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.taskgroup", odsAttrs.getContext());
  }

  TaskgroupOpGenericAdaptorBase(TaskgroupOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseBoolArrayAttr getTaskReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().task_reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getTaskReductionByref();
  ::mlir::ArrayAttr getTaskReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().task_reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getTaskReductionSyms();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class TaskgroupOpGenericAdaptor : public detail::TaskgroupOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TaskgroupOpGenericAdaptorBase;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_task_reduction_vars = 2;
public:
  TaskgroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TaskgroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TaskgroupOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TaskgroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TaskgroupOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TaskgroupOpGenericAdaptor(RangeT values, const TaskgroupOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TaskgroupOp, typename = std::enable_if_t<std::is_same_v<LateInst, TaskgroupOp>>>
  TaskgroupOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAllocateVars() {
    return getODSOperands(0);
  }

  RangeT getAllocatorVars() {
    return getODSOperands(1);
  }

  RangeT getTaskReductionVars() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TaskgroupOpAdaptor : public TaskgroupOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TaskgroupOpGenericAdaptor::TaskgroupOpGenericAdaptor;
  TaskgroupOpAdaptor(TaskgroupOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TaskgroupOp : public ::mlir::Op<TaskgroupOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TaskgroupOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TaskgroupOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_task_reduction_vars = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("task_reduction_byref"), ::llvm::StringRef("task_reduction_syms"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTaskReductionByrefAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTaskReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTaskReductionSymsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTaskReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.taskgroup");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAllocateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAllocatorVars() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getTaskReductionVars() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getAllocateVarsMutable();
  ::mlir::MutableOperandRange getAllocatorVarsMutable();
  ::mlir::MutableOperandRange getTaskReductionVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::DenseBoolArrayAttr getTaskReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().task_reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getTaskReductionByref();
  ::mlir::ArrayAttr getTaskReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().task_reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getTaskReductionSyms();
  void setTaskReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().task_reduction_byref = attr;
  }

  void setTaskReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setTaskReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().task_reduction_syms = attr;
  }

  ::mlir::Attribute removeTaskReductionByrefAttr() {
      auto attr = getProperties().task_reduction_byref;
      getProperties().task_reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeTaskReductionSymsAttr() {
      auto attr = getProperties().task_reduction_syms;
      getProperties().task_reduction_syms = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const TaskgroupOperands &clauses);
  static TaskgroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const TaskgroupOperands &clauses);
  static TaskgroupOp create(::mlir::ImplicitLocOpBuilder &builder, const TaskgroupOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange task_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr task_reduction_byref, /*optional*/::mlir::ArrayAttr task_reduction_syms);
  static TaskgroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange task_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr task_reduction_byref, /*optional*/::mlir::ArrayAttr task_reduction_syms);
  static TaskgroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange task_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr task_reduction_byref, /*optional*/::mlir::ArrayAttr task_reduction_syms);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange task_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr task_reduction_byref, /*optional*/::mlir::ArrayAttr task_reduction_syms);
  static TaskgroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange task_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr task_reduction_byref, /*optional*/::mlir::ArrayAttr task_reduction_syms);
  static TaskgroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange task_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr task_reduction_byref, /*optional*/::mlir::ArrayAttr task_reduction_syms);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TaskgroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TaskgroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TaskgroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TaskgroupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  unsigned getNumAllocateVars() { return getAllocateVars().size(); }
  unsigned getNumAllocatorsVars() { return getAllocatorVars().size(); }

};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TaskgroupOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TaskloopOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TaskloopOpGenericAdaptorBase {
public:
  struct Properties {
    using grainsize_modTy = ::mlir::omp::ClauseGrainsizeTypeAttr;
    grainsize_modTy grainsize_mod;

    auto getGrainsizeMod() const {
      auto &propStorage = this->grainsize_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseGrainsizeTypeAttr>(propStorage);
    }
    void setGrainsizeMod(const ::mlir::omp::ClauseGrainsizeTypeAttr &propValue) {
      this->grainsize_mod = propValue;
    }
    using in_reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    in_reduction_byrefTy in_reduction_byref;

    auto getInReductionByref() const {
      auto &propStorage = this->in_reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setInReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->in_reduction_byref = propValue;
    }
    using in_reduction_symsTy = ::mlir::ArrayAttr;
    in_reduction_symsTy in_reduction_syms;

    auto getInReductionSyms() const {
      auto &propStorage = this->in_reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setInReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->in_reduction_syms = propValue;
    }
    using mergeableTy = ::mlir::UnitAttr;
    mergeableTy mergeable;

    auto getMergeable() const {
      auto &propStorage = this->mergeable;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setMergeable(const ::mlir::UnitAttr &propValue) {
      this->mergeable = propValue;
    }
    using nogroupTy = ::mlir::UnitAttr;
    nogroupTy nogroup;

    auto getNogroup() const {
      auto &propStorage = this->nogroup;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNogroup(const ::mlir::UnitAttr &propValue) {
      this->nogroup = propValue;
    }
    using num_tasks_modTy = ::mlir::omp::ClauseNumTasksTypeAttr;
    num_tasks_modTy num_tasks_mod;

    auto getNumTasksMod() const {
      auto &propStorage = this->num_tasks_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseNumTasksTypeAttr>(propStorage);
    }
    void setNumTasksMod(const ::mlir::omp::ClauseNumTasksTypeAttr &propValue) {
      this->num_tasks_mod = propValue;
    }
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
    }
    using reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    reduction_byrefTy reduction_byref;

    auto getReductionByref() const {
      auto &propStorage = this->reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->reduction_byref = propValue;
    }
    using reduction_modTy = ::mlir::omp::ReductionModifierAttr;
    reduction_modTy reduction_mod;

    auto getReductionMod() const {
      auto &propStorage = this->reduction_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(propStorage);
    }
    void setReductionMod(const ::mlir::omp::ReductionModifierAttr &propValue) {
      this->reduction_mod = propValue;
    }
    using reduction_symsTy = ::mlir::ArrayAttr;
    reduction_symsTy reduction_syms;

    auto getReductionSyms() const {
      auto &propStorage = this->reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->reduction_syms = propValue;
    }
    using untiedTy = ::mlir::UnitAttr;
    untiedTy untied;

    auto getUntied() const {
      auto &propStorage = this->untied;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setUntied(const ::mlir::UnitAttr &propValue) {
      this->untied = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 10>;
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
        rhs.grainsize_mod == this->grainsize_mod &&
        rhs.in_reduction_byref == this->in_reduction_byref &&
        rhs.in_reduction_syms == this->in_reduction_syms &&
        rhs.mergeable == this->mergeable &&
        rhs.nogroup == this->nogroup &&
        rhs.num_tasks_mod == this->num_tasks_mod &&
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
        rhs.reduction_byref == this->reduction_byref &&
        rhs.reduction_mod == this->reduction_mod &&
        rhs.reduction_syms == this->reduction_syms &&
        rhs.untied == this->untied &&
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
  TaskloopOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.taskloop", odsAttrs.getContext());
  }

  TaskloopOpGenericAdaptorBase(TaskloopOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::omp::ClauseGrainsizeTypeAttr getGrainsizeModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseGrainsizeTypeAttr>(getProperties().grainsize_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseGrainsizeType> getGrainsizeMod();
  ::mlir::DenseBoolArrayAttr getInReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().in_reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getInReductionByref();
  ::mlir::ArrayAttr getInReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().in_reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getInReductionSyms();
  ::mlir::UnitAttr getMergeableAttr();
  bool getMergeable();
  ::mlir::UnitAttr getNogroupAttr();
  bool getNogroup();
  ::mlir::omp::ClauseNumTasksTypeAttr getNumTasksModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseNumTasksTypeAttr>(getProperties().num_tasks_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseNumTasksType> getNumTasksMod();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  ::mlir::UnitAttr getUntiedAttr();
  bool getUntied();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class TaskloopOpGenericAdaptor : public detail::TaskloopOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TaskloopOpGenericAdaptorBase;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_final = 2;
  static constexpr int odsIndex_grainsize = 3;
  static constexpr int odsIndex_if_expr = 4;
  static constexpr int odsIndex_in_reduction_vars = 5;
  static constexpr int odsIndex_num_tasks = 6;
  static constexpr int odsIndex_priority = 7;
  static constexpr int odsIndex_private_vars = 8;
  static constexpr int odsIndex_reduction_vars = 9;
public:
  TaskloopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TaskloopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TaskloopOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TaskloopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TaskloopOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TaskloopOpGenericAdaptor(RangeT values, const TaskloopOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TaskloopOp, typename = std::enable_if_t<std::is_same_v<LateInst, TaskloopOp>>>
  TaskloopOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAllocateVars() {
    return getODSOperands(0);
  }

  RangeT getAllocatorVars() {
    return getODSOperands(1);
  }

  ValueT getFinal() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getGrainsize() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getInReductionVars() {
    return getODSOperands(5);
  }

  ValueT getNumTasks() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getPriority() {
    auto operands = getODSOperands(7);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getPrivateVars() {
    return getODSOperands(8);
  }

  RangeT getReductionVars() {
    return getODSOperands(9);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TaskloopOpAdaptor : public TaskloopOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TaskloopOpGenericAdaptor::TaskloopOpGenericAdaptor;
  TaskloopOpAdaptor(TaskloopOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TaskloopOp : public ::mlir::Op<TaskloopOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::omp::ComposableOpInterface::Trait, ::mlir::omp::OutlineableOpenMPOpInterface::Trait, ::mlir::omp::LoopWrapperInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TaskloopOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TaskloopOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_final = 2;
  static constexpr int odsIndex_grainsize = 3;
  static constexpr int odsIndex_if_expr = 4;
  static constexpr int odsIndex_in_reduction_vars = 5;
  static constexpr int odsIndex_num_tasks = 6;
  static constexpr int odsIndex_priority = 7;
  static constexpr int odsIndex_private_vars = 8;
  static constexpr int odsIndex_reduction_vars = 9;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::omp::ComposableOpInterface::Trait<TaskloopOp>::isComposite;
  using ::mlir::omp::ComposableOpInterface::Trait<TaskloopOp>::setComposite;
  using ::mlir::omp::LoopWrapperInterface::Trait<TaskloopOp>::getNestedWrapper;
  using ::mlir::omp::LoopWrapperInterface::Trait<TaskloopOp>::getWrappedLoop;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grainsize_mod"), ::llvm::StringRef("in_reduction_byref"), ::llvm::StringRef("in_reduction_syms"), ::llvm::StringRef("mergeable"), ::llvm::StringRef("nogroup"), ::llvm::StringRef("num_tasks_mod"), ::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("reduction_byref"), ::llvm::StringRef("reduction_mod"), ::llvm::StringRef("reduction_syms"), ::llvm::StringRef("untied"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGrainsizeModAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGrainsizeModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInReductionByrefAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getInReductionSymsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getInReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getMergeableAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getMergeableAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getNogroupAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getNogroupAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getNumTasksModAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getNumTasksModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(7);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 7);
  }

  ::mlir::StringAttr getReductionByrefAttrName() {
    return getAttributeNameForIndex(8);
  }

  static ::mlir::StringAttr getReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 8);
  }

  ::mlir::StringAttr getReductionModAttrName() {
    return getAttributeNameForIndex(9);
  }

  static ::mlir::StringAttr getReductionModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 9);
  }

  ::mlir::StringAttr getReductionSymsAttrName() {
    return getAttributeNameForIndex(10);
  }

  static ::mlir::StringAttr getReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 10);
  }

  ::mlir::StringAttr getUntiedAttrName() {
    return getAttributeNameForIndex(11);
  }

  static ::mlir::StringAttr getUntiedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 11);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.taskloop");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAllocateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAllocatorVars() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getFinal() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getGrainsize() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getInReductionVars() {
    return getODSOperands(5);
  }

  ::mlir::TypedValue<::mlir::Type> getNumTasks() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getPriority() {
    auto operands = getODSOperands(7);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(8);
  }

  ::mlir::Operation::operand_range getReductionVars() {
    return getODSOperands(9);
  }

  ::mlir::MutableOperandRange getAllocateVarsMutable();
  ::mlir::MutableOperandRange getAllocatorVarsMutable();
  ::mlir::MutableOperandRange getFinalMutable();
  ::mlir::MutableOperandRange getGrainsizeMutable();
  ::mlir::MutableOperandRange getIfExprMutable();
  ::mlir::MutableOperandRange getInReductionVarsMutable();
  ::mlir::MutableOperandRange getNumTasksMutable();
  ::mlir::MutableOperandRange getPriorityMutable();
  ::mlir::MutableOperandRange getPrivateVarsMutable();
  ::mlir::MutableOperandRange getReductionVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::omp::ClauseGrainsizeTypeAttr getGrainsizeModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseGrainsizeTypeAttr>(getProperties().grainsize_mod);
  }

  ::std::optional<::mlir::omp::ClauseGrainsizeType> getGrainsizeMod();
  ::mlir::DenseBoolArrayAttr getInReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().in_reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getInReductionByref();
  ::mlir::ArrayAttr getInReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().in_reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getInReductionSyms();
  ::mlir::UnitAttr getMergeableAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().mergeable);
  }

  bool getMergeable();
  ::mlir::UnitAttr getNogroupAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nogroup);
  }

  bool getNogroup();
  ::mlir::omp::ClauseNumTasksTypeAttr getNumTasksModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseNumTasksTypeAttr>(getProperties().num_tasks_mod);
  }

  ::std::optional<::mlir::omp::ClauseNumTasksType> getNumTasksMod();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  ::mlir::UnitAttr getUntiedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().untied);
  }

  bool getUntied();
  void setGrainsizeModAttr(::mlir::omp::ClauseGrainsizeTypeAttr attr) {
    getProperties().grainsize_mod = attr;
  }

  void setGrainsizeMod(::std::optional<::mlir::omp::ClauseGrainsizeType> attrValue);
  void setInReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().in_reduction_byref = attr;
  }

  void setInReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setInReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().in_reduction_syms = attr;
  }

  void setMergeableAttr(::mlir::UnitAttr attr) {
    getProperties().mergeable = attr;
  }

  void setMergeable(bool attrValue);
  void setNogroupAttr(::mlir::UnitAttr attr) {
    getProperties().nogroup = attr;
  }

  void setNogroup(bool attrValue);
  void setNumTasksModAttr(::mlir::omp::ClauseNumTasksTypeAttr attr) {
    getProperties().num_tasks_mod = attr;
  }

  void setNumTasksMod(::std::optional<::mlir::omp::ClauseNumTasksType> attrValue);
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  void setReductionModAttr(::mlir::omp::ReductionModifierAttr attr) {
    getProperties().reduction_mod = attr;
  }

  void setReductionMod(::std::optional<::mlir::omp::ReductionModifier> attrValue);
  void setReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().reduction_byref = attr;
  }

  void setReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().reduction_syms = attr;
  }

  void setUntiedAttr(::mlir::UnitAttr attr) {
    getProperties().untied = attr;
  }

  void setUntied(bool attrValue);
  ::mlir::Attribute removeGrainsizeModAttr() {
      auto attr = getProperties().grainsize_mod;
      getProperties().grainsize_mod = {};
      return attr;
  }

  ::mlir::Attribute removeInReductionByrefAttr() {
      auto attr = getProperties().in_reduction_byref;
      getProperties().in_reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeInReductionSymsAttr() {
      auto attr = getProperties().in_reduction_syms;
      getProperties().in_reduction_syms = {};
      return attr;
  }

  ::mlir::Attribute removeMergeableAttr() {
      auto attr = getProperties().mergeable;
      getProperties().mergeable = {};
      return attr;
  }

  ::mlir::Attribute removeNogroupAttr() {
      auto attr = getProperties().nogroup;
      getProperties().nogroup = {};
      return attr;
  }

  ::mlir::Attribute removeNumTasksModAttr() {
      auto attr = getProperties().num_tasks_mod;
      getProperties().num_tasks_mod = {};
      return attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  ::mlir::Attribute removeReductionModAttr() {
      auto attr = getProperties().reduction_mod;
      getProperties().reduction_mod = {};
      return attr;
  }

  ::mlir::Attribute removeReductionByrefAttr() {
      auto attr = getProperties().reduction_byref;
      getProperties().reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeReductionSymsAttr() {
      auto attr = getProperties().reduction_syms;
      getProperties().reduction_syms = {};
      return attr;
  }

  ::mlir::Attribute removeUntiedAttr() {
      auto attr = getProperties().untied;
      getProperties().untied = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const TaskloopOperands &clauses);
  static TaskloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const TaskloopOperands &clauses);
  static TaskloopOp create(::mlir::ImplicitLocOpBuilder &builder, const TaskloopOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::UnitAttr nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::UnitAttr untied);
  static TaskloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::UnitAttr nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::UnitAttr untied);
  static TaskloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::UnitAttr nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::UnitAttr untied);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::UnitAttr nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::UnitAttr untied);
  static TaskloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::UnitAttr nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::UnitAttr untied);
  static TaskloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/::mlir::UnitAttr mergeable, /*optional*/::mlir::UnitAttr nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::UnitAttr untied);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/bool nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/bool untied = false);
  static TaskloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/bool nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/bool untied = false);
  static TaskloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/bool nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/bool untied = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/bool nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/bool untied = false);
  static TaskloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/bool nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/bool untied = false);
  static TaskloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value final, /*optional*/::mlir::omp::ClauseGrainsizeTypeAttr grainsize_mod, /*optional*/::mlir::Value grainsize, /*optional*/::mlir::Value if_expr, ::mlir::ValueRange in_reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr in_reduction_byref, /*optional*/::mlir::ArrayAttr in_reduction_syms, /*optional*/bool mergeable, /*optional*/bool nogroup, /*optional*/::mlir::omp::ClauseNumTasksTypeAttr num_tasks_mod, /*optional*/::mlir::Value num_tasks, /*optional*/::mlir::Value priority, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/bool untied = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TaskloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TaskloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TaskloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TaskloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 12 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  void getEffects(SmallVectorImpl<MemoryEffects::EffectInstance> &effects);

  unsigned getNumAllocateVars() { return getAllocateVars().size(); }
  unsigned getNumAllocatorsVars() { return getAllocatorVars().size(); }











  /// Returns the number of reduction variables.
  unsigned getNumReductionVars() { return getReductionVars().size(); }

};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TaskloopOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TaskwaitOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TaskwaitOpGenericAdaptorBase {
public:
  struct Properties {
    using depend_kindsTy = ::mlir::ArrayAttr;
    depend_kindsTy depend_kinds;

    auto getDependKinds() const {
      auto &propStorage = this->depend_kinds;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setDependKinds(const ::mlir::ArrayAttr &propValue) {
      this->depend_kinds = propValue;
    }
    using nowaitTy = ::mlir::UnitAttr;
    nowaitTy nowait;

    auto getNowait() const {
      auto &propStorage = this->nowait;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNowait(const ::mlir::UnitAttr &propValue) {
      this->nowait = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.depend_kinds == this->depend_kinds &&
        rhs.nowait == this->nowait &&
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
  TaskwaitOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.taskwait", odsAttrs.getContext());
  }

  TaskwaitOpGenericAdaptorBase(TaskwaitOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getDependKindsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::UnitAttr getNowaitAttr();
  bool getNowait();
};

} // namespace detail
template <typename RangeT>
class TaskwaitOpGenericAdaptor : public detail::TaskwaitOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TaskwaitOpGenericAdaptorBase;
  static constexpr int odsIndex_depend_vars = 0;
public:
  TaskwaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TaskwaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TaskwaitOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TaskwaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TaskwaitOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TaskwaitOpGenericAdaptor(RangeT values, const TaskwaitOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TaskwaitOp, typename = std::enable_if_t<std::is_same_v<LateInst, TaskwaitOp>>>
  TaskwaitOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDependVars() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TaskwaitOpAdaptor : public TaskwaitOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TaskwaitOpGenericAdaptor::TaskwaitOpGenericAdaptor;
  TaskwaitOpAdaptor(TaskwaitOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TaskwaitOp : public ::mlir::Op<TaskwaitOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TaskwaitOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TaskwaitOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_depend_vars = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("depend_kinds"), ::llvm::StringRef("nowait")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDependKindsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDependKindsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNowaitAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNowaitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.taskwait");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDependVars() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getDependVarsMutable();
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
  ::mlir::ArrayAttr getDependKindsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().depend_kinds);
  }

  ::std::optional< ::mlir::ArrayAttr > getDependKinds();
  ::mlir::UnitAttr getNowaitAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nowait);
  }

  bool getNowait();
  void setDependKindsAttr(::mlir::ArrayAttr attr) {
    getProperties().depend_kinds = attr;
  }

  void setNowaitAttr(::mlir::UnitAttr attr) {
    getProperties().nowait = attr;
  }

  void setNowait(bool attrValue);
  ::mlir::Attribute removeDependKindsAttr() {
      auto attr = getProperties().depend_kinds;
      getProperties().depend_kinds = {};
      return attr;
  }

  ::mlir::Attribute removeNowaitAttr() {
      auto attr = getProperties().nowait;
      getProperties().nowait = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const TaskwaitOperands &clauses);
  static TaskwaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const TaskwaitOperands &clauses);
  static TaskwaitOp create(::mlir::ImplicitLocOpBuilder &builder, const TaskwaitOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::UnitAttr nowait);
  static TaskwaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::UnitAttr nowait);
  static TaskwaitOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::UnitAttr nowait);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::UnitAttr nowait);
  static TaskwaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::UnitAttr nowait);
  static TaskwaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/::mlir::UnitAttr nowait);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/bool nowait = false);
  static TaskwaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/bool nowait = false);
  static TaskwaitOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/bool nowait = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/bool nowait = false);
  static TaskwaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/bool nowait = false);
  static TaskwaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr depend_kinds, ::mlir::ValueRange depend_vars, /*optional*/bool nowait = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TaskwaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TaskwaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TaskwaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TaskwaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TaskwaitOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TaskyieldOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TaskyieldOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TaskyieldOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.taskyield", odsAttrs.getContext());
  }

  TaskyieldOpGenericAdaptorBase(TaskyieldOp op);

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
class TaskyieldOpGenericAdaptor : public detail::TaskyieldOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TaskyieldOpGenericAdaptorBase;
public:
  TaskyieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TaskyieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TaskyieldOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TaskyieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TaskyieldOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TaskyieldOpGenericAdaptor(RangeT values, const TaskyieldOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TaskyieldOp, typename = std::enable_if_t<std::is_same_v<LateInst, TaskyieldOp>>>
  TaskyieldOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class TaskyieldOpAdaptor : public TaskyieldOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TaskyieldOpGenericAdaptor::TaskyieldOpGenericAdaptor;
  TaskyieldOpAdaptor(TaskyieldOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TaskyieldOp : public ::mlir::Op<TaskyieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TaskyieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TaskyieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.taskyield");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static TaskyieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static TaskyieldOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static TaskyieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static TaskyieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TaskyieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TaskyieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TaskyieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TaskyieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TaskyieldOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TeamsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TeamsOpGenericAdaptorBase {
public:
  struct Properties {
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
    }
    using reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    reduction_byrefTy reduction_byref;

    auto getReductionByref() const {
      auto &propStorage = this->reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->reduction_byref = propValue;
    }
    using reduction_modTy = ::mlir::omp::ReductionModifierAttr;
    reduction_modTy reduction_mod;

    auto getReductionMod() const {
      auto &propStorage = this->reduction_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(propStorage);
    }
    void setReductionMod(const ::mlir::omp::ReductionModifierAttr &propValue) {
      this->reduction_mod = propValue;
    }
    using reduction_symsTy = ::mlir::ArrayAttr;
    reduction_symsTy reduction_syms;

    auto getReductionSyms() const {
      auto &propStorage = this->reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->reduction_syms = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 8>;
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
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
        rhs.reduction_byref == this->reduction_byref &&
        rhs.reduction_mod == this->reduction_mod &&
        rhs.reduction_syms == this->reduction_syms &&
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
  TeamsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.teams", odsAttrs.getContext());
  }

  TeamsOpGenericAdaptorBase(TeamsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class TeamsOpGenericAdaptor : public detail::TeamsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TeamsOpGenericAdaptorBase;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_if_expr = 2;
  static constexpr int odsIndex_num_teams_lower = 3;
  static constexpr int odsIndex_num_teams_upper_vars = 4;
  static constexpr int odsIndex_private_vars = 5;
  static constexpr int odsIndex_reduction_vars = 6;
  static constexpr int odsIndex_thread_limit_vars = 7;
public:
  TeamsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TeamsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TeamsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TeamsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TeamsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TeamsOpGenericAdaptor(RangeT values, const TeamsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TeamsOp, typename = std::enable_if_t<std::is_same_v<LateInst, TeamsOp>>>
  TeamsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAllocateVars() {
    return getODSOperands(0);
  }

  RangeT getAllocatorVars() {
    return getODSOperands(1);
  }

  ValueT getIfExpr() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getNumTeamsLower() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getNumTeamsUpperVars() {
    return getODSOperands(4);
  }

  RangeT getPrivateVars() {
    return getODSOperands(5);
  }

  RangeT getReductionVars() {
    return getODSOperands(6);
  }

  RangeT getThreadLimitVars() {
    return getODSOperands(7);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TeamsOpAdaptor : public TeamsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TeamsOpGenericAdaptor::TeamsOpGenericAdaptor;
  TeamsOpAdaptor(TeamsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TeamsOp : public ::mlir::Op<TeamsOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::omp::OutlineableOpenMPOpInterface::Trait, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TeamsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TeamsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_if_expr = 2;
  static constexpr int odsIndex_num_teams_lower = 3;
  static constexpr int odsIndex_num_teams_upper_vars = 4;
  static constexpr int odsIndex_private_vars = 5;
  static constexpr int odsIndex_reduction_vars = 6;
  static constexpr int odsIndex_thread_limit_vars = 7;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("reduction_byref"), ::llvm::StringRef("reduction_mod"), ::llvm::StringRef("reduction_syms"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getReductionByrefAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getReductionModAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getReductionModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getReductionSymsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.teams");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAllocateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAllocatorVars() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIfExpr() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getNumTeamsLower() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getNumTeamsUpperVars() {
    return getODSOperands(4);
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(5);
  }

  ::mlir::Operation::operand_range getReductionVars() {
    return getODSOperands(6);
  }

  ::mlir::Operation::operand_range getThreadLimitVars() {
    return getODSOperands(7);
  }

  ::mlir::MutableOperandRange getAllocateVarsMutable();
  ::mlir::MutableOperandRange getAllocatorVarsMutable();
  ::mlir::MutableOperandRange getIfExprMutable();
  ::mlir::MutableOperandRange getNumTeamsLowerMutable();
  ::mlir::MutableOperandRange getNumTeamsUpperVarsMutable();
  ::mlir::MutableOperandRange getPrivateVarsMutable();
  ::mlir::MutableOperandRange getReductionVarsMutable();
  ::mlir::MutableOperandRange getThreadLimitVarsMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  void setReductionModAttr(::mlir::omp::ReductionModifierAttr attr) {
    getProperties().reduction_mod = attr;
  }

  void setReductionMod(::std::optional<::mlir::omp::ReductionModifier> attrValue);
  void setReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().reduction_byref = attr;
  }

  void setReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().reduction_syms = attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  ::mlir::Attribute removeReductionModAttr() {
      auto attr = getProperties().reduction_mod;
      getProperties().reduction_mod = {};
      return attr;
  }

  ::mlir::Attribute removeReductionByrefAttr() {
      auto attr = getProperties().reduction_byref;
      getProperties().reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeReductionSymsAttr() {
      auto attr = getProperties().reduction_syms;
      getProperties().reduction_syms = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const TeamsOperands &clauses);
  static TeamsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const TeamsOperands &clauses);
  static TeamsOp create(::mlir::ImplicitLocOpBuilder &builder, const TeamsOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static TeamsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static TeamsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static TeamsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static TeamsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static TeamsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static TeamsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static TeamsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static TeamsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, /*optional*/::mlir::Value if_expr, /*optional*/::mlir::Value num_teams_lower, ::mlir::ValueRange num_teams_upper_vars, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, ::mlir::ValueRange thread_limit_vars);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TeamsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TeamsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TeamsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TeamsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  unsigned getNumAllocateVars() { return getAllocateVars().size(); }
  unsigned getNumAllocatorsVars() { return getAllocatorVars().size(); }



  /// Returns true if using the multi-dimensional values format
  bool hasNumTeamsMultiDim() {
    return getNumTeamsUpperVars().size() > 1;
  }

  /// Returns the number of dimensions specified for num_teams
  unsigned getNumTeamsDimsCount() {
    return getNumTeamsUpperVars().size();
  }

  /// Returns the value for a specific dimension index
  /// Index must be less than getNumTeamsUpperVars().size()
  ::mlir::Value getNumTeams(unsigned dim = 0) {
    assert(dim < getNumTeamsDimsCount() &&
           "Num teams dims index out of bounds");
    return getNumTeamsUpperVars()[dim];
  }



  /// Returns the number of reduction variables.
  unsigned getNumReductionVars() { return getReductionVars().size(); }


  /// Returns true if using multi-dimensional values (more than one value)
  bool hasThreadLimitMultiDim() {
    return getThreadLimitVars().size() > 1;
  }

  /// Returns the number of dimensions specified for thread_limit
  unsigned getThreadLimitDimsCount() {
    return getThreadLimitVars().size();
  }

  /// Returns the value for a specific dimension
  /// dim must be less than getThreadLimitDimsCount()
  ::mlir::Value getThreadLimit(unsigned dim = 0) {
    assert(dim < getThreadLimitDimsCount() &&
           "Thread limit index out of bounds");
    return getThreadLimitVars()[dim];
  }
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TeamsOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TerminatorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TerminatorOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TerminatorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.terminator", odsAttrs.getContext());
  }

  TerminatorOpGenericAdaptorBase(TerminatorOp op);

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
class TerminatorOpGenericAdaptor : public detail::TerminatorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TerminatorOpGenericAdaptorBase;
public:
  TerminatorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TerminatorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TerminatorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TerminatorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TerminatorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TerminatorOpGenericAdaptor(RangeT values, const TerminatorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TerminatorOp, typename = std::enable_if_t<std::is_same_v<LateInst, TerminatorOp>>>
  TerminatorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class TerminatorOpAdaptor : public TerminatorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TerminatorOpGenericAdaptor::TerminatorOpGenericAdaptor;
  TerminatorOpAdaptor(TerminatorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TerminatorOp : public ::mlir::Op<TerminatorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TerminatorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TerminatorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.terminator");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static TerminatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static TerminatorOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static TerminatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static TerminatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TerminatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TerminatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TerminatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TerminatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TerminatorOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::ThreadprivateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ThreadprivateOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ThreadprivateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.threadprivate", odsAttrs.getContext());
  }

  ThreadprivateOpGenericAdaptorBase(ThreadprivateOp op);

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
class ThreadprivateOpGenericAdaptor : public detail::ThreadprivateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ThreadprivateOpGenericAdaptorBase;
  static constexpr int odsIndex_sym_addr = 0;
public:
  ThreadprivateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ThreadprivateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ThreadprivateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ThreadprivateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ThreadprivateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ThreadprivateOpGenericAdaptor(RangeT values, const ThreadprivateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ThreadprivateOp, typename = std::enable_if_t<std::is_same_v<LateInst, ThreadprivateOp>>>
  ThreadprivateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSymAddr() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ThreadprivateOpAdaptor : public ThreadprivateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ThreadprivateOpGenericAdaptor::ThreadprivateOpGenericAdaptor;
  ThreadprivateOpAdaptor(ThreadprivateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ThreadprivateOp : public ::mlir::Op<ThreadprivateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::omp::PointerLikeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ThreadprivateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ThreadprivateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_sym_addr = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.threadprivate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::omp::PointerLikeType> getSymAddr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::PointerLikeType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getSymAddrMutable() {
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

  ::mlir::TypedValue<::mlir::omp::PointerLikeType> getTlsAddr() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::PointerLikeType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type tls_addr, ::mlir::Value sym_addr);
  static ThreadprivateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type tls_addr, ::mlir::Value sym_addr);
  static ThreadprivateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type tls_addr, ::mlir::Value sym_addr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value sym_addr);
  static ThreadprivateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value sym_addr);
  static ThreadprivateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value sym_addr);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ThreadprivateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ThreadprivateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ThreadprivateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ThreadprivateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::ThreadprivateOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::TileOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TileOpGenericAdaptorBase {
public:
  struct Properties {
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
  TileOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.tile", odsAttrs.getContext());
  }

  TileOpGenericAdaptorBase(TileOp op);

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
class TileOpGenericAdaptor : public detail::TileOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TileOpGenericAdaptorBase;
  static constexpr int odsIndex_generatees = 0;
  static constexpr int odsIndex_applyees = 1;
  static constexpr int odsIndex_sizes = 2;
public:
  TileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TileOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : TileOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TileOpGenericAdaptor(RangeT values, const TileOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TileOp, typename = std::enable_if_t<std::is_same_v<LateInst, TileOp>>>
  TileOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getGeneratees() {
    return getODSOperands(0);
  }

  RangeT getApplyees() {
    return getODSOperands(1);
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
class TileOpAdaptor : public TileOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TileOpGenericAdaptor::TileOpGenericAdaptor;
  TileOpAdaptor(TileOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TileOp : public ::mlir::Op<TileOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::LoopTransformationInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TileOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TileOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_generatees = 0;
  static constexpr int odsIndex_applyees = 1;
  static constexpr int odsIndex_sizes = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::omp::LoopTransformationInterface::Trait<TileOp>::getNumApplyees;
  using ::mlir::omp::LoopTransformationInterface::Trait<TileOp>::getNumGeneratees;
  using ::mlir::omp::LoopTransformationInterface::Trait<TileOp>::isApplyee;
  using ::mlir::omp::LoopTransformationInterface::Trait<TileOp>::isGeneratee;
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
    return ::llvm::StringLiteral("omp.tile");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getGeneratees() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getApplyees() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getSizes() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getGenerateesMutable();
  ::mlir::MutableOperandRange getApplyeesMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange generatees, ::mlir::ValueRange applyees, ::mlir::ValueRange sizes);
  static TileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange generatees, ::mlir::ValueRange applyees, ::mlir::ValueRange sizes);
  static TileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange generatees, ::mlir::ValueRange applyees, ::mlir::ValueRange sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange generatees, ::mlir::ValueRange applyees, ::mlir::ValueRange sizes);
  static TileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange generatees, ::mlir::ValueRange applyees, ::mlir::ValueRange sizes);
  static TileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange generatees, ::mlir::ValueRange applyees, ::mlir::ValueRange sizes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  std::pair<unsigned, unsigned> getApplyeesODSOperandIndexAndLength();
  std::pair<unsigned, unsigned> getGenerateesODSOperandIndexAndLength();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    return {};
  }

public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::TileOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::UnrollHeuristicOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnrollHeuristicOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UnrollHeuristicOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.unroll_heuristic", odsAttrs.getContext());
  }

  UnrollHeuristicOpGenericAdaptorBase(UnrollHeuristicOp op);

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
class UnrollHeuristicOpGenericAdaptor : public detail::UnrollHeuristicOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnrollHeuristicOpGenericAdaptorBase;
  static constexpr int odsIndex_applyee = 0;
public:
  UnrollHeuristicOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnrollHeuristicOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : UnrollHeuristicOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnrollHeuristicOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnrollHeuristicOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnrollHeuristicOpGenericAdaptor(RangeT values, const UnrollHeuristicOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnrollHeuristicOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnrollHeuristicOp>>>
  UnrollHeuristicOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getApplyee() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UnrollHeuristicOpAdaptor : public UnrollHeuristicOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnrollHeuristicOpGenericAdaptor::UnrollHeuristicOpGenericAdaptor;
  UnrollHeuristicOpAdaptor(UnrollHeuristicOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnrollHeuristicOp : public ::mlir::Op<UnrollHeuristicOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::omp::LoopTransformationInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnrollHeuristicOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnrollHeuristicOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_applyee = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::omp::LoopTransformationInterface::Trait<UnrollHeuristicOp>::getNumApplyees;
  using ::mlir::omp::LoopTransformationInterface::Trait<UnrollHeuristicOp>::getNumGeneratees;
  using ::mlir::omp::LoopTransformationInterface::Trait<UnrollHeuristicOp>::isApplyee;
  using ::mlir::omp::LoopTransformationInterface::Trait<UnrollHeuristicOp>::isGeneratee;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.unroll_heuristic");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::omp::CanonicalLoopInfoType> getApplyee() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::omp::CanonicalLoopInfoType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getApplyeeMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value cli);
  static UnrollHeuristicOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value cli);
  static UnrollHeuristicOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value cli);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value applyee);
  static UnrollHeuristicOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value applyee);
  static UnrollHeuristicOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value applyee);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnrollHeuristicOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnrollHeuristicOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnrollHeuristicOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnrollHeuristicOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  std::pair<unsigned, unsigned> getApplyeesODSOperandIndexAndLength();
  std::pair<unsigned, unsigned> getGenerateesODSOperandIndexAndLength();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::UnrollHeuristicOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::WorkdistributeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WorkdistributeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WorkdistributeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.workdistribute", odsAttrs.getContext());
  }

  WorkdistributeOpGenericAdaptorBase(WorkdistributeOp op);

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
class WorkdistributeOpGenericAdaptor : public detail::WorkdistributeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WorkdistributeOpGenericAdaptorBase;
public:
  WorkdistributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WorkdistributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WorkdistributeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WorkdistributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WorkdistributeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WorkdistributeOpGenericAdaptor(RangeT values, const WorkdistributeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WorkdistributeOp, typename = std::enable_if_t<std::is_same_v<LateInst, WorkdistributeOp>>>
  WorkdistributeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class WorkdistributeOpAdaptor : public WorkdistributeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WorkdistributeOpGenericAdaptor::WorkdistributeOpGenericAdaptor;
  WorkdistributeOpAdaptor(WorkdistributeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WorkdistributeOp : public ::mlir::Op<WorkdistributeOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WorkdistributeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WorkdistributeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.workdistribute");
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
  static WorkdistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static WorkdistributeOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static WorkdistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static WorkdistributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WorkdistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WorkdistributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WorkdistributeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WorkdistributeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::WorkdistributeOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::WorkshareLoopWrapperOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WorkshareLoopWrapperOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WorkshareLoopWrapperOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.workshare.loop_wrapper", odsAttrs.getContext());
  }

  WorkshareLoopWrapperOpGenericAdaptorBase(WorkshareLoopWrapperOp op);

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
class WorkshareLoopWrapperOpGenericAdaptor : public detail::WorkshareLoopWrapperOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WorkshareLoopWrapperOpGenericAdaptorBase;
public:
  WorkshareLoopWrapperOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WorkshareLoopWrapperOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WorkshareLoopWrapperOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WorkshareLoopWrapperOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WorkshareLoopWrapperOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WorkshareLoopWrapperOpGenericAdaptor(RangeT values, const WorkshareLoopWrapperOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WorkshareLoopWrapperOp, typename = std::enable_if_t<std::is_same_v<LateInst, WorkshareLoopWrapperOp>>>
  WorkshareLoopWrapperOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class WorkshareLoopWrapperOpAdaptor : public WorkshareLoopWrapperOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WorkshareLoopWrapperOpGenericAdaptor::WorkshareLoopWrapperOpGenericAdaptor;
  WorkshareLoopWrapperOpAdaptor(WorkshareLoopWrapperOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WorkshareLoopWrapperOp : public ::mlir::Op<WorkshareLoopWrapperOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::omp::LoopWrapperInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WorkshareLoopWrapperOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WorkshareLoopWrapperOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::omp::LoopWrapperInterface::Trait<WorkshareLoopWrapperOp>::getNestedWrapper;
  using ::mlir::omp::LoopWrapperInterface::Trait<WorkshareLoopWrapperOp>::getWrappedLoop;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.workshare.loop_wrapper");
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
  static WorkshareLoopWrapperOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static WorkshareLoopWrapperOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static WorkshareLoopWrapperOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static WorkshareLoopWrapperOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WorkshareLoopWrapperOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WorkshareLoopWrapperOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WorkshareLoopWrapperOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WorkshareLoopWrapperOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::WorkshareLoopWrapperOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::WorkshareOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WorkshareOpGenericAdaptorBase {
public:
  struct Properties {
    using nowaitTy = ::mlir::UnitAttr;
    nowaitTy nowait;

    auto getNowait() const {
      auto &propStorage = this->nowait;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNowait(const ::mlir::UnitAttr &propValue) {
      this->nowait = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.nowait == this->nowait &&
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
  WorkshareOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.workshare", odsAttrs.getContext());
  }

  WorkshareOpGenericAdaptorBase(WorkshareOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getNowaitAttr();
  bool getNowait();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class WorkshareOpGenericAdaptor : public detail::WorkshareOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WorkshareOpGenericAdaptorBase;
public:
  WorkshareOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WorkshareOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WorkshareOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WorkshareOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WorkshareOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WorkshareOpGenericAdaptor(RangeT values, const WorkshareOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WorkshareOp, typename = std::enable_if_t<std::is_same_v<LateInst, WorkshareOp>>>
  WorkshareOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class WorkshareOpAdaptor : public WorkshareOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WorkshareOpGenericAdaptor::WorkshareOpGenericAdaptor;
  WorkshareOpAdaptor(WorkshareOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WorkshareOp : public ::mlir::Op<WorkshareOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WorkshareOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WorkshareOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("nowait")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNowaitAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNowaitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.workshare");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::UnitAttr getNowaitAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nowait);
  }

  bool getNowait();
  void setNowaitAttr(::mlir::UnitAttr attr) {
    getProperties().nowait = attr;
  }

  void setNowait(bool attrValue);
  ::mlir::Attribute removeNowaitAttr() {
      auto attr = getProperties().nowait;
      getProperties().nowait = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const WorkshareOperands &clauses);
  static WorkshareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const WorkshareOperands &clauses);
  static WorkshareOp create(::mlir::ImplicitLocOpBuilder &builder, const WorkshareOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::UnitAttr nowait);
  static WorkshareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::UnitAttr nowait);
  static WorkshareOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::UnitAttr nowait);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr nowait);
  static WorkshareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr nowait);
  static WorkshareOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr nowait);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/bool nowait = false);
  static WorkshareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/bool nowait = false);
  static WorkshareOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/bool nowait = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/bool nowait = false);
  static WorkshareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/bool nowait = false);
  static WorkshareOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/bool nowait = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WorkshareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WorkshareOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WorkshareOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WorkshareOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::WorkshareOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::WsloopOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WsloopOpGenericAdaptorBase {
public:
  struct Properties {
    using linear_var_typesTy = ::mlir::ArrayAttr;
    linear_var_typesTy linear_var_types;

    auto getLinearVarTypes() const {
      auto &propStorage = this->linear_var_types;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setLinearVarTypes(const ::mlir::ArrayAttr &propValue) {
      this->linear_var_types = propValue;
    }
    using nowaitTy = ::mlir::UnitAttr;
    nowaitTy nowait;

    auto getNowait() const {
      auto &propStorage = this->nowait;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNowait(const ::mlir::UnitAttr &propValue) {
      this->nowait = propValue;
    }
    using orderTy = ::mlir::omp::ClauseOrderKindAttr;
    orderTy order;

    auto getOrder() const {
      auto &propStorage = this->order;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(propStorage);
    }
    void setOrder(const ::mlir::omp::ClauseOrderKindAttr &propValue) {
      this->order = propValue;
    }
    using order_modTy = ::mlir::omp::OrderModifierAttr;
    order_modTy order_mod;

    auto getOrderMod() const {
      auto &propStorage = this->order_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(propStorage);
    }
    void setOrderMod(const ::mlir::omp::OrderModifierAttr &propValue) {
      this->order_mod = propValue;
    }
    using orderedTy = ::mlir::IntegerAttr;
    orderedTy ordered;

    auto getOrdered() const {
      auto &propStorage = this->ordered;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setOrdered(const ::mlir::IntegerAttr &propValue) {
      this->ordered = propValue;
    }
    using private_needs_barrierTy = ::mlir::UnitAttr;
    private_needs_barrierTy private_needs_barrier;

    auto getPrivateNeedsBarrier() const {
      auto &propStorage = this->private_needs_barrier;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setPrivateNeedsBarrier(const ::mlir::UnitAttr &propValue) {
      this->private_needs_barrier = propValue;
    }
    using private_symsTy = ::mlir::ArrayAttr;
    private_symsTy private_syms;

    auto getPrivateSyms() const {
      auto &propStorage = this->private_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateSyms(const ::mlir::ArrayAttr &propValue) {
      this->private_syms = propValue;
    }
    using reduction_byrefTy = ::mlir::DenseBoolArrayAttr;
    reduction_byrefTy reduction_byref;

    auto getReductionByref() const {
      auto &propStorage = this->reduction_byref;
      return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setReductionByref(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->reduction_byref = propValue;
    }
    using reduction_modTy = ::mlir::omp::ReductionModifierAttr;
    reduction_modTy reduction_mod;

    auto getReductionMod() const {
      auto &propStorage = this->reduction_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(propStorage);
    }
    void setReductionMod(const ::mlir::omp::ReductionModifierAttr &propValue) {
      this->reduction_mod = propValue;
    }
    using reduction_symsTy = ::mlir::ArrayAttr;
    reduction_symsTy reduction_syms;

    auto getReductionSyms() const {
      auto &propStorage = this->reduction_syms;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setReductionSyms(const ::mlir::ArrayAttr &propValue) {
      this->reduction_syms = propValue;
    }
    using schedule_kindTy = ::mlir::omp::ClauseScheduleKindAttr;
    schedule_kindTy schedule_kind;

    auto getScheduleKind() const {
      auto &propStorage = this->schedule_kind;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseScheduleKindAttr>(propStorage);
    }
    void setScheduleKind(const ::mlir::omp::ClauseScheduleKindAttr &propValue) {
      this->schedule_kind = propValue;
    }
    using schedule_modTy = ::mlir::omp::ScheduleModifierAttr;
    schedule_modTy schedule_mod;

    auto getScheduleMod() const {
      auto &propStorage = this->schedule_mod;
      return ::llvm::dyn_cast_or_null<::mlir::omp::ScheduleModifierAttr>(propStorage);
    }
    void setScheduleMod(const ::mlir::omp::ScheduleModifierAttr &propValue) {
      this->schedule_mod = propValue;
    }
    using schedule_simdTy = ::mlir::UnitAttr;
    schedule_simdTy schedule_simd;

    auto getScheduleSimd() const {
      auto &propStorage = this->schedule_simd;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setScheduleSimd(const ::mlir::UnitAttr &propValue) {
      this->schedule_simd = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 7>;
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
        rhs.linear_var_types == this->linear_var_types &&
        rhs.nowait == this->nowait &&
        rhs.order == this->order &&
        rhs.order_mod == this->order_mod &&
        rhs.ordered == this->ordered &&
        rhs.private_needs_barrier == this->private_needs_barrier &&
        rhs.private_syms == this->private_syms &&
        rhs.reduction_byref == this->reduction_byref &&
        rhs.reduction_mod == this->reduction_mod &&
        rhs.reduction_syms == this->reduction_syms &&
        rhs.schedule_kind == this->schedule_kind &&
        rhs.schedule_mod == this->schedule_mod &&
        rhs.schedule_simd == this->schedule_simd &&
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
  WsloopOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("omp.wsloop", odsAttrs.getContext());
  }

  WsloopOpGenericAdaptorBase(WsloopOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getLinearVarTypesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().linear_var_types);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getLinearVarTypes();
  ::mlir::UnitAttr getNowaitAttr();
  bool getNowait();
  ::mlir::omp::ClauseOrderKindAttr getOrderAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(getProperties().order);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseOrderKind> getOrder();
  ::mlir::omp::OrderModifierAttr getOrderModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(getProperties().order_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::OrderModifier> getOrderMod();
  ::mlir::IntegerAttr getOrderedAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().ordered);
    return attr;
  }

  ::std::optional<uint64_t> getOrdered();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr();
  bool getPrivateNeedsBarrier();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  ::mlir::omp::ClauseScheduleKindAttr getScheduleKindAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ClauseScheduleKindAttr>(getProperties().schedule_kind);
    return attr;
  }

  ::std::optional<::mlir::omp::ClauseScheduleKind> getScheduleKind();
  ::mlir::omp::ScheduleModifierAttr getScheduleModAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::omp::ScheduleModifierAttr>(getProperties().schedule_mod);
    return attr;
  }

  ::std::optional<::mlir::omp::ScheduleModifier> getScheduleMod();
  ::mlir::UnitAttr getScheduleSimdAttr();
  bool getScheduleSimd();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class WsloopOpGenericAdaptor : public detail::WsloopOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WsloopOpGenericAdaptorBase;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_linear_vars = 2;
  static constexpr int odsIndex_linear_step_vars = 3;
  static constexpr int odsIndex_private_vars = 4;
  static constexpr int odsIndex_reduction_vars = 5;
  static constexpr int odsIndex_schedule_chunk = 6;
public:
  WsloopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WsloopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WsloopOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WsloopOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : WsloopOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WsloopOpGenericAdaptor(RangeT values, const WsloopOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WsloopOp, typename = std::enable_if_t<std::is_same_v<LateInst, WsloopOp>>>
  WsloopOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAllocateVars() {
    return getODSOperands(0);
  }

  RangeT getAllocatorVars() {
    return getODSOperands(1);
  }

  RangeT getLinearVars() {
    return getODSOperands(2);
  }

  RangeT getLinearStepVars() {
    return getODSOperands(3);
  }

  RangeT getPrivateVars() {
    return getODSOperands(4);
  }

  RangeT getReductionVars() {
    return getODSOperands(5);
  }

  ValueT getScheduleChunk() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WsloopOpAdaptor : public WsloopOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WsloopOpGenericAdaptor::WsloopOpGenericAdaptor;
  WsloopOpAdaptor(WsloopOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WsloopOp : public ::mlir::Op<WsloopOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::omp::ComposableOpInterface::Trait, ::mlir::omp::LoopWrapperInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::omp::BlockArgOpenMPOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WsloopOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WsloopOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_allocate_vars = 0;
  static constexpr int odsIndex_allocator_vars = 1;
  static constexpr int odsIndex_linear_vars = 2;
  static constexpr int odsIndex_linear_step_vars = 3;
  static constexpr int odsIndex_private_vars = 4;
  static constexpr int odsIndex_reduction_vars = 5;
  static constexpr int odsIndex_schedule_chunk = 6;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::omp::ComposableOpInterface::Trait<WsloopOp>::isComposite;
  using ::mlir::omp::ComposableOpInterface::Trait<WsloopOp>::setComposite;
  using ::mlir::omp::LoopWrapperInterface::Trait<WsloopOp>::getNestedWrapper;
  using ::mlir::omp::LoopWrapperInterface::Trait<WsloopOp>::getWrappedLoop;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("linear_var_types"), ::llvm::StringRef("nowait"), ::llvm::StringRef("order"), ::llvm::StringRef("order_mod"), ::llvm::StringRef("ordered"), ::llvm::StringRef("private_needs_barrier"), ::llvm::StringRef("private_syms"), ::llvm::StringRef("reduction_byref"), ::llvm::StringRef("reduction_mod"), ::llvm::StringRef("reduction_syms"), ::llvm::StringRef("schedule_kind"), ::llvm::StringRef("schedule_mod"), ::llvm::StringRef("schedule_simd"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLinearVarTypesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLinearVarTypesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNowaitAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNowaitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOrderAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getOrderAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOrderModAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getOrderModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getOrderedAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getOrderedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getPrivateNeedsBarrierAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getPrivateNeedsBarrierAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getPrivateSymsAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getPrivateSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  ::mlir::StringAttr getReductionByrefAttrName() {
    return getAttributeNameForIndex(7);
  }

  static ::mlir::StringAttr getReductionByrefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 7);
  }

  ::mlir::StringAttr getReductionModAttrName() {
    return getAttributeNameForIndex(8);
  }

  static ::mlir::StringAttr getReductionModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 8);
  }

  ::mlir::StringAttr getReductionSymsAttrName() {
    return getAttributeNameForIndex(9);
  }

  static ::mlir::StringAttr getReductionSymsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 9);
  }

  ::mlir::StringAttr getScheduleKindAttrName() {
    return getAttributeNameForIndex(10);
  }

  static ::mlir::StringAttr getScheduleKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 10);
  }

  ::mlir::StringAttr getScheduleModAttrName() {
    return getAttributeNameForIndex(11);
  }

  static ::mlir::StringAttr getScheduleModAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 11);
  }

  ::mlir::StringAttr getScheduleSimdAttrName() {
    return getAttributeNameForIndex(12);
  }

  static ::mlir::StringAttr getScheduleSimdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 12);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("omp.wsloop");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAllocateVars() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getAllocatorVars() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getLinearVars() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getLinearStepVars() {
    return getODSOperands(3);
  }

  ::mlir::Operation::operand_range getPrivateVars() {
    return getODSOperands(4);
  }

  ::mlir::Operation::operand_range getReductionVars() {
    return getODSOperands(5);
  }

  ::mlir::TypedValue<::mlir::Type> getScheduleChunk() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getAllocateVarsMutable();
  ::mlir::MutableOperandRange getAllocatorVarsMutable();
  ::mlir::MutableOperandRange getLinearVarsMutable();
  ::mlir::MutableOperandRange getLinearStepVarsMutable();
  ::mlir::MutableOperandRange getPrivateVarsMutable();
  ::mlir::MutableOperandRange getReductionVarsMutable();
  ::mlir::MutableOperandRange getScheduleChunkMutable();
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getLinearVarTypesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().linear_var_types);
  }

  ::std::optional< ::mlir::ArrayAttr > getLinearVarTypes();
  ::mlir::UnitAttr getNowaitAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().nowait);
  }

  bool getNowait();
  ::mlir::omp::ClauseOrderKindAttr getOrderAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseOrderKindAttr>(getProperties().order);
  }

  ::std::optional<::mlir::omp::ClauseOrderKind> getOrder();
  ::mlir::omp::OrderModifierAttr getOrderModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::OrderModifierAttr>(getProperties().order_mod);
  }

  ::std::optional<::mlir::omp::OrderModifier> getOrderMod();
  ::mlir::IntegerAttr getOrderedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().ordered);
  }

  ::std::optional<uint64_t> getOrdered();
  ::mlir::ArrayAttr getPrivateSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateSyms();
  ::mlir::UnitAttr getPrivateNeedsBarrierAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().private_needs_barrier);
  }

  bool getPrivateNeedsBarrier();
  ::mlir::omp::ReductionModifierAttr getReductionModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ReductionModifierAttr>(getProperties().reduction_mod);
  }

  ::std::optional<::mlir::omp::ReductionModifier> getReductionMod();
  ::mlir::DenseBoolArrayAttr getReductionByrefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseBoolArrayAttr>(getProperties().reduction_byref);
  }

  ::std::optional<::llvm::ArrayRef<bool>> getReductionByref();
  ::mlir::ArrayAttr getReductionSymsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().reduction_syms);
  }

  ::std::optional< ::mlir::ArrayAttr > getReductionSyms();
  ::mlir::omp::ClauseScheduleKindAttr getScheduleKindAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ClauseScheduleKindAttr>(getProperties().schedule_kind);
  }

  ::std::optional<::mlir::omp::ClauseScheduleKind> getScheduleKind();
  ::mlir::omp::ScheduleModifierAttr getScheduleModAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::omp::ScheduleModifierAttr>(getProperties().schedule_mod);
  }

  ::std::optional<::mlir::omp::ScheduleModifier> getScheduleMod();
  ::mlir::UnitAttr getScheduleSimdAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().schedule_simd);
  }

  bool getScheduleSimd();
  void setLinearVarTypesAttr(::mlir::ArrayAttr attr) {
    getProperties().linear_var_types = attr;
  }

  void setNowaitAttr(::mlir::UnitAttr attr) {
    getProperties().nowait = attr;
  }

  void setNowait(bool attrValue);
  void setOrderAttr(::mlir::omp::ClauseOrderKindAttr attr) {
    getProperties().order = attr;
  }

  void setOrder(::std::optional<::mlir::omp::ClauseOrderKind> attrValue);
  void setOrderModAttr(::mlir::omp::OrderModifierAttr attr) {
    getProperties().order_mod = attr;
  }

  void setOrderMod(::std::optional<::mlir::omp::OrderModifier> attrValue);
  void setOrderedAttr(::mlir::IntegerAttr attr) {
    getProperties().ordered = attr;
  }

  void setOrdered(::std::optional<uint64_t> attrValue);
  void setPrivateSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_syms = attr;
  }

  void setPrivateNeedsBarrierAttr(::mlir::UnitAttr attr) {
    getProperties().private_needs_barrier = attr;
  }

  void setPrivateNeedsBarrier(bool attrValue);
  void setReductionModAttr(::mlir::omp::ReductionModifierAttr attr) {
    getProperties().reduction_mod = attr;
  }

  void setReductionMod(::std::optional<::mlir::omp::ReductionModifier> attrValue);
  void setReductionByrefAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().reduction_byref = attr;
  }

  void setReductionByref(::std::optional<::llvm::ArrayRef<bool>> attrValue);
  void setReductionSymsAttr(::mlir::ArrayAttr attr) {
    getProperties().reduction_syms = attr;
  }

  void setScheduleKindAttr(::mlir::omp::ClauseScheduleKindAttr attr) {
    getProperties().schedule_kind = attr;
  }

  void setScheduleKind(::std::optional<::mlir::omp::ClauseScheduleKind> attrValue);
  void setScheduleModAttr(::mlir::omp::ScheduleModifierAttr attr) {
    getProperties().schedule_mod = attr;
  }

  void setScheduleMod(::std::optional<::mlir::omp::ScheduleModifier> attrValue);
  void setScheduleSimdAttr(::mlir::UnitAttr attr) {
    getProperties().schedule_simd = attr;
  }

  void setScheduleSimd(bool attrValue);
  ::mlir::Attribute removeLinearVarTypesAttr() {
      auto attr = getProperties().linear_var_types;
      getProperties().linear_var_types = {};
      return attr;
  }

  ::mlir::Attribute removeNowaitAttr() {
      auto attr = getProperties().nowait;
      getProperties().nowait = {};
      return attr;
  }

  ::mlir::Attribute removeOrderAttr() {
      auto attr = getProperties().order;
      getProperties().order = {};
      return attr;
  }

  ::mlir::Attribute removeOrderModAttr() {
      auto attr = getProperties().order_mod;
      getProperties().order_mod = {};
      return attr;
  }

  ::mlir::Attribute removeOrderedAttr() {
      auto attr = getProperties().ordered;
      getProperties().ordered = {};
      return attr;
  }

  ::mlir::Attribute removePrivateSymsAttr() {
      auto attr = getProperties().private_syms;
      getProperties().private_syms = {};
      return attr;
  }

  ::mlir::Attribute removePrivateNeedsBarrierAttr() {
      auto attr = getProperties().private_needs_barrier;
      getProperties().private_needs_barrier = {};
      return attr;
  }

  ::mlir::Attribute removeReductionModAttr() {
      auto attr = getProperties().reduction_mod;
      getProperties().reduction_mod = {};
      return attr;
  }

  ::mlir::Attribute removeReductionByrefAttr() {
      auto attr = getProperties().reduction_byref;
      getProperties().reduction_byref = {};
      return attr;
  }

  ::mlir::Attribute removeReductionSymsAttr() {
      auto attr = getProperties().reduction_syms;
      getProperties().reduction_syms = {};
      return attr;
  }

  ::mlir::Attribute removeScheduleKindAttr() {
      auto attr = getProperties().schedule_kind;
      getProperties().schedule_kind = {};
      return attr;
  }

  ::mlir::Attribute removeScheduleModAttr() {
      auto attr = getProperties().schedule_mod;
      getProperties().schedule_mod = {};
      return attr;
  }

  ::mlir::Attribute removeScheduleSimdAttr() {
      auto attr = getProperties().schedule_simd;
      getProperties().schedule_simd = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<NamedAttribute> attributes = {});
  static WsloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<NamedAttribute> attributes = {});
  static WsloopOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const WsloopOperands &clauses);
  static WsloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const WsloopOperands &clauses);
  static WsloopOp create(::mlir::ImplicitLocOpBuilder &builder, const WsloopOperands &clauses);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/::mlir::UnitAttr schedule_simd);
  static WsloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/::mlir::UnitAttr schedule_simd);
  static WsloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/::mlir::UnitAttr schedule_simd);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/::mlir::UnitAttr schedule_simd);
  static WsloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/::mlir::UnitAttr schedule_simd);
  static WsloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/::mlir::UnitAttr nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/::mlir::UnitAttr private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/::mlir::UnitAttr schedule_simd);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/bool schedule_simd = false);
  static WsloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/bool schedule_simd = false);
  static WsloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/bool schedule_simd = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/bool schedule_simd = false);
  static WsloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/bool schedule_simd = false);
  static WsloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange allocate_vars, ::mlir::ValueRange allocator_vars, ::mlir::ValueRange linear_vars, ::mlir::ValueRange linear_step_vars, /*optional*/::mlir::ArrayAttr linear_var_types, /*optional*/bool nowait, /*optional*/::mlir::omp::ClauseOrderKindAttr order, /*optional*/::mlir::omp::OrderModifierAttr order_mod, /*optional*/::mlir::IntegerAttr ordered, ::mlir::ValueRange private_vars, /*optional*/::mlir::ArrayAttr private_syms, /*optional*/bool private_needs_barrier, /*optional*/::mlir::omp::ReductionModifierAttr reduction_mod, ::mlir::ValueRange reduction_vars, /*optional*/::mlir::DenseBoolArrayAttr reduction_byref, /*optional*/::mlir::ArrayAttr reduction_syms, /*optional*/::mlir::omp::ClauseScheduleKindAttr schedule_kind, /*optional*/::mlir::Value schedule_chunk, /*optional*/::mlir::omp::ScheduleModifierAttr schedule_mod, /*optional*/bool schedule_simd = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WsloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WsloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WsloopOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WsloopOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 13 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  unsigned getNumAllocateVars() { return getAllocateVars().size(); }
  unsigned getNumAllocatorsVars() { return getAllocatorVars().size(); }







  /// Returns the number of reduction variables.
  unsigned getNumReductionVars() { return getReductionVars().size(); }

};

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::WsloopOp)

namespace mlir::omp {


//===----------------------------------------------------------------------===//
// ::mlir::omp::YieldOp declarations
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
      odsOpName.emplace("omp.yield", odsAttrs.getContext());
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
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<AtomicUpdateOp, DeclareReductionOp, LoopNestOp, PrivateClauseOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
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
    return ::llvm::StringLiteral("omp.yield");
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

} // namespace mlir::omp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::omp::YieldOp)


#endif // GET_OP_CLASSES

