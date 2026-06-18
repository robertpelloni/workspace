/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: GPUOps.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::gpu {

/// Reduce values among workgroup.
/// The `all_reduce` op reduces the value of every work item across a local
///     workgroup. The result is equal for all work items of a workgroup.
/// 
///     For example, both
/// 
///     ```mlir
///     %1 = gpu.all_reduce add %0 {} : (f32) -> (f32)
///     %2 = gpu.all_reduce %0 {
///     ^bb(%lhs : f32, %rhs : f32):
///       %sum = arith.addf %lhs, %rhs : f32
///       "gpu.yield"(%sum) : (f32) -> ()
///     } : (f32) -> (f32)
///     ```
/// 
///     compute the sum of each work item's %0 value. The first version specifies
///     the accumulation as operation, whereas the second version specifies the
///     accumulation as code region. The reduction operation must be one of:
///     *  Integer types: `add`, `mul`, `minui`, `minsi`, `maxui`, `maxsi`, `and`,
///        `or`, `xor`
///     *  Floating point types: `add`, `mul`, `minnumf`, `maxnumf`, `minimumf`,
///        `maximumf`
/// 
///     If `uniform` flag is set either none or all work items of a workgroup
///     need to execute this op in convergence.
class AllReduceOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU memory allocation operation.
/// The `gpu.alloc` operation allocates a region of memory on the GPU. It is
///     similar to the `memref.alloc` op, but supports asynchronous GPU execution.
/// 
///     The op does not execute before all async dependencies have finished
///     executing.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it also returns a !gpu.async.token.
/// 
///     If the `host_shared` keyword is present, the memory will be allocated in a
///     memory accessible both on host and on device.
/// 
///     Example:
/// 
///     ```mlir
///     %memref, %token = gpu.alloc async [%dep] host_shared (%width) : memref<64x?xf32, 1>
///     ```
class AllocOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Synchronizes all work items of a workgroup.
/// The `barrier` op synchronizes all work items of a workgroup. It is used
///     to coordinate communication between the work items of the workgroup.
/// 
///     ```mlir
///     gpu.barrier
///     ```
/// 
///     waits until all work items in the workgroup have reached the operation
///     and all memory accesses made by these work items prior to the op are
///     visible to all work items in the workgroup. Data hazards between work items
///     accessing the same memory can be avoided by synchronizing work items
///     in-between these accesses.
/// 
///     If the `memfence` attribute is specified, the set of memory accesses that must
///     by completed after the barrier resolves is limited to only those accesses that
///     read from or write to the specified address spaces (though accesses to other
///     address spaces may be completed as well, especially if a particular combination
///     of address spaces is not supported on a given backend). In particular,
///     specifying `memfence []` creates a barrier that is not required to affect
///     the visibility of any memory operations and is purely used for synchronizing
///     work items.
/// 
///     ```mlir
///     // Only workgroup address spaces accesses required to be visible.
///     gpu.barrier memfence [#gpu.address_space<workgroup>]
///     // No memory accesses required to be visible.
///     gpu.barrier memfence []
///     // All memory accesses required to be visible.
///     gpu.barrier
///     ```
/// 
///     Either none or all work items of a workgroup need to execute this op
///     in convergence.
class BarrierOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// An Op for storing serialized GPU binary objects.
/// GPU binaries provide a semantic mechanism for storing GPU objects,
///     e.g. the result of compiling a GPU module to an object file.
/// 
///     This operation has 3 arguments:
///      - The name of the binary.
///      - An optional attribute implementing the offloading LLVM translation interface.
///      - An array of GPU object attributes.
/// 
///     During translation, the offloading attribute will be called for translating
///     GPU `binary` and `launch_func` operations. The default offloading handler is:
///     `#gpu.select_object`, this handler selects the first object from the array
///     and embeds it as a string.
/// 
///     Examples:
///     ```
///       // Selects the first object.
///       gpu.binary @myobject [#gpu.object<...>, #gpu.object<...>]
///       // Uses the `#foo.my_handler` for handling the binary during translation.
///       gpu.binary @myobject <#foo.my_handler> [#gpu.object<...>, #gpu.object<...>]
///       // Selects the object with the `#rocdl.target` target attribute.
///       gpu.binary @myobject <#gpu.select_object<#rocdl.target>> [#gpu.object<...>, #gpu.object<#rocdl.target, ...>]
///     ```
class BinaryOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the number of threads in the thread block (aka the block size) along
///     the x, y, or z `dimension`.
/// 
///     Example:
/// 
///     ```mlir
///     %bDimX = gpu.block_dim x
///     ```
/// 
///     If `known_block_size` is set on an this operation's enclosing `gpu.func`,
///     or `gpu.known_block_size` is set on an enclosing `FunctionOpInterface`
///     implementor, or if the enclosing `gpu.launch` specifies a constant size for
///     `dimension`'s blocks, these contextual facts may be used to infer that this
///     operation has a constant value, though such a transformation will not be
///     performed by canonicalization or the default constant folder. Executions which
///     cause that constant-value assumption to be false incur undefined behavior.
/// 
///     If `upper_bound` is set, executions where the bblock size along `dimension`
///     exceeds `upper_bound` cause undefined behavior.
/// 
///     There is an implicit upper bound of `kMaxDim` (currently uint32_t::max).
class BlockDimOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the block id, i.e. the index of the current block within the grid
///     along the x, y, or z `dimension`.
/// 
///     Example:
/// 
///     ```mlir
///     %bIdY = gpu.block_id y
///     ```
/// 
///     If `upper_bound` is set, or if one can be inferred from `known_grid_size`-type
///     annotations in context, executions where the block index in `dimension` would
///     be greater than or equal to that bound cause undefined behavior. `upper_bound`
///     takes priority over bounds inferrable from context.
/// 
///     There is an implicit upper bound of `kMaxDim` (currently uint32_t::max).
class BlockIdOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the block id within the cluster along the x, y, or z `dimension`.
/// 
///     Example:
/// 
///     ```mlir
///     %cBlockIdY = gpu.cluster_block_id y
///     ```
/// 
///     If `upper_bound` is set, then executing (a lowering of) this operation in an
///     environment where the number of thread blocks per cluster along `dimension`
///     is greater than `upper_bound` causes undefined behavior.
/// 
///     There is an implicit upper bound of `kMaxClusterDim` (currently 8).
class ClusterBlockIdOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the number of thread blocks in the cluster along
///     the x, y, or z `dimension`.
/// 
///     Example:
/// 
///     ```mlir
///     %cDimBlocksX = gpu.cluster_dim_blocks x
///     ```
/// 
///     If `upper_bound` is set, then executing (a lowering of) this operation in an
///     environment where the thread blocks per cluster  is greater than `upper_bound`
///     causes undefined behavior.
/// 
///     There is an implicit upper bound of `kMaxClusterDim` (currently 8).
class ClusterDimBlocksOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the number of cluster identifiers per grid along
///     the x, y, or z `dimension`.
/// 
///     Example:
/// 
///     ```mlir
///     %cDimX = gpu.cluster_dim x
///     ```
/// 
///     If `upper_bound` is set, then executing (a lowering of) this operation in an
///     environment where the clusters per grid is greater than `upper_bound` causes
///     undefined behavior.
/// 
///     There is an implicit upper bound of `kMaxDim` (currently uint32_t::max).
class ClusterDimOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the cluster id, i.e. the index of the current cluster within the
///     grid along the x, y, or z `dimension`.
/// 
///     Example:
/// 
///     ```mlir
///     %cIdY = gpu.cluster_id y
///     ```
/// 
///     If `upper_bound` is set, then executing (a lowering of) this operation in an
///     environment where the number of clusters in the grid along `dimension` is
///     greater than `upper_bound` causes undefined behavior.
/// 
///     There is an implicit upper bound of `kMaxDim` (currently uint32_t::max).
class ClusterIdOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Create sparse matrix with 2:4 sparsity operation
/// The `gpu.create_2to4_spmat` operation initializes a sparse matrix in dense
///     format with 2:4 sparsity.
///     The buffers must already be copied from the host to the device prior to
///     using this operation. The operation returns a handle to the sparse
///     matrix descriptor.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %spmat, %token = gpu.create_2to4_spmat async [%dep] {PRUNE_AND_CHECK} %rows, %cols, %mem: memref<?xf64>
///     ```
class Create2To4SpMatOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Create sparse matrix in BSR format operation
/// The `gpu.create_bsr` operation initializes a sparse matrix in BSR format
///     with the given sizes for the matrix and blocks from the given position,
///     index, and values buffers. The buffers must already be copied from the
///     host to the device prior to using this operation. The operation returns
///     a handle to the sparse matrix descriptor.
/// 
///     The BSR format is similar to CSR, where the column indices represent
///     two-dimensional blocks instead of a single matrix entry. Note that this
///     operation (currently) only supports storage with **square** blocks,
///     i.e., `rBlockSize == cBlockSize`.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %spmat, %token = gpu.create_bsr async [%dep]
///        %brows, %bcols, %bnnz, %rBlockSize, %cBlockSize,
///        %bRowPos, %bColIdxs, %values : memref<?xindex>, memref<?xindex>, memref<?xf64>
///     ```
class CreateBsrOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Create sparse matrix in COO format operation (AoS)
/// The `gpu.create_coo_aos` operation initializes a sparse matrix in COO format
///     with the given sizes from the given index and values buffers. The buffers
///     must already be copied from the host to the device prior to using this
///     operation. The operation returns a handle to the sparse matrix descriptor.
///     Unlike the default `gpu.create_coo` operation, this operation builds the
///     COO format from a single index buffer in AoS format (note that this
///     feature has been deprecated in cuSparse 11.2).
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %spmat, %token = gpu.create_coo_aos async [%dep] %rows, %cols, %nnz, %idxs,
///         %values : memref<?xindex>, memref<?xf64>
///     ```
class CreateCooAoSOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Create sparse matrix in COO format operation
/// The `gpu.create_coo` operation initializes a sparse matrix in COO format
///     with the given sizes from the given index and values buffers. The buffers
///     must already be copied from the host to the device prior to using this
///     operation. The operation returns a handle to the sparse matrix descriptor.
///     Note that this operation builds the COO in SoA format.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %spmat, %token = gpu.create_coo async [%dep] %rows, %cols, %nnz, %rowIdx,
///         %colIdx, %values : memref<?xindex>, memref<?xindex>, memref<?xf64>
///     ```
class CreateCooOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Create sparse matrix in CSC format operation
/// The `gpu.create_csc` operation initializes a sparse matrix in CSC format
///     with the given sizes from the given position, index, and values buffers.
///     The buffers must already be copied from the host to the device prior to
///     using this operation. The operation returns a handle to the sparse
///     matrix descriptor.
/// 
///     The CSC format has exactly the same memory layout as its transpose
///     in CSR format (and vice versa).
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %spmat, %token = gpu.create_csc async [%dep] %rows, %cols, %nnz, %colPos,
///         %rowIdx, %values : memref<?xindex>, memref<?xindex>, memref<?xf64>
///     ```
class CreateCscOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Create sparse matrix in CSR format operation
/// The `gpu.create_csr` operation initializes a sparse matrix in CSR format
///     with the given sizes from the given position, index, and values buffers.
///     The buffers must already be copied from the host to the device prior to
///     using this operation. The operation returns a handle to the sparse
///     matrix descriptor.
/// 
///     The CSR format has exactly the same memory layout as its transpose
///     in CSC format (and vice versa).
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %spmat, %token = gpu.create_csr async [%dep] %rows, %cols, %nnz, %rowPos,
///         %colIdx, %values : memref<?xindex>, memref<?xindex>, memref<?xf64>
///     ```
class CreateCsrOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Create dense tensor operation
/// The `gpu.create_dn_tensor` operation initializes a dense tensor from
///     the given values buffer and sizes. The buffer must already be copied
///     from the host to the device prior to using this operation. The
///     operation returns a handle to the dense tensor descriptor.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %dmat, %token = gpu.create_dn_tensor async [%dep] %mem, %dims : index, index into memref<?xf64>
///     ```
class CreateDnTensorOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU memory deallocation operation
/// The `gpu.dealloc` operation frees the region of memory referenced by a
///     memref which was originally created by the `gpu.alloc` operation. It is
///     similar to the `memref.dealloc` op, but supports asynchronous GPU execution.
/// 
///     The op does not execute before all async dependencies have finished
///     executing.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token.
/// 
///     Example:
/// 
///     ```mlir
///     %token = gpu.dealloc async [%dep] %memref : memref<8x64xf32, 1>
///     ```
class DeallocOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Destroy dense tensor operation
/// The `gpu.destroy_dn_tensor` operation releases all resources of a dense
///     tensor represented by a handle that was previously created by a
///     `gpu.create_dn_tensor` operation.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %token = gpu.destroy_dn_tensor async [%dep] %dnTensor
///     ```
class DestroyDnTensorOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Destroy sparse matrix operation
/// The `gpu.destroy_sp_mat` operation releases all resources of a sparse
///     matrix represented by a handle that was previously created by a
///     one of the sparse matrix creation operations.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %token = gpu.destroy_sp_mat async [%dep] %spmat
///     ```
class DestroySpMatOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Get the memref for dynamic shared memory
/// This operation provides a memref pointer to the start of dynamic shared
///     memory, often referred to as workgroup memory. It's important to note that
///     this dynamic shared memory needs to be allocated at kernel launch. One can
///     conveniently utilize the `dynamic_shared_memory_size` parameter of
///     `gpu.launch` for this purpose.
/// 
///     Examples:
///     ```mlir
///     %0 = gpu.dynamic.shared.memory : memref<?xi8, #gpu.address_space<workgroup>>
///     %1 = memref.view %0[%c8192][] : memref<?xi8, #gpu.address_space<workgroup>>
///                             to memref<32x64xf32, #gpu.address_space<workgroup>>
///     %2 = memref.view %0[%c16384][] : memref<?xi8, #gpu.address_space<workgroup>>
///                             to memref<32x64xf32, #gpu.address_space<workgroup>>
///     ```
class DynamicSharedMemoryOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Function executable on a GPU
/// Defines a function that can be executed on a GPU. This supports memory
///     attribution and its body has a particular execution model.
/// 
///     GPU functions are either kernels (as indicated by the `kernel` attribute) or
///     regular functions. The former can be launched from the host side, while the
///     latter are device side only.
/// 
///     The memory attribution defines SSA values that correspond to memory buffers
///     allocated in the memory hierarchy of the GPU (see below).
/// 
///     The operation has one attached region that corresponds to the body of the
///     function. The region arguments consist of the function arguments without
///     modification, followed by buffers defined in memory annotations. The body of
///     a GPU function, when launched, is executed by multiple work items. There are
///     no guarantees on the order in which work items execute, or on the connection
///     between them. In particular, work items are not necessarily executed in
///     lock-step. Synchronization ops such as "gpu.barrier" should be used to
///     coordinate work items. Declarations of GPU functions, i.e. not having the
///     body region, are not supported.
/// 
///     A function may optionally be annotated with the block and/or grid sizes
///     that will be used when it is launched using the `known_block_size` and
///     `known_grid_size` attributes, respectively. If set, these attributes must
///     be arrays of three 32-bit integers giving the x, y, and z launch dimensions.
///     Launching a kernel that has these annotations, or that calls a function with
///     these annotations, using a block size or grid size other than what is specified
///     is undefined behavior. These attributes may be set on non-`gpu.func` functions
///     by using `gpu.known_block_size` or `gpu.known_grid_size`, but this carries
///     the risk that they will de discarded.
/// 
///     Syntax:
/// 
///     ```
///     op ::= `gpu.func` symbol-ref-id `(` argument-list `)` (`->`
///     function-result-list)?
///            memory-attribution `kernel`? function-attributes? region
/// 
///     memory-attribution ::= (`workgroup` `(` ssa-id-and-type-list `)`)?
///                            (`private` `(` ssa-id-and-type-list `)`)?
///     ```
/// 
///     Example:
/// 
///     ```mlir
///     gpu.func @foo(%arg0: index)
///         workgroup(%workgroup: memref<32xf32, 3>)
///         private(%private: memref<1xf32, 5>)
///         kernel
///         attributes {qux: "quux"} {
///       gpu.return
///     }
///     ```
/// 
///     The generic form illustrates the concept
/// 
///     ```mlir
///     "gpu.func"(%arg: index) {sym_name: "foo", kernel, qux: "quux"} ({
///     ^bb0(%arg0: index, %workgroup: memref<32xf32, 3>,
///          %private: memref<1xf32, 5>):
///       "gpu.return"() : () -> ()
///     }) : (index) -> ()
///     ```
/// 
///     Note the non-default memory spaces used in memref types in memory
///     attribution.
class GPUFuncOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// A top level compilation unit containing code to be run on a GPU.
/// GPU module contains code that is intended to be run on a GPU. A host device
///     can launch this code through a gpu.launc_func that creates a fully
///     qualified symbol through the gpu.module's symbol and a gpu.func symbol
///     contained in the gpu.module.
/// 
///     The module's top-level scope is modeled by a single region with a single
///     block. GPU modules are required to have a name that is used for symbol
///     resolution by the gpu.launch_func operation.
/// 
///     Using an op with a region to define a GPU module enables "embedding" GPU
///     modules with SIMT execution models in other dialects in a clean manner and
///     allows filtering of code regions to execute passes on only code intended to
///     or not intended to be run on the separate device.
/// 
///     Modules can contain zero or more target attributes. These attributes encode
///     how to transform modules into binary strings and are used by the
///     `gpu-module-to-binary` pass to transform modules into GPU binaries.
/// 
///     Modules can contain an optional `OffloadingTranslationAttr` attribute. This
///     attribute will be used during the `gpu-module-to-binary` pass to specify the
///     `OffloadingTranslationAttr` used when creating the `gpu.binary` operation.
/// 
///     ```
///     gpu.module @symbol_name {
///       gpu.func {}
///         ...
///     }
///     // Module with offloading handler and target attributes.
///     gpu.module @symbol_name2 <#gpu.select_object<1>> [
///         #nvvm.target,
///         #rocdl.target<chip = "gfx90a">] {
///       gpu.func {}
///         ...
///     }
///     ```
class GPUModuleOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the unique global workitem/thread id, i.e., the unique index of the
///     current workitem/thread within all workgroups / grid along the x, y, or z
///     `dimension`.
/// 
///     Example:
/// 
///     ```mlir
///     %gidX = gpu.global_id x
///     %gidX = gpu.global_id x upper_bound 65536
///     ```
/// 
///     The `upper_bound` attribute defines an upper bound analogously to the ones on
///     `thread_id` and `block_id`. If one is not set, the bound may be inferred from
///     a combination of `known_block_size` and `known_grid_size`-type annotations.
class GlobalIdOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the number of thread blocks in the grid along the x, y, or z
///     `dimension`.
/// 
///     Example:
/// 
///     ```mlir
///     %gDimZ = gpu.grid_dim z
///     ```
/// 
/// 
///     If `known_grid_size` is set on an this operation's enclosing `gpu.func`,
///     or `gpu.known_grid_size` is set on an enclosing `FunctionOpInterface`
///     implementor, or if the enclosing `gpu.launch` specifies a constant size for
///     `dimension`'s grid length, these contextual facts may be used to infer that this
///     operation has a constant value, though such a transformation will not be
///     performed by canonicalization or the default constant folder. Executions which
///     cause that constant-value assumption to be false incur undefined behavior.
/// 
///     If `upper_bound` is set, executions where the grid size in `dimension` would
///     exceed `upper_bound` cause undefined behavior.
/// 
///     There is an implicit upper bound of `kMaxDim` (currently uint32_t::max).
class GridDimOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Registers a memref for access from device.
/// This op maps the provided host buffer into the device address space.
/// 
///     This operation may not be supported in every environment, there is not yet a
///     way to check at runtime whether this feature is supported.
/// 
///     Writes from the host are guaranteed to be visible to device kernels that are
///     launched afterwards. Writes from the device are guaranteed to be visible on
///     the host after synchronizing with the device kernel completion.
class HostRegisterOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Unregisters a memref for access from device.
/// This op unmaps the provided host buffer from the device address space.
/// 
///       This operation may not be supported in every environment, there is not yet a
///           way to check at runtime whether this feature is supported.
class HostUnregisterOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the lane id within the subgroup (warp/wave).
/// 
///     Example:
///     ```mlir
///     %laneId = gpu.lane_id
///     ```
/// 
///     If `upper_bound` is set, executions with more than `upper_bound` lanes per
///     subgroup cause undefined behavior. In the abscence of `upper_bound`,
///     the lane id is still assumed to be non-negative and less than the
///     target-independent `kMaxSubgroupSize` (currently 128).
class LaneIdOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Launches a function as a GPU kernel
/// Launch a kernel function on the specified grid of thread blocks.
///     `gpu.launch` operations are lowered to `gpu.launch_func` operations by
///     outlining the kernel body into a function in a dedicated module, which
///     reflects the separate compilation process. The kernel function is required
///     to have the `gpu.kernel` attribute. The module containing the kernel
///     function is required to be a gpu.module. And finally, the module containing
///     the kernel module (which thus cannot be the top-level module) is required
///     to have the `gpu.container_module` attribute. The `gpu.launch_func`
///     operation has a symbol attribute named `kernel` to identify the fully
///     specified kernel function to launch (both the gpu.module and func).
/// 
///     The `gpu.launch_func` supports async dependencies: the kernel does not start
///     executing until the ops producing those async dependencies have completed.
/// 
///     By the default, the host implicitly blocks until kernel execution has
///     completed. If the `async` keyword is present, the host does not block but
///     instead a `!gpu.async.token` is returned. Other async GPU ops can take this
///     token as dependency.
/// 
///     The operation requires at least the grid and block sizes along the x,y,z
///     dimensions as arguments. When a lower-dimensional kernel is required,
///     unused sizes must be explicitly set to `1`.
/// 
///     The remaining operands are optional. The first optional operand corresponds
///     to the amount of dynamic shared memory a kernel's workgroup should be
///     allocated; when this operand is not present, a zero size is assumed.
/// 
///     The remaining operands if present are passed as arguments to the kernel
///     function.
/// 
///     The `gpu.launch_func` also supports kernel launching with clusters if
///     supported by the target architecture. The cluster size can be set by
///     `clusterSizeX`, `clusterSizeY`, and `clusterSizeZ` arguments. When these
///     arguments are present, the Op launches a kernel that clusters the given
///     thread blocks. This feature is exclusive to certain architectures.
/// 
///     Example:
/// 
///     ```mlir
///     module attributes {gpu.container_module} {
/// 
///       // This module creates a separate compilation unit for the GPU compiler.
///       gpu.module @kernels {
///         func.func @kernel_1(%arg0 : f32, %arg1 : memref<?xf32, 1>)
///             attributes { nvvm.kernel = true } {
/// 
///           // Operations that produce block/thread IDs and dimensions are
///           // injected when outlining the `gpu.launch` body to a function called
///           // by `gpu.launch_func`.
///           %tIdX = gpu.thread_id x
///           %tIdY = gpu.thread_id y
///           %tIdZ = gpu.thread_id z
/// 
///           %bDimX = gpu.block_dim x
///           %bDimY = gpu.block_dim y
///           %bDimZ = gpu.block_dim z
/// 
///           %bIdX = gpu.block_id x
///           %bIdY = gpu.block_id y
///           %bIdZ = gpu.block_id z
/// 
///           %gDimX = gpu.grid_dim x
///           %gDimY = gpu.grid_dim y
///           %gDimZ = gpu.grid_dim z
/// 
///           // (Optional)  Cluster size only for support architectures
///           %cIdX = gpu.cluster_id x
///           %cIdY = gpu.cluster_id y
///           %cIdZ = gpu.cluster_id z
/// 
///           %cDimX = gpu.cluster_dim x
///           %cDimY = gpu.cluster_dim y
///           %cDimZ = gpu.cluster_dim z
/// 
///           "some_op"(%bx, %tx) : (index, index) -> ()
///           %42 = load %arg1[%bx] : memref<?xf32, 1>
///         }
///       }
/// 
///       %t0 = gpu.wait async
///       gpu.launch_func
///           async                           // (Optional) Don't block host, return token.
///           [%t0]                           // (Optional) Execute only after %t0 has completed.
///           @kernels::@kernel_1             // Kernel function.
///           clusters in (%cst, %cst, %cst)  // (Optional) Cluster size only for support architectures.
///           blocks in (%cst, %cst, %cst)    // Grid size.
///           threads in (%cst, %cst, %cst)   // Block size.
///           dynamic_shared_memory_size %s   // (Optional) Amount of dynamic shared
///                                           // memory to allocate for a workgroup.
///           args(%arg0 : f32,               // (Optional) Kernel arguments.
///                %arg1 : memref<?xf32, 1>)
///     }
///     ```
class LaunchFuncOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU kernel launch operation
/// Launch a kernel on the specified grid of thread blocks. The body of the
///     kernel is defined by the single region that this operation contains. The
///     operation takes an optional list of async dependencies followed by six
///     operands and an optional operand.
/// 
///     The `async` keyword indicates the kernel should be launched asynchronously;
///     the operation returns a new !gpu.async.token when the keyword is specified.
///     The kernel launched does not start executing until the ops producing its
///     async dependencies (optional operands) have completed.
/// 
///     The first three operands (following any async dependencies) are grid sizes
///     along the x,y,z dimensions and the following three are block sizes along the
///     x,y,z dimensions. When a lower-dimensional kernel is required, unused sizes
///     must be explicitly set to `1`.  The last operand is optional and corresponds
///     to the amount of dynamic shared memory a kernel's workgroup should be
///     allocated; when this operand is not present, a zero size is assumed.
/// 
///     The body region has at least _twelve_ arguments, or _eighteen_ if cluster
///     dimensions are present, grouped as follows:
/// 
///     -   three optional arguments that contain cluster identifiers along x,y,z
///         dimensions;
///     -   three arguments that contain block identifiers along x,y,z dimensions;
///     -   three arguments that contain thread identifiers along x,y,z dimensions;
///     -   operands of the `gpu.launch` operation as is (i.e. the operands for
///         grid and block sizes).
///     -   a variadic number of Workgroup memory attributions.
///     -   a variadic number of Private memory attributions.
/// 
///     The `function` and `module` attributes are optional and specifies
///     the kernel name and a module in which the kernel should be outlined.
/// 
///     Syntax:
/// 
///     ```
///     operation ::= `gpu.launch` (`async` (`[` ssa-id-list `]`)? )?
///                              ( `clusters` `(` ssa-id-list `)` `in` ssa-reassignment )?
///                              `blocks` `(` ssa-id-list `)` `in` ssa-reassignment
///                              `threads` `(` ssa-id-list `)` `in` ssa-reassignment
///                              (dynamic_shared_memory_size ssa-use)?
///                              (`module(` symbol-ref-id `)`)?
///                              (`function(` symbol-ref-id `)`)?
///                              memory-attribution
///                              region attr-dict?
///     ssa-reassignment ::= `(` ssa-id `=` ssa-use (`,` ssa-id `=` ssa-use)* `)`
///     memory-attribution ::= (`workgroup` `(` ssa-id-and-type-list `)`)?
///                            (`private` `(` ssa-id-and-type-list `)`)?
///     ```
/// 
///     Example:
/// 
///     ```mlir
///     gpu.launch blocks(%bx, %by, %bz) in (%sz_bx = %0, %sz_by = %1, %sz_bz = %2)
///                threads(%tx, %ty, %tz) in (%sz_tx = %3, %sz_ty = %4, %sz_tz = %5) {
///       // Block and thread identifiers, as well as block/grid sizes are
///       // immediately usable inside body region.
///       "some_op"(%bx, %tx) : (index, index) -> ()
///       // Assuming %val1 is defined outside the gpu.launch region.
///       %42 = load %val1[%bx] : memref<?xf32, 1>
///     }
/// 
///     // Generic syntax explains how the pretty syntax maps to the IR structure.
///     "gpu.launch"(%cst, %cst, %c1,  // Grid sizes.
///                  %cst, %c1, %c1)   // Block sizes.
/// 
///         {/*attributes*/}
///         // All sizes and identifiers have "index" size.
///         : (index, index, index, index, index, index) -> () {
///     // The operation passes block and thread identifiers, followed by grid and
///     // block sizes.
///     ^bb0(%bx : index, %by : index, %bz : index,
///          %tx : index, %ty : index, %tz : index,
///          %num_bx : index, %num_by : index, %num_bz : index,
///          %num_tx : index, %num_ty : index, %num_tz : index)
///       "some_op"(%bx, %tx) : (index, index) -> ()
///       %3 = "memref.load"(%val1, %bx) : (memref<?xf32, 1>, index) -> f32
///     }
/// 
///     // Launch with memory attributions.
///     gpu.launch blocks(%bx, %by, %bz) in (%sz_bx = %0, %sz_by = %1, %sz_bz = %2)
///                threads(%tx, %ty, %tz) in (%sz_tx = %3, %sz_ty = %4, %sz_tz = %5)
///                workgroup(%workgroup: memref<32xf32, 3>)
///                private(%private: memref<1xf32, 5>) {
///       // Block and thread identifiers, as well as block/grid sizes are
///       // immediately usable inside body region.
///       "some_op"(%bx, %tx) : (index, index) -> ()
///       // Assuming %val1 is defined outside the gpu.launch region.
///       %42 = load %workgroup[%bx] : memref<32xf32, 3>
///     }
/// 
///     // Launch with clusters.
///     gpu.launch clusters(%cx, %cy, %cz) in (%sz_cx = %0, %sz_cy = %1, %sz_cz = %2)
///                blocks(%bx, %by, %bz) in (%sz_bx = %3, %sz_by = %4, %sz_bz = %5)
///                threads(%tx, %ty, %tz) in (%sz_tx = %6, %sz_ty = %7, %sz_tz = %8)
///     {
///       // Cluster, block and thread identifiers, as well as cluster/block/grid
///       // sizes are immediately usable inside body region.
///       "some_op"(%cx, %bx, %tx) : (index, index, index) -> ()
///     }
/// 
///     // Launch with module and function attributes.
///     gpu.launch blocks(%bx, %by, %bz) in (%sz_bx = %0, %sz_by = %1, %sz_bz = %2)
///                threads(%tx, %ty, %tz) in (%sz_tx = %3, %sz_ty = %4, %sz_tz = %5)
///                module(@kernel_module) function(@kernel_func) {
///       "some_op"(%bx, %tx) : (index, index) -> ()
///       %42 = load %val1[%bx] : memref<?xf32, 1>
///     }
///     ```
/// 
///     Rationale: using operation/block arguments gives analyses a clear way of
///     understanding that a value has additional semantics (e.g., we will need to
///     know what value corresponds to threadIdx.x for coalescing). We can recover
///     these properties by analyzing the operations producing values, but it is
///     easier just to have that information by construction.
class LaunchOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU memcpy operation
/// The `gpu.memcpy` operation copies the content of one memref to another.
/// 
///     The op does not execute before all async dependencies have finished
///     executing.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token.
/// 
///     Example:
/// 
///     ```mlir
///     %token = gpu.memcpy async [%dep] %dst, %src : memref<?xf32, 1>, memref<?xf32>
///     ```
class MemcpyOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU memset operation
/// The `gpu.memset` operation sets the content of memref to a scalar value.
/// 
///     The op does not execute before all async dependencies have finished
///     executing.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token.
/// 
///     Example:
/// 
///     ```mlir
///     %token = gpu.memset async [%dep] %dst, %value : memref<?xf32, 1>, f32
///     ```
class MemsetOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the number of subgroups within a workgroup.
/// 
///     Example:
/// 
///     ```mlir
///     %numSg = gpu.num_subgroups : index
///     ```
/// 
///     If `upper_bound` is set, executions with more than `upper_bound` subgroups
///     per workgroup cause undefined behavior. There is a default upper bound of
///     `kMaxDim` (currently uint32_t::max).
class NumSubgroupsOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Device-side printf, as in CUDA or OpenCL, for debugging
/// `gpu.printf` takes a literal format string `format` and an arbitrary number of
///     scalar arguments that should be printed.
/// 
///     The format string is a C-style printf string, subject to any restrictions
///     imposed by one's target platform.
class PrintfOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Terminator for GPU functions.
/// A terminator operation for regions that appear in the body of `gpu.func`
///     functions. The operands to the `gpu.return` are the result values returned
///     by an invocation of the `gpu.func`.
class ReturnOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Rotate values within a subgroup.
/// The "rotate" op moves values across lanes in a subgroup (a.k.a., local
///     invocations) within the same subgroup. The `width` attribute specifies the
///     number of lanes that participate in the rotation, and must be uniform across
///     all participating lanes. Further, the first `width` lanes of the subgroup
///     must be active.
/// 
///     `width` must be a power of two, and `offset` must be in the range
///     `[0, width)`.
/// 
///     Return the `rotateResult` of the invocation whose id within the group is
///     calculated as follows:
/// 
///     ```mlir
///     Invocation ID = ((LaneId + offset) & (width - 1)) + (LaneId & ~(width - 1))
///     ```
/// 
///     Returns the `rotateResult` and `true` if the current lane id is smaller than
///     `width`, and poison value and `false` otherwise.
/// 
///     example:
/// 
///     ```mlir
///     %1, %2 = gpu.rotate %0, 1, 16 : f32
///     ```
/// 
///     For lane `k`, returns the value from lane `(k + cst1) % width`.
class RotateOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Precompute buffersize for SDDMM operation
/// The `gpu.sddmm_buffer_size` operation returns the buffer size required
///     to perform the SDDMM operation on the given sparse and dense matrices.
///     The operation expects handles returned by previous sparse operations
///     to construct an environment and the operands for SDDMM.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %buffersz, %token = gpu.sddmm_buffer_size async [%dep] %dnmatA{TRANSPOSE}, %dnmatB{TRANSPOSE}, %spmatC into f32
///     ```
/// 
///     The matrix arguments can also be associated with one of the following
///     operators: NON_TRANSPOSE, TRANSPOSE, CONJUGATE_TRANSPOSE. The default value
///     is NON_TRANSPOSE.
class SDDMMBufferSizeOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// SDDMM operation
/// The `gpu.sddmm` operation performs the SDDMM operation on the given sparse and
///     dense matrices, and buffer.  The operation expects handles returned by previous
///     sparse operations to construct an environment and the operands for SDDMM. The
///     buffer must have been allocated on the device.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %token = gpu.sddmm async [%dep] %dnmatA{TRANSPOSE}, %dnmatB{TRANSPOSE}, %spmatC, %buffer into f32
///     ```
/// 
///     The matrix arguments can also be associated with one of the following
///     operators: NON_TRANSPOSE, TRANSPOSE, CONJUGATE_TRANSPOSE. The default value
///     is NON_TRANSPOSE.
class SDDMMOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// SpGEMM get size operation
/// The `gpu.set_csr_pointers` assigns the given positions, coordinates,
///     and values buffer that reside on the device directly to the given sparse
///     matrix descriptor in csr format.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a `!gpu.async.token` in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %token = gpu.set_csr_pointers async [%dep] %positions, %coordinates, %values
///           : memref<?xf32>, memref<?xindex>, memref<?xindex>
///     ```
class SetCsrPointersOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Set default GPU for operations after this by index
/// Operation that sets the current default GPU, using a zero-based index
///     into the set of GPUs on the system. The default GPU setting may be
///     thread-local.
class SetDefaultDeviceOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Shuffles values within a subgroup.
/// The "shuffle" op moves values across lanes in a subgroup (a.k.a., local
///     invocation) within the same subgroup. The `width` argument specifies the
///     number of lanes that participate in the shuffle, and must be uniform
///     across all lanes. Further, the first `width` lanes of the subgroup must
///     be active.
/// 
///     The intepretation of the `offset` arguments depends on the selected
///     `mode`.
/// 
///     Returns the `shuffleResult` and `true` if the current lane id is smaller
///     than `width`, and an unspecified value and `false` otherwise.
/// 
///     `xor` example:
/// 
///     ```mlir
///     %1, %2 = gpu.shuffle xor %0, %offset, %width : f32
///     ```
/// 
///     For lane `k`, returns the value `%0` from lane `k ^ offset`. Every lane
///     trades value with exactly one other lane.
/// 
///     `down` example:
/// 
///     ```mlir
///     %cst1 = arith.constant 1 : i32
///     %3, %4 = gpu.shuffle down %0, %cst1, %width : f32
///     ```
/// 
///     For lane `k`, returns the value from lane `(k + cst1)`. If `(k + cst1)` is
///     bigger than or equal to `width`, the value is poison and `valid` is `false`.
/// 
///     `up` example:
/// 
///     ```mlir
///     %cst1 = arith.constant 1 : i32
///     %5, %6 = gpu.shuffle up %0, %cst1, %width : f32
///     ```
/// 
///     For lane `k`, returns the value from lane `(k - cst1)`. If `(k - cst1)` is
///     smaller than `0`, the value is poison and `valid` is `false`.
/// 
///     `idx` example:
/// 
///     ```mlir
///     %cst0 = arith.constant 0 : i32
///     %7, %8 = gpu.shuffle idx %0, %cst0, %width : f32
///     ```
/// 
///     Broadcasts the value from lane 0 to all lanes.
class ShuffleOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// SpGEMM copy operation
/// The `gpu.spgemm_copy` operation copies the sparse matrix result of
///     a SpGEMM computation.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a `!gpu.async.token` in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     gpu.spgemm_copy %spmatA, %spmatB, %spmatC, %spgemmDesc: f32
///     ```
/// 
///     The matrix arguments can also be associated with one of the following
///     operators: NON_TRANSPOSE, TRANSPOSE, CONJUGATE_TRANSPOSE. The default value
///     is NON_TRANSPOSE.
class SpGEMMCopyOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// SpGEMM Create Descr operation
/// The `gpu.spgemm_create_descr` creates a descriptor for the SpGEMM operation.
///     The descriptor describes the SpGEMM operation and stores the internal data
///     throughout the computation. It needs to be passed as an argument to
///     spgemm_* operations.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a `!gpu.async.token` in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %desc, %token = gpu.spgemm_create_descr async [%dep]
///     ```
class SpGEMMCreateDescrOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// SpGEMM Destroy Descr operation
/// The `gpu.spgemm_destroy_descr` destroys the SpGEMM operation descriptor.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a `!gpu.async.token` in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %token = gpu.spgemm_destroy_descr async [%dep] %desc
///     ```
class SpGEMMDestroyDescrOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// SpGEMM work estimation operation
/// The `gpu.spgemm_work_estimation_or_compute` is used to call
///     cusparseSpGEMM_workEstimation or cusparseSpGEMM_compute. Both of them are
///     for both determining the buffer size and performing the actual computation.
///     The operation expects handles returned by previous sparse operations to
///     construct an environment and the operands for SpGEMM.
///     The buffer must have been allocated on the device.
/// 
///     C' = alpha * op(A) * op(B) + beta * C
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a `!gpu.async.token` in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %bufferSz, %token = gpu.spgemm_work_estimation_or_compute async [%dep] {COMPUTE}
///                           %desc, %spmatA{NON_TRANSPOSE}, %spmatB{NON_TRANSPOSE},
///                           %spmatC, %spgemmDesc, %c0, %alloc: f32 into
///                           memref<0xi8>
///     ```
/// 
///     The matrix arguments can also be associated with one of the following
///     operators: NON_TRANSPOSE, TRANSPOSE, CONJUGATE_TRANSPOSE. The default value
///     is NON_TRANSPOSE.
class SpGEMMWorkEstimationOrComputeOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Precompute buffersize for SpMM operation
/// The `gpu.spmm_buffer_size` operation returns the buffer size required
///     to perform the SpMM operation on the given sparse and dense matrix.
///     The operation expects handles returned by previous sparse operations
///     to construct an environment and the operands for SpMM.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     The matrix arguments can also be associated with one of the following
///     operators: NON_TRANSPOSE, TRANSPOSE, CONJUGATE_TRANSPOSE. The default value
///     is NON_TRANSPOSE.
/// 
///     Example:
/// 
///     ```mlir
///     %bufferszs, %token = gpu.spmm_buffer_size async [%dep] %spmatA{TRANSPOSE}, %dnmatB{TRANSPOSE}, %dnmatC : i64 into f32
///     ```
class SpMMBufferSizeOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// SpMM operation
/// The `gpu.spmm` operation performs the SpMM operation on the given sparse and
///     dense matrix, and buffer.  The operation expects handles returned by previous
///     sparse operations to construct an environment and the operands for SpMM. The
///     buffer must have been allocated on the device.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     The matrix arguments can also be associated with one of the following
///     operators: NON_TRANSPOSE, TRANSPOSE, CONJUGATE_TRANSPOSE. The default value
///     is NON_TRANSPOSE.
/// 
///     Example:
/// 
///     ```mlir
///     %token = gpu.spmm async [%dep] %spmatA{TRANSPOSE}, %dnmatB{TRANSPOSE}, %dnmatC, %buffers : type($buffers) into f32
///     ```
class SpMMOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Precompute buffersize for SpMV operation
/// The `gpu.spmv_buffer_size` operation returns the buffer size required
///     to perform the SpMV operation on the given sparse matrix and dense vectors.
///     The operation expects handles returned by previous sparse operations
///     to construct an environment and the operands for SpMV.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     The matrix arguments can also be associated with one of the following
///     operators: NON_TRANSPOSE, TRANSPOSE, CONJUGATE_TRANSPOSE. The default value
///     is NON_TRANSPOSE.
/// 
///     Example:
/// 
///     ```mlir
///     %buffersz, %token = gpu.spmv_buffer_size async [%dep] %spmatA{TRANSPOSE}, %dnX, %dnY into f32
///     ```
class SpMVBufferSizeOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// SpMV operation
/// The `gpu.spmv` operation performs the SpMV operation on the given sparse matrix,
///     dense vectors, and buffer.  The operation expects handles returned by previous
///     sparse operations to construct an environment and the operands for SpMV. The
///     buffer must have been allocated on the device.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a !gpu.async.token in addition to the environment.
/// 
///     The matrix arguments can also be associated with one of the following
///     operators: NON_TRANSPOSE, TRANSPOSE, CONJUGATE_TRANSPOSE. The default value
///     is NON_TRANSPOSE.
/// 
///     Example:
/// 
///     ```mlir
///     %token = gpu.spmv async [%dep] %spmatA{TRANSPOSE}, %dnX, %dnY : memref<?xf64> into bf16
///     ```
class SpMVOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// SpMat get size operation
/// The `gpu.spmat_get_size` operation retrieves the number of rows, number of
///     columns, and number of non-zero elements of a sparse matrix.
/// 
///     If the `async` keyword is present, the op is executed asynchronously (i.e.
///     it does not block until the execution has finished on the device). In
///     that case, it returns a `!gpu.async.token` in addition to the environment.
/// 
///     Example:
/// 
///     ```mlir
///     %rows, %cols, %nnz, %token = gpu.spmat_get_size async [%dep] %spmatC
///     ```
class SpMatGetSizeOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Broadcasts a value from the specific lane across subgroup
/// Broadcasts a value from one lane to all active lanes in a subgroup. The
///       result is guaranteed to be uniform across the active lanes in subgroup.
/// 
///       The possible broadcast types are:
/// 
///       * `first_active_lane` - broadcasts the value from the first active lane
///       in the subgroup.
///       * `specific_lane` - broadcasts from the specified lane. The lane index
///       must be uniform and within the subgroup size. The result is poison if the
///       lane index is invalid, non subgroup-uniform, or if the source lane is not
///       active.
class SubgroupBroadcastOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the subgroup id, i.e., the index of the current subgroup within the
///     workgroup.
/// 
///     Example:
/// 
///     ```mlir
///     %sgId = gpu.subgroup_id : index
///     ```
/// 
///     Executions where there are more than `upper_bound` subgroups per workgroup
///     cause undefined behavior. There is an implicit upper bound of `kMaxDim`
///     (currently uint32_t::max).
class SubgroupIdOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU warp synchronous matrix multiply accumulate
/// The `gpu.subgroup_mma_compute` operation performs a matrix-multiply accumulate (mma)
///     operation using all the threads in a subgroup.
/// 
///     This operation takes three `!gpu.mma_matrix`s as arguments: these hold `A`,
///     `B` and `C`operands for the mma operation. The operation performed is represented
///     as `C += A * B`. The op returns a `!gpu.mma_matrix` which contains the result of
///     the operation held by all threads in a subgroup. `a_transpose` or
///     `b_transpose` if present, signify that the respective operand was loaded in a
///     transposed manner. The transpose operands are required to map to correct
///     underlying intrisics but they currently do not seem to affect correctness
///     even if they are absent given that the operands were loaded correctly using
///     the `transpose` attribute in `gpu.subgroup_mma_load_matrix` op.
/// 
///     For integer types, the `A` and `B` matrices carry their signedness with their
///     types. The accumulator type is expected to be signless and imply a signed integer
///     with a greater width than the other two operands.
/// 
///     This op is meant to be used along with `gpu.subgroup_mma_store_matrix` and
///     `gpu.subgroup_mma_load_matrix` ops.
/// 
///     Example:
/// 
///     ```mlir
///     %D = gpu.subgroup_mma_compute_matrix %A, %B, %C :
///       !gpu.mma_matrix<16x16xf16, "AOp">, !gpu.mma_matrix<16x16xf16, "BOp">>
///       -> !gpu.mma_matrix<16x16xf16, "COp">
///     ```
class SubgroupMmaComputeOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU warp synchronous constant matrix
/// The `gpu.subgroup_mma_constant_matrix` creates a `!gpu.mma_matrix` with
///     constant elements.
/// 
///     The operation takes a scalar input and return a `!gpu.mma_matrix` where
///     each element of is equal to the operand constant. The destination
///     mma_matrix type must have elememt type equal to the constant type. Since
///     the layout of `!gpu.mma_matrix` is opaque this only support setting all the
///     elements to the same value.
/// 
///     This op is meant to be used along with `gpu.subgroup_mma_compute`.
/// 
///     Example:
/// 
///     ```mlir
///      %0 = gpu.subgroup_mma_constant_matrix %a :
///        !gpu.mma_matrix<16x16xf16, "AOp">
///      %1 = gpu.subgroup_mma_constant_matrix %b :
///        !gpu.mma_matrix<16x16xf32, "COp">
///     ```
class SubgroupMmaConstantMatrixOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU warp elementwise operation on a matrix
/// The `gpu.subgroup_mma_elementwise` takes `!gpu.mma_matrix` inputs and
///     compute a new `!gpu.mma_matrix` by applying an elementwise operation to each
///     element.
/// 
///     Since the operation is elementwise and the matrix type must match, the
///     matrix elements are processed independently of the matrix layout.
/// 
///     This op is meant to be used along with `gpu.subgroup_mma_compute`.
/// 
///     Example:
/// 
///     ```mlir
///      %0 =  %A, %B { opType = "ADD" } :
///       (!gpu.mma_matrix<16x16xf16, "COp">, !gpu.mma_matrix<16x16xf16, "COp">)
///       -> !gpu.mma_matrix<16x16xf16, "COp">
///     ```
class SubgroupMmaElementwiseOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Extract a value from GPU warp by invocation and indices
/// The `gpu.subgroup_mma_extract_thread_local` operation extracts a value from `!gpu.mma_matrix`
///     that is stored at subgroup level.
/// 
///     This operation takes `!gpu.mma_matrix` as its first operand. It is the source
///     matrix across a subgroup. The op returns a scalar value stored in the invocation
///     in the subgroup.
/// 
///     Since `matrix` is packed into the the threads within a subgroup, `indices` are
///     the indices into the values stored by each thread. That is, an index of 0 (or [0, 0])
///     does not necessarily refer to the first element of the matrix, but the first element
///     that a particular thread holds.
/// 
///     The mapping of matrix elements to threads is not defined by this operation and may
///     not be defined by some lowerings (such as the lowering to SPIR-V). However, if the
///     size of the subgroup is S, then `subgroup_mma_extract_thread_local` at each index in
///     `[0, (M * N) / S)` will have the entire matrix extracted across the subgroup.
/// 
///     Example:
/// 
///     ```mlir
///     %c0 = arith.constant 0 : index
///     %val = gpu.subgroup_mma_extract_thread_local %m[%c0] : !gpu.mma_matrix<16x16xf32, "AOp"> -> f32
///     ```
class SubgroupMmaExtractThreadLocalOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Insert a value into GPU warp by invocation and indices
/// The `gpu.subgroup_mma_insert_thread_local` operation inserts a value to `!gpu.mma_matrix`
///     that is stored at subgroup level.
/// 
///     This operation takes scalar value as its first operand and `!gpu.mma_matrix`
///     as its second operand. The op inserts the scalar value to the matrix.
/// 
///     Since `matrix` is packed into the the threads within a subgroup, `indices` are
///     the indices into the values stored by each thread. That is, an index of 0 (or [0, 0])
///     does not necessarily refer to the first element of the matrix, but the first element
///     that a particular thread holds.
/// 
///     The mapping of matrix elements to threads is not defined by this operation and may
///     not be defined by some lowerings (such as the lowering to SPIR-V). However, if the
///     size of the subgroup is S, then `subgroup_mma_insert_thread_local` at each index in
///     `[0, (M * N) / S)` will have the entire matrix inserted across the subgroup.
/// 
///     The op returns `!gpu.mma_matrix` with the updated value.
/// 
///     Example:
/// 
///     ```mlir
///     %c0 = arith.constant 0 : index
///     %s0 = gpu.subgroup_mma_insert_thread_local %val, %m[%c0] : f16, !gpu.mma_matrix<16x16xf16, "COp">
///             -> !gpu.mma_matrix<16x16xf16, "COp">
///     ```
class SubgroupMmaInsertThreadLocalOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU warp synchronous matrix load
/// The `gpu.subgroup_mma_load_matrix` operation loads a matrix collectively
///     using all the threads in a subgroup.
/// 
///     This operation takes a memref as its first operand: it is the source matrix
///     from which data is to be loaded. The op returns a `!gpu.mma_matrix`. The
///     source memref can be in global memory or shared memory. The load address is
///     determined using `indices`. The matrix being loaded into is the result.  The
///     `leadDimension` attribute specifies the leading dimension size of the source
///     matrix which eventually allows the lowering to determine the size of each
///     row.  If the `transpose` attribute is present then the op does a transposed load.
/// 
///     For integer types, the resulting `!gpu.mma_matrix` type needs to specify the
///     signedness of the data if the matrix type is an `A` or `B` operand for
///     `gpu.subgroup_mma_compute`.
/// 
///     This op is often meant to be used along with `gpu.subgroup_mma_store_matrix` and
///     `gpu.subgroup_mma_compute`.
/// 
///     Example:
/// 
///     ```mlir
///      %0 = gpu.subgroup_mma_load_matrix src[%i,%j] : {leadDimension = 32 : i32}
///           : memref<32x32xf16, 3>, !gpu.mma_matrix<16x16xf16, "AOp">
///     ```
class SubgroupMmaLoadMatrixOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU warp synchronous matrix store
/// The `gpu.subgroup_mma_store_matrix` operation stores a matrix collectively
///     using all the threads in a subgroup.
/// 
///     This operation takes a `!gpu.mma_matrix` and a memref as operands.
///     `!gpu.mma_matrix` is the source value containing the data to be stored into the
///     destination memref which can be in global or shared memory.  The store address
///     is determined using the indices provided. The `leadDimension` attribute
///     specifies the leading dimension of the destination matrix. If the
///     `transpose` attribute is present then the op does a transposed store.
/// 
///     This op is often meant to be used along with `gpu.subgroup_mma_load_matrix` and
///     `gpu.subgroup_mma_compute`.
/// 
///     Example:
/// 
///     ```mlir
///     gpu.subgroup_mma_store_matrix %D, %sg[%i,%j] : { leadDimension = 32 : i32}
///                     : !gpu.mma_matrix<16x16xf16, "COp">, memref<32x32xf16, 3>
///     ```
class SubgroupMmaStoreMatrixOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Reduce values among subgroup.
/// The `subgroup_reduce` op reduces the values of lanes (work items) across a
///     subgroup.
/// 
///     The subgroup is divided into clusters starting at lane index 0. Within each
///     cluster, there are `size` lanes, and the lane index advances by `stride`.
///     A reduction is done for each cluster in parallel: every lane in the cluster
///     is reduced, and the result is equal for all lanes in the cluster. If `size`
///     is omitted, there is a single cluster covering the entire subgroup. If
///     `stride` is omitted, the stride is 1 (the cluster's lanes are contiguous).
/// 
///     When the reduced value is of a vector type, each vector element is reduced
///     independently. Only 1-d vector types are allowed.
/// 
///     Example:
/// 
///     ```mlir
///     %1 = gpu.subgroup_reduce add %a : (f32) -> f32
///     %2 = gpu.subgroup_reduce add %b : (vector<4xf16>) -> vector<4xf16>
///     %3 = gpu.subgroup_reduce add %c cluster(size = 4) : (f32) -> f32
///     %3 = gpu.subgroup_reduce add %c cluster(size = 4, stride = 2) : (f32) -> f32
///     ```
/// 
///     If `uniform` flag is set either none or all lanes of a subgroup need to execute
///     this op in convergence.
/// 
///     The reduction operation must be one of:
///     *  Integer types: `add`, `mul`, `minui`, `minsi`, `maxui`, `maxsi`, `and`,
///        `or`, `xor`
///     *  Floating point types: `add`, `mul`, `minnumf`, `maxnumf`, `minimumf`,
///        `maximumf`
class SubgroupReduceOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the number of threads within a subgroup.
/// 
///     Example:
/// 
///     ```mlir
///     %sgSz = gpu.subgroup_size : index
///     ```
/// 
///     Executions where the number of threads per subgroup exceed `upper_bound` cause
///     undefined behavior. When no `upper_bound` is specified, range analyses and
///     similar machinery assume the default bound of `kMaxSubgroupSize`, currently
///     128.
class SubgroupSizeOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Terminator for GPU launch regions.
/// A terminator operation for regions that appear in the body of `gpu.launch`
///     operation.  These regions are not expected to return any value so the
///     terminator takes no operands.
class TerminatorOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Returns the thread id, i.e. the index of the current thread within the block
///     along the x, y, or z `dimension`.
/// 
///     Example:
/// 
///     ```mlir
///     %tIdX = gpu.thread_id x
///     ```
/// 
///     If `upper_bound` is set, or if one can be inferred from `known_block_size`-type
///     annotations in context, executions where the thread index would be greater
///     than or equal to that bound cause undefined behavior.
/// 
///     There is an implicit upper bound of `kMaxDim` (currently uint32_t::max).
class ThreadIdOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Wait for async gpu ops to complete.
/// This op synchronizes the host or the device with a list of dependent ops.
/// 
///     If the op contains the `async` keyword, it returns a new async token which
///     is synchronized with the op arguments. This new token is merely a shortcut
///     to the argument list, and one could replace the uses of the result with the
///     arguments for the same effect. The async version of this op is primarily
///     used to make each async token have a single use during lowering and
///     thereby make forks in async execution explicit. Example usage:
/// 
///     ```mlir
///     %t0 = gpu.foo async : !gpu.async.token
///     %t1 = gpu.bar async : !gpu.async.token
///     %t2 = gpu.wait async [%t0, %t1]
///     // gpu.baz doesn't run until gpu.foo and gpu.bar have both completed, just
///     // as if the async dependencies were [%t0, %t1].
///     %t3 = gpu.baz async [%t2]
///     ```
/// 
///     If the op does not contain the `async` keyword, it does not return a new
///     async token but blocks until all ops producing the async dependency tokens
///     finished execution. All dependent memory operations are visible to the host
///     once this op completes. Example usage:
/// 
///     ```mlir
///     %t0 = gpu.foo async : !gpu.async.token
///     %t1 = gpu.bar async : !gpu.async.token
///     // The gpu.wait op blocks until gpu.foo and gpu.bar have completed.
///     gpu.wait [%t0, %t1]
///     ```
class WaitOp;

} // namespace mlir::gpu
namespace mlir::gpu {

/// Executes operations in the associated region on thread #0 of aSPMD program
/// `warp_execute_on_lane_0` is an operation used to bridge the gap between
///     vector programming and SPMD programming model like GPU SIMT. It allows to
///     trivially convert a region of vector code meant to run on a multiple threads
///     into a valid SPMD region and then allows incremental transformation to
///     distribute vector operations on the threads.
/// 
///     Any code present in the region would only be executed on first thread/lane
///     based on the `laneid` operand. The `laneid` operand is an integer ID between
///     [0, `warp_size`). The `warp_size` attribute indicates the number of lanes in
///     a warp.
/// 
///     Operands are vector values distributed on all lanes that may be used by
///     the single lane execution. The matching region argument is a vector of all
///     the values of those lanes available to the single active lane. The
///     distributed dimension is implicit based on the shape of the operand and
///     argument. the properties of the distribution may be described by extra
///     attributes (e.g. affine map).
/// 
///     Return values are distributed on all lanes using laneId as index. The
///     vector is distributed based on the shape ratio between the vector type of
///     the yield and the result type.
///     If the shapes are the same this means the value is broadcasted to all lanes.
///     In the future the distribution can be made more explicit using affine_maps
///     and will support having multiple Ids.
/// 
///     Therefore the `warp_execute_on_lane_0` operations allow to implicitly copy
///     between lane0 and the lanes of the warp. When distributing a vector
///     from lane0 to all the lanes, the data are distributed in a block cyclic way.
///     For example `vector<64xf32>` gets distributed on 32 threads and map to
///     `vector<2xf32>` where thread 0 contains vector[0] and vector[1].
/// 
///     During lowering values passed as operands and return value need to be
///     visible to different lanes within the warp. This would usually be done by
///     going through memory.
/// 
///     The region is *not* isolated from above. For values coming from the parent
///     region not going through operands only the lane 0 value will be accesible so
///     it generally only make sense for uniform values.
/// 
///     Example:
///     ```
///     // Execute in parallel on all threads/lanes.
///     gpu.warp_execute_on_lane_0 (%laneid)[32] {
///       // Serial code running only on thread/lane 0.
///       ...
///     }
///     // Execute in parallel on all threads/lanes.
///     ```
/// 
///     This may be lowered to an scf.if region as below:
///     ```
///       // Execute in parallel on all threads/lanes.
///       %cnd = arith.cmpi eq, %laneid, %c0 : index
///       scf.if %cnd {
///         // Serial code running only on thread/lane 0.
///         ...
///       }
///       // Execute in parallel on all threads/lanes.
///     ```
/// 
///     When the region has operands and/or return values:
///     ```
///     // Execute in parallel on all threads/lanes.
///     %0 = gpu.warp_execute_on_lane_0(%laneid)[32]
///     args(%v0 : vector<4xi32>) -> (vector<1xf32>) {
///     ^bb0(%arg0 : vector<128xi32>) :
///       // Serial code running only on thread/lane 0.
///       ...
///       gpu.yield %1 : vector<32xf32>
///     }
///     // Execute in parallel on all threads/lanes.
///     ```
/// 
///     values at the region boundary would go through memory:
///     ```
///     // Execute in parallel on all threads/lanes.
///     ...
///     // Store the data from each thread into memory and Synchronization.
///     %tmp0 = memreg.alloc() : memref<128xf32>
///     %tmp1 = memreg.alloc() : memref<32xf32>
///     %cnd = arith.cmpi eq, %laneid, %c0 : index
///     vector.store %v0, %tmp0[%laneid] : memref<128xf32>, vector<4xf32>
///     some_synchronization_primitive
///     scf.if %cnd {
///       // Serialized code running only on thread 0.
///       // Load the data from all the threads into a register from thread 0. This
///       // allow threads 0 to access data from all the threads.
///       %arg0 = vector.load %tmp0[%c0] : memref<128xf32>, vector<128xf32>
///       ...
///       // Store the data from thread 0 into memory.
///       vector.store %1, %tmp1[%c0] : memref<32xf32>, vector<32xf32>
///     }
///     // Synchronization and load the data in a block cyclic way so that the
///     // vector is distributed on all threads.
///     some_synchronization_primitive
///     %0 = vector.load %tmp1[%laneid] : memref<32xf32>, vector<32xf32>
///     // Execute in parallel on all threads/lanes.
///     ```
class WarpExecuteOnLane0Op;

} // namespace mlir::gpu
namespace mlir::gpu {

/// GPU yield operation
/// `gpu.yield` is a special terminator operation for blocks inside regions
///     in gpu ops. It returns values to the immediately enclosing gpu op.
/// 
///     Example:
/// 
///     ```mlir
///     gpu.yield %f0, %f1 : f32, f32
///     ```
class YieldOp;

} // namespace mlir::gpu
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::AllReduceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllReduceOpGenericAdaptorBase {
public:
  struct Properties {
    using opTy = ::mlir::gpu::AllReduceOperationAttr;
    opTy op;

    auto getOp() const {
      auto &propStorage = this->op;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::AllReduceOperationAttr>(propStorage);
    }
    void setOp(const ::mlir::gpu::AllReduceOperationAttr &propValue) {
      this->op = propValue;
    }
    using uniformTy = ::mlir::UnitAttr;
    uniformTy uniform;

    auto getUniform() const {
      auto &propStorage = this->uniform;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setUniform(const ::mlir::UnitAttr &propValue) {
      this->uniform = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.op == this->op &&
        rhs.uniform == this->uniform &&
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
  AllReduceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.all_reduce", odsAttrs.getContext());
  }

  AllReduceOpGenericAdaptorBase(AllReduceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::AllReduceOperationAttr getOpAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::gpu::AllReduceOperationAttr>(getProperties().op);
    return attr;
  }

  ::std::optional<::mlir::gpu::AllReduceOperation> getOp();
  ::mlir::UnitAttr getUniformAttr();
  bool getUniform();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class AllReduceOpGenericAdaptor : public detail::AllReduceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllReduceOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  AllReduceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllReduceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllReduceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllReduceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AllReduceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllReduceOpGenericAdaptor(RangeT values, const AllReduceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllReduceOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllReduceOp>>>
  AllReduceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AllReduceOpAdaptor : public AllReduceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllReduceOpGenericAdaptor::AllReduceOpGenericAdaptor;
  AllReduceOpAdaptor(AllReduceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllReduceOp : public ::mlir::Op<AllReduceOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllReduceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllReduceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("op"), ::llvm::StringRef("uniform")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOpAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOpAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUniformAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUniformAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.all_reduce");
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

  ::mlir::TypedValue<::mlir::Type> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  ::mlir::gpu::AllReduceOperationAttr getOpAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::AllReduceOperationAttr>(getProperties().op);
  }

  ::std::optional<::mlir::gpu::AllReduceOperation> getOp();
  ::mlir::UnitAttr getUniformAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().uniform);
  }

  bool getUniform();
  void setOpAttr(::mlir::gpu::AllReduceOperationAttr attr) {
    getProperties().op = attr;
  }

  void setOp(::std::optional<::mlir::gpu::AllReduceOperation> attrValue);
  void setUniformAttr(::mlir::UnitAttr attr) {
    getProperties().uniform = attr;
  }

  void setUniform(bool attrValue);
  ::mlir::Attribute removeOpAttr() {
      auto attr = getProperties().op;
      getProperties().op = {};
      return attr;
  }

  ::mlir::Attribute removeUniformAttr() {
      auto attr = getProperties().uniform;
      getProperties().uniform = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/bool uniform = false);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/bool uniform = false);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/bool uniform = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/bool uniform = false);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/bool uniform = false);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/bool uniform = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/bool uniform = false);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/bool uniform = false);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::gpu::AllReduceOperationAttr op, /*optional*/bool uniform = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::AllReduceOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::AllocOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllocOpGenericAdaptorBase {
public:
  struct Properties {
    using hostSharedTy = ::mlir::UnitAttr;
    hostSharedTy hostShared;

    auto getHostShared() const {
      auto &propStorage = this->hostShared;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setHostShared(const ::mlir::UnitAttr &propValue) {
      this->hostShared = propValue;
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
        rhs.hostShared == this->hostShared &&
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
      odsOpName.emplace("gpu.alloc", odsAttrs.getContext());
  }

  AllocOpGenericAdaptorBase(AllocOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getHostSharedAttr();
  bool getHostShared();
};

} // namespace detail
template <typename RangeT>
class AllocOpGenericAdaptor : public detail::AllocOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllocOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dynamicSizes = 1;
  static constexpr int odsIndex_symbolOperands = 2;
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

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  RangeT getDynamicSizes() {
    return getODSOperands(1);
  }

  RangeT getSymbolOperands() {
    return getODSOperands(2);
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
class AllocOp : public ::mlir::Op<AllocOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllocOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllocOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dynamicSizes = 1;
  static constexpr int odsIndex_symbolOperands = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("hostShared"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getHostSharedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getHostSharedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.alloc");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getDynamicSizes() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getSymbolOperands() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::MutableOperandRange getDynamicSizesMutable();
  ::mlir::MutableOperandRange getSymbolOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::UnitAttr getHostSharedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().hostShared);
  }

  bool getHostShared();
  void setHostSharedAttr(::mlir::UnitAttr attr) {
    getProperties().hostShared = attr;
  }

  void setHostShared(bool attrValue);
  ::mlir::Attribute removeHostSharedAttr() {
      auto attr = getProperties().hostShared;
      getProperties().hostShared = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type memref, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::UnitAttr hostShared);
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type memref, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::UnitAttr hostShared);
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type memref, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::UnitAttr hostShared);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::UnitAttr hostShared);
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::UnitAttr hostShared);
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/::mlir::UnitAttr hostShared);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type memref, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/bool hostShared = false);
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type memref, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/bool hostShared = false);
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type memref, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/bool hostShared = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/bool hostShared = false);
  static AllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/bool hostShared = false);
  static AllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::ValueRange dynamicSizes, ::mlir::ValueRange symbolOperands, /*optional*/bool hostShared = false);
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
  MemRefType getType() { return ::llvm::cast<MemRefType>(getMemref().getType()); }
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::AllocOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::BarrierOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BarrierOpGenericAdaptorBase {
public:
  struct Properties {
    using address_spacesTy = ::mlir::ArrayAttr;
    address_spacesTy address_spaces;

    auto getAddressSpaces() const {
      auto &propStorage = this->address_spaces;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setAddressSpaces(const ::mlir::ArrayAttr &propValue) {
      this->address_spaces = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.address_spaces == this->address_spaces &&
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
  BarrierOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.barrier", odsAttrs.getContext());
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

  ::mlir::ArrayAttr getAddressSpacesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().address_spaces);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getAddressSpaces();
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
class BarrierOp : public ::mlir::Op<BarrierOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BarrierOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BarrierOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("address_spaces")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAddressSpacesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAddressSpacesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.barrier");
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
  ::mlir::ArrayAttr getAddressSpacesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().address_spaces);
  }

  ::std::optional< ::mlir::ArrayAttr > getAddressSpaces();
  void setAddressSpacesAttr(::mlir::ArrayAttr attr) {
    getProperties().address_spaces = attr;
  }

  ::mlir::Attribute removeAddressSpacesAttr() {
      auto attr = getProperties().address_spaces;
      getProperties().address_spaces = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static BarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static BarrierOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::ArrayAttr address_spaces);
  static BarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::ArrayAttr address_spaces);
  static BarrierOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::ArrayAttr address_spaces);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr address_spaces);
  static BarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr address_spaces);
  static BarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr address_spaces);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BarrierOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BarrierOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::BarrierOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::BinaryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BinaryOpGenericAdaptorBase {
public:
  struct Properties {
    using objectsTy = ::mlir::ArrayAttr;
    objectsTy objects;

    auto getObjects() const {
      auto &propStorage = this->objects;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setObjects(const ::mlir::ArrayAttr &propValue) {
      this->objects = propValue;
    }
    using offloadingHandlerTy = ::mlir::Attribute;
    offloadingHandlerTy offloadingHandler;

    auto getOffloadingHandler() const {
      auto &propStorage = this->offloadingHandler;
      return ::llvm::dyn_cast_or_null<::mlir::Attribute>(propStorage);
    }
    void setOffloadingHandler(const ::mlir::Attribute &propValue) {
      this->offloadingHandler = propValue;
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
        rhs.objects == this->objects &&
        rhs.offloadingHandler == this->offloadingHandler &&
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
  BinaryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.binary", odsAttrs.getContext());
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

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
  ::mlir::Attribute getOffloadingHandlerAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().offloadingHandler);
    return attr;
  }

  ::std::optional<::mlir::Attribute> getOffloadingHandler();
  ::mlir::ArrayAttr getObjectsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().objects);
    return attr;
  }

  ::mlir::ArrayAttr getObjects();
};

} // namespace detail
template <typename RangeT>
class BinaryOpGenericAdaptor : public detail::BinaryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BinaryOpGenericAdaptorBase;
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
class BinaryOp : public ::mlir::Op<BinaryOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BinaryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BinaryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("objects"), ::llvm::StringRef("offloadingHandler"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getObjectsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getObjectsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOffloadingHandlerAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getOffloadingHandlerAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.binary");
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
  ::mlir::Attribute getOffloadingHandlerAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().offloadingHandler);
  }

  ::std::optional<::mlir::Attribute> getOffloadingHandler();
  ::mlir::ArrayAttr getObjectsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().objects);
  }

  ::mlir::ArrayAttr getObjects();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setOffloadingHandlerAttr(::mlir::Attribute attr) {
    getProperties().offloadingHandler = attr;
  }

  void setObjectsAttr(::mlir::ArrayAttr attr) {
    getProperties().objects = attr;
  }

  ::mlir::Attribute removeOffloadingHandlerAttr() {
      auto attr = getProperties().offloadingHandler;
      getProperties().offloadingHandler = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name, Attribute offloadingHandler, ArrayAttr objects);
  static BinaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, Attribute offloadingHandler, ArrayAttr objects);
  static BinaryOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, Attribute offloadingHandler, ArrayAttr objects);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name, Attribute offloadingHandler, ArrayRef<Attribute> objects);
  static BinaryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, Attribute offloadingHandler, ArrayRef<Attribute> objects);
  static BinaryOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, Attribute offloadingHandler, ArrayRef<Attribute> objects);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::BinaryOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::BlockDimOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BlockDimOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::gpu::DimensionAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::gpu::DimensionAttr>(propStorage);
    }
    void setDimension(const ::mlir::gpu::DimensionAttr &propValue) {
      this->dimension = propValue;
    }
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
        rhs.upper_bound == this->upper_bound &&
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
  BlockDimOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.block_dim", odsAttrs.getContext());
  }

  BlockDimOpGenericAdaptorBase(BlockDimOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
    return attr;
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class BlockDimOpGenericAdaptor : public detail::BlockDimOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BlockDimOpGenericAdaptorBase;
public:
  BlockDimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BlockDimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : BlockDimOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BlockDimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BlockDimOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BlockDimOpGenericAdaptor(RangeT values, const BlockDimOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BlockDimOp, typename = std::enable_if_t<std::is_same_v<LateInst, BlockDimOp>>>
  BlockDimOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class BlockDimOpAdaptor : public BlockDimOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BlockDimOpGenericAdaptor::BlockDimOpGenericAdaptor;
  BlockDimOpAdaptor(BlockDimOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BlockDimOp : public ::mlir::Op<BlockDimOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BlockDimOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BlockDimOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<BlockDimOp>::inferResultRangesFromOptional;
  using ::mlir::OpAsmOpInterface::Trait<BlockDimOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<BlockDimOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<BlockDimOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension"), ::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.block_dim");
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
  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setDimensionAttr(::mlir::gpu::DimensionAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(::mlir::gpu::Dimension attrValue);
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension);
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension);
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BlockDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BlockDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::BlockDimOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::BlockIdOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BlockIdOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::gpu::DimensionAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::gpu::DimensionAttr>(propStorage);
    }
    void setDimension(const ::mlir::gpu::DimensionAttr &propValue) {
      this->dimension = propValue;
    }
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
        rhs.upper_bound == this->upper_bound &&
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
  BlockIdOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.block_id", odsAttrs.getContext());
  }

  BlockIdOpGenericAdaptorBase(BlockIdOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
    return attr;
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class BlockIdOpGenericAdaptor : public detail::BlockIdOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BlockIdOpGenericAdaptorBase;
public:
  BlockIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BlockIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : BlockIdOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BlockIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BlockIdOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BlockIdOpGenericAdaptor(RangeT values, const BlockIdOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BlockIdOp, typename = std::enable_if_t<std::is_same_v<LateInst, BlockIdOp>>>
  BlockIdOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class BlockIdOpAdaptor : public BlockIdOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BlockIdOpGenericAdaptor::BlockIdOpGenericAdaptor;
  BlockIdOpAdaptor(BlockIdOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BlockIdOp : public ::mlir::Op<BlockIdOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BlockIdOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BlockIdOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<BlockIdOp>::inferResultRangesFromOptional;
  using ::mlir::OpAsmOpInterface::Trait<BlockIdOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<BlockIdOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<BlockIdOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension"), ::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.block_id");
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
  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setDimensionAttr(::mlir::gpu::DimensionAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(::mlir::gpu::Dimension attrValue);
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension);
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension);
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::BlockIdOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::ClusterBlockIdOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClusterBlockIdOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::gpu::DimensionAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::gpu::DimensionAttr>(propStorage);
    }
    void setDimension(const ::mlir::gpu::DimensionAttr &propValue) {
      this->dimension = propValue;
    }
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
        rhs.upper_bound == this->upper_bound &&
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
  ClusterBlockIdOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.cluster_block_id", odsAttrs.getContext());
  }

  ClusterBlockIdOpGenericAdaptorBase(ClusterBlockIdOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
    return attr;
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class ClusterBlockIdOpGenericAdaptor : public detail::ClusterBlockIdOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClusterBlockIdOpGenericAdaptorBase;
public:
  ClusterBlockIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClusterBlockIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ClusterBlockIdOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClusterBlockIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClusterBlockIdOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClusterBlockIdOpGenericAdaptor(RangeT values, const ClusterBlockIdOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClusterBlockIdOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClusterBlockIdOp>>>
  ClusterBlockIdOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ClusterBlockIdOpAdaptor : public ClusterBlockIdOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClusterBlockIdOpGenericAdaptor::ClusterBlockIdOpGenericAdaptor;
  ClusterBlockIdOpAdaptor(ClusterBlockIdOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClusterBlockIdOp : public ::mlir::Op<ClusterBlockIdOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClusterBlockIdOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClusterBlockIdOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<ClusterBlockIdOp>::inferResultRangesFromOptional;
  using ::mlir::OpAsmOpInterface::Trait<ClusterBlockIdOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ClusterBlockIdOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ClusterBlockIdOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension"), ::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.cluster_block_id");
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
  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setDimensionAttr(::mlir::gpu::DimensionAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(::mlir::gpu::Dimension attrValue);
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension);
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension);
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterBlockIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterBlockIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::ClusterBlockIdOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::ClusterDimBlocksOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClusterDimBlocksOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::gpu::DimensionAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::gpu::DimensionAttr>(propStorage);
    }
    void setDimension(const ::mlir::gpu::DimensionAttr &propValue) {
      this->dimension = propValue;
    }
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
        rhs.upper_bound == this->upper_bound &&
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
  ClusterDimBlocksOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.cluster_dim_blocks", odsAttrs.getContext());
  }

  ClusterDimBlocksOpGenericAdaptorBase(ClusterDimBlocksOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
    return attr;
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class ClusterDimBlocksOpGenericAdaptor : public detail::ClusterDimBlocksOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClusterDimBlocksOpGenericAdaptorBase;
public:
  ClusterDimBlocksOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClusterDimBlocksOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ClusterDimBlocksOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClusterDimBlocksOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClusterDimBlocksOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClusterDimBlocksOpGenericAdaptor(RangeT values, const ClusterDimBlocksOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClusterDimBlocksOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClusterDimBlocksOp>>>
  ClusterDimBlocksOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ClusterDimBlocksOpAdaptor : public ClusterDimBlocksOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClusterDimBlocksOpGenericAdaptor::ClusterDimBlocksOpGenericAdaptor;
  ClusterDimBlocksOpAdaptor(ClusterDimBlocksOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClusterDimBlocksOp : public ::mlir::Op<ClusterDimBlocksOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClusterDimBlocksOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClusterDimBlocksOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<ClusterDimBlocksOp>::inferResultRangesFromOptional;
  using ::mlir::OpAsmOpInterface::Trait<ClusterDimBlocksOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ClusterDimBlocksOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ClusterDimBlocksOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension"), ::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.cluster_dim_blocks");
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
  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setDimensionAttr(::mlir::gpu::DimensionAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(::mlir::gpu::Dimension attrValue);
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension);
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension);
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterDimBlocksOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterDimBlocksOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::ClusterDimBlocksOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::ClusterDimOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClusterDimOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::gpu::DimensionAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::gpu::DimensionAttr>(propStorage);
    }
    void setDimension(const ::mlir::gpu::DimensionAttr &propValue) {
      this->dimension = propValue;
    }
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
        rhs.upper_bound == this->upper_bound &&
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
  ClusterDimOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.cluster_dim", odsAttrs.getContext());
  }

  ClusterDimOpGenericAdaptorBase(ClusterDimOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
    return attr;
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class ClusterDimOpGenericAdaptor : public detail::ClusterDimOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClusterDimOpGenericAdaptorBase;
public:
  ClusterDimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClusterDimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ClusterDimOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClusterDimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClusterDimOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClusterDimOpGenericAdaptor(RangeT values, const ClusterDimOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClusterDimOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClusterDimOp>>>
  ClusterDimOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ClusterDimOpAdaptor : public ClusterDimOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClusterDimOpGenericAdaptor::ClusterDimOpGenericAdaptor;
  ClusterDimOpAdaptor(ClusterDimOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClusterDimOp : public ::mlir::Op<ClusterDimOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClusterDimOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClusterDimOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<ClusterDimOp>::inferResultRangesFromOptional;
  using ::mlir::OpAsmOpInterface::Trait<ClusterDimOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ClusterDimOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ClusterDimOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension"), ::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.cluster_dim");
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
  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setDimensionAttr(::mlir::gpu::DimensionAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(::mlir::gpu::Dimension attrValue);
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension);
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension);
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::ClusterDimOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::ClusterIdOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClusterIdOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::gpu::DimensionAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::gpu::DimensionAttr>(propStorage);
    }
    void setDimension(const ::mlir::gpu::DimensionAttr &propValue) {
      this->dimension = propValue;
    }
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
        rhs.upper_bound == this->upper_bound &&
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
  ClusterIdOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.cluster_id", odsAttrs.getContext());
  }

  ClusterIdOpGenericAdaptorBase(ClusterIdOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
    return attr;
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class ClusterIdOpGenericAdaptor : public detail::ClusterIdOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClusterIdOpGenericAdaptorBase;
public:
  ClusterIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClusterIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ClusterIdOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClusterIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClusterIdOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClusterIdOpGenericAdaptor(RangeT values, const ClusterIdOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClusterIdOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClusterIdOp>>>
  ClusterIdOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ClusterIdOpAdaptor : public ClusterIdOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClusterIdOpGenericAdaptor::ClusterIdOpGenericAdaptor;
  ClusterIdOpAdaptor(ClusterIdOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClusterIdOp : public ::mlir::Op<ClusterIdOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClusterIdOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClusterIdOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<ClusterIdOp>::inferResultRangesFromOptional;
  using ::mlir::OpAsmOpInterface::Trait<ClusterIdOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ClusterIdOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ClusterIdOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension"), ::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.cluster_id");
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
  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setDimensionAttr(::mlir::gpu::DimensionAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(::mlir::gpu::Dimension attrValue);
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension);
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension);
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClusterIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::ClusterIdOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::Create2To4SpMatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class Create2To4SpMatOpGenericAdaptorBase {
public:
  struct Properties {
    using pruneFlagTy = ::mlir::gpu::Prune2To4SpMatFlagAttr;
    pruneFlagTy pruneFlag;

    auto getPruneFlag() const {
      auto &propStorage = this->pruneFlag;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::Prune2To4SpMatFlagAttr>(propStorage);
    }
    void setPruneFlag(const ::mlir::gpu::Prune2To4SpMatFlagAttr &propValue) {
      this->pruneFlag = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.pruneFlag == this->pruneFlag &&
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
  Create2To4SpMatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.create_2to4_spmat", odsAttrs.getContext());
  }

  Create2To4SpMatOpGenericAdaptorBase(Create2To4SpMatOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::Prune2To4SpMatFlagAttr getPruneFlagAttr();
  ::mlir::gpu::Prune2To4SpMatFlag getPruneFlag();
};

} // namespace detail
template <typename RangeT>
class Create2To4SpMatOpGenericAdaptor : public detail::Create2To4SpMatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::Create2To4SpMatOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_rows = 1;
  static constexpr int odsIndex_cols = 2;
  static constexpr int odsIndex_memref = 3;
public:
  Create2To4SpMatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  Create2To4SpMatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : Create2To4SpMatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  Create2To4SpMatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : Create2To4SpMatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  Create2To4SpMatOpGenericAdaptor(RangeT values, const Create2To4SpMatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = Create2To4SpMatOp, typename = std::enable_if_t<std::is_same_v<LateInst, Create2To4SpMatOp>>>
  Create2To4SpMatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getRows() {
    return (*getODSOperands(1).begin());
  }

  ValueT getCols() {
    return (*getODSOperands(2).begin());
  }

  ValueT getMemref() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class Create2To4SpMatOpAdaptor : public Create2To4SpMatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using Create2To4SpMatOpGenericAdaptor::Create2To4SpMatOpGenericAdaptor;
  Create2To4SpMatOpAdaptor(Create2To4SpMatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class Create2To4SpMatOp : public ::mlir::Op<Create2To4SpMatOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = Create2To4SpMatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = Create2To4SpMatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_rows = 1;
  static constexpr int odsIndex_cols = 2;
  static constexpr int odsIndex_memref = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("pruneFlag")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPruneFlagAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPruneFlagAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.create_2to4_spmat");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IndexType> getRows() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCols() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(3).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getRowsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getColsMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMemrefMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getSpMat() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::gpu::Prune2To4SpMatFlagAttr getPruneFlagAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::Prune2To4SpMatFlagAttr>(getProperties().pruneFlag);
  }

  ::mlir::gpu::Prune2To4SpMatFlag getPruneFlag();
  void setPruneFlagAttr(::mlir::gpu::Prune2To4SpMatFlagAttr attr) {
    getProperties().pruneFlag = attr;
  }

  void setPruneFlag(::mlir::gpu::Prune2To4SpMatFlag attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type spMat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlagAttr pruneFlag, ::mlir::Value memref);
  static Create2To4SpMatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type spMat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlagAttr pruneFlag, ::mlir::Value memref);
  static Create2To4SpMatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type spMat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlagAttr pruneFlag, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlagAttr pruneFlag, ::mlir::Value memref);
  static Create2To4SpMatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlagAttr pruneFlag, ::mlir::Value memref);
  static Create2To4SpMatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlagAttr pruneFlag, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type spMat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlag pruneFlag, ::mlir::Value memref);
  static Create2To4SpMatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type spMat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlag pruneFlag, ::mlir::Value memref);
  static Create2To4SpMatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type spMat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlag pruneFlag, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlag pruneFlag, ::mlir::Value memref);
  static Create2To4SpMatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlag pruneFlag, ::mlir::Value memref);
  static Create2To4SpMatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::gpu::Prune2To4SpMatFlag pruneFlag, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static Create2To4SpMatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static Create2To4SpMatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static Create2To4SpMatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static Create2To4SpMatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::Create2To4SpMatOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::CreateBsrOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateBsrOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CreateBsrOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.create_bsr", odsAttrs.getContext());
  }

  CreateBsrOpGenericAdaptorBase(CreateBsrOp op);

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
class CreateBsrOpGenericAdaptor : public detail::CreateBsrOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateBsrOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_brows = 1;
  static constexpr int odsIndex_bcols = 2;
  static constexpr int odsIndex_bnnz = 3;
  static constexpr int odsIndex_rBlockSize = 4;
  static constexpr int odsIndex_cBlockSize = 5;
  static constexpr int odsIndex_bRowPos = 6;
  static constexpr int odsIndex_bColIdxs = 7;
  static constexpr int odsIndex_values = 8;
