/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ShardOps.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::shard {

/// All-gather over a device grid.
/// Concatenates all tensor slices from a device group defined by `grid_axes` along
///     the tensor dimension `gather_axis` and replicates the result across all devices
///     in the group.
/// 
///     Example:
///     ```mlir
///     shard.grid @grid0(shape = 2x2)
///     ...
///     %1 = shard.all_gather %0 on @grid0 grid_axes = [1] gather_axis = 1
///       : tensor<2x2xi8> -> tensor<2x4xi8>
///     ```
///     Input:
///     ```
///                      +-------+-------+
///     device (0, 0) -> |  1  2 |  5  6 | <- device (0, 1)
///                      |  3  4 |  7  8 |
///                      +-------+-------+
///     device (1, 0) -> |  9 10 | 13 14 | <- device (1, 1)
///                      | 11 12 | 15 16 |
///                      +-------+-------+
///     ```
///     Result:
///     ```
///     gather tensor
///     axis 1
///     ------------>
///     +-------------+
///     |  1  2  5  6 | <- devices (0, 0) and (0, 1)
///     |  3  4  7  8 |
///     +-------------+
///     |  9 10 13 14 | <- devices (1, 0) and (1, 1)
///     | 11 12 15 16 |
///     +-------------+
///     ```
class AllGatherOp;

} // namespace mlir::shard
namespace mlir::shard {

/// All-reduce over a device grid.
/// Reduces the input tensor across all devices within the groups defined by
///     `grid_axes`, using the specified reduction method. The operation performs an
///     element-wise reduction over the tensor slices from all devices in each group.
///     Each device in a group receives a replicated copy of the reduction result.
///     The accumulation element type is determined by the result type and does not
///     need to match the input element type. Before performing the reduction, each
///     input element is converted to the result element type.
/// 
///     Attributes:
///     `reduction`: Indicates the reduction method.
/// 
///     Example:
///     ```
///     %1 = shard.all_reduce %0 on @grid0 grid_axes = [1, 0] reduction = <max>
///       : tensor<3x4xf32> -> tensor<3x4xf64>
///     ```
class AllReduceOp;

} // namespace mlir::shard
namespace mlir::shard {

/// All-slice over a device grid.
/// Within each device group defined by `grid_axes`, slices the input tensor along
///     the `slice_axis` dimension. It can be viewed as the inverse of an all-gather if
///     the input data is replicated along the `slice_axis`.
///     Each process simply crops its local data to the slice corresponding to its
///     in-group device index.
///     Notice: `AllSliceOp` does not involve any communication between devices and
///             devices within a group may not have replicated input data.
/// 
///     Example:
///     ```mlir
///     shard.grid @grid0(shape = 2x2)
///     ...
///     %1 = shard.all_slice %0 on @grid0 grid_axes = [1] slice_axis = 1
///       : tensor<2x4xi8> -> tensor<2x2xi8>
///     ```
///     Input:
///     ```
///     +-------------+
///     |  1  2  5  6 | <- devices (0, 0) and (0, 1)
///     |  3  4  7  8 |
///     +-------------+
///     |  9 10 13 14 | <- devices (1, 0) and (1, 1)
///     | 11 12 15 16 |
///     +-------------+
///     ```
///     Result:
///     ```
///     slice tensor
///     axis 1
///     ------------>
///                      +-------+-------+
///     device (0, 0) -> |  1  2 |  5  6 | <- device (0, 1)
///                      |  3  4 |  7  8 |
///                      +-------+-------+
///     device (1, 0) -> |  9 10 | 13 14 | <- device (1, 1)
///                      | 11 12 | 15 16 |
///                      +-------+-------+
///     ```
class AllSliceOp;

} // namespace mlir::shard
namespace mlir::shard {

/// All-to-all over a device grid.
/// Each participant logically splits its input along split_axis,
///     then scatters the resulting pieces across the group defined by `grid_axes`.
///     After receiving data pieces from other participants' scatters,
///     it concatenates them along concat_axis to produce the final result.
/// 
///     Example:
///     ```
///     shard.grid @grid0(shape = 3)
///     ...
///     %1 = shard.all_to_all %0 on @grid0 grid_axes = [0]
///       split_axis = 0 concat_axis = 0
///       : tensor<3x2xi8> -> tensor<3x2xi8>
///     ```
///     Input:
///     ```
///      device  device  device
///      (0)     (1)     (2)
///     +-------+-------+-------+  | split and concat along
///     | 11 12 | 21 22 | 31 32 |  | tensor axis 0
///     | 13 14 | 23 24 | 33 34 |  ↓
///     | 15 16 | 25 26 | 35 36 |
///     +-------+-------+-------+
///     ```
///     Result:
///     ```
///      device  device  device
///      (0)     (1)     (2)
///     +-------+-------+-------+
///     | 11 12 | 13 14 | 15 16 |
///     | 21 22 | 23 24 | 25 26 |
///     | 31 32 | 33 34 | 35 36 |
///     +-------+-------+-------+
///     ```
class AllToAllOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Broadcast over a device grid.
/// Copies the input tensor on `root` to all devices in each group defined by
///     `grid_axes`. The `root` device is defined by its in-group multi-index.
///     The contents of input tensors on non-root devices are ignored.
///     
///     Example:
///     ```
///     shard.grid @grid0(shape = 2x2)
/// 
///     %1 = shard.broadcast %0 on @grid0
///       grid_axes = [0]
///       root = [0]
///       : (tensor<2xi8>) -> tensor<2xi8>
///     ```
///     
///     Input:
///     ```
///                      +-------+-------+                   | broadcast
///     device (0, 0) -> |  1  2 |  3  4 | <- device (0, 1)  | along axis 0
///                      +-------+-------+                   ↓
///     device (1, 0) -> |  *  * |  *  * | <- device (1, 1)
///                      +-------+-------+
///     ```
/// 
///     Output:
///     ```
///                      +-------+-------+
///     device (0, 0) -> |  1  2 |  3  4 | <- device (0, 1)
///                      +-------+-------+
///     device (1, 0) -> |  1  2 |  3  4 | <- device (1, 1)
///                      +-------+-------+
///     ```
class BroadcastOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Gather over a device grid.
/// Concatenates all tensor slices from a device group defined by `grid_axes` along
///     the tensor dimension `gather_axis` and returns the resulting tensor on each
///     `root` device. The result on all other (non-root) devices is undefined.
///     The `root` device is defined by its in-group multi-index.
/// 
///     Example:
///     ```mlir
///     shard.grid @grid0(shape = 2x2)
///     ...
///     %1 = shard.gather %0 on @grid0 grid_axes = [1]
///       gather_axis = 1 root = [1]
///       : (tensor<2x2xi8>) -> tensor<2x4xi8>
///     ```
///     Input:
///     ```
///                       gather tensor
///                       axis 1
///                       ------------>
///                      +-------+-------+
///     device (0, 0) -> |  1  2 |  5  6 | <- device (0, 1)
///                      |  3  4 |  7  8 |
///                      +-------+-------+
///     device (1, 0) -> |  9 10 | 13 14 | <- device (1, 1)
///                      | 11 12 | 15 16 |
///                      +-------+-------+
///     ```
///     Result:
///     ```
///     +-------------+
///     |  1  2  5  6 | <- devices (0, 1)
///     |  3  4  7  8 |
///     +-------------+
///     |  9 10 13 14 | <- devices (1, 1)
///     | 11 12 15 16 |
///     +-------------+
///     ```
///     Devices `(0, 0)` and `(1, 0)` have undefined result.
class GatherOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Get the sharding of the given tensor.
/// This operation returns the sharding of the given tensor as a Sharding.
class GetShardingOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Description of a device/process grid.
/// The shard.grid operation is a symbol operation that identifies a specific
///     grid. The operation has three attributes:
/// 
///     1. `sym_name`: This attribute uniquely identifies the name of the grid.
///     This name serves as a symbolic reference to the grid throughout
///     the MLIR module, allowing for consistent referencing and easier debugging.
/// 
///     2. `shape`: This attribute represents the shape of the device grid.
///     It uses the same notation as a tensor shape. Also allowing for dynamic
///     dimensions.
///     This flexibility allows for dynamic device assignment or configurations
///     where the exact number of devices might not be determined during compile
///     time.
///     For example `2x?x4`.
/// 
///     Example:
///     ```
///     // A device grid with 3 axes, the total device number is 4 * 8 * 12
///     // The dimension sizes are 4, 8, 12 
///     shard.grid @grid0(shape = 4x8x12)
/// 
///     // A device grid with 2 axes, the total device number is unknown
///     // The first dimension size is 4 and the second is unknown
///     shard.grid @grid1(shape = 4x?)
/// 
///     // A device grid with 2 axes, the total device number is unknown
///     // The first dimension size is unknown and the second is 4
///     shard.grid @grid2(shape = ?x4)
/// 
///     // A device grid with 2 axes, the number of devices along both axes
///     // is unknown
///     shard.grid @grid3(shape = ?x?)
///     ```
class GridOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Get the shape of the grid.
class GridShapeOp;

} // namespace mlir::shard
namespace mlir::shard {

/// For given grid index get the linear indices of the direct neighbor processes along the given split.
/// Example:
///     ```
///     shard.grid @grid0(shape = 10x20x30)
///     %c1 = arith.constant 1 : index
///     %c2 = arith.constant 2 : index
///     %c3 = arith.constant 3 : index
///     %idx = shard.neighbors_linear_indices on @grid[%c1, %c2, %c3] split_axes = [1] : index
///     ```
///     The above returns two indices, `633` and `693`, which correspond to the
///     index of the previous process `(1, 1, 3)`, and the next process 
///     `(1, 3, 3)` along the split axis `1`.
/// 
///     A negative value is returned if there is no neighbor in the respective
///     direction along the given `split_axes`.
class NeighborsLinearIndicesOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Get the linear index of the current device.
/// Example:
///     ```
///     %idx = shard.process_linear_index on @grid : index
///     ```
///     if `@grid` has shape `(10, 20, 30)`, a device with multi
///     index `(1, 2, 3)` will have linear index `3 + 30*2 + 20*30*1`.
class ProcessLinearIndexOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Get the multi index of current device along specified grid axes.
/// It is used in the SPMD format of IR.
///     The `axes` mush be non-negative and less than the total number of grid axes.
///     If the axes are empty then get the index along all axes.
class ProcessMultiIndexOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Send over a device grid.
/// Receive tensor from device `source`, which is defined by its in-group
///     multi-index. The groups are defined by `grid_axes`.
///     The content of input tensor is ignored.
class RecvOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Reduce over a device grid.
/// Reduces the input tensor across all devices within the groups defined by
///     `grid_axes`, using the specified reduction method. The operation performs an
///     element-wise reduction over the tensor slices from all devices in each group.
///     The reduction result will be returned on the `root` device of each group.
///     It is undefined on all other (non-root) devices.
///     The `root` device is defined by its in-group multi-index.
///     The accumulation element type is determined by the result type and does not
///     need to match the input element type. Before performing the reduction, each
///     input element is converted to the result element type.
/// 
///     Attributes:
///     `reduction`: Indicates the reduction method.
/// 
///     Example:
///     ```
///     %1 = shard.reduce %0 on @grid0 grid_axes = [1, 0]
///       reduction = <max> root = [2, 3]
///       : (tensor<3x4xf32>) -> tensor<3x4xf64>
///     ```
class ReduceOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Reduce-scatter over a device grid.
/// Reduces the input tensor across all devices within the groups defined by
///     `grid_axes` using the specified reduction method. The reduction is performed
///     element-wise across the tensor pieces from all devices in the group.
///     After reduction, the reduction result is scattered (split and distributed)
///     across the device group along `scatter_axis`.
///     Example:
///     ```
///     shard.grid @grid0(shape = 2x2)
///     ...
///     %1 = shard.reduce_scatter %0 on @grid0 grid_axes = [1]
///       reduction = <max> scatter_axis = 0
///       : tensor<2x2xf32> -> tensor<1x2xf64>
///     ```
///     Input:
///     ```
///                               device
///                               (0, 1)
///                                  ↓
///                      +-------+-------+  | scatter tensor
///     device (0, 0) -> |  1  2 |  5  6 |  | axis 0
///                      |  3  4 |  7  8 |  ↓
///                      +-------+-------+
///     device (1, 0) -> |  9 10 | 13 14 |
///                      | 11 12 | 15 16 |
///                      +-------+-------+
///                                 ↑
///                               device
///                               (1, 1)
///     ```
///     Result:
///     ```
///     +-------+
///     |  5  6 | <- devices (0, 0)
///     +-------+
///     |  7  8 | <- devices (0, 1)
///     +-------+
///     | 13 14 | <- devices (1, 0)
///     +-------+
///     | 15 16 | <- devices (1, 1)
///     +-------+
///     ```
class ReduceScatterOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Scatter over a device grid.
/// For each device group defined by `grid_axes`, the input tensor on the `root`
///     device is split along axis `scatter_axis` and distributed across the group.
///     The content of the input on all other (non-root) devices is ignored.
///     The `root` device is defined by its in-group multi-index.
/// 
///     Example:
///     ```
///     shard.grid @grid0(shape = 2x2)
///     %1 = shard.scatter %0 on @grid0 grid_axes = [0]
///       scatter_axis = 0
///       root = [1]
///       : (tensor<2x2xi8>) -> tensor<1x2xi8>
///     ```
/// 
///     Input:
///     ```
///                               device
///                               (0, 1)
///                                  ↓
///                      +-------+-------+  | scatter tensor
///     device (0, 0) -> |  *  * |  *  * |  | axis 0
///                      |  *  * |  *  * |  ↓
///                      +-------+-------+
///     device (1, 0) -> |  1  2 |  5  6 |
///                      |  3  4 |  7  8 |
///                      +-------+-------+
///                                 ↑
///                               device
///                               (1, 1)
///     ```
///     
///     Result:
///     ```
///                               device
///                               (0, 1)
///                                  ↓
///                      +-------+-------+
///     device (0, 0) -> |  1  2 |  5  6 |
///                      +-------+-------+ 
///     device (1, 0) -> |  3  4 |  7  8 |
///                      +-------+-------+
///                                 ↑
///                               device
///                               (1, 1)
///     ```
class ScatterOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Send over a device grid.
/// Send input tensor to device `destination`, which is defined by its in-group
///     multi-index. The groups are defined by `grid_axes`.
class SendOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Annotate on how a tensor is sharded across a shard.
/// The shard.shard operation is designed to specify and guide the sharding
///     behavior of a tensor value across a grid topology. This operation has two
///     operands and two optional attributes:
/// 
///     1. `input`: This operand represents the tensor value that needs to be
///     annotated for sharding.
/// 
///     2. `sharding`: This attribute is type of `ShardingType`, which is the core data
///     structure to represent distribution of a tensor on a shard. it is typically defined
///     by an `shard.sharding` operation.
/// 
///     3. `annotate_for_users`: A unit attribute addressing the scenario when a
///     tensor's sharding annotation differs based on its context of use (either as
///     a result or an operand). If specified, the sharding pertains to specific
///     users of the tensor value, indicating how it should be considered when used
///     as an operand in subsequent operations. If not, the sharding applies to the
///     operation that defines the tensor value.
/// 
///     Example:
///     ```
///   func.func @only_result_annotated(%arg0 : tensor<4x8xf32>) -> () {
///       %sharding = shard.sharding @grid0 split_axes = [[0]] : !shard.sharding
///       %0 = shard.shard %arg0 to %sharding : tensor<4x8xf32>
///       ...
///     }
/// 
///     func.func @only_operand_annotated(%arg0 : tensor<4x8xf32>) -> () {
///       %sharding = shard.sharding @grid0 split_axes = [[0]] : !shard.sharding
///       %0 = shard.shard %arg0 to %sharding annotate_for_users : tensor<4x8xf32>
///       ...
///     }
///     
///     func.func @two_operands_annotated(%arg0 : tensor<4x8xf32>, %arg1 : tensor<16x8xf32>) -> () {
///       %sharding = shard.sharding @grid0 split_axes = [[0]] : !shard.sharding
///       %0 = shard.shard %arg0 to %sharding annotate_for_users : tensor<4x8xf32>
///       %1 = shard.shard %arg1 to %sharding annotate_for_users : tensor<16x8xf32>
///       ...
///     }
/// 
///     // The first shard.shard op applies to %arg0, the second shard.shard op
///     // applies for the operand of op0, the third shard.shard op applies for the
///     // operand of op2
///     func.func @both_result_and_multi_operands_annotated(
///         %arg0 : tensor<4x8xf32>) -> () {
///       %sharding = shard.sharding @grid0 split_axes = [[0]] : !shard.sharding
///       %0 = shard.shard %arg0 to %sharding : tensor<4x8xf32>
///       %sharding1 = shard.sharding @grid0 split_axes = [[1]] : !shard.sharding
///       %1 = shard.shard %0 to %sharding1 annotate_for_users : tensor<4x8xf32>
///       %sharding2 = shard.sharding @grid0 split_axes = [[2]] : !shard.sharding
///       %2 = shard.shard %0 to %sharding2 annotate_for_users : tensor<4x8xf32>
///       "op0"(%1) : ...
///       "op1"(%2) : ...
///       ...
///     }
///     ```
/// 
///     The following usages are undefined:
///     ```
///     func.func @annotate_on_same_result_with_different_sharding(
///         %arg0 : tensor<4x8xf32>) -> () {
///       %sharding1 = shard.sharding @grid0 split_axes = [[0]] : !shard.sharding
///       %sharding2 = shard.sharding @grid0 split_axes = [[1]] : !shard.sharding
///       %0 = shard.shard %arg0 to $sharding1 : tensor<4x8xf32>
///       %1 = shard.shard %0 to sharding2 : tensor<4x8xf32>
///       ...
///     }
/// 
///     func.func @annotate_on_same_result_same_value_with_different_sharding(
///         %arg0 : tensor<4x8xf32>) -> () {
///       %sharding1 = shard.sharding @grid0 split_axes = [[0]] : !shard.sharding
///       %sharding2 = shard.sharding @grid0 split_axes = [[1]] : !shard.sharding
///       %0 = shard.shard %arg0 to %sharding1 : tensor<4x8xf32>
///       %1 = shard.shard %arg0 to %sharding2 : tensor<4x8xf32>
///       ...
///     }
/// 
///     func.func @annotate_on_same_operand_with_different_sharding(
///         %arg0 : tensor<4x8xf32>) -> () {
///       %sharding1 = shard.sharding @grid0 split_axes = [[0]] : !shard.sharding
///       %sharding2 = shard.sharding @grid0 split_axes = [[1]] : !shard.sharding
///       %0 = shard.shard %arg0 to %sharding1 annotate_for_users : tensor<4x8xf32>
///       %1 = shard.shard %0 to %sharding2 annotate_for_users : tensor<4x8xf32>
///       ...
///     }
/// 
///     func.func @result_annotated_after_operand(
///         %arg0 : tensor<4x8xf32>) -> () {
///       %sharding1 = shard.sharding @grid0 split_axes = [[0]] : !shard.sharding
///       %sharding2 = shard.sharding @grid0 split_axes = [[1]] : !shard.sharding
///       %0 = shard.shard %arg0 to %sharding1 annotate_for_users : tensor<4x8xf32>
///       %1 = shard.shard %0 to %sharding2 : tensor<4x8xf32>
///       ...
///     }
///     ```
class ShardOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Get the shard shape for a given process/device.
/// The device/process id is a multi-index of the device/process in the shard.
///     This operation might be used during partition when the shard shape depends
///     on (non-constant) values used in `shard.sharding`.
class ShardShapeOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Define a sharding of a tensor.
/// The Sharding specifies how a tensor is sharded and distributed across the
///     process shard. It is typically used in a `shard.shard` operation.
///     The operation has the following attributes and operands:
/// 
///     1. `grid`: this attribute is a FlatSymbolRefAttr that refers to the device
///     grid where the distributed tensor is placed. The symbol must resolve to a
///     `shard.grid` operation.
/// 
///     2. `split_axes`: is an array composed of int64_t sub-arrays. The outer array's
///     maximum size is the `rank` of the related tensor. For the i-th sub-array, if
///     its value is [x, y], it indicates that the tensor's i-th dimension is splitted
///     along the x and y axes of the device grid.
/// 
///     3. [Optional] Sizes of halos to be added for each sharded tensor dimension.
///     `halo_sizes` is provided as a flattened 1d array of i64s, 2 values for each
///     sharded dimension. `halo_sizes = [1, 2]` means that the first sharded dimension
///     gets an additional halo of size 1 at the start of the first dimension and a halo
///     size is 2 at its end. `halo_sizes = [1, 2, 2, 3]` defines halos for the first 2
///     sharded dimensions e.g. the first sharded dimension gets `[1,2]` halos and the
///     seconds gets `[2,3]` halos. `?` indicates dynamic halo sizes.
///     
///     4. [Optional] Offsets for each shard and sharded tensor dimension.
///     `sharded_dims_offsets` is provided as a flattened 1d array of i64s. For each
///     sharded tensor dimension the offsets (starting index) of all shards in that
///     dimension and an additional value for the end of the last shard are provided.
///     For a 1d sharding this means that position `i` has the exclusive prefix sum for
///     shard `i`, and since only contiguous sharding is supported, its inclusive prefix
///     sum is at position 'i+1'.
///     
///     Assuming a 3d-tensor of shape 32x32x32 with the first 2 dimensions being sharded,
///     `sharded_dims_offsets` = [0, 24, 32, 0, 20, 32] means that the first device of
///     the device-grid will get a shard of shape 24x20x32 and the second device will get
///     a shard of shape 8x12x32. `?` indicates dynamic shard dimensions.
///     
///     `halo_sizes` and `sharded_dims_offsets` are mutually exclusive.
/// 
///     Examples:
/// 
///     ```
///     shard.grid @grid0(shape = 2x2x4)
///     shard.grid @grid1d_4(shape = 4)
/// 
///     // The tensor is fully replicated on @grid0.
///     // Currently, there must be at least one sub-array present in axes, even
///     // if it's empty. Otherwise, a parsing error will occur.
///     %sharding0 = shard.sharding @grid0 split_axes = [[]]
/// 
///     // The tensor is sharded on the first dimension along axis 0 of @grid0
///     %sharding1 = shard.sharding @grid0 split_axes = [[0]]
/// 
///     // Could be used for a shard.shard op
///     %sharded0 = shard.shard %arg0 to %sharding3 : tensor<4x8xf32>
/// 
///     // The tensor is sharded on its first dimension along axis 0 of @grid0 and
///     // and it has halo-sizes of 1 and 2 on the sharded dim.
///     %halo_sharding = shard.sharding @grid0 split_axes = [[0]] halo_sizes = [1, 2]
///     %sharded1 = shard.shard %arg0 to %halo_sharding : tensor<4x8xf32>
///     
///     // The tensor is sharded on its second dimension along axis 0 of @grid1d_4
///     // and it has pre-defined shard sizes. The shards of the devices will have
///     // the following shapes: [4x2, 4x3, 4x4, 4x5]
///     %sharding4 = shard.sharding @grid1d_4 split_axes = [[], [0]] sharded_dims_offsets = [0, 2, 5, 9, 14]
///     %sharded2 = shard.shard %arg0 to %sharding4 : tensor<4x14xf32>
///     ```
class ShardingOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Shift over a device grid.
/// Within each device group defined by `grid_axes`, shifts input tensors along the
///     device grid's axis `shift_axis` by the specified offset. The `shift_axis` must
///     be one of the `grid_axes`. If the `rotate` attribute is set, the shift is circular.
///     That is, the offset wraps around according to the group size along `shift_axis`.
///     Otherwise, the results on devices without a corresponding source are undefined.
/// 
///     Example:
///     ```
///     shard.grid @grid0(shape = 2x4)
///     %1 = shard.shift on @grid0 grid_axes = [1]
///       shift_axis = 1 offset = 2 rotate
///       : tensor<2xi8> -> tensor<2xi8>
///     ```
/// 
///     Input:
///     ```
///     grid axis 1
///     ----------->
/// 
///     +----+----+----+----+
///     |  1 |  2 |  3 |  4 |
///     +----+----+----+----+
///     |  5 |  6 |  7 |  8 |
///     +----+----+----+----+
///     ```
/// 
///     Result:
///     ```
///     +----+----+----+----+
///     |  3 |  4 |  1 |  2 |
///     +----+----+----+----+
///     |  7 |  8 |  5 |  6 |
///     +----+----+----+----+
///     ```
class ShiftOp;

} // namespace mlir::shard
namespace mlir::shard {

/// Update halo data.
/// This operation updates halo regions of shards, e.g. if their sharding
///     specified halos and the actual tensor/memref data might have changed
///     on the remote devices. Changes might be caused by mutating operations
///     and/or if the new halo regions are larger than the existing ones.
/// 
///     Destination is supposed to be initialized with the local data (not halos).
/// 
///     Assumes all devices hold tensors with same-sized halo data as specified
///     by `source_halo_sizes/static_source_halo_sizes` and
///     `destination_halo_sizes/static_destination_halo_sizes` in source shard
///     and destination/result shard.
/// 
///     `split_axes` specifies for each tensor axis along which grid axes its halo
///     data is updated.
class UpdateHaloOp;

} // namespace mlir::shard
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::AllGatherOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllGatherOpGenericAdaptorBase {
public:
  struct Properties {
    using gather_axisTy = ::mlir::IntegerAttr;
    gather_axisTy gather_axis;

    auto getGatherAxis() const {
      auto &propStorage = this->gather_axis;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setGatherAxis(const ::mlir::IntegerAttr &propValue) {
      this->gather_axis = propValue;
    }
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.gather_axis == this->gather_axis &&
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
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
  AllGatherOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.all_gather", odsAttrs.getContext());
  }

  AllGatherOpGenericAdaptorBase(AllGatherOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getGatherAxisAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().gather_axis);
    return attr;
  }

  ::llvm::APInt getGatherAxis();
};

} // namespace detail
template <typename RangeT>
class AllGatherOpGenericAdaptor : public detail::AllGatherOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllGatherOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  AllGatherOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllGatherOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllGatherOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllGatherOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AllGatherOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllGatherOpGenericAdaptor(RangeT values, const AllGatherOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllGatherOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllGatherOp>>>
  AllGatherOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllGatherOpAdaptor : public AllGatherOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllGatherOpGenericAdaptor::AllGatherOpGenericAdaptor;
  AllGatherOpAdaptor(AllGatherOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllGatherOp : public ::mlir::Op<AllGatherOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultElementType, ::mlir::OpTrait::SameOperandsAndResultRank, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllGatherOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllGatherOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<AllGatherOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<AllGatherOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<AllGatherOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("gather_axis"), ::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGatherAxisAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGatherAxisAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.all_gather");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getGatherAxisAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().gather_axis);
  }

  ::llvm::APInt getGatherAxis();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setGatherAxisAttr(::mlir::IntegerAttr attr) {
    getProperties().gather_axis = attr;
  }

  void setGatherAxis(::llvm::APInt attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis);
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis);
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis);
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis);
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis);
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis);
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis);
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis);
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllGatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllGatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::AllGatherOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::AllReduceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllReduceOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    using reductionTy = ::mlir::shard::ReductionKindAttr;
    reductionTy reduction;

    auto getReduction() const {
      auto &propStorage = this->reduction;
      return ::llvm::dyn_cast_or_null<::mlir::shard::ReductionKindAttr>(propStorage);
    }
    void setReduction(const ::mlir::shard::ReductionKindAttr &propValue) {
      this->reduction = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
        rhs.reduction == this->reduction &&
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
      odsOpName.emplace("shard.all_reduce", odsAttrs.getContext());
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

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::shard::ReductionKindAttr getReductionAttr();
  ::mlir::shard::ReductionKind getReduction();
};

} // namespace detail
template <typename RangeT>
class AllReduceOpGenericAdaptor : public detail::AllReduceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllReduceOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
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

  ValueT getInput() {
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
class AllReduceOp : public ::mlir::Op<AllReduceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultShape, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllReduceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllReduceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<AllReduceOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<AllReduceOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<AllReduceOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes"), ::llvm::StringRef("reduction")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getReductionAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getReductionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.all_reduce");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::shard::ReductionKindAttr getReductionAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::shard::ReductionKindAttr>(getProperties().reduction);
  }

  ::mlir::shard::ReductionKind getReduction();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setReductionAttr(::mlir::shard::ReductionKindAttr attr) {
    getProperties().reduction = attr;
  }

  void setReduction(::mlir::shard::ReductionKind attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StringRef grid, ArrayRef<GridAxis> gridAxes, ReductionKind reduction);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringRef grid, ArrayRef<GridAxis> gridAxes, ReductionKind reduction);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringRef grid, ArrayRef<GridAxis> gridAxes, ReductionKind reduction);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction = nullptr);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction = nullptr);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction = nullptr);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction = nullptr);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction = ::mlir::shard::ReductionKind::Sum);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction = ::mlir::shard::ReductionKind::Sum);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction = ::mlir::shard::ReductionKind::Sum);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction = ::mlir::shard::ReductionKind::Sum);
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction = ::mlir::shard::ReductionKind::Sum);
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction = ::mlir::shard::ReductionKind::Sum);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::AllReduceOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::AllSliceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllSliceOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    using slice_axisTy = ::mlir::IntegerAttr;
    slice_axisTy slice_axis;

    auto getSliceAxis() const {
      auto &propStorage = this->slice_axis;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setSliceAxis(const ::mlir::IntegerAttr &propValue) {
      this->slice_axis = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
        rhs.slice_axis == this->slice_axis &&
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
  AllSliceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.all_slice", odsAttrs.getContext());
  }

  AllSliceOpGenericAdaptorBase(AllSliceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getSliceAxisAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().slice_axis);
    return attr;
  }

  ::llvm::APInt getSliceAxis();
};

} // namespace detail
template <typename RangeT>
class AllSliceOpGenericAdaptor : public detail::AllSliceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllSliceOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  AllSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllSliceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AllSliceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllSliceOpGenericAdaptor(RangeT values, const AllSliceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllSliceOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllSliceOp>>>
  AllSliceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllSliceOpAdaptor : public AllSliceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllSliceOpGenericAdaptor::AllSliceOpGenericAdaptor;
  AllSliceOpAdaptor(AllSliceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllSliceOp : public ::mlir::Op<AllSliceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultElementType, ::mlir::OpTrait::SameOperandsAndResultRank, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllSliceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllSliceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<AllSliceOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<AllSliceOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<AllSliceOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes"), ::llvm::StringRef("slice_axis")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSliceAxisAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSliceAxisAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.all_slice");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getSliceAxisAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().slice_axis);
  }

  ::llvm::APInt getSliceAxis();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setSliceAxisAttr(::mlir::IntegerAttr attr) {
    getProperties().slice_axis = attr;
  }

  void setSliceAxis(::llvm::APInt attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, GridOp grid, ArrayRef<GridAxis> gridAxes, int64_t sliceAxis);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, GridOp grid, ArrayRef<GridAxis> gridAxes, int64_t sliceAxis);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, GridOp grid, ArrayRef<GridAxis> gridAxes, int64_t sliceAxis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type result_type, Value input, StringRef grid, ArrayRef<GridAxis> gridAxes, int64_t sliceAxis);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type result_type, Value input, StringRef grid, ArrayRef<GridAxis> gridAxes, int64_t sliceAxis);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, Type result_type, Value input, StringRef grid, ArrayRef<GridAxis> gridAxes, int64_t sliceAxis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr slice_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis);
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis);
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt slice_axis);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::AllSliceOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::AllToAllOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllToAllOpGenericAdaptorBase {
public:
  struct Properties {
    using concat_axisTy = ::mlir::IntegerAttr;
    concat_axisTy concat_axis;

    auto getConcatAxis() const {
      auto &propStorage = this->concat_axis;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setConcatAxis(const ::mlir::IntegerAttr &propValue) {
      this->concat_axis = propValue;
    }
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    using split_axisTy = ::mlir::IntegerAttr;
    split_axisTy split_axis;

    auto getSplitAxis() const {
      auto &propStorage = this->split_axis;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setSplitAxis(const ::mlir::IntegerAttr &propValue) {
      this->split_axis = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.concat_axis == this->concat_axis &&
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
        rhs.split_axis == this->split_axis &&
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
  AllToAllOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.all_to_all", odsAttrs.getContext());
  }

  AllToAllOpGenericAdaptorBase(AllToAllOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getSplitAxisAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().split_axis);
    return attr;
  }

  ::llvm::APInt getSplitAxis();
  ::mlir::IntegerAttr getConcatAxisAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().concat_axis);
    return attr;
  }

  ::llvm::APInt getConcatAxis();
};

} // namespace detail
template <typename RangeT>
class AllToAllOpGenericAdaptor : public detail::AllToAllOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllToAllOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  AllToAllOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllToAllOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllToAllOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllToAllOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AllToAllOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllToAllOpGenericAdaptor(RangeT values, const AllToAllOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllToAllOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllToAllOp>>>
  AllToAllOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllToAllOpAdaptor : public AllToAllOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllToAllOpGenericAdaptor::AllToAllOpGenericAdaptor;
  AllToAllOpAdaptor(AllToAllOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllToAllOp : public ::mlir::Op<AllToAllOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultElementType, ::mlir::OpTrait::SameOperandsAndResultRank, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllToAllOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllToAllOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<AllToAllOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<AllToAllOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<AllToAllOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("concat_axis"), ::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes"), ::llvm::StringRef("split_axis")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getConcatAxisAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getConcatAxisAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getSplitAxisAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSplitAxisAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.all_to_all");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getSplitAxisAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().split_axis);
  }

  ::llvm::APInt getSplitAxis();
  ::mlir::IntegerAttr getConcatAxisAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().concat_axis);
  }

  ::llvm::APInt getConcatAxis();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setSplitAxisAttr(::mlir::IntegerAttr attr) {
    getProperties().split_axis = attr;
  }

  void setSplitAxis(::llvm::APInt attrValue);
  void setConcatAxisAttr(::mlir::IntegerAttr attr) {
    getProperties().concat_axis = attr;
  }

  void setConcatAxis(::llvm::APInt attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis);
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis);
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis);
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis);
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr split_axis, ::mlir::IntegerAttr concat_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis);
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis);
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis);
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis);
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt split_axis, ::llvm::APInt concat_axis);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllToAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllToAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::AllToAllOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::BroadcastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BroadcastOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    using rootTy = ::mlir::DenseI64ArrayAttr;
    rootTy root;

    auto getRoot() const {
      auto &propStorage = this->root;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setRoot(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->root = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
        rhs.root == this->root &&
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
  BroadcastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.broadcast", odsAttrs.getContext());
  }

  BroadcastOpGenericAdaptorBase(BroadcastOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::DenseI64ArrayAttr getRootAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().root);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getRoot();
};

} // namespace detail
template <typename RangeT>
class BroadcastOpGenericAdaptor : public detail::BroadcastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BroadcastOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_root_dynamic = 1;
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

  ValueT getInput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getRootDynamic() {
    return getODSOperands(1);
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
class BroadcastOp : public ::mlir::Op<BroadcastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BroadcastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BroadcastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_root_dynamic = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<BroadcastOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<BroadcastOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<BroadcastOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes"), ::llvm::StringRef("root")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getRootAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getRootAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.broadcast");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getRootDynamic() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getRootDynamicMutable();
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::DenseI64ArrayAttr getRootAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().root);
  }

  ::llvm::ArrayRef<int64_t> getRoot();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setRootAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().root = attr;
  }

  void setRoot(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static BroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static BroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static BroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static BroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static BroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static BroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static BroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static BroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BroadcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BroadcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::BroadcastOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::GatherOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GatherOpGenericAdaptorBase {
public:
  struct Properties {
    using gather_axisTy = ::mlir::IntegerAttr;
    gather_axisTy gather_axis;

    auto getGatherAxis() const {
      auto &propStorage = this->gather_axis;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setGatherAxis(const ::mlir::IntegerAttr &propValue) {
      this->gather_axis = propValue;
    }
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    using rootTy = ::mlir::DenseI64ArrayAttr;
    rootTy root;

    auto getRoot() const {
      auto &propStorage = this->root;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setRoot(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->root = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.gather_axis == this->gather_axis &&
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
        rhs.root == this->root &&
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
      odsOpName.emplace("shard.gather", odsAttrs.getContext());
  }

  GatherOpGenericAdaptorBase(GatherOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getGatherAxisAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().gather_axis);
    return attr;
  }

  ::llvm::APInt getGatherAxis();
  ::mlir::DenseI64ArrayAttr getRootAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().root);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getRoot();
};

} // namespace detail
template <typename RangeT>
class GatherOpGenericAdaptor : public detail::GatherOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GatherOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_root_dynamic = 1;
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

  ValueT getInput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getRootDynamic() {
    return getODSOperands(1);
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
class GatherOp : public ::mlir::Op<GatherOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GatherOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GatherOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_root_dynamic = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<GatherOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GatherOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GatherOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("gather_axis"), ::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes"), ::llvm::StringRef("root")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGatherAxisAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGatherAxisAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getRootAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getRootAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.gather");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getRootDynamic() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getRootDynamicMutable();
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getGatherAxisAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().gather_axis);
  }

  ::llvm::APInt getGatherAxis();
  ::mlir::DenseI64ArrayAttr getRootAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().root);
  }

  ::llvm::ArrayRef<int64_t> getRoot();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setGatherAxisAttr(::mlir::IntegerAttr attr) {
    getProperties().gather_axis = attr;
  }

  void setGatherAxis(::llvm::APInt attrValue);
  void setRootAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().root = attr;
  }

  void setRoot(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr gather_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt gather_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GatherOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GatherOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::GatherOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::GetShardingOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetShardingOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GetShardingOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.get_sharding", odsAttrs.getContext());
  }

  GetShardingOpGenericAdaptorBase(GetShardingOp op);

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
class GetShardingOpGenericAdaptor : public detail::GetShardingOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetShardingOpGenericAdaptorBase;
  static constexpr int odsIndex_source = 0;