public:
  CreateBsrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateBsrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateBsrOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateBsrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CreateBsrOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateBsrOpGenericAdaptor(RangeT values, const CreateBsrOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateBsrOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateBsrOp>>>
  CreateBsrOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getBrows() {
    return (*getODSOperands(1).begin());
  }

  ValueT getBcols() {
    return (*getODSOperands(2).begin());
  }

  ValueT getBnnz() {
    return (*getODSOperands(3).begin());
  }

  ValueT getRBlockSize() {
    return (*getODSOperands(4).begin());
  }

  ValueT getCBlockSize() {
    return (*getODSOperands(5).begin());
  }

  ValueT getBRowPos() {
    return (*getODSOperands(6).begin());
  }

  ValueT getBColIdxs() {
    return (*getODSOperands(7).begin());
  }

  ValueT getValues() {
    return (*getODSOperands(8).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CreateBsrOpAdaptor : public CreateBsrOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateBsrOpGenericAdaptor::CreateBsrOpGenericAdaptor;
  CreateBsrOpAdaptor(CreateBsrOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateBsrOp : public ::mlir::Op<CreateBsrOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<8>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateBsrOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateBsrOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_brows = 1;
  static constexpr int odsIndex_bcols = 2;
  static constexpr int odsIndex_bnnz = 3;
  static constexpr int odsIndex_rBlockSize = 4;
  static constexpr int odsIndex_cBlockSize = 5;
  static constexpr int odsIndex_bRowPos = 6;
  static constexpr int odsIndex_bColIdxs = 7;
  static constexpr int odsIndex_values = 8;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.create_bsr");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IndexType> getBrows() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getBcols() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getBnnz() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getRBlockSize() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCBlockSize() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(5).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBRowPos() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(6).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBColIdxs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(7).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(8).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getBrowsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBcolsMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBnnzMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRBlockSizeMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getCBlockSizeMutable() {
    auto range = getODSOperandIndexAndLength(5);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBRowPosMutable() {
    auto range = getODSOperandIndexAndLength(6);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBColIdxsMutable() {
    auto range = getODSOperandIndexAndLength(7);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValuesMutable() {
    auto range = getODSOperandIndexAndLength(8);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getSpmat() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value brows, ::mlir::Value bcols, ::mlir::Value bnnz, ::mlir::Value rBlockSize, ::mlir::Value cBlockSize, ::mlir::Value bRowPos, ::mlir::Value bColIdxs, ::mlir::Value values);
  static CreateBsrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value brows, ::mlir::Value bcols, ::mlir::Value bnnz, ::mlir::Value rBlockSize, ::mlir::Value cBlockSize, ::mlir::Value bRowPos, ::mlir::Value bColIdxs, ::mlir::Value values);
  static CreateBsrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value brows, ::mlir::Value bcols, ::mlir::Value bnnz, ::mlir::Value rBlockSize, ::mlir::Value cBlockSize, ::mlir::Value bRowPos, ::mlir::Value bColIdxs, ::mlir::Value values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value brows, ::mlir::Value bcols, ::mlir::Value bnnz, ::mlir::Value rBlockSize, ::mlir::Value cBlockSize, ::mlir::Value bRowPos, ::mlir::Value bColIdxs, ::mlir::Value values);
  static CreateBsrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value brows, ::mlir::Value bcols, ::mlir::Value bnnz, ::mlir::Value rBlockSize, ::mlir::Value cBlockSize, ::mlir::Value bRowPos, ::mlir::Value bColIdxs, ::mlir::Value values);
  static CreateBsrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value brows, ::mlir::Value bcols, ::mlir::Value bnnz, ::mlir::Value rBlockSize, ::mlir::Value cBlockSize, ::mlir::Value bRowPos, ::mlir::Value bColIdxs, ::mlir::Value values);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateBsrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateBsrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateBsrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateBsrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::CreateBsrOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::CreateCooAoSOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateCooAoSOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CreateCooAoSOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.create_coo_aos", odsAttrs.getContext());
  }

  CreateCooAoSOpGenericAdaptorBase(CreateCooAoSOp op);

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
class CreateCooAoSOpGenericAdaptor : public detail::CreateCooAoSOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateCooAoSOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_rows = 1;
  static constexpr int odsIndex_cols = 2;
  static constexpr int odsIndex_nnz = 3;
  static constexpr int odsIndex_idxs = 4;
  static constexpr int odsIndex_values = 5;
public:
  CreateCooAoSOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateCooAoSOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateCooAoSOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateCooAoSOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CreateCooAoSOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateCooAoSOpGenericAdaptor(RangeT values, const CreateCooAoSOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateCooAoSOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateCooAoSOp>>>
  CreateCooAoSOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getRows() {
    return (*getODSOperands(1).begin());
  }

  ValueT getCols() {
    return (*getODSOperands(2).begin());
  }

  ValueT getNnz() {
    return (*getODSOperands(3).begin());
  }

  ValueT getIdxs() {
    return (*getODSOperands(4).begin());
  }

  ValueT getValues() {
    return (*getODSOperands(5).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CreateCooAoSOpAdaptor : public CreateCooAoSOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateCooAoSOpGenericAdaptor::CreateCooAoSOpGenericAdaptor;
  CreateCooAoSOpAdaptor(CreateCooAoSOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateCooAoSOp : public ::mlir::Op<CreateCooAoSOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<5>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateCooAoSOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateCooAoSOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_rows = 1;
  static constexpr int odsIndex_cols = 2;
  static constexpr int odsIndex_nnz = 3;
  static constexpr int odsIndex_idxs = 4;
  static constexpr int odsIndex_values = 5;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.create_coo_aos");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IndexType> getRows() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCols() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getNnz() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getIdxs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(5).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getRowsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getColsMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getNnzMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIdxsMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValuesMutable() {
    auto range = getODSOperandIndexAndLength(5);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getSpmat() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value idxs, ::mlir::Value values);
  static CreateCooAoSOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value idxs, ::mlir::Value values);
  static CreateCooAoSOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value idxs, ::mlir::Value values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value idxs, ::mlir::Value values);
  static CreateCooAoSOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value idxs, ::mlir::Value values);
  static CreateCooAoSOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value idxs, ::mlir::Value values);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateCooAoSOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateCooAoSOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateCooAoSOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateCooAoSOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::CreateCooAoSOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::CreateCooOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateCooOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CreateCooOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.create_coo", odsAttrs.getContext());
  }

  CreateCooOpGenericAdaptorBase(CreateCooOp op);

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
class CreateCooOpGenericAdaptor : public detail::CreateCooOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateCooOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_rows = 1;
  static constexpr int odsIndex_cols = 2;
  static constexpr int odsIndex_nnz = 3;
  static constexpr int odsIndex_rowIdxs = 4;
  static constexpr int odsIndex_colIdxs = 5;
  static constexpr int odsIndex_values = 6;