public:
  GetShardingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetShardingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GetShardingOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetShardingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetShardingOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetShardingOpGenericAdaptor(RangeT values, const GetShardingOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetShardingOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetShardingOp>>>
  GetShardingOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GetShardingOpAdaptor : public GetShardingOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetShardingOpGenericAdaptor::GetShardingOpGenericAdaptor;
  GetShardingOpAdaptor(GetShardingOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetShardingOp : public ::mlir::Op<GetShardingOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::shard::ShardingType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetShardingOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetShardingOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_source = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.get_sharding");
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

  ::mlir::TypedValue<::mlir::shard::ShardingType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::shard::ShardingType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value source);
  static GetShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value source);
  static GetShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value source);
  static GetShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value source);
  static GetShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static GetShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static GetShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::GetShardingOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::GridOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GridOpGenericAdaptorBase {
public:
  struct Properties {
    using shapeTy = ::mlir::DenseI64ArrayAttr;
    shapeTy shape;

    auto getShape() const {
      auto &propStorage = this->shape;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setShape(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->shape = propValue;
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
        rhs.shape == this->shape &&
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
  GridOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.grid", odsAttrs.getContext());
  }

  GridOpGenericAdaptorBase(GridOp op);

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
  ::mlir::DenseI64ArrayAttr getShapeAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().shape);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getShape();
};

} // namespace detail
template <typename RangeT>
class GridOpGenericAdaptor : public detail::GridOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GridOpGenericAdaptorBase;
public:
  GridOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GridOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GridOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GridOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GridOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GridOpGenericAdaptor(RangeT values, const GridOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GridOp, typename = std::enable_if_t<std::is_same_v<LateInst, GridOp>>>
  GridOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GridOpAdaptor : public GridOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GridOpGenericAdaptor::GridOpGenericAdaptor;
  GridOpAdaptor(GridOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GridOp : public ::mlir::Op<GridOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GridOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GridOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("shape"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getShapeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getShapeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.grid");
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
  ::mlir::DenseI64ArrayAttr getShapeAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().shape);
  }

  ::llvm::ArrayRef<int64_t> getShape();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setShapeAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().shape = attr;
  }

  void setShape(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape);
  static GridOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape);
  static GridOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape);
  static GridOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape);
  static GridOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DenseI64ArrayAttr shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape);
  static GridOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape);
  static GridOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape);
  static GridOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape);
  static GridOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::ArrayRef<int64_t> shape);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GridOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GridOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GridOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GridOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  int64_t getRank() { return getShape().size(); }
};

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::GridOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::GridShapeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GridShapeOpGenericAdaptorBase {
public:
  struct Properties {
    using axesTy = ::mlir::DenseI16ArrayAttr;
    axesTy axes;

    auto getAxes() const {
      auto &propStorage = this->axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->axes = propValue;
    }
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.axes == this->axes &&
        rhs.grid == this->grid &&
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
  GridShapeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.grid_shape", odsAttrs.getContext());
  }

  GridShapeOpGenericAdaptorBase(GridShapeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getAxesAttr();
  ::llvm::ArrayRef<int16_t> getAxes();
};

} // namespace detail
template <typename RangeT>
class GridShapeOpGenericAdaptor : public detail::GridShapeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GridShapeOpGenericAdaptorBase;
public:
  GridShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GridShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : GridShapeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GridShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GridShapeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GridShapeOpGenericAdaptor(RangeT values, const GridShapeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GridShapeOp, typename = std::enable_if_t<std::is_same_v<LateInst, GridShapeOp>>>
  GridShapeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GridShapeOpAdaptor : public GridShapeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GridShapeOpGenericAdaptor::GridShapeOpGenericAdaptor;
  GridShapeOpAdaptor(GridShapeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GridShapeOp : public ::mlir::Op<GridShapeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GridShapeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GridShapeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<GridShapeOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GridShapeOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GridShapeOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("axes"), ::llvm::StringRef("grid")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAxesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.grid_shape");
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

  ::mlir::Operation::result_range getResult() {
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().axes);
  }

  ::llvm::ArrayRef<int16_t> getAxes();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().axes = attr;
  }

  void setAxes(::llvm::ArrayRef<int16_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::shard::GridOp grid);
  static GridShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::shard::GridOp grid);
  static GridShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::shard::GridOp grid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::shard::GridOp grid, ArrayRef<GridAxis> axes);
  static GridShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::shard::GridOp grid, ArrayRef<GridAxis> axes);
  static GridShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::shard::GridOp grid, ArrayRef<GridAxis> axes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef grid, ArrayRef<GridAxis> axes);
  static GridShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef grid, ArrayRef<GridAxis> axes);
  static GridShapeOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef grid, ArrayRef<GridAxis> axes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes = nullptr);
  static GridShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes = nullptr);
  static GridShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes = {});
  static GridShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes = {});
  static GridShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GridShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GridShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GridShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GridShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::GridShapeOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::NeighborsLinearIndicesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NeighborsLinearIndicesOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using split_axesTy = ::mlir::DenseI16ArrayAttr;
    split_axesTy split_axes;

    auto getSplitAxes() const {
      auto &propStorage = this->split_axes;
      return ::llvm::cast<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setSplitAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->split_axes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
        rhs.split_axes == this->split_axes &&
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
  NeighborsLinearIndicesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.neighbors_linear_indices", odsAttrs.getContext());
  }

  NeighborsLinearIndicesOpGenericAdaptorBase(NeighborsLinearIndicesOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getSplitAxesAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI16ArrayAttr>(getProperties().split_axes);
    return attr;
  }

  ::llvm::ArrayRef<int16_t> getSplitAxes();
};

} // namespace detail
template <typename RangeT>
class NeighborsLinearIndicesOpGenericAdaptor : public detail::NeighborsLinearIndicesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NeighborsLinearIndicesOpGenericAdaptorBase;
  static constexpr int odsIndex_device = 0;
public:
  NeighborsLinearIndicesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NeighborsLinearIndicesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : NeighborsLinearIndicesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NeighborsLinearIndicesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NeighborsLinearIndicesOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NeighborsLinearIndicesOpGenericAdaptor(RangeT values, const NeighborsLinearIndicesOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NeighborsLinearIndicesOp, typename = std::enable_if_t<std::is_same_v<LateInst, NeighborsLinearIndicesOp>>>
  NeighborsLinearIndicesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDevice() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class NeighborsLinearIndicesOpAdaptor : public NeighborsLinearIndicesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NeighborsLinearIndicesOpGenericAdaptor::NeighborsLinearIndicesOpGenericAdaptor;
  NeighborsLinearIndicesOpAdaptor(NeighborsLinearIndicesOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NeighborsLinearIndicesOp : public ::mlir::Op<NeighborsLinearIndicesOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NeighborsLinearIndicesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NeighborsLinearIndicesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_device = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<NeighborsLinearIndicesOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<NeighborsLinearIndicesOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<NeighborsLinearIndicesOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("split_axes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSplitAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSplitAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.neighbors_linear_indices");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDevice() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getDeviceMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IndexType> getNeighborDown() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getNeighborUp() {
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getSplitAxesAttr() {
    return ::llvm::cast<::mlir::DenseI16ArrayAttr>(getProperties().split_axes);
  }

  ::llvm::ArrayRef<int16_t> getSplitAxes();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setSplitAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().split_axes = attr;
  }

  void setSplitAxes(::llvm::ArrayRef<int16_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes);
  static NeighborsLinearIndicesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes);
  static NeighborsLinearIndicesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes);
  static NeighborsLinearIndicesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes);
  static NeighborsLinearIndicesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes);
  static NeighborsLinearIndicesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes);
  static NeighborsLinearIndicesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::ValueRange device, ::mlir::DenseI16ArrayAttr split_axes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes);
  static NeighborsLinearIndicesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes);
  static NeighborsLinearIndicesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type neighbor_down, ::mlir::Type neighbor_up, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes);
  static NeighborsLinearIndicesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes);
  static NeighborsLinearIndicesOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes);
  static NeighborsLinearIndicesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes);
  static NeighborsLinearIndicesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::ValueRange device, ::llvm::ArrayRef<int16_t> split_axes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NeighborsLinearIndicesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NeighborsLinearIndicesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NeighborsLinearIndicesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NeighborsLinearIndicesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NeighborsLinearIndicesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NeighborsLinearIndicesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NeighborsLinearIndicesOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NeighborsLinearIndicesOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::NeighborsLinearIndicesOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ProcessLinearIndexOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ProcessLinearIndexOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
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
  ProcessLinearIndexOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.process_linear_index", odsAttrs.getContext());
  }

  ProcessLinearIndexOpGenericAdaptorBase(ProcessLinearIndexOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
};

} // namespace detail
template <typename RangeT>
class ProcessLinearIndexOpGenericAdaptor : public detail::ProcessLinearIndexOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ProcessLinearIndexOpGenericAdaptorBase;
public:
  ProcessLinearIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ProcessLinearIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ProcessLinearIndexOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ProcessLinearIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ProcessLinearIndexOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ProcessLinearIndexOpGenericAdaptor(RangeT values, const ProcessLinearIndexOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ProcessLinearIndexOp, typename = std::enable_if_t<std::is_same_v<LateInst, ProcessLinearIndexOp>>>
  ProcessLinearIndexOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ProcessLinearIndexOpAdaptor : public ProcessLinearIndexOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ProcessLinearIndexOpGenericAdaptor::ProcessLinearIndexOpGenericAdaptor;
  ProcessLinearIndexOpAdaptor(ProcessLinearIndexOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ProcessLinearIndexOp : public ::mlir::Op<ProcessLinearIndexOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ProcessLinearIndexOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ProcessLinearIndexOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ProcessLinearIndexOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ProcessLinearIndexOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ProcessLinearIndexOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.process_linear_index");
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::shard::GridOp grid);
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::shard::GridOp grid);
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::shard::GridOp grid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid);
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid);
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr grid);
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr grid);
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr grid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid);
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid);
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid);
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid);
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef grid);
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef grid);
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef grid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid);
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid);
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ProcessLinearIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ProcessLinearIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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
};

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ProcessLinearIndexOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ProcessMultiIndexOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ProcessMultiIndexOpGenericAdaptorBase {
public:
  struct Properties {
    using axesTy = ::mlir::DenseI16ArrayAttr;
    axesTy axes;

    auto getAxes() const {
      auto &propStorage = this->axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->axes = propValue;
    }
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.axes == this->axes &&
        rhs.grid == this->grid &&
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
  ProcessMultiIndexOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.process_multi_index", odsAttrs.getContext());
  }

  ProcessMultiIndexOpGenericAdaptorBase(ProcessMultiIndexOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getAxesAttr();
  ::llvm::ArrayRef<int16_t> getAxes();
};

} // namespace detail
template <typename RangeT>
class ProcessMultiIndexOpGenericAdaptor : public detail::ProcessMultiIndexOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ProcessMultiIndexOpGenericAdaptorBase;
public:
  ProcessMultiIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ProcessMultiIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ProcessMultiIndexOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ProcessMultiIndexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ProcessMultiIndexOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ProcessMultiIndexOpGenericAdaptor(RangeT values, const ProcessMultiIndexOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ProcessMultiIndexOp, typename = std::enable_if_t<std::is_same_v<LateInst, ProcessMultiIndexOp>>>
  ProcessMultiIndexOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ProcessMultiIndexOpAdaptor : public ProcessMultiIndexOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ProcessMultiIndexOpGenericAdaptor::ProcessMultiIndexOpGenericAdaptor;
  ProcessMultiIndexOpAdaptor(ProcessMultiIndexOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ProcessMultiIndexOp : public ::mlir::Op<ProcessMultiIndexOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ProcessMultiIndexOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ProcessMultiIndexOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ProcessMultiIndexOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ProcessMultiIndexOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ProcessMultiIndexOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("axes"), ::llvm::StringRef("grid")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAxesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.process_multi_index");
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

  ::mlir::Operation::result_range getResult() {
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().axes);
  }

  ::llvm::ArrayRef<int16_t> getAxes();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().axes = attr;
  }

  void setAxes(::llvm::ArrayRef<int16_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::shard::GridOp grid);
  static ProcessMultiIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::shard::GridOp grid);
  static ProcessMultiIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::shard::GridOp grid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef grid, ArrayRef<GridAxis> axes);
  static ProcessMultiIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef grid, ArrayRef<GridAxis> axes);
  static ProcessMultiIndexOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef grid, ArrayRef<GridAxis> axes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes = nullptr);
  static ProcessMultiIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes = nullptr);
  static ProcessMultiIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr axes = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes = {});
  static ProcessMultiIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes = {});
  static ProcessMultiIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> axes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ProcessMultiIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ProcessMultiIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ProcessMultiIndexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ProcessMultiIndexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ProcessMultiIndexOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::RecvOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RecvOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    using sourceTy = ::mlir::DenseI64ArrayAttr;
    sourceTy source;

    auto getSource() const {
      auto &propStorage = this->source;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setSource(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->source = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
        rhs.source == this->source &&
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
  RecvOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.recv", odsAttrs.getContext());
  }

  RecvOpGenericAdaptorBase(RecvOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::DenseI64ArrayAttr getSourceAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().source);
    return attr;
  }

  ::std::optional<::llvm::ArrayRef<int64_t>> getSource();
};

} // namespace detail
template <typename RangeT>
class RecvOpGenericAdaptor : public detail::RecvOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RecvOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_source_dynamic = 1;
public:
  RecvOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RecvOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : RecvOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RecvOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RecvOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RecvOpGenericAdaptor(RangeT values, const RecvOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RecvOp, typename = std::enable_if_t<std::is_same_v<LateInst, RecvOp>>>
  RecvOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getSourceDynamic() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RecvOpAdaptor : public RecvOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RecvOpGenericAdaptor::RecvOpGenericAdaptor;
  RecvOpAdaptor(RecvOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RecvOp : public ::mlir::Op<RecvOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RecvOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RecvOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_source_dynamic = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<RecvOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<RecvOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<RecvOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes"), ::llvm::StringRef("source")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSourceAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSourceAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.recv");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getSourceDynamic() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getSourceDynamicMutable();
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::DenseI64ArrayAttr getSourceAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().source);
  }

  ::std::optional<::llvm::ArrayRef<int64_t>> getSource();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setSourceAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().source = attr;
  }

  void setSource(::std::optional<::llvm::ArrayRef<int64_t>> attrValue);
  ::mlir::Attribute removeSourceAttr() {
      auto attr = getProperties().source;
      getProperties().source = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static RecvOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static RecvOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static RecvOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static RecvOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static RecvOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static RecvOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static RecvOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static RecvOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, /*optional*/::mlir::DenseI64ArrayAttr source, ::mlir::ValueRange source_dynamic);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RecvOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RecvOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RecvOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RecvOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::RecvOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ReduceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReduceOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    using reductionTy = ::mlir::shard::ReductionKindAttr;
    reductionTy reduction;

    auto getReduction() const {
      auto &propStorage = this->reduction;
      return ::llvm::dyn_cast_or_null<::mlir::shard::ReductionKindAttr>(propStorage);
    }
    void setReduction(const ::mlir::shard::ReductionKindAttr &propValue) {
      this->reduction = propValue;
    }
    using rootTy = ::mlir::DenseI64ArrayAttr;
    rootTy root;

    auto getRoot() const {
      auto &propStorage = this->root;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setRoot(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->root = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
        rhs.reduction == this->reduction &&
        rhs.root == this->root &&
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
  ReduceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.reduce", odsAttrs.getContext());
  }

  ReduceOpGenericAdaptorBase(ReduceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::shard::ReductionKindAttr getReductionAttr();
  ::mlir::shard::ReductionKind getReduction();
  ::mlir::DenseI64ArrayAttr getRootAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().root);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getRoot();
};

} // namespace detail
template <typename RangeT>
class ReduceOpGenericAdaptor : public detail::ReduceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReduceOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_root_dynamic = 1;
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

  ValueT getInput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getRootDynamic() {
    return getODSOperands(1);
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
class ReduceOp : public ::mlir::Op<ReduceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReduceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReduceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_root_dynamic = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ReduceOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ReduceOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ReduceOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes"), ::llvm::StringRef("reduction"), ::llvm::StringRef("root")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getReductionAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getReductionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getRootAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getRootAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.reduce");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getRootDynamic() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getRootDynamicMutable();
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::shard::ReductionKindAttr getReductionAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::shard::ReductionKindAttr>(getProperties().reduction);
  }

  ::mlir::shard::ReductionKind getReduction();
  ::mlir::DenseI64ArrayAttr getRootAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().root);
  }

  ::llvm::ArrayRef<int64_t> getRoot();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setReductionAttr(::mlir::shard::ReductionKindAttr attr) {
    getProperties().reduction = attr;
  }

  void setReduction(::mlir::shard::ReductionKind attrValue);
  void setRootAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().root = attr;
  }

  void setRoot(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ReduceOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ReduceScatterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReduceScatterOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    using reductionTy = ::mlir::shard::ReductionKindAttr;
    reductionTy reduction;

    auto getReduction() const {
      auto &propStorage = this->reduction;
      return ::llvm::dyn_cast_or_null<::mlir::shard::ReductionKindAttr>(propStorage);
    }
    void setReduction(const ::mlir::shard::ReductionKindAttr &propValue) {
      this->reduction = propValue;
    }
    using scatter_axisTy = ::mlir::IntegerAttr;
    scatter_axisTy scatter_axis;

    auto getScatterAxis() const {
      auto &propStorage = this->scatter_axis;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setScatterAxis(const ::mlir::IntegerAttr &propValue) {
      this->scatter_axis = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
        rhs.reduction == this->reduction &&
        rhs.scatter_axis == this->scatter_axis &&
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
  ReduceScatterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.reduce_scatter", odsAttrs.getContext());
  }

  ReduceScatterOpGenericAdaptorBase(ReduceScatterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::shard::ReductionKindAttr getReductionAttr();
  ::mlir::shard::ReductionKind getReduction();
  ::mlir::IntegerAttr getScatterAxisAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().scatter_axis);
    return attr;
  }

  ::llvm::APInt getScatterAxis();
};

} // namespace detail
template <typename RangeT>
class ReduceScatterOpGenericAdaptor : public detail::ReduceScatterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReduceScatterOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ReduceScatterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReduceScatterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ReduceScatterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReduceScatterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReduceScatterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReduceScatterOpGenericAdaptor(RangeT values, const ReduceScatterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReduceScatterOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReduceScatterOp>>>
  ReduceScatterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReduceScatterOpAdaptor : public ReduceScatterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReduceScatterOpGenericAdaptor::ReduceScatterOpGenericAdaptor;
  ReduceScatterOpAdaptor(ReduceScatterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReduceScatterOp : public ::mlir::Op<ReduceScatterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultRank, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReduceScatterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReduceScatterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ReduceScatterOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ReduceScatterOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ReduceScatterOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes"), ::llvm::StringRef("reduction"), ::llvm::StringRef("scatter_axis")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getReductionAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getReductionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getScatterAxisAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getScatterAxisAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.reduce_scatter");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::shard::ReductionKindAttr getReductionAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::shard::ReductionKindAttr>(getProperties().reduction);
  }

  ::mlir::shard::ReductionKind getReduction();
  ::mlir::IntegerAttr getScatterAxisAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().scatter_axis);
  }

  ::llvm::APInt getScatterAxis();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setReductionAttr(::mlir::shard::ReductionKindAttr attr) {
    getProperties().reduction = attr;
  }

  void setReduction(::mlir::shard::ReductionKind attrValue);
  void setScatterAxisAttr(::mlir::IntegerAttr attr) {
    getProperties().scatter_axis = attr;
  }

  void setScatterAxis(::llvm::APInt attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis);
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis);
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis);
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis);
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKindAttr reduction, ::mlir::IntegerAttr scatter_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis);
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis);
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis);
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis);
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::mlir::shard::ReductionKind reduction, ::llvm::APInt scatter_axis);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReduceScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ReduceScatterOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ScatterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ScatterOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    using rootTy = ::mlir::DenseI64ArrayAttr;
    rootTy root;

    auto getRoot() const {
      auto &propStorage = this->root;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setRoot(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->root = propValue;
    }
    using scatter_axisTy = ::mlir::IntegerAttr;
    scatter_axisTy scatter_axis;

    auto getScatterAxis() const {
      auto &propStorage = this->scatter_axis;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setScatterAxis(const ::mlir::IntegerAttr &propValue) {
      this->scatter_axis = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
        rhs.root == this->root &&
        rhs.scatter_axis == this->scatter_axis &&
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
      odsOpName.emplace("shard.scatter", odsAttrs.getContext());
  }

  ScatterOpGenericAdaptorBase(ScatterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getScatterAxisAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().scatter_axis);
    return attr;
  }

  ::llvm::APInt getScatterAxis();
  ::mlir::DenseI64ArrayAttr getRootAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().root);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getRoot();
};

} // namespace detail
template <typename RangeT>
class ScatterOpGenericAdaptor : public detail::ScatterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ScatterOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_root_dynamic = 1;
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

  ValueT getInput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getRootDynamic() {
    return getODSOperands(1);
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
class ScatterOp : public ::mlir::Op<ScatterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ScatterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ScatterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_root_dynamic = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ScatterOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ScatterOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ScatterOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes"), ::llvm::StringRef("root"), ::llvm::StringRef("scatter_axis")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getRootAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getRootAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getScatterAxisAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getScatterAxisAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.scatter");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getRootDynamic() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getRootDynamicMutable();
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getScatterAxisAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().scatter_axis);
  }

  ::llvm::APInt getScatterAxis();
  ::mlir::DenseI64ArrayAttr getRootAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().root);
  }

  ::llvm::ArrayRef<int64_t> getRoot();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setScatterAxisAttr(::mlir::IntegerAttr attr) {
    getProperties().scatter_axis = attr;
  }

  void setScatterAxis(::llvm::APInt attrValue);
  void setRootAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().root = attr;
  }

  void setRoot(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr scatter_axis, ::mlir::DenseI64ArrayAttr root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt scatter_axis, ::llvm::ArrayRef<int64_t> root, ::mlir::ValueRange root_dynamic);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScatterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScatterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ScatterOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::SendOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SendOpGenericAdaptorBase {
public:
  struct Properties {
    using destinationTy = ::mlir::DenseI64ArrayAttr;
    destinationTy destination;

    auto getDestination() const {
      auto &propStorage = this->destination;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setDestination(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->destination = propValue;
    }
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.destination == this->destination &&
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
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
  SendOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.send", odsAttrs.getContext());
  }

  SendOpGenericAdaptorBase(SendOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::DenseI64ArrayAttr getDestinationAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().destination);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getDestination();
};

} // namespace detail
template <typename RangeT>
class SendOpGenericAdaptor : public detail::SendOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SendOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_destination_dynamic = 1;
public:
  SendOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SendOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SendOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SendOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SendOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SendOpGenericAdaptor(RangeT values, const SendOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SendOp, typename = std::enable_if_t<std::is_same_v<LateInst, SendOp>>>
  SendOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getDestinationDynamic() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SendOpAdaptor : public SendOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SendOpGenericAdaptor::SendOpGenericAdaptor;
  SendOpAdaptor(SendOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SendOp : public ::mlir::Op<SendOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SendOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SendOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_destination_dynamic = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<SendOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SendOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SendOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("destination"), ::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDestinationAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDestinationAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.send");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getDestinationDynamic() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDestinationDynamicMutable();
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::DenseI64ArrayAttr getDestinationAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().destination);
  }

  ::llvm::ArrayRef<int64_t> getDestination();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setDestinationAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().destination = attr;
  }

  void setDestination(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic);
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic);
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic);
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic);
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::DenseI64ArrayAttr destination, ::mlir::ValueRange destination_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic);
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic);
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic);
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic);
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::ArrayRef<int64_t> destination, ::mlir::ValueRange destination_dynamic);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SendOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SendOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::SendOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ShardOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShardOpGenericAdaptorBase {
public:
  struct Properties {
    using annotate_for_usersTy = ::mlir::UnitAttr;
    annotate_for_usersTy annotate_for_users;

    auto getAnnotateForUsers() const {
      auto &propStorage = this->annotate_for_users;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setAnnotateForUsers(const ::mlir::UnitAttr &propValue) {
      this->annotate_for_users = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.annotate_for_users == this->annotate_for_users &&
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
  ShardOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.shard", odsAttrs.getContext());
  }

  ShardOpGenericAdaptorBase(ShardOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getAnnotateForUsersAttr();
  bool getAnnotateForUsers();
};

} // namespace detail
template <typename RangeT>
class ShardOpGenericAdaptor : public detail::ShardOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShardOpGenericAdaptorBase;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_sharding = 1;
public:
  ShardOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShardOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ShardOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShardOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ShardOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShardOpGenericAdaptor(RangeT values, const ShardOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShardOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShardOp>>>
  ShardOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getSharding() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ShardOpAdaptor : public ShardOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShardOpGenericAdaptor::ShardOpGenericAdaptor;
  ShardOpAdaptor(ShardOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShardOp : public ::mlir::Op<ShardOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShardOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShardOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_sharding = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ShardOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ShardOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ShardOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("annotate_for_users")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAnnotateForUsersAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAnnotateForUsersAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.shard");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::RankedTensorType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::RankedTensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::shard::ShardingType> getSharding() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::shard::ShardingType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getShardingMutable() {
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
  ::mlir::UnitAttr getAnnotateForUsersAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().annotate_for_users);
  }

  bool getAnnotateForUsers();
  void setAnnotateForUsersAttr(::mlir::UnitAttr attr) {
    getProperties().annotate_for_users = attr;
  }

  void setAnnotateForUsers(bool attrValue);
  ::mlir::Attribute removeAnnotateForUsersAttr() {
      auto attr = getProperties().annotate_for_users;
      getProperties().annotate_for_users = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users);
  static ShardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users);
  static ShardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users);
  static ShardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users);
  static ShardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users);
  static ShardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users);
  static ShardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/::mlir::UnitAttr annotate_for_users);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users = false);
  static ShardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users = false);
  static ShardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users = false);
  static ShardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users = false);
  static ShardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users = false);
  static ShardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users = false);
  static ShardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, ::mlir::Value sharding, /*optional*/bool annotate_for_users = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
};

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ShardOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ShardShapeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShardShapeOpGenericAdaptorBase {
public:
  struct Properties {
    using deviceTy = ::mlir::DenseI64ArrayAttr;
    deviceTy device;

    auto getDevice() const {
      auto &propStorage = this->device;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setDevice(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->device = propValue;
    }
    using dimsTy = ::mlir::DenseI64ArrayAttr;
    dimsTy dims;

    auto getDims() const {
      auto &propStorage = this->dims;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setDims(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->dims = propValue;
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
        rhs.device == this->device &&
        rhs.dims == this->dims &&
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
  ShardShapeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.shard_shape", odsAttrs.getContext());
  }

  ShardShapeOpGenericAdaptorBase(ShardShapeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getDimsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().dims);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getDims();
  ::mlir::DenseI64ArrayAttr getDeviceAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().device);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getDevice();
};

} // namespace detail
template <typename RangeT>
class ShardShapeOpGenericAdaptor : public detail::ShardShapeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShardShapeOpGenericAdaptorBase;
  static constexpr int odsIndex_dims_dynamic = 0;
  static constexpr int odsIndex_sharding = 1;
  static constexpr int odsIndex_device_dynamic = 2;
public:
  ShardShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShardShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ShardShapeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShardShapeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ShardShapeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShardShapeOpGenericAdaptor(RangeT values, const ShardShapeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShardShapeOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShardShapeOp>>>
  ShardShapeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDimsDynamic() {
    return getODSOperands(0);
  }

  ValueT getSharding() {
    return (*getODSOperands(1).begin());
  }

  RangeT getDeviceDynamic() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ShardShapeOpAdaptor : public ShardShapeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShardShapeOpGenericAdaptor::ShardShapeOpGenericAdaptor;
  ShardShapeOpAdaptor(ShardShapeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShardShapeOp : public ::mlir::Op<ShardShapeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShardShapeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShardShapeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dims_dynamic = 0;
  static constexpr int odsIndex_sharding = 1;
  static constexpr int odsIndex_device_dynamic = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ShardShapeOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ShardShapeOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ShardShapeOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("device"), ::llvm::StringRef("dims"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDeviceAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDeviceAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getDimsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getDimsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.shard_shape");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDimsDynamic() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::shard::ShardingType> getSharding() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::shard::ShardingType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getDeviceDynamic() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getDimsDynamicMutable();
  ::mlir::OpOperand &getShardingMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDeviceDynamicMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResult() {
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
  ::mlir::DenseI64ArrayAttr getDimsAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().dims);
  }

  ::llvm::ArrayRef<int64_t> getDims();
  ::mlir::DenseI64ArrayAttr getDeviceAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().device);
  }

  ::llvm::ArrayRef<int64_t> getDevice();
  void setDimsAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().dims = attr;
  }

  void setDims(::llvm::ArrayRef<int64_t> attrValue);
  void setDeviceAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().device = attr;
  }

  void setDevice(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<int64_t> dims, ArrayRef<Value> dims_dyn, Value sharding, ValueRange device);
  static ShardShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<int64_t> dims, ArrayRef<Value> dims_dyn, Value sharding, ValueRange device);
  static ShardShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<int64_t> dims, ArrayRef<Value> dims_dyn, Value sharding, ValueRange device);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::DenseI64ArrayAttr dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::mlir::DenseI64ArrayAttr device, ::mlir::ValueRange device_dynamic);
  static ShardShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::DenseI64ArrayAttr dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::mlir::DenseI64ArrayAttr device, ::mlir::ValueRange device_dynamic);
  static ShardShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::DenseI64ArrayAttr dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::mlir::DenseI64ArrayAttr device, ::mlir::ValueRange device_dynamic);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::llvm::ArrayRef<int64_t> dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::llvm::ArrayRef<int64_t> device, ::mlir::ValueRange device_dynamic);
  static ShardShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::llvm::ArrayRef<int64_t> dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::llvm::ArrayRef<int64_t> device, ::mlir::ValueRange device_dynamic);
  static ShardShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::llvm::ArrayRef<int64_t> dims, ::mlir::ValueRange dims_dynamic, ::mlir::Value sharding, ::llvm::ArrayRef<int64_t> device, ::mlir::ValueRange device_dynamic);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardShapeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardShapeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ShardShapeOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ShardingOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShardingOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using split_axesTy = ::mlir::shard::GridAxesArrayAttr;
    split_axesTy split_axes;

    auto getSplitAxes() const {
      auto &propStorage = this->split_axes;
      return ::llvm::cast<::mlir::shard::GridAxesArrayAttr>(propStorage);
    }
    void setSplitAxes(const ::mlir::shard::GridAxesArrayAttr &propValue) {
      this->split_axes = propValue;
    }
    using static_halo_sizesTy = ::mlir::DenseI64ArrayAttr;
    static_halo_sizesTy static_halo_sizes;

    auto getStaticHaloSizes() const {
      auto &propStorage = this->static_halo_sizes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticHaloSizes(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_halo_sizes = propValue;
    }
    using static_sharded_dims_offsetsTy = ::mlir::DenseI64ArrayAttr;
    static_sharded_dims_offsetsTy static_sharded_dims_offsets;

    auto getStaticShardedDimsOffsets() const {
      auto &propStorage = this->static_sharded_dims_offsets;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticShardedDimsOffsets(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_sharded_dims_offsets = propValue;
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
        rhs.grid == this->grid &&
        rhs.split_axes == this->split_axes &&
        rhs.static_halo_sizes == this->static_halo_sizes &&
        rhs.static_sharded_dims_offsets == this->static_sharded_dims_offsets &&
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
  ShardingOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.sharding", odsAttrs.getContext());
  }

  ShardingOpGenericAdaptorBase(ShardingOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::shard::GridAxesArrayAttr getSplitAxesAttr() {
    auto attr = ::llvm::cast<::mlir::shard::GridAxesArrayAttr>(getProperties().split_axes);
    return attr;
  }

  ::mlir::shard::GridAxesArrayAttr getSplitAxes();
  ::mlir::DenseI64ArrayAttr getStaticShardedDimsOffsetsAttr();
  ::llvm::ArrayRef<int64_t> getStaticShardedDimsOffsets();
  ::mlir::DenseI64ArrayAttr getStaticHaloSizesAttr();
  ::llvm::ArrayRef<int64_t> getStaticHaloSizes();
};

} // namespace detail
template <typename RangeT>
class ShardingOpGenericAdaptor : public detail::ShardingOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShardingOpGenericAdaptorBase;
  static constexpr int odsIndex_dynamic_sharded_dims_offsets = 0;
  static constexpr int odsIndex_dynamic_halo_sizes = 1;
public:
  ShardingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShardingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ShardingOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShardingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ShardingOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShardingOpGenericAdaptor(RangeT values, const ShardingOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShardingOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShardingOp>>>
  ShardingOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDynamicShardedDimsOffsets() {
    return getODSOperands(0);
  }

  RangeT getDynamicHaloSizes() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ShardingOpAdaptor : public ShardingOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShardingOpGenericAdaptor::ShardingOpGenericAdaptor;
  ShardingOpAdaptor(ShardingOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShardingOp : public ::mlir::Op<ShardingOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::shard::ShardingType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShardingOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShardingOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dynamic_sharded_dims_offsets = 0;
  static constexpr int odsIndex_dynamic_halo_sizes = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ShardingOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ShardingOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ShardingOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("split_axes"), ::llvm::StringRef("static_halo_sizes"), ::llvm::StringRef("static_sharded_dims_offsets"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSplitAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSplitAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStaticHaloSizesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStaticHaloSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getStaticShardedDimsOffsetsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getStaticShardedDimsOffsetsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.sharding");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDynamicShardedDimsOffsets() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getDynamicHaloSizes() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getDynamicShardedDimsOffsetsMutable();
  ::mlir::MutableOperandRange getDynamicHaloSizesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::shard::ShardingType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::shard::ShardingType>>(*getODSResults(0).begin());
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::shard::GridAxesArrayAttr getSplitAxesAttr() {
    return ::llvm::cast<::mlir::shard::GridAxesArrayAttr>(getProperties().split_axes);
  }

  ::mlir::shard::GridAxesArrayAttr getSplitAxes();
  ::mlir::DenseI64ArrayAttr getStaticShardedDimsOffsetsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().static_sharded_dims_offsets);
  }

  ::llvm::ArrayRef<int64_t> getStaticShardedDimsOffsets();
  ::mlir::DenseI64ArrayAttr getStaticHaloSizesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().static_halo_sizes);
  }

  ::llvm::ArrayRef<int64_t> getStaticHaloSizes();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setSplitAxesAttr(::mlir::shard::GridAxesArrayAttr attr) {
    getProperties().split_axes = attr;
  }

  void setStaticShardedDimsOffsetsAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_sharded_dims_offsets = attr;
  }

  void setStaticShardedDimsOffsets(::llvm::ArrayRef<int64_t> attrValue);
  void setStaticHaloSizesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_halo_sizes = attr;
  }

  void setStaticHaloSizes(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, FlatSymbolRefAttr grid, ArrayRef<GridAxesAttr> split_axes, ArrayRef<int64_t> static_halo_sizes = {}, ArrayRef<int64_t> static_sharded_dims_offsets = {});
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, FlatSymbolRefAttr grid, ArrayRef<GridAxesAttr> split_axes, ArrayRef<int64_t> static_halo_sizes = {}, ArrayRef<int64_t> static_sharded_dims_offsets = {});
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, FlatSymbolRefAttr grid, ArrayRef<GridAxesAttr> split_axes, ArrayRef<int64_t> static_halo_sizes = {}, ArrayRef<int64_t> static_sharded_dims_offsets = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, FlatSymbolRefAttr grid, ArrayRef<GridAxesAttr> split_axes, ::mlir::ArrayRef<::mlir::OpFoldResult> halo_sizes, ::mlir::ArrayRef<::mlir::OpFoldResult> sharded_dims_offsets);
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, FlatSymbolRefAttr grid, ArrayRef<GridAxesAttr> split_axes, ::mlir::ArrayRef<::mlir::OpFoldResult> halo_sizes, ::mlir::ArrayRef<::mlir::OpFoldResult> sharded_dims_offsets);
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, FlatSymbolRefAttr grid, ArrayRef<GridAxesAttr> split_axes, ::mlir::ArrayRef<::mlir::OpFoldResult> halo_sizes, ::mlir::ArrayRef<::mlir::OpFoldResult> sharded_dims_offsets);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, llvm::StringRef grid, ArrayRef<GridAxesAttr> split_axes, ArrayRef<int64_t> static_halo_sizes = {}, ArrayRef<int64_t> static_sharded_dims_offsets = {});
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, llvm::StringRef grid, ArrayRef<GridAxesAttr> split_axes, ArrayRef<int64_t> static_halo_sizes = {}, ArrayRef<int64_t> static_sharded_dims_offsets = {});
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, llvm::StringRef grid, ArrayRef<GridAxesAttr> split_axes, ArrayRef<int64_t> static_halo_sizes = {}, ArrayRef<int64_t> static_sharded_dims_offsets = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::shard::Sharding from);
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::shard::Sharding from);
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::shard::Sharding from);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::DenseI64ArrayAttr static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::mlir::DenseI64ArrayAttr static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::llvm::ArrayRef<int64_t> static_sharded_dims_offsets, ::mlir::ValueRange dynamic_sharded_dims_offsets, ::llvm::ArrayRef<int64_t> static_halo_sizes, ::mlir::ValueRange dynamic_halo_sizes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShardingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ShardingOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::ShiftOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShiftOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using grid_axesTy = ::mlir::DenseI16ArrayAttr;
    grid_axesTy grid_axes;

    auto getGridAxes() const {
      auto &propStorage = this->grid_axes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(propStorage);
    }
    void setGridAxes(const ::mlir::DenseI16ArrayAttr &propValue) {
      this->grid_axes = propValue;
    }
    using offsetTy = ::mlir::IntegerAttr;
    offsetTy offset;

    auto getOffset() const {
      auto &propStorage = this->offset;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setOffset(const ::mlir::IntegerAttr &propValue) {
      this->offset = propValue;
    }
    using rotateTy = ::mlir::UnitAttr;
    rotateTy rotate;

    auto getRotate() const {
      auto &propStorage = this->rotate;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setRotate(const ::mlir::UnitAttr &propValue) {
      this->rotate = propValue;
    }
    using shift_axisTy = ::mlir::IntegerAttr;
    shift_axisTy shift_axis;

    auto getShiftAxis() const {
      auto &propStorage = this->shift_axis;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setShiftAxis(const ::mlir::IntegerAttr &propValue) {
      this->shift_axis = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
        rhs.grid_axes == this->grid_axes &&
        rhs.offset == this->offset &&
        rhs.rotate == this->rotate &&
        rhs.shift_axis == this->shift_axis &&
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
  ShiftOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.shift", odsAttrs.getContext());
  }

  ShiftOpGenericAdaptorBase(ShiftOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr();
  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getShiftAxisAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().shift_axis);
    return attr;
  }

  ::llvm::APInt getShiftAxis();
  ::mlir::IntegerAttr getOffsetAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().offset);
    return attr;
  }

  uint64_t getOffset();
  ::mlir::UnitAttr getRotateAttr();
  bool getRotate();
};

} // namespace detail
template <typename RangeT>
class ShiftOpGenericAdaptor : public detail::ShiftOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShiftOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ShiftOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShiftOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ShiftOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShiftOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ShiftOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShiftOpGenericAdaptor(RangeT values, const ShiftOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShiftOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShiftOp>>>
  ShiftOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ShiftOpAdaptor : public ShiftOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShiftOpGenericAdaptor::ShiftOpGenericAdaptor;
  ShiftOpAdaptor(ShiftOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShiftOp : public ::mlir::Op<ShiftOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::RankedTensorType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultElementType, ::mlir::OpTrait::SameOperandsAndResultShape, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShiftOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShiftOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ShiftOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ShiftOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ShiftOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("grid_axes"), ::llvm::StringRef("offset"), ::llvm::StringRef("rotate"), ::llvm::StringRef("shift_axis")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGridAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGridAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOffsetAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getOffsetAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getRotateAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getRotateAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getShiftAxisAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getShiftAxisAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.shift");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TensorType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TensorType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::DenseI16ArrayAttr getGridAxesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI16ArrayAttr>(getProperties().grid_axes);
  }

  ::llvm::ArrayRef<int16_t> getGridAxes();
  ::mlir::IntegerAttr getShiftAxisAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().shift_axis);
  }

  ::llvm::APInt getShiftAxis();
  ::mlir::IntegerAttr getOffsetAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().offset);
  }

  uint64_t getOffset();
  ::mlir::UnitAttr getRotateAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().rotate);
  }

  bool getRotate();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setGridAxesAttr(::mlir::DenseI16ArrayAttr attr) {
    getProperties().grid_axes = attr;
  }

  void setGridAxes(::llvm::ArrayRef<int16_t> attrValue);
  void setShiftAxisAttr(::mlir::IntegerAttr attr) {
    getProperties().shift_axis = attr;
  }

  void setShiftAxis(::llvm::APInt attrValue);
  void setOffsetAttr(::mlir::IntegerAttr attr) {
    getProperties().offset = attr;
  }

  void setOffset(uint64_t attrValue);
  void setRotateAttr(::mlir::UnitAttr attr) {
    getProperties().rotate = attr;
  }

  void setRotate(bool attrValue);
  ::mlir::Attribute removeRotateAttr() {
      auto attr = getProperties().rotate;
      getProperties().rotate = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate = nullptr);
  static ShiftOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate = nullptr);
  static ShiftOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate = nullptr);
  static ShiftOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate = nullptr);
  static ShiftOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr grid, ::mlir::DenseI16ArrayAttr grid_axes, ::mlir::Value input, ::mlir::IntegerAttr shift_axis, ::mlir::IntegerAttr offset, /*optional*/::mlir::UnitAttr rotate = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate = false);
  static ShiftOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate = false);
  static ShiftOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate = false);
  static ShiftOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate = false);
  static ShiftOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef grid, ::llvm::ArrayRef<int16_t> grid_axes, ::mlir::Value input, ::llvm::APInt shift_axis, uint64_t offset, /*optional*/bool rotate = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShiftOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShiftOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShiftOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShiftOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::ShiftOp)