public:
  CreateCooOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateCooOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateCooOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateCooOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CreateCooOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateCooOpGenericAdaptor(RangeT values, const CreateCooOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateCooOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateCooOp>>>
  CreateCooOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getRows() {
    return (*getODSOperands(1).begin());
  }

  ValueT getCols() {
    return (*getODSOperands(2).begin());
  }

  ValueT getNnz() {
    return (*getODSOperands(3).begin());
  }

  ValueT getRowIdxs() {
    return (*getODSOperands(4).begin());
  }

  ValueT getColIdxs() {
    return (*getODSOperands(5).begin());
  }

  ValueT getValues() {
    return (*getODSOperands(6).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CreateCooOpAdaptor : public CreateCooOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateCooOpGenericAdaptor::CreateCooOpGenericAdaptor;
  CreateCooOpAdaptor(CreateCooOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateCooOp : public ::mlir::Op<CreateCooOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<6>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateCooOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateCooOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_rows = 1;
  static constexpr int odsIndex_cols = 2;
  static constexpr int odsIndex_nnz = 3;
  static constexpr int odsIndex_rowIdxs = 4;
  static constexpr int odsIndex_colIdxs = 5;
  static constexpr int odsIndex_values = 6;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.create_coo");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IndexType> getRows() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCols() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getNnz() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getRowIdxs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getColIdxs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(5).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(6).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getRowsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getColsMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getNnzMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRowIdxsMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getColIdxsMutable() {
    auto range = getODSOperandIndexAndLength(5);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValuesMutable() {
    auto range = getODSOperandIndexAndLength(6);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getSpmat() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowIdxs, ::mlir::Value colIdxs, ::mlir::Value values);
  static CreateCooOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowIdxs, ::mlir::Value colIdxs, ::mlir::Value values);
  static CreateCooOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowIdxs, ::mlir::Value colIdxs, ::mlir::Value values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowIdxs, ::mlir::Value colIdxs, ::mlir::Value values);
  static CreateCooOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowIdxs, ::mlir::Value colIdxs, ::mlir::Value values);
  static CreateCooOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowIdxs, ::mlir::Value colIdxs, ::mlir::Value values);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateCooOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateCooOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateCooOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateCooOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::CreateCooOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::CreateCscOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateCscOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CreateCscOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.create_csc", odsAttrs.getContext());
  }

  CreateCscOpGenericAdaptorBase(CreateCscOp op);

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
class CreateCscOpGenericAdaptor : public detail::CreateCscOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateCscOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_rows = 1;
  static constexpr int odsIndex_cols = 2;
  static constexpr int odsIndex_nnz = 3;
  static constexpr int odsIndex_colPos = 4;
  static constexpr int odsIndex_rowIdxs = 5;
  static constexpr int odsIndex_values = 6;
public:
  CreateCscOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateCscOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateCscOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateCscOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CreateCscOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateCscOpGenericAdaptor(RangeT values, const CreateCscOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateCscOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateCscOp>>>
  CreateCscOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getRows() {
    return (*getODSOperands(1).begin());
  }

  ValueT getCols() {
    return (*getODSOperands(2).begin());
  }

  ValueT getNnz() {
    return (*getODSOperands(3).begin());
  }

  ValueT getColPos() {
    return (*getODSOperands(4).begin());
  }

  ValueT getRowIdxs() {
    return (*getODSOperands(5).begin());
  }

  ValueT getValues() {
    return (*getODSOperands(6).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CreateCscOpAdaptor : public CreateCscOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateCscOpGenericAdaptor::CreateCscOpGenericAdaptor;
  CreateCscOpAdaptor(CreateCscOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateCscOp : public ::mlir::Op<CreateCscOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<6>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateCscOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateCscOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_rows = 1;
  static constexpr int odsIndex_cols = 2;
  static constexpr int odsIndex_nnz = 3;
  static constexpr int odsIndex_colPos = 4;
  static constexpr int odsIndex_rowIdxs = 5;
  static constexpr int odsIndex_values = 6;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.create_csc");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IndexType> getRows() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCols() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getNnz() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getColPos() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getRowIdxs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(5).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(6).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getRowsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getColsMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getNnzMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getColPosMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRowIdxsMutable() {
    auto range = getODSOperandIndexAndLength(5);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValuesMutable() {
    auto range = getODSOperandIndexAndLength(6);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getSpmat() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value colPos, ::mlir::Value rowIdxs, ::mlir::Value values);
  static CreateCscOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value colPos, ::mlir::Value rowIdxs, ::mlir::Value values);
  static CreateCscOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value colPos, ::mlir::Value rowIdxs, ::mlir::Value values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value colPos, ::mlir::Value rowIdxs, ::mlir::Value values);
  static CreateCscOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value colPos, ::mlir::Value rowIdxs, ::mlir::Value values);
  static CreateCscOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value colPos, ::mlir::Value rowIdxs, ::mlir::Value values);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateCscOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateCscOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateCscOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateCscOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::CreateCscOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::CreateCsrOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateCsrOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CreateCsrOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.create_csr", odsAttrs.getContext());
  }

  CreateCsrOpGenericAdaptorBase(CreateCsrOp op);

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
class CreateCsrOpGenericAdaptor : public detail::CreateCsrOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateCsrOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_rows = 1;
  static constexpr int odsIndex_cols = 2;
  static constexpr int odsIndex_nnz = 3;
  static constexpr int odsIndex_rowPos = 4;
  static constexpr int odsIndex_colIdxs = 5;
  static constexpr int odsIndex_values = 6;