namespace mlir::shard {


//===----------------------------------------------------------------------===//
// ::mlir::shard::UpdateHaloOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UpdateHaloOpGenericAdaptorBase {
public:
  struct Properties {
    using gridTy = ::mlir::FlatSymbolRefAttr;
    gridTy grid;

    auto getGrid() const {
      auto &propStorage = this->grid;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGrid(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->grid = propValue;
    }
    using split_axesTy = ::mlir::shard::GridAxesArrayAttr;
    split_axesTy split_axes;

    auto getSplitAxes() const {
      auto &propStorage = this->split_axes;
      return ::llvm::cast<::mlir::shard::GridAxesArrayAttr>(propStorage);
    }
    void setSplitAxes(const ::mlir::shard::GridAxesArrayAttr &propValue) {
      this->split_axes = propValue;
    }
    using static_halo_sizesTy = ::mlir::DenseI64ArrayAttr;
    static_halo_sizesTy static_halo_sizes;

    auto getStaticHaloSizes() const {
      auto &propStorage = this->static_halo_sizes;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setStaticHaloSizes(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->static_halo_sizes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.grid == this->grid &&
        rhs.split_axes == this->split_axes &&
        rhs.static_halo_sizes == this->static_halo_sizes &&
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
  UpdateHaloOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("shard.update_halo", odsAttrs.getContext());
  }

  UpdateHaloOpGenericAdaptorBase(UpdateHaloOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGridAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
    return attr;
  }

  ::llvm::StringRef getGrid();
  ::mlir::shard::GridAxesArrayAttr getSplitAxesAttr() {
    auto attr = ::llvm::cast<::mlir::shard::GridAxesArrayAttr>(getProperties().split_axes);
    return attr;
  }

  ::mlir::shard::GridAxesArrayAttr getSplitAxes();
  ::mlir::DenseI64ArrayAttr getStaticHaloSizesAttr();
  ::llvm::ArrayRef<int64_t> getStaticHaloSizes();
};

} // namespace detail
template <typename RangeT>
class UpdateHaloOpGenericAdaptor : public detail::UpdateHaloOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UpdateHaloOpGenericAdaptorBase;
  static constexpr int odsIndex_destination = 0;
  static constexpr int odsIndex_halo_sizes = 1;
public:
  UpdateHaloOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UpdateHaloOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : UpdateHaloOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UpdateHaloOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UpdateHaloOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UpdateHaloOpGenericAdaptor(RangeT values, const UpdateHaloOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UpdateHaloOp, typename = std::enable_if_t<std::is_same_v<LateInst, UpdateHaloOp>>>
  UpdateHaloOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDestination() {
    return (*getODSOperands(0).begin());
  }

  RangeT getHaloSizes() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UpdateHaloOpAdaptor : public UpdateHaloOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UpdateHaloOpGenericAdaptor::UpdateHaloOpGenericAdaptor;
  UpdateHaloOpAdaptor(UpdateHaloOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UpdateHaloOp : public ::mlir::Op<UpdateHaloOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::DestinationStyleOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UpdateHaloOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UpdateHaloOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_destination = 0;
  static constexpr int odsIndex_halo_sizes = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("grid"), ::llvm::StringRef("split_axes"), ::llvm::StringRef("static_halo_sizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGridAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGridAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSplitAxesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSplitAxesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStaticHaloSizesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStaticHaloSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("shard.update_halo");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getDestination() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getHaloSizes() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getDestinationMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getHaloSizesMutable();
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
  ::mlir::FlatSymbolRefAttr getGridAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().grid);
  }

  ::llvm::StringRef getGrid();
  ::mlir::shard::GridAxesArrayAttr getSplitAxesAttr() {
    return ::llvm::cast<::mlir::shard::GridAxesArrayAttr>(getProperties().split_axes);
  }

  ::mlir::shard::GridAxesArrayAttr getSplitAxes();
  ::mlir::DenseI64ArrayAttr getStaticHaloSizesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DenseI64ArrayAttr>(getProperties().static_halo_sizes);
  }

  ::llvm::ArrayRef<int64_t> getStaticHaloSizes();
  void setGridAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().grid = attr;
  }

  void setGrid(::llvm::StringRef attrValue);
  void setSplitAxesAttr(::mlir::shard::GridAxesArrayAttr attr) {
    getProperties().split_axes = attr;
  }

  void setStaticHaloSizesAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().static_halo_sizes = attr;
  }

  void setStaticHaloSizes(::llvm::ArrayRef<int64_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes = nullptr);
  static UpdateHaloOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes = nullptr);
  static UpdateHaloOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes = nullptr);
  static UpdateHaloOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes = nullptr);
  static UpdateHaloOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::mlir::FlatSymbolRefAttr grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::mlir::DenseI64ArrayAttr static_halo_sizes = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes = {});
  static UpdateHaloOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes = {});
  static UpdateHaloOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes = {});
  static UpdateHaloOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes = {});
  static UpdateHaloOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value destination, ::llvm::StringRef grid, ::mlir::shard::GridAxesArrayAttr split_axes, ::mlir::ValueRange halo_sizes, ::llvm::ArrayRef<int64_t> static_halo_sizes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UpdateHaloOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UpdateHaloOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UpdateHaloOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UpdateHaloOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
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
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  MutableOperandRange getDpsInitsMutable() { return getDestinationMutable(); }
};

} // namespace mlir::shard
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::shard::UpdateHaloOp)


#endif // GET_OP_CLASSES