public:
  CreateCsrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateCsrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateCsrOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateCsrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CreateCsrOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateCsrOpGenericAdaptor(RangeT values, const CreateCsrOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateCsrOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateCsrOp>>>
  CreateCsrOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getRows() {
    return (*getODSOperands(1).begin());
  }

  ValueT getCols() {
    return (*getODSOperands(2).begin());
  }

  ValueT getNnz() {
    return (*getODSOperands(3).begin());
  }

  ValueT getRowPos() {
    return (*getODSOperands(4).begin());
  }

  ValueT getColIdxs() {
    return (*getODSOperands(5).begin());
  }

  ValueT getValues() {
    return (*getODSOperands(6).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CreateCsrOpAdaptor : public CreateCsrOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateCsrOpGenericAdaptor::CreateCsrOpGenericAdaptor;
  CreateCsrOpAdaptor(CreateCsrOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateCsrOp : public ::mlir::Op<CreateCsrOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<6>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateCsrOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateCsrOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_rows = 1;
  static constexpr int odsIndex_cols = 2;
  static constexpr int odsIndex_nnz = 3;
  static constexpr int odsIndex_rowPos = 4;
  static constexpr int odsIndex_colIdxs = 5;
  static constexpr int odsIndex_values = 6;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.create_csr");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IndexType> getRows() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCols() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getNnz() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getRowPos() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getColIdxs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(5).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(6).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getRowsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getColsMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getNnzMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRowPosMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getColIdxsMutable() {
    auto range = getODSOperandIndexAndLength(5);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValuesMutable() {
    auto range = getODSOperandIndexAndLength(6);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getSpmat() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowPos, ::mlir::Value colIdxs, ::mlir::Value values);
  static CreateCsrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowPos, ::mlir::Value colIdxs, ::mlir::Value values);
  static CreateCsrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type spmat, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowPos, ::mlir::Value colIdxs, ::mlir::Value values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowPos, ::mlir::Value colIdxs, ::mlir::Value values);
  static CreateCsrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowPos, ::mlir::Value colIdxs, ::mlir::Value values);
  static CreateCsrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value rows, ::mlir::Value cols, ::mlir::Value nnz, ::mlir::Value rowPos, ::mlir::Value colIdxs, ::mlir::Value values);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateCsrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateCsrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateCsrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateCsrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::CreateCsrOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::CreateDnTensorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CreateDnTensorOpGenericAdaptorBase {
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
  CreateDnTensorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.create_dn_tensor", odsAttrs.getContext());
  }

  CreateDnTensorOpGenericAdaptorBase(CreateDnTensorOp op);

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
class CreateDnTensorOpGenericAdaptor : public detail::CreateDnTensorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CreateDnTensorOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_memref = 1;
  static constexpr int odsIndex_dims = 2;
public:
  CreateDnTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CreateDnTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CreateDnTensorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CreateDnTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : CreateDnTensorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CreateDnTensorOpGenericAdaptor(RangeT values, const CreateDnTensorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CreateDnTensorOp, typename = std::enable_if_t<std::is_same_v<LateInst, CreateDnTensorOp>>>
  CreateDnTensorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getMemref() {
    return (*getODSOperands(1).begin());
  }

  RangeT getDims() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CreateDnTensorOpAdaptor : public CreateDnTensorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CreateDnTensorOpGenericAdaptor::CreateDnTensorOpGenericAdaptor;
  CreateDnTensorOpAdaptor(CreateDnTensorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CreateDnTensorOp : public ::mlir::Op<CreateDnTensorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CreateDnTensorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CreateDnTensorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_memref = 1;
  static constexpr int odsIndex_dims = 2;
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

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.create_dn_tensor");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getDims() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getMemrefMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDimsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getDnTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dnTensor, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref, ::mlir::ValueRange dims);
  static CreateDnTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dnTensor, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref, ::mlir::ValueRange dims);
  static CreateDnTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dnTensor, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref, ::mlir::ValueRange dims);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref, ::mlir::ValueRange dims);
  static CreateDnTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref, ::mlir::ValueRange dims);
  static CreateDnTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref, ::mlir::ValueRange dims);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateDnTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CreateDnTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateDnTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CreateDnTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::CreateDnTensorOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::DeallocOp declarations
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
      odsOpName.emplace("gpu.dealloc", odsAttrs.getContext());
  }

  DeallocOpGenericAdaptorBase(DeallocOp op);

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
class DeallocOpGenericAdaptor : public detail::DeallocOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeallocOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_memref = 1;
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

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getMemref() {
    return (*getODSOperands(1).begin());
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
class DeallocOp : public ::mlir::Op<DeallocOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeallocOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeallocOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_memref = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.dealloc");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getMemrefMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref);
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref);
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref);
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref);
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value memref);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::DeallocOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::DestroyDnTensorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DestroyDnTensorOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DestroyDnTensorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.destroy_dn_tensor", odsAttrs.getContext());
  }

  DestroyDnTensorOpGenericAdaptorBase(DestroyDnTensorOp op);

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
class DestroyDnTensorOpGenericAdaptor : public detail::DestroyDnTensorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DestroyDnTensorOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dnTensor = 1;
public:
  DestroyDnTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DestroyDnTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DestroyDnTensorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DestroyDnTensorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DestroyDnTensorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DestroyDnTensorOpGenericAdaptor(RangeT values, const DestroyDnTensorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DestroyDnTensorOp, typename = std::enable_if_t<std::is_same_v<LateInst, DestroyDnTensorOp>>>
  DestroyDnTensorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getDnTensor() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DestroyDnTensorOpAdaptor : public DestroyDnTensorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DestroyDnTensorOpGenericAdaptor::DestroyDnTensorOpGenericAdaptor;
  DestroyDnTensorOpAdaptor(DestroyDnTensorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DestroyDnTensorOp : public ::mlir::Op<DestroyDnTensorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DestroyDnTensorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DestroyDnTensorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dnTensor = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.destroy_dn_tensor");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getDnTensor() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getDnTensorMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value dnTensor);
  static DestroyDnTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value dnTensor);
  static DestroyDnTensorOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value dnTensor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value dnTensor);
  static DestroyDnTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value dnTensor);
  static DestroyDnTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value dnTensor);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DestroyDnTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DestroyDnTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DestroyDnTensorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DestroyDnTensorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::DestroyDnTensorOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::DestroySpMatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DestroySpMatOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DestroySpMatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.destroy_sp_mat", odsAttrs.getContext());
  }

  DestroySpMatOpGenericAdaptorBase(DestroySpMatOp op);

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
class DestroySpMatOpGenericAdaptor : public detail::DestroySpMatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DestroySpMatOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmat = 1;
public:
  DestroySpMatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DestroySpMatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DestroySpMatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DestroySpMatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DestroySpMatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DestroySpMatOpGenericAdaptor(RangeT values, const DestroySpMatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DestroySpMatOp, typename = std::enable_if_t<std::is_same_v<LateInst, DestroySpMatOp>>>
  DestroySpMatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getSpmat() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DestroySpMatOpAdaptor : public DestroySpMatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DestroySpMatOpGenericAdaptor::DestroySpMatOpGenericAdaptor;
  DestroySpMatOpAdaptor(DestroySpMatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DestroySpMatOp : public ::mlir::Op<DestroySpMatOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DestroySpMatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DestroySpMatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmat = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.destroy_sp_mat");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getSpmat() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getSpmatMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static DestroySpMatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static DestroySpMatOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static DestroySpMatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static DestroySpMatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DestroySpMatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DestroySpMatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DestroySpMatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DestroySpMatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::DestroySpMatOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::DynamicSharedMemoryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DynamicSharedMemoryOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DynamicSharedMemoryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.dynamic_shared_memory", odsAttrs.getContext());
  }

  DynamicSharedMemoryOpGenericAdaptorBase(DynamicSharedMemoryOp op);

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
class DynamicSharedMemoryOpGenericAdaptor : public detail::DynamicSharedMemoryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DynamicSharedMemoryOpGenericAdaptorBase;
public:
  DynamicSharedMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DynamicSharedMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DynamicSharedMemoryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DynamicSharedMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DynamicSharedMemoryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DynamicSharedMemoryOpGenericAdaptor(RangeT values, const DynamicSharedMemoryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DynamicSharedMemoryOp, typename = std::enable_if_t<std::is_same_v<LateInst, DynamicSharedMemoryOp>>>
  DynamicSharedMemoryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DynamicSharedMemoryOpAdaptor : public DynamicSharedMemoryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DynamicSharedMemoryOpGenericAdaptor::DynamicSharedMemoryOpGenericAdaptor;
  DynamicSharedMemoryOpAdaptor(DynamicSharedMemoryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DynamicSharedMemoryOp : public ::mlir::Op<DynamicSharedMemoryOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DynamicSharedMemoryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DynamicSharedMemoryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.dynamic_shared_memory");
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

  ::mlir::TypedValue<::mlir::MemRefType> getResultMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultMemref);
  static DynamicSharedMemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultMemref);
  static DynamicSharedMemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultMemref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static DynamicSharedMemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static DynamicSharedMemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DynamicSharedMemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DynamicSharedMemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DynamicSharedMemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DynamicSharedMemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::DynamicSharedMemoryOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::GPUFuncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GPUFuncOpGenericAdaptorBase {
public:
  struct Properties {
    using arg_attrsTy = ::mlir::ArrayAttr;
    arg_attrsTy arg_attrs;

    auto getArgAttrs() const {
      auto &propStorage = this->arg_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setArgAttrs(const ::mlir::ArrayAttr &propValue) {
      this->arg_attrs = propValue;
    }
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() const {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using known_block_sizeTy = ::mlir::DenseI32ArrayAttr;
    known_block_sizeTy known_block_size;

    auto getKnownBlockSize() const {
      auto &propStorage = this->known_block_size;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(propStorage);
    }
    void setKnownBlockSize(const ::mlir::DenseI32ArrayAttr &propValue) {
      this->known_block_size = propValue;
    }
    using known_cluster_sizeTy = ::mlir::DenseI32ArrayAttr;
    known_cluster_sizeTy known_cluster_size;

    auto getKnownClusterSize() const {
      auto &propStorage = this->known_cluster_size;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(propStorage);
    }
    void setKnownClusterSize(const ::mlir::DenseI32ArrayAttr &propValue) {
      this->known_cluster_size = propValue;
    }
    using known_grid_sizeTy = ::mlir::DenseI32ArrayAttr;
    known_grid_sizeTy known_grid_size;

    auto getKnownGridSize() const {
      auto &propStorage = this->known_grid_size;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(propStorage);
    }
    void setKnownGridSize(const ::mlir::DenseI32ArrayAttr &propValue) {
      this->known_grid_size = propValue;
    }
    using private_attrib_attrsTy = ::mlir::ArrayAttr;
    private_attrib_attrsTy private_attrib_attrs;

    auto getPrivateAttribAttrs() const {
      auto &propStorage = this->private_attrib_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPrivateAttribAttrs(const ::mlir::ArrayAttr &propValue) {
      this->private_attrib_attrs = propValue;
    }
    using res_attrsTy = ::mlir::ArrayAttr;
    res_attrsTy res_attrs;

    auto getResAttrs() const {
      auto &propStorage = this->res_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setResAttrs(const ::mlir::ArrayAttr &propValue) {
      this->res_attrs = propValue;
    }
    using workgroup_attrib_attrsTy = ::mlir::ArrayAttr;
    workgroup_attrib_attrsTy workgroup_attrib_attrs;

    auto getWorkgroupAttribAttrs() const {
      auto &propStorage = this->workgroup_attrib_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setWorkgroupAttribAttrs(const ::mlir::ArrayAttr &propValue) {
      this->workgroup_attrib_attrs = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.known_block_size == this->known_block_size &&
        rhs.known_cluster_size == this->known_cluster_size &&
        rhs.known_grid_size == this->known_grid_size &&
        rhs.private_attrib_attrs == this->private_attrib_attrs &&
        rhs.res_attrs == this->res_attrs &&
        rhs.workgroup_attrib_attrs == this->workgroup_attrib_attrs &&
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
  GPUFuncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.func", odsAttrs.getContext());
  }

  GPUFuncOpGenericAdaptorBase(GPUFuncOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getFunctionTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
    return attr;
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::ArrayAttr getWorkgroupAttribAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().workgroup_attrib_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getWorkgroupAttribAttrs();
  ::mlir::ArrayAttr getPrivateAttribAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_attrib_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateAttribAttrs();
  ::mlir::DenseI32ArrayAttr getKnownBlockSizeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(getProperties().known_block_size);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<int32_t>> getKnownBlockSize();
  ::mlir::DenseI32ArrayAttr getKnownGridSizeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(getProperties().known_grid_size);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<int32_t>> getKnownGridSize();
  ::mlir::DenseI32ArrayAttr getKnownClusterSizeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(getProperties().known_cluster_size);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<int32_t>> getKnownClusterSize();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class GPUFuncOpGenericAdaptor : public detail::GPUFuncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GPUFuncOpGenericAdaptorBase;
public:
  GPUFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GPUFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GPUFuncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GPUFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GPUFuncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GPUFuncOpGenericAdaptor(RangeT values, const GPUFuncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GPUFuncOp, typename = std::enable_if_t<std::is_same_v<LateInst, GPUFuncOp>>>
  GPUFuncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GPUFuncOpAdaptor : public GPUFuncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GPUFuncOpGenericAdaptor::GPUFuncOpGenericAdaptor;
  GPUFuncOpAdaptor(GPUFuncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GPUFuncOp : public ::mlir::Op<GPUFuncOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<GPUModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::SymbolOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::OpTrait::AffineScope> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GPUFuncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GPUFuncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("known_block_size"), ::llvm::StringRef("known_cluster_size"), ::llvm::StringRef("known_grid_size"), ::llvm::StringRef("private_attrib_attrs"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("workgroup_attrib_attrs")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgAttrsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFunctionTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFunctionTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getKnownBlockSizeAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getKnownBlockSizeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getKnownClusterSizeAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getKnownClusterSizeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getKnownGridSizeAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getKnownGridSizeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getPrivateAttribAttrsAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getPrivateAttribAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  ::mlir::StringAttr getWorkgroupAttribAttrsAttrName() {
    return getAttributeNameForIndex(7);
  }

  static ::mlir::StringAttr getWorkgroupAttribAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 7);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.func");
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
  ::mlir::TypeAttr getFunctionTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::ArrayAttr getWorkgroupAttribAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().workgroup_attrib_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getWorkgroupAttribAttrs();
  ::mlir::ArrayAttr getPrivateAttribAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().private_attrib_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getPrivateAttribAttrs();
  ::mlir::DenseI32ArrayAttr getKnownBlockSizeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(getProperties().known_block_size);
  }

  ::std::optional<::llvm::ArrayRef<int32_t>> getKnownBlockSize();
  ::mlir::DenseI32ArrayAttr getKnownGridSizeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(getProperties().known_grid_size);
  }

  ::std::optional<::llvm::ArrayRef<int32_t>> getKnownGridSize();
  ::mlir::DenseI32ArrayAttr getKnownClusterSizeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(getProperties().known_cluster_size);
  }

  ::std::optional<::llvm::ArrayRef<int32_t>> getKnownClusterSize();
  void setFunctionTypeAttr(::mlir::TypeAttr attr) {
    getProperties().function_type = attr;
  }

  void setFunctionType(::mlir::FunctionType attrValue);
  void setArgAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().arg_attrs = attr;
  }

  void setResAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().res_attrs = attr;
  }

  void setWorkgroupAttribAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().workgroup_attrib_attrs = attr;
  }

  void setPrivateAttribAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().private_attrib_attrs = attr;
  }

  void setKnownBlockSizeAttr(::mlir::DenseI32ArrayAttr attr) {
    getProperties().known_block_size = attr;
  }

  void setKnownBlockSize(::std::optional<::llvm::ArrayRef<int32_t>> attrValue);
  void setKnownGridSizeAttr(::mlir::DenseI32ArrayAttr attr) {
    getProperties().known_grid_size = attr;
  }

  void setKnownGridSize(::std::optional<::llvm::ArrayRef<int32_t>> attrValue);
  void setKnownClusterSizeAttr(::mlir::DenseI32ArrayAttr attr) {
    getProperties().known_cluster_size = attr;
  }

  void setKnownClusterSize(::std::optional<::llvm::ArrayRef<int32_t>> attrValue);
  ::mlir::Attribute removeArgAttrsAttr() {
      auto attr = getProperties().arg_attrs;
      getProperties().arg_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeResAttrsAttr() {
      auto attr = getProperties().res_attrs;
      getProperties().res_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeWorkgroupAttribAttrsAttr() {
      auto attr = getProperties().workgroup_attrib_attrs;
      getProperties().workgroup_attrib_attrs = {};
      return attr;
  }

  ::mlir::Attribute removePrivateAttribAttrsAttr() {
      auto attr = getProperties().private_attrib_attrs;
      getProperties().private_attrib_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeKnownBlockSizeAttr() {
      auto attr = getProperties().known_block_size;
      getProperties().known_block_size = {};
      return attr;
  }

  ::mlir::Attribute removeKnownGridSizeAttr() {
      auto attr = getProperties().known_grid_size;
      getProperties().known_grid_size = {};
      return attr;
  }

  ::mlir::Attribute removeKnownClusterSizeAttr() {
      auto attr = getProperties().known_cluster_size;
      getProperties().known_cluster_size = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name, FunctionType type, TypeRange workgroupAttributions = {}, TypeRange privateAttributions = {}, ArrayRef<NamedAttribute> attrs = {});
  static GPUFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, FunctionType type, TypeRange workgroupAttributions = {}, TypeRange privateAttributions = {}, ArrayRef<NamedAttribute> attrs = {});
  static GPUFuncOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, FunctionType type, TypeRange workgroupAttributions = {}, TypeRange privateAttributions = {}, ArrayRef<NamedAttribute> attrs = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  /// Returns `true` if the GPU function defined by this Op is a kernel, i.e.
  /// it is intended to be launched from host.
  bool isKernel() {
    return (*this)->getAttrOfType<UnitAttr>(
        GPUDialect::getKernelFuncAttrName()) != nullptr;
  }

  /// Returns the number of buffers located in the workgroup memory.
  unsigned getNumWorkgroupAttributions() {
    auto attr = (*this)->getAttrOfType<IntegerAttr>(
        getNumWorkgroupAttributionsAttrName());
    if (!attr)
      return 0;
    int64_t value = attr.getInt();
    assert(value >= 0 && value < std::numeric_limits<uint32_t>::max() &&
           "invalid workgroup attribution count");
    return value;
  }

  /// Return the index of the first workgroup attribution in the block argument
  /// list.
  unsigned getFirstWorkgroupAttributionIndex() {
    return getFunctionType().getNumInputs();
  }

  /// Returns a list of block arguments that correspond to buffers located in
  /// the workgroup memory
  ArrayRef<BlockArgument> getWorkgroupAttributions() {
    auto begin =
        std::next(getBody().args_begin(), getFirstWorkgroupAttributionIndex());
    auto end = std::next(begin, getNumWorkgroupAttributions());
    return {begin, end};
  }

  /// Adds a new block argument that corresponds to buffers located in
  /// workgroup memory.
  BlockArgument addWorkgroupAttribution(Type type, Location loc);

  /// Get the workgroup attribution attribute dictionary for the attribution
  /// at index `index`, counted from the start of the workgroup attributions.
  DictionaryAttr getworkgroupAttributionAttrs(unsigned index);

  /// Set the workgroup attribution attribute dictionary for the attribution
  /// at index `index`, counted from the start of the workgroup attributions.
  void setworkgroupAttributionAttrs(unsigned index, DictionaryAttr value);

  /// Get an attribute for a workgroup attribution. `index` is counted
  /// from the start of the workgroup attributions, not the start of the block.
  Attribute getWorkgroupAttributionAttr(unsigned index, StringAttr name);
  Attribute getWorkgroupAttributionAttr(unsigned index, StringRef name) {
    return getWorkgroupAttributionAttr(index, StringAttr::get((*this)->getContext(), name));
  }

  /// Set an attribute for a workgroup attribution. `index` is counted
  /// from the start of the workgroup attributions, not the start of the block.
  /// A null `value` removes an attributino attribute.
  void setWorkgroupAttributionAttr(unsigned index, StringAttr name, Attribute value);
  void setWorkgroupAttributionAttr(unsigned index, StringRef name, Attribute value) {
    return setWorkgroupAttributionAttr(index, StringAttr::get((*this)->getContext(), name), value);
  }

  /// Returns the number of buffers located in the private memory.
  unsigned getNumPrivateAttributions() {
    return getBody().getNumArguments() - getFunctionType().getNumInputs() -
        getNumWorkgroupAttributions();
  }

  /// Returns the index of the first private buffer in the block argument list.
  unsigned getFirstPrivateAttributionIndex() {
    // Buffers on the private memory always come after buffers on the workgroup
    // memory.
    return getFunctionType().getNumInputs() + getNumWorkgroupAttributions();
  }

  /// Returns a list of block arguments that correspond to buffers located in
  /// the private memory.
  ArrayRef<BlockArgument> getPrivateAttributions() {
    auto begin =
        std::next(getBody().args_begin(), getFirstPrivateAttributionIndex());
    return {begin, getBody().args_end()};
  }

  /// Adds a new block argument that corresponds to buffers located in
  /// private memory.
  BlockArgument addPrivateAttribution(Type type, Location loc);

  /// Get the private attribution attribute dictionary for the attribution
  /// at index `index`, counted from the start of the private attributions.
  DictionaryAttr getPrivateAttributionAttrs(unsigned index);

  /// Set the private attribution attribute dictionary for the attribution
  /// at index `index`, counted from the start of the private attributions.
  void setPrivateAttributionAttrs(unsigned index, DictionaryAttr value);

  /// Get an attribute for a private attribution. `index` is counted
  /// from the start of the private attributions, not the start of the block.
  Attribute getPrivateAttributionAttr(unsigned index, StringAttr name);
  Attribute getPrivateAttributionAttr(unsigned index, StringRef name) {
    return getPrivateAttributionAttr(index, StringAttr::get((*this)->getContext(), name));
  }

  /// Set an attribute for a private attribution. `index` is counted
  /// from the start of the private attributions, not the start of the block.
  /// A null `value` removes an attribute.
  void setPrivateAttributionAttr(unsigned index, StringAttr name, Attribute value);
  void setPrivateAttributionAttr(unsigned index, StringRef name, Attribute value) {
    return setPrivateAttributionAttr(index, StringAttr::get((*this)->getContext(), name), value);
  }

  /// Returns the name of the attribute containing the number of buffers
  /// located in the workgroup memory.
  static StringRef getNumWorkgroupAttributionsAttrName() {
    return "workgroup_attributions";
  }

  /// Returns the argument types of this function.
  ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

  /// Returns the result types of this function.
  ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

  Region *getCallableRegion() { return &getBody(); }

  /// Returns the keywords used in the custom syntax for this Op.
  static StringRef getWorkgroupKeyword() { return "workgroup"; }
  static StringRef getPrivateKeyword() { return "private"; }
  static StringRef getKernelKeyword() { return "kernel"; }

  /// Hook for FunctionOpInterface verifier.
  LogicalResult verifyType();

  /// Verifies the body of the function.
  LogicalResult verifyBody();
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GPUFuncOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::GPUModuleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GPUModuleOpGenericAdaptorBase {
public:
  struct Properties {
    using offloadingHandlerTy = ::mlir::Attribute;
    offloadingHandlerTy offloadingHandler;

    auto getOffloadingHandler() const {
      auto &propStorage = this->offloadingHandler;
      return ::llvm::dyn_cast_or_null<::mlir::Attribute>(propStorage);
    }
    void setOffloadingHandler(const ::mlir::Attribute &propValue) {
      this->offloadingHandler = propValue;
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
    using targetsTy = ::mlir::ArrayAttr;
    targetsTy targets;

    auto getTargets() const {
      auto &propStorage = this->targets;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setTargets(const ::mlir::ArrayAttr &propValue) {
      this->targets = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.offloadingHandler == this->offloadingHandler &&
        rhs.sym_name == this->sym_name &&
        rhs.targets == this->targets &&
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
  GPUModuleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.module", odsAttrs.getContext());
  }

  GPUModuleOpGenericAdaptorBase(GPUModuleOp op);

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
  ::mlir::ArrayAttr getTargetsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().targets);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getTargets();
  ::mlir::Attribute getOffloadingHandlerAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().offloadingHandler);
    return attr;
  }

  ::std::optional<::mlir::Attribute> getOffloadingHandler();
  ::mlir::Region &getBodyRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class GPUModuleOpGenericAdaptor : public detail::GPUModuleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GPUModuleOpGenericAdaptorBase;
public:
  GPUModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GPUModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GPUModuleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GPUModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GPUModuleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GPUModuleOpGenericAdaptor(RangeT values, const GPUModuleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GPUModuleOp, typename = std::enable_if_t<std::is_same_v<LateInst, GPUModuleOp>>>
  GPUModuleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GPUModuleOpAdaptor : public GPUModuleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GPUModuleOpGenericAdaptor::GPUModuleOpGenericAdaptor;
  GPUModuleOpAdaptor(GPUModuleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GPUModuleOp : public ::mlir::Op<GPUModuleOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::DataLayoutOpInterface::Trait, ::mlir::HasDefaultDLTIDataLayout, ::mlir::OpTrait::SymbolTable, ::mlir::SymbolOpInterface::Trait, ::mlir::RegionKindInterface::Trait, ::mlir::OpTrait::HasOnlyGraphRegion> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GPUModuleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GPUModuleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("offloadingHandler"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("targets")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOffloadingHandlerAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOffloadingHandlerAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getTargetsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getTargetsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.module");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  ::mlir::ArrayAttr getTargetsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().targets);
  }

  ::std::optional< ::mlir::ArrayAttr > getTargets();
  ::mlir::Attribute getOffloadingHandlerAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().offloadingHandler);
  }

  ::std::optional<::mlir::Attribute> getOffloadingHandler();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setTargetsAttr(::mlir::ArrayAttr attr) {
    getProperties().targets = attr;
  }

  void setOffloadingHandlerAttr(::mlir::Attribute attr) {
    getProperties().offloadingHandler = attr;
  }

  ::mlir::Attribute removeTargetsAttr() {
      auto attr = getProperties().targets;
      getProperties().targets = {};
      return attr;
  }

  ::mlir::Attribute removeOffloadingHandlerAttr() {
      auto attr = getProperties().offloadingHandler;
      getProperties().offloadingHandler = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name, ArrayAttr targets = {}, Attribute handler = {});
  static GPUModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, ArrayAttr targets = {}, Attribute handler = {});
  static GPUModuleOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, ArrayAttr targets = {}, Attribute handler = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name, ArrayRef<Attribute> targets, Attribute handler = {});
  static GPUModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, ArrayRef<Attribute> targets, Attribute handler = {});
  static GPUModuleOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, ArrayRef<Attribute> targets, Attribute handler = {});
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
  /// Checks if `target` is in the `targets` list.
  bool hasTarget(Attribute target);

  /// Sets the targets of the module.
  void setTargets(ArrayRef<TargetAttrInterface> targets);
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GPUModuleOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::GlobalIdOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GlobalIdOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::gpu::DimensionAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::gpu::DimensionAttr>(propStorage);
    }
    void setDimension(const ::mlir::gpu::DimensionAttr &propValue) {
      this->dimension = propValue;
    }
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
        rhs.upper_bound == this->upper_bound &&
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
  GlobalIdOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.global_id", odsAttrs.getContext());
  }

  GlobalIdOpGenericAdaptorBase(GlobalIdOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
    return attr;
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class GlobalIdOpGenericAdaptor : public detail::GlobalIdOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GlobalIdOpGenericAdaptorBase;
public:
  GlobalIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GlobalIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GlobalIdOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GlobalIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GlobalIdOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GlobalIdOpGenericAdaptor(RangeT values, const GlobalIdOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GlobalIdOp, typename = std::enable_if_t<std::is_same_v<LateInst, GlobalIdOp>>>
  GlobalIdOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GlobalIdOpAdaptor : public GlobalIdOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GlobalIdOpGenericAdaptor::GlobalIdOpGenericAdaptor;
  GlobalIdOpAdaptor(GlobalIdOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GlobalIdOp : public ::mlir::Op<GlobalIdOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GlobalIdOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GlobalIdOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<GlobalIdOp>::inferResultRangesFromOptional;
  using ::mlir::OpAsmOpInterface::Trait<GlobalIdOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GlobalIdOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GlobalIdOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension"), ::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.global_id");
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
  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setDimensionAttr(::mlir::gpu::DimensionAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(::mlir::gpu::Dimension attrValue);
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension);
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension);
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GlobalIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GlobalIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GlobalIdOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::GridDimOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GridDimOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::gpu::DimensionAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::gpu::DimensionAttr>(propStorage);
    }
    void setDimension(const ::mlir::gpu::DimensionAttr &propValue) {
      this->dimension = propValue;
    }
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
        rhs.upper_bound == this->upper_bound &&
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
  GridDimOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.grid_dim", odsAttrs.getContext());
  }

  GridDimOpGenericAdaptorBase(GridDimOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
    return attr;
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class GridDimOpGenericAdaptor : public detail::GridDimOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GridDimOpGenericAdaptorBase;
public:
  GridDimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GridDimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GridDimOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GridDimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GridDimOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GridDimOpGenericAdaptor(RangeT values, const GridDimOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GridDimOp, typename = std::enable_if_t<std::is_same_v<LateInst, GridDimOp>>>
  GridDimOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GridDimOpAdaptor : public GridDimOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GridDimOpGenericAdaptor::GridDimOpGenericAdaptor;
  GridDimOpAdaptor(GridDimOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GridDimOp : public ::mlir::Op<GridDimOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GridDimOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GridDimOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<GridDimOp>::inferResultRangesFromOptional;
  using ::mlir::OpAsmOpInterface::Trait<GridDimOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GridDimOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GridDimOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension"), ::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.grid_dim");
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
  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setDimensionAttr(::mlir::gpu::DimensionAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(::mlir::gpu::Dimension attrValue);
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension);
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension);
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GridDimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GridDimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::GridDimOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::HostRegisterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HostRegisterOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  HostRegisterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.host_register", odsAttrs.getContext());
  }

  HostRegisterOpGenericAdaptorBase(HostRegisterOp op);

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
class HostRegisterOpGenericAdaptor : public detail::HostRegisterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HostRegisterOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  HostRegisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HostRegisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : HostRegisterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HostRegisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HostRegisterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HostRegisterOpGenericAdaptor(RangeT values, const HostRegisterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HostRegisterOp, typename = std::enable_if_t<std::is_same_v<LateInst, HostRegisterOp>>>
  HostRegisterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class HostRegisterOpAdaptor : public HostRegisterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HostRegisterOpGenericAdaptor::HostRegisterOpGenericAdaptor;
  HostRegisterOpAdaptor(HostRegisterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HostRegisterOp : public ::mlir::Op<HostRegisterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HostRegisterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HostRegisterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.host_register");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::UnrankedMemRefType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::UnrankedMemRefType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value);
  static HostRegisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value);
  static HostRegisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static HostRegisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static HostRegisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HostRegisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HostRegisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HostRegisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HostRegisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::HostRegisterOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::HostUnregisterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HostUnregisterOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  HostUnregisterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.host_unregister", odsAttrs.getContext());
  }

  HostUnregisterOpGenericAdaptorBase(HostUnregisterOp op);

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
class HostUnregisterOpGenericAdaptor : public detail::HostUnregisterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HostUnregisterOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  HostUnregisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HostUnregisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : HostUnregisterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HostUnregisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HostUnregisterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HostUnregisterOpGenericAdaptor(RangeT values, const HostUnregisterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HostUnregisterOp, typename = std::enable_if_t<std::is_same_v<LateInst, HostUnregisterOp>>>
  HostUnregisterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class HostUnregisterOpAdaptor : public HostUnregisterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HostUnregisterOpGenericAdaptor::HostUnregisterOpGenericAdaptor;
  HostUnregisterOpAdaptor(HostUnregisterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HostUnregisterOp : public ::mlir::Op<HostUnregisterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HostUnregisterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HostUnregisterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.host_unregister");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::UnrankedMemRefType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::UnrankedMemRefType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value);
  static HostUnregisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value);
  static HostUnregisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static HostUnregisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static HostUnregisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HostUnregisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HostUnregisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HostUnregisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HostUnregisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::HostUnregisterOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::LaneIdOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LaneIdOpGenericAdaptorBase {
public:
  struct Properties {
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.upper_bound == this->upper_bound &&
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
  LaneIdOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.lane_id", odsAttrs.getContext());
  }

  LaneIdOpGenericAdaptorBase(LaneIdOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class LaneIdOpGenericAdaptor : public detail::LaneIdOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LaneIdOpGenericAdaptorBase;
public:
  LaneIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LaneIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LaneIdOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LaneIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LaneIdOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LaneIdOpGenericAdaptor(RangeT values, const LaneIdOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LaneIdOp, typename = std::enable_if_t<std::is_same_v<LateInst, LaneIdOp>>>
  LaneIdOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class LaneIdOpAdaptor : public LaneIdOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LaneIdOpGenericAdaptor::LaneIdOpGenericAdaptor;
  LaneIdOpAdaptor(LaneIdOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LaneIdOp : public ::mlir::Op<LaneIdOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LaneIdOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LaneIdOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<LaneIdOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.lane_id");
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
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static LaneIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static LaneIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::IntegerAttr upper_bound);
  static LaneIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::IntegerAttr upper_bound);
  static LaneIdOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static LaneIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static LaneIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LaneIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LaneIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LaneIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LaneIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LaneIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LaneIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LaneIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LaneIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::LaneIdOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::LaunchFuncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LaunchFuncOpGenericAdaptorBase {
public:
  struct Properties {
    using kernelTy = ::mlir::SymbolRefAttr;
    kernelTy kernel;

    auto getKernel() const {
      auto &propStorage = this->kernel;
      return ::llvm::cast<::mlir::SymbolRefAttr>(propStorage);
    }
    void setKernel(const ::mlir::SymbolRefAttr &propValue) {
      this->kernel = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 13>;
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
        rhs.kernel == this->kernel &&
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
  LaunchFuncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.launch_func", odsAttrs.getContext());
  }

  LaunchFuncOpGenericAdaptorBase(LaunchFuncOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::SymbolRefAttr getKernelAttr() {
    auto attr = ::llvm::cast<::mlir::SymbolRefAttr>(getProperties().kernel);
    return attr;
  }

  ::mlir::SymbolRefAttr getKernel();
};

} // namespace detail
template <typename RangeT>
class LaunchFuncOpGenericAdaptor : public detail::LaunchFuncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LaunchFuncOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_gridSizeX = 1;
  static constexpr int odsIndex_gridSizeY = 2;
  static constexpr int odsIndex_gridSizeZ = 3;
  static constexpr int odsIndex_blockSizeX = 4;
  static constexpr int odsIndex_blockSizeY = 5;
  static constexpr int odsIndex_blockSizeZ = 6;
  static constexpr int odsIndex_clusterSizeX = 7;
  static constexpr int odsIndex_clusterSizeY = 8;
  static constexpr int odsIndex_clusterSizeZ = 9;
  static constexpr int odsIndex_dynamicSharedMemorySize = 10;
  static constexpr int odsIndex_kernelOperands = 11;
  static constexpr int odsIndex_asyncObject = 12;
public:
  LaunchFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LaunchFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LaunchFuncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LaunchFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : LaunchFuncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LaunchFuncOpGenericAdaptor(RangeT values, const LaunchFuncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LaunchFuncOp, typename = std::enable_if_t<std::is_same_v<LateInst, LaunchFuncOp>>>
  LaunchFuncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getGridSizeX() {
    return (*getODSOperands(1).begin());
  }

  ValueT getGridSizeY() {
    return (*getODSOperands(2).begin());
  }

  ValueT getGridSizeZ() {
    return (*getODSOperands(3).begin());
  }

  ValueT getBlockSizeX() {
    return (*getODSOperands(4).begin());
  }

  ValueT getBlockSizeY() {
    return (*getODSOperands(5).begin());
  }

  ValueT getBlockSizeZ() {
    return (*getODSOperands(6).begin());
  }

  ValueT getClusterSizeX() {
    auto operands = getODSOperands(7);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getClusterSizeY() {
    auto operands = getODSOperands(8);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getClusterSizeZ() {
    auto operands = getODSOperands(9);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getDynamicSharedMemorySize() {
    auto operands = getODSOperands(10);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getKernelOperands() {
    return getODSOperands(11);
  }

  ValueT getAsyncObject() {
    auto operands = getODSOperands(12);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LaunchFuncOpAdaptor : public LaunchFuncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LaunchFuncOpGenericAdaptor::LaunchFuncOpGenericAdaptor;
  LaunchFuncOpAdaptor(LaunchFuncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LaunchFuncOp : public ::mlir::Op<LaunchFuncOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<6>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LaunchFuncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LaunchFuncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_gridSizeX = 1;
  static constexpr int odsIndex_gridSizeY = 2;
  static constexpr int odsIndex_gridSizeZ = 3;
  static constexpr int odsIndex_blockSizeX = 4;
  static constexpr int odsIndex_blockSizeY = 5;
  static constexpr int odsIndex_blockSizeZ = 6;
  static constexpr int odsIndex_clusterSizeX = 7;
  static constexpr int odsIndex_clusterSizeY = 8;
  static constexpr int odsIndex_clusterSizeZ = 9;
  static constexpr int odsIndex_dynamicSharedMemorySize = 10;
  static constexpr int odsIndex_kernelOperands = 11;
  static constexpr int odsIndex_asyncObject = 12;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("kernel"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getKernelAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getKernelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.launch_func");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getGridSizeX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getGridSizeY() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getGridSizeZ() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getBlockSizeX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getBlockSizeY() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(5).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getBlockSizeZ() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(6).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getClusterSizeX() {
    auto operands = getODSOperands(7);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getClusterSizeY() {
    auto operands = getODSOperands(8);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getClusterSizeZ() {
    auto operands = getODSOperands(9);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDynamicSharedMemorySize() {
    auto operands = getODSOperands(10);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getKernelOperands() {
    return getODSOperands(11);
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncObject() {
    auto operands = getODSOperands(12);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getGridSizeXMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getGridSizeYMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getGridSizeZMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBlockSizeXMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBlockSizeYMutable() {
    auto range = getODSOperandIndexAndLength(5);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBlockSizeZMutable() {
    auto range = getODSOperandIndexAndLength(6);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getClusterSizeXMutable();
  ::mlir::MutableOperandRange getClusterSizeYMutable();
  ::mlir::MutableOperandRange getClusterSizeZMutable();
  ::mlir::MutableOperandRange getDynamicSharedMemorySizeMutable();
  ::mlir::MutableOperandRange getKernelOperandsMutable();
  ::mlir::MutableOperandRange getAsyncObjectMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::SymbolRefAttr getKernelAttr() {
    return ::llvm::cast<::mlir::SymbolRefAttr>(getProperties().kernel);
  }

  ::mlir::SymbolRefAttr getKernel();
  void setKernelAttr(::mlir::SymbolRefAttr attr) {
    getProperties().kernel = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, GPUFuncOp kernelFunc, KernelDim3 gridSize, KernelDim3 blockSize, Value dynamicSharedMemorySize, ValueRange kernelOperands, Type asyncTokenType = nullptr, ValueRange asyncDependencies = {}, std::optional<KernelDim3> clusterSize = std::nullopt);
  static LaunchFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, GPUFuncOp kernelFunc, KernelDim3 gridSize, KernelDim3 blockSize, Value dynamicSharedMemorySize, ValueRange kernelOperands, Type asyncTokenType = nullptr, ValueRange asyncDependencies = {}, std::optional<KernelDim3> clusterSize = std::nullopt);
  static LaunchFuncOp create(::mlir::ImplicitLocOpBuilder &builder, GPUFuncOp kernelFunc, KernelDim3 gridSize, KernelDim3 blockSize, Value dynamicSharedMemorySize, ValueRange kernelOperands, Type asyncTokenType = nullptr, ValueRange asyncDependencies = {}, std::optional<KernelDim3> clusterSize = std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, SymbolRefAttr kernel, KernelDim3 gridSize, KernelDim3 blockSize, Value dynamicSharedMemorySize, ValueRange kernelOperands, Type asyncTokenType, ValueRange asyncDependencies = {}, std::optional<KernelDim3> clusterSize = std::nullopt);
  static LaunchFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, SymbolRefAttr kernel, KernelDim3 gridSize, KernelDim3 blockSize, Value dynamicSharedMemorySize, ValueRange kernelOperands, Type asyncTokenType, ValueRange asyncDependencies = {}, std::optional<KernelDim3> clusterSize = std::nullopt);
  static LaunchFuncOp create(::mlir::ImplicitLocOpBuilder &builder, SymbolRefAttr kernel, KernelDim3 gridSize, KernelDim3 blockSize, Value dynamicSharedMemorySize, ValueRange kernelOperands, Type asyncTokenType, ValueRange asyncDependencies = {}, std::optional<KernelDim3> clusterSize = std::nullopt);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, SymbolRefAttr kernel, KernelDim3 gridSize, KernelDim3 blockSize, Value dynamicSharedMemorySize, ValueRange kernelOperands, Value asyncObject = nullptr, std::optional<KernelDim3> clusterSize = std::nullopt);
  static LaunchFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, SymbolRefAttr kernel, KernelDim3 gridSize, KernelDim3 blockSize, Value dynamicSharedMemorySize, ValueRange kernelOperands, Value asyncObject = nullptr, std::optional<KernelDim3> clusterSize = std::nullopt);
  static LaunchFuncOp create(::mlir::ImplicitLocOpBuilder &builder, SymbolRefAttr kernel, KernelDim3 gridSize, KernelDim3 blockSize, Value dynamicSharedMemorySize, ValueRange kernelOperands, Value asyncObject = nullptr, std::optional<KernelDim3> clusterSize = std::nullopt);
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
  /// The name of the kernel's containing module.
  StringAttr getKernelModuleName();

  /// The name of the kernel.
  StringAttr getKernelName();

  /// Returns true if cluster size is specified.
  bool hasClusterSize() {
    if (getClusterSizeX() && getClusterSizeY() && getClusterSizeZ())
      return true;
    return false;
  }

  /// The number of operands passed to the kernel function.
  unsigned getNumKernelOperands();

  /// The i-th operand passed to the kernel function.
  Value getKernelOperand(unsigned i);

  /// Get the SSA values passed as operands to specify the cluster size.
  /// When the cluster sizes are not specified, it asserts.
  KernelDim3 getClusterSizeOperandValues();

  /// Get the SSA values passed as operands to specify the grid size.
  KernelDim3 getGridSizeOperandValues();

  /// Get the SSA values passed as operands to specify the block size.
  KernelDim3 getBlockSizeOperandValues();

  // This needs to quietly verify if attributes with names defined below are
  // present since it is run before the verifier of this op.
  friend LogicalResult GPUDialect::verifyOperationAttribute(Operation *,
                                                            NamedAttribute);
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::LaunchFuncOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::LaunchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LaunchOpGenericAdaptorBase {
public:
  struct Properties {
    using functionTy = ::mlir::FlatSymbolRefAttr;
    functionTy function;

    auto getFunction() const {
      auto &propStorage = this->function;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setFunction(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->function = propValue;
    }
    using moduleTy = ::mlir::FlatSymbolRefAttr;
    moduleTy module;

    auto getModule() const {
      auto &propStorage = this->module;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setModule(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->module = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 11>;
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
        rhs.function == this->function &&
        rhs.module == this->module &&
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
  LaunchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.launch", odsAttrs.getContext());
  }

  LaunchOpGenericAdaptorBase(LaunchOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getModuleAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().module);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getModule();
  ::mlir::FlatSymbolRefAttr getFunctionAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().function);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getFunction();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class LaunchOpGenericAdaptor : public detail::LaunchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LaunchOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_gridSizeX = 1;
  static constexpr int odsIndex_gridSizeY = 2;
  static constexpr int odsIndex_gridSizeZ = 3;
  static constexpr int odsIndex_blockSizeX = 4;
  static constexpr int odsIndex_blockSizeY = 5;
  static constexpr int odsIndex_blockSizeZ = 6;
  static constexpr int odsIndex_clusterSizeX = 7;
  static constexpr int odsIndex_clusterSizeY = 8;
  static constexpr int odsIndex_clusterSizeZ = 9;
  static constexpr int odsIndex_dynamicSharedMemorySize = 10;
public:
  LaunchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LaunchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : LaunchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LaunchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : LaunchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LaunchOpGenericAdaptor(RangeT values, const LaunchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LaunchOp, typename = std::enable_if_t<std::is_same_v<LateInst, LaunchOp>>>
  LaunchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getGridSizeX() {
    return (*getODSOperands(1).begin());
  }

  ValueT getGridSizeY() {
    return (*getODSOperands(2).begin());
  }

  ValueT getGridSizeZ() {
    return (*getODSOperands(3).begin());
  }

  ValueT getBlockSizeX() {
    return (*getODSOperands(4).begin());
  }

  ValueT getBlockSizeY() {
    return (*getODSOperands(5).begin());
  }

  ValueT getBlockSizeZ() {
    return (*getODSOperands(6).begin());
  }

  ValueT getClusterSizeX() {
    auto operands = getODSOperands(7);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getClusterSizeY() {
    auto operands = getODSOperands(8);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getClusterSizeZ() {
    auto operands = getODSOperands(9);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getDynamicSharedMemorySize() {
    auto operands = getODSOperands(10);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LaunchOpAdaptor : public LaunchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LaunchOpGenericAdaptor::LaunchOpGenericAdaptor;
  LaunchOpAdaptor(LaunchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LaunchOp : public ::mlir::Op<LaunchOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<6>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AffineScope, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::InferIntRangeInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LaunchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LaunchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_gridSizeX = 1;
  static constexpr int odsIndex_gridSizeY = 2;
  static constexpr int odsIndex_gridSizeZ = 3;
  static constexpr int odsIndex_blockSizeX = 4;
  static constexpr int odsIndex_blockSizeY = 5;
  static constexpr int odsIndex_blockSizeZ = 6;
  static constexpr int odsIndex_clusterSizeX = 7;
  static constexpr int odsIndex_clusterSizeY = 8;
  static constexpr int odsIndex_clusterSizeZ = 9;
  static constexpr int odsIndex_dynamicSharedMemorySize = 10;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<LaunchOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("function"), ::llvm::StringRef("module"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFunctionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFunctionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModuleAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModuleAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.launch");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IndexType> getGridSizeX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getGridSizeY() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getGridSizeZ() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getBlockSizeX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getBlockSizeY() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(5).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getBlockSizeZ() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(6).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getClusterSizeX() {
    auto operands = getODSOperands(7);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IndexType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getClusterSizeY() {
    auto operands = getODSOperands(8);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IndexType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getClusterSizeZ() {
    auto operands = getODSOperands(9);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IndexType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDynamicSharedMemorySize() {
    auto operands = getODSOperands(10);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getGridSizeXMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getGridSizeYMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getGridSizeZMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBlockSizeXMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBlockSizeYMutable() {
    auto range = getODSOperandIndexAndLength(5);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBlockSizeZMutable() {
    auto range = getODSOperandIndexAndLength(6);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getClusterSizeXMutable();
  ::mlir::MutableOperandRange getClusterSizeYMutable();
  ::mlir::MutableOperandRange getClusterSizeZMutable();
  ::mlir::MutableOperandRange getDynamicSharedMemorySizeMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::FlatSymbolRefAttr getModuleAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().module);
  }

  ::std::optional< ::llvm::StringRef > getModule();
  ::mlir::FlatSymbolRefAttr getFunctionAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().function);
  }

  ::std::optional< ::llvm::StringRef > getFunction();
  void setModuleAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().module = attr;
  }

  void setModule(::std::optional<::llvm::StringRef> attrValue);
  void setFunctionAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().function = attr;
  }

  void setFunction(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeModuleAttr() {
      auto attr = getProperties().module;
      getProperties().module = {};
      return attr;
  }

  ::mlir::Attribute removeFunctionAttr() {
      auto attr = getProperties().function;
      getProperties().function = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value gridSizeX, Value gridSizeY, Value gridSizeZ, Value blockSizeX, Value blockSizeY, Value blockSizeZ, Value dynamicSharedMemorySize = nullptr, Type asyncTokenType = nullptr, ValueRange asyncDependencies = {}, TypeRange workgroupAttributions = {}, TypeRange privateAttributions = {}, Value clusterSizeX = nullptr, Value clusterSizeY = nullptr, Value clusterSizeZ = nullptr, FlatSymbolRefAttr module = nullptr, FlatSymbolRefAttr function = nullptr);
  static LaunchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value gridSizeX, Value gridSizeY, Value gridSizeZ, Value blockSizeX, Value blockSizeY, Value blockSizeZ, Value dynamicSharedMemorySize = nullptr, Type asyncTokenType = nullptr, ValueRange asyncDependencies = {}, TypeRange workgroupAttributions = {}, TypeRange privateAttributions = {}, Value clusterSizeX = nullptr, Value clusterSizeY = nullptr, Value clusterSizeZ = nullptr, FlatSymbolRefAttr module = nullptr, FlatSymbolRefAttr function = nullptr);
  static LaunchOp create(::mlir::ImplicitLocOpBuilder &builder, Value gridSizeX, Value gridSizeY, Value gridSizeZ, Value blockSizeX, Value blockSizeY, Value blockSizeZ, Value dynamicSharedMemorySize = nullptr, Type asyncTokenType = nullptr, ValueRange asyncDependencies = {}, TypeRange workgroupAttributions = {}, TypeRange privateAttributions = {}, Value clusterSizeX = nullptr, Value clusterSizeY = nullptr, Value clusterSizeZ = nullptr, FlatSymbolRefAttr module = nullptr, FlatSymbolRefAttr function = nullptr);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
  /// Get the SSA values corresponding to kernel block identifiers.
  KernelDim3 getBlockIds();
  /// Get the SSA values corresponding to kernel thread identifiers.
  KernelDim3 getThreadIds();
  /// Get the SSA values corresponding to kernel cluster identifiers.
  std::optional<KernelDim3> getClusterIds();
  /// Get the SSA values corresponding to kernel grid size.
  KernelDim3 getGridSize();
  /// Get the SSA values corresponding to kernel block size.
  KernelDim3 getBlockSize();
  /// Get the SSA values corresponding to kernel cluster size.
  std::optional<KernelDim3> getClusterSize();

  /// Get the SSA values passed as operands to specify the grid size.
  KernelDim3 getGridSizeOperandValues();
  /// Get the SSA values passed as operands to specify the block size.
  KernelDim3 getBlockSizeOperandValues();
  /// Get the SSA values passed as operands to specify the cluster size.
  std::optional<KernelDim3> getClusterSizeOperandValues();

  static StringRef getBlocksKeyword() { return "blocks"; }
  static StringRef getClustersKeyword() { return "clusters"; }
  static StringRef getThreadsKeyword() { return "threads"; }
  static StringRef getDynamicSharedMemorySizeKeyword() {
    return "dynamic_shared_memory_size";
  }

  /// The number of launch configuration operands, placed at the leading
  /// positions of the operand list.
  static constexpr unsigned kNumConfigOperands = 6;

  /// The number of region attributes containing the launch configuration,
  /// placed in the leading positions of the argument list.
  static constexpr unsigned kNumConfigRegionAttributes = 12;

  /// Returns true if cluster size is specified.
  bool hasClusterSize() {
    if (getClusterSizeX() && getClusterSizeY() && getClusterSizeZ())
      return true;
    return false;
  }
  /// Returns the number of operands including cluster size
  unsigned getNumConfigOperands() {
    return kNumConfigOperands + (hasClusterSize() ? 3 : 0);
  }
  /// Returns the number of region attributes including cluster size
  unsigned getNumConfigRegionAttributes() {
    return kNumConfigRegionAttributes + (hasClusterSize() ? 6 : 0);
  }

  /// Returns the keywords used in the custom syntax for this Op.
  static StringRef getWorkgroupKeyword() { return "workgroup"; }
  static StringRef getPrivateKeyword() { return "private"; }

  /// Returns the number of buffers located in the workgroup memory.
  unsigned getNumWorkgroupAttributions() {
    auto attr = (*this)->getAttrOfType<IntegerAttr>(
        getNumWorkgroupAttributionsAttrName());
    if (!attr)
      return 0;
    int64_t value = attr.getInt();
    assert(value >= 0 && value < std::numeric_limits<uint32_t>::max() &&
           "invalid workgroup attribution count");
    return value;
  }

  /// Returns a list of block arguments that correspond to buffers located in
  /// the workgroup memory
  ArrayRef<BlockArgument> getWorkgroupAttributions() {
    auto begin =
        std::next(getBody().args_begin(), getNumConfigRegionAttributes());
    auto end = std::next(begin, getNumWorkgroupAttributions());
    return {begin, end};
  }

  /// Adds a new block argument that corresponds to buffers located in
  /// workgroup memory.
  BlockArgument addWorkgroupAttribution(Type type, Location loc);

  /// Returns the number of buffers located in the private memory.
  unsigned getNumPrivateAttributions() {
    return getBody().getNumArguments() - getNumConfigRegionAttributes() -
        getNumWorkgroupAttributions();
  }

  /// Returns a list of block arguments that correspond to buffers located in
  /// the private memory.
  ArrayRef<BlockArgument> getPrivateAttributions() {
    // Buffers on the private memory always come after buffers on the workgroup
    // memory.
    auto begin =
        std::next(getBody().args_begin(),
                  getNumConfigRegionAttributes() + getNumWorkgroupAttributions());
    return {begin, getBody().args_end()};
  }

  /// Adds a new block argument that corresponds to buffers located in
  /// private memory.
  BlockArgument addPrivateAttribution(Type type, Location loc);

  /// Returns the name of the attribute containing the number of buffers
  /// located in the workgroup memory.
  static StringRef getNumWorkgroupAttributionsAttrName() {
    return "workgroup_attributions";
  }
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::LaunchOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::MemcpyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemcpyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MemcpyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.memcpy", odsAttrs.getContext());
  }

  MemcpyOpGenericAdaptorBase(MemcpyOp op);

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
class MemcpyOpGenericAdaptor : public detail::MemcpyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemcpyOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dst = 1;
  static constexpr int odsIndex_src = 2;
public:
  MemcpyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemcpyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MemcpyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemcpyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemcpyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemcpyOpGenericAdaptor(RangeT values, const MemcpyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemcpyOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemcpyOp>>>
  MemcpyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getDst() {
    return (*getODSOperands(1).begin());
  }

  ValueT getSrc() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MemcpyOpAdaptor : public MemcpyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemcpyOpGenericAdaptor::MemcpyOpGenericAdaptor;
  MemcpyOpAdaptor(MemcpyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemcpyOp : public ::mlir::Op<MemcpyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemcpyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemcpyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dst = 1;
  static constexpr int odsIndex_src = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.memcpy");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::MemRefType> getDst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(2).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getDstMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value src);
  static MemcpyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value src);
  static MemcpyOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value src);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value src);
  static MemcpyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value src);
  static MemcpyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value src);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemcpyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemcpyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemcpyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemcpyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::MemcpyOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::MemsetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemsetOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MemsetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.memset", odsAttrs.getContext());
  }

  MemsetOpGenericAdaptorBase(MemsetOp op);

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
class MemsetOpGenericAdaptor : public detail::MemsetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemsetOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dst = 1;
  static constexpr int odsIndex_value = 2;
public:
  MemsetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemsetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : MemsetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemsetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemsetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemsetOpGenericAdaptor(RangeT values, const MemsetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemsetOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemsetOp>>>
  MemsetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getDst() {
    return (*getODSOperands(1).begin());
  }

  ValueT getValue() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MemsetOpAdaptor : public MemsetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemsetOpGenericAdaptor::MemsetOpGenericAdaptor;
  MemsetOpAdaptor(MemsetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemsetOp : public ::mlir::Op<MemsetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemsetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemsetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dst = 1;
  static constexpr int odsIndex_value = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.memset");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::MemRefType> getDst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getDstMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value value);
  static MemsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value value);
  static MemsetOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value value);
  static MemsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value value);
  static MemsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value dst, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemsetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemsetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::MemsetOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::NumSubgroupsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NumSubgroupsOpGenericAdaptorBase {
public:
  struct Properties {
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.upper_bound == this->upper_bound &&
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
  NumSubgroupsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.num_subgroups", odsAttrs.getContext());
  }

  NumSubgroupsOpGenericAdaptorBase(NumSubgroupsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class NumSubgroupsOpGenericAdaptor : public detail::NumSubgroupsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NumSubgroupsOpGenericAdaptorBase;
public:
  NumSubgroupsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NumSubgroupsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : NumSubgroupsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NumSubgroupsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NumSubgroupsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NumSubgroupsOpGenericAdaptor(RangeT values, const NumSubgroupsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NumSubgroupsOp, typename = std::enable_if_t<std::is_same_v<LateInst, NumSubgroupsOp>>>
  NumSubgroupsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class NumSubgroupsOpAdaptor : public NumSubgroupsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NumSubgroupsOpGenericAdaptor::NumSubgroupsOpGenericAdaptor;
  NumSubgroupsOpAdaptor(NumSubgroupsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NumSubgroupsOp : public ::mlir::Op<NumSubgroupsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NumSubgroupsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NumSubgroupsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<NumSubgroupsOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.num_subgroups");
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
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static NumSubgroupsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static NumSubgroupsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::IntegerAttr upper_bound);
  static NumSubgroupsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::IntegerAttr upper_bound);
  static NumSubgroupsOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static NumSubgroupsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static NumSubgroupsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NumSubgroupsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NumSubgroupsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NumSubgroupsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NumSubgroupsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NumSubgroupsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NumSubgroupsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NumSubgroupsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NumSubgroupsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::NumSubgroupsOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::PrintfOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PrintfOpGenericAdaptorBase {
public:
  struct Properties {
    using formatTy = ::mlir::StringAttr;
    formatTy format;

    auto getFormat() const {
      auto &propStorage = this->format;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setFormat(const ::mlir::StringAttr &propValue) {
      this->format = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.format == this->format &&
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
  PrintfOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.printf", odsAttrs.getContext());
  }

  PrintfOpGenericAdaptorBase(PrintfOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getFormatAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().format);
    return attr;
  }

  ::llvm::StringRef getFormat();
};

} // namespace detail
template <typename RangeT>
class PrintfOpGenericAdaptor : public detail::PrintfOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PrintfOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  PrintfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PrintfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : PrintfOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PrintfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PrintfOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PrintfOpGenericAdaptor(RangeT values, const PrintfOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PrintfOp, typename = std::enable_if_t<std::is_same_v<LateInst, PrintfOp>>>
  PrintfOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PrintfOpAdaptor : public PrintfOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PrintfOpGenericAdaptor::PrintfOpGenericAdaptor;
  PrintfOpAdaptor(PrintfOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PrintfOp : public ::mlir::Op<PrintfOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PrintfOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PrintfOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_args = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("format")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFormatAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFormatAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.printf");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getArgs() {
    return getODSOperands(0);
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getFormatAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().format);
  }

  ::llvm::StringRef getFormat();
  void setFormatAttr(::mlir::StringAttr attr) {
    getProperties().format = attr;
  }

  void setFormat(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr format, ::mlir::ValueRange args);
  static PrintfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr format, ::mlir::ValueRange args);
  static PrintfOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr format, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr format, ::mlir::ValueRange args);
  static PrintfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr format, ::mlir::ValueRange args);
  static PrintfOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr format, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef format, ::mlir::ValueRange args);
  static PrintfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef format, ::mlir::ValueRange args);
  static PrintfOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef format, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef format, ::mlir::ValueRange args);
  static PrintfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef format, ::mlir::ValueRange args);
  static PrintfOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef format, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintfOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintfOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::PrintfOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::ReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.return", odsAttrs.getContext());
  }

  ReturnOpGenericAdaptorBase(ReturnOp op);

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
class ReturnOpGenericAdaptor : public detail::ReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReturnOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  ReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReturnOpGenericAdaptor(RangeT values, const ReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReturnOp>>>
  ReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ReturnOpAdaptor : public ReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReturnOpGenericAdaptor::ReturnOpGenericAdaptor;
  ReturnOpAdaptor(ReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReturnOp : public ::mlir::Op<ReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<GPUFuncOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.return");
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
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::ReturnOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::RotateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RotateOpGenericAdaptorBase {
public:
  struct Properties {
    using offsetTy = ::mlir::IntegerAttr;
    offsetTy offset;

    auto getOffset() const {
      auto &propStorage = this->offset;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setOffset(const ::mlir::IntegerAttr &propValue) {
      this->offset = propValue;
    }
    using widthTy = ::mlir::IntegerAttr;
    widthTy width;

    auto getWidth() const {
      auto &propStorage = this->width;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setWidth(const ::mlir::IntegerAttr &propValue) {
      this->width = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.offset == this->offset &&
        rhs.width == this->width &&
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
  RotateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.rotate", odsAttrs.getContext());
  }

  RotateOpGenericAdaptorBase(RotateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getOffsetAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().offset);
    return attr;
  }

  uint32_t getOffset();
  ::mlir::IntegerAttr getWidthAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().width);
    return attr;
  }

  uint32_t getWidth();
};

} // namespace detail
template <typename RangeT>
class RotateOpGenericAdaptor : public detail::RotateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RotateOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  RotateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RotateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : RotateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RotateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RotateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RotateOpGenericAdaptor(RangeT values, const RotateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RotateOp, typename = std::enable_if_t<std::is_same_v<LateInst, RotateOp>>>
  RotateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class RotateOpAdaptor : public RotateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RotateOpGenericAdaptor::RotateOpGenericAdaptor;
  RotateOpAdaptor(RotateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RotateOp : public ::mlir::Op<RotateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RotateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RotateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("offset"), ::llvm::StringRef("width")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOffsetAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOffsetAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getWidthAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.rotate");
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

  ::mlir::TypedValue<::mlir::Type> getRotateResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValid() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
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
  ::mlir::IntegerAttr getOffsetAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().offset);
  }

  uint32_t getOffset();
  ::mlir::IntegerAttr getWidthAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().width);
  }

  uint32_t getWidth();
  void setOffsetAttr(::mlir::IntegerAttr attr) {
    getProperties().offset = attr;
  }

  void setOffset(uint32_t attrValue);
  void setWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().width = attr;
  }

  void setWidth(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type rotateResult, ::mlir::Type valid, ::mlir::Value value, ::mlir::IntegerAttr offset, ::mlir::IntegerAttr width);
  static RotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type rotateResult, ::mlir::Type valid, ::mlir::Value value, ::mlir::IntegerAttr offset, ::mlir::IntegerAttr width);
  static RotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type rotateResult, ::mlir::Type valid, ::mlir::Value value, ::mlir::IntegerAttr offset, ::mlir::IntegerAttr width);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::IntegerAttr offset, ::mlir::IntegerAttr width);
  static RotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::IntegerAttr offset, ::mlir::IntegerAttr width);
  static RotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::IntegerAttr offset, ::mlir::IntegerAttr width);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::IntegerAttr offset, ::mlir::IntegerAttr width);
  static RotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::IntegerAttr offset, ::mlir::IntegerAttr width);
  static RotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::IntegerAttr offset, ::mlir::IntegerAttr width);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type rotateResult, ::mlir::Type valid, ::mlir::Value value, uint32_t offset, uint32_t width);
  static RotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type rotateResult, ::mlir::Type valid, ::mlir::Value value, uint32_t offset, uint32_t width);
  static RotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type rotateResult, ::mlir::Type valid, ::mlir::Value value, uint32_t offset, uint32_t width);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, uint32_t offset, uint32_t width);
  static RotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, uint32_t offset, uint32_t width);
  static RotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, uint32_t offset, uint32_t width);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, uint32_t offset, uint32_t width);
  static RotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, uint32_t offset, uint32_t width);
  static RotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, uint32_t offset, uint32_t width);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RotateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RotateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::RotateOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SDDMMBufferSizeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SDDMMBufferSizeOpGenericAdaptorBase {
public:
  struct Properties {
    using computeTypeTy = ::mlir::TypeAttr;
    computeTypeTy computeType;

    auto getComputeType() const {
      auto &propStorage = this->computeType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setComputeType(const ::mlir::TypeAttr &propValue) {
      this->computeType = propValue;
    }
    using modeATy = ::mlir::gpu::TransposeModeAttr;
    modeATy modeA;

    auto getModeA() const {
      auto &propStorage = this->modeA;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeA(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeA = propValue;
    }
    using modeBTy = ::mlir::gpu::TransposeModeAttr;
    modeBTy modeB;

    auto getModeB() const {
      auto &propStorage = this->modeB;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeB(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeB = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.computeType == this->computeType &&
        rhs.modeA == this->modeA &&
        rhs.modeB == this->modeB &&
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
  SDDMMBufferSizeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.sddmm_buffer_size", odsAttrs.getContext());
  }

  SDDMMBufferSizeOpGenericAdaptorBase(SDDMMBufferSizeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::TransposeModeAttr getModeAAttr();
  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr();
  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
    return attr;
  }

  ::mlir::Type getComputeType();
};

} // namespace detail
template <typename RangeT>
class SDDMMBufferSizeOpGenericAdaptor : public detail::SDDMMBufferSizeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SDDMMBufferSizeOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dnmatA = 1;
  static constexpr int odsIndex_dnmatB = 2;
  static constexpr int odsIndex_spmatC = 3;
public:
  SDDMMBufferSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SDDMMBufferSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SDDMMBufferSizeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SDDMMBufferSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SDDMMBufferSizeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SDDMMBufferSizeOpGenericAdaptor(RangeT values, const SDDMMBufferSizeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SDDMMBufferSizeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SDDMMBufferSizeOp>>>
  SDDMMBufferSizeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getDnmatA() {
    return (*getODSOperands(1).begin());
  }

  ValueT getDnmatB() {
    return (*getODSOperands(2).begin());
  }

  ValueT getSpmatC() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SDDMMBufferSizeOpAdaptor : public SDDMMBufferSizeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SDDMMBufferSizeOpGenericAdaptor::SDDMMBufferSizeOpGenericAdaptor;
  SDDMMBufferSizeOpAdaptor(SDDMMBufferSizeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SDDMMBufferSizeOp : public ::mlir::Op<SDDMMBufferSizeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SDDMMBufferSizeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SDDMMBufferSizeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dnmatA = 1;
  static constexpr int odsIndex_dnmatB = 2;
  static constexpr int odsIndex_spmatC = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("computeType"), ::llvm::StringRef("modeA"), ::llvm::StringRef("modeB")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getComputeTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getComputeTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModeAAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModeAAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getModeBAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getModeBAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.sddmm_buffer_size");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getDnmatA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDnmatB() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(3).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getDnmatAMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDnmatBMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSpmatCMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getBufferSz() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::gpu::TransposeModeAttr getModeAAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeA);
  }

  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeB);
  }

  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
  }

  ::mlir::Type getComputeType();
  void setModeAAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeA = attr;
  }

  void setModeA(::mlir::gpu::TransposeMode attrValue);
  void setModeBAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeB = attr;
  }

  void setModeB(::mlir::gpu::TransposeMode attrValue);
  void setComputeTypeAttr(::mlir::TypeAttr attr) {
    getProperties().computeType = attr;
  }

  void setComputeType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type bufferSz, Type asyncToken, ValueRange asyncDependencies, Value dnmatA, Value dnmatB, Value spmatC, Type computeType);
  static SDDMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type bufferSz, Type asyncToken, ValueRange asyncDependencies, Value dnmatA, Value dnmatB, Value spmatC, Type computeType);
  static SDDMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, Type bufferSz, Type asyncToken, ValueRange asyncDependencies, Value dnmatA, Value dnmatB, Value spmatC, Type computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static SDDMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static SDDMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static SDDMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static SDDMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static SDDMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static SDDMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static SDDMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static SDDMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SDDMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SDDMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SDDMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SDDMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SDDMMBufferSizeOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SDDMMOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SDDMMOpGenericAdaptorBase {
public:
  struct Properties {
    using computeTypeTy = ::mlir::TypeAttr;
    computeTypeTy computeType;

    auto getComputeType() const {
      auto &propStorage = this->computeType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setComputeType(const ::mlir::TypeAttr &propValue) {
      this->computeType = propValue;
    }
    using modeATy = ::mlir::gpu::TransposeModeAttr;
    modeATy modeA;

    auto getModeA() const {
      auto &propStorage = this->modeA;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeA(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeA = propValue;
    }
    using modeBTy = ::mlir::gpu::TransposeModeAttr;
    modeBTy modeB;

    auto getModeB() const {
      auto &propStorage = this->modeB;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeB(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeB = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.computeType == this->computeType &&
        rhs.modeA == this->modeA &&
        rhs.modeB == this->modeB &&
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
  SDDMMOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.sddmm", odsAttrs.getContext());
  }

  SDDMMOpGenericAdaptorBase(SDDMMOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::TransposeModeAttr getModeAAttr();
  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr();
  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
    return attr;
  }

  ::mlir::Type getComputeType();
};

} // namespace detail
template <typename RangeT>
class SDDMMOpGenericAdaptor : public detail::SDDMMOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SDDMMOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dnmatA = 1;
  static constexpr int odsIndex_dnmatB = 2;
  static constexpr int odsIndex_spmatC = 3;
  static constexpr int odsIndex_buffer = 4;
public:
  SDDMMOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SDDMMOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SDDMMOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SDDMMOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SDDMMOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SDDMMOpGenericAdaptor(RangeT values, const SDDMMOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SDDMMOp, typename = std::enable_if_t<std::is_same_v<LateInst, SDDMMOp>>>
  SDDMMOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getDnmatA() {
    return (*getODSOperands(1).begin());
  }

  ValueT getDnmatB() {
    return (*getODSOperands(2).begin());
  }

  ValueT getSpmatC() {
    return (*getODSOperands(3).begin());
  }

  ValueT getBuffer() {
    return (*getODSOperands(4).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SDDMMOpAdaptor : public SDDMMOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SDDMMOpGenericAdaptor::SDDMMOpGenericAdaptor;
  SDDMMOpAdaptor(SDDMMOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SDDMMOp : public ::mlir::Op<SDDMMOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<4>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SDDMMOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SDDMMOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_dnmatA = 1;
  static constexpr int odsIndex_dnmatB = 2;
  static constexpr int odsIndex_spmatC = 3;
  static constexpr int odsIndex_buffer = 4;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("computeType"), ::llvm::StringRef("modeA"), ::llvm::StringRef("modeB")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getComputeTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getComputeTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModeAAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModeAAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getModeBAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getModeBAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.sddmm");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getDnmatA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDnmatB() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBuffer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(4).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getDnmatAMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDnmatBMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSpmatCMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBufferMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::gpu::TransposeModeAttr getModeAAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeA);
  }

  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeB);
  }

  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
  }

  ::mlir::Type getComputeType();
  void setModeAAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeA = attr;
  }

  void setModeA(::mlir::gpu::TransposeMode attrValue);
  void setModeBAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeB = attr;
  }

  void setModeB(::mlir::gpu::TransposeMode attrValue);
  void setComputeTypeAttr(::mlir::TypeAttr attr) {
    getProperties().computeType = attr;
  }

  void setComputeType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type asyncToken, ValueRange asyncDependencies, Value dnmatA, Value dnmatB, Value spmatC, Type computeType, Value buffer);
  static SDDMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type asyncToken, ValueRange asyncDependencies, Value dnmatA, Value dnmatB, Value spmatC, Type computeType, Value buffer);
  static SDDMMOp create(::mlir::ImplicitLocOpBuilder &builder, Type asyncToken, ValueRange asyncDependencies, Value dnmatA, Value dnmatB, Value spmatC, Type computeType, Value buffer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static SDDMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static SDDMMOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static SDDMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static SDDMMOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value buffer);
  static SDDMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value buffer);
  static SDDMMOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value buffer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value buffer);
  static SDDMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value buffer);
  static SDDMMOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value dnmatA, ::mlir::Value dnmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value buffer);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SDDMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SDDMMOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SDDMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SDDMMOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SDDMMOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SetCsrPointersOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SetCsrPointersOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SetCsrPointersOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.set_csr_pointers", odsAttrs.getContext());
  }

  SetCsrPointersOpGenericAdaptorBase(SetCsrPointersOp op);

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
class SetCsrPointersOpGenericAdaptor : public detail::SetCsrPointersOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SetCsrPointersOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmat = 1;
  static constexpr int odsIndex_positions = 2;
  static constexpr int odsIndex_coordinates = 3;
  static constexpr int odsIndex_values = 4;
public:
  SetCsrPointersOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SetCsrPointersOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SetCsrPointersOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SetCsrPointersOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SetCsrPointersOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SetCsrPointersOpGenericAdaptor(RangeT values, const SetCsrPointersOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SetCsrPointersOp, typename = std::enable_if_t<std::is_same_v<LateInst, SetCsrPointersOp>>>
  SetCsrPointersOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getSpmat() {
    return (*getODSOperands(1).begin());
  }

  ValueT getPositions() {
    return (*getODSOperands(2).begin());
  }

  ValueT getCoordinates() {
    return (*getODSOperands(3).begin());
  }

  ValueT getValues() {
    return (*getODSOperands(4).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SetCsrPointersOpAdaptor : public SetCsrPointersOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SetCsrPointersOpGenericAdaptor::SetCsrPointersOpGenericAdaptor;
  SetCsrPointersOpAdaptor(SetCsrPointersOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SetCsrPointersOp : public ::mlir::Op<SetCsrPointersOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<4>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SetCsrPointersOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SetCsrPointersOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmat = 1;
  static constexpr int odsIndex_positions = 2;
  static constexpr int odsIndex_coordinates = 3;
  static constexpr int odsIndex_values = 4;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.set_csr_pointers");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getSpmat() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getPositions() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getCoordinates() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getValues() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(4).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getSpmatMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPositionsMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getCoordinatesMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValuesMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat, ::mlir::Value positions, ::mlir::Value coordinates, ::mlir::Value values);
  static SetCsrPointersOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat, ::mlir::Value positions, ::mlir::Value coordinates, ::mlir::Value values);
  static SetCsrPointersOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat, ::mlir::Value positions, ::mlir::Value coordinates, ::mlir::Value values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat, ::mlir::Value positions, ::mlir::Value coordinates, ::mlir::Value values);
  static SetCsrPointersOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat, ::mlir::Value positions, ::mlir::Value coordinates, ::mlir::Value values);
  static SetCsrPointersOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat, ::mlir::Value positions, ::mlir::Value coordinates, ::mlir::Value values);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SetCsrPointersOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SetCsrPointersOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SetCsrPointersOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SetCsrPointersOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SetCsrPointersOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SetDefaultDeviceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SetDefaultDeviceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SetDefaultDeviceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.set_default_device", odsAttrs.getContext());
  }

  SetDefaultDeviceOpGenericAdaptorBase(SetDefaultDeviceOp op);

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
class SetDefaultDeviceOpGenericAdaptor : public detail::SetDefaultDeviceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SetDefaultDeviceOpGenericAdaptorBase;
  static constexpr int odsIndex_devIndex = 0;
public:
  SetDefaultDeviceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SetDefaultDeviceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SetDefaultDeviceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SetDefaultDeviceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SetDefaultDeviceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SetDefaultDeviceOpGenericAdaptor(RangeT values, const SetDefaultDeviceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SetDefaultDeviceOp, typename = std::enable_if_t<std::is_same_v<LateInst, SetDefaultDeviceOp>>>
  SetDefaultDeviceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDevIndex() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SetDefaultDeviceOpAdaptor : public SetDefaultDeviceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SetDefaultDeviceOpGenericAdaptor::SetDefaultDeviceOpGenericAdaptor;
  SetDefaultDeviceOpAdaptor(SetDefaultDeviceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SetDefaultDeviceOp : public ::mlir::Op<SetDefaultDeviceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SetDefaultDeviceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SetDefaultDeviceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_devIndex = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.set_default_device");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDevIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getDevIndexMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value devIndex);
  static SetDefaultDeviceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value devIndex);
  static SetDefaultDeviceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value devIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value devIndex);
  static SetDefaultDeviceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value devIndex);
  static SetDefaultDeviceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value devIndex);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SetDefaultDeviceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SetDefaultDeviceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SetDefaultDeviceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SetDefaultDeviceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SetDefaultDeviceOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::ShuffleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShuffleOpGenericAdaptorBase {
public:
  struct Properties {
    using modeTy = ::mlir::gpu::ShuffleModeAttr;
    modeTy mode;

    auto getMode() const {
      auto &propStorage = this->mode;
      return ::llvm::cast<::mlir::gpu::ShuffleModeAttr>(propStorage);
    }
    void setMode(const ::mlir::gpu::ShuffleModeAttr &propValue) {
      this->mode = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.mode == this->mode &&
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
      odsOpName.emplace("gpu.shuffle", odsAttrs.getContext());
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

  ::mlir::gpu::ShuffleModeAttr getModeAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::ShuffleModeAttr>(getProperties().mode);
    return attr;
  }

  ::mlir::gpu::ShuffleMode getMode();
};

} // namespace detail
template <typename RangeT>
class ShuffleOpGenericAdaptor : public detail::ShuffleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShuffleOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_offset = 1;
  static constexpr int odsIndex_width = 2;
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

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getOffset() {
    return (*getODSOperands(1).begin());
  }

  ValueT getWidth() {
    return (*getODSOperands(2).begin());
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
class ShuffleOp : public ::mlir::Op<ShuffleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShuffleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShuffleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_offset = 1;
  static constexpr int odsIndex_width = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("mode")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getModeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getModeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.shuffle");
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

  ::mlir::TypedValue<::mlir::IntegerType> getOffset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getWidth() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getOffsetMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getWidthMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getShuffleResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValid() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
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
  ::mlir::gpu::ShuffleModeAttr getModeAttr() {
    return ::llvm::cast<::mlir::gpu::ShuffleModeAttr>(getProperties().mode);
  }

  ::mlir::gpu::ShuffleMode getMode();
  void setModeAttr(::mlir::gpu::ShuffleModeAttr attr) {
    getProperties().mode = attr;
  }

  void setMode(::mlir::gpu::ShuffleMode attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value, int32_t offset, int32_t width, ShuffleMode mode);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value, int32_t offset, int32_t width, ShuffleMode mode);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, Value value, int32_t offset, int32_t width, ShuffleMode mode);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type shuffleResult, ::mlir::Type valid, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleModeAttr mode);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type shuffleResult, ::mlir::Type valid, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleModeAttr mode);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type shuffleResult, ::mlir::Type valid, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleModeAttr mode);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleModeAttr mode);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleModeAttr mode);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleModeAttr mode);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleModeAttr mode);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleModeAttr mode);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleModeAttr mode);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type shuffleResult, ::mlir::Type valid, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleMode mode);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type shuffleResult, ::mlir::Type valid, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleMode mode);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type shuffleResult, ::mlir::Type valid, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleMode mode);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleMode mode);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleMode mode);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleMode mode);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleMode mode);
  static ShuffleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleMode mode);
  static ShuffleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value offset, ::mlir::Value width, ::mlir::gpu::ShuffleMode mode);
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::ShuffleOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SpGEMMCopyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SpGEMMCopyOpGenericAdaptorBase {
public:
  struct Properties {
    using computeTypeTy = ::mlir::TypeAttr;
    computeTypeTy computeType;

    auto getComputeType() const {
      auto &propStorage = this->computeType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setComputeType(const ::mlir::TypeAttr &propValue) {
      this->computeType = propValue;
    }
    using modeATy = ::mlir::gpu::TransposeModeAttr;
    modeATy modeA;

    auto getModeA() const {
      auto &propStorage = this->modeA;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeA(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeA = propValue;
    }
    using modeBTy = ::mlir::gpu::TransposeModeAttr;
    modeBTy modeB;

    auto getModeB() const {
      auto &propStorage = this->modeB;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeB(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeB = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.computeType == this->computeType &&
        rhs.modeA == this->modeA &&
        rhs.modeB == this->modeB &&
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
  SpGEMMCopyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.spgemm_copy", odsAttrs.getContext());
  }

  SpGEMMCopyOpGenericAdaptorBase(SpGEMMCopyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::TransposeModeAttr getModeAAttr();
  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr();
  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
    return attr;
  }

  ::mlir::Type getComputeType();
};

} // namespace detail
template <typename RangeT>
class SpGEMMCopyOpGenericAdaptor : public detail::SpGEMMCopyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SpGEMMCopyOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_desc = 1;
  static constexpr int odsIndex_spmatA = 2;
  static constexpr int odsIndex_spmatB = 3;
  static constexpr int odsIndex_spmatC = 4;
public:
  SpGEMMCopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SpGEMMCopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SpGEMMCopyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SpGEMMCopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SpGEMMCopyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SpGEMMCopyOpGenericAdaptor(RangeT values, const SpGEMMCopyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SpGEMMCopyOp, typename = std::enable_if_t<std::is_same_v<LateInst, SpGEMMCopyOp>>>
  SpGEMMCopyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getDesc() {
    return (*getODSOperands(1).begin());
  }

  ValueT getSpmatA() {
    return (*getODSOperands(2).begin());
  }

  ValueT getSpmatB() {
    return (*getODSOperands(3).begin());
  }

  ValueT getSpmatC() {
    return (*getODSOperands(4).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SpGEMMCopyOpAdaptor : public SpGEMMCopyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SpGEMMCopyOpGenericAdaptor::SpGEMMCopyOpGenericAdaptor;
  SpGEMMCopyOpAdaptor(SpGEMMCopyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SpGEMMCopyOp : public ::mlir::Op<SpGEMMCopyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<4>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SpGEMMCopyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SpGEMMCopyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_desc = 1;
  static constexpr int odsIndex_spmatA = 2;
  static constexpr int odsIndex_spmatB = 3;
  static constexpr int odsIndex_spmatC = 4;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("computeType"), ::llvm::StringRef("modeA"), ::llvm::StringRef("modeB")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getComputeTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getComputeTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModeAAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModeAAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getModeBAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getModeBAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.spgemm_copy");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getDesc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatB() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(4).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getDescMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSpmatAMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSpmatBMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSpmatCMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::gpu::TransposeModeAttr getModeAAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeA);
  }

  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeB);
  }

  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
  }

  ::mlir::Type getComputeType();
  void setModeAAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeA = attr;
  }

  void setModeA(::mlir::gpu::TransposeMode attrValue);
  void setModeBAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeB = attr;
  }

  void setModeB(::mlir::gpu::TransposeMode attrValue);
  void setComputeTypeAttr(::mlir::TypeAttr attr) {
    getProperties().computeType = attr;
  }

  void setComputeType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type asyncToken, ValueRange asyncDependencies, Value desc, Value spmatA, Value spmatB, Value spmatC, Type computeType);
  static SpGEMMCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type asyncToken, ValueRange asyncDependencies, Value desc, Value spmatA, Value spmatB, Value spmatC, Type computeType);
  static SpGEMMCopyOp create(::mlir::ImplicitLocOpBuilder &builder, Type asyncToken, ValueRange asyncDependencies, Value desc, Value spmatA, Value spmatB, Value spmatC, Type computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static SpGEMMCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static SpGEMMCopyOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static SpGEMMCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static SpGEMMCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static SpGEMMCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static SpGEMMCopyOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static SpGEMMCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static SpGEMMCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpGEMMCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpGEMMCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpGEMMCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpGEMMCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SpGEMMCopyOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SpGEMMCreateDescrOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SpGEMMCreateDescrOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SpGEMMCreateDescrOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.spgemm_create_descr", odsAttrs.getContext());
  }

  SpGEMMCreateDescrOpGenericAdaptorBase(SpGEMMCreateDescrOp op);

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
class SpGEMMCreateDescrOpGenericAdaptor : public detail::SpGEMMCreateDescrOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SpGEMMCreateDescrOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
public:
  SpGEMMCreateDescrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SpGEMMCreateDescrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SpGEMMCreateDescrOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SpGEMMCreateDescrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SpGEMMCreateDescrOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SpGEMMCreateDescrOpGenericAdaptor(RangeT values, const SpGEMMCreateDescrOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SpGEMMCreateDescrOp, typename = std::enable_if_t<std::is_same_v<LateInst, SpGEMMCreateDescrOp>>>
  SpGEMMCreateDescrOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SpGEMMCreateDescrOpAdaptor : public SpGEMMCreateDescrOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SpGEMMCreateDescrOpGenericAdaptor::SpGEMMCreateDescrOpGenericAdaptor;
  SpGEMMCreateDescrOpAdaptor(SpGEMMCreateDescrOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SpGEMMCreateDescrOp : public ::mlir::Op<SpGEMMCreateDescrOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SpGEMMCreateDescrOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SpGEMMCreateDescrOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.spgemm_create_descr");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getDesc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type desc, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies);
  static SpGEMMCreateDescrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type desc, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies);
  static SpGEMMCreateDescrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type desc, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpGEMMCreateDescrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpGEMMCreateDescrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpGEMMCreateDescrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpGEMMCreateDescrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SpGEMMCreateDescrOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SpGEMMDestroyDescrOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SpGEMMDestroyDescrOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SpGEMMDestroyDescrOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.spgemm_destroy_descr", odsAttrs.getContext());
  }

  SpGEMMDestroyDescrOpGenericAdaptorBase(SpGEMMDestroyDescrOp op);

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
class SpGEMMDestroyDescrOpGenericAdaptor : public detail::SpGEMMDestroyDescrOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SpGEMMDestroyDescrOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_desc = 1;
public:
  SpGEMMDestroyDescrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SpGEMMDestroyDescrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SpGEMMDestroyDescrOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SpGEMMDestroyDescrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SpGEMMDestroyDescrOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SpGEMMDestroyDescrOpGenericAdaptor(RangeT values, const SpGEMMDestroyDescrOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SpGEMMDestroyDescrOp, typename = std::enable_if_t<std::is_same_v<LateInst, SpGEMMDestroyDescrOp>>>
  SpGEMMDestroyDescrOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getDesc() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SpGEMMDestroyDescrOpAdaptor : public SpGEMMDestroyDescrOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SpGEMMDestroyDescrOpGenericAdaptor::SpGEMMDestroyDescrOpGenericAdaptor;
  SpGEMMDestroyDescrOpAdaptor(SpGEMMDestroyDescrOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SpGEMMDestroyDescrOp : public ::mlir::Op<SpGEMMDestroyDescrOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SpGEMMDestroyDescrOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SpGEMMDestroyDescrOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_desc = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.spgemm_destroy_descr");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getDesc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getDescMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc);
  static SpGEMMDestroyDescrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc);
  static SpGEMMDestroyDescrOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc);
  static SpGEMMDestroyDescrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc);
  static SpGEMMDestroyDescrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpGEMMDestroyDescrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpGEMMDestroyDescrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpGEMMDestroyDescrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpGEMMDestroyDescrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SpGEMMDestroyDescrOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SpGEMMWorkEstimationOrComputeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SpGEMMWorkEstimationOrComputeOpGenericAdaptorBase {
public:
  struct Properties {
    using computeTypeTy = ::mlir::TypeAttr;
    computeTypeTy computeType;

    auto getComputeType() const {
      auto &propStorage = this->computeType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setComputeType(const ::mlir::TypeAttr &propValue) {
      this->computeType = propValue;
    }
    using kindTy = ::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr;
    kindTy kind;

    auto getKind() const {
      auto &propStorage = this->kind;
      return ::llvm::cast<::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr>(propStorage);
    }
    void setKind(const ::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr &propValue) {
      this->kind = propValue;
    }
    using modeATy = ::mlir::gpu::TransposeModeAttr;
    modeATy modeA;

    auto getModeA() const {
      auto &propStorage = this->modeA;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeA(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeA = propValue;
    }
    using modeBTy = ::mlir::gpu::TransposeModeAttr;
    modeBTy modeB;

    auto getModeB() const {
      auto &propStorage = this->modeB;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeB(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeB = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.computeType == this->computeType &&
        rhs.kind == this->kind &&
        rhs.modeA == this->modeA &&
        rhs.modeB == this->modeB &&
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
  SpGEMMWorkEstimationOrComputeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.spgemm_work_estimation_or_compute", odsAttrs.getContext());
  }

  SpGEMMWorkEstimationOrComputeOpGenericAdaptorBase(SpGEMMWorkEstimationOrComputeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::TransposeModeAttr getModeAAttr();
  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr();
  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
    return attr;
  }

  ::mlir::Type getComputeType();
  ::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr getKindAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr>(getProperties().kind);
    return attr;
  }

  ::mlir::gpu::SpGEMMWorkEstimationOrComputeKind getKind();
};

} // namespace detail
template <typename RangeT>
class SpGEMMWorkEstimationOrComputeOpGenericAdaptor : public detail::SpGEMMWorkEstimationOrComputeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SpGEMMWorkEstimationOrComputeOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_desc = 1;
  static constexpr int odsIndex_spmatA = 2;
  static constexpr int odsIndex_spmatB = 3;
  static constexpr int odsIndex_spmatC = 4;
  static constexpr int odsIndex_bufferSz = 5;
  static constexpr int odsIndex_buffer = 6;
public:
  SpGEMMWorkEstimationOrComputeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SpGEMMWorkEstimationOrComputeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SpGEMMWorkEstimationOrComputeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SpGEMMWorkEstimationOrComputeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SpGEMMWorkEstimationOrComputeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SpGEMMWorkEstimationOrComputeOpGenericAdaptor(RangeT values, const SpGEMMWorkEstimationOrComputeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SpGEMMWorkEstimationOrComputeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SpGEMMWorkEstimationOrComputeOp>>>
  SpGEMMWorkEstimationOrComputeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getDesc() {
    return (*getODSOperands(1).begin());
  }

  ValueT getSpmatA() {
    return (*getODSOperands(2).begin());
  }

  ValueT getSpmatB() {
    return (*getODSOperands(3).begin());
  }

  ValueT getSpmatC() {
    return (*getODSOperands(4).begin());
  }

  ValueT getBufferSz() {
    return (*getODSOperands(5).begin());
  }

  ValueT getBuffer() {
    return (*getODSOperands(6).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SpGEMMWorkEstimationOrComputeOpAdaptor : public SpGEMMWorkEstimationOrComputeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SpGEMMWorkEstimationOrComputeOpGenericAdaptor::SpGEMMWorkEstimationOrComputeOpGenericAdaptor;
  SpGEMMWorkEstimationOrComputeOpAdaptor(SpGEMMWorkEstimationOrComputeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SpGEMMWorkEstimationOrComputeOp : public ::mlir::Op<SpGEMMWorkEstimationOrComputeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<6>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SpGEMMWorkEstimationOrComputeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SpGEMMWorkEstimationOrComputeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_desc = 1;
  static constexpr int odsIndex_spmatA = 2;
  static constexpr int odsIndex_spmatB = 3;
  static constexpr int odsIndex_spmatC = 4;
  static constexpr int odsIndex_bufferSz = 5;
  static constexpr int odsIndex_buffer = 6;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("computeType"), ::llvm::StringRef("kind"), ::llvm::StringRef("modeA"), ::llvm::StringRef("modeB")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getComputeTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getComputeTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getKindAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getModeAAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getModeAAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getModeBAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getModeBAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.spgemm_work_estimation_or_compute");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getDesc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatB() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getBufferSz() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(5).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBuffer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(6).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getDescMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSpmatAMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSpmatBMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSpmatCMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBufferSzMutable() {
    auto range = getODSOperandIndexAndLength(5);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBufferMutable() {
    auto range = getODSOperandIndexAndLength(6);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getBufferSzNew() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::gpu::TransposeModeAttr getModeAAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeA);
  }

  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeB);
  }

  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
  }

  ::mlir::Type getComputeType();
  ::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr getKindAttr() {
    return ::llvm::cast<::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr>(getProperties().kind);
  }

  ::mlir::gpu::SpGEMMWorkEstimationOrComputeKind getKind();
  void setModeAAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeA = attr;
  }

  void setModeA(::mlir::gpu::TransposeMode attrValue);
  void setModeBAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeB = attr;
  }

  void setModeB(::mlir::gpu::TransposeMode attrValue);
  void setComputeTypeAttr(::mlir::TypeAttr attr) {
    getProperties().computeType = attr;
  }

  void setComputeType(::mlir::Type attrValue);
  void setKindAttr(::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr attr) {
    getProperties().kind = attr;
  }

  void setKind(::mlir::gpu::SpGEMMWorkEstimationOrComputeKind attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type bufferSzNew, Type asyncToken, ValueRange asyncDependencies, Value desc, Value spmatA, Value spmatB, Value spmatC, Type computeType, Value bufferSz, Value buffer);
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type bufferSzNew, Type asyncToken, ValueRange asyncDependencies, Value desc, Value spmatA, Value spmatB, Value spmatC, Type computeType, Value bufferSz, Value buffer);
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::ImplicitLocOpBuilder &builder, Type bufferSzNew, Type asyncToken, ValueRange asyncDependencies, Value desc, Value spmatA, Value spmatB, Value spmatC, Type computeType, Value bufferSz, Value buffer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type bufferSzNew, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr kind);
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type bufferSzNew, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr kind);
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type bufferSzNew, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr kind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr kind);
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr kind);
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::TypeAttr computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKindAttr kind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type bufferSzNew, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKind kind);
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type bufferSzNew, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKind kind);
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type bufferSzNew, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKind kind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKind kind);
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKind kind);
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value desc, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value spmatB, ::mlir::Value spmatC, ::mlir::Type computeType, ::mlir::Value bufferSz, ::mlir::Value buffer, ::mlir::gpu::SpGEMMWorkEstimationOrComputeKind kind);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpGEMMWorkEstimationOrComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SpGEMMWorkEstimationOrComputeOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SpMMBufferSizeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SpMMBufferSizeOpGenericAdaptorBase {
public:
  struct Properties {
    using computeTypeTy = ::mlir::TypeAttr;
    computeTypeTy computeType;

    auto getComputeType() const {
      auto &propStorage = this->computeType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setComputeType(const ::mlir::TypeAttr &propValue) {
      this->computeType = propValue;
    }
    using modeATy = ::mlir::gpu::TransposeModeAttr;
    modeATy modeA;

    auto getModeA() const {
      auto &propStorage = this->modeA;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeA(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeA = propValue;
    }
    using modeBTy = ::mlir::gpu::TransposeModeAttr;
    modeBTy modeB;

    auto getModeB() const {
      auto &propStorage = this->modeB;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeB(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeB = propValue;
    }
    using resultSegmentSizesTy = std::array<int32_t, 2>;
    resultSegmentSizesTy resultSegmentSizes;
    ::llvm::ArrayRef<int32_t> getResultSegmentSizes() const {
      auto &propStorage = this->resultSegmentSizes;
      return propStorage;
    }
    void setResultSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->resultSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.computeType == this->computeType &&
        rhs.modeA == this->modeA &&
        rhs.modeB == this->modeB &&
        rhs.resultSegmentSizes == this->resultSegmentSizes &&
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
  SpMMBufferSizeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.spmm_buffer_size", odsAttrs.getContext());
  }

  SpMMBufferSizeOpGenericAdaptorBase(SpMMBufferSizeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::TransposeModeAttr getModeAAttr();
  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr();
  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
    return attr;
  }

  ::mlir::Type getComputeType();
};

} // namespace detail
template <typename RangeT>
class SpMMBufferSizeOpGenericAdaptor : public detail::SpMMBufferSizeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SpMMBufferSizeOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmatA = 1;
  static constexpr int odsIndex_dnmatB = 2;
  static constexpr int odsIndex_dnmatC = 3;
public:
  SpMMBufferSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SpMMBufferSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SpMMBufferSizeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SpMMBufferSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SpMMBufferSizeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SpMMBufferSizeOpGenericAdaptor(RangeT values, const SpMMBufferSizeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SpMMBufferSizeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SpMMBufferSizeOp>>>
  SpMMBufferSizeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getSpmatA() {
    return (*getODSOperands(1).begin());
  }

  ValueT getDnmatB() {
    return (*getODSOperands(2).begin());
  }

  ValueT getDnmatC() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SpMMBufferSizeOpAdaptor : public SpMMBufferSizeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SpMMBufferSizeOpGenericAdaptor::SpMMBufferSizeOpGenericAdaptor;
  SpMMBufferSizeOpAdaptor(SpMMBufferSizeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SpMMBufferSizeOp : public ::mlir::Op<SpMMBufferSizeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::AttrSizedResultSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SpMMBufferSizeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SpMMBufferSizeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmatA = 1;
  static constexpr int odsIndex_dnmatB = 2;
  static constexpr int odsIndex_dnmatC = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("computeType"), ::llvm::StringRef("modeA"), ::llvm::StringRef("modeB")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getComputeTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getComputeTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModeAAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModeAAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getModeBAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getModeBAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.spmm_buffer_size");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDnmatB() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDnmatC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(3).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getSpmatAMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDnmatBMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDnmatCMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getBufferSzs() {
    return getODSResults(0);
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::gpu::TransposeModeAttr getModeAAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeA);
  }

  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeB);
  }

  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
  }

  ::mlir::Type getComputeType();
  void setModeAAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeA = attr;
  }

  void setModeA(::mlir::gpu::TransposeMode attrValue);
  void setModeBAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeB = attr;
  }

  void setModeB(::mlir::gpu::TransposeMode attrValue);
  void setComputeTypeAttr(::mlir::TypeAttr attr) {
    getProperties().computeType = attr;
  }

  void setComputeType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type bufferSzs, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnmatB, Value dnmatC, Type computeType);
  static SpMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type bufferSzs, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnmatB, Value dnmatC, Type computeType);
  static SpMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, Type bufferSzs, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnmatB, Value dnmatC, Type computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange bufferSzs, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType);
  static SpMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange bufferSzs, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType);
  static SpMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange bufferSzs, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType);
  static SpMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType);
  static SpMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange bufferSzs, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType);
  static SpMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange bufferSzs, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType);
  static SpMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange bufferSzs, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType);
  static SpMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType);
  static SpMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpMMBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpMMBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SpMMBufferSizeOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SpMMOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SpMMOpGenericAdaptorBase {
public:
  struct Properties {
    using computeTypeTy = ::mlir::TypeAttr;
    computeTypeTy computeType;

    auto getComputeType() const {
      auto &propStorage = this->computeType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setComputeType(const ::mlir::TypeAttr &propValue) {
      this->computeType = propValue;
    }
    using modeATy = ::mlir::gpu::TransposeModeAttr;
    modeATy modeA;

    auto getModeA() const {
      auto &propStorage = this->modeA;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeA(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeA = propValue;
    }
    using modeBTy = ::mlir::gpu::TransposeModeAttr;
    modeBTy modeB;

    auto getModeB() const {
      auto &propStorage = this->modeB;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeB(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeB = propValue;
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
        rhs.computeType == this->computeType &&
        rhs.modeA == this->modeA &&
        rhs.modeB == this->modeB &&
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
  SpMMOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.spmm", odsAttrs.getContext());
  }

  SpMMOpGenericAdaptorBase(SpMMOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::TransposeModeAttr getModeAAttr();
  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr();
  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
    return attr;
  }

  ::mlir::Type getComputeType();
};

} // namespace detail
template <typename RangeT>
class SpMMOpGenericAdaptor : public detail::SpMMOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SpMMOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmatA = 1;
  static constexpr int odsIndex_dnmatB = 2;
  static constexpr int odsIndex_dnmatC = 3;
  static constexpr int odsIndex_buffers = 4;
public:
  SpMMOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SpMMOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SpMMOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SpMMOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : SpMMOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SpMMOpGenericAdaptor(RangeT values, const SpMMOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SpMMOp, typename = std::enable_if_t<std::is_same_v<LateInst, SpMMOp>>>
  SpMMOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getSpmatA() {
    return (*getODSOperands(1).begin());
  }

  ValueT getDnmatB() {
    return (*getODSOperands(2).begin());
  }

  ValueT getDnmatC() {
    return (*getODSOperands(3).begin());
  }

  RangeT getBuffers() {
    return getODSOperands(4);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SpMMOpAdaptor : public SpMMOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SpMMOpGenericAdaptor::SpMMOpGenericAdaptor;
  SpMMOpAdaptor(SpMMOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SpMMOp : public ::mlir::Op<SpMMOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SpMMOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SpMMOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmatA = 1;
  static constexpr int odsIndex_dnmatB = 2;
  static constexpr int odsIndex_dnmatC = 3;
  static constexpr int odsIndex_buffers = 4;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("computeType"), ::llvm::StringRef("modeA"), ::llvm::StringRef("modeB"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getComputeTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getComputeTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModeAAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModeAAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getModeBAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getModeBAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.spmm");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDnmatB() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDnmatC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(3).begin());
  }

  ::mlir::Operation::operand_range getBuffers() {
    return getODSOperands(4);
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getSpmatAMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDnmatBMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDnmatCMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getBuffersMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::gpu::TransposeModeAttr getModeAAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeA);
  }

  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::gpu::TransposeModeAttr getModeBAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeB);
  }

  ::mlir::gpu::TransposeMode getModeB();
  ::mlir::TypeAttr getComputeTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
  }

  ::mlir::Type getComputeType();
  void setModeAAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeA = attr;
  }

  void setModeA(::mlir::gpu::TransposeMode attrValue);
  void setModeBAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeB = attr;
  }

  void setModeB(::mlir::gpu::TransposeMode attrValue);
  void setComputeTypeAttr(::mlir::TypeAttr attr) {
    getProperties().computeType = attr;
  }

  void setComputeType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnmatB, Value dnmatC, Type computeType, ValueRange buffers);
  static SpMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnmatB, Value dnmatC, Type computeType, ValueRange buffers);
  static SpMMOp create(::mlir::ImplicitLocOpBuilder &builder, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnmatB, Value dnmatC, Type computeType, ValueRange buffers);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType, ::mlir::ValueRange buffers);
  static SpMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType, ::mlir::ValueRange buffers);
  static SpMMOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType, ::mlir::ValueRange buffers);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType, ::mlir::ValueRange buffers);
  static SpMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType, ::mlir::ValueRange buffers);
  static SpMMOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::gpu::TransposeModeAttr modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::TypeAttr computeType, ::mlir::ValueRange buffers);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType, ::mlir::ValueRange buffers);
  static SpMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType, ::mlir::ValueRange buffers);
  static SpMMOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType, ::mlir::ValueRange buffers);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType, ::mlir::ValueRange buffers);
  static SpMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType, ::mlir::ValueRange buffers);
  static SpMMOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::gpu::TransposeMode modeB, ::mlir::Value spmatA, ::mlir::Value dnmatB, ::mlir::Value dnmatC, ::mlir::Type computeType, ::mlir::ValueRange buffers);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpMMOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpMMOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpMMOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SpMMOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SpMVBufferSizeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SpMVBufferSizeOpGenericAdaptorBase {
public:
  struct Properties {
    using computeTypeTy = ::mlir::TypeAttr;
    computeTypeTy computeType;

    auto getComputeType() const {
      auto &propStorage = this->computeType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setComputeType(const ::mlir::TypeAttr &propValue) {
      this->computeType = propValue;
    }
    using modeATy = ::mlir::gpu::TransposeModeAttr;
    modeATy modeA;

    auto getModeA() const {
      auto &propStorage = this->modeA;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeA(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeA = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.computeType == this->computeType &&
        rhs.modeA == this->modeA &&
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
  SpMVBufferSizeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.spmv_buffer_size", odsAttrs.getContext());
  }

  SpMVBufferSizeOpGenericAdaptorBase(SpMVBufferSizeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::TransposeModeAttr getModeAAttr();
  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::TypeAttr getComputeTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
    return attr;
  }

  ::mlir::Type getComputeType();
};

} // namespace detail
template <typename RangeT>
class SpMVBufferSizeOpGenericAdaptor : public detail::SpMVBufferSizeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SpMVBufferSizeOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmatA = 1;
  static constexpr int odsIndex_dnX = 2;
  static constexpr int odsIndex_dnY = 3;
public:
  SpMVBufferSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SpMVBufferSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SpMVBufferSizeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SpMVBufferSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SpMVBufferSizeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SpMVBufferSizeOpGenericAdaptor(RangeT values, const SpMVBufferSizeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SpMVBufferSizeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SpMVBufferSizeOp>>>
  SpMVBufferSizeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getSpmatA() {
    return (*getODSOperands(1).begin());
  }

  ValueT getDnX() {
    return (*getODSOperands(2).begin());
  }

  ValueT getDnY() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SpMVBufferSizeOpAdaptor : public SpMVBufferSizeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SpMVBufferSizeOpGenericAdaptor::SpMVBufferSizeOpGenericAdaptor;
  SpMVBufferSizeOpAdaptor(SpMVBufferSizeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SpMVBufferSizeOp : public ::mlir::Op<SpMVBufferSizeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SpMVBufferSizeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SpMVBufferSizeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmatA = 1;
  static constexpr int odsIndex_dnX = 2;
  static constexpr int odsIndex_dnY = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("computeType"), ::llvm::StringRef("modeA")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getComputeTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getComputeTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModeAAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModeAAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.spmv_buffer_size");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDnX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDnY() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(3).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getSpmatAMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDnXMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDnYMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getBufferSz() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(1);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::gpu::TransposeModeAttr getModeAAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeA);
  }

  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::TypeAttr getComputeTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
  }

  ::mlir::Type getComputeType();
  void setModeAAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeA = attr;
  }

  void setModeA(::mlir::gpu::TransposeMode attrValue);
  void setComputeTypeAttr(::mlir::TypeAttr attr) {
    getProperties().computeType = attr;
  }

  void setComputeType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type bufferSz, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnX, Value dnY, Type computeType);
  static SpMVBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type bufferSz, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnX, Value dnY, Type computeType);
  static SpMVBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, Type bufferSz, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnX, Value dnY, Type computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType);
  static SpMVBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType);
  static SpMVBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType);
  static SpMVBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType);
  static SpMVBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType);
  static SpMVBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType);
  static SpMVBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type bufferSz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType);
  static SpMVBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType);
  static SpMVBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpMVBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpMVBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpMVBufferSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpMVBufferSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SpMVBufferSizeOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SpMVOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SpMVOpGenericAdaptorBase {
public:
  struct Properties {
    using computeTypeTy = ::mlir::TypeAttr;
    computeTypeTy computeType;

    auto getComputeType() const {
      auto &propStorage = this->computeType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setComputeType(const ::mlir::TypeAttr &propValue) {
      this->computeType = propValue;
    }
    using modeATy = ::mlir::gpu::TransposeModeAttr;
    modeATy modeA;

    auto getModeA() const {
      auto &propStorage = this->modeA;
      return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(propStorage);
    }
    void setModeA(const ::mlir::gpu::TransposeModeAttr &propValue) {
      this->modeA = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.computeType == this->computeType &&
        rhs.modeA == this->modeA &&
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
  SpMVOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.spmv", odsAttrs.getContext());
  }

  SpMVOpGenericAdaptorBase(SpMVOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::TransposeModeAttr getModeAAttr();
  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::TypeAttr getComputeTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
    return attr;
  }

  ::mlir::Type getComputeType();
};

} // namespace detail
template <typename RangeT>
class SpMVOpGenericAdaptor : public detail::SpMVOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SpMVOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmatA = 1;
  static constexpr int odsIndex_dnX = 2;
  static constexpr int odsIndex_dnY = 3;
  static constexpr int odsIndex_buffer = 4;
public:
  SpMVOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SpMVOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SpMVOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SpMVOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SpMVOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SpMVOpGenericAdaptor(RangeT values, const SpMVOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SpMVOp, typename = std::enable_if_t<std::is_same_v<LateInst, SpMVOp>>>
  SpMVOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getSpmatA() {
    return (*getODSOperands(1).begin());
  }

  ValueT getDnX() {
    return (*getODSOperands(2).begin());
  }

  ValueT getDnY() {
    return (*getODSOperands(3).begin());
  }

  ValueT getBuffer() {
    return (*getODSOperands(4).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SpMVOpAdaptor : public SpMVOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SpMVOpGenericAdaptor::SpMVOpGenericAdaptor;
  SpMVOpAdaptor(SpMVOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SpMVOp : public ::mlir::Op<SpMVOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<4>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::gpu::AsyncOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SpMVOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SpMVOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmatA = 1;
  static constexpr int odsIndex_dnX = 2;
  static constexpr int odsIndex_dnY = 3;
  static constexpr int odsIndex_buffer = 4;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("computeType"), ::llvm::StringRef("modeA")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getComputeTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getComputeTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModeAAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModeAAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.spmv");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getSpmatA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDnX() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDnY() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getBuffer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(4).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getSpmatAMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDnXMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDnYMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getBufferMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
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
  ::mlir::gpu::TransposeModeAttr getModeAAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::gpu::TransposeModeAttr>(getProperties().modeA);
  }

  ::mlir::gpu::TransposeMode getModeA();
  ::mlir::TypeAttr getComputeTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().computeType);
  }

  ::mlir::Type getComputeType();
  void setModeAAttr(::mlir::gpu::TransposeModeAttr attr) {
    getProperties().modeA = attr;
  }

  void setModeA(::mlir::gpu::TransposeMode attrValue);
  void setComputeTypeAttr(::mlir::TypeAttr attr) {
    getProperties().computeType = attr;
  }

  void setComputeType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnX, Value dnY, Type computeType, Value buffer);
  static SpMVOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnX, Value dnY, Type computeType, Value buffer);
  static SpMVOp create(::mlir::ImplicitLocOpBuilder &builder, Type asyncToken, ValueRange asyncDependencies, Value spmatA, Value dnX, Value dnY, Type computeType, Value buffer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static SpMVOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static SpMVOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static SpMVOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static SpMVOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeModeAttr modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::TypeAttr computeType, ::mlir::Value buffer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType, ::mlir::Value buffer);
  static SpMVOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType, ::mlir::Value buffer);
  static SpMVOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType, ::mlir::Value buffer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType, ::mlir::Value buffer);
  static SpMVOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType, ::mlir::Value buffer);
  static SpMVOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::gpu::TransposeMode modeA, ::mlir::Value spmatA, ::mlir::Value dnX, ::mlir::Value dnY, ::mlir::Type computeType, ::mlir::Value buffer);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpMVOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpMVOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpMVOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpMVOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SpMVOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SpMatGetSizeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SpMatGetSizeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SpMatGetSizeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.spmat_get_size", odsAttrs.getContext());
  }

  SpMatGetSizeOpGenericAdaptorBase(SpMatGetSizeOp op);

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
class SpMatGetSizeOpGenericAdaptor : public detail::SpMatGetSizeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SpMatGetSizeOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmat = 1;
public:
  SpMatGetSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SpMatGetSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SpMatGetSizeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SpMatGetSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SpMatGetSizeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SpMatGetSizeOpGenericAdaptor(RangeT values, const SpMatGetSizeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SpMatGetSizeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SpMatGetSizeOp>>>
  SpMatGetSizeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  ValueT getSpmat() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SpMatGetSizeOpAdaptor : public SpMatGetSizeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SpMatGetSizeOpGenericAdaptor::SpMatGetSizeOpGenericAdaptor;
  SpMatGetSizeOpAdaptor(SpMatGetSizeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SpMatGetSizeOp : public ::mlir::Op<SpMatGetSizeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SpMatGetSizeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SpMatGetSizeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  static constexpr int odsIndex_spmat = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.spmat_get_size");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getSpmat() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  ::mlir::OpOperand &getSpmatMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getRows() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getCols() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getNnz() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(3);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type rows, ::mlir::Type cols, ::mlir::Type nnz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static SpMatGetSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type rows, ::mlir::Type cols, ::mlir::Type nnz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static SpMatGetSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type rows, ::mlir::Type cols, ::mlir::Type nnz, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static SpMatGetSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static SpMatGetSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange asyncDependencies, ::mlir::Value spmat);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpMatGetSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SpMatGetSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpMatGetSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SpMatGetSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SpMatGetSizeOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupBroadcastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupBroadcastOpGenericAdaptorBase {
public:
  struct Properties {
    using broadcast_typeTy = ::mlir::gpu::BroadcastTypeAttr;
    broadcast_typeTy broadcast_type;

    auto getBroadcastType() const {
      auto &propStorage = this->broadcast_type;
      return ::llvm::cast<::mlir::gpu::BroadcastTypeAttr>(propStorage);
    }
    void setBroadcastType(const ::mlir::gpu::BroadcastTypeAttr &propValue) {
      this->broadcast_type = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.broadcast_type == this->broadcast_type &&
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
  SubgroupBroadcastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_broadcast", odsAttrs.getContext());
  }

  SubgroupBroadcastOpGenericAdaptorBase(SubgroupBroadcastOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::BroadcastTypeAttr getBroadcastTypeAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::BroadcastTypeAttr>(getProperties().broadcast_type);
    return attr;
  }

  ::mlir::gpu::BroadcastType getBroadcastType();
};

} // namespace detail
template <typename RangeT>
class SubgroupBroadcastOpGenericAdaptor : public detail::SubgroupBroadcastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupBroadcastOpGenericAdaptorBase;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_lane = 1;
public:
  SubgroupBroadcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupBroadcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupBroadcastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupBroadcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupBroadcastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupBroadcastOpGenericAdaptor(RangeT values, const SubgroupBroadcastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupBroadcastOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupBroadcastOp>>>
  SubgroupBroadcastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getLane() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SubgroupBroadcastOpAdaptor : public SubgroupBroadcastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupBroadcastOpGenericAdaptor::SubgroupBroadcastOpGenericAdaptor;
  SubgroupBroadcastOpAdaptor(SubgroupBroadcastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupBroadcastOp : public ::mlir::Op<SubgroupBroadcastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::Elementwise, ::mlir::OpTrait::Scalarizable, ::mlir::OpTrait::Vectorizable, ::mlir::OpTrait::Tensorizable, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupBroadcastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupBroadcastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_lane = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<SubgroupBroadcastOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("broadcast_type")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBroadcastTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBroadcastTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_broadcast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getLane() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getLaneMutable();
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
  ::mlir::gpu::BroadcastTypeAttr getBroadcastTypeAttr() {
    return ::llvm::cast<::mlir::gpu::BroadcastTypeAttr>(getProperties().broadcast_type);
  }

  ::mlir::gpu::BroadcastType getBroadcastType();
  void setBroadcastTypeAttr(::mlir::gpu::BroadcastTypeAttr attr) {
    getProperties().broadcast_type = attr;
  }

  void setBroadcastType(::mlir::gpu::BroadcastType attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastTypeAttr broadcast_type);
  static SubgroupBroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastTypeAttr broadcast_type);
  static SubgroupBroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastTypeAttr broadcast_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastTypeAttr broadcast_type);
  static SubgroupBroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastTypeAttr broadcast_type);
  static SubgroupBroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastTypeAttr broadcast_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastTypeAttr broadcast_type);
  static SubgroupBroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastTypeAttr broadcast_type);
  static SubgroupBroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastTypeAttr broadcast_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastType broadcast_type);
  static SubgroupBroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastType broadcast_type);
  static SubgroupBroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastType broadcast_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastType broadcast_type);
  static SubgroupBroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastType broadcast_type);
  static SubgroupBroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastType broadcast_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastType broadcast_type);
  static SubgroupBroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastType broadcast_type);
  static SubgroupBroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value lane, ::mlir::gpu::BroadcastType broadcast_type);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupBroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupBroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupBroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupBroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupBroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupBroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupBroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupBroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
  ::mlir::Speculation::Speculatability getSpeculatability();
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupBroadcastOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupIdOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupIdOpGenericAdaptorBase {
public:
  struct Properties {
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.upper_bound == this->upper_bound &&
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
  SubgroupIdOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_id", odsAttrs.getContext());
  }

  SubgroupIdOpGenericAdaptorBase(SubgroupIdOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class SubgroupIdOpGenericAdaptor : public detail::SubgroupIdOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupIdOpGenericAdaptorBase;
public:
  SubgroupIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupIdOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupIdOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupIdOpGenericAdaptor(RangeT values, const SubgroupIdOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupIdOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupIdOp>>>
  SubgroupIdOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SubgroupIdOpAdaptor : public SubgroupIdOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupIdOpGenericAdaptor::SubgroupIdOpGenericAdaptor;
  SubgroupIdOpAdaptor(SubgroupIdOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupIdOp : public ::mlir::Op<SubgroupIdOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupIdOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupIdOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<SubgroupIdOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_id");
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
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupIdOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupIdOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupMmaComputeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupMmaComputeOpGenericAdaptorBase {
public:
  struct Properties {
    using a_transposeTy = ::mlir::UnitAttr;
    a_transposeTy a_transpose;

    auto getATranspose() const {
      auto &propStorage = this->a_transpose;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setATranspose(const ::mlir::UnitAttr &propValue) {
      this->a_transpose = propValue;
    }
    using b_transposeTy = ::mlir::UnitAttr;
    b_transposeTy b_transpose;

    auto getBTranspose() const {
      auto &propStorage = this->b_transpose;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setBTranspose(const ::mlir::UnitAttr &propValue) {
      this->b_transpose = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.a_transpose == this->a_transpose &&
        rhs.b_transpose == this->b_transpose &&
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
  SubgroupMmaComputeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_mma_compute", odsAttrs.getContext());
  }

  SubgroupMmaComputeOpGenericAdaptorBase(SubgroupMmaComputeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getATransposeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().a_transpose);
    return attr;
  }

  ::std::optional<bool> getATranspose();
  ::mlir::UnitAttr getBTransposeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().b_transpose);
    return attr;
  }

  ::std::optional<bool> getBTranspose();
};

} // namespace detail
template <typename RangeT>
class SubgroupMmaComputeOpGenericAdaptor : public detail::SubgroupMmaComputeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupMmaComputeOpGenericAdaptorBase;
  static constexpr int odsIndex_opA = 0;
  static constexpr int odsIndex_opB = 1;
  static constexpr int odsIndex_opC = 2;
public:
  SubgroupMmaComputeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupMmaComputeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupMmaComputeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupMmaComputeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupMmaComputeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupMmaComputeOpGenericAdaptor(RangeT values, const SubgroupMmaComputeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupMmaComputeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupMmaComputeOp>>>
  SubgroupMmaComputeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getOpA() {
    return (*getODSOperands(0).begin());
  }

  ValueT getOpB() {
    return (*getODSOperands(1).begin());
  }

  ValueT getOpC() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SubgroupMmaComputeOpAdaptor : public SubgroupMmaComputeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupMmaComputeOpGenericAdaptor::SubgroupMmaComputeOpGenericAdaptor;
  SubgroupMmaComputeOpAdaptor(SubgroupMmaComputeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupMmaComputeOp : public ::mlir::Op<SubgroupMmaComputeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupMmaComputeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupMmaComputeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_opA = 0;
  static constexpr int odsIndex_opB = 1;
  static constexpr int odsIndex_opC = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("a_transpose"), ::llvm::StringRef("b_transpose")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getATransposeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getATransposeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getBTransposeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getBTransposeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_mma_compute");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::gpu::MMAMatrixType> getOpA() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::gpu::MMAMatrixType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::gpu::MMAMatrixType> getOpB() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::gpu::MMAMatrixType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::gpu::MMAMatrixType> getOpC() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::gpu::MMAMatrixType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getOpAMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getOpBMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getOpCMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getRes() {
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
  ::mlir::UnitAttr getATransposeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().a_transpose);
  }

  ::std::optional<bool> getATranspose();
  ::mlir::UnitAttr getBTransposeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().b_transpose);
  }

  ::std::optional<bool> getBTranspose();
  void setATransposeAttr(::mlir::UnitAttr attr) {
    getProperties().a_transpose = attr;
  }

  void setATranspose(bool attrValue);
  void setBTransposeAttr(::mlir::UnitAttr attr) {
    getProperties().b_transpose = attr;
  }

  void setBTranspose(bool attrValue);
  ::mlir::Attribute removeATransposeAttr() {
      auto attr = getProperties().a_transpose;
      getProperties().a_transpose = {};
      return attr;
  }

  ::mlir::Attribute removeBTransposeAttr() {
      auto attr = getProperties().b_transpose;
      getProperties().b_transpose = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value opA, ::mlir::Value opB, ::mlir::Value opC, /*optional*/::mlir::UnitAttr a_transpose, /*optional*/::mlir::UnitAttr b_transpose);
  static SubgroupMmaComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value opA, ::mlir::Value opB, ::mlir::Value opC, /*optional*/::mlir::UnitAttr a_transpose, /*optional*/::mlir::UnitAttr b_transpose);
  static SubgroupMmaComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value opA, ::mlir::Value opB, ::mlir::Value opC, /*optional*/::mlir::UnitAttr a_transpose, /*optional*/::mlir::UnitAttr b_transpose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value opA, ::mlir::Value opB, ::mlir::Value opC, /*optional*/::mlir::UnitAttr a_transpose, /*optional*/::mlir::UnitAttr b_transpose);
  static SubgroupMmaComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value opA, ::mlir::Value opB, ::mlir::Value opC, /*optional*/::mlir::UnitAttr a_transpose, /*optional*/::mlir::UnitAttr b_transpose);
  static SubgroupMmaComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value opA, ::mlir::Value opB, ::mlir::Value opC, /*optional*/::mlir::UnitAttr a_transpose, /*optional*/::mlir::UnitAttr b_transpose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value opA, ::mlir::Value opB, ::mlir::Value opC, /*optional*/::mlir::UnitAttr a_transpose, /*optional*/::mlir::UnitAttr b_transpose);
  static SubgroupMmaComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value opA, ::mlir::Value opB, ::mlir::Value opC, /*optional*/::mlir::UnitAttr a_transpose, /*optional*/::mlir::UnitAttr b_transpose);
  static SubgroupMmaComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value opA, ::mlir::Value opB, ::mlir::Value opC, /*optional*/::mlir::UnitAttr a_transpose, /*optional*/::mlir::UnitAttr b_transpose);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaComputeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaComputeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupMmaComputeOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupMmaConstantMatrixOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupMmaConstantMatrixOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SubgroupMmaConstantMatrixOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_mma_constant_matrix", odsAttrs.getContext());
  }

  SubgroupMmaConstantMatrixOpGenericAdaptorBase(SubgroupMmaConstantMatrixOp op);

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
class SubgroupMmaConstantMatrixOpGenericAdaptor : public detail::SubgroupMmaConstantMatrixOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupMmaConstantMatrixOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  SubgroupMmaConstantMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupMmaConstantMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupMmaConstantMatrixOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupMmaConstantMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupMmaConstantMatrixOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupMmaConstantMatrixOpGenericAdaptor(RangeT values, const SubgroupMmaConstantMatrixOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupMmaConstantMatrixOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupMmaConstantMatrixOp>>>
  SubgroupMmaConstantMatrixOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SubgroupMmaConstantMatrixOpAdaptor : public SubgroupMmaConstantMatrixOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupMmaConstantMatrixOpGenericAdaptor::SubgroupMmaConstantMatrixOpGenericAdaptor;
  SubgroupMmaConstantMatrixOpAdaptor(SubgroupMmaConstantMatrixOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupMmaConstantMatrixOp : public ::mlir::Op<SubgroupMmaConstantMatrixOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupMmaConstantMatrixOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupMmaConstantMatrixOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_mma_constant_matrix");
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

  ::mlir::TypedValue<::mlir::Type> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value value);
  static SubgroupMmaConstantMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value value);
  static SubgroupMmaConstantMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static SubgroupMmaConstantMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static SubgroupMmaConstantMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaConstantMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaConstantMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaConstantMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaConstantMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  gpu::MMAMatrixType getType() {
    return ::llvm::cast<gpu::MMAMatrixType>(getRes().getType());
  }
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupMmaConstantMatrixOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupMmaElementwiseOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupMmaElementwiseOpGenericAdaptorBase {
public:
  struct Properties {
    using opTypeTy = ::mlir::gpu::MMAElementwiseOpAttr;
    opTypeTy opType;

    auto getOpType() const {
      auto &propStorage = this->opType;
      return ::llvm::cast<::mlir::gpu::MMAElementwiseOpAttr>(propStorage);
    }
    void setOpType(const ::mlir::gpu::MMAElementwiseOpAttr &propValue) {
      this->opType = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.opType == this->opType &&
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
  SubgroupMmaElementwiseOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_mma_elementwise", odsAttrs.getContext());
  }

  SubgroupMmaElementwiseOpGenericAdaptorBase(SubgroupMmaElementwiseOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::MMAElementwiseOpAttr getOpTypeAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::MMAElementwiseOpAttr>(getProperties().opType);
    return attr;
  }

  ::mlir::gpu::MMAElementwiseOp getOpType();
};

} // namespace detail
template <typename RangeT>
class SubgroupMmaElementwiseOpGenericAdaptor : public detail::SubgroupMmaElementwiseOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupMmaElementwiseOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  SubgroupMmaElementwiseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupMmaElementwiseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupMmaElementwiseOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupMmaElementwiseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupMmaElementwiseOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupMmaElementwiseOpGenericAdaptor(RangeT values, const SubgroupMmaElementwiseOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupMmaElementwiseOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupMmaElementwiseOp>>>
  SubgroupMmaElementwiseOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SubgroupMmaElementwiseOpAdaptor : public SubgroupMmaElementwiseOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupMmaElementwiseOpGenericAdaptor::SubgroupMmaElementwiseOpGenericAdaptor;
  SubgroupMmaElementwiseOpAdaptor(SubgroupMmaElementwiseOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupMmaElementwiseOp : public ::mlir::Op<SubgroupMmaElementwiseOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupMmaElementwiseOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupMmaElementwiseOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_args = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("opType")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOpTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOpTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_mma_elementwise");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getArgs() {
    return getODSOperands(0);
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

  ::mlir::TypedValue<::mlir::Type> getRes() {
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
  ::mlir::gpu::MMAElementwiseOpAttr getOpTypeAttr() {
    return ::llvm::cast<::mlir::gpu::MMAElementwiseOpAttr>(getProperties().opType);
  }

  ::mlir::gpu::MMAElementwiseOp getOpType();
  void setOpTypeAttr(::mlir::gpu::MMAElementwiseOpAttr attr) {
    getProperties().opType = attr;
  }

  void setOpType(::mlir::gpu::MMAElementwiseOp attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOpAttr opType);
  static SubgroupMmaElementwiseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOpAttr opType);
  static SubgroupMmaElementwiseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOpAttr opType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOpAttr opType);
  static SubgroupMmaElementwiseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOpAttr opType);
  static SubgroupMmaElementwiseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOpAttr opType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOp opType);
  static SubgroupMmaElementwiseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOp opType);
  static SubgroupMmaElementwiseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOp opType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOp opType);
  static SubgroupMmaElementwiseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOp opType);
  static SubgroupMmaElementwiseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::gpu::MMAElementwiseOp opType);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaElementwiseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaElementwiseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaElementwiseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaElementwiseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  gpu::MMAMatrixType getType() {
    return ::llvm::cast<gpu::MMAMatrixType>(getRes().getType());
  }
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupMmaElementwiseOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupMmaExtractThreadLocalOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupMmaExtractThreadLocalOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SubgroupMmaExtractThreadLocalOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_mma_extract_thread_local", odsAttrs.getContext());
  }

  SubgroupMmaExtractThreadLocalOpGenericAdaptorBase(SubgroupMmaExtractThreadLocalOp op);

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
class SubgroupMmaExtractThreadLocalOpGenericAdaptor : public detail::SubgroupMmaExtractThreadLocalOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupMmaExtractThreadLocalOpGenericAdaptorBase;
  static constexpr int odsIndex_matrix = 0;
  static constexpr int odsIndex_indices = 1;
public:
  SubgroupMmaExtractThreadLocalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupMmaExtractThreadLocalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupMmaExtractThreadLocalOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupMmaExtractThreadLocalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupMmaExtractThreadLocalOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupMmaExtractThreadLocalOpGenericAdaptor(RangeT values, const SubgroupMmaExtractThreadLocalOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupMmaExtractThreadLocalOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupMmaExtractThreadLocalOp>>>
  SubgroupMmaExtractThreadLocalOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMatrix() {
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
class SubgroupMmaExtractThreadLocalOpAdaptor : public SubgroupMmaExtractThreadLocalOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupMmaExtractThreadLocalOpGenericAdaptor::SubgroupMmaExtractThreadLocalOpGenericAdaptor;
  SubgroupMmaExtractThreadLocalOpAdaptor(SubgroupMmaExtractThreadLocalOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupMmaExtractThreadLocalOp : public ::mlir::Op<SubgroupMmaExtractThreadLocalOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupMmaExtractThreadLocalOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupMmaExtractThreadLocalOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_matrix = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_mma_extract_thread_local");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getMatrix() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getMatrixMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static SubgroupMmaExtractThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static SubgroupMmaExtractThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static SubgroupMmaExtractThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static SubgroupMmaExtractThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static SubgroupMmaExtractThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static SubgroupMmaExtractThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaExtractThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaExtractThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaExtractThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaExtractThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaExtractThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaExtractThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaExtractThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaExtractThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupMmaExtractThreadLocalOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupMmaInsertThreadLocalOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupMmaInsertThreadLocalOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SubgroupMmaInsertThreadLocalOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_mma_insert_thread_local", odsAttrs.getContext());
  }

  SubgroupMmaInsertThreadLocalOpGenericAdaptorBase(SubgroupMmaInsertThreadLocalOp op);

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
class SubgroupMmaInsertThreadLocalOpGenericAdaptor : public detail::SubgroupMmaInsertThreadLocalOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupMmaInsertThreadLocalOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_matrix = 1;
  static constexpr int odsIndex_indices = 2;
public:
  SubgroupMmaInsertThreadLocalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupMmaInsertThreadLocalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupMmaInsertThreadLocalOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupMmaInsertThreadLocalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupMmaInsertThreadLocalOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupMmaInsertThreadLocalOpGenericAdaptor(RangeT values, const SubgroupMmaInsertThreadLocalOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupMmaInsertThreadLocalOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupMmaInsertThreadLocalOp>>>
  SubgroupMmaInsertThreadLocalOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getMatrix() {
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
class SubgroupMmaInsertThreadLocalOpAdaptor : public SubgroupMmaInsertThreadLocalOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupMmaInsertThreadLocalOpGenericAdaptor::SubgroupMmaInsertThreadLocalOpGenericAdaptor;
  SubgroupMmaInsertThreadLocalOpAdaptor(SubgroupMmaInsertThreadLocalOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupMmaInsertThreadLocalOp : public ::mlir::Op<SubgroupMmaInsertThreadLocalOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupMmaInsertThreadLocalOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupMmaInsertThreadLocalOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_matrix = 1;
  static constexpr int odsIndex_indices = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_mma_insert_thread_local");
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

  ::mlir::TypedValue<::mlir::Type> getMatrix() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMatrixMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value value, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static SubgroupMmaInsertThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value value, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static SubgroupMmaInsertThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value value, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static SubgroupMmaInsertThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static SubgroupMmaInsertThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value matrix, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaInsertThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaInsertThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaInsertThreadLocalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaInsertThreadLocalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupMmaInsertThreadLocalOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupMmaLoadMatrixOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupMmaLoadMatrixOpGenericAdaptorBase {
public:
  struct Properties {
    using leadDimensionTy = ::mlir::IntegerAttr;
    leadDimensionTy leadDimension;

    auto getLeadDimension() const {
      auto &propStorage = this->leadDimension;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLeadDimension(const ::mlir::IntegerAttr &propValue) {
      this->leadDimension = propValue;
    }
    using transposeTy = ::mlir::UnitAttr;
    transposeTy transpose;

    auto getTranspose() const {
      auto &propStorage = this->transpose;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setTranspose(const ::mlir::UnitAttr &propValue) {
      this->transpose = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.leadDimension == this->leadDimension &&
        rhs.transpose == this->transpose &&
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
  SubgroupMmaLoadMatrixOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_mma_load_matrix", odsAttrs.getContext());
  }

  SubgroupMmaLoadMatrixOpGenericAdaptorBase(SubgroupMmaLoadMatrixOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getLeadDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().leadDimension);
    return attr;
  }

  ::llvm::APInt getLeadDimension();
  ::mlir::UnitAttr getTransposeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().transpose);
    return attr;
  }

  ::std::optional<bool> getTranspose();
};

} // namespace detail
template <typename RangeT>
class SubgroupMmaLoadMatrixOpGenericAdaptor : public detail::SubgroupMmaLoadMatrixOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupMmaLoadMatrixOpGenericAdaptorBase;
  static constexpr int odsIndex_srcMemref = 0;
  static constexpr int odsIndex_indices = 1;
public:
  SubgroupMmaLoadMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupMmaLoadMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupMmaLoadMatrixOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupMmaLoadMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupMmaLoadMatrixOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupMmaLoadMatrixOpGenericAdaptor(RangeT values, const SubgroupMmaLoadMatrixOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupMmaLoadMatrixOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupMmaLoadMatrixOp>>>
  SubgroupMmaLoadMatrixOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSrcMemref() {
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
class SubgroupMmaLoadMatrixOpAdaptor : public SubgroupMmaLoadMatrixOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupMmaLoadMatrixOpGenericAdaptor::SubgroupMmaLoadMatrixOpGenericAdaptor;
  SubgroupMmaLoadMatrixOpAdaptor(SubgroupMmaLoadMatrixOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupMmaLoadMatrixOp : public ::mlir::Op<SubgroupMmaLoadMatrixOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupMmaLoadMatrixOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupMmaLoadMatrixOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_srcMemref = 0;
  static constexpr int odsIndex_indices = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("leadDimension"), ::llvm::StringRef("transpose")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLeadDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLeadDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTransposeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTransposeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_mma_load_matrix");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getSrcMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getSrcMemrefMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getRes() {
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
  ::mlir::IntegerAttr getLeadDimensionAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().leadDimension);
  }

  ::llvm::APInt getLeadDimension();
  ::mlir::UnitAttr getTransposeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().transpose);
  }

  ::std::optional<bool> getTranspose();
  void setLeadDimensionAttr(::mlir::IntegerAttr attr) {
    getProperties().leadDimension = attr;
  }

  void setLeadDimension(::llvm::APInt attrValue);
  void setTransposeAttr(::mlir::UnitAttr attr) {
    getProperties().transpose = attr;
  }

  void setTranspose(bool attrValue);
  ::mlir::Attribute removeTransposeAttr() {
      auto attr = getProperties().transpose;
      getProperties().transpose = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaLoadMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaLoadMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaLoadMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaLoadMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaLoadMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaLoadMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaLoadMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaLoadMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value srcMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaLoadMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaLoadMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaLoadMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaLoadMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupMmaLoadMatrixOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupMmaStoreMatrixOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupMmaStoreMatrixOpGenericAdaptorBase {
public:
  struct Properties {
    using leadDimensionTy = ::mlir::IntegerAttr;
    leadDimensionTy leadDimension;

    auto getLeadDimension() const {
      auto &propStorage = this->leadDimension;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLeadDimension(const ::mlir::IntegerAttr &propValue) {
      this->leadDimension = propValue;
    }
    using transposeTy = ::mlir::UnitAttr;
    transposeTy transpose;

    auto getTranspose() const {
      auto &propStorage = this->transpose;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setTranspose(const ::mlir::UnitAttr &propValue) {
      this->transpose = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.leadDimension == this->leadDimension &&
        rhs.transpose == this->transpose &&
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
  SubgroupMmaStoreMatrixOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_mma_store_matrix", odsAttrs.getContext());
  }

  SubgroupMmaStoreMatrixOpGenericAdaptorBase(SubgroupMmaStoreMatrixOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getLeadDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().leadDimension);
    return attr;
  }

  ::llvm::APInt getLeadDimension();
  ::mlir::UnitAttr getTransposeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().transpose);
    return attr;
  }

  ::std::optional<bool> getTranspose();
};

} // namespace detail
template <typename RangeT>
class SubgroupMmaStoreMatrixOpGenericAdaptor : public detail::SubgroupMmaStoreMatrixOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupMmaStoreMatrixOpGenericAdaptorBase;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_dstMemref = 1;
  static constexpr int odsIndex_indices = 2;
public:
  SubgroupMmaStoreMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupMmaStoreMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupMmaStoreMatrixOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupMmaStoreMatrixOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupMmaStoreMatrixOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupMmaStoreMatrixOpGenericAdaptor(RangeT values, const SubgroupMmaStoreMatrixOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupMmaStoreMatrixOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupMmaStoreMatrixOp>>>
  SubgroupMmaStoreMatrixOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getDstMemref() {
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
class SubgroupMmaStoreMatrixOpAdaptor : public SubgroupMmaStoreMatrixOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupMmaStoreMatrixOpGenericAdaptor::SubgroupMmaStoreMatrixOpGenericAdaptor;
  SubgroupMmaStoreMatrixOpAdaptor(SubgroupMmaStoreMatrixOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupMmaStoreMatrixOp : public ::mlir::Op<SubgroupMmaStoreMatrixOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupMmaStoreMatrixOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupMmaStoreMatrixOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_dstMemref = 1;
  static constexpr int odsIndex_indices = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("leadDimension"), ::llvm::StringRef("transpose")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLeadDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLeadDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTransposeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTransposeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_mma_store_matrix");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::gpu::MMAMatrixType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::gpu::MMAMatrixType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getDstMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDstMemrefMutable() {
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
  ::mlir::IntegerAttr getLeadDimensionAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().leadDimension);
  }

  ::llvm::APInt getLeadDimension();
  ::mlir::UnitAttr getTransposeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().transpose);
  }

  ::std::optional<bool> getTranspose();
  void setLeadDimensionAttr(::mlir::IntegerAttr attr) {
    getProperties().leadDimension = attr;
  }

  void setLeadDimension(::llvm::APInt attrValue);
  void setTransposeAttr(::mlir::UnitAttr attr) {
    getProperties().transpose = attr;
  }

  void setTranspose(bool attrValue);
  ::mlir::Attribute removeTransposeAttr() {
      auto attr = getProperties().transpose;
      getProperties().transpose = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaStoreMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaStoreMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaStoreMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaStoreMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::mlir::IntegerAttr leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaStoreMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaStoreMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaStoreMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static SubgroupMmaStoreMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value dstMemref, ::mlir::ValueRange indices, ::llvm::APInt leadDimension, /*optional*/::mlir::UnitAttr transpose);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaStoreMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupMmaStoreMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaStoreMatrixOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupMmaStoreMatrixOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupMmaStoreMatrixOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupReduceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupReduceOpGenericAdaptorBase {
public:
  struct Properties {
    using cluster_sizeTy = ::mlir::IntegerAttr;
    cluster_sizeTy cluster_size;

    auto getClusterSize() const {
      auto &propStorage = this->cluster_size;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setClusterSize(const ::mlir::IntegerAttr &propValue) {
      this->cluster_size = propValue;
    }
    using cluster_strideTy = ::mlir::IntegerAttr;
    cluster_strideTy cluster_stride;

    auto getClusterStride() const {
      auto &propStorage = this->cluster_stride;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setClusterStride(const ::mlir::IntegerAttr &propValue) {
      this->cluster_stride = propValue;
    }
    using opTy = ::mlir::gpu::AllReduceOperationAttr;
    opTy op;

    auto getOp() const {
      auto &propStorage = this->op;
      return ::llvm::cast<::mlir::gpu::AllReduceOperationAttr>(propStorage);
    }
    void setOp(const ::mlir::gpu::AllReduceOperationAttr &propValue) {
      this->op = propValue;
    }
    using uniformTy = ::mlir::UnitAttr;
    uniformTy uniform;

    auto getUniform() const {
      auto &propStorage = this->uniform;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setUniform(const ::mlir::UnitAttr &propValue) {
      this->uniform = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.cluster_size == this->cluster_size &&
        rhs.cluster_stride == this->cluster_stride &&
        rhs.op == this->op &&
        rhs.uniform == this->uniform &&
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
  SubgroupReduceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_reduce", odsAttrs.getContext());
  }

  SubgroupReduceOpGenericAdaptorBase(SubgroupReduceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::AllReduceOperationAttr getOpAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::AllReduceOperationAttr>(getProperties().op);
    return attr;
  }

  ::mlir::gpu::AllReduceOperation getOp();
  ::mlir::UnitAttr getUniformAttr();
  bool getUniform();
  ::mlir::IntegerAttr getClusterSizeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().cluster_size);
    return attr;
  }

  ::std::optional<uint32_t> getClusterSize();
  ::mlir::IntegerAttr getClusterStrideAttr();
  uint32_t getClusterStride();
};

} // namespace detail
template <typename RangeT>
class SubgroupReduceOpGenericAdaptor : public detail::SubgroupReduceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupReduceOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  SubgroupReduceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupReduceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupReduceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupReduceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupReduceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupReduceOpGenericAdaptor(RangeT values, const SubgroupReduceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupReduceOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupReduceOp>>>
  SubgroupReduceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SubgroupReduceOpAdaptor : public SubgroupReduceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupReduceOpGenericAdaptor::SubgroupReduceOpGenericAdaptor;
  SubgroupReduceOpAdaptor(SubgroupReduceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupReduceOp : public ::mlir::Op<SubgroupReduceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupReduceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupReduceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("cluster_size"), ::llvm::StringRef("cluster_stride"), ::llvm::StringRef("op"), ::llvm::StringRef("uniform")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getClusterSizeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getClusterSizeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getClusterStrideAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getClusterStrideAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOpAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getOpAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getUniformAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getUniformAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_reduce");
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
  ::mlir::gpu::AllReduceOperationAttr getOpAttr() {
    return ::llvm::cast<::mlir::gpu::AllReduceOperationAttr>(getProperties().op);
  }

  ::mlir::gpu::AllReduceOperation getOp();
  ::mlir::UnitAttr getUniformAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().uniform);
  }

  bool getUniform();
  ::mlir::IntegerAttr getClusterSizeAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().cluster_size);
  }

  ::std::optional<uint32_t> getClusterSize();
  ::mlir::IntegerAttr getClusterStrideAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().cluster_stride);
  }

  uint32_t getClusterStride();
  void setOpAttr(::mlir::gpu::AllReduceOperationAttr attr) {
    getProperties().op = attr;
  }

  void setOp(::mlir::gpu::AllReduceOperation attrValue);
  void setUniformAttr(::mlir::UnitAttr attr) {
    getProperties().uniform = attr;
  }

  void setUniform(bool attrValue);
  void setClusterSizeAttr(::mlir::IntegerAttr attr) {
    getProperties().cluster_size = attr;
  }

  void setClusterSize(::std::optional<uint32_t> attrValue);
  void setClusterStrideAttr(::mlir::IntegerAttr attr) {
    getProperties().cluster_stride = attr;
  }

  void setClusterStride(uint32_t attrValue);
  ::mlir::Attribute removeUniformAttr() {
      auto attr = getProperties().uniform;
      getProperties().uniform = {};
      return attr;
  }

  ::mlir::Attribute removeClusterSizeAttr() {
      auto attr = getProperties().cluster_size;
      getProperties().cluster_size = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value, ::mlir::gpu::AllReduceOperation op, bool uniform);
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value, ::mlir::gpu::AllReduceOperation op, bool uniform);
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, Value value, ::mlir::gpu::AllReduceOperation op, bool uniform);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value, ::mlir::gpu::AllReduceOperation op, bool uniform, std::optional<uint32_t> cluster_size);
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value, ::mlir::gpu::AllReduceOperation op, bool uniform, std::optional<uint32_t> cluster_size);
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, Value value, ::mlir::gpu::AllReduceOperation op, bool uniform, std::optional<uint32_t> cluster_size);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value value, ::mlir::gpu::AllReduceOperation op, bool uniform, std::optional<uint32_t> cluster_size, uint32_t cluster_stride);
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value value, ::mlir::gpu::AllReduceOperation op, bool uniform, std::optional<uint32_t> cluster_size, uint32_t cluster_stride);
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, Value value, ::mlir::gpu::AllReduceOperation op, bool uniform, std::optional<uint32_t> cluster_size, uint32_t cluster_stride);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform, /*optional*/::mlir::IntegerAttr cluster_size, ::mlir::IntegerAttr cluster_stride = nullptr);
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform, /*optional*/::mlir::IntegerAttr cluster_size, ::mlir::IntegerAttr cluster_stride = nullptr);
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform, /*optional*/::mlir::IntegerAttr cluster_size, ::mlir::IntegerAttr cluster_stride = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform, /*optional*/::mlir::IntegerAttr cluster_size, ::mlir::IntegerAttr cluster_stride = nullptr);
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform, /*optional*/::mlir::IntegerAttr cluster_size, ::mlir::IntegerAttr cluster_stride = nullptr);
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform, /*optional*/::mlir::IntegerAttr cluster_size, ::mlir::IntegerAttr cluster_stride = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform, /*optional*/::mlir::IntegerAttr cluster_size, ::mlir::IntegerAttr cluster_stride = nullptr);
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform, /*optional*/::mlir::IntegerAttr cluster_size, ::mlir::IntegerAttr cluster_stride = nullptr);
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::gpu::AllReduceOperationAttr op, /*optional*/::mlir::UnitAttr uniform, /*optional*/::mlir::IntegerAttr cluster_size, ::mlir::IntegerAttr cluster_stride = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::gpu::AllReduceOperation op, /*optional*/bool uniform, /*optional*/::mlir::IntegerAttr cluster_size, uint32_t cluster_stride = 1);
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::gpu::AllReduceOperation op, /*optional*/bool uniform, /*optional*/::mlir::IntegerAttr cluster_size, uint32_t cluster_stride = 1);
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::gpu::AllReduceOperation op, /*optional*/bool uniform, /*optional*/::mlir::IntegerAttr cluster_size, uint32_t cluster_stride = 1);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::gpu::AllReduceOperation op, /*optional*/bool uniform, /*optional*/::mlir::IntegerAttr cluster_size, uint32_t cluster_stride = 1);
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::gpu::AllReduceOperation op, /*optional*/bool uniform, /*optional*/::mlir::IntegerAttr cluster_size, uint32_t cluster_stride = 1);
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::gpu::AllReduceOperation op, /*optional*/bool uniform, /*optional*/::mlir::IntegerAttr cluster_size, uint32_t cluster_stride = 1);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::gpu::AllReduceOperation op, /*optional*/bool uniform, /*optional*/::mlir::IntegerAttr cluster_size, uint32_t cluster_stride = 1);
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::gpu::AllReduceOperation op, /*optional*/bool uniform, /*optional*/::mlir::IntegerAttr cluster_size, uint32_t cluster_stride = 1);
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::gpu::AllReduceOperation op, /*optional*/bool uniform, /*optional*/::mlir::IntegerAttr cluster_size, uint32_t cluster_stride = 1);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupReduceOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::SubgroupSizeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubgroupSizeOpGenericAdaptorBase {
public:
  struct Properties {
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.upper_bound == this->upper_bound &&
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
  SubgroupSizeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.subgroup_size", odsAttrs.getContext());
  }

  SubgroupSizeOpGenericAdaptorBase(SubgroupSizeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class SubgroupSizeOpGenericAdaptor : public detail::SubgroupSizeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubgroupSizeOpGenericAdaptorBase;
public:
  SubgroupSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubgroupSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SubgroupSizeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubgroupSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubgroupSizeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubgroupSizeOpGenericAdaptor(RangeT values, const SubgroupSizeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubgroupSizeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubgroupSizeOp>>>
  SubgroupSizeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SubgroupSizeOpAdaptor : public SubgroupSizeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubgroupSizeOpGenericAdaptor::SubgroupSizeOpGenericAdaptor;
  SubgroupSizeOpAdaptor(SubgroupSizeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubgroupSizeOp : public ::mlir::Op<SubgroupSizeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubgroupSizeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubgroupSizeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<SubgroupSizeOp>::inferResultRangesFromOptional;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.subgroup_size");
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
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupSizeOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static SubgroupSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SubgroupSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SubgroupSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::SubgroupSizeOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::TerminatorOp declarations
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
      odsOpName.emplace("gpu.terminator", odsAttrs.getContext());
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
class TerminatorOp : public ::mlir::Op<TerminatorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<LaunchOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
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
    return ::llvm::StringLiteral("gpu.terminator");
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::TerminatorOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::ThreadIdOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ThreadIdOpGenericAdaptorBase {
public:
  struct Properties {
    using dimensionTy = ::mlir::gpu::DimensionAttr;
    dimensionTy dimension;

    auto getDimension() const {
      auto &propStorage = this->dimension;
      return ::llvm::cast<::mlir::gpu::DimensionAttr>(propStorage);
    }
    void setDimension(const ::mlir::gpu::DimensionAttr &propValue) {
      this->dimension = propValue;
    }
    using upper_boundTy = ::mlir::IntegerAttr;
    upper_boundTy upper_bound;

    auto getUpperBound() const {
      auto &propStorage = this->upper_bound;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setUpperBound(const ::mlir::IntegerAttr &propValue) {
      this->upper_bound = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.dimension == this->dimension &&
        rhs.upper_bound == this->upper_bound &&
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
  ThreadIdOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.thread_id", odsAttrs.getContext());
  }

  ThreadIdOpGenericAdaptorBase(ThreadIdOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    auto attr = ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
    return attr;
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
    return attr;
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
};

} // namespace detail
template <typename RangeT>
class ThreadIdOpGenericAdaptor : public detail::ThreadIdOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ThreadIdOpGenericAdaptorBase;
public:
  ThreadIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ThreadIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ThreadIdOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ThreadIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ThreadIdOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ThreadIdOpGenericAdaptor(RangeT values, const ThreadIdOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ThreadIdOp, typename = std::enable_if_t<std::is_same_v<LateInst, ThreadIdOp>>>
  ThreadIdOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ThreadIdOpAdaptor : public ThreadIdOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ThreadIdOpGenericAdaptor::ThreadIdOpGenericAdaptor;
  ThreadIdOpAdaptor(ThreadIdOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ThreadIdOp : public ::mlir::Op<ThreadIdOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ThreadIdOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ThreadIdOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferIntRangeInterface::Trait<ThreadIdOp>::inferResultRangesFromOptional;
  using ::mlir::OpAsmOpInterface::Trait<ThreadIdOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ThreadIdOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ThreadIdOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dimension"), ::llvm::StringRef("upper_bound")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDimensionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDimensionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getUpperBoundAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getUpperBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.thread_id");
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
  ::mlir::gpu::DimensionAttr getDimensionAttr() {
    return ::llvm::cast<::mlir::gpu::DimensionAttr>(getProperties().dimension);
  }

  ::mlir::gpu::Dimension getDimension();
  ::mlir::IntegerAttr getUpperBoundAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().upper_bound);
  }

  ::std::optional< ::llvm::APInt > getUpperBound();
  void setDimensionAttr(::mlir::gpu::DimensionAttr attr) {
    getProperties().dimension = attr;
  }

  void setDimension(::mlir::gpu::Dimension attrValue);
  void setUpperBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().upper_bound = attr;
  }

  void setUpperBound(::std::optional<::llvm::APInt> attrValue);
  ::mlir::Attribute removeUpperBoundAttr() {
      auto attr = getProperties().upper_bound;
      getProperties().upper_bound = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension);
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension);
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType, ::mlir::gpu::Dimension dimension);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::DimensionAttr dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::gpu::Dimension dimension, /*optional*/::mlir::IntegerAttr upper_bound);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ThreadIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ThreadIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
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
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::ThreadIdOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::WaitOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WaitOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WaitOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.wait", odsAttrs.getContext());
  }

  WaitOpGenericAdaptorBase(WaitOp op);

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
class WaitOpGenericAdaptor : public detail::WaitOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WaitOpGenericAdaptorBase;
  static constexpr int odsIndex_asyncDependencies = 0;
public:
  WaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WaitOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WaitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WaitOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WaitOpGenericAdaptor(RangeT values, const WaitOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WaitOp, typename = std::enable_if_t<std::is_same_v<LateInst, WaitOp>>>
  WaitOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAsyncDependencies() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WaitOpAdaptor : public WaitOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WaitOpGenericAdaptor::WaitOpGenericAdaptor;
  WaitOpAdaptor(WaitOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WaitOp : public ::mlir::Op<WaitOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::gpu::AsyncOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WaitOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WaitOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_asyncDependencies = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.wait");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAsyncDependencies() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getAsyncDependenciesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getAsyncToken() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::Type>() : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*results.begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies);
  static WaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies);
  static WaitOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type asyncToken, ::mlir::ValueRange asyncDependencies);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WaitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WaitOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::WaitOp)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::WarpExecuteOnLane0Op declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WarpExecuteOnLane0OpGenericAdaptorBase {
public:
  struct Properties {
    using warp_sizeTy = ::mlir::IntegerAttr;
    warp_sizeTy warp_size;

    auto getWarpSize() const {
      auto &propStorage = this->warp_size;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setWarpSize(const ::mlir::IntegerAttr &propValue) {
      this->warp_size = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.warp_size == this->warp_size &&
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
  WarpExecuteOnLane0OpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("gpu.warp_execute_on_lane_0", odsAttrs.getContext());
  }

  WarpExecuteOnLane0OpGenericAdaptorBase(WarpExecuteOnLane0Op op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getWarpSizeAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().warp_size);
    return attr;
  }

  uint64_t getWarpSize();
  ::mlir::Region &getWarpRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class WarpExecuteOnLane0OpGenericAdaptor : public detail::WarpExecuteOnLane0OpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WarpExecuteOnLane0OpGenericAdaptorBase;
  static constexpr int odsIndex_laneid = 0;
  static constexpr int odsIndex_args = 1;
public:
  WarpExecuteOnLane0OpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WarpExecuteOnLane0OpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : WarpExecuteOnLane0OpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WarpExecuteOnLane0OpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WarpExecuteOnLane0OpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WarpExecuteOnLane0OpGenericAdaptor(RangeT values, const WarpExecuteOnLane0OpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WarpExecuteOnLane0Op, typename = std::enable_if_t<std::is_same_v<LateInst, WarpExecuteOnLane0Op>>>
  WarpExecuteOnLane0OpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLaneid() {
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
class WarpExecuteOnLane0OpAdaptor : public WarpExecuteOnLane0OpGenericAdaptor<::mlir::ValueRange> {
public:
  using WarpExecuteOnLane0OpGenericAdaptor::WarpExecuteOnLane0OpGenericAdaptor;
  WarpExecuteOnLane0OpAdaptor(WarpExecuteOnLane0Op op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WarpExecuteOnLane0Op : public ::mlir::Op<WarpExecuteOnLane0Op, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<gpu::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::RegionBranchOpInterface::Trait, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WarpExecuteOnLane0OpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WarpExecuteOnLane0OpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_laneid = 0;
  static constexpr int odsIndex_args = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchOpInterface::Trait<WarpExecuteOnLane0Op>::getEntrySuccessorOperands;
  using ::mlir::RegionBranchOpInterface::Trait<WarpExecuteOnLane0Op>::getEntrySuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<WarpExecuteOnLane0Op>::getSuccessorRegions;
  using ::mlir::RegionBranchOpInterface::Trait<WarpExecuteOnLane0Op>::getPredecessors;
  using ::mlir::RegionBranchOpInterface::Trait<WarpExecuteOnLane0Op>::getPredecessorValues;
  using ::mlir::RegionBranchOpInterface::Trait<WarpExecuteOnLane0Op>::getRegionInvocationBounds;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("warp_size")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getWarpSizeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getWarpSizeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.warp_execute_on_lane_0");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getLaneid() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getArgs() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getLaneidMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
  }

  ::mlir::Region &getWarpRegion() {
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
  ::mlir::IntegerAttr getWarpSizeAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().warp_size);
  }

  uint64_t getWarpSize();
  void setWarpSizeAttr(::mlir::IntegerAttr attr) {
    getProperties().warp_size = attr;
  }

  void setWarpSize(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, Value laneid, int64_t warpSize);
  static WarpExecuteOnLane0Op create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, Value laneid, int64_t warpSize);
  static WarpExecuteOnLane0Op create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, Value laneid, int64_t warpSize);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes, Value laneid, int64_t warpSize, ValueRange args, TypeRange blockArgTypes);
  static WarpExecuteOnLane0Op create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, Value laneid, int64_t warpSize, ValueRange args, TypeRange blockArgTypes);
  static WarpExecuteOnLane0Op create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, Value laneid, int64_t warpSize, ValueRange args, TypeRange blockArgTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getSuccessorRegions(::mlir::RegionBranchPoint point, ::llvm::SmallVectorImpl<::mlir::RegionSuccessor> &regions);
  ::mlir::ValueRange getSuccessorInputs(::mlir::RegionSuccessor successor);
  bool areTypesCompatible(::mlir::Type lhs, ::mlir::Type rhs);
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
  bool isDefinedOutsideOfRegion(Value value) {
    return !getRegion().isAncestor(value.getParentRegion());
  }

  /// Get the terminator of the warp region.
  gpu::YieldOp getTerminator();
};

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::WarpExecuteOnLane0Op)

namespace mlir::gpu {


//===----------------------------------------------------------------------===//
// ::mlir::gpu::YieldOp declarations
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
      odsOpName.emplace("gpu.yield", odsAttrs.getContext());
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
  static constexpr int odsIndex_values = 0;
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

  RangeT getValues() {
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
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = YieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = YieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_values = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<YieldOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("gpu.yield");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getValues() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getValuesMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange values);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange values);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange values);
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

} // namespace mlir::gpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::gpu::YieldOp)


#endif // GET_OP_CLASSES

